// Modulo generado automaticamente a partir de VDACTSTKBUL.DEF
//#***
//# VDACTSTKBUL.DEF - Generaci�n autom�tica del c�digo c para actualizado de stock y bultos de pedido
//# 
//# Prop�sito: idem.
//#           
//# Autor	 : RFD
//# Revisado por: 
//# Fecha  : 06-05-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=STKBUL;
//EXTRA=RET,V10LONG
//
//
//PROCEDURE=ACTSTKBUL,BEGIN 
//                        VDACTSTKBUL.ACTSTOCKBULTOS(:VDMOVIM.CODMOV,:VDBULTOCAB.STATUS,:RET) ;
//                    END;@

#include "vdpedidos.h"\

#define SELACTSTKBUL "BEGIN  VDACTSTKBUL.ACTSTOCKBULTOS(:CODMOV,:STATUS,:RET) ; END;"
static v10cursors *vdselactstkbul;

static vdstkbuls svdstkbul;

static diccols colvdstkbul[]={ 
    {"RET",V10LONG,(int)&svdstkbul.ret,sizeof(svdstkbul.ret)},
    {"CODMOV",V10LONG,(int)&svdstkbul.codmov,sizeof(svdstkbul.codmov)},
    {"STATUS",V10LONG,(int)&svdstkbul.status,sizeof(svdstkbul.status)}
    };

static diccionarios dvdstkbul[]={
    {colvdstkbul,3}
    };

diccionario dstkbul={dvdstkbul,1};

static char msgdebugstkbul[LCADENABIG];

static int init=0;


static void fin_vd_STKBUL(void)
{
    if(vdselactstkbul){
        liberacursor(vdselactstkbul);
        vdselactstkbul=NULL;
    }
}


static void init_selactstkbul(void)
{
    int nc;

    for(nc=0;nc<dvdstkbul[0].numcol;nc++) dvdstkbul[0].c[nc].offset-=(int)&svdstkbul;

    vdselactstkbul=abrecursor(SELACTSTKBUL);
    definetodo(vdselactstkbul,NULL);
    bindtodo(vdselactstkbul,"CODMOV",&svdstkbul.codmov,sizeof(svdstkbul.codmov),V10LONG,
             "STATUS",&svdstkbul.status,sizeof(svdstkbul.status),V10LONG,
             "RET",&svdstkbul.ret,sizeof(svdstkbul.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKBUL);
        init = 1;
    }
}

diccionario *STKBULdamediccionario(void)
{
    return(&dstkbul);
}

int STKBULprocactstkbul(long codmov,long status,long ret,vdstkbuls *stkbul)
{
    int vdret;
    if (vdselactstkbul==NULL) init_selactstkbul();
    memset(&svdstkbul,0,sizeof(svdstkbul));
    svdstkbul.codmov=codmov;
    svdstkbul.status=status;
    svdstkbul.ret=ret;
    vdret=ejecutacursor(vdselactstkbul);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKBULprocactstkbul vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkbul=svdstkbul;
    return(vdret);
}

char * STKBULdebug(vdstkbuls *stkbul)
{
    debugestruct(&dstkbul,stkbul,msgdebugstkbul);
    return(msgdebugstkbul);
}

