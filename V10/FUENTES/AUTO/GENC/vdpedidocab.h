// Modulo generado automaticamente a partir de VDPEDIDOCAB.DEF

VDEXPORT diccionario dpec;
#define PECNUMCOL	186
#define LCOMENPEC 1026
//#define LCODBULTO 19
typedef struct {
        char    rowid[ROWIDLON];
        char    coddiv[LCODDIV];
        long    anoped;
        char    codped[LCODPED];
        long    seqped;
        long    anoalb;
        char    codalb[LCODALB];
        long    anogrup;
        long    codgrup;
        long    codserieprep;
        long    codserieexp;
        char    tipopedido[LTIPOPEDIDO];
        long    nlineas;
        char    pedidocliente[LPEDIDOCLIENTE];
        long    fecpedidocliente;
        char    pedidohost[LPEDIDOHOST];
        char    codcliente[LCODCLIENTE];
        char    descliente[LDESCLIENTE];
        char    nif[LNIF];
        char    contacto[LCONTACTO];
        char    direccion[LDIRECCION];
        char    direccion1[LDIRECCION1];
        char    direccion2[LDIRECCION2];
        char    direccion3[LDIRECCION3];
        char    poblacion[LPOBLACION];
        char    codprov[LCODPROV];
        char    dp[LDP];
        char    codpais[LCODPAIS];
        char    telefono[LTELEFONO];
        char    fax[LFAX];
        char    email[LEMAIL];
        char    direccionedi[LDIRECCIONEDI];
        char    sufijodoc[LSUFIJODOC];
        char    idiomaetiq[LIDIOMAETIQ];
        char    idiomadoc[LIDIOMADOC];
        long    numalba;
        char    menhost[LMENHOST];
        char    swtanular[LSWTANULAR];
        char    swtvalorado[LSWTVALORADO];
        char    swttotales[LSWTTOTALES];
        char    swtproforma[LSWTPROFORMA];
        char    swtalbexterior[LSWTALBEXTERIOR];
        char    swtalbsellado[LSWTALBSELLADO];
        char    portes[LPORTES];
        char    swtagrupar[LSWTAGRUPAR];
        char    swtcomunicar[LSWTCOMUNICAR];
        char    swtmodelo[LSWTMODELO];
        char    refmodelo[LREFMODELO];
        char    swtmiscelaneo[LSWTMISCELANEO];
        char    swtpackinglist[LSWTPACKINGLIST];
        char    swtnoetiqcc[LSWTNOETIQCC];
        char    swtpaletizar[LSWTPALETIZAR];
        char    swtetiqeci[LSWTETIQECI];
        char    swtbloqexp[LSWTBLOQEXP];
        char    swtmail[LSWTMAIL];
        char    swtfax[LSWTFAX];
        char    swtedi[LSWTEDI];
        char    codareaexped[LCODAREAEXPED];
        char    backorder[LBACKORDER];
        char    swtprepmono[LSWTPREPMONO];
        long    tpcverif;
        char    colcambiovol[LCOLCAMBIOVOL];
        char    moneda[LMONEDA];
        double  descuento;
        char    desdescuento[LDESDESCUENTO];
        double  recargo;
        char    desrecargo[LDESRECARGO];
        char    condpago[LCONDPAGO];
        long    prioridad;
        long    urgencia;
        char    codage[LCODAGE];
        char    trackingage[LTRACKINGAGE];
        char    datosage[LDATOSAGE];
        long    puerto;
        char    swtseguro[LSWTSEGURO];
        char    swtreembolso[LSWTREEMBOLSO];
        char    swtaduana[LSWTADUANA];
        long    recargoage;
        char    swtreexp[LSWTREEXP];
        char    codclireexp[LCODCLIREEXP];
        char    desclireexp[LDESCLIREEXP];
        char    nifreexp[LNIFREEXP];
        char    contareexp[LCONTAREEXP];
        char    dirreexp[LDIRREEXP];
        char    dirreexp1[LDIRREEXP1];
        char    dirreexp2[LDIRREEXP2];
        char    dirreexp3[LDIRREEXP3];
        char    pobreexp[LPOBREEXP];
        char    codprovreexp[LCODPROVREEXP];
        char    dpreexp[LDPREEXP];
        char    codpaisreexp[LCODPAISREEXP];
        char    telreexp[LTELREEXP];
        char    faxreexp[LFAXREEXP];
        char    emailreexp[LEMAILREEXP];
        char    direccionedireexp[LDIRECCIONEDIREEXP];
        char    swtfactu[LSWTFACTU];
        char    swtnumeroserie[LSWTNUMEROSERIE];
        char    codclifactu[LCODCLIFACTU];
        char    desclifactu[LDESCLIFACTU];
        char    niffactu[LNIFFACTU];
        char    contafactu[LCONTAFACTU];
        char    dirfactu[LDIRFACTU];
        char    dirfactu1[LDIRFACTU1];
        char    dirfactu2[LDIRFACTU2];
        char    dirfactu3[LDIRFACTU3];
        char    pobfactu[LPOBFACTU];
        char    codprovfactu[LCODPROVFACTU];
        char    dpfactu[LDPFACTU];
        char    codpaisfactu[LCODPAISFACTU];
        char    telfactu[LTELFACTU];
        char    faxfactu[LFAXFACTU];
        char    emailfactu[LEMAILFACTU];
        char    direccionedifactu[LDIRECCIONEDIFACTU];
        char    coddemanda[LCODDEMANDA];
        char    tipodemanda[LTIPODEMANDA];
        long    codcomen;
        double  pesopedido;
        double  volumenpedido;
        double  importepedido;
        long    feccaptura;
        char    horacaptura[LHORACAPTURA];
        long    fecservicio;
        long    fecgrabacion;
        char    horagrabacion[LHORAGRABACION];
        long    fecrecep;
        char    horarecep[LHORARECEP];
        long    fecreserva;
        char    horareserva[LHORARESERVA];
        long    fectermin;
        char    horatermin[LHORATERMIN];
        long    feccomunica;
        char    horacomunica[LHORACOMUNICA];
        long    fecentrega;
        char    horaentrega[LHORAENTREGA];
        long    status;
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        double  baseseguro;
        char    cde[LCDE];
        double  difagencia;
        char    factagencia[LFACTAGENCIA];
        char    tipobaseseguro[LTIPOBASESEGURO];
        char    swtvolpedido[LSWTVOLPEDIDO];
        char    codagesap[LCODAGESAP];
        long    seclabel;
        char    referenciacli[LREFERENCIACLI];
        char    facturasap[LFACTURASAP];
        long    fecembarca;
        char    horaembarca[LHORAEMBARCA];
        long    fectransporta;
        long    fecfinpick;
        char    horafinpick[LHORAFINPICK];
        long    fecfactura;
        char    horafactura[LHORAFACTURA];
        long    fecasignaf;
        char    horaasignaf[LHORAASIGNAF];
        long    fectimbre;
        double  impfact;
        char    eci_comprador[LECI_COMPRADOR];
        char    eci_departamento[LECI_DEPARTAMENTO];
        char    eci_destino[LECI_DESTINO];
        char    eci_origen[LECI_ORIGEN];
        char    eci_proveedor[LECI_PROVEEDOR];
        char    eci_receptor[LECI_RECEPTOR];
        char    eci_sscc[LECI_SSCC];
        char    eci_sucursal[LECI_SUCURSAL];
        char    codopealta[LCODOPEALTA];
        char    clavepenitenciario[LCLAVEPENITENCIARIO];
        char    tipopedidoextra[LTIPOPEDIDOEXTRA];
        char    codopeanu[LCODOPEANU];
        long    fecanu;
        char    horaanu[LHORAANU];
        char    motivoanu[LMOTIVOANU];
        char    swtcajascompletas[LSWTCAJASCOMPLETAS];
        char    swtsepararcapas[LSWTSEPARARCAPAS];
        char    swtsepararreferencias[LSWTSEPARARREFERENCIAS];
        char    swtimpnodespaletizar[LSWTIMPNODESPALETIZAR];
        long    numpacklist;
        char    swtanuladohost[LSWTANULADOHOST];
        char    refagrupacion[LREFAGRUPACION];
        long    claveinci;
        char    swtfmd[LSWTFMD];
        char    comenpec[LCOMENPEC];
        char    codbulto[LCODBULTO];
    } vdpedidocabs;

// Prototipos de funciones definidas en VDPEDIDOCAB.C
VDEXPORT diccionario *PECdamediccionario(void);
VDEXPORT int PECselcodbulto(char *codbulto,vdpedidocabs *pec);
VDEXPORT int PECbuscastatus(long status,vdpedidocabs *pec);
VDEXPORT int PECnextstatus(vdpedidocabs *pec);
VDEXPORT int PECbuscastatusmenor(char *coddiv,long anoped,char *codped,long status,vdpedidocabs *pec);
VDEXPORT int PECnextstatusmenor(vdpedidocabs *pec);
VDEXPORT int PECbuscastatusmayor(char *coddiv,long anoped,char *codped,long status,vdpedidocabs *pec);
VDEXPORT int PECnextstatusmayor(vdpedidocabs *pec);
VDEXPORT int PECselvdpedidocab(char *coddiv,long anoped,char *codped,long seqped,vdpedidocabs *pec);
VDEXPORT int PEClock(vdpedidocabs *pec,int wait,int verificar,...);
VDEXPORT int PECactualizastatusydemanda(vdpedidocabs *pec,int error);
VDEXPORT int PECactualizastatus(vdpedidocabs *pec,int error);
VDEXPORT int PECactualizareserva(vdpedidocabs *pec,int error);
VDEXPORT int PECactualizacodage(vdpedidocabs *pec,int error);
VDEXPORT int PECactualizavolumenypeso(vdpedidocabs *pec,int error);
VDEXPORT int PECinsert(vdpedidocabs *pec,int error);
VDEXPORT int PECdel(vdpedidocabs *pec,int error);
VDEXPORT char *PEClog(vdpedidocabs *pec);
char * PECdebug(vdpedidocabs *pec);
