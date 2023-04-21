# Módulo   : VDSTKART.PAN
# Función  : Selección de artículo a consultar stock
#
# Creación : 01-04-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
SELECCION DE ARTICULO
Codart       
_40_______________ _100______________________________
                                                    |

TABLA=VDARTIC

WHERE=EXISTS (SELECT 1 FROM VDSTOCK STK WHERE STK.CODART=VDARTIC.CODART);


CAMPO=CODART,TOOLTIP("Código del artículo"),CONTEXTUAL=FEJECUTA(FEJECUTAFORM("VDSELART","N","","","CODART=:CODART","SELECCION DE ARTICULOS","S"),"",
                                                                           FPULSATECLAS("F2")),TITULO("Artículo")
CAMPO=DESART,TOOLTIP("Designación del artículo"),TITULO("Designación")

                        
TECLA=SF9,FEJECUTAFORM("VDSTKCALIFLOT.FRM","N","LOT.CODART=:CODART","","","DESGLOSE DE STOCK POR CALIFICACION DE ARTICULO :CODART","S")                        


