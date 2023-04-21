# Módulo   : VDSCANMIRROR.PAN
# Función  : MANTENIMIENTO DE ASOCIACIONES ENTRE ESCANERS
#
# Creación : 22-02-2010
# Autor    : FGS
# Fichero generado por el Asistente de Generación de Pantallas V10 
###########################################
# Histórico de cambios:
MANTENIMIENTO DE ASOCIACIONES ENTRE ESCANERS
ORD RED SCA RED SCA A CODOPEMODIF            FECMODIF   HORAMODI 
@L@ @L@ @L@ @L@ @L@ _ _32___________________ ¿D-MM-Y.YY ________ 
|

TABLA=VDSCANMIRROR
PREINSERT=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")
WLONX=700
ORDERBY=ORDEN;
REGPAG=30
CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

# LISTA DE CAMPOS DE LA PANTALLA
CAMPO=ORDEN,TITULO("ORDEN"),TOOLTIP("Orden de la asociación")
CAMPO=REDSCAN,TITULO("ESCANER MAESTRO"),TOOLTIP("Red de scanners del escaner maestro")
CAMPO=SCANNER,TOOLTIP("Numero de scanner en la red del escaner maestro"),WLONX=100
CAMPO=REDSCANM,TITULO("ESCANER ESPEJO"),TOOLTIP("Red de scanners del escaner espejo")
CAMPO=SCANNERM,TOOLTIP("Numero de scanner en la red del escaner espejo"),WLONX=100
CAMPO=ACTIVO,TITULO("ACT"),TOOLTIP("Si la asociacion esta activa"),WLONX=20
CAMPO=CODOPEMODIF,TITULO("Ultima modificación"),TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,TOOLTIP("Fecha en la que se efectuo la ultima modificacion")
CAMPO=HORAMODIF,TOOLTIP("Hora ultima modificacion")

# PARTE PERSONALIZADA DE LA PANTALLA 