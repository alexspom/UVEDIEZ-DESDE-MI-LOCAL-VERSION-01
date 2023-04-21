// Fichero generado automaticamente a partir de VDASIGNAGEAUX.DEF

VDEXPORT diccionario dasiage;
#ifndef LCODDIVPED
#define LCODDIVPED 6
#endif

#ifndef LCODDIVART
#define LCODDIVART 6
#endif

#ifndef LCODDIV
#define LCODDIV 5
#endif

#ifndef LCODPED
#define LCODPED 21
#endif

#ifndef LAGEARTICULO
#define LAGEARTICULO 4001
#endif

#ifndef LTIPOPEDIDO
#define LTIPOPEDIDO 11
#endif

#ifndef LDP
#define LDP 11
#endif

#ifndef LCODCLIENTE
#define LCODCLIENTE 21
#endif

#ifndef LCODART
#define LCODART 41
#endif

#ifndef LCODCLASE
#define LCODCLASE 16
#endif

#ifndef LCODAGE
#define LCODAGE 11
#endif

#ifndef LCODPAIS
#define LCODPAIS 6
#endif

#ifndef LAGEPEDMISC
#define LAGEPEDMISC 4001
#endif

typedef struct {
        long    pesopedido;
        long    bultospedido;
        double  volpedido;
        char    coddivped[LCODDIVPED];
        char    coddivart[LCODDIVART];
        char    coddiv[LCODDIV];
        long    anoped;
        char    codped[LCODPED];
        long    seqped;
        char    agearticulo[LAGEARTICULO];
        char    tipopedido[LTIPOPEDIDO];
        char    dp[LDP];
        char    codcliente[LCODCLIENTE];
        long    urgencia;
        long    prioridad;
        char    codart[LCODART];
        char    codclase[LCODCLASE];
        char    codage[LCODAGE];
        char    codpais[LCODPAIS];
        char    agepedmisc[LAGEPEDMISC];
} vdasiages; 


VDEXPORT diccionario *ASIAGEdamediccionario(void);
VDEXPORT int ASIAGEseldatospedido(char *coddiv,long anoped,char *codped,long seqped,vdasiages *asiage);
VDEXPORT int ASIAGEselageartic(char *coddivped,char *tipopedido,char *dp,char *codcliente,long pesopedido,long bultospedido,double volpedido,long urgencia,long prioridad,char *codart,char *coddivart,char *codclase,char *codage,char *codpais,vdasiages *asiage);
VDEXPORT int ASIAGEselagepedmisc(char *coddivped,char *tipopedido,char *dp,char *codcliente,long pesopedido,long bultospedido,double volpedido,long urgencia,long prioridad,char *codage,char *codpais,vdasiages *asiage);
VDEXPORT char * ASIAGEdebug(vdasiages *asiage);
