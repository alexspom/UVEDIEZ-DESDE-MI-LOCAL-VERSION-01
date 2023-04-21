// Fichero generado automaticamente a partir de VDPEDIDOAUX.DEF

VDEXPORT diccionario dpedido;
#ifndef LCODDIV
#define LCODDIV 5
#endif

#ifndef LCODPED
#define LCODPED 21
#endif

#ifndef LCOMENTARIO
#define LCOMENTARIO 513
#endif

#ifndef LTAREA
#define LTAREA 33
#endif

#ifndef LCODDEMANDA
#define LCODDEMANDA 21
#endif

typedef struct {
        long    nuevaversion;
        long    estadospr;
        long    estadosex;
        long    estadoini;
        long    estadofin;
        long    ret;
        char    coddiv[LCODDIV];
        long    anoped;
        char    codped[LCODPED];
        long    seqped;
        long    status;
        char    comentario[LCOMENTARIO];
        char    tarea[LTAREA];
        char    coddemanda[LCODDEMANDA];
} vdpedidos; 


VDEXPORT diccionario *PEDIDOdamediccionario(void);
VDEXPORT int PEDIDOselnuevaversion(char *coddiv,long anoped,char *codped,vdpedidos *pedido);
VDEXPORT int PEDIDOprocfinpedido(char *coddiv,long anoped,char *codped,long seqped,long status,long estadospr,long estadosex,long ret,vdpedidos *pedido);
VDEXPORT int PEDIDOproccreaversion(char *coddiv,long anoped,char *codped,long seqped,char *comentario,long ret,vdpedidos *pedido);
VDEXPORT int PEDIDObuscastatusprio(long status,vdpedidos *pedido);
VDEXPORT int PEDIDOnextstatusprio(vdpedidos *pedido);
VDEXPORT int PEDIDOprocdisponibilidad(char *tarea,vdpedidos *pedido);
VDEXPORT int PEDIDOprocliberamovpedido(char *coddemanda,long estadoini,long estadofin,long ret,vdpedidos *pedido);
VDEXPORT int PEDIDOprocactlineaspedido(char *coddiv,long anoped,char *codped,long seqped,long ret,vdpedidos *pedido);
VDEXPORT char * PEDIDOdebug(vdpedidos *pedido);
