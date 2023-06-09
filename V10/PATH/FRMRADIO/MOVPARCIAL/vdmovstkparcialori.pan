# M�dulo   : VDMOVSTKPARCIALORI.PAN
# Funci�n  : Formulario de movimiento de stock parcial asignado a recurso
#            Pantalla de lectura de contenedor origen.
#
# Creaci�n : 20-05-2008
# Autor    : JMM
###########################################
# Hist�rico de cambios:
#
MOVIMIENTO DE STOCK PARCIAL
_10_______ _10_______
MOVIMIENTO PARCIAL
LECTURA CONTENEDOR ORIGEN

ORIGEN    _12_________
ARTICULO  _40_________________
   _20_________________
   _20_________________

DESTINO   _12_________
MATRICULA ORIGEN:
_18_______________ 
_18_______________
|

PREQUERY=FEJECUTA(FIF("CRESTAURAMOVDEST",FEJECUTA("CSELCANTIDADINTER","",FPOSICIONABLOQUE("VDMOVSTKPARCIALDEST.PAN"),"ERROR AL CARGAR VDMOVSTKPARCIALDEST.PAN")),"ERROR EN CRESTAURAMOVDEST",
                  "CSELCODMOV","\nERROR, OBTENIENDO\n DATO DEL MOVIMIENTO\n :CODMOV",
                  "CCONGELAMOVS","ERROR\n CONGELANDO MOVTOS DE\n UBICACION :CODUBIORI",
                  FCOMMIT,"",
                  FIF("-CSELMOVSAJECUTAR", FPOSICIONABLOQUE("VDMOVPARCIALERRCONGELA.PAN"),FSUCCESS),"\n\nNO HAY \nMOVIMIENTOS\nCONGELADOS")
                  
                  

POSTQUERY=FEJECUTA(FIF("CSELNOTNULL",FEJECUTA(FCARGAFORM(""),"ERROR\n VOLVIENDO AL MENU")),"",
                   "CSELVERIFDATOS","ERROR,\nMATRICULA INCORRECTA\n LEIDO :CODMATORILEIDO\n ESPERADO :CODMATORI",        
                   "CSELCANTIDAD","",
                   FIF("CSELBULTO",FPOSICIONABLOQUE("VDMOVSTKPARCIALBUL.PAN"),
                                   FPOSICIONABLOQUE("VDMOVSTKPARCIALART.PAN")),"ERROR\n AL CARGAR SIGUIENTE\n BLOQUE")

# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODMOV,VIRTUAL,OCULTO
CAMPO=CODUBIORI,NOENTER
CAMPO=CODART,NOENTER
CAMPO=DESART1,NOENTER
CAMPO=DESART2,NOENTER
CAMPO=CODUBIDEST,NOENTER
CAMPO=CODMATORI,NOENTER
CAMPO=CODMATORILEIDO,SCAN,AUTOENTER
CAMPO=BULTO,OCULTO,"_18_"
CAMPO=CODLOT,OCULTO,"_40_"
CAMPO=UNIEMB,OCULTO,"@L@@@@@@@@@@",CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=NCAJAS,OCULTO,"@L@@@@@"
CAMPO=UNIDSUELTAS,OCULTO,"@L@@@@@@",CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=TOTALUNID,OCULTO,"@L@@@@@@@@@",CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=UNIDADESHOST,OCULTO,"_10_"


# DEFINICION DE CURSORES
CURSOR=CRESTAURAMOVDEST SELECT MOV.CODUBIORI,MOV.CODART, MOV.CODMATORI, MOV.CODUBIDEST,MOV.UNIEMB,MOV.CODLOT,MOV.BULTO, 
                               VD.DIVIDEXBUSQUEDA(1,ART.DESART,' ',20,0) DESART1,VD.DIVIDEXBUSQUEDA(2,ART.DESART,' ',20,0) DESART2
                          FROM VDMOVIM MOV , VDARTIC ART
                         WHERE STATUS = VDST.FMOVENUBIINTER AND 
                               CODRECURSO = :CODRECURSO  AND 
                               CODMATORI != CODMATDEST AND
                               MOV.CODART = ART.CODART AND
                               MOV.CODMOV =:CODMOV;
                               
CURSOR=CSELCANTIDADINTER SELECT SUM(MOV.CANTIDAD) TOTALUNID, 
                           FLOOR(SUM(MOV.CANTIDAD)/:UNIEMB) NCAJAS, 
                           MOD(SUM(MOV.CANTIDAD),:UNIEMB) UNIDSUELTAS,
                           ART.UNIDADESHOST, 
                           ART.DECIMALES UNIEMB__DECIMALES, 
                           ART.DECIMALES UNIDSUELTAS__DECIMALES,
                           ART.DECIMALES TOTALUNID__DECIMALES
                      FROM VDMOVIM MOV, VDARTIC ART
                     WHERE MOV.STATUS = VDST.FMOVENUBIINTER AND
                           MOV.CODRECURSO = :CODRECURSO AND
                           MOV.CODMATORI = :CODMATORI AND
                           MOV.CODUBIORI = :CODUBIORI AND
                           MOV.CODUBIDEST = :CODUBIDEST AND
                           MOV.UNIEMB  = :UNIEMB AND
                           MOV.CODART  = :CODART AND
                           MOV.CODLOT =  :CODLOT AND
                           (MOV.BULTO  =  :BULTO OR :BULTO IS NULL) AND
                           ART.CODART = MOV.CODART
                      GROUP BY ART.UNIDADESHOST,ART.DECIMALES;                              
                               
CURSOR=CSELCODMOV SELECT MOV.CODUBIORI,MOV.CODART, MOV.CODMATORI, MOV.CODUBIDEST,MOV.UNIEMB,MOV.CODLOT,MOV.BULTO, 
                         VD.DIVIDEXBUSQUEDA(1,ART.DESART,' ',20,0) DESART1,VD.DIVIDEXBUSQUEDA(2,ART.DESART,' ',20,0) DESART2
                    FROM VDMOVIM MOV, VDARTIC ART
                   WHERE MOV.CODMOV = :CODMOV  
                     AND MOV.CODMATORI != MOV.CODMATDEST
                     AND ART.CODART = MOV.CODART;

CURSOR=CSELNOTNULL SELECT :CODMATORILEIDO 
                     FROM DUAL 
                    WHERE :CODMATORILEIDO IS NULL;

CURSOR=CMOVPDTESTOCK UPDATE VDMOVIM 
                        SET CODRECURSO=NULL, STATUS=VDST.FMOVPDTESTOCK,
                            CODOPEMODIF = :CODOPE, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS
                      WHERE CODMOV=:CODMOV;

CURSOR=CMOVPRESENTADO UPDATE VDMOVIM 
                        SET STATUS=VDST.FMOVPRESENTADO,
                            CODOPEMODIF = :CODOPE, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS
                      WHERE CODMOV=:CODMOV AND STATUS=VDST.FMOVASIGNADO;                      
                      
CURSOR=CSELVERIFDATOS SELECT :CODMATORILEIDO CODMATORI 
                        FROM DUAL 
                       WHERE :CODMATORILEIDO=:CODMATORI ; 

CURSOR=CSELBULTO SELECT :BULTO FROM DUAL WHERE :BULTO IS NOT NULL ; 




CURSOR=CCONGELAMOVS DECLARE
											CURSOR C1 IS SELECT MOV.* 
											         FROM VDMOVIM MOV
											         WHERE  MOV.STATUS = VDST.FMOVASIGNADO
											            AND MOV.CODRECURSO = :CODRECURSO 											            
											            AND MOV.CODUBIORI  = :CODUBIORI 
											            AND MOV.CODUBIDEST = :CODUBIDEST 
											            AND MOV.CODMATORI  = :CODMATORI 
											            AND MOV.CODART     = :CODART 
											            AND MOV.UNIEMB     = :UNIEMB 
											            AND (NVL(MOV.CODLOT,:CODLOT) = :CODLOT OR :CODLOT IS NULL)
											            AND (NVL(MOV.BULTO,:BULTO) = :BULTO OR :BULTO IS NULL)
                            ORDER BY DECODE(NVL(NUMEROSERIE,'-'),'-',1,0),
                                  DECODE(NVL(BULTO,'-'),'-',1,0),
                                  DECODE(PRECIOUNI,0,1,0),
                                  DECODE(NVL(TIPOEMBA,'-'),'-',1,0),
                                  DECODE(NVL(CODRECEP,'-'),'-',1,0),
                                  DECODE(NVL(MARCASTK,'-'),'-',1,0),
                                  DECODE(NVL(BLOQUEOSORI,'-'),'-',1,0),
                                  DECODE(NVL(CODLOT,'-'),'-',1,0);
                     CONGELADOS NUMBER;                                   
                   BEGIN
									    UPDATE VDMOVIM SET STATUS=VDST.FMOVASIGNADO,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS 
									       WHERE STATUS=VDST.FMOVPRESENTADO AND CODRECURSO=:CODRECURSO;									          
									    CONGELADOS:=0;
									    FOR I IN C1 LOOP									    
									      IF (VDMOV.CONGELA(I.CODMOV)=0) THEN
									        CONGELADOS:=CONGELADOS+1;
									        VDLOG.PONMENSAJE('VDMOCSTKPARCIALORI','CCONGELAMOVS: CONGELADO MOVTO ' || I.CODMOV);
									        UPDATE VDMOVIM SET STATUS=VDST.FMOVPRESENTADO,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS WHERE CODMOV=I.CODMOV;
									      ELSE
                           VDLOG.PONERROR('VDMOCSTKPARCIALORI','CCONGELAMOVS: NO SE PUEDE CONGELAR MOVTO ' || I.CODMOV);
									      END IF;
									    END LOOP;                      
                      
                      IF (CONGELADOS=0) THEN									    
 							          UPDATE VDMOVIM MOV SET STATUS=VDST.FMOVPDTESTOCK,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS 
 							            WHERE MOV.STATUS = VDST.FMOVASIGNADO
											      AND MOV.CODRECURSO = :CODRECURSO 											            
											      AND MOV.CODUBIORI  = :CODUBIORI 
											      AND MOV.CODUBIDEST = :CODUBIDEST 
											      AND MOV.CODMATORI  = :CODMATORI 
											      AND MOV.CODART     = :CODART 
											      AND MOV.UNIEMB     = :UNIEMB;
									    END IF; 
									    
                   END;@       
                   
CURSOR=CSELMOVSAJECUTAR SELECT MOV.CODMOV, MOV.CODLOT,  MOV.BULTO
                          FROM VDMOVIM MOV
                         WHERE MOV.STATUS = VDST.FMOVPRESENTADO
                           AND MOV.CODUBIORI = :CODUBIORI
                           AND MOV.CODRECURSO = :CODRECURSO
                           AND MOV.CODUBIDEST = :CODUBIDEST 
											     AND MOV.CODMATORI  = :CODMATORI 											                           
                           AND MOV.CODART = :CODART
                           AND MOV.UNIEMB = :UNIEMB;                                  

                                                  
CURSOR=CSELCANTIDAD SELECT SUM(MOV.CANTIDAD) TOTALUNID, 
                           FLOOR(SUM(MOV.CANTIDAD)/:UNIEMB) NCAJAS, 
                           MOD(SUM(MOV.CANTIDAD),:UNIEMB) UNIDSUELTAS,
                           ART.UNIDADESHOST, 
                           ART.DECIMALES UNIEMB__DECIMALES, 
                           ART.DECIMALES UNIDSUELTAS__DECIMALES,
                           ART.DECIMALES TOTALUNID__DECIMALES
                      FROM VDMOVIM MOV, VDARTIC ART
                     WHERE MOV.STATUS = VDST.FMOVPRESENTADO AND
                           MOV.CODRECURSO = :CODRECURSO AND
                           MOV.CODMATORI = :CODMATORI AND
                           MOV.CODUBIORI = :CODUBIORI AND
                           MOV.CODUBIDEST = :CODUBIDEST AND
                           MOV.UNIEMB  = :UNIEMB AND
                           MOV.CODART  = :CODART AND
                           MOV.CODLOT =  :CODLOT AND
                           (MOV.BULTO  =  :BULTO OR :BULTO IS NULL) AND
                           ART.CODART = MOV.CODART
                      GROUP BY ART.UNIDADESHOST,ART.DECIMALES;