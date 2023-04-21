# Módulo   : VDRECARTICULO.PAN
# Función  : RECEPCIÓN DE MERCANCÍA: Selección del artículo que se va a recepcionar
#            Validaciones:
#             Se podrá leer tanto el código de barras como introducir el código del artículo.
#             - Tipo palet: mostrará el que tenga por defecto en vdartic.tipopalet, si no 
#                contiene ningún valor, se mostrará el de la varialbe TIPOPALET. Deberá
#                existir como tipo de palet.
#             - Capacidad (emb/cont): mostrará el que tenga por defecto en vdartic.embcont, 
#                pero siempre se podrá modificar.
#             - Precio unidad: No se valida
#             - Buscar código de recepción del operario que esté pendiente de validar o
#               crear un nuevo código de recepción, idem para la línea de recepción.
#            
# Creación : 31-01-2008
# Autor    : ICC
###########################################
# Histórico de cambios:
# 
SELECCION ARTICULO
 _10_______ _10_______

 PULMON: _12_________
 _11__ _20________________
 REC.: _20________________
 DIV.: _5___ _40_____________
 PALET: _18_______________

 ART.: _50_______________________________________________________________________
       _50_______________________________________________________________________
 
 TIPO PALET  : _10_______
 CAPACIDAD: #### EMB/CONT
|


PREQUERY=FEJECUTA("CLIMPIAR","\nERROR,\nAL LIMPIAR LOS CAMPOS",
                  "COCULTACAMPOS", "\nERROR,\nOCULTANDO CÓDIGO DE BARRAS 2", 
                  "CINICIO","\nERROR,\nINICIALIZANDO CAMPOS", 
                  FIF("-CSELARTNULL",FEJECUTA("+CSELART","ERROR CALCULANDO LA DESCRIPCION DEL ARTICULO",
                                              "+CSELDIV","ERROR CALCULANDO LA DESCRIPCION DE LA DIVISION",
                                              "CRECEP","\nERROR,\nOBTENIENDO LA RECEPCION",
                                              "+CSELCONTE","\nERROR,\nOBTENIENDO EL CONTENEDOR",
                                              "CSELCLASEART", "\nERROR,\nEL ARTICULO :CODART\nNO ESTA CLASIFICADO\nPARA EL TIPO DE RECEPCION\n :TIPORDREC",
                                              FCOMMIT,"",
                                              FPOSICIONABLOQUE("VDRECCANTIDADCSF.PAN"),"\nNO SE PUEDE POSICIONAR\nEN EL SIG. BLOQUE"),
                                    FPOSICIONACAMPO(FSUCCESS,"CODART"),"\nERROR,\nAL POSICIONARSE EN EL CAMPO"),"")

POSTQUERY=FEJECUTA(FIF("CSELNOTNULL",FPOSICIONABLOQUE("VDRECPULMONCSF.PAN"),FSUCCESS),"",
                   "CSELCLASEART", "\nERROR,\nEL ARTICULO :CODART\nNO ESTA CLASIFICADO\nPARA EL TIPO DE RECEPCION\n :TIPORDREC",
                   FPOSICIONABLOQUE("VDRECCANTIDADCSF.PAN"),"\nNO SE PUEDE POSICIONAR\nEN EL SIG. BLOQUE")


CAMPO=TIPORDREC,OCULTO,"_40________"
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=PULMON,NOENTER,VIRTUAL
CAMPO=NCODORDREC,NOENTER
CAMPO=CODORDREC,NOENTER,VIRTUAL
CAMPO=CODRECEP,NOENTER 
CAMPO=CODDIV

CAMPO=DESDIV,NOENTER
CAMPO=CODMAT,NOENTER
CAMPO=CODART,VIRTUAL,POSTCHANGE=FDESIGNACION(FIF("CSELNOTNULL",FPOSICIONABLOQUE("VDRECPULMONCSF.PAN"),FSUCCESS),"",
                                                 +FLEEARTICULO("CODART", "CODARTAUX","", "CODLOT"),":V10ERROR",
                                                 "+CSELCODART","\nERROR,\nOBTENIENDO EL CÓDIGO DE ARTICULO", 
                                                 "CSELART", "\nERROR,\nNO EXISTE EL ARTICULO\n :CODART",
                                                 "CRECEP","\nERROR,\nOBTENIENDO LA RECEPCION",
                                                 "+CSELCONTE","\nERROR,\nOBTENIENDO EL CONTENEDOR", 
                                                 FCOMMIT,"")
CAMPO=DESART,NOENTER
CAMPO=CODARTAUX,OCULTO,"_50___________"
CAMPO=DUMMY,OCULTO,"#"
CAMPO=TIPOCONTE,POSTCHANGE=FEJECUTA("CVALTIPOPALET","\nERROR,\nNO EXISTE TIPO DE PALET\n :TIPOCONTE") 
CAMPO=EMBCONT,VIRTUAL
CAMPO=TIPOEMBA,OCULTO,"_10_______",POSTCHANGE=FEJECUTA("CVALTIPOEMBA","\nERROR,\nNO EXISTE TIPO DE EMBALAJE\n :TIPOEMBA") 
CAMPO=PRECIOUNI,OCULTO,"#L##############", CONVIERTE=FCONVIERTEINVARTFROMDB(":CODART");FCONVIERTEINVART2DB(":CODART"),
                POSTCHANGE=FEJECUTA("-CPVPCERO","DEBE INFORMAR EL PRECIO,\nSE ENCUENTRA EN PERIODO DE\n REETIQUETAJE")
CAMPO=DECIMALES,OCULTO,"#"
CAMPO=PVPVIGENTE,OCULTO,"#L##########.###"
CAMPO=PVPNUEVO,OCULTO,"#L##########.###"

CAMPO=CODLOT,VIRTUAL,OCULTO
CAMPO=CADUCI,VIRTUAL,OCULTO
#CAMPO=UNIEMB,VIRTUAL,OCULTO
CAMPO=ESTADOS_STOCK, OCULTO,"_10_______"
CAMPO=INDLOTE,  OCULTO,"_"
CAMPO=MUESTREAR,OCULTO,"_"
CAMPO=DIASANTFECPREV,OCULTO,"###"
CAMPO=DIASRETFECPREV,OCULTO,"###"
CAMPO=MULTIARTICULO,OCULTO,"_"
CAMPO=NBULTOS,OCULTO,"######"
CAMPO=CONTBULTOS,OCULTO,"########"
CAMPO=PANTANTERIOR,OCULTO,"_20______________"
CAMPO=PESO,VIRTUAL,OCULTO 
CAMPO=SSCC,VIRTUAL,OCULTO
CAMPO=CODALBPROVE,VIRTUAL,OCULTO

CURSOR=CINICIO SELECT 'NORMAL' TIPORDREC  FROM DUAL;

CURSOR=CLIMPIAR SELECT '' DESART, '' CODARTAUX, '' CODDIV, '' DESDIV, '' CODRECEP, 0 CODMAT, '' TIPOCONTE FROM DUAL;

CURSOR=CSELNOTNULL SELECT 1 DUMMY FROM DUAL WHERE :CODART IS NULL AND :EMBCONT=0 AND :CODDIV IS NULL;

CURSOR=CSELARTNULL SELECT 1 DUMMY FROM DUAL WHERE :CODART IS NULL;

CURSOR=COCULTACAMPOS SELECT DECODE(:CODORDREC, null, 0, 1) NCODORDREC__INVISIBLE,
                            DECODE(:CODORDREC, null, 0, 1) CODORDREC__INVISIBLE
                        FROM DUAL;
                    
CURSOR=CSELCODART SELECT :CODARTAUX CODART FROM DUAL WHERE :CODARTAUX IS NOT NULL;      

CURSOR=CSELCONTE SELECT VDSECCNT.NEXTVAL CODMAT FROM DUAL WHERE :CODMAT = 0 OR :CODMAT IS NULL;      

#Recupera una recepción que haya realizado el recurso y no se haya validado, siendo para la misma orden de 
#recepción y para el mismo albarán, si se recepcionara contra una orden. En caso de no encontrar ninguna, crea una nueva
CURSOR=CRECEP BEGIN
             :CODRECEP := VDRECEP.OBTRECEPSINRECURSO (NULL, :TIPORDREC, :CODDIV, :CODALBPROVE);
             END;@

##VALIDACIONES
CURSOR=CSELART SELECT CODART, NVL(:TIPOCONTE,NVL(TIPOCONTEDEF, VD.GETPROP('TIPOCONTE'))) TIPOCONTE, 
                      NVL(:TIPOEMBA,NVL(TIPOEMBADEF, VD.GETPROP('TIPOEMBA'))) TIPOEMBA, DECODE(:EMBCONT,0,EMBCONT,NULL,EMBCONT,:EMBCONT) EMBCONT, 
                      4 PRECIOUNI__DECIMALES, 4 DECIMALES, PVPVIGENTE, PVPNUEVO,
                      DESART, CODDIV, 'N' MULTIARTICULO 
               FROM VDARTIC
               WHERE CODART = :CODART OR (CODARTDIV = :CODART AND CODDIV = :CODDIV);

CURSOR=CSELDIV SELECT DESDIV FROM VDDIVIS WHERE CODDIV = :CODDIV;

CURSOR=CVALTIPOPALET SELECT 1 DUMMY           
                     FROM VDTIPOCONTE       
                     WHERE TIPOCONTE = :TIPOCONTE;
                     
CURSOR=CVALTIPOEMBA SELECT 1 DUMMY            
                      FROM VDTIPOEMBA
                     WHERE TIPOEMBA = :TIPOEMBA AND :TIPOEMBA IS NOT NULL;   

CURSOR=CPVPCERO SELECT 1 DUMMY
                  FROM DUAL
                 WHERE :PRECIOUNI = '0'
                   AND :PVPVIGENTE != :PVPNUEVO;                                       
                       
CURSOR=CSELCLASEART SELECT TOL.ESTADOS_STOCK, INDLOTE, MUESTREAR, DIASANTFECPREV, DIASRETFECPREV
                      FROM VDCLASEARTIC CLA, VDTIPORDRECLIN TOL
                     WHERE CLA.CODART = :CODART
                       AND TOL.CODCLASIF = CLA.CODCLASIF
                       AND TOL.CODCLASE = CLA.CODCLASE
                       AND TOL.TIPORDREC = :TIPORDREC;
                                           