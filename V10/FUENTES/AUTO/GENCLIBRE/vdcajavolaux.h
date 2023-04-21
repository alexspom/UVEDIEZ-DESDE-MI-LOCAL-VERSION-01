// Fichero generado automaticamente a partir de VDCAJAVOLAUX.DEF

VDEXPORT diccionario dcajavol;
#ifndef LTIPOVOL
#define LTIPOVOL 11
#endif

#ifndef LTIPOCAJA
#define LTIPOCAJA 11
#endif

#ifndef LDESCAJA
#define LDESCAJA 41
#endif

#ifndef LVOLDINAMICA
#define LVOLDINAMICA 2
#endif

#ifndef LCODOPEMODIF
#define LCODOPEMODIF 33
#endif

#ifndef LHORAMODIF
#define LHORAMODIF 9
#endif

typedef struct {
        double  volumencaj;
        long    altura;
        char    tipovol[LTIPOVOL];
        char    tipocaja[LTIPOCAJA];
        char    descaja[LDESCAJA];
        long    largocaja;
        long    anchocaja;
        long    altocaja;
        long    pesocaja;
        long    pesorelleno;
        double  margenpeso;
        long    maxllenado;
        long    minllenado;
        long    maxpicos;
        long    maxpeso;
        char    voldinamica[LVOLDINAMICA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
} vdcajavols; 


VDEXPORT diccionario *CAJAVOLdamediccionario(void);
VDEXPORT int CAJAVOLbuscademayoramenor(char *tipovol,vdcajavols *cajavol);
VDEXPORT int CAJAVOLnextdemayoramenor(vdcajavols *cajavol);
VDEXPORT char * CAJAVOLdebug(vdcajavols *cajavol);
