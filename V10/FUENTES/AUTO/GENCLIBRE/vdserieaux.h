// Fichero generado automaticamente a partir de VDSERIEAUX.DEF

VDEXPORT diccionario dseries;
#ifndef LCODCONCE
#define LCODCONCE 11
#endif

#ifndef LCODUBIDEST
#define LCODUBIDEST 13
#endif

#ifndef LCOMENTARIO
#define LCOMENTARIO 513
#endif

typedef struct {
        long    ret;
        long    stpeclimite;
        long    stpecexpedido;
        long    codserieexp;
        long    status;
        char    codconce[LCODCONCE];
        char    codubidest[LCODUBIDEST];
        char    comentario[LCOMENTARIO];
} vdseriess; 


VDEXPORT diccionario *SERIESdamediccionario(void);
VDEXPORT int SERIESprocexpideserie(long codserieexp,long status,long stpeclimite,long stpecexpedido,char *codconce,char *codubidest,char *comentario,long ret,vdseriess *series);
VDEXPORT char * SERIESdebug(vdseriess *series);
