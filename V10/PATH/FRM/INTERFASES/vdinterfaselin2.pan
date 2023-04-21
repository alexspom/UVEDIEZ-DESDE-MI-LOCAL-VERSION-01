Descripción del Campo de interfase
 _1024_____________________________________________________________________________________________________________________________________
|
TABLA=VDINTERFASELIN


PROTECT("IMPLANTADOR")

PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
WDESPLEGADO
POSTCOMMIT=FPULSATECLAS("CF6","CF2","F2")

CAMPO=TIPOFICHERO,VIRTUAL,OCULTO,AUXILIAR
CAMPO=TIPOINTERFASE,VIRTUAL,OCULTO,TOOLTIP("Tipo de interfase")
CAMPO=FORMATO,VIRTUAL,OCULTO,TOOLTIP("Tipo de formato para una interfase")
CAMPO=ORDEN,VIRTUAL,OCULTO,TOOLTIP("Orden del campo dentro del fichero"),TITULO("Ord")
CAMPO=CAMPO,VIRTUAL,OCULTO,UPPER,TOOLTIP("Nombre del campo de 10"),TITULO("Campo")
CAMPO=TABLA,VIRTUAL,OCULTO,UPPER,TOOLTIP("Nombre de la tabla de V10 desde donde se obtendrá o desde donde se insertará o modificará"),TITULO("Tabla")
CAMPO=DESCCAMPO,MIXED,TOOLTIP("Descripción del campo que se imprimirá en la documentación de interfases"),TITULO("Descripción"),REGPAG=5
CAMPO=CODOPEMODIF,OCULTO,"_32__________"
CAMPO=FECMODIF,OCULTO,"¿D-MM-Y.YYY" 
CAMPO=HORAMODIF,OCULTO,"_8______"

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

