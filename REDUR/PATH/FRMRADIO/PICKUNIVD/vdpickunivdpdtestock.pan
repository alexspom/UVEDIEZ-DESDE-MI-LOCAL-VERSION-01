# Módulo   : VDPICKUNIVDPDRESTOCK.PAN
# Función  : Muestra mensaje de que no se puede servir el bulto al completo,
#            al tener movtos en estado pdtestock.
#
# Creación : 14-08-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
#
PICKING DE UNIDADES
_10_______ _10_______

BULTO 
____________________
  
PENDIENTE DE STOCK
  
   PULSE ENTER _
|

POSTQUERY=FEJECUTA(FPOSICIONABLOQUE("VDPICKUNIVDMAT.PAN"),"\n\n ERROR AL CARGAR \nFORMULARIO POR DEFECTO")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODBULTO,VIRTUAL,NOENTER
CAMPO=PULSACION