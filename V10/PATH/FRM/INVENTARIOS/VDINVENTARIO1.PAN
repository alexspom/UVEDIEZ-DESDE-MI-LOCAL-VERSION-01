###########################################
# MOdulo   : VDINVENCABRESUMEN.PAN
# Función  : Pantalla de cabecera de inventarios resumen
#
# Creación : 03-02-2010
# Autor    : ICC
###########################################
# HistOrico de cambios:
CABECERA DE INVENTARIOS

Inventario                         Tipo           Pr. Estado                      Creación                  Validacion        
###### _100_______________________ _20___________ @L@ ##### _____________________ _32_________ ¿D-MM-Y.YYY  _8______ ¿D-MM-Y.YY ________
|
TABLA=VDINVENCAB
ORDERBY=STATUS,CODINVEN DESC;

PQUERY
POSX=1
POSY=1

NODELETE,PROTECT("V10")
NOINSERT
NOUPDATE,PROTECT("SUPERVISOR")

PREDELETE=FEJECUTA("CDELINVENCONTEO","")

CURSOR=CDELINVENCONTEO DELETE VDINVENCONTEO WHERE CODINVEN=:CODINVEN;


CAMPO=CODINVEN,NOUPDATE,TOOLTIP("Código de inventario obtenido del secuencia VDSECINVEN"),TITULO("Inventario")
CAMPO=DESINVEN,TOOLTIP("Descripción de inventario"),TITULO("Descripción")
CAMPO=TIPOINVEN,TOOLTIP("Tipo de inventario"),TITULO("Tipo")
CAMPO=PRIOINVEN,TOOLTIP("Prioridad"),TITULO("Pr.")
CAMPO=STATUS,NOUPDATE("SUPERVISOR"),TOOLTIP("Estado de las líneas del inventario. Posibles valores: 100 creado\n 200 en curso\n 300 Fin"),
             POSTCHANGE=FDESIGNACION("+CSELDESSTATUS","No existe status"),TITULO("Estado")
CAMPO=DESSTATUS, NOENTER,AUXILIAR
CAMPO=CODOPEINS,NOUPDATE,TOOLTIP("Código de operario se solicita el inventario"),TITULO("Creación")
CAMPO=FECINS,NOUPDATE,TOOLTIP("Fecha en juliano de cuando se solicitó el inventario"),TITULO("Creacion")
CAMPO=HORAINS,NOUPDATE,TOOLTIP("Hora en que se solicitó el inventario")
CAMPO=FECVAL,NOUPDATE,TITULO("Validacion")
CAMPO=HORAVAL,NOUPDATE
CAMPO=MSJERROR,AUXILIAR,NOUPDATE,OCULTO,"_200"

CURSOR=CSELDESSTATUS SELECT DESSTATUS 
                       FROM VDSTATUS
                      WHERE TIPOSTATUS = 'INC'
                        AND STATUS = :STATUS;


CURSOR=CFININVENTARIO BEGIN
                        SMINVEN.CIERRAINVENDIARIO(:TIPOINVEN,:CODINVEN);
                      END;@
                      
CURSOR=CLANZA BEGIN
                        SMINVEN.LANZAINVENTARIO(:CODINVEN,:MSJERROR);
                      END;@
                      
CURSOR=CANULA BEGIN
                  SMINVEN.ANULAINVENTARIO(:CODINVEN,:MSJERROR);
               END;@      

CURSOR=CVERERROR SELECT :MSJERROR FROM DUAL WHERE :MSJERROR IS NULL;               
                
                           

TECLA=SF2,FEJECUTA("CFININVENTARIO", "NO PUEDE FINALIZAR EL INVENTARIO PORQUE NO HA FINALIZADO O YA ESTA FINALIZADO",
                   FCOMMIT,"",
                   %FFAILURE,"INVENTARIO VALIDADO")
                   
TECLA=SF4,FEJECUTA("CLANZA","No se puede lanzar el inventario",
                   "CVERERROR","Error lanzando :MSJERROR",
                   FCOMMIT,"",
                   FRELOADREG,"",
                   %FFAILURE,"INVENTARIO LANZADO")
TECLA=SF5,FEJECUTA("CANULA","No se puede anular el inventario",
                   "CVERERROR","Error cerrando :MSJERROR",
                   FCOMMIT,"",
                   %FFAILURE,"INVENTARIO ANULADO",
                   FPULSATECLAS("F5","F2"),"")
                                           
                                           
BOTON=B1,920,40,50,50,"P",restart.png,SF4,"Lanzar",INCLUDECSS="background-color: transparent;border-width:0px"
BOTON=B2,920,130,50,50,"P",close.png,SF5,"Cerrar",INCLUDECSS="background-color: transparent;border-width:0px"

ONLINE= {F1} Ayuda    {F2} Consulta    {May-F2} Validar inventario {May-F4} Lanza {May-F5} Cierra  {Esc} Cerrar Pantalla    {F5} Borrar Pantalla    ;
