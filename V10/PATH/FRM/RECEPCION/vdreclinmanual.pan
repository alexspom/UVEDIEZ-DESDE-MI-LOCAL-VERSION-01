#****************************************************************
#MСdulo: VDRECLINMANUAL.PAN
#Funcionalidad : 
#Autor: ICC      
#Fecha: 25-03-2008
#*****************************************************************
#* HistСrico de cambios
#* ====================
#
RECEPCION

 оддддддддддддддддддддддд DATOS ARTICULO дддддддддддддддддддддддддддддддддддддк
 Ё ArtМculo _40_________________ _100____________________________________     Ё
 Ё Lote _40_________________   Caducidad _8______                             Ё
 Ё Precio unidad  ############                                                Ё
 юдддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддды
 
 оддддддддддддддддддддддд  CANTIDAD  дддддддддддддддддддддддддддддддддддддддддк
 Ё Unidad/embalaje EMB     Pico         Unidad de medida                      Ё
 Ё ############### #### ############### _10_______                            Ё
 Ё N╨ Muestras ###                                                            Ё
 юдддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддды
 
 оддддддддддддддддддддддд DATOS BULTO  дддддддддддддддддддддддддддддддддддддддк
 Ё Bulto         _18_______________                                           Ё
 Ё Tipo Embalaje _10_______                                                   Ё
 юдддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддды
 
 оддддддддддддддддддддд DATOS CONTENEDOR дддддддддддддддддддддддддддддддддддддк
 Ё MatrМcula _18_______________                                               Ё
 Ё Tipo contenedor _10_______ _40_________________                            Ё
 Ё Capacidad  ##### (emb x cont)    Altura ### cm                             Ё
 юдддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддддды
|
    
TABLA=DUAL
NOQUERY
PROTECT("RECEPCIONES")

PREINSERT=FEJECUTA(!FFAILURE,"VA A RECEPCIONAR EL ARTICULO :CODART Y LOTE :CODLOT",
                   "CVALTIPO", "ERROR, ARTICULO NO PERMITIDO PARA RECEPCIONES MANUALES",
                   "-CVALDIASRECEP","\nERROR\n:MSGERROR",
                   "CVALLOTEORD","\nERROR,\nEN PL VDRECEP.VALLOTEORDEN",
                   "CVERERROR", "\nERROR,\n:MSGERROR",
                   "CVALLOTE", "\nERROR,AL VALIDAR EL LOTE",
                   "CVERERROR", "\nERROR,\n:MSGERROR",
                   "COBTBLOQUEOS", "\nERROR,\n:BLOQUEOS",
                   "CVERERROR", "\nERROR\n:MSGERROR",
                   FIF("CVALCODMAT",FEJECUTA("CVERSIERROR", "ERROR, MATRICULA EN USO",
                                             "CMULTIART", "ERROR, TIPO DE RECEPCION NO PERMITE RECEPCION MULTIARTICULO")),"",
                   "CVALEMBCONT","\nERROR,\nDEMASIADAS UNIDADES PARA\nEL CONTENEDOR\nMAXIMO :EMBCONT",
                   "CVALCANT", "\nERROR,\nSE SOBREPASA LA CANTIDAD\nA RECEPCIONAR EN LA ORDEN",
                   "+INSCONTE","",
                   "COBTLINREC","\nERROR,\nAL BUSCAR LA LINEA DE LA\nRECEPCION PARA LA RECEPCION\n :CODRECEP",
                   "CVERERROR", "\nERROR,\n:MSGERROR",
                   "CCONCEPTO", "\nERROR,\nERROR SELECCIONANDO EL CONCEPTO",
                   "CCODMATORI", "\nERROR,\nERROR SELECCIONANDO CODMATORI",
                   "CCREAMOV", ":V10ERROR",
                   "CVERERROR2", ":V10ERROR",
                   FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOV",""),"\n ERROR\n\n :V10ERROR\n EJECUTANDO MOVIMIENTO",
                   FIF("CEXMUESTRA", FEJECUTA("CBLOQUEOSM","\nERROR,\nSELECCIONANDO LOS BLOQUEOS DE LA MUESTRA",
                                              "COBTLINRECM","\nERROR,\nAL BUSCAR LA LINEA DE LA\nRECEPCION PARA LA RECEPCION\n :CODRECEP",
                                              "CVERERROR", "\nERROR,\n:MSGERROR",
                                              "CUBIDESTM", "\nERROR,\nARTICULO SIN UBICACION DE MUESTREOTECA",
                                              "CCREAMUESTRAS",":V10ERROR",
                                              "CVERERROR2", ":V10ERROR",
                                              FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOV",""),"\n ERROR\n\n :V10ERROR\n EJECUTANDO MOVIMIENTO"
                                              )),"",                                               
                   FCOMMIT,"",
                   FPLAYWAV("I:\V10\BIN\Blip.wav"),"",
                   %FFAILURE,"\n RECEPCIONADO  \n",
                   FPULSATECLAS("F3"),"")

CAMPO=CODDIV,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODRECEP,VIRTUAL,AUXILIAR,OCULTO,TOOLTIP("Movimiento por el que se hizo recepciСn del producto en el almacИn")
CAMPO=CODORDREC,VIRTUAL,AUXILIAR,OCULTO
CAMPO=TIPORDREC,VIRTUAL,AUXILIAR,OCULTO
CAMPO=PULMON,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODART,AUXILIAR,TOOLTIP("CСdigo del artМculo"), POSTCHANGE=FDESIGNACION("CSELDATOSART","ARTICULO :CODART NO EXISTE"),
             CONTEXTUAL=FDESIGNACION(FEJECUTAFORM("VDARTIC","N","CODART = :CODART OR CODART=NVL(:CODART, CODART)","","CODART=:CODART","","S"))   
CAMPO=DESART,AUXILIAR,NOENTER
CAMPO=CODLOT,AUXILIAR,TOOLTIP("Lote"), POSTCHANGE=FEJECUTA("+CCADUCI",""),
             CONTEXTUAL=FDESIGNACION(FEJECUTAFORM("VDLOTES","N","CODART=:CODART","","CODLOT=:CODLOT CADUCI=:CADUCI","","S"))   
CAMPO=CADUCI,AUXILIAR,TOOLTIP("Caducidad del Lote")
CAMPO=PRECIOUNI,AUXILIAR,TOOLTIP("Precio de cada unidad"),
                POSTCHANGE=FEJECUTA("-CPVPCERO","DEBE INFORMAR EL PRECIO, SE ENCUENTRA EN PERIODO DE REETIQUETAJE")
CAMPO=UNIEMB,AUXILIAR,TOOLTIP("Unidades por embalaje"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),
             POSTCHANGE=FVALNOCERO("Deben informarse las unidades por embalaje")
CAMPO=EMBCONTREC,AUXILIAR,TOOLTIP("NЗmero de embalajes que se estАn recepcionando en el palet")
CAMPO=PICO,AUXILIAR,TOOLTIP("Unidades que no completan una caja"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=UNIDADESHOST,NOENTER,AUXILIAR,TOOLTIP("Unidades en que se mide el artМculo"),
                   POSTCHANGE=FEJECUTA("CVALUNID","\nERROR,\nNO EXISTE LA UNIDAD :UNIDADESHOST")
CAMPO=NUMMUESTRAS,AUXILIAR,TOOLTIP("NЗmero de muestras a recepcionar en este palet"),
                CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=BULTO,NOENTER,AUXILIAR,TOOLTIP("Bulto a recepecionar, si hay trazabilidad de bulto"),
      POSTCHANGE=FEJECUTA("-CVALBULTO","\nERROR, BULTO YA EXISTE")
CAMPO=TIPOEMBA,AUXILIAR, TOOLTIP("Tipo de embalaje"),
               POSTCHANGE=FEJECUTA("CVALTIPOEMBA","ERROR, TIPO DE EMBALAJE :TIPOEMBA NO EXISTE")
CAMPO=CODMAT,AUXILIAR,TOOLTIP("MatrМcula del contenedor dСnde se va a recepcionar")
CAMPO=TIPOCONTE,AUXILIAR,TOOLTIP("Tipo del contenedor"),
                POSTCHANGE=FDESIGNACION("CSELDESTIPOCONTE","ERROR AL EJECUTAR CURSOR CSELVDTIPOCONTEDESTIPOCONTE",
                                        "CCALALTPALET","\nERROR,\nPALET :TIPOCONTE NO TIENE\n EQUIVALENCIA EN VDTIPOCONTEEQ")
CAMPO=DESTIPOCONTE,AUXILIAR,NOENTER,AUXILIAR,TOOLTIP("DescripciСn del tipo de contenedor")
CAMPO=EMBCONT,AUXILIAR,TOOLTIP("Embalajes por contenedor"),
             POSTCHANGE=FVALNOCERO("Deben informarse los embalajes por contenedor")
CAMPO=ALTURACONTE,AUXILIAR,TOOLTIP("Altura del contenedor en cm")
CAMPO=BLOQSTOCK,AUXILIAR,OCULTO,TOOLTIP("CalificaciСn de stock de la mercancia"), "_10_____"
CAMPO=BLOQUEOSM,AUXILIAR,OCULTO, "_10_____"
CAMPO=ESTADOS_STOCK,AUXILIAR,OCULTO,"_10_______"
CAMPO=CODCONCE,AUXILIAR,OCULTO,"_10________"
CAMPO=CODMATORI,AUXILIAR,OCULTO,"_18_____"
CAMPO=CODMATDEST,AUXILIAR,OCULTO,"_18_____"
CAMPO=CODUBI,AUXILIAR,OCULTO,"_20_________"
CAMPO=MUESTROTECA,AUXILIAR,OCULTO,"_12_______"
CAMPO=MULTIARTICULO,AUXILIAR,OCULTO,"_"
CAMPO=DIASRETFECPREV,AUXILIAR,OCULTO,"###"
CAMPO=DIASANTFECPREV,AUXILIAR,OCULTO,"###"
CAMPO=PVPVIGENTE,AUXILIAR,OCULTO,"#L##########.###"
CAMPO=PVPNUEVO,AUXILIAR,OCULTO,"#L##########.###"
CAMPO=CODMOV,AUXILIAR,OCULTO,"#########"
CAMPO=MSGERROR,AUXILIAR,OCULTO,"_100___"
CAMPO=DUMMY,AUXILIAR,OCULTO,"#"

#Obtener datos
CURSOR=CSELDESTIPOCONTE SELECT DESTIPOCONTE FROM VDTIPOCONTE WHERE TIPOCONTE=:TIPOCONTE;

CURSOR=CSELDATOSART SELECT DESART, EMBCONT, NUMMUESTRAS, UNIDADESHOST, NVL(DECIMALES,VD.GETPROP('DECIMALES')) PRECIOUNI__DECIMALES,
                           PVPVIGENTE, PVPNUEVO, DECODE(TRAZABULTO,'S',1,0) BULTO__ENTER
                      FROM VDARTIC
                     WHERE CODART = :CODART;

CURSOR=CCADUCI SELECT CADUCI
                 FROM VDLOTES
                WHERE CODLOT = :CODLOT
                  AND CODART = :CODART;

CURSOR=CCALALTPALET SELECT VDCNT.ALTURASTK(:CODART, (:UNIEMB*:EMBCONTREC)+:PICO, :UNIEMB, :TIPOCONTE) ALTURACONTE
                      FROM DUAL;

#Validaciones
# 0-Orden de recepciСn
CURSOR=CVALTIPO SELECT LTO.ESTADOS_STOCK, LTO.MULTIARTICULO, LTO.DIASANTFECPREV, LTO.DIASRETFECPREV
                  FROM VDTIPORDRECLIN LTO, VDCLASEARTIC CLA
                 WHERE LTO.TIPORDREC = :TIPORDREC
                   AND LTO.CODCLASIF = CLA.CODCLASIF
                   AND LTO.CODCLASE  = CLA.CODCLASE
                   AND CLA.CODART    = :CODART
                   AND LTO.ALTAS_MANUALES='S';

CURSOR=CVALDIASRECEP SELECT CASE WHEN FECRECPRE < (FECRECPRE - :DIASANTFECPREV) THEN
                                      'NO SE PUEDEN EMPEZAR A\nRECEPCIONAR HASTA\n EL DIA '||TO_CHAR(TO_DATE((VD.FECHASYS - :DIASANTFECPREV),'J'), 'DD/MM/YYYY')
                                 WHEN FECRECPRE > (FECRECPRE + :DIASRETFECPREV) THEN
                                      'NO SE PUEDE RECEPCIONAR\nEL ULTIMO DIA\nFUE EL '||TO_CHAR(TO_DATE((FECRECPRE + :DIASRETFECPREV),'J'), 'DD/MM/YYYY')
                            END MSGERROR
                       FROM VDORDRECLIN
                      WHERE CODORDREC = :CODORDREC
                        AND CODDIV    = :CODDIV
                        AND CODART    = :CODART
                        AND CODLOT    = NVL(:CODLOT, CODLOT)
                        AND FECRECPRE NOT BETWEEN (FECRECPRE - :DIASANTFECPREV) AND (FECRECPRE + :DIASRETFECPREV);

#     Valida el lote y la caducidad introducido en la recepciСn contra la orden de recepciСn     
CURSOR=CVALLOTEORD BEGIN VDRECEP.VALLOTEORDEN (:CODART, :CODLOT, :CADUCI, :CODORDREC, :CODDIV, :MSGERROR);
                   END;@

# 1-ArtМculo
#     Valida el lote y la caducidad, y lo crea si no existe y es permitido por el tipo de recepciСn.
CURSOR=CVALLOTE BEGIN VDRECEP.VALIDALOTE (:CODART, :CODLOT, :CADUCI, :TIPORDREC, 'S', 'N', :MSGERROR);
                END;@

#     Devuelve los bloqueos o el mensaje de error en el campo Bloqstock, calcula tambiИn el bloqueo del precio si es introducido.
CURSOR=COBTBLOQUEOS SELECT VDRECEP.OBTBLOQUEOS(:ESTADOS_STOCK, :CODART, :CODLOT, :PRECIOUNI) BLOQSTOCK
                      FROM DUAL;

#     El precio vigente y nuevo son iguales, con lo que no serА necesario informar el precio, ya que este serА el precio vigente.
#     El precio vigente y nuevo no son iguales, esto implica que va a haber un reetiquetaje, por lo que a partir de ese momento 
#     deberА informarse el precio en recepciСn, ya que sino se informa no se sabrМa el precio del stock que se estА recepcionando.

CURSOR=CPVPCERO SELECT 1 DUMMY
                  FROM DUAL
                 WHERE :PRECIOUNI = '0'
                   AND :PVPVIGENTE != :PVPNUEVO;

# 2-Cantidad
CURSOR=CVALUNID SELECT 1 DUMMY
                  FROM VDCONVERSIONES
                 WHERE UNIDADORIGEN = :UNIDADESHOST;

CURSOR=CVALEMBCONT SELECT 1 DUMMY
                     FROM DUAL
                    WHERE :EMBCONT*:UNIEMB >= (:UNIEMB*:EMBCONTREC) + :PICO;

#     Valida que no sobrepase la cantidad a recepcionar de la cantidad pendiente de recepcionar de la orden.
CURSOR=CVALCANT SELECT 1 DUMMY
                  FROM DUAL
                 WHERE VDRECEP.CANTPDTE(:CODORDREC, :CODART, :CODDIV, :CODLOT, 0, 'S')  >= (:UNIEMB*:EMBCONTREC) + :PICO;


# 3-Bulto 
CURSOR=CVALBULTO SELECT 1 DUMMY
                   FROM VDMOVIM
                  WHERE BULTO = :BULTO
                    AND STATUS < 12999;

CURSOR=CVALTIPOEMBA SELECT 1 DUMMY
                      FROM VDTIPOEMBA
                     WHERE TIPOEMBA = :TIPOEMBA;


# 4-Contenedor
CURSOR=CVALCODMAT SELECT DECODE(CODRECEP, :CODRECEP, 0, 1) DUMMY
                    FROM VDSTOCK
                   WHERE CODMAT = :CODMAT;

CURSOR=CVERSIERROR SELECT 1 DUMMY 
                     FROM DUAL
                    WHERE :DUMMY = 0;

CURSOR=CMULTIART SELECT 1 DUMMY
                   FROM DUAL
                  WHERE :MULTIARTICULO = 'S';


#5-CONFIRMAR RECEPCION:
CURSOR=INSCONTE INSERT INTO VDCONTE
                           (CODMAT  , TIPOCONTE  , CNTSSCC    , CODUBI     , POSCONTE   , ALTURACONTE, 
                            STATUS  , FECENTRADA , HORAENTRADA, VDEXTRA    , CODCOMEN   , CODOPEMODIF, 
                            FECMODIF, HORAMODIF)
                           (SELECT :CODMAT , :TIPOCONTE  , NULL  , :PULMON , COUNT(*)+1, :ALTURACONTE, 0, VD.FECHASYS, VD.HORASYS, 
                                   NULL, 0,  VDUSER.GETUSER,  VD.FECHASYS, VD.HORASYS
                              FROM VDCONTE
                             WHERE CODUBI = :PULMON);

CURSOR=COBTLINREC BEGIN
                    :DUMMY:= VDRECEP.OBTLINREC (:CODORDREC, :CODRECEP, :CODART, :CODDIV, :CODLOT, :BLOQSTOCK,:CADUCI, ((:UNIEMB*:EMBCONTREC) + :PICO));
                    IF :DUMMY != 0 THEN
                       :MSGERROR := '\nERROR2,\nAL BUSCAR LA LINEA DE LA\nRECEPCION PARA LA RECEPCION\n'|| :CODRECEP;
                    END IF;
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

CURSOR=CCREAMOV BEGIN
                 :CODMOV := 0;
                 VDMOV.CREAMOV (:CODMOV, VD.GETPROP('TAREARECEP'), :CODCONCE, VDST.FMOVRECOGIDO, :CODMATORI, :PULMON, :CODMAT, :CODART, :CODLOT,
                                :UNIEMB, '',((:UNIEMB*:EMBCONTREC) + :PICO),0,0, NULL);
                 IF :CODMOV > 0 THEN
                    VDMOV.VDACTMOVIM (:CODMOV, :PRECIOUNI, :BLOQSTOCK, :BLOQSTOCK, :EMBCONT, :TIPOEMBA, :BULTO, :CODRECEP);
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

CURSOR=CBLOQUEOSM SELECT '1'||SUBSTR(:BLOQSTOCK,2, 10) BLOQUEOSM
                    FROM DUAL;

CURSOR=CUBIDESTM SELECT CNT.CODUBI MUESTROTECA, CNT.CODMAT CODMATDEST
                   FROM VDARTIC ART, VDCONTE CNT, VDUBICA UBI
                  WHERE ART.CODART      = :CODART
                    AND ART.MUESTROTECA = UBI.CODAREA
                    AND UBI.STOCK       = 'S'
                    AND UBI.CODUBI      = CNT.CODUBI
                  ORDER BY 1;

#Igual pero con bloqueos de muestras
CURSOR=CCREAMUESTRAS BEGIN
                      :CODMOV := 0;
                      VDMOV.CREAMOV (:CODMOV, VD.GETPROP('TAREARECEP'), :CODCONCE||'M', VDST.FMOVRECOGIDO, :CODMATORI, :MUESTROTECA, :CODMATDEST, 
                                     :CODART, :CODLOT, :UNIEMB, '',:NUMMUESTRAS, 0,0, NULL); 
                      IF :CODMOV != 0 THEN
                         VDMOV.VDACTMOVIM (:CODMOV, :PRECIOUNI, :BLOQUEOSM, :BLOQUEOSM, :EMBCONT, :TIPOEMBA, :BULTO, :CODRECEP);
                      END IF;
                    END;@
 
CURSOR=CVERERROR SELECT 1 DUMMY
                   FROM DUAL
                  WHERE :MSGERROR IS NULL;

CURSOR=CVERERROR2 SELECT 1 DUMMY
                    FROM DUAL
                   WHERE :CODMOV != 0;

