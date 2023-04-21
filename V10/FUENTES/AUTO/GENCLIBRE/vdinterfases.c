// Modulo generado automaticamente a partir de VDINTERFASES.DEF
//#***
//# VDINTERFASES.DEF - Generación automática del código c SOLOQUERY para querys sobre tablas de interfases
//# 
//# Propósito: idem.
//#           
//# Autor	 : ICC
//# Revisado por: 
//# Fecha  : 15-04-2008                                             
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=INTLAUX;
//
//EXTRA=ROWIDAUX,V10CADENA,18;
//EXTRA=VALOR,V10CADENA,255;
//EXTRA=TABLAORIG,V10CADENA,33;
//EXTRA=STATUSCAB,V10LONG;
//EXTRA=VDINTERFASECAB.FORMATOPADRE
//EXTRA=FECHAENT,V10CADENA,31;
//EXTRA=FECHASAL,V10CADENA,31;
//EXTRA=FMTOENT,V10CADENA,31;
//EXTRA=FMTOSAL,V10CADENA,31;
//EXTRA=LONGREG,V10LONG;  
//
//CURSOR=DAMEROID, SELECT VDINTERF.DAMEROWID(:VDINTERFASELIN.TABLA, :TABLAORIG, :VDINTERFASELIN.TIPOINTERFASE, :VDINTERFASELIN.FORMATO, :VDINTERFCARGALIN.REGISTRO) ROWIDAUX
//                   FROM DUAL;
//
//CURSOR=VALORCAMPO,SELECT TRIM(VALOR) VALOR
//                    FROM TABLE (VDINTERF.OBTVALORESCAMPOS(:VDINTERFCARGALIN.TIPOINTERFASE,:VDINTERFCARGALIN.FORMATO,:VDINTERFCARGALIN.REGISTRO))
//                   WHERE CAMPO = :VDINTERFASELIN.CAMPO
//                     AND TABLA = :VDINTERFASELIN.TABLA;
//
//CURSOR=REGGRAL, SELECT ICL.TIPOINTERFASE, ICL.FORMATO, INTC.FORMATOPADRE
//                 FROM VDINTERFCARGALIN ICL, VDINTERFCARGACAB ICC, VDINTERFASECAB INTC 
//                WHERE ICL.STATUS         = :VDINTERFCARGALIN.STATUS 
//                  AND ICL.CODINTERFASE   = ICC.CODINTERFASE 
//                  AND ICC.STATUS         = :STATUSCAB
//                  AND INTC.TIPOINTERFASE = ICL.TIPOINTERFASE 
//                  AND INTC.FORMATO       = ICL.FORMATO 
//                 GROUP BY ICL.TIPOINTERFASE, ICL.FORMATO,INTC.ORDEN, INTC.FORMATOPADRE
//                 ORDER BY INTC.ORDEN;
//
//#CURSOR=VALORCPK, SELECT INTL.CAMPO, A.VALOR, INTL.LONGITUD
//#                   FROM TABLE (VDINTERF.OBTVALORESCAMPOS(:VDINTERFASELIN.TIPOINTERFASE, :VDINTERFASELIN.FORMATO,:VDINTERFCARGALIN.REGISTRO)) A,
//#                        VDINTERFASELIN INTL
//#                  WHERE INTL.TIPOINTERFASE = :VDINTERFASELIN.TIPOINTERFASE
//#                    AND INTL.FORMATO       = :VDINTERFASELIN.FORMATO
//#                    AND INTL.PK            = 'S'
//#                    AND INTL.CAMPO         = A.CAMPO
//#                   ORDER BY INTL.ORDEN;
//#                   
//#SELECT=LONREG, SELECT SUM(LON) LONGREG
//#                 FROM (SELECT MAX(LONGITUD) LON, ORDEN   
//#                         FROM VDINTERFASELIN
//#                        WHERE TIPOINTERFASE = :VDINTERFASELIN.TIPOINTERFASE
//#                          AND FORMATO       = :VDINTERFASELIN.FORMATO
//#                          AND SWTACTIVO     = 'S'
//#                          AND PK           IN ('S','N')
//#                        GROUP BY ORDEN);
//#  
//SELECT=TRANSFECHA,SELECT VD.TRANSFECHA(:FECHAENT, :FMTOENT, :FMTOSAL) FECHASAL FROM DUAL;
//

#include "vd.h"\

#define SELDAMEROID " SELECT VDINTERF.DAMEROWID(:TABLA, :TABLAORIG, :TIPOINTERFASE, :FORMATO, :REGISTRO) ROWIDAUX FROM DUAL"
static v10cursors *vdseldameroid;
#define SELVALORCAMPO "SELECT TRIM(VALOR) VALOR FROM TABLE (VDINTERF.OBTVALORESCAMPOS(:TIPOINTERFASE,:FORMATO,:REGISTRO)) WHERE CAMPO = :CAMPO AND TABLA = :TABLA"
static v10cursors *vdselvalorcampo;
#define SELREGGRAL " SELECT ICL.TIPOINTERFASE, ICL.FORMATO, INTC.FORMATOPADRE FROM VDINTERFCARGALIN ICL, VDINTERFCARGACAB ICC, VDINTERFASECAB INTC  WHERE ICL.STATUS         = :STATUS  AND ICL.CODINTERFASE   = ICC.CODINTERFASE  AND ICC.STATUS         = :STATUSCAB AND INTC.TIPOINTERFASE = ICL.TIPOINTERFASE  AND INTC.FORMATO       = ICL.FORMATO  GROUP BY ICL.TIPOINTERFASE, ICL.FORMATO,INTC.ORDEN, INTC.FORMATOPADRE ORDER BY INTC.ORDEN"
static v10cursors *vdselreggral;
#define SELTRANSFECHA "SELECT VD.TRANSFECHA(:FECHAENT, :FMTOENT, :FMTOSAL) FECHASAL FROM DUAL"
static v10cursors *vdseltransfecha;

static vdintlauxs svdintlaux;

static diccols colvdintlaux[]={ 
    {"ROWIDAUX",V10CADENA,(int)&svdintlaux.rowidaux,sizeof(svdintlaux.rowidaux)},
    {"VALOR",V10CADENA,(int)&svdintlaux.valor,sizeof(svdintlaux.valor)},
    {"TABLAORIG",V10CADENA,(int)&svdintlaux.tablaorig,sizeof(svdintlaux.tablaorig)},
    {"STATUSCAB",V10LONG,(int)&svdintlaux.statuscab,sizeof(svdintlaux.statuscab)},
    {"FORMATOPADRE",V10CADENA,(int)&svdintlaux.formatopadre,sizeof(svdintlaux.formatopadre)},
    {"FECHAENT",V10CADENA,(int)&svdintlaux.fechaent,sizeof(svdintlaux.fechaent)},
    {"FECHASAL",V10CADENA,(int)&svdintlaux.fechasal,sizeof(svdintlaux.fechasal)},
    {"FMTOENT",V10CADENA,(int)&svdintlaux.fmtoent,sizeof(svdintlaux.fmtoent)},
    {"FMTOSAL",V10CADENA,(int)&svdintlaux.fmtosal,sizeof(svdintlaux.fmtosal)},
    {"LONGREG",V10LONG,(int)&svdintlaux.longreg,sizeof(svdintlaux.longreg)},
    {"TABLA",V10CADENA,(int)&svdintlaux.tabla,sizeof(svdintlaux.tabla)},
    {"TIPOINTERFASE",V10CADENA,(int)&svdintlaux.tipointerfase,sizeof(svdintlaux.tipointerfase)},
    {"FORMATO",V10CADENA,(int)&svdintlaux.formato,sizeof(svdintlaux.formato)},
    {"REGISTRO",V10CADENA,(int)&svdintlaux.registro,sizeof(svdintlaux.registro)},
    {"CAMPO",V10CADENA,(int)&svdintlaux.campo,sizeof(svdintlaux.campo)},
    {"STATUS",V10LONG,(int)&svdintlaux.status,sizeof(svdintlaux.status)}
    };

static diccionarios dvdintlaux[]={
    {colvdintlaux,16}
    };

diccionario dintlaux={dvdintlaux,1};

static char msgdebugintlaux[LCADENABIG];

static int init=0;


static void fin_vd_INTLAUX(void)
{
    if(vdseldameroid){
        liberacursor(vdseldameroid);
        vdseldameroid=NULL;
    }
    if(vdselvalorcampo){
        liberacursor(vdselvalorcampo);
        vdselvalorcampo=NULL;
    }
    if(vdselreggral){
        liberacursor(vdselreggral);
        vdselreggral=NULL;
    }
    if(vdseltransfecha){
        liberacursor(vdseltransfecha);
        vdseltransfecha=NULL;
    }
}


static void init_seldameroid(void)
{
    int nc;

    for(nc=0;nc<dvdintlaux[0].numcol;nc++) dvdintlaux[0].c[nc].offset-=(int)&svdintlaux;

    vdseldameroid=abrecursor(SELDAMEROID);
    definetodo(vdseldameroid,svdintlaux.rowidaux,sizeof(svdintlaux.rowidaux),V10CADENA,
               NULL);
    bindtodo(vdseldameroid,"TABLA",svdintlaux.tabla,sizeof(svdintlaux.tabla),V10CADENA,
             "TABLAORIG",svdintlaux.tablaorig,sizeof(svdintlaux.tablaorig),V10CADENA,
             "TIPOINTERFASE",svdintlaux.tipointerfase,sizeof(svdintlaux.tipointerfase),V10CADENA,
             "FORMATO",svdintlaux.formato,sizeof(svdintlaux.formato),V10CADENA,
             "REGISTRO",svdintlaux.registro,sizeof(svdintlaux.registro),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_INTLAUX);
        init = 1;
    }
}

static void init_selvalorcampo(void)
{
    int nc;

    for(nc=0;nc<dvdintlaux[0].numcol;nc++) dvdintlaux[0].c[nc].offset-=(int)&svdintlaux;

    vdselvalorcampo=abrecursor(SELVALORCAMPO);
    definetodo(vdselvalorcampo,svdintlaux.valor,sizeof(svdintlaux.valor),V10CADENA,
               NULL);
    bindtodo(vdselvalorcampo,"TIPOINTERFASE",svdintlaux.tipointerfase,sizeof(svdintlaux.tipointerfase),V10CADENA,
             "FORMATO",svdintlaux.formato,sizeof(svdintlaux.formato),V10CADENA,
             "REGISTRO",svdintlaux.registro,sizeof(svdintlaux.registro),V10CADENA,
             "CAMPO",svdintlaux.campo,sizeof(svdintlaux.campo),V10CADENA,
             "TABLA",svdintlaux.tabla,sizeof(svdintlaux.tabla),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_INTLAUX);
        init = 1;
    }
}

static void init_selreggral(void)
{
    int nc;

    for(nc=0;nc<dvdintlaux[0].numcol;nc++) dvdintlaux[0].c[nc].offset-=(int)&svdintlaux;

    vdselreggral=abrecursor(SELREGGRAL);
    definetodo(vdselreggral,svdintlaux.tipointerfase,sizeof(svdintlaux.tipointerfase),V10CADENA,
               svdintlaux.formato,sizeof(svdintlaux.formato),V10CADENA,
               svdintlaux.formatopadre,sizeof(svdintlaux.formatopadre),V10CADENA,
               NULL);
    bindtodo(vdselreggral,"STATUS",&svdintlaux.status,sizeof(svdintlaux.status),V10LONG,
             "STATUSCAB",&svdintlaux.statuscab,sizeof(svdintlaux.statuscab),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_INTLAUX);
        init = 1;
    }
}

static void init_seltransfecha(void)
{
    int nc;

    for(nc=0;nc<dvdintlaux[0].numcol;nc++) dvdintlaux[0].c[nc].offset-=(int)&svdintlaux;

    vdseltransfecha=abrecursor(SELTRANSFECHA);
    definetodo(vdseltransfecha,svdintlaux.fechasal,sizeof(svdintlaux.fechasal),V10CADENA,
               NULL);
    bindtodo(vdseltransfecha,"FECHAENT",svdintlaux.fechaent,sizeof(svdintlaux.fechaent),V10CADENA,
             "FMTOENT",svdintlaux.fmtoent,sizeof(svdintlaux.fmtoent),V10CADENA,
             "FMTOSAL",svdintlaux.fmtosal,sizeof(svdintlaux.fmtosal),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_INTLAUX);
        init = 1;
    }
}

diccionario *INTLAUXdamediccionario(void)
{
    return(&dintlaux);
}

int INTLAUXbuscadameroid(char *tabla,char *tablaorig,char *tipointerfase,char *formato,char *registro,vdintlauxs *intlaux)
{
    int vdret;
    if (vdseldameroid==NULL) init_seldameroid();
    memset(&svdintlaux,0,sizeof(svdintlaux));
    strcpy(svdintlaux.tabla,tabla);
    strcpy(svdintlaux.tablaorig,tablaorig);
    strcpy(svdintlaux.tipointerfase,tipointerfase);
    strcpy(svdintlaux.formato,formato);
    strcpy(svdintlaux.registro,registro);
    vdret=ejefetchcursor(vdseldameroid);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch INTLAUXbuscadameroid vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *intlaux=svdintlaux;
    return(vdret);
}

int INTLAUXnextdameroid(vdintlauxs *intlaux)
{
    int vdret;
    vdret=fetchcursor(vdseldameroid);
    if (!vdret) {
        *intlaux=svdintlaux;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldameroid);
    return(VD_EERRORACLE);
}

int INTLAUXbuscavalorcampo(char *tipointerfase,char *formato,char *registro,char *campo,char *tabla,vdintlauxs *intlaux)
{
    int vdret;
    if (vdselvalorcampo==NULL) init_selvalorcampo();
    memset(&svdintlaux,0,sizeof(svdintlaux));
    strcpy(svdintlaux.tipointerfase,tipointerfase);
    strcpy(svdintlaux.formato,formato);
    strcpy(svdintlaux.registro,registro);
    strcpy(svdintlaux.campo,campo);
    strcpy(svdintlaux.tabla,tabla);
    vdret=ejefetchcursor(vdselvalorcampo);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch INTLAUXbuscavalorcampo vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *intlaux=svdintlaux;
    return(vdret);
}

int INTLAUXnextvalorcampo(vdintlauxs *intlaux)
{
    int vdret;
    vdret=fetchcursor(vdselvalorcampo);
    if (!vdret) {
        *intlaux=svdintlaux;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselvalorcampo);
    return(VD_EERRORACLE);
}

int INTLAUXbuscareggral(long status,long statuscab,vdintlauxs *intlaux)
{
    int vdret;
    if (vdselreggral==NULL) init_selreggral();
    memset(&svdintlaux,0,sizeof(svdintlaux));
    svdintlaux.status=status;
    svdintlaux.statuscab=statuscab;
    vdret=ejefetchcursor(vdselreggral);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch INTLAUXbuscareggral vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *intlaux=svdintlaux;
    return(vdret);
}

int INTLAUXnextreggral(vdintlauxs *intlaux)
{
    int vdret;
    vdret=fetchcursor(vdselreggral);
    if (!vdret) {
        *intlaux=svdintlaux;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselreggral);
    return(VD_EERRORACLE);
}

int INTLAUXseltransfecha(char *fechaent,char *fmtoent,char *fmtosal,vdintlauxs *intlaux)
{
    int vdret;
    if (vdseltransfecha==NULL) init_seltransfecha();
    memset(&svdintlaux,0,sizeof(svdintlaux));
    strcpy(svdintlaux.fechaent,fechaent);
    strcpy(svdintlaux.fmtoent,fmtoent);
    strcpy(svdintlaux.fmtosal,fmtosal);
    vdret=ejefetchcursor(vdseltransfecha);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch INTLAUXbuscatransfecha vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *intlaux=svdintlaux;
    return(vdret);
}

char * INTLAUXdebug(vdintlauxs *intlaux)
{
    debugestruct(&dintlaux,intlaux,msgdebugintlaux);
    return(msgdebugintlaux);
}

