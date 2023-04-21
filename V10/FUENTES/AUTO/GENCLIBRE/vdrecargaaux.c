// Modulo generado automaticamente a partir de VDRECARGAAUX.DEF
//#***
//# VDRECARGAR.DEF - Generación automática del código c SOLOQUERY para Recargas
//# 
//# Propósito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 11-03-2008                                          
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=RECARGA;
//EXTRA=LISTAALMAS,V10CADENA,1024
//EXTRA=LISTAAREAS,V10CADENA,1024
//
//
//CURSOR=UBIS, SELECT * FROM TABLE(VDRECARGA.DAMEUBIRECARGAR(:LISTAAREAS,:LISTAALMAS));

#include "vd.h"\

#define SELUBIS " SELECT * FROM TABLE(VDRECARGA.DAMEUBIRECARGAR(:LISTAAREAS,:LISTAALMAS))"
static v10cursors *vdselubis;

static vdrecargas svdrecarga;

static diccols colvdrecarga[]={ 
    {"LISTAALMAS",V10CADENA,(size_t)&svdrecarga.listaalmas,sizeof(svdrecarga.listaalmas)},
    {"LISTAAREAS",V10CADENA,(size_t)&svdrecarga.listaareas,sizeof(svdrecarga.listaareas)},
    {"CODUBI",V10CADENA,(size_t)&svdrecarga.codubi,sizeof(svdrecarga.codubi)},
    {"RECARGAR",V10CADENA,(size_t)&svdrecarga.recargar,sizeof(svdrecarga.recargar)},
    {"UNIAGRUPAE",V10CADENA,(size_t)&svdrecarga.uniagrupae,sizeof(svdrecarga.uniagrupae)},
    {"UNICAPAC",V10CADENA,(size_t)&svdrecarga.unicapac,sizeof(svdrecarga.unicapac)},
    {"UNIAGRUPADEML",V10CADENA,(size_t)&svdrecarga.uniagrupademl,sizeof(svdrecarga.uniagrupademl)},
    {"STKMAX",V10LONG,(size_t)&svdrecarga.stkmax,sizeof(svdrecarga.stkmax)},
    {"STKMIN",V10LONG,(size_t)&svdrecarga.stkmin,sizeof(svdrecarga.stkmin)},
    {"STKURG",V10LONG,(size_t)&svdrecarga.stkurg,sizeof(svdrecarga.stkurg)},
    {"CODART",V10CADENA,(size_t)&svdrecarga.codart,sizeof(svdrecarga.codart)},
    {"STOCK",V10LONG,(size_t)&svdrecarga.stock,sizeof(svdrecarga.stock)},
    {"ORDENADO",V10LONG,(size_t)&svdrecarga.ordenado,sizeof(svdrecarga.ordenado)},
    {"CANTIDAD",V10LONG,(size_t)&svdrecarga.cantidad,sizeof(svdrecarga.cantidad)},
    {"TIPOREDONDEO",V10CADENA,(size_t)&svdrecarga.tiporedondeo,sizeof(svdrecarga.tiporedondeo)}
    };

static diccionarios dvdrecarga[]={
    {colvdrecarga,15}
    };

diccionario drecarga={dvdrecarga,1};

static char msgdebugrecarga[LCADENABIG];

static int init=0;


static void fin_vd_RECARGA(void)
{
    if(vdselubis){
        liberacursor(vdselubis);
        vdselubis=NULL;
    }
}


static void init_selubis(void)
{
    int nc;

    for(nc=0;nc<dvdrecarga[0].numcol;nc++) dvdrecarga[0].c[nc].offset-=(size_t)&svdrecarga;

    vdselubis=abrecursor(SELUBIS);
    definetodo(vdselubis,svdrecarga.codubi,sizeof(svdrecarga.codubi),V10CADENA,
               svdrecarga.recargar,sizeof(svdrecarga.recargar),V10CADENA,
               svdrecarga.uniagrupae,sizeof(svdrecarga.uniagrupae),V10CADENA,
               svdrecarga.unicapac,sizeof(svdrecarga.unicapac),V10CADENA,
               svdrecarga.uniagrupademl,sizeof(svdrecarga.uniagrupademl),V10CADENA,
               &svdrecarga.stkmax,sizeof(svdrecarga.stkmax),V10LONG,
               &svdrecarga.stkmin,sizeof(svdrecarga.stkmin),V10LONG,
               &svdrecarga.stkurg,sizeof(svdrecarga.stkurg),V10LONG,
               svdrecarga.codart,sizeof(svdrecarga.codart),V10CADENA,
               &svdrecarga.stock,sizeof(svdrecarga.stock),V10LONG,
               &svdrecarga.ordenado,sizeof(svdrecarga.ordenado),V10LONG,
               &svdrecarga.cantidad,sizeof(svdrecarga.cantidad),V10LONG,
               svdrecarga.tiporedondeo,sizeof(svdrecarga.tiporedondeo),V10CADENA,
               NULL);
    bindtodo(vdselubis,"LISTAAREAS",svdrecarga.listaareas,sizeof(svdrecarga.listaareas),V10CADENA,
             "LISTAALMAS",svdrecarga.listaalmas,sizeof(svdrecarga.listaalmas),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_RECARGA);
        init = 1;
    }
}

diccionario *RECARGAdamediccionario(void)
{
    return(&drecarga);
}

int RECARGAbuscaubis(char *listaareas,char *listaalmas,vdrecargas *recarga)
{
    int vdret;
    if (vdselubis==NULL) init_selubis();
    memset(&svdrecarga,0,sizeof(svdrecarga));
    strcpy(svdrecarga.listaareas,listaareas);
    strcpy(svdrecarga.listaalmas,listaalmas);
    vdret=ejefetchcursor(vdselubis);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch RECARGAbuscaubis vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *recarga=svdrecarga;
    return(vdret);
}

int RECARGAnextubis(vdrecargas *recarga)
{
    int vdret;
    vdret=fetchcursor(vdselubis);
    if (!vdret) {
        *recarga=svdrecarga;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselubis);
    return(VD_EERRORACLE);
}

char * RECARGAdebug(vdrecargas *recarga)
{
    debugestruct(&drecarga,recarga,msgdebugrecarga);
    return(msgdebugrecarga);
}

