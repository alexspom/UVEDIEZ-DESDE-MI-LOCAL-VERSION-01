# M�dulo   : VDCAJASCLIENTE.PAN
# Funci�n  : PANTALLA PRUEBA
#
# Creaci�n : 04-11-2011
# Autor    : X
# Fichero generado por el Asistente de Generaci�n de Pantallas V10 
###########################################
# Hist�rico de cambios:
LOREN
SEQDEVOL  NUM CODART                 CODLOT                 CANTIDAD        STATU FECINS     
@L@@@@@@@ @L@ _40___________________ _40___________________ @L@@@@@@@@@@@@@ @L@@@ �D-MM-Y.YY 
|

TABLA=VDDEVOLLIN
SOLOQUERY
SELECT = SELECT  SEQDEVOL, NUMCAJA, CODART, CODLOT,  CANTIDAD,  STATUS, FECINS  FROM VDDEVOLLIN;
WHERE= STATUS=50;
ORDERBY= FECINS;

# LISTA DE CAMPOS DE LA PANTALLA
CAMPO=SEQDEVOL,TITULO("SEQDEVOL")
CAMPO=NUMCAJA,TITULO("NUMCAJA")
CAMPO=CODART,TITULO("CODART")
CAMPO=CODLOT,TITULO("CODLOT")
CAMPO=CANTIDAD,TITULO("CANTIDAD")
CAMPO=STATUS,TITULO("STATUS")
CAMPO=FECINS,TITULO("FECINS")

# PARTE PERSONALIZADA DE LA PANTALLA 