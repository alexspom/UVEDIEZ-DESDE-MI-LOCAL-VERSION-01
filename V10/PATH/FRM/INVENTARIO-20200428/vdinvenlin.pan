#*****************************************************************
#Módulo: VDINVENLIN.PAN
#Funcionalidad : 
#Autor: ICC      
#Fecha: 03-02-2010
#*****************************************************************
#* Histórico de cambios
#* ====================
LINEAS DEL INVENTARIO
Ubicación    Matrícula          Estado                    Ultima modificación            
_20_________ _18_______________ ###### _40_______________ _32_______ ¿D-MM-Y.YYY _8______
                                                                                           |

TABLA=VDINVENLIN
ORDERBY=CODUBI,CODMAT;

AQUERY
NOINSERT
NODELETE
NOUPDATE

POSX=1
POSY=1
REGPAG=25

CAMPO=CODINVEN,TOOLTIP("Código de inventario"),OCULTO,VIRTUAL
CAMPO=CODUBI,TOOLTIP("Código de ubicación a inventariar"),TITULO("Ubicación")
CAMPO=CODMAT,TOOLTIP("Código de matrícula a inventariar"),TITULO("Matrícula")
CAMPO=STATUS,NOENTER,TOOLTIP("Estado de las líneas del inventario. Posibles valores: 100 creado\n 200 en curso\n 300 Fin"),
             POSTCHANGE=FDESIGNACION("+CSELDESSTATUS","No existe status"),TITULO("Estado")
CAMPO=DESSTATUS, NOENTER,AUXILIAR
CAMPO=CODOPEMODIF,NOUPDATE,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOUPDATE,TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOUPDATE,TOOLTIP("Hora  en que se efectuó alguna modificación a los datos del registro")
CAMPO=CODMATINVL,OCULTO,AUXILIAR,"_18____________"


CURSOR=CSELDESSTATUS SELECT DESSTATUS, :CODMAT CODMATINVL
                       FROM VDSTATUS
                      WHERE TIPOSTATUS = 'INL'
                        AND STATUS = :STATUS;



ONLINE= {F1} Ayuda    {F2} Consulta    {F4} Confirmar cambios    {Esc} Cerrar Pantalla    
        {May-F7} Documentación {May+F8} Imprimir  {F9} Borrar un registro    {F5} Borrar Pantalla    ;
