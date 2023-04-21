# Módulo   : VDINCICAB.PAN
# Función  : DATOS DE CABECERA DE INCIDENCIAS
#
# Creación : 14-09-2009
# Autor    : JCSR
# Fichero generado por el Asistente de Generación de Pantallas V10 
###########################################
# Histórico de cambios:
DATOS DE CABECERA DE INCIDENCIA


  Incidencia:        @L@@@@@@@                 Núm. incidencia cliente: __________
  Nº de incidencias: @@@ / @@@

  
    Pedido:    _20_________  Cliente: _20_______ _________________________________ 
    División:  _4__  _40_____________________________________                
    Agencia:   __________ _30___________________________                     
    Bultos:    _100_______________________________________________________________ 
    Unidades:  _100_______________________________________________________________ 
    Articulos: _100_______________________________________________________________  
  
  Catalogación: _    _100_____________________________ 
  Area:         ____________________
  Motivo:       @L@@@@ _50_________________________________________   
  
  Descripcion:  _4000_______________________________________________________________

  
  Causa:        _500________________________________________________________________ 
  
  Solución:     _500________________________________________________________________ 

  
  Estado:@L@@@  _30_____________________ Asignado a _32____ _93_____________________
  


  Fecha incidencia:  ¿D-MM-Y.YY a las ________
  Creada:            ¿D-MM-Y.YY a las ________ 
  Cerrada:           ¿D-MM-Y.YY a las ________   Facturable _1_
  
  Contacto: _100__________________  Correo Electrónico _100_________________________
  
  Adjunto:  _1024________________________________________  
  
  Ultima modificación  _32___ ¿D-MM-Y.YY ________ 

|

TABLA = VDINCICAB
ORDERBY = CODINCI DESC;

PREINSERT = FEJECUTA ( "+CSELSTATUS","",
                       "CSELMODIF","ERROR EN CSELMODIF",
                       "CSELCREA","ERROR EN CSELCREA",
					   "CSELCAT","Obligatorio seleccionar área",
                       "CSELCODINCI", " Error seleccionando nuevo código de incidencia",
					   "+CSELSEQINCI",""
					   )
					   
PREUPDATE = FEJECUTA ( "CSELMODIF","ERROR EN CSELMODIF",
                       "CSELCAT","Obligatorio seleccionar área" )
POSTQUERY = FEJECUTA ("+CSELHORASINCI", "ERROR CALCULANDO LAS HORAS DE INCIDENCIAS",
                      "+CSELFICHERO","",
					  "+CSELNUMINCI","")

CURSOR = CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CSELSTATUS SELECT DECODE(:STATUS,0,100,:STATUS) STATUS FROM DUAL;
WLONX=630
WFRAME (5,1,600,375,"Datos técnicos","")
WFRAME (15,60,580,115,"Datos del pedido","")
WFRAME (5,380,600,165,"Datos administrativos","")

# LISTA DE CAMPOS DE LA PANTALLA
################################################### DATOS TECNICOS ################################################### 
CAMPO = CODINCI, NOENTER,TITULO ( "INCIDENCIA" ), TOOLTIP ( "CODIGO DE INCIDENCIA" )
#CAMPO = INCIHARD, NOUPDATE,TITULO ( "INCI. HARD." ), TOOLTIP ( "INCIDENCIA HARDWARE EN EL CASO QUE LA HUBIERA" )
#CAMPO = CLAVEINCI,NOENTER,VIRTUAL,TITULO("Clave de acceso a la incidencia"), TOOLTIP("Clave de acceso a la incidencia")
CAMPO = CLAVEINCI,VIRTUAL,OCULTO
CAMPO = TIPOCLAVEINCI,NOENTER,VIRTUAL,TOOLTIP("Tipo de la clave de acceso a la incidencia"),OCULTO

CAMPO=CODINCICLI, TITULO("Código de incidencia interno del cliente")
CAMPO=SEQCLAVEINCI,NOENTER
CAMPO=NUMINCI,AUXILIAR,NOENTER

################################################### DATOS TECNICOS ################################################### 
CAMPO=CODPED,VIRTUAL,NOENTER,TOOLTIP("Código del pedido")
CAMPO=CODCLI,VIRTUAL,NOENTER
CAMPO=ANOPED,VIRTUAL,OCULTO
CAMPO=SEQPED,VIRTUAL,OCULTO
CAMPO=DESCLI,AUXILIAR,VIRTUAL, NOENTER, MIXED
CAMPO=CODDIV,VIRTUAL,NOENTER,TOOLTIP("Division o compañia del pedido")
CAMPO=DESDIV,VIRTUAL,AUXILIAR,NOENTER
CAMPO=CODAGE,VIRTUAL,NOENTER,TOOLTIP("Es el código de la agencia que transportará el pedido. Deberá existir en la tabla de agencias")
CAMPO=DESAGE,VIRTUAL,AUXILIAR,NOENTER,TOOLTIP("Descripción de la agencia de transporte")
CAMPO=BULTOS,TOOLTIP("Bultos del pedido a los que afecta la incidencia")
CAMPO=UNIDADES,TOOLTIP("Unidades del pedido a las que afecta la incidencia")
CAMPO=ARTICULOS,TOOLTIP("Artículos del pedido a los que afecta la incidencia")
CAMPO=ORIGEN,OCULTO,"_14_"
CAMPO=CODEMP,OCULTO,"_3_"

################################################### DATOS TECNICOS ################################################### 
CAMPO = TIPOCAT, TITULO ( "CATALOGACION" ), TOOLTIP ( "TIPO DE CATALOGACION" ),
        POSTCHANGE = FDESIGNACION ("+CSELCATALOGACION", "NO ENCUENTRO CATALOGACIÓN ASOCIADA"), COMBOX ("CSELTIPOCATALOGACION"), COMBOXREADONLY
CAMPO = CATALOGACION, AUXILIAR , NOENTER, MIXED
CAMPO = AREA, TITULO("AREA"),TOOLTIP("AREA ASOCIADA A LA INCIDENCIA"),COMBOX("CSELAREAINCIDENCIA"),COMBOXREADONLY, WLONX=30 
CAMPO = CODCONCEPTO , COMBOX ("CSELCONCEPTOS"), COMBOXREGPAG = 20, POSTCHANGE = FDESIGNACION ("+CSELDESCCONCEPTO", "")
CAMPO = CONCEPTO, AUXILIAR , NOENTER , TITULO ( "CONCEPTO" )
CAMPO = DESCRIPCION,MIXED,TITULO ( "DESCRIPCION" ),TOOLTIP ( "DESCRIPCION DE LA INCIDENCIA. TEXTO QUE IRÁ EN EL CORREO DE CIERRE" ),REGPAG=3,INCLUDECSS="border-style:inset;border-width:2px;background-color:#FBE9C0"
CAMPO = CAUSA,MIXED, TITULO ( "CAUSA" ), TOOLTIP ( "CAUSA DE LA INCIDENCIA. TEXTO QUE IRÁ EN EL CORREO DE CIERRE" ),REGPAG=2,INCLUDECSS="border-style:inset;border-width:2px;background-color:#FBE9C0"
CAMPO = SOLUCION,MIXED, TITULO ( "SOLUCION" ), TOOLTIP ( "SOLUCION DE LA INCIDENCIA. TEXTO QUE IRÁ EN EL CORREO DE CIERRE" ),REGPAG=3,INCLUDECSS="border-style:inset;border-width:2px;background-color:#FBE9C0"
CAMPO = CAUSAINTER,MIXED, TITULO ( "CAUSA INTERNA" ), TOOLTIP ( "CAUSA DE LA INCIDENCIA QUE NO LE LLEGA AL CONSIGNATARIO" ),OCULTO,"_3000_"
CAMPO = SOLUCIONINTER,MIXED, TITULO ( "SOLUCION INTERNA" ), TOOLTIP ( "SOLUCION DE LA INCIDENCIA QUE NO LE LLEGA AL CONSIGNATARIO" ),OCULTO,"_3000_"
CAMPO = FAQ,MIXED, TITULO ( "F.A.Q." ),OCULTO,"_50_"
CAMPO = DOCUMENTACION, TITULO ( "DOCUMENTACION" ),MIXED,OCULTO,"_250_"
CAMPO = STATUS, TITULO ( "ESTADO" ) , POSTCHANGE = FDESIGNACION ("+CSELDESSTATUS" , "NO ENCUENTRO EL ESTADO"),COMBOX("CLISTASTATUS")
CAMPO = DESSTATUS, AUXILIAR , NOENTER
CAMPO = CODOPEASIGNA, COMBOX ("CSELOPEASIG"), COMBOXREADONLY , POSTCHANGE = FDESIGNACION ("+CSELOPEASIGLARGO", "")
CAMPO = OPELARGOASIGNA, AUXILIAR , NOENTER
################################################### DATOS ADMINISTRATIVOS ################################################### 
CAMPO = FECINCIDENCIA,TOOLTIP ("Fecha en la que se ha producido la incidencia."),COMBOX("CALENDARIO")
CAMPO = HORAINCIDENCIA,TOOLTIP ("Hora en la que se ha producido la incidencia.")
CAMPO = FECCREADO, TITULO ( "CREADO EL" ),COMBOX("CALENDARIO")
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

CURSOR = CSELCONCEPTOS SELECT CODCONCEPTO, GRUPOCONCEPTO || ' - ' || CONCEPTO FROM VDINCICONCE ORDER BY GRUPOCONCEPTO, CODCONCEPTO;

CURSOR = CSELDESCCONCEPTO SELECT GRUPOCONCEPTO || ' - ' || CONCEPTO CONCEPTO  FROM VDINCICONCE WHERE CODCONCEPTO = :CODCONCEPTO;

CURSOR = CSELTIPOCATALOGACION SELECT TIPO, CATALOGACION FROM VDCATALOGACION;

CURSOR = CVERIFICACAUSA SELECT :CAUSA FROM DUAL WHERE :CAUSA IS NOT NULL;

CURSOR = CSELVERIFSOLUCION SELECT :SOLUCION FROM DUAL WHERE :SOLUCION IS NOT NULL;

CURSOR = CACTUALIZASTATUS UPDATE VDINCICAB SET STATUS = VDST.FICDFACTURADA,
												FECCERRADO = VD.FECHASYS, HORACERRADO = VD.HORASYS
								WHERE CODINCI = :CODINCI;
								
CURSOR = CVERIFSTPARAFACTURAR SELECT :STATUS FROM DUAL WHERE :STATUS IN (VDST.FICDASIGNADA, VDST.FICDCREADA, VDST.FICDCERRADA);

CURSOR = CINSERTALINEA INSERT ALL 
						INTO VDINCILIN (CODINCI, SEQLINEA, ACTUACION, CODOPEMODIF) 
						VALUES (:CODINCI, SEQLINEA, 'Se envía la incidencia a facturar al darla por buena', VDUSER.GETUSER)
						INTO VDINCILINOPE (CODINCI, SEQLINEA, CODOPE, TIEMPO, CODOPEMODIF)
						VALUES ( :CODINCI, SEQLINEA, VDUSER.GETUSER, 0, VDUSER.GETUSER)
						SELECT NVL(MAX(SEQLINEA),0)+1 SEQLINEA 
						  FROM VDINCILIN 
						WHERE CODINCI = :CODINCI;

CURSOR = CGENERACORREO BEGIN VDESCRIBECORREOS.CORREO_FACTURAINCI(:CODINCI); END;@

CURSOR = CVERIFICAFACTURA SELECT DISTINCT :CODINCI
                            FROM VDINCICAB INC, VDINCILINOPE INO 
						   WHERE INC.CODINCI = :CODINCI AND 
						         INO.CODINCI = INC.CODINCI AND 
                                 (INC.FACTURABLE = 'S' OR INO.FACTURABLE = 'S'); 



## Facturar
#TECLA = F8, FEJECUTA ("CVERIFICACAUSA", " No tiene mucho sentido mandar la incidencia \n a facturar si no se sabe la causa... ",
#                      "CSELVERIFSOLUCION", " No tiene mucho sentido mandar la incidencia \n a facturar si no se ha puesto solución... ",
#					            "CVERIFICAFACTURA", " No tiene sentido mandar a facturar una incidencia \n sin nada facturable... ",
#					            "CVERIFSTPARAFACTURAR", " El estado de la incidencia no es el correcto para mandar a facturar.",
#					            "CACTUALIZASTATUS", " No he podido poner el estado correspondiente ",
#					            "CINSERTALINEA", " No puedo insertar línea de incidencia", 
#					            FCOMMIT, "", %FFAILURE, " Incidencia enviada a facturación", FPULSATECLAS ("F5","CF2","CF2","F2", ""))
#
##					            "CGENERACORREO", " No he podido generar correo de aviso de facturación",
##					            "CGENERACORREOCIERRE", "No he podido generar el correo de aviso de cierre de incidencia",

CURSOR = CACTSTATUSANULA UPDATE VDINCICAB SET STATUS = VDST.FICDANULADA,
						FECCERRADO = VD.FECHASYS, HORACERRADO = VD.HORASYS  
						WHERE CODINCI = :CODINCI;

CURSOR = CINSERTALINEAANULA INSERT ALL 
						INTO VDINCILIN (CODINCI, SEQLINEA, ACTUACION, CODOPEMODIF) 
						VALUES (:CODINCI, SEQLINEA, 'Se anula la incidencia', VDUSER.GETUSER)
						
						INTO VDINCILINOPE (CODINCI, SEQLINEA, CODOPE, TIEMPO, CODOPEMODIF)
						VALUES ( :CODINCI, SEQLINEA, VDUSER.GETUSER, 0, VDUSER.GETUSER)
						
						SELECT NVL(MAX(SEQLINEA),0)+1 SEQLINEA 
						  FROM VDINCILIN 
						WHERE CODINCI = :CODINCI;

# ANULAR INCIDENCIA
TECLA = AF8, FEJECUTA ("CACTSTATUSANULA", " No he podido poner el estado correspondiente ",
					             "CINSERTALINEAANULA", " No puedo insertar línea de incidencia",
					             FEJECUTAFORM ("VDINSERTALINEAINCI", "S", "", "CODINCI=:CODINCI", "", "", "N"), "",
					             FCOMMIT, "", %FFAILURE, " Incidencia anulada correctamente",  FPULSATECLAS ("F5","CF2","CF2","F2", ""))
                                 
#imprimir
TECLA = F10, FEJECUTA (FIMPRIME("INFORME","VDINCIDENCIA.rpt","CODINCI=:CODINCI",""), "Error imprimiendo incidencia")
#TECLA = F10, FEJECUTA ("CIMPRIME","Error al Imprimr \n :V10ERROR")

CURSOR=CIMPRIME BEGIN
                  VDIMPRIME.IMPRIME('INFORME','VDINCIDENCIA.rpt','CODINCI='||:CODINCI,1,'','',:V10ERROR);
				  COMMIT;
                  END;@

CURSOR = CACTSTATUSCIERRA UPDATE VDINCICAB SET STATUS = VDST.FICDCERRADA,
							FECCERRADO = VD.FECHASYS, HORACERRADO = VD.HORASYS WHERE CODINCI = :CODINCI;

CURSOR = CINSERTALINEACIERRA INSERT ALL 
						INTO VDINCILIN (CODINCI, SEQLINEA, ACTUACION, CODOPEMODIF) 
						VALUES (:CODINCI, SEQLINEA, 'Se cierra la incidencia.', VDUSER.GETUSER)
						INTO VDINCILINOPE (CODINCI, SEQLINEA, CODOPE, TIEMPO, CODOPEMODIF)
						VALUES ( :CODINCI, SEQLINEA, VDUSER.GETUSER, 0, VDUSER.GETUSER)
						SELECT NVL(MAX(SEQLINEA),0)+1 SEQLINEA 
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
						SELECT NVL(MAX(SEQLINEA),0)+1 SEQLINEA 
						  FROM VDINCILIN 
						WHERE CODINCI = :CODINCI;

CURSOR = CUPDASTATUSASIGNA UPDATE VDINCICAB SET STATUS = VDST.FICDASIGNADA WHERE CODINCI = :CODINCI;

CURSOR = CGENERACORREOASIGNA BEGIN VDESCRIBECORREOS.CORREO_ASIGNA_INCI(:CODINCI); END;@

CURSOR = CUPDAUSUARIO UPDATE VDINCICAB SET CODOPEASIGNA=:CODOPEASIGNA WHERE CODINCI = :CODINCI;

#ASIGNAR INCIDENCIA
#TECLA = CF8, FEJECUTA ("CUPDAUSUARIO", "ERROR ACTUALIZANDO", FCOMMIT, "", "CINSERTALINEAASIGNA", " No puedo insertar línea de incidencia",
#						           "CUPDASTATUSASIGNA", " No puedo actualizar el estado de la incidencia", 
#					             FCOMMIT, "", %FFAILURE, " Incidencia asignada correctamente",  FPULSATECLAS ("F5","CF2","CF2","F2"), "")

#					             "CGENERACORREOASIGNA", " No he podido generar correo de aviso de asignacion",

#DATOS DEL CLIENTE
#TECLA = CF6, FEJECUTA (FEJECUTAFORM("VDCONTACTOSCLI", "S", "CODCLI=:CODCLI", "", "","", "S"), "",
#                      FPULSATECLAS ("F5", "CF2", "CF2", "F2"), "")

#CREACION DE INCIDENCIA
CURSOR = CCONFIRMAFECHORA SELECT :HORACREADO FROM DUAL WHERE :HORACREADO IS NULL OR :FECCREADO = 0;

CURSOR = CSELCODINCI SELECT VDSECNUMINCI.NEXTVAL CODINCI FROM DUAL;

CURSOR=CLISTASTATUS SELECT STATUS,DESSTATUS FROM VDSTATUS WHERE TIPOSTATUS='ICD' AND STATUS>0 ORDER BY STATUS;

CURSOR=CSELCREA SELECT DECODE(NVL(:FECCREADO,0),0,VD.FECHASYS,:FECCREADO) FECCREADO,
                       NVL(:HORACREADO,VD.HORASYS) HORACREADO
                  FROM DUAL;

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
                         SELECT '<table id="tablaSubida"  width="1400" style="position:absolute;top:392px;left:-120px;z-index:9000" cellpadding="0" cellspacing="5">
                         <tr height="10">
                          <input type="image" title="Visualizar fichero adjunto" src="ojo.jpg" style="position:absolute;top:165px;left:196px;height:15px;width:15px;border-color:blue " 
                                  onClick="window.open(location.href=''http://V10-TEST-NEW:5301/'||:ADJUNTO||''',''window'',''params'');" value="Ver Adjunto">
                        </tr>
                           </table>' INTO :V10HTML FROM DUAL;
                        END IF;
                    END;@

CURSOR=CSELCAT SELECT :AREA FROM DUAL WHERE :AREA IS NOT NULL OR (:AREA IS NULL AND :TIPOCAT!='I');
CURSOR=CSELNUMINCI SELECT COUNT(*) NUMINCI FROM VDINCICAB WHERE CLAVEINCI = :CLAVEINCI;
CURSOR=CSELSEQINCI SELECT COUNT(*)+1 SEQCLAVEINCI FROM VDINCICAB WHERE CLAVEINCI = :CLAVEINCI; 					
CURSOR=CSELBULTOS SELECT  'TODOS' FROM DUAL
                   UNION ALL
				  SELECT CODBULTO FROM VDBULTOCAB WHERE CODPED=:CODPED AND CODDIV=:CODDIV AND SEQPED=:SEQPED AND ANOPED=:ANOPED;
#CURSOR=CSELARTIC SELECT BUL.CODART, ART.DESART Articulo, BUL.CANTPEDIDA CantPedida, BUL.CANTSERVIDA CatnServida FROM VDBULTOLIN BUL, VDARTIC ART WHERE BUL.CODBULTO IN (:BULTOS) AND BUL.CODART=ART.CODART;
CURSOR=CSELARTIC SELECT BUL.CODART,
						   ART.DESART      ARTICULO,
						   BUL.CANTPEDIDA  CANTPEDIDA,
						   BUL.CANTSERVIDA CATNSERVIDA,
						   BUL.CODBULTO    BULTO
					  FROM VDBULTOCAB BUC, VDBULTOLIN BUL, VDARTIC ART
					 WHERE BUC.CODPED = :CODPED
					   AND BUC.CODDIV = :CODDIV
					   AND BUC.SEQPED = :SEQPED
					   AND BUC.ANOPED = :ANOPED
					   AND BUC.CODBULTO = BUL.CODBULTO    
					   AND BUL.CODBULTO IN DECODE(:BULTOS,'TODOS',BUL.CODBULTO, :BULTOS)
					   AND BUL.CODART = ART.CODART
					 ORDER BY BUL.CODBULTO,BUL.CODART,BUL.CANTSERVIDA;
TECLA=CF8,FEJECUTA(FEJECUTAFORM("XVDUPLOAD","N","","CODCOMEN=:CODCOMEN CODTABLA='VDINCICAB'","","","S"))
				  