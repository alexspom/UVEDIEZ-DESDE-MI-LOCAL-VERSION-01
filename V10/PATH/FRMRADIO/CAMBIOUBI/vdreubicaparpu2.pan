# Módulo   : VDREUBICAPARPU2.PAN
# Función  : Cambio de ubicación parcial de stock. 
#            Pantalla de inserción de datos del destino.
#
###########################################
# Histórico de cambios:
# 
CAMBIOS DE UBICACION
_10_______ _10_______  
REUBICACION PARCIAL DE STOCK

 HAY #L######### __ LIBRES

 DESTINO
 LLEVAR #L#########  __ A 
 UBICACION _12_________

|
PREQUERY=FEJECUTA("CSELINITCAMPOS","ERROR AL CALCULAR \nEL STOCK LIBRE.",
                  "CSELLONGERROR","ERROR\n OBTENIENDO VARIABLE\n LONGITUDERROR",
				  FPOSICIONACAMPO(FSUCCESS,"CANTACOGER"),"\n\n ERROR AL POSICIONAR")

POSTQUERY=FEJECUTA(FIF("CSELSINULL",FEJECUTA(FLIMPIABLOQUE("0"),"ERROR\n LIMPIANDO BLOQUE 0",FPOSICIONABLOQUE("0"),"ERROR\n CARGANDO BLOQUE 0"),FSUCCESS),"",
                   "CSELNOTNULL","\nError,\ncontenedor o ubicación\nson obligatorios.",
                   "CSELHAYCANT","\nError,\nla cantidad a coger \nno puede ser mayor\n que la libre.",
                   FEJECUTA("CDAMEFLUJO","","CVERIFFLUJO",""),"\nNO ENCUENTRO VARIABLE\nDE CONFIGURACION OBLIGATORIA\n'FLUJOCAMBIOUBI' \n O ES NULA",                   
                   "CSELCONCEP","ERROR \nNO SE ENCONTRO EL CONCEPTO",
                   FIF("CSELNOCONTE","CSELCONTEVIRT"),"\ERROR \nLA UBICACION NO \n TIENE CONTENEDOR\n VIRTUAL",
                   FIF(FCAMBIOUBISTK(":CODMATORI",":CODUBIDEST",":CODMATDEST",":TAREA",":CODART","","0","",":CANTACOGER","CODMOV",
                                  "N","N",":CODCONCE","10","2000",":CODRECURSO"),
                       FSUCCESS,
                       FEJECUTA("CDIVIDEERROR","ERROR\nDIVIDIENDO ERROR CAMBIO",FFAILURE,":MSGERROR")),"",
                   FIF(FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOV",":CODRECURSO"),
                       FSUCCESS,
                       FEJECUTA("CDIVIDEERROR","ERROR\nDIVIDIENDO ERROR MOV",FFAILURE,":MSGERROR")),"",
                   FIF("CHAYPREASIGORI",FIF("CHAYSTOCKORI",FSUCCESS,"CUPDPREASIGORI"),FSUCCESS),"",
                   "CUPDPREASIGDEST","ERROR AL ASIGNAR\nARTICULO A UBICACION",
                   FCOMMIT,"ERROR\n HACIENDO COMMIT",
                   FLIMPIABLOQUE("0"),"ERROR\n LIMPIANDO BLOQUE 0",
                   FPOSICIONABLOQUE("VDREUBICAPARPUOK.PAN"),"ERROR AL CARGAR \n VDREUBICAPARPUOK.PAN")



# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODMATORI,VIRTUAL,OCULTO
CAMPO=CODART,VIRTUAL,OCULTO
CAMPO=CANTLIBRE,NOENTER,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=UNIDADESHOST,NOENTER
CAMPO=CANTACOGER,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=UNIDACOGER,NOENTER
CAMPO=CODUBIDEST,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FFUERZASCAN("UBI"),"\nERROR\n DEBE SCANNEAR\n LA UBICACION")
CAMPO=CODMATDEST,OCULTO,"_18_"
CAMPO=CODMOV,OCULTO,"@@@@@@@@@"
CAMPO=TAREA,OCULTO,"_255_____"
CAMPO=CODCONCE,OCULTO,"_10______"
CAMPO=MSGERROR,OCULTO,"_512_"
CAMPO=LONGERROR,OCULTO,"@@@"
CAMPO=CODUBIORI,VIRTUAL,OCULTO


# DEFINICION DE CURSORES
CURSOR=CSELINITCAMPOS SELECT VDSTK.CNTDISPONIBLE (:CODMATORI,'U',:CODART) CANTLIBRE, ART.DECIMALES CANTLIBRE__DECIMALES, ART.UNIDADESHOST,
                             ART.UNIDADESHOST UNIDACOGER, '' CODMATDEST, '' CODUBIDEST, 0 CANTACOGER, ART.DECIMALES CANTACOGER__DECIMALES
                        FROM VDARTIC ART
                       WHERE ART.CODART = :CODART;

CURSOR=CSELLONGERROR SELECT VD.GETPROP('LONGITUDERROR') LONGERROR FROM DUAL;

CURSOR=CSELSINULL SELECT :CODUBIDEST FROM DUAL WHERE :CODUBIDEST IS NULL AND :CANTACOGER = 0;

CURSOR=CSELNOTNULL SELECT :CODUBIDEST FROM DUAL WHERE :CODMATDEST IS NOT NULL OR :CODUBIDEST IS NOT NULL;

CURSOR=CSELHAYCANT SELECT :CANTACOGER 
                     FROM DUAL 
                    WHERE :CANTACOGER <= :CANTLIBRE
                      AND :CANTACOGER > 0 ; 

CURSOR=CDAMEFLUJO SELECT 'REUBICAR' TAREA FROM DUAL;

CURSOR=CVERIFFLUJO SELECT :TAREA FROM DUAL WHERE :TAREA IS NOT NULL;


CURSOR=CSELCONCEP  SELECT CODCONCE FROM VDCONCEPTO WHERE CODCONCE='CU';

CURSOR=CSELNOCONTE SELECT :CODUBIDEST FROM DUAL WHERE :CODMATDEST IS NULL ; 

CURSOR=CSELCONTEVIRT SELECT CNT.CODMAT CODMATDEST
                       FROM VDCONTE CNT, VDTIPOCONTE TCO
                      WHERE CNT.CODUBI = :CODUBIDEST AND
                            CNT.TIPOCONTE = TCO.TIPOCONTE AND
                            TCO.MOVIBLE = 'N';

CURSOR=CDIVIDEERROR BEGIN :MSGERROR:=VD.DIVERRORRADIO(:V10ERROR,:LONGERROR);
                    END;@

CURSOR=CHAYPREASIGORI SELECT :CODUBIORI FROM VDUBICA WHERE CODUBI=:CODUBIORI AND CODART IS NOT NULL;

CURSOR=CHAYSTOCKORI SELECT :CODMATORI FROM DUAL WHERE VDSTK.CNTSTOCK(:CODMATORI,'U',:CODART)>0;

CURSOR=CUPDPREASIGORI UPDATE VDUBICA SET CODART=NULL WHERE CODUBI=:CODUBIORI;

CURSOR=CUPDPREASIGDEST UPDATE VDUBICA SET CODART=:CODART WHERE CODUBI=:CODUBIDEST;
