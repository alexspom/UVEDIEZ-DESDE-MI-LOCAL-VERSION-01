# Módulo   : VDRECCANTIDAD.PAN
# Función  : RECEPCIÓN DE MERCANCÍA:Introducción de la cantidad a recepcionar y demás datos
#            Validaciones:
#              - Unidad de medida: por defecto mostrará el valor VDARTIC.UNIDADESHOST, si se 
#                modifica deberá existir.
#              - Bulto: En caso de trazabilidad, el operario leerá el código de bulto, este no
#                deberá existir en el stock.
#              - x/n: x indicará el número de bulto que está recepcionando, y n el número de
#                bultos totales que debe leer.
#              - u/e: unidades por embalaje, se mostrará si se ha leído el código de barras o   
#                si  vdartic.uniemb > 0,  pero siempre se podrá modificar.
#              - emb: nº de embalajes a recepcionar, en caso de trazabilidad de bulto, se 
#                obligará que sea 1.
#              - Pico: cantidad que no llega a un embalaje completo, también se podrá poner
#                toda la cantidad y en función de u/e se calcularán el número de embalajes.
#              - Nº Muestras: Si vdartic.nmuestras> 0, se mostrará este campo indicando el
#                valor por defecto, el cual se podrá modificar dependiendo de la variable 
#                MUESTRAS_MODIF (S/N).
#              -  El lote debe existir, a no ser que por el tipo de recepción se dé de alta 
#                 automáticamente.
#              - Caducidad: 
#                Si se ha introducido en la orden de recepción, comprobar que coincide con este.
#                Si existe el lote: validar que coincide con el del lote?
#                Si no existe, validar el formato para dar de alta el lote
#              - La cantidad que se va a recepcionar no debe sobrepasar la cantidad a
#                recepcionar por la órden de recepción, teniendo en cuenta el % de exceso.
#            
# Creación : 01-02-2008
# Autor    : ICC
###########################################
# Histórico de cambios:
# 
CANTIDAD A RECEPCIONAR
 _10_______ _10_______
ART.: _20_________________
_30_______________________
_30_______________________
_6____ _18________ _7_____
U/E        EMB  
#L#######  #### 
_12_________ ######

__________________

_5___ _20_________________
_10_______ _8______

ALTURA PALET  : ###  CM
PESO PALET: #L##.### KG

(1) Continuar
(2) Retroceder OPCION:#

|


PREQUERY=FEJECUTA(FIF("CSELPANTANT", FSUCCESS,
                                     FEJECUTA("CLIMPIAR","\nERROR,\nAL LIMPIAR LOS CAMPOS")),"",
                  "CSELART","\nERROR,\nOBTENIENDO DATOS\nDEL ARTICULO :CODART",
                  FIF("CHAYCADUCI","+CPONCADUCI",FSUCCESS),"ERROR TRATANDO CADUCIDAD",                  
                  "COCULTACAMPOS","",
                  "+CCALCPESO","\nERROR,\nNO SE PUEDE CALCULAR EL PESO",
                  "+CCALCPESOMOVIM","\nERROR AL CALCULAR EL PESO DEL MOVIMIENTO",
                  "+CCALALTPALET","\nERROR,\nPALET :TIPOCONTE NO TIENE\n EQUIVALENCIA EN VDTIPOCONTEEQ",
                  FIF("CSELNOTNULLORDEN", FEJECUTA("-CVALDIASRECEP",":MSGERROR")),"",
                  FPOSICIONACAMPO(FSUCCESS,"EMBCONT"),"\nERROR,\nAL POSICIONARSE EN \nEL CAMPO EMBCONT",
                  FPOSICIONACAMPO("CSELGRAMOS","PESO"),"\nERROR,\nAL POSICIONARSE EN \nEL CAMPO PESO",
                  FPOSICIONACAMPO("CSELTODOS","OPCIONCANT"),"\nERROR,\nAL POSICIONARSE EN \nEL CAMPO OPCION",
                  FIF("CSELDATOSSSCC",FPOSICIONABLOQUE("VDRECVERIFCSF.PAN"),FSUCCESS),"")

POSTQUERY=FEJECUTA("CSELOPCIONCANT","SELECCIONE UNA OPCION\nENTRE 1 Y 2",
                   FIF("CSELOPCION2",FPOSICIONABLOQUE("VDRECPULMONCSF.PAN"),FSUCCESS),"",
                   FIF("CSELNOTNULL",FPOSICIONABLOQUE("VDRECARTICULOCSF.PAN"),FSUCCESS),"",
                   "-CVALBULTO","\nERROR,\nBULTO YA EXISTE",
                   "CVALEMBCONT","\nERROR,\nDEMASIADAS UNIDADES PARA\nEL CONTENEDOR\nMAXIMO :EMBCONT",
                   "CVALLOTEORD","\nERROR,\nEN PL VDRECEP.VALLOTEORDEN",      
                   "CVERERROR", "\nERROR\n:MSGERROR",
                   "CVALLOTE","\nERROR,\n:EN PL VDRECEP.VALLOTE",
                   "CVERERROR", "\nERROR\n:MSGERROR",
                   "-CVALDIASRECEP","\nERROR\n:MSGERROR",
                   "CVALCANT", "\nERROR,\nSE SOBREPASA LA CANTIDAD\nA RECEPCIONAR EN LA ORDEN",
                   "-CCANTIDAD", "\nERROR,\nNO HA INFORMADO LA CANTIDAD A RECEPCIONAR",
                   "CSELPESOCERO","EL PESO NO \nPUEDE SER 0",
                   FPOSICIONABLOQUE("VDRECVERIFCSF.PAN"),"\nNO SE PUEDE POSICIONAR\nEN EL SIG. BLOQUE")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODRECEP,VIRTUAL,OCULTO
CAMPO=CODMAT,VIRTUAL,OCULTO
CAMPO=CODART,NOENTER,VIRTUAL
CAMPO=DESART1,NOENTER
CAMPO=DESART2,NOENTER
CAMPO=UNIDADESHOST,NOENTER,OCULTO,"_10_______"
CAMPO=UNIDADES,NOENTER,OCULTO,"_10_______"
CAMPO=NBULTO,NOENTER
CAMPO=BULTO,SCAN
CAMPO=MUESTRABULTOS,NOENTER
CAMPO=UNIEMB,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=EMBCONT,VIRTUAL,POSTCHANGE=FDESIGNACION("CCALALTPALET","\nERROR,\nPALET :TIPOCONTE NO TIENE\n EQUIVALENCIA EN VDTIPOCONTEEQ",
                                              "+CCALCPESO","\nERROR,\nNO SE PUEDE CALCULAR EL PESO",
                                              "+CCALCPESOMOVIM","\nERROR,\nAL CALCULAR EL PESO DEL MOVIMIENTO")
CAMPO=PICO,OCULTO,"#L########",CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),
                               POSTCHANGE=FDESIGNACION("CCALALTPALET","\nERROR,\nPALET :TIPOCONTE NO TIENE\n EQUIVALENCIA EN VDTIPOCONTEEQ")
CAMPO=NNMUESTRAS,NOENTER
CAMPO=NUMMUESTRAS,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=SSCC,VIRTUAL
CAMPO=CODALBPROVE,VIRTUAL,OCULTO 
CAMPO=NCODLOT,NOENTER
CAMPO=CODLOT,VIRTUAL,POSTCHANGE=FDESIGNACION("+CSELCADUCI","\nERROR\nCALCULANDO LA CADUCIDAD")
CAMPO=NCADUCI,NOENTER
CAMPO=CADUCI,VIRTUAL
CAMPO=ALTPALET
CAMPO=PESO,VIRTUAL,POSTCHANGE=FDESIGNACION("CCALCPESO","\nERROR,\nCALCULANDO UNIDADES")
CAMPO=PESOMOVIM,OCULTO,"#L##.##########"
CAMPO=TIPOEMBA,OCULTO,VIRTUAL
CAMPO=MULTIARTICULO,OCULTO,VIRTUAL
CAMPO=PULMON,OCULTO,VIRTUAL
CAMPO=CODDIV,OCULTO,VIRTUAL
CAMPO=CODORDREC,OCULTO,VIRTUAL
CAMPO=TIPORDREC,OCULTO,VIRTUAL
CAMPO=NBULTOS,OCULTO,VIRTUAL
CAMPO=CONTBULTOS,OCULTO,VIRTUAL
CAMPO=DESDIV,OCULTO,VIRTUAL
CAMPO=TIPOCONTE,OCULTO,VIRTUAL
CAMPO=TRAZABULTO,OCULTO,"_"
CAMPO=DIASANTFECPREV,OCULTO,VIRTUAL
CAMPO=DIASRETFECPREV,OCULTO,VIRTUAL
CAMPO=ESTADOS_STOCK, OCULTO,VIRTUAL
CAMPO=INDLOTE,  OCULTO,VIRTUAL
CAMPO=MUESTREAR,OCULTO,VIRTUAL
CAMPO=PRECIOUNI,OCULTO,VIRTUAL
CAMPO=PANTANTERIOR,OCULTO,VIRTUAL
CAMPO=MSGERROR, OCULTO,"_100______"
CAMPO=DUMMY,OCULTO,"#"
#CAMPO=STATUSREC1,NOENTER
CAMPO=OPCIONCANT

CURSOR=CHAYCADUCI SELECT :CADUCI
                    FROM DUAL
                   WHERE :CADUCI IS NOT NULL;
                   
CURSOR=CPONCADUCI SELECT '20'||:CADUCI CADUCI
                    FROM DUAL
                   WHERE LENGTH(:CADUCI)=6;
  
CURSOR=CSELPANTANT SELECT 1 DUMMY FROM DUAL WHERE :PANTANTERIOR = 'VDRECVERIFCSF.PAN';


CURSOR=CLIMPIAR SELECT '' UNIDADESHOST, '' BULTO, 0 PICO, 0 NUMMUESTRAS, '' ALTPALET, 'VDRECCANTIDAD.PAN' PANTANTERIOR,
                       :CONTBULTOS+1||'/'||:NBULTOS MUESTRABULTOS, 0 PESOMOVIM, 1 OPCIONCANT
                  FROM DUAL;

CURSOR=CSELART SELECT NUMMUESTRAS,  UNIDADES, UNIDADESHOST, TRAZABULTO,PESOUNI UNIEMB,
                      VD.DIVIDEXBUSQUEDA (1, DESART, ' ', 20, 0) DESART1, VD.DIVIDEXBUSQUEDA (2, DESART, ' ', 20, 0) DESART2,
                      DECODE(:EMBCONT,0,EMBCONT,NULL,EMBCONT,:EMBCONT) EMBCONT
                 FROM VDARTIC
                WHERE CODART = :CODART;                 

CURSOR=COCULTACAMPOS SELECT DECODE(:INDLOTE, 'S', 0, 1) NCODLOT__INVISIBLE,
                            DECODE(:INDLOTE, 'S', 0, 1) CODLOT__INVISIBLE,
                            DECODE(:INDLOTE, 'S', 0, 1) NCADUCI__INVISIBLE,
                            DECODE(:INDLOTE, 'S', 0, 1) CADUCI__INVISIBLE,
                            DECODE(:MUESTREAR,'P', 0,
                                              'L',(SELECT DECODE(MUESTREADO,'N',0,1)
                                                       FROM VDLOTES WHERE CODART=:CODART
                                                                      AND CODLOT=:CODLOT ),
                                              'R',(SELECT DISTINCT DECODE(MUESTREADO,'N',0,1)
                                                       FROM VDRECEPLIN WHERE CODRECEP=:CODRECEP
                                                                         AND CODART=:CODART
                                                                         AND CODLOT=:CODLOT),
                                               1)  NNMUESTRAS__INVISIBLE,
                            DECODE(:MUESTREAR,'P', 0,
                                              'L',(SELECT DECODE(MUESTREADO,'N',0,1)
                                                       FROM VDLOTES WHERE CODART=:CODART
                                                                      AND CODLOT=:CODLOT ),
                                              'R',(SELECT DISTINCT DECODE(MUESTREADO,'N',0,1)
                                                       FROM VDRECEPLIN WHERE CODRECEP=:CODRECEP
                                                                         AND CODART=:CODART
                                                                         AND CODLOT=:CODLOT),
                                               1) NUMMUESTRAS__INVISIBLE,
                            DECODE(:MUESTREAR,'P', :NUMMUESTRAS,
                                              'L',(SELECT DECODE(MUESTREADO,'N',:NUMMUESTRAS,0)
                                                       FROM VDLOTES WHERE CODART=:CODART
                                                                      AND CODLOT=:CODLOT ),
                                              'R',(SELECT DISTINCT DECODE(MUESTREADO,'N',:NUMMUESTRAS,0)
                                                       FROM VDRECEPLIN WHERE CODRECEP=:CODRECEP
                                                                         AND CODART=:CODART
                                                                         AND CODLOT=:CODLOT),
                                               0) NUMMUESTRAS,
                            DECODE(:TRAZABULTO, 'S',0,1) NBULTO__INVISIBLE,
                            DECODE(:TRAZABULTO, 'S',0,1) BULTO__INVISIBLE,
                            DECODE(:TRAZABULTO, 'S',0,1) MUESTRABULTOS__INVISIBLE,
                            'Nº MUESTRAS:' NNMUESTRAS, 'LOTE:' NCODLOT, 'CADUCIDAD:' NCADUCI, 'BULTO:' NBULTO,
                            :DIASANTFECPREV, :DIASRETFECPREV
                        FROM DUAL;

CURSOR=CSELNOTNULLORDEN SELECT 1 DUMMY FROM DUAL WHERE :CODORDREC IS NOT NULL;

CURSOR=CSELNOTNULL SELECT 1 DUMMY FROM DUAL 
                    WHERE :BULTO IS NULL AND :EMBCONT = 0 AND :PICO = 0 AND :NUMMUESTRAS = 0;

CURSOR=CVALDIASRECEP SELECT CASE WHEN VD.FECHASYS < (FECRECPRE - :DIASANTFECPREV) THEN
                                      'NO SE PUEDEN EMPEZAR A\nRECEPCIONAR HASTA\n EL DIA '||TO_CHAR(TO_DATE((FECRECPRE - :DIASANTFECPREV),'J'), 'DD/MM/YYYY')
                                 WHEN VD.FECHASYS > (FECRECPRE + :DIASRETFECPREV) THEN
                                      'NO SE PUEDE RECEPCIONAR\nEL ULTIMO DIA\nFUE EL '||TO_CHAR(TO_DATE((FECRECPRE + :DIASRETFECPREV),'J'), 'DD/MM/YYYY')
                            END MSGERROR
                       FROM VDORDRECLIN
                      WHERE CODORDREC = :CODORDREC
                        AND CODDIV    = :CODDIV
                        AND CODART    = :CODART
                        AND CODLOT    = NVL(:CODLOT, CODLOT)
                        AND VD.FECHASYS NOT BETWEEN (FECRECPRE - :DIASANTFECPREV) AND (FECRECPRE + :DIASRETFECPREV)
                        AND FECRECPRE > 0;


CURSOR=CCALALTPALET SELECT ALTOCONTE/10 ALTPALET FROM VDTIPOCONTE WHERE TIPOCONTE = :TIPOCONTE;

#VALIDACIONES 
CURSOR=CVALBULTO SELECT 1 DUMMY
                   FROM VDMOVIM
                  WHERE BULTO = :BULTO
                    AND STATUS < 12999;

CURSOR=CVALEMBCONT SELECT 1 DUMMY
                     FROM DUAL
                    WHERE :EMBCONT*:UNIEMB >= (:UNIEMB*:EMBCONT) + :PICO;

CURSOR=CVALLOTE BEGIN VDRECEP.VALIDALOTE (:CODART, :CODLOT, :CADUCI, :TIPORDREC, 'N', :CODRECEP, :MSGERROR);
                END;@

#Valida el lote y la caducidad introducido en la recepción contra la orden de recepción     
CURSOR=CVALLOTEORD BEGIN VDRECEP.VALLOTEORDEN (:CODART, :CODLOT, :CADUCI, :CODORDREC, :CODDIV, :MSGERROR);
                   END;@

CURSOR=CVERERROR SELECT 1 DUMMY FROM DUAL WHERE :MSGERROR IS NULL;

CURSOR=CVALCANT SELECT 1 DUMMY
                  FROM DUAL
                 WHERE VDRECEP.CANTPDTE(:CODORDREC, :CODART, :CODDIV, :CODLOT, 0, 'S')  >= (:UNIEMB*:EMBCONT) + :PICO;

CURSOR=CCANTIDAD SELECT 1 DUMMY
                   FROM DUAL
                  WHERE :EMBCONT=0 AND :PICO=0 AND :NUMMUESTRAS=0;

CURSOR=CCALCPESO SELECT DECODE(UNIDADES,'UN',(:EMBCONT*PESOUNI/1000),:PESO) PESO,
                        DECODE(UNIDADES,'UN',:UNIEMB,:PESO/:EMBCONT*1000) UNIEMB
                 FROM VDARTIC WHERE CODART = :CODART;

CURSOR=CSELPESOCERO SELECT :PESO FROM DUAL WHERE :PESO>0;

CURSOR=CCALCPESOMOVIM SELECT DECODE(UNIDADES,'UN',DECODE(:PESO,0,PESOUNI,:PESO*1000/:EMBCONT),
                                                  :UNIEMB) PESOMOVIM
                      FROM VDARTIC WHERE CODART = :CODART;
                                       
CURSOR=CSELCADUCI SELECT CADUCI FROM VDLOTES WHERE CODART = :CODART AND CODLOT = :CODLOT AND :CODLOT IS NOT NULL;

CURSOR=CSELGRAMOS SELECT :UNIDADES UNIDADES FROM DUAL WHERE :UNIDADES='GRAMOS';

CURSOR=CSELTODOS SELECT 1 DUMMY FROM DUAL WHERE :PESO IS NOT NULL AND :CODLOT IS NOT NULL;


CURSOR=CSELOPCIONCANT SELECT 1 DUMMY 
                        FROM DUAL 
                       WHERE :OPCIONCANT BETWEEN 1 AND 2;

CURSOR=CSELOPCION2 SELECT 1 DUMMY 
                        FROM DUAL 
                       WHERE :OPCIONCANT=2;

CURSOR=CSELDATOSSSCC SELECT CODART,LOTE_FABRICACION CODLOT,
                            TO_CHAR(TO_DATE(FECHA_CADUCIDAD,'DD-MON-YY'),'YYYYMMDD') CADUCI,
                            PESO_KG PESO
                       FROM VDENVIOSVIRTO, VDARTIC
                      WHERE COD_PALET=:SSCC AND N_TRASLADO=:CODALBPROVE AND
                            COD_MERCANCIA=CODARTDIV;
                    