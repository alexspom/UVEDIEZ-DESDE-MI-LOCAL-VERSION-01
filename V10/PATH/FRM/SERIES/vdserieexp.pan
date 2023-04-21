###################################################################
#Módulo: VDSERIEEXP.PAN
#Funcionalidad : Mantenimiento de series de expedición
#Autor: FPD      
#Fecha: 22-04-2008
###################################################################
# Histórico de cambios:
MANTENIMIENTO SERIES DE EXPEDICION
       Serie ÏÄÄ BOLETA ÄË                                               
Código Prep.  Año  Código Agencia                 P. Pri Estado             Desc 
@L@@@@ @L@@@@ @L@@ @L@@@@ _10____ _30____________ @@ @@  @L@@@@ _30________ _1000_____________ 

|

TABLA=VDSERIEEXP
ORDERBY=CODSERIEEXP DESC;

POSTQUERY=FEJECUTA("CSELAGENCIA","ERROR AL RECUPERAR LA DESCRIPCION DE LA AGENCIA")

WFRAME(61,-2,45,0,"Serie","")
WFRAME(106,-2,90,0,"Boleta","")


CAMPO=CODSERIEEXP,NOUPDATE,TOOLTIP("Clave única de la serie de expedición"),TITULO("Código"), WLONX=20
CAMPO=CODSERIEPREP,NOUPDATE,TOOLTIP("Clave única de la serie de preparación"),TITULO("Prep.")
CAMPO=ANOBOLETA,NOENTER,TOOLTIP("Año de expedición de la boleta de transporte"),TITULO("Año")
CAMPO=CODBOLETA,NOENTER,TOOLTIP("Código de la boleta de transporte para la agencia"),TITULO("Código"), WLONX=20
CAMPO=CODAGE,NOENTER,TOOLTIP("Código de la agencia que recoge la serie"),CONTEXTUAL=FEJECUTAFORM("VDAGENCIA","N","CODAGE=:CODAGE","","","MANTENIMIENTO DE AGENCIAS","S"),TITULO("Agencia")
CAMPO=DESAGE,AUXILIAR,NOENTER,TOOLTIP("Descripción de la agencia que recoge la serie")
CAMPO=PUERTO,TOOLTIP("Número de puerto del sorter por el que se desvían las cajas de la serie"),TITULO("P.")
CAMPO=PRIORIDAD,TOOLTIP("Prioridad de la serie de expedición. Inicialmente es heredada de la serie de preparación."),TITULO("Pri"), WLONX=18
CAMPO=STATUS,NOUPDATE("IMPLANTADOR"),TOOLTIP("Estado en que se encuentra la serie /n :DESSTATUS"),POSTCHANGE=FDESIGNACION("CSELSTATUS","STATUS NO EXISTE"),TITULO("Estado"), WLONX=20
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TITULO("")
CAMPO=DESSERIE,TOOLTIP("Descripción de la serie"),TITULO("Descripción")
CAMPO=CODCOMEN,OCULTO,"@@@@@@@@@"

CURSOR=CSELSTATUS SELECT DESSTATUS 
                    FROM VDSTATUS 
                   WHERE TIPOSTATUS='SEX' AND STATUS=:STATUS; 
                   
CURSOR=CSELAGENCIA SELECT DESAGE 
                     FROM VDAGENCIA
                    WHERE CODAGE=:CODAGE;
                    



TECLA=SF8,FEJECUTA(FIMPRIME("INFORME","$(VDBOLETA)","CODBOLETA=:CODBOLETA;ANOBOLETA=:ANOBOLETA;FORMCOPIA='S';",""),":V10ERROR",FCOMMIT,"")


ONLINE= {May+F10} Datos de la serie de preparación {May+F8} Impresion listado;
