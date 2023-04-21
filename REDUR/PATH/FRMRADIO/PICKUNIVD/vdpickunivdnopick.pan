# Módulo   : VDPICKUNIVDNOPICK.PAN
# Función  : Formulario de recogida de bultos de unidades.
#            Pantalla de situacion sin picking pendiente.
#
# Creación : 13-05-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
PICKING DE UNIDADES
_10_______ _10_______

  NO HAY PICKING
  PENDIENTE DEL
  BULTO 
  _18_______________  
  
  LLEVE MATRICULA
  ____________________
  A MESA DE FALTAS

   PULSE ENTER _
|

POSTQUERY=FEJECUTA(FPOSICIONABLOQUE("VDPICKUNIVDMATN14.PAN"),"\n\n ERROR AL CARGAR \nFORMULARIO POR DEFECTO")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODBULTO,VIRTUAL,NOENTER
CAMPO=MATCAJA,VIRTUAL,NOENTER
CAMPO=PULSACION
