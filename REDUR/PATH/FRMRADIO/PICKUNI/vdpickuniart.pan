# M�dulo   : VDPICKUNIART.PAN
# Funci�n  : Formulario de recogida de bultos de unidades.
#            Pantalla de lectura de articulo.
#
# Creaci�n : 13-05-2008
# Autor    : JMM
###########################################
# Hist�rico de cambios:
#
PICKING POR TERMINAL
_10_______ _10_______
BULTO @L@@ PED: _20___________
UBICACION : _12_________
MATRICULA : _20_________________
            _20_________________  
ARTICULO: _20___________________
_________________________________________
_________________________________________
LOTE: _20_________________

[41;37mCANTIDAD : #L#############[40;37m


LEA ARTICULO Y LOTE
_255_________________________________________________________________________________
|

PREQUERY=FEJECUTA("CLIMPIA","ERROR\n LIMPIANDO CAMPOS",
                  "CSELLONGERROR","ERROR\n OBTENIENDO VARIABLE\n LONGITUDERROR",
                  FIF(FCONGELAMOV(":CODMOV"),FSUCCESS,FEJECUTA("CMOVPDTESTOCK","ERROR ACTUALIZANDO MOVTO A PDTESTOCK",
                                                                FCOMMIT,"",
                                                                FPOSICIONABLOQUE("VDPICKUNIERRCONGELA.PAN"))),"ERROR\n CONGELANDO MOVIMIENTO\n :CODMOV",
                  "CSELLOTEYCANTIDAD","ERROR\n OBTENIENDO LOTE Y CANTIDAD",
                  FCOMMIT,"ERROR\n HACIENDO COMMIT",   
                  "+CSELDECIMALES","",
                  FPOSICIONACAMPO(FSUCCESS,"CODMATLEIDA"),"")

POSTQUERY=FEJECUTA(FIF("CSELNULL",FPOSICIONABLOQUE("VDPICKUNIANUL.PAN"),FSUCCESS),"ERROR\n CARGANDO BLOQUE\nVDPICKUNIANUL.PAN",
                   "CVERIFART","ERROR\n ARTICULO INCORRECTO",
                   "CVERIFLOTE","ERROR\n LOTE INCORRECTO",
                   FPOSICIONABLOQUE("VDPICKUNIOK.PAN"),"ERROR\n CARGANDO BLOQUE\nVDPICKUNIOK.PAN")

#DEFINICION DE CAMPOS
CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=NBULTO,VIRTUAL,NOENTER
CAMPO=CODPED,VIRTUAL,NOENTER
CAMPO=CODUBI,VIRTUAL,NOENTER
CAMPO=CODMAT,VIRTUAL,NOENTER
CAMPO=CODMATLEIDA,SCAN,POSTCHANGE=FEJECUTA("CVERIFMAT","MATRICULA INCORRECTA")
CAMPO=CODART,VIRTUAL,NOENTER
CAMPO=DESART1,VIRTUAL,NOENTER
CAMPO=DESART2,VIRTUAL,NOENTER
CAMPO=CODLOT,NOENTER
CAMPO=CANTIDAD,NOENTER,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=CODBULTO,VIRTUAL,NOENTER,OCULTO
CAMPO=CODBARRAS,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FLEEARTICULO("CODBARRAS","CODARTIN",":CODART","CODLOTIN"),"ERROR\n OBTENIENDO ARTICULO Y LOTE")

CAMPO=CODMOV,VIRTUAL,OCULTO
CAMPO=MSGERROR,OCULTO,"_512_"
CAMPO=LONGERROR,OCULTO,"@@@"
CAMPO=CODARTIN,OCULTO,"_20_",POSTCHANGE=FEJECUTA(FFUERZASCAN("ART"),"\nERROR\n DEBE SCANNEAR\n EL ARTICULO")
CAMPO=CODLOTIN,OCULTO,"_20_"

#DEFINICION DE CURSORES
CURSOR=CLIMPIA SELECT NULL CODBARRAS, NULL CODARTIN, NULL CODLOTIN,NULL CODMATLEIDA FROM DUAL;

CURSOR=CSELLONGERROR SELECT VD.GETPROP('LONGITUDERROR') LONGERROR FROM DUAL;

CURSOR=CVERIFMAT SELECT :CODMAT FROM DUAL WHERE :CODMAT=:CODMATLEIDA;

CURSOR=CSELDECIMALES SELECT ART.DECIMALES CANTIDAD__DECIMALES FROM VDARTIC ART WHERE CODART = :CODART;

CURSOR=CSELNULL SELECT :CODBARRAS FROM DUAL WHERE :CODBARRAS IS NULL;


CURSOR=CSELLOTEYCANTIDAD SELECT CODLOT,CANTIDAD FROM VDMOVIM WHERE CODMOV=:CODMOV;

CURSOR=CVERIFART SELECT :CODARTIN
                   FROM DUAL
                  WHERE :CODARTIN = :CODART;

CURSOR=CVERIFLOTE SELECT :CODLOTIN
                    FROM DUAL
                   WHERE :CODLOTIN = :CODLOT;

CURSOR=CDIVIDEERROR BEGIN :MSGERROR:=VD.DIVERRORRADIO(:V10ERROR,:LONGERROR);
                    END;@
                    
CURSOR=CMOVPDTESTOCK UPDATE VDMOVIM 
                        SET CODRECURSO=NULL, STATUS=VDST.FMOVPDTESTOCK,
                            CODOPEMODIF = :CODOPE, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS
                      WHERE CODMOV=:CODMOV;                    
