#
# VDINVENAJUSTE.PAN
#
INVENTARIO
__________ __________

##### - ________________________________
Matricula: _18_______________
Articulo: _40_________________
 _30_______________________
 _30_______________________
Lote: _40_________________
 
 SE VAN A AJUSTAR ####### _10_ 
 ESTA DE ACUERDO? # ( 0 NO, 1 SI)
|

PREQUERY=FEJECUTA("CCALAJUSTES", "")

POSTQUERY=FEJECUTA(FIF("CSELNOTNULL",FPOSICIONABLOQUE("3"),FSUCCESS),"", 
                   "CVALCONFIRMA", "ERROR, CONFIRME CON\n1 PARA SI, 0 PARA NO",
                   "CINSCONTEO","ERROR INSERTANDO CONTEO\n:V10ERROR",
                   "CSELSEQINVEN", "ERROR RECUPERANDO LA\nSECUENCIA DE INVENTARIO",
                   "CAJUDIFERENCIA", "ERROR\n:V10ERROR",
                   "CVERSIERROR", ":MSJERROR",     
                   FCOMMIT,"",
                   FPOSICIONABLOQUE("1"),"")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODINVEN,NOENTER,VIRTUAL
CAMPO=DESINVEN,NOENTER,VIRTUAL
CAMPO=CODMATLEIDA,NOENTER,VIRTUAL
CAMPO=CODARTLEIDO,NOENTER,VIRTUAL
CAMPO=DESART1,NOENTER,VIRTUAL
CAMPO=DESART2,NOENTER,VIRTUAL
CAMPO=CODLOTLEIDO,NOENTER,VIRTUAL
CAMPO=CANTIDADAJ,NOENTER
CAMPO=UNIDADESHOST,VIRTUAL,NOENTER
CAMPO=CONFIRMA
CAMPO=CODUBI,OCULTO,VIRTUAL
CAMPO=CANTTEORICA,OCULTO,VIRTUAL
CAMPO=CANTIDAD,OCULTO,VIRTUAL
CAMPO=CANTROTAS,OCULTO,VIRTUAL
CAMPO=CODART,OCULTO,VIRTUAL
CAMPO=CODLOT,OCULTO,VIRTUAL
CAMPO=FECINI,OCULTO,VIRTUAL
CAMPO=HORAINI,OCULTO,VIRTUAL
CAMPO=SEQINVEN,OCULTO, "##"
CAMPO=CODMOVOUT,OCULTO,"#########"
CAMPO=CANTIDADAJU,OCULTO,"#########"
CAMPO=CODCONCE,OCULTO,"_12______"
CAMPO=MSJERROR,OCULTO,AUXILIAR,"_200____________________________________"

                    
CURSOR=CCALAJUSTES SELECT ((:CANTIDAD - :CANTTEORICA) - :CANTROTAS) CANTIDADAJ
                     FROM DUAL;


CURSOR=CSELNOTNULL SELECT :CONFIRMA FROM DUAL 
                    WHERE :CONFIRMA = 0;

CURSOR=CVALCONFIRMA SELECT :CONFIRMA FROM DUAL
                     WHERE :CONFIRMA IN (0,1);

CURSOR=CINSCONTEO BEGIN
                    VDINVEN.INSCONTEO (:CODINVEN, :CODUBI,:CODMATLEIDA, :CODART, :CODLOT, :CANTTEORICA, :CODARTLEIDO, :CODLOTLEIDO, :CANTIDAD,
                                       :CODOPE, :FECINI, :HORAINI , :CANTROTAS);
                  END;@

CURSOR=CSELSEQINVEN SELECT SEQINVEN
                      FROM VDINVENCONTEO
                     WHERE CODINVEN = :CODINVEN
                       AND CODUBI   = :CODUBI
                       AND CODMAT   = :CODMATLEIDA
                       AND CANTREAL = :CANTIDAD
                       AND CODOPE   = :CODOPE
                     ORDER BY FECFIN DESC, HORAFIN DESC;

CURSOR=CAJUDIFERENCIA BEGIN
                         VDINVEN.REGULARIZAINVEN (:CODINVEN, :CODUBI, :SEQINVEN, :CODART, :CODLOT, :CANTTEORICA, :MSJERROR);
                      END;@

CURSOR=CVERSIERROR SELECT :MSJERROR
                     FROM DUAL
                    WHERE :MSJERROR IS NULL;


ONLINE=F1 AYUDA F10 LOGOUT ;