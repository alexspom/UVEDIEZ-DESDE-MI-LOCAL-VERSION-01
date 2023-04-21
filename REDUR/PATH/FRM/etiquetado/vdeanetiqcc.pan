#
LECTURA DE ARTICULOS PENDIENTES DE ETIQUETAR
EAN: _20_________________
       
|

TABLA=DUAL
NOINSERT
NODELETE
NOCOMMIT
NOUPDATE,PROTECT("SUPERVISOR")


CAMPO=CNTSSCC,AUXILIAR,VIRTUAL,OCULTO
CAMPO=EAN,AUXILIAR		          
CAMPO=CODARTIN,AUXILIAR,OCULTO,"_40_"
CAMPO=CODBULTO,AUXILIAR,OCULTO,"_18_"
CAMPO=NBULTO,AUXILIAR,OCULTO,"@@@@@"
CAMPO=NUMALBA,AUXILIAR,OCULTO,"@@@"
CAMPO=CODPED,AUXILIAR,OCULTO,"_20_"
CAMPO=CODDIV,AUXILIAR,OCULTO,"_20_"
CAMPO=ANOPED,AUXILIAR,OCULTO,"@@@@"
CAMPO=SEQPED,AUXILIAR,OCULTO,"@@@"
CAMPO=ETIQTODAS,AUXILIAR,OCULTO,"_"
CAMPO=SWTNUMSER,AUXILIAR,OCULTO,"_"



CURSOR=CSELNOTNULL SELECT :EAN, VD.GETPROP('ETIQTODASCAJAS') ETIQTODAS FROM DUAL WHERE :EAN IS NOT NULL;

CURSOR=CSELARTIC SELECT VDART.DAMEART(:EAN) CODARTIN FROM DUAL;
									   
CURSOR=CSELBULTOSEAN SELECT CNTSSCC FROM VDBULTOCAB BUC,VDBULTOLIN BUL 
                      WHERE BUC.CODBULTO=BUL.CODBULTO AND CNTSSCC=:CNTSSCC AND 
				            TIPOBULTO='E' AND BUC.STATUS=VDST.FBUCAETIQUETAR AND
					        BUL.CODART=:CODARTIN;

CURSOR=CSELBULTOS SELECT BUC.CODBULTO,BUC.NBULTO,PEC.CODPED,PEC.ANOPED,PEC.CODDIV,PEC.SEQPED, 
                         NVL(ART.SWTNUMEROSERIE,'N') SWTNUMSER                         						 
                    FROM VDBULTOCAB BUC,VDBULTOLIN BUL,VDPEDIDOCAB PEC, VDARTIC ART
                   WHERE BUC.CNTSSCC=:CNTSSCC AND BUC.TIPOBULTO='E' AND 
                         BUC.STATUS+0=VDST.FBUCAETIQUETAR AND BUC.CODBULTO=BUL.CODBULTO AND
                         BUL.CODART=:CODARTIN AND 
						 ART.CODART=BUL.CODART AND
                         BUC.CODPED=PEC.CODPED AND BUC.ANOPED=PEC.ANOPED AND 
                         BUC.CODDIV=PEC.CODDIV AND BUC.SEQPED=PEC.SEQPED;
                         
CURSOR=CQUEDAN SELECT BUC.CODBULTO,BUC.NBULTO
                    FROM VDBULTOCAB BUC
                   WHERE BUC.CNTSSCC=:CNTSSCC AND BUC.TIPOBULTO='E' AND 
                         BUC.STATUS+0=VDST.FBUCAETIQUETAR;

CURSOR=CETIQBUL BEGIN
                  UPDATE VDBULTOCAB SET STATUS= DECODE(:SWTNUMSER,"L",4060,VDST.FBUCENEXPED),
                                        FECIMPRIME=VD.FECHASYS,HORAIMPRIME=VD.HORASYS
                   WHERE CODBULTO=:CODBULTO;
                  VDIMPRIME.IMPRIME('ETIQ','VDETIQBU.GEN;VDETIQUETAS.VSQ;CSELBULTO','ESCOPIA=''N'';CODBULTO='||:CODBULTO,1,NULL,NULL,:V10ERROR,VDST.FISPPENDFICH);
				  IF RDRPKG.DIVIMPPACKINGLISTETIQ(:CODBULTO) = 'S' THEN
				     RDRPKG.IMPRIMIRPACKINGLISTETIQ(:CODBULTO);
                  END IF;
                END;@
				
CURSOR=CULTIMOBUL SELECT :CODBULTO FROM DUAL WHERE VDBULTO.DAMEULTBULTO(:CODBULTO)='S';

CURSOR=CUPDBUL UPDATE VDBULTOCAB 
                  SET CODOPEVERIFICA=VDUSER.GETUSER,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS,
                      FECVERIFICA=VD.FECHASYS,HORAVERIFICA=VD.HORASYS,
                      SWTLLEVAALB='S'
                  WHERE CODBULTO=:CODBULTO;				

CURSOR=CSELNUMALBA SELECT PEC.NUMALBA 
                     FROM VDBULTOCAB BUC,VDPEDIDOCAB PEC
                    WHERE BUC.CODBULTO=:CODBULTO AND 
                          BUC.CODPED=PEC.CODPED AND BUC.ANOPED=PEC.ANOPED AND 
                          BUC.CODDIV=PEC.CODDIV AND BUC.SEQPED=PEC.SEQPED;

CURSOR=SELTODAS SELECT :ETIQTODAS FROM DUAL WHERE :ETIQTODAS='S';
							
CURSOR=CSELLECTEAN DECLARE 
                   MITEXTO VARCHAR2(1024); 
                   MIROWIDSCAN VARCHAR2(1024);  
                    BEGIN
                     :V10EVAJAX:=-1;
                     SELECT NVL(LTRIM(TEXTO,'0'),'0'),ROWID INTO MITEXTO,MIROWIDSCAN FROM VDSCANLECT 
                     WHERE MIROWIDSCAN IS NULL AND (REDSCAN, SCANNER) IN
                           (SELECT ORD.IDINFOLECTURA, ORD.SCANNER
                               FROM VDORDENADORES ORD
                                 WHERE ORD.ORDENADOR =VDUSER.GETHOSTNAME)
                        AND ROWNUM=1;
                     IF MITEXTO IS NOT NULL THEN
                         DELETE VDSCANLECT WHERE ROWID=MIROWIDSCAN; 
                         :V10EVAJAX:=3000;
                         :EAN:=MITEXTO;
                         COMMIT;
                     ELSE 
                      :V10EVAJAX:=-1;
                     END IF; 
                     EXCEPTION WHEN OTHERS THEN NULL;
                    END;@ 

TECLA=F4,FEJECUTA(FPULSATECLAS("3000"),"")
TECLA=3000,FEJECUTA("@CSELNOTNULL","",
                    "CSELARTIC","ERROR OBTENIENDO ARTICULO",
                    "CSELBULTOSEAN","CODIGO EAN NO ASOCIADO A BULTOS\nPENDIENTES DE ETIQUETAR",
					"+CSELBULTOS","ERROR OBTENIENDO BULTOS A ETIQUETAR",					
					FIF("SELTODAS",FEJECUTA(FWHILE(FERRORCURSOR("CSELBULTOS"),
				                                                FEJECUTA("CETIQBUL","ERROR ETIQUETANDO BULTOS",
					                                            FIF("CULTIMOBUL",FEJECUTA("CUPDBUL","ERROR ACTUALIZANDO EL BULTO",
					                                                                      "CSELNUMALBA","ERROR OBTENIENDO NUMERO DE COPIAS DE ALBARAN",
					                                                                      FIMPRIMEPEDIDO("INFORME",":CODDIV",":ANOPED",":CODPED",":SEQPED","$(VDALBARAN)","CODDIV=:CODDIV;ANOPED=:ANOPED;CODPED=:CODPED;SEQPED=:SEQPED","",":NUMALBA"),":V10ERROR",
					                        					                          FCOMMIT,"",
					                        					                          %FFAILURE,"\nINCLUIR ALBARAN EN EL\nBULTO :NBULTO DE PEDIDO :CODPED"),
                                                                                 FSUCCESS),"",
					                                            FCOMMIT,"",
                                                                +FFETCHCURSOR("CSELBULTOS"),"ERROR EN FETCH")),"ERROR EN FWHILE"),
								   FEJECUTA("CETIQBUL","ERROR ETIQUETANDO BULTOS",
					                        FIF("CULTIMOBUL",FEJECUTA("CUPDBUL","ERROR ACTUALIZANDO EL BULTO",
					                                                  "CSELNUMALBA","ERROR OBTENIENDO NUMERO DE COPIAS DE ALBARAN",
					                                                  FIMPRIMEPEDIDO("INFORME",":CODDIV",":ANOPED",":CODPED",":SEQPED","$(VDALBARAN)","CODDIV=:CODDIV;ANOPED=:ANOPED;CODPED=:CODPED;SEQPED=:SEQPED","",":NUMALBA"),":V10ERROR",
					                                                  FCOMMIT,"",
					                                                  %FFAILURE,"\nINCLUIR ALBARAN EN EL\nBULTO :NBULTO DE PEDIDO :CODPED"),
                                                             FSUCCESS),"",
					                        FCOMMIT,"")),"ERROR SELECCIONANDO ETIQUETAS",
                   PRESEHIJO,"",
                   FIF("CQUEDAN",FPULSATECLAS("F3"),FPULSATECLAS("F5")),"")
					
AJAX(SCANNER,"","C","","CSELLECTEAN","EAN",100)