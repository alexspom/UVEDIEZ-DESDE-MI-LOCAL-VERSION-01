##############################################################################
#  Módulo  : VDIMPBULBCE.FRM                                                 #
#  Función :                                                                 #
#                                                                            #
#  Autor : FPD                                                               #
#  Fecha : 14-10-14                                                          #
#  Revisador por  :                                                          #
#  Fecha revisión :                                                          #
##############################################################################

CAMPO=ALTURA,AUXILIAR,OCULTO,"_"     
PREFORM=FEJECUTA("CSELDEF","")                                        
BEGINBLOQUE=VDIMPBULBCE1.PAN
  TITULO=ASIGNACION DE CAJAS COMPLETAS ALMACEN
  PREREGISTRO=PRESEHIJO
  NODELETE
  NOINSERT
  POSX=10
  POSY=3
  CURSOR=CSELDEF SELECT 'N' ALTURA FROM DUAL;
ENDBLOQUE
BEGINBLOQUE=VDIMPBULBCE2.PAN
  PADRE=VDIMPBULBCE1.PAN
  PREREGISTRO=PRESEHIJO
  POSX=2
  POSY=8
  REGPAG=33
ENDBLOQUE
POSTCOMMIT=LIMPIAFORM
