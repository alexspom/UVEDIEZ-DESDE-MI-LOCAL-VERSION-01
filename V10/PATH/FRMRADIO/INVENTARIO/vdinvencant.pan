#
# VDINVENCANT.PAN: 
#
INVENTARIO
__________ __________

##### - ________________________________

Matricula: _18_______________
Articulo: _40_________________
 _30_______________________
 _30_______________________
Lote: _40_________________
_________ ######## _10_
 
 U/E       EMB  PICO
#L15###### #### #L########
 
Defectuosas: ##### _10_ 
|

PREQUERY=FEJECUTA("CSELDESART", "ERROR DIVIDIENDO :DESART",
                  FPOSICIONACAMPO(FSUCCESS,"EMB"),"")

POSTQUERY=FEJECUTA(FIF("CSELNOTNULL",FPOSICIONABLOQUE("VDINVENART.PAN"),FSUCCESS),"", 
                   "CSELLOTLEIDO", "LOTE :CODLOT NO EXISTE",
                   "CVALROTAS", "CANTIDAD DEFECTUOSA (:CANTROTAS)\nNO PUEDE SER MAYOR A LA\nCANTIDAD EXISTENTE (:CANTIDAD)\nEN LA UBICACION",
                   FIF("COK", FEJECUTA(FPOSICIONABLOQUE("VDINVENOK.PAN"),""),
                              FEJECUTA(FIF("CVALINVEN", FEJECUTA(FPOSICIONABLOQUE("VDINVENAJUSTE.PAN"), ""),
                                                        FEJECUTA(FPOSICIONABLOQUE("VDINVENINCUMPLE.PAN"), "")),"")),"")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODINVEN,NOENTER,VIRTUAL
CAMPO=DESINVEN,NOENTER,VIRTUAL
CAMPO=CODMATLEIDA,NOENTER,VIRTUAL
CAMPO=CODARTLEIDO,NOENTER,VIRTUAL
CAMPO=DESART1,NOENTER
CAMPO=DESART2,NOENTER
CAMPO=CODLOTLEIDO,VIRTUAL
CAMPO=NCANTSTK,NOENTER
CAMPO=CANTSTK,NOENTER
CAMPO=UNIDADESHOST2,NOENTER
CAMPO=UNIEMB,NOENTER,VIRTUAL
CAMPO=EMB
CAMPO=PICO,CONVIERTE=FCONVIERTEARTFROMDB(":CODARTLEIDO");FCONVIERTEART2DB(":CODARTLEIDO")
CAMPO=CANTROTAS,CONVIERTE=FCONVIERTEARTFROMDB(":CODARTLEIDO");FCONVIERTEART2DB(":CODARTLEIDO")
CAMPO=UNIDADESHOST,VIRTUAL,NOENTER
CAMPO=CODUBI,OCULTO,VIRTUAL
CAMPO=DESART,OCULTO,VIRTUAL
CAMPO=CADUCI,OCULTO,VIRTUAL
CAMPO=CANTTEORICA,OCULTO,VIRTUAL
CAMPO=CODART,OCULTO,VIRTUAL
CAMPO=CODLOT,OCULTO,VIRTUAL
CAMPO=FECINI,OCULTO,VIRTUAL
CAMPO=HORAINI,OCULTO,VIRTUAL
CAMPO=CIEGO,OCULTO,VIRTUAL
CAMPO=CANTIDAD,OCULTO,"#L########"

CURSOR=CSELDESART SELECT VD.DIVIDEXBUSQUEDA (1, :DESART, ' ', 20, 0) DESART1, :UNIDADESHOST UNIDADESHOST2,
                         VD.DIVIDEXBUSQUEDA (2, :DESART, ' ', 20, 0) DESART2, 0 EMB, 0 PICO, 0 CANTROTAS,
                         :CIEGO NCANTSTK__INVISIBLE, :CIEGO CANTSTK__INVISIBLE, :CIEGO UNIDADESHOST2__INVISIBLE,
                         CASE WHEN :CODART = :CODARTLEIDO AND :CODLOT = :CODLOTLEIDO THEN 
                                   :CANTTEORICA END CANTSTK, 'Cantidad:' NCANTSTK
                    FROM DUAL;

CURSOR=CSELNOTNULL SELECT :EMB FROM DUAL 
                    WHERE :EMB = 0 AND :PICO = 0;

CURSOR=CSELLOTLEIDO SELECT ((:UNIEMB*:EMB) + :PICO) CANTIDAD
                      FROM VDLOTES
                     WHERE CODART = :CODARTLEIDO
                       AND CODLOT = :CODLOTLEIDO;


#Validaciones para dar por bueno el inventario
CURSOR=CVALROTAS SELECT :CANTROTAS
                   FROM DUAL
                  WHERE :CANTIDAD > :CANTROTAS;
CURSOR=COK SELECT :CODART
             FROM DUAL
            WHERE :CODART    = :CODARTLEIDO
              AND :CODLOT    = :CODLOTLEIDO
              AND :CANTIDAD  = :CANTTEORICA
              AND :CANTROTAS = 0;

#Inventario no v�lido:
#   1.- Distinto art�culo o lote
#   2.- Porcentaje de cantidad a regularizar mayor que el permitido en la variable PMAXDESCUADRE
#   3.- Cantidad a regularizar mayor a la cantidad definida en la variable CANTMAXDESCUADRE
#   4.- Cantidad a regularizar supera el precio permitido definido en la variable MAXPVP
#   5.- El n�mero de unidades defectuosas es superior al n�mero de unidades definido en la variable MAXUNIROTAS
CURSOR=CVALINVEN  SELECT :CODART
                    FROM DUAL
                  WHERE VDINVEN.VALIDARINVEN (:CODINVEN, :CODUBI, :CODMATLEIDA, :CODART, :CODLOT, :CANTTEORICA, :CODARTLEIDO, :CODLOTLEIDO, :CANTIDAD, :CODOPE, :CANTROTAS)='S';

ONLINE=F1 AYUDA F10 LOGOUT ;