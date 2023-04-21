# Módulo   : VDIMPREASIGIMPRE.PAN
# Función  : Mantenimiento de Asignación de Informes a Impresoras
#
# Creación : 13-05-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
MANTENIMIENTO DE ASIGNACION DE INFORMES
Usuario        Ordenador      Tipo Imp.    Nombre de Documento                      Activo Ult. Modificación            
_32___________ _32___________ ____________ _256____________________________________   _    _32_________ ¿D-MM-Y.YY ________
|

TABLA=VDIMPREASIG
ORDERBY=ORDENADOR;

PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")



CAMPO=CODIMPRE,VIRTUAL,OCULTO
CAMPO=CODOPEASIG,TOOLTIP("Usuario que realiza la impresión"),TITULO("Usuario")
CAMPO=ORDENADOR,TOOLTIP("Ordenador desde el que se imprime. 'DEFECTO' para cualquiera"),TITULO("Ordenador")
CAMPO=TIPOIMPRE,TOOLTIP("Tipo de Impresión"),TITULO("Tipo Impr.")
CAMPO=DOCUMENTO,TOOLTIP("Documento que se imprime. 'DEFECTO' para cualquiera. No se indica ruta completa, se buscará en el Path"),TITULO("Documento")
CAMPO=ACTIVO,TOOLTIP("Si la asignación está activa actualmente"),POSTCHANGE=FEJECUTA(FVERIFICA("NS"),"CAMPO ACTIVO DEBE SER 'S' O 'N'"),TITULO("Activo"),WLONX=20
CAMPO=CODOPEMODIF,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,TOOLTIP("Fecha en la que se realizó la Ultima modificación")
CAMPO=HORAMODIF,TOOLTIP("Hora en la que se realizó la Ultima modificación")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;




