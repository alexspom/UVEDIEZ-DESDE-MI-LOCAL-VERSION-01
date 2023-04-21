#*****************************************************************
#Módulo: VDINTERFCARGACAB.PAN
#Funcionalidad : 
#Autor: ICC      
#Fecha: 29-04-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
CABECERA DE LAS INTERFASES DE ENTRADA

Código    Estado Tipo                 Formato              Nombre del Fichero con ruta          Ultima modificación             Inf. extra    
######### #####  _20_________________ _20_________________ _100_________________________________ _32_______ ¿D-MM-Y.YYY _8______ _255_______   
|
TABLA=VDINTERFCARGACAB
ORDERBY=DECODE(STATUS, (-1)*VDST.FICCPENDPROCES,1,150,3,VDST.FICCPENDPROCES,2,VDST.FICCPROCESADO,4,5), CODINTERFASE DESC;

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=CODINTERFASE,TOOLTIP("Código de la interfase"),TITULO("Código")
CAMPO=STATUS,UPDATE,TOOLTIP("Estado en que se encuentra el fichero"),TITULO("Estado"),WLONX=20
CAMPO=TIPOINTERFASE,TOOLTIP("Tipo de interfase"),TITULO("Tipo")
CAMPO=FORMATO,TOOLTIP("Tipo de formato (o segmento para SAP) para una interfase"),TITULO("Formato")
CAMPO=FICHERO,UPDATE,TOOLTIP("Nombre del fichero que ha dado error"),TITULO("Nombre del Fichero con ruta")
CAMPO=CODOPEMODIF,TOOLTIP("Usuario que ha realizado la ultima modificación.Es utilizado para depuración y control de los registros en las tablas"),TITULO("Ultima modificación")
CAMPO=FECMODIF,TOOLTIP("Es la fecha  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=HORAMODIF,TOOLTIP("Es la hora  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=VDEXTRA,TOOLTIP("Datos adicionales externos a V10 y útiles para el cliente"),TITULO("Inf. Extra")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

