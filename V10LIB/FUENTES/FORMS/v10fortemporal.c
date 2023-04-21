/*
* Módulo : V10FORTEMPORAL.C
* Objeto:  Tratamiento de ficheros temporales de formulario
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"

char DIRTEMP[MAXPATH]="";
int FORMCON=-1;


void cierraficheroaux(bloques *b)
{
  if (b->fbuffer) {
     fclose(b->fbuffer);
     b->fbuffer=NULL;
     unlink(b->fname);
     free(b->fname);
     b->fname=NULL;
   }
  if (b->fdelete) {
     fclose(b->fdelete);
     b->fdelete=NULL;
     unlink(b->fndelete);
     free(b->fndelete);
     b->fndelete=NULL;
  }
}

void reabreficheroaux(bloques *b)
{
  long VIRTPOS=0;
  if (b->fbuffer) VIRTPOS=ftell(b->fbuffer);
  if (b->fbuffer) fclose(b->fbuffer);
  if ((b->fbuffer=fopen(b->fname,"r+b"))==NULL) final(("El fichero temporal no existe %s",b->fname));
  fseek(b->fbuffer,VIRTPOS,SEEK_SET);
}


void abreficheroaux(bloques *b)
{
  int nbloque;
  char *temp;
  nbloque=damenumbloque(b);
  //cierraficheroaux(b);
  if (FORMCON==-1) {
     FORMCON=damecon();
   }
  b->fname=calloc(1,MAXPATH);
  temp=getenv("TEMP");
  if (temp) sprintf(DIRTEMP,"%s/",temp);
  sprintf(b->fname,"%sFORR%08x%02x.TEM",DIRTEMP,FORMCON,nbloque);
  b->fndelete=calloc(1,MAXPATH);
  sprintf(b->fndelete,"%sFORB%08x%02x.TEM",DIRTEMP,FORMCON,nbloque);
  if (b->fbuffer) {
#ifdef __LINUX__
      ftruncate(fileno(b->fbuffer),0);
#else
	  _chsize(fileno(b->fbuffer), 0);
#endif
  } else {
  if ((b->fbuffer=fopen(b->fname,"w+b"))==NULL) {
		  final(("No puedo abrir fichero %s\n", b->fname));
	  }
   }
  if (b->fdelete) {
#ifdef __LINUX__
      ftruncate(fileno(b->fdelete),0);
#else
	  _chsize(fileno(b->fdelete), 0);
#endif
  } else {
  if ((b->fdelete=fopen(b->fndelete,"w+b"))==NULL) {
		  final(("No puedo abrir fichero %s\n", b->fndelete));
	  }
   }
  b->quedan=0;
}


void pordefectoregistro(bloques *b)
{
  int nc;
  memset(b->buffer,0,(unsigned)b->tamano);
  for (nc=0;nc<b->ncamp;nc++) {
	  fcampos *c=b->c+nc;
      if (c->virtual) continue;
      if (c->change) *FERROR(b,c)=-1;
	  *indicadorcampo(b,c,CINDDEC)=-1;
	  *indicadorcampo(b,c,CINDFORMATO)=-1;
	  *indicadorcampo(b,c,CINDSCAN)=-1;
	  *indicadorcampo(b,c,CINDLPAN)=-1;
	  *indicadorcampo(b,c,CINDENTER)=-1;
	  *indicadorcampo(b,c,CINDNOINPUT)=-1;
	  *indicadorcampo(b,c,CINDINVISIBLE)=-1;
	  *indicadorcampo(b,c,CINDNOUPDATE)=-1;
	  *indicadorcampo(b,c,CINDCOLOR)=-1;
	  *indicadorcampo(b,c,CINDAUTOENTER)=-1;
   }
  memcpy(b->buffer+b->tamano,b->buffer,b->tamano);
}

int insertaregistropos(bloques *b,long pos)
{
  long VIRTPOS,final;
  VIRTPOS=pos*b->tamano*2;
  final=(b->s->numero-1)*b->tamano*2;
  if (final<VIRTPOS) final=VIRTPOS;
  while (final>VIRTPOS) {
        fseek(b->fbuffer,final-2*b->tamano,SEEK_SET);
        while (fread(b->buffer,(unsigned)2*b->tamano,1,b->fbuffer)==0) { 
              reabreficheroaux(b);
              fseek(b->fbuffer,final-2*b->tamano,SEEK_SET);
            }
        fseek(b->fbuffer,final,SEEK_SET);
        if (fwrite(b->buffer,(unsigned)2*b->tamano,1,b->fbuffer)==0) final(("No puedo escribir fichero temporal"));
        final-=b->tamano*2;
     }
  pordefectoregistro(b);
  if (b->padre) {
     b->regpadre=VIRTPOS(b->padre->s);
  }
  fseek(b->fbuffer,final,SEEK_SET);
  if (fwrite(b->buffer,(unsigned)2*b->tamano,1,b->fbuffer)==0) final(("No puedo escribir en fichero temporal"));
  if (fflush(b->fbuffer)) final(("No puedo escribir en fichero temporal"));
  fseek(b->fbuffer,final,SEEK_SET);
  return(0);
}

int insertaregistro(bloques *b)
{
  int ret;
  ret=insertaregistropos(b,(VIRTPOS(b->s)+1));
  return(ret);
}

static void eliminaregistro(bloques *b)
{
  long VIRTPOS,final;
  VIRTPOS=(VIRTPOS(b->s)+1)*2*b->tamano;
  final=(b->s->numero-1)*2*b->tamano;
  fseek(b->fbuffer,VIRTPOS,SEEK_SET);
  while (fread(b->buffer,1,(unsigned)2*b->tamano,b->fbuffer)) {
        fseek(b->fbuffer,-4L*b->tamano,SEEK_CUR);
        if (fwrite(b->buffer,(unsigned)2*b->tamano,1,b->fbuffer)<1) final(("Grabando fichero temporal"));
        fseek(b->fbuffer,2*b->tamano,SEEK_CUR);
    }
  if (final) chsize(fileno(b->fbuffer),final-2*b->tamano);
  fseek(b->fbuffer,VIRTPOS-2*b->tamano,SEEK_SET);
  fread(b->buffer,1,(unsigned)2*b->tamano,b->fbuffer);
  fseek(b->fbuffer,VIRTPOS,SEEK_SET);
}

void grabareg(bloques *b,int pos)
{
  long off;
  off=pos*2*b->tamano;
  if (b->padre) {
     b->regpadre=VIRTPOS(b->padre->s);
  }
  if (b->fbuffer==NULL) reabreficheroaux(b);
  fseek(b->fbuffer,off,SEEK_SET);
  if (fwrite(b->buffer,(unsigned)2*b->tamano,1,b->fbuffer)==0) final(("No puedo escribir fichero temporal"));
  if (fflush(b->fbuffer))
     final(("No puedo escribir en temporal"));
  fseek(b->fbuffer,off+2*b->tamano,SEEK_SET);
}

int grabaregistro(bloques *b,int pos)
{
  if (compararegistro(b) && !(v10versionweb && formglobal->b[formglobal->act]!=b))  {
     CABECERA(b)->modif=1;
     if (!b->nocommit && (CABECERA(b)->antiguo || !b->noinsert)) {
        b->modif=1;
        FORM(b)->modif=1;
      }
  }
  grabareg(b,pos);
  return(0);
}

int leeregistroi(bloques *b,int i)
{
    int ret;
    fseek(b->fbuffer,i*2*b->tamano,SEEK_SET);
    if (fread(b->buffer,(unsigned)2*b->tamano,1,b->fbuffer)==0) {
        if (b->enquery && b->quedan) {
            while (1) {
                pordefectoregistro(b);
                if ((ret=fetchcursor(b->select))==0) {
                    conviertefromdb(b,b->select);
                    CABECERA(b)->antiguo=1;  
                    if (b->fpostquery) {
                        ret=ejecutaftriger(b,PPOSTQUERY,b->fpostquery,NULL);
                        switch (ret) {
                            case 0:break;
                            case IGNORAR:continue;
                           default:CABECERA(b)->updated=1;
                                   break;
                        }
                    }
                    ejecutapostchange(b);
                    memcpy(b->buffer+b->tamano,b->buffer,b->tamano);
                    grabareg(b,i);
                    ret=0;
                } else {
                    if (ret!=NOFOUND)
                        cursordebug(b->select);
                    insertaregistropos(b,i);
                    b->quedan=0;
                    if (b->ffinquery) {
                        ejecutaftriger(b,PFINQUERY,b->ffinquery,NULL);
                    }
                    ret=1;
                }
                break;
            }
        } else {
            if (!esnuloregistro(b) || VIRTPOS(b->s)==0) insertaregistropos(b,i);
            ret=1;
        }
    } else ret=0;
    memcpy(b->ant,b->buffer,(unsigned)b->tamano);
    return(ret);
}

int marcadelete(bloques *b)
{
  fseek(b->fdelete,0,SEEK_END);
  if (fwrite(b->buffer,(unsigned)2*b->tamano,1,b->fdelete)<1) final(("Grabando en fichero de borrados"));
  if (fflush(b->fdelete)) final(("No puedo escribir en fichero borrados"));
  eliminaregistro(b);
  return(0);
}
