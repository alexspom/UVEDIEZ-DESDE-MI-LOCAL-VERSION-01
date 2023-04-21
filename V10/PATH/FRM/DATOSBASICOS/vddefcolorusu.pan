# M�dulo   : VDUSUARIO.PAN
# Funci�n  : Mantenimiento de usuarios
#
# Creaci�n : 01-10-2007
# Autor    : EAA
###########################################
# Hist�rico de cambios:
#
ASIGNACION DE TEMAS A USUARIOS
C�digo     Nombre           Apellido 1          Apellido 2        Tema       Ultima modificaci�n
__________ _30_____________ _30________________ _30______________ _20_______ _32_________ �D-MM-Y.YY ________
|

TABLA=VDUSUARIO

PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")

CAMPO=CODOPE,NOUPDATE,POSTCHANGE=FVALNOCERO("Debe introducir C�digo del operario")
CAMPO=NOMBRE,NOENTER
CAMPO=APELLIDO1,NOENTER
CAMPO=APELLIDO2,NOENTER
CAMPO=TEMA,POSTCHANGE=FDESIGNACION("CSELDESTEMA","ERROR, TEMA SELECCIONADO NO EXISTE"),TOOLTIP("Tema de colores\n:DESTEMA")
CAMPO=DESTEMA,AUXILIAR,OCULTO,"_40_"
CAMPO=CODOPEMODIF,NOENTER
CAMPO=FECMODIF,NOENTER
CAMPO=HORAMODIF,NOENTER

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELDESTEMA SELECT DESTEMA FROM VDDEFTEMA WHERE TEMA=:TEMA
                    UNION
                   SELECT NULL DESTEMA FROM DUAL WHERE :TEMA IS NULL;


