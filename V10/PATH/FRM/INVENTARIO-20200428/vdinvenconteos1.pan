#*****************************************************************
#Módulo: VDINVENCONTEOS.PAN
#Funcionalidad : Muestra todos los conteos de los inventarios.
#Autor: ICC      
#Fecha: 03-02-2010
#*****************************************************************
#* Histórico de cambios
#* ====================
#
INVENTARIOS REALIZADOS POR MATRICULA Y STOCK TEORICO
Matricula            Artículo                                           Lote               Cantidad
_18_______________   _40______________ _100____________________________ _40_______________ ######## _10_
                                                                                                           |
SELECT=SELECT CODMAT,CODARTTEORICO,CODLOTTEORICO,CANTTEORICO
         FROM VDINVENCONTEO
        WHERE NVL(:CODMATINVL, CODMAT)=CODMAT;
ORDERBY=CODMAT;
GROUPBY=CODMAT,CODARTTEORICO,CODLOTTEORICO,CANTTEORICO;

SOLOQUERY
NODELETE
NOINSERT


CAMPO=CODINVEN,TOOLTIP("Código de inventario"),VIRTUAL, OCULTO
CAMPO=CODUBI,TOOLTIP("Código de ubicación a inventariar"),VIRTUAL, OCULTO
CAMPO=CODMATINVL,TOOLTIP("Código de matrícula a inventariar"),VIRTUAL,AUXILIAR, OCULTO
CAMPO=CODMAT,NOUPDATE,TITULO("Matrícula")
CAMPO=CODARTTEORICO,NOENTER,TOOLTIP("Código de artículo antes de inventariar"), POSTCHANGE=FDESIGNACION("+CSELDESARTT",""),TITULO("Artículo")
CAMPO=DESARTT,AUXILIAR,NOENTER
CAMPO=CODLOTTEORICO,NOENTER,TOOLTIP("Código de lote antes de inventaria"),TITULO("Lote")
CAMPO=CANTTEORICO,NOENTER,TOOLTIP("Cantidad antes de inventaria"),TITULO("Cantidad")
CAMPO=UNIDADESHOST,NOENTER,AUXILIAR

CURSOR=CSELDESARTT SELECT DESART DESARTT, UNIDADESHOST
                     FROM VDARTIC
                    WHERE CODART = :CODARTTEORICO;

ONLINE= {F1} Ayuda    {F2} Consulta    {Esc} Cerrar Pantalla    {F5} Borrar Pantalla    ;


