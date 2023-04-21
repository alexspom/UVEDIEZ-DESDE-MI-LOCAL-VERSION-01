###################################################################
#Módulo: VDMONBULTOSPICKINV5.PAN
#Funcionalidad : Monitor de bultos de picking inverso, movtos de la línea de bulto 
#Autor: FGS   
#Fecha: 24-06-2008
###################################################################
# Histórico de cambios:
MANTENIMIENTO DE CABECERAS DE BULTO


 Código : _18_______________   Matrícula Asoc.:  _18_______________  
 
 Cant.Total: #L####### Resto: #L####### Capac.Caja: #L####### CajaCompleta: _
 
 Estado: @L@@@@ _30________________________   Prepicking: _ 
 
 Fecha de creación:     ¿D-MM-YY.Y ________
 Fecha de finalización: ¿D-MM-YY.Y ________        
 Ult. Modif.: _32_______ ¿D-MM-YY.Y ________   Comentario:@L@@@@@@@
 Información: _255____________________________________________________________
|

TABLA=VDBULTOCABPINV

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")


CAMPO=CODBULTO,NOUPDATE,POSTCHANGE=FDESIGNACION("CSELCODART","","+CSELUNIEMB","","+CCANTIDAD","","+CRESTOS",""),TOOLTIP("Código del bulto. Número único que lo identifica")
CAMPO=CODART,AUXILIAR,OCULTO,"_40________"
CAMPO=CODMAT,PROTECT("IMPLANTADOR"),TOOLTIP("Matrícula asociada al bulto de picking inverso")
CAMPO=CANTIDAD,NOENTER,AUXILIAR,TOOLTIP("Cantidad Total que se mueve en el bulto"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=RESTO,NOENTER,AUXILIAR,TOOLTIP("Cantidad de Resto que se mueve en el bulto"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=UNIEMB,NOENTER,AUXILIAR,TOOLTIP("Cantidad de la caja al completo"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=CAJACOMPLETA,NOENTER,TOOLTIP("Si la caja se sirve en su totalidad para el picking inverso, o solo una parte de la misma")
CAMPO=STATUS,PROTECT("IMPLANTADOR"),TOOLTIP("Estado del bulto según tabla de estados tipo BUC"),POSTCHANGE=FDESIGNACION("CSELSTATUS","Estado no existe")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripción del estado del bulto según tabla de estados tipo BUC")
CAMPO=PREPICKING,AUXILIAR,NOENTER,TOOLTIP("Si el articulo se sirve con prepicking o no")
CAMPO=FECCREADO,NOENTER,TOOLTIP("Fecha en que creó el bulto")
CAMPO=HORACREADO,NOENTER,TOOLTIP("Hora en que creo el bulto")
CAMPO=FECFINALIZA,NOENTER,TOOLTIP("Fecha en que se finalizó el bulto")
CAMPO=HORAFINALIZA,NOENTER,TOOLTIP("Hora en que se finalizó el bulto")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que realiza la Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,UPPER,NOENTER,TOOLTIP("Hora de la Ultima modificación")
CAMPO=CODCOMEN,NOUPDATE,TOOLTIP("Código de los comentarios a la cabecera del bulto")
CAMPO=VDEXTRA,PROTECT("SUPALMACEN"),TOOLTIP("Datos adicionales externos a V10")

CURSOR=CSELCODART SELECT ART.CODART,DECODE(PICKINV,'P','S','N') PREPICKING FROM VDBULTOLINPINV BPL, VDARTIC ART WHERE CODBULTO=:CODBULTO AND BPL.CODART=ART.CODART ; 

CURSOR=CSELUNIEMB SELECT UNIEMB FROM VDBULTOLINPINV BPL, VDMOVIM MOV 
                     WHERE BPL.CODMOV=MOV.CODMOV AND BPL.CODBULTO=:CODBULTO;

CURSOR=CCANTIDAD SELECT SUM(CANTPEDIDA) CANTIDAD FROM VDBULTOLINPINV WHERE CODBULTO=:CODBULTO;

CURSOR=CRESTOS SELECT SUM(CANTPEDIDA) RESTO FROM VDBULTOLINPINV BPL WHERE  BPL.CODBULTO=:CODBULTO  AND STATUS= VDST.FBPLRESTOS;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMOD
IF FROM DUAL;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='BPC';


TECLA=F12,FEJECUTA(FIMPRIMEBULTO("ETIQ","VDBULTO.ZPL;VDPRUEBABU.VSQ;CSELPRUEBABU","CODBULTO=:CODBULTO",""),":V10ERROR")

 



