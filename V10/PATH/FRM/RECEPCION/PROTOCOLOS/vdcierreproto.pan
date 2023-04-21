CIERRE DE PROTOCOLOS DE ENTRADA
Código    Ord. Recepción     Proveedor       Descripción                Tipo             Importe    Palets Cajas  Estado Descripción                       Cerrar 
#L####### __________________ _20____________ _40_______________________ ________________ #L,####.## ###### ###### @L@@@  _40______________________________   _    
|

TABLA=VDPROTOCOLO
SELECT='N' CERRAR;
ORDERBY=TO_NUMBER(CODPROTO) DESC;

NOINSERT
NODELETE,PROTECT("IMPLANTADOR")
POSX=15
WPOSY=110
REGPAG=20

#POSTQUERY=FEJECUTA("+CCALCPRECIO","")

PREUPDATE=FEJECUTA("CSELOPEMODIF","No puedo poner usuario ultima modificación")

CAMPO=CODPROTO,NOUPDATE,TOOLTIP("Código del protocolo"),TECLA=CR,FPULSATECLAS("F2"),INCLUDECSS="height:16px;COLOR:DARKBLUE;font-style:bold;border-style:ridge;background-color:#F7BE81;",WLONX=6,TITULO("Protocolo")
CAMPO=CODORDREC,TITULO("Orden Recepción")
CAMPO=CODPROVE,UPPER,POSTCHANGE=FEJECUTA("+CSELDATOSPROVE",""),INCLUDECSS="height:16px;COLOR:DARKBLUE;font-style:bold;border-style:ridge;background-color:#F7BE81;",WLONX=6,TITULO("Proveedor")
CAMPO=DESPROVE,AUXILIAR,NOUPDATE,INCLUDECSS="font-style:bold;border-style:ridge;background-color:#F7BE81;",TITULO("Descripción")
CAMPO=TIPOPROVE,AUXILIAR,NOUPDATE,INCLUDECSS="font-style:bold;border-style:ridge;background-color:#F7BE81;",TITULO("Tipo")
CAMPO=PRECIO,NOUPDATE,TITULO("Importe")
CAMPO=NUMPALETS,POSTCHANGE=FDESIGNACION("CACTNUMBUL","Error actualizando número de bultos"),TITULO("Palets")
CAMPO=NUMCAJAS,POSTCHANGE=FDESIGNACION("CACTNUMBUL","Error actualizando número de bultos"),TITULO("Cajas")
CAMPO=NUMBULTOS,OCULTO,"######"
CAMPO=STATUS,PROTECT("SUPERVISOR"),POSTCHANGE=FDESIGNACION("CSELSTATUS","No existe estado"),COMBOX("CSELCOMBOST"),TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TITULO("Descripción")
CAMPO=CERRAR,AUXILIAR,CHECKBOX("N","S"),TITULO("Cerrar")
CAMPO=CODDIV,OCULTO,NOUPDATE,"_20___"
CAMPO=CODOPEMODIF,OCULTO,"_________________"
CAMPO=FECMODIF,OCULTO,"¿D-MM-Y.YY"
CAMPO=HORAMODIF,OCULTO,"_8_"
CAMPO=DUMMY,AUXILIAR,OCULTO,NOUPDATE,"@@@"
CAMPO=MENSAJE,AUXILIAR,NOUPDATE,OCULTO,"_100_"


#CURSORES

CURSOR=CSELCOMBOST SELECT STATUS,DESSTATUS FROM VDSTATUS WHERE TIPOSTATUS = 'PRT' ORDER BY STATUS;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='PRT';

CURSOR=CSELOPEMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF
                    FROM DUAL;

CURSOR=CACTNUMBUL SELECT NVL(:NUMPALETS,0) + NVL(:NUMCAJAS,0) NUMBULTOS FROM DUAL;
					
CURSOR=CFINPROTO UPDATE VDPROTOCOLO 
                    SET STATUS=VDST.FPRTCERRADO,
                        CODOPEMODIF=VDUSER.GETUSER,
                        FECMODIF=VD.FECHASYS,
                        HORAMODIF=VD.HORASYS,
                        CODOPEFIN=VDUSER.GETUSER,
                        FECFIN=VD.FECHASYS,
                        HORAFIN=VD.HORASYS
                  WHERE CODPROTO = :CODPROTO;

CURSOR=CCOMPRUEBASTATUS SELECT 1 DUMMY FROM DUAL WHERE :STATUS = 50;

CURSOR=CVALCONTENIDO  BEGIN
                        BEGIN 
                           SELECT 'XXX' MENSAJE INTO :MENSAJE FROM VDORDRECCAB WHERE CODORDREC= :CODORDREC AND CODDIV=:CODDIV;
                        EXCEPTION
                              WHEN NO_DATA_FOUND THEN
                                   :MENSAJE:=NULL;
                                   RETURN;
                        END;
                       BEGIN 
                         SELECT 'Existen recepciones activas asociadas al protocolo '||:CODPROTO||' , \n\n¿ Desea continuar ? \n' MENSAJE INTO :MENSAJE 
						   FROM VDORDRECCAB 
						  WHERE CODORDREC=:CODORDREC AND CODDIV=:CODDIV AND STATUS<2000 AND ROWNUM<2;
                         RETURN;
					   EXCEPTION
                                 WHEN NO_DATA_FOUND THEN
                                      BEGIN
                                        SELECT 'La orden de recepcion asociada a este protocolo no ha sido finalizada, \n\n¿ Desea continuar ? \n' MENSAJE INTO :MENSAJE 
										  FROM VDORDRECCAB 
									     WHERE CODORDREC=:CODORDREC AND CODDIV=:CODDIV AND STATUS<1500 AND ROWNUM<2;
										 RETURN;
                                      EXCEPTION
                                        WHEN NO_DATA_FOUND THEN 
                                          :MENSAJE:=NULL;
                                          RETURN;
                                      END;  
                       END;
						:MENSAJE :=NULL;	 
                     END;@

CURSOR=CVERERROR SELECT :MENSAJE
                   FROM DUAL 
                  WHERE :MENSAJE IS NULL;

#CURSOR=CCALCPRECIO SELECT NVL(SUM(ORL.PRECIO),0) PRECIO 
#                     FROM VDPROTOCAB PRT,VDORDRECLIN ORL 
#					WHERE CODPROTO=:CODPROTO AND PRT.CODORDREC=ORL.CODORDREC AND ORL.STATUS=VDST.FORLFINALIZADA;

CURSOR=CSELDATOSPROVE SELECT TIPOPROVE,DESPROVE FROM VDPROVEEDOR WHERE CODPROVE=:CODPROVE;


#CERRAR PROTOCOLO				  
TECLA=SF6,FDESIGNACION(FIF("CCOMPRUEBASTATUS",FEJECUTA("CVALCONTENIDO","", 
										               "!CVERERROR",":MENSAJE",
													   "CFINPROTO","Error cerrando protocolo",
													   FCOMMIT,"",
													   %FFAILURE,"Protocolo :CODPROTO cerrado",
													   FPULSATECLAS("CF2","CF2","F2"),""),
                                              FEJECUTA(%FFAILURE,"El protocolo ya está cerrado")),
	                   "Protocolo :CODPROTO NO cerrado. ")

											  
ONLINE={SF6} Cerrar protocolo {F4} Confirmar cambios {F3} Limpiar pantalla {Esc} Salir;             
