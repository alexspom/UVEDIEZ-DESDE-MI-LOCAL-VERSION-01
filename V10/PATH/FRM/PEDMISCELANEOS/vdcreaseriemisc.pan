###################################################################
#Módulo: VDCREASERIEMISC.PAN
#Funcionalidad : Selección de pedidos misceláneos para la creación de una serie de preparación
#Autor: RFD     
#Fecha: 29-09-2009
###################################################################
# Histórico de cambios:
PEDIDOS MISCELANEOS PENDIENTES DE INCLUIR EN SERIE
                                     ÏÄÄÄÄÄÄÄÄÄÄÄ  CLIENTE  ÄÄÄÄÄÄÄÄÄÄÄË                                     
 Pedido               Div.    Año  Sec.  Código       Descripción           Tipo  Fecha Serv. P.   U. Agencia     Inc.       
 _20_________________ _20_    @@@@ @@@   _12_________ _40_________________  _10__ ¿D-MM-Y.YY  @@   @@  _30_______   _ 

|

TABLA=VDPEDIDOCAB
WHERE=NVL(CODSERIEPREP,0)=0 AND SWTMISCELANEO='S' AND STATUS=VDST.FPECMISCELANEO;
ORDERBY=PRIORIDAD,FECSERVICIO,URGENCIA;

REGPAG=50

NOINSERT
NODELETE
NOUPDATE
NOLOCK

PRECOMMIT=FEJECUTA("CSELSECSERIE","ERROR SELECCIONANDO Código DE SERIE",
                   "CINSSERIE","ERROR CREANDO UNA SERIE DONDE INCLUIR LOS PEDIDOS")

PREUPDATE=FEJECUTA("CUPMETEPEDERIE","Error al registrar pedido :CODPED en  la serie :CDSERIEPREP")

POSTCOMMIT=FEJECUTA("@CSELCODAGE","NO SE PUEDE OBTENER AGENCIA",
                                FWHILE(FERRORCURSOR("CSELCODAGE"),
                                       FEJECUTA("CSELSERIEEXP","NO SE PUEDE OBTENER SECUENCIAL DE SERIE DE EXPEDICION",
                                                "CINSSEXP","NO SE PUEDEN INSERTAR LAS SERIES DE EXPEDICION",
                                                "CUPDPEDIDOS","NO SE PUEDEN ACTUALIZAR LAS CABECERAS DE PEDIDO",
                                                +FFETCHCURSOR("CSELCODAGE"),"ERROR EN FETCH")),"ERROR EN FWHILE",
                    +FPULSATECLAS("CF2","F2"),"")

CAMPO=CODPED,NOUPDATE,TOOLTIP("Código del pedido"),TITULO("Pedido")
CAMPO=CODDIV,NOUPDATE,TOOLTIP("Division o compañia del pedido"),TITULO("División"),WLONX=28
CAMPO=ANOPED,NOUPDATE,TOOLTIP("Año del pedido"),TITULO("Año"),WLONX=15
CAMPO=SEQPED,NOUPDATE,TOOLTIP("Versión del pedido"),TITULO("Vers."),WLONX=20
CAMPO=CODCLIENTE,NOUPDATE,TOOLTIP("Es el Código de cliente que realiza el pedido."),TITULO("Cliente")
CAMPO=DESCLIENTE,NOUPDATE,TOOLTIP("Cliente al que se sirve el pedido\n :DESCLI ")
CAMPO=TIPOPEDIDO,NOUPDATE,TOOLTIP("Identifica el tipo del pedido según criterio de la compañía. Es recibido del Host y \ntal como se recibe se introduce en la Base de datos. Tiene utilidad para establecer \nrestricciones a la hora de crear series de pedidos."),TITULO("Tipo")
CAMPO=FECSERVICIO,NOUPDATE,TOOLTIP("Fecha prevista de servicio del pedido."),TITULO("Fec.Serv.")
CAMPO=PRIORIDAD,NOUPDATE,TOOLTIP("Prioridad para reservar stock"),TITULO("Pri"),WLONX=15
CAMPO=URGENCIA,NOUPDATE,TOOLTIP("Urgencia del pedido 0 Máxima 99 Mínima."),TITULO("Ur"),WLONX=10
CAMPO=CODAGE,NOUPDATE,OCULTO,"_10_",TOOLTIP("Es el Código de la agencia de transporte para el pedido."),POSTCHANGE=FDESIGNACION("CSELDESAGE","NO SE PUEDE OBTENER DESCRIPCION DE LA AGENCIA")
CAMPO=DESAGE,AUXILIAR,NOENTER,TOOLTIP("Es la descipción de la agencia dee transporte para el pedido."),TITULO("Agencia")           
CAMPO=INCLUIR,UPPER,AUXILIAR,TOOLTIP("Indica si este pedido se incluye en la serie"),POSTCHANGE=FEJECUTA(FVERIFICA("SN ","Valores permitidos son: S, N o blanco"),""),TITULO("Inc"),WLONX=30
CAMPO=CODSERIEPREP,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODAGEAUX,AUXILIAR,OCULTO,"_10_"
CAMPO=CODSERIEEXPAUX,AUXILIAR,OCULTO,"@@@@@@"

CURSOR=CSELSECSERIE SELECT VDSECSERIEPREP.NEXTVAL CODSERIEPREP
                      FROM DUAL;

CURSOR=CINSSERIE INSERT INTO VDSERIEPREP ( 
                    CODSERIEPREP,PRIORIDAD,SWTPICKINGINV,SWTPICKINGAGR,
                    TIPOPUERTO,CODOPECREADA,FECCREADA,HORACREADA,CODOPELANZA,
                    FECLANZA,HORALANZA,FECTERMIN,HORATERMIN,STATUS,CODCOMEN,
                    VDEXTRA,CODOPEMODIF,FECMODIF,HORAMODIF)
                 SELECT :CODSERIEPREP,0,NULL,NULL,
                        NULL,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,VDUSER.GETUSER,
                        VD.FECHASYS,VD.HORASYS,VD.FECHASYS,VD.HORASYS,VDST.FSPRLANZADA,0,
                        NULL,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS
                   FROM DUAL;

CURSOR=CSELDESAGE SELECT DESAGE
                    FROM VDAGENCIA
                   WHERE CODAGE=:CODAGE;

CURSOR=CUPMETEPEDERIE UPDATE VDPEDIDOCAB 
                         SET CODSERIEPREP=DECODE(:INCLUIR,'S',:CODSERIEPREP,0),
                             CODOPEMODIF=VDUSER.GETUSER,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS
                       WHERE :INCLUIR='S' AND
                             CODDIV=:CODDIV AND ANOPED=:ANOPED AND 
                             CODPED=:CODPED AND SEQPED=:SEQPED; 

CURSOR=CSELCODAGE SELECT DISTINCT CODAGE CODAGEAUX
                    FROM VDPEDIDOCAB
                   WHERE CODSERIEPREP=:CODSERIEPREP;

CURSOR=CSELSERIEEXP SELECT VDSECSERIEEXP.NEXTVAL CODSERIEEXPAUX
                      FROM DUAL;

CURSOR=CINSSEXP INSERT INTO VDSERIEEXP (CODSERIEEXP,CODSERIEPREP,ANOBOLETA,CODBOLETA,CODAGE,
                                        PUERTO,PRIORIDAD,CODOPELANZA,FECLANZA,HORALANZA,FECTERMIN,
                                        HORATERMIN,FECEXPIDE,HORAEXPIDE,STATUS,CODCOMEN,VDEXTRA,
                                        CODOPEMODIF,FECMODIF,HORAMODIF)   
                                       (SELECT :CODSERIEEXPAUX,:CODSERIEPREP,0,0,AGE.CODAGE,
                                               AGE.PUERTO,SPR.PRIORIDAD,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,
                                               0,NULL,0,NULL,VDST.FSEXLANZADA,0,NULL,
                                               VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS
                                          FROM VDAGENCIA AGE,VDSERIEPREP SPR
                                           WHERE SPR.CODSERIEPREP=:CODSERIEPREP AND AGE.CODAGE=:CODAGEAUX);

CURSOR=CUPDPEDIDOS UPDATE VDPEDIDOCAB 
                      SET CODSERIEEXP=:CODSERIEEXPAUX
                    WHERE CODSERIEPREP=:CODSERIEPREP AND STATUS+0=VDST.FPECMISCELANEO AND
                          CODAGE=:CODAGEAUX; 


CONTEXTUAL=FEJECUTAFORM("VDPEDIDOS","S","CODPED=:CODPED AND CODDIV=:CODDIV AND SEQPED=:SEQPED AND ANOPED=:ANOPED")

ONLINE={F4} Incluye pedidos en serie    {May+F10} Mantenimiento de pedido;
