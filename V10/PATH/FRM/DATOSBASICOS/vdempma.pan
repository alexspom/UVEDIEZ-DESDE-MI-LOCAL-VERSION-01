# Módulo   : VDEMPMA.PAN
# Función  : Mantenimiento de empresas
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
TABLA DE EMPRESAS

  Empresa
  _10__ _40________________________________
  Abreviatura  NIF
  _10________  _15_____________

  Sufijo Documentos _____

  Contacto: _40____________________________

  Dirección
  _40______________________________________
  _40______________________________________
  _40______________________________________
  _40______________________________________
  Población
  _40______________________________________
  País
  _____ __________________________________
  Provincia                         D.P.
  ______ _40_______________________ __________


  Teléfono1     Fax1
  _20__________ _20__________
  Teléfono2     Fax2
  _20__________ _20__________

  e-mail
  _40______________________________________
  EDI
  _40______________________________________



___________________________________________





  Ultima modificación
  _32________ ¿D-MM-Y.YY  ________

                                              |

TABLA=VDEMPRE

PREUPDATE=FEJECUTA("%CDAMECAMPO","NUEVO :NIF VIEJO :ANTIGUO antoguo :NIF__OLD")


CURSOR=CDAMECAMPO BEGIN
                     SELECT :NIF__OLD INTO :ANTIGUO FROM DUAL;
                     RAISE NO_DATA_FOUND;
                  END;@

CAMPO=ANTIGUO,AUXILIAR,NOUPDATE,OCULTO,"_20"


CAMPO=CODEMP,NOUPDATE,TOOLTIP("Código de la empresa")
CAMPO=DESEMP,TITULO("DESIGNACION DE LA EMPRESA")
CAMPO=DABEMP,TOOLTIP("Abreviatura de la empresa")
CAMPO=NIF
CAMPO=SUFIJODOC,TOOLTIP("Sufijo a añadir a los nombres documentos de esta division")
CAMPO=CONTACTO,TOOLTIP("Persona de contacto en la empresa")
CAMPO=DIRECCION1,MIXED,TOOLTIP("Dirección de la empresa")
CAMPO=DIRECCION2,TOOLTIP("Dirección de la empresa"),MIXED
CAMPO=DIRECCION3,TOOLTIP("Dirección de la empresa")
CAMPO=DIRECCION4,TOOLTIP("Dirección de la empresa")
CAMPO=POBLACION,TOOLTIP("Población de la empresa")
CAMPO=CODPAIS,TOOLTIP("Código del país de la empresa\nMay-F10   Ayuda contextual"),POSTCHANGE=FDESIGNACION("CSELDESPAIS","No existe país"),
                CONTEXTUAL=FEJECUTAFORM("VDPAIS","N","","","CODPAIS=:CODPAIS","Selección de pais","S"),
                COMBOX("CLISTAPAIS")
CAMPO=DESPAIS,AUXILIAR,NOENTER,TOOLTIP("Designación del país")
CAMPO=CODPROV,TOOLTIP("Código de la provincia de la empresa\nMay-F10   Ayuda contextual"),POSTCHANGE=FDESIGNACION("CSELDESPROV","No existe la provincia"),
                CONTEXTUAL=FEJECUTAFORM("VDSELPROVI","N","","CODPAIS=:CODPAIS","CODPROV=:CODPROV","Selección de provincia","S"),
                COMBOX("CLISTAPROV"),COMBOXREGPAG=10
CAMPO=DESPROV,AUXILIAR,NOENTER,TOOLTIP("Nombre de la provincia de la empresa")
CAMPO=DP,TOOLTIP("Distrito postal de la empresa")
CAMPO=TELEFONO1,TOOLTIP("Teléfono1 de la empresa")
CAMPO=FAX1,TOOLTIP("Fax 1 de la empresa")
CAMPO=TELEFONO2,TOOLTIP("Teléfono 2 de la empresa")
CAMPO=FAX2,TOOLTIP("Fax 2 de la empresa")
CAMPO=EMAIL,TOOLTIP("E-Mail de la empresa")
CAMPO=EDI,TOOLTIP("EDI de la empresa")
CAMPO=PRUEBA,AUXILIAR,NOENTER
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CLISTAPAIS SELECT CODPAIS,DESPAIS FROM VDPAIS ORDER BY CODPAIS;

CURSOR=CLISTAPROV SELECT CODPROV, DESPROV FROM VDPROVI WHERE CODPAIS=NVL(:CODPAIS, CODPAIS) ORDER BY CODPAIS,CODPROV;

CURSOR=CSELDESPROV SELECT DESPROV FROM VDPROVI WHERE CODPAIS=:CODPAIS AND CODPROV=:CODPROV;
CURSOR=CSELDESPAIS SELECT DESPAIS FROM VDPAIS WHERE CODPAIS=:CODPAIS;

CURSOR=CSELOLD SELECT :DESEMP__OLD PRUEBA FROM DUAL;

TECLA=CF1,FDESIGNACION("CSELOLD","")

CURSOR=CSELERR DECLARE
                 CURSOR C1 IS SELECT * FROM VDARTIC;
               BEGIN                  
                 :V10ERROR:='PEPE COME PATATAS';
                 SELECT 1 INTO :V10ORAERR FROM DUAL;
               END;@

TECLA=CF2,FDESIGNACION("CSELERR","ERROR AL VALIDAR :V10ERROR CUANDO QUIERE")

