// Modulo generado automaticamente a partir de VDRUTAS.DEF
//#***
//# RUTAS.DEF - Generación automática del código c SOLOQUERY para enrutador                                                    
//# 
//# Propósito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 8-11-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=RUTAS;
//
//EXTRA=VDTRAMOS.CODAREAORI;
//EXTRA=CANTIDADTOTAL,V10DOUBLE;
//#EXTRA=RESERVADA,V10DOUBLE;
//EXTRA=TRAMOFINAL,V10CADENA,2;
//
//CURSOR=STKDISPONIBLE, SELECT  NVL(SUM(STK.CANTIDAD),0) CANTIDADTOTAL 
//                        FROM VDMOVIM MOV, 
//                       (SELECT * FROM TABLE (VDFOTOSTK.STKCONTE(:VDCONTE.CODMAT))) STK
//                       WHERE
//                           MOV.CODMOV = :VDMOVIM.CODMOV AND
//                           STK.CODART   = MOV.CODART AND 
//                           STK.UNIEMB   = MOV.UNIEMB AND                          
//                           (STK.CODLOT||'' = MOV.CODLOT OR MOV.CODLOT IS NULL) AND
//                           (STK.BLOQUEOS||'' = MOV.BLOQUEOSORI OR MOV.BLOQUEOSORI IS NULL) AND
//                           (STK.NUMEROSERIE||'' = MOV.NUMEROSERIE OR MOV.NUMEROSERIE IS NULL) AND
//                           NVL(STK.MARCASTK,'-') = NVL(MOV.MARCASTK,'-');
//                           
//CURSOR=CONTESFLUJOS, SELECT CNT.CODMAT , CNT.CODUBI                         
//                        FROM  VDSTOCK STK, VDFLUJOPARAM FLP, VDCONTE CNT, VDUBICA UBI, VDMOVIM MOV
//                        WHERE UBI.BLOQUEOSS='N' AND 
//                          MOV.CODMOV   = :VDMOVIM.CODMOV    AND 
//                          FLP.CODFLUJO = :VDFLUJOPARAM.CODFLUJO  AND 
//                          UBI.CODAREA || ''  = :VDUBICA.CODAREA   AND
//                          CNT.CODUBI   = UBI.CODUBI AND
//                          STK.CODMAT   = CNT.CODMAT AND
//                          STK.CODART   = MOV.CODART AND 
//                          STK.UNIEMB   = MOV.UNIEMB AND                          
//                          (STK.CODLOT = MOV.CODLOT OR MOV.CODLOT IS NULL) AND
//                          VDSTK.ESTADOCOMPATIBLE(STK.BLOQUEOS, FLP.PATRONESTADO)=0 AND
//                          CNT.TIPOCONTE <> 'TMP' AND  
//                          UBI.TIPOUBI <> 'V' AND
//                          VDSTK.CNTDISPONIBLE(CNT.CODMAT, 'U',MOV.CODART, MOV.CODLOT,MOV.UNIEMB,MOV.BLOQUEOSORI, MOV.TIPOEMBA, MOV.CODRECEP, MOV.PRECIOUNI, MOV.MARCASTK, MOV.BULTO, MOV.NUMEROSERIE ) > 0
//	              GROUP BY CNT.CODMAT, CNT.CODUBI;
//
//CURSOR=STKAREAPICKING,SELECT UBI.CODUBI, CNT.CODMAT, STK.CODART, STK.CODLOT, STK.UNIEMB, STK.BLOQUEOS, SUM(CANTIDAD) CANTIDADTOTAL                         
//                        FROM  VDSTOCK STK, VDFLUJOPARAM FLP, VDCONTE CNT, VDUBICA UBI 
//                        WHERE 
//                          UBI.CODAREA = :VDUBICA.CODAREA   AND 
//                          UBI.CODUBI  = CNT.CODUBI AND
//                          CNT.CODMAT  = STK.CODMAT AND
//                          STK.CODART  = :VDSTOCK.CODART AND 
//                          STK.UNIEMB  = :VDSTOCK.UNIEMB AND
//                          FLP.CODFLUJO = :VDFLUJOPARAM.CODFLUJO AND 
//                          (STK.CODLOT = :VDSTOCK.CODLOT OR :VDSTOCK.CODLOT IS NULL) AND
//                          VDSTK.ESTADOCOMPATIBLE(STK.BLOQUEOS, FLP.PATRONESTADO)=0
//                        GROUP BY UBI.CODUBI, CNT.CODMAT, STK.CODART, STK.CODLOT, STK.UNIEMB, STK.BLOQUEOS;
//                        
//
//
//CURSOR=SGTETRAMO,SELECT * FROM TABLE(VDFLP.DAMETRAMOSMOV(:VDMOVIM.CODMOV)) WHERE VALIDEZ='VALIDO';
//
//
//CURSOR=AREASPICKING,SELECT CODAREAORI FROM 
//                      (SELECT TRM.CODAREAORI,TRM.CODAREADEST FROM VDTRAMOS TRM WHERE CODCAMINO=:VDTRAMOS.CODCAMINO AND BLOQUEADO='N') 
//	              CONNECT BY PRIOR CODAREADEST=CODAREAORI 
//	              START WITH CODAREAORI=:VDTRAMOS.CODAREAORI; 
//
//
//
//PROCEDURE=ASIGNAFLUJO,BEGIN
//                       VDFLP.ASIGNAFLUJO(:VDMOVIM.CODMOV,:VDMOVIM.STATUS);
//                      END;@    
//
//CURSOR=UBICAPACIDAD,SELECT VDUBI.UBICAPACIDAD(:VDUBICA.CODUBI,:VDUBICA.UNICAPAC) CANTIDAD FROM DUAL; 
//
//
// 
//

#include "vd.h"\

#define SELSTKDISPONIBLE " SELECT  NVL(SUM(STK.CANTIDAD),0) CANTIDADTOTAL  FROM VDMOVIM MOV,  (SELECT * FROM TABLE (VDFOTOSTK.STKCONTE(:CODMAT))) STK WHERE MOV.CODMOV = :CODMOV AND STK.CODART   = MOV.CODART AND  STK.UNIEMB   = MOV.UNIEMB AND                           (STK.CODLOT||'' = MOV.CODLOT OR MOV.CODLOT IS NULL) AND (STK.BLOQUEOS||'' = MOV.BLOQUEOSORI OR MOV.BLOQUEOSORI IS NULL) AND (STK.NUMEROSERIE||'' = MOV.NUMEROSERIE OR MOV.NUMEROSERIE IS NULL) AND NVL(STK.MARCASTK,'-') = NVL(MOV.MARCASTK,'-')"
static v10cursors *vdselstkdisponible;
#define SELCONTESFLUJOS " SELECT CNT.CODMAT , CNT.CODUBI                          FROM  VDSTOCK STK, VDFLUJOPARAM FLP, VDCONTE CNT, VDUBICA UBI, VDMOVIM MOV WHERE  UBI.BLOQUEOSS='N' AND MOV.CODMOV   = :CODMOV    AND  FLP.CODFLUJO = :CODFLUJO  AND  UBI.CODAREA || ''  = :CODAREA   AND CNT.CODUBI   = UBI.CODUBI AND STK.CODMAT   = CNT.CODMAT AND STK.CODART   = MOV.CODART AND  STK.UNIEMB   = MOV.UNIEMB AND                           (STK.CODLOT = MOV.CODLOT OR MOV.CODLOT IS NULL) AND VDSTK.ESTADOCOMPATIBLE(STK.BLOQUEOS, FLP.PATRONESTADO)=0 AND CNT.TIPOCONTE <> 'TMP' AND UBI.TIPOUBI <> 'V' AND                           VDSTK.CNTDISPONIBLE(CNT.CODMAT, 'U',MOV.CODART, MOV.CODLOT,MOV.UNIEMB,MOV.BLOQUEOSORI, MOV.TIPOEMBA, MOV.CODRECEP, MOV.PRECIOUNI, MOV.MARCASTK, MOV.BULTO, MOV.NUMEROSERIE ) > 0 GROUP BY CNT.CODMAT, CNT.CODUBI"
static v10cursors *vdselcontesflujos;
#define SELSTKAREAPICKING "SELECT UBI.CODUBI, CNT.CODMAT, STK.CODART, STK.CODLOT, STK.UNIEMB, STK.BLOQUEOS, SUM(CANTIDAD) CANTIDADTOTAL                          FROM  VDSTOCK STK, VDFLUJOPARAM FLP, VDCONTE CNT, VDUBICA UBI  WHERE  UBI.CODAREA = :CODAREA   AND  UBI.CODUBI  = CNT.CODUBI AND CNT.CODMAT  = STK.CODMAT AND STK.CODART  = :CODART AND  STK.UNIEMB  = :UNIEMB AND FLP.CODFLUJO = :CODFLUJO AND  (STK.CODLOT = :CODLOT OR :CODLOT IS NULL) AND VDSTK.ESTADOCOMPATIBLE(STK.BLOQUEOS, FLP.PATRONESTADO)=0 GROUP BY UBI.CODUBI, CNT.CODMAT, STK.CODART, STK.CODLOT, STK.UNIEMB, STK.BLOQUEOS"
static v10cursors *vdselstkareapicking;
#define SELSGTETRAMO "SELECT * FROM TABLE(VDFLP.DAMETRAMOSMOV(:CODMOV)) WHERE VALIDEZ='VALIDO'"
static v10cursors *vdselsgtetramo;
#define SELAREASPICKING "SELECT CODAREAORI FROM  (SELECT TRM.CODAREAORI,TRM.CODAREADEST FROM VDTRAMOS TRM WHERE CODCAMINO=:CODCAMINO AND BLOQUEADO='N')  CONNECT BY PRIOR CODAREADEST=CODAREAORI  START WITH CODAREAORI=:CODAREAORI"
static v10cursors *vdselareaspicking;
#define SELASIGNAFLUJO "BEGIN VDFLP.ASIGNAFLUJO(:CODMOV,:STATUS); END;"
static v10cursors *vdselasignaflujo;
#define SELUBICAPACIDAD "SELECT VDUBI.UBICAPACIDAD(:CODUBI,:UNICAPAC) CANTIDAD FROM DUAL"
static v10cursors *vdselubicapacidad;

static vdrutass svdrutas;

static diccols colvdrutas[]={ 
    {"CODAREAORI",V10CADENA,(size_t)&svdrutas.codareaori,sizeof(svdrutas.codareaori)},
    {"CANTIDADTOTAL",V10DOUBLE,(size_t)&svdrutas.cantidadtotal,sizeof(svdrutas.cantidadtotal)},
    {"TRAMOFINAL",V10CADENA,(size_t)&svdrutas.tramofinal,sizeof(svdrutas.tramofinal)},
    {"CODMAT",V10CADENA,(size_t)&svdrutas.codmat,sizeof(svdrutas.codmat)},
    {"CODMOV",V10LONG,(size_t)&svdrutas.codmov,sizeof(svdrutas.codmov)},
    {"CODUBI",V10CADENA,(size_t)&svdrutas.codubi,sizeof(svdrutas.codubi)},
    {"CODFLUJO",V10LONG,(size_t)&svdrutas.codflujo,sizeof(svdrutas.codflujo)},
    {"CODAREA",V10CADENA,(size_t)&svdrutas.codarea,sizeof(svdrutas.codarea)},
    {"CODART",V10CADENA,(size_t)&svdrutas.codart,sizeof(svdrutas.codart)},
    {"CODLOT",V10CADENA,(size_t)&svdrutas.codlot,sizeof(svdrutas.codlot)},
    {"UNIEMB",V10DOUBLE,(size_t)&svdrutas.uniemb,sizeof(svdrutas.uniemb)},
    {"BLOQUEOS",V10CADENA,(size_t)&svdrutas.bloqueos,sizeof(svdrutas.bloqueos)},
    {"PRIOTRAMO",V10LONG,(size_t)&svdrutas.priotramo,sizeof(svdrutas.priotramo)},
    {"CODAREADEST",V10CADENA,(size_t)&svdrutas.codareadest,sizeof(svdrutas.codareadest)},
    {"FUERZAPALET",V10CADENA,(size_t)&svdrutas.fuerzapalet,sizeof(svdrutas.fuerzapalet)},
    {"MOVMUEVEPALET",V10CADENA,(size_t)&svdrutas.movmuevepalet,sizeof(svdrutas.movmuevepalet)},
    {"TRMMUEVEPALET",V10CADENA,(size_t)&svdrutas.trmmuevepalet,sizeof(svdrutas.trmmuevepalet)},
    {"TRMMUEVEPARCIAL",V10CADENA,(size_t)&svdrutas.trmmueveparcial,sizeof(svdrutas.trmmueveparcial)},
    {"VALIDEZ",V10CADENA,(size_t)&svdrutas.validez,sizeof(svdrutas.validez)},
    {"COMENTARIO",V10CADENA,(size_t)&svdrutas.comentario,sizeof(svdrutas.comentario)},
    {"CODCAMINO",V10LONG,(size_t)&svdrutas.codcamino,sizeof(svdrutas.codcamino)},
    {"STATUS",V10LONG,(size_t)&svdrutas.status,sizeof(svdrutas.status)},
    {"CANTIDAD",V10LONG,(size_t)&svdrutas.cantidad,sizeof(svdrutas.cantidad)},
    {"UNICAPAC",V10CADENA,(size_t)&svdrutas.unicapac,sizeof(svdrutas.unicapac)}
    };

static diccionarios dvdrutas[]={
    {colvdrutas,24}
    };

diccionario drutas={dvdrutas,1};

static char msgdebugrutas[LCADENABIG];

static int init=0;


static void fin_vd_RUTAS(void)
{
    if(vdselstkdisponible){
        liberacursor(vdselstkdisponible);
        vdselstkdisponible=NULL;
    }
    if(vdselcontesflujos){
        liberacursor(vdselcontesflujos);
        vdselcontesflujos=NULL;
    }
    if(vdselstkareapicking){
        liberacursor(vdselstkareapicking);
        vdselstkareapicking=NULL;
    }
    if(vdselsgtetramo){
        liberacursor(vdselsgtetramo);
        vdselsgtetramo=NULL;
    }
    if(vdselareaspicking){
        liberacursor(vdselareaspicking);
        vdselareaspicking=NULL;
    }
    if(vdselasignaflujo){
        liberacursor(vdselasignaflujo);
        vdselasignaflujo=NULL;
    }
    if(vdselubicapacidad){
        liberacursor(vdselubicapacidad);
        vdselubicapacidad=NULL;
    }
}


static void init_selstkdisponible(void)
{
    int nc;

    for(nc=0;nc<dvdrutas[0].numcol;nc++) dvdrutas[0].c[nc].offset-=(size_t)&svdrutas;

    vdselstkdisponible=abrecursor(SELSTKDISPONIBLE);
    definetodo(vdselstkdisponible,&svdrutas.cantidadtotal,sizeof(svdrutas.cantidadtotal),V10DOUBLE,
               NULL);
    bindtodo(vdselstkdisponible,"CODMAT",svdrutas.codmat,sizeof(svdrutas.codmat),V10CADENA,
             "CODMOV",&svdrutas.codmov,sizeof(svdrutas.codmov),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_RUTAS);
        init = 1;
    }
}

static void init_selcontesflujos(void)
{
    int nc;

    for(nc=0;nc<dvdrutas[0].numcol;nc++) dvdrutas[0].c[nc].offset-=(size_t)&svdrutas;

    vdselcontesflujos=abrecursor(SELCONTESFLUJOS);
    definetodo(vdselcontesflujos,svdrutas.codmat,sizeof(svdrutas.codmat),V10CADENA,
               svdrutas.codubi,sizeof(svdrutas.codubi),V10CADENA,
               NULL);
    bindtodo(vdselcontesflujos,"CODMOV",&svdrutas.codmov,sizeof(svdrutas.codmov),V10LONG,
             "CODFLUJO",&svdrutas.codflujo,sizeof(svdrutas.codflujo),V10LONG,
             "CODAREA",svdrutas.codarea,sizeof(svdrutas.codarea),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_RUTAS);
        init = 1;
    }
}

static void init_selstkareapicking(void)
{
    int nc;

    for(nc=0;nc<dvdrutas[0].numcol;nc++) dvdrutas[0].c[nc].offset-=(size_t)&svdrutas;

    vdselstkareapicking=abrecursor(SELSTKAREAPICKING);
    definetodo(vdselstkareapicking,svdrutas.codubi,sizeof(svdrutas.codubi),V10CADENA,
               svdrutas.codmat,sizeof(svdrutas.codmat),V10CADENA,
               svdrutas.codart,sizeof(svdrutas.codart),V10CADENA,
               svdrutas.codlot,sizeof(svdrutas.codlot),V10CADENA,
               &svdrutas.uniemb,sizeof(svdrutas.uniemb),V10DOUBLE,
               svdrutas.bloqueos,sizeof(svdrutas.bloqueos),V10CADENA,
               &svdrutas.cantidadtotal,sizeof(svdrutas.cantidadtotal),V10DOUBLE,
               NULL);
    bindtodo(vdselstkareapicking,"CODAREA",svdrutas.codarea,sizeof(svdrutas.codarea),V10CADENA,
             "CODART",svdrutas.codart,sizeof(svdrutas.codart),V10CADENA,
             "UNIEMB",&svdrutas.uniemb,sizeof(svdrutas.uniemb),V10DOUBLE,
             "CODFLUJO",&svdrutas.codflujo,sizeof(svdrutas.codflujo),V10LONG,
             "CODLOT",svdrutas.codlot,sizeof(svdrutas.codlot),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_RUTAS);
        init = 1;
    }
}

static void init_selsgtetramo(void)
{
    int nc;

    for(nc=0;nc<dvdrutas[0].numcol;nc++) dvdrutas[0].c[nc].offset-=(size_t)&svdrutas;

    vdselsgtetramo=abrecursor(SELSGTETRAMO);
    definetodo(vdselsgtetramo,&svdrutas.priotramo,sizeof(svdrutas.priotramo),V10LONG,
               svdrutas.codareaori,sizeof(svdrutas.codareaori),V10CADENA,
               svdrutas.codareadest,sizeof(svdrutas.codareadest),V10CADENA,
               svdrutas.fuerzapalet,sizeof(svdrutas.fuerzapalet),V10CADENA,
               svdrutas.tramofinal,sizeof(svdrutas.tramofinal),V10CADENA,
               svdrutas.movmuevepalet,sizeof(svdrutas.movmuevepalet),V10CADENA,
               svdrutas.trmmuevepalet,sizeof(svdrutas.trmmuevepalet),V10CADENA,
               svdrutas.trmmueveparcial,sizeof(svdrutas.trmmueveparcial),V10CADENA,
               svdrutas.validez,sizeof(svdrutas.validez),V10CADENA,
               svdrutas.comentario,sizeof(svdrutas.comentario),V10CADENA,
               NULL);
    bindtodo(vdselsgtetramo,"CODMOV",&svdrutas.codmov,sizeof(svdrutas.codmov),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_RUTAS);
        init = 1;
    }
}

static void init_selareaspicking(void)
{
    int nc;

    for(nc=0;nc<dvdrutas[0].numcol;nc++) dvdrutas[0].c[nc].offset-=(size_t)&svdrutas;

    vdselareaspicking=abrecursor(SELAREASPICKING);
    definetodo(vdselareaspicking,svdrutas.codareaori,sizeof(svdrutas.codareaori),V10CADENA,
               NULL);
    bindtodo(vdselareaspicking,"CODCAMINO",&svdrutas.codcamino,sizeof(svdrutas.codcamino),V10LONG,
             "CODAREAORI",svdrutas.codareaori,sizeof(svdrutas.codareaori),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_RUTAS);
        init = 1;
    }
}

static void init_selasignaflujo(void)
{
    int nc;

    for(nc=0;nc<dvdrutas[0].numcol;nc++) dvdrutas[0].c[nc].offset-=(size_t)&svdrutas;

    vdselasignaflujo=abrecursor(SELASIGNAFLUJO);
    definetodo(vdselasignaflujo,NULL);
    bindtodo(vdselasignaflujo,"CODMOV",&svdrutas.codmov,sizeof(svdrutas.codmov),V10LONG,
             "STATUS",&svdrutas.status,sizeof(svdrutas.status),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_RUTAS);
        init = 1;
    }
}

static void init_selubicapacidad(void)
{
    int nc;

    for(nc=0;nc<dvdrutas[0].numcol;nc++) dvdrutas[0].c[nc].offset-=(size_t)&svdrutas;

    vdselubicapacidad=abrecursor(SELUBICAPACIDAD);
    definetodo(vdselubicapacidad,&svdrutas.cantidad,sizeof(svdrutas.cantidad),V10LONG,
               NULL);
    bindtodo(vdselubicapacidad,"CODUBI",svdrutas.codubi,sizeof(svdrutas.codubi),V10CADENA,
             "UNICAPAC",svdrutas.unicapac,sizeof(svdrutas.unicapac),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_RUTAS);
        init = 1;
    }
}

diccionario *RUTASdamediccionario(void)
{
    return(&drutas);
}

int RUTASbuscastkdisponible(char *codmat,long codmov,vdrutass *rutas)
{
    int vdret;
    if (vdselstkdisponible==NULL) init_selstkdisponible();
    memset(&svdrutas,0,sizeof(svdrutas));
    strcpy(svdrutas.codmat,codmat);
    svdrutas.codmov=codmov;
    vdret=ejefetchcursor(vdselstkdisponible);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch RUTASbuscastkdisponible vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *rutas=svdrutas;
    return(vdret);
}

int RUTASnextstkdisponible(vdrutass *rutas)
{
    int vdret;
    vdret=fetchcursor(vdselstkdisponible);
    if (!vdret) {
        *rutas=svdrutas;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselstkdisponible);
    return(VD_EERRORACLE);
}

int RUTASbuscacontesflujos(long codmov,long codflujo,char *codarea,vdrutass *rutas)
{
    int vdret;
    if (vdselcontesflujos==NULL) init_selcontesflujos();
    memset(&svdrutas,0,sizeof(svdrutas));
    svdrutas.codmov=codmov;
    svdrutas.codflujo=codflujo;
    strcpy(svdrutas.codarea,codarea);
    vdret=ejefetchcursor(vdselcontesflujos);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch RUTASbuscacontesflujos vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *rutas=svdrutas;
    return(vdret);
}

int RUTASnextcontesflujos(vdrutass *rutas)
{
    int vdret;
    vdret=fetchcursor(vdselcontesflujos);
    if (!vdret) {
        *rutas=svdrutas;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselcontesflujos);
    return(VD_EERRORACLE);
}

int RUTASbuscastkareapicking(char *codarea,char *codart,double uniemb,long codflujo,char *codlot,vdrutass *rutas)
{
    int vdret;
    if (vdselstkareapicking==NULL) init_selstkareapicking();
    memset(&svdrutas,0,sizeof(svdrutas));
    strcpy(svdrutas.codarea,codarea);
    strcpy(svdrutas.codart,codart);
    svdrutas.uniemb=uniemb;
    svdrutas.codflujo=codflujo;
    strcpy(svdrutas.codlot,codlot);
    vdret=ejefetchcursor(vdselstkareapicking);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch RUTASbuscastkareapicking vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *rutas=svdrutas;
    return(vdret);
}

int RUTASnextstkareapicking(vdrutass *rutas)
{
    int vdret;
    vdret=fetchcursor(vdselstkareapicking);
    if (!vdret) {
        *rutas=svdrutas;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselstkareapicking);
    return(VD_EERRORACLE);
}

int RUTASbuscasgtetramo(long codmov,vdrutass *rutas)
{
    int vdret;
    if (vdselsgtetramo==NULL) init_selsgtetramo();
    memset(&svdrutas,0,sizeof(svdrutas));
    svdrutas.codmov=codmov;
    vdret=ejefetchcursor(vdselsgtetramo);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch RUTASbuscasgtetramo vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *rutas=svdrutas;
    return(vdret);
}

int RUTASnextsgtetramo(vdrutass *rutas)
{
    int vdret;
    vdret=fetchcursor(vdselsgtetramo);
    if (!vdret) {
        *rutas=svdrutas;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselsgtetramo);
    return(VD_EERRORACLE);
}

int RUTASbuscaareaspicking(long codcamino,char *codareaori,vdrutass *rutas)
{
    int vdret;
    if (vdselareaspicking==NULL) init_selareaspicking();
    memset(&svdrutas,0,sizeof(svdrutas));
    svdrutas.codcamino=codcamino;
    strcpy(svdrutas.codareaori,codareaori);
    vdret=ejefetchcursor(vdselareaspicking);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch RUTASbuscaareaspicking vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *rutas=svdrutas;
    return(vdret);
}

int RUTASnextareaspicking(vdrutass *rutas)
{
    int vdret;
    vdret=fetchcursor(vdselareaspicking);
    if (!vdret) {
        *rutas=svdrutas;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselareaspicking);
    return(VD_EERRORACLE);
}

int RUTASprocasignaflujo(long codmov,long status,vdrutass *rutas)
{
    int vdret;
    if (vdselasignaflujo==NULL) init_selasignaflujo();
    memset(&svdrutas,0,sizeof(svdrutas));
    svdrutas.codmov=codmov;
    svdrutas.status=status;
    vdret=ejecutacursor(vdselasignaflujo);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta RUTASprocasignaflujo vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *rutas=svdrutas;
    return(vdret);
}

int RUTASbuscaubicapacidad(char *codubi,char *unicapac,vdrutass *rutas)
{
    int vdret;
    if (vdselubicapacidad==NULL) init_selubicapacidad();
    memset(&svdrutas,0,sizeof(svdrutas));
    strcpy(svdrutas.codubi,codubi);
    strcpy(svdrutas.unicapac,unicapac);
    vdret=ejefetchcursor(vdselubicapacidad);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch RUTASbuscaubicapacidad vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *rutas=svdrutas;
    return(vdret);
}

int RUTASnextubicapacidad(vdrutass *rutas)
{
    int vdret;
    vdret=fetchcursor(vdselubicapacidad);
    if (!vdret) {
        *rutas=svdrutas;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselubicapacidad);
    return(VD_EERRORACLE);
}

char * RUTASdebug(vdrutass *rutas)
{
    debugestruct(&drutas,rutas,msgdebugrutas);
    return(msgdebugrutas);
}

