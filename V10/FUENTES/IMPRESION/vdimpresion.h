#include "vd.h"
#include "etiquetas/v10etiqueta.h"

#define IMPRENOCONECTADA -1000
#define IMPRESORANOSPOOL -1001

#define PREVISUALIZA    "WINVIEW"
#define PORDEFECTO      "WINDEF"
#define EXPORTAFICHERO  "WINFILE"
#define SELECCIONA      "WINSEL"

// vdimpresion.c
VDEXPORT int vdimprimedesdespool(char *tipoimpre,char *documento,char *params,long copias,char *codimpre,char *fichero,char *msjerror,char *tipocorreo,char *asunto,char *cuerpo,int prioridad);
VDEXPORT int vdimprime(char *tipoimpre,char *documento,char *params,long copias,char *codimpre,char *fichero, 
              long modospool, // modospool: 0. crear, 1. crear y abrir, 2. vía spool
              char *msjerror );
VDEXPORT int dametipoimpre(char *tipoimpre, vdimpretipos *imtp, 
                            char *documento, char *fichero,  
                            char *fichetiqueta,char *fichvsq,char *ncursor,char *midocumento,
                            char *msjerror);

// vdspoolimpre.c
VDEXPORT int imprimeporspool(char *tipoimpre,char *codimpre,char *fichero,char *documento,char *params,long numcopias,long fecplanif,char *horaplanif);
VDEXPORT int auditaimpre(char *tipoimpre,char *codimpre,char *fichero,char *documento,char *params,long numcopias);

// funciones en vdimpresio.c
VDEXPORT int dameasignacion(char *tipoimpre, char *midocumento, char *codimpre, vdimpreasigs *imas,int desdespool, char *msjerror);
VDEXPORT int dameimpresora(char *codimpre,vdimpresorass *impr,vdimpregrupos *imgr, char *msjerror);
    