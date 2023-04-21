###################################################################
#M�dulo: VDBULCAB.PAN
#Funcionalidad : Mantenimiento de cabecera de bultos
#Autor: RFD      
#Fecha: 08-04-2008
###################################################################
# Hist�rico de cambios:
MANTENIMIENTO DE CABECERAS DE BULTO
 C�digo : _18_______________    Tipo bulto: _    N� bulto: @L@@@ / @L@@@ 
 
 Estado:  @L@@@@ _30________________________  Tracking: _20_________________
 
 Pedido:  _20_______________ Div.:_20_ _40_____________________ A�o: @@@@   Versi�n: @@@@    
 
 ����������� Empaquetado ������������ ���� Preparaci�n �������� ������������ Preparaci�n �������������
 � Volumetr�a:   _10_________       � � ID.Pick:       @@@    � � CNTSSCC:   _18_______________      �
 � Caja:         _10_________       � � N�m.Display:   @@@@@@@� � Matr�cula: _18_______________      �
 � Peso Te�rico: #L############# g. � � Anular prec.:  _      � � Recogida:  _20__________________   �
 � Peso Real:    #L############# g. � � Lleva albar�n: _      � � PDA: _20_______________________    �
 � Vol�men:      #L############# cc.� � Verif.Forzada: _      � � Scanner:   @@@@ �D-MM-YY.Y ________�
 �                                  � �                       � � Recir.Prepar: @@@@ Verif: @@@@     �
 ������������������������������������ ������������������������� ��������������������������������������
 ���������������������������� Seguimiento ���������������������������
 � Fecha de creaci�n:      �D-MM-YY.Y ________                      �
 � Impreso:                �D-MM-YY.Y ________ _32________________  � 
 � Verificado:             �D-MM-YY.Y ________ _32________________  � 
 � Fecha de finalizaci�n:  �D-MM-YY.Y ________                      �
 � Ultima modificaci�n:    �D-MM-YY.Y ________ _32________________  � Comentario:@L@@@@@@@
 ��������������������������������������������������������������������    
 Informaci�n: _255________________________________________________________________________
|

TABLA=VDBULTOCABFU

#TIMEOUT=QUERYAUTOM,100
#TECLA=F3,FEJECUTA(FIF(FLECTURAS("CODBULTO"),FEJECUTA(FCOMMIT,"",FPULSATECLAS("F2"),"")),"DASDASDASD")

CURSOR=CSELLECT BEGIN
                  SELECT TEXTO INTO :CODBULTO FROM VDSCANLECT WHERE REDSCAN=1 AND SCANNER=10 AND ROWNUM=1;
                  DELETE VDSCANLECT WHERE REDSCAN=1 AND SCANNER=10;
                  COMMIT;
                END;@
                   
POSTQUERY=FEJECUTA("+CSELPDA","")
PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=CODBULTO,NOUPDATE,TOOLTIP("C�digo del bulto. N�mero �nico que lo identifica")
CAMPO=TIPOBULTO,PROTECT("SUPALMACEN"),TOOLTIP("Tipo del bulto 'U' unidades, 'E' Embalajes, 'C' Contenedor")
CAMPO=NBULTO,NOUPDATE("SUPALMACEN"),TOOLTIP("N�mero de bulto dentro del pedido")
CAMPO=TOTALBULTOS,AUXILIAR,NOENTER,TOOLTIP("Total de bultos dentro del pedido")
CAMPO=STATUS,UPDATE("STATUS"),TOOLTIP("Estado del bulto seg�n tabla de estados tipo BUC"),POSTCHANGE=FDESIGNACION("CSELSTATUS","Estado no existe"),COMBOX("CSELMISTATUS")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripci�n del estado del bulto seg�n tabla de estados tipo BUC")
CAMPO=TRACKINGAGE,NOUPDATE,TOOLTIP("C�digo identificativo del bulto para la agencia de transporte")
CAMPO=CODPED,NOUPDATE,POSTCHANGE=FDESIGNACION("CCOUNT","ERROR CONTANDO BULTOS DEL PEDIDOS"),TOOLTIP("C�digo del pedido")
CAMPO=CODDIV,NOUPDATE,POSTCHANGE=FDESIGNACION("CDESDIV","C�digo de divisi�n no existe."),TOOLTIP("Divisi�n o compa�ia del pedido")
CAMPO=DESDIV,AUXILIAR,NOENTER,TOOLTIP("Descripci�n de la divisi�n o compa��a del pedido")
CAMPO=ANOPED,NOUPDATE,TOOLTIP("A�o del pedido")
CAMPO=SEQPED,NOUPDATE,TOOLTIP("Versi�n del pedido")
CAMPO=TIPOVOL,PROTECT("SUPALMACEN"),CONTEXTUAL=FEJECUTAFORM("VDVOLUMETRIA","N","TIPOVOL=:TIPOVOL","","","","S"),TOOLTIP("Tipo de volumetr�a si el bulto es de unidades")
CAMPO=IDINFOPICK,NOUPDATE,TOOLTIP("Indica a que infopick hardware se refiere el numero de display al que est� asociado el bulto")
CAMPO=CNTSSCC,NOUPDATE("V10"),TOOLTIP("Matr�cula del palet de expediciones en caso de paletizaci�n para la expedici�n")
CAMPO=TIPOCAJA,PROTECT("SUPALMACEN"),TOOLTIP("Inicial de la caja que aparece en la etiqueta")
CAMPO=NUMDISP,NOUPDATE,TOOLTIP("N�mero de display en la red infopick hardware al que est� asociado el bulto")
CAMPO=MATCAJA,PROTECT("SUPALMACEN"),TOOLTIP("Matr�cula de la caja para identificarla unicamente.")
CAMPO=PESOTEORICO,PROTECT("SUPALMACEN"),TOOLTIP("Peso te�rico del bulto en gramos")
CAMPO=SWTANULAR,PROTECT("SUPALMACEN"),TOOLTIP("Indicador con valores: 'S' anular precintos, 'N' no se deben anular precintos")
CAMPO=SERIERECOGIDA,PROTECT("SUPALMACEN"),TOOLTIP("N�mero de serie de recogida en recogidas de cajas por etiquetado de cajas manual")
CAMPO=PESOREAL,PROTECT("SUPALMACEN"),TOOLTIP("Peso medido por la b�scula en gramos")
CAMPO=SWTLLEVAALB,PROTECT("SUPALMACEN"),TOOLTIP("Indicador con valores: 'S' si el bulto lleva el albar�n del pedido, VACIO si no lleva el albar�n")
CAMPO=CODRECURSO,AUXILIAR,NOUPDATE,WHERE=:CODRECURSO IN (SELECT CODRECURSO FROM VDMOVIM MOV,VDBULTOLIN BUL WHERE BUL.CODBULTO=VDBULTOCAB.CODBULTO AND BUL.CODMOV=MOV.CODMOV);
CAMPO=VOLUMEN,TOOLTIP("Vol�men del bulto en cent�metros c�bicos"),PROTECT("SUPALMACEN"),TOOLTIP("Volumen del bulto en centimetros c�bicos")
CAMPO=SWTVERIFFORZADA,PROTECT("SUPALMACEN"),TOOLTIP("Indicador con valores: 'S' si el bulto se ha forzado, por alguien o por un programa a que se verifique, 'N' no se fuerza a que entre en verificaci�n.")
CAMPO=ULTSCAN,NOENTER,TOOLTIP("Ultimo scanner por el que ha pasado el bulto")
CAMPO=FECULTSCAN,NOENTER,TOOLTIP("Fecha en que actualiz� el campo de �ltimo scanner por el que ha pasado el bulto")
CAMPO=HORAULTSCAN,NOENTER,TOOLTIP("Hora en que actualiz� el campo de �ltimo scanner por el que ha pasado el bulto")
CAMPO=NUMRECIRCULAPREP,NOENTER,TOOLTIP("N�mero de recirculaciones del bulto en la zona de preparaci�n")
CAMPO=NUMRECIRCULAVERIF,NOENTER,TOOLTIP("N�mero de recirculaciones del bulto en la zona de verificaci�n")
CAMPO=FECCREADO,NOENTER,TOOLTIP("Fecha en que cre� el bulto")
CAMPO=HORACREADO,NOENTER,TOOLTIP("Hora en que creo el bulto")
CAMPO=FECIMPRIME,NOENTER,TOOLTIP("Fecha en que realiz� la impresi�n de la etiqueta  del bulto")
CAMPO=HORAIMPRIME,NOENTER,TOOLTIP("Hora en que realiz� la impresi�n de la etiqueta  del bulto")
CAMPO=CODOPEIMPRIME,NOENTER,TOOLTIP("Usuario que realiza la impresi�n de la etiqueta del bulto")
CAMPO=FECVERIFICA,NOENTER,TOOLTIP("Fecha en que realiz� la verificaci�n del bulto")
CAMPO=HORAVERIFICA,NOENTER,TOOLTIP("Hora en que realiz� la verificaci�n del bulto")
CAMPO=CODOPEVERIFICA,NOENTER,TOOLTIP("Usuario que realiza la verificaci�n del bulto")
CAMPO=FECFINALIZA,NOENTER,TOOLTIP("Fecha en que se finaliz� el bulto")
CAMPO=HORAFINALIZA,NOENTER,TOOLTIP("Hora en que se finaliz� el bulto")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificaci�n")
CAMPO=HORAMODIF,UPPER,NOENTER,TOOLTIP("Hora de la Ultima modificaci�n")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que realiza la Ultima modificaci�n")
CAMPO=CODCOMEN,NOUPDATE,TOOLTIP("C�digo de los comentarios a la cabecera del bulto")
CAMPO=VDEXTRA,PROTECT("SUPALMACEN"),TOOLTIP("Datos adicionales externos a V10")

CURSOR=CSELPDA SELECT CODRECURSO FROM (SELECT CODRECURSO FROM VDMOVIM WHERE CODMOV IN (SELECT CODMOV FROM VDBULTOLIN WHERE CODBULTO=:CODBULTO)ORDER BY CASE WHEN STATUS BETWEEN 2000 AND 2100 THEN 0 ELSE 1 END) WHERE ROWNUM=1;


CURSOR=CSELMISTATUS SELECT STATUS,DABSTATUS,DESSTATUS,TIPOSTATUS FROM VDSTATUS WHERE TIPOSTATUS='BUC' ORDER BY STATUS;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CCOUNT SELECT COUNT(*) TOTALBULTOS FROM VDBULTOCAB
              WHERE CODPED=:CODPED AND SEQPED=:SEQPED AND CODDIV=:CODDIV AND ANOPED=:ANOPED ; 

CURSOR=CDESDIV SELECT DESDIV
                 FROM VDDIVIS
                WHERE CODDIV=:CODDIV;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='BUC';
 
                      
CURSOR=CIMPREBULTO BEGIN
                     VDIMPRIME.IMPRIME('ETIQ','VDETIQBU.GEN;VDETIQUETAS.VSQ;CSELBULTO','CODBULTO='||:CODBULTO,1,'','',:V10ERROR,VDST.FISPPENDFICH);
					 RDRPKG.IMPRIMEAMZNCCBULTO(:CODBULTO);
                     COMMIT;
                   END;@ 
				   
CURSOR=CIMPREPACKLISTETIQ BEGIN
                            RDRPKG.IMPRIMIRPACKINGLISTETIQ(:CODBULTO);
                            COMMIT;
                          END;@ 

TECLA=CF1,FEJECUTA("CIMPREBULTO","ERROR AL IMPRIMIR")
					