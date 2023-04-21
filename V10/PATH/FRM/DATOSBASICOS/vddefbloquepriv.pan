# Módulo   : VDDEFBLOQUE.PAN
# Función  : Mantenimiento de propiedades por defecto de bloques
#
# Creación : 18-12-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
CARACTERISTICAS POR DEFECTO DE BLOQUE DE DATOS
Pantalla       Grupo       T PrivInsert          PrivDelete          PrivNoenter         PrivNoupdate        PrivNoorains        Ultima modificación
_40___________ _32________ _ _ _1024____________ _ _1024____________ _ _1024____________ _ _1024____________ _ _1024____________ _32________ ¿D-MM-Y.YY  ________
|


TABLA=VDDEFBLOQUE


PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")



CAMPO=NBLOQUE,TOOLTIP("Nombre del bloque"),TITULO("Pantalla")
CAMPO=GRUPOBLOQUE,TOOLTIP("Grupo de pantallas al que pertenece el bloque"),TITULO("Grupo")
CAMPO=TIPOPANTALLA,TOOLTIP("Tipo de pantallas a las que se aplican los defectos puede ser F(orms) R(adios) o A(mbos)"),TITULO("T")
CAMPO=CNOINSERT,TOOLTIP("Si tiene protegido para no INSERT"),TITULO("I")
CAMPO=PRIVINSERT,TOOLTIP("Privilegios para Insertar registros"),COMBOXMULTIPLE("CLISTAPRIV"),TITULO("Priv Insert")
CAMPO=CNODELETE,TOOLTIP("Si tiene protegido para no DELETE"),TITULO("D")
CAMPO=PRIVDELETE,TOOLTIP("Privilegios para Insertar registros"),COMBOXMULTIPLE("CLISTAPRIV"),TITULO("Priv Delete")
CAMPO=CNOENTER,TOOLTIP("Si tiene protegido para no ENTER"),TITULO("E")
CAMPO=PRIVNOENTER,TOOLTIP("Privilegios para Insertar registros"),COMBOXMULTIPLE("CLISTAPRIV"),TITULO("Priv Enter")
CAMPO=CNOUPDATE,TOOLTIP("Si tiene protegido para no UPDATE"),TITULO("U")
CAMPO=PRIVUPDATE,TOOLTIP("Privilegios para Insertar registros"),COMBOXMULTIPLE("CLISTAPRIV"),TITULO("Priv Update")
CAMPO=CNOORAINS,TOOLTIP("Si tiene protegido para no ORAINS"),TITULO("O")
CAMPO=PRIVORAINS,TOOLTIP("Privilegios para Insertar registros"),COMBOXMULTIPLE("CLISTAPRIV"),TITULO("Priv OraIns")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CLISTAPRIV SELECT PRIVILEGIO,COMENTARIO FROM VDPRIVILEGIO ORDER BY PRIVILEGIO;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


TECLA=SF10,FEDITAPANTALLA(":NBLOQUE")
TECLA=SF9,FCARGAPANTALLA(":NBLOQUE")



