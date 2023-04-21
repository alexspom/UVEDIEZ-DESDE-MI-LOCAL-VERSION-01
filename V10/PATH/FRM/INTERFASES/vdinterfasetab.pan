#*****************************************************************
#Módulo: VDINTERFASETAB.PAN
#Funcionalidad : Mantenimiento de las tablas a mantener por las interfases
#Autor: ICC      
#Fecha: 04-08-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
#
TABLAS A MANTENER POR INTERFASE
Tabla                            Alias tabla                      Librería      Abreviatura Orden Ins. Ultima modificación                Inf. extra
_32_____________________________ _32_____________________________ _256_________  _5___        ##   _32_______  ¿D-MM-Y.YYY  _8______  _255______   
|
TABLA=VDINTERFASETAB


ORDERBY=ORDENINSUPD;

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=TABLA,TOOLTIP("Nombre de la tabla"),TITULO("Tabla")
CAMPO=TABLAALIAS,TOOLTIP("Alias de la tabla, por defecto nombre de la tabla a no ser que se inserten varios registros para una misma línea de un fichero"),TITULO("Alias Tabla")
CAMPO=LIBRERIA,TOOLTIP("Librería de las funciones generadas automáticamente para el tratamiento de la tabla"),TITULO("Librería")
CAMPO=ABREVIATURA,TOOLTIP("Abreviatura de la tabla que da el genc"),TITULO("Abreviatura"),WLONX=45
CAMPO=ORDENINSUPD,TOOLTIP("Orden de inserción y de update, necesario para que no salte ninguna constraint"),TITULO("Orden Ins."),WLONX=55
CAMPO=CODOPEMODIF,TOOLTIP("Usuario que ha realizado la ultima modificación.Es utilizado para depuración y control de los registros en las tablas"),TITULO("Ultima modificación")
CAMPO=FECMODIF,TOOLTIP("Es la fecha  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=HORAMODIF,TOOLTIP("Es la hora  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=VDEXTRA,TOOLTIP("Datos adicionales externos a V10 y útiles para el cliente")




CURSOR=CSELMODIF SELECT DECODE (:TABLAALIAS, NULL, :TABLA, :TABLAALIAS) TABLAALIAS,
                         VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF 
                   FROM DUAL;



