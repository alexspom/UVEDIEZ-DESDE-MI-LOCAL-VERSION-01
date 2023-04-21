# Módulo   : VDLISTADOARTICULOS.PAN
# Función  : Listado de articulos REDUR
#
# Creación : 28-03-2020
# Autor    : infanahe
###########################################
# Histórico de cambios:
#
LISTADO DE ARTICULOS
 CODDIV CODART DESART             CLASEREDUR TIPOABC CODUBI Libre    Bloqueado Reservado  Cont.    UNIEMB EMBPISO EMBCONT ALTOUNI ANCHOUNI LARGOUNI PESOUNI ALTOCAJC ANCHOCAJC LARGOCAJC PESOCAJC   
 _3_    _40__  _100______________ _15___     _5___  _10___  #L,##### #L,####   #L,####    @L@@@    @L@@@@@ @L@@@@@ @L@@@@@   #L##    #L##     #L##     #L##    #L##     #L##      #L##      #L##   
 |


SOLOQUERY
TABLA=ART
SELECT=SELECT * FROM (select A.CODDIV, A.CODART, A.DESART, CLASEREDUR.CODCLASE CLASEREDUR,
              TIPOABC.CODCLASE TIPOABC, U.CODUBI, A.UNIEMB, A.EMBPISO, A.EMBCONT, A.ALTOUNI,
              A.ANCHOUNI, A.LARGOUNI, A.PESOUNI, A.ALTOCAJC, A.ANCHOCAJC, A.LARGOCAJC,
              A.PESOCAJC, CANTIDAD.LIBRE, CANTIDAD.BLOQUEADO, CANTIDAD.CONTENEDORES,
              CANTIDAD.RESERVADO
         from VDARTIC A,
              (select *
                 from VDCLASEARTIC
                where CODCLASIF = 'REDUR') CLASEREDUR,
              (select *
                from VDCLASEARTIC
               where CODCLASIF = 'TIPOABC') TIPOABC, VDUBICA U,
               (select ART.CODART,
                       VDART.VD2HOST(sum(DECODE(STK.BLOQUEOS, '0000000000', CANTIDAD, 0)),
                          STK.CODART) LIBRE,
                       VDART.VD2HOST(sum(DECODE(STK.BLOQUEOS, '0000000000', 0, CANTIDAD)),
                          STK.CODART) BLOQUEADO,
                       count(distinct STK.CODMAT) CONTENEDORES,
                       VDART.VD2HOST(VDUBI.ALMARESERVADO(ALM.CODALM,'U',ART.CODART),STK.CODART) RESERVADO 
                  from VDALMA ALM, VDAREA ARE, VDUBICA UBI, VDCONTE CNT, VDSTOCK STK,
                       VDARTIC ART
                 where ALM.CODALM = ARE.CODALM
                   and ARE.CODAREA = UBI.CODAREA
                   and UBI.CODUBI = CNT.CODUBI
                   and STK.CODMAT = CNT.CODMAT
                   and STK.CODART = ART.CODART
                 group by ALM.CODALM, ALM.DESALM, STK.CODART, CANTIDAD) CANTIDAD
        WHERE A.CODART = CLASEREDUR.CODART(+) and A.CODART = TIPOABC.CODART(+) and A.CODART = U.CODART(+) and A.CODART like 'BEL%'
              AND CANTIDAD.CODART(+) = A.CODART) ART
        WHERE 1=1;   
WHERE = 1=1;
ORDERBY=ART.CODART;
        
WLONX=1300

CAMPO=CODDIV,TOOLTIP("Cliente"),TITULO("Div"),WLONX=6
CAMPO=CODART,TOOLTIP("Código del artículo"),TITULO("Codigo"),WLONX=20
CAMPO=DESART,TOOLTIP("Designación del artículo"),TITULO("Descripción"),WLONX=70
CAMPO=CLASEREDUR,TOOLTIP("Clase REDUR"),COMBOX("CCLASEREDUR"),TITULO("Clase REDUR"),WLONX=20
CAMPO=TIPOABC,TOOLTIP("ABC"),COMBOX("CTIPOABC"),TITULO("ABC"),WLONX=3
CAMPO=CODUBI,TOOLTIP("Ubicación de Picking asignada"),TITULO("Picking"),WLONX=10
CAMPO=LIBRE,TOOLTIP("Stock libre"),TITULO("Libre"), WLONX=18
CAMPO=BLOQUEADO,TOOLTIP("Stock bloqueado"),TITULO("Bloqueado"), WLONX=18
CAMPO=RESERVADO,TOOLTIP("Cantidad Reservada del Artículo en el Almacén"),TITULO("Reservado"), WLONX=18
CAMPO=CONTENEDORES,TOOLTIP("Número de contenedores"),TITULO("Cont."), WLONX=18
CAMPO=UNIEMB,TOOLTIP("Unidades por caja"), TITULO("Un.caja"),WLONX=6
CAMPO=EMBPISO,TOOLTIP("Cajas por piso de paletización"), TITULO("Cajaxpiso"),WLONX=9
CAMPO=EMBCONT,TOOLTIP("Embalajes por contenedor"), TITULO("Emb.cont"),WLONX=8
CAMPO=PESOUNI,TOOLTIP("Peso de la unidad en gramos"), TITULO("Peso un"),WLONX=8
CAMPO=LARGOUNI,TOOLTIP("Largo de la unidad en mm."), TITULO("Largo un"),WLONX=8
CAMPO=ANCHOUNI,TOOLTIP("Ancho de la unidad en mm."), TITULO("Ancho un"),WLONX=8
CAMPO=ALTOUNI,TOOLTIP("Alto de la unidad en mm."), TITULO("Alto un"),WLONX=8
CAMPO=PESOCAJC,TOOLTIP("Peso de la caja en gramos"), TITULO("Peso cj"),WLONX=8
CAMPO=LARGOCAJC,TOOLTIP("Longitud de la caja completa en mm."), TITULO("Largo cj"),WLONX=8
CAMPO=ANCHOCAJC,TOOLTIP("Ancho de la caja completa en mm."), TITULO("Ancho cj"),WLONX=8
CAMPO=ALTOCAJC,TOOLTIP("Alto de la caja completa en mm."), TITULO("Alto cj"),WLONX=8

###CURSORES

CURSOR=CCLASEREDUR select codclase from vdclases WHERE CODCLASIF = 'REDUR';

CURSOR=CTIPOABC select codclase, desclase from vdclases WHERE CODCLASIF = 'TIPOABC';

###TECLAS
TECLA=SF10,FLEEMENU("VDLISTADOARTICULOS.ZOO")




