BUSQUEDA ALFABETICA DE ARTICULOS

 Designaci�n                              C�digo               Cod. nac.
 _40_____________________________________ _40_________________ _____________  





















                                                                            |

TABLA=VDARTIC

WLONX=650

WHERE=ORDER BY DESART;

PREQUERY=FEJECUTA("CANADE","")


CAMPO=DESART,UPPER,TOOLTIP("Designaci�n del art�culo, se puede introducir todo o parte de la misma"),TITULO("Designaci�n")
CAMPO=CODART,UPPER,TOOLTIP("C�digo del art�culo"),TITULO("C�digo")
CAMPO=CODNAC,TOOLTIP("C�digo nacional del art�culo"),TITULO("C�d. Nac.")

CURSOR=CANADE SELECT '%'||:DESART||'%' DESART FROM DUAL;

