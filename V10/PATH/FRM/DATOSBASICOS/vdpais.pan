# Módulo   : VDPAIS.PAN
# Función  : Mantenimiento de paises
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
TABLA DE PAISES
Cod.País País                          C2  C3  UE   Extra         Ultima modificación
________ _____________________________ _2_ _3__ _1_  _256_________ _32__________ ¿D-MM-Y.YY _8________
|

TABLA=VDPAIS
ORDERBY=DESPAIS;

PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

CAMPO=CODPAIS,NOUPDATE,TOOLTIP("Código ISO del país"),TITULO("Cod.País")
CAMPO=DESPAIS,MIXED,TOOLTIP("Designación del pais"),POSTCHANGE=FVALNOCERO("Debe introducir designación del pais"), TITULO("País")
CAMPO=CODPAIS2,TITULO("C2"),TOOLTIP("Codigo iso 2 del pais")
CAMPO=CODPAIS3,TITULO("C3"),TOOLTIP("Codigo iso3 del pais")
CAMPO=UE,TITULO("UE"),TOOLTIP("Indica si pertenece a la UE")
CAMPO=VDEXTRA,TITULO("Extra"),TOOLTIP("Campo extra")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


