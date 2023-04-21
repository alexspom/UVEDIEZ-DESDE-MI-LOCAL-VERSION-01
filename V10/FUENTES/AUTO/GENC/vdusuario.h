// Modulo generado automaticamente a partir de VDUSUARIO.DEF

VDEXPORT diccionario dusu;
#define USUNUMCOL	26
typedef struct {
        char    rowid[ROWIDLON];
        char    codope[LCODOPE];
        char    nombre[LNOMBRE];
        char    apellido1[LAPELLIDO1];
        char    apellido2[LAPELLIDO2];
        char    iniciales[LINICIALES];
        char    hpassword[LHPASSWORD];
        long    fecpassword;
        char    horapassword[LHORAPASSWORD];
        long    feccaduc;
        char    cpub[LCPUB];
        char    cpriv[LCPRIV];
        char    tema[LTEMA];
        long    nivel;
        char    bloqueope[LBLOQUEOPE];
        long    conterrsuc;
        long    conterrtot;
        long    contlog;
        char    menuasociado[LMENUASOCIADO];
        char    idioma[LIDIOMA];
        long    tpcverif;
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
    } vdusuarios;

// Prototipos de funciones definidas en VDUSUARIO.C
VDEXPORT diccionario *USUdamediccionario(void);
VDEXPORT int USUselcodope(char *codope,vdusuarios *usu);
VDEXPORT int USUselvdusuario(char *codope,vdusuarios *usu);
VDEXPORT char *USUlog(vdusuarios *usu);
char * USUdebug(vdusuarios *usu);
