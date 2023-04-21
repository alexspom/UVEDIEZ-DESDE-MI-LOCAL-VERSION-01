#*****************************************************************
#Módulo: VDORDRECCAB.PAN
#Función : Mantenimiento y consulta de las Ordenes de recepción
#Autor: ICC      
#Fecha: 13-02-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
ALTA DE ORDENES DE RECEPCION

 Division:  _20___    _40______________________________________
 Orden:     _20______________ Código de Ord. Cliente:_60_______
 Tipo:      _10_________  _40__________________________________
 Proveedor: _20_________  _60__________________________________
 Descargar: _20_________  
 Fecha:     ¿D-MM-Y.YYY
 Creacion:  ¿D-MM-Y.YYY ________
 Estado:    @L@@@@ _40___________________________________
 Utima modificacion: _32__________ ¿D-MM-Y.YY ________

|
TABLA=VDORDRECCAB
WLONX=475
WHERE=STATUS<VDST.FORCACTIVA;
#PROTECT("IMPLANTADOR")

#NOINSERT,PROTECT("ORDENESRECEP")
#NODELETE,PROTECT("ORDENESRECEP")
#NOUPDATE,PROTECT("ORDENESRECEP")


PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION",
                   "CSELINSERT","ERROR AL OBTENER LOS DATOS DE INSERCION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")


CAMPO=CODDIV,TOOLTIP("Código de la división/compañía.División ':DESDIV'"),TITULO("División"),WLONX=27,COMBOX("CSELDIV"),POSTCHANGE=FEJECUTA("+CSELDESDIV","")
CAMPO=DESDIV,AUXILIAR,NOENTER             
CAMPO=CODORDREC,TOOLTIP("Código de la orden de recepción"),TITULO("Orden de Recepción"),NOENTER  
CAMPO=CLAVEEXT,TOOLTIP("Código de Orden del cliente")
CAMPO=TIPORDREC,TOOLTIP("Es el tipo de orden de recepción. Existirá en la tabla VDTIPORDREC"),TITULO("Tipo orden"),WLONX=20,COMBOX("CSELTIPOREC"),POSTCHANGE=FEJECUTA("+CSELDESTIPO","")
CAMPO=DESORDREC,AUXILIAR,NOENTER
#CAMPO=CODPROVE,TOOLTIP("Es el Código del proveedor "),TITULO("Proveedor"),COMBOX("CLISTAPROVE"),POSTCHANGE=FEJECUTA("CSELDESPROV","NO EXISTE PROVEEDOR")
CAMPO=CODPROVE,TOOLTIP("Es el Código del proveedor "),TITULO("Proveedor"),POSTCHANGE=FEJECUTA("CSELDESPROV","NO EXISTE PROVEEDOR")
CAMPO=DESPROVE,TOOLTIP("Es la denominación del proveedor "),TITULO(""),NOENTER
CAMPO=VDEXTRA,TOOLTIP("Área donde se debe recepcionar la mercancía"),COMBOX("CSELAREA"), POSTCHANGE=FEJECUTA("CVERAREA","No existe el area seleccionado")
#CAMPO=SWTLICENCIA,TOOLTIP("Indica si la orden necesita licencia de exportacion"),CHECKBOX("N","S")
#CAMPO=LICENCIA,TOOLTIP("Codigo de la licencia de exportacion")
#CAMPO=REFCODPED,TOOLTIP("Indica el pedido al que corresponde si procede de un error"),POSTCHANGE=FDESIGNACION("CSELREFPED","Pedido no existe")
#CAMPO=DESCLIREF,TOOLTIP("Destinatario del pedido"),AUXILIAR,NOENTER
CAMPO=FECORDREC,TOOLTIP("Fecha original de la orden de recepción. Vendrá informado en la interfase"),TITULO("F.orden"),COMBOX("CALENDARIO")
CAMPO=FECCREADO,TOOLTIP("Es la fecha de creación de la orden en el sistema "),TITULO("F. creación")
CAMPO=HORACREADO,TOOLTIP("Es la hora de creación de la orden en el sistema ")
CAMPO=STATUS,PROTECT("IMPLANTADOR"),TOOLTIP("Es el estado en el que se encuentra la orden de recepción"),TITULO("Estado"),POSTCHANGE=FDESIGNACION("+CSELSTATUS","No existe estado"),NOENTER
CAMPO=DESSTATUS,AUXILIAR,NOENTER
CAMPO=CODOPEMODIF,TOOLTIP("Usuario que ha realizado la Ultima modificación.Es utilizado para depuración y control de los registros en las tablas"),TITULO("Ultima modificación")
CAMPO=FECMODIF,TOOLTIP("Es la fecha  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=HORAMODIF,TOOLTIP("Es la hora  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")

CURSOR=CSELDIV SELECT CODDIV, DESDIV FROM VDDIVIS;
CURSOR=CSELDESDIV SELECT DESDIV FROM VDDIVIS WHERE CODDIV=:CODDIV;
CURSOR=CSELTIPOREC SELECT TIPORDREC, DESORDREC FROM VDTIPORDRECCAB;
CURSOR=CSELDESTIPO SELECT DESORDREC FROM VDTIPORDRECCAB WHERE  TIPORDREC=:TIPORDREC;
CURSOR=CSELREFPED SELECT DESCLIENTE DESCLIREF
                   FROM VDPEDIDOCAB
                   WHERE CODPED=:REFCODPED
                  UNION
                   SELECT '' FROM DUAL WHERE :REFCODPED IS NULL;						 
                               
CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='ORC';                         

CURSOR=CLISTAPROVE SELECT CODPROVE, DESPROVE, NIF FROM VDPROVEEDOR ORDER BY DESPROVE;                  

CURSOR=CSELDESPROV SELECT DESPROVE FROM VDPROVEEDOR WHERE CODPROVE=:CODPROVE UNION SELECT '' FROM DUAL WHERE :CODPROVE IS NULL;

CURSOR=CSELINSERT SELECT VDST.FORCPENRECEP STATUS, VD.FECHASYS FECCREADO, VD.HORASYS HORACREADO,
                         DECODE(:FECORDREC, 0, VD.FECHASYS,:FECORDREC) FECORDREC,
                         NVL(:CODORDREC,'M'||VDSECORDREC.NEXTVAL) CODORDREC
                    FROM DUAL;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELDESSTATUS SELECT DESSTATUS
                       FROM VDSTATUS 
                      WHERE STATUS     = :STATUS
                        AND TIPOSTATUS = 'ORC';                        

CURSOR=CIMPREETIQ DECLARE
                   RET NUMBER;
                   MICODIMPRE VARCHAR2(100);
                  BEGIN
                    VDIMPRIME.IMPRIME('ETIQ','VDORDRECEP.ZPL;VDETIQUETAS.VSQ;CSELORDEN','CODORDREC='||:CODORDREC,1,MICODIMPRE,'',RET);    
                    COMMIT;
                  END;@                       

CURSOR=CSELAREA SELECT CODUBI FROM VDUBICA WHERE CODAREA LIKE 'RECEP%' AND STOCK='S';
CURSOR=CVERAREA SELECT :VDEXTRA FROM VDUBICA WHERE CODUBI=:VDEXTRA UNION SELECT :VDEXTRA FROM DUAL WHERE :VDEXTRA IS NULL;  
TECLA=CF1,FEJECUTA(FIMPRIME("INFORME","VDRECEPCION.RPT","CODDIV=:CODDIV;CODORDREC=:CODORDREC",""),":V10ERROR",FCOMMIT,"")

TECLA=SF1,FEJECUTA("CIMPREETIQ",":V10ERROR")

BOTON=B3,490,45,50,50,"P",apply.png,SF3,"Genera PDF Albaran",INCLUDECSS="background-color: transparent;border-width:0px"

