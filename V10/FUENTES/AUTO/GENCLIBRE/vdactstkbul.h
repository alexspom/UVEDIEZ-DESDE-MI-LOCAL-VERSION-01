// Fichero generado automaticamente a partir de VDACTSTKBUL.DEF

VDEXPORT diccionario dstkbul;
typedef struct {
        long    ret;
        long    codmov;
        long    status;
} vdstkbuls; 


VDEXPORT diccionario *STKBULdamediccionario(void);
VDEXPORT int STKBULprocactstkbul(long codmov,long status,long ret,vdstkbuls *stkbul);
VDEXPORT char * STKBULdebug(vdstkbuls *stkbul);
