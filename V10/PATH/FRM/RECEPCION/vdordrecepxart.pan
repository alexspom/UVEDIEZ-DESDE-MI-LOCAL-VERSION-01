#*****************************************************************
#Módulo: VDORDRECEPXART.PAN
#Funcionalidad : 
#Autor: ICC      
#Fecha: 13-02-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
ORDEN DE RECEPCION POR ARTICULO

Orden de recepción   Div.  Línea  Artículo                           Lote                 Tipo lote   Caducidad Cantidad              F.Pr.recep  Exc Def Estado Clave ext Ultima modificación             
_20_________________ _20_  ###### _40_______________ _100__________  _40_________________ _10_______  _8______  ############# _10____ ¿D-MM-Y.YYY ### ###  #####  _50______ _32_______ ¿D-MM-Y.YYY _8______     
|
TABLA=VDORDRECLIN         
ORDERBY=CODORDREC,CODDIV,CODART;



PREINSERT=FEJECUTA("-CCADUCNULL","NO SE DEBE INFORMAR LA CADUCIDAD SI NO SE INFORMA EL LOTE",
                   "CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION",
                   "CSELINSERT","ERROR AL OBTENER LOS DATOS DE INSERCION")

PREUPDATE=FEJECUTA("-CCADUCNULL","NO SE DEBE INFORMAR LA CADUCIDAD SI NO SE INFORMA EL LOTE",
                   "CVALCANTIDAD","ERROR, LA CANTIDAD NO PUEDE SER INFERIOR A LA CANTIDAD YA RECEPCIONADA",
                   "CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=CODORDREC,TOOLTIP("Código de la orden de recepción"),TITULO("Orden de recepción")
CAMPO=CODDIV,TOOLTIP("Código de la division/compañia.Para permitir duplicidad de ordenes en distintas divisiones = interfases"),TITULO("Div.")
CAMPO=SECLINORD,NOENTER,TOOLTIP("Secuencia de registro. Pueden no ser consecutivos"),TITULO("Línea")
CAMPO=CODART,POSTCHANGE=FDESIGNACION("CDESART","ERROR, NO EXISTE EL ARTICULO :CODART"),TOOLTIP("Código de articulo"),
             CONTEXTUAL=FDESIGNACION(FEJECUTAFORM("VDARTIC","N","CODART = :CODART OR CODART=NVL(:CODART, CODART)","","CODART=:CODART","","S")),
             TITULO("Artículo")
CAMPO=DESART,NOENTER,AUXILIAR,TOOLTIP("Designacion")
CAMPO=CODLOT,TOOLTIP("Lote previsto. Si esta informado la mercancia en recepcion debe ser de dicho lote"),
             CONTEXTUAL=FDESIGNACION(FEJECUTAFORM("VDLOTES","N","CODART=:CODART","","CODLOT=:CODLOT CADUCI=:CADUCI","","S")),
             TITULO("Lote")
CAMPO=TIPOLOTE,TOOLTIP("Indica el tipo de lote. Es útil cuando se distinguen lotes de venta, fabricante, etc..."),TITULO("Tipo Lote")
CAMPO=CADUCI,TOOLTIP("Caducidad prevista. Si esta informada la mercancia en recepcion debe ser de dicha caducidad"),WLONX=25,
             POSTCHANGE=FEJECUTA("+CVALCADUCI", "",
                                 "+CVERERROR",":MSGERROR",
                                 "CVALCADUCI1", "ERROR, FORMATO INCORRECTO\nFORMATO CORRECTO AAAAMMDD"),TITULO("Caducidad"),NOUPDATE
CAMPO=CANTIDAD,TOOLTIP("Cantidad prevista a recibir"),TITULO("Cantidad")
CAMPO=UNIDADESHOST,TOOLTIP("Unidad de medida en la que nos comunicamos con el host. Debe convertirse a cantidad V10")
CAMPO=FECRECPRE,TOOLTIP("Fecha de recepcion prevista de la linea"),TITULO("F.Pr.Recep")
CAMPO=VDEXTRA,OCULTO,"_255_",TOOLTIP("Información adicional suministrada por el cliente")
CAMPO=TOLEREXC,TOOLTIP("Porcentaje de variacion por exceso en la cantidad permitida en entradas.Valor null o negativo no aplica tolerancia"),TITULO("Exc"),WLONX=7
CAMPO=TOLERDEF,TOOLTIP("Porcentaje de variacion por defecto en la cantidad permitida en entradas.En ordenes que admiten multiples entradas no es aplicable.Valor null o negativo no aplica tolerancia"),TITULO("Def"),WLONX=7
CAMPO=STATUS,PROTECT("IMPLANTADOR"),TOOLTIP("Status de la linea"),TITULO("Estado"),WLONX=20
CAMPO=CODCOMEN,OCULTO,"#########",TOOLTIP("Código de comentario")
CAMPO=CLAVEEXT,TOOLTIP("Clave externa que permite relacionar con otros sistemas no definidos"),TITULO("Clave Ext."),WLONX=30
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que ha realizado la ultima modificación.Es utilizado para depuración y control de los registros en las tablas"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=MSGERROR,AUXILIAR,OCULTO,"_100______"
CAMPO=DUMMY,AUXILIAR,OCULTO,"#"

CURSOR=CDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;

CURSOR=CCADUCNULL SELECT 1 DUMMY
                    FROM DUAL
                   WHERE TRIM(:CODLOT) IS NULL
                     AND :CADUCI IS NOT NULL;

CURSOR=CVALCADUCI SELECT DECODE(CADUCI, :CADUCI,'','ERROR,\nLA CADUCIDAD NO PUEDE SER DISTINTA A LA DEL LOTE YA CREADO') MSGERROR
                    FROM VDLOTES
                   WHERE CODLOT = :CODLOT
                     AND CODART = :CODART
                     AND :CADUCI IS NOT NULL;

CURSOR=CVERERROR SELECT 1 DUMMY FROM DUAL WHERE TRIM(:MSGERROR) IS NULL;                       

CURSOR=CVALCADUCI1 SELECT 1 DUMMY
                     FROM DUAL
                    WHERE VD.FECHAOK(:CADUCI, 'YYYYMMDD') = 0;

CURSOR=CSELINSERT SELECT NVL(MAX(SECLINORD),0)+1 SECLINORD, VDST.FORLACTIVA STATUS 
                    FROM VDORDRECLIN
                   WHERE CODORDREC = :CODORDREC
                     AND CODDIV    = :CODDIV;

CURSOR=CVALCANTIDAD SELECT 1 DUMMY
                      FROM DUAL
                     WHERE :CANTIDAD >= VDRECEP.CANTRECEP(:CODORDREC, :CODART, :CODDIV, :CODLOT);

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF  FROM DUAL;


