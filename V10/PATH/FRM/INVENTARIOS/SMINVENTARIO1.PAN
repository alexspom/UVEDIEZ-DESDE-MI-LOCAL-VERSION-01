###########################################
# MOdulo   : VDINVENCABRESUMEN.PAN
# Función  : Pantalla de cabecera de inventarios resumen
#
# Creación : 03-02-2010
# Autor    : ICC
###########################################
# HistOrico de cambios:
CABECERA DE INVENTARIOS
Inventario                         Tipo      Pr. Estado                         Creación                  Validacion        
###### _100_______________________ _20______ @L@ ##### __________________ _32_________ ¿D-MM-Y.YYY  _8______ ¿D-MM-Y.YY ________
|

TABLA=VDINVENCAB
ORDERBY=STATUS,CODINVEN DESC;

WLONX=990

PQUERY
POSX=1
POSY=1

NODELETE,PROTECT("V10")
NOINSERT
NOUPDATE,PROTECT("SUPERVISOR")

PREDELETE=FEJECUTA("CDELINVENCONTEO","")

CURSOR=CDELINVENCONTEO DELETE VDINVENCONTEO WHERE CODINVEN=:CODINVEN;


CAMPO=CODINVEN,NOUPDATE,TOOLTIP("Código de inventario obtenido del secuencia VDSECINVEN"),TITULO("Inventario")
CAMPO=DESINVEN,TOOLTIP("Descripción de inventario"),TITULO("Descripción"),WLONX=15
CAMPO=TIPOINVEN,TOOLTIP("Tipo de inventario"),TITULO("Tipo"),WLONX=10
CAMPO=PRIOINVEN,TOOLTIP("Prioridad"),TITULO("Pr.")
CAMPO=STATUS,NOUPDATE("IMPLANTADOR"),TITULO("Estado"),WLONX=15,TOOLTIP("Estado de las líneas del inventario. Posibles valores: 100 creado\n 200 en curso\n 300 Fin"),
             POSTCHANGE=FDESIGNACION("+CSELDESSTATUS","No existe status"),TITULO("Estado")
CAMPO=DESSTATUS, NOENTER,NOUPDATE,AUXILIAR,TITULO(""),WLONX=15
CAMPO=CODOPEINS,NOUPDATE,TOOLTIP("Código de operario se solicita el inventario"),TITULO("Creación")
CAMPO=FECINS,NOUPDATE,TOOLTIP("Fecha en juliano de cuando se solicitó el inventario"),TITULO("Creacion")
CAMPO=HORAINS,NOUPDATE,TOOLTIP("Hora en que se solicitó el inventario")
CAMPO=FECVAL,NOUPDATE,TITULO("Validacion")
CAMPO=HORAVAL,NOUPDATE
CAMPO=MSJERROR,AUXILIAR,NOUPDATE,OCULTO,"_200"

CURSOR=CSELVALIDABLE SELECT :CODINVEN 
                      FROM VDINVENCONTEO
                      WHERE CODINVEN=:CODINVEN AND STATUS BETWEEN 100 AND 150;

CURSOR=CSELDESSTATUS SELECT DESSTATUS 
                       FROM VDSTATUS
                      WHERE TIPOSTATUS = 'INC'
                        AND STATUS = :STATUS;
                        
CURSOR=CSELDATOS SELECT INC.STATUS,STA.DESSTATUS FROM VDINVENCAB INC,VDSTATUS STA WHERE CODINVEN=:CODINVEN AND INC.STATUS=STA.STATUS AND STA.TIPOSTATUS='INC';                        


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
                
                           

TECLA=SF2,FEJECUTA("@-!CSELVALIDABLE","INVENTARIO CON LINEAS PENDIENTES\n DESEA TERMINARLO?",
                   "CFININVENTARIO", "NO PUEDE FINALIZAR EL INVENTARIO PORQUE NO HA FINALIZADO O YA ESTA FINALIZADO",
                   FCOMMIT,"",
                   %FFAILURE,"INVENTARIO VALIDADO")
                   
TECLA=SF4,FEJECUTA("CLANZA","No se puede lanzar el inventario",
                   "CVERERROR","Error lanzando :MSJERROR",
                   FCOMMIT,"",
                   PRESEHIJO,"",
                   %FFAILURE,"INVENTARIO LANZADO",
				   FPULSATECLAS("F5","F2"),"")

#TECLA=SF4,FEJECUTA("CLANZA","No se puede lanzar el inventario",
#                   "CVERERROR","Error lanzando :MSJERROR",
#                   FCOMMIT,"",
#                   "CSELDATOS","",
#                   PRESEHIJO,"",
#                   %FFAILURE,"INVENTARIO LANZADO")
                   
TECLA=SF5,FEJECUTA("@-!CSELVALIDABLE","INVENTARIO CON LINEAS PENDIENTES\n DESEA ANULARLO?",
                   "CANULA","No se puede anular el inventario",
                   "CVERERROR","Error cerrando :MSJERROR",
                   FCOMMIT,"",
                   %FFAILURE,"INVENTARIO ANULADO",
                   FPULSATECLAS("F5","F2"),"")
                                           
                                           
BOTON=B1,1000,1,50,50,"P",restart.png,SF4,"Lanza inventario",INCLUDECSS="background-color: transparent;border-width:0px"
BOTON=B3,1000,51,50,50,"P",apply.png,SF2,"Valida inventario",INCLUDECSS="background-color: transparent;border-width:0px"
BOTON=B2,1000,101,50,50,"P",close.png,SF5,"Anula inventario",INCLUDECSS="background-color: transparent;border-width:0px"

ONLINE= {F1} Ayuda    {F2} Consulta    {May-F2} Validar inventario {May-F4} Lanza {May-F5} Cierra  {Esc} Cerrar Pantalla    {F5} Borrar Pantalla    ;
