# Módulo   : VDMONFECHAS.PAN           
# Función  : Entrada de fechas 
#                                          
# Creación : 16-08-2008                    
# Autor    : MGM                           
###########################################
DETERMINAR FECHAS
 Desde: ¿D-MM-Y.YYY    Hasta: ¿D-MM-Y.YYY 

                                           |

NOQUERY
CAMPO=FECDESDE,AUXILIAR,COMBOX("CALENDARIO")
CAMPO=FECHASTA,COMBOX("CALENDARIO")
