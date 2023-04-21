###################################################################
#Módulo: VDBULCABPINV.PAN
#Funcionalidad : Mantenimiento de cabecera de bultos
#Autor: MGM   
#Fecha: 03-06-2008
###################################################################
# Histórico de cambios:
MANTENIMIENTO DE CABECERAS DE BULTO

 Matrícula Asoc.:  _18_______________   Código : _18_______________   
 
 Estado: @L@@@@ _30________________________   
  
 Cant.Total: #L#######    CajaCompleta: _
 Resto:      #L#######    Prepicking:   _
 Capac.Caja: #L#######    Ubic.         _20___________
 Fecha de creación:      ¿D-MM-YY.Y ________   
 Fecha de finalización:  ¿D-MM-YY.Y ________       
 Ult. Modif.: _32_______ ¿D-MM-YY.Y ________   Comentario:@L@@@@@@@
 Información: _255____________________________________________________________
|

TABLA=VDBULTOCABPINV

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION","CSELHORACREA","")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=CODMAT,PROTECT("IMPLANTADOR"),TOOLTIP("Matrícula asociada al bulto de picking inverso"),INCLUDECSS="border-style:ridge;background-color:#F7BE81;"
CAMPO=CODBULTO,NOUPDATE,POSTCHANGE=FDESIGNACION("+CSELCODUBI","","+CRESTOS",""),TOOLTIP("Código del bulto. Número único que lo identifica")
CAMPO=CODART,AUXILIAR,OCULTO,"_40________"
CAMPO=STATUS,TOOLTIP("Estado del bulto según tabla de estados tipo BUC"),POSTCHANGE=FDESIGNACION("CSELSTATUS","Estado no existe")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripción del estado del bulto según tabla de estados tipo BUC")
CAMPO=CANTIDAD,NOENTER,AUXILIAR,TOOLTIP("Cantidad Total que se mueve en el bulto"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=CAJACOMPLETA,TOOLTIP("Si la caja se sirve en su totalidad para el picking inverso, o solo una parte de la misma")
CAMPO=RESTO,NOENTER,AUXILIAR,TOOLTIP("Cantidad de Resto que se mueve en el bulto"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=PREPICKING,AUXILIAR,NOENTER,TOOLTIP("Si el articulo se sirve con prepicking o no")
CAMPO=UNIEMB,NOENTER,AUXILIAR,TOOLTIP("Cantidad de la caja al completo"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=CODUBI,AUXILIAR,NOENTER
CAMPO=FECCREADO,NOENTER,TOOLTIP("Fecha en que creó el bulto")
CAMPO=HORACREADO,NOENTER,TOOLTIP("Hora en que creo el bulto")
CAMPO=FECFINALIZA,NOENTER,TOOLTIP("Fecha en que se finalizó el bulto")
CAMPO=HORAFINALIZA,NOENTER,TOOLTIP("Hora en que se finalizó el bulto")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que realiza la Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,UPPER,NOENTER,TOOLTIP("Hora de la Ultima modificación")
CAMPO=CODCOMEN,NOUPDATE,TOOLTIP("Código de los comentarios a la cabecera del bulto")
CAMPO=VDEXTRA,PROTECT("SUPALMACEN"),TOOLTIP("Datos adicionales externos a V10")

CURSOR=CSELCODUBI SELECT CODUBI FROM VDCONTE WHERE CODMAT=:CODMAT AND :CODMAT IS NOT NULL;

CURSOR=CSELCODART SELECT ART.CODART,MOV.UNIEMB,DECODE(PICKINV,'P','S','N') PREPICKING,SUM(CANTIDAD) CANTIDAD
                    FROM VDMOVIM MOV, VDARTIC ART 
					WHERE CODBULTOORI=:CODBULTO AND MOV.CODART=ART.CODART
				GROUP BY ART.CODART,ART.PICKINV,MOV.UNIEMB; 

CURSOR=CRESTOS SELECT SUM(CANTIDAD)-:CANTIDAD RESTO 
                  FROM VDSTOCK STK
				  WHERE  STK.CODMAT=:CODMAT;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELHORACREA SELECT VD.FECHASYS FECCREADO,VD.HORASYS HORACREADO FROM DUAL;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='BPC';


TECLA=F12,FEJECUTA(FIMPRIMEBULTO("ETIQ","VDBULTO.ZPL;VDPRUEBABU.VSQ;CSELPRUEBABU","CODBULTO=:CODBULTO",""),":V10ERROR")

 



