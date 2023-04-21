# Módulo   : VDINFODISP.PAN
# Función  : Mantenimiento de displays
#
# Creación : 21-05-2008
# Autor    : Maite González
###########################################
CONFIGURACION DE LOS DISPLAYS DE PICKING
                        
Disp.       Ubicación    Z.  Orden   D.Padre     D. Luz      Cubeta    Estado            Ultima modificación
@L@ @L@@@@@ _20_________ @L@ @L@@@@@ @L@ @L@@@@@ @L@ @L@@@@@ _20______ @L@@ _32_________ _32_________ ¿D-MM-Y.YY ________ 
|
TABLA=VDINFODISP
ORDERBY=IDINFOPICK,CODZONA,NUMDISP;
                   
PROTECT("IMPLANTADOR")                   

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=IDINFOPICK,TOOLTIP("Número de infopick hardware al que se refiere el display"),TITULO("Infopick"),WLONX=35
CAMPO=NUMDISP,TOOLTIP("Número de display en la red InfoPick.\nEste Código y el anterior forman la clave primaria."),TITULO("Display")
CAMPO=CODUBI,TOOLTIP("Código de ubicación asociada al display"),TITULO("Ubicación")
CAMPO=CODZONA,TOOLTIP("Código de Zona a la que pertenece el display asociado a la ubicación, para picking directo"),
                     POSTCHANGE=FEJECUTA("+CSELZONA","ZONA :CODZONA NO EXISTE",
                                         "-CCHECKZONA","ZONA :CODZONA NO SE CORRESPONDE CON LA UBIC. DEL DISPLAY"),TITULO("Zona"),WLONX=15
CAMPO=ORDENDISP,TOOLTIP("Orden para seleccionar los displays"),TITULO("Orden")                                         
CAMPO=IDINFOPICKPADRE,TOOLTIP("Número de infopick hardware al que se refiere el display"),TITULO("Inf. Padre"),WLONX=45
CAMPO=DPADRE,TOOLTIP("Indica qué display representa las operaciones a realizar.\nLos displays que se autorepresentan a sí mismos tienen como padres su mismo Código"),TITULO("Padre")
CAMPO=IDINFOPICKLUZ,TOOLTIP("Número de infopick hardware al que se refiere el display"),TITULO("Inf. Luz"),WLONX=30
CAMPO=NUMLUZ,TOOLTIP("Indica que display encenderá su luz intermitente para indicar que en esa columna hay picking pendiente."),TITULO("Luz")
CAMPO=CODMAT,TOOLTIP("Matrícula de caja o cubeta en el display"),TITULO("Matricula"),WLONX=30
CAMPO=STATUS,POSTCHANGE=FDESIGNACION("CSELSTATUS","No existe estado"),TOOLTIP("Status del display"),TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,TOOLTIP("Descripcion del status")
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro")

CURSOR=CSELZONA SELECT :CODZONA FROM VDZONAS WHERE CODZONA=:CODZONA;

CURSOR=CCHECKZONA SELECT :CODZONA  FROM VDUBICA UBI WHERE NVL(:CODUBI,'-')=CODUBI AND NVL(UBI.CODZONA,'-1')<>:CODZONA;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='IDI';



