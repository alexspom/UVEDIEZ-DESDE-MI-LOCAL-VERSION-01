#
# Etiqueta de para cajas para la recepción de la mercancía con matricula incorporada
# 10-01-2017. DZG
#
$C$
@VDPRODRECEP.GEN
$D0$
#$T10-10$
#$P900-50$
#$IALBARAN:$
#
#$P1100-100$
#$B8-30-80-2-%T_NUMALBARAN%$
#
#$P900-150$
#$I%T_NUMALBARAN%$

$P1000-400$
$I%T_CODMATPARETS%$

$T40-00$
$P1100-650$
$I%T_RP%$

$T10-10$
$P50-50$
$IMATRICULA$

#$D90$
$P250-200$
$B8-70-180-2-%T_CODMAT%$
$P400-250$
$I%T_CODMAT%$
$A$