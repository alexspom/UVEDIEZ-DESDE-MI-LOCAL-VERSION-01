$C$
$X1760-1080$
$F0$
$D0$

################## Codigo de barras 1: Codigo de barras de Correos Express

$T10-12$
$P60-680$
$IEXP: %T_RDACODBARRAS%$

$P120-920$
$B8-60-220-2-%T_RDACODBARRAS%$

################Derecha del codigo de barras
$T10-8$
$P920-700$
$IArticulo: %T_CODART%$
$P920-730$
$IUbicacion: %T_CODUBIORI%$

################Derecha extra de RDA
$T10-8$
$P555-480$
$IZona reparto:%T_ZONAREP%$
$P555-510$
$IRuta:%T_NOMBRE_RUTA%$

@VDETIQBU.ZPL

$A$