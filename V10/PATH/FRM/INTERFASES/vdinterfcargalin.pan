#*****************************************************************
#Módulo: VDINTERFCARGALIN.PAN
#Funcionalidad : 
#Autor: ICC      
#Fecha: 29-04-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
#
#*****************************************************************
REGISTROS DE INTERFASES DE ENTRADA

Estado Nº Reg Registro                                   Mensaje de error                                                         Ultima modificación             Inf. extra
#####  #9#### _2048_____________________________________ _255____________________________________________________________________ _32_______ ¿D-MM-Y.YYY _8______ _255_______
|
TABLA=VDINTERFCARGALIN
ORDERBY=DECODE(MENSAJE,NULL,1,0), NUMREG;

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=CODINTERFASE,VIRTUAL,OCULTO,TOOLTIP("Código de la interfase")
CAMPO=STATUS,TOOLTIP("Estado en que se encuentra el registro del fichero"),TITULO("Estado"),WLONX=20
CAMPO=TIPOINTERFASE,OCULTO,"_20_",TOOLTIP("Tipo de interfase")
CAMPO=FORMATO,OCULTO,"_20_",TOOLTIP("Tipo de formato (o segmento para SAP) para una interfase")
CAMPO=NUMREG,NOENTER,TOOLTIP("Número de regitro dentro del fichero"),TITULO("Nº Reg"),WLONX=20
CAMPO=REGISTRO,TOOLTIP("Registros del fichero"),TITULO("Registro")
CAMPO=MENSAJE,NOENTER,TOOLTIP(":MENSAJE"),TITULO("Mensaje de error")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que ha realizado la ultima modificación.Es utilizado para depuración y control de los registros en las tablas"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=VDEXTRA,NOENTER,TOOLTIP("Datos adicionales externos a V10 y útiles para el cliente"),TITULO("Inf. Extra")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

