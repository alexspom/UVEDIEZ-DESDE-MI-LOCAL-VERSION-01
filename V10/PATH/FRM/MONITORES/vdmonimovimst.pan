# Módulo   : VDMONIMOVIMS.PAN
# Función  : Monitor de movimientos. Desglose de estados
#
# Creación : 04-08-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
ESTADO DEL MOVIMIENTO
 Estado Descripción          Total   
 @L@@@@ _30________________  @L@@@@@  
|

WLONX=330
SOLOQUERY
SELECT=SELECT MOV.STATUS, COUNT(DISTINCT MOV.CODMOV) TOTAL
         FROM VDMOVIM MOV
        WHERE MOV.STATUS < VDST.FMOVINTERFASAD;
GROUPBY=MOV.STATUS;        
ORDERBY=MOV.STATUS;
        

CAMPO=STATUS,NOENTER,TOOLTIP("Estado del movimiento"),POSTCHANGE=FDESIGNACION("+CSELDESSTATUS",""),TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripcion del estado"),TITULO("Descripción")
CAMPO=TOTAL,AUXILIAR,NOENTER,TOOLTIP("Numero total de movimientos en ese estado"),TITULO("Total")


CURSOR=CSELDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS = :STATUS AND TIPOSTATUS = 'MOV';

CURSOR=CSELRANALM SELECT '1,2,3,4' RANALM FROM DUAL;


