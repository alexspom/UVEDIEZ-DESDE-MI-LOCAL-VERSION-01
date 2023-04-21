// Modulo generado automaticamente a partir de VDINFOMENUS.DEF

VDEXPORT diccionario dime;
#define IMENUMCOL	20
typedef struct {
        char    rowid[ROWIDLON];
        char    idmenu[LIDMENU];
        char    padremenu[LPADREMENU];
        long    ordenmenu;
        char    texto[LTEXTO];
        char    tipoaccion[LTIPOACCION];
        char    funcion[LFUNCION];
        char    param[LPARAM];
        long    ttick;
        char    fpresenta[LFPRESENTA];
        char    paramtick[LPARAMTICK];
        long    statusorigzona;
        long    statusorigdisp;
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
        long    ordendesde;
        long    ordenhasta;
    } vdinfomenuss;

// Prototipos de funciones definidas en VDINFOMENUS.C
VDEXPORT diccionario *IMEdamediccionario(void);
VDEXPORT int IMEselidmenu(char *idmenu,vdinfomenuss *ime);
VDEXPORT int IMEselsigpadre(char *padremenu,long ordendesde,vdinfomenuss *ime);
VDEXPORT int IMEselantpadre(char *padremenu,long ordenhasta,vdinfomenuss *ime);
VDEXPORT int IMEselstatusorigzona(long statusorigzona,vdinfomenuss *ime);
VDEXPORT int IMEselvdinfomenus(vdinfomenuss *ime);
VDEXPORT int IMEinsert(vdinfomenuss *ime,int error);
VDEXPORT char *IMElog(vdinfomenuss *ime);
char * IMEdebug(vdinfomenuss *ime);
