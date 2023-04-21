// Modulo generado automaticamente a partir de VDSEMAFOROAUX.DEF
//# Módulo : VDSEMAFOROAUX.DEF                                                         
//
//# Propósito: Funciones extra de acceso a los semaforos
//#
//# Autor	 : Eduardo Alsina
//# Revisado por:
//# Fecha  : 24-01-2008
//#********************************************************************************
//# Modificaciones
//#***
//
//NOMBRE=SEMA;
//
//
//PROCEDURE=DAMESEMAFORO,DECLARE
//                         ESTADO NUMBER;
//                       BEGIN 
//                          ESTADO:=VDSEM.DAMESEMAFORO(:VDSEMAFORO.CODSEMAFORO,'N');
//                          IF ESTADO!=0 THEN 
//                             RAISE NO_DATA_FOUND;
//                          END IF;
//                       END;@
//                       
//PROCEDURE=LIBERASEMAFORO,BEGIN
//                           VDSEM.LIBERASEMAFORO(:VDSEMAFORO.CODSEMAFORO);
//                         END;@     
//                         
//%%h
//VDEXPORT int damesemaforo(char *semaforo);
//VDEXPORT int liberasemaforo(char *semaforo);
//%%c      
//int damesemaforo(char *semaforo)
//{
//   vdsemas sema;
//   int ret;
//   ret=SEMAprocdamesemaforo(semaforo,&sema);
//   v10log(LOGDEBUG,"Adquiriendo semaforo %s error %d\n",semaforo,ret);
//   return(ret);
//}   
//
//int liberasemaforo(char *semaforo)
//{
//   vdsemas sema;
//   int ret;
//   ret=SEMAprocliberasemaforo(semaforo,&sema);
//   v10log(LOGDEBUG,"Liberando semaforo %s error %d\n",semaforo,ret);
//   return(ret);
//}                                  

#include "vd.h"\

#define SELDAMESEMAFORO "DECLARE ESTADO NUMBER; BEGIN  ESTADO:=VDSEM.DAMESEMAFORO(:CODSEMAFORO,'N'); IF ESTADO!=0 THEN  RAISE NO_DATA_FOUND; END IF; END;"
static v10cursors *vdseldamesemaforo;
#define SELLIBERASEMAFORO "BEGIN VDSEM.LIBERASEMAFORO(:CODSEMAFORO); END;"
static v10cursors *vdselliberasemaforo;

static vdsemas svdsema;

static diccols colvdsema[]={ 
    {"CODSEMAFORO",V10CADENA,(size_t)&svdsema.codsemaforo,sizeof(svdsema.codsemaforo)}
    };

static diccionarios dvdsema[]={
    {colvdsema,1}
    };

diccionario dsema={dvdsema,1};

static char msgdebugsema[LCADENABIG];

static int init=0;


static void fin_vd_SEMA(void)
{
    if(vdseldamesemaforo){
        liberacursor(vdseldamesemaforo);
        vdseldamesemaforo=NULL;
    }
    if(vdselliberasemaforo){
        liberacursor(vdselliberasemaforo);
        vdselliberasemaforo=NULL;
    }
}


static void init_seldamesemaforo(void)
{
    int nc;

    for(nc=0;nc<dvdsema[0].numcol;nc++) dvdsema[0].c[nc].offset-=(size_t)&svdsema;

    vdseldamesemaforo=abrecursordebug(SELDAMESEMAFORO,1024);
    definetodo(vdseldamesemaforo,NULL);
    bindtodo(vdseldamesemaforo,"CODSEMAFORO",svdsema.codsemaforo,sizeof(svdsema.codsemaforo),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_SEMA);
        init = 1;
    }
}

static void init_selliberasemaforo(void)
{
    int nc;

    for(nc=0;nc<dvdsema[0].numcol;nc++) dvdsema[0].c[nc].offset-=(size_t)&svdsema;

    vdselliberasemaforo=abrecursordebug(SELLIBERASEMAFORO,1024);
    definetodo(vdselliberasemaforo,NULL);
    bindtodo(vdselliberasemaforo,"CODSEMAFORO",svdsema.codsemaforo,sizeof(svdsema.codsemaforo),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_SEMA);
        init = 1;
    }
}

diccionario *SEMAdamediccionario(void)
{
    return(&dsema);
}

int SEMAprocdamesemaforo(char *codsemaforo,vdsemas *sema)
{
    int vdret;
    if (vdseldamesemaforo==NULL) init_seldamesemaforo();
    memset(&svdsema,0,sizeof(svdsema));
    strcpy(svdsema.codsemaforo,codsemaforo);
    vdret=ejecutacursor(vdseldamesemaforo);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta SEMAprocdamesemaforo vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *sema=svdsema;
    return(vdret);
}

int SEMAprocliberasemaforo(char *codsemaforo,vdsemas *sema)
{
    int vdret;
    if (vdselliberasemaforo==NULL) init_selliberasemaforo();
    memset(&svdsema,0,sizeof(svdsema));
    strcpy(svdsema.codsemaforo,codsemaforo);
    vdret=ejecutacursor(vdselliberasemaforo);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta SEMAprocliberasemaforo vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *sema=svdsema;
    return(vdret);
}

char * SEMAdebug(vdsemas *sema)
{
    debugestruct(&dsema,sema,msgdebugsema);
    return(msgdebugsema);
}


//Codigo incluido explicitamente en el DEF
int damesemaforo(char *semaforo)
{
   vdsemas sema;
   int ret;
   if (es_blanco(semaforo)) return(0);
   ret=SEMAprocdamesemaforo(semaforo,&sema);
   v10log(LOGDEBUG,"Adquiriendo semaforo %s error %d\n",semaforo,ret);
   return(ret);
}   

int liberasemaforo(char *semaforo)
{
   vdsemas sema;
   int ret;
   if (es_blanco(semaforo)) return(0);
   ret=SEMAprocliberasemaforo(semaforo,&sema);
   v10log(LOGDEBUG,"Liberando semaforo %s error %d\n",semaforo,ret);
   return(ret);
}                                  
