// Modulo generado automaticamente a partir de VDALMA.DEF

VDEXPORT diccionario dalm;
#define ALMNUMCOL	22
typedef struct {
        char    rowid[ROWIDLON];
        char    codalm[LCODALM];
        char    desalm[LDESALM];
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
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdalmas;

// Prototipos de funciones definidas en VDALMA.C
VDEXPORT diccionario *ALMdamediccionario(void);
VDEXPORT int ALMselvdalma(char *codalm,vdalmas *alm);
VDEXPORT char *ALMlog(vdalmas *alm);
char * ALMdebug(vdalmas *alm);
