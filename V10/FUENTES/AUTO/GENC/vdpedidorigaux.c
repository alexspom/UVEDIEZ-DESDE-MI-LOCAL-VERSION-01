// Modulo generado automaticamente a partir de VDPEDIDORIGAUX.DEF
//#***
//# VDPEDIDORIGAUX.DEF - Generación automática del código c SOLOQUERY para pedidos originales
//# 
//# Propósito: idem.
//#           
//# Autor	 : RFD
//# Revisado por: 
//# Fecha  : 13-03-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=PORI;
//EXTRA=RETORNA,V10LONG;
//
//
//PROCEDURE=VALPEDIDORIGCAB,BEGIN 
//                       VDPED.VALPEDIDORIGCAB(:VDPEDIDORIGCAB.CODDIV,:VDPEDIDORIGCAB.ANOPED,:VDPEDIDORIGCAB.CODPED,:VDPEDIDORIGCAB.SEQPED,:RETORNA);
//                     END;@
//
//PROCEDURE=VALPEDIDORIGLIN,BEGIN 
//                       VDPED.VALPEDIDORIGLIN(:VDPEDIDORIGLIN.CODDIV,:VDPEDIDORIGLIN.ANOPED,:VDPEDIDORIGLIN.CODPED,:VDPEDIDORIGLIN.SEQPED,:VDPEDIDORIGLIN.SEQLINEA,:RETORNA);
//                     END;@
//
//PROCEDURE=BORRAPELAANULAR,BEGIN
//                       VPED.BORRAPELAANULAR(:VDPEDIDORIGLIN.CODDIV,:VDPEDIDORIGLIN.ANOPED,:VDPEDIDORIGLIN.CODPED,:VDPEDIDORIGCAB.SEQPED,:VDPEDIDORIGLIN.STATUS);
//                     END;@  
//
//PROCEDURE=INSERTACABECERA,BEGIN 
//                    VDPED.INSERTACABECERA(:VDPEDIDOCAB.CODDIV,:VDPEDIDOCAB.ANOPED,:VDPEDIDOCAB.CODPED,:VDPEDIDOCAB.SEQPED,:VDPEDIDOCAB.STATUS,:RETORNA);
//                    END;@
//
//PROCEDURE=INSERTALINEA,BEGIN 
//                    VDPED.INSERTALINEA(:VDPEDIDOLIN.CODDIV,:VDPEDIDOLIN.ANOPED,:VDPEDIDOLIN.CODPED,:VDPEDIDOLIN.SEQPED,:VDPEDIDOLIN.SEQLINEA,:RETORNA);
//                    END;@
//
//CURSOR=SECUENCIA, SELECT VDPED.DAMESECUENCIA(:VDPEDIDOCAB.CODDIV,:VDPEDIDOCAB.ANOPED,:VDPEDIDOCAB.CODPED) SECUENCIA FROM DUAL;

#include "vdpedidos.h"\

#define SELVALPEDIDORIGCAB "BEGIN  VDPED.VALPEDIDORIGCAB(:CODDIV,:ANOPED,:CODPED,:SEQPED,:RETORNA); END;"
static v10cursors *vdselvalpedidorigcab;
#define SELVALPEDIDORIGLIN "BEGIN  VDPED.VALPEDIDORIGLIN(:CODDIV,:ANOPED,:CODPED,:SEQPED,:SEQLINEA,:RETORNA); END;"
static v10cursors *vdselvalpedidoriglin;
#define SELBORRAPELAANULAR "BEGIN VPED.BORRAPELAANULAR(:CODDIV,:ANOPED,:CODPED,:SEQPED,:STATUS); END;"
static v10cursors *vdselborrapelaanular;
#define SELINSERTACABECERA "BEGIN  VDPED.INSERTACABECERA(:CODDIV,:ANOPED,:CODPED,:SEQPED,:STATUS,:RETORNA); END;"
static v10cursors *vdselinsertacabecera;
#define SELINSERTALINEA "BEGIN  VDPED.INSERTALINEA(:CODDIV,:ANOPED,:CODPED,:SEQPED,:SEQLINEA,:RETORNA); END;"
static v10cursors *vdselinsertalinea;
#define SELSECUENCIA " SELECT VDPED.DAMESECUENCIA(:CODDIV,:ANOPED,:CODPED) SECUENCIA FROM DUAL"
static v10cursors *vdselsecuencia;

static vdporis svdpori;

static diccols colvdpori[]={ 
    {"RETORNA",V10LONG,(int)&svdpori.retorna,sizeof(svdpori.retorna)},
    {"CODDIV",V10CADENA,(int)&svdpori.coddiv,sizeof(svdpori.coddiv)},
    {"ANOPED",V10LONG,(int)&svdpori.anoped,sizeof(svdpori.anoped)},
    {"CODPED",V10CADENA,(int)&svdpori.codped,sizeof(svdpori.codped)},
    {"SEQPED",V10LONG,(int)&svdpori.seqped,sizeof(svdpori.seqped)},
    {"SEQLINEA",V10LONG,(int)&svdpori.seqlinea,sizeof(svdpori.seqlinea)},
    {"STATUS",V10LONG,(int)&svdpori.status,sizeof(svdpori.status)},
    {"SECUENCIA",V10LONG,(int)&svdpori.secuencia,sizeof(svdpori.secuencia)}
    };

static diccionarios dvdpori[]={
    {colvdpori,8}
    };

diccionario dpori={dvdpori,1};

static char msgdebugpori[LCADENABIG];

static int init=0;


static void fin_vd_PORI(void)
{
    if(vdselvalpedidorigcab){
        liberacursor(vdselvalpedidorigcab);
        vdselvalpedidorigcab=NULL;
    }
    if(vdselvalpedidoriglin){
        liberacursor(vdselvalpedidoriglin);
        vdselvalpedidoriglin=NULL;
    }
    if(vdselborrapelaanular){
        liberacursor(vdselborrapelaanular);
        vdselborrapelaanular=NULL;
    }
    if(vdselinsertacabecera){
        liberacursor(vdselinsertacabecera);
        vdselinsertacabecera=NULL;
    }
    if(vdselinsertalinea){
        liberacursor(vdselinsertalinea);
        vdselinsertalinea=NULL;
    }
    if(vdselsecuencia){
        liberacursor(vdselsecuencia);
        vdselsecuencia=NULL;
    }
}


static void init_selvalpedidorigcab(void)
{
    int nc;

    for(nc=0;nc<dvdpori[0].numcol;nc++) dvdpori[0].c[nc].offset-=(int)&svdpori;

    vdselvalpedidorigcab=abrecursordebug(SELVALPEDIDORIGCAB,256);
    definetodo(vdselvalpedidorigcab,NULL);
    bindtodo(vdselvalpedidorigcab,"CODDIV",svdpori.coddiv,sizeof(svdpori.coddiv),V10CADENA,
             "ANOPED",&svdpori.anoped,sizeof(svdpori.anoped),V10LONG,
             "CODPED",svdpori.codped,sizeof(svdpori.codped),V10CADENA,
             "SEQPED",&svdpori.seqped,sizeof(svdpori.seqped),V10LONG,
             "RETORNA",&svdpori.retorna,sizeof(svdpori.retorna),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PORI);
        init = 1;
    }
}

static void init_selvalpedidoriglin(void)
{
    int nc;

    for(nc=0;nc<dvdpori[0].numcol;nc++) dvdpori[0].c[nc].offset-=(int)&svdpori;

    vdselvalpedidoriglin=abrecursordebug(SELVALPEDIDORIGLIN,256);
    definetodo(vdselvalpedidoriglin,NULL);
    bindtodo(vdselvalpedidoriglin,"CODDIV",svdpori.coddiv,sizeof(svdpori.coddiv),V10CADENA,
             "ANOPED",&svdpori.anoped,sizeof(svdpori.anoped),V10LONG,
             "CODPED",svdpori.codped,sizeof(svdpori.codped),V10CADENA,
             "SEQPED",&svdpori.seqped,sizeof(svdpori.seqped),V10LONG,
             "SEQLINEA",&svdpori.seqlinea,sizeof(svdpori.seqlinea),V10LONG,
             "RETORNA",&svdpori.retorna,sizeof(svdpori.retorna),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PORI);
        init = 1;
    }
}

static void init_selborrapelaanular(void)
{
    int nc;

    for(nc=0;nc<dvdpori[0].numcol;nc++) dvdpori[0].c[nc].offset-=(int)&svdpori;

    vdselborrapelaanular=abrecursordebug(SELBORRAPELAANULAR,256);
    definetodo(vdselborrapelaanular,NULL);
    bindtodo(vdselborrapelaanular,"CODDIV",svdpori.coddiv,sizeof(svdpori.coddiv),V10CADENA,
             "ANOPED",&svdpori.anoped,sizeof(svdpori.anoped),V10LONG,
             "CODPED",svdpori.codped,sizeof(svdpori.codped),V10CADENA,
             "SEQPED",&svdpori.seqped,sizeof(svdpori.seqped),V10LONG,
             "STATUS",&svdpori.status,sizeof(svdpori.status),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PORI);
        init = 1;
    }
}

static void init_selinsertacabecera(void)
{
    int nc;

    for(nc=0;nc<dvdpori[0].numcol;nc++) dvdpori[0].c[nc].offset-=(int)&svdpori;

    vdselinsertacabecera=abrecursordebug(SELINSERTACABECERA,256);
    definetodo(vdselinsertacabecera,NULL);
    bindtodo(vdselinsertacabecera,"CODDIV",svdpori.coddiv,sizeof(svdpori.coddiv),V10CADENA,
             "ANOPED",&svdpori.anoped,sizeof(svdpori.anoped),V10LONG,
             "CODPED",svdpori.codped,sizeof(svdpori.codped),V10CADENA,
             "SEQPED",&svdpori.seqped,sizeof(svdpori.seqped),V10LONG,
             "STATUS",&svdpori.status,sizeof(svdpori.status),V10LONG,
             "RETORNA",&svdpori.retorna,sizeof(svdpori.retorna),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PORI);
        init = 1;
    }
}

static void init_selinsertalinea(void)
{
    int nc;

    for(nc=0;nc<dvdpori[0].numcol;nc++) dvdpori[0].c[nc].offset-=(int)&svdpori;

    vdselinsertalinea=abrecursordebug(SELINSERTALINEA,256);
    definetodo(vdselinsertalinea,NULL);
    bindtodo(vdselinsertalinea,"CODDIV",svdpori.coddiv,sizeof(svdpori.coddiv),V10CADENA,
             "ANOPED",&svdpori.anoped,sizeof(svdpori.anoped),V10LONG,
             "CODPED",svdpori.codped,sizeof(svdpori.codped),V10CADENA,
             "SEQPED",&svdpori.seqped,sizeof(svdpori.seqped),V10LONG,
             "SEQLINEA",&svdpori.seqlinea,sizeof(svdpori.seqlinea),V10LONG,
             "RETORNA",&svdpori.retorna,sizeof(svdpori.retorna),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PORI);
        init = 1;
    }
}

static void init_selsecuencia(void)
{
    int nc;

    for(nc=0;nc<dvdpori[0].numcol;nc++) dvdpori[0].c[nc].offset-=(int)&svdpori;

    vdselsecuencia=abrecursordebug(SELSECUENCIA,256);
    definetodo(vdselsecuencia,&svdpori.secuencia,sizeof(svdpori.secuencia),V10LONG,
               NULL);
    bindtodo(vdselsecuencia,"CODDIV",svdpori.coddiv,sizeof(svdpori.coddiv),V10CADENA,
             "ANOPED",&svdpori.anoped,sizeof(svdpori.anoped),V10LONG,
             "CODPED",svdpori.codped,sizeof(svdpori.codped),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PORI);
        init = 1;
    }
}

diccionario *PORIdamediccionario(void)
{
    return(&dpori);
}

int PORIprocvalpedidorigcab(char *coddiv,long anoped,char *codped,long seqped,long retorna,vdporis *pori)
{
    int vdret;
    if (vdselvalpedidorigcab==NULL) init_selvalpedidorigcab();
    memset(&svdpori,0,sizeof(svdpori));
    strcpy(svdpori.coddiv,coddiv);
    svdpori.anoped=anoped;
    strcpy(svdpori.codped,codped);
    svdpori.seqped=seqped;
    svdpori.retorna=retorna;
    vdret=ejecutacursor(vdselvalpedidorigcab);
    if(vdret) {
        v10log(LOGDEBUGAPI,"Ejecuta PORIprocvalpedidorigcab vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pori=svdpori;
    return(vdret);
}

int PORIprocvalpedidoriglin(char *coddiv,long anoped,char *codped,long seqped,long seqlinea,long retorna,vdporis *pori)
{
    int vdret;
    if (vdselvalpedidoriglin==NULL) init_selvalpedidoriglin();
    memset(&svdpori,0,sizeof(svdpori));
    strcpy(svdpori.coddiv,coddiv);
    svdpori.anoped=anoped;
    strcpy(svdpori.codped,codped);
    svdpori.seqped=seqped;
    svdpori.seqlinea=seqlinea;
    svdpori.retorna=retorna;
    vdret=ejecutacursor(vdselvalpedidoriglin);
    if(vdret) {
        v10log(LOGDEBUGAPI,"Ejecuta PORIprocvalpedidoriglin vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pori=svdpori;
    return(vdret);
}

int PORIprocborrapelaanular(char *coddiv,long anoped,char *codped,long seqped,long status,vdporis *pori)
{
    int vdret;
    if (vdselborrapelaanular==NULL) init_selborrapelaanular();
    memset(&svdpori,0,sizeof(svdpori));
    strcpy(svdpori.coddiv,coddiv);
    svdpori.anoped=anoped;
    strcpy(svdpori.codped,codped);
    svdpori.seqped=seqped;
    svdpori.status=status;
    vdret=ejecutacursor(vdselborrapelaanular);
    if(vdret) {
        v10log(LOGDEBUGAPI,"Ejecuta PORIprocborrapelaanular vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pori=svdpori;
    return(vdret);
}

int PORIprocinsertacabecera(char *coddiv,long anoped,char *codped,long seqped,long status,long retorna,vdporis *pori)
{
    int vdret;
    if (vdselinsertacabecera==NULL) init_selinsertacabecera();
    memset(&svdpori,0,sizeof(svdpori));
    strcpy(svdpori.coddiv,coddiv);
    svdpori.anoped=anoped;
    strcpy(svdpori.codped,codped);
    svdpori.seqped=seqped;
    svdpori.status=status;
    svdpori.retorna=retorna;
    vdret=ejecutacursor(vdselinsertacabecera);
    if(vdret) {
        v10log(LOGDEBUGAPI,"Ejecuta PORIprocinsertacabecera vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pori=svdpori;
    return(vdret);
}

int PORIprocinsertalinea(char *coddiv,long anoped,char *codped,long seqped,long seqlinea,long retorna,vdporis *pori)
{
    int vdret;
    if (vdselinsertalinea==NULL) init_selinsertalinea();
    memset(&svdpori,0,sizeof(svdpori));
    strcpy(svdpori.coddiv,coddiv);
    svdpori.anoped=anoped;
    strcpy(svdpori.codped,codped);
    svdpori.seqped=seqped;
    svdpori.seqlinea=seqlinea;
    svdpori.retorna=retorna;
    vdret=ejecutacursor(vdselinsertalinea);
    if(vdret) {
        v10log(LOGDEBUGAPI,"Ejecuta PORIprocinsertalinea vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pori=svdpori;
    return(vdret);
}

int PORIbuscasecuencia(char *coddiv,long anoped,char *codped,vdporis *pori)
{
    int vdret;
    if (vdselsecuencia==NULL) init_selsecuencia();
    memset(&svdpori,0,sizeof(svdpori));
    strcpy(svdpori.coddiv,coddiv);
    svdpori.anoped=anoped;
    strcpy(svdpori.codped,codped);
    vdret=ejefetchcursor(vdselsecuencia);
    if(vdret) {
        v10log(LOGDEBUGAPI,"Ejefetch PORIbuscasecuencia vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pori=svdpori;
    return(vdret);
}

int PORInextsecuencia(vdporis *pori)
{
    int vdret;
    vdret=fetchcursor(vdselsecuencia);
    if (!vdret) {
        *pori=svdpori;
        v10log(LOGDEBUGAPI,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselsecuencia);
    return(VD_EERRORACLE);
}

char * PORIdebug(vdporis *pori)
{
    debugestruct(&dpori,pori,msgdebugpori);
    return(msgdebugpori);
}

