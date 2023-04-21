# Módulo   : VDDEFBLOQUE.PAN
# Función  : Mantenimiento de propiedades por defecto de bloques
#
# Creación : 18-12-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
CARACTERISTICAS POR DEFECTO DE BLOQUE DE DATOS      
Pantalla           Grupo          T PosX  PosY  Reg  NoInsert NoDelete NoUpdate NoEnter NoOraIns Ayuda Online             Título                     Q Contextual                    Tecla                  Cap  PrivInsert             PrivDelete             PrivNoenter            PrivNoupdate           PrivNoorains           TextoWhere                           TextoOrdery                  FAuxiliar                  Ultima modificación
_40_______________ _32___________ _ @L@@@ @L@@@ @L@@ _1______ _1______ _1______ _1_____ _1______ _1024___________________ _1024_____________________ _ _1024________________________ _1024__________________ _   _1024_________________ _1024_________________ _1024_________________ _1024_________________ _1024_________________ _1024_______________________________ _1024_______________________ _1024_____________________ _32________ ¿D-MM-Y.YY  ________
|


TABLA=VDDEFBLOQUE

#WPLEGADO
PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")



CAMPO=NBLOQUE,TOOLTIP("Nombre del bloque"),TITULO("Pantalla")
CAMPO=GRUPOBLOQUE,TOOLTIP("Grupo de pantallas al que pertenece el bloque"),TITULO("Grupo")
CAMPO=TIPOPANTALLA,TOOLTIP("Tipo de pantallas a las que se aplican los defectos puede ser F(orms) R(adios) o A(mbos)"),TITULO("T")
CAMPO=NUMPOSX,TOOLTIP("Coordenada X en el que comienza la pantalla"),TITULO("PosX")
CAMPO=NUMPOSY,TOOLTIP("Coordenada Y en el que comienza la pantalla"),TITULO("PosY")
CAMPO=NUMREGPAG,TOOLTIP("Número de registros de la pantalla"),TITULO("Reg")
CAMPO=CNOINSERT,TOOLTIP("Si tiene protegido para no insert"),TITULO("NoInsert")
CAMPO=CNODELETE,TOOLTIP("Si tiene protegido para no delete"),TITULO("NoDelete")
CAMPO=CNOUPDATE,TOOLTIP("Si tiene protegido para no update"),TITULO("NoUpdate")
CAMPO=CNOENTER,TOOLTIP("Si tiene protegido para no enter"),TITULO("NoEnter")
CAMPO=CNOORAINS,TOOLTIP("Si tiene protegido para no orains"),TITULO("NoOraIns")
CAMPO=AYUDAONLINE,MIXED,TOOLTIP("Ayuda online del Bloque. Si se antepone un signo + se concatena a la ayuda online por defecto"),TITULO("Ayuda Online")
CAMPO=TITULOBLOQUE,TOOLTIP("Título del bloque de datos"),TITULO("Título")
CAMPO=MODOQUERY,TOOLTIP("Modo de query de la pantalla: A(query), P(query), T(query) o NULO"),TITULO("Q")
CAMPO=FCONTEXTUAL,TOOLTIP("Función a ejecutar al pulsar Shift+F10"),TITULO("Contextual")
CAMPO=FTECLA,TOOLTIP("Funciones programables para puslaciones de teclas especiales"),TITULO("Tecla")
CAMPO=CAPITALIZA,TOOLTIP("Capitalización del campo U(pper) L(ower) M(ixed)"),POSTCHANGE=FEJECUTA(FSUCCESS,"")
CAMPO=PRIVINSERT,TOOLTIP("Privilegios para Insertar registros"),TITULO("Cap")
CAMPO=PRIVDELETE,TOOLTIP("Privilegios para Insertar registros"),TITULO("Privilegios Delete"),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=PRIVNOENTER,TOOLTIP("Privilegios para Insertar registros"),TITULO("Privilegios Noenter"),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=PRIVUPDATE,TOOLTIP("Privilegios para Insertar registros"),TITULO("Privilegios Update"),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=PRIVORAINS,TOOLTIP("Privilegios para Insertar registros"),TITULO("Privilegios Orains"),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=TWHERE,TOOLTIP("Texto where de la pantalla, anteponiéndole un signo + lo concatena a la where en fichero de la misma"),TITULO("Where")
CAMPO=TORDERBY,TOOLTIP("Criterio de ordenación de la pantalla"),TITULO("Order By")
CAMPO=FAUXILIAR,TOOLTIP("Propiedades adicionales a añadir a la pantalla"),TITULO("Auxiliar")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CLISTAPRIV SELECT '"'||PRIVILEGIO||'"',COMENTARIO FROM VDPRIVILEGIO ORDER BY PRIVILEGIO;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


TECLA=SF10,FEDITAPANTALLA(":NBLOQUE")
TECLA=SF9,FCARGAPANTALLA(":NBLOQUE")



