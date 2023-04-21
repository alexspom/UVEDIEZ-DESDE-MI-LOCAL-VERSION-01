// Modulo generado automaticamente a partir de VDEMPRE.DEF

VDEXPORT diccionario dempre;
#define EMPRENUMCOL	25
typedef struct {
        char    rowid[ROWIDLON];
        char    codemp[LCODEMP];
        char    desemp[LDESEMP];
        char    dabemp[LDABEMP];
        char    nif[LNIF];
        char    contacto[LCONTACTO];
        char    direccion1[LDIRECCION1];
        char    direccion2[LDIRECCION2];
        char    direccion3[LDIRECCION3];
        char    direccion4[LDIRECCION4];
        char    poblacion[LPOBLACION];
        char    codpais[LCODPAIS];
        char    codprov[LCODPROV];
        char    dp[LDP];
        char    telefono1[LTELEFONO1];
        char    telefono2[LTELEFONO2];
        char    fax1[LFAX1];
        char    fax2[LFAX2];
        char    email[LEMAIL];
        char    edi[LEDI];
        char    sufijodoc[LSUFIJODOC];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdempres;

// Prototipos de funciones definidas en VDEMPRE.C
VDEXPORT diccionario *EMPREdamediccionario(void);
VDEXPORT int EMPREselvdempre(char *codemp,vdempres *empre);
VDEXPORT char *EMPRElog(vdempres *empre);
char * EMPREdebug(vdempres *empre);
