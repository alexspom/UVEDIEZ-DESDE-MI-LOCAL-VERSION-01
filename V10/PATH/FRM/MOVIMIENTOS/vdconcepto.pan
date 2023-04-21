# Módulo   : VDCONCEPTO.PAN
# Función  : Mantenimiento de concepto de movimientos
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE CONCEPTOS DE MOVIMIENTO
Concepto   Designación                       Privilegios                     T H T Ultima modificación
__________ _40______________________________ _1024__________________________ _ _ _ _32________ ¿D-MM-Y.YY  ________
|
TABLA=VDCONCEPTO
ORDERBY=CODCONCE;

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")


CAMPO=CODCONCE,NOUPDATE,TOOLTIP("Código interno del concepto"),TITULO("Concepto")
CAMPO=DESCONCE,TOOLTIP("Designación del concepto"),TITULO("Designación")
CAMPO=PRIVILEGIOS,TOOLTIP("Privilegios necesarios para crear este tipo de movimiento"),TITULO("Privilegios"),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=TIPOCONCE,TOOLTIP("Tipo del concepto, puede ser E(ntrada) S(alida) o I(nterno)"),POSTCHANGE=FVERIFICA("ESI","Debe introducir E(ntrada) S(alida) o I(nterno)"),TITULO("Tipo"),WLONX=20
CAMPO=SWTHOST,TOOLTIP("Indica si se ha de transmitir al host S(i) N(o) o I(mmediato)"),POSTCHANGE=FVERIFICA("SNIR","Debe introducir S(i) N(o) R(evisable) o I(mmediato)"),TITULO("Host"),WLONX=20
CAMPO=SWTTRAZA,TOOLTIP("Indica si es visible en las consultas de trazabilidad o no"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)"),TITULO("Traza"),WLONX=25
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CLISTAPRIV SELECT PRIVILEGIO, COMENTARIO FROM VDPRIVILEGIO  ORDER BY PRIVILEGIO;
