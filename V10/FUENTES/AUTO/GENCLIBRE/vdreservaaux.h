// Fichero generado automaticamente a partir de VDRESERVAAUX.DEF

VDEXPORT diccionario dres;
#ifndef LTAREACONTE
#define LTAREACONTE 33
#endif

#ifndef LTAREAEMBA
#define LTAREAEMBA 33
#endif

#ifndef LTAREAUNIINV
#define LTAREAUNIINV 33
#endif

#ifndef LTAREAPREPICK
#define LTAREAPREPICK 33
#endif

#ifndef LTAREAUNI
#define LTAREAUNI 33
#endif

#ifndef LUNIAGRUPAEMBA
#define LUNIAGRUPAEMBA 2
#endif

#ifndef LUNIAGRUPAUNI
#define LUNIAGRUPAUNI 2
#endif

#ifndef LMONOFORMATO
#define LMONOFORMATO 2
#endif

#ifndef LEMBALAJESCOMPLETOS
#define LEMBALAJESCOMPLETOS 2
#endif

#ifndef LSOLOPARCIALES
#define LSOLOPARCIALES 2
#endif

#ifndef LREVISARCOMPLETO
#define LREVISARCOMPLETO 2
#endif

#ifndef LCODDEMANDA
#define LCODDEMANDA 21
#endif

#ifndef LTIPODEMANDA
#define LTIPODEMANDA 11
#endif

#ifndef LUNIAGRUPA
#define LUNIAGRUPA 2
#endif

#ifndef LCODUBIORI
#define LCODUBIORI 13
#endif

#ifndef LCODCONCE
#define LCODCONCE 11
#endif

#ifndef LCOMENTARIO
#define LCOMENTARIO 513
#endif

#ifndef LTAREA
#define LTAREA 33
#endif

#ifndef LUNIAGRUPAE
#define LUNIAGRUPAE 2
#endif

typedef struct {
        char    tareaconte[LTAREACONTE];
        char    tareaemba[LTAREAEMBA];
        char    tareauniinv[LTAREAUNIINV];
        char    tareaprepick[LTAREAPREPICK];
        char    tareauni[LTAREAUNI];
        char    uniagrupaemba[LUNIAGRUPAEMBA];
        char    uniagrupauni[LUNIAGRUPAUNI];
        char    monoformato[LMONOFORMATO];
        char    embalajescompletos[LEMBALAJESCOMPLETOS];
        char    soloparciales[LSOLOPARCIALES];
        char    revisarcompleto[LREVISARCOMPLETO];
        double  reservado;
        double  cantidad;
        double  diferconte;
        double  diferemba;
        double  diferuni;
        char    coddemanda[LCODDEMANDA];
        char    tipodemanda[LTIPODEMANDA];
        long    lindemanda;
        char    uniagrupa[LUNIAGRUPA];
        char    codubiori[LCODUBIORI];
        char    codconce[LCODCONCE];
        long    status;
        char    comentario[LCOMENTARIO];
        char    tarea[LTAREA];
        char    uniagrupae[LUNIAGRUPAE];
} vdress; 


VDEXPORT diccionario *RESdamediccionario(void);
VDEXPORT int RESbuscareservadodeml(char *coddemanda,char *tipodemanda,long lindemanda,char *uniagrupa,vdress *res);
VDEXPORT int RESnextreservadodeml(vdress *res);
VDEXPORT int RESprocreservapedidodif(char *coddemanda,char *tipodemanda,long lindemanda,double cantidad,char *codubiori,char *tareauni,char *tareaemba,char *tareaconte,char *codconce,long status,char *comentario,double reservado,vdress *res);
VDEXPORT int RESprocreservapedidostd(char *coddemanda,char *tipodemanda,long lindemanda,double cantidad,char *tareaconte,char *tareaemba,char *tareauniinv,char *tareaprepick,char *tareauni,char *uniagrupaemba,char *uniagrupauni,char *monoformato,char *revisarcompleto,char *comentario,double reservado,vdress *res);
VDEXPORT int RESprocreservapedidoext(char *coddemanda,char *tipodemanda,long lindemanda,double cantidad,char *tareaconte,char *tareaemba,char *tareauniinv,char *tareaprepick,char *tareauni,char *uniagrupaemba,char *uniagrupauni,char *monoformato,char *revisarcompleto,char *comentario,double reservado,double diferconte,double diferemba,double diferuni,vdress *res);
VDEXPORT int RESprocreservastd(char *coddemanda,char *tipodemanda,long lindemanda,double cantidad,char *tarea,char *embalajescompletos,char *soloparciales,char *uniagrupae,char *monoformato,char *revisarcompleto,char *comentario,double reservado,vdress *res);
VDEXPORT char * RESdebug(vdress *res);
