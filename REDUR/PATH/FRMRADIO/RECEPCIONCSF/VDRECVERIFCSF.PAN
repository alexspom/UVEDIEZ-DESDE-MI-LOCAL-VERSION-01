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
 PALET : _18_______________
 __________________
 ART. : _20________________
 _30_______________________
 _30_______________________
_5___ _20_________________
U/E        EMB      
#L###.###  #### 
_12_________ ###
TOTAL: #L###.##  KG

(1) Entrada correcta
(2) Modificar datos
(3) Anular      OPCION:#
|

#                  "+CSELSTATUS2","",
PREQUERY=FEJECUTA("CLIMPIAR","",
                  "COCULTACAMPOS","",
                  "CCALTOTAL","\nERROR,\nCALCULANDO EL TOTAL",
                  FPOSICIONACAMPO(FSUCCESS,"OPCION"),"\nERROR,\nAL POSICIONARSE EN EL CAMPO")

#"CVERIFRECEP","\nLA RECEPCIÓN HA SIDO VALIDADA,\nANULE LA RECEPCION Y VUELVA\nA RECEPCIONAR EL PALET",

POSTQUERY=FEJECUTA("CSELNOTNULL","SELECCIONE UNA OPCION\nENTRE 1 Y 3",
                   FSWITCHCADENA(":OPCION",
                                 "1", FEJECUTA("CVALLOTE", "\nERROR,AL VALIDAR SI ES NECESARIO\nCREAR EL LOTE",
                                               "CVERERROR", "\nERROR,\n:MSGERROR",
                                               "COBTBLOQUEOS", "\nERROR,\n:BLOQUEOS",
                                               "COBTLINREC","\nERROR,\nAL BUSCAR LA LINEA DE LA\nRECEPCION PARA LA RECEPCION\n :CODRECEP",
                                               "CVERERROR", "\nERROR,\n:MSGERROR",
                                               "INSCONTE","\nERROR,\nINSERTANDO CONTENEDOR\n:CODMAT",
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
                                                                          ),FSUCCESS),"",
                                               FCOMMIT,"",   
#                                               FIMPRIME("INFORME","VDETIQRECEP.rpt","CODMAT=:CODMAT;PESO=:PESO",""),"ERROR IMPRIMIENDO ETIQUETA RECEPCION :V10ERROR",
#                                               FCOMMIT,"",
                                               FSWITCHCADENA(":MULTIARTICULO",
                                                             "S",FEJECUTA(FPOSICIONABLOQUE("VDRECARTICULOCSF.PAN"),"\nNO SE PUEDE POSICIONAR\nEN LA PANTALLA VDRECARTICULO.PAN"),
                                                             "N",FEJECUTA(FIF("CCONTRZ", FEJECUTA(FPOSICIONABLOQUE("VDRECCANTIDADCSF.PAN"),"\nNO SE PUEDE POSICIONAR\nEN LA PANTALLA VDRECCANTIDAD.PAN"),
                                                                                         FEJECUTA(FPOSICIONABLOQUE("VDRECPULMONCSF.PAN"),"\nNO SE PUEDE POSICIONAR\nEN LA PANTALLA VDRECMATRICULA.PAN")),"")),""),
                                 "2", FEJECUTA(FPOSICIONABLOQUE("VDRECCANTIDADCSF.PAN"),"\nNO SE PUEDE POSICIONAR\nEN EL ANTERIOR BLOQUE\n(VDRECCANTIDAD.PAN)"),
                                 "3", FEJECUTA(FPOSICIONABLOQUE("VDRECPULMONCSF.PAN"),"\nNO SE PUEDE POSICIONAR\nEN EL BLOQUE\n(VDRECORDEN.PAN)")), "")   
#                                 "4", FEJECUTA("CVERIFRECEP","\n\nLA RECEPCIÓN HA SIDO VALIDADA,\nANULE LA RECEPCION Y VUELVA\nA RECEPCIONAR EL PALET",
#                                               "CVALLOTE", "\nERROR,AL VALIDAR SI ES NECESARIO\nCREAR EL LOTE",
#                                               "CVERERROR", "\nERROR,\n:MSGERROR",
#                                               "COBTBLOQUEOS", "\nERROR,\n:BLOQUEOS",
#                                               "COBTLINREC","\nERROR,\nAL BUSCAR LA LINEA DE LA\nRECEPCION PARA LA RECEPCION\n :CODRECEP",
#                                               "CVERERROR", "\nERROR,\n:MSGERROR",
#                                               "+INSCONTE","\nERROR,\nINSERTANDO CONTENEDOR\n:CODMAT",
#                                               "CCONCEPTO", "\nERROR,\nERROR SELECCIONANDO EL CONCEPTO",
#                                               "CCODMATORI", "\nERROR,\nERROR SELECCIONANDO CODMATORI",
#                                               "CCREAMOV", "\nERROR,\n:V10ERROR",
#                                               "CVERERROR2", ":V10ERROR",
#                                               FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOV",":CODRECURSO"),"ERROR EJECUTANDO MOVIMIENTO :CODMOV",
#                                               FIF("CEXMUESTRA", FEJECUTA("CBLOQUEOSM","\nERROR,\nSELECCIONANDO LOS BLOQUEOS DE LA MUESTRA",
#                                                                          "COBTLINRECM","\nERROR,\nAL BUSCAR LA LINEA DE LA\nRECEPCION PARA LA RECEPCION\n :CODRECEP",
#                                                                          "CVERERROR", "\nERROR,\n:MSGERROR",
#                                                                          "CUBIDESTM", "\nERROR,\nARTÍCULO SIN UBICACIÓN DE MUESTREOTECA",
#                                                                          "CCREAMUESTRAS","\nERROR,\n:V10ERROR",
#                                                                          "CVERERROR2", ":V10ERROR",                                              
#                                                                          FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOV",":CODRECURSO"),"ERROR EJECUTANDO MOVIMIENTO :NCODMOV",
#                                                                          FIF("CSELMUESTREADOLOTE","CUPDMUESTREADOLOTE",FSUCCESS),"",
#                                                                          FIF("CSELMUESTREADORECEP","CUPDMUESTREADORECEP",FSUCCESS),""
#                                                                         )),"", 
#                                               FCOMMIT,"",
#                                               FPOSICIONABLOQUE("VDUBICAENTRADASDESDERECEP.PAN"),"\nNO SE PUEDE POSICIONAR\nEN EL BLOQUE")), "")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODRECEP,NOENTER,VIRTUAL
CAMPO=CODMAT,NOENTER,VIRTUAL
CAMPO=SSCC,VIRTUAL,NOENTER
CAMPO=CODART,NOENTER,VIRTUAL
CAMPO=DESART1,NOENTER,VIRTUAL
CAMPO=DESART2,NOENTER,VIRTUAL
CAMPO=NCODLOT,NOENTER
CAMPO=CODLOT,VIRTUAL,NOENTER
CAMPO=UNIEMB,VIRTUAL,NOENTER
CAMPO=EMBCONT,VIRTUAL,NOENTER
CAMPO=PICO,VIRTUAL,OCULTO
CAMPO=NNMUESTRAS,VIRTUAL,NOENTER
CAMPO=NUMMUESTRAS,VIRTUAL,NOENTER
CAMPO=TOTAL,OCULTO,"#L###.###"
CAMPO=PESO,VIRTUAL
CAMPO=PESOMOVIM,VIRTUAL,OCULTO
CAMPO=UNIDADESHOST,VIRTUAL,OCULTO
#CAMPO=STATUSREC2,NOENTER
CAMPO=OPCION
CAMPO=BULTO,VIRTUAL,OCULTO
CAMPO=TIPOEMBA,OCULTO,VIRTUAL
#CAMPO=EMBCONT,VIRTUAL,OCULTO
CAMPO=MULTIARTICULO,VIRTUAL,OCULTO
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
CAMPO=BLOQUEOS,OCULTO,"_50____________"
CAMPO=BLOQUEOSM,OCULTO,"_10____________"
CAMPO=MSGERROR, OCULTO,"_100______"
CAMPO=PANTANTERIOR,OCULTO,VIRTUAL
CAMPO=CODMOV,OCULTO,"#########"
CAMPO=DUMMY,OCULTO,"#"
CAMPO=MUESTREADO,OCULTO,"_"

CURSOR=CSELMUESTREADOLOTE SELECT :MUESTREADO FROM VDLOTES WHERE CODART=:CODART AND CODLOT=:CODLOT AND MUESTREADO='N' AND :MUESTREAR= 'L';
CURSOR=CUPDMUESTREADOLOTE UPDATE VDLOTES SET MUESTREADO='S' WHERE CODART=:CODART AND CODLOT=:CODLOT; 
CURSOR=CSELMUESTREADORECEP SELECT :MUESTREADO FROM VDRECEPLIN WHERE CODART=:CODART AND CODLOT=:CODLOT AND CODRECEP=:CODRECEP AND MUESTREADO='N' AND :MUESTREAR= 'R';
CURSOR=CUPDMUESTREADORECEP UPDATE VDRECEPLIN SET MUESTREADO='S' WHERE CODART=:CODART AND CODLOT=:CODLOT AND CODRECEP=:CODRECEP AND MUESTREADO='N'; 


CURSOR=CLIMPIAR SELECT 1 OPCION, 'VDRECVERIF.PAN' PANTANTERIOR, 
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
                            'LOTE:' NCODLOT, 'Nº MUESTRAS:' NNMUESTRAS
                       FROM DUAL;

CURSOR=CSELNOTNULL SELECT 1 DUMMY 
                     FROM DUAL 
                    WHERE :OPCION BETWEEN 1 AND 3;

CURSOR=CCALTOTAL SELECT (:UNIEMB*:EMBCONT) + :PICO + :NUMMUESTRAS TOTAL
                   FROM DUAL;

#Puede ocurrir que mientras se está recepcionando alguien valide la recepción, se comprueba que no sea así.
CURSOR= CVERIFRECEP SELECT 1 DUMMY
                      FROM VDRECEPCAB
                     WHERE STATUS=#STRCCACTIVA 
                       AND CODRECEP = :CODRECEP;

#Devuelve el lote, y si es necesario lo crea.
CURSOR=CVALLOTE BEGIN VDRECEP.VALIDALOTE (:CODART, :CODLOT, :CADUCI, :TIPORDREC, 'S', :CODRECEP, :MSGERROR);
                END;@

#Devuelve los bloqueos o el mensaje de error en el campo Bloqueos.
CURSOR=COBTBLOQUEOS SELECT VDRECEP.OBTBLOQUEOS(:ESTADOS_STOCK, :CODART, :CODLOT, :PRECIOUNI) BLOQUEOS
                      FROM DUAL;

CURSOR=COBTLINREC BEGIN
                    :DUMMY:= VDRECEP.OBTLINREC (:CODORDREC, :CODRECEP, :CODART, :CODDIV, :CODLOT, :BLOQUEOS,:CADUCI, (:TOTAL*1000-:NUMMUESTRAS));
                    IF :DUMMY != 0 THEN
                       :MSGERROR := '\nERROR2,\nAL BUSCAR LA LINEA DE LA\nRECEPCION PARA LA RECEPCION\n'|| :CODRECEP;
                    END IF;
                  END;@

CURSOR=INSCONTE INSERT INTO VDCONTE
                           (CODMAT     , TIPOCONTE  , CNTSSCC    , CODUBI     , POSCONTE   , ALTURACONTE, 
                            STATUS     , FECENTRADA , HORAENTRADA, VDEXTRA    , CODCOMEN   , CODOPEMODIF, 
                            FECMODIF   , HORAMODIF  )
                           (SELECT :CODMAT , :TIPOCONTE  , :SSCC  , :PULMON , COUNT(*)+1, :ALTPALET, 0, VD.FECHASYS, VD.HORASYS, 
                                   NULL, 0,  VDUSER.GETUSER,  VD.FECHASYS, VD.HORASYS
                              FROM VDCONTE
                             WHERE CODUBI = :PULMON);

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
                                :UNIEMB*1000, '',((:TOTAL*1000)-:NUMMUESTRAS),0,0, :CODRECURSO);
                 IF :CODMOV != 0 THEN
                    VDMOV.VDACTMOVIM (:CODMOV, :PRECIOUNI, :BLOQUEOS, :BLOQUEOS, :EMBCONT, :TIPOEMBA, :BULTO, :CODRECEP);
                    UPDATE VDMOVIM SET PESOUNI = :PESOMOVIM WHERE CODMOV = :CODMOV;
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
                                      :CODART, :CODLOT, :UNIEMB*1000,'', :NUMMUESTRAS, 0,0, :CODRECURSO);
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

#CURSOR=CSELSTATUS2 SELECT STATUS STATUSREC2 FROM VDRECEPCAB WHERE CODRECEP = :CODRECEP;