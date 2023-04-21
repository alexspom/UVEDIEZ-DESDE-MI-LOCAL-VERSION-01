###################################################################
#Módulo: XVDLANZAORDEN.PAN
#Funcionalidad : Selección de articulos a producir junto con sus cantidades
#Autor: DGB      
#Fecha: 02-04-2019
###################################################################
# Histórico de cambios:
#
#
#
Modificaciones de órdenes de fabricación pendientes de confirmar

Orden             DIVISION ArtÍculo                 LOTE  Fecha de fabricación  Nueva cantidad   Cargar S/N
_20______________ _4__      _40___________ _60_____ _15_     ¿D-MM-Y.YY            @L@@@@             _           
                                                                                                                            |
																																															 
																																															 
PQUERY

SOLOQUERY

PREBLOQUE=FPREGUNTAR("0")

SELECT=SELECT OKC.CODORDKIT, OKC.CODDIV, OKC.CODART, OKC.CODLOT, FECFABKIT, OKC.CANTIDAD, OKC.SEQORDKIT, 'N' SWTLANZAR
       FROM VDORDKITCAB OKC
       WHERE OKC.STATUS=50;

PREUPDATE=FEJECUTA("CSWTLANZARS","DEBE MARCAR EL CAMPO LANZAR AL VALOR S.",
                   "CCOMPCANT","LA CANTIDAD A PREPARAR NO PUEDE SER INFERIOR\nA LA CANTIDAD PREPARADA",
				   "!CSELPREGUNTA","¿DESEA CARGAR LA ORDEN DEL KIT :CODORDKIT ?",
				   "CACTUALIZASTATUS","ERROR GENERANDO O ACTUALIZANDO CONFIGURACIÓN DE ARTÍCULOS EN AREA DE KITS")
				   
POSTUPDATE=FEJECUTA(%FFAILURE,"CARGA DE ORDEN :CODORDKIT REALIZADO CORRECTAMENTE.",
                   "CVALIDAYTRANSFORMA","ERROR AL VALIDAR Y TRANSFORMAR", 
				   FPULSATECLAS("F3","F2","F6","F3","F2"),"")
				   
CAMPO=CODORDKIT,AUXILIAR,UPPER,TOOLTIP("Es la orden del artículo a producir"),TITULO("Orden")
CAMPO=CODDIV,AUXILIAR,UPPER,TOOLTIP("Código de división"),TITULO("Division")
CAMPO=CODART,AUXILIAR,UPPER,TOOLTIP("Es el código del artículo a producir"),TITULO("Artículo"), POSTCHANGE=FDESIGNACION("+CDESART","Código de artículo no existe.")
CAMPO=DESART,AUXILIAR,NOENTER,UPPER,NOENTER
CAMPO=CODLOT,AUXILIAR,UPPER,TOOLTIP("Código lote"),TITULO("Lote")
CAMPO=FECFABKIT,AUXILIAR,NOENTER,TOOLTIP("Fecha en la que debe haberse terminado la orden de kitting"),TITULO("Fecha fabr.")
CAMPO=CANTIDAD,AUXILIAR,NOENTER,TOOLTIP("Nueva cantidad total de cajas completas a producir"),TITULO("Cantidad")
CAMPO=SWTLANZAR,AUXILIAR,TOOLTIP("Switch de carga"),TITULO("Cargar S/N"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)")
CAMPO=SEQORDKIT,AUXILIAR,OCULTO,"@@@"

CURSOR=CDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;

CURSOR=CSWTLANZARS SELECT :SWTLANZAR FROM DUAL WHERE :SWTLANZAR='S';

CURSOR=CSELPREGUNTA SELECT :CODART FROM DUAL WHERE 1=2;

CURSOR=CCOMPCANT SELECT :CANTIDAD FROM DUAL WHERE :CANTIDAD>(SELECT COUNT(*) FROM VDPEDIDOCAB WHERE PEDIDOHOST = :CODORDKIT AND STATUS >= 4300 AND STATUS < 7000);

CURSOR=CACTUALIZASTATUS UPDATE VDORDKITCAB SET STATUS = 100 WHERE CODORDKIT = :CODORDKIT AND CODDIV = :CODDIV AND SEQORDKIT = :SEQORDKIT;

CURSOR=CVALIDAYTRANSFORMA BEGIN VDKITS.VALIDARORDENES; VDKITS.TRANSFORMARORDENESPROD; END;@

ONLINE={F4} Lanzar   {Esc} Salir;
