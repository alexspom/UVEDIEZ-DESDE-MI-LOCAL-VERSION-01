#*****************************************************************
#Módulo: VDORDRECLIN.PAN
#Funcionalidad : 
#Autor: ICC      
#Fecha: 13-02-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
MANTENIMIENTO DE LAS LÍNEAS DE LA ORDEN DE RECEPCION

Línea Artículo                       Cantidad    Lote         Tipo lote  Caducidad            Etiq. %Rec F.Pr.recep  %Exc %Def Estado Clave ext Última modificación             
##### _40____________ _100__________ ########### _40_________ _10_______ _8______  #L####### _10__ ##### ###  ¿D-MM-Y.YYY ###  ###  #####  _50______ _32_______ ¿D-MM-Y.YYY _8______
|
WLONX=1400
TABLA=VDORDRECLIN



POSTQUERY=FEJECUTA("CPORCENTAJERECEP", "ERROR AL CALCULAR EL PORCENTAJE RECEPCIONADO",
                   "CNETIQUETAS", "ERROR CALCULANDO EL NÚMERO DE ETIQUETAS A IMPRIMIR",
				   "+CCANTREC","ERROR CALCULANDO CANTIDAD RECEPCIONADA","+CCOLORES","")

PREINSERT=FEJECUTA("-CCADUCNULL","NO SE DEBE INFORMAR LA CADUCIDAD SI NO SE INFORMA EL LOTE",
                   "CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION",
                   "CSELINSERT","ERROR AL OBTENER LOS DATOS DE INSERCION")

PREUPDATE=FEJECUTA("-CCADUCNULL","NO SE DEBE INFORMAR LA CADUCIDAD SI NO SE INFORMA EL LOTE",
                   "CVALCANTIDAD","ERROR, LA CANTIDAD NO PUEDE SER INFERIOR A LA CANTIDAD YA RECEPCIONADA",
                   "CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=CODORDREC,VIRTUAL,OCULTO,TOOLTIP("Código de la orden de recepción")
CAMPO=CODDIV,VIRTUAL,OCULTO,TOOLTIP("Código de la división/compañía.Para permitir duplicidad de órdenes en distintas divisiones = interfases")
CAMPO=SECLINORD,NOENTER,TOOLTIP("Secuencia de registro. Pueden no ser consecutivos"),TITULO("Línea"),WLONX=15
CAMPO=CODART,POSTCHANGE=FDESIGNACION("CDESART","ERROR, NO EXISTE EL ARTICULO :CODART"),TOOLTIP("Código de artículo"),TITULO("Artículo"),
             CONTEXTUAL=FDESIGNACION(FEJECUTAFORM("VDARTIC","N","CODART=:CODART","","","","S"))   

CAMPO=DESART,NOENTER,AUXILIAR,TOOLTIP("Designacion")
CAMPO=CANTIDAD,TOOLTIP("Cantidad prevista a recibir"),TITULO("Cant.Ped.")
CAMPO=CODLOT,TOOLTIP("Lote previsto. Si esta informado la mercancía en recepción debe ser de dicho lote"),TITULO("Lote"),
             CONTEXTUAL=FDESIGNACION(FEJECUTAFORM("VDLOTES","N","CODART=:CODART","","CODLOT=:CODLOT","","S")),
             POSTCHANGE=FEJECUTA("@COBTCADUCI","")
CAMPO=TIPOLOTE,TOOLTIP("Indica el tipo de lote. Es útil cuando se distinguen lotes de venta, fabricante, etc..."),TITULO("Tipo Lote")
CAMPO=CADUCI,TOOLTIP("Caducidad prevista. Si esta informada la mercancía en recepción debe ser de dicha caducidad"),TITULO("Caducidad"),WLONX=30,
             POSTCHANGE=FEJECUTA("+CVALCADUCI", "",
                                 "CVERERROR",":MSGERROR",
                                 "CVALCADUCI1", "ERROR, FORMATO INCORRECTO\nFORMATO CORRECTO AAAAMMDD")
CAMPO=CANTIDADR,AUXILIAR,TOOLTIP("Cantidad prevista a recibir"),TITULO("Cant.Rec.")
CAMPO=UNIDADESHOST,TOOLTIP("Unidad de medida en la que nos comunicamos con el host. Debe convertirse a cantidad V10"),NOENTER,TITULO("Unid.")
CAMPO=NETIQUETAS,AUXILIAR,TOOLTIP("Nº Etiquetas a imprimir"),TITULO("Etiq.")
CAMPO=PORCENTAJERECEP,AUXILIAR,TOOLTIP("Porcentaje ya recepcionado, sin tener en cuenta el exceso"),TITULO("Rec%"),WLONX=17
CAMPO=FECRECPRE,TOOLTIP("Fecha de recepcion prevista de la línea"),TITULO("F.Pr.Recep")
CAMPO=VDEXTRA,OCULTO,"_255_",TOOLTIP("Información adicional suministrada por el cliente")
CAMPO=TOLEREXC,TOOLTIP("Porcentaje de variación por exceso en la cantidad permitida en entradas.Valor null o negativo no aplica tolerancia"),TITULO("Exc%"),WLONX=17
CAMPO=TOLERDEF,TOOLTIP("Porcentaje de variación por defecto en la cantidad permitida en entradas.En órdenes que admiten múltiples entradas no es aplicable.Valor null o negativo no aplica tolerancia"),TITULO("Def%"),WLONX=17
CAMPO=STATUS,PROTECT("IMPLANTADOR"),TOOLTIP("Status de la linea"),TITULO("Estado"),WLONX=20
CAMPO=CODCOMEN,OCULTO,"#########",TOOLTIP("Código de comentario")
CAMPO=CLAVEEXT,TOOLTIP("Clave externa que permite relacionar con otros sistemas no definidos"),TITULO("Claveext")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que ha realizado la Última modificación.Es utilizado para depuración y control de los registros en las tablas"),TITULO("Última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=MSGERROR,AUXILIAR,OCULTO,"_100______"
CAMPO=DUMMY,AUXILIAR,OCULTO,"#"
CAMPO=UNIEMB,AUXILIAR,OCULTO,"###############"

CURSOR=CCANTREC SELECT SUM(CANTIDADR) CANTIDADR
				FROM VDRECEPLIN
				WHERE CODORDREC = :CODORDREC
				AND CODART = :CODART;

CURSOR=CPORCENTAJERECEP SELECT (:CANTIDAD-VDRECEP.CANTPDTE(:CODORDREC, :CODART, :CODDIV, :CODLOT, :SECLINORD, 'N'))*100/DECODE(:CANTIDAD,0,1,:CANTIDAD) PORCENTAJERECEP
                          FROM DUAL;

CURSOR=CNETIQUETAS SELECT CEIL(:CANTIDAD/DECODE(UNIEMB,0,1,UNIEMB)) NETIQUETAS, UNIEMB
                     FROM VDARTIC
                    WHERE CODART=:CODART;
                    
CURSOR=CDESART SELECT DESART, UNIDADESHOST FROM VDARTIC WHERE CODART=:CODART;

CURSOR=CCADUCNULL SELECT 1 DUMMY
                    FROM DUAL
                   WHERE TRIM(:CODLOT) IS NULL
                     AND :CADUCI IS NOT NULL;

CURSOR=COBTCADUCI SELECT DECODE(:CADUCI,NULL,CADUCI, :CADUCI) CADUCI
                    FROM VDLOTES
                   WHERE (CODART = :CODART
                      AND CODLOT = :CODLOT)
                      OR :CADUCI IS NOT NULL;

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
                      FROM VDORDRECLIN
                     WHERE CODORDREC = :CODORDREC
                       AND CODDIV    = :CODDIV
                       AND SECLINORD = :SECLINORD
                       AND :CANTIDAD >= (CANTIDAD - VDRECEP.CANTPDTE(:CODORDREC, :CODART, :CODDIV, :CODLOT, :SECLINORD, 'S'));

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF,DECODE(:FECRECPRE,0,VD.FECHASYS,:FECRECPRE) FECRECPRE  FROM DUAL;

CURSOR=CCOLORES SELECT CASE WHEN :PORCENTAJERECEP>=100 THEN 19 ELSE 22 END PORCENTAJERECEP__COLOR FROM DUAL;

CURSOR=CCHECKUNIEMB SELECT :UNIEMB UNIEMB FROM DUAL WHERE :UNIEMB > 0;

CURSOR=CPRINTETIQ BEGIN
               VDIMPRIME.IMPRIME('ETIQ', 'VDARTIC.GEN;VDETIART.VSQ;CSELART', 'CODART='||:CODART||';CODLOT='||:CODLOT||';UNIEMB='||:UNIEMB,1,  '', '', :V10ERROR);               
			   COMMIT; 
             END;@


#Imprimir etiquetas
TECLA=CF1,FEJECUTA("CCHECKUNIEMB","EL NUMERO DE UNIDADES POR EMBALAJE\n DEBE SER MAYOR QUE CERO",
                   "CPRINTETIQ","ERROR AL IMPRIMIR")
				   
				   
CONTEXTUAL=FEJECUTAFORM("VDARTIC","S","CODART=:CODART")				   

