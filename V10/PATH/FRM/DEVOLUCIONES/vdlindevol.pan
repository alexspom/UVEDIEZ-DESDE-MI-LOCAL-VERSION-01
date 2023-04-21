Mantenimiento de lineas de devolucion
Articulo      Designación           A Lote                 Caduc.       Cant. Causa      St                    Caja Precinto  Observ                 Ultima modificación
_40__________ _100_________________ _ _40_________________ ________ _ _ @L@@@ __________ @L@@@ _______________ @L  _________ _255_________________ _______________ ¿D-MM-Y.YY ________
|

TABLA=VDDEVOLLIN
ORDERBY=FECMODIF,HORAMODIF;
NOUPDATE
NODELETE
WPIXELX=10
WREGPAG=10
WLONY=290

PREINSERT=FDESIGNACION("CVERIFICALOTE","Debe introducir lote",
                       "CCHECKCANTIDAD","Debe indicar la cantidad", 
                       "-CCAUSAESNULL","DEBE DE INDICAR LA CAUSA",      
                       "%-CSELTRAZA","NO PEDIDO",
                       FIF("CSELRECALL",FEJECUTA(FFAILURE,"")),"<FONT class='resmens2' >&nbsp&nbsp&nbsp&nbspLOTE NO MARCADO\n\n&nbsp&nbsp COMO RECALL",
                       FIF("CSELNORECALL",FEJECUTA(FFAILURE,"")),"<FONT class='resmens2' >&nbsp&nbsp&nbsp&nbspOPCION NO VALIDA PARA \n\n&nbsp&nbsp LOTE MARCADO COMO RECALL",
                       "-CSELDISCONTINUADO","<FONT class='resmens2' >PRODUCTO DISCONTINUADO\n\nSELECCIONE OTRA CAUSA VALIDA",
                       "+CSELLINEA","",
                       FIF("CSELAPTO",
                           FEJECUTA(FIF(FEJECUTA("!CLOTEAPTO","LOTE CADUCADO, ¿ESTA SEGURO DE UTILIZAR UNA CAUSA DE BUEN ESTADO?"),
                                        FSUCCESS,
                                        FEJECUTA("+CLIMPIACAUSA","",FHTMLCONFIRM,"",FFAILURE,"")),"SELECCIONE DE NUEVO\nLA CAUSA DE LA DEVOLUCION",
                                    "+CSELNUMETIQ","",
                                    "+CSELETIQ","",
                                    "CINSLABELLING","ERROR INSERTANDO REGISTRO DE LABELLING",
                                    FIMPRIMEUNIDCARGA("DEV",":SEQDEVOL",":SEQLINEA",":CODMATMES",":ESCOPIA","T",":FICETIQUETACNT;:NOMBREVSQCNT;:NOMBRECURSORCNT",":FICETIQUETAEMB;:NOMBREVSQEMB;:NOMBRECURSOREMB","1",":NUMETIQ","","1"),"ERROR IMPRIMIENDO UNIDAD DE CARGA",
                                    "CSELOPEINS","ERROR EN CSELOPEINS", 
                                    "CACTDEVOL","ERROR ACTUALIZANDO DEVOLUCION",   
                                    "CSTATUSDEVAPTO","ERROR ACTUALIZANDO LINEA DE DEVOLUCION",
                                    "+CDESSTATUS","",
                                    FCOMMIT,"",
                                    FHTMLALERT,"",
                                    FHTMLCONFIRM,"",
                                    FPULSATECLAS("CUA")),                                               
                           FEJECUTA("+CCALCULAABONABLE","",      
                                    "+CCALCULAAPTO","",    
                                    "+CNOAPTOPORLOTE","", 
                                    "+CREACOND","",
                                    "+CINIAPRECINTO","",
                                    "%-CDISCONTINUADO","<FONT class='resmens2' >PRODUCTO DISCONTINUADO",
                                    "+CDISCONTINUADO","",
                                    FIF("CHAYST",
                                        FIF(FEJECUTA("!CABONABLE","MERCANCIA A CAJA DE SINIESTRO DE TRANSPORTE"),
                                            FSUCCESS,
                                    				FEJECUTA(FIF(FEJECUTA("!CPREGUNTA","MERCANCIA SE ENVIA A PRECINTO"),
                                    				             FEJECUTA("CPONABONABLE","","CAPRECINTO",""), 
                                    				             FEJECUTA("+CLIMPIACAUSA","",FHTMLCONFIRM,"",FFAILURE,"")),"DEVOLUCION CANCELADA")),
                                        FIF(FEJECUTA("!CABONABLE","MERCANCIA A CAJA DE CLIENTE ORIGEN"),
                                            FSUCCESS,
                                            FEJECUTA(FIF(FEJECUTA("!CPREGUNTA","MERCANCIA SE ENVIA A PRECINTO"),
                                                         FEJECUTA("CPONABONABLE","","CAPRECINTO",""),
                                                         FEJECUTA("+CLIMPIACAUSA","",FFAILURE,"")),"DEVOLUCION CANCELADA"))),"",
                                    FHTMLCONFIRM,"",
                                    FHTMLALERT,"",
                                    FIF("CESNOAPTOPORLOTE",
                                        FEJECUTA(FHTMLALERT("VERTIS.NOAPTOPORLOTE.msjalert.html"),"",
                                                 %FFAILURE,"<FONT class='resmens2' >&nbsp&nbsp&nbsp&nbspMERCANCIA NO APTA\n\n&nbsp&nbsp POR CADUCIDAD DEL LOTE")),"",                                              
                                    FHTMLALERT,"",
                                    FIF("CSELAPRECINTO",
                                        FSUCCESS,
                                        FIF(FEJECUTA("!CNOABONABLE","MERCANCIA SE ENVIA A PRECINTO"),
                                        						 FSUCCESS,
                                        						 FEJECUTA(FIF(FEJECUTA("!CPREGUNTA","MERCANCIA A CAJA DE CLIENTE ORIGEN"),
                                        						                       "CPONNOABONABLE", 
                                        						                       FEJECUTA("+CLIMPIACAUSA","",FFAILURE,"")),"DEVOLUCION CANCELADA"),"DEVOLUCION CANCELADA")),"",
                                    FIF("CABONABLE", 
# POR AQUI SI ABONABLE, VA A DECIRLE QUE LO META EN LA CAJA DE APTO O NO APTO                       
                                        FEJECUTA("CSELCAJA","ERROR EN CSELCAJA",
                                                 "CSELPRECINTO","NO EXISTE PRECINTO ABIERTO\n\nDE TIPO :MENSAJEEXT",
                                                 "CSELMENSAJEPREC","ERROR PRESENTANDO MENSAJE",
                                                 FEJECUTA(FHTMLALERT("VERTIS.CAJADEVOLNUEVA.msjalert.html"),"",
                                                          %FFAILURE,":MENSAJE"),"",
                                                 FIF("CHAYMUSICA",FEJECUTA( FPONSONIDO("1"),"",FPLAYWAV(":MUSICA"),"",FPONSONIDO("0"),"")),"",
                                                 "CSELOPEINS","ERROR EN CSELOPEINS", 
                                                 "CACTDEVOL","ERROR EN CACTDEVOL",   
                                                 FCOMMIT,""),                                   
# POR AQUI SI NO ES ABONABLE         
                                        FEJECUTA(
# MIRAR SI IMPRIME NUEVA CAJA PARA EL ARTICULO, HAY 2 OPCIONES, DEPENDIENDO SI NUMCAJA ES 0 O NO                                  
                                                 "CSELCAJA","ERROR EN CSELCAJA",
                                                 FIF("CNUEVACAJA", 
# MENSAJE ALERT DE IMPRIMIR NUEVA CAJA, SI NUMCAJA ES 0 CAJADEVOLNUEVA
                                                     FEJECUTA(FHTMLALERT("VERTIS.CAJADEVOLNUEVA.msjalert.html"),"",
                                                              %FFAILURE,":MENSAJE"),
                                                     FEJECUTA(FHTMLCONFIRM("VERTIS.CAJADEVOLENUSO.msjconfirma.html"),"",
                                                              FIF(FEJECUTA("!CNUEVACAJA",":MENSAJE"),
# DESEA IMPRIMIR UNA NUEVA CAJA, LE DA A ACEPTAR EN LA PREGUNTA
                                                                  "CPONNUEVACAJAACERO",
                                                                  FSUCCESS),"")),"",
                                                 FIF("CNUEVACAJA", 
                                                     FEJECUTA("+CDAMENUEVACAJA","",
                                                              "+CUPDCAJASCLIENTE","",
                                                              FIF("CIMPRECAJADEVOL",
                                                                  FIF("CHAYST",
                                                                      FIMPRIME("ETIQ","VDDEVOLST.GEN;VDDEVOL.VSQ;CSELDEVOLCAJ","SEQDEVOL=:SEQDEVOL;NUMCAJA=:NUMCAJA;CODART=:CODART;STATUS=:STATUS",""),
                                                                      FIMPRIME("ETIQ","VDDEVOLCLI.GEN;VDDEVOL.VSQ;CSELDEVOLCAJ","SEQDEVOL=:SEQDEVOL;NUMCAJA=:NUMCAJA;CODART=:CODART;STATUS=:STATUS","")), 
                                                                  FSUCCESS),"ERROR IMPRIMIENDO CAJA")),":V10ERROR",                                   
# EN CASO CONTRARIO PONER PREGUNTA DE CONFIRMACION CAJADEVOLENUSO
                                                 "CSTATUSDEVCLIENTE","",
                                                 FHTMLALERT("VERTIS.ACAJACLIENTE.msjalert.html"),"",
                                                 "CSELOPEINS","ERROR EN CSELOPEINS", 
                                                 "CACTDEVOL","ERROR EN CACTDEVOL",   
                                                 FCOMMIT,"")),"",
                                    FHTMLALERT,"",
                                    FHTMLCONFIRM,"",
                                    FPULSATECLAS("CUA"))),"")


# SE METE LA FECHA DE DESTRUCCION SI NO VA A CAJA CLIENTE

PREUPDATE=FDESIGNACION("CSELOPEMODIF","")

PREREGISTRO=FEJECUTA(FIF("CNOINSERTADO",
                         FIF("CHAYST",
                             FEJECUTA(FCREABOTONES("LOTES","CSELBOTONLOTE", "PBOTONLOTE",":CODLOTAUX",":TOOLTIPBOTON","CODLOT","40","555","155","60","3","4","10","6","20000","blote",""),"",
                                      FCREABOTONES("CAUSA1","CSELBOTONCAUSA3","PBOTONCAUSA1",":CODCAUSAAUX",":TOOLTIPBOTON","CODCAUSABOTONPULSADO","690","590","120","60","3","5","10","6","20200","bcausa1",""),"",
                                      FCREABOTONES("CAUSA2","CSELBOTONCAUSA4","PBOTONCAUSA2",":CODCAUSAAUX",":TOOLTIPBOTON","CODCAUSABOTONPULSADO","690","790","120","60","3","5","10","6","20500","bcausa2",""),""),
                             FEJECUTA(FCREABOTONES("LOTES","CSELBOTONLOTE", "PBOTONLOTE",":CODLOTAUX",":TOOLTIPBOTON","CODLOT","40","555","155","60","3","4","10","6","20000","blote",""),"",
                                      FCREABOTONES("CAUSA1","CSELBOTONCAUSA1","PBOTONCAUSA1",":CODCAUSAAUX",":TOOLTIPBOTON","CODCAUSABOTONPULSADO","560","590","120","60","3","5","10","6","20200","bcausa1",""),"",
                                      FCREABOTONES("CAUSA2","CSELBOTONCAUSA2","PBOTONCAUSA2",":CODCAUSAAUX",":TOOLTIPBOTON","CODCAUSABOTONPULSADO","560","790","120","60","3","5","10","6","20500","bcausa2",""),"")),     
                         FEJECUTA(FPOSICIONACAMPO(FSUCCESS,"CODART"),"",
                                  FBORRABOTONES("LOTES"),"",
                                  FBORRABOTONES("CAUSA1"),"",
								                  FBORRABOTONES("CAUSA2"),"")),"")

CAMPO=SEQDEVOL,VIRTUAL,OCULTO
CAMPO=CODDIV,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODART,UPPER,POSTCHANGE=FDESIGNACION("CCHECKDEVOL","No ha seleccionado ninguna devolución",
                                           "@CODARTISNULL","",
                                           "+CDAMEART","", 
                                           "CCHECKARTDIV","El artículo no es de la división de la devolución",
                                           "CTIPOPRECINTOART","No se conoce el tipo de precintos para el artículo", 
                                           "CSELDESART","No existe artículo",                                          
                                           FIF("CNOINSERTADO",
                                               FIF("CHAYST",
                                                   FEJECUTA(FCREABOTONES("LOTES","CSELBOTONLOTE", "PBOTONLOTE",":CODLOTAUX",":TOOLTIPBOTON","CODLOT","40","555","155","60","3","4","10","6","20000","blote",""),"",
                                                            FCREABOTONES("CAUSA1","CSELBOTONCAUSA3","PBOTONCAUSA1",":CODCAUSAAUX",":TOOLTIPBOTON","CODCAUSABOTONPULSADO","690","590","120","60","3","5","10","6","20200","bcausa1",""),"",
                                                            FCREABOTONES("CAUSA2","CSELBOTONCAUSA4","PBOTONCAUSA2",":CODCAUSAAUX",":TOOLTIPBOTON","CODCAUSABOTONPULSADO","690","790","120","60","3","5","10","6","20500","bcausa2",""),""),
                                                   FEJECUTA(FCREABOTONES("LOTES","CSELBOTONLOTE","PBOTONLOTE",":CODLOTAUX",":TOOLTIPBOTON","CODLOT","40","555","155","60","3","4","10","6","20000","blote",""),"",
	                                                          FCREABOTONES("CAUSA1","CSELBOTONCAUSA1","PBOTONCAUSA1",":CODCAUSAAUX",":TOOLTIPBOTON","CODCAUSABOTONPULSADO","560","590","120","60","3","5","10","6","20200","bcausa1",""),"",
	                                                          FCREABOTONES("CAUSA2","CSELBOTONCAUSA2","PBOTONCAUSA2",":CODCAUSAAUX",":TOOLTIPBOTON","CODCAUSABOTONPULSADO","560","790","120","60","3","5","10","6","20500","bcausa2","background-color:red"),"",
	                                                          FPOSICIONACAMPO(FSUCCESS,"CODLOT")))),""),TITULO("Artículo"),
	                                        TECLA=SF10,FEJECUTAFORM("VDSELART","N","AR.CODART LIKE NVL(:CODART,'%') AND CODDIV=NVL(:CODDIV,CODDIV)","","CODART=:CODART CODLOT=:CODLOT")
CAMPO=DESART,AUXILIAR,NOENTER,TITULO("Designación"),TOOLTIP("Descripción del artículo")
CAMPO=ABONABLE,NOENTER,TITULO("A"),TOOLTIP("Abonable")
CAMPO=CODLOT,UPPER,POSTCHANGE=FDESIGNACION("CSELCODLOT","No existe lote",                                           
                                           "@CSELLOTVACIO","",
                                           "CCALCESTADO","No puedo calcular el estado",
                                           "+CSELCANTIDAD","No puedo poner cantidad 1",
                                           "@-CHAYST","",
                                           "+CSELCAUSA",""),TITULO("Lote")
#"%CSERVIDOCLIENTE","ARTICULO NO SERVIDO AL CLIENTE", 
CAMPO=CADUCI,AUXILIAR,NOENTER,TITULO("Caducidad"),TOOLTIP("Caducidad"),TOOLTIP("Caducidad del Lote en formato AAAAMMDD")
CAMPO=STLOTEAB,NOENTER,TOOLTIP("0 No abonable, al no tener definido criterios => A CAJA DE CLIENTE\n1 No ha caducado y caduca mas allá de un número de meses => A CAJA DE CLIENTE\n2 Caducado hace menos de y meses o no caducado, y caduca en menos de x meses  => ABONABLE\n3 Caducado hace mas de y meses => A CAJA DE CLIENTE")
CAMPO=STLOTEAPTO,NOENTER,TOOLTIP("0 NO apto, porque no se han definido criterios => NO APTO\n1 No ha caducado y caduca en menos de x meses => NO APTO\n2 No ha caducado y caduca mas allá de x meses => SUSCEPTIBLE DE APTO\n 3 Caducado => NO APTO")
CAMPO=CANTIDAD,TITULO("Cantidad"),POSTCHANGE=FEJECUTA("CCHECKCANTIDAD","Debe indicar la cantidad"),WLONX=25
CAMPO=CODCAUSA,NOENTER,TITULO("Causa")
CAMPO=STATUS,NOENTER,TITULO("Estado"),POSTCHANGE=FDESIGNACION("+CDESSTATUS","")
CAMPO=DESSTATUS,AUXILIAR,NOENTER
CAMPO=NUMCAJA,NOENTER,TITULO("NCaja"),WLONX=30
CAMPO=CODPRECINTO,NOENTER,TITULO("Precinto"),WLONX=10
CAMPO=OBSERV,TITULO("Observaciones")
CAMPO=CODOPEINS,NOENTER,TITULO("Ultima modificación")
CAMPO=FECINS,NOENTER
CAMPO=HORAINS,NOENTER
CAMPO=CODOPEMODIF,OCULTO,"_32"
CAMPO=FECMODIF,OCULTO,"¿D-MM-YY"
CAMPO=HORAMODIF,OCULTO,"________"
CAMPO=CODLOTAUX,NOUPDATE,AUXILIAR,OCULTO,"_20"
CAMPO=TOOLTIPBOTON,NOUPDATE,AUXILIAR,OCULTO,"_100"
CAMPO=PBOTONLOTE,NOUPDATE,AUXILIAR,OCULTO,"@L"
CAMPO=PBOTONCAUSA1,NOUPDATE,AUXILIAR,OCULTO,"@L"
CAMPO=PBOTONCAUSA2,NOUPDATE,AUXILIAR,OCULTO,"@L"

#CAMPO=STATUS,AUXILIAR,VIRTUAL,OCULTO
CAMPO=MUSICA,AUXILIAR,OCULTO,"_100"
CAMPO=MENSAJE,NOUPDATE,AUXILIAR,OCULTO,"_600_"
CAMPO=CODCAUSABOTONPULSADO,AUXILIAR,OCULTO,"_10_",POSTCHANGE=FIF("CDATOSRELLENOS",FEJECUTA("CPONCAUSA","",FPULSATECLAS("F4")),"CRESERBOTONPULSADO")
CAMPO=CODCAUSAAUX,AUXILIAR,NOUPDATE,OCULTO,"_10_"
CAMPO=APTO,AUXILIAR,OCULTO,"_"
CAMPO=CODCLIENTE,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODOPENOAPTO,OCULTO,"_32"
CAMPO=FECNOAPTO,OCULTO,"¿D-MM-Y.YY"
CAMPO=HORANOAPTO,OCULTO,"________"
CAMPO=CAJASCLIENTE,AUXILIAR,VIRTUAL,OCULTO
CAMPO=MENSAJEEXT,AUXILIAR,OCULTO,"_600_"
CAMPO=CODCOMEN,OCULTO,"@L@@@@@@@"
CAMPO=MSJNOAPTOPORLOTE,AUXILIAR,OCULTO,"_"
CAMPO=SEQLINEA,OCULTO,"@@@@@@@@@"
CAMPO=CODMATMES,AUXILIAR,OCULTO,"__________"
CAMPO=ESCOPIA,AUXILIAR,OCULTO,"_10_"
CAMPO=FICETIQUETACNT,AUXILIAR,OCULTO,"_30_"
CAMPO=NOMBRECURSORCNT,AUXILIAR,OCULTO,"_20______________"
CAMPO=NOMBREVSQCNT,AUXILIAR,OCULTO,"_20______________"
CAMPO=FICETIQUETAEMB,AUXILIAR,OCULTO,"_30_"
CAMPO=NOMBRECURSOREMB,AUXILIAR,OCULTO,"_20______________"
CAMPO=NOMBREVSQEMB,AUXILIAR,OCULTO,"_20______________"
CAMPO=NUMETIQ,AUXILIAR,OCULTO,"@@@@@@@"
CAMPO=UNIEMB,AUXILIAR,OCULTO,"@@@@@@"
CAMPO=EMBCONT,AUXILIAR,OCULTO,"@@@@@@"
CAMPO=CODNAC,AUXILIAR,OCULTO,"_13_"
CAMPO=PICO,AUXILIAR,OCULTO,"@@@@@@@@"
CAMPO=CODALBAST,NOUPDATE,AUXILIAR,OCULTO,"_20_"
CAMPO=ESTADO,AUXILIAR,OCULTO,"@"
CAMPO=APRECINTO,AUXILIAR,OCULTO,"_"

# GESTION DE LA MERCANCIA A ABONABLE O A CAJA CLIENTE
CURSOR=CSTATUSDEVCLIENTE SELECT VDVST.FDVLDEVCLIENTE STATUS FROM DUAL;

CURSOR=CDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='DVL';

CURSOR=CHAYMUSICA SELECT :MUSICA FROM DUAL WHERE :MUSICA IS NOT NULL;

CURSOR=CCHECKARTDIV SELECT :CODART FROM VDARTIC WHERE CODART=:CODART AND CODDIV = NVL(:CODDIV,CODDIV);

CURSOR=CRESERBOTONPULSADO  SELECT NULL CODCAUSABOTONPULSADO FROM DUAL;

CURSOR=CLIMPIACAUSA SELECT NULL CODCAUSA, NULL CODCAUSABOTONPULSADO FROM DUAL;

CURSOR=CPREGUNTA SELECT :CODART FROM DUAL WHERE 1=2;

CURSOR=CODARTISNULL SELECT :CODART FROM DUAL WHERE :CODART IS NOT NULL;

CURSOR=CCALCESTADO SELECT VDDEVOL.ESTADOLOTEAB(:CODDIV,:CODART,:CODLOT) STLOTEAB,VDDEVOL.ESTADOLOTEAPTO(:CODDIV,:CODART,:CODLOT) STLOTEAPTO FROM DUAL;


CURSOR=CVERIFICALOTE SELECT CADUCI,'N' ABONABLE,'N' APTO,'N' MSJNOAPTOPORLOTE FROM VDLOTES WHERE CODART=:CODART AND CODLOT=:CODLOT;

CURSOR=CESNOAPTOPORLOTE SELECT :MSJNOAPTOPORLOTE  FROM DUAL WHERE :MSJNOAPTOPORLOTE = 'S';

CURSOR=CNOAPTOPORLOTE SELECT 'S' MSJNOAPTOPORLOTE 
                              FROM VDDEVOLCAUSA
                              WHERE CODCAUSA=:CODCAUSA AND 
                                    :ABONABLE='S'  AND 
                                    :APTO='N' AND 
                                    APTO='D';
CURSOR=CREACOND SELECT 'R' APTO 
                              FROM VDDEVOLCAUSA 
                              WHERE CODCAUSA=:CODCAUSA AND  
							        :ABONABLE='S' AND
                                    INTERNO='N' AND APTO='R';
									
CURSOR=CCALCULAAPTO SELECT 'S' APTO 
                              FROM VDDEVOLCAUSA 
                              WHERE CODCAUSA=:CODCAUSA AND  
                                    INTERNO='N' AND
                                    (APTO='S' OR ( APTO='D' AND :STLOTEAPTO='2'));
                                    
CURSOR=CCALCULAABONABLE SELECT 'S' ABONABLE , VDVST.FDVLDEVCLIENTE STATUS
                              FROM VDDEVOLCAUSA 
                              WHERE CODCAUSA=:CODCAUSA AND 
                                    INTERNO='N' AND
                                    (ABONAR='S' OR ( ABONAR='D' AND :STLOTEAB='2'));

CURSOR=CABONABLE SELECT :ABONABLE FROM DUAL WHERE :ABONABLE='S';

CURSOR=CNOABONABLE SELECT :ABONABLE FROM DUAL WHERE :ABONABLE='N';

CURSOR=CPONABONABLE  SELECT 'S' ABONABLE FROM DUAL;

CURSOR=CPONNOABONABLE  SELECT 'N' ABONABLE FROM DUAL;
                    
CURSOR=CSELOPEINS SELECT VDUSER.GETUSER CODOPEINS,VD.FECHASYS FECINS,VD.HORASYS HORAINS,
                         VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF,
                         VDSECCOMEN.NEXTVAL CODCOMEN                         
                    FROM DUAL;

CURSOR=CSELCAJA BEGIN VDDEVOL.DAMEDATOSCAJA(:ABONABLE,:STATUS,:DESSTATUS,:MENSAJEEXT,:CODART,:NUMCAJA,:SEQDEVOL,:MUSICA,:CODALBAST,:MENSAJE,:APTO); END;@

CURSOR=CPONNUEVACAJAACERO SELECT 0 NUMCAJA FROM DUAL;

CURSOR=CDAMENUEVACAJA SELECT NVL(MAX(NUMCAJA),0)+1  NUMCAJA FROM VDDEVOLLIN WHERE SEQDEVOL=:SEQDEVOL;

CURSOR=CNUEVACAJA SELECT TO_NUMBER(:NUMCAJA) NUMCAJA FROM DUAL WHERE NVL(:NUMCAJA,0) = 0;              
                    
# CHEQUEOS VARIOS DEL MANEJO DE LA VENTANA
CURSOR=CCHECKCANTIDAD SELECT TO_NUMBER(:CANTIDAD) CANTIDAD FROM DUAL WHERE :CANTIDAD>0 OR :CODLOT IS NULL;

CURSOR=CSERVIDOCLIENTE SELECT :MENSAJE 
                         FROM VDPEDIDOCAB PEC,VDPEDIDOLIN PEL
                        WHERE PEC.CODPED=PEL.CODPED AND PEC.SEQPED=PEL.SEQPED AND 
                              PEC.ANOPED=PEL.ANOPED AND PEC.CODDIV=PEL.CODDIV AND
                              CODCLIENTE=:CODCLIENTE AND CODART=:CODART AND CODLOT=:CODLOT AND CANTSERVIDA>0 
                       UNION 
                       SELECT :MENSAJE FROM DUAL WHERE :CODART IS NULL;

CURSOR=CNOINSERTADO SELECT :MENSAJE FROM DUAL WHERE :HORAINS IS NULL;

CURSOR=CCAUSAESNULL SELECT :CODCAUSA FROM DUAL WHERE :CODCAUSA IS NULL;

CURSOR=CDAMEART SELECT VDDEVOL.DAMEART(:CODART) CODART FROM DUAL;

CURSOR=CSELDESART  SELECT CODART,DESART FROM VDARTIC WHERE  CODART=NVL(:CODART,'-');

CURSOR=CTIPOPRECINTOART SELECT CODART FROM VDCLASEARTIC WHERE CODART=:CODART AND CODCLASIF='DESTRUCCION';


CURSOR=CSELCODLOT SELECT CADUCI FROM VDLOTES WHERE CODART=:CODART AND CODLOT=:CODLOT
                    UNION
                  SELECT NULL CADUCI FROM DUAL WHERE :CODLOT IS NULL AND :CANTIDAD=0;

                    
CURSOR=CSELLOTVACIO SELECT :CODLOT FROM DUAL WHERE :CODLOT IS NOT NULL;

CURSOR=CSELCANTIDAD SELECT 1 CANTIDAD FROM DUAL WHERE :CANTIDAD = 0;                    


CURSOR=CDATOSRELLENOS SELECT :CODCAUSABOTONPULSADO FROM DUAL WHERE :CODART IS NOT NULL AND :CODLOT IS NOT NULL AND :CANTIDAD > 0 AND :HORAINS IS NULL;

# BOTONERAS DINAMICAS
CURSOR=CSELBOTONCAUSA SELECT CODCAUSA CODCAUSAAUX ,DESCAUSA TOOLTIPBOTON 
                                FROM VDDEVOLCAUSA WHERE INTERNO='N' AND (CODDIV=NVL(:CODDIV,'-') OR CODDIV IS NULL) ORDER BY ORDEN ;

CURSOR=CSELBOTONCAUSA1 SELECT CODCAUSA CODCAUSAAUX ,DESCAUSA TOOLTIPBOTON 
                         FROM VDDEVOLCAUSA WHERE INTERNO='N' AND (CODDIV=NVL(:CODDIV,'-') OR CODDIV IS NULL) 
								          AND CODCAUSA IN ('INCOMPLETO','ROTO','MANCHADO','VACIO','OTROS') 
								       ORDER BY ORDEN ;
								
CURSOR=CSELBOTONCAUSA2 SELECT CODCAUSA CODCAUSAAUX ,DESCAUSA TOOLTIPBOTON 
                         FROM VDDEVOLCAUSA WHERE INTERNO='N' AND (CODDIV=NVL(:CODDIV,'-') OR CODDIV IS NULL) 
								          AND CODCAUSA IN ('BE','RECALL','ANULADO BE','AF-PDG')
								       ORDER BY ORDEN ;

						
CURSOR=CSELBOTONLOTE SELECT CODLOTAUX, TOOLTIPBOTON   
                       FROM (SELECT 1 ORDEN,LOT.CODLOT CODLOTAUX,'Lote: '||LOT.CODLOT||' Caducidad: '||LOT.CADUCI TOOLTIPBOTON, LOT.CADUCI  
                               FROM VDDEVOLLIN DVL, VDLOTES LOT 
                              WHERE SEQDEVOL=:SEQDEVOL AND DVL.CODART=:CODART AND LOT.CODART=DVL.CODART AND LOT.CODLOT=DVL.CODLOT
                              GROUP BY LOT.CODLOT, LOT.CADUCI 
                             UNION
                             SELECT 2 ORDEN,PEL.CODLOT CODLOTAUX,'Lote: '||PEL.CODLOT||' Caducidad: '||PEL.CADUCI TOOLTIPBOTON, PEL.CADUCI
                               FROM VDPEDIDOLIN PEL,VDDEVOLCAB DVC
                              WHERE DVC.SEQDEVOL=:SEQDEVOL AND DVC.CODPED=PEL.CODPED AND PEL.CODART||''=:CODART AND 
                                    DVC.CODPED IS NOT NULL
                             UNION	
                             SELECT 3 ORDEN,PEL.CODLOT CODLOTAUX,'Lote: '||PEL.CODLOT||' Caducidad: '||PEL.CADUCI TOOLTIPBOTON, PEL.CADUCI
                               FROM VDPEDIDOCAB PEC,VDPEDIDOLIN PEL,VDDEVOLCAB DVC
                              WHERE DVC.SEQDEVOL=:SEQDEVOL AND DVC.CODCLIENTE=PEC.CODCLIENTE AND
                                    PEC.CODPED=PEL.CODPED AND PEC.ANOPED=PEL.ANOPED AND
                                    PEC.SEQPED=PEL.SEQPED AND PEC.CODDIV=PEL.CODDIV AND PEL.CODART||''=:CODART AND 
                                    DVC.CODPED IS NULL AND DVC.CODCLIENTE IS NOT NULL AND
                                    PEL.CADUCI<TO_CHAR(TO_DATE(VD.FECHASYS,'J'),'YYYYMMDD')
                             UNION	
                             SELECT 4 ORDEN,PEL.CODLOT CODLOTAUX,'Lote: '||PEL.CODLOT||' Caducidad: '||PEL.CADUCI TOOLTIPBOTON, PEL.CADUCI
                               FROM VDPEDIDOCAB PEC,VDPEDIDOLIN PEL,VDDEVOLCAB DVC
                              WHERE DVC.SEQDEVOL=:SEQDEVOL AND DVC.CODCLIENTE=PEC.CODCLIENTE AND
                                    PEC.CODPED=PEL.CODPED AND PEC.ANOPED=PEL.ANOPED AND
                                    PEC.SEQPED=PEL.SEQPED AND PEC.CODDIV=PEL.CODDIV AND PEL.CODART=:CODART AND 
                                    DVC.CODPED IS NULL AND DVC.CODCLIENTE IS NOT NULL AND
                                    PEL.CADUCI>=TO_CHAR(TO_DATE(VD.FECHASYS,'J'),'YYYYMMDD')
                             UNION
                             SELECT 5 ORDEN,CODLOT CODLOTAUX,'Lote: '||CODLOT||' Caducidad: '||CADUCI TOOLTIPBOTON, CADUCI 
                               FROM VDLOTES WHERE CODART=:CODART) 
                     ORDER BY ORDEN, CADUCI DESC,CODLOTAUX DESC;  
					

CURSOR=CPONCAUSA SELECT  :CODCAUSABOTONPULSADO CODCAUSA  FROM DUAL WHERE :CODCAUSABOTONPULSADO IS NOT NULL ;

# RESTO DE CURSORES
CURSOR=CSELOPEMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF
                    FROM DUAL;


# TRATA ESTADO DE LA DEVOLUCION
CURSOR=CPRIMCAJACLIENTE SELECT 1 CAJASCLIENTE FROM VDDEVOLCAB WHERE SEQDEVOL=:SEQDEVOL AND STATUS IN (VDVST.FDVCPENDIENTE,VDVST.FDVCENCURSO) AND :CAJASCLIENTE=0 AND :ABONABLE='N';

CURSOR=CACTDEVOL UPDATE VDDEVOLCAB SET STATUS = VDVST.FDVCENCURSO,
                                         CODOPEMODIF=VDUSER.GETUSER,
                                         FECMODIF=VD.FECHASYS,
                                         HORAMODIF=VD.HORASYS
                                   WHERE SEQDEVOL=:SEQDEVOL;
                                   
CURSOR=CMODIFPADRE UPDATE VDDEVOLCAB SET CAJASCLIENTE = :CAJASCLIENTE,
                                         CODOPEMODIF=VDUSER.GETUSER,
                                         FECMODIF=VD.FECHASYS,
                                         HORAMODIF=VD.HORASYS
                                   WHERE SEQDEVOL=:SEQDEVOL;
                    
CURSOR=CCHECKDEVOL SELECT TO_NUMBER(:SEQDEVOL) SEQDEVOL FROM DUAL WHERE :SEQDEVOL > 0;
                   
CURSOR=CINCCAJASCLIENTE2 UPDATE VDDEVOLCAB SET   CAJASCLIENTE = :CAJASCLIENTE,
                                                 CODOPEMODIF  = VDUSER.GETUSER,
                                                 FECMODIF     = VD.FECHASYS,
                                                 HORAMODIF    = VD.HORASYS
                                      WHERE SEQDEVOL = :SEQDEVOL;
                                      
CURSOR=CINCCAJASCLIENTE SELECT TO_NUMBER(NVL(:CAJASCLIENTE,0)) + 1 CAJASCLIENTE FROM DUAL;                                     

CURSOR=CIMPRECAJADEVOL SELECT :NUMCAJA FROM DUAL
                        WHERE VD.GETPROP('IMPRIMECAJADEVOL')='S';

CURSOR=CSELTRAZA SELECT 1 ESTADO FROM DUAL
                  WHERE NOT EXISTS (SELECT :SEQDEVOL
                                      FROM VDPEDIDOLIN PEL,VDPEDIDOCAB PEC
                                     WHERE PEL.CODPED=PEC.CODPED AND PEL.ANOPED=PEC.ANOPED AND PEL.CODDIV=PEC.CODDIV AND PEL.SEQPED=PEC.SEQPED AND
                                           PEL.CODART=:CODART AND PEL.CODLOT=:CODLOT AND EXISTS 
                                           (SELECT SEQDEVOL FROM VDDEVOLCAB WHERE SEQDEVOL=:SEQDEVOL AND (PEC.CODCLIENTE=CODCLIENTE))
                                    UNION
                                    SELECT :SEQDEVOL FROM VDCLASEARTIC WHERE CODCLASIF='TRAZADEVOL' AND CODART=:CODART AND CODCLASE='NO');

CURSOR=CSELAPTO SELECT 'S' APTO 
                  FROM VDDEVOLCAUSA 
                 WHERE CODCAUSA=:CODCAUSA AND APTO='S';

CURSOR=CSELLINEA SELECT MAX(SEQLINEA)+1 SEQLINEA FROM VDDEVOLLIN WHERE SEQDEVOL=:SEQDEVOL;

CURSOR=CSELETIQ SELECT 'DAMEDATMATMES' NOMBRECURSORCNT,'VDETIQUETAS.VSQ' NOMBREVSQCNT, 'VDETIQPALMES.GEN' FICETIQUETACNT,
                       'DAMEDATARTMES' NOMBRECURSOREMB,'VDETIQUETAS.VSQ' NOMBREVSQEMB, 'VDETIQBULMES.GEN' FICETIQUETAEMB,
                       'N' ESCOPIA FROM DUAL;

CURSOR=CSELNUMETIQ SELECT CEIL(:CANTIDAD/UNIEMB) NUMETIQ,UNIEMB,EMBCONT,CODNAC,MOD(:CANTIDAD,UNIEMB) PICO 
                     FROM VDARTIC
                    WHERE CODART=:CODART;

CURSOR=CINSLABELLING INSERT INTO XVDLABELING (CODTRANS, NORDEN, LINEA, EMPRESA, CODARTETIQ, DESART1, 
                                              DESART2, FECBPCS, CODLOTETIQ, FECCADUCI, CANTTEOBPCS, UCAJABPCS, 
                                              UPALETBPCS, CODNACETIQ, MAQUINA, IDIOMA, CODLOTGRANEL, FECFABRIC, 
                                              CODPEDEXP, PAISEXP, CODUNI, CODBASILEA, SWTIPOETI, CANTREAL, 
                                              CANTPICOTEOR, CANTPICOREAL, FILLER, TIPO, FECREPEC, HORARECEP, 
                                              FECAPER, HORAAPER, FECTERMIN, HORATERMIN, STATUS, CODOPEMODIF, FECMODIF, HORAMODIF) 
                                      VALUES ('DEV',:SEQDEVOL,:SEQLINEA,'ROCHE FARMA,S.A',:CODART,:DESART,
                                              NULL,VD.FECHASYS,:CODLOT,TO_CHAR(TO_DATE(:CADUCI,'YYYYMMDD'),'J'),:CANTIDAD,:UNIEMB,
                                              :EMBCONT,:CODNAC,NULL,NULL,NULL,VD.FECHASYS,
                                              NULL,NULL,NULL,NULL,'T',:CANTIDAD,
                                              :PICO,:PICO,NULL,NULL,VD.FECHASYS,VD.HORASYS,
                                              VD.FECHASYS,VD.HORASYS,VD.FECHASYS,VD.HORASYS,200,'VERTIS',VD.FECHASYS,VD.HORASYS);

CURSOR=CSTATUSDEVAPTO SELECT VDVST.FDVLAPTO STATUS FROM DUAL;

CURSOR=CSELPRECINTO SELECT CODPRECINTO
                      FROM VDPRECINTO 
                     WHERE STATUS = VDVST.FPRCABIERTO AND TIPOPRECINTO=:MENSAJEEXT;
                     
CURSOR=CSELMENSAJEPREC SELECT '&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbspDEPOSITE MERCANCIA EN\n\n&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbspPRECINTO <FONT class="resmens1"> ' || :CODPRECINTO || ' </FONT>\n\nDE TIPO <FONT class="resmens2" > ''' || :MENSAJEEXT || ''' </FONT>&nbsp&nbsp&nbsp&nbsp\n\n&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp<FONT class="resmens3" >EN USO</FONT>\n\n' MENSAJE
                         FROM DUAL;

CURSOR=CUPDCAJASCLIENTE UPDATE VDDEVOLCAB SET CAJASCLIENTE = :NUMCAJA,
                                         CODOPEMODIF=VDUSER.GETUSER,
                                         FECMODIF=VD.FECHASYS,
                                         HORAMODIF=VD.HORASYS
                                   WHERE SEQDEVOL=:SEQDEVOL;

CURSOR=CSELRECALL SELECT :CODCAUSA FROM DUAL 
                   WHERE :CODCAUSA='RECALL' AND 
                          NOT EXISTS (SELECT COMENTARIO FROM VDLOTES LOT,VDCOMEN COM
                                   WHERE LOT.CODART=:CODART AND LOT.CODLOT=:CODLOT AND
                                         LOT.CODCOMEN=COM.CODCOMEN AND COM.TIPOCOMEN='RECALL' AND
                                         COM.COMENTARIO='S');
                 
CURSOR=CSELNORECALL SELECT :CODCAUSA FROM DUAL
                     WHERE :CODCAUSA IN ('BE','ANULADO BE') AND
                           EXISTS (SELECT COMENTARIO FROM VDLOTES LOT,VDCOMEN COM
                                   WHERE LOT.CODART=:CODART AND LOT.CODLOT=:CODLOT AND
                                         LOT.CODCOMEN=COM.CODCOMEN AND COM.TIPOCOMEN='RECALL' AND
                                         COM.COMENTARIO='S');

CURSOR=CSELDISCONTINUADO SELECT :CODCAUSA FROM DUAL
                          WHERE :CODCAUSA IN ('BE','ANULADO BE','RECUPERAST') AND
                                EXISTS (SELECT CLA.CODART FROM VDCLASEARTIC CLA
                                         WHERE CLA.CODCLASIF='ADMITEDEVOL' AND CLA.CODCLASE='C' AND
                                               CLA.CODART=:CODART);

CURSOR=CSELCAUSA SELECT 'CORRECTO' CODCAUSA, 'CORRECTO' CODCAUSABOTONPULSADO FROM DUAL WHERE :CODCAUSA IS NULL AND :STLOTEAB='2';

CURSOR=CHAYST SELECT CODALBAST FROM VDDEVOLCAB WHERE SEQDEVOL=:SEQDEVOL AND CODALBAST IS NOT NULL;

CURSOR=CSELBOTONCAUSA3 SELECT CODCAUSA CODCAUSAAUX ,DESCAUSA TOOLTIPBOTON 
                         FROM VDDEVOLCAUSA WHERE INTERNO='N' AND (CODDIV=NVL(:CODDIV,'-') OR CODDIV IS NULL) 
								          AND CODCAUSA='ROTOAGE'
								       ORDER BY ORDEN;                    

CURSOR=CSELBOTONCAUSA4 SELECT CODCAUSA CODCAUSAAUX ,DESCAUSA TOOLTIPBOTON 
                         FROM VDDEVOLCAUSA WHERE INTERNO='N' AND (CODDIV=NVL(:CODDIV,'-') OR CODDIV IS NULL) 
								          AND CODCAUSA='RECUPERAST'
								       ORDER BY ORDEN;                    

CURSOR=CLOTEAPTO SELECT :STLOTEAPTO FROM DUAL WHERE :STLOTEAPTO='2';
                    
CURSOR=CINIAPRECINTO SELECT 'N' APRECINTO FROM DUAL;
                    
CURSOR=CAPRECINTO SELECT 'S' APRECINTO FROM DUAL;
                    
CURSOR=CSELAPRECINTO SELECT :APRECINTO FROM DUAL WHERE :APRECINTO='S';                   

CURSOR=CDISCONTINUADO SELECT 'N' ABONABLE FROM DUAL 
                       WHERE EXISTS (SELECT CLA.CODART FROM VDCLASEARTIC CLA
                                      WHERE CLA.CODCLASIF='ADMITEDEVOL' AND CLA.CODCLASE='C' AND
                                            CLA.CODART=:CODART);

CONTEXTUAL=FEJECUTAFORM("VDSELART","N","AR.CODART LIKE NVL(:CODART,'%') AND CODDIV=NVL(:CODDIV,CODDIV)","","CODART=:CODART CODLOT=:CODLOT")
                                      
TECLA=SF6,FEJECUTA("CCHECKDEVOL","DEBE SELECCIONAR UNA DEVOLUCION",                   
                   "+CINCCAJASCLIENTE","",
                   "CINCCAJASCLIENTE2","ERROR INCREMENTANDO CAJAS CLIENTE",                   
                   FIMPRIME("ETIQ","VDDEVOLCLI.GEN;VDDEVOL.VSQ;CSELDEVOLCLI","SEQDEVOL=:SEQDEVOL",""),":V10ERROR",
                   FCOMMIT,"",
                   %FFAILURE,"Impresa Etiqueta de Caja Cliente") 
                   

BOTON=CONFIRMA,920,50,120,120,"Confirmar Protocolo",vertis\confprotolin.png,F4,"Confirmar",INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=SALIR,1060,50,120,120,"Salir",vertis\vertissalir.png,27,"Salir de la pantalla" ,INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=CLAEJEMPLAR,680,550,150,30,"CLASIFICACION EJEMPLAR",NO,0,""
BOTON=CLAPROCESO,680,750,150,30,"CLASIFICACION PROCESO",NO,0,""
