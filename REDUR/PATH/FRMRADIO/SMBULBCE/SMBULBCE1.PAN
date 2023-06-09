#
GESTION DE BULB CON ETIQUETA
_10_______ _10_______
CAJA COMPLETA                    

ARTICULO:  _20_______________
           _20_______________
		   
MATRICULA: ____________________
ORIGEN:    ________________

UBICACION: ________________

|

PREQUERY=FEJECUTA("CLIMPIA","",
                  FIF("-CMOVTOPDTES",FPOSICIONABLOQUE("VDPICKCCNOMOV.PAN"),FSUCCESS),"\n NO HAY \n MOVIMIENTOS\n PENDIENTES",
                  "CCONGELAMOVS","\n ERROR CONGELANDO\n MOVIMIENTOS DE\n UBICACION :CODUBI",
                  FCOMMIT,"",
                  FIF("-CMOVCONGELADOS",FEJECUTA("+CSELUBI","",+FPOSICIONABLOQUE("VDPICKCCERRCONGELA.PAN"),""),FSUCCESS),"\n NO HAY\n MOVIMIENTOS\n CONGELADOS",
                  "+CSELDECIMALES","",
				  FPOSICIONACAMPO(FSUCCESS,"NCODART"),"")

POSTQUERY=FEJECUTA("+CCTRLCALIDAD","",
                   "CVERIFICAUBI","\n UBICACION INCORRECTA", 
                   "CVERERROR",":V10ERROR",                                    
                   FPOSICIONABLOQUE("SMBULBCE2.PAN"))

# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=CODTERBLOQ,OCULTO,"_10_"
CAMPO=CODARTT,NOENTER
CAMPO=DESARTT,OCULTO,"_30_"
CAMPO=NCODART,SCAN,POSTCHANGE=FEJECUTA("CVERIFART","\n ARTICULO INCORRECTO",
                                       FFUERZASCAN("ART"),"\n DEBE LEER\n  ARTICULO")
CAMPO=CODMATT,NOENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=CODUBIORIGT,OCULTO,"_20_"
CAMPO=CODMAT,OCULTO,"_18_"
CAMPO=CODUBI,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA("CVERPARCIAL","\n UBICACION INCORRECTA",
                                                FFUERZASCAN("UBI"),"\n DEBE LEER\n UBICACION")
CAMPO=CODBULTO,OCULTO,"_18_"
CAMPO=CODDIV,OCULTO,"____"
CAMPO=ANOPED,OCULTO,"@L@@"
CAMPO=SEQPED,OCULTO,"@L@"
CAMPO=CODPED,OCULTO,"_20_"
CAMPO=NBULTO,OCULTO,"@L@@@"
CAMPO=UNIEMB,OCULTO,"@L@@@@@"
CAMPO=CAJAS,OCULTO,"@L@@@@@"
CAMPO=CANTIDAD,OCULTO,"@L@@@@@"
CAMPO=STSOLICITADO,OCULTO,"@L@@"
CAMPO=STACABADO,OCULTO,"@L@@"
CAMPO=STENPUERTO,OCULTO,"@L@@"
CAMPO=FIELDDUMMY,OCULTO,"@L@@"
CAMPO=CERO,OCULTO,"_"
CAMPO=NBACABADOS,OCULTO,"@L@@@"
CAMPO=PUERTO,OCULTO,"@L"
CAMPO=CTRLCALIDAD,OCULTO,"_"
CAMPO=CODIMPRE,OCULTO,"________________"
CAMPO=VERIFECI,OCULTO,"_"
CAMPO=CODUBIDEST,OCULTO,"_12____"
CAMPO=CODLOT,OCULTO,"_20_"
CAMPO=CODPREPARACION,OCULTO,"@L"
CAMPO=CODARTANT,OCULTO,"_20_"
CAMPO=DESARTT1,OCULTO,"_30_"



CURSOR=CLIMPIA SELECT 'N' CTRLCALIDAD,NULL CODUBI,NULL NCODART FROM DUAL;

CURSOR=CMOVTOPDTES SELECT 'N' CERO,MOV.CODUBIORI CODUBIORIGT,VDCLIPKG.PINTAUBICA(MOV.CODUBIORI) PINTAUBI,MOV.CODMATORI CODMATT,MOV.CODMATORI CODMAT,
                          MOV.CODUBIDEST CODUBIDEST,MOV.CODART CODARTT,MOV.UNIEMB,SUBSTR(ART.CODEAN,2) CODARTANT,MOV.CODPREPARACION,
						  VD.DIVIDEXBUSQUEDA(1,ART.DESART,' ',30,0) DESARTT,VD.DIVIDEXBUSQUEDA(2,ART.DESART,' ',30,0) DESARTT1
                     FROM VDMOVIM MOV,VDARTIC ART, VDUBICA UBI
                    WHERE MOV.STATUS IN (VDST.FMOVASIGNADO,VDST.FMOVPRESENTADO) 
                          AND MOV.CODRECURSO = :CODRECURSO 
                          AND MOV.TAREA = 'PEDEMBA'
                          AND ART.CODART = MOV.CODART
                          AND MOV.CODUBIORI = UBI.CODUBI
						  AND MOV.CODMOV IN (SELECT BUL.CODMOV FROM VDBULTOCAB BUC,VDBULTOLIN BUL
                                              WHERE BUC.CODBULTO=BUL.CODBULTO AND BUC.STATUS=VDST.FBUCBULABANETI)
                    ORDER BY UBI.ORDENSALIDA,MOV.CODPREPARACION,DECODE(MOV.STATUS,VDST.FMOVPRESENTADO,0,1);

CURSOR=CCONGELAMOVS DECLARE
					  CURSOR C1 IS SELECT MOV.* 
						             FROM VDMOVIM MOV
						            WHERE MOV.TAREA = 'PEDEMBA' 
						              AND MOV.STATUS = VDST.FMOVASIGNADO
						              AND MOV.CODRECURSO = :CODRECURSO 											            
						              AND MOV.CODUBIORI  = :CODUBIORIGT 
						              AND MOV.CODUBIDEST = :CODUBIDEST 
						              AND MOV.CODMATORI  = :CODMATT 
						              AND MOV.CODART     = :CODARTT 
						              AND MOV.UNIEMB     = :UNIEMB 
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
					     VDLOG.PONMENSAJE('SMBULBCE1','CCONGELAMOVS: CONGELADO MOVTO ' || I.CODMOV);
					     UPDATE VDMOVIM SET STATUS=VDST.FMOVPRESENTADO,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS WHERE CODMOV=I.CODMOV;
					   ELSE
                         VDLOG.PONERROR('SMBULBCE1','CCONGELAMOVS: NO SE PUEDE CONGELAR MOVTO ' || I.CODMOV);
						 UPDATE VDMOVIM SET STATUS=VDST.FMOVPDTESTOCK,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS WHERE CODMOV=I.CODMOV; 
					   END IF;
					 END LOOP;                      
                     UPDATE VDMOVIM SET STATUS=VDST.FMOVPDTESTOCK,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS 
					  WHERE STATUS=VDST.FMOVASIGNADO 
					    AND CODRECURSO = :CODRECURSO 											            
						AND CODUBIORI  = :CODUBIORIGT 
						AND CODUBIDEST = :CODUBIDEST 
						AND CODMATORI  = :CODMATT 
						AND CODART     = :CODARTT 
						AND UNIEMB     = :UNIEMB
						AND CODPREPARACION = :CODPREPARACION;					 
                   END;@       

CURSOR=CMOVCONGELADOS SELECT SUM(CANTIDAD/UNIEMB) CAJAS,CODLOT,UNIEMB 
                        FROM VDMOVIM MOV
                       WHERE MOV.TAREA = 'PEDEMBA' 
						 AND MOV.STATUS = VDST.FMOVPRESENTADO
						 AND MOV.CODRECURSO = :CODRECURSO 											            
						 AND MOV.CODUBIORI  = :CODUBIORIGT 
						 AND MOV.CODUBIDEST = :CODUBIDEST 
						 AND MOV.CODMATORI  = :CODMATT 
						 AND MOV.CODART     = :CODARTT
						 AND MOV.UNIEMB     = :UNIEMB
                         AND MOV.CODLOT IS NOT NULL
						 AND MOV.CODPREPARACION = :CODPREPARACION
					   GROUP BY CODLOT,UNIEMB; 

CURSOR=CSELUBI SELECT :CODUBIORIGT CODUBI FROM DUAL;

CURSOR=CSELDECIMALES SELECT ART.DECIMALES UNIEMB__DECIMALES FROM VDARTIC ART WHERE CODART = :CODARTT;
					   
CURSOR=CVERIFUBI SELECT :CODUBI CODUBI FROM DUAL WHERE :CODUBIORIGT=:CODUBI;

CURSOR=CVERIFART SELECT :CODARTT FROM DUAL WHERE (:CODARTT=:NCODART OR :CODARTT=SUBSTR(:NCODART,2));

CURSOR=CVERIFMAT SELECT :CODMAT CODMAT FROM DUAL WHERE :CODMAT=:CODMATT;

CURSOR=CCTRLCALIDAD SELECT 'S' CTRLCALIDAD
                      FROM VDBULTOCAB BUC,VDBULTOLIN BUL 
                     WHERE BUC.CODBULTO=BUL.CODBULTO AND 
						   BUL.CODMOV IN (SELECT CODMOV 
                                            FROM VDMOVIM MOV
                                           WHERE MOV.TAREA = 'PEDEMBA' 
						                     AND MOV.STATUS = VDST.FMOVPRESENTADO
						                     AND MOV.CODRECURSO = :CODRECURSO 											            
						                     AND MOV.CODUBIORI  = :CODUBIORIGT 
						                     AND MOV.CODUBIDEST = :CODUBIDEST 
						                     AND MOV.CODMATORI  = :CODMATT 
						                     AND MOV.CODART     = :CODARTT
						                     AND MOV.UNIEMB     = :UNIEMB
                                             AND MOV.CODPREPARACION = :CODPREPARACION
											 AND MOV.CODLOT IS NOT NULL);                                             
                           
CURSOR=CVERIFICAUBI BEGIN
                   IF :CODUBIORIGT!=:CODUBI THEN 
                      IF SUBSTR(:CODUBI,1,LENGTH(:CODUBIORIGT)-1)=SUBSTR(:CODUBIORIGT,1,LENGTH(:CODUBIORIGT)-1) THEN
                         :V10ERROR:='\n TIENES QUE PULSAR F1 O F2';
                        ELSE
                         :V10ERROR:='\n UBICACION INCORRECTA\n LEIDO :CODUBI \n ESPERADO :CODUBIORIGT';
                       END IF;
                     ELSE
                      :V10ERROR:='';
                   END IF;
                 END;@

CURSOR=CVERERROR SELECT :V10ERROR FROM DUAL WHERE :V10ERROR IS NULL;

CURSOR=CVERPARCIAL BEGIN
                     IF :CODUBI IS NULL THEN RAISE NO_DATA_FOUND;
                      END IF;
                     IF LENGTH(:CODUBIORIGT)=LENGTH(:CODUBI) THEN
                        IF :CODUBIORIGT!=:CODUBI THEN RAISE NO_DATA_FOUND;
                         END IF;
                      ELSE
                        IF SUBSTR(:CODUBI,1,LENGTH(:CODUBIORIGT)-1)!=SUBSTR(:CODUBIORIGT,1,LENGTH(:CODUBIORIGT)-1) THEN RAISE NO_DATA_FOUND;
                          END IF;
                    END IF;
                   END;@
                                          
				   