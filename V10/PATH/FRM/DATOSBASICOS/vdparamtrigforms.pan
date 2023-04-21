######
# VDPARAMTRIGFORM.PAN 
# 
# Propósito: Definición de parámetros de trigers
#               
#           
# Autor	   : FCO JOSE GUERRERO
# Fecha    : 03-106-2008
####
# Modificaciones:
####
PARAMETROS DEL TRIGER
 Pos. TipoParam   Tipo Oblig. Nombre           Descripción
 @L@  _1________  _1__ _1____ _32____________  _255_____________________________________________________________________________ 
|

TABLA=VDPARAMALGPROC

ORDERBY=POSICION;

CAMPO=FUNCION, VIRTUAL("FUNTRIGER"),OCULTO
CAMPO=POSICION,UPPER,TITULO("Pos")
CAMPO=TIPOPROC,POSTCHANGE=FVERIFICA("Tt","TIPO DE PARAMETRO DEBE SER (T)RIGER"),TOOLTIP("TIPO DE PARAMETRO: (T)RIGER"),TITULO("Tipo Param")
CAMPO=TIPO,UPPER,TITULO("Tipo")
CAMPO=INFORMAR,UPPER,TOOLTIP("SI EL PARAMETRO ES OBLIGATORIO"),POSTCHANGE=FEJECUTA(FVERIFICA("S "),"DEBE INTRODUCIR (S)I O BLANCO"),TITULO("Oblig.")
CAMPO=NOMBREPARAM,UPPER,TITULO("Nombre")
CAMPO=DESCRIPCION,UPPER,TITULO("Descripción")

