# M�dulo   : VDASIUSUGRU.PAN
# Funci�n  : Asignaci�n de un usuario a grupos
#
# Creaci�n : 01-10-2007
# Autor    : EAA
###########################################
# Hist�rico de cambios:
ASIGNACION DE USUARIO A GRUPOS
Grupo                Ultima modificaci�n
____________________ _32_______ �D-MM-Y.YY _8________
|

TABLA=VDGRUPOOPE


PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

CAMPO=CODOPE,VIRTUAL,OCULTO
CAMPO=CODGRUPO,POSTCHANGE=FDESIGNACION("CSELGRU","No existe grupo"),TOOLTIP("Grupo con el usuario"),
              CONTEXTUAL=FEJECUTAFORM("VDLISTAGRUPO","N","","","CODGRUPO=:CODGRUPO","LISTA DE GRUPOS","S"), TITULO("Grupo"),
              COMBOX("CLISTAGRUPO")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realiz� la �ltima modificaci�n"),TITULO("Ultima modificaci�n")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CLISTAGRUPO SELECT CODGRUPO,DESGRUPO FROM VDGRUPO ORDER BY CODGRUPO;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CSELGRU SELECT :CODGRUPO FROM VDGRUPO WHERE CODGRUPO=:CODGRUPO;


