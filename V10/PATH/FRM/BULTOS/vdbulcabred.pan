###################################################################
#M�dulo: VDBULCABRED.PAN
#Funcionalidad : Mantenimiento de cabecera de bultos reducido
#Autor: RFD      
#Fecha: 08-04-2008
###################################################################
# Hist�rico de cambios:
MANTENIMIENTO DE CABECERAS DE BULTO
 C�digo : _18_______________   N� bulto: @L@@@ / @L@@@  
 Pedido:  _20_______________ Div.:_20_  _40_____________________ A�o:@@@@   Versi�n:@@@    
 Tipo bulto: _ Volumetr�a: _10_________  Caja: _10_________   
 Estado: @L@@@@ _30________________________  
 Ultima modificaci�n: _32________________  �D-MM-YY.Y ________   Comentario:@L@@@@@@@
 Informaci�n: _255________________________________________________________________________
|

TABLA=VDBULTOCAB

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")


CAMPO=CODBULTO,NOUPDATE,TOOLTIP("C�digo del bulto. N�mero �nico que lo identifica")
CAMPO=NBULTO,NOUPDATE,TOOLTIP("N�mero de bulto dentro del pedido")
CAMPO=TOTALBULTOS,AUXILIAR,NOENTER,TOOLTIP("Total de bultos dentro del pedido")
CAMPO=CODPED,NOUPDATE,POSTCHANGE=FDESIGNACION("CCOUNT","ERROR CONTANDO BULTOS DEL PEDIDOS"),TOOLTIP("C�digo del pedido")
CAMPO=CODDIV,NOUPDATE,POSTCHANGE=FDESIGNACION("CDESDIV","C�digo de divisi�n no existe."),TOOLTIP("Divisi�n o compa�ia del pedido")
CAMPO=DESDIV,AUXILIAR,NOENTER,TOOLTIP("Descripci�n de la divisi�n o compa��a del pedido")
CAMPO=ANOPED,NOUPDATE,TOOLTIP("A�o del pedido")
CAMPO=SEQPED,NOUPDATE,TOOLTIP("Versi�n del pedido")
CAMPO=TIPOBULTO,PROTECT("SUPALMACEN"),TOOLTIP("Tipo del bulto 'U' unidades, 'E' Embalajes, 'C' Contenedor")
CAMPO=TIPOVOL,PROTECT("SUPALMACEN"),CONTEXTUAL=FEJECUTAFORM("VDCOLUMETRIA","N","TIPOVOL=:TIPOVOL","","","","S"),TOOLTIP("Tipo de volumetr�a si el bulto es de unidades")
CAMPO=TIPOCAJA,PROTECT("SUPALMACEN"),TOOLTIP("Inicial de la caja que aparece en la etiqueta")
CAMPO=STATUS,PROTECT("SUPALMACEN"),TOOLTIP("Estado del bulto seg�n tabla de estados tipo BUC"),POSTCHANGE=FDESIGNACION("CSELSTATUS","Estado no existe")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripci�n del estado del bulto seg�n tabla de estados tipo BUC")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que realiza la Ultima modificaci�n")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificaci�n")
CAMPO=HORAMODIF,UPPER,NOENTER,TOOLTIP("Hora de la Ultima modificaci�n")
CAMPO=CODCOMEN,NOUPDATE,TOOLTIP("C�digo de los comentarios a la cabecera del bulto")
CAMPO=VDEXTRA,PROTECT("SUPALMACEN"),TOOLTIP("Datos adicionales externos a V10")




CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CCOUNT SELECT COUNT(*) TOTALBULTOS FROM VDBULTOCAB
              WHERE CODPED=:CODPED AND SEQPED=:SEQPED AND CODDIV=:CODDIV AND ANOPED=:ANOPED ; 

CURSOR=CDESDIV SELECT DESDIV
                 FROM VDDIVIS
                WHERE CODDIV=:CODDIV;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='BUC';
 


