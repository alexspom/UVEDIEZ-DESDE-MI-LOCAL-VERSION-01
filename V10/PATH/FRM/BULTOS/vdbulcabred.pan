###################################################################
#Módulo: VDBULCABRED.PAN
#Funcionalidad : Mantenimiento de cabecera de bultos reducido
#Autor: RFD      
#Fecha: 08-04-2008
###################################################################
# Histórico de cambios:
MANTENIMIENTO DE CABECERAS DE BULTO
 Código : _18_______________   Nº bulto: @L@@@ / @L@@@  
 Pedido:  _20_______________ Div.:_20_  _40_____________________ Año:@@@@   Versión:@@@    
 Tipo bulto: _ Volumetría: _10_________  Caja: _10_________   
 Estado: @L@@@@ _30________________________  
 Ultima modificación: _32________________  ¿D-MM-YY.Y ________   Comentario:@L@@@@@@@
 Información: _255________________________________________________________________________
|

TABLA=VDBULTOCAB

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")


CAMPO=CODBULTO,NOUPDATE,TOOLTIP("Código del bulto. Número único que lo identifica")
CAMPO=NBULTO,NOUPDATE,TOOLTIP("Número de bulto dentro del pedido")
CAMPO=TOTALBULTOS,AUXILIAR,NOENTER,TOOLTIP("Total de bultos dentro del pedido")
CAMPO=CODPED,NOUPDATE,POSTCHANGE=FDESIGNACION("CCOUNT","ERROR CONTANDO BULTOS DEL PEDIDOS"),TOOLTIP("Código del pedido")
CAMPO=CODDIV,NOUPDATE,POSTCHANGE=FDESIGNACION("CDESDIV","Código de división no existe."),TOOLTIP("División o compañia del pedido")
CAMPO=DESDIV,AUXILIAR,NOENTER,TOOLTIP("Descripción de la división o compañía del pedido")
CAMPO=ANOPED,NOUPDATE,TOOLTIP("Año del pedido")
CAMPO=SEQPED,NOUPDATE,TOOLTIP("Versión del pedido")
CAMPO=TIPOBULTO,PROTECT("SUPALMACEN"),TOOLTIP("Tipo del bulto 'U' unidades, 'E' Embalajes, 'C' Contenedor")
CAMPO=TIPOVOL,PROTECT("SUPALMACEN"),CONTEXTUAL=FEJECUTAFORM("VDCOLUMETRIA","N","TIPOVOL=:TIPOVOL","","","","S"),TOOLTIP("Tipo de volumetría si el bulto es de unidades")
CAMPO=TIPOCAJA,PROTECT("SUPALMACEN"),TOOLTIP("Inicial de la caja que aparece en la etiqueta")
CAMPO=STATUS,PROTECT("SUPALMACEN"),TOOLTIP("Estado del bulto según tabla de estados tipo BUC"),POSTCHANGE=FDESIGNACION("CSELSTATUS","Estado no existe")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripción del estado del bulto según tabla de estados tipo BUC")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que realiza la Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,UPPER,NOENTER,TOOLTIP("Hora de la Ultima modificación")
CAMPO=CODCOMEN,NOUPDATE,TOOLTIP("Código de los comentarios a la cabecera del bulto")
CAMPO=VDEXTRA,PROTECT("SUPALMACEN"),TOOLTIP("Datos adicionales externos a V10")




CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CCOUNT SELECT COUNT(*) TOTALBULTOS FROM VDBULTOCAB
              WHERE CODPED=:CODPED AND SEQPED=:SEQPED AND CODDIV=:CODDIV AND ANOPED=:ANOPED ; 

CURSOR=CDESDIV SELECT DESDIV
                 FROM VDDIVIS
                WHERE CODDIV=:CODDIV;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='BUC';
 


