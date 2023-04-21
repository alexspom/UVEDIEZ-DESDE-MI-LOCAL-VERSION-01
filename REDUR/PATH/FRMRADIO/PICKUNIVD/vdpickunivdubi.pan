# M�dulo   : VDPICKUNIVDUBI.PAN
# Funci�n  : Formulario de recogida de bultos de unidades.
#            Pantalla de confirmaci�n de ubicaci�n.
#
# Creaci�n : 02-04-2020
# Autor    : FPD
###########################################
# Hist�rico de cambios:
#
PICKING DE UNIDADES
_10_______ _10_______
_____________________
PED._20________  @L@@@@
MAT: _255__________________
TOTAL UNIDADES: @L@@@@@
ARTICULO: _40_____________
  _20_________________
  _20_________________ 
_5___ _40_________________

UBI: ____________________
     ____________________

|

PREQUERY=FEJECUTA("CSELLONGERROR","\n\n ERROR\n OBTENIENDO VARIABLE\n LONGITUDERROR",
                  "CSELTOTAL","ERROR AL CALCULAR EL TOTAL",
                  FIF(FCONGELAMOV(":CODMOV"),FSUCCESS,FEJECUTA("CMOVPDTESTOCK","\n\n ERROR ACTUALIZANDO \nMOVTO A PDTESTOCK",
                                                                FCOMMIT,"",
                                                                FPOSICIONABLOQUE("VDPICKUNIVDERRCONGELA.PAN"))),"\n\n ERROR\n CONGELANDO MOVIMIENTO\n :CODMOV",
                  "CSELLOTEYCANTIDAD","\n\n ERROR\n OBTENIENDO LOTE Y CANTIDAD",
                  FCOMMIT,"\n\n ERROR\n HACIENDO COMMIT",
				  "+CCARGASTOCK","",
                  "+CSELDECIMALES","",
				  "COCULTACAMPOS","",
				  FPOSICIONACAMPO(FSUCCESS,"UNIDADES"),"\n\n ERROR AL POSICIONAR")

POSTQUERY=FEJECUTA(FIF("CSELUBINULL",FEJECUTA(FCARGAFORM(""),"\n ERROR\n VOLVIENDO AL MENU"),
                                     FSUCCESS),"",
                   "CVERIFICAUBI","\n UBICACION INCORRECTA",
                   FPOSICIONABLOQUE("VDPICKUNIVDART2.PAN"),"\n\n ERROR\n CARGANDO SIGUIENTE\n BLOQUE")


#DEFINICION DE CAMPOS
CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=TEXTOTAREA,VIRTUAL,NOENTER
CAMPO=CODPED,VIRTUAL,NOENTER
CAMPO=NBULTO,VIRTUAL,NOENTER
CAMPO=MATCAJA,VIRTUAL,NOENTER
CAMPO=TOTALUNIDADES,NOENTER
CAMPO=CODART,VIRTUAL,NOENTER
CAMPO=DESART1,VIRTUAL,NOENTER
CAMPO=DESART2,VIRTUAL,NOENTER
CAMPO=NCODLOT,NOENTER
CAMPO=CODLOT,NOENTER
CAMPO=PINTAUBI,VIRTUAL,NOENTER
CAMPO=CODUBIR,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FFUERZASCAN("UBI"),"\n DEBE LEER\n UBICACION")
CAMPO=CANTIDAD,OCULTO,"#L#############",CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=CAJAS,OCULTO,"@@@@@"
CAMPO=ENVASES,OCULTO,"@@@@@"
CAMPO=UNIDADES,OCULTO,"@@@@@"
CAMPO=CODBULTO,VIRTUAL,OCULTO
CAMPO=CODMOV,VIRTUAL,OCULTO
CAMPO=SWTLOTE,VIRTUAL,OCULTO
CAMPO=LONGERROR,OCULTO,"@@@"
CAMPO=SERVIDA,OCULTO,"#L#############"
CAMPO=UNIEMB,OCULTO,"@@@@@"
CAMPO=UNIPAQ,OCULTO,"@@@@"
CAMPO=CODMATORI,OCULTO,"_18_"
CAMPO=SKORIG,OCULTO,"@L@@@@"
CAMPO=ORDENSTK,OCULTO, "@L@@@@@@@"
CAMPO=SEQLINEA,VIRTUAL,OCULTO
CAMPO=CODUBIORI,VIRTUAL,OCULTO


#DEFINICION DE CURSORES
CURSOR=CSELLONGERROR SELECT VD.GETPROP('LONGITUDERROR') LONGERROR,'' CODUBIR FROM DUAL;

CURSOR=CSELTOTAL SELECT SUM(CANTPEDIDA-CANTSERVIDA) TOTALUNIDADES FROM VDBULTOLIN  WHERE CODBULTO IN (SELECT CODBULTO FROM VDBULTOLIN WHERE CODMOV=:CODMOV);

CURSOR=CMOVPDTESTOCK UPDATE VDMOVIM 
                        SET CODRECURSO=NULL, STATUS=VDST.FMOVPDTESTOCK,
                            CODOPEMODIF = :CODOPE, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS
                      WHERE CODMOV=:CODMOV;                    

CURSOR=CSELLOTEYCANTIDAD SELECT CODLOT,CANTIDAD,
                                FLOOR(CANTIDAD/ART.UNIEMB) CAJAS,
                                DECODE(ART.UNIPAQ,0,0,FLOOR(MOD(CANTIDAD,ART.UNIEMB)/ART.UNIPAQ)) ENVASES,
								DECODE(ART.UNIPAQ,0,MOD(CANTIDAD,ART.UNIEMB),MOD(MOD(CANTIDAD,ART.UNIEMB),ART.UNIPAQ)) UNIDADES,
                                ART.UNIEMB,ART.UNIPAQ,MOV.CODMATORI
                           FROM VDMOVIM MOV,VDARTIC ART 
						  WHERE CODMOV=:CODMOV AND MOV.CODART=ART.CODART;

#CURSOR=CCARGASTOCK SELECT SUM(CANTIDAD) SKORIG,ORDENSTK
#                     FROM VDSTOCK 
#                    WHERE CODMAT=:CODMATORI AND CODART=:CODART AND CODLOT=:CODLOT
#                   GROUP BY ORDENSTK;

CURSOR=CCARGASTOCK SELECT SUM(CANTIDAD) SKORIG
                     FROM VDSTOCK 
                    WHERE CODMAT=:CODMATORI AND CODART=:CODART AND CODLOT=:CODLOT;
					
CURSOR=CSELDECIMALES SELECT ART.DECIMALES CANTIDAD__DECIMALES FROM VDARTIC ART WHERE CODART = :CODART;

CURSOR=COCULTACAMPOS SELECT DECODE(:SWTLOTE, 'S', 0, 1) NCODLOT__INVISIBLE,
                            DECODE(:SWTLOTE, 'S', 0, 1) CODLOT__INVISIBLE,
							'LOTE:' NCODLOT
                       FROM DUAL;

CURSOR=CSELUBINULL SELECT :CODUBIR
                     FROM DUAL
                    WHERE :CODUBIR IS NULL;

CURSOR=CVERIFICAUBI SELECT :CODUBIR FROM DUAL WHERE :CODUBIR=:CODUBIORI;
					