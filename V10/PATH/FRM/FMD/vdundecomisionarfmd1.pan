##############################################################################
#  Módulo  : VDUNDECOMISIONARFMD1.PAN                                        #
#  Función : Decomisionar un numero de serie                                 #
#                                                                            #
#  Revisador por  :                                                          #
#  Fecha revisión :                                                          #
##############################################################################
#  Histórico de cambios
#  --------------------
#
##############################################################################
ACTIVAR DESACTIVAR UNIDADES
 Motivo  ____________________
|

NOQUERY
NOCOMMIT
NOINSERT
NOUPDATE
NODELETE

WLONX=300					

CAMPO=MOTIVOFMD,AUXILIAR,COMBOX("CSELMOTIVOFMD")

CURSOR=CSELMOTIVOFMD SELECT MOTIVOFMD FROM VDMOTIVOFMD;

					 
ONLINE=     {F1} Ayuda {F2} Consulta {F4} Confirmar cambios {F5} Borrar pantalla {F9} Borrar registro
                                    {May-F10} Menú {Esc} Salir;
