# Módulo   : VDALMA.PAN
# Función  : Mantenimiento de almacenes
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE ALMACENES
 Cod. Alm.  ____ Designación _40_______________________________ Contacto _40___________________________
 Direccion: _40______________________________________ _40______________________________________________
            _40______________________________________ _40______________________________________________
 Población  _40______________________________________
 Pais       _____  _30_______________________________
 Provincia  _5_  _40_________________________      DP _10________
 Teléfono1  _12_________ Fax1 _12_________ Teléfono 2 _12_________ Fax 2 _12_________
 e-mail     _40______________________________________ EDI _40______________________________________
 
 Ultima modificación _32________ ¿D-MM-Y.YY  ________
|

TABLA=VDALMA
ORDERBY=CODALM;
PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")




CAMPO=CODALM,NOUPDATE,TOOLTIP("Código del almacén")
CAMPO=DESALM,TOOLTIP("Designación del almacén")
CAMPO=CONTACTO,TOOLTIP("Persona de contacto en el almacén")
CAMPO=DIRECCION1,MIXED,TOOLTIP("Dirección del almacén")
CAMPO=DIRECCION2,MIXED,TOOLTIP("Dirección del almacén")
CAMPO=DIRECCION3,MIXED,TOOLTIP("Dirección del almacén")
CAMPO=DIRECCION4,MIXED,TOOLTIP("Dirección del almacén")
CAMPO=POBLACION,MIXED,TOOLTIP("Población del almacén")
CAMPO=CODPAIS,TOOLTIP("Código del país del almacén\nMay-F10   Ayuda contextual"),POSTCHANGE=FDESIGNACION("CSELDESPAIS","No existe país"),
                CONTEXTUAL=FEJECUTAFORM("VDPAIS","N","","","CODPAIS=:CODPAIS","Selección de pais","S"),
                COMBOX("CLISTAPAIS")
CAMPO=DESPAIS,AUXILIAR,NOENTER,TOOLTIP("Nombre del del almacén")
CAMPO=CODPROV,TOOLTIP("Código de la provincia del almacén\nMay-F10   Ayuda contextual"),POSTCHANGE=FDESIGNACION("CSELDESPROV","No existe provincia"),
                CONTEXTUAL=FEJECUTAFORM("VDSELPROVI","N","","CODPAIS=:CODPAIS","CODPROV=:CODPROV","Selección de provincia","S"),
                COMBOX("CLISTAPROV"),WLONX=8,COMBOXREGPAG=15
CAMPO=DESPROV,AUXILIAR,NOENTER,TOOLTIP("Nombre de la provincia del almacén")
CAMPO=DP,TOOLTIP("Distrito postal del almacén")
CAMPO=TELEFONO1,TOOLTIP("Teléfono del almacén")
CAMPO=TELEFONO2,TOOLTIP("Teléfono del almacén")
CAMPO=FAX1,TOOLTIP("Fax del almacén")
CAMPO=FAX2,TOOLTIP("Fax del almacén")
CAMPO=EMAIL,TOOLTIP("Dirección de correo electrónico del almacén")
CAMPO=EDI,TOOLTIP("Dirección EDI del almacén")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CLISTAPAIS SELECT CODPAIS, DESPAIS FROM VDPAIS;

CURSOR=CLISTAPROV SELECT CODPROV, DESPROV,CODPAIS FROM VDPROVI WHERE CODPAIS=:CODPAIS;

CURSOR=CSELDESPROV SELECT DESPROV FROM VDPROVI WHERE CODPAIS=:CODPAIS AND CODPROV=:CODPROV;
CURSOR=CSELDESPAIS SELECT DESPAIS FROM VDPAIS WHERE CODPAIS=:CODPAIS;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


