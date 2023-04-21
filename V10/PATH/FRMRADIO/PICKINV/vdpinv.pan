# M�dulo   : VDPINV.PAN
# Funci�n  : Se encarga de crear los bultos de picking inverso para los movtos asignados, del contenedor
#           y se pasa a seleccionar los bultos que se van recogiendo. Sin cubeta, puede recoger varios bultos
#           de caja completa de golpe, si se etiqueta en una etiq. autom�tica
#
# Creaci�n : 11-06-2009
# Autor    : FGS
###########################################
# Hist�rico de cambios:
# 
RECOGIDA PICKING INVERSO A CUBETA
_10_______ _10_______
PICKING INVERSO A CUBETA

ERROR

MOVTOS DE PICKING
INVERSO ERRONEOS

|
PREQUERY=FEJECUTA(
#                 VER SI HAY MOVIMIENTOS DE PINV PENDIENTES DE EJECUTAR PERO YA SE HAN DIVIDIDO EN BULTOS DE PREPICKING
                  FIF("CMOVTOPDTESCAJA",FPOSICIONABLOQUE("VDPINVCAJAART.PAN"),FSUCCESS),"",
				  FIF("CMOVTOPDTESPICO",FPOSICIONABLOQUE("VDPINVPICOART.PAN"),FSUCCESS),"",
#                 SI NO HAY MOVIMIENTOS PENDIENTES DE EJECUTAR, VEMOS SI HAY MOVIMIENTOS PENDIENTE DE ASIGNAR Y CREAR BULTOS
				  FIF("-CMOVTOPDTESDIV",FPOSICIONABLOQUE("VDPINVCAJANOMOV.PAN"),FSUCCESS),"",
                  "CCREAMOVPINV","ERROR - :RET",
                  FCOMMIT,"",				  
#                 UNA VEZ DIVIDIDO Y ASOCIADO NUEVOS MOVIMIENTOS A PREPICKING Y P.INV, VOLVEMOS A EVALUAR SI TENEMOS CAJAS COMPLETAS Y PICOS
				  FIF("CMOVTOPDTESCAJA",FPOSICIONABLOQUE("VDPINVCAJAART.PAN"),FSUCCESS),"",
				  FIF("CMOVTOPDTESPICO",FPOSICIONABLOQUE("VDPINVPICOART.PAN"),FSUCCESS),""
                  )
           

POSTQUERY=FEJECUTA(FCARGAFORM(""),"ERROR\n AL VOLVER AL MENU")
          
# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODUBI,OCULTO,"_12_____"
CAMPO=CODMAT,OCULTO,"_20______"
CAMPO=CODART,OCULTO,"_40_______"
CAMPO=CODLOT,OCULTO,"_40_______"
CAMPO=DESART1,OCULTO,"_40_______"
CAMPO=DESART2,OCULTO,"_40_______"
CAMPO=UNIEMB,OCULTO,"@L@@@@@@@",CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=CODUBIDEST,OCULTO,"_12______"
CAMPO=CAJACOMPLETA,OCULTO,"_"
CAMPO=CODBULTO,OCULTO,"_20__________"
CAMPO=CODMOV,OCULTO,"@@@@@@@@@"
CAMPO=RET,OCULTO,"_100_"

CURSOR=CCAJACOMPLETA SELECT :CAJACOMPLETA FROM DUAL WHERE :CAJACOMPLETA='S';

CURSOR=CMOVTOPDTESCAJA  SELECT MOV.CODMOV, MOV.CODUBIORI CODUBI, MOV.CODMATORI CODMAT, MOV.CODLOT, 
                           MOV.CODART, MOV.UNIEMB,MOV.CODUBIDEST CODUBIDEST,
                           VD.DIVIDEXBUSQUEDA (1, ART.DESART, ' ', 20, 0) DESART1,
                           VD.DIVIDEXBUSQUEDA (2, ART.DESART, ' ', 20, 0) DESART2                           
                      FROM VDMOVIM MOV, VDARTIC ART, VDUBICA UBI
                      WHERE MOV.STATUS IN (VDST.FMOVASIGNADO, VDST.FMOVPRESENTADO)
                            AND MOV.CODRECURSO||'' = :CODRECURSO
                            AND MOV.TAREA = VD.GETPROP('TIPOTAREAPINV')
                            AND ART.CODART = MOV.CODART
                            AND MOV.CODUBIORI = UBI.CODUBI
                            AND MOV.CODUBIORI <> 'PI'							
                            AND MOV.CODUBIDEST = 'PI'
							AND MOV.CANTIDAD = MOV.UNIEMB
							AND ROWNUM =1
                      ORDER BY DECODE (MOV.STATUS, VDST.FMOVPRESENTADO, 0, 1), UBI.ORDENMOVIM, MOV.PRIOMOV, MOV.CODMOV;
					  
CURSOR=CMOVTOPDTESPICO  SELECT MOV.CODMOV, MOV.CODUBIORI CODUBI, MOV.CODMATORI CODMAT, MOV.CODLOT, 
                           MOV.CODART, MOV.UNIEMB,MOV.CODUBIDEST CODUBIDEST,
                           VD.DIVIDEXBUSQUEDA (1, ART.DESART, ' ', 20, 0) DESART1,
                           VD.DIVIDEXBUSQUEDA (2, ART.DESART, ' ', 20, 0) DESART2                           
                      FROM VDMOVIM MOV, VDARTIC ART, VDUBICA UBI
                      WHERE MOV.STATUS IN (VDST.FMOVASIGNADO, VDST.FMOVPRESENTADO)
                            AND MOV.CODRECURSO||'' = :CODRECURSO
                            AND MOV.TAREA = VD.GETPROP('TIPOTAREAPINV')
                            AND ART.CODART = MOV.CODART
                            AND MOV.CODUBIORI = UBI.CODUBI
                            AND MOV.CODUBIORI <> 'PI'							
                            AND MOV.CODUBIDEST = 'PI'
							AND MOV.CANTIDAD < MOV.UNIEMB
							AND ROWNUM =1
                      ORDER BY DECODE (MOV.STATUS, VDST.FMOVPRESENTADO, 0, 1), UBI.ORDENMOVIM, MOV.PRIOMOV, MOV.CODMOV;					  

CURSOR=CMOVTOPDTESDIV  SELECT MOV.CODMOV, MOV.CODUBIORI CODUBI, MOV.CODMATORI CODMAT, MOV.CODLOT, 
                           MOV.CODART, MOV.UNIEMB,MOV.CODUBIDEST CODUBIDEST,
                           VD.DIVIDEXBUSQUEDA (1, ART.DESART, ' ', 20, 0) DESART1,
                           VD.DIVIDEXBUSQUEDA (2, ART.DESART, ' ', 20, 0) DESART2                           
                      FROM VDMOVIM MOV, VDARTIC ART, VDUBICA UBI
                      WHERE MOV.STATUS IN (VDST.FMOVASIGNADO, VDST.FMOVPRESENTADO)
                            AND MOV.CODRECURSO||'' = :CODRECURSO
                            AND MOV.TAREA = VD.GETPROP('TIPOTAREAPINV')
                            AND ART.CODART = MOV.CODART
                            AND MOV.CODUBIORI = UBI.CODUBI
							AND MOV.CODUBIORI <> 'PI'
                            AND MOV.CODUBIDEST <> 'PI'
							AND ROWNUM =1
                      ORDER BY DECODE (MOV.STATUS, VDST.FMOVPRESENTADO, 0, 1), UBI.ORDENMOVIM, MOV.PRIOMOV, MOV.CODMOV;
                      
CURSOR=CCREAMOVPINV BEGIN
                        :RET := VDPICKINV.MOVIMIENTOSPINV(:CODMOV);						   
						IF :RET IS NOT NULL THEN RAISE NO_DATA_FOUND; END IF;						
                      END;@
