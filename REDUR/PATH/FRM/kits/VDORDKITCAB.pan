######################################################################
#MOdulo: VDORDKITCAB.PAN
#Funcionalidad : Consulta de cabeceras de ordenes de producción procedentes del sistema superior
#Autor: DGB      
#Fecha: 28-03-2019
######################################################################
# HistOrico de cambios:
#
#
#
CABECERA DE ORDENES
  Orden:  _15____________  Versión: _4___ Tipo de orden: _4__   
  
  Artículo a componer: _40_______ _40___________________ Lote: _15____________ Cantidad: _8_______
  
  Cod. Empresa: _5___  División: ____  Nº de cajas: @L@@@    Nº líneas: @L@@    Fecha de fabricación: ¿D-MM-Y.YY
  
 ÏÄ Seguimiento ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË 
 ³ Captura:   ¿D-MM-Y.YY  ________    Validación:  ¿D-MM-Y.YY  ________   Completada:  #L#.### %                          ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 
  Estado: @@@@@  _30____________________________ Ultima modificación: _32_______ ¿D-MM-Y.YY  ________ Comentario: @@@@@@@@@ 
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
CAMPO=SEQORDKIT,TOOLTIP("Versión del kit")
CAMPO=TIPOORDKIT,TOOLTIP("Tipo de orden: Producción: PROM, Desmontaje:PROD")
CAMPO=CODART,UPPER,TOOLTIP("Es el Código del artículo ordenado a tratar"),TITULO("Artículo a componer/destruir"),
        POSTCHANGE=FDESIGNACION("+CDESART","Código de artículo no existe.")
CAMPO=DESART,AUXILIAR,UPPER,NOENTER
CAMPO=CODLOT,UPPER,TOOLTIP("Código de lote"),TITULO("LOTE")
CAMPO=CANTIDAD,TOOLTIP("Total de unidades solicitadas"),TITULO("CANTIDAD"),POSTCHANGE=FEJECUTA("CSELPORCENCOMPLETA","ERROR CALCULANDO PORCENTAJE COMPLETAD0 DE LA SERIE")
CAMPO=CODPROVE,TOOLTIP("Identificador de la empresa responsable de la orden"),TITULO("Cod. Proveedor")
CAMPO=CODDIV,TOOLTIP("División"),TITULO("División")
CAMPO=NUMCAJAS,TOOLTIP("Número total de cajas que componen el kit"),TITULO("Nº de cajas")
CAMPO=NLINEAS,AUXILIAR,TOOLTIP("Es el número original de líneas de la orden que se recibio del host."),TITULO("Nº líneas")
CAMPO=FECFABKIT,TOOLTIP("Fecha en la que debe haberse terminado la orden de kitting")
CAMPO=FECCAPTURA,NOENTER,TOOLTIP("Fecha de captura de la orden")
CAMPO=HORACAPTURA,NOENTER,TOOLTIP("Hora de captura de la orden")
CAMPO=FECVALIDA,NOENTER,TOOLTIP("Fecha de validación de la orden")
CAMPO=HORAVALIDA,NOENTER,TOOLTIP("Hora de validación de la orden")
CAMPO=PORCENCOMPLETA,NOENTER,AUXILIAR,TOOLTIP("Porcentaje completado de la orden de porducción")
CAMPO=STATUS,TOOLTIP("Es el estado en que se encuentra la orden en el momento de la consulta."),POSTCHANGE=FDESIGNACION("CDESSTATUS","Estado incorrecto."),COMBOX("CLISTASTATUS"),COMBOXREGPAG=6
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripción del estado en el que se encuentra la orden")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizO la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la última modificacion")
CAMPO=CODCOMEN,NOENTER,TOOLTIP("Código de los comentarios a la cabecera del pedido")
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