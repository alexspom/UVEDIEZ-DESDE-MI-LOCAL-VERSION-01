// Modulo generado automaticamente a partir de VDDEMANDAAUX.DEF
//#***
//# VDSTOCK.DEF - Generación automática del código c SOLOQUERY sobre la tablas VDDEMANDACAB y VDDEMANDALIN                                                    
//# 
//# Propósito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 06-03-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=DEM;
//EXTRA=AGRUPALINEAS,V10CADENA,1
//EXTRA=LINEASINSERTADAS,V10LONG
//EXTRA=STATUSINI,V10LONG
//EXTRA=STDEMLFINAL,V10LONG
//EXTRA=STDEMCFINAL,V10LONG
//EXTRA=REABRIRDEML,V10CADENA,1
//EXTRA=STDEMLREABRIR,V10LONG
//EXTRA=STDEMCREABRIR,V10LONG
//EXTRA=RET,V10LONG
//EXTRA=ANULABLE,V10LONG
//
//CURSOR=DEMLANULABLE, SELECT VDDEM.DEMLANULABLE(:VDDEMANDALIN.CODDEMANDA,:VDDEMANDALIN.TIPODEMANDA,:VDDEMANDALIN.LINDEMANDA) ANULABLE FROM DUAL;
//
//CURSOR=DEMCANULABLE, SELECT VDDEM.DEMCANULABLE(:VDDEMANDALIN.CODDEMANDA,:VDDEMANDALIN.TIPODEMANDA) ANULABLE FROM DUAL;
//
//PROCEDURE=ANULADEML,BEGIN                       
//                       VDDEM.ANULADEML(:VDDEMANDALIN.CODDEMANDA,:VDDEMANDALIN.TIPODEMANDA,:VDDEMANDALIN.LINDEMANDA,:RET); 
//                   END;@    
//                   
//PROCEDURE=ANULADEMC,BEGIN                       
//                       VDDEM.ANULADEMC(:VDDEMANDALIN.CODDEMANDA,:VDDEMANDALIN.TIPODEMANDA,:RET); 
//                   END;@    
//
//
//PROCEDURE=FINALIZADEML,BEGIN                       
//                       VDDEM.FINALIZADEML(:VDDEMANDALIN.CODDEMANDA,:VDDEMANDALIN.TIPODEMANDA,:VDDEMANDALIN.LINDEMANDA, 
//                        :STATUSINI,:STDEMLFINAL,:STDEMCFINAL,:REABRIRDEML,:STDEMLREABRIR,:STDEMCREABRIR,:RET); 
//                   END;@    
//                      
//PROCEDURE=CREADEMANDAPEDIDO,BEGIN
//                        VDDEM.CREADEMANDAPEDIDO(:VDPEDIDOCAB.CODDIV,:VDPEDIDOCAB.ANOPED,:VDPEDIDOCAB.CODPED,:VDPEDIDOCAB.SEQPED,
//                                                :VDDEMANDACAB.BACKORDER, :VDDEMANDACAB.TIPODEMANDA, :VDDEMANDACAB.STATUS,
//                                                :VDUBICA.CODUBI, :AGRUPALINEAS, :LINEASINSERTADAS, :VDDEMANDACAB.CODDEMANDA);
//                      END;@    
//
//PROCEDURE=CREADEMANDARECARGA,BEGIN
//                        VDDEM.CREADEMANDARECARGA(:VDUBICA.CODUBI,:VDDEMANDALIN.UNIAGRUPA,:VDDEMANDALIN.CANTIDAD,:VDDEMANDALIN.TIPOREDONDEO,
//                                                 :VDDEMANDALIN.CODART,:VDDEMANDACAB.TIPODEMANDA, :VDDEMANDACAB.STATUS,:LINEASINSERTADAS, :VDDEMANDACAB.CODDEMANDA);
//                      END;@  
//                      
//CURSOR=LISTACODCOMEN, SELECT VDDEM.DAMECODCOMENDEM(:VDDEMANDACAB.CODDEMANDA,:VDDEMANDACAB.TIPODEMANDA) VDEXTRA FROM DUAL;
//                      
//%%h
//VDEXPORT int creademandapedido(vdpedidocabs *pec,char *tipodemanda,long status,char *codubiexped,char *backorder,char *agrupalineas,char *coddemanda);
//VDEXPORT int creademandarecarga(vdrecargas *rec,char *tipodemanda,long status,char *coddemanda);
//VDEXPORT int finalizademl(vddemandalins *deml, long statusini,long stdemlfinal, long stdemcfinal, char *reabrir, long stdemlreabrir, long stdemcreabrir);
//VDEXPORT int anulademl(vddemandalins *deml);
//VDEXPORT int anulademc(vddemandacabs *demc);
//
//%%c
//
//VDEXPORT int finalizademl(vddemandalins *deml, long statusini,long stdemlfinal, long stdemcfinal, char *reabrir, long stdemlreabrir, long stdemcreabrir) {
//	int ret,miret;
//	vddems dem;
//	
//	miret=0;
//	ret=DEMprocfinalizademl(deml->coddemanda,deml->tipodemanda,deml->lindemanda,statusini,stdemlfinal,stdemcfinal,reabrir,stdemlreabrir,stdemcreabrir,miret,&dem);
//	if (ret) {
//		v10log(LOGERROR,"finalizademl: Error al ejecutar PLSQL DEMprocfinalizademl\n");
//		return(ret);
//	} else {
//		return(dem.ret);
//	}
//}
//
//
//VDEXPORT int creademandapedido(vdpedidocabs *pec,char *tipodemanda,long status,char *codubiexped,char *backorder,char *agrupalineas,char *coddemanda) {
//	int ret;
//	long lineasinsertadas=0;
//	vddems dem;
// 
//	ret=DEMproccreademandapedido(pec->coddiv,pec->anoped,pec->codped,pec->seqped,backorder,tipodemanda,status,codubiexped,agrupalineas,lineasinsertadas,coddemanda,&dem);
//	if (ret) {
//		v10log(LOGERROR,"creademandapedido: Error al ejecutar PLSQL DEMproccreademandapedido\n");
//		return(ret);
//	} else {
//		if (*dem.coddemanda==0) {
//			v10log(LOGERROR,"creademandapedido: No se ha podido generar demanda del tipo %s para pedido. %s\n",
//						    tipodemanda, PEClog(pec));
//			return(-1);
//		} 
//	}
// 
//	strcopia(coddemanda,dem.coddemanda,strlen(dem.coddemanda));
//	v10log(LOGNORMAL,"creademandapedido: generadas %ld lineas de demandas en demanda %s %s\n",dem.lineasinsertadas,tipodemanda,dem.coddemanda);
//	return(0);
//}
//
//VDEXPORT int creademandarecarga(vdrecargas *rec,char *tipodemanda,long status,char *coddemanda) {
//	int ret;
//	long lineasinsertadas=0;
//	vddems dem;
// 
//	ret=DEMproccreademandarecarga(rec->codubi, rec->uniagrupademl, rec->cantidad, rec->tiporedondeo,rec->codart, tipodemanda,status,lineasinsertadas,coddemanda,&dem);
//	if (ret) {
//		v10log(LOGERROR,"creademandarecarga: Error al ejecutar PLSQL DEMproccreademandarecarga\n");
//		return(ret);
//	} else {
//		if (*dem.coddemanda==0) {
//			v10log(LOGERROR,"creademandarecarga: No se ha podido generar demanda del tipo %s para recarga de ubicación %s\n",
//						    tipodemanda, rec->codubi);
//			return(-1);
//		} 
//	} 
//	strcopia(coddemanda,dem.coddemanda,strlen(dem.coddemanda));
//	v10log(LOGNORMAL,"creademandarecarga: generadas %ld lineas de demandas en demanda %s %s\n",dem.lineasinsertadas,tipodemanda,dem.coddemanda);
//	return(0);
//}
//
//VDEXPORT int anulademl(vddemandalins *deml) {
//	int ret,miret;
//	vddems dem;
//	
//	miret=0;
//	ret=DEMprocanulademl(deml->coddemanda,deml->tipodemanda,deml->lindemanda,miret,&dem);
//	if (ret) {
//		v10log(LOGERROR,"anulademl: Error al ejecutar PLSQL DEMprocanulademl\n");
//		return(ret);
//	} else {
//		return(dem.ret);
//	}
//}
//
//VDEXPORT int anulademc(vddemandacabs *demc) {
//	int ret,miret;
//	vddems dem;
//	
//	miret=0;
//	ret=DEMprocanulademc(demc->coddemanda,demc->tipodemanda,miret,&dem);
//	if (ret) {
//		v10log(LOGERROR,"anulademc: Error al ejecutar PLSQL DEMprocanulademc\n");
//		return(ret);
//	} else {
//		return(dem.ret);
//	}
//}
//

#include "vd.h"\

#define SELDEMLANULABLE " SELECT VDDEM.DEMLANULABLE(:CODDEMANDA,:TIPODEMANDA,:LINDEMANDA) ANULABLE FROM DUAL"
static v10cursors *vdseldemlanulable;
#define SELDEMCANULABLE " SELECT VDDEM.DEMCANULABLE(:CODDEMANDA,:TIPODEMANDA) ANULABLE FROM DUAL"
static v10cursors *vdseldemcanulable;
#define SELANULADEML "BEGIN                        VDDEM.ANULADEML(:CODDEMANDA,:TIPODEMANDA,:LINDEMANDA,:RET);  END;"
static v10cursors *vdselanulademl;
#define SELANULADEMC "BEGIN                        VDDEM.ANULADEMC(:CODDEMANDA,:TIPODEMANDA,:RET);  END;"
static v10cursors *vdselanulademc;
#define SELFINALIZADEML "BEGIN                        VDDEM.FINALIZADEML(:CODDEMANDA,:TIPODEMANDA,:LINDEMANDA,  :STATUSINI,:STDEMLFINAL,:STDEMCFINAL,:REABRIRDEML,:STDEMLREABRIR,:STDEMCREABRIR,:RET);  END;"
static v10cursors *vdselfinalizademl;
#define SELCREADEMANDAPEDIDO "BEGIN VDDEM.CREADEMANDAPEDIDO(:CODDIV,:ANOPED,:CODPED,:SEQPED, :BACKORDER, :TIPODEMANDA, :STATUS, :CODUBI, :AGRUPALINEAS, :LINEASINSERTADAS, :CODDEMANDA); END;"
static v10cursors *vdselcreademandapedido;
#define SELCREADEMANDARECARGA "BEGIN VDDEM.CREADEMANDARECARGA(:CODUBI,:UNIAGRUPA,:CANTIDAD,:TIPOREDONDEO, :CODART,:TIPODEMANDA, :STATUS,:LINEASINSERTADAS, :CODDEMANDA); END;"
static v10cursors *vdselcreademandarecarga;
#define SELLISTACODCOMEN " SELECT VDDEM.DAMECODCOMENDEM(:CODDEMANDA,:TIPODEMANDA) VDEXTRA FROM DUAL"
static v10cursors *vdsellistacodcomen;

static vddems svddem;

static diccols colvddem[]={ 
    {"AGRUPALINEAS",V10CADENA,(int)&svddem.agrupalineas,sizeof(svddem.agrupalineas)},
    {"LINEASINSERTADAS",V10LONG,(int)&svddem.lineasinsertadas,sizeof(svddem.lineasinsertadas)},
    {"STATUSINI",V10LONG,(int)&svddem.statusini,sizeof(svddem.statusini)},
    {"STDEMLFINAL",V10LONG,(int)&svddem.stdemlfinal,sizeof(svddem.stdemlfinal)},
    {"STDEMCFINAL",V10LONG,(int)&svddem.stdemcfinal,sizeof(svddem.stdemcfinal)},
    {"REABRIRDEML",V10CADENA,(int)&svddem.reabrirdeml,sizeof(svddem.reabrirdeml)},
    {"STDEMLREABRIR",V10LONG,(int)&svddem.stdemlreabrir,sizeof(svddem.stdemlreabrir)},
    {"STDEMCREABRIR",V10LONG,(int)&svddem.stdemcreabrir,sizeof(svddem.stdemcreabrir)},
    {"RET",V10LONG,(int)&svddem.ret,sizeof(svddem.ret)},
    {"ANULABLE",V10LONG,(int)&svddem.anulable,sizeof(svddem.anulable)},
    {"CODDEMANDA",V10CADENA,(int)&svddem.coddemanda,sizeof(svddem.coddemanda)},
    {"TIPODEMANDA",V10CADENA,(int)&svddem.tipodemanda,sizeof(svddem.tipodemanda)},
    {"LINDEMANDA",V10LONG,(int)&svddem.lindemanda,sizeof(svddem.lindemanda)},
    {"CODDIV",V10CADENA,(int)&svddem.coddiv,sizeof(svddem.coddiv)},
    {"ANOPED",V10LONG,(int)&svddem.anoped,sizeof(svddem.anoped)},
    {"CODPED",V10CADENA,(int)&svddem.codped,sizeof(svddem.codped)},
    {"SEQPED",V10LONG,(int)&svddem.seqped,sizeof(svddem.seqped)},
    {"BACKORDER",V10CADENA,(int)&svddem.backorder,sizeof(svddem.backorder)},
    {"STATUS",V10LONG,(int)&svddem.status,sizeof(svddem.status)},
    {"CODUBI",V10CADENA,(int)&svddem.codubi,sizeof(svddem.codubi)},
    {"UNIAGRUPA",V10CADENA,(int)&svddem.uniagrupa,sizeof(svddem.uniagrupa)},
    {"CANTIDAD",V10DOUBLE,(int)&svddem.cantidad,sizeof(svddem.cantidad)},
    {"TIPOREDONDEO",V10CADENA,(int)&svddem.tiporedondeo,sizeof(svddem.tiporedondeo)},
    {"CODART",V10CADENA,(int)&svddem.codart,sizeof(svddem.codart)},
    {"VDEXTRA",V10CADENA,(int)&svddem.vdextra,sizeof(svddem.vdextra)}
    };

static diccionarios dvddem[]={
    {colvddem,25}
    };

diccionario ddem={dvddem,1};

static char msgdebugdem[LCADENABIG];

static int init=0;


static void fin_vd_DEM(void)
{
    if(vdseldemlanulable){
        liberacursor(vdseldemlanulable);
        vdseldemlanulable=NULL;
    }
    if(vdseldemcanulable){
        liberacursor(vdseldemcanulable);
        vdseldemcanulable=NULL;
    }
    if(vdselanulademl){
        liberacursor(vdselanulademl);
        vdselanulademl=NULL;
    }
    if(vdselanulademc){
        liberacursor(vdselanulademc);
        vdselanulademc=NULL;
    }
    if(vdselfinalizademl){
        liberacursor(vdselfinalizademl);
        vdselfinalizademl=NULL;
    }
    if(vdselcreademandapedido){
        liberacursor(vdselcreademandapedido);
        vdselcreademandapedido=NULL;
    }
    if(vdselcreademandarecarga){
        liberacursor(vdselcreademandarecarga);
        vdselcreademandarecarga=NULL;
    }
    if(vdsellistacodcomen){
        liberacursor(vdsellistacodcomen);
        vdsellistacodcomen=NULL;
    }
}


static void init_seldemlanulable(void)
{
    int nc;

    for(nc=0;nc<dvddem[0].numcol;nc++) dvddem[0].c[nc].offset-=(int)&svddem;

    vdseldemlanulable=abrecursor(SELDEMLANULABLE);
    definetodo(vdseldemlanulable,&svddem.anulable,sizeof(svddem.anulable),V10LONG,
               NULL);
    bindtodo(vdseldemlanulable,"CODDEMANDA",svddem.coddemanda,sizeof(svddem.coddemanda),V10CADENA,
             "TIPODEMANDA",svddem.tipodemanda,sizeof(svddem.tipodemanda),V10CADENA,
             "LINDEMANDA",&svddem.lindemanda,sizeof(svddem.lindemanda),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_DEM);
        init = 1;
    }
}

static void init_seldemcanulable(void)
{
    int nc;

    for(nc=0;nc<dvddem[0].numcol;nc++) dvddem[0].c[nc].offset-=(int)&svddem;

    vdseldemcanulable=abrecursor(SELDEMCANULABLE);
    definetodo(vdseldemcanulable,&svddem.anulable,sizeof(svddem.anulable),V10LONG,
               NULL);
    bindtodo(vdseldemcanulable,"CODDEMANDA",svddem.coddemanda,sizeof(svddem.coddemanda),V10CADENA,
             "TIPODEMANDA",svddem.tipodemanda,sizeof(svddem.tipodemanda),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_DEM);
        init = 1;
    }
}

static void init_selanulademl(void)
{
    int nc;

    for(nc=0;nc<dvddem[0].numcol;nc++) dvddem[0].c[nc].offset-=(int)&svddem;

    vdselanulademl=abrecursor(SELANULADEML);
    definetodo(vdselanulademl,NULL);
    bindtodo(vdselanulademl,"CODDEMANDA",svddem.coddemanda,sizeof(svddem.coddemanda),V10CADENA,
             "TIPODEMANDA",svddem.tipodemanda,sizeof(svddem.tipodemanda),V10CADENA,
             "LINDEMANDA",&svddem.lindemanda,sizeof(svddem.lindemanda),V10LONG,
             "RET",&svddem.ret,sizeof(svddem.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_DEM);
        init = 1;
    }
}

static void init_selanulademc(void)
{
    int nc;

    for(nc=0;nc<dvddem[0].numcol;nc++) dvddem[0].c[nc].offset-=(int)&svddem;

    vdselanulademc=abrecursor(SELANULADEMC);
    definetodo(vdselanulademc,NULL);
    bindtodo(vdselanulademc,"CODDEMANDA",svddem.coddemanda,sizeof(svddem.coddemanda),V10CADENA,
             "TIPODEMANDA",svddem.tipodemanda,sizeof(svddem.tipodemanda),V10CADENA,
             "RET",&svddem.ret,sizeof(svddem.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_DEM);
        init = 1;
    }
}

static void init_selfinalizademl(void)
{
    int nc;

    for(nc=0;nc<dvddem[0].numcol;nc++) dvddem[0].c[nc].offset-=(int)&svddem;

    vdselfinalizademl=abrecursor(SELFINALIZADEML);
    definetodo(vdselfinalizademl,NULL);
    bindtodo(vdselfinalizademl,"CODDEMANDA",svddem.coddemanda,sizeof(svddem.coddemanda),V10CADENA,
             "TIPODEMANDA",svddem.tipodemanda,sizeof(svddem.tipodemanda),V10CADENA,
             "LINDEMANDA",&svddem.lindemanda,sizeof(svddem.lindemanda),V10LONG,
             "STATUSINI",&svddem.statusini,sizeof(svddem.statusini),V10LONG,
             "STDEMLFINAL",&svddem.stdemlfinal,sizeof(svddem.stdemlfinal),V10LONG,
             "STDEMCFINAL",&svddem.stdemcfinal,sizeof(svddem.stdemcfinal),V10LONG,
             "REABRIRDEML",svddem.reabrirdeml,sizeof(svddem.reabrirdeml),V10CADENA,
             "STDEMLREABRIR",&svddem.stdemlreabrir,sizeof(svddem.stdemlreabrir),V10LONG,
             "STDEMCREABRIR",&svddem.stdemcreabrir,sizeof(svddem.stdemcreabrir),V10LONG,
             "RET",&svddem.ret,sizeof(svddem.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_DEM);
        init = 1;
    }
}

static void init_selcreademandapedido(void)
{
    int nc;

    for(nc=0;nc<dvddem[0].numcol;nc++) dvddem[0].c[nc].offset-=(int)&svddem;

    vdselcreademandapedido=abrecursor(SELCREADEMANDAPEDIDO);
    definetodo(vdselcreademandapedido,NULL);
    bindtodo(vdselcreademandapedido,"CODDIV",svddem.coddiv,sizeof(svddem.coddiv),V10CADENA,
             "ANOPED",&svddem.anoped,sizeof(svddem.anoped),V10LONG,
             "CODPED",svddem.codped,sizeof(svddem.codped),V10CADENA,
             "SEQPED",&svddem.seqped,sizeof(svddem.seqped),V10LONG,
             "BACKORDER",svddem.backorder,sizeof(svddem.backorder),V10CADENA,
             "TIPODEMANDA",svddem.tipodemanda,sizeof(svddem.tipodemanda),V10CADENA,
             "STATUS",&svddem.status,sizeof(svddem.status),V10LONG,
             "CODUBI",svddem.codubi,sizeof(svddem.codubi),V10CADENA,
             "AGRUPALINEAS",svddem.agrupalineas,sizeof(svddem.agrupalineas),V10CADENA,
             "LINEASINSERTADAS",&svddem.lineasinsertadas,sizeof(svddem.lineasinsertadas),V10LONG,
             "CODDEMANDA",svddem.coddemanda,sizeof(svddem.coddemanda),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_DEM);
        init = 1;
    }
}

static void init_selcreademandarecarga(void)
{
    int nc;

    for(nc=0;nc<dvddem[0].numcol;nc++) dvddem[0].c[nc].offset-=(int)&svddem;

    vdselcreademandarecarga=abrecursor(SELCREADEMANDARECARGA);
    definetodo(vdselcreademandarecarga,NULL);
    bindtodo(vdselcreademandarecarga,"CODUBI",svddem.codubi,sizeof(svddem.codubi),V10CADENA,
             "UNIAGRUPA",svddem.uniagrupa,sizeof(svddem.uniagrupa),V10CADENA,
             "CANTIDAD",&svddem.cantidad,sizeof(svddem.cantidad),V10DOUBLE,
             "TIPOREDONDEO",svddem.tiporedondeo,sizeof(svddem.tiporedondeo),V10CADENA,
             "CODART",svddem.codart,sizeof(svddem.codart),V10CADENA,
             "TIPODEMANDA",svddem.tipodemanda,sizeof(svddem.tipodemanda),V10CADENA,
             "STATUS",&svddem.status,sizeof(svddem.status),V10LONG,
             "LINEASINSERTADAS",&svddem.lineasinsertadas,sizeof(svddem.lineasinsertadas),V10LONG,
             "CODDEMANDA",svddem.coddemanda,sizeof(svddem.coddemanda),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_DEM);
        init = 1;
    }
}

static void init_sellistacodcomen(void)
{
    int nc;

    for(nc=0;nc<dvddem[0].numcol;nc++) dvddem[0].c[nc].offset-=(int)&svddem;

    vdsellistacodcomen=abrecursor(SELLISTACODCOMEN);
    definetodo(vdsellistacodcomen,svddem.vdextra,sizeof(svddem.vdextra),V10CADENA,
               NULL);
    bindtodo(vdsellistacodcomen,"CODDEMANDA",svddem.coddemanda,sizeof(svddem.coddemanda),V10CADENA,
             "TIPODEMANDA",svddem.tipodemanda,sizeof(svddem.tipodemanda),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_DEM);
        init = 1;
    }
}

diccionario *DEMdamediccionario(void)
{
    return(&ddem);
}

int DEMbuscademlanulable(char *coddemanda,char *tipodemanda,long lindemanda,vddems *dem)
{
    int vdret;
    if (vdseldemlanulable==NULL) init_seldemlanulable();
    memset(&svddem,0,sizeof(svddem));
    strcpy(svddem.coddemanda,coddemanda);
    strcpy(svddem.tipodemanda,tipodemanda);
    svddem.lindemanda=lindemanda;
    vdret=ejefetchcursor(vdseldemlanulable);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch DEMbuscademlanulable vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *dem=svddem;
    return(vdret);
}

int DEMnextdemlanulable(vddems *dem)
{
    int vdret;
    vdret=fetchcursor(vdseldemlanulable);
    if (!vdret) {
        *dem=svddem;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldemlanulable);
    return(VD_EERRORACLE);
}

int DEMbuscademcanulable(char *coddemanda,char *tipodemanda,vddems *dem)
{
    int vdret;
    if (vdseldemcanulable==NULL) init_seldemcanulable();
    memset(&svddem,0,sizeof(svddem));
    strcpy(svddem.coddemanda,coddemanda);
    strcpy(svddem.tipodemanda,tipodemanda);
    vdret=ejefetchcursor(vdseldemcanulable);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch DEMbuscademcanulable vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *dem=svddem;
    return(vdret);
}

int DEMnextdemcanulable(vddems *dem)
{
    int vdret;
    vdret=fetchcursor(vdseldemcanulable);
    if (!vdret) {
        *dem=svddem;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldemcanulable);
    return(VD_EERRORACLE);
}

int DEMprocanulademl(char *coddemanda,char *tipodemanda,long lindemanda,long ret,vddems *dem)
{
    int vdret;
    if (vdselanulademl==NULL) init_selanulademl();
    memset(&svddem,0,sizeof(svddem));
    strcpy(svddem.coddemanda,coddemanda);
    strcpy(svddem.tipodemanda,tipodemanda);
    svddem.lindemanda=lindemanda;
    svddem.ret=ret;
    vdret=ejecutacursor(vdselanulademl);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta DEMprocanulademl vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *dem=svddem;
    return(vdret);
}

int DEMprocanulademc(char *coddemanda,char *tipodemanda,long ret,vddems *dem)
{
    int vdret;
    if (vdselanulademc==NULL) init_selanulademc();
    memset(&svddem,0,sizeof(svddem));
    strcpy(svddem.coddemanda,coddemanda);
    strcpy(svddem.tipodemanda,tipodemanda);
    svddem.ret=ret;
    vdret=ejecutacursor(vdselanulademc);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta DEMprocanulademc vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *dem=svddem;
    return(vdret);
}

int DEMprocfinalizademl(char *coddemanda,char *tipodemanda,long lindemanda,long statusini,long stdemlfinal,long stdemcfinal,char *reabrirdeml,long stdemlreabrir,long stdemcreabrir,long ret,vddems *dem)
{
    int vdret;
    if (vdselfinalizademl==NULL) init_selfinalizademl();
    memset(&svddem,0,sizeof(svddem));
    strcpy(svddem.coddemanda,coddemanda);
    strcpy(svddem.tipodemanda,tipodemanda);
    svddem.lindemanda=lindemanda;
    svddem.statusini=statusini;
    svddem.stdemlfinal=stdemlfinal;
    svddem.stdemcfinal=stdemcfinal;
    strcpy(svddem.reabrirdeml,reabrirdeml);
    svddem.stdemlreabrir=stdemlreabrir;
    svddem.stdemcreabrir=stdemcreabrir;
    svddem.ret=ret;
    vdret=ejecutacursor(vdselfinalizademl);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta DEMprocfinalizademl vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *dem=svddem;
    return(vdret);
}

int DEMproccreademandapedido(char *coddiv,long anoped,char *codped,long seqped,char *backorder,char *tipodemanda,long status,char *codubi,char *agrupalineas,long lineasinsertadas,char *coddemanda,vddems *dem)
{
    int vdret;
    if (vdselcreademandapedido==NULL) init_selcreademandapedido();
    memset(&svddem,0,sizeof(svddem));
    strcpy(svddem.coddiv,coddiv);
    svddem.anoped=anoped;
    strcpy(svddem.codped,codped);
    svddem.seqped=seqped;
    strcpy(svddem.backorder,backorder);
    strcpy(svddem.tipodemanda,tipodemanda);
    svddem.status=status;
    strcpy(svddem.codubi,codubi);
    strcpy(svddem.agrupalineas,agrupalineas);
    svddem.lineasinsertadas=lineasinsertadas;
    strcpy(svddem.coddemanda,coddemanda);
    vdret=ejecutacursor(vdselcreademandapedido);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta DEMproccreademandapedido vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *dem=svddem;
    return(vdret);
}

int DEMproccreademandarecarga(char *codubi,char *uniagrupa,double cantidad,char *tiporedondeo,char *codart,char *tipodemanda,long status,long lineasinsertadas,char *coddemanda,vddems *dem)
{
    int vdret;
    if (vdselcreademandarecarga==NULL) init_selcreademandarecarga();
    memset(&svddem,0,sizeof(svddem));
    strcpy(svddem.codubi,codubi);
    strcpy(svddem.uniagrupa,uniagrupa);
    svddem.cantidad=cantidad;
    strcpy(svddem.tiporedondeo,tiporedondeo);
    strcpy(svddem.codart,codart);
    strcpy(svddem.tipodemanda,tipodemanda);
    svddem.status=status;
    svddem.lineasinsertadas=lineasinsertadas;
    strcpy(svddem.coddemanda,coddemanda);
    vdret=ejecutacursor(vdselcreademandarecarga);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta DEMproccreademandarecarga vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *dem=svddem;
    return(vdret);
}

int DEMbuscalistacodcomen(char *coddemanda,char *tipodemanda,vddems *dem)
{
    int vdret;
    if (vdsellistacodcomen==NULL) init_sellistacodcomen();
    memset(&svddem,0,sizeof(svddem));
    strcpy(svddem.coddemanda,coddemanda);
    strcpy(svddem.tipodemanda,tipodemanda);
    vdret=ejefetchcursor(vdsellistacodcomen);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch DEMbuscalistacodcomen vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *dem=svddem;
    return(vdret);
}

int DEMnextlistacodcomen(vddems *dem)
{
    int vdret;
    vdret=fetchcursor(vdsellistacodcomen);
    if (!vdret) {
        *dem=svddem;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdsellistacodcomen);
    return(VD_EERRORACLE);
}

char * DEMdebug(vddems *dem)
{
    debugestruct(&ddem,dem,msgdebugdem);
    return(msgdebugdem);
}


//Codigo incluido explicitamente en el DEF

VDEXPORT int finalizademl(vddemandalins *deml, long statusini,long stdemlfinal, long stdemcfinal, char *reabrir, long stdemlreabrir, long stdemcreabrir) {
	int ret,miret;
	vddems dem;
	
	miret=0;
	ret=DEMprocfinalizademl(deml->coddemanda,deml->tipodemanda,deml->lindemanda,statusini,stdemlfinal,stdemcfinal,reabrir,stdemlreabrir,stdemcreabrir,miret,&dem);
	if (ret) {
		v10log(LOGERROR,"finalizademl: Error al ejecutar PLSQL DEMprocfinalizademl\n");
		return(ret);
	} else {
		return(dem.ret);
	}
}


VDEXPORT int creademandapedido(vdpedidocabs *pec,char *tipodemanda,long status,char *codubiexped,char *backorder,char *agrupalineas,char *coddemanda) {
	int ret;
	long lineasinsertadas=0;
	vddems dem;
 
	ret=DEMproccreademandapedido(pec->coddiv,pec->anoped,pec->codped,pec->seqped,backorder,tipodemanda,status,codubiexped,agrupalineas,lineasinsertadas,coddemanda,&dem);
	if (ret) {
		v10log(LOGERROR,"creademandapedido: Error al ejecutar PLSQL DEMproccreademandapedido\n");
		return(ret);
	} else {
		if (*dem.coddemanda==0) {
			v10log(LOGERROR,"creademandapedido: No se ha podido generar demanda del tipo %s para pedido. %s\n",
						    tipodemanda, PEClog(pec));
			return(-1);
		} 
	}
 
	strcopia(coddemanda,dem.coddemanda,strlen(dem.coddemanda));
	v10log(LOGNORMAL,"creademandapedido: generadas %ld lineas de demandas en demanda %s %s\n",dem.lineasinsertadas,tipodemanda,dem.coddemanda);
	return(0);
}

VDEXPORT int creademandarecarga(vdrecargas *rec,char *tipodemanda,long status,char *coddemanda) {
	int ret;
	long lineasinsertadas=0;
	vddems dem;
 
	ret=DEMproccreademandarecarga(rec->codubi, rec->uniagrupademl, rec->cantidad, rec->tiporedondeo,rec->codart, tipodemanda,status,lineasinsertadas,coddemanda,&dem);
	if (ret) {
		v10log(LOGERROR,"creademandarecarga: Error al ejecutar PLSQL DEMproccreademandarecarga\n");
		return(ret);
	} else {
		if (*dem.coddemanda==0) {
			v10log(LOGERROR,"creademandarecarga: No se ha podido generar demanda del tipo %s para recarga de ubicación %s\n",
						    tipodemanda, rec->codubi);
			return(-1);
		} 
	} 
	strcopia(coddemanda,dem.coddemanda,strlen(dem.coddemanda));
	v10log(LOGNORMAL,"creademandarecarga: generadas %ld lineas de demandas en demanda %s %s\n",dem.lineasinsertadas,tipodemanda,dem.coddemanda);
	return(0);
}

VDEXPORT int anulademl(vddemandalins *deml) {
	int ret,miret;
	vddems dem;
	
	miret=0;
	ret=DEMprocanulademl(deml->coddemanda,deml->tipodemanda,deml->lindemanda,miret,&dem);
	if (ret) {
		v10log(LOGERROR,"anulademl: Error al ejecutar PLSQL DEMprocanulademl\n");
		return(ret);
	} else {
		return(dem.ret);
	}
}

VDEXPORT int anulademc(vddemandacabs *demc) {
	int ret,miret;
	vddems dem;
	
	miret=0;
	ret=DEMprocanulademc(demc->coddemanda,demc->tipodemanda,miret,&dem);
	if (ret) {
		v10log(LOGERROR,"anulademc: Error al ejecutar PLSQL DEMprocanulademc\n");
		return(ret);
	} else {
		return(dem.ret);
	}
}

