#  Función : Menú para consultar números de serie                            #
#  Autor : MJGG                                                              #
#  Fecha : 21-11-2018                                                        #
#  Revisador por  :                                                          #
#  Fecha revisión :                                                          #
##############################################################################
#  Histórico de cambios
#  --------------------
#  Se adapta para los terminales de radio 06022019 - EAG - PFD
##############################################################################
CONSULTA NUMEROS DE SERIE

 Numero de serie: 
 _240________________________________________________________________________________ 
 
|

PREQUERY=FEJECUTA("CLIMPIACAMPO","NO PUEDO LIMPIAR EL CAMPO CODBIDI")

CAMPO=CODBIDI,SCAN,POSTCHANGE=FDESIGNACION(FIF("CSELNULL",FCARGAFORM(""),FSUCCESS),"ERROR\n AL VOLVER AL MENU",
											   "CCARGARAUX","ERROR AL LEER BIDI",
											   "CCARGARCODART","CODIGO EAN :CODEANAUX NO EXISTE",  
										       "CSELSEC","ERROR AL CALCULAR LA SECUENCIA FMD",
											   "CINSERTNS","ERROR AL INSERTAR EL NUMERO DE SERIE",
											   FCOMMIT,"",
											   "CCONSULTANS","ERROR AL CONSULTAR EL NUMERO DE SERIE",
											   "CUPDNSFMDINFORMADO","ERROR ACTUALIZANDO ESTADO DE LA CONSULTA DE NUMERO DE SERIE",
											   FCOMMIT,"",
											   FPOSICIONABLOQUE("VDCONSULTAFMD2.PAN"),"\nNO SE PUEDE POSICIONAR\nEN EL SIG. BLOQUE"
                                             )
 
CAMPO=NUMEROSERIE,OCULTO,"_40_"
CAMPO=CODARTAUX,OCULTO,"_40_"
CAMPO=CODLOTAUX,OCULTO,"_40_"
CAMPO=CODEANAUX,OCULTO,"_40_"

CAMPO=NVMSID,OCULTO,"_240_"     
CAMPO=NVMSSTATUS,OCULTO,"_40_" 
CAMPO=NVMSREASON,OCULTO,"_40_" 
CAMPO=NVMSRET,OCULTO,"_40_"    
CAMPO=NVMSRETDESC,OCULTO,"_40_"

CAMPO=MISEC,OCULTO,"@@@@@@@@@@@" 


#CURSORES
#########
			                        					 
CURSOR=CSELNULL SELECT :CODBIDI FROM DUAL WHERE :CODBIDI IS NULL;	
		                        					 
CURSOR=CLIMPIACAMPO SELECT '' CODBIDI FROM DUAL;			                        					 

CURSOR=CCARGARAUX SELECT VDEAN.VALOR(:CODBIDI,'21') NUMEROSERIE, VDEAN.VALOR(:CODBIDI,'240') CODARTAUX, VDEAN.VALOR(:CODBIDI,'01') CODEANAUX, VDEAN.VALOR(:CODBIDI,'10') CODLOTAUX FROM DUAL;

CURSOR=CCARGARCODART SELECT CODART CODARTAUX FROM VDARTIC WHERE CODEAN=:CODEANAUX;

CURSOR=CSELSEC SELECT VDSECFMD.NEXTVAL MISEC FROM DUAL;

CURSOR=CINSERTNS INSERT INTO VDNUMSERIESFMD(SECFMD, NUMEROSERIE,CODART,CODLOT,CODMOV,CODOPECREA,FECCREA,HORACREA ,
                                               ACCION,RESULTADO,ESTADO,SWTDECOMOK,
                                               SWTUSADODECOM,MOTDECOM, STATUS, CODOPEMODIF,FECMODIF,HORAMODIF,CODBULTO, CODBIDI)
                    VALUES (:MISEC, :NUMEROSERIE , :CODARTAUX , :CODLOTAUX , 0, VDUSER.GETUSER , VD.FECHASYS, VD.HORASYS,
					        VD.GETPROP('FMDACCIONVERIFICAR'),'','','',
                            'N', NULL, VDST.FFMDPENDIENTE,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,NULL,:CODBIDI);					 
					 
#CCONSULTANS hace la llamada al hub con el numero de serie que se lee en la pantalla y muestra la informacion recibida desde alli.
#El CODMOV no se necesita para la llamada al hub (aunque se pasa como parametro). El motivoFMD lo ponemos a fuego, pero habrá que cambiarlo						   
CURSOR=CCONSULTANS DECLARE
                        nvmsID      VARCHAR2(100);
                        nvmsSTATUS  VARCHAR2(100);
                        nvmsREASON  VARCHAR2(100);
                        nvmsRET     VARCHAR2(100);
                        nvmsRETDESC VARCHAR2(100);                       				
                     BEGIN 
                         							   
						IF VDFMD.VERIFICAFMD(:CODBIDI,nvmsID, nvmsSTATUS, nvmsREASON, nvmsRET, nvmsRETDESC)  <> 0 THEN RAISE NO_DATA_FOUND; END IF;
						
						SELECT nvmsSTATUS INTO :NVMSSTATUS FROM DUAL;
						SELECT nvmsRET INTO :NVMSRET FROM DUAL;
                     END;@

CURSOR=CUPDNSFMDINFORMADO   UPDATE VDNUMSERIESFMD
                               SET ESTADO     = :NVMSSTATUS,
                                   RESULTADO  = :nvmsRET,
                                   STATUS     = VDST.FFMDINFORMADO
                               WHERE SECFMD=:MISEC;