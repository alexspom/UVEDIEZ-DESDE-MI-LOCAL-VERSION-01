##############################################################################
#  Módulo  : VDFMDDECOMVERIF.PAN                                             #
#  Función : Leer decomisiones de artículos con FMD                          #
#                                                                            #
#  Autor : DFL                                                               #
#  Fecha : 16-07-2018                                                        #
#  Revisador por  :                                                          #
#  Fecha revisión :                                                          #
##############################################################################
#  Histórico de cambios
#  --------------------
#
##############################################################################
VERIFICACION DE ARTÍCULOS FMD
 Número de serie: _240____________________________________________________________________________   

|

NOQUERY
NOCOMMIT
NOINSERT
NOUPDATE
NODELETE

POSX=2
POSY=3


POSTCOMMIT=FEJECUTA("CVERTOTAL","")

CAMPO=NUMEROSERIE,AUXILIAR,OCULTO,"_240_"
CAMPO=CODARTAUX,AUXILIAR,OCULTO,"_40_"
CAMPO=CODLOTAUX,AUXILIAR,OCULTO,"_40_"
CAMPO=CODEANAUX,AUXILIAR,OCULTO,"_40_"
CAMPO=CANTTOTAL,AUXILIAR,OCULTO,"#L########"
CAMPO=LEIDASTOTAL,AUXILIAR,OCULTO,"#L#######"
CAMPO=CODENSAYO,AUXILIAR,OCULTO,"_40_"
CAMPO=CODBULTO,AUXILIAR,OCULTO,VIRTUAL
CAMPO=CODMOV,AUXILIAR,OCULTO,"#L#########"
CAMPO=CODBIDI,AUXILIAR,POSTCHANGE=FDESIGNACION("CCARGARAUX","ERROR AL LEER BIDI",
											   "CCARGARCODART","ERROR AL CARGAR ARTICULO",
#											   "CSELARTLOT","NUMERO DE SERIE LEIDO NO ES DE ARTICULO Y LOTE SELECCIONADO",
                                               FIF("-CVERSIEXISTE",FEJECUTA(FIF("CDECOMISIONAR",FSUCCESS,
#   		                                                                                            ##EN CASO DE ERROR AL DECOMISAR CAMBIAR CODART DE MATRICULA##
                                                                                                FEJECUTAFORM("VDFMDDECOMERROR","N","","CODART=:CODARTAUX CODLOT=:CODLOTAUX CODBULTO=:CODBULTO",""),""
											                                    ),"Error al insertar en VDNUMSERIESFMD"),
                                                                   FEJECUTA(%FFAILURE,"NUMERO DE SERIE YA LEIDO",
																            FSUCCESS)),"",                                              
                                               FCOMMIT,"",
                                               PRESEHIJO,"",
                                               "CVERTOTAL","",
											   FIF("CCOMPLEIDAS","CUPDCABBU",FSUCCESS),"",
                                               FCOMMIT,"",
                                               FIF("CCOMPLEIDAS",FEJECUTA(%FFAILURE,"FIN DE LECTURA DE NUMEROS DE SERIE",FPULSATECLAS("F5")),FSUCCESS),"",
                                               "+CINI",""
                                             )
 
CAMPO=RET,AUXILIAR,OCULTO,"#L#####"
CAMPO=NVMSID,AUXILIAR,OCULTO,"_240_"     
CAMPO=NVMSSTATUS,AUXILIAR,OCULTO,"_240_" 
CAMPO=NVMSREASON,AUXILIAR,OCULTO,"_240_" 
CAMPO=NVMSRET,AUXILIAR,OCULTO,"_240_"    
CAMPO=NVMSRETDESC,AUXILIAR,OCULTO,"_240_"

#CURSORES
#########
CURSOR=CCARGARAUX SELECT VDEAN.VALOR(:CODBIDI,'21') NUMEROSERIE, VDEAN.VALOR(:CODBIDI,'240') CODARTAUX, VDEAN.VALOR(:CODBIDI,'01') CODEANAUX, VDEAN.VALOR(:CODBIDI,'10') CODLOTAUX FROM DUAL;

CURSOR=CCARGARCODART SELECT CODART CODARTAUX FROM VDARTIC WHERE CODEAN=:CODEANAUX;

CURSOR=CSELARTLOT SELECT :CODARTAUX FROM VDNUMSERIESFMD 
                      WHERE CODBULTO=:CODBULTO AND CODART=:CODARTAUX AND CODLOT=:CODLOTAUX;

CURSOR=CVERSIEXISTE SELECT :CODBULTO CODBULTO
                      FROM VDNUMSERIESFMD 
                      WHERE CODBULTO=:CODBULTO
                        AND NUMEROSERIE=:NUMEROSERIE 
                        AND CODART=:CODARTAUX 
                        AND CODLOT=:CODLOTAUX 
                        AND ACCION='DECOMMISION';

CURSOR=CDECOMISIONAR DECLARE
                        nvmsID      VARCHAR2(100);
                        nvmsSTATUS  VARCHAR2(100);
                        nvmsREASON  VARCHAR2(100);
                        nvmsRET     VARCHAR2(100);
                        nvmsRETDESC VARCHAR2(100);
                        RET         NUMBER;
						vTIPOBUL    VARCHAR2(5);
						vTIPOVOL    VARCHAR2(10);
						MICODMOV    NUMBER;
                     BEGIN 
                        SELECT BUL.CODMOV, BUC.TIPOBULTO, BUC.TIPOVOL
                             INTO MICODMOV,vTIPOBUL,vTIPOVOL
                          FROM VDBULTOLIN BUL,VDBULTOCAB BUC,VDMOVIM MOV
                         WHERE BUL.CODBULTO = BUC.CODBULTO 
                               AND BUL.CODBULTO = :CODBULTO
                               AND BUL.CODMOV   = MOV.CODMOV
                               AND BUL.CODART   = MOV.CODART
                               AND BUL.CODART   = :CODARTAUX
                               AND MOV.CODLOT   = :CODLOTAUX
                               AND ROWNUM=1;
							   
                        IF VDFMD.INSERTANUMSERIEVERIF(:NUMEROSERIE,:CODARTAUX,:CODLOTAUX,MICODMOV, VDST.FFMDPENDIENTE,:CODBULTO, :CODBIDI) <> 0 THEN RAISE NO_DATA_FOUND; END IF;
                        IF VDFMD.VERIFICAFMD(:CODBIDI,nvmsID, nvmsSTATUS, nvmsREASON, nvmsRET, nvmsRETDESC)  <> 0 THEN RAISE NO_DATA_FOUND; END IF;

						UPDATE VDNUMSERIESFMD
                               SET ESTADO     = nvmsSTATUS,
                                   RESULTADO  = nvmsRET,
                                   STATUS     = VDST.FFMDINFORMADO
                               WHERE NUMEROSERIE = :NUMEROSERIE
                                 AND STATUS = VDST.FFMDPENDIENTE
                                 AND CODMOV =MICODMOV 
								 AND CODBULTO=:CODBULTO;						 
						   
						IF nvmsSTATUS <> 'ACTIVE' THEN
							   UPDATE VDBULTOCAB
                                  SET STATUS = VDST.FBUCERRFMD
                                  WHERE CODBULTO = :CODBULTO;
								COMMIT;
                               RAISE NO_DATA_FOUND;
                        ELSE
						       INSERT INTO VDNUMSERIESFMD(SECFMD, NUMEROSERIE,CODART,CODLOT,CODMOV,CODOPECREA,FECCREA,HORACREA ,ACCION,RESULTADO,ESTADO,SWTDECOMOK,
                                                          SWTUSADODECOM,MOTDECOM, STATUS, CODOPEMODIF,FECMODIF,HORAMODIF,CODBULTO, CODBIDI)
                               VALUES (VDSECFMD.NEXTVAL, :NUMEROSERIE , :CODARTAUX , :CODLOTAUX , MICODMOV , VDUSER.GETUSER , VD.FECHASYS, VD.HORASYS, VD.GETPROP('FMDACCIONDECOMMISION'), '', '', '',
                                       'N', 'DISPENSE', VDST.FFMDPENDIENTE, VDUSER.GETUSER, VD.FECHASYS, VD.HORASYS, :CODBULTO, :CODBIDI);
						END IF;
							

                        COMMIT; 
                     END;@



CURSOR=CVERTOTAL  SELECT DECODE(BUC.TIPOVOL,'PA',SUM(BUL.CANTPEDIDA),SUM(BUL.CANTSERVIDA)) CANTTOTAL,
                         (SELECT COUNT(*) FROM VDNUMSERIESFMD FMD WHERE CODBULTO=:CODBULTO AND RESULTADO IS NOT NULL ) LEIDASTOTAL
                     FROM VDBULTOLIN BUL,VDBULTOCAB BUC,VDARTIC ART 
                     WHERE BUC.CODBULTO = :CODBULTO AND BUC.CODBULTO=BUL.CODBULTO AND
                           BUL.CODART=ART.CODART AND ART.SWTFMD = 'S'
                     GROUP BY BUL.CODBULTO,BUC.TIPOVOL;


CURSOR=CCOMPLEIDAS SELECT :CODBULTO FROM DUAL WHERE :CANTTOTAL = :LEIDASTOTAL;

CURSOR=CINI SELECT '' CODBIDI FROM DUAL;

CURSOR=CUPDCABBU UPDATE VDBULTOCAB SET STATUS=DECODE(TIPOVOL,'PA',STATUS,VDST.FBUCPREPARADO) WHERE CODBULTO=:CODBULTO;

ONLINE=     {F1} Ayuda {F2} Consulta {F4} Confirmar cambios {F5} Borrar pantalla {F9} Borrar registro
                                    {May-F10} Menú {Esc} Salir;
