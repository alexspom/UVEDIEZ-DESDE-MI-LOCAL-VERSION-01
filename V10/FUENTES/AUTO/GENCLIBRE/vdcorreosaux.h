// Fichero generado automaticamente a partir de VDCORREOSAUX.DEF

VDEXPORT diccionario dcorreos;
#ifndef LORDENADOR
#define LORDENADOR 33
#endif

#ifndef LCUENTA
#define LCUENTA 33
#endif

#ifndef LPARA
#define LPARA 1001
#endif

#ifndef LCC
#define LCC 1001
#endif

#ifndef LCCO
#define LCCO 1001
#endif

#ifndef LASUNTO
#define LASUNTO 1001
#endif

#ifndef LCUERPO
#define LCUERPO 4001
#endif

#ifndef LDIRECTORIO
#define LDIRECTORIO 257
#endif

#ifndef LFICHERO
#define LFICHERO 257
#endif

#ifndef LMIME
#define LMIME 51
#endif

#ifndef LHORAPLANIF
#define LHORAPLANIF 9
#endif

#ifndef LCOMENTARIO
#define LCOMENTARIO 513
#endif

#ifndef LTIPOCORREO
#define LTIPOCORREO 13
#endif

typedef struct {
        long    ret;
        char    ordenador[LORDENADOR];
        char    cuenta[LCUENTA];
        char    para[LPARA];
        char    cc[LCC];
        char    cco[LCCO];
        char    asunto[LASUNTO];
        char    cuerpo[LCUERPO];
        char    directorio[LDIRECTORIO];
        char    fichero[LFICHERO];
        long    prioridad;
        char    mime[LMIME];
        long    fecplanif;
        char    horaplanif[LHORAPLANIF];
        char    comentario[LCOMENTARIO];
        char    tipocorreo[LTIPOCORREO];
        long    idmsg;
} vdcorreoss; 


VDEXPORT diccionario *CORREOSdamediccionario(void);
VDEXPORT int CORREOSproccorreodet(char *ordenador,char *cuenta,char *para,char *cc,char *cco,char *asunto,char *cuerpo,char *directorio,char *fichero,long prioridad,char *mime,long fecplanif,char *horaplanif,char *comentario,long ret,vdcorreoss *correos);
VDEXPORT int CORREOSproccorreo(char *tipocorreo,char *ordenador,char *asunto,char *cuerpo,char *directorio,char *fichero,long prioridad,char *mime,long fecplanif,char *horaplanif,char *comentario,long ret,vdcorreoss *correos);
VDEXPORT int CORREOSprocenviacorreo(long idmsg,char *comentario,long ret,vdcorreoss *correos);
VDEXPORT char * CORREOSdebug(vdcorreoss *correos);
