# Módulo   : VDGRUPO.PAN
# Función  : Mantenimiento de grupos de usuarios
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE GRUPOS DE USUARIOS
Grupo                                             D. M. m. L. Rep.  Cad.  A. Ultima modificación
_20_______________ _40___________________________ @L @L @L @L @L@@@ @L@@@ @L _32________ ¿D-MM-Y.YY  ________
|

TABLA=VDGRUPO
ORDERBY=CODGRUPO;


PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")



CAMPO=CODGRUPO,TOOLTIP("Código del grupo de usuarios"),TITULO("Grupo")
CAMPO=DESGRUPO,TOOLTIP("Designación del grupo de usuarios"),TITULO("Descripcion")
CAMPO=MINDIG,TOOLTIP("Mínimo número de digitos numericos en el password de los miembros del grupo"),TITULO("D")
CAMPO=MINMAY,TOOLTIP("Mínimo número de mayusculas en el password de los miembros del grupo"),TITULO("M")
CAMPO=MINMIN,TOOLTIP("Mínimo número de minusculas en el password de los miembros del grupo"),TITULO("m")
CAMPO=MINLON,TOOLTIP("Mínima longitud en el password de los miembros del grupo"),TITULO("L")
CAMPO=MINREP,TOOLTIP("Mínimo número de días antes de repetir el password de los miembros del grupo"),TITULO("Rep")
CAMPO=CADUCA,TOOLTIP("Número de días antes de que tengan que cambiar el password los miembros del grupo"),TITULO("Cad")
CAMPO=AVISAR,TOOLTIP("Número de días para avisar antes de que el password de los miembros del grupo caduque"),TITULO("A")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")




CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


