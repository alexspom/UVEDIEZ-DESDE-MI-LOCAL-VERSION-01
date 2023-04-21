# Módulo   : VDVOLUMETRIA.PAN
# Función  : Mantenimiento de volumetrias
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE VOLUMETRIAS
Tipo                                          Máx Peso   Pi. LLe Ultima modificación              
__________ _40_______________________________ #L,####### @L@ @L@ _32________ ¿D-MM-Y.YY  ________
|

TABLA=VDVOLUMETRIA

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")




CAMPO=TIPOVOL,NOUPDATE,TOOLTIP("Tipo del contenedor"),TITULO("Tipo")
CAMPO=DESVOL,TOOLTIP("Designación del tipo de contenedor"),POSTCHANGE=FVALNOCERO("No puede dejar designación en blanco")
CAMPO=MAXPESO,TOOLTIP("Máximo peso de una caja de la volumetria"),TITULO("Máx Peso")
CAMPO=MAXPICOS,TOOLTIP("Máximo número de artículos diferentes en una caja"),TITULO("Picos"),WLONX=15
CAMPO=MAXLLENADO,TOOLTIP("Máximo coeficiente de llenado"),POSTCHANGE=FENRANGO("0-100","Debe estar en rango 0-100"),TITULO("Max%"),WLONX=15
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


