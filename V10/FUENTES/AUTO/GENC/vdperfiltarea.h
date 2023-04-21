// Modulo generado automaticamente a partir de VDPERFILTAREA.DEF

VDEXPORT diccionario dper;
#define PERNUMCOL	34
typedef struct {
        char    rowid[ROWIDLON];
        char    codperfil[LCODPERFIL];
        char    desperfil[LDESPERFIL];
        char    npantalla[LNPANTALLA];
        char    rantarea[LRANTAREA];
        char    ranareaori[LRANAREAORI];
        char    ranareadest[LRANAREADEST];
        char    codclasifubi[LCODCLASIFUBI];
        char    ranclaseubiori[LRANCLASEUBIORI];
        char    ranclaseubidest[LRANCLASEUBIDEST];
        char    codclasifart[LCODCLASIFART];
        char    ranclaseart[LRANCLASEART];
        char    rancodzonori[LRANCODZONORI];
        char    rancodzondest[LRANCODZONDEST];
        char    contenedores[LCONTENEDORES];
        char    embalajes[LEMBALAJES];
        char    unidadessueltas[LUNIDADESSUELTAS];
        char    privilegiostarea[LPRIVILEGIOSTAREA];
        long    minalt;
        long    maxalt;
        char    agrupaorig[LAGRUPAORIG];
        char    agrupadest[LAGRUPADEST];
        char    agrupaserie[LAGRUPASERIE];
        long    maxagrupa;
        char    formplanif[LFORMPLANIF];
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    maxpriomov;
        long    minpriomov;
        char    asignamov[LASIGNAMOV];
        char    funplanif[LFUNPLANIF];
    } vdperfiltareas;

// Prototipos de funciones definidas en VDPERFILTAREA.C
VDEXPORT diccionario *PERdamediccionario(void);
VDEXPORT int PERselcodperfil(char *codperfil,vdperfiltareas *per);
VDEXPORT int PERselvdperfiltarea(char *codperfil,vdperfiltareas *per);
VDEXPORT char *PERlog(vdperfiltareas *per);
char * PERdebug(vdperfiltareas *per);
