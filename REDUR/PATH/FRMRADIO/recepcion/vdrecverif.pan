# Módulo   : VDRECVERIF.PAN
# Función  : RECEPCIÓN DE MERCANCÍA:Validación de que los datos introducidos son correctos.
#            Validaciones:
#              Opciones:
#              - 1, confirmar que la entrada ha sido correcta. Dependiendo del valor de
#                   multiartículo:
#                 	- S: volverá a la pantalla nº 4
#                 	- N: volverá a la pantalla nº 3
#                  Si trazabilidad de bulto y x < n, volverá a la pantalla nº 5.
#               - 2, queremos modificar los datos, con lo que iremos a la pantalla nº 5,
#                    donde se nos mostrarán todos los datos introducidos.
#               - 3, se anulará la entrada, es decir, no se hará nada, y volverá a la pantalla nº 2. 
#               - 4, se ubicará el palet e irá a la pantalla de ubicación.
#              
#              Si la entrada ha sido correcta:
#               - Si no existe una línea de recepción para ese artículo se dará de alta.
#               - Se creará un movimiento con el stock pendiente de validar (Pos. 5).
#               - Si hay muestras, se creará un movimiento de entrada a la ubicación definida por
#                 el campo VDARTIC.MUESTROTECA. Se creará con el bloqueo de muestras.
#               - Si no existe el lote y el tipo de orden y se indica darlo de alta, se dará de alta.
#              
#            
# Creación : 07-02-2008
# Autor    : ICC
###########################################
# Histórico de cambios:
# 
VERFICACION DE DATOS
 _10_______ _10_______
 REC. : _20________________
 MAT. : _18_______________
 ART. : _40________________
 _30_______________________
 _30_______________________
_5___ _20_________________
U/E        EMB  PICO     
#L15###### #### ##########
_12_________ @@@
TOTAL: #L############ _10__
(1) Entrada correcta
(2) Modificar datos
(3) Anular
(4) Ubicar
(5) Ubicar con carro
OPCION:#
|

PREQUERY=FEJECUTA("CLIMPIAR","",
                  "COCULTACAMPOS","",
                  "CCALTOTAL","\nERROR,\nCALCULANDO EL TOTAL",
				  "CVERIFRECEP","\nLA RECEPCIÓN HA SIDO VALIDADA,\nANULE LA RECEPCION Y VUELVA\nA RECEPCIONAR EL PALET",
				  "CVALLOTE", "\nERROR,AL VALIDAR SI ES NECESARIO\nCREAR EL LOTE",
				  "CVERERROR", "\nERROR,\n:MSGERROR",
#SE OBTIENEN LOS BLOQUEOS SOLO LA PRIMERA VEZ QUE SE ENTRA
				  FIF("CBLOQEOSNULO",FEJECUTA("COBTBLOQUEOS","",
                                              FIF("DIVESPALEX", "COBTBLOQUEOSPALEX"), ""),FSUCCESS), "\nERROR,\n:BLOQUEOS",
                  FPOSICIONACAMPO(FSUCCESS,"OPCION"),"\nERROR,\nAL POSICIONARSE EN EL CAMPO")

POSTQUERY=FEJECUTA("CSELNOTNULL","\nSELECCIONE UNA OPCION \nENTRE 1 Y 5",
				   FSWITCHCADENA(":OPCION",
                                 "1", FEJECUTA("COBTLINREC","\nERROR,\nAL BUSCAR LA LINEA DE LA\nRECEPCION PARA LA RECEPCION\n :CODRECEP",
                                               "CVERERROR", "\nERROR,\n:MSGERROR",
                                               "INSCONTE","\nERROR,\nINSERTANDO CONTENEDOR\n:CODMAT",
#                                               FUSACONTE(":CODMAT",":PULMON",":TIPOCONTE"),":V10ERROR",
                                               "CCONCEPTO", "\nERROR,\nERROR SELECCIONANDO EL CONCEPTO",
                                               "CCODMATORI", "\nERROR,\nERROR SELECCIONANDO CODMATORI",
                                               "CCREAMOV", "\nERROR,\n:V10ERROR",
                                               "CVERERROR2", ":V10ERROR",
                                               FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOV",":CODRECURSO"),"ERROR EJECUTANDO MOVIMIENTO :CODMOV",
                                               FIF("CEXMUESTRA", FEJECUTA("CBLOQUEOSM","\nERROR,\nSELECCIONANDO LOS BLOQUEOS DE LA MUESTRA",
                                                                          "COBTLINRECM","\nERROR,\nAL BUSCAR LA LINEA DE LA\nRECEPCION PARA LA RECEPCION\n :CODRECEP",
                                                                          "CVERERROR", "\nERROR,\n:MSGERROR",
                                                                          "CUBIDESTM", "\nERROR,\nARTICULO SIN UBICACION\nDE MUESTREOTECA",
                                                                          "CCREAMUESTRAS","\nERROR,\n:V10ERROR",
                                                                          "CVERERROR2", ":V10ERROR",
                                                                          FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOV",":CODRECURSO"),"ERROR EJECUTANDO MOVIMIENTO :CODMOV",
                                                                          FIF("CSELMUESTREADOLOTE","CUPDMUESTREADOLOTE",FSUCCESS),"",
                                                                          FIF("CSELMUESTREADORECEP","CUPDMUESTREADORECEP",FSUCCESS),""
                                                                          )),"",
                                               FCOMMIT,"",
                                               "CASIGBLOQEOSNULO","",
                                               FSWITCHCADENA(":MULTIARTICULO",
                                                             "S",FEJECUTA(FPOSICIONABLOQUE("VDRECARTICULO.PAN"),"\nNO SE PUEDE POSICIONAR\nEN LA PANTALLA VDRECARTICULO.PAN"),
                                                             "N",FEJECUTA(FIF("CCONTRZ", FEJECUTA(FPOSICIONABLOQUE("VDRECCANTIDAD.PAN"),"\nNO SE PUEDE POSICIONAR\nEN LA PANTALLA VDRECCANTIDAD.PAN"),
                                                                                         FEJECUTA(FPOSICIONABLOQUE("VDRECMATRICULA.PAN"),"\nNO SE PUEDE POSICIONAR\nEN LA PANTALLA VDRECMATRICULA.PAN")),"")),""),
#SE HACE ROLLBACK POR SI SE HA CREADO UN LOTE
                                 "2", FEJECUTA(FROLLBACK,"",
                                               "CASIGBLOQEOSNULO","",
								               FPOSICIONABLOQUE("VDRECCANTIDAD.PAN"),"\nNO SE PUEDE POSICIONAR\nEN EL ANTERIOR BLOQUE\n(VDRECCANTIDAD.PAN)"),
#SE HACE ROLLBACK POR SI SE HA CREADO UN LOTE
                                 "3", FEJECUTA(FROLLBACK,"",
                                               "CASIGBLOQEOSNULO","",
								               FPOSICIONABLOQUE("VDRECORDEN.PAN"),"\nNO SE PUEDE POSICIONAR\nEN EL BLOQUE\n(VDRECORDEN.PAN)"),
                                 "4", FEJECUTA("COBTLINREC","\nERROR,\nAL BUSCAR LA LINEA DE LA\nRECEPCION PARA LA RECEPCION\n :CODRECEP",
                                               "CVERERROR", "\nERROR,\n:MSGERROR",
                                               "+INSCONTE","\nERROR,\nINSERTANDO CONTENEDOR\n:CODMAT",
#                                               FUSACONTE(":CODMAT",":PULMON",":TIPOCONTE"),":V10ERROR",
                                               "CCONCEPTO", "\nERROR,\nERROR SELECCIONANDO EL CONCEPTO",
                                               "CCODMATORI", "\nERROR,\nERROR SELECCIONANDO CODMATORI",
                                               "CCREAMOV", "\nERROR,\n:V10ERROR",
                                               "CVERERROR2", ":V10ERROR",
                                               FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOV",":CODRECURSO"),"ERROR EJECUTANDO MOVIMIENTO :CODMOV",
                                               FIF("CEXMUESTRA", FEJECUTA("CBLOQUEOSM","\nERROR,\nSELECCIONANDO LOS BLOQUEOS DE LA MUESTRA",
                                                                          "COBTLINRECM","\nERROR,\nAL BUSCAR LA LINEA DE LA\nRECEPCION PARA LA RECEPCION\n :CODRECEP",
                                                                          "CVERERROR", "\nERROR,\n:MSGERROR",
                                                                          "CUBIDESTM", "\nERROR,\nARTÍCULO SIN UBICACIÓN DE MUESTREOTECA",
                                                                          "CCREAMUESTRAS","\nERROR,\n:V10ERROR",
                                                                          "CVERERROR2", ":V10ERROR",                                              
                                                                          FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOV",":CODRECURSO"),"ERROR EJECUTANDO MOVIMIENTO :NCODMOV",
                                                                          FIF("CSELMUESTREADOLOTE","CUPDMUESTREADOLOTE",FSUCCESS),"",
                                                                          FIF("CSELMUESTREADORECEP","CUPDMUESTREADORECEP",FSUCCESS),""
                                                                         )),"", 
                                               FCOMMIT,"",
                                               "CASIGBLOQEOSNULO","",
                                               FPOSICIONABLOQUE("VDUBICAENTRADASDESDERECEP.PAN"),"\nNO SE PUEDE POSICIONAR\nEN EL BLOQUE"),
								"5", FEJECUTA(
#								"COBTLINREC","\nERROR,\nAL BUSCAR LA LINEA DE LA\nRECEPCION PARA LA RECEPCION\n :CODRECEP",
#                                               "CVERERROR", "\nERROR,\n:MSGERROR",
                                               "+INSCONTE","\nERROR,\nINSERTANDO CONTENEDOR\n:CODMAT",
                                               "CCONCEPTO", "\nERROR,\nERROR SELECCIONANDO EL CONCEPTO",
                                               "CCODMATORI", "\nERROR,\nERROR SELECCIONANDO CODMATORI",
                                               "CCREAMOV", "\nERROR,\n:V10ERROR",
                                               "CVERERROR2", ":V10ERROR",
                                               FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOV",":CODRECURSO"),"ERROR EJECUTANDO MOVIMIENTO :CODMOV",
											   FIF("-CSELMOVFIN",FEJECUTA("CCREAMOVIM","ERROR CREANDO MOVIMIENTOS",
																		  FCOMMIT,"",
																		  FIF("CCOMPRUEBAMOV",FFAILURE),"ERROR COMPROBANDO MOVIMIENTOS\n:MENSAJE",
																		  "CACTUALIZACONTE","ERROR ACTUALIZANDO CONTENEDOR",
																		  FCOMMIT,"",
																		  "CCOMPRUEBAMOV2","ERROR COMPROBANDO\nCREACION DE MOVIMIENTOS",
																		  FIF("CCOMPRUEBAMOV",FFAILURE),"TIMEOUT\nCOMPROBANDO MOVIMIENTOS")),"",
#											   FIF("CSELMOVFIN",FSUCCESS,FIF("CSELMOVPROC",FEJECUTA(FFAILURE,"MOVIMIENTOS\nEN TRAMITACIÓN\nINTÉNTELO MÁS TARDE"),
#																						   FEJECUTA(FFAILURE,"NO SE ENCUENTRAN\nMOVIMIENTOS QUE UBICAR"))),"",
                                               FIF("CEXMUESTRA", FEJECUTA("CBLOQUEOSM","\nERROR,\nSELECCIONANDO LOS BLOQUEOS DE LA MUESTRA",
                                                                          "COBTLINRECM","\nERROR,\nAL BUSCAR LA LINEA DE LA\nRECEPCION PARA LA RECEPCION\n :CODRECEP",
                                                                          "CVERERROR", "\nERROR,\n:MSGERROR",
                                                                          "CUBIDESTM", "\nERROR,\nARTÍCULO SIN UBICACIÓN DE MUESTREOTECA",
                                                                          "CCREAMUESTRAS","\nERROR,\n:V10ERROR",
                                                                          "CVERERROR2", ":V10ERROR",                                              
                                                                          FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOV",":CODRECURSO"),"ERROR EJECUTANDO MOVIMIENTO :NCODMOV",
                                                                          FIF("CSELMUESTREADOLOTE","CUPDMUESTREADOLOTE",FSUCCESS),"",
                                                                          FIF("CSELMUESTREADORECEP","CUPDMUESTREADORECEP",FSUCCESS),""
                                                                         )),"", 
                                               FCOMMIT,"",
                                               "CASIGBLOQEOSNULO","",
##											   FIF("CSELNOTNULL",FCARGAFORM("")),"ERROR COMPROBANDO VALORES NULOS",
                                               FPOSICIONABLOQUE("VDUBICAENTRADASCARRO2.PAN"),"\nNO SE PUEDE POSICIONAR\nEN EL BLOQUE")),"")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODRECEP,NOENTER,VIRTUAL
CAMPO=CODMAT,NOENTER,VIRTUAL
CAMPO=CODART,NOENTER,VIRTUAL
CAMPO=DESART1,NOENTER,VIRTUAL
CAMPO=DESART2,NOENTER,VIRTUAL
CAMPO=NCODLOT,NOENTER
CAMPO=CODLOT,VIRTUAL,NOENTER
CAMPO=UNIEMB,VIRTUAL,NOENTER
CAMPO=EMBCONTREC,VIRTUAL,NOENTER
CAMPO=PICO,VIRTUAL,NOENTER
CAMPO=NNMUESTRAS,VIRTUAL,NOENTER
CAMPO=NUMMUESTRAS,VIRTUAL,NOENTER
CAMPO=TOTAL,NOENTER
CAMPO=UNIDADESHOST,VIRTUAL,NOENTER
CAMPO=OPCION
CAMPO=BULTO,VIRTUAL,OCULTO
CAMPO=TIPOEMBA,OCULTO,VIRTUAL
CAMPO=EMBCONT,VIRTUAL,OCULTO
CAMPO=MULTIARTICULO,OCULTO,VIRTUAL
CAMPO=PULMON,OCULTO,VIRTUAL
CAMPO=INDLOTE,OCULTO,VIRTUAL
CAMPO=MUESTREAR,OCULTO,VIRTUAL
CAMPO=CADUCI,OCULTO,VIRTUAL
CAMPO=TIPORDREC,OCULTO,VIRTUAL
CAMPO=ESTADOS_STOCK,OCULTO,VIRTUAL
CAMPO=PRECIOUNI,OCULTO,VIRTUAL
CAMPO=CODDIV,OCULTO,VIRTUAL
CAMPO=CODORDREC,OCULTO,VIRTUAL
CAMPO=ALTPALET,OCULTO,VIRTUAL
CAMPO=TIPOCONTE,OCULTO,VIRTUAL
CAMPO=MUESTROTECA,OCULTO,"_12_________"
CAMPO=CODMATDEST,OCULTO,"_18_______________"
CAMPO=CODCONCE,OCULTO,"_10_______"
CAMPO=CODMATORI,OCULTO,"_18_______________"
CAMPO=BLOQUEOS,OCULTO,VIRTUAL
CAMPO=BLOQUEOSORIG,OCULTO,VIRTUAL
CAMPO=BLOQUEOSM,OCULTO,"_10____________"
CAMPO=MSGERROR, OCULTO,"_100______"
CAMPO=PANTANTERIOR,OCULTO,VIRTUAL
CAMPO=CODMOV,OCULTO,"#########"
CAMPO=DUMMY,OCULTO,"#"
CAMPO=SALIDA,OCULTO,"@"
CAMPO=MUESTREADO,OCULTO,"_"
CAMPO=MENSAJE,OCULTO,"_256_"

CURSOR=CBLOQEOSNULO SELECT 1 DUMMY FROM DUAL WHERE :BLOQUEOS IS NULL;
CURSOR=CASIGBLOQEOSNULO SELECT NULL BLOQUEOS FROM DUAL;

CURSOR=CSELMUESTREADOLOTE SELECT :MUESTREADO FROM VDLOTES WHERE CODART=:CODART AND CODLOT=:CODLOT AND MUESTREADO='N' AND :MUESTREAR= 'L';
CURSOR=CUPDMUESTREADOLOTE UPDATE VDLOTES SET MUESTREADO='S' WHERE CODART=:CODART AND CODLOT=:CODLOT; 
CURSOR=CSELMUESTREADORECEP SELECT :MUESTREADO FROM VDRECEPLIN WHERE CODART=:CODART AND CODLOT=:CODLOT AND CODRECEP=:CODRECEP AND MUESTREADO='N' AND :MUESTREAR= 'R';
CURSOR=CUPDMUESTREADORECEP UPDATE VDRECEPLIN SET MUESTREADO='S' WHERE CODART=:CODART AND CODLOT=:CODLOT AND CODRECEP=:CODRECEP AND MUESTREADO='N'; 

CURSOR=DIVESPALEX SELECT 1 DUMMY FROM DUAL WHERE :CODDIV IN ('PA', 'LP');


CURSOR=CLIMPIAR SELECT 0 OPCION, 'VDRECVERIF.PAN' PANTANTERIOR, 
                          DECODE(:MUESTREAR, 'L',(SELECT DECODE(MUESTREADO,'S',0,:NUMMUESTRAS)
                                                  FROM VDLOTES WHERE CODART=:CODART
                                                   AND CODLOT=:CODLOT ),
                                             'R',(SELECT DISTINCT DECODE(MUESTREADO,'S',0,:NUMMUESTRAS)
                                                  FROM VDRECEPLIN WHERE CODRECEP=:CODRECEP
                                                     AND CODART=:CODART
                                                     AND CODLOT=:CODLOT),
                                             'P',:NUMMUESTRAS,0) NUMMUESTRAS
                  FROM DUAL;

CURSOR=COCULTACAMPOS SELECT DECODE(:INDLOTE, 'S', 0, 1) NCODLOT__INVISIBLE,
                            DECODE(:INDLOTE, 'S', 0, 1) CODLOT__INVISIBLE,
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
                                                                      AND CODLOT=:CODLOT),
                                              'R',(SELECT DISTINCT DECODE(MUESTREADO,'N',0,1)
                                                       FROM VDRECEPLIN WHERE CODRECEP=:CODRECEP
                                                                         AND CODART=:CODART
                                                                         AND CODLOT=:CODLOT),
                                               1) NUMMUESTRAS__INVISIBLE,
                            'LOTE:' NCODLOT, 'N. MUESTRAS:' NNMUESTRAS
                       FROM DUAL;

CURSOR=CSELNOTNULL SELECT 1 DUMMY 
                     FROM DUAL 
                    WHERE :OPCION BETWEEN 1 AND 5;

#CURSOR=CCALTOTAL SELECT (:UNIEMB*:EMBCONTREC) + :PICO + :NUMMUESTRAS TOTAL
#                   FROM DUAL;
CURSOR=CCALTOTAL SELECT (:UNIEMB*:EMBCONTREC) + :PICO  TOTAL
                   FROM DUAL;

#Puede ocurrir que mientras se está recepcionando alguien valide la recepción, se comprueba que no sea así.
CURSOR= CVERIFRECEP SELECT 1 DUMMY
                      FROM VDRECEPCAB
                     WHERE STATUS=VDST.FRCCACTIVA 
                       AND CODRECEP = :CODRECEP;

#Devuelve el lote, y si es necesario lo crea.
CURSOR=CVALLOTE BEGIN VDRECEP.VALIDALOTE (:CODART, :CODLOT, :CADUCI, :TIPORDREC, 'S', :CODRECEP, :MSGERROR);
                END;@

#Devuelve los bloqueos o el mensaje de error en el campo Bloqueos.
CURSOR=COBTBLOQUEOS SELECT VDRECEP.OBTBLOQUEOS(:ESTADOS_STOCK, :CODART, :CODLOT, :PRECIOUNI) BLOQUEOS, VDRECEP.OBTBLOQUEOS(:ESTADOS_STOCK, :CODART, :CODLOT, :PRECIOUNI) BLOQUEOSORIG
                      FROM DUAL;
                      
CURSOR=COBTBLOQUEOSPALEX DECLARE
                           ALM VARCHAR2(1);
                           VALORES VARCHAR2(10);
                           RET VARCHAR2(10);
                         BEGIN
                          
                            SELECT DPPKG.DAMEALMACENPALEXDP(VDCOM.DAMECOMEN (ORL.CODCOMEN, 'CODALM', 1))
                            INTO ALM
                            FROM VDORDRECLIN ORL, VDRECEPCAB RCA 
                            WHERE RCA.CODORDREC = ORL.CODORDREC
                            AND RCA.CODRECEP = :CODRECEP
                            AND ORL.CODART = :CODART
                            AND NVL(ORL.CODLOT, NVL(:CODLOT, 'X')) = NVL(:CODLOT, 'X')
                            AND ROWNUM = 1;
                            
                            IF ALM <> 'V' THEN
                            
                                SELECT VALORES
                                INTO VALORES
                                FROM XVDALMACENES
                                WHERE CODDIV = :CODDIV
                                AND CODALM = ALM;
                                    
                                FOR I IN 1..10 LOOP
                                    IF SUBSTR(VALORES, I, 1) <> '_' THEN
                                        RET := RET || SUBSTR(VALORES, I, 1);
                                    ELSE
                                        RET := RET || SUBSTR(:BLOQUEOS, I, 1);
                                    END IF;
                                END LOOP;
                                
                                :BLOQUEOS := RET;
                                :BLOQUEOSORIG := RET;
                            
                            END IF;

                        END;@

CURSOR=COBTLINREC BEGIN
                    :DUMMY:= VDRECEP.OBTLINREC (:CODORDREC, :CODRECEP, :CODART, :CODDIV, :CODLOT, :BLOQUEOS,:CADUCI, (:TOTAL-:NUMMUESTRAS));
                    IF :DUMMY != 0 THEN
                       :MSGERROR := '\nERROR2,\nAL BUSCAR LA LINEA DE LA\nRECEPCION PARA LA RECEPCION\n'|| :CODRECEP;
                    END IF;
                  END;@

#DFL 05/07/2019 - AL INSERTAR O ACTUALIZAR EL CONTENEDOR, HACER UN MAX(POSCONTE) PORQUE EL COUNT PUEDE COINCIDIR CON UN POSCONTE EXISTENTE
#CURSOR=INSCONTE BEGIN
#                   INSERT INTO VDCONTE
#                           (CODMAT     , TIPOCONTE  , CNTSSCC    , CODUBI     , POSCONTE   , ALTURACONTE, 
#                            STATUS     , FECENTRADA , HORAENTRADA, VDEXTRA    , CODCOMEN   , CODOPEMODIF, 
#                            FECMODIF   , HORAMODIF  )
#                           (SELECT :CODMAT , :TIPOCONTE  , NULL  , :PULMON , COUNT(*)+1, :ALTPALET, 0, VD.FECHASYS, VD.HORASYS, 
#                                   NULL, 0,  VDUSER.GETUSER,  VD.FECHASYS, VD.HORASYS
#                              FROM VDCONTE
#                             WHERE CODUBI = :PULMON);
#                   EXCEPTION  WHEN OTHERS THEN
#                      UPDATE VDCONTE SET CODUBI=:PULMON,POSCONTE=(SELECT NVL(COUNT(*),0)+1 FROM VDCONTE WHERE CODUBI=:PULMON)
#                         WHERE CODMAT=:CODMAT;
#                 END;@

CURSOR=INSCONTE BEGIN
                   INSERT INTO VDCONTE
                           (CODMAT     , TIPOCONTE  , CNTSSCC    , CODUBI     , POSCONTE   , ALTURACONTE, 
                            STATUS     , FECENTRADA , HORAENTRADA, VDEXTRA    , CODCOMEN   , CODOPEMODIF, 
                            FECMODIF   , HORAMODIF  )
                           (SELECT :CODMAT , :TIPOCONTE  , NULL  , :PULMON , NVL(MAX(POSCONTE),0)+1, :ALTPALET, 0, VD.FECHASYS, VD.HORASYS, 
                                   NULL, 0,  VDUSER.GETUSER,  VD.FECHASYS, VD.HORASYS
                              FROM VDCONTE
                             WHERE CODUBI = :PULMON);
                   EXCEPTION 
                     WHEN DUP_VAL_ON_INDEX THEN                                          
                      UPDATE VDCONTE SET CODUBI=:PULMON,POSCONTE=(SELECT NVL(MAX(POSCONTE),0)+1 FROM VDCONTE WHERE CODUBI=:PULMON)
                         WHERE CODMAT=:CODMAT;
                     WHEN OTHERS THEN
                      RAISE NO_DATA_FOUND; 
                 END;@
				 
CURSOR=CCONCEPTO SELECT CODCONCE
                   FROM VDTIPORDRECCAB
                  WHERE TIPORDREC = :TIPORDREC;
                  
CURSOR=CCODMATORI SELECT CNT.CODMAT CODMATORI
                    FROM VDCONTE CNT, VDUBICA UBI,  VDUBICA UBI2
                    WHERE CNT.TIPOCONTE  = 'VIRTUAL'
                     AND CNT.CODUBI     = UBI2.CODUBI
                     AND UBI2.STOCK     = 'N'
                     AND UBI2.BLOQUEOSS = 'N'
                     AND UBI2.CODAREA    = UBI.CODAREA
                     AND UBI.CODUBI     = :PULMON;


#Tener en cuenta los decimales en el precio DECIMALES CANTIDAD__DECIMALES--> Sin acabar, pdte de Paco
CURSOR=CCREAMOV BEGIN
                 :CODMOV := 0;
                 VDMOV.CREAMOV (:CODMOV, VD.GETPROP('TAREARECEP'), :CODCONCE, VDST.FMOVRECOGIDO, :CODMATORI, :PULMON, :CODMAT, :CODART, :CODLOT,
                                :UNIEMB, '',(:TOTAL-:NUMMUESTRAS),0,0, :CODRECURSO);
                 IF :CODMOV != 0 THEN
                    VDMOV.VDACTMOVIM (:CODMOV, :PRECIOUNI, :BLOQUEOS, :BLOQUEOS, :EMBCONT, :TIPOEMBA, :BULTO, :CODRECEP);
                 END IF;
                END;@

CURSOR=CEXMUESTRA SELECT 1 DUMMY
                    FROM DUAL
                   WHERE :NUMMUESTRAS > 0;


CURSOR=COBTLINRECM BEGIN
                      :DUMMY:= VDRECEP.OBTLINREC (:CODORDREC, :CODRECEP, :CODART, :CODDIV, :CODLOT, :BLOQUEOSM,:CADUCI, :NUMMUESTRAS) ;
                      IF :DUMMY != 0 THEN
                         :MSGERROR := '\nERROR2,\nAL BUSCAR LA LINEA DE LA\nRECEPCION PARA LA RECEPCION\n'|| :CODRECEP;
                      END IF;
                   END;@

CURSOR=CBLOQUEOSM SELECT '1'||SUBSTR(:BLOQUEOS,2, 10) BLOQUEOSM
                    FROM DUAL;

CURSOR=CUBIDESTM SELECT CNT.CODUBI MUESTROTECA, CNT.CODMAT CODMATDEST
                   FROM VDARTIC ART, VDCONTE CNT, VDUBICA UBI
                  WHERE ART.CODART      = :CODART
                    AND ART.MUESTROTECA = UBI.CODAREA
                    AND UBI.STOCK       = 'S'
                    AND UBI.CODUBI      = CNT.CODUBI
                  ORDER BY 1;

#Igual pero con bloqueos de muestras
CURSOR=CCREAMUESTRAS  DECLARE
                       ERROR EXCEPTION;
                      BEGIN
                       :CODMOV := 0;
                       VDMOV.CREAMOV (:CODMOV, VD.GETPROP('TAREARECEP'), TRIM(:CODCONCE)||'M', VDST.FMOVRECOGIDO, :CODMATORI, :MUESTROTECA, :CODMATDEST, 
                                      :CODART, :CODLOT, :UNIEMB,'', :NUMMUESTRAS, 0,0, :CODRECURSO);
                       IF :CODMOV != 0 THEN
                          VDMOV.VDACTMOVIM (:CODMOV, :PRECIOUNI, :BLOQUEOSM, :BLOQUEOSM, :EMBCONT, :TIPOEMBA, :BULTO, :CODRECEP);
                       END IF;
                     END;@

CURSOR=CVERERROR SELECT 1 DUMMY FROM DUAL WHERE :MSGERROR IS NULL;

CURSOR=CVERERROR2 SELECT 1 DUMMY
                    FROM DUAL
                   WHERE :CODMOV != 0;

CURSOR=CCONTRZ SELECT 1 DUMMY FROM DUAL
                WHERE :BULTO IS NOT NULL;


CURSOR=CANULAMOVS UPDATE VDMOVIM
                  SET STATUS = 7000
				  WHERE CODMATORI = :CODMAT
			      AND STATUS = 2000
			      AND CODCONCE = 'RECEP'
			      AND CODRECURSO = :CODRECURSO;

CURSOR=CHAYMOVS SELECT CODRECURSO TERMINAL
                FROM VDMOVIM
                WHERE CODMATORI = :CODMAT
                AND STATUS = 2000
                AND CODCONCE = 'RECEP'
                AND ROWNUM = 1
				AND CODRECURSO <> :CODRECURSO;			

#CURSOR=CLIMPIAR SELECT '' CODMAT,'' MENSAJE FROM DUAL;

#CURSOR=CSELNOTNULL SELECT :CODMAT FROM DUAL WHERE :CODMAT IS NULL;

CURSOR=CSELCODMAT SELECT 'X' DUMMY
                  FROM VDTIPOCONTE TCO,VDUBICA UBI,VDCONTE CNT 
                  WHERE CNT.CODMAT=':CODMAT'
                  AND TCO.TIPOCONTE=CNT.TIPOCONTE 
                  AND MOVIBLE='S' 
                  AND CNT.CODUBI=UBI.CODUBI;

CURSOR=CSELCREAMOV SELECT 'X' DUMMY FROM VDCONTE WHERE CODMAT=:CODMAT AND NVL(STATUS,0) <> 0;

CURSOR=CCREAMOVIM BEGIN
                     :SALIDA := RDRUBICA.REUBICACONTE(:CODMAT,:CODRECURSO,:MENSAJE); 
                  END;@
                  
CURSOR=CCOMPRUEBAMOV SELECT 1 SALIDA FROM DUAL WHERE :SALIDA <> 0;

CURSOR=CACTUALIZACONTE UPDATE VDCONTE SET STATUS = 200 WHERE CODMAT=:CODMAT;

CURSOR=CSELMOVFIN SELECT 'X' DUMMY
                  FROM VDMOVIM
                  WHERE CODMATORI = :CODMAT
                  AND STATUS = 2000
                  AND CODCONCE = 'RECEP'
                  AND CODRECURSO = :CODRECURSO
                  AND ROWNUM = 1;
                  
CURSOR=CSELMOVPROC SELECT 'X' DUMMY
                   FROM VDMOVIM
                   WHERE CODMATORI = :CODMAT
                   AND STATUS >= 1100
                   AND STATUS < 2000
                   AND CODCONCE = 'RECEP'
                   AND CODRECURSO = :CODRECURSO
                   AND ROWNUM = 1;

#Se buscan los movimientos hasta que el enrutador los trate

CURSOR=CCOMPRUEBAMOV2 DECLARE
                          I NUMBER := 1;
                      BEGIN
                          :SALIDA := 1;
                          LOOP
                              DBMS_LOCK.SLEEP(1);
                              
                              BEGIN
                                  SELECT 1
                                  INTO :SALIDA
                                  FROM VDMOVIM
                                  WHERE CODMATORI = :CODMAT
                                  AND STATUS >= 1100
                                  AND STATUS < 2000
                                  AND CODCONCE = 'RECEP'
                                  AND CODRECURSO = :CODRECURSO
                                  AND ROWNUM = 1;
                              EXCEPTION
                                  WHEN NO_DATA_FOUND THEN
                                      :SALIDA := 0;
                              END;
                              
                              EXIT WHEN I = 10 OR :SALIDA = 0;
                              I := I + 1;
                          END LOOP;
                      END;@