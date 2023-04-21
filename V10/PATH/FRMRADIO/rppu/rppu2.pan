# Módulo   : RPPU2.PAN
# Función  : Pantalla de lectura de ubicación origen.
#
# Creación : 24-09-2014
# Autor    : FPD
###########################################
# Histórico de cambios:
#
PICKING TOUR (ORIGEN)
_10_______ _10_______
PICKING TOUR (ORIGEN)

PALET: __________________

UBI: _20_________________
_20______________________
_40__________________________
_20______________________


MATRICULA: _20_________________
ARTICULO : _255__________________________________________

_100__________________________

|


PREQUERY=FEJECUTA("CSELLIMPIA","\n NO PUEDO LIMPIAR CAMPOS",
                  "CSELCODMOV","\n ERROR OBTENIENDO\n DATOS DEL MOVIMIENTO\n :CODMOV",
                  "CCONGELAMOVS","\n ERROR CONGELANDO \n MOVIMIENTOS DE\n UBICACION :CODUBIORI",
                  FPOSICIONACAMPO(FSUCCESS,"CODMATORILEIDO"),"",
                  FCOMMIT,"",
                  FIF("-CSELMOVSAJECUTAR",FPOSICIONABLOQUE("VDMOVPARCIALERRCONGELA.PAN"),FSUCCESS),"\n NO HAY \n MOVIMIENTOS\n PENDIENTES")
                  
POSTQUERY=FEJECUTA(FIF("CSELNULL",FEJECUTA("CDESASIGNAMOV","\n ERROR\n QUITANDO MOVIMIENTO",
                                           +FCOMMIT,"",
										   +FCARGAFORM(""),""),
							      FSUCCESS),"",
                   "CVERIFICACNT","\n MATRICULA INCORRECTA", 
                   "CVERERROR",":V10ERROR",                                    
                   "CVERIFICAART","\n ARTICULO INCORRECTO", 
                   "CVERERROR",":V10ERROR",
                   "CVERIFICALOT","\n LOTE INCORRECTO", 
                   "CVERERROR",":V10ERROR",
                   "+CSELCANTIDAD","",
                   "+CULTCAJA","",
                   FPOSICIONABLOQUE("RPPU3.PAN"),"")

                    
# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODMAT,VIRTUAL,NOENTER
CAMPO=CODMOV,VIRTUAL,OCULTO
CAMPO=PINTAUBI,NOENTER
CAMPO=CODART,NOENTER
CAMPO=DESART1,NOENTER
CAMPO=CODLOT,NOENTER
CAMPO=CODART1,NOENTER,OCULTO,"_20___________"
CAMPO=CODLOT1,NOENTER,OCULTO,"_20___________"
CAMPO=CODUBIORI,OCULTO,"_12_"
CAMPO=CODUBIDEST,OCULTO,"_12_"
CAMPO=CODMATORI,OCULTO,"_18_"

#CAMPO=CODUBIORILEIDO,SCAN,POSTCHANGE=FEJECUTA(FFUERZASCAN("UBI"),"\n ERROR\n DEBE LEER\n LA UBICACION")

CAMPO=CODMATORILEIDO,SCAN,POSTCHANGE=FEJECUTA(FFUERZASCAN("CNT"),"\n ERROR\n DEBE LEER\n LA MATRICULA")
CAMPO=SCANART,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FFUERZASCAN("ART"),"\n DEBE LEER\n  ARTICULO",
                                                 +FLEEARTICULO("SCANART","CODART1","","CODLOT1")," ERROR \n NO ENCUENTRO \n ARTICULO",                                                 
												 FIF("-CSELCODARTNULL", FEJECUTA("CSELLOTE1","",
																				 "CSELUNIEMB1")),"")
CAMPO=OBSERV,NOENTER
CAMPO=BULTO,OCULTO,"_18_"
CAMPO=UNIEMB,OCULTO,"@L@@@@@@@@@@",CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=NCAJAS,OCULTO,"@L@@@@@"
CAMPO=UNIDSUELTAS,OCULTO,"@L@@@@@@",CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=TOTALUNID,OCULTO,"@L@@@@@@@@@",CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=UNIDADESHOST,OCULTO,"_10_"
CAMPO=ULTCAJA,OCULTO,"_"
CAMPO=CODCOMEN,OCULTO,"@L@@@@@@@@"
CAMPO=CERO,OCULTO,"_"
CAMPO=CODPERFIL,VIRTUAL,OCULTO
CAMPO=CADUCI,OCULTO,"_8_"
CAMPO=UNIEMB1,OCULTO,"#L############"
CAMPO=FORMATO,OCULTO,"____"
CAMPO=FORMATOPRE,OCULTO,"_______"
CAMPO=CODPREPARACION,OCULTO,"@@@@@@@@@"


# DEFINICION DE CURSORES
CURSOR=CSELLIMPIA SELECT '' CODMATORILEIDO, '' ULTCAJA, 'N' CERO, '' SCANART,
                         '' CODART1, '' CODLOT1, '' CADUCI, 0 UNIEMB1, '' FORMATO, '' FORMATOPRE
			        FROM DUAL;
                                                                                          
CURSOR=CSELCODMOV SELECT MOV.CODUBIORI, MOV.CODART, MOV.CODMATORI, MOV.CODUBIDEST, MOV.UNIEMB, MOV.CODLOT, MOV.BULTO, 
                         SUBSTR(ART.DESART,1,31) DESART1,
                         VDCLIPKG.PINTAUBICA(MOV.CODUBIORI) PINTAUBI,VDCOM.DAMECOMEN(MOV.CODCOMEN,'ANOTACION',1) OBSERV,
						 MOV.CODPREPARACION
                    FROM VDMOVIM MOV, VDARTIC ART
                   WHERE MOV.CODMOV = :CODMOV  
                     AND MOV.CODMATORI != MOV.CODMATDEST
                     AND ART.CODART = MOV.CODART;

CURSOR=CCONGELAMOV DECLARE
                     CONGELADOS NUMBER;                                   
                   BEGIN
                     CONGELADOS:=0;
                     IF (VDMOV.CONGELA(:CODMOV)=0) THEN
                        CONGELADOS:=CONGELADOS+1;
                        VDLOG.PONMENSAJE('RPPU2','CCONGELAMOV: CONGELADO MOVIMIENTO '||:CODMOV);
                        UPDATE VDMOVIM SET STATUS=VDST.FMOVPRESENTADO,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS WHERE CODMOV=:CODMOV;
                     ELSE
                        VDLOG.PONERROR('RPPU2','CCONGELAMOV: NO SE PUEDE CONGELAR MOVTO '||:CODMOV);
                     END IF;
                     IF (CONGELADOS=0) THEN
                         UPDATE VDMOVIM SET STATUS=VDST.FMOVPDTESTOCK,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS 
                         WHERE CODMOV=:CODMOV;
                     END IF; 
                   END;@  

CURSOR=CCONGELAMOVS DECLARE
                      CURSOR C1 IS SELECT MOV.* 
                                     FROM VDMOVIM MOV
                                    WHERE MOV.STATUS = VDST.FMOVASIGNADO
                                      AND MOV.CODRECURSO = :CODRECURSO      
                                      AND MOV.CODUBIORI  = :CODUBIORI 
                                      AND MOV.CODUBIDEST = :CODUBIDEST 
                                      AND MOV.CODMATORI  = :CODMATORI 
                                      AND MOV.CODART     = :CODART 
                                      AND MOV.CODPREPARACION = :CODPREPARACION
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
                         VDLOG.PONMENSAJE('RPPU2','CCONGELAMOVS: CONGELADO MOVTO ' || I.CODMOV);
                         UPDATE VDMOVIM SET STATUS=VDST.FMOVPRESENTADO,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS WHERE CODMOV=I.CODMOV;
                       ELSE
                         VDLOG.PONERROR('RPPU2','CCONGELAMOVS: NO SE PUEDE CONGELAR MOVTO ' || I.CODMOV);
                         UPDATE VDMOVIM SET STATUS=VDST.FMOVPDTESTOCK,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS WHERE CODMOV=I.CODMOV; 
                       END IF;
                     END LOOP;                      
                     UPDATE VDMOVIM SET STATUS=VDST.FMOVPDTESTOCK,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS 
                      WHERE STATUS=VDST.FMOVASIGNADO 
                        AND CODRECURSO = :CODRECURSO                                                        
                        AND CODUBIORI  = :CODUBIORI 
                        AND CODUBIDEST = :CODUBIDEST 
                        AND CODMATORI  = :CODMATORI 
                        AND CODART     = :CODART 
                        AND CODPREPARACION = :CODPREPARACION;                    
                   END;@       

				   
CURSOR=CSELMOVSAJECUTAR SELECT MOV.CODMOV, MOV.CODLOT,  MOV.BULTO
                          FROM VDMOVIM MOV
                         WHERE MOV.STATUS = VDST.FMOVPRESENTADO
                           AND MOV.CODUBIORI = :CODUBIORI
                           AND MOV.CODRECURSO = :CODRECURSO
                           AND MOV.CODUBIDEST = :CODUBIDEST 
                           AND MOV.CODMATORI  = :CODMATORI
                           AND MOV.CODART = :CODART;                                  
				 
CURSOR=CANALIZAEAN SELECT VDEAN.VALOR(:SCANART,240) CODART1, 
						  VDEAN.VALOR(:SCANART,10) CODLOT1,
						  VDEAN.VALOR(:SCANART,17) CADUCI,
                          VDEAN.VALOR(:SCANART,37) UNIEMB1
                     FROM DUAL;

CURSOR=CANALIZAFUTEAN SELECT VDPINTA.FUTEAN(:SCANART,240) CODART1, 
					   	     VDPINTA.FUTEAN(:SCANART,10) CODLOT1,
						     VDPINTA.FUTEAN(:SCANART,17) CADUCI,
                             VDPINTA.FUTEAN(:SCANART,37) UNIEMB1
                        FROM DUAL;				

CURSOR=CSELCODARTNULL SELECT :CODART CODART FROM DUAL WHERE :CODART1 IS NULL;						

CURSOR=CDAMEFORMATO SELECT VDPINTA.DAMEFORMATO(:SCANART) FORMATOPRE
                      FROM DUAL;

CURSOR=CSELFORMATODEFINIT SELECT DECODE(:FORMATOPRE, 'CO', 'CO',
                                                     'DE1', 'DE1',
												     'DE2', 'DE2',
                                                     'IB') FORMATO FROM DUAL;				   

CURSOR=CSELLOTE1 SELECT DECODE(AR.SWTLOTE, 'S', :CODLOT1, :CODLOT)  CODLOT1
                  FROM VDARTIC AR
                 WHERE AR.CODART=:CODART1;		

CURSOR=CSELUNIEMB1 SELECT DECODE(:UNIEMB1, 0, :UNIEMB) UNIEMB1 FROM DUAL;
                     
CURSOR=CDESASIGNAMOV DECLARE RET NUMBER; BEGIN RET:=VDPLANMOV.DESASIGNAMOVMAT(:CODRECURSO,1,:CODMATORI); END;@

CURSOR=CSELNULL SELECT :CODMATORILEIDO 
                  FROM DUAL 
                 WHERE :CODMATORILEIDO IS NULL;

CURSOR=CVERIFICACNT BEGIN
                        IF :CODMATORI!=:CODMATORILEIDO OR :CODMATORILEIDO IS NULL THEN 
                            :V10ERROR:='\n ERROR,\n MATRICULA INCORRECTA\n LEIDA '||:CODMATORILEIDO||'\n ESPERADA '||:CODMATORI;
                        ELSE
                            :V10ERROR:='';
                        END IF;
                    END;@
					
CURSOR=CVERIFICAART BEGIN
                        IF :CODART1 IS NULL OR :CODART1!=:CODART THEN 
                            :V10ERROR:='\n ERROR,\n ARTICULO INCORRECTO\n LEIDO '||:CODART1||'\n ESPERADO '||:CODART;
                        ELSE
                            :V10ERROR:='';
                        END IF;
                    END;@
					
CURSOR=CVERIFICALOT BEGIN
                        IF :CODLOT1 IS NULL OR :CODLOT1!=:CODLOT THEN 
                            :V10ERROR:='\n ERROR,\n LOTE INCORRECTO\n LEIDO '||:CODLOT1||'\n ESPERADO '||:CODLOT;
                        ELSE
                            :V10ERROR:='';
                        END IF;
                    END;@

CURSOR=CVERERROR SELECT :V10ERROR FROM DUAL WHERE :V10ERROR IS NULL;					

CURSOR=CSELCANTIDAD SELECT SUM(MOV.CANTIDAD) TOTALUNID, 
                           FLOOR(SUM(MOV.CANTIDAD)/DECODE(:UNIEMB,0,1,:UNIEMB)) NCAJAS, 
                           MOD(SUM(MOV.CANTIDAD),DECODE(:UNIEMB,0,1,:UNIEMB)) UNIDSUELTAS,
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
                           MOV.CODART  = :CODART AND
                           ART.CODART = MOV.CODART
                      GROUP BY ART.UNIDADESHOST,ART.DECIMALES;
					  
CURSOR=CULTCAJA SELECT CODCOMEN,VDCOM.DAMECOMEN(CODCOMEN,'ULTIMACAJA',1) ULTCAJA
                  FROM VDRECURSO
                 WHERE CODRECURSO=:CODRECURSO;

