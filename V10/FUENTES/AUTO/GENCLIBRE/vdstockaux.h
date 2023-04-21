// Fichero generado automaticamente a partir de VDSTOCKAUX.DEF

VDEXPORT diccionario dstkaux;
#ifndef LCODMATESPERADO
#define LCODMATESPERADO 20
#endif

#ifndef LCODMATLEIDO
#define LCODMATLEIDO 20
#endif

#ifndef LCODCONCEENTRADA
#define LCODCONCEENTRADA 11
#endif

#ifndef LCODCONCESALIDA
#define LCODCONCESALIDA 11
#endif

#ifndef LFUENTE
#define LFUENTE 13
#endif

#ifndef LSUMIDERO
#define LSUMIDERO 13
#endif

#ifndef LOBSERV
#define LOBSERV 4097
#endif

#ifndef LMSJERROR
#define LMSJERROR 1025
#endif

#ifndef LLIMPIAR
#define LLIMPIAR 2
#endif

#ifndef LCODRECURSO
#define LCODRECURSO 33
#endif

#ifndef LPATRONBLOQUEOSORI
#define LPATRONBLOQUEOSORI 21
#endif

#ifndef LCODMAT
#define LCODMAT 19
#endif

#ifndef LUNICAPAC
#define LUNICAPAC 2
#endif

#ifndef LCODART
#define LCODART 41
#endif

#ifndef LCODLOT
#define LCODLOT 21
#endif

#ifndef LBLOQUEOS
#define LBLOQUEOS 11
#endif

#ifndef LCODUBI
#define LCODUBI 13
#endif

#ifndef LNUMEROSERIE
#define LNUMEROSERIE 61
#endif

#ifndef LBULTO
#define LBULTO 19
#endif

#ifndef LMARCASTK
#define LMARCASTK 61
#endif

#ifndef LCODRECEP
#define LCODRECEP 21
#endif

#ifndef LTIPOEMBA
#define LTIPOEMBA 11
#endif

#ifndef LCODCONCE
#define LCODCONCE 11
#endif

#ifndef LCOMENTARIO
#define LCOMENTARIO 513
#endif

#ifndef LCODOPEMODIF
#define LCODOPEMODIF 33
#endif

typedef struct {
        long    statusaux;
        long    ret;
        char    codmatesperado[LCODMATESPERADO];
        char    codmatleido[LCODMATLEIDO];
        char    codconceentrada[LCODCONCEENTRADA];
        char    codconcesalida[LCODCONCESALIDA];
        char    fuente[LFUENTE];
        char    sumidero[LSUMIDERO];
        char    observ[LOBSERV];
        char    msjerror[LMSJERROR];
        double  codmoventrada;
        double  codmovsalida;
        double  codmovinterno;
        long    nuevoordenstk;
        double  diff;
        long    fuerzastock;
        double  cantidad;
        char    limpiar[LLIMPIAR];
        char    codrecurso[LCODRECURSO];
        long    codzona;
        long    totalnsl;
        char    patronbloqueosori[LPATRONBLOQUEOSORI];
        char    codmat[LCODMAT];
        char    unicapac[LUNICAPAC];
        char    codart[LCODART];
        char    codlot[LCODLOT];
        double  uniemb;
        char    bloqueos[LBLOQUEOS];
        char    codubi[LCODUBI];
        long    codmov;
        long    ordenstk;
        char    numeroserie[LNUMEROSERIE];
        char    bulto[LBULTO];
        char    marcastk[LMARCASTK];
        char    codrecep[LCODRECEP];
        long    embcont;
        char    tipoemba[LTIPOEMBA];
        double  preciouni;
        double  pesouni;
        char    codconce[LCODCONCE];
        char    comentario[LCOMENTARIO];
        char    codopemodif[LCODOPEMODIF];
} vdstkauxs; 


VDEXPORT diccionario *STKAUXdamediccionario(void);
VDEXPORT int STKAUXbuscareservadoencodmat(char *codmat,char *unicapac,char *codart,char *codlot,double uniemb,char *bloqueos,vdstkauxs *stkaux);
VDEXPORT int STKAUXnextreservadoencodmat(vdstkauxs *stkaux);
VDEXPORT int STKAUXbuscadisponibleencodmat(char *codmat,char *unicapac,char *codart,char *codlot,double uniemb,char *bloqueos,vdstkauxs *stkaux);
VDEXPORT int STKAUXnextdisponibleencodmat(vdstkauxs *stkaux);
VDEXPORT int STKAUXbuscastockencodmat(char *codmat,char *unicapac,char *codart,char *codlot,double uniemb,char *bloqueos,vdstkauxs *stkaux);
VDEXPORT int STKAUXnextstockencodmat(vdstkauxs *stkaux);
VDEXPORT int STKAUXbuscastockencodubi(char *codubi,char *unicapac,char *codart,char *codlot,double uniemb,char *bloqueos,vdstkauxs *stkaux);
VDEXPORT int STKAUXnextstockencodubi(vdstkauxs *stkaux);
VDEXPORT int STKAUXbuscastocklote(char *codart,char *codlot,char *patronbloqueosori,vdstkauxs *stkaux);
VDEXPORT int STKAUXnextstocklote(vdstkauxs *stkaux);
VDEXPORT int STKAUXprocactstockori(long ret,long codmov,long statusaux,vdstkauxs *stkaux);
VDEXPORT int STKAUXprocactstockdest(long ret,long codmov,long statusaux,vdstkauxs *stkaux);
VDEXPORT int STKAUXprocrecogestk(long codmov,long statusaux,long ret,char *codrecurso,vdstkauxs *stkaux);
VDEXPORT int STKAUXprocdepositastk(long codmov,long statusaux,long ret,vdstkauxs *stkaux);
VDEXPORT int STKAUXproccongela(long ret,long codmov,char *limpiar,vdstkauxs *stkaux);
VDEXPORT int STKAUXprocdescongela(long codmov,vdstkauxs *stkaux);
VDEXPORT int STKAUXproctransformastk(char *codmat,long ordenstk,char *codconceentrada,char *fuente,char *codconcesalida,char *sumidero,char *observ,char *codart,char *codlot,char *numeroserie,char *bulto,char *marcastk,char *codrecep,double uniemb,long embcont,char *tipoemba,double preciouni,double pesouni,char *bloqueos,char *msjerror,double codmoventrada,double codmovsalida,double codmovinterno,long ret,vdstkauxs *stkaux);
VDEXPORT int STKAUXprocregularizastk(char *codmat,long ordenstk,char *codconce,char *codubi,double diff,char *observ,char *msjerror,long codmov,long ret,vdstkauxs *stkaux);
VDEXPORT int STKAUXprocdividetk(char *codmat,long ordenstk,char *codconceentrada,char *fuente,char *codconcesalida,char *sumidero,double diff,char *observ,char *msjerror,double codmoventrada,double codmovsalida,long nuevoordenstk,long ret,vdstkauxs *stkaux);
VDEXPORT int STKAUXproccreastk(char *codmat,long ordenstk,char *codart,char *codlot,char *numeroserie,char *bulto,char *marcastk,char *codrecep,double uniemb,long embcont,char *tipoemba,double preciouni,double pesouni,char *bloqueos,double cantidad,char *codconceentrada,char *fuente,char *observ,char *msjerror,double codmoventrada,long fuerzastock,long ret,vdstkauxs *stkaux);
VDEXPORT int STKAUXprocbloqueosstkbulto(char *bulto,char *codart,char *codlot,char *codconceentrada,char *fuente,char *codconcesalida,char *sumidero,char *patronbloqueosori,char *bloqueos,char *observ,double cantidad,char *comentario,long ret,vdstkauxs *stkaux);
VDEXPORT int STKAUXprocbloqueosstkrecep(char *codrecep,char *codart,char *codlot,char *codconceentrada,char *fuente,char *codconcesalida,char *sumidero,char *patronbloqueosori,char *bloqueos,char *observ,double cantidad,char *comentario,long ret,vdstkauxs *stkaux);
VDEXPORT int STKAUXprocactstkns(char *codmat,char *numeroserie,char *codopemodif,char *codrecurso,long codzona,vdstkauxs *stkaux);
VDEXPORT int STKAUXprocdelnumleidos(char *codmat,vdstkauxs *stkaux);
VDEXPORT int STKAUXproclimpiansstock(char *codmat,vdstkauxs *stkaux);
VDEXPORT int STKAUXprocordenastockconns(char *codmat,long totalnsl,vdstkauxs *stkaux);
VDEXPORT char * STKAUXdebug(vdstkauxs *stkaux);

//Codigo incluido explicitamente en el DEF
 VDEXPORT int STKAUXactstockori(void *ptr,int statusfinal);
 VDEXPORT int STKAUXactstockdest(void *ptr,int statusfinal);
 
