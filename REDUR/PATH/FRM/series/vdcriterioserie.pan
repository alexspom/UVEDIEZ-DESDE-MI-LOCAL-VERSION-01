###################################################################
#Módulo: VDCRITERIOSERIE.PAN
#Funcionalidad : Selección de criterios para la creación de series de preparación
#Autor: FPD      
#Fecha: 08-04-2008
###################################################################
# Histórico de cambios:
CRITERIOS DE CREACION DE SERIES DE PREPARACION 

     Desde       Hasta      Agencia                       Tipo    Cliente                 Div.      Ruta                                                                
   ¿D-MM-Y.YY  ¿D-MM-Y.YY   _10_____ _30________________  _60__   _60__________________   _20____   _20_________________
| 

NOQUERY
WLONX=965
WLONY=70
WFRAME(10,-2,175,55,"Fecha de entrega","")
WFRAME(190,-2,210,55,"Transporte","")
WFRAME(405,-2,45,55,"Tipo","")
WFRAME(455,-2,165,55,"Cliente","")
WFRAME(625,-2,70,55,"Divisón","")
WFRAME(700,-2,165,55,"Ruta","")
PREBLOQUE=FPREGUNTAR("0")

POSTQUERY=FRECALCPADRE


CAMPO=CODSERIEPREP,VIRTUAL,AUXILIAR,OCULTO
CAMPO=FECHADESDE,AUXILIAR,TOOLTIP("Fecha de servicio prevista para el pedido desde la cual seleccionar"),COMBOX("CALENDARIO"),TITULO("Desde")
CAMPO=FECHAHASTA,AUXILIAR,TOOLTIP("Fecha de servicio prevista para el pedido hasta la cual seleccionar"),COMBOX("CALENDARIO"),TITULO("Hasta")
CAMPO=URGENCIAMIN,AUXILIAR,TOOLTIP("Urgencia mínima del pedido para seleccionar. 0 Máxima 99 Mínima"),TITULO("Mínima"),WLONX=40,OCULTO,"@L"
CAMPO=URGENCIAMAX,AUXILIAR,TOOLTIP("Urgencia máxima del pedido para seleccionar. 0 Máxima 99 Mínima"),TITULO("Máxima"),WLONX=40,OCULTO,"@L"
CAMPO=CODAGEAUX,AUXILIAR,TOOLTIP("Código de agencia del pedido"),TITULO("Agencia"),
                POSTCHANGE=FDESIGNACION("+CSELDESAGE",""),COMBOX("CLISTAAGE")
CAMPO=DESAGEAUX,AUXILIAR,NOENTER,TOOLTIP("Descripción de la agencia del pedido")
CAMPO=TIPOPEDIDOAUX,AUXILIAR,TITULO("Tipo")
CAMPO=PEDIDOCLIENTEAUX,AUXILIAR,TITULO("Referencia"),OCULTO,"_1024"
CAMPO=CLIENTEAUX,AUXILIAR,TOOLTIP("Código de cliente que realiza el pedido"),TITULO("Cliente")
CAMPO=CODDIVAUX,AUXILIAR,TOOLTIP("Código de división del pedido"),TITULO("División")  
CAMPO=CODRUTAAUX,AUXILIAR,TOOLTIP("Código de ruta"),TITULO("Ruta"),COMBOX("CLISTARUTA")            
CAMPO=TODOS,VIRTUAL,OCULTO,AUXILIAR,NOUPDATE


CURSOR=CSELTODOS SELECT 'S' TODOS FROM DUAL;
CURSOR=CSELNINGUNO SELECT 'N' TODOS FROM DUAL;

CURSOR=CLISTADIV SELECT CODDIV,DESDIV FROM VDDIVIS ORDER BY CODDIV;

CURSOR=CLISTAAGE SELECT CODAGE,DESAGE FROM VDAGENCIA ORDER BY CODAGE;

CURSOR=CSELDESAGE SELECT DESAGE DESAGEAUX
                    FROM VDAGENCIA
                   WHERE CODAGE=:CODAGEAUX;
  
CURSOR=CSELDIVIS SELECT DESDIV DESDIVAUX
                   FROM VDDIVIS
                  WHERE CODDIV=:CODDIVAUX;

CURSOR=CLISTARUTA SELECT CODRUTA,DESRUTA FROM VDRUTAS ORDER BY CODRUTA;


TECLA=SF5,FEJECUTA("CSELTODOS","",FPULSATECLAS("F6","F3","F2"))
TECLA=SF6,FEJECUTA("CSELNINGUNO","",FPULSATECLAS("F6","F3","F2"))

BOTON=P2,1215,100,110,40,"Selecciona \nTodos",NO,SF5,"Selecciona \nTodos",INCLUDECSS="background-color: green;border-width:1px"
BOTON=P3,1335,100,110,40,"Selecciona \nNinguno",NO,SF6,"Selecciona \nNinguno",INCLUDECSS="background-color: red;border-width:1px"
