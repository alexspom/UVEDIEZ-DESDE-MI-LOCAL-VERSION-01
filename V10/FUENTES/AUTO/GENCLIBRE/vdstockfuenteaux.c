// Modulo generado automaticamente a partir de VDSTOCKFUENTEAUX.DEF
//#***
//# VDSTOCKFUENTEAUX.DEF - Generación automática del código c SOLOQUERY sobre la tabla VDSOTCKFUENTE                                                    
//# 
//# Propósito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 17-07-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=STKFTEAUX;
//EXTRA=RET,V10LONG
//EXTRA=CREARCONTE,V10CADENA,2
//EXTRA=CREARLOTE,V10CADENA,2
// 
//PROCEDURE=FUENTESTK, BEGIN
//                         VDSTK.FUENTESTK( :VDSTOCKFUENTE.TIPOFUENTE,:VDSTOCKFUENTE.CODUBI,:VDSTOCKFUENTE.CODMAT,
//                                          :VDSTOCKFUENTE.TIPOCONTE ,:VDSTOCKFUENTE.CODART ,:VDSTOCKFUENTE.CODLOT ,
//                                          :VDSTOCKFUENTE.CANTIDADHOST ,:VDSTOCKFUENTE.UNIDADESHOST ,:VDSTOCKFUENTE.UNIEMBHOST ,
//                                          :VDSTOCKFUENTE.EMBCONT ,:VDSTOCKFUENTE.TIPOEMBA ,:VDSTOCKFUENTE.PRECIOUNI,
//                                          :VDSTOCKFUENTE.BLOQUEOS, :VDSTOCKFUENTE.BULTO, :VDSTOCKFUENTE.MARCASTK, 
//                                          :VDSTOCKFUENTE.NUMEROSERIE,:VDSTOCKFUENTE.CODRECEP ,:VDSTOCKFUENTE.PESOUNI,
//                                          :VDLOTES.CODLOTPROV, :VDLOTES.CADUCI, :VDLOTES.RETEST, :VDLOTES.BLOQLOTE,
//                                          :VDLOTES.POTENCIA, :VDLOTES.SWTPRECIO, :VDLOTES.MUESTREADO, :VDSTOCKFUENTE.VDEXTRA, :VDCOMEN.COMENTARIO, :RET);
//                     END;@
// 
// PROCEDURE=CREASTK, BEGIN
//                         VDSTK.CREASTK( :VDSTOCKFUENTE.SEQFUENTE,:VDCONCEPTO.CODCONCE,:VDUBICA.CODUBI,:CREARCONTE,:CREARLOTE,
//                                        :VDSTOCKFUENTE.VDEXTRA,:VDCOMEN.COMENTARIO,:VDMOVIM.CODMOV,:RET);
//                     END;@                                        

#include "vd.h"\

#define SELFUENTESTK " BEGIN VDSTK.FUENTESTK( :TIPOFUENTE,:CODUBI,:CODMAT, :TIPOCONTE ,:CODART ,:CODLOT , :CANTIDADHOST ,:UNIDADESHOST ,:UNIEMBHOST , :EMBCONT ,:TIPOEMBA ,:PRECIOUNI, :BLOQUEOS, :BULTO, :MARCASTK,  :NUMEROSERIE,:CODRECEP ,:PESOUNI, :CODLOTPROV, :CADUCI, :RETEST, :BLOQLOTE, :POTENCIA, :SWTPRECIO, :MUESTREADO, :VDEXTRA, :COMENTARIO, :RET); END;"
static v10cursors *vdselfuentestk;
#define SELCREASTK " BEGIN VDSTK.CREASTK( :SEQFUENTE,:CODCONCE,:CODUBI,:CREARCONTE,:CREARLOTE, :VDEXTRA,:COMENTARIO,:CODMOV,:RET); END;"
static v10cursors *vdselcreastk;

static vdstkfteauxs svdstkfteaux;

static diccols colvdstkfteaux[]={ 
    {"RET",V10LONG,(size_t)&svdstkfteaux.ret,sizeof(svdstkfteaux.ret)},
    {"CREARCONTE",V10CADENA,(size_t)&svdstkfteaux.crearconte,sizeof(svdstkfteaux.crearconte)},
    {"CREARLOTE",V10CADENA,(size_t)&svdstkfteaux.crearlote,sizeof(svdstkfteaux.crearlote)},
    {"TIPOFUENTE",V10CADENA,(size_t)&svdstkfteaux.tipofuente,sizeof(svdstkfteaux.tipofuente)},
    {"CODUBI",V10CADENA,(size_t)&svdstkfteaux.codubi,sizeof(svdstkfteaux.codubi)},
    {"CODMAT",V10CADENA,(size_t)&svdstkfteaux.codmat,sizeof(svdstkfteaux.codmat)},
    {"TIPOCONTE",V10CADENA,(size_t)&svdstkfteaux.tipoconte,sizeof(svdstkfteaux.tipoconte)},
    {"CODART",V10CADENA,(size_t)&svdstkfteaux.codart,sizeof(svdstkfteaux.codart)},
    {"CODLOT",V10CADENA,(size_t)&svdstkfteaux.codlot,sizeof(svdstkfteaux.codlot)},
    {"CANTIDADHOST",V10DOUBLE,(size_t)&svdstkfteaux.cantidadhost,sizeof(svdstkfteaux.cantidadhost)},
    {"UNIDADESHOST",V10CADENA,(size_t)&svdstkfteaux.unidadeshost,sizeof(svdstkfteaux.unidadeshost)},
    {"UNIEMBHOST",V10DOUBLE,(size_t)&svdstkfteaux.uniembhost,sizeof(svdstkfteaux.uniembhost)},
    {"EMBCONT",V10LONG,(size_t)&svdstkfteaux.embcont,sizeof(svdstkfteaux.embcont)},
    {"TIPOEMBA",V10CADENA,(size_t)&svdstkfteaux.tipoemba,sizeof(svdstkfteaux.tipoemba)},
    {"PRECIOUNI",V10DOUBLE,(size_t)&svdstkfteaux.preciouni,sizeof(svdstkfteaux.preciouni)},
    {"BLOQUEOS",V10CADENA,(size_t)&svdstkfteaux.bloqueos,sizeof(svdstkfteaux.bloqueos)},
    {"BULTO",V10CADENA,(size_t)&svdstkfteaux.bulto,sizeof(svdstkfteaux.bulto)},
    {"MARCASTK",V10CADENA,(size_t)&svdstkfteaux.marcastk,sizeof(svdstkfteaux.marcastk)},
    {"NUMEROSERIE",V10CADENA,(size_t)&svdstkfteaux.numeroserie,sizeof(svdstkfteaux.numeroserie)},
    {"CODRECEP",V10CADENA,(size_t)&svdstkfteaux.codrecep,sizeof(svdstkfteaux.codrecep)},
    {"PESOUNI",V10DOUBLE,(size_t)&svdstkfteaux.pesouni,sizeof(svdstkfteaux.pesouni)},
    {"CODLOTPROV",V10CADENA,(size_t)&svdstkfteaux.codlotprov,sizeof(svdstkfteaux.codlotprov)},
    {"CADUCI",V10CADENA,(size_t)&svdstkfteaux.caduci,sizeof(svdstkfteaux.caduci)},
    {"RETEST",V10CADENA,(size_t)&svdstkfteaux.retest,sizeof(svdstkfteaux.retest)},
    {"BLOQLOTE",V10CADENA,(size_t)&svdstkfteaux.bloqlote,sizeof(svdstkfteaux.bloqlote)},
    {"POTENCIA",V10DOUBLE,(size_t)&svdstkfteaux.potencia,sizeof(svdstkfteaux.potencia)},
    {"SWTPRECIO",V10CADENA,(size_t)&svdstkfteaux.swtprecio,sizeof(svdstkfteaux.swtprecio)},
    {"MUESTREADO",V10CADENA,(size_t)&svdstkfteaux.muestreado,sizeof(svdstkfteaux.muestreado)},
    {"VDEXTRA",V10CADENA,(size_t)&svdstkfteaux.vdextra,sizeof(svdstkfteaux.vdextra)},
    {"COMENTARIO",V10CADENA,(size_t)&svdstkfteaux.comentario,sizeof(svdstkfteaux.comentario)},
    {"SEQFUENTE",V10LONG,(size_t)&svdstkfteaux.seqfuente,sizeof(svdstkfteaux.seqfuente)},
    {"CODCONCE",V10CADENA,(size_t)&svdstkfteaux.codconce,sizeof(svdstkfteaux.codconce)},
    {"CODMOV",V10LONG,(size_t)&svdstkfteaux.codmov,sizeof(svdstkfteaux.codmov)}
    };

static diccionarios dvdstkfteaux[]={
    {colvdstkfteaux,33}
    };

diccionario dstkfteaux={dvdstkfteaux,1};

static char msgdebugstkfteaux[LCADENABIG];

static int init=0;


static void fin_vd_STKFTEAUX(void)
{
    if(vdselfuentestk){
        liberacursor(vdselfuentestk);
        vdselfuentestk=NULL;
    }
    if(vdselcreastk){
        liberacursor(vdselcreastk);
        vdselcreastk=NULL;
    }
}


static void init_selfuentestk(void)
{
    int nc;

    for(nc=0;nc<dvdstkfteaux[0].numcol;nc++) dvdstkfteaux[0].c[nc].offset-=(size_t)&svdstkfteaux;

    vdselfuentestk=abrecursor(SELFUENTESTK);
    definetodo(vdselfuentestk,NULL);
    bindtodo(vdselfuentestk,"TIPOFUENTE",svdstkfteaux.tipofuente,sizeof(svdstkfteaux.tipofuente),V10CADENA,
             "CODUBI",svdstkfteaux.codubi,sizeof(svdstkfteaux.codubi),V10CADENA,
             "CODMAT",svdstkfteaux.codmat,sizeof(svdstkfteaux.codmat),V10CADENA,
             "TIPOCONTE",svdstkfteaux.tipoconte,sizeof(svdstkfteaux.tipoconte),V10CADENA,
             "CODART",svdstkfteaux.codart,sizeof(svdstkfteaux.codart),V10CADENA,
             "CODLOT",svdstkfteaux.codlot,sizeof(svdstkfteaux.codlot),V10CADENA,
             "CANTIDADHOST",&svdstkfteaux.cantidadhost,sizeof(svdstkfteaux.cantidadhost),V10DOUBLE,
             "UNIDADESHOST",svdstkfteaux.unidadeshost,sizeof(svdstkfteaux.unidadeshost),V10CADENA,
             "UNIEMBHOST",&svdstkfteaux.uniembhost,sizeof(svdstkfteaux.uniembhost),V10DOUBLE,
             "EMBCONT",&svdstkfteaux.embcont,sizeof(svdstkfteaux.embcont),V10LONG,
             "TIPOEMBA",svdstkfteaux.tipoemba,sizeof(svdstkfteaux.tipoemba),V10CADENA,
             "PRECIOUNI",&svdstkfteaux.preciouni,sizeof(svdstkfteaux.preciouni),V10DOUBLE,
             "BLOQUEOS",svdstkfteaux.bloqueos,sizeof(svdstkfteaux.bloqueos),V10CADENA,
             "BULTO",svdstkfteaux.bulto,sizeof(svdstkfteaux.bulto),V10CADENA,
             "MARCASTK",svdstkfteaux.marcastk,sizeof(svdstkfteaux.marcastk),V10CADENA,
             "NUMEROSERIE",svdstkfteaux.numeroserie,sizeof(svdstkfteaux.numeroserie),V10CADENA,
             "CODRECEP",svdstkfteaux.codrecep,sizeof(svdstkfteaux.codrecep),V10CADENA,
             "PESOUNI",&svdstkfteaux.pesouni,sizeof(svdstkfteaux.pesouni),V10DOUBLE,
             "CODLOTPROV",svdstkfteaux.codlotprov,sizeof(svdstkfteaux.codlotprov),V10CADENA,
             "CADUCI",svdstkfteaux.caduci,sizeof(svdstkfteaux.caduci),V10CADENA,
             "RETEST",svdstkfteaux.retest,sizeof(svdstkfteaux.retest),V10CADENA,
             "BLOQLOTE",svdstkfteaux.bloqlote,sizeof(svdstkfteaux.bloqlote),V10CADENA,
             "POTENCIA",&svdstkfteaux.potencia,sizeof(svdstkfteaux.potencia),V10DOUBLE,
             "SWTPRECIO",svdstkfteaux.swtprecio,sizeof(svdstkfteaux.swtprecio),V10CADENA,
             "MUESTREADO",svdstkfteaux.muestreado,sizeof(svdstkfteaux.muestreado),V10CADENA,
             "VDEXTRA",svdstkfteaux.vdextra,sizeof(svdstkfteaux.vdextra),V10CADENA,
             "COMENTARIO",svdstkfteaux.comentario,sizeof(svdstkfteaux.comentario),V10CADENA,
             "RET",&svdstkfteaux.ret,sizeof(svdstkfteaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKFTEAUX);
        init = 1;
    }
}

static void init_selcreastk(void)
{
    int nc;

    for(nc=0;nc<dvdstkfteaux[0].numcol;nc++) dvdstkfteaux[0].c[nc].offset-=(size_t)&svdstkfteaux;

    vdselcreastk=abrecursor(SELCREASTK);
    definetodo(vdselcreastk,NULL);
    bindtodo(vdselcreastk,"SEQFUENTE",&svdstkfteaux.seqfuente,sizeof(svdstkfteaux.seqfuente),V10LONG,
             "CODCONCE",svdstkfteaux.codconce,sizeof(svdstkfteaux.codconce),V10CADENA,
             "CODUBI",svdstkfteaux.codubi,sizeof(svdstkfteaux.codubi),V10CADENA,
             "CREARCONTE",svdstkfteaux.crearconte,sizeof(svdstkfteaux.crearconte),V10CADENA,
             "CREARLOTE",svdstkfteaux.crearlote,sizeof(svdstkfteaux.crearlote),V10CADENA,
             "VDEXTRA",svdstkfteaux.vdextra,sizeof(svdstkfteaux.vdextra),V10CADENA,
             "COMENTARIO",svdstkfteaux.comentario,sizeof(svdstkfteaux.comentario),V10CADENA,
             "CODMOV",&svdstkfteaux.codmov,sizeof(svdstkfteaux.codmov),V10LONG,
             "RET",&svdstkfteaux.ret,sizeof(svdstkfteaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKFTEAUX);
        init = 1;
    }
}

diccionario *STKFTEAUXdamediccionario(void)
{
    return(&dstkfteaux);
}

int STKFTEAUXprocfuentestk(char *tipofuente,char *codubi,char *codmat,char *tipoconte,char *codart,char *codlot,double cantidadhost,char *unidadeshost,double uniembhost,long embcont,char *tipoemba,double preciouni,char *bloqueos,char *bulto,char *marcastk,char *numeroserie,char *codrecep,double pesouni,char *codlotprov,char *caduci,char *retest,char *bloqlote,double potencia,char *swtprecio,char *muestreado,char *vdextra,char *comentario,long ret,vdstkfteauxs *stkfteaux)
{
    int vdret;
    if (vdselfuentestk==NULL) init_selfuentestk();
    memset(&svdstkfteaux,0,sizeof(svdstkfteaux));
    strcpy(svdstkfteaux.tipofuente,tipofuente);
    strcpy(svdstkfteaux.codubi,codubi);
    strcpy(svdstkfteaux.codmat,codmat);
    strcpy(svdstkfteaux.tipoconte,tipoconte);
    strcpy(svdstkfteaux.codart,codart);
    strcpy(svdstkfteaux.codlot,codlot);
    svdstkfteaux.cantidadhost=cantidadhost;
    strcpy(svdstkfteaux.unidadeshost,unidadeshost);
    svdstkfteaux.uniembhost=uniembhost;
    svdstkfteaux.embcont=embcont;
    strcpy(svdstkfteaux.tipoemba,tipoemba);
    svdstkfteaux.preciouni=preciouni;
    strcpy(svdstkfteaux.bloqueos,bloqueos);
    strcpy(svdstkfteaux.bulto,bulto);
    strcpy(svdstkfteaux.marcastk,marcastk);
    strcpy(svdstkfteaux.numeroserie,numeroserie);
    strcpy(svdstkfteaux.codrecep,codrecep);
    svdstkfteaux.pesouni=pesouni;
    strcpy(svdstkfteaux.codlotprov,codlotprov);
    strcpy(svdstkfteaux.caduci,caduci);
    strcpy(svdstkfteaux.retest,retest);
    strcpy(svdstkfteaux.bloqlote,bloqlote);
    svdstkfteaux.potencia=potencia;
    strcpy(svdstkfteaux.swtprecio,swtprecio);
    strcpy(svdstkfteaux.muestreado,muestreado);
    strcpy(svdstkfteaux.vdextra,vdextra);
    strcpy(svdstkfteaux.comentario,comentario);
    svdstkfteaux.ret=ret;
    vdret=ejecutacursor(vdselfuentestk);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKFTEAUXprocfuentestk vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkfteaux=svdstkfteaux;
    return(vdret);
}

int STKFTEAUXproccreastk(long seqfuente,char *codconce,char *codubi,char *crearconte,char *crearlote,char *vdextra,char *comentario,long codmov,long ret,vdstkfteauxs *stkfteaux)
{
    int vdret;
    if (vdselcreastk==NULL) init_selcreastk();
    memset(&svdstkfteaux,0,sizeof(svdstkfteaux));
    svdstkfteaux.seqfuente=seqfuente;
    strcpy(svdstkfteaux.codconce,codconce);
    strcpy(svdstkfteaux.codubi,codubi);
    strcpy(svdstkfteaux.crearconte,crearconte);
    strcpy(svdstkfteaux.crearlote,crearlote);
    strcpy(svdstkfteaux.vdextra,vdextra);
    strcpy(svdstkfteaux.comentario,comentario);
    svdstkfteaux.codmov=codmov;
    svdstkfteaux.ret=ret;
    vdret=ejecutacursor(vdselcreastk);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKFTEAUXproccreastk vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkfteaux=svdstkfteaux;
    return(vdret);
}

char * STKFTEAUXdebug(vdstkfteauxs *stkfteaux)
{
    debugestruct(&dstkfteaux,stkfteaux,msgdebugstkfteaux);
    return(msgdebugstkfteaux);
}

