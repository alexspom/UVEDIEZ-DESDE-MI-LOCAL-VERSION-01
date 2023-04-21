#*****************************************************************
#Módulo: VDLOGIN.PAN
#Funcionalidad : 
#Autor: ICC      
#Fecha: 17-03-2010
#*****************************************************************
#* Histórico de cambios
#* ====================
#
#*****************************************************************
#
#
#*****************************************************************
CONEXIONES A LA APLICACION
Operario Correcto?  Fecha y hora login    Máquina              Programa
_10_____ _1________ ¿D-MM-Y.YY  ________  _64________________  _64__________________    
                                                                                    |
TABLA=VDLOGIN
ORDERBY=FECLOGIN DESC,HORALOGIN DESC;

NOUPDATE
NODELETE
NOINSERT
PQUERY
POSX=1
POSY=1
REGPAG=40



CAMPO=CODOPE,TOOLTIP("C¢digo del usuario"), TITULO("Operario")
CAMPO=CORRECTO,TOOLTIP("Indica si el intento de login fu‚ correcto"), TITULO("¿Correcto?"),WLONX=24
CAMPO=FECLOGIN,TOOLTIP("Fecha del login"), TITULO("Fecha y hora de Login")
CAMPO=HORALOGIN,TOOLTIP("Hora del login")
CAMPO=MACHINE,TOOLTIP("Maquina en la que se realiz¢ el login"), TITULO("Máquina")
CAMPO=PROGRAM,TOOLTIP("Programa con el que realiz¢ el login"), TITULO("Programa"),WLONX=5


ONLINE= {F1} Ayuda    {F2} Consulta    {F4} Confirmar cambios    {Esc} Cerrar Pantalla    
        {May-F7} Documentación {May+F8} Imprimir  {F9} Borrar un registro    {F5} Borrar Pantalla    ;
