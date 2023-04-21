###################################################################
#Módulo: VDCONFDIVIS.PAN
#Funcionalidad : Configuración de divisiones
#Autor: CGG      
#Fecha: 09-05-2016
###################################################################
# Histórico de cambios:
TABLA DE CONFIGURACION DE DIVISIONES

  División                                           ÏÄÄ Generación de albaranes en PDF ÄÄÄÄÄÄË
  ____ _40________________________________________   ³ Habilitado _                           ³
                                                     ³                                        ³
  EDI                                                ³ Envío de albaranes por correo          ³
  _40______________________________________          ³ Habilitado _                           ³
  Buzón entrada interfases                           ³ Tipo de correo asociado ____________   ³
  _256____________________________________           ³ Directorio Oracle _50_______________   ³
  Buzón salida interfases                            ³                                        ³
  _256____________________________________           ³ Envío de albaranes por FTP             ³
                                                     ³ Habilitado _                           ³
 Datos FTP                                           ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
  Host                                              
  _50_____________________________________           ÏÄÄ Envío de stock en CSV ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
  Usuario                                            ³ Habilitado _                           ³
  _50_____________________________________           ³                                        ³
  Contraseña                                         ³ Tipo de correo asociado ____________   ³
  _50_____________________________________           ³ Directorio Oracle _50_______________   ³
  Ruta                                               ³                                        ³
  _100____________________________________           ³ Almacenes seleccionados                ³
                                                     ³ Todos _                                ³
 Facturar por blisters    _                          ³ Almacenes _30________________________  ³
 Facturacion de U/E a 1 : _                          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
                                                    
 Número de copias de factura  @@ 
 Número de copias por albarán @@                     Enviar fichero seguimiento expediciones: _ 
 Texto para pie de albarán
 _1024________________________________________________________________________________________________ 
 


 
 
  Ultima Modificación:
  _32__________ ¿D-MM-Y.YY _8________
 
|
#SELECT=SELEECT DIV.CODDIV, DIV.DESDIV, DIV.EDI, DIV.BUZONIN, DIV.BUZONOUT, DIV.FTPHOST, DIV.FTPUSUARIO, DIV.FTPCLAVE, DIV.FTPRUTA
#       FROM VDDIVIS DIV, XVDCONFDIV CFD
TABLA=VDDIVIS
ORDERBY=CODDIV;
NOINSERT
NODELETE

POSTQUERY=FEJECUTA("+CARGACONFDIVIS","")



PREUPDATE=FEJECUTA("-CVALCOMP","El envío por correo y ftp no es compatible",
                   "CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION",
				   FIF("-CEXISTECONFDIV","CINSERTACONFDIV"),"Error insertando en XVDCONFDIVIS",
				   "CMODCONFDIV","Error actualizando datos de XVDCONFDIVIS")


CAMPO=CODDIV,NOUPDATE,TOOLTIP("Codigo de la division"),POSTCHANGE=FVALNOCERO("EL CODIGO DE DIVISION\nNO PUEDE SER NULO")
CAMPO=DESDIV,NOENTER,TOOLTIP("Nombre completo de la division")
CAMPO=GENERAPDF,AUXILIAR,TOOLTIP("Indica si se generarán albaranes en pdf"),POSTCHANGE=FVERIFICA("SN ","Introduzca S(í) o N(o)")
CAMPO=EDI,TOOLTIP("EDI de la division")
CAMPO=ENVIACORRPDF,AUXILIAR,TOOLTIP("Indica si se envían los albaranes por correo"),POSTCHANGE=FVERIFICA("SN ","Introduzca S(í) o N(o)")
CAMPO=TIPOCORREOPDF,AUXILIAR,TOOLTIP("Tipo de correo que se usará para el envío"),POSTCHANGE=FEJECUTA(FIF("CHAYTIPOCORREO","CVALIDACORREO"),"No se encuentra el tipo de correo"),CONTEXTUAL=FEJECUTAFORM("VDCORREOTIPO","N","","","TIPOCORREOPDF=:TIPOCORREO","Selección de tipo de correo","S")
CAMPO=BUZONIN, TOOLTIP("Directorio de entrada de los interfases de la division")
CAMPO=DIRORACLEPDF,AUXILIAR,TOOLTIP("Directorio Oracle que se usará para el envío por correo")
CAMPO=BUZONOUT, TOOLTIP("Directorio de salida de los interfases de la division")
CAMPO=ENVIAFTPPDF,AUXILIAR,TOOLTIP("Indica si se envían los albaranes por ftp"),POSTCHANGE=FVERIFICA("SN ","Introduzca S(í) o N(o)")
CAMPO=FTPHOST,TOOLTIP("Host al cual se enviarán las interface por FTP")
CAMPO=GENERASTKCSV,AUXILIAR,TOOLTIP("Indica si se generará fichero de stock"),POSTCHANGE=FVERIFICA("SN ","Introduzca S(í) o N(o)")
CAMPO=FTPUSUARIO,TOOLTIP("Usuario de FTP")
CAMPO=TIPOCORREOSTK,AUXILIAR,TOOLTIP("Tipo de correo que se usará para el envío"),POSTCHANGE=FEJECUTA(FIF("CHAYTIPOCORREOSTK","CVALIDACORREOSTK"),"No se encuentra el tipo de correo"),CONTEXTUAL=FEJECUTAFORM("VDCORREOTIPO","N","","","TIPOCORREOSTK=:TIPOCORREO","Selección de tipo de correo","S")
CAMPO=FTPCLAVE,MIXED,TOOLTIP("Clave FTP")
CAMPO=DIRORACLESTK,AUXILIAR,TOOLTIP("Directorio Oracle que se usará para el envío por correo")
CAMPO=FTPRUTA,TOOLTIP("Ruta de destino de FTP")
CAMPO=ENVIATODOSSTK,AUXILIAR,TOOLTIP("Indica si se envían todos los almacenes"),POSTCHANGE=FVERIFICA("SN ","Introduzca S(í) o N(o)")
CAMPO=FACTBLISTERS,AUXILIAR,TOOLTIP("Facturar por Blisters")
CAMPO=LISTAALM,AUXILIAR,TOOLTIP("Lista de almacenes que se enviarán separados por coma")
CAMPO=FACTUNIEMB1,AUXILIAR,TOOLTIP("Facturar articulos con unidades por embalaje a 1 como Unidades, Embalajes.."),POSTCHANGE=FVERIFICA("UE ","Introduzca U(Unidades) o E(Embalajes)")
CAMPO=NUMFACT,AUXILIAR,TOOLTIP("Número de copias que se imprimirán de la factura")
CAMPO=NUMALB,AUXILIAR,TOOLTIP("Número de copias que se imprimirán por albarán")
CAMPO=SEGAGENINTE,AUXILIAR,TOOLTIP("Enviar fichero con las situaciones de expedición comunicadas por las agencias."),POSTCHANGE=FVERIFICA("SN ","Introduzca S(i) o N(o)") 

CAMPO=TEXTOALBARAN,AUXILIAR,MIXED,TOOLTIP("Texto opcional para incluir en el pie de página del albarán"),REGPAG=4,INCLUDECSS="border-style:inset;border-width:2px;background-color:#FBE9C0"

CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
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