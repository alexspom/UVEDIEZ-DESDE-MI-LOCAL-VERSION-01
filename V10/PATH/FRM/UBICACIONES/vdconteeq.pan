#*****************************************************************
#Módulo: VDCONTEEQ.PAN
#Función  : Mantenimiento de equivalencia de capacidad entre palet.
#           Utilizado para calclar la altura del palet.
#Autor: ICC      
#Fecha: 27-02-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
#
MANTENIMIENTO DE LA EQUIVALENCIA ENTRE CONTENEDORES

Contenedor                               Contenedor a comparar                     Eq.  Ultima modificación              
_10_______ _40__________________________ _10_______ _40__________________________  ###  _32_________ ¿D-MM-Y.YY ________
|
TABLA=VDCONTEEQ



PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=TIPOCONTE,POSTCHANGE=FDESIGNACION("CSELVDTIPOCONTEDESTIPOCONTE","ERROR AL EJECUTAR CURSOR CSELVDTIPOCONTEDESTIPOCONTE"),TOOLTIP("Tipo de contenedor a comparar"),TITULO("Contenedor")
CAMPO=DESTIPOCONTE,AUXILIAR,TOOLTIP("Descripción del tipo de contenedor")
CAMPO=TIPOCONTECOMP,POSTCHANGE=FDESIGNACION("CSELVDTIPOCONTEDESTIPOCONTECOMP","ERROR AL EJECUTAR CURSOR CSELVDTIPOCONTEDESTIPOCONTE"),TOOLTIP("Tipo de contenedor con el que se compara"),TITULO("Contenedor a comparar")
CAMPO=DESTIPOCONTECOMP,AUXILIAR,TOOLTIP("Descripción del tipo de contenedor")
CAMPO=PROPORCION,TOOLTIP("Porcentaje del tamaño que es mayor(+), o que es menor(-)"),TITULO("Eq.")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("usuario que realizó la Ultima modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro")

CURSOR=CSELVDTIPOCONTEDESTIPOCONTE SELECT DESTIPOCONTE FROM VDTIPOCONTE WHERE TIPOCONTE=:TIPOCONTE;
CURSOR=CSELVDTIPOCONTEDESTIPOCONTECOMP SELECT DESTIPOCONTE DESTIPOCONTECOMP FROM VDTIPOCONTE WHERE TIPOCONTE=:TIPOCONTECOMP;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

