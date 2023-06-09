// Modulo generado automaticamente a partir de VDSERIEAUX.DEF
//#***
//# VDSERIEAUX.DEF - Generaci�n autom�tica del c�digo c SOLOQUERY para Series                                                       
//# 
//# Prop�sito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 24-06-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=SERIES;
//
//EXTRA=RET,V10LONG;
//EXTRA=STPECLIMITE,V10LONG;
//EXTRA=STPECEXPEDIDO,V10LONG;
//
//PROCEDURE=EXPIDESERIE,BEGIN 
//
//                           VDSERIES.EXPIDEMERCANCIA(:VDSERIEEXP.CODSERIEEXP,
//                                                    :VDSERIEEXP.STATUS,
//                                                    :STPECLIMITE,:STPECEXPEDIDO,                                                    
//                                                    :VDCONCEPTO.CODCONCE,:VDMOVIM.CODUBIDEST,
//                                                    :VDCOMEN.COMENTARIO, :RET);
//                     END;@
//                     
//                            
//                                                                                       	

#include "vdpedidos.h"\

#define SELEXPIDESERIE "BEGIN  VDSERIES.EXPIDEMERCANCIA(:CODSERIEEXP, :STATUS, :STPECLIMITE,:STPECEXPEDIDO,                                                     :CODCONCE,:CODUBIDEST, :COMENTARIO, :RET); END;"
static v10cursors *vdselexpideserie;

static vdseriess svdseries;

static diccols colvdseries[]={ 
    {"RET",V10LONG,(size_t)&svdseries.ret,sizeof(svdseries.ret)},
    {"STPECLIMITE",V10LONG,(size_t)&svdseries.stpeclimite,sizeof(svdseries.stpeclimite)},
    {"STPECEXPEDIDO",V10LONG,(size_t)&svdseries.stpecexpedido,sizeof(svdseries.stpecexpedido)},
    {"CODSERIEEXP",V10LONG,(size_t)&svdseries.codserieexp,sizeof(svdseries.codserieexp)},
    {"STATUS",V10LONG,(size_t)&svdseries.status,sizeof(svdseries.status)},
    {"CODCONCE",V10CADENA,(size_t)&svdseries.codconce,sizeof(svdseries.codconce)},
    {"CODUBIDEST",V10CADENA,(size_t)&svdseries.codubidest,sizeof(svdseries.codubidest)},
    {"COMENTARIO",V10CADENA,(size_t)&svdseries.comentario,sizeof(svdseries.comentario)}
    };

static diccionarios dvdseries[]={
    {colvdseries,8}
    };

diccionario dseries={dvdseries,1};

static char msgdebugseries[LCADENABIG];

static int init=0;


static void fin_vd_SERIES(void)
{
    if(vdselexpideserie){
        liberacursor(vdselexpideserie);
        vdselexpideserie=NULL;
    }
}


static void init_selexpideserie(void)
{
    int nc;

    for(nc=0;nc<dvdseries[0].numcol;nc++) dvdseries[0].c[nc].offset-=(size_t)&svdseries;

    vdselexpideserie=abrecursor(SELEXPIDESERIE);
    definetodo(vdselexpideserie,NULL);
    bindtodo(vdselexpideserie,"CODSERIEEXP",&svdseries.codserieexp,sizeof(svdseries.codserieexp),V10LONG,
             "STATUS",&svdseries.status,sizeof(svdseries.status),V10LONG,
             "STPECLIMITE",&svdseries.stpeclimite,sizeof(svdseries.stpeclimite),V10LONG,
             "STPECEXPEDIDO",&svdseries.stpecexpedido,sizeof(svdseries.stpecexpedido),V10LONG,
             "CODCONCE",svdseries.codconce,sizeof(svdseries.codconce),V10CADENA,
             "CODUBIDEST",svdseries.codubidest,sizeof(svdseries.codubidest),V10CADENA,
             "COMENTARIO",svdseries.comentario,sizeof(svdseries.comentario),V10CADENA,
             "RET",&svdseries.ret,sizeof(svdseries.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_SERIES);
        init = 1;
    }
}

diccionario *SERIESdamediccionario(void)
{
    return(&dseries);
}

int SERIESprocexpideserie(long codserieexp,long status,long stpeclimite,long stpecexpedido,char *codconce,char *codubidest,char *comentario,long ret,vdseriess *series)
{
    int vdret;
    if (vdselexpideserie==NULL) init_selexpideserie();
    memset(&svdseries,0,sizeof(svdseries));
    svdseries.codserieexp=codserieexp;
    svdseries.status=status;
    svdseries.stpeclimite=stpeclimite;
    svdseries.stpecexpedido=stpecexpedido;
    strcpy(svdseries.codconce,codconce);
    strcpy(svdseries.codubidest,codubidest);
    strcpy(svdseries.comentario,comentario);
    svdseries.ret=ret;
    vdret=ejecutacursor(vdselexpideserie);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta SERIESprocexpideserie vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *series=svdseries;
    return(vdret);
}

char * SERIESdebug(vdseriess *series)
{
    debugestruct(&dseries,series,msgdebugseries);
    return(msgdebugseries);
}

