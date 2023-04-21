// Modulo generado automaticamente a partir de VDVERIF.DEF
//#***
//# VDVERIF.DEF - Generación automática del código c SOLOQUERY para para verificación de bultos
//# 
//# Propósito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 4-03-2009                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=VERIF;
//
//EXTRA=RET,V10LONG;
//EXTRA=MSJERROR,V10CADENA,1024
//EXTRA=CONCMENSAJE,V10LONG;
//EXTRA=ANULARPRECINTOS,V10LONG;
//EXTRA=LLEVAALBARAN,V10LONG;
//
//PROCEDURE=PONVERIFICAR, BEGIN
//                         VDVERIF.PONVERIFICAR(:VDBULTOCAB.CODBULTO,:RET,:MSJERROR, :CONCMENSAJE);
//                     END;@
//                     
//PROCEDURE=VERIFICAPESO, BEGIN
//                         VDVERIF.VERIFICAPESO(:VDBULTOCAB.CODBULTO,:RET,:MSJERROR);
//                     END;@                     
//                     
//PROCEDURE=VERIFICATPC, BEGIN
//                         VDVERIF.VERIFICATPC(:VDBULTOCAB.CODBULTO,:RET,:MSJERROR);
//                     END;@     
//                     
//PROCEDURE=VERIFICAESTADO, BEGIN
//                         VDVERIF.VERIFICAESTADO(:VDBULTOCAB.CODBULTO,:RET,:MSJERROR);
//                     END;@                                
//                                    
//CURSOR=CLLEVAALBARAN SELECT VDVERIF.LLEVAALBARAN(:VDBULTOCAB.CODBULTO)  LLEVAALBARAN FROM DUAL;
//   
//CURSOR=CANULARPRECINTOS SELECT VDVERIF.ANULARPRECINTOS(:VDBULTOCAB.CODBULTO)  ANULARPRECINTOS FROM DUAL;                    

#include "vd.h"\

#define SELPONVERIFICAR " BEGIN VDVERIF.PONVERIFICAR(:CODBULTO,:RET,:MSJERROR, :CONCMENSAJE); END;"
static v10cursors *vdselponverificar;
#define SELVERIFICAPESO " BEGIN VDVERIF.VERIFICAPESO(:CODBULTO,:RET,:MSJERROR); END;"
static v10cursors *vdselverificapeso;
#define SELVERIFICATPC " BEGIN VDVERIF.VERIFICATPC(:CODBULTO,:RET,:MSJERROR); END;"
static v10cursors *vdselverificatpc;
#define SELVERIFICAESTADO " BEGIN VDVERIF.VERIFICAESTADO(:CODBULTO,:RET,:MSJERROR); END;"
static v10cursors *vdselverificaestado;
#define SELCLLEVAALBARAN "SELECT VDVERIF.LLEVAALBARAN(:CODBULTO)  LLEVAALBARAN FROM DUAL"
static v10cursors *vdselcllevaalbaran;
#define SELCANULARPRECINTOS "SELECT VDVERIF.ANULARPRECINTOS(:CODBULTO)  ANULARPRECINTOS FROM DUAL"
static v10cursors *vdselcanularprecintos;

static vdverifs svdverif;

static diccols colvdverif[]={ 
    {"RET",V10LONG,(size_t)&svdverif.ret,sizeof(svdverif.ret)},
    {"MSJERROR",V10CADENA,(size_t)&svdverif.msjerror,sizeof(svdverif.msjerror)},
    {"CONCMENSAJE",V10LONG,(size_t)&svdverif.concmensaje,sizeof(svdverif.concmensaje)},
    {"ANULARPRECINTOS",V10LONG,(size_t)&svdverif.anularprecintos,sizeof(svdverif.anularprecintos)},
    {"LLEVAALBARAN",V10LONG,(size_t)&svdverif.llevaalbaran,sizeof(svdverif.llevaalbaran)},
    {"CODBULTO",V10CADENA,(size_t)&svdverif.codbulto,sizeof(svdverif.codbulto)}
    };

static diccionarios dvdverif[]={
    {colvdverif,6}
    };

diccionario dverif={dvdverif,1};

static char msgdebugverif[LCADENABIG];

static int init=0;


static void fin_vd_VERIF(void)
{
    if(vdselponverificar){
        liberacursor(vdselponverificar);
        vdselponverificar=NULL;
    }
    if(vdselverificapeso){
        liberacursor(vdselverificapeso);
        vdselverificapeso=NULL;
    }
    if(vdselverificatpc){
        liberacursor(vdselverificatpc);
        vdselverificatpc=NULL;
    }
    if(vdselverificaestado){
        liberacursor(vdselverificaestado);
        vdselverificaestado=NULL;
    }
    if(vdselcllevaalbaran){
        liberacursor(vdselcllevaalbaran);
        vdselcllevaalbaran=NULL;
    }
    if(vdselcanularprecintos){
        liberacursor(vdselcanularprecintos);
        vdselcanularprecintos=NULL;
    }
}


static void init_selponverificar(void)
{
    int nc;

    for(nc=0;nc<dvdverif[0].numcol;nc++) dvdverif[0].c[nc].offset-=(size_t)&svdverif;

    vdselponverificar=abrecursor(SELPONVERIFICAR);
    definetodo(vdselponverificar,NULL);
    bindtodo(vdselponverificar,"CODBULTO",svdverif.codbulto,sizeof(svdverif.codbulto),V10CADENA,
             "RET",&svdverif.ret,sizeof(svdverif.ret),V10LONG,
             "MSJERROR",svdverif.msjerror,sizeof(svdverif.msjerror),V10CADENA,
             "CONCMENSAJE",&svdverif.concmensaje,sizeof(svdverif.concmensaje),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_VERIF);
        init = 1;
    }
}

static void init_selverificapeso(void)
{
    int nc;

    for(nc=0;nc<dvdverif[0].numcol;nc++) dvdverif[0].c[nc].offset-=(size_t)&svdverif;

    vdselverificapeso=abrecursor(SELVERIFICAPESO);
    definetodo(vdselverificapeso,NULL);
    bindtodo(vdselverificapeso,"CODBULTO",svdverif.codbulto,sizeof(svdverif.codbulto),V10CADENA,
             "RET",&svdverif.ret,sizeof(svdverif.ret),V10LONG,
             "MSJERROR",svdverif.msjerror,sizeof(svdverif.msjerror),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_VERIF);
        init = 1;
    }
}

static void init_selverificatpc(void)
{
    int nc;

    for(nc=0;nc<dvdverif[0].numcol;nc++) dvdverif[0].c[nc].offset-=(size_t)&svdverif;

    vdselverificatpc=abrecursor(SELVERIFICATPC);
    definetodo(vdselverificatpc,NULL);
    bindtodo(vdselverificatpc,"CODBULTO",svdverif.codbulto,sizeof(svdverif.codbulto),V10CADENA,
             "RET",&svdverif.ret,sizeof(svdverif.ret),V10LONG,
             "MSJERROR",svdverif.msjerror,sizeof(svdverif.msjerror),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_VERIF);
        init = 1;
    }
}

static void init_selverificaestado(void)
{
    int nc;

    for(nc=0;nc<dvdverif[0].numcol;nc++) dvdverif[0].c[nc].offset-=(size_t)&svdverif;

    vdselverificaestado=abrecursor(SELVERIFICAESTADO);
    definetodo(vdselverificaestado,NULL);
    bindtodo(vdselverificaestado,"CODBULTO",svdverif.codbulto,sizeof(svdverif.codbulto),V10CADENA,
             "RET",&svdverif.ret,sizeof(svdverif.ret),V10LONG,
             "MSJERROR",svdverif.msjerror,sizeof(svdverif.msjerror),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_VERIF);
        init = 1;
    }
}

static void init_selcllevaalbaran(void)
{
    int nc;

    for(nc=0;nc<dvdverif[0].numcol;nc++) dvdverif[0].c[nc].offset-=(size_t)&svdverif;

    vdselcllevaalbaran=abrecursor(SELCLLEVAALBARAN);
    definetodo(vdselcllevaalbaran,&svdverif.llevaalbaran,sizeof(svdverif.llevaalbaran),V10LONG,
               NULL);
    bindtodo(vdselcllevaalbaran,"CODBULTO",svdverif.codbulto,sizeof(svdverif.codbulto),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_VERIF);
        init = 1;
    }
}

static void init_selcanularprecintos(void)
{
    int nc;

    for(nc=0;nc<dvdverif[0].numcol;nc++) dvdverif[0].c[nc].offset-=(size_t)&svdverif;

    vdselcanularprecintos=abrecursor(SELCANULARPRECINTOS);
    definetodo(vdselcanularprecintos,&svdverif.anularprecintos,sizeof(svdverif.anularprecintos),V10LONG,
               NULL);
    bindtodo(vdselcanularprecintos,"CODBULTO",svdverif.codbulto,sizeof(svdverif.codbulto),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_VERIF);
        init = 1;
    }
}

diccionario *VERIFdamediccionario(void)
{
    return(&dverif);
}

int VERIFprocponverificar(char *codbulto,long ret,char *msjerror,long concmensaje,vdverifs *verif)
{
    int vdret;
    if (vdselponverificar==NULL) init_selponverificar();
    memset(&svdverif,0,sizeof(svdverif));
    strcpy(svdverif.codbulto,codbulto);
    svdverif.ret=ret;
    strcpy(svdverif.msjerror,msjerror);
    svdverif.concmensaje=concmensaje;
    vdret=ejecutacursor(vdselponverificar);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta VERIFprocponverificar vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *verif=svdverif;
    return(vdret);
}

int VERIFprocverificapeso(char *codbulto,long ret,char *msjerror,vdverifs *verif)
{
    int vdret;
    if (vdselverificapeso==NULL) init_selverificapeso();
    memset(&svdverif,0,sizeof(svdverif));
    strcpy(svdverif.codbulto,codbulto);
    svdverif.ret=ret;
    strcpy(svdverif.msjerror,msjerror);
    vdret=ejecutacursor(vdselverificapeso);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta VERIFprocverificapeso vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *verif=svdverif;
    return(vdret);
}

int VERIFprocverificatpc(char *codbulto,long ret,char *msjerror,vdverifs *verif)
{
    int vdret;
    if (vdselverificatpc==NULL) init_selverificatpc();
    memset(&svdverif,0,sizeof(svdverif));
    strcpy(svdverif.codbulto,codbulto);
    svdverif.ret=ret;
    strcpy(svdverif.msjerror,msjerror);
    vdret=ejecutacursor(vdselverificatpc);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta VERIFprocverificatpc vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *verif=svdverif;
    return(vdret);
}

int VERIFprocverificaestado(char *codbulto,long ret,char *msjerror,vdverifs *verif)
{
    int vdret;
    if (vdselverificaestado==NULL) init_selverificaestado();
    memset(&svdverif,0,sizeof(svdverif));
    strcpy(svdverif.codbulto,codbulto);
    svdverif.ret=ret;
    strcpy(svdverif.msjerror,msjerror);
    vdret=ejecutacursor(vdselverificaestado);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta VERIFprocverificaestado vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *verif=svdverif;
    return(vdret);
}

int VERIFbuscacllevaalbaran(char *codbulto,vdverifs *verif)
{
    int vdret;
    if (vdselcllevaalbaran==NULL) init_selcllevaalbaran();
    memset(&svdverif,0,sizeof(svdverif));
    strcpy(svdverif.codbulto,codbulto);
    vdret=ejefetchcursor(vdselcllevaalbaran);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch VERIFbuscacllevaalbaran vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *verif=svdverif;
    return(vdret);
}

int VERIFnextcllevaalbaran(vdverifs *verif)
{
    int vdret;
    vdret=fetchcursor(vdselcllevaalbaran);
    if (!vdret) {
        *verif=svdverif;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselcllevaalbaran);
    return(VD_EERRORACLE);
}

int VERIFbuscacanularprecintos(char *codbulto,vdverifs *verif)
{
    int vdret;
    if (vdselcanularprecintos==NULL) init_selcanularprecintos();
    memset(&svdverif,0,sizeof(svdverif));
    strcpy(svdverif.codbulto,codbulto);
    vdret=ejefetchcursor(vdselcanularprecintos);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch VERIFbuscacanularprecintos vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *verif=svdverif;
    return(vdret);
}

int VERIFnextcanularprecintos(vdverifs *verif)
{
    int vdret;
    vdret=fetchcursor(vdselcanularprecintos);
    if (!vdret) {
        *verif=svdverif;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselcanularprecintos);
    return(VD_EERRORACLE);
}

char * VERIFdebug(vdverifs *verif)
{
    debugestruct(&dverif,verif,msgdebugverif);
    return(msgdebugverif);
}

