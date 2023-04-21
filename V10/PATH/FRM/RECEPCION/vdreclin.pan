#*****************************************************************
#Módulo: VDRECLIN.PAN
#Funcionalidad : Consulta de las líneas de recepción
#Autor: ICC
#Fecha: 12-02-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
LINEAS DE RECEPCION
Línea   Div.  Artículo                                     Lote            Caduci   Bloq. stock Cant. recep Muest. Ultima modificación              Observaciones
@L@@@@  _20_  _40_____________ _100_______________________ _40____________ _8______ _10_______  @L,@@@@@@@@   _    _32_________ ¿D-MM-Y.YY ________ _60_________________________________________________________ 
|
TABLA=VDRECEPLIN

#CAMPO=CODRECEP,VIRTUAL,TOOLTIP("Número de recepción dentro de la misma orden de recepción")
CAMPO=SECLINREC,NOUPDATE,TOOLTIP("Secuencia de línea de recepción dentro de la propia recepción "),TITULO("Línea")
#CAMPO=SECLINORD,TOOLTIP("Secuencia de registro de línea de orden de recepción a que referencia")
CAMPO=CODDIV,NOUPDATE,TOOLTIP("Código de la división"),TITULO("División"),WLONX=26
CAMPO=CODART,NOUPDATE,TOOLTIP("Código de artículo"),TITULO("Artículo"),POSTCHANGE=FEJECUTA("CDESART","ERROR CONSULTANDO LA DESCRIPCION DEL ARTICULO")
CAMPO=DESART,NOENTER,AUXILIAR,TOOLTIP("Descripción de artículo"),TITULO("Artículo")
CAMPO=CODLOT,NOENTER,TOOLTIP("Lote"),TITULO("Lote"),WLONX=-10
CAMPO=CADUCI,TOOLTIP("Caducidad en formato AAAAMMDD"),TITULO("Caduci"),WLONX=15
CAMPO=BLOQSTOCK,NOENTER,TOOLTIP("Bloqueos con los que entra el stock"),TITULO("Bloq.stock"),WLONX=20
CAMPO=CANTIDADR,NOUPDATE("V10"),TOOLTIP("Cantidad recibida en esta recepción en registro burocratico por pantalla de PC"),TITULO("Cant. recep.")
CAMPO=CODCOMEN,NOENTER,OCULTO,"#########",TOOLTIP("")
CAMPO=MUESTREADO,NOENTER,TOOLTIP("Indica si se ha muestreado ese lote"),TITULO("Muestreado"),WLONX=70
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Usuario que ha realizado la ultima modificación.Es utilizado para depuración y control de los registros en las tablas"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=OBSERVACION1,TOOLTIP("Observaciones a la línea de recepción"),TITULO("Observaciones")

CURSOR=CDESART SELECT DESART
                 FROM VDARTIC
                WHERE CODART = :CODART;
                
CONTEXTUAL=FLEEMENU("VDRECEPLIN.ZOO")                