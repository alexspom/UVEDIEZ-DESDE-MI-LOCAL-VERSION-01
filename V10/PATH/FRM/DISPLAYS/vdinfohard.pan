# Módulo   : VDZONAS.PAN
# Función  : Mantenimiento de zonas
#
# Creación : 21-05-2008
# Autor    : Maite González
###########################################
CONFIGURACION DEL INFOHARD
 Infopick : @L@                     Librería: _256___________________________________   
 
 Delay cabecera:            @L@@@   Delay caracteres:                    @L@@@ 
 Tiempo repetición tecla:   @L@@@   Tiempo repetición siguientes teclas: @L@@@
 Tiempo parpadeo encendido: @L@@@   Tiempo parpadeo apagado:             @L@@@
 Máximo número errores:     @L@@@   Ratio error:                         @L@@@ 
 Tiempo estadisticas:       @L@@@   Tiempo ciclo:                        @L@@@   Limitación linea: @L@@@@@@@
 Tiempo entre tramas:       @L@@@   Timeout trama:                       @L@@@   Timeout who:      @L@

 
 DIRIP1  _15_____________                DIRIP2  _15_____________                DIRIP3  _15_____________
 DIRIP4  _15_____________                DIRIP5  _15_____________                DIRIP6  _15_____________
 DIRIP7  _15_____________                DIRIP8  _15_____________                DIRIP9  _15_____________
 DIRIP10 _15_____________                DIRIP11 _15_____________                DIRIP12 _15_____________
 DIRIP13 _15_____________                DIRIP14 _15_____________                DIRIP15 _15_____________  
 

 Rango líneas: _255_______________________________________________
 
 Ultima modificación: _32________ ¿D-MM-Y.YY ________
 Información extra: _256__________________________________________________________________________________
|


TABLA=VDINFOHARD
ORDERBY=IDINFOPICK;

WFRAME(3,120,755,105,"Direcciones IPs","")
PROTECT("IMPLANTADOR")

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=IDINFOPICK,NOUPDATE,TOOLTIP("Identificador del numero de infopick (Por si hay varios programas corriendo en la instalacion)")
CAMPO=LIBPROCESO,TOOLTIP("Libería que controla el proceso")
CAMPO=DELAYCAB,TOOLTIP("Delay entre cabeceras (Solo disp. 2g)")
CAMPO=DELAYCAR,TOOLTIP("Delay entre caracteres (Solo disp. 2g)")
CAMPO=PREPEAT,TOOLTIP("Tiempo de repeticion por primera vez de una tecla")
CAMPO=SREPEAT,TOOLTIP("Tiempo de repeticion siguientes teclas")
CAMPO=TPARPADE,TOOLTIP("Tiempo parpadeo encendido (Solo disp. 2g)")
CAMPO=TPARPADA,TOOLTIP("Tiempo parpadeo apagado (Solo disp. 2g)")
CAMPO=MAXERROR,TOOLTIP("Maximo numero de errores antes de resetear las lineas")
CAMPO=RATIOERR,TOOLTIP("Ratio de tramas buenas y malas para anular los errores")
CAMPO=STATGAPS,TOOLTIP("Tiempo entre estadisticas")
CAMPO=TCICLO,TOOLTIP("Tiempo de ciclo del ethernet-box (Solo dispalys 3g)")
CAMPO=LIMITELINEA,TOOLTIP("Limitacion de corriente por linea (Solo dispalys 3g)")
CAMPO=TENVTRAMA,TOOLTIP("Tiempo entre tramas (Solo dispalys 3g)")
CAMPO=TIMEOUTTRAMA,TOOLTIP("Timeout trama (Solo displays 3g)")
CAMPO=TIMEOUTWHO,TOOLTIP("Timeout who (Solo dispalys 3g)")
CAMPO=DIRIP1,TOOLTIP("Direccion IP del 1 ethernet-box")
CAMPO=DIRIP2,TOOLTIP("Direccion IP del 2 ethernet-box")
CAMPO=DIRIP3,TOOLTIP("Direccion IP del 3 ethernet-box")
CAMPO=DIRIP4,TOOLTIP("Direccion IP del 4 ethernet-box")
CAMPO=DIRIP5,TOOLTIP("Direccion IP del 5 ethernet-box")
CAMPO=DIRIP6,TOOLTIP("Direccion IP del 6 ethernet-box")
CAMPO=DIRIP7,TOOLTIP("Direccion IP del 7 ethernet-box")
CAMPO=DIRIP8,TOOLTIP("Direccion IP del 8 ethernet-box")
CAMPO=DIRIP9,TOOLTIP("Direccion IP del 9 ethernet-box")
CAMPO=DIRIP10,TOOLTIP("Direccion IP del 10 ethernet-box")
CAMPO=DIRIP11,TOOLTIP("Direccion IP del 11 ethernet-box")
CAMPO=DIRIP12,TOOLTIP("Direccion IP del 12 ethernet-box")
CAMPO=DIRIP13,TOOLTIP("Direccion IP del 13 ethernet-box")
CAMPO=DIRIP14,TOOLTIP("Direccion IP del 14 ethernet-box")
CAMPO=DIRIP15,TOOLTIP("Direccion IP del 15 ethernet-box")
CAMPO=RANGOLINEAS,TOOLTIP("Rango de lineas a conectar")
CAMPO=CODOPEMODIF,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,TOOLTIP("Fecha en la que se efectuo la ultima modificacion")
CAMPO=HORAMODIF,TOOLTIP("Hora ultima modificacion")
CAMPO=VDEXTRA,TOOLTIP("Datos adicionales externos a V10 y útiles para el cliente")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

