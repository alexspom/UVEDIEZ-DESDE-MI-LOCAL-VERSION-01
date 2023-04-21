// Modulo generado automaticamente a partir de VDORAERR.DEF
//#***
//# VDORAERR.DEF - Generación automática del código c SOLOQUERY sobre la tabla VDORAERR                                                    
//# 
//# Propósito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 19-11-2009                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=ORAERR;
//
//CURSOR=HANDLEERROR,SELECT ORDEN, NIVELERR, RANGOEXE, RANGOERROR,DESCERROR,LIBALGORITMO,FUNCIONALG,PARAM, TIEMPOESPERA FROM VDORAERR
//                       WHERE VD.CONTIENE(RANGOEXE,UPPER(:VDORAERR.RANGOEXE))>0 ORDER BY ORDEN;

#include "vd.h"\

#define SELHANDLEERROR "SELECT ORDEN, NIVELERR, RANGOEXE, RANGOERROR,DESCERROR,LIBALGORITMO,FUNCIONALG,PARAM, TIEMPOESPERA FROM VDORAERR WHERE VD.CONTIENE(RANGOEXE,UPPER(:RANGOEXE))>0 ORDER BY ORDEN"
static v10cursors *vdselhandleerror;

static vdoraerrs svdoraerr;

static diccols colvdoraerr[]={ 
    {"ORDEN",V10LONG,(size_t)&svdoraerr.orden,sizeof(svdoraerr.orden)},
    {"NIVELERR", V10LONG, (size_t)&svdoraerr.nivelerr, sizeof(svdoraerr.nivelerr)},
    {"RANGOEXE", V10CADENA, (size_t)&svdoraerr.rangoexe, sizeof(svdoraerr.rangoexe)},
    {"RANGOERROR", V10CADENA, (size_t)&svdoraerr.rangoerror, sizeof(svdoraerr.rangoerror)},
    {"DESCERROR", V10CADENA, (size_t)&svdoraerr.descerror, sizeof(svdoraerr.descerror)},
    {"LIBALGORITMO", V10CADENA, (size_t)&svdoraerr.libalgoritmo, sizeof(svdoraerr.libalgoritmo)},
    {"FUNCIONALG", V10CADENA, (size_t)&svdoraerr.funcionalg, sizeof(svdoraerr.funcionalg)},
    {"PARAM", V10CADENA, (size_t)&svdoraerr.param, sizeof(svdoraerr.param)},
    {"TIEMPOESPERA", V10LONG, (size_t)&svdoraerr.tiempoespera, sizeof(svdoraerr.tiempoespera)}
    };

static diccionarios dvdoraerr[]={
    {colvdoraerr,9}
    };

diccionario doraerr={dvdoraerr,1};

static char msgdebugoraerr[LCADENABIG];

static int init=0;


static void fin_vd_ORAERR(void)
{
    if(vdselhandleerror){
        liberacursor(vdselhandleerror);
        vdselhandleerror=NULL;
    }
}


static void init_selhandleerror(void)
{
    int nc;

	for (nc = 0; nc < dvdoraerr[0].numcol; nc++) dvdoraerr[0].c[nc].offset -= (size_t)&svdoraerr;

    vdselhandleerror=abrecursor(SELHANDLEERROR);
    definetodo(vdselhandleerror,&svdoraerr.orden,sizeof(svdoraerr.orden),V10LONG,
               &svdoraerr.nivelerr,sizeof(svdoraerr.nivelerr),V10LONG,
               svdoraerr.rangoexe,sizeof(svdoraerr.rangoexe),V10CADENA,
               svdoraerr.rangoerror,sizeof(svdoraerr.rangoerror),V10CADENA,
               svdoraerr.descerror,sizeof(svdoraerr.descerror),V10CADENA,
               svdoraerr.libalgoritmo,sizeof(svdoraerr.libalgoritmo),V10CADENA,
               svdoraerr.funcionalg,sizeof(svdoraerr.funcionalg),V10CADENA,
               svdoraerr.param,sizeof(svdoraerr.param),V10CADENA,
               &svdoraerr.tiempoespera,sizeof(svdoraerr.tiempoespera),V10LONG,
               NULL);
    bindtodo(vdselhandleerror,"RANGOEXE",svdoraerr.rangoexe,sizeof(svdoraerr.rangoexe),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_ORAERR);
        init = 1;
    }
}

diccionario *ORAERRdamediccionario(void)
{
    return(&doraerr);
}

int ORAERRbuscahandleerror(char *rangoexe,vdoraerrs *oraerr)
{
    int vdret;
    if (vdselhandleerror==NULL) init_selhandleerror();
    memset(&svdoraerr,0,sizeof(svdoraerr));
    strcpy(svdoraerr.rangoexe,rangoexe);
    vdret=ejefetchcursor(vdselhandleerror);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch ORAERRbuscahandleerror vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *oraerr=svdoraerr;
    return(vdret);
}

int ORAERRnexthandleerror(vdoraerrs *oraerr)
{
    int vdret;
    vdret=fetchcursor(vdselhandleerror);
    if (!vdret) {
        *oraerr=svdoraerr;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselhandleerror);
    return(VD_EERRORACLE);
}

char * ORAERRdebug(vdoraerrs *oraerr)
{
    debugestruct(&doraerr,oraerr,msgdebugoraerr);
    return(msgdebugoraerr);
}

