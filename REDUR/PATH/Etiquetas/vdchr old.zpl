$C$
$X1760-1080$
$F0$
$D0$

###### Cuadro Exterior
$P1395-1140$
$L1345-915-40-1$

###### Cuadro Codigo de barras de ChronoExpres
$P1395-1020$
$L500-380-40-1$

###### Cuadro Remitente
$P650-645$
$L600-250-40-1$

###### Cuadro extra datos cliente
$P1395-645$
$L745-130-40-1$

###### Cuadro ChronoExpres
$P650-1755$
$L600-300-40-1$

###### Cuadro extra datos cliente
$P1290-645$
$L120-130-40-1$

###### Cuadro extra datos cliente
$P900-645$
$L100-130-40-1$


######################DATOS DEL REMITENTE
$T12-12$
$P060-222$
$IRemitente:$
#Descripción de la division
$T18-8$
$P060-282$
$I%T_DESDIV-1-40%$
#Dirección de la división
$T8-8$
$P060-330$
$I%T_DIV_DIRECCION%$
#Población de la division
$P060-355$
$I%T_DIV_POBLACION%$
#DP y descripción de la Población
$P060-380$
$I%T_DIV_DP% - %T_DIV_PROVINCIA%$


######################DATOS DEL DESTINATARIO
$T12-12$
$P655-222$
$IDestinatario:$
##Descripción del destinatario
$T8-8$
$P655-282$
$I%T_PC_DESCLIENTE%%T_PC_DESCLIENTE1%$
$T8-8$
$P655-315$
$IATT: %T_CONTACTO%$
##Dirección del destinatario
$P655-350$
$I%T_PC_DIRECCION-1-30% %T_PC_DIRECCION1-1-22%$
$P755-380$
$I%T_PC_DIRECCION1-23-6% %T_PC_DIRECCION2-1-30%$
##Datos destino Chonoexpres
$T8-8$
$P655-400$
$I%T_PC_DP%$
$T8-8$
$P655-430$
$I%T_CHRDATOSDEST%$
$T8-8$
$P655-460$
$I%T_PC_PROVINCIA%$
$T8-8$
$P655-490$
$IObservaciones :%T_PC_OBSERVACIONES-1-37%$
$P655-520$
$I%T_PC_OBSERVACIONES-38-52%$
$P755-550$
$I%T_PC_OBSERVACIONES-90-52%$

###################### CHRONOEXPRES Y SERVICIO
$T8-8$
$P060-450$
$IEntrega: %T_CODPED%$
$T8-8$
$P060-480$
$ISerie: %T_CODPED%$
$T8-8$
$P060-510$
$IBulto: %i_NBULTO% / %T_TOTALBULTOS%$ 
$T8-8$
$P060-540$
$IPeso (kg): %i_PESOTEORICO%$


$T15-13$
$P060-620$
$I%_DESAGE-1-18% GROUPING XXX$
#fecha de expedicion

##################### Datos Extra para la agencia

$I%_DESAGE-1-18% GROUPING XXX$
#fecha de expedicion

##################### Datos Extra para la agencia

$T10-8$
$P655-580$
$IEmbalaje$
$P655-610$
$I%T_TIPOCAJA%$
#$P830-580$
#$IPeso (kg): $
#$T10-8$
#$P830-610$
#$I%i_PESOTEORICO%$
$P900-580$
$INúmero de pedido cliente$
$P900-610$
$I%T_PEDIDOCLIENTE%$
$P1180-580$
$IUnidades$
$P1200-610$
$I%i_NLINEAS%$
$P1300-580$
#$IBulto$
#$P1300-610$
#$I%i_NBULTO% / %T_TOTALBULTOS%$ 

################Derecha del codigo de barras
$T10-8$
$P1000-700$
$IZonas: %T_ZONASPICKING%$
$P1000-730$
$ITipo de bulto: %T_TIPOBULTO%$



################## Codigo de barras 1: Codigo de barras de ChronoExpress

$T10-12$
$P60-680$
$IEXP: %T_CHRCODBARRAS-1-20%$

$P120-980$
$B8-60-271-2-%T_CHRCODBARRAS-1-20%$

#######################################CODIGO DE BARRAS DE BULTO
$D270$
$P1650-1180$
$B8-50-250-4-¿00%T_CODBULTO%$
#LO MISMO EN HUMANO
$P1680-980$
$T9-9$
$ISSCC (00)%T_CODBULTO%$ 
