// Fichero generado automaticamente a partir de VDSERVICIOAUX.DEF

VDEXPORT diccionario dserviciosaux;
#ifndef LCODGRUPOSERV
#define LCODGRUPOSERV 33
#endif

#ifndef LCODSERVICIO
#define LCODSERVICIO 41
#endif

#ifndef LARRANQUE
#define LARRANQUE 2
#endif

#ifndef LCIERRE
#define LCIERRE 2
#endif

typedef struct {
        long    ret;
        char    codgruposerv[LCODGRUPOSERV];
        char    codservicio[LCODSERVICIO];
        char    arranque[LARRANQUE];
        char    cierre[LCIERRE];
} vdserviciosauxs; 


VDEXPORT diccionario *SERVICIOSAUXdamediccionario(void);
VDEXPORT int SERVICIOSAUXbuscaejecutableservicio(char *codgruposerv,char *codservicio,vdserviciosauxs *serviciosaux);
VDEXPORT int SERVICIOSAUXnextejecutableservicio(vdserviciosauxs *serviciosaux);
VDEXPORT int SERVICIOSAUXbuscaejecservplanif(char *codgruposerv,char *codservicio,char *arranque,char *cierre,vdserviciosauxs *serviciosaux);
VDEXPORT int SERVICIOSAUXnextejecservplanif(vdserviciosauxs *serviciosaux);
VDEXPORT int SERVICIOSAUXprocplanificagruposerv(char *codgruposerv,vdserviciosauxs *serviciosaux);
VDEXPORT int SERVICIOSAUXprocplanificaservicio(char *codgruposerv,char *codservicio,long ret,vdserviciosauxs *serviciosaux);
VDEXPORT char * SERVICIOSAUXdebug(vdserviciosauxs *serviciosaux);
