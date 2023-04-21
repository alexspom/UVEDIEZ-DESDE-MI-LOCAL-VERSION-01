# Módulo   : VDARTIC.PAN
# Función  : Mantenimiento de artículos
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
DETALLE DEL ARTICULO
 Código                 _40____________________ 
       _100____________________________________
 
 División               _20___ 
                        _40______________________________   
 
 Artículo para División ____________________
 
 Código Nacional        _____________ 
 
 Ean                    ______________         
 
 Descripción alt.       _40____________________________  
 
 Unidades               __________     
 
 Unidades Host          __________     
 
 UniCaj:                @L@@
 
 PVD Vigente            #L,########.### 
 
 Activo _     
 
 Ult. modificación ¿D-MM-Y.YY  ________
|


TABLA=VDARTIC
NOINSERT
NODELETE
NOUPDATE


CAMPO=IMAGEN,OCULTO,AUXILIAR,"_255_____",NOUPDATE
CAMPO=CODART,VIRTUAL,NOUPDATE,TOOLTIP("Código del artículo"),INCLUDECSS="border-style:ridge;background-color:#F7BE81;"
CAMPO=DESART,TOOLTIP("Designación del artículo")
CAMPO=CODDIV,TOOLTIP("División a la que pertenece el artículo"),POSTCHANGE=FDESIGNACION("CSELDIVIS","No existe división")
CAMPO=DESDIV,AUXILIAR,NOENTER,TOOLTIP("Designación de la división")
CAMPO=CODARTDIV,TOOLTIP("Código del artículo para la división")
CAMPO=CODNAC,TOOLTIP("Código nacional")
CAMPO=CODEAN,TOOLTIP("Código EAN DUN14")
#,INCLUDECSS="background-color:darkgreen;color:yellow;height:20px"
CAMPO=DESARTALT,TOOLTIP("Designación alternativa del artículo")
CAMPO=UNIDADES,TOOLTIP("Unidades en las que se mide el artículo en V10"),
               CONTEXTUAL=FEJECUTAFORM("VDUNIDADES","N","","","UNIDADES=:UNIDAD","Selección de unidades","S")
CAMPO=UNIDADESHOST,TOOLTIP("Unidades en las que mide el artículo el Host"),
               CONTEXTUAL=FEJECUTAFORM("VDUNIDADES","N","","","UNIDADESHOST=:UNIDAD","Selección de unidades","S")
CAMPO=UNIEMB,TOOLTIP("Unidades por embalaje"),CONVIERTE=FCONVIERTEFROMDB(":UNIDADES",":UNIDADESHOST");FCONVIERTE2DB(":UNIDADESHOST",":UNIDADES")
CAMPO=PVDVIGENTE,TOOLTIP("Precio de venta al distribuidor vigente")
CAMPO=SWTACTIVO,TOOLTIP("Indica si el producto esta activo"),POSTCHANGE=FENRANGO("S,N","Debe introducir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")
CURSOR=CLISTATIPOVOL SELECT TIPOVOL,DESVOL FROM VDVOLUMETRIA ORDER BY TIPOVOL;


CURSOR=CSELDIVIS SELECT DESDIV FROM VDDIVIS WHERE CODDIV=:CODDIV;

