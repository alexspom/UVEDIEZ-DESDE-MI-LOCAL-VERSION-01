# MСdulo   : vdnumseriesfpmd.PAN
# FunciСn  : Condiciones de busqueda de numeros de serie asociados a bulto
#
# CreaciСn : 28-03-2020
# Autor    : infanahe
###########################################
# HistOrico de cambios:
#
CONDICIONES DE BUSQUEDA
  DivisiСn: ______ 
 
 одддддддддд RANGO DE FECHAS ддддддддддк
 Ё Inicio: ©D-MM-YY.Y  Fin: ©D-MM-YY.Y Ё
 юддддддддддддддддддддддддддддддддддддды
 
 Motivo:  _20__________
|
 
 NOORAINS
 NOCOMMIT
 NOQUERY
 
 WLONX=400
 
CAMPO=DIVISIONP,AUXILIAR,COMBOX("CLISTADIV")
CAMPO=FECHAINICIOP,AUXILIAR,TOOLTIP("Fecha inferior del intervalo. Formato DD-MM-AAAA."),COMBOX("CALENDARIO")
CAMPO=FECHAFINP,AUXILIAR,TOOLTIP("Fecha superior del intervalo. Formato DD-MM-AAAA."),COMBOX("CALENDARIO")
CAMPO=MOTIVOP,AUXILIAR,TOOLTIP("Agregar Motivo"), WLONX=100

CURSOR=CLISTADIV SELECT CODDIV BCODDIV,DESDIV,DESEMP FROM VDDIVIS DIV,VDEMPRE EMP 
				 WHERE EMP.CODEMP=DIV.CODEMP AND EMP.CODEMP='001' ORDER BY CODDIV;

ONLINE= {F1} Ayuda    {F2} Consulta    {F5} Borrar Pantalla    {Esc} Cerrar Pantalla ;




