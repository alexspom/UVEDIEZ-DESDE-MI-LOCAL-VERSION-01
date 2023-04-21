# Módulo   : VDINFOBULTOZONAS.PAN
# Función  : Mantenimiento de bultos por zonas
#
# Creación : 21-05-2008
# Autor    : Maite González
###########################################
BULTOS DE LAS ZONAS
Secuencia Zon Bulto              Matcaja       Codope    Estado                             Ultima modificación
@L@@@@@@@ @L@ _18_______________ _20__________ _10______ @L@@ _32________________ _________ _32_________ ¿D-MM-Y.YY ________
|

TABLA=VDBULTOZONA
ORDERBY=CODZONA,SEQBULTO;

PROTECT("SUPERVISOR")

PREINSERT=FEJECUTA("CSELSEC","CSELSEC")

POSTQUERY=FEJECUTA("CSELMATCAJA","No existe bulto")

PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=SEQBULTO,NOUPDATE,TOOLTIP("Clave primaria de la tabla se obtiene de IPSECBULTOZONA"),TITULO("Secuencia")
CAMPO=CODZONA,NOUPDATE,TOOLTIP("Código de la zona en la que se procesa el bulto"),TITULO("Zona"),WLONX=10
CAMPO=CODBULTO,NOUPDATE,TOOLTIP("Código del bulto"),TITULO("Bulto")
CAMPO=MATCAJA,NOUPDATE,AUXILIAR,TOOLTIP("Matrícula de la caja o cubeta"),TITULO("Matrícula")
CAMPO=CODOPE,TOOLTIP("Operario que trata el bulto"),TITULO("Operario")
CAMPO=STATUS,POSTCHANGE=FDESIGNACION("CSELSTATUS","No existe estado"),TOOLTIP("Estado del bulto en la zona"),TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,TOOLTIP("Descripcion del status")
CAMPO=COLOROPE,TOOLTIP("Color de display asociado al operario"),TITULO("Color")
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='BZO';

CURSOR=CSELMATCAJA SELECT MATCAJA FROM VDBULTOCAB WHERE CODBULTO=:CODBULTO;

CURSOR=CSELSEC SELECT VDSECBULTOZONA.NEXTVAL SEQBULTO,VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;


CONTEXTUAL=FEJECUTAFORM("VDBULTOSMA","S","CODBULTO=:CODBULTO")