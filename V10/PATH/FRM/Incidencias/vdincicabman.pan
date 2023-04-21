# Módulo   : VDINCICAB.PAN
# Función  : DATOS DE CABECERA DE INCIDENCIAS
#
# Creación : 14-09-2009
# Autor    : JCSR
# Fichero generado por el Asistente de Generación de Pantallas V10 
###########################################
# Histórico de cambios:
DATOS DE CABECERA DE INCIDENCIA


  Incidencia: @L@@@@@@@       Núm. incidencia cliente: __________

  

    Tipo Incidencia: _3__ _20__________ Codigo Transacción: _100__________________
    
    Bultos:    _100_______________________________________________________________ 
    Unidades:  _100_______________________________________________________________ 
    Articulos: _100_______________________________________________________________  
  

  Catalogación: _    _100_____________________________ 
  Area:         ____________________
  Motivo:       @L@@@@ _50_________________________________________   
  
  Descripcion:  _4000_______________________________________________________________

  
  Causa:        _500________________________________________________________________ 
  
  Solución:     _500________________________________________________________________ 

  
  Estado:@L@@@  _30____________________  Asignado a _32____ _93_____________________


  
  Fecha incidencia:  ¿D-MM-Y.YY a las ________
  Creada:            ¿D-MM-Y.YY a las ________ 
  Cerrada:           ¿D-MM-Y.YY a las ________    Facturable _1_
                  
  Contacto: _100__________________  Correo Electrónico _100_________________________

  Adjunto:  _1024________________________________________  
  
  Ultima modificación  _32___ ¿D-MM-Y.YY ________ 
  
|

TABLA = VDINCICAB
ORDERBY = CODINCI DESC;

NOINSERT
#PREINSERT = FEJECUTA ( "CSELMODIF","ERROR EN CSELMODIF",
#                       "!-@CCONFIRMAFECHORA", "¿Seguro que desea crear la incidencia sin informar la fecha y/o la hora?",
#                       "CSELCODINCI", " Error seleccionando nuevo código de incidencia ",
#                       "CINSERTAINCI", " No puedo crear la incidencia " )
PREUPDATE = FEJECUTA ( "CSELMODIF","ERROR EN CSELMODIF",
                       "CSELCAT","Obligatorio seleccionar área" )
POSTQUERY = FEJECUTA ( "+CSELHORASINCI", "ERROR CALCULANDO LAS HORAS DE INCIDENCIAS","+CSELFICHERO","")

CURSOR = CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

WFRAME (5,1,600,375,"Datos técnicos","")
WFRAME (15,60,580,115,"Datos del pedido","")
WFRAME (5,380,600,165,"Datos administrativos","")

# LISTA DE CAMPOS DE LA PANTALLA
CAMPO=CODPED,OCULTO,"_20_"
CAMPO=CODDIV,NOENTER,TOOLTIP("Division o compañia del pedido"),OCULTO,"_20"
CAMPO=ANOPED,OCULTO,"@@@@"
CAMPO=SEQPED,OCULTO,"@@@@"
CAMPO=CODCLI,NOENTER,OCULTO,"_20_____"
CAMPO=DESCLI,AUXILIAR, NOENTER, MIXED,OCULTO,"_20_"
CAMPO=PATHINCI,AUXILIAR,OCULTO,"_400_"


################################################### DATOS TECNICOS ################################################### 
CAMPO = CODINCI, NOUPDATE,TITULO ( "INCIDENCIA" ), TOOLTIP ( "CODIGO DE INCIDENCIA" )
CAMPO = CLAVEINCI,OCULTO,"@@@@@@@@@"
CAMPO = CODINCICLI, TITULO("Código de incidencia interno del cliente")

################################################### DATOS TECNICOS ################################################### 
CAMPO=TIPOCLAVEINCI,NOENTER,TOOLTIP("Tipo de la clave de acceso a la incidencia"),POSTCHANGE=FEJECUTA("+CSELTIPOCLAVE","")
CAMPO=DESTIPOCLAVEINCI,AUXILIAR,NOENTER
CAMPO=CODTRA,AUXILIAR,NOENTER
CAMPO=BULTOS,TOOLTIP("Bultos del pedido a los que afecta la incidencia")
CAMPO=UNIDADES,TOOLTIP("Unidades del pedido a las que afecta la incidencia")
CAMPO=ARTICULOS,TOOLTIP("Artículos del pedido a los que afecta la incidencia")

################################################### DATOS TECNICOS ################################################### 
CAMPO = TIPOCAT, TITULO ( "CATALOGACION" ), TOOLTIP ( "TIPO DE CATALOGACION" ),
        POSTCHANGE = FDESIGNACION ("+CSELCATALOGACION", "NO ENCUENTRO CATALOGACIÓN ASOCIADA"), COMBOX ("CSELTIPOCATALOGACION"), COMBOXREADONLY
CAMPO = CATALOGACION, AUXILIAR , NOENTER, MIXED
CAMPO = AREA, TITULO("AREA"),TOOLTIP("AREA ASOCIADA A LA INCIDENCIA"), COMBOX("CSELAREAINCIDENCIA"),COMBOXREADONLY, WLONX=30 
CAMPO = CODCONCEPTO , COMBOX ("CSELCONCEPTOS"), COMBOXREGPAG = 20 , POSTCHANGE = FDESIGNACION ("+CSELDESCCONCEPTO", "")
CAMPO = CONCEPTO, AUXILIAR , NOENTER , TITULO ( "CONCEPTO" )
CAMPO = DESCRIPCION,MIXED, TITULO ( "DESCRIPCION" ), TOOLTIP ( "DESCRIPCION DE LA INCIDENCIA. TEXTO QUE IRÁ EN EL CORREO DE CIERRE" ),REGPAG=3,INCLUDECSS="border-style:inset;border-width:2px;background-color:#FBE9C0"
CAMPO = CAUSA,MIXED, TITULO ( "CAUSA" ), TOOLTIP ( "CAUSA DE LA INCIDENCIA. TEXTO QUE IRÁ EN EL CORREO DE CIERRE" ),REGPAG=2,INCLUDECSS="border-style:inset;border-width:2px;background-color:#FBE9C0"
CAMPO = SOLUCION,MIXED, TITULO ( "SOLUCION" ), TOOLTIP ( "SOLUCION DE LA INCIDENCIA. TEXTO QUE IRÁ EN EL CORREO DE CIERRE" ),REGPAG=3,INCLUDECSS="border-style:inset;border-width:2px;background-color:#FBE9C0"
CAMPO = CAUSAINTER,MIXED, TITULO ( "CAUSA INTERNA" ), TOOLTIP ( "CAUSA DE LA INCIDENCIA QUE NO LE LLEGA AL CONSIGNATARIO" ),OCULTO,"_3000_"
CAMPO = SOLUCIONINTER,MIXED, TITULO ( "SOLUCION INTERNA" ), TOOLTIP ( "SOLUCION DE LA INCIDENCIA QUE NO LE LLEGA AL CONSIGNATARIO" ),OCULTO,"_3000_"
CAMPO = FAQ,MIXED, TITULO ( "F.A.Q." ),OCULTO,"_50_"
CAMPO = DOCUMENTACION, TITULO ( "DOCUMENTACION" ),MIXED,OCULTO,"_250_"
CAMPO = STATUS, TITULO ( "ESTADO" ) , POSTCHANGE = FDESIGNACION ("+CSELDESSTATUS" , "NO ENCUENTRO EL ESTADO"),COMBOX("CLISTASTATUS"),COMBOXREGPAG=6 
CAMPO = DESSTATUS, AUXILIAR , NOENTER
CAMPO = CODOPEASIGNA, COMBOX ("CSELOPEASIG"), COMBOXREADONLY , POSTCHANGE = FDESIGNACION ("+CSELOPEASIGLARGO", "")
CAMPO = OPELARGOASIGNA, AUXILIAR , NOENTER
################################################### DATOS ADMINISTRATIVOS ################################################### 
CAMPO = FECINCIDENCIA,TOOLTIP ("Fecha en la que se ha producido la incidencia.")
CAMPO = HORAINCIDENCIA,TOOLTIP ("Hora en la que se ha producido la incidencia.")
CAMPO = FECCREADO, TITULO ( "CREADO EL" )
CAMPO = HORACREADO
CAMPO = FECCERRADO, TITULO ( "CERRADO EN" ), NOENTER
CAMPO = HORACERRADO, NOENTER
CAMPO = FACTURABLE, TITULO ( "FACTURABLE" ), TOOLTIP ( "INDICA SI ES FACTURABLE (S) O NO (N)"),POSTCHANGE=FVERIFICA(" SN","Los posibles valores son S(i) N(o).")
CAMPO = CONTACTO, TITULO ( "CONTACTO" ), TOOLTIP ( "PERSONA DE CONTACTO" )
CAMPO = CORREOE, TITULO ("CORREO")
CAMPO = ADJUNTO,TITULO("Adjunto"),AUXILIAR,COMBOX("CSELFICH"),POSTCHANGE=FDESIGNACION("+CSELCAMPOHTL","")
CAMPO = CODOPEMODIF, TITULO ( "MODIFICADO POR" ), NOENTER
CAMPO = FECMODIF, NOENTER
CAMPO = HORAMODIF, NOENTER
CAMPO = SEQLINEA, AUXILIAR, OCULTO, "@L@"
CAMPO = TIEMPO, AUXILIAR, OCULTO, "#L#####.##"
CAMPO = HORASINCI, AUXILIAR, OCULTO, "@L@@@"
CAMPO = CODCOMEN, OCULTO, "@L@@@@@@@"
CAMPO = V10HTML,AUXILIAR,OCULTO,"_2048_"


# PARTE PERSONALIZADA DE LA PANTALLA 
CURSOR=CDESAGE SELECT DESAGE FROM VDAGENCIA WHERE CODAGE=:CODAGE
                UNION 
               SELECT NULL DESAGE FROM DUAL WHERE :CODAGE IS NULL;
			   
CURSOR=CDESDIV SELECT DESDIV
                 FROM VDDIVIS
                WHERE CODDIV=:CODDIV;

CURSOR = CSELHORASINCI SELECT NVL(MAX(TIEMPO),0) TIEMPO FROM
                       (SELECT SUM(NVL(INO.TIEMPO,0))/60 TIEMPO
                          FROM VDINCICAB INC, VDINCILIN INL, VDINCILINOPE INO
                         WHERE     INC.CODINCI = INL.CODINCI
                               AND INC.CODCLI = :CODCLI
                               AND INC.FACTURABLE IS NULL
                               AND INO.FACTURABLE IS NULL
                               AND INO.CODINCI = INC.CODINCI
                               AND INL.SEQLINEA = INO.SEQLINEA
                               AND :STATUS BETWEEN VDST.FICDCREADA AND VDST.FICDPROYECTOS);

CURSOR = CSELOPEASIG SELECT USU.CODOPE USUARIO,  NOMBRE || ' ' || APELLIDO1 || ' ' || APELLIDO2 NOMBRE
                       FROM VDUSUARIO USU;
					  
CURSOR = CSELOPEASIGLARGO SELECT  NOMBRE || ' ' || APELLIDO1 || ' ' || APELLIDO2 OPELARGOASIGNA
                            FROM VDUSUARIO WHERE CODOPE = :CODOPEASIGNA;

CURSOR = CSELDESCLIENTE SELECT DESCLIENTE DESCLI FROM VDCLIENTES WHERE CODCLIENTE = :CODCLI;

CURSOR = CSELDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS = :STATUS AND TIPOSTATUS = 'ICD';

CURSOR = CSELCATALOGACION SELECT CATALOGACION FROM VDCATALOGACION WHERE TIPO = :TIPOCAT;

CURSOR = CSELCONCEPTOS SELECT CODCONCEPTO COD, GRUPOCONCEPTO || ' - ' || CONCEPTO CONCEPTO FROM VDINCICONCE ORDER BY GRUPOCONCEPTO, CODCONCEPTO;

CURSOR = CSELDESCCONCEPTO SELECT GRUPOCONCEPTO || ' - ' || CONCEPTO CONCEPTO  FROM VDINCICONCE WHERE CODCONCEPTO = :CODCONCEPTO;

CURSOR = CSELTIPOCATALOGACION SELECT TIPO, CATALOGACION FROM VDCATALOGACION;

CURSOR = CSELCONTACTOSCLI SELECT NOMBRE CONTACTO FROM VDCONTACTOSCLI WHERE CODCLI = :CODCLI;

CURSOR = CVERIFICACAUSA SELECT :CAUSA FROM DUAL WHERE :CAUSA IS NOT NULL;

CURSOR = CSELVERIFSOLUCION SELECT :SOLUCION FROM DUAL WHERE :SOLUCION IS NOT NULL;

CURSOR = CACTUALIZASTATUS UPDATE VDINCICAB SET STATUS = VDST.FICDFACTURAN,
												FECCERRADO = VD.FECHASYS, HORACERRADO = VD.HORASYS
								WHERE CODINCI = :CODINCI;
								
CURSOR = CVERIFSTPARAFACTURAR SELECT :STATUS FROM DUAL WHERE :STATUS IN (VDST.FICDASIGNA, VDST.FICDCREADA, VDST.FICDCERRADA);

CURSOR = CINSERTALINEA INSERT ALL 
						INTO VDINCILIN (CODINCI, SEQLINEA, ACTUACION, CODOPEMODIF) 
						VALUES (:CODINCI, SEQLINEA, 'Se envía la incidencia a facturar al darla por buena', VDUSER.GETUSER)
						INTO VDINCILINOPE (CODINCI, SEQLINEA, CODOPE, TIEMPO, CODOPEMODIF)
						VALUES ( :CODINCI, SEQLINEA, VDUSER.GETUSER, 0, VDUSER.GETUSER)
						SELECT MAX(SEQLINEA)+1 SEQLINEA 
						  FROM VDINCILIN 
						WHERE CODINCI = :CODINCI;

CURSOR = CGENERACORREO BEGIN VDESCRIBECORREOS.CORREO_FACTURAINCI(:CODINCI); END;@

CURSOR = CVERIFICAFACTURA SELECT DISTINCT :CODINCI
                            FROM VDINCICAB INC, VDINCILINOPE INO 
						   WHERE INC.CODINCI = :CODINCI AND 
						         INO.CODINCI = INC.CODINCI AND 
                                 (INC.FACTURABLE = 'S' OR INO.FACTURABLE = 'S'); 



# Facturar
TECLA = F8, FEJECUTA ("CVERIFICACAUSA", " Por favor, indique la causa de la incidencia... ",
                      "CSELVERIFSOLUCION", " Por favor, informe la solución... ",
					            "CVERIFICAFACTURA", " La incidencia es facturable \n Por favor, indique los datos de facturación.  ",
					            "CVERIFSTPARAFACTURAR", " El estado de la incidencia no es el correcto para mandar a facturar.",
					            "CACTUALIZASTATUS", " No he podido informar el estado correspondiente ",
					            "CINSERTALINEA", " No puedo insertar línea de incidencia", 
					            FCOMMIT, "", %FFAILURE, " Incidencia enviada a facturación", FPULSATECLAS ("F5","CF2","CF2","F2", ""))

#					            "CGENERACORREO", " No he podido generar correo de aviso de facturación",
#					            "CGENERACORREOCIERRE", "No he podido generar el correo de aviso de cierre de incidencia",

CURSOR = CACTSTATUSANULA UPDATE VDINCICAB SET STATUS = VDST.FICDANULADA,
						FECCERRADO = VD.FECHASYS, HORACERRADO = VD.HORASYS  
						WHERE CODINCI = :CODINCI;

CURSOR = CINSERTALINEAANULA INSERT ALL 
						INTO VDINCILIN (CODINCI, SEQLINEA, ACTUACION, CODOPEMODIF) 
						VALUES (:CODINCI, SEQLINEA, 'Se anula la incidencia', VDUSER.GETUSER)
						INTO VDINCILINOPE (CODINCI, SEQLINEA, CODOPE, TIEMPO, CODOPEMODIF)
						VALUES ( :CODINCI, SEQLINEA, VDUSER.GETUSER, 0, VDUSER.GETUSER)
						SELECT MAX(SEQLINEA)+1 SEQLINEA 
						  FROM VDINCILIN 
						WHERE CODINCI = :CODINCI;

# ANULAR INCIDENCIA
TECLA = AF8, FEJECUTA ("CACTSTATUSANULA", " No he podido poner el estado correspondiente ",
					             "CINSERTALINEAANULA", " No puedo insertar línea de incidencia",
					             FEJECUTAFORM ("VDINSERTALINEAINCI", "S", "", "CODINCI=:CODINCI", "", "", "N"), "",
					             FCOMMIT, "", %FFAILURE, " Incidencia anulada correctamente",  FPULSATECLAS ("F5","CF2","CF2","F2", ""))

CURSOR = CACTSTATUSCIERRA UPDATE VDINCICAB SET STATUS = VDST.FICDCERRADA,
							FECCERRADO = VD.FECHASYS, HORACERRADO = VD.HORASYS WHERE CODINCI = :CODINCI;

CURSOR = CINSERTALINEACIERRA INSERT ALL 
						INTO VDINCILIN (CODINCI, SEQLINEA, ACTUACION, CODOPEMODIF) 
						VALUES (:CODINCI, SEQLINEA, 'Se cierra la incidencia.', VDUSER.GETUSER)
						INTO VDINCILINOPE (CODINCI, SEQLINEA, CODOPE, TIEMPO, CODOPEMODIF)
						VALUES ( :CODINCI, SEQLINEA, VDUSER.GETUSER, 0, VDUSER.GETUSER)
						SELECT MAX(SEQLINEA)+1 SEQLINEA 
						  FROM VDINCILIN 
						WHERE CODINCI = :CODINCI;

CURSOR = CGENERACORREOCIERRE BEGIN VDESCRIBECORREOS.CORREO_CIERRE(:CODINCI); END;@

#CERRAR INCIDENCIA

CURSOR = CVERIFSTPARACERRAR SELECT :STATUS FROM DUAL WHERE :STATUS IN (VDST.FICDASIGNADA, VDST.FICDCREADA);


TECLA = CF7, FEJECUTA ("CVERIFICACAUSA", " No tiene mucho sentido cerrar la incidencia \n si no se sabe la causa... ",
					             "CSELVERIFSOLUCION", " No tiene mucho sentido cerrar la incidencia \n si no se ha puesto solución... ",
					             "-CVERIFICAFACTURA", " Esta incidencia tiene entradas facturables. ",
					             "CVERIFSTPARACERRAR", " El estado de la incidencia no es el correcto para cerrarla.",
					             "CACTSTATUSCIERRA", " No he podido poner el estado correspondiente ",
					             "CINSERTALINEACIERRA", " No puedo insertar línea de incidencia ",
					             FCOMMIT, "", %FFAILURE, " Incidencia cerrada correctamente ", FPULSATECLAS ("F5","CF2","CF2","F2", ""))

#					             "CGENERACORREOCIERRE", " No he podido generar correo de cierre de incidencia ",

#PEDIR INFORMACION
TECLA = F7, FEJECUTA (FEJECUTAFORM("VDREQINFO", "N", "", "CODINCI=:CODINCI", "", "TEXTO DEL CORREO PARA LA INCIDENCIA :CODINCI", ""), "",
                      FPULSATECLAS ("F5", "CF2", "CF2", "F2"), "")

TECLA = SF6, FEJECUTA (%FFAILURE, ":CODINCI")
					  
CURSOR = CINSERTALINEAASIGNA INSERT ALL 
						INTO VDINCILIN (CODINCI, SEQLINEA, ACTUACION, CODOPEMODIF) 
						VALUES (:CODINCI, SEQLINEA, VDUSER.GETUSER||' asigna la incidencia a '|| :CODOPEASIGNA, VDUSER.GETUSER)
						INTO VDINCILINOPE (CODINCI, SEQLINEA, CODOPE, TIEMPO, CODOPEMODIF)
						VALUES ( :CODINCI, SEQLINEA, VDUSER.GETUSER, 0, VDUSER.GETUSER)
						SELECT MAX(SEQLINEA)+1 SEQLINEA 
						  FROM VDINCILIN 
						WHERE CODINCI = :CODINCI;

CURSOR = CUPDASTATUSASIGNA UPDATE VDINCICAB SET STATUS = VDST.FICDASIGNADA WHERE CODINCI = :CODINCI;

CURSOR = CGENERACORREOASIGNA BEGIN VDESCRIBECORREOS.CORREO_ASIGNA_INCI(:CODINCI); END;@

CURSOR = CUPDAUSUARIO UPDATE VDINCICAB SET CODOPEASIGNA=:CODOPEASIGNA WHERE CODINCI = :CODINCI;

#ASIGNAR INCIDENCIA
#TECLA = CF8, FEJECUTA ("CUPDAUSUARIO", "ERROR ACTUALIZANDO", FCOMMIT, "", 
#                       "CINSERTALINEAASIGNA", " No puedo insertar línea de incidencia",
#					   "CUPDASTATUSASIGNA", " No puedo actualizar el estado de la incidencia", 
#					   FCOMMIT, "", %FFAILURE, " Incidencia asignada correctamente",  
#					   FPULSATECLAS ("F5","CF2","CF2","F2"), "")


#imprimir
TECLA = CF1, FEJECUTA (FIMPRIME("INFORME","VDINCIDENCIA.rpt","CODINCI=:CODINCI",""), "Error imprimiendo incidencia")

#DATOS DEL CLIENTE
TECLA = CF6, FEJECUTA (FEJECUTAFORM("VDCONTACTOSCLI", "S", "CODCLI=:CODCLI", "", "","", "S"), "",
                      FPULSATECLAS ("F5", "CF2", "CF2", "F2"), "")

#CREACION DE INCIDENCIA
CURSOR = CCONFIRMAFECHORA SELECT :HORACREADO FROM DUAL WHERE :HORACREADO IS NULL OR :FECCREADO = 0;

CURSOR = CSELCODINCI SELECT VDSECNUMINCI.NEXTVAL CODINCI FROM DUAL;

CURSOR = CINSERTAINCI INSERT ALL
					              INTO VDINCICAB (CODINCI, CODCLI, CODINCICLI, DESCRIPCION, TIPOCAT, CODCONCEPTO, GRAVEDAD, DOCUMENTACION, 
					                              CAUSAINTER, SOLUCIONINTER, FAQ, CAUSA, SOLUCION, STATUS, CODOPEMODIF, 
									              FECMODIF, HORAMODIF, CONTACTO, CORREOE, CODOPEASIGNA, CODINST, FECCREADO, HORACREADO, 
												  CLAVEINCI, TIPOCLAVEINCI,
												  CODDIV,CODAGE,CODEMP,CODPED,BULTOS,UNIDADES,ARTICULOS,ORIGEN,AREA,FECINCIDENCIA ) 
                                VALUES (:CODINCI, :CODCLI, NULL, :DESCRIPCION, :TIPOCAT, :CODCONCEPTO, 0, :DOCUMENTACION,
                                        :CAUSAINTER, :SOLUCIONINTER, :FAQ, :CAUSA, :SOLUCION,
   									                    DECODE (:CODOPEASIGNA, NULL, VDST.FICDCREADA, VDST.FICDASIGNADA), 
									                      CODOPEMODIF, FECMODIF, HORAMODIF, :CONTACTO, :CORREOE, :CODOPEASIGNA, NULL,
                                        DECODE(:FECCREADO, 0, FECMODIF, :FECCREADO), NVL(:HORACREADO, HORAMODIF), NVL(:CLAVEINCI,0),:TIPOCLAVEINCI,
                                        :CODDIV,:CODAGE,:CODEMP,:CODPED,:BULTOS,:UNIDADES,:ARTICULOS,:ORIGEN,:AREA,:FECINCIDENCIA)
      					        INTO VDINCILIN (CODINCI, SEQLINEA, FECHA, HORA, ACTUACION, CODOPEMODIF, FECMODIF, HORAMODIF)
                                VALUES (:CODINCI, 1, DECODE(:FECCREADO, 0, FECMODIF, :FECCREADO), NVL(:HORACREADO, HORAMODIF), 
									                      'EL OPERARIO ' || CODOPEMODIF || ' CREA LA INCIDENCIA', CODOPEMODIF, FECMODIF, HORAMODIF)
					              INTO VDINCILINOPE (CODINCI, SEQLINEA,CODOPE, TIEMPO, CODOPEMODIF, FECMODIF, HORAMODIF, FACTURABLE)
                                   VALUES (:CODINCI, 1, CODOPEMODIF, 1, CODOPEMODIF, FECMODIF, HORAMODIF, 'N')
					            SELECT  VDUSER.GETUSER CODOPEMODIF ,VD.FECHASYS FECMODIF ,VD.HORASYS HORAMODIF  FROM DUAL;

CURSOR=CLISTASTATUS SELECT STATUS,DESSTATUS FROM VDSTATUS WHERE TIPOSTATUS='ICD' AND STATUS>0 ORDER BY STATUS;

CURSOR=CSELAREAINCIDENCIA SELECT AREA FROM VDINCIAREA;

CURSOR=CSELFICH SELECT UPPER(COMENTARIO) ADJUNTO 
                       FROM VDCOMEN WHERE CODCOMEN=:CODCOMEN 
                                      AND TIPOCOMEN='FICHEROS' 
                                      ORDER BY LINCOMEN DESC;                         

CURSOR=CSELFICHERO SELECT UPPER(COMENTARIO) ADJUNTO 
                       FROM VDCOMEN WHERE CODCOMEN=:CODCOMEN 
                                      AND TIPOCOMEN='FICHEROS' 
                                      ORDER BY LINCOMEN DESC;                         

CURSOR=CSELCAMPOHTL BEGIN
                        IF :ADJUNTO IS NOT NULL THEN
                         SELECT '<table id="tablaSubida" width="1400" style="position:absolute;top:392px;left:-120px;z-index:9000" cellpadding="0" cellspacing="5">
                                  <tr height="10">
                                    <input type="image" title="Visualizar fichero adjunto" src="ojo.jpg" style="position:absolute;top:575px;left:418px;height:20px;width:20px;border-color:blue " 
                                       onClick="window.open(location.href='||''''||VD.GETPROP('SERVERINCI')||'/'||:CODINCI||'/'||:ADJUNTO||''',''window'',''params'');" value="Ver Adjunto">                                 
                                  </tr>
                                 </table>' INTO :V10HTML FROM DUAL;
                        END IF;
                    END;@

CURSOR=CSELCAT SELECT :AREA FROM DUAL WHERE :AREA IS NOT NULL OR (:AREA IS NULL AND :TIPOCAT!='I');

CURSOR=CSELTIPOCLAVE BEGIN
	                   CASE :TIPOCLAVEINCI
					      WHEN 'PEC' THEN 
						      SELECT 'PEDIDO' INTO :DESTIPOCLAVEINCI FROM DUAL;
							  SELECT CODPED||' - '||CODDIV INTO :CODTRA FROM VDPEDIDOCAB WHERE CLAVEINCI=:CLAVEINCI;
						  ELSE NULL;
						END CASE;  
                      END;@
					
CURSOR=CVERPATH SELECT VD.GETPROP('PATHADJUNTOS')||:CODINCI||'//' PATHINCI FROM DUAL;

TECLA=CF8,FEJECUTA("CVERPATH","ERROR AL VER EL PATH DE FICHEROS ADJUNTO PARA INCIDENCIAS",
                   FEJECUTAFORM("XVDUPLOAD","N","","CODCOMEN=:CODCOMEN CODTABLA='VDINCICAB' PATHFICHERO=:PATHINCI","","","S"))

CONTEXTUAL=FEJECUTA(FSWITCHCADENA(":TIPOCLAVEINCI",
                                  "PEC",FEJECUTAFORM("VDPEDIDOS","S","CLAVEINCI=:CLAVEINCI"),
								  "ORC",FEJECUTAFORM("VDORDENESRECEP","S","CLAVEINCI=:CLAVEINCI")),"IMPOSIBLE EJECUTAR OPCION")
