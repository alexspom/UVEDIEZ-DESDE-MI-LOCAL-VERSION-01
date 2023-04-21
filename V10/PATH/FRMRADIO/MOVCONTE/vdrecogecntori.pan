# M�dulo   : VDRECOGECNTORI.PAN
# Funci�n  : Recogida en origen de un palet completo
#
# Creaci�n : 19-05-2008
# Autor    : JMM
###########################################
# Hist�rico de cambios:
#
MOVIMIENTO DE CONTENEDOR
_10_______ _10_______  
RECOGER CONTENEDOR COMPLETO 
_32____________________
 MOVIMIENTO @L@@@@@@@
_____     ___        ________  
#####  *  #L#######      #L#######
______________
#L############# _10__ 
_________ _40_________________
   _20_________________
   _20_________________

UB. ORIG.  _20_________________   
MATRICULA _18_______________

MATRICULA _20_________________
|



PREQUERY=FEJECUTA(FIF("CRESTAURAMOVDEST",FEJECUTA(FPOSICIONABLOQUE("VDDEPOSITACNTDEST.PAN"),"ERROR \n AL CARGAR VDDEPOSITACNTDEST.PAN"),
                                         FEJECUTA("CSELCODMOV","\nERROR, OBTENIENDO\n DATO DEL MOVIMIENTO\n :CODMOV")),"",
                  "CSELLONGERROR","ERROR\n OBTENIENDO PROPIEDAD\n LONGERROR",
                  "+CSELMULTIART","",
                  "CSELCONVCANTYUNI","\nERROR\n AL CONVERTIR\nCANTIDAD Y UNIDADES",
                  "CPONCANTIDADES","ERROR\n PONIENDO CANTIDADES",
                  "CSELCOMPACTADISTUBI","ERROR \n OBTENIENDO VARIABLE\n COMPACTADISTUBI")

POSTQUERY=FEJECUTA(FIF("CSELMATNULL",FEJECUTA(FCARGAFORM(""),"ERROR\n VOLVIENDO AL MENU"),
                                     FSUCCESS),"",
                   "CSELVERIFCNT","\nERROR,\n CONTENEDOR INCORRECTO\n LEIDO :CODMATORILEIDO\n ESPERADO :CODMATORI",
                   FIF(FREENGANCHACONTE(":CODMOV",":CODMATORILEIDO",":COMPACTADISTUBI"),
                       FSUCCESS,
                       FEJECUTA("CDIVIDEERROR","ERROR\nDIVIDIENDO ERROR",FFAILURE,":MSGERROR")),"",
                   "CSELVERIFCNT","\nERROR,\n CONTENEDOR INCORRECTO\n LEIDO :CODMATORILEIDO\n ESPERADO :CODMATORI",
                   FIF(FRECOGESTKSYNC("ACTSTKORIGEN",":CODMOV",":CODRECURSO"),
                       FSUCCESS,
                       FEJECUTA("CDIVIDEERROR","ERROR\nDIVIDIENDO ERROR MOV",FFAILURE," mi error :MSGERROR")),"",
                   FCOMMIT,"\nERROR,\n HACIENDO COMMIT.",
                   FPOSICIONABLOQUE("VDDEPOSITACNTDEST.PAN"),"ERROR \n AL CARGAR VDDEPOSITACNTDEST.PAN")


# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=TAREA,NOENTER
CAMPO=CODMOV,NOENTER,VIRTUAL
CAMPO=CODUBIDEST,NOENTER,OCULTO,"_20_"
CAMPO=PINTACODUBIDEST,NOENTER,OCULTO,"_20"
CAMPO=LITNCAJAS,NOENTER
CAMPO=LITUNIEMB,NOENTER
CAMPO=LITUNIDSUELTAS,NOENTER
CAMPO=NCAJAS,NOENTER
CAMPO=UNIEMB,NOENTER,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=UNIDSUELTAS,NOENTER,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=LITTOTALUNID,NOENTER
CAMPO=TOTALUNID,NOENTER,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=UNIDADESHOST,NOENTER
CAMPO=LITCODART,NOENTER
CAMPO=CODART,NOENTER
CAMPO=DESART1,NOENTER
CAMPO=DESART2,NOENTER
CAMPO=CODUBIORI,NOENTER,OCULTO,"_20"
CAMPO=PINTACODUBIORI,NOENTER
CAMPO=CODMATORI,NOENTER
CAMPO=CODMATORILEIDO,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FFUERZASCAN("CNT"),"\n ERROR\n DEBE LEER\n EL PALLET",
                                                        "CELIMINA00", "ERROR AL TRATAR MATRICULA")
CAMPO=MSGERROR,OCULTO,"_512_"
CAMPO=NUMARTICS,OCULTO,"@L@@@"
CAMPO=LONGERROR,OCULTO,"@@@"
CAMPO=COMPACTADISTUBI,OCULTO,"@"


# DEFINICION DE CURSORES
CURSOR=CRESTAURAMOVDEST SELECT MOV.TAREA, MOV.CODMOV, MOV.CODUBIORI,VDCLIPKG.PINTAUBICA(MOV.CODUBIORI) PINTACODUBIORI, MOV.CODUBIDEST,VDCLIPKG.PINTAUBICA(MOV.CODUBIDEST) PINTACODUBIDEST,MOV.CODMATORI
                          FROM VDMOVIM MOV 
                         WHERE STATUS=VDST.FMOVENUBIINTER AND 
                               CODRECURSO=:CODRECURSO  AND
                               VDMOV.MUEVETODO(CODMOV)=1;

CURSOR=CSELCODMOV SELECT MOV.TAREA, MOV.CODMOV, MOV.CODUBIORI,VDCLIPKG.PINTAUBICA(MOV.CODUBIORI) PINTACODUBIORI, MOV.CODUBIDEST,VDCLIPKG.PINTAUBICA(MOV.CODUBIDEST) PINTACODUBIDEST,  MOV.CODMATORI, MOV.CODART,
                         VD.DIVIDEXBUSQUEDA(1,ART.DESART,' ',20,0) DESART1,VD.DIVIDEXBUSQUEDA(2,ART.DESART,' ',20,0) DESART2,
                         ART.DECIMALES UNIEMB__DECIMALES, ART.DECIMALES UNIDSUELTAS__DECIMALES, ART.DECIMALES TOTALUNID__DECIMALES,
                         ART.UNIDADESHOST, MOV.UNIEMB
                    FROM VDMOVIM MOV, VDARTIC ART
                   WHERE MOV.CODMOV=:CODMOV
                     AND MOV.CODART=ART.CODART;

CURSOR=CSELLONGERROR SELECT VD.GETPROP('LONGITUDERROR') LONGERROR FROM DUAL;

CURSOR=CSELCOMPACTADISTUBI SELECT VD.GETPROP('COMPACTADISTUBI') COMPACTADISTUBI FROM DUAL;

CURSOR=CSELMULTIART SELECT COUNT(DISTINCT CODART) NUMARTICS FROM VDSTOCK WHERE CODMAT = :CODMATORI;

CURSOR=CPONCANTIDADES SELECT (:NCAJAS * :UNIEMB + :UNIDSUELTAS )  TOTALUNID,
                             'CAJAS' LITNCAJAS,
                             DECODE(:NUMARTICS,1,0,1) LITNCAJAS__INVISIBLE,
                             DECODE(:NUMARTICS,1,0,1) NCAJAS__INVISIBLE,
                             'U/E' LITUNIEMB,
                             DECODE(:NUMARTICS,1,0,1) LITUNIEMB__INVISIBLE,
                             DECODE(:NUMARTICS,1,0,1) UNIEMB__INVISIBLE,
                             '+   PICO' LITUNIDSUELTAS,
                             DECODE(:NUMARTICS,1,0,1) LITUNIDSUELTAS__INVISIBLE,
                             DECODE(:NUMARTICS,1,0,1) UNIDSUELTAS__INVISIBLE,
                             DECODE(:NUMARTICS,1,0,1) UNIDADESHOST__INVISIBLE,
                             'TOTAL UNIDADES' LITTOTALUNID,
                             DECODE(:NUMARTICS,1,0,1) LITTOTALUNID__INVISIBLE,
                             DECODE(:NUMARTICS,1,0,1) TOTALUNID__INVISIBLE,
                             'ARTICULO:' LITCODART,
                             DECODE(:NUMARTICS,1,0,1) LITCODART__INVISIBLE,
                             DECODE(:NUMARTICS,1,0,1) CODART__INVISIBLE,
                             DECODE(:NUMARTICS,1,0,1) DESART1__INVISIBLE,
                             DECODE(:NUMARTICS,1,0,1) DESART2__INVISIBLE,
                             NULL CODMATORILEIDO
                        FROM DUAL;

CURSOR=CSELCONVCANTYUNI SELECT FLOOR(SUM(STK.CANTIDAD/DECODE(STK.UNIEMB,0,1,STK.UNIEMB))) NCAJAS, 
                               SUM(STK.CANTIDAD)-(FLOOR (SUM(STK.CANTIDAD)/DECODE(STK.UNIEMB,0,1,STK.UNIEMB))*DECODE(STK.UNIEMB,0,1,STK.UNIEMB)) UNIDSUELTAS 
                          FROM VDSTOCK STK
                         WHERE STK.CODMAT = :CODMATORI
                         GROUP BY STK.UNIEMB;

CURSOR=CSELMATNULL SELECT :CODMATORILEIDO
                     FROM DUAL
                    WHERE :CODMATORILEIDO IS NULL;

CURSOR=CSELVERIFCNT SELECT :CODMATORILEIDO CODMATORI FROM DUAL WHERE :CODMATORI=:CODMATORILEIDO; 


CURSOR=CDIVIDEERROR BEGIN :MSGERROR:=VD.DIVERRORRADIO(:V10ERROR,:LONGERROR);
                    END;@

CURSOR=CELIMINA00 SELECT CASE WHEN LENGTH(:CODMATORILEIDO)=20 AND :CODMATORILEIDO LIKE '00%' THEN SUBSTR(:CODMATORILEIDO,3) ELSE :CODMATORILEIDO END CODMATORILEIDO FROM DUAL;