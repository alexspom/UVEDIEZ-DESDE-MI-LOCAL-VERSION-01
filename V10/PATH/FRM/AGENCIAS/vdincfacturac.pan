# Módulo   : VDFACPED.PAN
# Función  : Listado de Facturacion
#
# Creación : 01-06-2007
# Autor    : RGP
#
# Comentarios:
#  Si es un pedido de REPALETIZACION, el pedido original lo marcaremos con 'R' en el 
#  campo REPALETIZACION y con 'S' en REPALETIZACION del pedido nuevo. Los pedidos
#  marcados con 'S' no se facturara la manipulacion ni transporte en SAP. Nos basaremos
#  en el pedido original  ya que facturamos por peso y no por bultos.
###########################################
INCIDENCIAS DE COSTE DE FACTURACION DE TRANSPORTE
 Div. Pedido            Cliente             Agencia              Fec. Term.       
 _20_ @L@@ _20_________ @L@ _40____________ _10____ _30_________ ¿D-MM-YYYY  _1024_____________________________________________________________
|

SOLOQUERY


SELECT=SELECT CODPED,CODDIV,ANOPED,SEQPED,PRECVTOTAL,FECTERMIN,DESCLIENTE,CODAGE,MENSAJEV
         FROM (SELECT CODPED,CODDIV,ANOPED,SEQPED,FECTERMIN,DESCLIENTE,CODAGE,
                      VDAUTOFAC.SELPRECIOPED('C',CODPED,CODDIV,ANOPED,SEQPED) PRECVTOTAL,
                      NVL(VDAUTOFAC.LASTERROR,'     <<SIN ERROR PERO CON IMPORTE 0>>') MENSAJEV
                 FROM VDPEDIDOCAB WHERE STATUS>=VDST.FPECEXPEDIDO AND STATUS<>VDST.FPECANULADO AND FACTAGENCIA IS NULL) 
        WHERE NVL(PRECVTOTAL,0)=0
        AND (:BCODDIV     IS NULL OR (:BCODDIV     IS NOT NULL AND CODDIV=:BCODDIV))
        AND ANOPED=DECODE(:BANO,0,ANOPED,:BANO)
        AND CODPED=NVL(:BPED,CODPED)
        AND FECTERMIN BETWEEN DECODE(:FECHAINICIO,0,FECTERMIN,:FECHAINICIO) AND DECODE(:FECHAFIN,0,FECTERMIN,:FECHAFIN)
        AND CODAGE=NVL(:BAGEN,CODAGE);
        
ORDERBY= FECTERMIN DESC,CODDIV ASC, ANOPED DESC, CODPED ASC,SEQPED ASC;
#POSTQUERY=FEJECUTA("CSELERROR","")        

CURSOR=CSELERROR SELECT NVL(VDAUTOFAC.LASTERROR,'     <<SIN ERROR PERO CON IMPORTE 0>>') MENSAJEV FROM DUAL;

NOINSERT
NOUPDATE
NODELETE
REGPAG=37

CAMPO=BCODDIV,    AUXILIAR,VIRTUAL,OCULTO
CAMPO=BANO,       AUXILIAR,VIRTUAL,OCULTO
CAMPO=BPED,       AUXILIAR,VIRTUAL,OCULTO
CAMPO=FECHAINICIO,AUXILIAR,VIRTUAL,OCULTO
CAMPO=FECHAFIN,   AUXILIAR,VIRTUAL,OCULTO
CAMPO=BAGEN,      AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODDIV,TITULO("Div.")
CAMPO=ANOPED,TITULO("Pedido")
CAMPO=CODPED
CAMPO=SEQPED
CAMPO=DESCLIENTE,TITULO("Cliente")
CAMPO=CODAGE,POSTCHANGE=FDESIGNACION("CDESAGE","Código de agencia no existe."),TITULO("Agencia")
CAMPO=DESAGE,AUXILIAR,NOENTER
CAMPO=FECTERMIN,TITULO("Fec. Termin"),WLONX=30
CAMPO=MENSAJEV,AUXILIAR,NOENTER,TITULO("Mensaje Env.")
CAMPO=PRECVTOTAL,AUXILIAR,OCULTO,"#L##############.###"

######################################################################################################
####################### CAMPOS OCULTOS ###############################################################
######################################################################################################

CAMPO=STATUS,OCULTO,"@L@@"

CURSOR=CDESAGE SELECT DECODE(:CODAGE,NULL,NULL,DESAGE) DESAGE
                 FROM VDAGENCIA
                WHERE CODAGE=:CODAGE OR :CODAGE IS NULL;


TECLA=SF10,FEJECUTAFORM("VDPEDIDOS","S","CODDIV=:CODDIV AND CODPED=:CODPED AND ANOPED=:ANOPED AND SEQPED=:SEQPED","","","","S")

AYUDA=CAMBIO DE RUTA
ONLINE=  {F1} Ayuda    {F5} Borra pantalla    {F11} Exportar a Excel    {May-F10} Consultar Pedido    {Esc} Salir 
         {Ctrl-F5} Consultar entre Fechas;