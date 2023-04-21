# Módulo   : VDLISTAIMPRESORAS.PAN
# Función  : Pantalla para seleccionar una impresora activa
#
# Creación : 13-05-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
CONSULTA DE IMPRESORAS ACTIVAS
 Act Grupo          Act Impresora      Descripción                   Spool Driver Fichero      Tipo Pto   Baudios Bits Par Stop Ult. Modificación            
  _  _______________ _  ______________ _60__________________________   _   _32___ _256________   @  @L@@@ @L@@@@   @   @   @    _32_________ ¿D-MM-Y.YY ________
|

TABLA=VDIMPRESORAS
WHERE=ACTIVO='S';
ORDERBY=GRUPOIMPRE,CODIMPRE;

WFRAME(28,-2,138,0,"Grupo","")
WFRAME(650,-2,218,0,"Conexión","")

CAMPO=ACTIVO,TOOLTIP("Si la impresora está activa"),POSTCHANGE=FEJECUTA(FVERIFICA("NS"),"CAMPO ACTIVO DEBE SER 'S' O 'N'"),TITULO("Act"),WLONX=15
CAMPO=GRUPOIMPRE,TOOLTIP("Grupo al que pertenece la impresora"),POSTCHANGE=FEJECUTA("CACTIVOGRUPO","GRUPO :GRUPOIMPRE NO EXISTE"),TITULO("Grupo")
CAMPO=ACTIVOGRUPO,AUXILIAR,NOENTER,TITULO("Act"),WLONX=15
CAMPO=CODIMPRE,TOOLTIP("Código V10 de la impresora"),TITULO("Impresora")
CAMPO=DESIMPRE,TOOLTIP("Descripción de la Impresora"),TITULO("Descripción")
CAMPO=SPOOL,TOOLTIP("Imprimir en la impresora por servicio de Spool V10"),TITULO("Spool"),WLONX=20
CAMPO=DRIVER,TOOLTIP("Driver de las impresoras que no se imprime por Window. P.e. ZPL, SAT,. ..."),TITULO("Driver"),WLONX=20
CAMPO=FICHERO,TOOLTIP("Fichero al que se envía datos de impresiones de la impresora"),TITULO("Fichero")
CAMPO=TIPOCONEX,TOOLTIP("Tipo de Conexión por la que se comunica con la impresora, 0. sin conex, 1 TCP, 2 RS232"),TITULO("Tipo"),WLONX=15
CAMPO=PUERTOCONEX,TOOLTIP("Puero TCP o 232 por el que se comunica con la impresora/etiquetadora"),TITULO("Pto")
CAMPO=BAUDIOS,TOOLTIP("Baudios en la comunic. 232"),TITULO("Baudios"),WLONX=20
CAMPO=BITS,TOOLTIP("Bits por caracter enviado por 232"),TITULO("Bits"),WLONX=15
CAMPO=PARIDAD,TOOLTIP("Paridad Par / Impar en  232"),TITULO("Par"),WLONX=15
CAMPO=BITSTOP,TOOLTIP("Número de Bits de parada por carácter en 232"),TITULO("Stop"),WLONX=20
CAMPO=CODOPEMODIF,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,TOOLTIP("Fecha en la que se realizó la Ultima modificación")
CAMPO=HORAMODIF,TOOLTIP("Hora en la que se realizó la Ultima modificación")

CURSOR=CACTIVOGRUPO SELECT ACTIVO ACTIVOGRUPO FROM VDIMPREGRUPO WHERE GRUPOIMPRE=:GRUPOIMPRE;


