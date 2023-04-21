###################################################################
#Módulo: VDDIVIS.PAN
#Funcionalidad : Mantenimiento de divisiones
#Autor: FPD      
#Fecha: 26-06-2008
###################################################################
# Histórico de cambios:
TABLA DE DIVISIONES

  División
  _20_ _40________________________________________
  Código interno   Abreviatura  
  ____             _10________  
  NIF              Código EAN
  _15_____________ _______
  
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
  ______ _40_______________________ _10________
  
  Teléfono1     Fax1          
  _12__________ _12__________ 
  Teléfono2     Fax2        
  _12__________ _12__________ 

  e-mail                        
  _40______________________________________
  EDI
  _40______________________________________

  Buzón entrada interfases
  _256____________________________________

  Buzón salida interfases
  _256____________________________________


  Ultima Modificación:
  _32__________ ¿D-MM-Y.YY _8________
 
                                                 |
TABLA=VDDIVIS


PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")




CAMPO=CODEMP,OCULTO,"_3_"

CAMPO=CODDIV,NOUPDATE,TOOLTIP("Código de la division"),POSTCHANGE=FVALNOCERO("EL Código DE DIVISION\nNO PUEDE SER NULO")
CAMPO=DESDIV,TOOLTIP("Nombre completo de la division")
CAMPO=CODDIVEMP,TOOLTIP("Código empresa-division"),POSTCHANGE=FVALNOCERO("EL Código DIVISION-EMPRESA\nNO PUEDE SER NULO")
CAMPO=DABDIV,TOOLTIP("Abreviatura de la division")
CAMPO=NIF,TOOLTIP("NIF de la division")
CAMPO=CODEANEMP,TOOLTIP("Código EAN de la empresa.\nDebe contener el Código de país.\nEn España es 84")
CAMPO=SUFIJODOC,TOOLTIP("Sufijo a añadir a los nombres documentos de esta división")
CAMPO=CONTACTO,TOOLTIP("Persona de contacto en la división")
CAMPO=DIRECCION1,TOOLTIP("Dirección de la division")
CAMPO=DIRECCION2,TOOLTIP("Dirección de la division")
CAMPO=DIRECCION3,TOOLTIP("Dirección de la division")
CAMPO=DIRECCION4,TOOLTIP("Dirección de la division")
CAMPO=POBLACION,TOOLTIP("Población de la division")
CAMPO=CODPAIS,TOOLTIP("Código del país de la division"),POSTCHANGE=FDESIGNACION("CSELDESPAIS","No existe país"),
                CONTEXTUAL=FEJECUTAFORM("VDPAIS","N","","","CODPAIS=:CODPAIS","Selección de pais","S")
CAMPO=DESPAIS,AUXILIAR,NOENTER,TOOLTIP("Nombre del pais de la división")
CAMPO=CODPROV,TOOLTIP("Código de la provincia de la division"),POSTCHANGE=FDESIGNACION("CSELDESPROV","No existe la provincia"),
                CONTEXTUAL=FEJECUTAFORM("VDSELPROVI","N","","CODPAIS=:CODPAIS","CODPROV=:CODPROV","Selección de provincia","S")
CAMPO=DESPROV,AUXILIAR,NOENTER,TOOLTIP("Nombre de la provincia de la division")
CAMPO=DP,TOOLTIP("Distrito postal de la division")
CAMPO=TELEFONO1,TOOLTIP("Teléfono1 de la division")
CAMPO=FAX1,TOOLTIP("Fax 1 de la division")
CAMPO=TELEFONO2,TOOLTIP("Teléfono 2 de la division")
CAMPO=FAX2,TOOLTIP("Fax 2 de la division")
CAMPO=EMAIL,TOOLTIP("E-Mail de la division")
CAMPO=EDI,TOOLTIP("EDI de la division")
CAMPO=BUZONIN, TOOLTIP("Directorio de entrada de los interfases de la division")
CAMPO=BUZONOUT, TOOLTIP("Directorio de salida de los interfases de la division")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")




CURSOR=CSELDESPROV SELECT DESPROV FROM VDPROVI WHERE CODPROV=:CODPROV AND CODPAIS=:CODPAIS;
CURSOR=CSELDESPAIS SELECT DESPAIS FROM VDPAIS WHERE CODPAIS=:CODPAIS;
CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


#TECLA=SF7,FIMPRIME("VDARTIC.REP","CODDIV=:CODDIV","0","C:\prueba.PDF","1")

