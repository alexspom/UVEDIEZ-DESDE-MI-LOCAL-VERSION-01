# Módulo   : VDDIVMA.PAN
# Función  : Mantenimiento de divisiones
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
TABLA DE DIVISIONES
  Empresa _4__ __________________________________
  División
  _20___ _40_____________________________________
  Código interno   Abreviatura  
  ______________   _10________  
  NIF              Código EAN   Sec SSCC
  _15_____________ _20________  _20_____________
  
  Sufijo Documentos _10____
  
  Albaranes: Imprimir _  Generar en pdf _
  
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
  ______ _40_______________________ _10________
  
  Teléfono1     Fax1          
  _20__________ _20__________ 
  Teléfono2     Fax2        
  _20__________ _20__________ 

  e-mail                        
  _40______________________________________
  EDI
  _40______________________________________
  
  ZONAS DE PICKING
  _40______________________________________

  Buzón entrada interfases
  _256____________________________________
  Buzón salida interfases
  _256____________________________________
  
  Compatibilidad ubicaciones
  _1024___________________________________

  Secuencial de entrada @@@@@@
  Secuencial de salida  @@@@@@
  
  Ultima modificación:
  _32__________ ¿D-MM-Y.YY _8________
 
                                                 |
TABLA=VDDIVIS


PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")




CAMPO=CODEMP, VIRTUAL,NOUPDATE
CAMPO=DESEMP, VIRTUAL,AUXILIAR,NOUPDATE

CAMPO=CODDIV,NOUPDATE,TOOLTIP("Código de la division"),POSTCHANGE=FVALNOCERO("EL Código DE DIVISION\nNO PUEDE SER NULO")
CAMPO=DESDIV,TOOLTIP("Nombre completo de la division")
CAMPO=CODDIVEMP,TOOLTIP("Código empresa-division"),POSTCHANGE=FVALNOCERO("EL Código DIVISION-EMPRESA\nNO PUEDE SER NULO")
CAMPO=DABDIV,TOOLTIP("Abreviatura de la division")
CAMPO=NIF,TOOLTIP("NIF de la division")
CAMPO=CODEANEMP,TOOLTIP("Código EAN de la empresa.\nDebe contener el Código de país.\nEn España es 84")
CAMPO=SECSSCC,TOOLTIP("Secuencial utilizado para los SSCC")
CAMPO=SUFIJODOC,TOOLTIP("Sufijo a añadir a los nombres documentos de esta division")
CAMPO=IMPRIMEALB,TOOLTIP("Indica si se imprimirán los albaranes de la divisón")
CAMPO=GENERAALBPDF,TOOLTIP("Indica si se generan en pdf en la ruta de salida los albaranes de la división")
CAMPO=CONTACTO,TOOLTIP("Persona de contacto en la división")
CAMPO=DIRECCION1,TOOLTIP("Dirección de la division"),MIXED
CAMPO=DIRECCION2,TOOLTIP("Dirección de la division"),MIXED
CAMPO=DIRECCION3,TOOLTIP("Dirección de la division"),MIXED
CAMPO=DIRECCION4,TOOLTIP("Dirección de la division"),MIXED
CAMPO=POBLACION,TOOLTIP("Población de la division"),MIXED
CAMPO=CODPAIS,TOOLTIP("Código del país de la division"),POSTCHANGE=FDESIGNACION("CSELDESPAIS","No existe país"),
                CONTEXTUAL=FEJECUTAFORM("VDPAIS","N","","","CODPAIS=:CODPAIS","Selección de pais","S"),
                COMBOX("CLISTAPAIS")
CAMPO=DESPAIS,AUXILIAR,NOENTER,TOOLTIP("Nombre del pais de la división")
CAMPO=CODPROV,TOOLTIP("Código de la provincia de la division"),POSTCHANGE=FDESIGNACION("CSELDESPROV","No existe la provincia"),
                CONTEXTUAL=FEJECUTAFORM("VDSELPROVI","N","","CODPAIS=:CODPAIS","CODPROV=:CODPROV","Selección de provincia","S"),
                COMBOX("CLISTAPROV"),COMBOXREGPAG=10
CAMPO=DESPROV,AUXILIAR,NOENTER,TOOLTIP("Nombre de la provincia de la division")
CAMPO=DP,TOOLTIP("Distrito postal de la division")
CAMPO=TELEFONO1,TOOLTIP("Teléfono1 de la division")
CAMPO=FAX1,TOOLTIP("Fax 1 de la division")
CAMPO=TELEFONO2,TOOLTIP("Teléfono 2 de la division")
CAMPO=FAX2,TOOLTIP("Fax 2 de la division")
CAMPO=EMAIL,TOOLTIP("E-Mail de la division")
CAMPO=EDI,TOOLTIP("EDI de la division")
CAMPO=ZONASPICKING,TOOLTIP("Zonas de asignacion automática de la división")
CAMPO=BUZONIN, TOOLTIP("Directorio de entrada de los interfases de la division")
CAMPO=BUZONOUT, TOOLTIP("Directorio de salida de los interfases de la division")
CAMPO=COMPATUBI, TOOLTIP("Compatibilidad con ubicaciones")
CAMPO=SECENT,TOOLTIP("Secuencial para la entrada de pedidos")
CAMPO=SECSAL,TOOLTIP("Secuencial para la salida de pedidos")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")
CAMPO=CODCOMEN,OCULTO,"@L@@@@@@@"

CURSOR=CLISTAPAIS SELECT CODPAIS,DESPAIS FROM VDPAIS ORDER BY CODPAIS;

CURSOR=CLISTAPROV SELECT CODPROV, DESPROV FROM VDPROVI WHERE CODPAIS=NVL(:CODPAIS, CODPAIS) ORDER BY CODPAIS,CODPROV;



CURSOR=CSELDESPROV SELECT DESPROV FROM VDPROVI WHERE CODPROV=:CODPROV AND CODPAIS=:CODPAIS;
CURSOR=CSELDESPAIS SELECT DESPAIS FROM VDPAIS WHERE CODPAIS=:CODPAIS;
CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


