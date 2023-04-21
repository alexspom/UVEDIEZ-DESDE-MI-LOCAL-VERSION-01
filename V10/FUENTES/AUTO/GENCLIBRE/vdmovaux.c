// Modulo generado automaticamente a partir de VDMOVAUX.DEF
//#***
//# VDSTOCK.DEF - Generación automática del código c SOLOQUERY sobre la tabla VDMOVIM                                                    
//# 
//# Propósito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 18-04-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=MOVAUX;
//EXTRA=RET,V10LONG
//EXTRA=STFINALIZADO,V10LONG
//EXTRA=STREVISION,V10LONG
//EXTRA=STPDTEINTER,V10LONG
//EXTRA=STSININTER,V10LONG
//EXTRA=STDEMLMVFINAL,V10LONG
//EXTRA=STDEMCMVFINAL,V10LONG
//EXTRA=NUEVOMOV,V10LONG
//EXTRA=LIMPIAR,V10CADENA,1
//EXTRA=AVANZA,V10LONG
//EXTRA=RESERVADO,V10DOUBLE
//
//PROCEDURE=PARTEMOV,DECLARE RET NUMBER;
//                   BEGIN
//                      RET:=VDMOV.PARTEMOV(:VDMOVIM.CODMOV,:VDMOVIM.CANTIDAD,:NUEVOMOV,:LIMPIAR);
//                      IF RET!=0 THEN RAISE NO_DATA_FOUND; END IF;
//                   END;@
//PROCEDURE=ANULAMOV,BEGIN
//                      VDMOV.ANULAMOV(:VDMOVIM.CODMOV,:RET);
//                   END;@      
//
//PROCEDURE=FINALIZAMOV,BEGIN
//                        VDMOV.FINALIZAMOV(:VDMOVIM.CODMOV,:STFINALIZADO,:STDEMLMVFINAL,:STDEMCMVFINAL,:RET);
//                      END;@   
//                      
//PROCEDURE=INTERFASAMOV,BEGIN
//                        VDMOV.INTERFASAMOV(:VDMOVIM.CODMOV,:STREVISION,:STPDTEINTER,:STSININTER,:RET);
//                      END;@                             
//                  
//PROCEDURE=AVANZAPDTESTOCK, BEGIN
//                             VDMOV.AVANZAPDTESTOCK(:VDMOVIM.CODMOV, :AVANZA);                                         
//                           END;@
//                           
//PROCEDURE=RESERVAMOV, BEGIN
//                             VDRESMOV.RESERVAMOVDIF(:VDMOVIM.CODMOV, :VDSTATUS.STATUS, :RESERVADO);                                       
//                           END;@                          
//                         
//%%h
//VDEXPORT int MOVfinalizamov(void *ptr, long stfinalizado, long stdemlmvfinal, long stdemcmvfinal);
//VDEXPORT int MOVinterfasamov(void *ptr,long strevision, long stpdteinter, long stsininter);
//VDEXPORT int MOVanulamov(void *ptr);
//
//%%c    
//
//// Anula un movto, y los que le esperan
//VDEXPORT int MOVanulamov(void *ptr) {
//  int ret=0;
//  vdmovims *mov=ptr;
//  vdmovauxs movaux;
//   
//  ret=MOVAUXprocanulamov(mov->codmov,ret,&movaux);
//  if (ret) {
//    *mov->comen=0;   
//  	strcpy(mov->comen,"MOVanulamov: error ejecutando algoritmo PLSQL VDMOV.ANULAMOV\n");
//    v10log(LOGERROR,mov->comen);
//  	return(-1);
//  }
//  return(movaux.ret);
//}  
//  
////Finaliza un movto, y lo deja en un estado finalizado
//VDEXPORT int MOVfinalizamov(void *ptr,long stfinalizado, long stdemlmvfinal, long stdemcmvfinal) {
//  int ret=0;
//  vdmovims *mov=ptr;   
//  vdmovauxs movaux;
//   
//  ret=MOVAUXprocfinalizamov(mov->codmov,stfinalizado,stdemlmvfinal,stdemcmvfinal,ret,&movaux);
//  if (ret) {
//    *mov->comen=0;   
//  	strcpy(mov->comen,"MOVfinalizamov: error ejecutando algoritmo PLSQL VDMOV.FINALIZAMOV\n");
//    v10log(LOGERROR,mov->comen);
//  	return(-1);
//  }
//  return(movaux.ret);
//}  
//
//
////Interfasa un movto, y lo deja en un estado,revision, pdteinter o sininter
//VDEXPORT int MOVinterfasamov(void *ptr,long strevision, long stpdteinter, long stsininter) {
//  int ret=0;
//  vdmovims *mov=ptr;   
//  vdmovauxs movaux;
//   
//  ret=MOVAUXprocinterfasamov(mov->codmov,strevision,stpdteinter,stsininter,ret,&movaux);
//  if (ret) {
//    *mov->comen=0;   
//  	strcpy(mov->comen,"MOVinterfasamov: error ejecutando algoritmo PLSQL VDMOV.INTERFASAMOV\n");
//    v10log(LOGERROR,mov->comen);
//  	return(-1);
//  }
//  return(movaux.ret);
//}  

#include "vd.h"\

#define SELPARTEMOV "DECLARE RET NUMBER; BEGIN RET:=VDMOV.PARTEMOV(:CODMOV,:CANTIDAD,:NUEVOMOV,:LIMPIAR); IF RET!=0 THEN RAISE NO_DATA_FOUND; END IF; END;"
static v10cursors *vdselpartemov;
#define SELANULAMOV "BEGIN VDMOV.ANULAMOV(:CODMOV,:RET); END;"
static v10cursors *vdselanulamov;
#define SELFINALIZAMOV "BEGIN VDMOV.FINALIZAMOV(:CODMOV,:STFINALIZADO,:STDEMLMVFINAL,:STDEMCMVFINAL,:RET); END;"
static v10cursors *vdselfinalizamov;
#define SELINTERFASAMOV "BEGIN VDMOV.INTERFASAMOV(:CODMOV,:STREVISION,:STPDTEINTER,:STSININTER,:RET); END;"
static v10cursors *vdselinterfasamov;
#define SELAVANZAPDTESTOCK " BEGIN VDMOV.AVANZAPDTESTOCK(:CODMOV, :AVANZA);                                          END;"
static v10cursors *vdselavanzapdtestock;
#define SELRESERVAMOV " BEGIN VDRESMOV.RESERVAMOVDIF(:CODMOV, :STATUS, :RESERVADO);                                        END;"
static v10cursors *vdselreservamov;

static vdmovauxs svdmovaux;

static diccols colvdmovaux[]={ 
    {"RET",V10LONG,(int)&svdmovaux.ret,sizeof(svdmovaux.ret)},
    {"STFINALIZADO",V10LONG,(int)&svdmovaux.stfinalizado,sizeof(svdmovaux.stfinalizado)},
    {"STREVISION",V10LONG,(int)&svdmovaux.strevision,sizeof(svdmovaux.strevision)},
    {"STPDTEINTER",V10LONG,(int)&svdmovaux.stpdteinter,sizeof(svdmovaux.stpdteinter)},
    {"STSININTER",V10LONG,(int)&svdmovaux.stsininter,sizeof(svdmovaux.stsininter)},
    {"STDEMLMVFINAL",V10LONG,(int)&svdmovaux.stdemlmvfinal,sizeof(svdmovaux.stdemlmvfinal)},
    {"STDEMCMVFINAL",V10LONG,(int)&svdmovaux.stdemcmvfinal,sizeof(svdmovaux.stdemcmvfinal)},
    {"NUEVOMOV",V10LONG,(int)&svdmovaux.nuevomov,sizeof(svdmovaux.nuevomov)},
    {"LIMPIAR",V10CADENA,(int)&svdmovaux.limpiar,sizeof(svdmovaux.limpiar)},
    {"AVANZA",V10LONG,(int)&svdmovaux.avanza,sizeof(svdmovaux.avanza)},
    {"RESERVADO",V10DOUBLE,(int)&svdmovaux.reservado,sizeof(svdmovaux.reservado)},
    {"CODMOV",V10LONG,(int)&svdmovaux.codmov,sizeof(svdmovaux.codmov)},
    {"CANTIDAD",V10DOUBLE,(int)&svdmovaux.cantidad,sizeof(svdmovaux.cantidad)},
    {"STATUS",V10LONG,(int)&svdmovaux.status,sizeof(svdmovaux.status)}
    };

static diccionarios dvdmovaux[]={
    {colvdmovaux,14}
    };

diccionario dmovaux={dvdmovaux,1};

static char msgdebugmovaux[LCADENABIG];

static int init=0;


static void fin_vd_MOVAUX(void)
{
    if(vdselpartemov){
        liberacursor(vdselpartemov);
        vdselpartemov=NULL;
    }
    if(vdselanulamov){
        liberacursor(vdselanulamov);
        vdselanulamov=NULL;
    }
    if(vdselfinalizamov){
        liberacursor(vdselfinalizamov);
        vdselfinalizamov=NULL;
    }
    if(vdselinterfasamov){
        liberacursor(vdselinterfasamov);
        vdselinterfasamov=NULL;
    }
    if(vdselavanzapdtestock){
        liberacursor(vdselavanzapdtestock);
        vdselavanzapdtestock=NULL;
    }
    if(vdselreservamov){
        liberacursor(vdselreservamov);
        vdselreservamov=NULL;
    }
}


static void init_selpartemov(void)
{
    int nc;

    for(nc=0;nc<dvdmovaux[0].numcol;nc++) dvdmovaux[0].c[nc].offset-=(int)&svdmovaux;

    vdselpartemov=abrecursor(SELPARTEMOV);
    definetodo(vdselpartemov,NULL);
    bindtodo(vdselpartemov,"CODMOV",&svdmovaux.codmov,sizeof(svdmovaux.codmov),V10LONG,
             "CANTIDAD",&svdmovaux.cantidad,sizeof(svdmovaux.cantidad),V10DOUBLE,
             "NUEVOMOV",&svdmovaux.nuevomov,sizeof(svdmovaux.nuevomov),V10LONG,
             "LIMPIAR",svdmovaux.limpiar,sizeof(svdmovaux.limpiar),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_MOVAUX);
        init = 1;
    }
}

static void init_selanulamov(void)
{
    int nc;

    for(nc=0;nc<dvdmovaux[0].numcol;nc++) dvdmovaux[0].c[nc].offset-=(int)&svdmovaux;

    vdselanulamov=abrecursor(SELANULAMOV);
    definetodo(vdselanulamov,NULL);
    bindtodo(vdselanulamov,"CODMOV",&svdmovaux.codmov,sizeof(svdmovaux.codmov),V10LONG,
             "RET",&svdmovaux.ret,sizeof(svdmovaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_MOVAUX);
        init = 1;
    }
}

static void init_selfinalizamov(void)
{
    int nc;

    for(nc=0;nc<dvdmovaux[0].numcol;nc++) dvdmovaux[0].c[nc].offset-=(int)&svdmovaux;

    vdselfinalizamov=abrecursor(SELFINALIZAMOV);
    definetodo(vdselfinalizamov,NULL);
    bindtodo(vdselfinalizamov,"CODMOV",&svdmovaux.codmov,sizeof(svdmovaux.codmov),V10LONG,
             "STFINALIZADO",&svdmovaux.stfinalizado,sizeof(svdmovaux.stfinalizado),V10LONG,
             "STDEMLMVFINAL",&svdmovaux.stdemlmvfinal,sizeof(svdmovaux.stdemlmvfinal),V10LONG,
             "STDEMCMVFINAL",&svdmovaux.stdemcmvfinal,sizeof(svdmovaux.stdemcmvfinal),V10LONG,
             "RET",&svdmovaux.ret,sizeof(svdmovaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_MOVAUX);
        init = 1;
    }
}

static void init_selinterfasamov(void)
{
    int nc;

    for(nc=0;nc<dvdmovaux[0].numcol;nc++) dvdmovaux[0].c[nc].offset-=(int)&svdmovaux;

    vdselinterfasamov=abrecursor(SELINTERFASAMOV);
    definetodo(vdselinterfasamov,NULL);
    bindtodo(vdselinterfasamov,"CODMOV",&svdmovaux.codmov,sizeof(svdmovaux.codmov),V10LONG,
             "STREVISION",&svdmovaux.strevision,sizeof(svdmovaux.strevision),V10LONG,
             "STPDTEINTER",&svdmovaux.stpdteinter,sizeof(svdmovaux.stpdteinter),V10LONG,
             "STSININTER",&svdmovaux.stsininter,sizeof(svdmovaux.stsininter),V10LONG,
             "RET",&svdmovaux.ret,sizeof(svdmovaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_MOVAUX);
        init = 1;
    }
}

static void init_selavanzapdtestock(void)
{
    int nc;

    for(nc=0;nc<dvdmovaux[0].numcol;nc++) dvdmovaux[0].c[nc].offset-=(int)&svdmovaux;

    vdselavanzapdtestock=abrecursor(SELAVANZAPDTESTOCK);
    definetodo(vdselavanzapdtestock,NULL);
    bindtodo(vdselavanzapdtestock,"CODMOV",&svdmovaux.codmov,sizeof(svdmovaux.codmov),V10LONG,
             "AVANZA",&svdmovaux.avanza,sizeof(svdmovaux.avanza),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_MOVAUX);
        init = 1;
    }
}

static void init_selreservamov(void)
{
    int nc;

    for(nc=0;nc<dvdmovaux[0].numcol;nc++) dvdmovaux[0].c[nc].offset-=(int)&svdmovaux;

    vdselreservamov=abrecursor(SELRESERVAMOV);
    definetodo(vdselreservamov,NULL);
    bindtodo(vdselreservamov,"CODMOV",&svdmovaux.codmov,sizeof(svdmovaux.codmov),V10LONG,
             "STATUS",&svdmovaux.status,sizeof(svdmovaux.status),V10LONG,
             "RESERVADO",&svdmovaux.reservado,sizeof(svdmovaux.reservado),V10DOUBLE,
             NULL);

    if (init == 0) {
        atexit(fin_vd_MOVAUX);
        init = 1;
    }
}

diccionario *MOVAUXdamediccionario(void)
{
    return(&dmovaux);
}

int MOVAUXprocpartemov(long codmov,double cantidad,long nuevomov,char *limpiar,vdmovauxs *movaux)
{
    int vdret;
    if (vdselpartemov==NULL) init_selpartemov();
    memset(&svdmovaux,0,sizeof(svdmovaux));
    svdmovaux.codmov=codmov;
    svdmovaux.cantidad=cantidad;
    svdmovaux.nuevomov=nuevomov;
    strcpy(svdmovaux.limpiar,limpiar);
    vdret=ejecutacursor(vdselpartemov);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta MOVAUXprocpartemov vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *movaux=svdmovaux;
    return(vdret);
}

int MOVAUXprocanulamov(long codmov,long ret,vdmovauxs *movaux)
{
    int vdret;
    if (vdselanulamov==NULL) init_selanulamov();
    memset(&svdmovaux,0,sizeof(svdmovaux));
    svdmovaux.codmov=codmov;
    svdmovaux.ret=ret;
    vdret=ejecutacursor(vdselanulamov);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta MOVAUXprocanulamov vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *movaux=svdmovaux;
    return(vdret);
}

int MOVAUXprocfinalizamov(long codmov,long stfinalizado,long stdemlmvfinal,long stdemcmvfinal,long ret,vdmovauxs *movaux)
{
    int vdret;
    if (vdselfinalizamov==NULL) init_selfinalizamov();
    memset(&svdmovaux,0,sizeof(svdmovaux));
    svdmovaux.codmov=codmov;
    svdmovaux.stfinalizado=stfinalizado;
    svdmovaux.stdemlmvfinal=stdemlmvfinal;
    svdmovaux.stdemcmvfinal=stdemcmvfinal;
    svdmovaux.ret=ret;
    vdret=ejecutacursor(vdselfinalizamov);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta MOVAUXprocfinalizamov vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *movaux=svdmovaux;
    return(vdret);
}

int MOVAUXprocinterfasamov(long codmov,long strevision,long stpdteinter,long stsininter,long ret,vdmovauxs *movaux)
{
    int vdret;
    if (vdselinterfasamov==NULL) init_selinterfasamov();
    memset(&svdmovaux,0,sizeof(svdmovaux));
    svdmovaux.codmov=codmov;
    svdmovaux.strevision=strevision;
    svdmovaux.stpdteinter=stpdteinter;
    svdmovaux.stsininter=stsininter;
    svdmovaux.ret=ret;
    vdret=ejecutacursor(vdselinterfasamov);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta MOVAUXprocinterfasamov vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *movaux=svdmovaux;
    return(vdret);
}

int MOVAUXprocavanzapdtestock(long codmov,long avanza,vdmovauxs *movaux)
{
    int vdret;
    if (vdselavanzapdtestock==NULL) init_selavanzapdtestock();
    memset(&svdmovaux,0,sizeof(svdmovaux));
    svdmovaux.codmov=codmov;
    svdmovaux.avanza=avanza;
    vdret=ejecutacursor(vdselavanzapdtestock);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta MOVAUXprocavanzapdtestock vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *movaux=svdmovaux;
    return(vdret);
}

int MOVAUXprocreservamov(long codmov,long status,double reservado,vdmovauxs *movaux)
{
    int vdret;
    if (vdselreservamov==NULL) init_selreservamov();
    memset(&svdmovaux,0,sizeof(svdmovaux));
    svdmovaux.codmov=codmov;
    svdmovaux.status=status;
    svdmovaux.reservado=reservado;
    vdret=ejecutacursor(vdselreservamov);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta MOVAUXprocreservamov vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *movaux=svdmovaux;
    return(vdret);
}

char * MOVAUXdebug(vdmovauxs *movaux)
{
    debugestruct(&dmovaux,movaux,msgdebugmovaux);
    return(msgdebugmovaux);
}


//Codigo incluido explicitamente en el DEF

// Anula un movto, y los que le esperan
VDEXPORT int MOVanulamov(void *ptr) {
  int ret=0;
  vdmovims *mov=ptr;
  vdmovauxs movaux;
   
  ret=MOVAUXprocanulamov(mov->codmov,ret,&movaux);
  if (ret) {
    *mov->comen=0;   
  	strcpy(mov->comen,"MOVanulamov: error ejecutando algoritmo PLSQL VDMOV.ANULAMOV\n");
    v10log(LOGERROR,mov->comen);
  	return(-1);
  }
  return(movaux.ret);
}  
  
//Finaliza un movto, y lo deja en un estado finalizado
VDEXPORT int MOVfinalizamov(void *ptr,long stfinalizado, long stdemlmvfinal, long stdemcmvfinal) {
  int ret=0;
  vdmovims *mov=ptr;   
  vdmovauxs movaux;
   
  ret=MOVAUXprocfinalizamov(mov->codmov,stfinalizado,stdemlmvfinal,stdemcmvfinal,ret,&movaux);
  if (ret) {
    *mov->comen=0;   
  	strcpy(mov->comen,"MOVfinalizamov: error ejecutando algoritmo PLSQL VDMOV.FINALIZAMOV\n");
    v10log(LOGERROR,mov->comen);
  	return(-1);
  }
  return(movaux.ret);
}  


//Interfasa un movto, y lo deja en un estado,revision, pdteinter o sininter
VDEXPORT int MOVinterfasamov(void *ptr,long strevision, long stpdteinter, long stsininter) {
  int ret=0;
  vdmovims *mov=ptr;   
  vdmovauxs movaux;
   
  ret=MOVAUXprocinterfasamov(mov->codmov,strevision,stpdteinter,stsininter,ret,&movaux);
  if (ret) {
    *mov->comen=0;   
  	strcpy(mov->comen,"MOVinterfasamov: error ejecutando algoritmo PLSQL VDMOV.INTERFASAMOV\n");
    v10log(LOGERROR,mov->comen);
  	return(-1);
  }
  return(movaux.ret);
}  
