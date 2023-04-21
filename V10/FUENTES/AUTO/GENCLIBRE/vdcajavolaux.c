// Modulo generado automaticamente a partir de VDCAJAVOLAUX.DEF
//#***
//# VDCAJASAUX.DEF - Generación automática del código c SOLOQUERY para Cajas                                                       
//# 
//# Propósito: idem
//#           
//# Autor	 : FPD
//# Revisado por: 
//# Fecha  : 06-05-2008
//#************************************************************************************
//# Modificaciones
//#***
//NOMBRE=CAJAVOL;
//EXTRA=VOLUMENCAJ,V10DOUBLE;
//EXTRA=ALTURA,V10LONG;
//
//CURSOR=DEMAYORAMENOR,SELECT CAJ.TIPOVOL,CAJ.TIPOCAJA, 
//                            CAJ.DESCAJA,CAJ.LARGOCAJA,CAJ.ANCHOCAJA, 
//                            CAJ.ALTOCAJA,CAJ.PESOCAJA,CAJ.PESORELLENO, 
//                            CAJ.MARGENPESO,DECODE(VOL.MAXLLENADO,0,CAJ.MAXLLENADO,VOL.MAXLLENADO) MAXLLENADO,
//                            CAJ.MINLLENADO, 
//                            DECODE(VOL.MAXPICOS,0,CAJ.MAXPICOS,VOL.MAXPICOS) MAXPICOS,
//                            DECODE(VOL.MAXPESO,0,CAJ.MAXPESO,VOL.MAXPESO) MAXPESO,
//                            CAJ.VOLDINAMICA,CAJ.CODCOMEN,
//                            CAJ.CODOPEMODIF,CAJ.FECMODIF,CAJ.HORAMODIF 
//                       FROM VDCAJAS CAJ,VDVOLUMETRIA VOL
//                      WHERE CAJ.TIPOVOL=:VDCAJAS.TIPOVOL AND CAJ.TIPOVOL=VOL.TIPOVOL
//                     ORDER BY LARGOCAJA*ANCHOCAJA*ALTOCAJA DESC;
//

#include "vdpedidos.h"\

#define SELDEMAYORAMENOR "SELECT CAJ.TIPOVOL,CAJ.TIPOCAJA,  CAJ.DESCAJA,CAJ.LARGOCAJA,CAJ.ANCHOCAJA,  CAJ.ALTOCAJA,CAJ.PESOCAJA,CAJ.PESORELLENO,  CAJ.MARGENPESO,DECODE(VOL.MAXLLENADO,0,CAJ.MAXLLENADO,VOL.MAXLLENADO) MAXLLENADO, CAJ.MINLLENADO,  DECODE(VOL.MAXPICOS,0,CAJ.MAXPICOS,VOL.MAXPICOS) MAXPICOS, DECODE(VOL.MAXPESO,0,CAJ.MAXPESO,VOL.MAXPESO) MAXPESO, CAJ.VOLDINAMICA,CAJ.CODCOMEN, CAJ.CODOPEMODIF,CAJ.FECMODIF,CAJ.HORAMODIF  FROM VDCAJAS CAJ,VDVOLUMETRIA VOL WHERE CAJ.TIPOVOL=:TIPOVOL AND CAJ.TIPOVOL=VOL.TIPOVOL AND SWTACTIVO='S' ORDER BY LARGOCAJA*ANCHOCAJA*ALTOCAJA DESC"
static v10cursors *vdseldemayoramenor;

static vdcajavols svdcajavol;

static diccols colvdcajavol[]={ 
    {"VOLUMENCAJ",V10DOUBLE,(int)&svdcajavol.volumencaj,sizeof(svdcajavol.volumencaj)},
    {"ALTURA",V10LONG,(int)&svdcajavol.altura,sizeof(svdcajavol.altura)},
    {"TIPOVOL",V10CADENA,(int)&svdcajavol.tipovol,sizeof(svdcajavol.tipovol)},
    {"TIPOCAJA",V10CADENA,(int)&svdcajavol.tipocaja,sizeof(svdcajavol.tipocaja)},
    {"DESCAJA",V10CADENA,(int)&svdcajavol.descaja,sizeof(svdcajavol.descaja)},
    {"LARGOCAJA",V10LONG,(int)&svdcajavol.largocaja,sizeof(svdcajavol.largocaja)},
    {"ANCHOCAJA",V10LONG,(int)&svdcajavol.anchocaja,sizeof(svdcajavol.anchocaja)},
    {"ALTOCAJA",V10LONG,(int)&svdcajavol.altocaja,sizeof(svdcajavol.altocaja)},
    {"PESOCAJA",V10LONG,(int)&svdcajavol.pesocaja,sizeof(svdcajavol.pesocaja)},
    {"PESORELLENO",V10LONG,(int)&svdcajavol.pesorelleno,sizeof(svdcajavol.pesorelleno)},
    {"MARGENPESO",V10DOUBLE,(int)&svdcajavol.margenpeso,sizeof(svdcajavol.margenpeso)},
    {"MAXLLENADO",V10LONG,(int)&svdcajavol.maxllenado,sizeof(svdcajavol.maxllenado)},
    {"MINLLENADO",V10LONG,(int)&svdcajavol.minllenado,sizeof(svdcajavol.minllenado)},
    {"MAXPICOS",V10LONG,(int)&svdcajavol.maxpicos,sizeof(svdcajavol.maxpicos)},
    {"MAXPESO",V10LONG,(int)&svdcajavol.maxpeso,sizeof(svdcajavol.maxpeso)},
    {"VOLDINAMICA",V10CADENA,(int)&svdcajavol.voldinamica,sizeof(svdcajavol.voldinamica)},
    {"CODCOMEN",V10LONG,(int)&svdcajavol.codcomen,sizeof(svdcajavol.codcomen)},
    {"CODOPEMODIF",V10CADENA,(int)&svdcajavol.codopemodif,sizeof(svdcajavol.codopemodif)},
    {"FECMODIF",V10LONG,(int)&svdcajavol.fecmodif,sizeof(svdcajavol.fecmodif)},
    {"HORAMODIF",V10CADENA,(int)&svdcajavol.horamodif,sizeof(svdcajavol.horamodif)}
    };

static diccionarios dvdcajavol[]={
    {colvdcajavol,20}
    };

diccionario dcajavol={dvdcajavol,1};

static char msgdebugcajavol[LCADENABIG];

static int init=0;


static void fin_vd_CAJAVOL(void)
{
    if(vdseldemayoramenor){
        liberacursor(vdseldemayoramenor);
        vdseldemayoramenor=NULL;
    }
}


static void init_seldemayoramenor(void)
{
    int nc;

    for(nc=0;nc<dvdcajavol[0].numcol;nc++) dvdcajavol[0].c[nc].offset-=(int)&svdcajavol;

    vdseldemayoramenor=abrecursor(SELDEMAYORAMENOR);
    definetodo(vdseldemayoramenor,svdcajavol.tipovol,sizeof(svdcajavol.tipovol),V10CADENA,
               svdcajavol.tipocaja,sizeof(svdcajavol.tipocaja),V10CADENA,
               svdcajavol.descaja,sizeof(svdcajavol.descaja),V10CADENA,
               &svdcajavol.largocaja,sizeof(svdcajavol.largocaja),V10LONG,
               &svdcajavol.anchocaja,sizeof(svdcajavol.anchocaja),V10LONG,
               &svdcajavol.altocaja,sizeof(svdcajavol.altocaja),V10LONG,
               &svdcajavol.pesocaja,sizeof(svdcajavol.pesocaja),V10LONG,
               &svdcajavol.pesorelleno,sizeof(svdcajavol.pesorelleno),V10LONG,
               &svdcajavol.margenpeso,sizeof(svdcajavol.margenpeso),V10DOUBLE,
               &svdcajavol.maxllenado,sizeof(svdcajavol.maxllenado),V10LONG,
               &svdcajavol.minllenado,sizeof(svdcajavol.minllenado),V10LONG,
               &svdcajavol.maxpicos,sizeof(svdcajavol.maxpicos),V10LONG,
               &svdcajavol.maxpeso,sizeof(svdcajavol.maxpeso),V10LONG,
               svdcajavol.voldinamica,sizeof(svdcajavol.voldinamica),V10CADENA,
               &svdcajavol.codcomen,sizeof(svdcajavol.codcomen),V10LONG,
               svdcajavol.codopemodif,sizeof(svdcajavol.codopemodif),V10CADENA,
               &svdcajavol.fecmodif,sizeof(svdcajavol.fecmodif),V10LONG,
               svdcajavol.horamodif,sizeof(svdcajavol.horamodif),V10CADENA,
               NULL);
    bindtodo(vdseldemayoramenor,"TIPOVOL",svdcajavol.tipovol,sizeof(svdcajavol.tipovol),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_CAJAVOL);
        init = 1;
    }
}

diccionario *CAJAVOLdamediccionario(void)
{
    return(&dcajavol);
}

int CAJAVOLbuscademayoramenor(char *tipovol,vdcajavols *cajavol)
{
    int vdret;
    if (vdseldemayoramenor==NULL) init_seldemayoramenor();
    memset(&svdcajavol,0,sizeof(svdcajavol));
    strcpy(svdcajavol.tipovol,tipovol);
    vdret=ejefetchcursor(vdseldemayoramenor);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch CAJAVOLbuscademayoramenor vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *cajavol=svdcajavol;
    return(vdret);
}

int CAJAVOLnextdemayoramenor(vdcajavols *cajavol)
{
    int vdret;
    vdret=fetchcursor(vdseldemayoramenor);
    if (!vdret) {
        *cajavol=svdcajavol;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldemayoramenor);
    return(VD_EERRORACLE);
}

char * CAJAVOLdebug(vdcajavols *cajavol)
{
    debugestruct(&dcajavol,cajavol,msgdebugcajavol);
    return(msgdebugcajavol);
}

