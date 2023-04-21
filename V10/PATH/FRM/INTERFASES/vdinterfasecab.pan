#*****************************************************************
#Módulo: VDINTERFASECAB.PAN
#Funcionalidad : 
#Autor: ICC      
#Fecha: 16-04-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
MANTENIMIENTO DE INTERFASES
                                                                   -------------Datos Fichero-----------------------------
Tipo de interfase  Formato          Formato padre Orden Nº Reg Mod Prefijo           Ext.         Tipo Fmto Secuencial Sep L.Fija L.Fmto Funcion             Libreria          Ultima modificación             Inf. extra
_20_______________ _20_____________ _20__________  ###  #####   _  _40______________ _40__________  _    _   #########   _    _      ##   _32_______________ _256_____________ _32_______ ¿D-MM-Y.YYY _8______ _255_______   
|
TABLA=VDINTERFASECAB
ORDERBY=ORDEN,TIPOFICHERO,TIPOINTERFASE,FORMATO;


PROTECT("IMPLANTADOR")

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREDELETE=FEJECUTA("CDELLININTER","ERROR AL BORRAR LINEAS DE INTERFASE")

CURSOR=CDELLININTER DELETE VDINTERFASELIN WHERE TIPOINTERFASE=:TIPOINTERFASE AND FORMATO=:FORMATO;

CAMPO=TIPOINTERFASE,TOOLTIP("Tipo de interfase"),TITULO("Tipo de interfase")
CAMPO=FORMATO,TOOLTIP("Tipo de formato (o segmento para SAP) para una interfase"),TITULO("Formato"),WLONX=25,MIXED
CAMPO=FORMATOPADRE,TOOLTIP("Tipo de formato del que depende el formato actual, muy utilizado en interfases con SAP, sería el equivalente al segmento padre"),TITULO("Formato padre"),WLONX=50
CAMPO=ORDEN,TOOLTIP("Orden en que deben procesarse los ficheros y debe documentarse"),TITULO("Orden"),WLONX=20
CAMPO=NREGISTROS,TOOLTIP("Número de registros máximo que existe para un tipo de formato o segmento"),TITULO("Nº Reg"),WLONX=18
CAMPO=SWTACTUALIZA,TOOLTIP("Indicador de si este tipo de interfase y formato pueden ser modificados o no. Posibles valores: S o N"),UPPER,
                   POSTCHANGE=FVERIFICA("SN","Posibles valores:\n S-Si puede modificarse el registro, N-No puede modificarse el registro"),TITULO("Mod"),WLONX=15
CAMPO=PREFFICHERO,MIXED,TOOLTIP("Prefijo del nombre del tipo de fichero a procesar"),TITULO("Prefijo")
CAMPO=EXTFICHERO,MIXED,TOOLTIP("Extensión del fichero"),TITULO("Ext."),WLONX=14
CAMPO=TIPOFICHERO,TOOLTIP("Tipo de fichero, se concatena al nombre _Z_. Posibles valores: E=entrada, S=salida, A=ambos"),
                  POSTCHANGE=FVERIFICA("SEA","El tipo de fichero debe ser (S)alida, (E)ntrada o (A)mbos"),TITULO("Tipo"),WLONX=20
CAMPO=FORMATOFICH,TOOLTIP("Formato del contador del fichero.\nPosibles valores:\n 0-prefijo,\n 1-prefijo+secuencial,\n 2-prefijo+timestamp,\n 3-prefijo+secuencial+timestamp"),
                  POSTCHANGE=FVERIFICA("01234567","Posibles valores:\n 0-Prefijo,\n 1-Prefijo+Secuencial,\n 2-Prefijo+Timestamp,\n 3-Prefijo+Secuencial+Timestamp"),TITULO("Fmto"),WLONX=20
CAMPO=SECUENCIAL,TOOLTIP("Secuencial del último fichero que se ha tratado")	,TITULO("Secuencial"),WLONX=32
CAMPO=SEPARADOR,TOOLTIP("Separador entre campos"),TITULO("Sep"),WLONX=15
CAMPO=SWTLONGFIJA,TOOLTIP("Indicador de si los campos de los ficheros tienen longitud fija o no.\nPosibles valores:\nS-Longitud fija \nN-No tienen longitud fija"),
                   POSTCHANGE=FVERIFICA("SN","Valores: \nS=Longitud fija\nN=No tienen longitud fija"),TITULO("L.Fija"),WLONX=24
CAMPO=LONGFORMATO,TOOLTIP("Longitud del formato, en caso de venir el Código del formato al inicio del registro, sino cero")	,TITULO("L.Fmto"),WLONX=26
CAMPO=FUNCION,TOOLTIP("Función de c"),TITULO("Función")
CAMPO=LIBRERIA,TOOLTIP("Libreria de la función de c"),TITULO("Librería")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que ha realizado la ultima modificación.Es utilizado para depuración y control de los registros en las tablas"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=VDEXTRA,TOOLTIP("Datos adicionales externos a V10 y útiles para el cliente"),TITULO("Inf. Extra")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

