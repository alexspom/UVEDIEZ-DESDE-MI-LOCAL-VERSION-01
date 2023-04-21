/*
* Módulo : V10FORFORM.C
* Objeto:  Tratamiento de generico de la estructura forms
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"

forms *formglobal;
int protegidoform;

int limpiaform(forms *f, ftrigers *ft)
{
  int ret=0;
  int nb;
  for (nb=0;nb<f->nbloques;nb++) {
      f->preguntar=0;
      borrabloque(f->b[nb],ft);
    }
  f->modif=0;
  f->preguntar=1;
  return(ret);
}

int rollbackform(forms *f, ftrigers *ft)
{
  int ret;
  if (f->modif) {
     if ((ret=commitsino(f))!=0) return(ret);
   }
  if (f->prerollback)
     if ((ret=f->prerollback->fun(f->b[0],f->prerollback))!=0) {
        f->preguntar=1;
        return(ret);
      }
  rollback();
  if (f->postrollback)
     f->postrollback->fun(f->b[0],f->postrollback);
  ret=limpiaform(f,ft);
  return(ret);
}

static int llcommitform(forms *f)
{
  int ret=0;
  long pos;
  int nb;
  if (f->modif==0) {
     mensajeform(f,"No hay cambios que realizar");
     return(0);
   }
  savepoint("FCOMMIT");
  f->preguntar=1;
  f->ninsert=f->nupdate=f->ndelete=0;
  if (f->precommit) {
     setaction("PRECOMMIT FORM");
     ret=f->precommit->fun(f->b[0],f->precommit);
   }
  if (ret) {
     rollbacksavepoint("FCOMMIT");
     return(ret);
   }
  for (nb=0;nb<f->nbloques;nb++) {
	  bloques *b=f->b[nb];
      if (b->padre && (b->modif==1 || b->sicommit) && !b->nocommit) {
	     if (b->regpadre!=VIRTPOS(b->padre->s)) {
            rollbacksavepoint("FCOMMIT");
		    mensajefcm(10,"No puedo modificar datos del registro porque dependen del registro %d",b->regpadre);
		    return(-1);
		 }
	  }
	  if ((b->modif==0 || b->nocommit) && !b->sicommit) continue;	    
      ret=commitbloque(b);
      setmodule("","");
      if (ret) {
         pos=(ftell(b->fbuffer)/b->tamano/2)-1;
         reposiciona(b->s,(unsigned)pos);
         f->act=nb;
         rollbacksavepoint("FCOMMIT");
		 break;
       }
   }
  if (ret==0) {
     if (f->postcommit) {
        setaction("POSTCOMMIT FORM");
        ret=f->postcommit->fun(f->b[0],f->postcommit);
	 }
  }
  if (ret) {
     for (nb=0;nb<f->nbloques;nb++) {
         terminarollbackbloque(f->b[nb]);
       }
     rollbacksavepoint("FCOMMIT");
     return(ret);
   } else  {
     for (nb=0;nb<f->nbloques;nb++) {
         terminacommitbloque(f->b[nb]);
       }
     ret=commit();
     if (ret) return(ret);
     f->modif=0;
    }
  mensajeform(f,"%3d Registros tratados %3d Insertados %3d borrados %3d modificados",f->ninsert+f->ndelete+f->nupdate,f->ninsert,f->ndelete,f->nupdate);
  return(ret);
}

int commitform(forms *f, ftrigers *ft)
{
  int ret;
  char modulo[LMODULE];
  sprintf(modulo,"FORM: %s",f->nombre);
  setmodule(modulo,"");
  ret=llcommitform(f);
  setmodule("","");
  return(ret);
}

int mirasimodif(forms *f)
{
  int nb;
  f->modif=0;
  for (nb=0;nb<f->nbloques;nb++) {
      if ((f->b[nb]->modif && !f->b[nb]->nocommit) || (f->b[nb]->sicommit && f->b[nb]->enquery)) f->modif=1;
    }
  return(0);
}


void liberaform(forms *f)
{
  int nb,i;
  if (f==NULL) {
     mensajefcm(10,"Intentando liberar form nulo");
     return;
   }
  for (nb=0;nb<f->nbloques;nb++) {
      liberabloque(f->b[nb]);
    }
  liberatriger(f->precommit);
  liberatriger(f->postcommit);
  liberatriger(f->prerollback);
  liberatriger(f->postrollback);
  liberatriger(f->preform);
  liberatriger(f->postform);
  for (i=0;i<f->ncamp;i++) {
      liberacampo(f->c+i);
    }
  free(f->buffer);
  free(f->ant);
  free(f->bufuquery);
  free(f->c);
  free(f);
  setmodule("","");
}

int teclaform(int ret)
{
  limpiamensaje(formglobal);
  return(ret);
}


void cargaform(char *nombre,char *opciones)
{
    forms *antform=formglobal;
    formglobal=leeform(nombre,opciones);
	if (v10versionweb) cargahtmlconf(); 
	rellenadefault();
    if (formglobal) {
        formglobal->preguntar=1;
        finputform(formglobal);
        liberaform(formglobal);
    }
    formglobal=antform;
}

void initform(void)
{
    GetTempPath(MAXPATH,DIRTEMP);
    inittriger();
    asignatecla(ALT('D'),toggleoradebug);
}


int STDcommitsino(forms *f)
{
  char *opciones[]={"Desea Confirmar Cambios","Si","No",NULL};
  int ret=-1;
  int antpul=ult_pul;
  if (f->preguntar==0) return(0);
  while (ret<0) {
        ret=menu(opciones,1,30,10);
        if (ult_pul!=13) ret=-1;
      }
  ult_pul=antpul;
  if (ret==0) ret=commitform(f,NULL);
     else     ret=0;
  f->preguntar=0;
  return(ret);
}