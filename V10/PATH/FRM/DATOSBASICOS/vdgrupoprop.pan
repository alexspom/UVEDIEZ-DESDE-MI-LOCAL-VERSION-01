# Módulo   : VDGRUPOPROP.PAN
# Función  : Mantenimiento de grupos de propiedades
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE CONFIGURACION
Grupo                                                Privilegios para ver               Ultima modificación
____________________ _40____________________________ _1000_____________________________ _32_________ ¿D-MM-Y.YY ________
|

TABLA=VDGRUPOPROP

WHERE=VDUSER.TENGOPRIVILEGIO(PRIVILEGIOSVER)=1;
ORDERBY=GRUPOPROP;


PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

CAMPO=GRUPOPROP,NOUPDATE,TOOLTIP("Código del grupo de propiedades"),TITULO("Grupo")
CAMPO=DESGRUPOPROP,MIXED,TOOLTIP("Designación del grupo de propiedades"),TITULO("Descripción")
CAMPO=PRIVILEGIOSVER,TOOLTIP("Privilegios necesarios para ver el grupo"),TITULO("Privilegios para ver"),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CLISTAPRIV SELECT PRIVILEGIO,COMENTARIO FROM VDPRIVILEGIO ORDER BY PRIVILEGIO;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;




