// Modulo generado automaticamente a partir de VDDIVIS.DEF

VDEXPORT diccionario ddiv;
#define DIVNUMCOL	30
typedef struct {
        char    rowid[ROWIDLON];
        char    coddiv[LCODDIV];
        char    codemp[LCODEMP];
        char    coddivemp[LCODDIVEMP];
        char    desdiv[LDESDIV];
        char    dabdiv[LDABDIV];
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
        char    buzonin[LBUZONIN];
        char    buzonout[LBUZONOUT];
        char    codeanemp[LCODEANEMP];
        char    sufijodoc[LSUFIJODOC];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vddiviss;

// Prototipos de funciones definidas en VDDIVIS.C
VDEXPORT diccionario *DIVdamediccionario(void);
VDEXPORT int DIVbuscatodo(vddiviss *div);
VDEXPORT int DIVnexttodo(vddiviss *div);
VDEXPORT int DIVselvddivis(char *coddiv,vddiviss *div);
VDEXPORT int DIVinsert(vddiviss *div,int error);
VDEXPORT int DIVdel(vddiviss *div,int error);
VDEXPORT char *DIVlog(vddiviss *div);
char * DIVdebug(vddiviss *div);
