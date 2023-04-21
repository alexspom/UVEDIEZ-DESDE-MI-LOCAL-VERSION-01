// Fichero generado automaticamente a partir de VDPEDIDORIGAUX.DEF

VDEXPORT diccionario dpori;
#ifndef LCODDIV
#define LCODDIV 17
#endif

#ifndef LCODPED
#define LCODPED 81
#endif

typedef struct {
        long    retorna;
        char    coddiv[LCODDIV];
        long    anoped;
        char    codped[LCODPED];
        long    seqped;
        long    seqlinea;
        long    status;
        long    secuencia;
} vdporis; 


VDEXPORT diccionario *PORIdamediccionario(void);
VDEXPORT int PORIprocvalpedidorigcab(char *coddiv,long anoped,char *codped,long seqped,long retorna,vdporis *pori);
VDEXPORT int PORIprocvalpedidoriglin(char *coddiv,long anoped,char *codped,long seqped,long seqlinea,long retorna,vdporis *pori);
VDEXPORT int PORIprocborrapelaanular(char *coddiv,long anoped,char *codped,long seqped,long status,vdporis *pori);
VDEXPORT int PORIprocinsertacabecera(char *coddiv,long anoped,char *codped,long seqped,long status,long retorna,vdporis *pori);
VDEXPORT int PORIprocinsertalinea(char *coddiv,long anoped,char *codped,long seqped,long seqlinea,long retorna,vdporis *pori);
VDEXPORT int PORIbuscasecuencia(char *coddiv,long anoped,char *codped,vdporis *pori);
VDEXPORT int PORInextsecuencia(vdporis *pori);
VDEXPORT char * PORIdebug(vdporis *pori);
