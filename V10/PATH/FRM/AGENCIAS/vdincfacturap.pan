# Módulo   : VDFACPED.PAN
# Función  : Listado de Facturacion
#
# Creación : 27-08-2008
# Autor    : RGP
#
###########################################
# Histórico de cambios:
#
#
CONDICIONES DE BUSQUEDA
 División: ____    Año: @L@@   Pedido: _20____________
  
 ÏÄÄÄÄÄÄÄÄÄÄ RANGO DE FECHAS ÄÄÄÄÄÄÄÄÄÄË 
 ³ Inicio: ¿D-MM-YY.Y  Fin: ¿D-MM-YY.Y ³ 
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ 
 
 Agencia: _10_______
|
            
TABLA=DUAL
NOORAINS
NOQUERY
NOCOMMIT

REGPAG=1

CAMPO=BCODDIV,AUXILIAR
CAMPO=BANO,AUXILIAR
CAMPO=BPED,AUXILIAR
CAMPO=FECHAINICIO,AUXILIAR,TOOLTIP("Fecha inferior del intervalo. Formato DD-MM-AAAA."),COMBOX("CALENDARIO")
CAMPO=FECHAFIN,AUXILIAR,TOOLTIP("Fecha superior del intervalo. Formato DD-MM-AAAA."),COMBOX("CALENDARIO")
CAMPO=BAGEN,AUXILIAR


TECLA=F2,FPULSATECLAS("F6","F2")


ONLINE=         {F2} Ejecutar Consulta                 {F5} Borrar pantalla                  {Esc} Salir;