# Módulo   : VDREPULMON.PAN
# Función  : RECEPCIÓN DE MERCANCÍA: Selección del pulmón donde se va a recepcionar
#            Validaciones:
#              - La ubicación debe existir, ser de stock y no bloqueado para entrada.
#              - Buscar la fuente de esa área, es decir, una ubicación que no sea de stock y no esté bloqueada para salida.
#              - El terminal debe poder realizar esta tarea. 
#
# Creación : 30-01-2008
# Autor    : ICC
###########################################
# Histórico de cambios:
# 
SELECCION DE CODIGOS
 _10_______ _10_______

 PULMON  _12___________

 ALBARAN _20___________
 PALETS  @L@@@

 CODIGO  _150__________________________________________________________________________________________________________________________________________________
|


PREQUERY=FEJECUTA("CLIMPIAR","\nERROR,\nAL LIMPIAR LOS CAMPOS",
                  "CCALCTOTAL","\nERROR\nAL OBETENER NUMERO DE PALETS",
                  FPOSICIONACAMPO(FSUCCESS,"CODIGO"),"\nERROR,\nAL POSICIONARSE EN EL CAMPO")

POSTQUERY=FEJECUTA(FIF("CSELNULL",FPOSICIONABLOQUE("VDRECALBARAN.PAN"),FSUCCESS),"",
                   "CVERIFPULMON","\nERROR,\nNO EXISTE\n EL PULMON :PULMON",
                   "CSELFUENTE","\nERROR,\nNO EXISTE NINGUNA FUENTE\nEN EL AREA DE :PULMON",
                   "CPERMISORECURSO", "\nERROR,\nEL TERMINAL NO TIENE\nPERMISOS PARA REALIZAR\nESTA TAREA",
                   +FLEEARTICULO("CODEAN","CODART","","CODLOT"),"ERROR",
                   "-CSELSSCC","PALET \n:SSCC \nYA LEIDO",
                   "+CSELDATOSSSCC","\nERROR,\nEL CODIGO DE BARRAS\nNO TIENE INFORMACION\nASOCIADA",
                   FPOSICIONABLOQUE("VDRECARTICULOCSF.PAN"),"\nNO SE PUEDE POSICIONAR\nEN EL SIG. BLOQUE")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=PULMON,SCAN,AUTOENTER
CAMPO=CODALBPROVE,VIRTUAL,NOENTER
CAMPO=NUMPALETS,NOENTER
CAMPO=CODIGO,SCAN(4),POSTCHANGE=FDESIGNACION(FIF("CSELNULL",FCARGAFORM(""),FSUCCESS),"",
                                              +FANALIZAEANRAD("CODIGO","3103","PESO3","3102","PESO2","3101","PESO1","3100","PESO0","15","CADUCI","17","CADUCI",
                                                              "00","SSCC","01","CODEAN","02","CODEAN","10","CODLOT","37","EMBCONT","30","EMBCONT","240","CODEAN","3302","PBRUTO2"),"\nERROR,\nEN LECTURA DEL\nCODIGO DE BARRAS")                                             
CAMPO=FUENTE,OCULTO,"_12___________"
CAMPO=CODAREA,OCULTO,"_10_______"
CAMPO=CODUBI,OCULTO,"_12___________"
CAMPO=DUMMY,OCULTO,"#"
CAMPO=SSCC,OCULTO,"_18_________________"
CAMPO=CODEAN,OCULTO,"_18_________________"
#CAMPO=UNIEMB,OCULTO,"#L#######"
CAMPO=EMBCONT,OCULTO,"#L######"
CAMPO=CADUCI,OCULTO,"_8______",POSTCHANGE=FEJECUTA("+CPONCADUCI","")
CAMPO=PESO,OCULTO,"#L####.####"
CAMPO=PESO3,OCULTO,"#L####",POSTCHANGE=FEJECUTA("+CDAMEPESO3","ERROR\nCALCULANDO EL PESO-3 CON DECIMALES") 
CAMPO=PESO2,OCULTO,"#L####",POSTCHANGE=FEJECUTA("+CDAMEPESO2","ERROR\nCALCULANDO EL PESO-2 CON DECIMALES") 
CAMPO=PESO1,OCULTO,"#L####",POSTCHANGE=FEJECUTA("+CDAMEPESO1","ERROR\nCALCULANDO EL PESO-1 CON DECIMALES") 
CAMPO=PESO0,OCULTO,"#L####",POSTCHANGE=FEJECUTA("+CDAMEPESO0","ERROR\nCALCULANDO EL PESO-0 CON DECIMALES")
CAMPO=PBRUTO2,OCULTO,"#L####"
CAMPO=CANTIDAD,OCULTO,"#L######"
CAMPO=CODART,OCULTO,"_50_______________________"
CAMPO=CODLOT,OCULTO,"_20_________________"
CAMPO=CODORDREC,OCULTO,"_20________________"



CURSOR=CLIMPIAR SELECT 'ENTRADAS' PULMON, '' CODIGO, 0 SSCC, '' CODEAN, '' CODLOT, '' CADUCI, 0 PESO, 0 PESO1, 0 PESO0, 0 PBRUTO2, 0 CANTIDAD, 
                       '' CODART, '' CODLOT, 0 EMBCONT FROM DUAL;
#0 UNIEMB, 
CURSOR=CSELNULL SELECT 1 DUMMY FROM DUAL WHERE :CODIGO IS NULL;

#La ubicación debe existir y ser de stock y no bloqueado para entrada y salida:
CURSOR=CVERIFPULMON SELECT CODAREA
                      FROM VDUBICA
                     WHERE CODUBI    = :PULMON
                       AND STOCK     = 'S'
                       AND BLOQUEOSE = 'N'
                       AND BLOQUEOSS = 'N';

#Buscar la fuente de esa área, es decir, una ubicación que no sea de stock y no esté bloqueada para salida.
CURSOR=CSELFUENTE SELECT CODUBI
                    FROM VDUBICA
                   WHERE CODAREA = :CODAREA
                     AND STOCK     = 'N'
                     AND BLOQUEOSS = 'N';

#El terminal debe poder realizar esta tarea.
CURSOR=CPERMISORECURSO SELECT 1 DUMMY
                         FROM VDRECTAREA REC, VDPERFILTAREA PTA,
                              (SELECT PRIVILEGIO
                                 FROM VDPRIVGRU PRG, VDGRUPOOPE GRO
                                WHERE GRO.CODOPE = :CODOPE
                                  AND GRO.CODGRUPO = PRG.CODGRUPO
                               UNION
                               SELECT PRIVILEGIO
                                 FROM VDPRIVOPE
                                 WHERE CODOPE = :CODOPE) B
                        WHERE REC.CODRECURSO= :CODRECURSO
                          AND REC.CODPERFIL = PTA.CODPERFIL
                          AND (TRIM(PTA.PRIVILEGIOSTAREA) IS NULL
                          OR VD.CONTIENE(PTA.PRIVILEGIOSTAREA,B.PRIVILEGIO,',','-',1) = 1)
                          AND VD.CONTIENE(PTA.RANTAREA, VD.GETPROP('TAREARECEP'),',','-',1) = 1;

CURSOR=CPONCADUCI SELECT '20'||:CADUCI CADUCI
                    FROM DUAL
                   WHERE LENGTH(:CADUCI)=6;

CURSOR=CDAMEPESO3 SELECT :PESO3/1000 PESO FROM DUAL WHERE :PESO3 <> 0;  
CURSOR=CDAMEPESO2 SELECT :PESO2/100 PESO FROM DUAL WHERE :PESO2 <> 0;                          
CURSOR=CDAMEPESO1 SELECT :PESO1/10 PESO FROM DUAL WHERE :PESO1 <> 0;                          
CURSOR=CDAMEPESO0 SELECT :PESO0 PESO FROM DUAL WHERE :PESO0 <> 0;

CURSOR=CSELSSCC SELECT :SSCC
                FROM VDCONTE CNT, VDSTOCK STK, VDRECEPCAB REC
                WHERE CNT.CNTSSCC=:SSCC AND :SSCC>0 AND CNT.CODMAT = STK.CODMAT AND STK.CODRECEP = REC.CODRECEP AND REC.CODALBPROVE = :CODALBPROVE;

CURSOR=CCALCTOTAL SELECT COUNT(DISTINCT CODMAT) NUMPALETS
                    FROM VDCONTE
                    WHERE CODMAT IN (SELECT STK.CODMAT
                                      FROM VDSTOCK STK,VDRECEPCAB REC
                                      WHERE STK.CODRECEP=REC.CODRECEP AND REC.CODALBPROVE=:CODALBPROVE);
   
CURSOR=CSELDATOSSSCC SELECT CODART,LOTE_FABRICACION CODLOT,
                            TO_CHAR(TO_DATE(FECHA_CADUCIDAD,'DD-MON-YY'),'YYYYMMDD') CADUCI,
                            PESO_KG PESO
                       FROM VDENVIOSVIRTO, VDARTIC
                      WHERE COD_PALET=:SSCC AND N_TRASLADO=:CODALBPROVE AND
                            COD_MERCANCIA=CODARTDIV;
                       