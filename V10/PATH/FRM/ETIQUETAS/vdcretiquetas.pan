# Módulo   : VDCRETIQUETAS.PAN
# Función  : Cola de impresión de etiquetas a imprimir
#
# Creación : 20-08-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
COLA DE IMPRESION DE ETIQUETAS A IMPRIMIR
Dato         Copia  Sid             Serial
_100________   _    ############### ############### 
|
TABLA=VDCRETIQUETAS

PREDELETE=FEJECUTA("CDELMATRICULA","ERROR EN CDELMATRICULA")

CURSOR=CDELMATRICULA DELETE VDCONTE WHERE CODMAT=:DATO AND TIPOCONTE='DUMMY' AND CODUBI IS NULL;

CAMPO=DATO,TOOLTIP("Dato que define la unidad que queremos imprimir (CODBULTO para bultos, CODUBI para ubicaciones...")
CAMPO=COPIA,TOOLTIP("Cantidad de etiquetas que queremos imprimir para ese dato.")
CAMPO=SID,TOOLTIP("Serial de la sesión que hace la inserción.")
CAMPO=SERIAL,TOOLTIP("")

