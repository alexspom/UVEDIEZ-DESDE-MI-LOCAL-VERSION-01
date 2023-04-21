###################################################################
#Módulo: VDVERIF.FRM
#Funcionalidad : Verificación de bultos, ciega, semiciega y nula
#Autor: FGS      
#Fecha: 04-03-2009
###################################################################
# Histórico de cambios:
BEGINBLOQUE=VDVERIFCAB.PAN
  PREBLOQUE=FEJECUTA(FLIMPIALECTURAS,"ERROR EN TRIGER FLIMPIALECTURAS", FCOMMIT,"ERROR HACIENDO COMMIT")
  PREREGISTRO=PRESEHIJO
  POSX=1
  POSY=1
  CURSOR=CSELVALIDAR SELECT 'S' TVALIDAR FROM DUAL;
ENDBLOQUE
BEGINBLOQUE=VDVERIFLIN.PAN
  PADRE=VDVERIFCAB.PAN
  PREQUERY=QUERYHIJO
  POSX=1
  POSY=28
  REGPAG=20
ENDBLOQUE