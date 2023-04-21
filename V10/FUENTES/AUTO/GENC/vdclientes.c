// Modulo generado automaticamente a partir de VDCLIENTES.DEF
//# M¢dulo : VDCLIENTES.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDCLIENTES
//#                        
//# Autor	 : RIK
//# Revisado por: 
//# Fecha  : 27-09-2011                                              
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=CLI
//
//PRIMARIA=CODCLIENTE,SEQCODCLI
//
//CLAVE=CODCLIENTE,CODCLIENTE,SEQCODCLI
//
//
//INTERFASE
//UPDATE
//INSERT
//DELETE

#include "vd.h"
#define SELCLICODCLIENTE "SELECT VDCLIENTES.ROWID,VDCLIENTES.CODCLIENTE,VDCLIENTES.SEQCODCLI, "\
                    " VDCLIENTES.DESCLIENTE,VDCLIENTES.TIPOCLI,VDCLIENTES.NIF, "\
                    " VDCLIENTES.CONTACTO,VDCLIENTES.TELEFONO,VDCLIENTES.FAX, "\
                    " VDCLIENTES.EMAIL,VDCLIENTES.DIRECCION,VDCLIENTES.DIRECCION1, "\
                    " VDCLIENTES.DIRECCION2,VDCLIENTES.DIRECCION3,VDCLIENTES.POBLACION, "\
                    " VDCLIENTES.DP,VDCLIENTES.CODPROV,VDCLIENTES.CODPAIS, "\
                    " VDCLIENTES.IDIOMAETIQ,VDCLIENTES.IDIOMADOC,VDCLIENTES.TIPOPEDIDO, "\
                    " VDCLIENTES.NUMALBA,VDCLIENTES.BACKORDER,VDCLIENTES.SWTANULAR, "\
                    " VDCLIENTES.SWTVALORADO,VDCLIENTES.SWTTOTALES,VDCLIENTES.SWTPROFORMA, "\
                    " VDCLIENTES.SWTAGRUPAR,VDCLIENTES.SWTPALETIZAR,VDCLIENTES.SWTMODELO, "\
                    " VDCLIENTES.SWTFACTU,VDCLIENTES.REFMODELO,VDCLIENTES.PORTES, "\
                    " VDCLIENTES.SWTSEGURO,VDCLIENTES.SWTEDI,VDCLIENTES.SWTREEMBOLSO, "\
                    " VDCLIENTES.SWTADUANA,VDCLIENTES.PRIORIDAD,VDCLIENTES.URGENCIA, "\
                    " VDCLIENTES.CODAGE,VDCLIENTES.RECARGOAGE,VDCLIENTES.DESCUENTOCAB, "\
                    " VDCLIENTES.DESCUENTOLIN,VDCLIENTES.RECARGOCAB,VDCLIENTES.RECARGOLIN, "\
                    " VDCLIENTES.IVA,VDCLIENTES.CODCLIFACTU,VDCLIENTES.DESCLIFACTU, "\
                    " VDCLIENTES.NIFFACTU,VDCLIENTES.DIRFACTU,VDCLIENTES.DIRFACTU1, "\
                    " VDCLIENTES.DIRFACTU2,VDCLIENTES.DIRFACTU3,VDCLIENTES.POBFACTU, "\
                    " VDCLIENTES.DPFACTU,VDCLIENTES.CODPROVFACTU,VDCLIENTES.CODPAISFACTU, "\
                    " VDCLIENTES.CONTAFACTU,VDCLIENTES.TELFACTU,VDCLIENTES.FAXFACTU, "\
                    " VDCLIENTES.EMAILFACTU,VDCLIENTES.SERIEFACTURA,VDCLIENTES.TIPOFORMAPAGO, "\
                    " VDCLIENTES.OBSERVACIONES,VDCLIENTES.TPCVERIF,VDCLIENTES.CODOPEMODIF, "\
                    " VDCLIENTES.FECMODIF,VDCLIENTES.HORAMODIF,VDCLIENTES.TIPOBASESEGURO, "\
                    " VDCLIENTES.BASESEGURO,VDCLIENTES.SWTBLOQDEV,VDCLIENTES.ACTIVO, "\
                    " VDCLIENTES.SWTBLOQSCAN,VDCLIENTES.ADMITEDEF,VDCLIENTES.CODCOMEN "\
        " FROM VDCLIENTES"\
        " WHERE "\
               " VDCLIENTES.CODCLIENTE=:CODCLIENTE "\
               " AND VDCLIENTES.SEQCODCLI=:SEQCODCLI "
static v10cursors *vdselclicodcliente;

#define SELCLIVDCLIENTES "SELECT VDCLIENTES.ROWID,VDCLIENTES.CODCLIENTE,VDCLIENTES.SEQCODCLI, "\
                    " VDCLIENTES.DESCLIENTE,VDCLIENTES.TIPOCLI,VDCLIENTES.NIF, "\
                    " VDCLIENTES.CONTACTO,VDCLIENTES.TELEFONO,VDCLIENTES.FAX, "\
                    " VDCLIENTES.EMAIL,VDCLIENTES.DIRECCION,VDCLIENTES.DIRECCION1, "\
                    " VDCLIENTES.DIRECCION2,VDCLIENTES.DIRECCION3,VDCLIENTES.POBLACION, "\
                    " VDCLIENTES.DP,VDCLIENTES.CODPROV,VDCLIENTES.CODPAIS, "\
                    " VDCLIENTES.IDIOMAETIQ,VDCLIENTES.IDIOMADOC,VDCLIENTES.TIPOPEDIDO, "\
                    " VDCLIENTES.NUMALBA,VDCLIENTES.BACKORDER,VDCLIENTES.SWTANULAR, "\
                    " VDCLIENTES.SWTVALORADO,VDCLIENTES.SWTTOTALES,VDCLIENTES.SWTPROFORMA, "\
                    " VDCLIENTES.SWTAGRUPAR,VDCLIENTES.SWTPALETIZAR,VDCLIENTES.SWTMODELO, "\
                    " VDCLIENTES.SWTFACTU,VDCLIENTES.REFMODELO,VDCLIENTES.PORTES, "\
                    " VDCLIENTES.SWTSEGURO,VDCLIENTES.SWTEDI,VDCLIENTES.SWTREEMBOLSO, "\
                    " VDCLIENTES.SWTADUANA,VDCLIENTES.PRIORIDAD,VDCLIENTES.URGENCIA, "\
                    " VDCLIENTES.CODAGE,VDCLIENTES.RECARGOAGE,VDCLIENTES.DESCUENTOCAB, "\
                    " VDCLIENTES.DESCUENTOLIN,VDCLIENTES.RECARGOCAB,VDCLIENTES.RECARGOLIN, "\
                    " VDCLIENTES.IVA,VDCLIENTES.CODCLIFACTU,VDCLIENTES.DESCLIFACTU, "\
                    " VDCLIENTES.NIFFACTU,VDCLIENTES.DIRFACTU,VDCLIENTES.DIRFACTU1, "\
                    " VDCLIENTES.DIRFACTU2,VDCLIENTES.DIRFACTU3,VDCLIENTES.POBFACTU, "\
                    " VDCLIENTES.DPFACTU,VDCLIENTES.CODPROVFACTU,VDCLIENTES.CODPAISFACTU, "\
                    " VDCLIENTES.CONTAFACTU,VDCLIENTES.TELFACTU,VDCLIENTES.FAXFACTU, "\
                    " VDCLIENTES.EMAILFACTU,VDCLIENTES.SERIEFACTURA,VDCLIENTES.TIPOFORMAPAGO, "\
                    " VDCLIENTES.OBSERVACIONES,VDCLIENTES.TPCVERIF,VDCLIENTES.CODOPEMODIF, "\
                    " VDCLIENTES.FECMODIF,VDCLIENTES.HORAMODIF,VDCLIENTES.TIPOBASESEGURO, "\
                    " VDCLIENTES.BASESEGURO,VDCLIENTES.SWTBLOQDEV,VDCLIENTES.ACTIVO, "\
                    " VDCLIENTES.SWTBLOQSCAN,VDCLIENTES.ADMITEDEF,VDCLIENTES.CODCOMEN "\
        " FROM VDCLIENTES"\
        " WHERE "\
               " VDCLIENTES.CODCLIENTE=:CODCLIENTE "\
               " AND VDCLIENTES.SEQCODCLI=:SEQCODCLI "
static v10cursors *vdselclivdclientes;

#define UPDACLI "UPDATE VDCLIENTES SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " DESCLIENTE=:DESCLIENTE , "\
               " TIPOCLI=:TIPOCLI , "\
               " NIF=:NIF , "\
               " CONTACTO=:CONTACTO , "\
               " TELEFONO=:TELEFONO , "\
               " FAX=:FAX , "\
               " EMAIL=:EMAIL , "\
               " DIRECCION=:DIRECCION , "\
               " DIRECCION1=:DIRECCION1 , "\
               " DIRECCION2=:DIRECCION2 , "\
               " DIRECCION3=:DIRECCION3 , "\
               " POBLACION=:POBLACION , "\
               " DP=:DP , "\
               " CODPROV=:CODPROV , "\
               " CODPAIS=:CODPAIS , "\
               " IDIOMAETIQ=:IDIOMAETIQ , "\
               " IDIOMADOC=:IDIOMADOC , "\
               " TIPOPEDIDO=:TIPOPEDIDO , "\
               " NUMALBA=:NUMALBA , "\
               " BACKORDER=:BACKORDER , "\
               " SWTANULAR=:SWTANULAR , "\
               " SWTVALORADO=:SWTVALORADO , "\
               " SWTTOTALES=:SWTTOTALES , "\
               " SWTPROFORMA=:SWTPROFORMA , "\
               " SWTAGRUPAR=:SWTAGRUPAR , "\
               " SWTPALETIZAR=:SWTPALETIZAR , "\
               " SWTMODELO=:SWTMODELO , "\
               " SWTFACTU=:SWTFACTU , "\
               " REFMODELO=:REFMODELO , "\
               " PORTES=:PORTES , "\
               " SWTSEGURO=:SWTSEGURO , "\
               " SWTEDI=:SWTEDI , "\
               " SWTREEMBOLSO=:SWTREEMBOLSO , "\
               " SWTADUANA=:SWTADUANA , "\
               " PRIORIDAD=:PRIORIDAD , "\
               " URGENCIA=:URGENCIA , "\
               " CODAGE=:CODAGE , "\
               " RECARGOAGE=:RECARGOAGE , "\
               " DESCUENTOCAB=:DESCUENTOCAB , "\
               " DESCUENTOLIN=:DESCUENTOLIN , "\
               " RECARGOCAB=:RECARGOCAB , "\
               " RECARGOLIN=:RECARGOLIN , "\
               " IVA=:IVA , "\
               " CODCLIFACTU=:CODCLIFACTU , "\
               " DESCLIFACTU=:DESCLIFACTU , "\
               " NIFFACTU=:NIFFACTU , "\
               " DIRFACTU=:DIRFACTU , "\
               " DIRFACTU1=:DIRFACTU1 , "\
               " DIRFACTU2=:DIRFACTU2 , "\
               " DIRFACTU3=:DIRFACTU3 , "\
               " POBFACTU=:POBFACTU , "\
               " DPFACTU=:DPFACTU , "\
               " CODPROVFACTU=:CODPROVFACTU , "\
               " CODPAISFACTU=:CODPAISFACTU , "\
               " CONTAFACTU=:CONTAFACTU , "\
               " TELFACTU=:TELFACTU , "\
               " FAXFACTU=:FAXFACTU , "\
               " EMAILFACTU=:EMAILFACTU , "\
               " SERIEFACTURA=:SERIEFACTURA , "\
               " TIPOFORMAPAGO=:TIPOFORMAPAGO , "\
               " OBSERVACIONES=:OBSERVACIONES , "\
               " TPCVERIF=:TPCVERIF , "\
               " TIPOBASESEGURO=:TIPOBASESEGURO , "\
               " BASESEGURO=:BASESEGURO , "\
               " SWTBLOQDEV=:SWTBLOQDEV , "\
               " ACTIVO=:ACTIVO , "\
               " SWTBLOQSCAN=:SWTBLOQSCAN , "\
               " ADMITEDEF=:ADMITEDEF , "\
               " CODCOMEN=:CODCOMEN  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaclivdclientes;

#define INSCLI "INSERT INTO VDCLIENTES (CODCLIENTE,SEQCODCLI,DESCLIENTE,TIPOCLI,NIF,CONTACTO, "\
                    " TELEFONO,FAX,EMAIL,DIRECCION,DIRECCION1,DIRECCION2,DIRECCION3, "\
                    " POBLACION,DP,CODPROV,CODPAIS,IDIOMAETIQ,IDIOMADOC,TIPOPEDIDO, "\
                    " NUMALBA,BACKORDER,SWTANULAR,SWTVALORADO,SWTTOTALES,SWTPROFORMA,SWTAGRUPAR, "\
                    " SWTPALETIZAR,SWTMODELO,SWTFACTU,REFMODELO,PORTES,SWTSEGURO,SWTEDI, "\
                    " SWTREEMBOLSO,SWTADUANA,PRIORIDAD,URGENCIA,CODAGE,RECARGOAGE,DESCUENTOCAB, "\
                    " DESCUENTOLIN,RECARGOCAB,RECARGOLIN,IVA,CODCLIFACTU,DESCLIFACTU,NIFFACTU, "\
                    " DIRFACTU,DIRFACTU1,DIRFACTU2,DIRFACTU3,POBFACTU,DPFACTU,CODPROVFACTU, "\
                    " CODPAISFACTU,CONTAFACTU,TELFACTU,FAXFACTU,EMAILFACTU,SERIEFACTURA,TIPOFORMAPAGO, "\
                    " OBSERVACIONES,TPCVERIF,CODOPEMODIF,FECMODIF,HORAMODIF,TIPOBASESEGURO,BASESEGURO, "\
                    " SWTBLOQDEV,ACTIVO,SWTBLOQSCAN,ADMITEDEF,CODCOMEN "\
       " ) VALUES ( "\
                    " :CODCLIENTE,:SEQCODCLI,:DESCLIENTE,:TIPOCLI,:NIF,:CONTACTO, "\
                    " :TELEFONO,:FAX,:EMAIL,:DIRECCION,:DIRECCION1,:DIRECCION2,:DIRECCION3, "\
                    " :POBLACION,:DP,:CODPROV,:CODPAIS,:IDIOMAETIQ,:IDIOMADOC,:TIPOPEDIDO, "\
                    " :NUMALBA,:BACKORDER,:SWTANULAR,:SWTVALORADO,:SWTTOTALES,:SWTPROFORMA,:SWTAGRUPAR, "\
                    " :SWTPALETIZAR,:SWTMODELO,:SWTFACTU,:REFMODELO,:PORTES,:SWTSEGURO,:SWTEDI, "\
                    " :SWTREEMBOLSO,:SWTADUANA,:PRIORIDAD,:URGENCIA,:CODAGE,:RECARGOAGE,:DESCUENTOCAB, "\
                    " :DESCUENTOLIN,:RECARGOCAB,:RECARGOLIN,:IVA,:CODCLIFACTU,:DESCLIFACTU,:NIFFACTU, "\
                    " :DIRFACTU,:DIRFACTU1,:DIRFACTU2,:DIRFACTU3,:POBFACTU,:DPFACTU,:CODPROVFACTU, "\
                    " :CODPAISFACTU,:CONTAFACTU,:TELFACTU,:FAXFACTU,:EMAILFACTU,:SERIEFACTURA,:TIPOFORMAPAGO, "\
                    " :OBSERVACIONES,:TPCVERIF,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,:TIPOBASESEGURO,:BASESEGURO, "\
                    " :SWTBLOQDEV,:ACTIVO,:SWTBLOQSCAN,:ADMITEDEF,:CODCOMEN) "
static v10cursors *vdinscli;

#define DELCLI "DELETE VDCLIENTES WHERE ROWID=:MIROWID "
static v10cursors *vddelcli;

static vdclientess svdclientes;

static diccols colvdclientes[]={
	{"ROWID",V10CADENA,(size_t)&svdclientes.rowid,sizeof(svdclientes.rowid)},
	{"CODCLIENTE",V10CADENA,(size_t)&svdclientes.codcliente,sizeof(svdclientes.codcliente)},
	{"SEQCODCLI",V10LONG,(size_t)&svdclientes.seqcodcli,sizeof(svdclientes.seqcodcli)},
	{"DESCLIENTE",V10CADENA,(size_t)&svdclientes.descliente,sizeof(svdclientes.descliente)},
	{"TIPOCLI",V10CADENA,(size_t)&svdclientes.tipocli,sizeof(svdclientes.tipocli)},
	{"NIF",V10CADENA,(size_t)&svdclientes.nif,sizeof(svdclientes.nif)},
	{"CONTACTO",V10CADENA,(size_t)&svdclientes.contacto,sizeof(svdclientes.contacto)},
	{"TELEFONO",V10CADENA,(size_t)&svdclientes.telefono,sizeof(svdclientes.telefono)},
	{"FAX",V10CADENA,(size_t)&svdclientes.fax,sizeof(svdclientes.fax)},
	{"EMAIL",V10CADENA,(size_t)&svdclientes.email,sizeof(svdclientes.email)},
	{"DIRECCION",V10CADENA,(size_t)&svdclientes.direccion,sizeof(svdclientes.direccion)},
	{"DIRECCION1",V10CADENA,(size_t)&svdclientes.direccion1,sizeof(svdclientes.direccion1)},
	{"DIRECCION2",V10CADENA,(size_t)&svdclientes.direccion2,sizeof(svdclientes.direccion2)},
	{"DIRECCION3",V10CADENA,(size_t)&svdclientes.direccion3,sizeof(svdclientes.direccion3)},
	{"POBLACION",V10CADENA,(size_t)&svdclientes.poblacion,sizeof(svdclientes.poblacion)},
	{"DP",V10CADENA,(size_t)&svdclientes.dp,sizeof(svdclientes.dp)},
	{"CODPROV",V10CADENA,(size_t)&svdclientes.codprov,sizeof(svdclientes.codprov)},
	{"CODPAIS",V10CADENA,(size_t)&svdclientes.codpais,sizeof(svdclientes.codpais)},
	{"IDIOMAETIQ",V10CADENA,(size_t)&svdclientes.idiomaetiq,sizeof(svdclientes.idiomaetiq)},
	{"IDIOMADOC",V10CADENA,(size_t)&svdclientes.idiomadoc,sizeof(svdclientes.idiomadoc)},
	{"TIPOPEDIDO",V10CADENA,(size_t)&svdclientes.tipopedido,sizeof(svdclientes.tipopedido)},
	{"NUMALBA",V10LONG,(size_t)&svdclientes.numalba,sizeof(svdclientes.numalba)},
	{"BACKORDER",V10CADENA,(size_t)&svdclientes.backorder,sizeof(svdclientes.backorder)},
	{"SWTANULAR",V10CADENA,(size_t)&svdclientes.swtanular,sizeof(svdclientes.swtanular)},
	{"SWTVALORADO",V10CADENA,(size_t)&svdclientes.swtvalorado,sizeof(svdclientes.swtvalorado)},
	{"SWTTOTALES",V10CADENA,(size_t)&svdclientes.swttotales,sizeof(svdclientes.swttotales)},
	{"SWTPROFORMA",V10CADENA,(size_t)&svdclientes.swtproforma,sizeof(svdclientes.swtproforma)},
	{"SWTAGRUPAR",V10CADENA,(size_t)&svdclientes.swtagrupar,sizeof(svdclientes.swtagrupar)},
	{"SWTPALETIZAR",V10CADENA,(size_t)&svdclientes.swtpaletizar,sizeof(svdclientes.swtpaletizar)},
	{"SWTMODELO",V10CADENA,(size_t)&svdclientes.swtmodelo,sizeof(svdclientes.swtmodelo)},
	{"SWTFACTU",V10CADENA,(size_t)&svdclientes.swtfactu,sizeof(svdclientes.swtfactu)},
	{"REFMODELO",V10CADENA,(size_t)&svdclientes.refmodelo,sizeof(svdclientes.refmodelo)},
	{"PORTES",V10CADENA,(size_t)&svdclientes.portes,sizeof(svdclientes.portes)},
	{"SWTSEGURO",V10CADENA,(size_t)&svdclientes.swtseguro,sizeof(svdclientes.swtseguro)},
	{"SWTEDI",V10CADENA,(size_t)&svdclientes.swtedi,sizeof(svdclientes.swtedi)},
	{"SWTREEMBOLSO",V10CADENA,(size_t)&svdclientes.swtreembolso,sizeof(svdclientes.swtreembolso)},
	{"SWTADUANA",V10CADENA,(size_t)&svdclientes.swtaduana,sizeof(svdclientes.swtaduana)},
	{"PRIORIDAD",V10LONG,(size_t)&svdclientes.prioridad,sizeof(svdclientes.prioridad)},
	{"URGENCIA",V10LONG,(size_t)&svdclientes.urgencia,sizeof(svdclientes.urgencia)},
	{"CODAGE",V10CADENA,(size_t)&svdclientes.codage,sizeof(svdclientes.codage)},
	{"RECARGOAGE",V10DOUBLE,(size_t)&svdclientes.recargoage,sizeof(svdclientes.recargoage)},
	{"DESCUENTOCAB",V10DOUBLE,(size_t)&svdclientes.descuentocab,sizeof(svdclientes.descuentocab)},
	{"DESCUENTOLIN",V10DOUBLE,(size_t)&svdclientes.descuentolin,sizeof(svdclientes.descuentolin)},
	{"RECARGOCAB",V10DOUBLE,(size_t)&svdclientes.recargocab,sizeof(svdclientes.recargocab)},
	{"RECARGOLIN",V10DOUBLE,(size_t)&svdclientes.recargolin,sizeof(svdclientes.recargolin)},
	{"IVA",V10DOUBLE,(size_t)&svdclientes.iva,sizeof(svdclientes.iva)},
	{"CODCLIFACTU",V10CADENA,(size_t)&svdclientes.codclifactu,sizeof(svdclientes.codclifactu)},
	{"DESCLIFACTU",V10CADENA,(size_t)&svdclientes.desclifactu,sizeof(svdclientes.desclifactu)},
	{"NIFFACTU",V10CADENA,(size_t)&svdclientes.niffactu,sizeof(svdclientes.niffactu)},
	{"DIRFACTU",V10CADENA,(size_t)&svdclientes.dirfactu,sizeof(svdclientes.dirfactu)},
	{"DIRFACTU1",V10CADENA,(size_t)&svdclientes.dirfactu1,sizeof(svdclientes.dirfactu1)},
	{"DIRFACTU2",V10CADENA,(size_t)&svdclientes.dirfactu2,sizeof(svdclientes.dirfactu2)},
	{"DIRFACTU3",V10CADENA,(size_t)&svdclientes.dirfactu3,sizeof(svdclientes.dirfactu3)},
	{"POBFACTU",V10CADENA,(size_t)&svdclientes.pobfactu,sizeof(svdclientes.pobfactu)},
	{"DPFACTU",V10CADENA,(size_t)&svdclientes.dpfactu,sizeof(svdclientes.dpfactu)},
	{"CODPROVFACTU",V10CADENA,(size_t)&svdclientes.codprovfactu,sizeof(svdclientes.codprovfactu)},
	{"CODPAISFACTU",V10CADENA,(size_t)&svdclientes.codpaisfactu,sizeof(svdclientes.codpaisfactu)},
	{"CONTAFACTU",V10CADENA,(size_t)&svdclientes.contafactu,sizeof(svdclientes.contafactu)},
	{"TELFACTU",V10CADENA,(size_t)&svdclientes.telfactu,sizeof(svdclientes.telfactu)},
	{"FAXFACTU",V10CADENA,(size_t)&svdclientes.faxfactu,sizeof(svdclientes.faxfactu)},
	{"EMAILFACTU",V10CADENA,(size_t)&svdclientes.emailfactu,sizeof(svdclientes.emailfactu)},
	{"SERIEFACTURA",V10CADENA,(size_t)&svdclientes.seriefactura,sizeof(svdclientes.seriefactura)},
	{"TIPOFORMAPAGO",V10CADENA,(size_t)&svdclientes.tipoformapago,sizeof(svdclientes.tipoformapago)},
	{"OBSERVACIONES",V10CADENA,(size_t)&svdclientes.observaciones,sizeof(svdclientes.observaciones)},
	{"TPCVERIF",V10LONG,(size_t)&svdclientes.tpcverif,sizeof(svdclientes.tpcverif)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdclientes.codopemodif,sizeof(svdclientes.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdclientes.fecmodif,sizeof(svdclientes.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdclientes.horamodif,sizeof(svdclientes.horamodif)},
	{"TIPOBASESEGURO",V10CADENA,(size_t)&svdclientes.tipobaseseguro,sizeof(svdclientes.tipobaseseguro)},
	{"BASESEGURO",V10DOUBLE,(size_t)&svdclientes.baseseguro,sizeof(svdclientes.baseseguro)},
	{"SWTBLOQDEV",V10CADENA,(size_t)&svdclientes.swtbloqdev,sizeof(svdclientes.swtbloqdev)},
	{"ACTIVO",V10CADENA,(size_t)&svdclientes.activo,sizeof(svdclientes.activo)},
	{"SWTBLOQSCAN",V10CADENA,(size_t)&svdclientes.swtbloqscan,sizeof(svdclientes.swtbloqscan)},
	{"ADMITEDEF",V10CADENA,(size_t)&svdclientes.admitedef,sizeof(svdclientes.admitedef)},
	{"CODCOMEN",V10LONG,(size_t)&svdclientes.codcomen,sizeof(svdclientes.codcomen)}
	};
static diccionarios dvdclientes[]={
    {colvdclientes,75}
};
diccionario dcli={dvdclientes,1};

static char msglogCLI[LCADENA];
static char msgdebugCLI[LCADENABIG];
static int init=0;


static void fin_vd_cli(void)
{
if (vdselclicodcliente) {
    liberacursor(vdselclicodcliente);
    vdselclicodcliente = NULL;
}
if (vdselclivdclientes) {
    liberacursor(vdselclivdclientes);
    vdselclivdclientes = NULL;
}
if (vdupdaclivdclientes) {
    liberacursor(vdupdaclivdclientes);
    vdupdaclivdclientes = NULL;
}
if (vdinscli != NULL) {
    liberacursor(vdinscli);
    vdinscli = NULL;
}
if (vddelcli != NULL) {
    liberacursor(vddelcli);
    vddelcli = NULL;
}
}
static void init_selclicodcliente(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdclientes[0].numcol;nc++) dvdclientes[0].c[nc].offset-=(size_t)&svdclientes;
    vdselclicodcliente=abrecursordebug(SELCLICODCLIENTE,1280);
    definetodo(vdselclicodcliente,svdclientes.rowid,sizeof(svdclientes.rowid),V10CADENA,
                          svdclientes.codcliente,sizeof(svdclientes.codcliente),V10CADENA,
                          &svdclientes.seqcodcli,sizeof(svdclientes.seqcodcli),V10LONG,
                          svdclientes.descliente,sizeof(svdclientes.descliente),V10CADENA,
                          svdclientes.tipocli,sizeof(svdclientes.tipocli),V10CADENA,
                          svdclientes.nif,sizeof(svdclientes.nif),V10CADENA,
                          svdclientes.contacto,sizeof(svdclientes.contacto),V10CADENA,
                          svdclientes.telefono,sizeof(svdclientes.telefono),V10CADENA,
                          svdclientes.fax,sizeof(svdclientes.fax),V10CADENA,
                          svdclientes.email,sizeof(svdclientes.email),V10CADENA,
                          svdclientes.direccion,sizeof(svdclientes.direccion),V10CADENA,
                          svdclientes.direccion1,sizeof(svdclientes.direccion1),V10CADENA,
                          svdclientes.direccion2,sizeof(svdclientes.direccion2),V10CADENA,
                          svdclientes.direccion3,sizeof(svdclientes.direccion3),V10CADENA,
                          svdclientes.poblacion,sizeof(svdclientes.poblacion),V10CADENA,
                          svdclientes.dp,sizeof(svdclientes.dp),V10CADENA,
                          svdclientes.codprov,sizeof(svdclientes.codprov),V10CADENA,
                          svdclientes.codpais,sizeof(svdclientes.codpais),V10CADENA,
                          svdclientes.idiomaetiq,sizeof(svdclientes.idiomaetiq),V10CADENA,
                          svdclientes.idiomadoc,sizeof(svdclientes.idiomadoc),V10CADENA,
                          svdclientes.tipopedido,sizeof(svdclientes.tipopedido),V10CADENA,
                          &svdclientes.numalba,sizeof(svdclientes.numalba),V10LONG,
                          svdclientes.backorder,sizeof(svdclientes.backorder),V10CADENA,
                          svdclientes.swtanular,sizeof(svdclientes.swtanular),V10CADENA,
                          svdclientes.swtvalorado,sizeof(svdclientes.swtvalorado),V10CADENA,
                          svdclientes.swttotales,sizeof(svdclientes.swttotales),V10CADENA,
                          svdclientes.swtproforma,sizeof(svdclientes.swtproforma),V10CADENA,
                          svdclientes.swtagrupar,sizeof(svdclientes.swtagrupar),V10CADENA,
                          svdclientes.swtpaletizar,sizeof(svdclientes.swtpaletizar),V10CADENA,
                          svdclientes.swtmodelo,sizeof(svdclientes.swtmodelo),V10CADENA,
                          svdclientes.swtfactu,sizeof(svdclientes.swtfactu),V10CADENA,
                          svdclientes.refmodelo,sizeof(svdclientes.refmodelo),V10CADENA,
                          svdclientes.portes,sizeof(svdclientes.portes),V10CADENA,
                          svdclientes.swtseguro,sizeof(svdclientes.swtseguro),V10CADENA,
                          svdclientes.swtedi,sizeof(svdclientes.swtedi),V10CADENA,
                          svdclientes.swtreembolso,sizeof(svdclientes.swtreembolso),V10CADENA,
                          svdclientes.swtaduana,sizeof(svdclientes.swtaduana),V10CADENA,
                          &svdclientes.prioridad,sizeof(svdclientes.prioridad),V10LONG,
                          &svdclientes.urgencia,sizeof(svdclientes.urgencia),V10LONG,
                          svdclientes.codage,sizeof(svdclientes.codage),V10CADENA,
                          &svdclientes.recargoage,sizeof(svdclientes.recargoage),V10DOUBLE,
                          &svdclientes.descuentocab,sizeof(svdclientes.descuentocab),V10DOUBLE,
                          &svdclientes.descuentolin,sizeof(svdclientes.descuentolin),V10DOUBLE,
                          &svdclientes.recargocab,sizeof(svdclientes.recargocab),V10DOUBLE,
                          &svdclientes.recargolin,sizeof(svdclientes.recargolin),V10DOUBLE,
                          &svdclientes.iva,sizeof(svdclientes.iva),V10DOUBLE,
                          svdclientes.codclifactu,sizeof(svdclientes.codclifactu),V10CADENA,
                          svdclientes.desclifactu,sizeof(svdclientes.desclifactu),V10CADENA,
                          svdclientes.niffactu,sizeof(svdclientes.niffactu),V10CADENA,
                          svdclientes.dirfactu,sizeof(svdclientes.dirfactu),V10CADENA,
                          svdclientes.dirfactu1,sizeof(svdclientes.dirfactu1),V10CADENA,
                          svdclientes.dirfactu2,sizeof(svdclientes.dirfactu2),V10CADENA,
                          svdclientes.dirfactu3,sizeof(svdclientes.dirfactu3),V10CADENA,
                          svdclientes.pobfactu,sizeof(svdclientes.pobfactu),V10CADENA,
                          svdclientes.dpfactu,sizeof(svdclientes.dpfactu),V10CADENA,
                          svdclientes.codprovfactu,sizeof(svdclientes.codprovfactu),V10CADENA,
                          svdclientes.codpaisfactu,sizeof(svdclientes.codpaisfactu),V10CADENA,
                          svdclientes.contafactu,sizeof(svdclientes.contafactu),V10CADENA,
                          svdclientes.telfactu,sizeof(svdclientes.telfactu),V10CADENA,
                          svdclientes.faxfactu,sizeof(svdclientes.faxfactu),V10CADENA,
                          svdclientes.emailfactu,sizeof(svdclientes.emailfactu),V10CADENA,
                          svdclientes.seriefactura,sizeof(svdclientes.seriefactura),V10CADENA,
                          svdclientes.tipoformapago,sizeof(svdclientes.tipoformapago),V10CADENA,
                          svdclientes.observaciones,sizeof(svdclientes.observaciones),V10CADENA,
                          &svdclientes.tpcverif,sizeof(svdclientes.tpcverif),V10LONG,
                          svdclientes.codopemodif,sizeof(svdclientes.codopemodif),V10CADENA,
                          &svdclientes.fecmodif,sizeof(svdclientes.fecmodif),V10LONG,
                          svdclientes.horamodif,sizeof(svdclientes.horamodif),V10CADENA,
                          svdclientes.tipobaseseguro,sizeof(svdclientes.tipobaseseguro),V10CADENA,
                          &svdclientes.baseseguro,sizeof(svdclientes.baseseguro),V10DOUBLE,
                          svdclientes.swtbloqdev,sizeof(svdclientes.swtbloqdev),V10CADENA,
                          svdclientes.activo,sizeof(svdclientes.activo),V10CADENA,
                          svdclientes.swtbloqscan,sizeof(svdclientes.swtbloqscan),V10CADENA,
                          svdclientes.admitedef,sizeof(svdclientes.admitedef),V10CADENA,
                          &svdclientes.codcomen,sizeof(svdclientes.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselclicodcliente,"CODCLIENTE",svdclientes.codcliente,sizeof(svdclientes.codcliente),V10CADENA,
                          "SEQCODCLI",&svdclientes.seqcodcli,sizeof(svdclientes.seqcodcli),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_cli);
        init = 1;
    }
}

static void init_selclivdclientes(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdclientes[0].numcol;nc++) dvdclientes[0].c[nc].offset-=(size_t)&svdclientes;
    vdselclivdclientes=abrecursordebug(SELCLIVDCLIENTES,1280);
    definetodo(vdselclivdclientes,svdclientes.rowid,sizeof(svdclientes.rowid),V10CADENA,
                          svdclientes.codcliente,sizeof(svdclientes.codcliente),V10CADENA,
                          &svdclientes.seqcodcli,sizeof(svdclientes.seqcodcli),V10LONG,
                          svdclientes.descliente,sizeof(svdclientes.descliente),V10CADENA,
                          svdclientes.tipocli,sizeof(svdclientes.tipocli),V10CADENA,
                          svdclientes.nif,sizeof(svdclientes.nif),V10CADENA,
                          svdclientes.contacto,sizeof(svdclientes.contacto),V10CADENA,
                          svdclientes.telefono,sizeof(svdclientes.telefono),V10CADENA,
                          svdclientes.fax,sizeof(svdclientes.fax),V10CADENA,
                          svdclientes.email,sizeof(svdclientes.email),V10CADENA,
                          svdclientes.direccion,sizeof(svdclientes.direccion),V10CADENA,
                          svdclientes.direccion1,sizeof(svdclientes.direccion1),V10CADENA,
                          svdclientes.direccion2,sizeof(svdclientes.direccion2),V10CADENA,
                          svdclientes.direccion3,sizeof(svdclientes.direccion3),V10CADENA,
                          svdclientes.poblacion,sizeof(svdclientes.poblacion),V10CADENA,
                          svdclientes.dp,sizeof(svdclientes.dp),V10CADENA,
                          svdclientes.codprov,sizeof(svdclientes.codprov),V10CADENA,
                          svdclientes.codpais,sizeof(svdclientes.codpais),V10CADENA,
                          svdclientes.idiomaetiq,sizeof(svdclientes.idiomaetiq),V10CADENA,
                          svdclientes.idiomadoc,sizeof(svdclientes.idiomadoc),V10CADENA,
                          svdclientes.tipopedido,sizeof(svdclientes.tipopedido),V10CADENA,
                          &svdclientes.numalba,sizeof(svdclientes.numalba),V10LONG,
                          svdclientes.backorder,sizeof(svdclientes.backorder),V10CADENA,
                          svdclientes.swtanular,sizeof(svdclientes.swtanular),V10CADENA,
                          svdclientes.swtvalorado,sizeof(svdclientes.swtvalorado),V10CADENA,
                          svdclientes.swttotales,sizeof(svdclientes.swttotales),V10CADENA,
                          svdclientes.swtproforma,sizeof(svdclientes.swtproforma),V10CADENA,
                          svdclientes.swtagrupar,sizeof(svdclientes.swtagrupar),V10CADENA,
                          svdclientes.swtpaletizar,sizeof(svdclientes.swtpaletizar),V10CADENA,
                          svdclientes.swtmodelo,sizeof(svdclientes.swtmodelo),V10CADENA,
                          svdclientes.swtfactu,sizeof(svdclientes.swtfactu),V10CADENA,
                          svdclientes.refmodelo,sizeof(svdclientes.refmodelo),V10CADENA,
                          svdclientes.portes,sizeof(svdclientes.portes),V10CADENA,
                          svdclientes.swtseguro,sizeof(svdclientes.swtseguro),V10CADENA,
                          svdclientes.swtedi,sizeof(svdclientes.swtedi),V10CADENA,
                          svdclientes.swtreembolso,sizeof(svdclientes.swtreembolso),V10CADENA,
                          svdclientes.swtaduana,sizeof(svdclientes.swtaduana),V10CADENA,
                          &svdclientes.prioridad,sizeof(svdclientes.prioridad),V10LONG,
                          &svdclientes.urgencia,sizeof(svdclientes.urgencia),V10LONG,
                          svdclientes.codage,sizeof(svdclientes.codage),V10CADENA,
                          &svdclientes.recargoage,sizeof(svdclientes.recargoage),V10DOUBLE,
                          &svdclientes.descuentocab,sizeof(svdclientes.descuentocab),V10DOUBLE,
                          &svdclientes.descuentolin,sizeof(svdclientes.descuentolin),V10DOUBLE,
                          &svdclientes.recargocab,sizeof(svdclientes.recargocab),V10DOUBLE,
                          &svdclientes.recargolin,sizeof(svdclientes.recargolin),V10DOUBLE,
                          &svdclientes.iva,sizeof(svdclientes.iva),V10DOUBLE,
                          svdclientes.codclifactu,sizeof(svdclientes.codclifactu),V10CADENA,
                          svdclientes.desclifactu,sizeof(svdclientes.desclifactu),V10CADENA,
                          svdclientes.niffactu,sizeof(svdclientes.niffactu),V10CADENA,
                          svdclientes.dirfactu,sizeof(svdclientes.dirfactu),V10CADENA,
                          svdclientes.dirfactu1,sizeof(svdclientes.dirfactu1),V10CADENA,
                          svdclientes.dirfactu2,sizeof(svdclientes.dirfactu2),V10CADENA,
                          svdclientes.dirfactu3,sizeof(svdclientes.dirfactu3),V10CADENA,
                          svdclientes.pobfactu,sizeof(svdclientes.pobfactu),V10CADENA,
                          svdclientes.dpfactu,sizeof(svdclientes.dpfactu),V10CADENA,
                          svdclientes.codprovfactu,sizeof(svdclientes.codprovfactu),V10CADENA,
                          svdclientes.codpaisfactu,sizeof(svdclientes.codpaisfactu),V10CADENA,
                          svdclientes.contafactu,sizeof(svdclientes.contafactu),V10CADENA,
                          svdclientes.telfactu,sizeof(svdclientes.telfactu),V10CADENA,
                          svdclientes.faxfactu,sizeof(svdclientes.faxfactu),V10CADENA,
                          svdclientes.emailfactu,sizeof(svdclientes.emailfactu),V10CADENA,
                          svdclientes.seriefactura,sizeof(svdclientes.seriefactura),V10CADENA,
                          svdclientes.tipoformapago,sizeof(svdclientes.tipoformapago),V10CADENA,
                          svdclientes.observaciones,sizeof(svdclientes.observaciones),V10CADENA,
                          &svdclientes.tpcverif,sizeof(svdclientes.tpcverif),V10LONG,
                          svdclientes.codopemodif,sizeof(svdclientes.codopemodif),V10CADENA,
                          &svdclientes.fecmodif,sizeof(svdclientes.fecmodif),V10LONG,
                          svdclientes.horamodif,sizeof(svdclientes.horamodif),V10CADENA,
                          svdclientes.tipobaseseguro,sizeof(svdclientes.tipobaseseguro),V10CADENA,
                          &svdclientes.baseseguro,sizeof(svdclientes.baseseguro),V10DOUBLE,
                          svdclientes.swtbloqdev,sizeof(svdclientes.swtbloqdev),V10CADENA,
                          svdclientes.activo,sizeof(svdclientes.activo),V10CADENA,
                          svdclientes.swtbloqscan,sizeof(svdclientes.swtbloqscan),V10CADENA,
                          svdclientes.admitedef,sizeof(svdclientes.admitedef),V10CADENA,
                          &svdclientes.codcomen,sizeof(svdclientes.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselclivdclientes,"CODCLIENTE",svdclientes.codcliente,sizeof(svdclientes.codcliente),V10CADENA,
                          "SEQCODCLI",&svdclientes.seqcodcli,sizeof(svdclientes.seqcodcli),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_cli);
        init = 1;
    }
}

static void init_updaclivdclientes(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdclientes[0].numcol;nc++) dvdclientes[0].c[nc].offset-=(size_t)&svdclientes;
    vdupdaclivdclientes=abrecursordebug(UPDACLI,1280);
    bindtodo(vdupdaclivdclientes,"DESCLIENTE",svdclientes.descliente,sizeof(svdclientes.descliente),V10CADENA,
                          "TIPOCLI",svdclientes.tipocli,sizeof(svdclientes.tipocli),V10CADENA,
                          "NIF",svdclientes.nif,sizeof(svdclientes.nif),V10CADENA,
                          "CONTACTO",svdclientes.contacto,sizeof(svdclientes.contacto),V10CADENA,
                          "TELEFONO",svdclientes.telefono,sizeof(svdclientes.telefono),V10CADENA,
                          "FAX",svdclientes.fax,sizeof(svdclientes.fax),V10CADENA,
                          "EMAIL",svdclientes.email,sizeof(svdclientes.email),V10CADENA,
                          "DIRECCION",svdclientes.direccion,sizeof(svdclientes.direccion),V10CADENA,
                          "DIRECCION1",svdclientes.direccion1,sizeof(svdclientes.direccion1),V10CADENA,
                          "DIRECCION2",svdclientes.direccion2,sizeof(svdclientes.direccion2),V10CADENA,
                          "DIRECCION3",svdclientes.direccion3,sizeof(svdclientes.direccion3),V10CADENA,
                          "POBLACION",svdclientes.poblacion,sizeof(svdclientes.poblacion),V10CADENA,
                          "DP",svdclientes.dp,sizeof(svdclientes.dp),V10CADENA,
                          "CODPROV",svdclientes.codprov,sizeof(svdclientes.codprov),V10CADENA,
                          "CODPAIS",svdclientes.codpais,sizeof(svdclientes.codpais),V10CADENA,
                          "IDIOMAETIQ",svdclientes.idiomaetiq,sizeof(svdclientes.idiomaetiq),V10CADENA,
                          "IDIOMADOC",svdclientes.idiomadoc,sizeof(svdclientes.idiomadoc),V10CADENA,
                          "TIPOPEDIDO",svdclientes.tipopedido,sizeof(svdclientes.tipopedido),V10CADENA,
                          "NUMALBA",&svdclientes.numalba,sizeof(svdclientes.numalba),V10LONG,
                          "BACKORDER",svdclientes.backorder,sizeof(svdclientes.backorder),V10CADENA,
                          "SWTANULAR",svdclientes.swtanular,sizeof(svdclientes.swtanular),V10CADENA,
                          "SWTVALORADO",svdclientes.swtvalorado,sizeof(svdclientes.swtvalorado),V10CADENA,
                          "SWTTOTALES",svdclientes.swttotales,sizeof(svdclientes.swttotales),V10CADENA,
                          "SWTPROFORMA",svdclientes.swtproforma,sizeof(svdclientes.swtproforma),V10CADENA,
                          "SWTAGRUPAR",svdclientes.swtagrupar,sizeof(svdclientes.swtagrupar),V10CADENA,
                          "SWTPALETIZAR",svdclientes.swtpaletizar,sizeof(svdclientes.swtpaletizar),V10CADENA,
                          "SWTMODELO",svdclientes.swtmodelo,sizeof(svdclientes.swtmodelo),V10CADENA,
                          "SWTFACTU",svdclientes.swtfactu,sizeof(svdclientes.swtfactu),V10CADENA,
                          "REFMODELO",svdclientes.refmodelo,sizeof(svdclientes.refmodelo),V10CADENA,
                          "PORTES",svdclientes.portes,sizeof(svdclientes.portes),V10CADENA,
                          "SWTSEGURO",svdclientes.swtseguro,sizeof(svdclientes.swtseguro),V10CADENA,
                          "SWTEDI",svdclientes.swtedi,sizeof(svdclientes.swtedi),V10CADENA,
                          "SWTREEMBOLSO",svdclientes.swtreembolso,sizeof(svdclientes.swtreembolso),V10CADENA,
                          "SWTADUANA",svdclientes.swtaduana,sizeof(svdclientes.swtaduana),V10CADENA,
                          "PRIORIDAD",&svdclientes.prioridad,sizeof(svdclientes.prioridad),V10LONG,
                          "URGENCIA",&svdclientes.urgencia,sizeof(svdclientes.urgencia),V10LONG,
                          "CODAGE",svdclientes.codage,sizeof(svdclientes.codage),V10CADENA,
                          "RECARGOAGE",&svdclientes.recargoage,sizeof(svdclientes.recargoage),V10DOUBLE,
                          "DESCUENTOCAB",&svdclientes.descuentocab,sizeof(svdclientes.descuentocab),V10DOUBLE,
                          "DESCUENTOLIN",&svdclientes.descuentolin,sizeof(svdclientes.descuentolin),V10DOUBLE,
                          "RECARGOCAB",&svdclientes.recargocab,sizeof(svdclientes.recargocab),V10DOUBLE,
                          "RECARGOLIN",&svdclientes.recargolin,sizeof(svdclientes.recargolin),V10DOUBLE,
                          "IVA",&svdclientes.iva,sizeof(svdclientes.iva),V10DOUBLE,
                          "CODCLIFACTU",svdclientes.codclifactu,sizeof(svdclientes.codclifactu),V10CADENA,
                          "DESCLIFACTU",svdclientes.desclifactu,sizeof(svdclientes.desclifactu),V10CADENA,
                          "NIFFACTU",svdclientes.niffactu,sizeof(svdclientes.niffactu),V10CADENA,
                          "DIRFACTU",svdclientes.dirfactu,sizeof(svdclientes.dirfactu),V10CADENA,
                          "DIRFACTU1",svdclientes.dirfactu1,sizeof(svdclientes.dirfactu1),V10CADENA,
                          "DIRFACTU2",svdclientes.dirfactu2,sizeof(svdclientes.dirfactu2),V10CADENA,
                          "DIRFACTU3",svdclientes.dirfactu3,sizeof(svdclientes.dirfactu3),V10CADENA,
                          "POBFACTU",svdclientes.pobfactu,sizeof(svdclientes.pobfactu),V10CADENA,
                          "DPFACTU",svdclientes.dpfactu,sizeof(svdclientes.dpfactu),V10CADENA,
                          "CODPROVFACTU",svdclientes.codprovfactu,sizeof(svdclientes.codprovfactu),V10CADENA,
                          "CODPAISFACTU",svdclientes.codpaisfactu,sizeof(svdclientes.codpaisfactu),V10CADENA,
                          "CONTAFACTU",svdclientes.contafactu,sizeof(svdclientes.contafactu),V10CADENA,
                          "TELFACTU",svdclientes.telfactu,sizeof(svdclientes.telfactu),V10CADENA,
                          "FAXFACTU",svdclientes.faxfactu,sizeof(svdclientes.faxfactu),V10CADENA,
                          "EMAILFACTU",svdclientes.emailfactu,sizeof(svdclientes.emailfactu),V10CADENA,
                          "SERIEFACTURA",svdclientes.seriefactura,sizeof(svdclientes.seriefactura),V10CADENA,
                          "TIPOFORMAPAGO",svdclientes.tipoformapago,sizeof(svdclientes.tipoformapago),V10CADENA,
                          "OBSERVACIONES",svdclientes.observaciones,sizeof(svdclientes.observaciones),V10CADENA,
                          "TPCVERIF",&svdclientes.tpcverif,sizeof(svdclientes.tpcverif),V10LONG,
                          "TIPOBASESEGURO",svdclientes.tipobaseseguro,sizeof(svdclientes.tipobaseseguro),V10CADENA,
                          "BASESEGURO",&svdclientes.baseseguro,sizeof(svdclientes.baseseguro),V10DOUBLE,
                          "SWTBLOQDEV",svdclientes.swtbloqdev,sizeof(svdclientes.swtbloqdev),V10CADENA,
                          "ACTIVO",svdclientes.activo,sizeof(svdclientes.activo),V10CADENA,
                          "SWTBLOQSCAN",svdclientes.swtbloqscan,sizeof(svdclientes.swtbloqscan),V10CADENA,
                          "ADMITEDEF",svdclientes.admitedef,sizeof(svdclientes.admitedef),V10CADENA,
                          "CODCOMEN",&svdclientes.codcomen,sizeof(svdclientes.codcomen),V10LONG,
                          "MIROWID",svdclientes.rowid,sizeof(svdclientes.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_cli);
        init = 1;
    }
}

static void init_inscli(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdclientes[0].numcol;nc++) dvdclientes[0].c[nc].offset-=(size_t)&svdclientes;
    vdinscli=abrecursordebug(INSCLI,1280);
    bindtodo(vdinscli,"CODCLIENTE",svdclientes.codcliente,sizeof(svdclientes.codcliente),V10CADENA,
                          "SEQCODCLI",&svdclientes.seqcodcli,sizeof(svdclientes.seqcodcli),V10LONG,
                          "DESCLIENTE",svdclientes.descliente,sizeof(svdclientes.descliente),V10CADENA,
                          "TIPOCLI",svdclientes.tipocli,sizeof(svdclientes.tipocli),V10CADENA,
                          "NIF",svdclientes.nif,sizeof(svdclientes.nif),V10CADENA,
                          "CONTACTO",svdclientes.contacto,sizeof(svdclientes.contacto),V10CADENA,
                          "TELEFONO",svdclientes.telefono,sizeof(svdclientes.telefono),V10CADENA,
                          "FAX",svdclientes.fax,sizeof(svdclientes.fax),V10CADENA,
                          "EMAIL",svdclientes.email,sizeof(svdclientes.email),V10CADENA,
                          "DIRECCION",svdclientes.direccion,sizeof(svdclientes.direccion),V10CADENA,
                          "DIRECCION1",svdclientes.direccion1,sizeof(svdclientes.direccion1),V10CADENA,
                          "DIRECCION2",svdclientes.direccion2,sizeof(svdclientes.direccion2),V10CADENA,
                          "DIRECCION3",svdclientes.direccion3,sizeof(svdclientes.direccion3),V10CADENA,
                          "POBLACION",svdclientes.poblacion,sizeof(svdclientes.poblacion),V10CADENA,
                          "DP",svdclientes.dp,sizeof(svdclientes.dp),V10CADENA,
                          "CODPROV",svdclientes.codprov,sizeof(svdclientes.codprov),V10CADENA,
                          "CODPAIS",svdclientes.codpais,sizeof(svdclientes.codpais),V10CADENA,
                          "IDIOMAETIQ",svdclientes.idiomaetiq,sizeof(svdclientes.idiomaetiq),V10CADENA,
                          "IDIOMADOC",svdclientes.idiomadoc,sizeof(svdclientes.idiomadoc),V10CADENA,
                          "TIPOPEDIDO",svdclientes.tipopedido,sizeof(svdclientes.tipopedido),V10CADENA,
                          "NUMALBA",&svdclientes.numalba,sizeof(svdclientes.numalba),V10LONG,
                          "BACKORDER",svdclientes.backorder,sizeof(svdclientes.backorder),V10CADENA,
                          "SWTANULAR",svdclientes.swtanular,sizeof(svdclientes.swtanular),V10CADENA,
                          "SWTVALORADO",svdclientes.swtvalorado,sizeof(svdclientes.swtvalorado),V10CADENA,
                          "SWTTOTALES",svdclientes.swttotales,sizeof(svdclientes.swttotales),V10CADENA,
                          "SWTPROFORMA",svdclientes.swtproforma,sizeof(svdclientes.swtproforma),V10CADENA,
                          "SWTAGRUPAR",svdclientes.swtagrupar,sizeof(svdclientes.swtagrupar),V10CADENA,
                          "SWTPALETIZAR",svdclientes.swtpaletizar,sizeof(svdclientes.swtpaletizar),V10CADENA,
                          "SWTMODELO",svdclientes.swtmodelo,sizeof(svdclientes.swtmodelo),V10CADENA,
                          "SWTFACTU",svdclientes.swtfactu,sizeof(svdclientes.swtfactu),V10CADENA,
                          "REFMODELO",svdclientes.refmodelo,sizeof(svdclientes.refmodelo),V10CADENA,
                          "PORTES",svdclientes.portes,sizeof(svdclientes.portes),V10CADENA,
                          "SWTSEGURO",svdclientes.swtseguro,sizeof(svdclientes.swtseguro),V10CADENA,
                          "SWTEDI",svdclientes.swtedi,sizeof(svdclientes.swtedi),V10CADENA,
                          "SWTREEMBOLSO",svdclientes.swtreembolso,sizeof(svdclientes.swtreembolso),V10CADENA,
                          "SWTADUANA",svdclientes.swtaduana,sizeof(svdclientes.swtaduana),V10CADENA,
                          "PRIORIDAD",&svdclientes.prioridad,sizeof(svdclientes.prioridad),V10LONG,
                          "URGENCIA",&svdclientes.urgencia,sizeof(svdclientes.urgencia),V10LONG,
                          "CODAGE",svdclientes.codage,sizeof(svdclientes.codage),V10CADENA,
                          "RECARGOAGE",&svdclientes.recargoage,sizeof(svdclientes.recargoage),V10DOUBLE,
                          "DESCUENTOCAB",&svdclientes.descuentocab,sizeof(svdclientes.descuentocab),V10DOUBLE,
                          "DESCUENTOLIN",&svdclientes.descuentolin,sizeof(svdclientes.descuentolin),V10DOUBLE,
                          "RECARGOCAB",&svdclientes.recargocab,sizeof(svdclientes.recargocab),V10DOUBLE,
                          "RECARGOLIN",&svdclientes.recargolin,sizeof(svdclientes.recargolin),V10DOUBLE,
                          "IVA",&svdclientes.iva,sizeof(svdclientes.iva),V10DOUBLE,
                          "CODCLIFACTU",svdclientes.codclifactu,sizeof(svdclientes.codclifactu),V10CADENA,
                          "DESCLIFACTU",svdclientes.desclifactu,sizeof(svdclientes.desclifactu),V10CADENA,
                          "NIFFACTU",svdclientes.niffactu,sizeof(svdclientes.niffactu),V10CADENA,
                          "DIRFACTU",svdclientes.dirfactu,sizeof(svdclientes.dirfactu),V10CADENA,
                          "DIRFACTU1",svdclientes.dirfactu1,sizeof(svdclientes.dirfactu1),V10CADENA,
                          "DIRFACTU2",svdclientes.dirfactu2,sizeof(svdclientes.dirfactu2),V10CADENA,
                          "DIRFACTU3",svdclientes.dirfactu3,sizeof(svdclientes.dirfactu3),V10CADENA,
                          "POBFACTU",svdclientes.pobfactu,sizeof(svdclientes.pobfactu),V10CADENA,
                          "DPFACTU",svdclientes.dpfactu,sizeof(svdclientes.dpfactu),V10CADENA,
                          "CODPROVFACTU",svdclientes.codprovfactu,sizeof(svdclientes.codprovfactu),V10CADENA,
                          "CODPAISFACTU",svdclientes.codpaisfactu,sizeof(svdclientes.codpaisfactu),V10CADENA,
                          "CONTAFACTU",svdclientes.contafactu,sizeof(svdclientes.contafactu),V10CADENA,
                          "TELFACTU",svdclientes.telfactu,sizeof(svdclientes.telfactu),V10CADENA,
                          "FAXFACTU",svdclientes.faxfactu,sizeof(svdclientes.faxfactu),V10CADENA,
                          "EMAILFACTU",svdclientes.emailfactu,sizeof(svdclientes.emailfactu),V10CADENA,
                          "SERIEFACTURA",svdclientes.seriefactura,sizeof(svdclientes.seriefactura),V10CADENA,
                          "TIPOFORMAPAGO",svdclientes.tipoformapago,sizeof(svdclientes.tipoformapago),V10CADENA,
                          "OBSERVACIONES",svdclientes.observaciones,sizeof(svdclientes.observaciones),V10CADENA,
                          "TPCVERIF",&svdclientes.tpcverif,sizeof(svdclientes.tpcverif),V10LONG,
                          "TIPOBASESEGURO",svdclientes.tipobaseseguro,sizeof(svdclientes.tipobaseseguro),V10CADENA,
                          "BASESEGURO",&svdclientes.baseseguro,sizeof(svdclientes.baseseguro),V10DOUBLE,
                          "SWTBLOQDEV",svdclientes.swtbloqdev,sizeof(svdclientes.swtbloqdev),V10CADENA,
                          "ACTIVO",svdclientes.activo,sizeof(svdclientes.activo),V10CADENA,
                          "SWTBLOQSCAN",svdclientes.swtbloqscan,sizeof(svdclientes.swtbloqscan),V10CADENA,
                          "ADMITEDEF",svdclientes.admitedef,sizeof(svdclientes.admitedef),V10CADENA,
                          "CODCOMEN",&svdclientes.codcomen,sizeof(svdclientes.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_cli);
        init = 1;
    }
}

static void init_delcli(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdclientes[0].numcol;nc++) dvdclientes[0].c[nc].offset-=(size_t)&svdclientes;
    vddelcli=abrecursordebug(DELCLI,1280);
    bindtodo(vddelcli,"MIROWID",svdclientes.rowid,sizeof(svdclientes.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_cli);
        init = 1;
    }
}

diccionario *CLIdamediccionario(void)
{
     return(&dcli);
}

int CLIselcodcliente(char *codcliente,long seqcodcli,vdclientess *cli)
{
  int vdret;
  if (vdselclicodcliente==NULL) init_selclicodcliente();
  memset(&svdclientes,0,sizeof(svdclientes));
  strcpy(svdclientes.codcliente,codcliente);
  svdclientes.seqcodcli=seqcodcli;
  vdret=ejefetchcursor(vdselclicodcliente);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselclicodcliente. vdret %d. \n",CLIlog(&svdclientes),vdret);
    return(VD_EERRORACLE);
   }
  *cli=svdclientes;
  return(vdret);
}

int CLIselvdclientes(char *codcliente,long seqcodcli,vdclientess *cli)
{
  int vdret;
  if (vdselclivdclientes==NULL) init_selclivdclientes();
  memset(&svdclientes,0,sizeof(svdclientes));
  strcpy(svdclientes.codcliente,codcliente);
  svdclientes.seqcodcli=seqcodcli;
  vdret=ejefetchcursor(vdselclivdclientes);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselclivdclientes. vdret %d. \n",CLIlog(&svdclientes),vdret);
    return(VD_EERRORACLE);
   }
  *cli=svdclientes;
  return(vdret);
}

int CLIactualizavdclientes(vdclientess *cli,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando CLIactualizavdclientes:  %s .  \n",CLIlog(&svdclientes));
  if (vdupdaclivdclientes==NULL) init_updaclivdclientes();
  svdclientes=*cli;
  vdret=ejecutacursor(vdupdaclivdclientes);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaclivdclientes);
     getcurerrornombre(vdupdaclivdclientes->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaclivdclientes)!=1) return(VD_EERRORACLE);
  return(0);
}

int CLIinsert(vdclientess *cli,int error)
{
  int vdret;
  if (!vdinscli) init_inscli();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",CLIlog(&svdclientes));
  svdclientes=*cli;
  vdret=ejecutacursor(vdinscli);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinscli);
     getcurerrornombre(vdinscli->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int CLIdel(vdclientess *cli,int error)
{
  int vdret;
  svdclientes=*cli;
  if (vddelcli==NULL) init_delcli();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",CLIlog(&svdclientes));
  vdret=ejecutacursor(vddelcli);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelcli);
     getcurerrornombre(vddelcli->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int CLIinter(vdclientess *cli)
{
  int vdret = 0;
  if (vdselclivdclientes==NULL) init_selclivdclientes();
  memset(&svdclientes,0,sizeof(svdclientes));
  strcpy(svdclientes.codcliente,cli->codcliente);
  svdclientes.seqcodcli = cli->seqcodcli;
  vdret=ejefetchcursor(vdselclivdclientes);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselclivdclientes. vdret %d. \n",CLIlog(&svdclientes),vdret);
    return(VD_EERRORACLE);
  }

  *cli=svdclientes;
  return(vdret);
}

char * CLIlog(vdclientess *cli)
{
    sprintf(msglogCLI, "VDCLIENTES: codcliente %s seqcodcli %ld ",cli->codcliente,cli->seqcodcli);
    return(msglogCLI);
}

char * CLIdebug(vdclientess *cli)
{
    debugestruct(&dcli,cli,msgdebugCLI);
    return(msgdebugCLI);
}

