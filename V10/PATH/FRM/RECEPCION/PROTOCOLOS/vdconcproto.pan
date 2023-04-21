MANTENIMIENTO DE PROTOCOLOS DE RECEPCION
  
   Código   #L#######  Proveedor _20____________ _40____________________________  ____________________  TIPO:_40_______
   
   División _20___ _40__________________________ Area Recep:_20_______________ Muelle: _10_______       Temp: _____
                                                                                                     
  ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ Dirección Proveedor ÄÄÄÄÄÄÄÄÄÄÄÄÄÄË ÏÄÄ Recibido ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
  ³ Contacto   _40_______________________________________ ³ ³ Orden Recepción __________________  Etiquetas: @L@@     ³ 
  ³ Dirección  _40_______________________________________ ³ ³ Alb.Prov. _20____________                               ³
  ³            _40_______________________________________ ³ ³                                                         ³
  ³            _40_______________________________________ ³ ³ Transporte: _40________________________________________ ³
  ³            _40_______________________________________ ³ ³ Alb.Trans:  _20___________     Matrícula : _20_________ ³
  ³ Poblacion  _40_______________________________________ ³ ³ Contenedor: _20_______________                          ³
  ³ Teléfono   ____________                               ³ ³                                                         ³
  ³ Pais       _____ _40_________________________________ ³ ³ Palets: @L@@    Cajas: @L@@    Bultos: @L@@             ³
  ³ Provincia  _____ _40_________________________________ ³ ³ Kilos: @L@@                                             ³
  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ³                                                         ³             
  ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ Seguimiento  ÄÄÄÄÄÄÄÄÄÄÄÄÄË ³ Observaciones                                           ³
  ³  Estado     @L@@@ _40______________________________   ³ ³ _255______________________________________________      ³
  ³                                                       ³ ³                                                         ³
  ³  Creación        _______________ ¿D-MM-Y.YY ________  ³ ³                                                         ³ 
  ³  Inicio Descarga _______________ ¿D-MM-Y.YY ________  ³ ³                                                         ³
  ³  Fin Descarga    _______________ ¿D-MM-Y.YY ________  ³ ³                                                         ³
  ³  Cierre          _______________ ¿D-MM-Y.YY ________  ³ ³  Modificado    _________________ ¿D-MM-Y.YY ________    ³
  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
  
|

TABLA=VDPROTOCOLO

ORDERBY=TO_NUMBER(CODPROTO) DESC;

NOINSERT
NODELETE,PROTECT("IMPLANTADOR")

PREQUERY=FEJECUTA("CSELINICIALIZACAMPOS","ERROR INICIALIZANDO CAMPOS")

PREUPDATE=FEJECUTA("-CDIVNULL","DEBE ELEGIR LA DIVISIÓN DEL PROTOCOLO DE ENTRADA",
                   "CVERIFREFDOCUMENTO","DEBE INFORMAR LA REFERENCIA DEL DOCUMENTO",
                   "CVERIFDESPROVE","DEBE INFORMAR LA DESCRIPCIÓN DEL PROVEEDOR",
                   "CVERIFTRANSPORTE","DEBE INFORMAR EL TRANSPORTE",                                      
                   "CSELOPEMODIF","No puedo poner usuario ultima modificación")

CAMPO=TIPOPROTOENTRADAAUX,AUXILIAR,VIRTUAL,OCULTO

CAMPO=CODCOMEN,OCULTO,"@L@@@@@@@"

CAMPO=CODPROTO,NOUPDATE,TOOLTIP("Código del protocolo"),TECLA=CR,FPULSATECLAS("F2"),INCLUDECSS="height:16px;COLOR:DARKBLUE;font-style:bold;border-style:ridge;background-color:#F7BE81;",WLONX=6
CAMPO=CODPROVE,UPPER,POSTCHANGE=FEJECUTA("+CSELDATOSPROVE",""),INCLUDECSS="height:16px;COLOR:DARKBLUE;font-style:bold;border-style:ridge;background-color:#F7BE81;",WLONX=6
CAMPO=DESPROVE,AUXILIAR,NOUPDATE,INCLUDECSS="font-style:bold;border-style:ridge;background-color:#F7BE81;"
CAMPO=TIPOPROVE,AUXILIAR,NOUPDATE,INCLUDECSS="font-style:bold;border-style:ridge;background-color:#F7BE81;"
CAMPO=TIPOPROTO,NOUPDATE,INCLUDECSS="font-style:bold;border-style:ridge;background-color:#F7BE81;"
CAMPO=CODDIV,COMBOX("CLISTADIVIS"),POSTCHANGE=FEJECUTA("+CSELDIVIS",""),COMBOXREGPAG=10
CAMPO=DESDIV,AUXILIAR,NOENTER
CAMPO=CODAREARECEP,PROTECT("IMPLANTADOR"),TOOLTIP("Centro de descarga"),COMBOX("CSELAREA"),POSTCHANGE=FEJECUTA("CACTORDRECEP","Error al actualizar la orden :CODORDREC")
CAMPO=CODMUELLE,TOOLTIP("Muelle asignado para la descarga")
CAMPO=TEMPTRANS,TOOLTIP("Temperatura del vehículo a la hora de la descarga")
CAMPO=CONTACTO,AUXILIAR
CAMPO=CODORDREC,CONTEXTUAL=FEJECUTAFORM("VDORDENESRECEP","N","CODORDREC=:CODORDREC","","","","S")
CAMPO=NUMETIQUETAS,AUXILIAR,TOOLTIP("Numero de etiquetas de protocolo de entrada a imprimir")
CAMPO=DIRECCION,AUXILIAR
CAMPO=CODALBPROVE, TOOLTIP("Código de Albarán del proveedor")
CAMPO=DIRECCION1,AUXILIAR
CAMPO=DIRECCION2,AUXILIAR
CAMPO=CODAGE,TOOLTIP("Agencia de transporte de la que se recibe la recepción"),COMBOX("CLISTAAGENCIAS")
CAMPO=DIRECCION3,AUXILIAR
CAMPO=CODALBTRAN, TOOLTIP("Código de Albarán del transportista")
CAMPO=MATRITRANS,TOOLTIP("Matricula del vehiculo que descarga")
CAMPO=POBLACION,AUXILIAR
CAMPO=NUMCONTETRANS,TOOLTIP("Número de contenedores marítimos")
CAMPO=TELEFONO,AUXILIAR
CAMPO=CODPAIS,POSTCHANGE=FDESIGNACION("CSELPAIS","No existe pais"),COMBOX("CSELCOMBPAIS"),AUXILIAR
CAMPO=DESPAIS,AUXILIAR,NOENTER
CAMPO=PALETS,POSTCHANGE=FDESIGNACION("CACTNUMBUL","Error actualizando número de bultos")
CAMPO=CAJAS,POSTCHANGE=FDESIGNACION("CACTNUMBUL","Error actualizando número de bultos")
CAMPO=BULTOS,NOENTER,AUXILIAR
CAMPO=CODPROV,POSTCHANGE=FDESIGNACION("+CSELDESPROV","No existe provincia"),COMBOX("CSELCOMBPROV"),COMBOXREGPAG=20,AUXILIAR
CAMPO=DESPROV,AUXILIAR,NOENTER
CAMPO=KILOS
CAMPO=STATUS,PROTECT("SUPERVISOR"),POSTCHANGE=FDESIGNACION("CSELSTATUS","No existe estado"),COMBOX("CSELCOMBOST")
CAMPO=DESSTATUS,AUXILIAR,NOENTER
CAMPO=OBSERV,REGPAG=4,INCLUDECSS="border-style:inset;border-width:2px;background-color:#FBE9C0"
CAMPO=CODOPECREA,NOUPDATE
CAMPO=FECCREA,NOUPDATE,COMBOX("CALENDARIO")
CAMPO=HORACREA,NOUPDATE
CAMPO=CODOPEDESCARGA
CAMPO=FECDESCARGA,COMBOX("CALENDARIO")
CAMPO=HORADESCARGA
CAMPO=CODOPEFINDESCARGA
CAMPO=FECFINDESCARGA,COMBOX("CALENDARIO")
CAMPO=HORAFINDESCARGA
CAMPO=CODOPEFIN,NOUPDATE
CAMPO=FECFIN,NOUPDATE,COMBOX("CALENDARIO")
CAMPO=HORAFIN,NOUPDATE
CAMPO=CODOPEMODIF,NOUPDATE
CAMPO=FECMODIF,NOUPDATE,COMBOX("CALENDARIO")
CAMPO=HORAMODIF,NOUPDATE
CAMPO=NBULTO,AUXILIAR,NOUPDATE,OCULTO,"@L@"

CAMPO=DUMMY,AUXILIAR,OCULTO,NOUPDATE,"@@@"
CAMPO=MENSAJE,AUXILIAR,NOUPDATE,OCULTO,"_100_"

CURSOR=CDIVNULL SELECT :CODDIV FROM DUAL WHERE :CODDIV IS NULL;
CURSOR=CVERIFDESPROVE SELECT :DESPROVE DESPROVE FROM DUAL WHERE :DESPROVE IS NOT NULL;
CURSOR=CVERIFREFDOCUMENTO SELECT :CODORDREC CODORDREC FROM DUAL WHERE :CODORDREC IS NOT NULL;
CURSOR=CVERIFTRANSPORTE SELECT :CODAGE FROM DUAL WHERE :CODAGE IS NOT NULL;

CURSOR=CVERIFCODOPECREA SELECT :CODOPECREA FROM DUAL WHERE :CODOPECREA IS NOT NULL;
CURSOR=CVERIFFECHAYHORA SELECT 1 DUMMY FROM DUAL WHERE (:FECCREA IS NOT NULL) AND (:HORACREA IS NOT NULL);

CURSOR=CSELINICIALIZACAMPOS SELECT 0 NUMETIQUETAS FROM DUAL;

CURSOR=CSELNUMETIQUETAS SELECT :NUMETIQUETAS NUMETIQUETAS FROM DUAL WHERE :NUMETIQUETAS > 0;

CURSOR=CLISTAUSUARIOS SELECT NOMBRE
                      FROM (SELECT 0 NUM, NOMBRE||' '||APELLIDO1 NOMBRE FROM VDUSUARIO WHERE CODOPE=VDUSER.GETUSER
                            UNION
                            SELECT 1 NUM, NOMBRE||' '||APELLIDO1 NOMBRE FROM VDUSUARIO WHERE CODOPE <> VDUSER.GETUSER)
                      ORDER BY NUM, NOMBRE;

CURSOR=CACTNUMBUL SELECT NVL(:PALETS,0) + NVL(:CAJAS,0) BULTOS FROM DUAL;

CURSOR=CLISTADIVIS SELECT CODDIV, DESDIV FROM VDDIVIS ORDER BY DECODE(CODDIV,NULL,1,0),CODDIV;

CURSOR=CSELDIVIS SELECT DESDIV FROM VDDIVIS WHERE NVL(CODDIV,'-') = NVL(:CODDIV,'-');

CURSOR=CSELCOMBOST SELECT STATUS,DESSTATUS FROM VDSTATUS WHERE TIPOSTATUS = 'PRT' ORDER BY STATUS;

CURSOR=CSELCOMBPAIS SELECT CODPAIS,DESPAIS FROM VDPAIS ORDER BY DESPAIS;

CURSOR=CSELCOMBPROV SELECT DISTINCT CODPROV,DESPROV,PROV.CODPAIS,DESPAIS FROM VDPROVI PROV, VDPAIS PA 
                             WHERE PA.CODPAIS = :CODPAIS AND PROV.CODPAIS=PA.CODPAIS ORDER BY DECODE(CODPAIS,:CODPAIS,0,1);
                             
CURSOR=CSELPAIS SELECT DESPAIS FROM VDPAIS WHERE CODPAIS=:CODPAIS AND :CODPAIS IS NOT NULL
                UNION SELECT ' ' FROM DUAL WHERE :CODPAIS IS NULL;

CURSOR=CSELDESPROV SELECT DESPROV FROM VDPROVI PROV, VDPAIS PA 
                             WHERE PROV.CODPAIS=PA.CODPAIS AND CODPROV=:CODPROV AND PROV.CODPAIS=:CODPAIS;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='PRT';


CURSOR=CSELOPEMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF
                    FROM DUAL;
             

CURSOR=CCHECKPROTO SELECT TO_NUMBER(:CODPROTO) CODPROTO FROM DUAL WHERE TO_NUMBER(:CODPROTO) > 0;

CURSOR=CFINPROTO UPDATE VDPROTOCOLO 
                    SET STATUS=VDST.FPRTCERRADO,
                        CODOPEMODIF=VDUSER.GETUSER,
                        FECMODIF=VD.FECHASYS,
                        HORAMODIF=VD.HORASYS,
                        CODOPEFIN=VDUSER.GETUSER,
                        FECFIN=VD.FECHASYS,
                        HORAFIN=VD.HORASYS
                  WHERE CODPROTO = :CODPROTO;

CURSOR=CSELFIN SELECT :STATUS FROM DUAL WHERE :STATUS>100;

CURSOR=CIMPREPROTOCOLO SELECT :CODPROTO FROM DUAL WHERE VD.GETPROP('IMPRIMEPROTOCOLO')='S';

CURSOR=CBORRABULTO SELECT 0 NBULTO FROM DUAL;

CURSOR=CSELNBULTO SELECT TO_NUMBER(:NBULTO)+1 NBULTO FROM DUAL
                    WHERE :NBULTO<:NUMETIQUETAS;
                      
CURSOR=CCOMPANULA SELECT :CODPROTO
                  FROM VDORDRECCAB
                  WHERE CODORDREC = TO_CHAR(:CODORDREC)
                    AND CODDIV = :CODDIV				  
                    AND STATUS < 2000;
                  
CURSOR=CANULA BEGIN
                UPDATE VDPROTOCOLO 
				  SET STATUS = 700, 
				      CODOPEMODIF = VDUSER.GETUSER, 
					  FECMODIF = VD.FECHASYS, 
					  HORAMODIF = VD.HORASYS
                WHERE CODPROTO = :CODPROTO;
              END;@
				   
#IMPRIMIR ETIQUETAS
TECLA=SF4,FEJECUTA("CSELNUMETIQUETAS","EL NUMERO DE ETIQUETAS A IMPRIMIR ES CERO",
#                   "CBORRABULTO","",
#                  FWHILE("CSELNBULTO",
#                         FIMPRIME("ETIQ","VDPROTOCOLO.GEN;VDPROTOCOLO.VSQ;CSELPROTO","CODPROTO=:CODPROTO;NBULTO=:NBULTO;NUMETIQUETAS=:NUMETIQUETAS",""),":V10ERROR"),":V10ERROR",
                   FIMPRIME("ETIQ","VDPROTOCOLO.GEN;VDPROTOCOLO.VSQ;CSELPROTO","CODPROTO=:CODPROTO;NBULTO=:NBULTO;NUMETIQUETAS=:NUMETIQUETAS",""),":V10ERROR",
                   FCOMMIT,"",
                   %FFAILURE,"Recoja etiquetas")                                      

#IMPRIMIR PROTOCOLO
TECLA=SF11,FEJECUTA(FIMPRIME("INFORME","VDPROTOCOLO.RPT","CODPROTO=:CODPROTO",""),":V10ERROR",FCOMMIT,"")

#ANULAR PROTOCOLO
TECLA=SF12,FDESIGNACION("CCHECKPROTO","DEBE SELECCIONAR UN PROTOCOLO",
                        "-CCOMPANULA","Existe recepción activa\nNo se permite su anulación",
                        "CANULA", "Error anulando protocolo",
                        FCOMMIT,"",
                        %FFAILURE,"Protocolo :CODPROTO Anulado",
                        FPULSATECLAS("CF2","CF2","F2"),"")

#CERRAR PROTOCOLO				  
TECLA=SF6,FDESIGNACION(FIF("CCOMPRUEBASTATUS",FEJECUTA("CVALCONTENIDO","", 
										               "!CVERERROR",":MENSAJE",
													   "CFINPROTO","Error cerrando protocolo",
													   FCOMMIT,"",
													   %FFAILURE,"Protocolo :CODPROTO cerrado",
													   FPULSATECLAS("CF2","CF2","F2"),""),
                                              FEJECUTA(%FFAILURE,"El protocolo ya está cerrado")),
	                   "Protocolo :CODPROTO NO cerrado. ")

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

CURSOR=CVERERROR SELECT :MENSAJE FROM DUAL WHERE :MENSAJE IS NULL;

CURSOR=CSELDATOSPROVE SELECT 
                      NVL(:DESPROVE,DESPROVE)     DESPROVE,
					  NVL(:TIPOPROVE,TIPOPROVE)   TIPOPROVE,
                      NVL(:CONTACTO,CONTACTO)     CONTACTO,
					  NVL(:DIRECCION,DIRECCION)   DIRECCION,
                      NVL(:DIRECCION1,DIRECCION1) DIRECCION1,
					  NVL(:DIRECCION2,DIRECCION2) DIRECCION2,
					  NVL(:DIRECCION3,DIRECCION3) DIRECCION3,
                      NVL(:POBLACION,POBLACION)   POBLACION,
					  NVL(:TELEFONO,TELEFONO)     TELEFONO,
                      NVL(:CODPAIS,PAI.CODPAIS)   CODPAIS,
					  NVL(:DESPAIS,PAI.DESPAIS)   DESPAIS,
					  NVL(:CODPROV,PRO.CODPROV)   CODPROV,
					  NVL(:DESPROV,PRO.DESPROV)   DESPROV
				FROM VDPROVEEDOR PROVE
				LEFT OUTER JOIN VDPAIS PAI ON
                     PROVE.CODPAIS = PAI.CODPAIS
                LEFT OUTER JOIN VDPROVI PRO ON
                     PROVE.CODPROV = PRO.CODPROV AND
                     PROVE.CODPAIS=PRO.CODPAIS   
				WHERE CODPROVE = :CODPROVE;

CURSOR=CLISTAAGENCIAS  SELECT CODAGE||'-'||DESAGE NOMBREAGE
                         FROM VDAGENCIA  
                      ORDER BY DESAGE;  

CURSOR=CSELAREA SELECT CODAREA, DESAREA FROM VDAREA WHERE CODAREA LIKE 'RECEP%';
CURSOR=CACTORDRECEP UPDATE VDORDRECCAB SET CODAREARECEP = :CODAREARECEP, CODOPEMODIF=VDUSER.GETUSER, FECMODIF=VD.FECHASYS, HORAMODIF=VD.HORASYS 
                    WHERE CODORDREC = :CODORDREC AND :CODORDREC IS NOT NULL;				
											  
ONLINE={SF2} Impresion de informe {SF3} Pasa a Excel {SF4} Etiqueta de bulto {F4} Confirmar cambios {F3} Limpiar pantalla {Esc} Salir;             
