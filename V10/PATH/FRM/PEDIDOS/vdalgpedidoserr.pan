###################################################################
#Módulo: VDALGPEDIDOSERR.PAN
#Funcionalidad : Listado de algoritmos asociados a procesos de pedidos.
#Autor: JCSR
#Fecha: 28-08-2008
###################################################################
# Histórico de cambios:
ALGORITMOS ASOCIADOS A LOS PROCESOS QUE ACTUAN SOBRE LOS PEDIDOS
 Algoritmo         Descripción                                                    
 _40_____________  _256______________________________________________________________________________________________________ 
|


TABLA=VDALGORITMOS

CAMPO=NOMBREALG, NOENTER,TOOLTIP("Es el nombre del algoritmo"),TITULO("Algoritmo")
CAMPO=PROCESO, VIRTUAL, OCULTO
CAMPO=DESALG, NOENTER, TOOLTIP("Descripción del algoritmo"),TITULO("Descripción")
