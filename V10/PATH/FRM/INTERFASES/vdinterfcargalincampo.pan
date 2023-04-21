#*****************************************************************
#Módulo: VDINTERFCARGALINCAMPO.PAN
#Funcionalidad : 
#Autor: ICC      
#Fecha: 29-04-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
#
#*****************************************************************
VALORES DE CADA UNO DE LOS CAMPOS DEL REGISTRO SELECCIONADO
 Campo                            Valor                                                                           
 _32_____________________________ _100______________________________________________________________________________________
                                                                                                                             |

SELECT=SELECT CAMPO, VALOR||'#' VALOR
         FROM TABLE (VDINTERF.OBTVALORESCAMPOS(:TIPOINTERFASE,:FORMATO, :REGISTRO));
SOLOQUERY

CAMPO=TIPOINTERFASE,VIRTUAL,AUXILIAR,OCULTO,TOOLTIP("Tipo de interfase")
CAMPO=FORMATO,VIRTUAL,AUXILIAR,OCULTO,TOOLTIP("Tipo de formato (o segmento para SAP) para una interfase")
CAMPO=REGISTRO,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CAMPO,TOOLTIP("Nombre del campo de V10 en la interfase"),TITULO("Campo")
CAMPO=VALOR,TOOLTIP("Valor del campo en el registro seleccionado"),TITULO("Valor")

