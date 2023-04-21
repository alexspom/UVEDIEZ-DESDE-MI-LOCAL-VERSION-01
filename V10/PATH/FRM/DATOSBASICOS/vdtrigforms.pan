# Módulo   : VDTRIGFORMS.PAN
# Función  : Mantenimiento de trigers del forms
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE TRIGERS DEL FORMS

Grupo       Función            T           C Librería triger    A Descripción                             Ultima modificación
_32________ _32_______________ _ _20______ _ _256______________ _ _256___________________________________ _32________ ¿D-MM-Y.YY ________
|

TABLA=VDTRIGFORMS
WHERE = GRUPOTRIGER LIKE :GRUPOTRIGERAUX;
ORDERBY=GRUPOTRIGER,CLASETRIGER,FUNTRIGER;



POSTQUERY=FEJECUTA("CDESTIPOTRIGER","ERROR EN CDESTIPOTRIGER")

PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

CAMPO=GRUPOTRIGERAUX,AUXILIAR,VIRTUAL("GRUPOTRIGER"),OCULTO
CAMPO=GRUPOTRIGER,TOOLTIP("GRUPO AL QUE PERTENECE EL TRIGGER"),TITULO("Grupo")
CAMPO=FUNTRIGER,MIXED,TOOLTIP("Función que ejecuta el triger"),TITULO("Función")
CAMPO=TIPOTRIGER,TOOLTIP("Tipo del triger puede ser R(adio), P(antalla) o (A)mbos"),POSTCHANGE=FVERIFICA("ARP","Tiene que introducir R(adio), P(antalla) o (A)mbos"),TITULO("Tipo Triger")
CAMPO=DESTIPOTRIGER,AUXILIAR,NOENTER
CAMPO=CLASETRIGER,TOOLTIP("CLASE DE TRIGER: (N)ormal o (I)nicilización"),POSTCHANGE=FVERIFICA("IN","Debe introducir (N)ormal o (I)nicialización de conjunto de Trigers"),TITULO("C")
CAMPO=LIBTRIGER,TOOLTIP("Libreria que contiene el triger"),TITULO("Librería Triger")
CAMPO=ACTIVO,TOOLTIP("Indica si el triger esta activo"),POSTCHANGE=FVERIFICA("SN","Tiene que introducir S(i) o N(o)"),TITULO("A")
CAMPO=DESTRIGER,TOOLTIP("Descripción del Triger"),TITULO("Descripción")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CDESTIPOTRIGER SELECT DECODE(:TIPOTRIGER,'P','PANTALLA','R','RADIO','A','AMBAS','ERROR') DESTIPOTRIGER FROM DUAL;
CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;



