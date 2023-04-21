###################################################################
#Módulo: VDSTOCKFUENTE1.PAN
#Funcionalidad :  Pantalla para consulta de lso registros de la tabla vdstockfuente
#Autor: FGS      
#Fecha: 17-07-2008
###################################################################
# Histórico de cambios:
REGISTROS PARA CREACION DE STOCK
Sec.      Tipo       Ubic.        Codmat             Tipo Cont. Artículo             Lote                 Cantidad Host       Status
######### _10_______ _20_________ __________________ __________ _40_________________ _40_________________ #########.#### _10_ @@@@@  _255____ _20______  
|
TABLA=VDSTOCKFUENTE
ORDERBY=SEQFUENTE DESC;


CAMPO=SEQFUENTE,TOOLTIP("Secuencia de la generación de stock"),TITULO("Secuencia"),WLONX=22
CAMPO=TIPOFUENTE,TOOLTIP("Tipo de generación de stock"),TITULO("Tipo")
CAMPO=CODUBI,TOOLTIP("Ubicación en la que se creará el stock"),TITULO("Ubicación"),CONTEXTUAL=FEJECUTAFORM("VDUBICA","S","CODUBI=:CODUBI","","","Consulta de Ubicación","S")
CAMPO=CODMAT,TOOLTIP("Si se informa, matrícula en la que se crea el stock"),TITULO("Matrícula"),CONTEXTUAL=FEJECUTAFORM("VDCONTE","S","CODMAT=:CODMAT","","","Consulta de Contenedor","S")
CAMPO=TIPOCONTE,TOOLTIP("Tipo de contenedor a crear, si no se informa matrícula"),TITULO("Tipo Cont.")
CAMPO=CODART,TOOLTIP("Artículo del que se crea stock"),TITULO("Artículo"),CONTEXTUAL=FEJECUTAFORM("VDARTIC","S","CODART=:CODART"),TITULO("Articulo")
CAMPO=CODLOT,TOOLTIP("Lote del que se crea stock"),TITULO("Lote")
CAMPO=CANTIDADHOST,TOOLTIP("Cantidad a crear en stock en unidades HOST"),TITULO("Cantidad Host")
CAMPO=UNIDADESHOST,TOOLTIP("Unidades HOST de la cantidad de stock a crear")
CAMPO=STATUS,TOOLTIP("Estado del registro")
CAMPO=VDEXTRA,TOOLTIP("Datos adicionales externos a V10 y útiles para el cliente")
CAMPO=CODRECEP,TOOLTIP("Código de Recepción del stock a crear")