# Módulo   : VDARTIC.PAN
# Función  : Mantenimiento de artículos
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
CONSULTA DE ARTICULOS
 Código                                             Div   Código Nacional Ean     
 _40___________ _100_______________________________ _20__ _13____________  ______________
|


TABLA=VDARTIC
NOINSERT
NODELETE
NOUPDATE
WLONX=700


CURSOR=CIMAGEN SELECT DECODE(:CODEAN,NULL,NULL,'ART/'||:CODEAN||'.jpg') IMAGEN FROM DUAL;
 
CAMPO=IMAGEN,OCULTO,AUXILIAR,"_255_____",NOUPDATE
CAMPO=CODART,NOUPDATE,TOOLTIP("Código del artículo"),INCLUDECSS="border-style:ridge;background-color:#F7BE81;",TITULO("Artículo")
CAMPO=DESART,TOOLTIP("Designación del artículo")
CAMPO=CODDIV,TOOLTIP("División a la que pertenece el artículo"),TITULO("Div"),WLONX=16
CAMPO=CODNAC,TOOLTIP("Código nacional"),TITULO("Código Nacional"),WLONX=26
CAMPO=CODEAN,TOOLTIP("Código EAN DUN14"),TITULO("Ean")

BOTON=PRUEBA,800,50,300,300,"Limpiar",NO,SF1,"Limpia la pantalla",INCLUDECSS="visibility:hidden;",BOTONDISABLED=1
#BOTON=KK,800,250,70,30,"DEMO",NO,SF1,"Limpia la pantalla"

