BUSQUEDA ALFABETICA DE ARTICULOS

 Designación                              Código               Cod. nac.
 _40_____________________________________ _40_________________ _____________  





















                                                                            |

TABLA=VDARTIC

WLONX=650

WHERE=ORDER BY DESART;

PREQUERY=FEJECUTA("CANADE","")


CAMPO=DESART,UPPER,TOOLTIP("Designación del artículo, se puede introducir todo o parte de la misma"),TITULO("Designación")
CAMPO=CODART,UPPER,TOOLTIP("Código del artículo"),TITULO("Código")
CAMPO=CODNAC,TOOLTIP("Código nacional del artículo"),TITULO("Cód. Nac.")

CURSOR=CANADE SELECT '%'||:DESART||'%' DESART FROM DUAL;

