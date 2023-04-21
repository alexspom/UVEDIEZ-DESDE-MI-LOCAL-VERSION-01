# Módulo   : VDORAERR.PAN
# Función  : MANEJO DE ERRORES ORACLE
#
# Creación : 19-11-2009
# Autor    : FGS
# Fichero generado por el Asistente de Generación de Pantallas V10 
###########################################
# Histórico de cambios:
ASIGNACION DE MANEJADORES DE ERRRES ORACLE
 
 Lib. Funcion: _256_________________  Funcion: _32_________________         
 
 Param: _256__________________________________________________________________________________________________________________________
 
 Tiempo Espera en seg. @L@@@                      Ult. Modificacion: _32___________________ ¿D-MM-Y.YY ________ 
 
|

TABLA=VDORAERR
PREINSERT=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")
ORDERBY=ORDEN;
REGPAG=20
CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

# LISTA DE CAMPOS DE LA PANTALLA
CAMPO=ORDEN,VIRTUAL,OCULTO
CAMPO=RANGOEXE,VIRTUAL,OCULTO,TITULO("RANGO PROGRAMAS"),TOOLTIP(" Rango de programas a tratar los errores (si .exe)")
CAMPO=RANGOERROR,VIRTUAL,OCULTO,TITULO("RANGO ERRORES"),TOOLTIP("Rango de errores a tratar")
CAMPO=NIVELERR,VIRTUAL,OCULTO,TITULO("Nivel"),TOOLTIP("'Nivel de Error; 0 Salirse, 1 Debug, 2 Warning, 3 Reiniciar programa")
CAMPO=DESCERROR,VIRTUAL,OCULTO,TITULO("DESCRIPCION"),TOOLTIP("Descripción de la asignación de errores")
CAMPO=LIBALGORITMO,TITULO("Librería del la funcion de manejo de error. SYSTEM para llamadas al sistema operativo (system(...))"),TOOLTIP("Librería donde se encuentra la función que trata los errores")
CAMPO=FUNCIONALG,TITULO("Algoritmo"),TOOLTIP("Función de la librería que trata los errores"),MIXED
CAMPO=PARAM,TITULO("Parametro del Algoritmo")
CAMPO=TIEMPOESPERA,TITULO("Tiempo Esp."),TOOLTIP("Tiempo en segundos antes de retornar de la función de tratamiento de error"),WLONX=50
CAMPO=CODOPEMODIF,TITULO("ULT. MODIFICACION"),TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,TOOLTIP("Es la fecha  en que se efectuó alguna modificación a los datos de los status. Es utilizado para depuración y control de los registros en las tablas.")
CAMPO=HORAMODIF,TOOLTIP("Es la  hora en que se efectuó alguna modificación a los datos de los status. Es utilizado para depuración y control de los registros en las tablas.")

# PARTE PERSONALIZADA DE LA PANTALLA 