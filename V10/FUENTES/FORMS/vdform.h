#ifndef __VDFORM__
#define __VDFORM__
#include "v10wwwform.h"
#include "vd.h"


VDEXPORT vdusuarios vduser;

VDEXPORT void ponwindowtext(void);
VDEXPORT void ponuserdb(void);
VDEXPORT void ponhostname(void);
VDEXPORT int verificausr(char *usr,char *pwd);
VDEXPORT int pideusuario(void);
VDEXPORT void inittriguser(void);

//Funciones definidas en VDPASS.C
#define ERRPASSCORTO     1
#define ERRPASSSIMPLE    2
#define ERRPASSINCORREC  3
#define ERRPASSBLOQUEAD  4
#define ERRPASSCADUCADO  5
#define ERRPASSAVISO     6
#define ERRPARAM         7
#define ERRPASSREPETIDO  8
VDEXPORT int damehashope(char *codope,char *pass,char *hpass);
VDEXPORT int verificanuevopass(char *codope,char *pass,char **error);
VDEXPORT int verificapass(char *codope,char *pass,char **error);
VDEXPORT int creafirma(char *codope,char *password,char *priv,char *pub,char **error);

//Funciones definidas en VDFORTRIG.C
VDEXPORT int inittrigersform(char *tipotriger);
void initrigcolores(); // inicializa triggers de carga de colores

//Funciones definidas en VDFORMCOLOR.C
#define TEMAESTANDAR  "ESTANDAR"
void inittrigcolores(); // inicializa triggers de colores del FORM

//Funciones definidas en VDFORMUSER.C
//int reiniciaform(char *param,void *dato);

//Funciones definidas en VDCAMBIAWHERE.C
VDEXPORT void initvdwhere(void);

//Funciones definidas en VDPROTECT.C
VDEXPORT int dameproteccionvd(char *cadena);

//Funciones definidas en VDDEFCAMPOAUX.C
VDEXPORT char *leedefectocampo(fcampos *campo);
VDEXPORT char *leedefectobloque(forms *f,bloques *b,int paso);

// Funciones definidas en VDFORMSTATS.C
int vdcargadatos(int nstat, bloques *b,char *nombre, char *v10datoscharts);
//Funciones definidas en VFTRIGBOTON.C
void inittrigboton(void);
//Funciones definidas en VFTRIGEXCEL.C
void inittrigexcel(void);
#endif