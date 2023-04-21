// Fichero generado automaticamente a partir de VDBULTOAUX.DEF

VDEXPORT diccionario dbulto;
#ifndef LACTPELIN
#define LACTPELIN 3
#endif

#ifndef LMIFLUJOC
#define LMIFLUJOC 257
#endif

#ifndef LMIFLUJOE
#define LMIFLUJOE 257
#endif

#ifndef LMIFLUJOU
#define LMIFLUJOU 257
#endif

#ifndef LTIPO
#define LTIPO 3
#endif

#ifndef LMIDIGITOEAN
#define LMIDIGITOEAN 3
#endif

#ifndef LCALCULOPESO
#define LCALCULOPESO 3
#endif

#ifndef LCALCULOVOLUMEN
#define LCALCULOVOLUMEN 3
#endif

#ifndef LVERIF
#define LVERIF 3
#endif

#ifndef LMIFLUJOPREPICK
#define LMIFLUJOPREPICK 257
#endif

#ifndef LMIFLUJOPICKIV
#define LMIFLUJOPICKIV 257
#endif

#ifndef LTAREACONTE
#define LTAREACONTE 34
#endif

#ifndef LTAREAEMBA
#define LTAREAEMBA 34
#endif

#ifndef LTAREAUNI
#define LTAREAUNI 34
#endif

#ifndef LUNIAGRUPAEMBA
#define LUNIAGRUPAEMBA 3
#endif

#ifndef LUNIAGRUPAUNI
#define LUNIAGRUPAUNI 3
#endif

#ifndef LMONOFORMATO
#define LMONOFORMATO 3
#endif

#ifndef LREVISARCOMPLETO
#define LREVISARCOMPLETO 3
#endif

#ifndef LCODMATPI
#define LCODMATPI 19
#endif

#ifndef LCODBULTO
#define LCODBULTO 19
#endif

#ifndef LTAREA
#define LTAREA 33
#endif

#ifndef LCODDIV
#define LCODDIV 5
#endif

#ifndef LSECBULTOTMP
#define LSECBULTOTMP 4001
#endif

#ifndef LCODPED
#define LCODPED 21
#endif

#ifndef LCODART
#define LCODART 41
#endif

#ifndef LCODLOT
#define LCODLOT 21
#endif

#ifndef LTIPOBULTO
#define LTIPOBULTO 2
#endif

#ifndef LCODSEMAFORO
#define LCODSEMAFORO 21
#endif

#ifndef LCODCONCE
#define LCODCONCE 11
#endif

#ifndef LCODUBI
#define LCODUBI 13
#endif

#ifndef LCODMAT
#define LCODMAT 19
#endif

typedef struct {
        long    estadoped;
        char    actpelin[LACTPELIN];
        long    ret;
        char    miflujoc[LMIFLUJOC];
        char    miflujoe[LMIFLUJOE];
        char    miflujou[LMIFLUJOU];
        char    tipo[LTIPO];
        char    midigitoean[LMIDIGITOEAN];
        char    calculopeso[LCALCULOPESO];
        char    calculovolumen[LCALCULOVOLUMEN];
        long    lineabulto;
        long    diferencia;
        long    inicio;
        long    fin;
        char    verif[LVERIF];
        long    cantaregularizar;
        char    miflujoprepick[LMIFLUJOPREPICK];
        char    miflujopickiv[LMIFLUJOPICKIV];
        double  cantrotura;
        double  cantasustituir;
        char    tareaconte[LTAREACONTE];
        char    tareaemba[LTAREAEMBA];
        char    tareauni[LTAREAUNI];
        long    statusconte;
        long    statusemba;
        long    statusuni;
        long    statusnuevouni;
        char    uniagrupaemba[LUNIAGRUPAEMBA];
        char    uniagrupauni[LUNIAGRUPAUNI];
        char    monoformato[LMONOFORMATO];
        char    revisarcompleto[LREVISARCOMPLETO];
        long    stnuevomov;
        long    ejecmov;
        char    codmatpi[LCODMATPI];
        long    codmovout;
        char    codbulto[LCODBULTO];
        long    status;
        char    tarea[LTAREA];
        char    coddiv[LCODDIV];
        char    secbultotmp[LSECBULTOTMP];
        long    secuencia;
        long    anoped;
        char    codped[LCODPED];
        long    seqped;
        long    seqlinea;
        char    codart[LCODART];
        long    codmov;
        char    codlot[LCODLOT];
        double  cantpedida;
        long    ultimobulto;
        char    tipobulto[LTIPOBULTO];
        char    codsemaforo[LCODSEMAFORO];
        char    codconce[LCODCONCE];
        char    codubi[LCODUBI];
        char    codmat[LCODMAT];
        long    ordenstk;
} vdbultos; 


VDEXPORT diccionario *BULTOdamediccionario(void);
VDEXPORT int BULTOprocfinbulto(char *codbulto,long status,long estadoped,char *actpelin,long ret,vdbultos *bulto);
VDEXPORT int BULTOproctipobulto(char *tarea,char *miflujoc,char *miflujoe,char *miflujoprepick,char *miflujopickiv,char *miflujou,char *tipo,vdbultos *bulto);
VDEXPORT int BULTObuscacodbulto(char *midigitoean,char *coddiv,vdbultos *bulto);
VDEXPORT int BULTOnextcodbulto(vdbultos *bulto);
VDEXPORT int BULTObuscasecbultotmp(char *midigitoean,vdbultos *bulto);
VDEXPORT int BULTOnextsecbultotmp(vdbultos *bulto);
VDEXPORT int BULTObuscasecuencia(char *codbulto,vdbultos *bulto);
VDEXPORT int BULTOnextsecuencia(vdbultos *bulto);
VDEXPORT int BULTOproccreabultos(char *coddiv,long anoped,char *codped,long seqped,char *miflujoc,char *miflujoe,char *miflujoprepick,char *miflujopickiv,char *miflujou,char *midigitoean,long ret,vdbultos *bulto);
VDEXPORT int BULTOprocborracabeceraylineas(char *codbulto,long ret,vdbultos *bulto);
VDEXPORT int BULTOprocvolumetriacajasycnt(char *codbulto,long ret,vdbultos *bulto);
VDEXPORT int BULTOprocrenumerabultos(char *coddiv,long anoped,char *codped,long seqped,long diferencia,long inicio,long fin,long ret,vdbultos *bulto);
VDEXPORT int BULTObuscalineabulto(char *codbulto,vdbultos *bulto);
VDEXPORT int BULTOnextlineabulto(vdbultos *bulto);
VDEXPORT int BULTObuscabultolinordenmovim(char *codbulto,vdbultos *bulto);
VDEXPORT int BULTOnextbultolinordenmovim(vdbultos *bulto);
VDEXPORT int BULTObuscaultimobulto(char *coddiv,long anoped,char *codped,long seqped,char *tipobulto,vdbultos *bulto);
VDEXPORT int BULTOnextultimobulto(vdbultos *bulto);
VDEXPORT int BULTOselchequeavolumetria(char *coddiv,long anoped,char *codped,long seqped,vdbultos *bulto);
VDEXPORT int BULTObuscadameultbulto(char *codbulto,vdbultos *bulto);
VDEXPORT int BULTOnextdameultbulto(vdbultos *bulto);
VDEXPORT int BULTOprocanulacantpendservir(char *codbulto,long seqlinea,long cantaregularizar,long ret,vdbultos *bulto);
VDEXPORT int BULTOprocroturabulto(char *codbulto,long seqlinea,double cantrotura,double cantasustituir,char *tareaconte,char *tareaemba,char *tareauni,long statusconte,long statusemba,long statusuni,long statusnuevouni,char *uniagrupaemba,char *uniagrupauni,char *monoformato,char *revisarcompleto,char *codsemaforo,char *codconce,char *codubi,long stnuevomov,long ret,vdbultos *bulto);
VDEXPORT int BULTOprocroturabultostk(char *codbulto,long seqlinea,double cantrotura,double cantasustituir,char *codmat,long ordenstk,char *tareaconte,char *tareaemba,char *tareauni,char *codconce,char *codubi,long ret,vdbultos *bulto);
VDEXPORT int BULTOproccambioreserva(char *codbulto,long seqlinea,double cantrotura,char *codmat,long ordenstk,char *codconce,char *codubi,long ret,long ejecmov,long codmovout,vdbultos *bulto);
VDEXPORT int BULTOproccambioreservapi(char *codbulto,char *codmatpi,double cantrotura,char *codmat,long ordenstk,char *codconce,char *codubi,long ret,long codmovout,vdbultos *bulto);
VDEXPORT char * BULTOdebug(vdbultos *bulto);
