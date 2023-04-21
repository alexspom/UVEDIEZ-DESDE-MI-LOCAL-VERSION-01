##############################################################################
#  Módulo  : VDCONSULTAFMD.PAN                                               #
#  Función : Consultar números de serie                                      #
#                                                                            #
#  Autor : MJGG                                                              #
#  Fecha : 21-11-2018                                                        #
#  Revisador por  :                                                          #
#  Fecha revisión :                                                          #
##############################################################################
#  Histórico de cambios
#  --------------------
#
##############################################################################
CONSULTA NUMEROS DE SERIE

 Número de serie: _240______________________________________________________________________________   
 
 
 NumeroSerie          Articulo            Lote                            ESTADO       MOTIVO         RESULTADO
 _40________________  _40_______________  _40_________________            _40________  _40__________  _40__________ 
   
 
 
|

NOQUERY
NOCOMMIT
NOINSERT
NOUPDATE
NODELETE

POSX=2
POSY=3
WLONX=1000


CAMPO=CODBIDI,AUXILIAR,POSTCHANGE=FDESIGNACION("CSELNOTNULL","ERROR NO PUEDE SER NULO",
											   "CCARGARAUX","ERROR AL LEER BIDI",
											   "CCARGARCODART","CODIGO EAN :CODEANAUX NO EXISTE",  
										       "CSELSEC","ERROR AL CALCULAR LA SECUENCIA FMD",
											   "CINSERTNS","ERROR AL INSERTAR EL NUMERO DE SERIE",
											   FCOMMIT,"",
											   "CCONSULTANS","ERROR AL CONSULTAR EL NUMERO DE SERIE",
											   "CUPDNSFMDINFORMADO","ERROR ACTUALIZANDO ESTADO DE LA CONSULTA DE NUMERO DE SERIE",
											   FCOMMIT,""
                                             )
 
CAMPO=NUMEROSERIE,AUXILIAR,NOENTER
CAMPO=CODARTAUX,AUXILIAR,NOENTER
CAMPO=CODLOTAUX,AUXILIAR,NOENTER
CAMPO=CODEANAUX,AUXILIAR,OCULTO,"_40_"

CAMPO=NVMSID,AUXILIAR,OCULTO,"_240_"     
CAMPO=NVMSSTATUS,AUXILIAR,NOENTER 
CAMPO=NVMSREASON,AUXILIAR,NOENTER
CAMPO=NVMSRET,AUXILIAR,NOENTER    
CAMPO=NVMSRETDESC,AUXILIAR,OCULTO,"_40_"

CAMPO=MISEC,AUXILIAR,OCULTO,"@@@@@@@@@@@" 


#CURSORES
#########
CURSOR=CSELNOTNULL SELECT :CODBIDI FROM DUAL WHERE :CODBIDI IS NOT NULL;			                        					 

CURSOR=CCARGARAUX SELECT VDEAN.VALOR(:CODBIDI,'21') NUMEROSERIE, VDEAN.VALOR(:CODBIDI,'240') CODARTAUX, VDEAN.VALOR(:CODBIDI,'01') CODEANAUX, VDEAN.VALOR(:CODBIDI,'10') CODLOTAUX FROM DUAL;

CURSOR=CCARGARCODART SELECT CODART CODARTAUX FROM VDARTIC WHERE CODEAN=:CODEANAUX;

CURSOR=CSELSEC SELECT VDSECFMD.NEXTVAL MISEC FROM DUAL;

CURSOR=CINSERTNS INSERT INTO VDNUMSERIESFMD(SECFMD, NUMEROSERIE,CODART,CODLOT,CODMOV,CODOPECREA,FECCREA,HORACREA ,
                                               ACCION,RESULTADO,ESTADO,SWTDECOMOK,
                                               SWTUSADODECOM,MOTDECOM, STATUS, CODOPEMODIF,FECMODIF,HORAMODIF,CODBULTO,CODBIDI)
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
                         							   
						IF VDFMD.VERIFICAFMD(:CODBIDI, nvmsID, nvmsSTATUS, nvmsREASON, nvmsRET, nvmsRETDESC)  <> 0 THEN RAISE NO_DATA_FOUND; END IF;
						
						SELECT nvmsSTATUS,nvmsRET,nvmsREASON INTO :NVMSSTATUS,:NVMSRET,:NVMSREASON FROM DUAL;
                     END;@

CURSOR=CUPDNSFMDINFORMADO   UPDATE VDNUMSERIESFMD
                               SET ESTADO     = :NVMSSTATUS,
                                   RESULTADO  = :nvmsRET,
                                   STATUS     = VDST.FFMDINFORMADO
                               WHERE SECFMD=:MISEC;

BOTON=ESCANEAR,850,60,100,100,"Escanear",vertis\codigo_barras.png,CR,"Escanear codigo 2D",INCLUDECSS="border-style:outset;background-color:transparent"
							   
							   
ONLINE=     {F1} Ayuda {F2} Consulta {F4} Confirmar cambios {F5} Borrar pantalla {F9} Borrar registro
                                    {May-F10} Menú {Esc} Salir;
