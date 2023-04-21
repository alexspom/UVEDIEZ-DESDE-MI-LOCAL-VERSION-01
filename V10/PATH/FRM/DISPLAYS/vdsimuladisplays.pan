# Módulo   : VDSIMULADISPLAYS
# Función  : Simulador de los displays del pciking
#
# Creación : 24-08-2008
# Autor    : MGM
###########################################
CONFIGURACION DE LOS DISPLAYS DE INFOPICK.
Display         Ubic.      Estado              Bulto              Pedida  Validada Next Tick        Disp. padre Disp. Luz   MCant. I.C.  Ult. Modif.
@@@ @L@ @L@@@@@ _20______  @L@@@ _40__________ __________________ #L####  #L####   #L##########.### @L@ @L@@@@@ @L@ @L@@@@@ @@@@    _    _32_________ ¿D-MM-Y.YY ________ 
|
TABLA=VDINFODISP

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=CODZONA,VIRTUAL,TOOLTIP("Identificador de zona InfoPick")
CAMPO=IDINFOPICK,TOOLTIP("Número de infopick hardware al que se refiere el display"),TITULO("Display")
CAMPO=NUMDISP,TOOLTIP("Número de display en la red InfoPick.\nEste Código y el anterior forman la clave primaria.")
CAMPO=CODUBI,TOOLTIP("Código de ubicación asociada al display"),TITULO("Ubicación")
CAMPO=STATUS,POSTCHANGE=FEJECUTA("CDESSTATUS","No existe status"),TOOLTIP("Status del display"),TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,TOOLTIP("Descripcion del status")
CAMPO=CODBULTO,TOOLTIP("Código del bulto que se está picando en el display"),TITULO("Bulto")
CAMPO=CANTPEDIDADISP,TOOLTIP("Cantidad pedida en el display"),TITULO("Pedida")
CAMPO=CANTVALIDADADISP,TOOLTIP("Cantidad validada en el display"),TITULO("Validad")
CAMPO=NEXTTICK,TOOLTIP("Tiempo del siguiente tick"),TITULO("Next Tick")

CAMPO=IDINFOPICKPADRE,TOOLTIP("Número de infopick hardware al que se refiere el display"),TITULO("Disp. Padre")
CAMPO=DPADRE,TOOLTIP("Indica qué display representa las operaciones a realizar.\nLos displays que se autorepresentan a sí mismos tienen como padres su mismo Código")

CAMPO=IDINFOPICKLUZ,TOOLTIP("Número de infopick hardware al que se refiere el display"),TITULO("Disp. Luz")
CAMPO=NUMLUZ,TOOLTIP("Indica que display encenderá su luz intermitente para indicar que en esa columna hay picking pendiente.")

CAMPO=MAXCANTDISP,TOOLTIP("Máxima cantidad a mostrar en el display.\nSirve para fraccionar el picking cuando las cantidades solicitadas\nson grandes o presentan dificultad en su manejo\ny el operario no se desenvuelve\ncon soltura, provocándose errores en picking."),TITULO("M.C.")
CAMPO=INVCONT,UPPER,POSTCHANGE=FVERIFICA("SN","Inventario Continuo: (S)i o (N)o"),TOOLTIP("Una S indica que el display realizará inventario continuo,\nmostrando los pasos por cero de cada caja al operario para que\néste confirme o regularice,en positivo, la cantidad existente."),TITULO("I.C.")

CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE TIPOSTATUS = 'IDI' AND STATUS = :STATUS;


