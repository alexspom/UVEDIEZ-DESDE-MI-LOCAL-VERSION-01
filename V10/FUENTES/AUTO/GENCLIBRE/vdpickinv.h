// Fichero generado automaticamente a partir de VDPICKINV.DEF

VDEXPORT diccionario dpickinv;
#ifndef LUBIRESTOS
#define LUBIRESTOS 13
#endif

#ifndef LMITAREARESTOS
#define LMITAREARESTOS 33
#endif

#ifndef LMITAREAUNI
#define LMITAREAUNI 33
#endif

#ifndef LMITAREAEMBA
#define LMITAREAEMBA 33
#endif

#ifndef LMICODCONCERESTOS
#define LMICODCONCERESTOS 11
#endif

#ifndef LLECTURA
#define LLECTURA 257
#endif

#ifndef LTEXTO
#define LTEXTO 21
#endif

#ifndef LDIFERIDO
#define LDIFERIDO 2
#endif

#ifndef LCODUBIDEST
#define LCODUBIDEST 13
#endif

#ifndef LCODUBIRESERVA
#define LCODUBIRESERVA 13
#endif

#ifndef LCODUBICODCONCE
#define LCODUBICODCONCE 13
#endif

#ifndef LOBSERV
#define LOBSERV 1025
#endif

#ifndef LFORZARREENGANCHE
#define LFORZARREENGANCHE 2
#endif

#ifndef LEJECMOVEMBA
#define LEJECMOVEMBA 2
#endif

#ifndef LFORZARPICKINV
#define LFORZARPICKINV 2
#endif

#ifndef LMSJERROR
#define LMSJERROR 1025
#endif

#ifndef LNUMEROSERIE
#define LNUMEROSERIE 61
#endif

#ifndef LCODDIV
#define LCODDIV 5
#endif

#ifndef LCODPED
#define LCODPED 21
#endif

#ifndef LCODART
#define LCODART 41
#endif

#ifndef LCODMAT
#define LCODMAT 19
#endif

#ifndef LCODRECURSO
#define LCODRECURSO 11
#endif

#ifndef LTAREA
#define LTAREA 33
#endif

#ifndef LCODUBI
#define LCODUBI 13
#endif

#ifndef LCODOPE
#define LCODOPE 11
#endif

#ifndef LCODBULTO
#define LCODBULTO 19
#endif

#ifndef LCODLOT
#define LCODLOT 21
#endif

#ifndef LCODCONCE
#define LCODCONCE 11
#endif

#ifndef LCOMENTARIO
#define LCOMENTARIO 513
#endif

typedef struct {
        long    ret;
        long    nuevoestatus;
        long    stpdteequili;
        long    stpdtebulinv;
        long    stpickinv;
        long    factor;
        long    haypickinv;
        char    ubirestos[LUBIRESTOS];
        char    mitarearestos[LMITAREARESTOS];
        char    mitareauni[LMITAREAUNI];
        char    mitareaemba[LMITAREAEMBA];
        char    micodconcerestos[LMICODCONCERESTOS];
        long    status1;
        long    status2;
        char    lectura[LLECTURA];
        char    texto[LTEXTO];
        long    encendidos;
        char    diferido[LDIFERIDO];
        char    codubidest[LCODUBIDEST];
        char    codubireserva[LCODUBIRESERVA];
        char    codubicodconce[LCODUBICODCONCE];
        char    observ[LOBSERV];
        double  nuevocodmov;
        long    maxbultos;
        char    forzarreenganche[LFORZARREENGANCHE];
        char    ejecmovemba[LEJECMOVEMBA];
        char    forzarpickinv[LFORZARPICKINV];
        char    msjerror[LMSJERROR];
        long    statusbul;
        long    statusbpl;
        char    numeroserie[LNUMEROSERIE];
        long    codzona;
        long    status;
        long    idinfopick;
        char    coddiv[LCODDIV];
        long    anoped;
        char    codped[LCODPED];
        long    seqped;
        long    codserieprep;
        char    codart[LCODART];
        char    codmat[LCODMAT];
        char    codrecurso[LCODRECURSO];
        char    tarea[LTAREA];
        char    codubi[LCODUBI];
        char    codope[LCODOPE];
        char    codbulto[LCODBULTO];
        char    codlot[LCODLOT];
        double  uniemb;
        double  cantidad;
        char    codconce[LCODCONCE];
        char    comentario[LCOMENTARIO];
        long    ordenstk;
        long    codmov;
        long    seqlinea;
        double  cantpedida;
} vdpickinvs; 


VDEXPORT diccionario *PICKINVdamediccionario(void);
VDEXPORT int PICKINVbuscacdispencendidos(long codzona,long status,vdpickinvs *pickinv);
VDEXPORT int PICKINVnextcdispencendidos(vdpickinvs *pickinv);
VDEXPORT int PICKINVprocdametextozona(long idinfopick,long codzona,char *lectura,char *texto,vdpickinvs *pickinv);
VDEXPORT int PICKINVprocfinvolumetria(char *coddiv,long anoped,char *codped,long seqped,char *forzarpickinv,long haypickinv,long ret,vdpickinvs *pickinv);
VDEXPORT int PICKINVprocequilibraserie(long codserieprep,long status1,long status2,long stpdteequili,long stpdtebulinv,long stpickinv,long nuevoestatus,char *forzarreenganche,long ret,vdpickinvs *pickinv);
VDEXPORT int PICKINVprocreenganchapinv(long codserieprep,char *codart,char *mitareauni,long ret,vdpickinvs *pickinv);
VDEXPORT int PICKINVprocreenganchaemba(long codserieprep,char *codart,char *mitareaemba,char *ejecmovemba,long ret,vdpickinvs *pickinv);
VDEXPORT int PICKINVprocreenganchasprpinv(long codserieprep,long stpdteequili,long stpdtebulinv,long stpickinv,char *diferido,char *mitareauni,char *mitareaemba,long nuevoestatus,char *ejecmovemba,long ret,vdpickinvs *pickinv);
VDEXPORT int PICKINVproccreabultospinvconte(char *codmat,char *codrecurso,char *tarea,long status1,char *codubi,char *mitarearestos,char *micodconcerestos,long maxbultos,long ret,vdpickinvs *pickinv);
VDEXPORT int PICKINVbuscacopepickinv(char *codope,vdpickinvs *pickinv);
VDEXPORT int PICKINVnextcopepickinv(vdpickinvs *pickinv);
VDEXPORT int PICKINVprocregularizabpc(char *codbulto,char *codmat,char *codart,char *codlot,double uniemb,char *codubidest,char *codubireserva,double cantidad,char *codconce,char *codubicodconce,char *observ,char *comentario,long ret,vdpickinvs *pickinv);
VDEXPORT int PICKINVprocregularizastkpinv(char *codmat,long ordenstk,char *codconce,char *codubicodconce,double cantidad,char *observ,double nuevocodmov,char *codubidest,char *comentario,long ret,vdpickinvs *pickinv);
VDEXPORT int PICKINVprocpartemovpinv(long codmov,char *codubidest,char *codmat,double nuevocodmov,char *comentario,long ret,vdpickinvs *pickinv);
VDEXPORT int PICKINVproccreabpc(char *codmat,long status1,char *msjerror,vdpickinvs *pickinv);
VDEXPORT int PICKINVbuscalinsinprep(char *codped,char *coddiv,long seqped,char *codart,long statusbul,long statusbpl,long status,vdpickinvs *pickinv);
VDEXPORT int PICKINVnextlinsinprep(vdpickinvs *pickinv);
VDEXPORT int PICKINVbuscayaleidons(char *numeroserie,vdpickinvs *pickinv);
VDEXPORT int PICKINVnextyaleidons(vdpickinvs *pickinv);
VDEXPORT char * PICKINVdebug(vdpickinvs *pickinv);
