// Modulo generado automaticamente a partir de VDARTICULOS.DEF
//#***
//# VDARTICULO.DEF - Generación automática del código c SOLOQUERY para querys sobre la tabla de artículos
//# 
//# Propósito: idem.
//#           
//# Autor	 : ICC
//# Revisado por: 
//# Fecha  : 15-04-2008                                             
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=ARTICULO;
//
//EXTRA=RETEST,V10CADENA,8;
//EXTRA=SOLOSTOCK,V10CADENA,1;
//EXTRA=MSJERROR,V10CADENA,1024;
//EXTRA=RET,V10LONG;
//EXTRA=COMENMOV,V10CADENA,1
//
//
//
//
//CURSOR=DAMERETEST,SELECT TO_CHAR((CASE WHEN UNIRETEST ='M' THEN 
//                                            ADD_MONTHS(TO_DATE(:VDLOTES.CADUCI, 'YYYYMMDD'), -1*TRETEST) 
//                                       WHEN UNIRETEST = 'D' THEN 
//                                            TO_DATE(:VDLOTES.CADUCI, 'YYYYMMDD') - TRETEST 
//                                  END), 'YYYYMMDD') RETEST 
//                    FROM VDARTIC 
//                   WHERE CODART = :VDARTIC.CODART;
//                   
//PROCEDURE=NUEVOBLOQLOTE,BEGIN
//														VDART.NUEVOBLOQLOTE(:VDLOTES.CODART,:VDLOTES.CODLOT,:VDLOTES.BLOQLOTE,:SOLOSTOCK,:MSJERROR,:RET);
//											 END;@                   
//
//PROCEDURE=TRATALOTESHIST,BEGIN
//						               VDART.TRATALOTESHIST(:VDLOTESHIST.SEQ, :COMENMOV);														
//											  END;@   

#include "vd.h"\

#define SELDAMERETEST "SELECT TO_CHAR((CASE WHEN UNIRETEST ='M' THEN  ADD_MONTHS(TO_DATE(:CADUCI, 'YYYYMMDD'), -1*TRETEST)  WHEN UNIRETEST = 'D' THEN  TO_DATE(:CADUCI, 'YYYYMMDD') - TRETEST  END), 'YYYYMMDD') RETEST  FROM VDARTIC  WHERE CODART = :CODART"
static v10cursors *vdseldameretest;
#define SELNUEVOBLOQLOTE "BEGIN VDART.NUEVOBLOQLOTE(:CODART,:CODLOT,:BLOQLOTE,:SOLOSTOCK,:MSJERROR,:RET); END;"
static v10cursors *vdselnuevobloqlote;
#define SELTRATALOTESHIST "BEGIN VDART.TRATALOTESHIST(:SEQ, :COMENMOV);														 END;"
static v10cursors *vdseltrataloteshist;

static vdarticulos svdarticulo;

static diccols colvdarticulo[]={ 
    {"RETEST",V10CADENA,(int)&svdarticulo.retest,sizeof(svdarticulo.retest)},
    {"SOLOSTOCK",V10CADENA,(int)&svdarticulo.solostock,sizeof(svdarticulo.solostock)},
    {"MSJERROR",V10CADENA,(int)&svdarticulo.msjerror,sizeof(svdarticulo.msjerror)},
    {"RET",V10LONG,(int)&svdarticulo.ret,sizeof(svdarticulo.ret)},
    {"COMENMOV",V10CADENA,(int)&svdarticulo.comenmov,sizeof(svdarticulo.comenmov)},
    {"CADUCI",V10CADENA,(int)&svdarticulo.caduci,sizeof(svdarticulo.caduci)},
    {"CODART",V10CADENA,(int)&svdarticulo.codart,sizeof(svdarticulo.codart)},
    {"CODLOT",V10CADENA,(int)&svdarticulo.codlot,sizeof(svdarticulo.codlot)},
    {"BLOQLOTE",V10CADENA,(int)&svdarticulo.bloqlote,sizeof(svdarticulo.bloqlote)},
    {"SEQ",V10LONG,(int)&svdarticulo.seq,sizeof(svdarticulo.seq)}
    };

static diccionarios dvdarticulo[]={
    {colvdarticulo,10}
    };

diccionario darticulo={dvdarticulo,1};

static char msgdebugarticulo[LCADENABIG];

static int init=0;


static void fin_vd_ARTICULO(void)
{
    if(vdseldameretest){
        liberacursor(vdseldameretest);
        vdseldameretest=NULL;
    }
    if(vdselnuevobloqlote){
        liberacursor(vdselnuevobloqlote);
        vdselnuevobloqlote=NULL;
    }
    if(vdseltrataloteshist){
        liberacursor(vdseltrataloteshist);
        vdseltrataloteshist=NULL;
    }
}


static void init_seldameretest(void)
{
    int nc;

    for(nc=0;nc<dvdarticulo[0].numcol;nc++) dvdarticulo[0].c[nc].offset-=(int)&svdarticulo;

    vdseldameretest=abrecursor(SELDAMERETEST);
    definetodo(vdseldameretest,svdarticulo.retest,sizeof(svdarticulo.retest),V10CADENA,
               NULL);
    bindtodo(vdseldameretest,"CADUCI",svdarticulo.caduci,sizeof(svdarticulo.caduci),V10CADENA,
             "CODART",svdarticulo.codart,sizeof(svdarticulo.codart),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_ARTICULO);
        init = 1;
    }
}

static void init_selnuevobloqlote(void)
{
    int nc;

    for(nc=0;nc<dvdarticulo[0].numcol;nc++) dvdarticulo[0].c[nc].offset-=(int)&svdarticulo;

    vdselnuevobloqlote=abrecursor(SELNUEVOBLOQLOTE);
    definetodo(vdselnuevobloqlote,NULL);
    bindtodo(vdselnuevobloqlote,"CODART",svdarticulo.codart,sizeof(svdarticulo.codart),V10CADENA,
             "CODLOT",svdarticulo.codlot,sizeof(svdarticulo.codlot),V10CADENA,
             "BLOQLOTE",svdarticulo.bloqlote,sizeof(svdarticulo.bloqlote),V10CADENA,
             "SOLOSTOCK",svdarticulo.solostock,sizeof(svdarticulo.solostock),V10CADENA,
             "MSJERROR",svdarticulo.msjerror,sizeof(svdarticulo.msjerror),V10CADENA,
             "RET",&svdarticulo.ret,sizeof(svdarticulo.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_ARTICULO);
        init = 1;
    }
}

static void init_seltrataloteshist(void)
{
    int nc;

    for(nc=0;nc<dvdarticulo[0].numcol;nc++) dvdarticulo[0].c[nc].offset-=(int)&svdarticulo;

    vdseltrataloteshist=abrecursor(SELTRATALOTESHIST);
    definetodo(vdseltrataloteshist,NULL);
    bindtodo(vdseltrataloteshist,"SEQ",&svdarticulo.seq,sizeof(svdarticulo.seq),V10LONG,
             "COMENMOV",svdarticulo.comenmov,sizeof(svdarticulo.comenmov),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_ARTICULO);
        init = 1;
    }
}

diccionario *ARTICULOdamediccionario(void)
{
    return(&darticulo);
}

int ARTICULObuscadameretest(char *caduci,char *codart,vdarticulos *articulo)
{
    int vdret;
    if (vdseldameretest==NULL) init_seldameretest();
    memset(&svdarticulo,0,sizeof(svdarticulo));
    strcpy(svdarticulo.caduci,caduci);
    strcpy(svdarticulo.codart,codart);
    vdret=ejefetchcursor(vdseldameretest);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch ARTICULObuscadameretest vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *articulo=svdarticulo;
    return(vdret);
}

int ARTICULOnextdameretest(vdarticulos *articulo)
{
    int vdret;
    vdret=fetchcursor(vdseldameretest);
    if (!vdret) {
        *articulo=svdarticulo;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldameretest);
    return(VD_EERRORACLE);
}

int ARTICULOprocnuevobloqlote(char *codart,char *codlot,char *bloqlote,char *solostock,char *msjerror,long ret,vdarticulos *articulo)
{
    int vdret;
    if (vdselnuevobloqlote==NULL) init_selnuevobloqlote();
    memset(&svdarticulo,0,sizeof(svdarticulo));
    strcpy(svdarticulo.codart,codart);
    strcpy(svdarticulo.codlot,codlot);
    strcpy(svdarticulo.bloqlote,bloqlote);
    strcpy(svdarticulo.solostock,solostock);
    strcpy(svdarticulo.msjerror,msjerror);
    svdarticulo.ret=ret;
    vdret=ejecutacursor(vdselnuevobloqlote);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta ARTICULOprocnuevobloqlote vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *articulo=svdarticulo;
    return(vdret);
}

int ARTICULOproctrataloteshist(long seq,char *comenmov,vdarticulos *articulo)
{
    int vdret;
    if (vdseltrataloteshist==NULL) init_seltrataloteshist();
    memset(&svdarticulo,0,sizeof(svdarticulo));
    svdarticulo.seq=seq;
    strcpy(svdarticulo.comenmov,comenmov);
    vdret=ejecutacursor(vdseltrataloteshist);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta ARTICULOproctrataloteshist vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *articulo=svdarticulo;
    return(vdret);
}

char * ARTICULOdebug(vdarticulos *articulo)
{
    debugestruct(&darticulo,articulo,msgdebugarticulo);
    return(msgdebugarticulo);
}

