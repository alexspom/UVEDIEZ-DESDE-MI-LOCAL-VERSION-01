#*****************************************************************
#M�dulo: VDINTERFCARGACAB.PAN
#Funcionalidad : 
#Autor: ICC      
#Fecha: 29-04-2008
#*****************************************************************
#* Hist�rico de cambios
#* ====================
CABECERA DE LAS INTERFASES DE ENTRADA

C�digo    Estado Tipo                 Nombre del Fichero                    MENSAJE                                                                                                     Ultima modificaci�n                 
######### #####  _20_________________ _100_________________________________ _4000_______________________________________________________________________________________________________ _32_______ �D-MM-Y.YYY _8______   
|
TABLA=VDINTERFCARGACAB
ORDERBY=FECMODIF DESC, HORAMODIF DESC;

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=CODINTERFASE,TOOLTIP("C�digo de la interfase"),TITULO("C�digo")
CAMPO=STATUS,UPDATE,TOOLTIP("Estado en que se encuentra el fichero"),TITULO("Estado"),WLONX=20
CAMPO=TIPOINTERFASE,TOOLTIP("Tipo de interfase"),TITULO("Tipo")
CAMPO=FICHERO,UPDATE,TOOLTIP("Nombre del fichero que ha dado error"),TITULO("Nombre del Fichero")
CAMPO=MENSAJE,TOOLTIP("Mensaje descriptivo del resultado de la carga"),TITULO("Mensaje")
CAMPO=CODOPEMODIF,TOOLTIP("Usuario que ha realizado la ultima modificaci�n.Es utilizado para depuraci�n y control de los registros en las tablas"),TITULO("Ultima modificaci�n")
CAMPO=FECMODIF,TOOLTIP("Es la fecha  en que se efectu� alguna modificaci�n. Es utilizado para depuraci�n y control de los registros en las tablas")
CAMPO=HORAMODIF,TOOLTIP("Es la hora  en que se efectu� alguna modificaci�n. Es utilizado para depuraci�n y control de los registros en las tablas")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

