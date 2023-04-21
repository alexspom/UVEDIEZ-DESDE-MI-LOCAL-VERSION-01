###################################################################
#Módulo: VDSTERRYPROC.PAN
#Funcionalidad : Listado de estados posibles de error y procesos asociados
#Autor: JCSR
#Fecha: 28-08-2008
###################################################################
# Histórico de cambios:
PROCESOS QUE ACTUAN SOBRE LOS PEDIDOS
 Proceso asociado   Estado correcto del pedido
 _32_____________   @L@@@@ _30___________________________ 
|

SOLOQUERY

SELECT=SELECT PRO.PROCESO PROCESO, STA.STATUS, STA.DESSTATUS	 
         FROM VDPARAMALGPROC PAR, VDPROCESOS PRO, VDSTATUS STA
        WHERE PRO.GRUPOPROC='PEDIDOS' AND 
              PAR.NOMBREPARAM = 'ESTADO PEDIDO' AND 
              STA.DABSTATUS=VD.PIECE(PRO.PARAM,'#',PAR.POSICION) AND 
              PAR.FUNCION=PRO.FUNCIONPROC AND
              STA.TIPOSTATUS='PEC' AND   
              PAR.TIPOPROC='F' ;
ORDERBY=STA.STATUS;

CAMPO=PROCESO, AUXILIAR, TOOLTIP("Nombre del proceso"),TITULO("Proceso asociado")
CAMPO=STATUS, AUXILIAR, TOOLTIP ("Estado en el que el el proceso captura el pedido"),TITULO("Estado correcto del pedido")
CAMPO=DESSTATUS, AUXILIAR, TOOLTIP ("Descripción del estado en el que el el proceso captura el pedido")