/* USUARIO: . */

/* Defines de los status. */
#define  STBASREQUERIDO      100  /* PESO REQUERIDO */
#define  STBASSOLICITADO     200  /* PESO SOLICITADO A BASCULA */
#define  STBASLEIDO          300  /* PESO LEIDO */
#define  STBASTRATADO        400  /* PESO TRATADO */
#define  STBPCCREADO         100  /* CREADO */
#define  STBPCPRESENTADO     300  /* PRESENTADO EN TERMINAL */
#define  STBPCPDTEETIQ       500  /* PDTE ETIQUETAR */
#define  STBPCIMPRESO        700  /* IMPRESO */
#define  STBPCODS           1000  /* CIRCULANDO EN ODS */
#define  STBPCTRANSVASE     1100  /* REENGANCHANDO BULTO */
#define  STBPCRESTOS        2000  /* BULTO DE RESTOS */
#define  STBPCAHDS          2500  /* CAMINO A MINILOAD */
#define  STBPCHDS           3000  /* ALMACENADO EN HDS */
#define  STBPCFINALIZADO    5000  /* FINALIZADO */
#define  STBPCTTOFIN        6000  /* TRATADO FIN DEL BULTO DE PINV */
#define  STBPCANULADO       7000  /* ANULADO */
#define  STBPCTRATADAANU    7100  /* TRATADA ANULACION */
#define  STBPCBLOQUEADO     8000  /* BLOQUEADO POR EL HDS */
#define  STBPLASERVIR        100  /* PENDIENTE DE SERVIR */
#define  STBPLSERVIDA       2000  /* SERVIDA */
#define  STBPLPROCESADA     3000  /* PROCESADA Y ACTUALIZADO STOCK */
#define  STBPLANULADA       4000  /* ANULADA */
#define  STBPLRESTOS        5000  /* LINEA DE RESTOS */
#define  STBPLTEMPORAL      5001  /* TEMPORAL MIO */
#define  STBPLTRATAANU      7100  /* TRATADA ANULACION */
#define  STBUCEPREPARADO    -4000  /* ERROR AL SERVIR */
#define  STBUCERRSELETIQ    -1060  /* ERROR SEL. PARA IMPRIMIR */
#define  STBUCCREADO         100  /* CREADO */
#define  STBUCASIGNADISP     500  /* ASIGNADO A UN DISPLAY */
#define  STBUCPDTEETIQ      1000  /* PENDIENTE DE RESERVAR */
#define  STBUCENFALTA       1020  /* EN MESA DE FALTAS */
#define  STBUCRESERVADO     1050  /* RESERVADO */
#define  STBUCSELETIQ       1060  /* SELECCIONADO PARA IMPRIMIR */
#define  STBUCPDTESERVIR    1200  /* PENDIENTE DE SERVIR */
#define  STBUCMESAFALTAS    1250  /* EN MESA DE FALTAS */
#define  STBUCASITERM       1300  /* ASIGNADO A TERMINAL */
#define  STBUCBULABAN       2000  /* CAJA COMPLETA */
#define  STBUCBULABANETI    2100  /* CAJA COMPLETA ETIQUETADA */
#define  STBUCBULABANREC    2200  /* BULABAN RECOGIDO */
#define  STBUCCC            3000  /* CONTENEDOR COMPLETO */
#define  STBUCCCRECOGIDO    3100  /* CONTENEDOR RECOGIDO */
#define  STBUCPENDRETIRA    3200  /* PENDIENTE RETIRAR */
#define  STBUCPDTEFMD       3975  /* PENDIENTE FMD */
#define  STBUCERRFMD        3980  /* CON ERROR FMD */
#define  STBUCPREPARADO     4000  /* PREPARADO */
#define  STBUCABASCULA      4025  /* A BASCULA */
#define  STBUCAMANIPULAR    4040  /* A MANIPULACION */
#define  STBUCAETIQUETAR    4050  /* A ETIQUETAR */
#define  STBUCAVERIF        4100  /* ENVIADO A VERIFICACION */
#define  STBUCACERRAR       4200  /* ENVIADO A CERRADORA */
#define  STBUCAALBA         4250  /* ENVIADO A ALBARANAR */
#define  STBUCAEXPED        4300  /* ENVIADO A EXPEDICION */
#define  STBUCENEXPED       4400  /* EN EXPEDICION */
#define  STBUCFINALIZADO    5000  /* FINALIZADO */
#define  STBUCDEVUELTO      6000  /* DEVUELTO AL ALMACEN */
#define  STBUCANULADO       7000  /* ANULADO */
#define  STBUCAPARTADO      8000  /* APARTADO */
#define  STBULASERVIR        100  /* PENDIENTE DE SERVIR */
#define  STBULSERVIDA        200  /* SERVIDA */
#define  STBULROTURA         300  /* ROTURA */
#define  STBULANULADA        400  /* ANULADA */
#define  STBZOAZONA           30  /* CAMINO A LA ZONA */
#define  STBZOENCOLA          50  /* EN COLA */
#define  STBZOPDTECONF       100  /* PENDIENTE DE CONFIRMAR */
#define  STBZOENCURSO        200  /* EN CURSO */
#define  STBZOPDTEFIN        300  /* PENDIENTE FIN */
#define  STCASCREADA         100  /* CREADA */
#define  STCASTERMPU        1000  /* TERMINADA PU */
#define  STCASCUBETIZADA    1100  /* CUBETIZADA */
#define  STCASANULADA       1200  /* ANULADA */
#define  STCNTNORMAL           0  /* NORMAL */
#define  STCNTREUBIERROR     100  /* ERROR REUBICANDO CONTENEDOR */
#define  STCNTCERRADO        200  /* CERRADO */
#define  STCSPPENDIENTE      100  /* ENV�O PENDIENTE */
#define  STCSPESPCOMUNIC     500  /* ESPERANDO COMUNIC. SERVER SMTP */
#define  STCSPFINALIZADA    1000  /* ENV�O REALIZADO */
#define  STCSPANULADA       1300  /* ENV�O ANULADO */
#define  STDECCREADA         100  /* CREADA */
#define  STDECPDTERESERV    1000  /* PENDIENTE DE RESERVA */
#define  STDECPROCESANDO    1100  /* PROCESANDO */
#define  STDECRESERVADA     2000  /* RESERVADA */
#define  STDECMVFINAL       3000  /* MOVIMIENTOS FINALIZADOS */
#define  STDECFINALIZADA    4000  /* FINALIZADA */
#define  STDECANULADA       7000  /* ANULADA */
#define  STDELPDTEACTIV      100  /* PENDIENTE DE ACTIVAR */
#define  STDELPDTERESERV    1000  /* PENDIENTE DE RESERVAR */
#define  STDELPROCESANDO    1100  /* PROCESANDO */
#define  STDELRESERVADA     2000  /* RESERVADA */
#define  STDELMVFINAL       3000  /* MOVIMIENTOS FINALIZADOS */
#define  STDELFINALIZADA    4000  /* FINALIZADA */
#define  STDELANULADA       7000  /* ANULADA */
#define  STDELPROCESANUL    7100  /* PROCESADA ANULACI�N */
#define  STDSCCREADA         100  /* CREADA */
#define  STDSCPDTEVALIDA     200  /* PDTE VALIDAR */
#define  STDSCFINALIZADA     300  /* FINALIZADA */
#define  STDSLCREADA         100  /* CREADA */
#define  STDSLRESERVADA      200  /* RESERVADA */
#define  STDSLENCURSO        300  /* ENCURSO */
#define  STDSLFINALIZADA     400  /* FINALIZADA */
#define  STDVCPENDIENTE       50  /* PENDIENTE */
#define  STDVCENCURSO        100  /* EN CURSO */
#define  STDVCESCANEADA      200  /* ESCANEADA */
#define  STDVCPDTEPROTO      300  /* PDTE PROTOCOLO */
#define  STDVCVALPROTO       400  /* PENDIENTE DE DEFECTUOSOS */
#define  STDVCFINALIZADA     500  /* FINALIZADA */
#define  STDVCDEVUELTA       600  /* DEVUELTOS DEFECTUOSOS */
#define  STDVCACEPTADA       700  /* ACEPTADOS DEFECTUOSOS */
#define  STDVLDEVCLIENTE      50  /* DEV. A CLIENTE */
#define  STDVLAPTO           100  /* APTO BLOQUEADA */
#define  STDVLREACOND        150  /* REACOND */
#define  STDVLNOAPTO         200  /* NO APTO */
#define  STDVLDEVEXT         250  /* DEVUELTA A EXTERIOR */
#define  STDVLINVENTARIO     300  /* INVENTARIADA */
#define  STDVLDESTRUIDA      400  /* DESTRUIDA */
#define  STFMDPTEPERIODI      25  /* PENDIENTE DEL PERIODICO */
#define  STFMDPENDIENTE       50  /* PDTE DE CONFIRMAR */
#define  STFMDINFORMADO       75  /* CONFIRMADO/VERIFICADO */
#define  STFMDCREADO         100  /* CREADO */
#define  STFMDENVIADO        200  /* ENVIADO */
#define  STFMDTIMEOUT        300  /* TIMEOUT */
#define  STFMDCORRECTO       400  /* CORRECTO */
#define  STFMDERRVER         500  /* ERROR VERIFICACION */
#define  STFMDANULADO       7000  /* ANULADO */
#define  STFTEERRCREASTK    -100  /* ERROR CREANDO STOCK */
#define  STFTEPENDIENTE      100  /* PENDIENTE DE CREAR STOCK */
#define  STFTEFINALIZADO    1000  /* CREADO STOCK */
#define  STFTEANULADO       2000  /* ANULADO */
#define  STICCPENDPROCES     100  /* PENDIENTE DE PROCESAR */
#define  STICCPROCESADO      200  /* PROCESADO */
#define  STICDERRANULAND    -600  /* ERROR ANULANDO INCIDENCIA */
#define  STICDERRINCCERR    -500  /* ERROR CERRANDO INCIDENCIA */
#define  STICDERRINCIFAC    -400  /* ERROR FACTURANDO INCIDENCIA */
#define  STICDERRINCPROY    -250  /* ERROR DESVIANDO INCIDENCIA */
#define  STICDERRINCPEDI    -225  /* ERROR PIDIENDO INFORMACION */
#define  STICDERRINCIASI    -200  /* ERROR ASIGNANDO INCINDENCIA */
#define  STICDERRINCICRE    -100  /* ERROR CREANDO CORREO DE INCID */
#define  STICDCREADA         100  /* INCIDENCIA ABIERTA */
#define  STICDASIGNADA       200  /* INCIDENCIA ASIGNADA */
#define  STICDPEDINFO        225  /* ENVIADA PETICION INFORMACION */
#define  STICDPROYECTOS      250  /* INC. EN PROYECTOS */
#define  STICDFACTURAN       400  /* INC. ENVIADA A FACTURACION */
#define  STICDCERRADA        500  /* INC. CERRADA */
#define  STICDANULADA        600  /* INC. ANULADA */
#define  STICLPENDPROCES     100  /* PENDIENTE DE PROCESAR */
#define  STICLPROCESADO      200  /* PROCESADO */
#define  STIDIDISPERROR     -1000  /* ERROR MOSTRANDO DISPLAY */
#define  STIDIINACTIVO         0  /* INACTIVO */
#define  STIDILIBRE           50  /* LIBRE */
#define  STIDIAPAGADO        100  /* APAGADO */
#define  STIDIASOCIACAJA     500  /* ASOCIA CAJA PARA PICK. INVERSO */
#define  STIDIASOCIANDOC     550  /* ASOCIANDO CAJA PARA PICK. INVE */
#define  STIDIPIDECIERRE     600  /* PIDE CIERRE DE CAJA */
#define  STIDIPIDEALBA       750  /* PIDE ALBARAN */
#define  STIDIPIDESCANA      760  /* PIDE SCAN ALBARAN */
#define  STIDIPIDEETIQ       770  /* PIDE ETIQUETA */
#define  STIDIPIDESCANET     780  /* PIDE SCAN ETIQUETA */
#define  STIDIPICKING       1000  /* REALIZANDO PICKING */
#define  STIDISIRVEMENOS    1100  /* SIRVE MENOS */
#define  STIDIPASOX0        1200  /* PASO POR CERO */
#define  STIDICONFVACIA     1300  /* CONFIRMA CUBETA VACIA */
#define  STIDICONFSIG       1400  /* CONFIRMA SIGUIENTE CUBETA */
#define  STIDICONFCIERRE    1500  /* CONFIRMA CIERRE CANDADO */
#define  STIDIFINPICKING    1600  /* FIN PICKING */
#define  STIDIFINBULTO      1700  /* FIN BULTO EXPEDICION */
#define  STIDIINFOREG       2000  /* INFORMADO PARA REGULARIZACION */
#define  STIDIVACIADO       3000  /* SOLICITADO VACIADO DE UBICACIO */
#define  STIDIVACIANDO      3100  /* VACIANDO */
#define  STIHDAPAGADO        100  /* DISPLAY APAGADO */
#define  STIHDPENDIENTE      200  /* DISPLAY PENDIENTE */
#define  STIHDPRESENTADO     300  /* PRESENTADO */
#define  STIHOCLIRECERR     -300  /* INTER. RECEP. CLIENTE ERROR */
#define  STIHOENVERR        -200  /* INTERFASE ENVIADO ERROR */
#define  STIHOPENDERR       -100  /* INTERFASE PENDIENTE ERROR */
#define  STIHOPENDIENTE      100  /* INTERFASE PENDIENTE ENVIAR */
#define  STIHOENVIADO        200  /* INTERFASE ENVIADO */
#define  STIHOCLIRECEP       300  /* INTER. RECEPCIONADO EN CLIENTE */
#define  STINCPDTE            50  /* PENDIENTE LANZAR */
#define  STINCCREADO         100  /* CREADO */
#define  STINCENCURSO        200  /* EN CURSO */
#define  STINCDIARIO         250  /* INVENTARIO DIARIO ACTIVO */
#define  STINCFINALIZADO     300  /* FINALIZADO Y VALIDADO */
#define  STINCSINLINEAS      400  /* INVENTARIO SIN L�NEAS */
#define  STINCANULADO        500  /* ANULADO */
#define  STINCPASOCERO       600  /* PASO POR CERO */
#define  STINLCREADO         100  /* CREADO */
#define  STINLENCURSO        200  /* EN CURSO */
#define  STINLFINALIZADO     300  /* FINALIZADO */
#define  STINLVALIDADO       400  /* VALIDADO */
#define  STINOPDTE            50  /* PENDIENTE DE LANZAR */
#define  STINOCREADO         100  /* CONTEO CREADO */
#define  STINOPREASIG        150  /* PREASIGNADO */
#define  STINOASIGNADO       200  /* CONTEO ASIGNADO */
#define  STINOFINALIZADO     300  /* FINALIZADO */
#define  STINOESPMULTI       350  /* ESPERANDO MULTIREFERENCIA */
#define  STINOMASCONTEO      400  /* OTRO RECONTEO REQUERIDO */
#define  STINOACEPTADO       500  /* CONTEO ACEPTADO */
#define  STINONOOK          1000  /* CONTEO NO OK, PDTE RECONTEO */
#define  STINONOKFIN        2000  /* CONTEO NO OK, YA RECONTADO */
#define  STINOSRECONTEO     3000  /* SOLICITADO RECONTEO */
#define  STINOVALIDADO      4000  /* VALIDADO POR PANTALLA */
#define  STINOANULADO       7000  /* ANULADO INVENTARIO */
#define  STINTPDTETTOV10     100  /* PENDIENTE POR TRATAR POR V10 */
#define  STINTENTTOV10       150  /* REGISTRO TRATANDOSE POR V10 */
#define  STINTTTOXV10        200  /* TRATADO POR V10 */
#define  STINTTTOXSGA        300  /* TRATADO POR SGA */
#define  STISPPENDFICH        50  /* PENDIENTE DETERMINAR FICHERO */
#define  STISPPENDIENTE      100  /* IMPRESION PENDIENTE */
#define  STISPPREVISUAL      200  /* FICHERO PREVISUALIZA PREPARADO */
#define  STISPESPCOMUNIC     500  /* ESPERANDO COMUNIC. IMPRESORA */
#define  STISPFINALIZADA    1000  /* IMPRESION REALIZADA */
#define  STISPAUDITADA      1200  /* IMPRESION EN LOCAL AUDITADA */
#define  STISPANULADA       1300  /* IMPRESION ANULADA */
#define  STLOHPENDIENTE      100  /* PENDIENTE DE SER TRATADO */
#define  STLOHFINALIZADO    1000  /* TRATADO POR EL SISTEMA */
#define  STMLSPENDORIG        50  /* PENDIENTE VERIFICAR ORIGEN */
#define  STMLSCREADO         100  /* CREADO */
#define  STMLSREVISAR        150  /* REVISAR */
#define  STMLSCALCULADO      200  /* CALCULADO */
#define  STMLSPENDIENTE      300  /* PENDIENTE */
#define  STMLSFINALIZADO     400  /* FINALIZADO */
#define  STMOVENERROR       -4000  /* EN ERROR */
#define  STMOVEDEPOSITA     -3100  /* ERROR DEPOSITANDO */
#define  STMOVERRRECODEP    -2300  /* ERROR RECODEPOOSITADO */
#define  STMOVERECOGIDO     -2200  /* ERROR RECOGIDO */
#define  STMOVERRPRESENT    -2150  /* ERROR PRESENTADO */
#define  STMOVESINSTOCK     -1950  /* ERROR SIN STOCK */
#define  STMOVERRFLUJO      -1100  /* ERROR ASIGNANDO FLUJO */
#define  STMOVERRPDTEPED    -1000  /* ERROR PENDIENTE DE PEDIDO */
#define  STMOVRECEPCIONA     100  /* RECEPCIONANDO MERCANCIA */
#define  STMOVPDTEPEDIDO    1000  /* PENDIENTE DE PEDIDO */
#define  STMOVPICKINV       1050  /* REORGANIZANDOSE EN PICKING INV */
#define  STMOVPDTEFLUJO     1100  /* PENDIENTE DE ASIGNAR FLUJO */
#define  STMOVPDTERUTA      1200  /* PENDIENTE DE ASIGNAR RUTA */
#define  STMOVESPERARUTA    1250  /* ESPERANDO RUTA */
#define  STMOVPDTEMOVIM     1300  /* PENDIENTE DE MOVIMIENTO */
#define  STMOVPDTECERRAR    1400  /* PENDIENTE CERRAR */
#define  STMOVPDTESTOCK     1900  /* PENDIENTE DE STOCK */
#define  STMOVSINSTOCK      1950  /* SIN STOCK */
#define  STMOVPDTERECOGE    2000  /* PENDIENTE DE RECOGER */
#define  STMOVTEMPPINV      2050  /* CREANDO BULTO PICKING INVERSO */
#define  STMOVASIGNADO      2100  /* ASIGNADO */
#define  STMOVPRESENTADO    2150  /* PRESENTADO */
#define  STMOVRECOGIDO      2200  /* RECOGIDO */
#define  STMOVRECODEPO      2300  /* RECOGIDO Y DEPOSITADO */
#define  STMOVENUBIINTER    3000  /* EN UBICACION INTERMEDIA */
#define  STMOVDEPOSITADO    3100  /* DEPOSITADO */
#define  STMOVACTUALIZA     4000  /* ACTUALIZADO */
#define  STMOVACTPICKING    4100  /* ACTUALIZADO PICKING */
#define  STMOVFINALIZADO    5000  /* FINALIZADO */
#define  STMOVREVISION      5100  /* PENDIENTE REVISION */
#define  STMOVPDTEINTER     5200  /* PENDIENTE INTERFASE */
#define  STMOVDEVOLVIEND    5300  /* DEVOLVIENDO */
#define  STMOVINTERFASAD    6000  /* INTERFASADO */
#define  STMOVSININTER      6100  /* SIN INTERFASE */
#define  STMOVANULADO       7000  /* ANULADO */
#define  STMOVTRATADAANU    7100  /* TRATADA ANULACION */
#define  STMUELIBRE          100  /* MUELLE LIBRE */
#define  STMUEOCUPADO        200  /* MUELLE OCUPADO */
#define  STMUEBLOQUEADO      300  /* MUELLE BLOQUEADO */
#define  STORCPENRECEP       100  /* PENDIENTE DE RECEPCION */
#define  STORCPENREPASO      200  /* PENDIENTE DE REPASO */
#define  STORCACTIVA        1000  /* ORDEN ACTIVA */
#define  STORCFINALIZADA    2000  /* ORDEN FINALIZADA */
#define  STORCANULADA       7000  /* ORDEN DE RECEPCION ANULADA */
#define  STORLACTIVA         100  /* LINEA ACTIVA */
#define  STORLRECHAZADA      150  /* LINEA RECHAZADA */
#define  STORLFINALIZADA     200  /* LINEA FINALIZADA */
#define  STORLANULADA        400  /* LINEA ANULADA */
#define  STORLCOMUNICNOR     520  /* LINEA COMUNICADA DE NORMAL */
#define  STORLCOMUNICANU     540  /* LINEA COMUNICADA DE ANULADA */
#define  STPCALIBRE           50  /* LIBRE */
#define  STPCAASIGBULTO      100  /* ASIGNANDO BULTO */
#define  STPCABULTOASIG      200  /* BULTO ASIGNADO */
#define  STPCADESASIGBU      300  /* DESASIGNANDO BULTO */
#define  STPCAPRESCANT       400  /* PRESENTADA CANTIDAD */
#define  STPECERRVOL        -2600  /* ERROR EN VOLUMETRIA */
#define  STPECERRCREABUL    -2500  /* ERROR AL CREAR BULTOS */
#define  STPECERRLANZ       -2000  /* ERROR EN LANZAMIENTO */
#define  STPECERRAGEN       -400  /* ERROR AL  ASIGNAR AGENCIA */
#define  STPECERRRECIBID    -100  /* ERROR VALIDANDO */
#define  STPECERRLINS          2  /* ERROR PENDIENTE GRABAR LINEAS */
#define  STPECPEDMAN          50  /* GRABADO MANUALMENTE */
#define  STPECRECIBIDO       100  /* RECIBIDO */
#define  STPECVALIDADO       200  /* VALIDADO */
#define  STPECGRABADO        300  /* GRABADO */
#define  STPECPDTEAGEN       400  /* PENDIENTE ASIGNAR AGENCIA */
#define  STPECDIFERIDO       500  /* DIFERIDO */
#define  STPECPDTELINS       900  /* PENDIENTE GRABAR LINEAS */
#define  STPECPDTEDON        950  /* PENDIENTE DE VALIDAR DONACION */
#define  STPECRETENIDO       990  /* RETENIDO */
#define  STPECPDTESERIE     1000  /* PENDIENTE SERIE */
#define  STPECENSERIE       1100  /* EN SERIE */
#define  STPECPDTELANZAR    1200  /* PENDIENTE DE LANZAR */
#define  STPECLANZADO       2000  /* LANZADO */
#define  STPECPDTESTOCK     2100  /* PENDIENTE DE STOCK */
#define  STPECRESERVADO     2500  /* RESERVADO */
#define  STPECPDTEVOL       2600  /* PENDIENTE VOLUMETRIA */
#define  STPECPDTETRACK     2700  /* PENDIENTE TRACKING AGENCIA */
#define  STPECSPRPICKINV    2900  /* TRATANDO SERIE PICKING INVERSO */
#define  STPECPDTEPETSTK    2950  /* PENDIENTE DE PEDIR STOCK */
#define  STPECPREPARANDO    3000  /* PREPARANDOSE */
#define  STPECSERVIDO       4000  /* SERVIDO */
#define  STPECESPFACTURA    4050  /* ESPERANDO DOCUMENTACION */
#define  STPECCONFACTURA    4070  /* RECIBIDA DOCUMENTACION */
#define  STPECPENDASOCIA    4090  /* PENDIENTE ASOCIAR DOCUMENTACIO */
#define  STPECENEXPED       4100  /* EN EXPEDICIONES */
#define  STPECVERSCREADA    4200  /* VERSION CREADA */
#define  STPECFINALIZADO    4300  /* FINALIZADO */
#define  STPECASIGNADA      4350  /* ASIGNADA RUTA */
#define  STPECEXPEDIDO      5000  /* EXPEDIDO */
#define  STPECENTREGADO     5100  /* ENTREGADO */
#define  STPECFALLIDA       5200  /* ENTREGA FALLIDA */
#define  STPECINTERHOST     5500  /* INTERFASADO HOST */
#define  STPECNOCOMPUTA     6000  /* INTERFASADO NO COMPUTABLE */
#define  STPECCONFCERO      6200  /* CONFIRMADO A CERO */
#define  STPECANULADO       7000  /* ANULADO */
#define  STPECANULHOST      7500  /* ANULADO INTERFASADO HOST */
#define  STPECNOSERVIR      8000  /* NO SERVIR ERROR */
#define  STPELASERVIR        100  /* LINEA DE PEDIDO PARA SERVIR */
#define  STPELANULADADIS     200  /* LINPEDIDO ANULADA POR DISP. */
#define  STPELNOSERVIR       300  /* LINEA DE PEDIDO PARA NO SERVIR */
#define  STPELANULADAINT     400  /* LINEA DE PEDIDO ANULADA INTERF */
#define  STPELSERVIDA        500  /* LINEA DE PEDIDO SERVIDA */
#define  STPLTRECPLC         100  /* RECIBIDO DEL PLC */
#define  STPLTPENDEMITIR     200  /* PENDIENTE EMITIR */
#define  STPLTPDTEACK        300  /* PENDIENTE ACK */
#define  STPLTRECACK         400  /* RECIBIDO ACK */
#define  STPLTTRATADO        500  /* TRATADO */
#define  STPLTENVADO         600  /* ENVIADO MENSAJE AL PLC */
#define  STPRTCREADO          50  /* CREADO */
#define  STPRTREPASO         100  /* EN REPASO */
#define  STPRTCERRADO        600  /* CERRADO */
#define  STPRTANULADO        700  /* ANULADO */
#define  STPTEFINALIZADO    1000  /* STOCK CREADO */
#define  STRCCACTIVA        1000  /* ACTIVA */
#define  STRCCFINALIZADA    2000  /* FINALIZADA */
#define  STRCCINTERHOST     3000  /* INTERFASADA CON EL HOST */
#define  STRCCANULADA       7000  /* ANULADA */
#define  STRECINACTIVO       100  /* TERMINAL LIBRE */
#define  STRECBUSCANDO       200  /* TERMINAL BUSCANDO TRABAJO */
#define  STRECASIGNADO       300  /* TERMINAL ASIGNADO */
#define  STRECSINTRAB        400  /* SIN TRABAJO */
#define  STRECCONFORM       1000  /* CON PANTALLA CARGADA */
#define  STRECMENSAJE       2000  /* PRESENTANDO MENSAJE */
#define  STSCLPENDIENTE      100  /* LECTURA PENDIENTE DE TRATAR */
#define  STSCLTRATADA        200  /* LECTURA TRATADA */
#define  STSERDETENIDO       100  /* SERVICIO DETENIDO */
#define  STSERENMARCHA       200  /* SERVICIO EN MARCHA */
#define  STSEXLANZADA        300  /* LANZADA */
#define  STSEXPREPARANDO    1000  /* PREPARANDOSE */
#define  STSEXFINALIZADA    2000  /* FINALIZADA */
#define  STSEXIMPRESA       2100  /* MERCANCIA EXPEDIDA */
#define  STSEXEXPEDIDA      3000  /* SIN INTERFASE */
#define  STSEXCONINTER      4000  /* CON INTERFASE */
#define  STSGTERRTADOV10    -100  /* ERROR TRATADO POR V10 */
#define  STSGTEZVISITADA     -50  /* Z. VISITADA NO SOLICITADA */
#define  STSGTERRIMPR        -40  /* ERROR AL IMPRIMIR */
#define  STSGTTRANSITO        25  /* BULTO EN TRANSITO POR SGT */
#define  STSGTPDTEIMPR        40  /* PENDIENTE DE IMPRIMIR */
#define  STSGTTRATADOSGT      50  /* BULTO TRATADO POR SGT */
#define  STSGTTRATADOV10     100  /* BULTO TRATADO POR V10 */
#define  STSGTTRATETIQER     125  /* TRATADO ERROR ETIQUETADORA */
#define  STSHTPDTEENV         10  /* PENDIENTE DE ENVIAR */
#define  STSHTENVIADO         20  /* ENVIADO */
#define  STSHTTERMINADA       60  /* TERMINADA SALIDA */
#define  STSHTRECIBIDA      1000  /* RECIBIDA ENTRADA */
#define  STSHTENVUBI        1020  /* ENVIADA UBICACION */
#define  STSHTENTRADA       1060  /* ENTRADA REALIZADA */
#define  STSHTPDTEBORRA     2000  /* BORRADA PENDIENTE */
#define  STSHTBORRADA       2010  /* BORRADA */
#define  STSPRPROPUESTA       50  /* PROPUESTA */
#define  STSPRCREADA         100  /* CREADA */
#define  STSPRCONDISPONI     200  /* CON DISPONIBILIDAD */
#define  STSPRLANZADA        300  /* LANZADA */
#define  STSPRPDTEEQUILI     350  /* PDTE EQUILIBRADO (PICKINV) */
#define  STSPRPDTEBULINV     370  /* PDTE BULTO PICKING (PICKINV) */
#define  STSPREQUILIBRAD     380  /* EQUILIBRADAS ESTACIONES */
#define  STSPRPICKINV        390  /* PREPARANDOSE PICKING INVERSO */
#define  STSPRFINPICK        395  /* PICKING FINALIZADO */
#define  STSPRFINALIZADA     400  /* SERIE FINALIZADA */
#define  STSTCPDTE           100  /* PENDIENTE DE ENVIAR */
#define  STSTCENVIADO        200  /* ENVIADO PENDIENTE DE ACK */
#define  STSTCRESPONDIDO     300  /* RESPONDIDO */
#define  STXAIPENDIC         100  /* PENDIENTE C */
#define  STXAIPENDIAB        200  /* PENDIENTE A Y B */
#define  STXAIPROCESADO     1000  /* PROCESADO */
#define  STXCOPENDIENTE      100  /* PENDIENTE */
#define  STXCOPROCESADO     1000  /* PROCESADO */
#define  STXINSOLICITADO     100  /* AUN NO SOLICITADO */
#define  STXINSOLHDS         200  /* SOLICITADO AL MINILOAD */
#define  STXINENODS          250  /* EN EL BUCLE */
#define  STXININVGARE1       300  /* REALIZADA LA PRIMERA ESTACION */
#define  STXININVGARE2       400  /* REALIZADA LA SEGUNDA ESTACION */
#define  STXINFINALIZADO    5000  /* TERMINADO */
#define  STXINANULADO       6000  /* ANULADO */
#define  STXMOPENDIENTE      100  /* PENDIENTE */
#define  STXMOPROCESADO      200  /* PROCESADO */
#define  STXMOANULADO        250  /* ANULADO */
#define  STXSBPENDIENTE      100  /* PENDIENTE */
#define  STXSBPROCESADO     1000  /* PROCESADO */
#define  STZONCERRADA        100  /* CERRADA */
#define  STZONABIERTA        200  /* ABIERTA */
#define  STZONIDDLE          300  /* ABIERTACC */
#define  STZONCONFBULTO     1000  /* CONFIRMA BULTO */
#define  STZONCONBULTO      1100  /* CON BULTOS */
#define  STZONFINBULTO      1200  /* FIN BULTO */
#define  STZONVACIANDO      1300  /* VACIANDO */
#define  STZONRESTOS        2000  /* RESTOS */
#define  STZONCIERRE        3000  /* PIDE CERRAR CAJA */
#define  STZONREGULARIZA    5000  /* REGULARIZACION  */
#define  STZONCONCEREG      5500  /* ESCOGE CONCEPTO REGULARIZA */
#define  STZONCAMBCAJA      7000  /* CAMBIO CAJA */
#define  STZONLEEBULTO      7500  /* LEE BULTO NUEVO */
#define  STZONLEENS         8000  /* LEE NUMEROS DE SERIE */
#define  STZONVERIFART      9000  /* VERIFICANDO ARTICULO */
#define  STZONPDTETARA      9100  /* PENDIENTE TARA */
#define  STZONPDTEVACIA     9200  /* PENDIENTE VACIA */
#define  STZONPDTEPESO      9300  /* PENDIENTE PESO */
#define  STZONVERIFICAND    9400  /* VERIFICANDO */
#define  STZONINVENART      9500  /* INVENTARIO ARTICULO */
#define  STZONINVENTARIO    9600  /* INVENTARIO */
#define  STZONVERIFINVEN    9700  /* VERIFICA INVENTARIO */
#define  STZONSOLSALIDA     9800  /* SOLICITADA SALIDA */
#define  STZONSOLRETIRAD    9900  /* SOLICITADA RETIRADA */
