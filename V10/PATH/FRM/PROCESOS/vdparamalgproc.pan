######
# VDPARAMALGPROC.PAN - Sistema de ventanas para configurar los parámetros que se le pasan a los diferentes procedimientos y algoritmos
#
# Propósito: Ventana para configurar los parámetros que se le pasan a los diferentes procedimientos y algoritmos
#
#
# Autor	   : José Carlos Santos
# Fecha    : 26-12-2007
####
# Modificaciones:
####

Pos. Tipo Inf.  Nombre           Descripción
@L@  _     _    _32____________  _255__________________________________________________________
|

TABLA=VDPARAMALGPROC

ORDERBY=POSICION;


CAMPO=FUNCION, VIRTUAL,OCULTO
CAMPO=TIPOPROC,VIRTUAL,OCULTO
CAMPO=POSICION,UPPER,TOOLTIP("Posición del parametro"),TITULO("Pos")
CAMPO=TIPO,UPPER,TOOLTIP("Tipo del parametro puede ser C(adena) o N(umerico)"),POSTCHANGE=FVERIFICA("CN","Debe introducir C(adena) o N(umerico)"),TITULO("Tipo"),WLONX=15
CAMPO=INFORMAR,UPPER,TOOLTIP("Indica si es obligatorio o no informar este campo"),TITULO("Inf."),WLONX=15
CAMPO=NOMBREPARAM,UPPER,TITULO("Nombre")
CAMPO=DESCRIPCION,UPPER,TITULO("Descripción")
