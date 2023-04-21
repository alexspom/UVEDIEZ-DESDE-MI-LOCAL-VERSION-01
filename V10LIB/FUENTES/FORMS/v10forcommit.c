/*
* Módulo : V10FORCOMMIT.C
* Objeto:  Tratamiento de commits en bloques de formularios
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"


static int ejecutaforacle(bloques *b,v10cursors *lc)
{
  int ret;
  ret=convierte2db(b,lc);
  if (ret==0) ret=ejecutacursor(lc);
  if (ret) {
     FORM(b)->oraerr=ret;
	  if (ret==DUPLICADO) formerror(FORM(b),"Clave duplicada");
        else if (ret!=BLOQUEADO)  cursordebug(lc); 	 
   }
  return(ret);
}

static int ejecutadeletes(bloques *b)
{
  int ret=0;
  forms *f=FORM(b);
  rewind(b->fdelete);
  while (fread(b->buffer,1,(unsigned)2*b->tamano,b->fdelete)) {
        if (CABECERA(b)->antiguo) {
           if (b->fpredelete) {
              setaction("PREDELETE");
              ret=ejecutaftriger(b,PPREDELETE,b->fpredelete,NULL);
            }
           if (ret==0) {                         
               if (b->nooradel==0) {
                 setaction("DELETE");
                 if (b->delete==NULL) gendelete(b);
                 ret=convierte2db(b,b->delete);
                 if (ret==0) ret=ejecutaforacle(b,b->delete);
               } 
               if (ret) {
                 FORM(b)->oraerr=ret;
               } else {
                 if (b->fpostdelete) {
                    setaction("POSTDELETE");
                    ret=ejecutaftriger(b,PPOSTDELETE,b->fpostdelete,NULL);
                  }
               }
            }
          if (ret) {
             insertaregistropos(b,0);
             b->s->numero++;
             b->s->numlin++;
             fseek(b->fdelete,-2L*b->tamano,SEEK_CUR);
             fread(b->buffer,2,(unsigned)b->tamano,b->fdelete);
             CABECERA(b)->antiguo=0;
             fseek(b->fdelete,-2L*b->tamano,SEEK_CUR);
             fwrite(b->buffer,2,(unsigned)b->tamano,b->fdelete);
             CABECERA(b)->antiguo=1;
             grabareg(b,0);
             reposiciona(b->s,0);
             representapagina(b->s);
             setaction("");
             return(ret);
            }
          f->ndelete++;
        }
    }
 setaction("");
 return(0);
}

static int llbloquearegistro(bloques *b,int nreg)
{
  int ret,nc;
  char *dupreg;
  if (b->nolock) return(0);
  if (CABECERA(b)->antiguo==0) return(0);
  if (CABECERA(b)->lock) return(0);
  dupreg=calloc(1,(unsigned)2*b->tamano);
  memcpy(dupreg,b->buffer,(unsigned)2*b->tamano);
  memcpy(b->buffer,b->buffer+b->tamano,(unsigned)b->tamano);
  if (b->lock==NULL) genlock(b);

  if (!llbloquearegistroaux)
	  mensajeform(FORM(b),"Bloqueando registro pulse ^A para abortar");
  while ((ret=ejecutaforacle(b,b->lock))==BLOQUEADO) {
	  if (!llbloquearegistroaux) {
		  if (hay_tecla()) {
			  if (tecla()==1) break;
		  }
		  Sleep(10);
	  } else {
			if (llbloquearegistroaux(b)==-1)
				break;
	  }
  }
  if (ret!=0 && ret!=BLOQUEADO) cursordebug(b->lock);
  if (ret==0) {
      CABECERA(b)->lock=1;
      while ((ret=fetchcursor(b->lock))==BLOQUEADO) {
		  if (!llbloquearegistroaux) {
			  if (hay_tecla()) {
				  if (tecla()==1) break;
			  }
          }
		  else {
			if (llbloquearegistroaux(b)==-1)
				break;			 		
		  }
	  }
     }
  
  limpiamensaje(FORM(b));
  if (ret!=0 && ret!=BLOQUEADO) cursordebug(b->lock);
  memcpy(b->ant,b->buffer,b->tamano);
  memcpy(b->buffer,dupreg+b->tamano,b->tamano);
  memcpy(b->buffer+b->tamano,dupreg,b->tamano);
  if ((nc=compararegistrolock(b))==0 && ret==0) {
     memcpy(b->buffer,dupreg,(unsigned)b->tamano*2);
     memcpy(b->ant,b->buffer+b->tamano,b->tamano);
     CABECERA(b)->lock=1;
   } else {
	 memcpy(b->buffer,b->ant,b->tamano);
     if (b->fpostquery) {
        ret=ejecutaftriger(b,PPOSTQUERY,b->fpostquery,NULL);
        switch (ret) {
                   case 0:break;
                   case IGNORAR:break;
                   default:CABECERA(b)->updated=1;
                           break;
             }
       }
     ejecutapostchange(b);
     memcpy(b->buffer+b->tamano,b->buffer,b->tamano);
     grabareg(b,nreg);
     if (nc==0) wmensajeform(b,"El registro no se puede bloquear");
        else    wmensajeform(b,"El campo %s ha sido mofificado desde otra sesion",b->c[nc-1].nombre);
     if (ret==0) ret=-1;
   }
  free(dupreg);
  return(ret);
}

int llcommitbloque(bloques *b)
{
  int  nreg=0;
  int  ret=0;
  forms *f=FORM(b);
  char module[2*MAXPATH];
	int antpos = b->s->clin;
  sprintf(module,"FORM: %s/%s",b->form->nombre,b->fichero);
  if ((b->modif==0 || b->nocommit) && !b->sicommit) return(0);
  setmodule(module,"");
  if (b->fprecommit) {
     setaction("PRECOMMIT BLOQUE");
     ret=ejecutaftriger(b,PPRECOMMIT,b->fprecommit,NULL);
   }
  if (ret) return(ret);
  grabaregistro(b,VIRTPOS(b->s));
  rewind(b->fbuffer);
  if (!b->nodelete) {
     ret=ejecutadeletes(b);
     if (ret) return(ret);
   }
  while (fread(b->buffer,(unsigned)2*b->tamano,1,b->fbuffer)) {
      b->s->clin = nreg;
    if (!esnuloregistro(b) && CABECERA(b)->modif) {
       fcampos *c;
       if ((c=primerinvalido(b))!=NULL) {
          posicionadialog(&b->vi,direccampoptr(b,c));
          return(*FERROR(b,c));
        }
       if (CABECERA(b)->antiguo) {
          if (!CABECERA(b)->updated) {
             if (!b->soloquery && CABECERA(b)->lock==0) {
                ret=llbloquearegistro(b,nreg);
                if (ret) return(ret);
              }
             if (b->fpreupdate) {
                setaction("PREUPDATE");
                ret=ejecutaftriger(b,PPREUPDATE,b->fpreupdate,NULL);
                if (ret) return(ret);
              }
             if (!b->noupdate) {  
                setaction("UPDATE");
				memcpy(b->ant,b->buffer+b->tamano,b->tamano);
                if (b->update==NULL) genupdate(b);
                if (b->update!=NULL) {
                   ret=convierte2db(b,b->update);
                   if (ret==0) ret=ejecutaforacle(b,b->update);
				   liberacursor(b->update);
				   b->update=NULL;
                   if (ret) {
                      FORM(b)->oraerr=ret;
                      return(ret);
				   }
				}
              }
             if (b->fpostupdate) {
                setaction("POSTUPDATE");
                ret=ejecutaftriger(b,PPOSTUPDATE,b->fpostupdate,NULL);
                if (ret) return(ret);
              }
             grabareg(b,nreg);
             f->nupdate++;
           }
         } else {
           if (b->fpreinsert) {
              setaction("PREINSERT");
              ret=ejecutaftriger(b,PPREINSERT,b->fpreinsert,NULL);
              if (ret) return(ret);
            }
           if (!b->noinsert && !b->noorains) {   
              setaction("INSERT");
              if (b->insert==NULL) geninsert(b);
              ret=ejecutaforacle(b,b->insert);
			  if (b->insert->funsql==FSELECT) fetchcursor(b->insert);
              if (ret) {
                 FORM(b)->oraerr=ret;
                 return(ret);
               }
            }
           if (b->fpostinsert) {
              setaction("POSTINSERT");
              ret=ejecutaftriger(b,PPOSTINSERT,b->fpostinsert,NULL);
              if (ret) return(ret);
            }
           f->ninsert++;
           grabareg(b,nreg);
         }
     }
    nreg++;
   }
	b->s->clin = antpos;
  leeregistroi(b,VIRTPOS(b->s));
  if (b->fpostcommit)  {
     setaction("POSTCOMMIT BLOQUE");
     ret=ejecutaftriger(b,PPOSTCOMMIT,b->fpostcommit,NULL);
   }
  return(ret);
}

int commitbloque(bloques *b)
{
    int antpos = VIRTPOS(b->s);
    int ret;
    ret = llcommitbloque(b);
    b->s->clin = antpos;
    return(ret);
}

int terminacommitbloque(bloques *b)
{
  long VIRTPOS;
  int nreg=0;
  int ret=0;
  if ((b->modif==0 || b->nocommit) && !b->sicommit) return(0);
  chsize(fileno(b->fdelete),0);
  VIRTPOS=ftell(b->fbuffer);
  rewind(b->fbuffer);
  b->modif=0;
  while (fread(b->buffer,(unsigned)2*b->tamano,1,b->fbuffer)) {
        CABECERA(b)->lock=0;
        if (CABECERA(b)->antiguo && CABECERA(b)->modif) {
            CABECERA(b)->modif=0; 
            memcpy(b->buffer+b->tamano,b->buffer,b->tamano);
            grabareg(b,nreg);
         } else if (CABECERA(b)->modif && !esnuloregistro(b)) {
                   if (!b->noinsert) {
                       CABECERA(b)->antiguo=1;
                       CABECERA(b)->modif=0;
                       memcpy(b->buffer+b->tamano,b->buffer,b->tamano);
                       grabareg(b,nreg);
                     }
                 }
       nreg++;
   }
  if (VIRTPOS) {
     leeregistroi(b,VIRTPOS(b->s));
   }
  fseek(b->fbuffer,VIRTPOS,SEEK_SET);
  return(ret);
}

int terminarollbackbloque(bloques *b)
{
  long VIRTPOS;
  int nreg=0;
  int ret=0;
  if ((b->modif==0 || b->nocommit) && !b->sicommit) return(0);
  chsize(fileno(b->fdelete),0);
  VIRTPOS=ftell(b->fbuffer);
  rewind(b->fbuffer);
  while (fread(b->buffer,(unsigned)2*b->tamano,1,b->fbuffer)) {
	  if (CABECERA(b)->lock) {
		  CABECERA(b)->lock=0;
          grabareg(b,nreg);
       }
      nreg++;
   }
  if (VIRTPOS) {
     leeregistroi(b,VIRTPOS(b->s));
   }
  fseek(b->fbuffer,VIRTPOS,SEEK_SET);
  return(ret);
}