#*****************************************************************
#MOdulo: VDORDRECCAB.PAN
#Función : Mantenimiento y consulta de las Ordenes de recepción
#Autor: ICC      
#Fecha: 13-02-2008
#*****************************************************************
#* HistOrico de cambios
#* ====================
MANTENIMIENTO DE LAS ORDENES DE RECEPCION

Orden de recepción   Clave ext.       Division Tipo orden   Cod.Prove.  Proveedor           F. orden    F. creación          Estado Muelle           AREA RECEP.   Ultima modificación             
_20_________________ _50_____________ _20____   _10_______  _20________ _60________________ ¿D-MM-Y.YYY ¿D-MM-Y.YYY _8______ #####  _255____________ _20__________ _32_______ ¿D-MM-Y.YYY _8______
|
TABLA=VDORDRECCAB
ORDERBY=CASE WHEN STATUS>=7000 THEN 1 ELSE 0 END,FECCREADO DESC, HORACREADO DESC;
WLONX=1400

POSTQUERY=FEJECUTA("CPONPRIVILEGIOS", "ERROR PONIENDO PRIVILEGIOS",
                   "CPONPRIVILEGIOS2", "ERROR PONIENDO PRIVILEGIOS 2")

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION",
                   "CSELINSERT","ERROR AL OBTENER LOS DATOS DE INSERCION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=CODORDREC,TOOLTIP("Código de la orden de recepción"),TITULO("Orden de Recepción")
CAMPO=CLAVEEXT,TOOLTIP("Clave externa que permite relacionar con otros sistemas no definidos"),TITULO("Ord.Cliente")
CAMPO=CODDIV,TOOLTIP("Código de la division/compañía.Division ':DESDIV'"),TITULO("Division"),WLONX=27,
             POSTCHANGE=FEJECUTA("CDESDIVIS","ERROR, LA DIVISION :CODDIV NO EXISTE"),
             CONTEXTUAL=FDESIGNACION(FEJECUTAFORM("VDDIVIS","N","","","CODDIV=:CODDIV","","S"))   
CAMPO=TIPORDREC,TOOLTIP("Es el tipo de orden de recepción. Existirá en la tabla VDTIPORDREC"),TITULO("Tipo orden"),WLONX=20,
                CONTEXTUAL=FDESIGNACION(FEJECUTAFORM("VDTIPORDRECCAB","N","","","TIPORDREC=:TIPORDREC","","S"))   
CAMPO=CODPROVE,TOOLTIP("Es el Código del proveedor "),TITULO("Cod.Prov."),CONTEXTUAL=FEJECUTAFORM("VDPROVEEDORES","","CODPROVE=:CODPROVE")
CAMPO=DESPROVE,TOOLTIP("Es la denominación del proveedor "),TITULO("Proveedor") 
CAMPO=FECORDREC,TOOLTIP("Fecha original de la orden de recepción. Vendrá informado en la interfase"),TITULO("F.orden"),COMBOX("CALENDARIO")
CAMPO=FECCREADO,TOOLTIP("Es la fecha de creación de la orden en el sistema "),TITULO("F. creación")
CAMPO=HORACREADO,TOOLTIP("Es la hora de creación de la orden en el sistema ")
CAMPO=STATUS,PROTECT("IMPLANTADOR"),TOOLTIP("Es el estado en el que se encuentra la orden de recepción"),TITULO("Estado"),WLONX=15
CAMPO=VDEXTRA,TOOLTIP("Muelle de recepcion"),TITULO("Muelle"),COMBOX("CSELAREA"), POSTCHANGE=FEJECUTA("CVERAREA","No existe el area seleccionado")
CAMPO=CODAREARECEP,TOOLTIP("Area donde se debe recepcionar la mercancía"),TITULO("Area Recep.")
CAMPO=CODOPEMODIF,TOOLTIP("Usuario que ha realizado la Ultima modificación.Es utilizado para depuración y control de los registros en las tablas"),TITULO("Ultima modificación")
CAMPO=FECMODIF,TOOLTIP("Es la fecha  en que se efectuO alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=HORAMODIF,TOOLTIP("Es la hora  en que se efectuO alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=CODCOMEN,OCULTO,"#########",TOOLTIP("")
CAMPO=DESDIV,AUXILIAR,OCULTO,"_40_"
CAMPO=TENGOPRIV,AUXILIAR,OCULTO,"#"

CURSOR=CPONPRIVILEGIOS SELECT VDUSER.TENGOPRIVILEGIO(RANGOPRIVILEGIO) TENGOPRIV
                         FROM VDTIPORDRECCAB
                        WHERE TIPORDREC = :TIPORDREC;
                        
CURSOR=CPONPRIVILEGIOS2 SELECT :TENGOPRIV CODORDREC__ENTER, :TENGOPRIV CODDIV__ENTER, :TENGOPRIV TIPORDREC__ENTER,
                               :TENGOPRIV CODPROVE__ENTER, :TENGOPRIV DESPROVE__ENTER, :TENGOPRIV FECORDREC__ENTER,
                               :TENGOPRIV FECCREADO__ENTER, :TENGOPRIV HORACREADO__ENTER, :TENGOPRIV CLAVEEXT__ENTER
                          FROM DUAL;

CURSOR=CDESDIVIS SELECT DESDIV
                   FROM VDDIVIS
                  WHERE CODDIV = :CODDIV;

CURSOR=CSELINSERT SELECT VDST.FORCACTIVA STATUS, VD.FECHASYS FECCREADO, VD.HORASYS HORACREADO,
                         DECODE(TRIM(:FECORDREC), NULL, VD.FECHASYS,0, VD.FECHASYS,TRIM(:FECORDREC)) FECORDREC 
                    FROM DUAL;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CSELDESSTATUS SELECT DESSTATUS
                       FROM VDSTATUS 
                      WHERE STATUS     = :STATUS
                        AND TIPOSTATUS = 'ORC';

CURSOR=CSELAREA SELECT CODUBI FROM VDUBICA WHERE CODAREA LIKE 'RECEP%' AND STOCK='S';
CURSOR=CVERAREA SELECT :VDEXTRA FROM VDUBICA WHERE CODUBI=:VDEXTRA UNION SELECT :VDEXTRA FROM DUAL WHERE :VDEXTRA IS NULL;                        

						
TECLA=SF8,FEJECUTA(FIMPRIME("INFORME","VDRECEPCION.RPT","CODDIV=:CODDIV;CODORDREC=:CODORDREC",""),":V10ERROR",FCOMMIT,"")
TECLA=SF9,FEJECUTAFORM("VDINCIDENCIAS","S","CLAVEINCI=:CODCOMEN","CLAVEINCI=:CODCOMEN TIPOCLAVEINCI='ORC' DESTIPOCLAVEINCI='ORD.RECEPCIÓN' CODTRA=:CODORDREC")
