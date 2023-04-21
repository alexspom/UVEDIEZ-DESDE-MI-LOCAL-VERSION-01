# Módulo   : VDINCICAB.PAN
# Función  : DATOS DE CABECERA DE INCIDENCIAS
#
# Creación : 14-09-2009
# Autor    : JCSR
# Fichero generado por el Asistente de Generación de Pantallas V10 
###########################################
# Histórico de cambios:
DATOS DE CABECERA DE INCIDENCIA


  Incidencia:        @L@@@@@@@                 Clave Incidencia: @@@@@@@@@@@@@@@@@
  Nº de incidencias: @@@ / @@@                 Núm. incidencia cliente: __________

  
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
WLONX=630
WFRAME (5,1,600,375,"Datos técnicos","")
WFRAME (15,60,580,115,"Datos de la transacción","")
WFRAME (5,380,600,165,"Datos administrativos","")

PREINSERT = FEJECUTA ( "+CSELSTATUS","",
                       "CSELMODIF","ERROR EN CSELMODIF",
                       "CSELCREA","ERROR EN CSELCREA",
					   "CSELCAT","Obligatorio seleccionar área",
                       "CSELCODINCI", " Error seleccionando nuevo código de incidencia",
					   "+CSELSEQINCI","",
					   FPULSATECLAS("SF12","F4","F5","F2"),""					   
					   )
					   
PREUPDATE = FEJECUTA ( "CSELMODIF","ERROR EN CSELMODIF",
                       "CSELCAT","Obligatorio seleccionar área" )
POSTQUERY = FEJECUTA ("+CSELHORASINCI", "ERROR CALCULANDO LAS HORAS DE INCIDENCIAS",
                      "+CSELFICHERO","",
					  "+CSELNUMINCI","")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CSELSTATUS SELECT DECODE(:STATUS,0,100,:STATUS) STATUS FROM DUAL;



CAMPO=CODPED,OCULTO,"_20_"
CAMPO=ANOPED,OCULTO,"@@@@"
CAMPO=SEQPED,OCULTO,"@@@@"
CAMPO=CODDIV,NOENTER,TOOLTIP("Division o compañia del pedido"),OCULTO,"_20"
CAMPO=CODCLI,NOENTER,OCULTO,"_20_____"
CAMPO=DESCLI,AUXILIAR, NOENTER, MIXED,OCULTO,"_20_"
CAMPO = SEQLINEA, AUXILIAR, OCULTO, "@L@"
CAMPO = TIEMPO, AUXILIAR, OCULTO, "#L#####.##"
CAMPO = HORASINCI, AUXILIAR, OCULTO, "@L@@@"
CAMPO = CODCOMEN, OCULTO, "@L@@@@@@@"
CAMPO = V10HTML,AUXILIAR,OCULTO,"_2048_"
CAMPO=CARPETAINCI,AUXILIAR,OCULTO,"_100_"
CAMPO=LIST,AUXILIAR,OCULTO,"_000_"
CAMPO=PATHINCI,AUXILIAR,OCULTO,"_400_"

# LISTA DE CAMPOS DE LA PANTALLA
################################################### DATOS TECNICOS ################################################### 
CAMPO=CODINCI, NOENTER,TITULO ( "INCIDENCIA" ), TOOLTIP ( "CODIGO DE INCIDENCIA" )
CAMPO = CLAVEINCI,VIRTUAL,TOOLTIP("Clave de incidencia asociada"),NOENTER
CAMPO=SEQCLAVEINCI,NOENTER
CAMPO=NUMINCI,AUXILIAR,NOENTER
CAMPO=CODINCICLI, TITULO("Código de incidencia interno del cliente")
################################################### DATOS TECNICOS ################################################### 
CAMPO=TIPOCLAVEINCI,VIRTUAL,NOENTER,TOOLTIP("Tipo de incidencia")
CAMPO=DESTIPOCLAVEINCI,AUXILIAR,VIRTUAL,NOENTER
CAMPO=CODTRA,AUXILIAR,NOENTER,VIRTUAL
CAMPO=BULTOS,TOOLTIP("Bultos del pedido a los que afecta la incidencia")
CAMPO=UNIDADES,TOOLTIP("Unidades del pedido a las que afecta la incidencia")
CAMPO=ARTICULOS,TOOLTIP("Artículos del pedido a los que afecta la incidencia")

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

CURSOR = CSELDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS = :STATUS AND TIPOSTATUS = 'ICD';

CURSOR = CSELCATALOGACION SELECT CATALOGACION FROM VDCATALOGACION WHERE TIPO = :TIPOCAT;

CURSOR = CSELCONCEPTOS SELECT CODCONCEPTO COD, GRUPOCONCEPTO || ' - ' || CONCEPTO CONCEPTO FROM VDINCICONCE ORDER BY GRUPOCONCEPTO, CODCONCEPTO;

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
					             FCOMMIT, "", %FFAILURE, " Incidencia anulada correctamente",  FPULSATECLAS ("F4","F5","CF2","CF2","F2", ""))
                                 
#imprimir
TECLA = CF1, FEJECUTA (FIMPRIME("INFORME","VDINCIDENCIA.rpt","CODINCI=:CODINCI",""), "Error imprimiendo incidencia")
#TECLA = CF1, FEJECUTA ("CIMPRIME","Error al Imprimr \n :V10ERROR")

CURSOR=CIMPRIME DECLARE 
                  RET NUMBER;
				  BEGIN
                    RET:=VDIMPRIME.FIMPRIME('INFORME','VDINCIDENCIA.rpt','CODINCI='||:CODINCI,1,'','',:V10ERROR);
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
                         SELECT '<table id="tablaSubida" width="1400" style="position:absolute;top:392px;left:-120px;z-index:9000" cellpadding="0" cellspacing="5">
                                  <tr height="10">
                                    <input type="image" title="Visualizar fichero adjunto" src="ojo.jpg" style="position:absolute;top:575px;left:418px;height:20px;width:20px;border-color:blue " 
                                       onClick="window.open(location.href='||''''||VD.GETPROP('SERVERINCI')||'/'||:CODINCI||'/'||:ADJUNTO||''',''window'',''params'');" value="Ver Adjunto">                                 
                                  </tr>
                                 </table>' INTO :V10HTML FROM DUAL;
                        END IF;
                    END;@

CURSOR=CSELCAT SELECT :AREA FROM DUAL WHERE :AREA IS NOT NULL OR (:AREA IS NULL AND :TIPOCAT!='I');
CURSOR=CSELNUMINCI SELECT COUNT(*) NUMINCI FROM VDINCICAB WHERE CLAVEINCI = :CLAVEINCI;
CURSOR=CSELSEQINCI SELECT COUNT(*)+1 SEQCLAVEINCI FROM VDINCICAB WHERE CLAVEINCI = :CLAVEINCI; 					
CURSOR=CVERCARPETAINCI SELECT VD.GETPROP('DIRINCI')||:CODINCI CARPETAINCI FROM DUAL;
CURSOR=CVERPATH SELECT VD.GETPROP('PATHADJUNTOS')||:CODINCI||'//' PATHINCI FROM DUAL;

TECLA=CF8,FEJECUTA("CVERPATH","ERROR AL VER EL PATH DE FICHEROS ADJUNTO PARA INCIDENCIAS",
                   FEJECUTAFORM("XVDUPLOAD","N","","CODCOMEN=:CODCOMEN CODTABLA='VDINCICAB' PATHFICHERO=:PATHINCI","","","S"))
TECLA=SF12,FEJECUTA("CVERCARPETAINCI","Error al ver carpeta",
                    FWINEXEC("CMD /CMKDIR :CARPETAINCI"),"")
