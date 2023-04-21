###################################################################
#Módulo: VDARTESPSTOCK1.PAN
#Funcionalidad : Consulta GLOBAL de COMENTARIOS de Reserva de Pedidos Esperando Stock
#Autor: FGS      
#Fecha: 01-04-2008
###################################################################
#Histórico de cambios:
MOVIMIENTOS ESPERANDO A RECARGAS
                        
Artículo                                      Movimientos 
_40____________ _100_______________________   @L@@@
|


SOLOQUERY
SELECT=SELECT MOV.CODART,DESART,COUNT(*) TOTALMOV
         FROM VDMOVIM MOV,VDARTIC ART 
        WHERE STATUS IN (1200,VDST.FMOVESPERARUTA) AND MOV.CODART=ART.CODART;
GROUPBY=MOV.CODART,DESART;
ORDERBY=TOTALMOV DESC;


CAMPO=CODART,AUXILIAR,UPPER,TOOLTIP("Es el Código del artículo a servir"),TITULO("Artículo")
CAMPO=DESART,NOUPDATE,AUXILIAR,UPPER
CAMPO=TOTALMOV,NOUPDATE,AUXILIAR




