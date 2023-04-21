# Módulo   : VDARTIC.PAN
# Función  : Mantenimiento de artículos
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE ARTICULOS
 Código   _40________________________________ ________________________________________
                Descripción alt.  ________________________________________ 

 División ____ _40_____________________ Art.para División _40_________________         
 Código Nacional    _____________  Ean ______________ 
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ Propiedades ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³ Unidades       __________     Anulado  _           Stock _     Traza bulto _  ³
 ³ Unidades Host  __________     Genérico _    Orden salida _        Etiqueta _  ³
 ³ Decimales:     @                                              Agrupa stock _  ³   
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ 






 Activo _ Comentario @L,@@@@@@@  Ultima modificación _32_____ ¿D-MM-Y.YY  ________       
|


TABLA=VDARTIC



CAMPO=CODART,NOUPDATE,TOOLTIP("Código interno del artículo")
CAMPO=DESART,TOOLTIP("Designación del artículo")
CAMPO=DESARTALT,TOOLTIP("Designación alternativa del artículo")
CAMPO=CODDIV,TOOLTIP("División a la que pertenece el artículo"),POSTCHANGE=FDESIGNACION("CSELDIVIS","No existe división"),
                CONTEXTUAL=FEJECUTAFORM("VDSELDIVIS","N","","","CODDIV=:CODDIV","Selección de división","S")
CAMPO=DESDIV,AUXILIAR,NOUPDATE,TITULO("Descripción") ,CONTEXTUAL=FEJECUTAFORM("VDSELDIVIS","N","","","CODDIV=:CODDIV","Selección de división","S"),WHERE=CODDIV IN (SELECT CODDIV FROM VDDIVIS WHERE DESDIV LIKE '%'||:DESDIV||'%');
CAMPO=CODARTDIV,TOOLTIP("Código del artículo para la división")
CAMPO=CODNAC,TOOLTIP("Código nacional")
CAMPO=CODEAN,TOOLTIP("Código EAN DUN14")
CAMPO=UNIDADES,TOOLTIP("Unidades en las que se mide el artículo en V10"),POSTCHANGE=FDESIGNACION("CSELUNIDADES","No existen las unidades V10"),
               CONTEXTUAL=FEJECUTAFORM("VDUNIDADES","N","","","UNIDADES=:UNIDAD","Selección de unidades","S")
CAMPO=SWTANULADO,TOOLTIP("Indica si el producto tiene preanulado el precio"),POSTCHANGE=FENRANGO("S,N,I","Debe introducir S(i) o N(o)o I(ndiferente)")
CAMPO=SWTSTOCK,TOOLTIP("Indica si el producto controla stock"),POSTCHANGE=FENRANGO("S,N","Debe introducir S(i) o N(o)")
CAMPO=TRAZABULTO,TOOLTIP("Indica si el artículo precisa trazabilidad de bulto"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)")
CAMPO=UNIDADESHOST,TOOLTIP("Unidades en las que mide el artículo el Host"),POSTCHANGE=FDESIGNACION("CSELUNIDADESHOST","No existen las unidades Host"),
               CONTEXTUAL=FEJECUTAFORM("VDUNIDADES","N","","","UNIDADESHOST=:UNIDAD","Selección de unidades","S")
CAMPO=SWTGENERICO,TOOLTIP("Indica si el producto debe tomar designacion de comentarios en albaranes"),POSTCHANGE=FENRANGO("S,N","Debe introducir S(i) o N(o)")
CAMPO=ORDENSAL,TOOLTIP("Orden de salida del articulo C(aducidad) F(ifo) R(etest) L(ote)"),POSTCHANGE=FVERIFICA("CFRL","Debe introducir C(aducidad) F(ifo) R(etest) L(ote)")
CAMPO=SWTETIQ,TOOLTIP("Indica si se puede leer la etiqueta del producto"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)")
CAMPO=DECIMALES,TOOLTIP("Numero de decimales en la representación de cantidades")
CAMPO=AGRUPALIN,TOOLTIP("Indica si la ubicación ha de agrupar las lineas con las mismas caracteristicas"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)")
CAMPO=SWTACTIVO,TOOLTIP("Indica si el producto esta activo"),POSTCHANGE=FENRANGO("S,N","Debe introducir S(i) o N(o)")
CAMPO=CODCOMEN,TOOLTIP("Código de comentario asociado al producto")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELDIVIS SELECT DESDIV FROM VDDIVIS WHERE CODDIV=:CODDIV;

CURSOR=CSELUNIDADES SELECT UNIDAD UNIDADES FROM VDUNIDADES WHERE UNIDAD=:UNIDADES;
CURSOR=CSELUNIDADESHOST SELECT UNIDAD UNIDADESHOST FROM VDUNIDADES WHERE UNIDAD=:UNIDADESHOST;



