###########################################
# Módulo   : VDINVENCABRESUMEN.PAN
# Función  : Pantalla de cabecera de inventarios resumen
#
# Creación : 03-02-2010
# Autor    : ICC
###########################################
# Histórico de cambios:
CABECERA DE INVENTARIOS

Inventario                         Clave Host Estado             Creación                            Interfasado
###### _100_______________________ _40_______ ##### ____________  _32_________ ¿D-MM-Y.YYY  _8______ ¿D-MM-Y.YYY a las _8______
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
CAMPO=DATOSHOST,NOENTER,TOOLTIP("Código enviado por el host al que este hace referencia"),TITULO("Clave Host"),WLONX=25
CAMPO=STATUS,NOENTER,TOOLTIP("Estado de las líneas del inventario. Posibles valores: 100 creado\n 200 en curso\n 300 Fin"),
             POSTCHANGE=FDESIGNACION("+CSELDESSTATUS","No existe status"),TITULO("Estado")
CAMPO=DESSTATUS, NOENTER,AUXILIAR
CAMPO=CODOPEINS,NOUPDATE,TOOLTIP("Código de operario se solicita el inventario"),TITULO("Creación")
CAMPO=FECINS,NOUPDATE,TOOLTIP("Fecha en juliano de cuando se solicitó el inventario")
CAMPO=HORAINS,NOUPDATE,TOOLTIP("Hora en que se solicitó el inventario")
CAMPO=FECINTERF,NOUPDATE,TOOLTIP("Fecha en juliano en que se interfasó el inventario"),TITULO("Interfasado")
CAMPO=HORAINTERF,NOUPDATE,TOOLTIP("Hora en que se interfasó el inventario")

CURSOR=CSELDESSTATUS SELECT DESSTATUS 
                       FROM VDSTATUS
                      WHERE TIPOSTATUS = 'INC'
                        AND STATUS = :STATUS;


CURSOR=CFININVENTARIO SELECT :CODINVEN
                        FROM VDINVENCAB
                       WHERE CODINVEN = :CODINVEN
                         AND STATUS = VDST.FINCENCURSO
                         AND CODINVEN NOT IN (SELECT CODINVEN
                                                FROM VDINVENLIN
                                               WHERE CODINVEN = :CODINVEN
                                                 AND STATUS  != VDST.FINLFINALIZADO);

CURSOR=CUPDINVENCAB UPDATE VDINVENCAB
                       SET STATUS      = VDST.FINCFINALIZADO,
                           CODOPEVAL   = VDUSER.GETUSER,
                           FECVAL      = VD.FECHASYS,
                           HORAVAL     = VD.HORASYS,
                           CODOPEMODIF = VDUSER.GETUSER,
                           FECMODIF    = VD.FECHASYS,
                           HORAMODIF   = VD.HORASYS
                     WHERE CODINVEN = :CODINVEN;                   
                           

TECLA=SF2,FEJECUTA("CFININVENTARIO", "NO PUEDE FINALIZAR EL INVENTARIO PORQUE NO HA FINALIZADO O YA ESTA FINALIZADO",
                   "CUPDINVENCAB", "ERROR FINALIZANDO INVENTARIO",
                   FCOMMIT,"",
                   %FFAILURE,"INVENTARIO VALIDADO")

ONLINE= {F1} Ayuda    {F2} Consulta    {May-F2} Validar inventario   {Esc} Cerrar Pantalla    {F5} Borrar Pantalla    ;
