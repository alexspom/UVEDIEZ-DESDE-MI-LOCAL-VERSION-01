# Módulo   : VDBULTOZONAPINV.PAN
# Función  : Bultos de zonas de picking inverso
#
# Creación : 28-01-2009
# Autor    : FGS
###########################################
BULTOS DE LAS ZONAS DE PICKING INVERSO
Zon Matrícula          Bulto              Codope    Estado                   Impresora
@L@ _18_______________ _18_______________ _10______ @L@@ _32________________ _32______________ 
|

REGPAG=10
SOLOQUERY
SELECT = SELECT * FROM 
             (SELECT BZO.CODZONA, BZO.CODBULTO, BPC.CODMAT, BZO.CODOPE, BZO.STATUS, DECODE(BZO.CODZONA,1,'PICKING1',2,'PICKING1','PICKING2') IMPRESORA 
                FROM VDBULTOZONA BZO, VDBULTOCABPINV BPC
                WHERE BZO.CODBULTO=BPC.CODBULTO)
            WHERE 1 = 1;
            
AQUERY                
POSY=2
POSX=2
ORDERBY=CODZONA;

NOINSERT
NODELETE

CAMPO=CODZONA,NOUPDATE,TOOLTIP("Código de la zona en la que se procesa el bulto"),TITULO("Zona"),WLONX=15
CAMPO=CODMAT,TOOLTIP("Código de la matrícula de bulto de picking inverso"),TITULO("Matrícula")
CAMPO=CODBULTO,NOUPDATE,TOOLTIP("Código del bulto"),TITULO("Bulto")
CAMPO=CODOPE,TOOLTIP("Operario que trata el bulto"),TITULO("Codope")
CAMPO=STATUS,POSTCHANGE=FDESIGNACION("CSELSTATUS","No existe estado"),TOOLTIP("Estado del bulto en la zona"),TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,TOOLTIP("Descripcion del status")
CAMPO=IMPRESORA,TITULO("Impresora")

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='BZO';

TECLA=SF8,FIMPRIME("ETIQ","VDETIBPC.ZPL;VDETIQBPC_PG.VSQ;CBULTOBPCCOPIA","CODBULTO=:CODBULTO",":IMPRESORA","1")

CONTEXTUAL=FLEEMENU("VDBULCABPINV.ZOO")

ONLINE=	{F1} Ayuda  {F2} Consulta  {F4} Confirmar Cambios  {F5} Borrar Pantalla
        {F9} Borrar Registro  {Máy-F8} Imprime etiqueta {Esc} Salir;
