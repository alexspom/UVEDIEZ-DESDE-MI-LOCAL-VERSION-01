###########################################
# Módulo   : VDMONINVENCAB.PAN
# Función  : Monitor de inventarios
#
# Creación : 04-02-2010
# Autor    : ICC
###########################################
# Histórico de cambios:
CABECERA DE INVENTARIOS
Inventario                                    Clave HOST                  Estado                 Creación
########  _100_______________________________ _40________________________ ##### ________________ _32_______ ¿D-MM-Y.YYY  _8______
                                                                                                                                 |
TABLA=VDINVENCAB
ORDERBY=STATUS,CODINVEN DESC;

PQUERY
POSX=1
POSY=1

NODELETE
NOINSERT
NOUPDATE

CAMPO=CODINVEN,NOUPDATE,TOOLTIP("Código de inventario obtenido del secuencia VDSECINVEN"),TITULO("Inventario")
CAMPO=DESINVEN,TOOLTIP("Descripción de inventario")
CAMPO=DATOSHOST,NOENTER,TOOLTIP("Código enviado por el host al que este hace referencia"),TITULO("Clave Host")
CAMPO=STATUS,NOENTER,TOOLTIP("Estado de las líneas del inventario. Posibles valores: 100 creado\n 200 en curso\n 300 Fin\n 400 Inventario sin líneas"),
             POSTCHANGE=FDESIGNACION("+CSELDESSTATUS","No existe status"), TITULO("Estado")
CAMPO=DESSTATUS, NOENTER,AUXILIAR
CAMPO=CODOPEINS,NOUPDATE,TOOLTIP("Código de operario se solicita el inventario"),TITULO("Creación")
CAMPO=FECINS,NOUPDATE,TOOLTIP("Fecha en juliano de cuando se solicitó el inventario")
CAMPO=HORAINS,NOUPDATE,TOOLTIP("Hora en que se solicitó el inventario")


CURSOR=CSELDESSTATUS SELECT DESSTATUS 
                       FROM VDSTATUS
                      WHERE TIPOSTATUS = 'INC'
                        AND STATUS = :STATUS;


TECLA=SF8,FEJECUTA(FIMPRIME("INFORME","VDINVENTARIO.RPT","CODINVEN=:CODINVEN",""),":V10ERROR")

ONLINE= {F1} Ayuda    {F2} Consulta    {May-F8} Imprimir    {Esc} Cerrar Pantalla    {F5} Borrar Pantalla    ;
