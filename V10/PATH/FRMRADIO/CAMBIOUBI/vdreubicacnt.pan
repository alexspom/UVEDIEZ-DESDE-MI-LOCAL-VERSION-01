# M�dulo   : VDREUBICACNT.PAN
# Funci�n  : Cambio de ubicaci�n de contenedor
#
# Creaci�n : 06-05-2008
# Autor    : JMM
###########################################
# Hist�rico de cambios:
# 
CAMBIOS DE UBICACION
_10_______ _10_______  
REUBICACION DE CONTENEDOR

 CONTENEDOR:  _20_________________
 A UBICACION: _12_________
 CHEQUEAR FLUJO: _

|

PREQUERY=FEJECUTA("+CINITCAMPOS","",
                  "CSELLONGERROR","ERROR\n OBTENIENDO VARIABLE\n LONGITUDERROR")

POSTQUERY=FEJECUTA(FIF("CSELNOTNULL",FCARGAFORM(""),FSUCCESS),"ERROR\n AL VOLVER AL MENU",
                   "CCHECKCHEQUEAFLUJOS","\nERROR\n CHEQUEAR FLUJO DEBE VALER \n S o N",
                   FIF("CCHEQUEAFLUJOS",FEJECUTA("CDAMEFLUJO","",
                                                 "CVERIFFLUJO","")),"\nNO ENCUENTRO VARIABLE\nDE CONFIGURACION OBLIGATORIA\n'FLUJOCAMBIOUBI' \n O ES NULA",
                   "-CSELVERIFCNT","\nERROR,\n CONTENEDOR CON MOVIMIENTOS\n PENDIENTES",
                   "CCHECKMOVIBLE","\n ERROR\n CONTENEDOR NO EXISTE \n O ES NO MOVIBLE",
                   "CSELBLOQORI","\nERROR,\n LA UBICACION ORIGEN\n ESTA BLOQUEADA PARA SALIDA",
                   "CSELBLOQDEST","\nERROR,\n LA UBICACION DESTINO\n ESTA BLOQUEADA PARA ENTRADA",
                   "CSELCONCEP","ERROR \nNO SE ENCONTRO EL CONCEPTO",
                   "CSELPERMISOS","\nERROR, \n ESTE TERMINAL NO TIENE\n PERMISOS PARA ESTE CAMBIO\n DE UBICACION",
                   FIF(FCAMBIOUBICONTE(":CODMAT",":CODUBIDEST",":TAREA","CODMOV",":CHEQUEAFLUJOS","N",
                                ":CODCONCE","10","2000",":CODRECURSO"),
                       FSUCCESS,
                       FFAILURE),"ERROR AL REUBICAR",
                   FIF(FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOV",":CODRECURSO"),
                       FSUCCESS,
                       FEJECUTA("CDIVIDEERROR","ERROR\nDIVIDIENDO ERROR MOV",FFAILURE,":MSGERROR")),"",
                   FCOMMIT,"ERROR\n HACIENDO COMMIT",
                   FLIMPIABLOQUE("0"),"ERROR\n EN FLIMPIABLOQUE",
                   "CINITCAMPOS","",
                   FFAILURE,"\nCAMBIO REALIZADO")



# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODMAT,SCAN,POSTCHANGE=FEJECUTA("CELIMINA00", "ERROR AL TRATAR MATRICULA")
                          
CAMPO=CODUBIDEST,SCAN,POSTCHANGE=FEJECUTA(FFUERZASCAN("UBI"),"\nERROR\n DEBE SCANNEAR\n LA UBICACION",FPULSATECLAS("9","335","331"),"")
CAMPO=CHEQUEAFLUJOS,UPPER,NOENTER
CAMPO=CODCONCE,OCULTO,"__________"
CAMPO=TAREA,OCULTO,"_32_______________"
CAMPO=CODMOV,OCULTO,"@@@@@@@@@"
CAMPO=MSGERROR,OCULTO,"_512_"
CAMPO=LONGERROR,OCULTO,"@@@"

# DEFINICION DE CURSORES
CURSOR=CINITCAMPOS SELECT 'N' CHEQUEAFLUJOS, NULL CODMAT, NULL CODUBIDEST FROM DUAL;

CURSOR=CSELLONGERROR SELECT VD.GETPROP('LONGITUDERROR') LONGERROR FROM DUAL;

CURSOR=CSELNOTNULL SELECT :CODMAT FROM DUAL WHERE :CODMAT IS NULL;

CURSOR=CCHECKCHEQUEAFLUJOS SELECT :CHEQUEAFLUJOS FROM DUAL WHERE :CHEQUEAFLUJOS IN ('S','N');

CURSOR=CCHEQUEAFLUJOS SELECT :CHEQUEAFLUJOS FROM DUAL WHERE :CHEQUEAFLUJOS = 'S';

CURSOR=CVERIFFLUJO SELECT :TAREA FROM DUAL WHERE :TAREA IS NOT NULL;

CURSOR=CSELCONCEP  SELECT CODCONCE
                     FROM VDCONCEPTO
                    WHERE CODCONCE='CU';

CURSOR=CSELVERIFCNT SELECT :CODMAT 
                       FROM VDMOVIM
                       WHERE (CODMATDEST=:CODMAT OR CODMATORI=:CODMAT) AND STATUS < VDST.FMOVACTUALIZA;

CURSOR=CSELBLOQORI SELECT :CODMAT
                     FROM VDUBICA UBI, VDCONTE CNT
                    WHERE CNT.CODMAT=:CODMAT AND UBI.CODUBI=CNT.CODUBI AND UBI.BLOQUEOSS='N';

CURSOR=CSELBLOQDEST SELECT :CODUBIDEST CODUBIDEST
                      FROM VDUBICA 
                     WHERE CODUBI=:CODUBIDEST AND BLOQUEOSE='N';
                    
CURSOR=CSELPERMISOS SELECT :CODRECURSO
                      FROM VDRECTAREA TAR, VDPERFILTAREA PTA, VDCONTE CNT, VDUBICA UBIORI, VDUBICA UBIDEST
                     WHERE TAR.CODRECURSO = :CODRECURSO
                       AND TAR.CODPERFIL  = PTA.CODPERFIL
                       AND VD.CONTIENECAD(PTA.RANTAREA,:TAREA,',','-',1) = 1
                       AND CNT.CODMAT     = :CODMAT
                       AND CNT.CODUBI     = UBIORI.CODUBI
                       AND VD.CONTIENECAD(PTA.RANAREAORI,UBIORI.CODAREA,',','-',1) = 1
                       AND UBIDEST.CODUBI = :CODUBIDEST
                       AND VD.CONTIENECAD(PTA.RANAREADEST,UBIDEST.CODAREA,',','-',1) = 1;

CURSOR=CCHECKMOVIBLE SELECT :CODMAT
                       FROM VDCONTE CNT, VDTIPOCONTE TCO 
                      WHERE CNT.CODMAT=:CODMAT AND
                            CNT.TIPOCONTE=TCO.TIPOCONTE AND
                            TCO.MOVIBLE = 'S';

CURSOR=CDAMEFLUJO SELECT 'REUBICAR' TAREA FROM DUAL;

CURSOR=CDIVIDEERROR BEGIN :MSGERROR:=VD.DIVERRORRADIO(:V10ERROR,:LONGERROR);
                    END;@

CURSOR=CELIMINA00 SELECT CASE WHEN LENGTH(:CODMAT)=20 THEN SUBSTR(:CODMAT,3) ELSE :CODMAT END CODMAT FROM DUAL;	