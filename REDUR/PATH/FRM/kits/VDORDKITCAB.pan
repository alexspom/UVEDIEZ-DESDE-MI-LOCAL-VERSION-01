######################################################################
#MOdulo: VDORDKITCAB.PAN
#Funcionalidad : Consulta de cabeceras de ordenes de producci�n procedentes del sistema superior
#Autor: DGB      
#Fecha: 28-03-2019
######################################################################
# HistOrico de cambios:
#
#
#
CABECERA DE ORDENES
  Orden:  _15____________  Versi�n: _4___ Tipo de orden: _4__   
  
  Art�culo a componer: _40_______ _40___________________ Lote: _15____________ Cantidad: _8_______
  
  Cod. Empresa: _5___  Divisi�n: ____  N� de cajas: @L@@@    N� l�neas: @L@@    Fecha de fabricaci�n: �D-MM-Y.YY
  
 �� Seguimiento ����������������������������������������������������������������������������������������������������������� 
 � Captura:   �D-MM-Y.YY  ________    Validaci�n:  �D-MM-Y.YY  ________   Completada:  #L#.### %                          �
 ��������������������������������������������������������������������������������������������������������������������������
 
  Estado: @@@@@  _30____________________________ Ultima modificaci�n: _32_______ �D-MM-Y.YY  ________ Comentario: @@@@@@@@@ 
|


TABLA=VDORDKITCABFU
ORDERBY=FECMODIF DESC,HORAMODIF DESC;

NOINSERT
NODELETE

PROTECT("SUPERVISOR")

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

POSTUPDATE=FEJECUTA(FROLLBACK,"")

TECLA=SF10,FEJECUTA("CGENACTARTAREAKIT2","ERROR RECALCULANDO RECARGA",
                    "CDAMECODAREAKIT", "ERROR OBTENIENDO AREA DE KIT",
				   FCOMMIT,"",
				   FFAILURE,"RECARGA LANZANDA CORRECTAME", 
				   FPULSATECLAS("F3","F2"))

CAMPO=CODORDKIT,TOOLTIP("Identificador de la orden")
CAMPO=SEQORDKIT,TOOLTIP("Versi�n del kit")
CAMPO=TIPOORDKIT,TOOLTIP("Tipo de orden: Producci�n: PROM, Desmontaje:PROD")
CAMPO=CODART,UPPER,TOOLTIP("Es el C�digo del art�culo ordenado a tratar"),TITULO("Art�culo a componer/destruir"),
        POSTCHANGE=FDESIGNACION("+CDESART","C�digo de art�culo no existe.")
CAMPO=DESART,AUXILIAR,UPPER,NOENTER
CAMPO=CODLOT,UPPER,TOOLTIP("C�digo de lote"),TITULO("LOTE")
CAMPO=CANTIDAD,TOOLTIP("Total de unidades solicitadas"),TITULO("CANTIDAD"),POSTCHANGE=FEJECUTA("CSELPORCENCOMPLETA","ERROR CALCULANDO PORCENTAJE COMPLETAD0 DE LA SERIE")
CAMPO=CODPROVE,TOOLTIP("Identificador de la empresa responsable de la orden"),TITULO("Cod. Proveedor")
CAMPO=CODDIV,TOOLTIP("Divisi�n"),TITULO("Divisi�n")
CAMPO=NUMCAJAS,TOOLTIP("N�mero total de cajas que componen el kit"),TITULO("N� de cajas")
CAMPO=NLINEAS,AUXILIAR,TOOLTIP("Es el n�mero original de l�neas de la orden que se recibio del host."),TITULO("N� l�neas")
CAMPO=FECFABKIT,TOOLTIP("Fecha en la que debe haberse terminado la orden de kitting")
CAMPO=FECCAPTURA,NOENTER,TOOLTIP("Fecha de captura de la orden")
CAMPO=HORACAPTURA,NOENTER,TOOLTIP("Hora de captura de la orden")
CAMPO=FECVALIDA,NOENTER,TOOLTIP("Fecha de validaci�n de la orden")
CAMPO=HORAVALIDA,NOENTER,TOOLTIP("Hora de validaci�n de la orden")
CAMPO=PORCENCOMPLETA,NOENTER,AUXILIAR,TOOLTIP("Porcentaje completado de la orden de porducci�n")
CAMPO=STATUS,TOOLTIP("Es el estado en que se encuentra la orden en el momento de la consulta."),POSTCHANGE=FDESIGNACION("CDESSTATUS","Estado incorrecto."),COMBOX("CLISTASTATUS"),COMBOXREGPAG=6
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripci�n del estado en el que se encuentra la orden")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizO la �ltima modificaci�n")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificaci�n")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la �ltima modificacion")
CAMPO=CODCOMEN,NOENTER,TOOLTIP("C�digo de los comentarios a la cabecera del pedido")
CAMPO=CODAREAKIT,AUXILIAR,OCULTO,"_40_"
CAMPO=CODAREAEXPED,AUXILIAR,OCULTO,"_40_"
CAMPO=MENSAJE,AUXILIAR,OCULTO,"_2048_"
CAMPO=RESULTADO,AUXILIAR,OCULTO,"@"

CURSOR=CDESART SELECT DESART
                 FROM VDARTIC
                WHERE CODART=:CODART;
                
CURSOR=CSELPORCENCOMPLETA SELECT ((SELECT COUNT(*) FROM VDPEDIDOCAB WHERE PEDIDOHOST=:CODORDKIT AND STATUS>=VDST.FPECSERVIDO AND STATUS<VDST.FPECANULADO)/NVL(:CANTIDAD,1))*100 PORCENCOMPLETA FROM DUAL;
				
CURSOR=CLISTASTATUS SELECT STATUS,DESSTATUS FROM VDSTATUS WHERE TIPOSTATUS='OKC' ORDER BY STATUS;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='OKC';

CURSOR=CCANTLINEAS SELECT COUNT(*) NLINEAS FROM XVDORDLIN WHERE CODART=:CODART;

CURSOR=CDAMECODAREAKIT SELECT RDRPKG.DAMEAREA(:CODDIV, 'KITTING') CODAREAKIT, RDRPKG.DAMEAREA(:CODDIV, 'EXPEKIT') CODAREAEXPED FROM DUAL;

CURSOR=CGENACTARTAREAKIT2 BEGIN VDKITS.GENERARYACTUALIZARARTAREAKIT(:CODORDKIT,:CODLOT,0,:CODAREAKIT,:CODAREAEXPED,:RESULTADO,:MENSAJE, :CODDIV); END;@

BOTON=B2,1115,100,70,70,"P",bajar.png,SF10,"Recalcular reapro para este kit",INCLUDECSS="background-color: transparent;border-width:0px"