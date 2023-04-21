##############################################################################
#  Módulo  : VDUNDECOMISIONARFMD.PAN                                         #
#  Función : Decomisionar un numero de serie                                 #
#                                                                            #
#  Autor : MJGG                                                              #
#  Fecha : 21-11-2018                                                        #
#  Revisador por  :                                                          #
#  Fecha revisión :                                                          #
##############################################################################
#  Histórico de cambios
#  --------------------
# Autor    : MJGG
# Fecha    : 26/11/2018
# Cambio   : M001 - Limpieza de campos cuando no se quiere hacer actualizaciones de estado 
#
#
##############################################################################
ACTIVAR DESACTIVAR UNIDADES

 Número de serie: _240____________________________________________________________________________   
 
 
 NumeroSerie          Articulo            Lote                          ESTADO       MOTIVO         RESULTADO          
 _40________________  _40_______________  _40_________________          _40________  _40__________  _40_______________ 
  
 _200_________________________________________________________________________________________________________________

 
|

NOQUERY
NOCOMMIT
NOINSERT
NOUPDATE
NODELETE


CAMPO=MOTIVOFMD,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODBIDI,AUXILIAR,POSTCHANGE=FDESIGNACION("CSELNOTNULL","POR FAVOR, INFORME NUMERO DE SERIE",
											   "CCARGARAUX","ERROR AL LEER CODIGO BIDIMENSIONAL",
											   "CCARGARCODART","CODIGO EAN :CODEANAUX NO EXISTE",  
											   "CSELSEC","ERROR AL CALCULAR LA SECUENCIA FMD",
											   "CINSERTNS","ERROR AL INSERTAR EL NUMERO DE SERIE",
											   FCOMMIT,"",
											   "CCONSULTANS","ERROR AL CONSULTAR EL NUMERO DE SERIE",
                                               "CUPDNSFMDINFORMADO","ERROR ACTUALIZANDO ESTADO DE LA CONSULTA DE NUMERO DE SERIE",											   
                                               FCOMMIT,"",											   
                                               FIF("CSELACTIVO",FEJECUTA("!-CSELACTIVO","\n NUMERO DE SERIE :NUMEROSERIE EN ESTADO\n\n                 ACTIVO\n\n      ¿DESACTIVAR NUMERO DE SERIE?\n",
											                             "CSELSECDECO","ERROR AL CALCULAR LA SECUENCIA DECO FMD",
																		 "CINSERTNSDECO","ERROR AL INSERTAR EL NUMERO DE SERIE 2",
																		 FCOMMIT,"",
											                             "CDESACTIVAR","ERROR ACTIVANDO NUMERO DE SERIE",
																		 "CUPDNSFMDINFORMADODECO","ERROR ACTUALIZANDO ESTADO DE LA CONSULTA DE NUMERO DE SERIE DECO",
																		 FCOMMIT,""
																		 ),
											                    FEJECUTA(FIF("CSELNOACTIVO",FEJECUTA("!-CSELNOACTIVO","\n NUMERO DE SERIE :NUMEROSERIE EN ESTADO\n\n                 DESACTIVADO\n\n     ¿ACTIVAR NUMERO DE SERIE?\n",
																                                     "CSELSECUNDECO","ERROR AL CALCULAR LA SECUENCIA UNDECO FMD",
																									 "CINSERTNSUNDECO","ERROR AL INSERTAR EL NUMERO DE SERIE 3",
																									 FCOMMIT,"",
																                                     "CACTIVAR","ERROR DESACTIVANDO NUMERO DE SERIE",
																									 "CUPDNSFMDINFORMADOUNDECO","ERROR ACTUALIZANDO ESTADO DE LA CONSULTA DE NUMERO DE SERIE UNDECO",
																									 FCOMMIT,""
																									 ),
																                            %FFAILURE,"NUMERO DE SERIE DESCONOCIDO"),"ERROR AL COMPROBAR ESTADO NO ACTIVO"
																		)
												   ),"ERROR AL COMPROBAR ESTADO ACTIVO",
												   "CMOSTRAR","ERROR AL MOSTRAR LAS VARIABLES"
                                             )
CAMPO=NUMEROSERIE,AUXILIAR,OCULTO,"_240_"
CAMPO=CODARTAUX,AUXILIAR,OCULTO,"_40_"
CAMPO=CODLOTAUX,AUXILIAR,OCULTO,"_40_"
CAMPO=CODEANAUX,AUXILIAR,OCULTO,"_40_"

CAMPO=NVMSID,AUXILIAR,OCULTO,"_240_"     
CAMPO=NVMSSTATUS,AUXILIAR,OCULTO,"_40_" 
CAMPO=NVMSREASON,AUXILIAR,OCULTO,"_40_" 
CAMPO=NVMSRET,AUXILIAR,OCULTO,"_40_"	   
CAMPO=NVMSRETDESC,AUXILIAR,OCULTO,"_40_"
CAMPO=SWTESTADO,AUXILIAR,OCULTO,"_240_" 

CAMPO=MISEC,AUXILIAR,OCULTO,"@@@@@@@@@@@" 
CAMPO=MISECDECO,AUXILIAR,OCULTO,"@@@@@@@@@@@" 
CAMPO=MISECUNDECO,AUXILIAR,OCULTO,"@@@@@@@@@@@" 


CAMPO=NUMEROSERIE1,AUXILIAR,NOENTER
CAMPO=CODARTAUX1,AUXILIAR,NOENTER
CAMPO=CODLOTAUX1,AUXILIAR,NOENTER
CAMPO=NVMSSTATUS1,AUXILIAR,NOENTER 
CAMPO=NVMSREASON1,AUXILIAR,NOENTER 
CAMPO=NVMSRET1,AUXILIAR,NOENTER	   

CAMPO=DESCRIPTION,AUXILIAR,NOENTER


#CURSORES
#########
CURSOR=CSELNOTNULL SELECT :CODBIDI FROM DUAL WHERE :CODBIDI IS NOT NULL;			                        					 

CURSOR=CCARGARAUX SELECT VDEAN.VALOR(:CODBIDI,'21') NUMEROSERIE, VDEAN.VALOR(:CODBIDI,'240') CODARTAUX, VDEAN.VALOR(:CODBIDI,'01') CODEANAUX, VDEAN.VALOR(:CODBIDI,'10') CODLOTAUX FROM DUAL;

CURSOR=CCARGARCODART SELECT CODART CODARTAUX FROM VDARTIC WHERE CODEAN=:CODEANAUX;

CURSOR=CSELSEC SELECT VDSECFMD.NEXTVAL MISEC FROM DUAL;

CURSOR=CSELSECDECO SELECT VDSECFMD.NEXTVAL MISECDECO FROM DUAL;

CURSOR=CSELSECUNDECO SELECT VDSECFMD.NEXTVAL MISECUNDECO FROM DUAL;
	

CURSOR=CINSERTNS INSERT INTO VDNUMSERIESFMD(SECFMD, NUMEROSERIE,CODART,CODLOT,CODMOV,CODOPECREA,FECCREA,HORACREA ,
                                             ACCION,RESULTADO,ESTADO,SWTDECOMOK,
                                             SWTUSADODECOM,MOTDECOM, STATUS, CODOPEMODIF,FECMODIF,HORAMODIF,CODBULTO, CODBIDI)
                    VALUES (:MISEC, :NUMEROSERIE , :CODARTAUX , :CODLOTAUX , 0, VDUSER.GETUSER , VD.FECHASYS, VD.HORASYS,
					        VD.GETPROP('FMDACCIONVERIFICAR'),'','','',
                            'N', NULL, VDST.FFMDPENDIENTE,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,NULL,:CODBIDI);								
							
CURSOR=CINSERTNSDECO INSERT INTO VDNUMSERIESFMD(SECFMD, NUMEROSERIE, CODART, CODLOT, CODMOV, CODOPECREA, FECCREA, HORACREA,
								  			    ACCION,RESULTADO,ESTADO,SWTDECOMOK,MOTDECOM,STATUS,
												CODOPEMODIF,FECMODIF,HORAMODIF,CODBIDI) 	
                                        VALUES (:MISECDECO, :NUMEROSERIE , :CODARTAUX , :CODLOTAUX , 0, VDUSER.GETUSER, VD.FECHASYS, VD.HORASYS,
											    VD.GETPROP('FMDACCIONDECOMMISION'),NULL,NULL,NULL,NVL(:MOTIVOFMD,'DISPENSE'),VDST.FFMDPENDIENTE,
												VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,:CODBIDI);							

CURSOR=CINSERTNSUNDECO INSERT INTO VDNUMSERIESFMD(SECFMD, NUMEROSERIE, CODART, CODLOT, CODMOV, CODOPECREA, FECCREA, HORACREA,
												   ACCION,RESULTADO,ESTADO,SWTDECOMOK,MOTDECOM,STATUS,
												   CODOPEMODIF,FECMODIF,HORAMODIF,CODBIDI) 	
                                            VALUES (:MISECUNDECO, :NUMEROSERIE , :CODARTAUX , :CODLOTAUX , 0, VDUSER.GETUSER, VD.FECHASYS, VD.HORASYS,
											        VD.GETPROP('FMDACCIONUNDODECOMMISION'),NULL,NULL,NULL,NVL(:MOTIVOFMD,'DISPENSE'),VDST.FFMDPENDIENTE,
													VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS, :CODBIDI);												   
							

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
						
						SELECT nvmsSTATUS,nvmsRET,nvmsREASON INTO :NVMSSTATUS,:NVMSRET,:NVMSREASON FROM DUAL;
                     END;@

					 
CURSOR=CSELACTIVO SELECT :NVMSSTATUS FROM DUAL WHERE :NVMSSTATUS='ACTIVE';

CURSOR=CSELNOACTIVO SELECT :NVMSSTATUS FROM DUAL WHERE :NVMSSTATUS='INACTIVE';


CURSOR=CACTIVAR DECLARE
                        nvmsIDact      VARCHAR2(100);
                        nvmsSTATUSact  VARCHAR2(100);
                        nvmsREASONact  VARCHAR2(100);
                        nvmsRETact     VARCHAR2(100);
                        nvmsRETDESCact VARCHAR2(100);                       				
                     BEGIN 
                         							   
						IF VDFMD.UNDECOMISIONARFMD(:CODBIDI,:MOTIVOFMD,nvmsIDact, nvmsSTATUSact, nvmsREASONact, nvmsRETact, nvmsRETDESCact)  <> 0 THEN RAISE NO_DATA_FOUND; END IF;
						
						SELECT nvmsSTATUSact,nvmsRETact,nvmsREASONact INTO :NVMSSTATUS,:NVMSRET,:NVMSREASON FROM DUAL;
												
                     END;@

CURSOR=CDESACTIVAR DECLARE
                        nvmsIDinact      VARCHAR2(100);
                        nvmsSTATUSinact  VARCHAR2(100);
                        nvmsREASONinact  VARCHAR2(100);
                        nvmsRETinact     VARCHAR2(100);
                        nvmsRETDESCinact VARCHAR2(100);                       				
                     BEGIN 
                         							   
						IF VDFMD.DECOMISIONARFMD(:CODBIDI,:MOTIVOFMD,nvmsIDinact, nvmsSTATUSinact, nvmsREASONinact, nvmsRETinact, nvmsRETDESCinact)  <> 0 THEN RAISE NO_DATA_FOUND; END IF;
						SELECT nvmsSTATUSinact,nvmsRETinact,nvmsREASONinact INTO :NVMSSTATUS,:NVMSRET,:NVMSREASON FROM DUAL;
						
                     END;@
					 
CURSOR=CUPDNSFMDINFORMADO   UPDATE VDNUMSERIESFMD
                               SET ESTADO     = :NVMSSTATUS,
                                   RESULTADO  = :NVMSRET,
                                   STATUS     = VDST.FFMDINFORMADO
                               WHERE SECFMD=:MISEC;		

CURSOR=CUPDNSFMDINFORMADODECO   UPDATE VDNUMSERIESFMD
                                   SET ESTADO     = :NVMSSTATUS,
                                       RESULTADO  = :NVMSRET,
                                       STATUS     = VDST.FFMDINFORMADO
                                   WHERE SECFMD=:MISECDECO;

CURSOR=CUPDNSFMDINFORMADOUNDECO   UPDATE VDNUMSERIESFMD
                                     SET ESTADO     = :NVMSSTATUS,
                                         RESULTADO  = :NVMSRET,
                                         STATUS     = VDST.FFMDINFORMADO
                                     WHERE SECFMD=:MISECUNDECO;							   
					 
CURSOR=CMOSTRAR DECLARE                                        				
                     BEGIN                         							   						
						SELECT :NUMEROSERIE INTO :NUMEROSERIE1 FROM DUAL;
						SELECT :CODARTAUX INTO :CODARTAUX1 FROM DUAL;
						SELECT :CODLOTAUX INTO :CODLOTAUX1 FROM DUAL;
						SELECT :NVMSSTATUS INTO :NVMSSTATUS1 FROM DUAL;
						SELECT :NVMSREASON INTO :NVMSREASON1 FROM DUAL;
						SELECT :NVMSRET INTO :NVMSRET1 FROM DUAL;
						BEGIN
						  SELECT COMENTARIOEXT INTO :DESCRIPTION FROM VDFMDLANG WHERE RETURNCODE=:NVMSRET;
						  EXCEPTION WHEN NO_DATA_FOUND THEN NULL;
						END;
                     END;@

CURSOR=CSELMOTIVOFMD SELECT MOTIVOFMD FROM VDMOTIVOFMD; 
					 					 

BOTON=ESCANEAR,870,160,100,100,"Escanear",qr.png,CR,"Escanear codigo 2D",INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=LIMPIAR,1000,160,75,75,"Limpiar",vertislimpiar.png,F3,"Limpiar",INCLUDECSS="border-style:outset;background-color:transparent"

					 
ONLINE=     {F1} Ayuda {F2} Consulta {F4} Confirmar cambios {F5} Borrar pantalla {F9} Borrar registro
                                    {May-F10} Menú {Esc} Salir;
