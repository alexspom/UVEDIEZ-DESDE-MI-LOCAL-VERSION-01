#
# VDINVENINCUMPLE.PAN: Inventario realizado, pero incumple una de las condiciones para que sea correcto, ver PLSQL VDINVEN.
#
INVENTARIO
__________ __________

##### - ________________________________

  INVENTARIO CON DESCUADRES
  NO ACEPTADOS
 
|

POSTQUERY=FEJECUTA("CINSCONTEO","ERROR INSERTANDO CONTEO\n:V10ERROR",
                   FCOMMIT,"",
                   FPOSICIONABLOQUE("1"),"")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODINVEN,NOENTER,VIRTUAL
CAMPO=DESINVEN,NOENTER,VIRTUAL

CAMPO=CODMATLEIDA,OCULTO,VIRTUAL
CAMPO=CODLOTLEIDO,OCULTO,VIRTUAL
CAMPO=CODARTLEIDO,OCULTO,VIRTUAL
CAMPO=CODUBI,OCULTO,VIRTUAL
CAMPO=CANTTEORICA,OCULTO,VIRTUAL
CAMPO=CANTIDAD,OCULTO,VIRTUAL
CAMPO=CANTROTAS,OCULTO,VIRTUAL
CAMPO=CODART,OCULTO,VIRTUAL
CAMPO=CODLOT,OCULTO,VIRTUAL
CAMPO=FECINI,OCULTO,VIRTUAL
CAMPO=HORAINI,OCULTO,VIRTUAL


CURSOR=CINSCONTEO BEGIN
                    VDINVEN.INSCONTEO (:CODINVEN, :CODUBI,:CODMATLEIDA, :CODART, :CODLOT, :CANTTEORICA, :CODARTLEIDO, :CODLOTLEIDO, :CANTIDAD,
                                       :CODOPE, :FECINI, :HORAINI , :CANTROTAS);
                  END;@



ONLINE=F1 AYUDA F10 LOGOUT ;