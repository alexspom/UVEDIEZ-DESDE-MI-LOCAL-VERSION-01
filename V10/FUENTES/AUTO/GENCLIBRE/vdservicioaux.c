// Modulo generado automaticamente a partir de VDSERVICIOAUX.DEF
//#***
//# VDSERVICIO.DEF - Generación automática del código c SOLOQUERY para Servicios                                                       
//# 
//# Propósito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 03-02-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=SERVICIOSAUX;
//
//EXTRA=RET,V10LONG
//
//CURSOR=EJECUTABLESERVICIO,SELECT VDPLANIF.EJECUTABLESERVICIO(:VDSERVICIOS.CODGRUPOSERV, :VDSERVICIOS.CODSERVICIO) RET FROM DUAL;
//      
//CURSOR=EJECSERVPLANIF,SELECT VDPLANIF.EJECUTABLESERVPLANIFICADO(:VDSERVICIOS.CODGRUPOSERV, :VDSERVICIOS.CODSERVICIO, :VDSERVICIOS.ARRANQUE, :VDSERVICIOS.CIERRE) RET FROM DUAL;
//                                  
//PROCEDURE=PLANIFICAGRUPOSERV,BEGIN
//                                VDPLANIF.PLANIFICAGRUPOSERV(:VDSERVICIOS.CODGRUPOSERV);
//                             END;@
//
//PROCEDURE=PLANIFICASERVICIO,BEGIN
//                                VDPLANIF.PLANIFICASERVICIO(:VDSERVICIOS.CODGRUPOSERV,:VDSERVICIOS.CODSERVICIO,:RET);
//                             END;@
//                                                                                                                    	

#include "vd.h"\

#define SELEJECUTABLESERVICIO "SELECT VDPLANIF.EJECUTABLESERVICIO(:CODGRUPOSERV, :CODSERVICIO) RET FROM DUAL"
static v10cursors *vdselejecutableservicio;
#define SELEJECSERVPLANIF "SELECT VDPLANIF.EJECUTABLESERVPLANIFICADO(:CODGRUPOSERV, :CODSERVICIO, :ARRANQUE, :CIERRE) RET FROM DUAL"
static v10cursors *vdselejecservplanif;
#define SELPLANIFICAGRUPOSERV "BEGIN VDPLANIF.PLANIFICAGRUPOSERV(:CODGRUPOSERV); END;"
static v10cursors *vdselplanificagruposerv;
#define SELPLANIFICASERVICIO "BEGIN VDPLANIF.PLANIFICASERVICIO(:CODGRUPOSERV,:CODSERVICIO,:RET); END;"
static v10cursors *vdselplanificaservicio;

static vdserviciosauxs svdserviciosaux;

static diccols colvdserviciosaux[]={ 
    {"RET", V10LONG, (size_t)&svdserviciosaux.ret, sizeof(svdserviciosaux.ret)},
    {"CODGRUPOSERV", V10CADENA, (size_t)&svdserviciosaux.codgruposerv, sizeof(svdserviciosaux.codgruposerv)},
    {"CODSERVICIO", V10CADENA, (size_t)&svdserviciosaux.codservicio, sizeof(svdserviciosaux.codservicio)},
    {"ARRANQUE", V10CADENA, (size_t)&svdserviciosaux.arranque, sizeof(svdserviciosaux.arranque)},
    {"CIERRE", V10CADENA, (size_t)&svdserviciosaux.cierre, sizeof(svdserviciosaux.cierre)}
    };

static diccionarios dvdserviciosaux[]={
    {colvdserviciosaux,5}
    };

diccionario dserviciosaux={dvdserviciosaux,1};

static char msgdebugserviciosaux[LCADENABIG];

static int init=0;


static void fin_vd_SERVICIOSAUX(void)
{
    if(vdselejecutableservicio){
        liberacursor(vdselejecutableservicio);
        vdselejecutableservicio=NULL;
    }
    if(vdselejecservplanif){
        liberacursor(vdselejecservplanif);
        vdselejecservplanif=NULL;
    }
    if(vdselplanificagruposerv){
        liberacursor(vdselplanificagruposerv);
        vdselplanificagruposerv=NULL;
    }
    if(vdselplanificaservicio){
        liberacursor(vdselplanificaservicio);
        vdselplanificaservicio=NULL;
    }
}


static void init_selejecutableservicio(void)
{
    int nc;

	if (init == 0) {
		for (nc = 0; nc < dvdserviciosaux[0].numcol; nc++) dvdserviciosaux[0].c[nc].offset -= (size_t)&svdserviciosaux;
	}
    vdselejecutableservicio=abrecursor(SELEJECUTABLESERVICIO);
    definetodo(vdselejecutableservicio,&svdserviciosaux.ret,sizeof(svdserviciosaux.ret),V10LONG,
               NULL);
    bindtodo(vdselejecutableservicio,"CODGRUPOSERV",svdserviciosaux.codgruposerv,sizeof(svdserviciosaux.codgruposerv),V10CADENA,
             "CODSERVICIO",svdserviciosaux.codservicio,sizeof(svdserviciosaux.codservicio),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_SERVICIOSAUX);
        init = 1;
    }
}

static void init_selejecservplanif(void)
{
    int nc;

	if (init == 0) {
		for (nc = 0; nc < dvdserviciosaux[0].numcol; nc++) dvdserviciosaux[0].c[nc].offset -= (size_t)&svdserviciosaux;
	}
    vdselejecservplanif=abrecursor(SELEJECSERVPLANIF);
    definetodo(vdselejecservplanif,&svdserviciosaux.ret,sizeof(svdserviciosaux.ret),V10LONG,
               NULL);
    bindtodo(vdselejecservplanif,"CODGRUPOSERV",svdserviciosaux.codgruposerv,sizeof(svdserviciosaux.codgruposerv),V10CADENA,
             "CODSERVICIO",svdserviciosaux.codservicio,sizeof(svdserviciosaux.codservicio),V10CADENA,
             "ARRANQUE",svdserviciosaux.arranque,sizeof(svdserviciosaux.arranque),V10CADENA,
             "CIERRE",svdserviciosaux.cierre,sizeof(svdserviciosaux.cierre),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_SERVICIOSAUX);
        init = 1;
    }
}

static void init_selplanificagruposerv(void)
{
    int nc;

	if (init == 0) {
		for (nc = 0; nc < dvdserviciosaux[0].numcol; nc++) dvdserviciosaux[0].c[nc].offset -= (size_t)&svdserviciosaux;
	}
    vdselplanificagruposerv=abrecursor(SELPLANIFICAGRUPOSERV);
   // definetodo(vdselplanificagruposerv, &svdserviciosaux.ret, sizeof(svdserviciosaux.ret), V10LONG, NULL);
    bindtodo(vdselplanificagruposerv,"CODGRUPOSERV",svdserviciosaux.codgruposerv,sizeof(svdserviciosaux.codgruposerv),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_SERVICIOSAUX);
        init = 1;
    }
}

static void init_selplanificaservicio(void)
{
    int nc;

	if (init == 0) {
		for (nc = 0; nc < dvdserviciosaux[0].numcol; nc++) dvdserviciosaux[0].c[nc].offset -= (size_t)&svdserviciosaux;
	}
    vdselplanificaservicio=abrecursor(SELPLANIFICASERVICIO);
    definetodo(vdselplanificaservicio,NULL);
    bindtodo(vdselplanificaservicio,"CODGRUPOSERV",svdserviciosaux.codgruposerv,sizeof(svdserviciosaux.codgruposerv),V10CADENA,
             "CODSERVICIO",svdserviciosaux.codservicio,sizeof(svdserviciosaux.codservicio),V10CADENA,
             "RET",&svdserviciosaux.ret,sizeof(svdserviciosaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_SERVICIOSAUX);
        init = 1;
    }
}

diccionario *SERVICIOSAUXdamediccionario(void)
{
    return(&dserviciosaux);
}

int SERVICIOSAUXbuscaejecutableservicio(char *codgruposerv,char *codservicio,vdserviciosauxs *serviciosaux)
{
    int vdret;
    if (vdselejecutableservicio==NULL) init_selejecutableservicio();
    memset(&svdserviciosaux,0,sizeof(svdserviciosaux));
    strcpy(svdserviciosaux.codgruposerv,codgruposerv);
    strcpy(svdserviciosaux.codservicio,codservicio);
    vdret=ejefetchcursor(vdselejecutableservicio);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch SERVICIOSAUXbuscaejecutableservicio vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *serviciosaux=svdserviciosaux;
    return(vdret);
}

int SERVICIOSAUXnextejecutableservicio(vdserviciosauxs *serviciosaux)
{
    int vdret;
    vdret=fetchcursor(vdselejecutableservicio);
    if (!vdret) {
        *serviciosaux=svdserviciosaux;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselejecutableservicio);
    return(VD_EERRORACLE);
}

int SERVICIOSAUXbuscaejecservplanif(char *codgruposerv,char *codservicio,char *arranque,char *cierre,vdserviciosauxs *serviciosaux)
{
    int vdret;
    if (vdselejecservplanif==NULL) init_selejecservplanif();
    memset(&svdserviciosaux,0,sizeof(svdserviciosaux));
    strcpy(svdserviciosaux.codgruposerv,codgruposerv);
    strcpy(svdserviciosaux.codservicio,codservicio);
    strcpy(svdserviciosaux.arranque,arranque);
    strcpy(svdserviciosaux.cierre,cierre);
    vdret=ejefetchcursor(vdselejecservplanif);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch SERVICIOSAUXbuscaejecservplanif vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *serviciosaux=svdserviciosaux;
    return(vdret);
}

int SERVICIOSAUXnextejecservplanif(vdserviciosauxs *serviciosaux)
{
    int vdret;
    vdret=fetchcursor(vdselejecservplanif);
    if (!vdret) {
        *serviciosaux=svdserviciosaux;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselejecservplanif);
    return(VD_EERRORACLE);
}

int SERVICIOSAUXprocplanificagruposerv(char *codgruposerv,vdserviciosauxs *serviciosaux)
{
    int vdret;
    if (vdselplanificagruposerv==NULL) init_selplanificagruposerv();
    memset(&svdserviciosaux,0,sizeof(svdserviciosaux));
    strcpy(svdserviciosaux.codgruposerv,codgruposerv);
    vdret=ejecutacursor(vdselplanificagruposerv);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta SERVICIOSAUXprocplanificagruposerv vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *serviciosaux=svdserviciosaux;
    return(vdret);
}

int SERVICIOSAUXprocplanificaservicio(char *codgruposerv,char *codservicio,long ret,vdserviciosauxs *serviciosaux)
{
    int vdret;
    if (vdselplanificaservicio==NULL) init_selplanificaservicio();
    memset(&svdserviciosaux,0,sizeof(svdserviciosaux));
    strcpy(svdserviciosaux.codgruposerv,codgruposerv);
    strcpy(svdserviciosaux.codservicio,codservicio);
    svdserviciosaux.ret=ret;
    vdret=ejecutacursor(vdselplanificaservicio);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta SERVICIOSAUXprocplanificaservicio vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *serviciosaux=svdserviciosaux;
    return(vdret);
}

char * SERVICIOSAUXdebug(vdserviciosauxs *serviciosaux)
{
    debugestruct(&dserviciosaux,serviciosaux,msgdebugserviciosaux);
    return(msgdebugserviciosaux);
}

