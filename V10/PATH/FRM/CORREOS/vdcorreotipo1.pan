# Módulo   : VDCORREOTIPO1.PAN
# Función  : Consulta de Tipos de Correos
#
# Creación : 04-07-2008
# Autor    : FGS
###########################################
Consulta de Tipos de Correos
Tipo de Correo                              Pdtes Err   Anul
____________ _40___________________________ @L@@@ @L@@@ @L@@@ 
|
TABLA=VDCORRTIPOS

POSTQUERY=FEJECUTA("CSELDATOS","ERROR OBTENIENDO DATOS DE LOS CORREOS DEL TIPO :TIPOCORREO")

CAMPO=TIPOCORREO,TOOLTIP("Tipo de Correo"),TITULO("Tipo de Correo")
CAMPO=DESTIPOCORREO,TOOLTIP("Descripción del tipo de Correo")
CAMPO=PDTES,AUXILIAR,NOENTER,TOOLTIP("Correos de este tipo pdtes de enviar"),TITULO("Pdtes"), WLONX=20
CAMPO=ERR,AUXILIAR,NOENTER,TOOLTIP("Correos de este tipo en error"),TITULO("Err")
CAMPO=ANUL,AUXILIAR,NOENTER,TOOLTIP("Correos de este tipo anulados  en el día de hoy"),TITULO("Anul")

CURSOR=CSELDATOS SELECT SUM(DECODE(STATUS,VDST.FCSPPENDIENTE,1,0)) PDTES,
                        SUM(DECODE(STATUS,VDST.FCSPESPCOMUNIC,1,(-1)*VDST.FCSPPENDIENTE,1,0)) ERR,
                        SUM(DECODE(STATUS,VDST.FCSPANULADA,1,0)) ANUL
                   FROM VDCORRSMTP 
                   WHERE TIPOCORREO=:TIPOCORREO AND 
                         STATUS IN (VDST.FCSPPENDIENTE, VDST.FCSPESPCOMUNIC,VDST.FCSPANULADA, (-1)*VDST.FCSPPENDIENTE); 


