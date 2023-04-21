###########################################
# Módulo   : VEGAMONINVENCABDATOS.PAN
# Función  : Monitor de inventarios
#
# Creación : 04-04-2022
# Autor    : VEGA
###########################################
# Histórico de cambios:
DATOS SOBRE CONTEOS DE INVENTARIOS REALIZADOS VEGA
               ÏÄÄÄÄÄÄ Matriculas ÄÄÄÄÄÄÄÄÄË   ÏÄÄStock ajustadoÄÄÄË 
Nº Ubicaciones  Inventariadas  Descuadradas  Positivo   Negativo  Roturas
 ##########      ##########    ##########   + #######  - #######  #########
                                                                            |
TABLA=VDINVENCAB
ORDERBY=STATUS,CODINVEN DESC;

PQUERY
POSX=1
POSY=1
REGPAG=2
NODELETE
NOINSERT
NOUPDATE

POSTQUERY=FEJECUTA("+CCALDATOS","",
                   "+CCALSTOCK","")

WFRAME(108,-2,195,0,"Matrículas","text-aling:center")
WFRAME(301,-2,200,0,"Stock ajustado","text-aling:center")

CAMPO=CODINVEN,NOUPDATE,TOOLTIP("Código de inventario obtenido del secuencia VDSECINVEN"),OCULTO,VIRTUAL
CAMPO=NUBIAINVEN,NOENTER,AUXILIAR,TITULO("Nº Ubicaciones"),WLONX=30
CAMPO=NMATINVEN,NOENTER,AUXILIAR,TITULO("Inventariadas"),WLONX=25
CAMPO=NMATDESCUADRE,NOENTER,AUXILIAR,TITULO("Descuadradas"),WLONX=25
CAMPO=STKPOSITIVO,NOENTER,AUXILIAR,TOOLTIP("Cantidad ajustada positivamente"), TITULO("Positivo"),WLONX=20
CAMPO=STKNEGATIVO,NOENTER,AUXILIAR,TOOLTIP("Cantidad ajustada negativamente"), TITULO("Negativo"),WLONX=20
CAMPO=STKROTURAS,NOENTER,AUXILIAR,TOOLTIP("Cantidad ajustada por unidades defectuosas"), TITULO("Roturas")
                              
CURSOR=CCALDATOS SELECT COUNT(DISTINCT CODUBI) NUBIAINVEN, COUNT(DISTINCT CODMAT) NMATINVEN,
                        SUM(CASE WHEN STATUS IN (VDST.FINOFINALIZADO, VDST.FINOVALIDADO) AND
                                      (CODARTREAL != CODARTTEORICO OR CODLOTREAL != CODLOTTEORICO OR CANTREAL != CANTTEORICO OR CANTROTAS >0) THEN
                                      1
                                 ELSE 0 END) NMATDESCUADRE
                   FROM VDINVENCONTEO
                  WHERE CODINVEN = :CODINVEN
                    AND STATUS IN (VDST.FINOFINALIZADO, VDST.FINOVALIDADO);

CURSOR=CCALSTOCK SELECT SUM(DECODE(CODCONCE, 'INVAJU-', CANTIDAD, 0)) STKNEGATIVO,
                        SUM(DECODE(CODCONCE, 'INVAJU+', CANTIDAD, 0)) STKPOSITIVO,
                        SUM(DECODE(CODCONCE, 'INVROT', CANTIDAD, 0)) STKROTURAS
                   FROM VDMOVIM
                  WHERE CODDOCUMENTO = :CODINVEN
                    AND CODCONCE    IN ('INVAJU-','INVAJU+','INVROT')
                    AND STATUS       < VDST.FMOVANULADO;



ONLINE= {F1} Ayuda    {F2} Consulta     {Esc} Cerrar Pantalla    {F5} Borrar Pantalla    ;
