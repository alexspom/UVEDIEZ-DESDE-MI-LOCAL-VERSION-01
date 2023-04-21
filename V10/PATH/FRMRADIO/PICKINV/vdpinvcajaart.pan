# Módulo   : VDPINVCAJAART.PAN
# Función  : Formulario de recogida de caja completa para depositar en la cinta del Picking Inverso.
#
# Creación : 19-09-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
# 
CAJAS COMPLETAS PARA PICKING INVERSO
_10_______ _10_______
CAJAS PARA PICKING INVERSO
U.ORIGEN :_12_________
CONTENEDOR: _18______________
  
ARTICULO _20_________________
  _20_________________
  _20_________________
LOTE:  _20_________________  
LECTURA DE ARTICULO 
_200_____________________________________________________________________________________
  
CAJAS A COGER #L#####
DE (U/E): #15L#######
|


PREQUERY=FEJECUTA("CSELLIMPIA","ERROR LIMPIANDO PANTALLA",
                  "CSELLONGERROR","ERROR\n OBTENIENDO PROPIEDAD\n LONGERROR",   
                  "+CSELDECIMALES","",
                  "CUPDMOVS","ERROR\n ACTUALIZANDO MOVTOS A PRESENTADO",
                  "CIMPETIQ","ERROR AL IMPRIMIR MATRICULAS ",
				  "CUPDBULTOS","ERROR\n ACTUALIZANDO BULTOS",
                  "CCUENTACAJAS","ERROR\n CONTANDO BULTOS A RECOGER"
				  )

POSTQUERY=FEJECUTA(FIF("CSELNULL",FCARGAFORM(""),FSUCCESS),"ERROR\n AL VOLVER AL MENU",                  
                   "CVERIFDAT","ERROR\n DATOS LEIDOS\n INCORRECTOS",
                   "CEJEMOV","ERROR EJECUTANDO MOVIMIENTO",
				   FCOMMIT,"",
				   FPOSICIONABLOQUE("VDPINV.PAN"))                                                                        
          
# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODUBI,VIRTUAL,NOENTER
CAMPO=CODUBIDEST,VIRTUAL,OCULTO
CAMPO=CODMAT,VIRTUAL,NOENTER
CAMPO=CODART,VIRTUAL,NOENTER
CAMPO=DESART1,VIRTUAL,NOENTER
CAMPO=DESART2,VIRTUAL,NOENTER
CAMPO=CODLOT,VIRTUAL,NOENTER
CAMPO=CODBARRAS,SCAN,POSTCHANGE=FEJECUTA("CVALLEIDO","ERROR\n OBTENIENDO ARTICULO Y LOTE") 
CAMPO=CAJAS,NOENTER
CAMPO=CAJAACTUAL,OCULTO,"@L@@@@"
CAMPO=CAJASSINMATRICULA,OCULTO,"@L@@@@"
CAMPO=UNIEMB,VIRTUAL,NOENTER,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")

CAMPO=UNIEMBSCAN,OCULTO,"#L#############",CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=CODARTLEIDO,OCULTO,"_40_"
CAMPO=CODLOTLEIDO,OCULTO,"_40_"
CAMPO=CODEANLEIDO,OCULTO,"_20_"
CAMPO=MSGERROR,OCULTO,"_2048_"
CAMPO=LONGERROR,OCULTO,"@@@"
CAMPO=CODMOV,OCULTO,"@L@@@@@@@"
CAMPO=ETIQUETADOENCINTA,OCULTO,"_"

# DEFINICION DE CURSORES
CURSOR=CSELLIMPIA SELECT ' ' CODBARRAS, 'S' ETIQUETADOENCINTA,0 CAJASSINMATRICULA,0 CAJAACTUAL  FROM DUAL;

CURSOR=CSELLONGERROR SELECT VD.GETPROP('LONGITUDERROR') LONGERROR FROM DUAL;

CURSOR=CSELDECIMALES SELECT ART.DECIMALES UNIEMB__DECIMALES FROM VDARTIC ART WHERE CODART = :CODART;

CURSOR=CUPDMOVS UPDATE VDMOVIM SET CODRECURSO=:CODRECURSO,STATUS=VDST.FMOVPRESENTADO, CODOPEMODIF = VDUSER.GETUSER, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS 
                   WHERE CODMOV IN ( SELECT MOV.CODMOV                                        
                                       FROM  VDMOVIM MOV
                                       WHERE MOV.TAREA = VD.GETPROP('TIPOTAREAPINV')                                                                                          
                                         AND MOV.STATUS BETWEEN VDST.FMOVASIGNADO AND VDST.FMOVPRESENTADO
                                         AND MOV.CODRECURSO = :CODRECURSO
                                         AND MOV.CODUBIORI   = :CODUBI
                                         AND MOV.CODUBIDEST||''  = 'PI'
                                         AND MOV.CODMATORI ||''  = :CODMAT
                                         AND MOV.CODART    ||''  = :CODART
                                         AND MOV.UNIEMB+0        = :UNIEMB
										 AND MOV.UNIEMB+0        = MOV.CANTIDAD
                                         AND NVL(MOV.CODLOT,'-') = NVL(:CODLOT,'-'));	
                                              
CURSOR=CUPDBULTOS UPDATE VDBULTOCABPINV BPC
                    SET STATUS=VDST.FBPCPRESENTADO, CODOPEMODIF = VDUSER.GETUSER, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS 
                    WHERE BPC.STATUS = VDST.FBPCCREADO                                              
                        AND BPC.CODMAT IN (SELECT CODMATORI
                                              FROM  VDMOVIM MOV
                                              WHERE MOV.TAREA = VD.GETPROP('TIPOTAREAPINV')                                              
                                                AND MOV.STATUS     BETWEEN VDST.FMOVASIGNADO AND VDST.FMOVPRESENTADO
                                                AND MOV.CODRECURSO  = :CODRECURSO
                                                AND MOV.CODUBIORI   = :CODUBI
                                                AND MOV.CODUBIDEST||''  = 'PI'
                                                AND MOV.CODMATORI ||''  = :CODMAT
                                                AND MOV.CODART    ||''  = :CODART
                                                AND MOV.UNIEMB+0        = :UNIEMB
                                                AND NVL(MOV.CODLOT,'-') = NVL(:CODLOT,'-'))
				        AND BPC.CAJACOMPLETA='S';	
                                              
CURSOR=CCUENTACAJAS SELECT FLOOR(SUM(CANTIDAD)/UNIEMB) CAJAS
                     FROM  VDMOVIM MOV
                     WHERE MOV.TAREA           = VD.GETPROP('TIPOTAREAPINV')                                              
                       AND MOV.STATUS         BETWEEN VDST.FMOVASIGNADO AND VDST.FMOVPRESENTADO 
                       AND MOV.CODRECURSO  = :CODRECURSO
                       AND MOV.CODUBIORI   = :CODUBI
                       AND MOV.CODUBIDEST||''  = 'PI'
                       AND MOV.CODMATORI ||''  = :CODMAT
                       AND MOV.CODART    ||''  = :CODART
                       AND MOV.UNIEMB+0        = :UNIEMB
                       AND NVL(MOV.CODLOT,'-') = NVL(:CODLOT,'-') 
					   GROUP BY UNIEMB;
												
												
CURSOR=CSELNULL SELECT :CODBARRAS
                     FROM DUAL 
                    WHERE :CODBARRAS IS NULL; 

CURSOR=CVERIFDAT SELECT :CODBARRAS
                   FROM DUAL
                  WHERE :CODARTLEIDO = :CODART  
                    AND NVL(:CODLOTLEIDO,'-') = NVL(:CODLOT,'-');

CURSOR=CIMPETIQ DECLARE
                  CURSOR C1 IS
				  SELECT BPC.*
				  FROM VDBULTOCABPINV BPC
				  WHERE BPC.CODMAT IN (SELECT CODMATORI
                                              FROM  VDMOVIM MOV
                                              WHERE MOV.TAREA = VD.GETPROP('TIPOTAREAPINV')                                              
                                                AND MOV.STATUS     BETWEEN VDST.FMOVASIGNADO AND VDST.FMOVPRESENTADO
                                                AND MOV.CODRECURSO  = :CODRECURSO
                                                AND MOV.CODUBIORI   = :CODUBI
                                                AND MOV.CODUBIDEST||''  = 'PI'
                                                AND MOV.CODMATORI ||''  = :CODMAT
                                                AND MOV.CODART    ||''  = :CODART
                                                AND MOV.UNIEMB+0        = :UNIEMB
                                                AND MOV.UNIEMB+0	    = MOV.CANTIDAD											
                                                AND NVL(MOV.CODLOT,'-') = NVL(:CODLOT,'-'))
					    AND BPC.CAJACOMPLETA        = 'S';
				BEGIN
				  FOR I IN C1 LOOP
                    VDIMPRIME.IMPRIME('ETIQ','VDBULTOINV.GEN;VDETIQUETAS.VSQ;CBULTOPINV','CODBULTO='||I.CODBULTO,1,'','',:V10ERROR);
					COMMIT;
					END LOOP;
				  END;@

CURSOR=CVALLEIDO SELECT CASE
                           WHEN VDEAN.VALOR(:CODBARRAS,'240') IS NOT NULL THEN VDEAN.VALOR(:CODBARRAS,'240') 
                           WHEN VDART.DAMEART(:CODBARRAS) IS NOT NULL THEN VDART.DAMEART(:CODBARRAS)
						   ELSE :CODBARRAS
                           END CODARTLEIDO,
                        VDEAN.VALOR(:CODBARRAS,'01')  CODEANLEIDO,
                        VDEAN.VALOR(:CODBARRAS,'10')  CODLOTLEIDO
                    FROM DUAL;						

CURSOR=CEJEMOV DECLARE
                  RET NUMBER;				  
                  CURSOR C1 IS
				     SELECT MOV.*
                       FROM  VDMOVIM MOV
                       WHERE MOV.TAREA = VD.GETPROP('TIPOTAREAPINV')                                              
                         AND MOV.STATUS     BETWEEN VDST.FMOVASIGNADO AND VDST.FMOVPRESENTADO
                         AND MOV.CODRECURSO  = :CODRECURSO
                         AND MOV.CODUBIORI  = :CODUBI
                         AND MOV.CODUBIDEST||''  = 'PI'
                         AND MOV.CODMATORI ||''  = :CODMAT
                         AND MOV.CODART    ||''  = :CODART
                         AND MOV.UNIEMB+0        = :UNIEMB
                         AND MOV.UNIEMB+0	    = MOV.CANTIDAD											
                         AND NVL(MOV.CODLOT,'-') = NVL(:CODLOT,'-');
                BEGIN
				  FOR I IN C1 LOOP
				      RET:=VDACTSTOCK.EJECUTAMOV(I.CODMOV, :V10ERROR);
					  IF RET <> 0 THEN 
					    RAISE NO_DATA_FOUND;
						END IF;
				    END LOOP;
                 END;@ 