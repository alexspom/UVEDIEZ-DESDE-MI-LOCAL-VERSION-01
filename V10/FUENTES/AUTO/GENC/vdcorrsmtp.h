// Modulo generado automaticamente a partir de VDCORRSMTP.DEF

VDEXPORT diccionario dsmtp;
#define SMTPNUMCOL	31
#define LCOMEN 1026
typedef struct {
        char    rowid[ROWIDLON];
        long    idmsg;
        char    ordenador[LORDENADOR];
        char    tipocorreo[LTIPOCORREO];
        char    cuenta[LCUENTA];
        char    para[LPARA];
        char    cc[LCC];
        char    cco[LCCO];
        char    asunto[LASUNTO];
        char    cuerpo[LCUERPO];
        char    adjunto[LADJUNTO];
        long    prioridad;
        char    mime[LMIME];
        char    directorio[LDIRECTORIO];
        char    fichero[LFICHERO];
        long    status;
        char    codopeins[LCODOPEINS];
        long    fecins;
        char    horains[LHORAINS];
        char    moduloins[LMODULOINS];
        char    accionins[LACCIONINS];
        long    fecplanif;
        char    horaplanif[LHORAPLANIF];
        long    fecenvio;
        char    horaenvio[LHORAENVIO];
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        char    comen[LCOMEN];
    } vdcorrsmtps;

// Prototipos de funciones definidas en VDCORRSMTP.C
VDEXPORT diccionario *SMTPdamediccionario(void);
VDEXPORT int SMTPbuscastatus(long status,vdcorrsmtps *smtp);
VDEXPORT int SMTPnextstatus(vdcorrsmtps *smtp);
VDEXPORT int SMTPselvdcorrsmtp(long idmsg,vdcorrsmtps *smtp);
VDEXPORT int SMTPactualizaenviado(vdcorrsmtps *smtp,int error);
VDEXPORT char *SMTPlog(vdcorrsmtps *smtp);
char * SMTPdebug(vdcorrsmtps *smtp);
