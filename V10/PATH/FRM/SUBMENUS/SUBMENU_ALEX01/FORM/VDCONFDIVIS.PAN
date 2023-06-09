###################################################################
#M�dulo: VDCONFDIVIS.PAN
#Funcionalidad : Configuraci�n de divisiones
#Autor: CGG      
#Fecha: 09-05-2016
###################################################################
# Hist�rico de cambios:
TABLA DE CONFIGURACION DE DIVISIONES

  Divisi�n                                           ��� Generaci�n de albaranes en PDF �������
  ____ _40________________________________________   � Habilitado _                           �
                                                     �                                        �
  EDI                                                � Env�o de albaranes por correo          �
  _40______________________________________          � Habilitado _                           �
  Buz�n entrada interfases                           � Tipo de correo asociado ____________   �
  _256____________________________________           � Directorio Oracle _50_______________   �
  Buz�n salida interfases                            �                                        �
  _256____________________________________           � Env�o de albaranes por FTP             �
                                                     � Habilitado _                           �
 Datos FTP                                           ������������������������������������������
  Host                                              
  _50_____________________________________           ��� Env�o de stock en CSV ����������������
  Usuario                                            � Habilitado _                           �
  _50_____________________________________           �                                        �
  Contrase�a                                         � Tipo de correo asociado ____________   �
  _50_____________________________________           � Directorio Oracle _50_______________   �
  Ruta                                               �                                        �
  _100____________________________________           � Almacenes seleccionados                �
                                                     � Todos _                                �
 Facturar por blisters    _                          � Almacenes _30________________________  �
 Facturacion de U/E a 1 : _                          ������������������������������������������
                                                    
 N�mero de copias de factura  @@ 
 N�mero de copias por albar�n @@                     Enviar fichero seguimiento expediciones: _ 
 Texto para pie de albar�n
 _1024________________________________________________________________________________________________ 
 


 
 
  Ultima Modificaci�n:
  _32__________ �D-MM-Y.YY _8________
 
|
#SELECT=SELEECT DIV.CODDIV, DIV.DESDIV, DIV.EDI, DIV.BUZONIN, DIV.BUZONOUT, DIV.FTPHOST, DIV.FTPUSUARIO, DIV.FTPCLAVE, DIV.FTPRUTA
#       FROM VDDIVIS DIV, XVDCONFDIV CFD
TABLA=VDDIVIS
ORDERBY=CODDIV;
NOINSERT
NODELETE

POSTQUERY=FEJECUTA("+CARGACONFDIVIS","")



PREUPDATE=FEJECUTA("-CVALCOMP","El env�o por correo y ftp no es compatible",
                   "CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION",
				   FIF("-CEXISTECONFDIV","CINSERTACONFDIV"),"Error insertando en XVDCONFDIVIS",
				   "CMODCONFDIV","Error actualizando datos de XVDCONFDIVIS")


CAMPO=CODDIV,NOUPDATE,TOOLTIP("Codigo de la division"),POSTCHANGE=FVALNOCERO("EL CODIGO DE DIVISION\nNO PUEDE SER NULO")
CAMPO=DESDIV,NOENTER,TOOLTIP("Nombre completo de la division")
CAMPO=GENERAPDF,AUXILIAR,TOOLTIP("Indica si se generar�n albaranes en pdf"),POSTCHANGE=FVERIFICA("SN ","Introduzca S(�) o N(o)")
CAMPO=EDI,TOOLTIP("EDI de la division")
CAMPO=ENVIACORRPDF,AUXILIAR,TOOLTIP("Indica si se env�an los albaranes por correo"),POSTCHANGE=FVERIFICA("SN ","Introduzca S(�) o N(o)")
CAMPO=TIPOCORREOPDF,AUXILIAR,TOOLTIP("Tipo de correo que se usar� para el env�o"),POSTCHANGE=FEJECUTA(FIF("CHAYTIPOCORREO","CVALIDACORREO"),"No se encuentra el tipo de correo"),CONTEXTUAL=FEJECUTAFORM("VDCORREOTIPO","N","","","TIPOCORREOPDF=:TIPOCORREO","Selecci�n de tipo de correo","S")
CAMPO=BUZONIN, TOOLTIP("Directorio de entrada de los interfases de la division")
CAMPO=DIRORACLEPDF,AUXILIAR,TOOLTIP("Directorio Oracle que se usar� para el env�o por correo")
CAMPO=BUZONOUT, TOOLTIP("Directorio de salida de los interfases de la division")
CAMPO=ENVIAFTPPDF,AUXILIAR,TOOLTIP("Indica si se env�an los albaranes por ftp"),POSTCHANGE=FVERIFICA("SN ","Introduzca S(�) o N(o)")
CAMPO=FTPHOST,TOOLTIP("Host al cual se enviar�n las interface por FTP")
CAMPO=GENERASTKCSV,AUXILIAR,TOOLTIP("Indica si se generar� fichero de stock"),POSTCHANGE=FVERIFICA("SN ","Introduzca S(�) o N(o)")
CAMPO=FTPUSUARIO,TOOLTIP("Usuario de FTP")
CAMPO=TIPOCORREOSTK,AUXILIAR,TOOLTIP("Tipo de correo que se usar� para el env�o"),POSTCHANGE=FEJECUTA(FIF("CHAYTIPOCORREOSTK","CVALIDACORREOSTK"),"No se encuentra el tipo de correo"),CONTEXTUAL=FEJECUTAFORM("VDCORREOTIPO","N","","","TIPOCORREOSTK=:TIPOCORREO","Selecci�n de tipo de correo","S")
CAMPO=FTPCLAVE,MIXED,TOOLTIP("Clave FTP")
CAMPO=DIRORACLESTK,AUXILIAR,TOOLTIP("Directorio Oracle que se usar� para el env�o por correo")
CAMPO=FTPRUTA,TOOLTIP("Ruta de destino de FTP")
CAMPO=ENVIATODOSSTK,AUXILIAR,TOOLTIP("Indica si se env�an todos los almacenes"),POSTCHANGE=FVERIFICA("SN ","Introduzca S(�) o N(o)")
CAMPO=FACTBLISTERS,AUXILIAR,TOOLTIP("Facturar por Blisters")
CAMPO=LISTAALM,AUXILIAR,TOOLTIP("Lista de almacenes que se enviar�n separados por coma")
CAMPO=FACTUNIEMB1,AUXILIAR,TOOLTIP("Facturar articulos con unidades por embalaje a 1 como Unidades, Embalajes.."),POSTCHANGE=FVERIFICA("UE ","Introduzca U(Unidades) o E(Embalajes)")
CAMPO=NUMFACT,AUXILIAR,TOOLTIP("N�mero de copias que se imprimir�n de la factura")
CAMPO=NUMALB,AUXILIAR,TOOLTIP("N�mero de copias que se imprimir�n por albar�n")
CAMPO=SEGAGENINTE,AUXILIAR,TOOLTIP("Enviar fichero con las situaciones de expedici�n comunicadas por las agencias."),POSTCHANGE=FVERIFICA("SN ","Introduzca S(i) o N(o)") 

CAMPO=TEXTOALBARAN,AUXILIAR,MIXED,TOOLTIP("Texto opcional para incluir en el pie de p�gina del albar�n"),REGPAG=4,INCLUDECSS="border-style:inset;border-width:2px;background-color:#FBE9C0"

CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realiz� la �ltima modificaci�n")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CAMPO=SEQDIV,AUXILIAR,OCULTO,"#########"
CAMPO=CODCOMEN,OCULTO,"@L@@@@@@"

#CURSORES 
CURSOR=CVALCOMP SELECT :CODDIV CODDIV FROM DUAL WHERE :ENVIAFTPPDF = 'S' AND :ENVIACORRPDF = 'S';
CURSOR=CHAYTIPOCORREO SELECT :CODDIV CODDIV FROM DUAL WHERE :TIPOCORREOPDF IS NOT NULL;
CURSOR=CHAYTIPOCORREOSTK SELECT :CODDIV CODDIV FROM DUAL WHERE :TIPOCORREOSTK IS NOT NULL;
CURSOR=CVALIDACORREO SELECT TIPOCORREO TIPOCORREOPDF FROM VDCORRTIPOS WHERE TIPOCORREO = :TIPOCORREOPDF;
CURSOR=CVALIDACORREOSTK SELECT :TIPOCORREOSTK TIPOCORREOSTK FROM VDCORRTIPOS WHERE TIPOCORREO = :TIPOCORREOSTK;
CURSOR=CEXISTECONFDIV SELECT :CODDIV CODDIV FROM XVDCONFDIVIS WHERE CODDIV = :CODDIV;
CURSOR=CINSERTACONFDIV INSERT INTO XVDCONFDIVIS (CODDIV, GENERAPDF, ENVIACORRPDF, TIPOCORREOPDF, DIRORACLEPDF, ENVIAFTPPDF, NUMFACT, NUMALB, GENERASTKCSV, TIPOCORREOSTK, DIRORACLESTK, ENVIATODOSSTK, LISTAALM, FACTBLISTERS, FACTUNIEMB1, SEGAGENINTE, TEXTOALBARAN, CODOPEMODIF, FECMODIF, HORAMODIF)
                       VALUES (:CODDIV, :GENERAPDF, :ENVIACORRPDF, :TIPOCORREOPDF, :DIRORACLEPDF, :ENVIAFTPPDF, :NUMFACT, :NUMALB, :GENERASTKCSV, :TIPOCORREOSTK, :DIRORACLESTK, :ENVIATODOSSTK, :LISTAALM, :FACTBLISTERS, :FACTUNIEMB1, :SEGAGENINTE, :TEXTOALBARAN, VDUSER.GETUSER, VD.FECHASYS, VD.HORASYS);
CURSOR=CMODCONFDIV UPDATE XVDCONFDIVIS
                   SET GENERAPDF = :GENERAPDF,
                       ENVIACORRPDF = :ENVIACORRPDF,
                       TIPOCORREOPDF = :TIPOCORREOPDF,
                       DIRORACLEPDF = :DIRORACLEPDF,
                       ENVIAFTPPDF = :ENVIAFTPPDF,
                       NUMFACT = :NUMFACT,
                       NUMALB = :NUMALB,
					   GENERASTKCSV = :GENERASTKCSV,
					   TIPOCORREOSTK = :TIPOCORREOSTK,
					   DIRORACLESTK = :DIRORACLESTK,
					   ENVIATODOSSTK = :ENVIATODOSSTK,
					   LISTAALM = :LISTAALM,
                       FACTBLISTERS = :FACTBLISTERS,
					   FACTUNIEMB1 = :FACTUNIEMB1,
					   SEGAGENINTE = :SEGAGENINTE,
                       TEXTOALBARAN = :TEXTOALBARAN,
                       CODOPEMODIF = VDUSER.GETUSER,
                       FECMODIF = VD.FECHASYS,
                       HORAMODIF = VD.HORASYS
				   WHERE CODDIV = :CODDIV;
CURSOR=CARGACONFDIVIS SELECT GENERAPDF, ENVIACORRPDF, TIPOCORREOPDF, DIRORACLEPDF, ENVIAFTPPDF, NUMFACT, NUMALB, GENERASTKCSV, TIPOCORREOSTK, DIRORACLESTK, ENVIATODOSSTK, LISTAALM, FACTBLISTERS, FACTUNIEMB1, SEGAGENINTE, TEXTOALBARAN FROM XVDCONFDIVIS WHERE CODDIV = :CODDIV;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;