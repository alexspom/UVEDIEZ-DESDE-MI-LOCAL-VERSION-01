/*
* Módulo : EOSPCDISP.C
* Objeto: Tratamiento de la estructura de displays en sistema EOS
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-12-2007

* MODIFICACIONES
* --
*/
#include "eospc.h"

static displays disp[MAXTOTDISPLAYS];
static displays *pdispserie[MAXTOTDISPLAYS];
static displays *pdispnumdisp[MAXTOTDISPLAYS];
static int numdisplays=0,numdserie=0,numdnumdisp=0;

etherboxs eth[MAXETHER];

tecladisps tecdisp[MAXTECLAS];
int numteclasdisp;

static int buscaposporserie(long serie)
{
  int alto=numdserie-1,bajo=0,medio;
  while (bajo<=alto) {
        medio=(alto+bajo)/2;
        if (pdispserie[medio]->serie<serie) bajo=medio+1;
        if (pdispserie[medio]->serie>serie) alto=medio-1;
        if (pdispserie[medio]->serie==serie) return(medio);
    }
  return(bajo);
}

static displays *buscaporserie(long serie)
{
  int pos;
  pos=buscaposporserie(serie);
  if (pos>=numdserie) return(NULL);
  if (pdispserie[pos]->serie==serie) return(pdispserie[pos]);
  return(NULL);
}

static void insertaporserie(displays *pdisp)
{
  int pos;
  if (pdisp->serie==0) return;
  pos=buscaposporserie(pdisp->serie);
  if (pos<numdserie) {
     int j;
     for (j=numdserie+1;j>pos;j--) {
         pdispserie[j]=pdispserie[j-1];
      }
   }
  pdispserie[pos]=pdisp;
  numdserie++;
}

static int buscapospornumdisp(long numdisp)
{
  int alto=numdnumdisp-1,bajo=0,medio;
  while (bajo<=alto) {
        medio=(alto+bajo)/2;
        if (pdispnumdisp[medio]->numdisp<numdisp) bajo=medio+1;
        if (pdispnumdisp[medio]->numdisp>numdisp) alto=medio-1;
        if (pdispnumdisp[medio]->numdisp==numdisp) return(medio);
    }
  return(bajo);
}

static displays *buscapornumdisp(long numdisp)
{
  int pos;
  pos=buscapospornumdisp(numdisp);
  if (pos>=numdnumdisp) return(NULL);
  if (pdispnumdisp[pos]->numdisp==numdisp) return(pdispnumdisp[pos]);
  return(NULL);
}

static int borrapornumdisp(long numdisp)
{
  int pos;
  pos=buscapospornumdisp(numdisp);
  if (pos>=numdnumdisp) return(1);
  if (pdispnumdisp[pos]->numdisp==numdisp) {
     int j;
     pdispnumdisp[pos]->numdisp=0;
     for (j=pos;j<numdnumdisp;j++) pdispnumdisp[j]=pdispnumdisp[j+1];
     numdnumdisp--;
     return(0);
   }
  return(1);
}

static void insertapornumdisp(displays *pdisp)
{
  int pos;
  if (pdisp->numdisp==0) return;
  pos=buscapospornumdisp(pdisp->numdisp);
  if (pos<numdnumdisp) {
     int j;
     for (j=numdnumdisp+1;j>pos;j--) {
         pdispnumdisp[j]=pdispnumdisp[j-1];
      }
   }
  pdispnumdisp[pos]=pdisp;
  numdnumdisp++;
}

void cambianumdisp(long primero,long anterior,long nuevo)
{
  int pos,i;
  pos=buscapospornumdisp(primero);
  if (nuevo>anterior) for (i=pos+anterior;i<numdnumdisp;i++) pdispnumdisp[i]->numdisp+=nuevo-anterior;
     else             {
        for (i=primero+nuevo;i<primero+anterior;i++) borrapornumdisp(i);
        for (i=pos+nuevo;i<numdnumdisp;i++) pdispnumdisp[i]->numdisp+=nuevo-anterior;
      }
}

static displays *nuevodisplay(long serie,long numdisp,int tipo)
{
  displays *pdisp;
  int pos;
  pdisp=disp+numdisplays;
  pdisp->serie=serie;
  pdisp->numdisp=numdisp;
  pdisp->tipo=tipo;
  pdisp->ptipo=dametipo(tipo);
  if (serie) {
     pos=buscaposporserie(serie);
     if (pos<numdserie) {
        int j;
        for (j=numdserie;j>pos;j--) {
            pdispserie[j]=pdispserie[j-1];
         }
      }
     pdispserie[pos]=pdisp;
     numdserie++;
   }
  if (numdisp) {
     insertapornumdisp(pdisp);
  }
  numdisplays++;
  return(pdisp);
}

static displays *dadealtadisp(long serie,long numdisp,int tipo)
{
  displays *pdisp;
  if (serie==0 && numdisp==0) return(NULL);
  if (serie!=0) {
     pdisp=buscaporserie(serie);
     if (pdisp==NULL) {
        pdisp=nuevodisplay(serie,numdisp,tipo);
     }
  } else {
     pdisp=buscapornumdisp(numdisp);
     if (pdisp==NULL) {
        pdisp=nuevodisplay(serie,numdisp,tipo);
     }
  }
  return(pdisp);
}

displays *revisadisp(long serie,long numdisp,int tipo)
{
  displays *pdisp,*antdisp=NULL;
  pdisp=buscaporserie(serie);
  if (numdisp!=0) antdisp=buscapornumdisp(numdisp);
  if (pdisp!=NULL) {
     if (pdisp!=antdisp) {
        if (antdisp!=NULL) {
           borrapornumdisp(antdisp->numdisp);
           antdisp->numdisp=0;
           antdisp->modificado=1;
           MODIFICADOINFO++;
         }
        if (pdisp->numdisp!=0) {
           if (pdisp->numdisp!=numdisp) {
              int neth,nlin,ndisp;
              int neth1,nlin1,ndisp1;
              dimedatosdisp(numdisp,&neth,&nlin,&ndisp);
              dimedatosdisp(pdisp->numdisp,&neth1,&nlin1,&ndisp1);
              escribe_log(LOGERROR,"El display de numero de serie %d  Estaba en %d-%d-%d y esta en %d-%d-%d\n",serie,neth1+1,nlin1+1,ndisp1,neth+1,nlin+1,ndisp);
            }
           borrapornumdisp(pdisp->numdisp);
         }
        pdisp->numdisp=numdisp;
        pdisp->tipo=tipo;
        insertapornumdisp(pdisp);
        pdisp->modificado=1;
        MODIFICADOINFO++;
        return(pdisp);
      } else return(pdisp);
   } else {
     if (antdisp!=NULL) {
        antdisp->serie=serie;
        antdisp->tipo=tipo;
        insertaporserie(antdisp);
        antdisp->modificado=1;
        MODIFICADOINFO++;
        return(antdisp);
      } else {
        pdisp=dadealtadisp(serie,numdisp,tipo);
        pdisp->modificado=1;
        MODIFICADOINFO++;
        return(pdisp);
      }
   }
}

displays *damedisplayid(int tipoid,long iddisplay)
{
  displays *pdisp;
  if (tipoid==TIPOIDSERIE) pdisp=dadealtadisp(iddisplay,0,0);
     else                  pdisp=dadealtadisp(0,iddisplay,0);
  return(pdisp);
}

displays *damedisplay(long iddisplay)
{
  displays *pdisp;
  if (tipoidentdisp==TIPOIDSERIE) pdisp=dadealtadisp(iddisplay,0,0);
     else                         pdisp=dadealtadisp(0,iddisplay,0);
  return(pdisp);
}


int vdisplayprintfp(displays *p,char *format,va_list arg)
{
  char cadena[MAXCADENA];
  int ret;
  ret=vsprintf(cadena,format,arg);
  //if (strcmp(p->valor,cadena)) {
     strcopia(p->valor,cadena,sizeof(p->valor)-1);
     if (p->luces[0]==0) p->luces[0]=1;
     p->modificado=1;
     MODIFICADOINFO++;
   //}
  return(ret);
}

int displayprintfp(displays *p,char *format,...)
{
  int ret;
  va_list arg;
  va_start(arg,format);
  ret=vdisplayprintfp(p,format,arg);
  va_end(arg);
  return(ret);
}

int vdisplayprintfid(int tipoid,long iddisplay,char *format,va_list arg)
{
  displays *pdisp;
  int ret;
  pdisp=damedisplayid(tipoid,iddisplay);
  if (pdisp==NULL) {
     v10log(LOGERROR,"Intentando escribir en display 0\n");
     return(0);
   }
  ret=vdisplayprintfp(pdisp,format,arg);
  return(ret);
}

int displayprintfid(int tipoid,long iddisplay,char *format,...)
{
  int ret;
  va_list arg;
  va_start(arg,format);
  ret=vdisplayprintfid(tipoid,iddisplay,format,arg);
  va_end(arg);
  return(ret);
}

void lucesdisplayp(displays *p,int numluz,int valor)
{
  if (p->luces[numluz]!=(unsigned short) valor) {
     p->luces[numluz]=(unsigned short)valor;
     p->modificado=1;
     MODIFICADOINFO++;
   }
}

void togglelucesdisplayp(displays *p,int numluz)
{
  p->luces[numluz]=(short)(p->luces[numluz]?0:3);
  p->modificado=1;
  MODIFICADOINFO++;
}

void lucesdisplayid(int tipoid,long iddisplay,int numluz,int valor)
{
   displays *pdisp;
   pdisp=damedisplayid(tipoid,iddisplay);
   if (pdisp==NULL) {
      v10log(LOGERROR,"Intentando escribir en display 0\n");
      return;
    }
   lucesdisplayp(pdisp,numluz,valor);
}

void togglelucesdisplayid(int tipoid,long iddisplay,int numluz)
{
   displays *pdisp;
   pdisp=damedisplayid(tipoid,iddisplay);
   if (pdisp==NULL) {
      v10log(LOGERROR,"Intentando escribir en display 0\n");
      return;
    }
   togglelucesdisplayp(pdisp,numluz);
}

int statusdisplayp(displays *p)
{
   return(p->status[0]);
}

int statusdisplayid(int tipoid,long iddisplay)
{
   displays *pdisp;
   pdisp=damedisplayid(tipoid,iddisplay);
   if (pdisp==NULL) {
      v10log(LOGERROR,"Intentando escribir en display 0\n");
      return(0);
    }
   return(statusdisplayp(pdisp));
}

void encolatecladispp(displays *p,int boton,int causa)
{
  if (numteclasdisp>=MAXTECLAS-1) return;
  tecdisp[numteclasdisp].numdisp=p->numdisp;
  tecdisp[numteclasdisp].serie=p->serie;
  tecdisp[numteclasdisp].boton=boton;
  tecdisp[numteclasdisp].causa=causa;
  tecdisp[numteclasdisp].version=p->version;
  numteclasdisp++;
}

void encolatecladispid(int tipoid,long iddisplay,int boton,int causa)
{
   displays *pdisp;
   pdisp=damedisplayid(tipoid,iddisplay);
   if (pdisp==NULL) {
      v10log(LOGERROR,"Intentando escribir en display 0\n");
      return;
    }
   encolatecladispp(pdisp,boton,causa);
}

int haytecladisp(void)
{
  return(numteclasdisp);
}

int tecladisp(tecladisps *tec)
{
  if (numteclasdisp==0) return(0);
  *tec=tecdisp[0];
  memcpy(tecdisp,tecdisp+1,(numteclasdisp-1)*sizeof(tecladisps));
  numteclasdisp--;
  return(1);
}
