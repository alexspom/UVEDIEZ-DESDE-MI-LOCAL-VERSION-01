# M�dulo   : VDPICKUNIPDRESTOCK.PAN
# Funci�n  : Muestra mensaje de que no se puede servir el bulto al completo,
#            al tener movtos en estado pdtestock.
#
# Creaci�n : 14-08-2008
# Autor    : FGS
###########################################
# Hist�rico de cambios:
#
PICKING POR TERMINAL
_10_______ _10_______

BULTO 
____________________
  
PENDIENTE DE STOCK
  
   PULSE ENTER _
|

POSTQUERY=FEJECUTA(FPOSICIONABLOQUE("VDPICKUNIBUL.PAN"),"ERROR AL CARGAR \nFORMULARIO POR DEFECTO")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODBULTO,VIRTUAL,NOENTER
CAMPO=PULSACION