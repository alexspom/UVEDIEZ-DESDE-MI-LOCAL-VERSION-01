#MOdulo: VDTARIFAASIGDIVISR.FRM
#Funcionalidad : Asignacin Rapida de Divisiones a Tarifas
#Autor: Sergio Rojo     
#Fecha: 18-04-2008
#* Copyright @2007 V10, S.L.                                     *
#*****************************************************************
#* HistOrico de cambios
#* ====================
#
#*****************************************************************
#
#
#*****************************************************************
BEGINBLOQUE=VDTARIFAASIGRAP1.PAN
  PREREGISTRO=PRESEHIJO
  REGPAG=4
ENDBLOQUE
BEGINBLOQUE=VDTARIFAASIGRAP2.PAN
  PREQUERY=QUERYHIJO
  PREREGISTRO=PRESEHIJO
  PADRE=VDTARIFAASIGRAP1.PAN
  REGPAG=4
  POSY=9
ENDBLOQUE  
BEGINBLOQUE=VDTARIFAASIGRAP3V.PAN
  PREQUERY=QUERYHIJO
  PADRE=VDTARIFAASIGRAP2.PAN
  REGPAG=20
  POSY=16
ENDBLOQUE  
