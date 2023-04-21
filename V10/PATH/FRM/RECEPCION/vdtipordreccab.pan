#*****************************************************************
#Módulo: VDTIPORDRECCAB.PAN
#Función: Mantenimiento de las cabeceras de los tipos de recepción
#Autor: ICC      
#Fecha: 12-02-2008
##*****************************************************************
#* Histórico de cambios
#* ====================
MANTENIMIENTO DE LAS CABECERAS DE LOS TIPOS DE RECEPCION

Tipo                                            Concepto                            Privilegio         Inf. adicional         Ultima modificación            
_10_______ _40_________________________________ _10_______ _80_____________________ _20_______________ _255__________________ _32_______ ¿D-MM-Y.YYY _8______
|

TABLA=VDTIPORDRECCAB

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=TIPORDREC,TOOLTIP("Tipo de orden de recepción"),TITULO("Tipo"),NOUPDATE
CAMPO=DESORDREC,TOOLTIP("Designación del tipo de orden de recepción"),TITULO("Descripcion")
CAMPO=CODCONCE,POSTCHANGE=FDESIGNACION("CSELVDCONCEPTODESCONCE","ERROR AL EJECUTAR CURSOR CSELVDCONCEPTODESCONCE"),TOOLTIP("Concepto del movimiento de entrada de mercancía, desde un manantial hasta su pulmón correspondiente."),
               CONTEXTUAL=FDESIGNACION(FEJECUTAFORM("VDCONCEPTO","S","","","CODCONCE=:CODCONCE","","S")),
               TITULO("Concepto")
CAMPO=DESCONCE,NOENTER,AUXILIAR,TOOLTIP("Descripción del concepto")
CAMPO=RANGOPRIVILEGIO,TOOLTIP("Privilegio que debe tener el operario para modificar este tipo de Ordenes"),TITULO("Privilegio"),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=VDEXTRA,TOOLTIP("Datos adicionales externos a V10 y útiles para el cliente"),TITULO("Inf. Adicional")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora en que se efectuó alguna modificación a los datos del registro")

CURSOR=CSELVDCONCEPTODESCONCE SELECT DESCONCE FROM VDCONCEPTO WHERE CODCONCE=:CODCONCE;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CLISTAPRIV SELECT PRIVILEGIO, COMENTARIO FROM VDPRIVILEGIO ORDER BY PRIVILEGIO;