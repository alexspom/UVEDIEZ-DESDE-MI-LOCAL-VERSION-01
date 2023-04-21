# Módulo   : VDZONAGEOCAB.PAN
# Función  : Mantenimiento de cabeceras de zonas geográficas
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE ZONAS GEOGRAFICAS
Cod.Zona    Desc.Zona                           Extra                             Ultima modificación
_10________ _40________________________________ _255_____________________________ _32_________ ¿D-MM-Y.YY ________
|

TABLA=VDZONAGEOCAB

ORDERBY=CODZONAGEO;

PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

CAMPO=CODZONAGEO,NOUPDATE,TOOLTIP("Código de zona geográfica"),TITULO("Cod.Zona")
CAMPO=DESZONAGEO,TOOLTIP("Designación de la zona geográfica"),TITULO("Desc. Zona Geográfica")
CAMPO=VDEXTRA,TOOLTIP("Campo extra libre para el implantador"),TITULO("Extra")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


