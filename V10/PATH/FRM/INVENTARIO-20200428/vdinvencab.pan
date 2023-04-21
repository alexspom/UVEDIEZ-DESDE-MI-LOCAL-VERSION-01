###########################################
# Módulo   : VDINVENCAB.PAN
# Función  : Pantalla de solicitud de inventarios
#
# Creación : 21-01-2010
# Autor    : ICC
###########################################
# Histórico de cambios:
MANTENIMIENTO DE INVENTARIO

Inventario:  ########  Clave HOST: _40______________________________________    Estado: ##### ________________
Descripción: _100_____________________________________________________________________________________________

 Rango cod. división      : _1024_____________________________________________________________________________
 Rango cod. áreas         : _1024_____________________________________________________________________________
 Rango cod. ubicaciones   : _1024_____________________________________________________________________________
 Rango cod. matrículas    : _1024_____________________________________________________________________________
 Rango cod. clasificación de artículos: _1024___________________  Clase de artículos: _15_____________
 Rango cod. de artículos  : _1024_____________________________________________________________________________ 
 Rango cod. lotes         : _1024_____________________________________________________________________________
 Ubicación sin movimientos: _ (S/N/Blanco)
 Ubicaciones marcadas     : _ (S/N/Blanco)
 Fecha desde inventario de ubicación: ¿D-MM-Y.YYY         
 
 Solicitado por    : _32_____________ el ¿D-MM-Y.YYY a las _8______             Nº ubicaciones : #####
 Validado por      : _32_____________ el ¿D-MM-Y.YYY a las _8______
 Ult. modificación : _32_____________ el ¿D-MM-Y.YYY a las _8______
 Fc. Interfasado   : ¿D-MM-Y.YYY a las _8______          

                                                                                                                     |
TABLA=VDINVENCAB
ORDERBY= CODINVEN DESC;
PQUERY
POSX=1
POSY=1

PREQUERY=FEJECUTA(FPOSICIONACAMPO(FSUCCESS,"DESINVEN"),"")

PREINSERT=FEJECUTA("CSELCODINVEN", "ERROR SELECCIONANDO Código DE INVENTARIO",
                   "CSELINSERT", "ERROR AL OBTENER LA FECHA DE INSERCION",
                   "CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
                   
POSTINSERT=FEJECUTA("CGENINVEN","ERROR :V10ERROR",
                   "CCONTINVENLIN", ":MSG",
                   %FFAILURE,  ":MSG",
                   FCOMMIT,"",
                   FPULSATECLAS("F3","F2"),"")

PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION",
                   "CDELINVENLIN", "ERROR AL BORRAR UN INVENTARIO",
                   "-CCONTINVENLIN2", "ERROR AL BORRAR UN INVENTARIO YA LANZADO")
                   
POSTUPDATE=FEJECUTA("CGENINVEN","ERROR :V10ERROR",
                   "CCONTINVENLIN", ":MSG",
                   %FFAILURE,  ":MSG",
                   FCOMMIT,"")


CAMPO=CODINVEN,NOENTER,TOOLTIP("Código de inventario obtenido del secuencia VDSECINVEN"),TITULO("Inventario")
CAMPO=DATOSHOST,NOENTER,TOOLTIP("Código enviado por el host al que este hace referencia")
CAMPO=STATUS,NOENTER,TOOLTIP("Estado de las líneas del inventario. Posibles valores: 100 creado\n 200 en curso\n 300 Fin"),
             POSTCHANGE=FDESIGNACION("+CSELDESSTATUS","No existe status",
                                     "+CSELNUBIAINVEN","")
CAMPO=DESSTATUS, NOENTER,AUXILIAR
CAMPO=DESINVEN,TOOLTIP("Descripción de inventario")
CAMPO=CODDIVR,TOOLTIP("Rango de Códigos de división a inventariar"),COMBOXMULTIPLE("CSELDIVIS")
CAMPO=CODAREAR,TOOLTIP("Rango de áreas a inventariar"),COMBOXMULTIPLE("CSELAREAS")
CAMPO=CODUBIR,TOOLTIP("Código de ubicación a inventariar")
CAMPO=CODMATR,TOOLTIP("Código de matrícula a inventariar, si nulo, se inventarían todas las de la ubicación")
CAMPO=CODCLASIFR,TOOLTIP("Rango de Códigos de clasificación de artículo a inventariar"),COMBOXMULTIPLE("CSELCLASIF")
CAMPO=CODCLASE,TOOLTIP("Clase de artículos a inventariar")
CAMPO=CODARTR, TOOLTIP("Rango de Códigos de artículos a inventariar")
CAMPO=CODLOTR,TOOLTIP("Rango de Códigos de lotes a inventariar")
CAMPO=SWTUBISINMOV,TOOLTIP("Indicador de si debe seleccionarse las ubicaciones que no hayan tenido movimientos desde su último inventario")
CAMPO=SWTUBIMARCADAS,TOOLTIP("Indicador de si debe seleccionarse las ubicaciones que han sido marcadas para inventariar")
CAMPO=FECDESDEUBIINV,TOOLTIP("Fecha desde que se realizó el último inventario de las ubicaciones"),COMBOX("CALENDARIO")
CAMPO=CODOPEINS,NOUPDATE,TOOLTIP("Código de operario se solicita el inventario"),NOENTER
CAMPO=FECINS,NOUPDATE,TOOLTIP("Fecha en juliano de cuando se solicitó el inventario"),NOENTER
CAMPO=HORAINS,NOUPDATE,TOOLTIP("Hora en que se solicitó el inventario"),NOENTER
CAMPO=NUBIAINVEN,NOENTER,AUXILIAR,NOENTER
CAMPO=CODOPEVAL,NOUPDATE,TOOLTIP("Código de operario que valida el inventario finalizado"),NOENTER
CAMPO=FECVAL,NOUPDATE,TOOLTIP("Fecha en juliano de cuando se validó el inventario finalizado"),NOENTER
CAMPO=HORAVAL,NOUPDATE,TOOLTIP("Hora en que se validó el inventario finalizado"),NOENTER
CAMPO=CODOPEMODIF,NOUPDATE,TOOLTIP("Operario que realizó la última modificación"),NOENTER
CAMPO=FECMODIF,NOUPDATE,TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro"),NOENTER
CAMPO=HORAMODIF,NOUPDATE,TOOLTIP("Hora  en que se efectuó alguna modificación a los datos del registro"),NOENTER
CAMPO=FECINTERF,NOUPDATE,TOOLTIP("Fecha en juliano en que se interfasó el inventario"),NOENTER
CAMPO=HORAINTERF,NOUPDATE,TOOLTIP("Hora en que se interfasó el inventario"),NOENTER
CAMPO=MSG,OCULTO,"_100_",AUXILIAR


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELINSERT SELECT VDST.FINCCREADO STATUS, VDUSER.GETUSER CODOPEINS, VD.FECHASYS FECINS, VD.HORASYS HORAINS FROM DUAL;

CURSOR=CSELCODINVEN SELECT VDSECINVEN.NEXTVAL CODINVEN FROM DUAL;

CURSOR=CSELDESSTATUS SELECT DESSTATUS 
                       FROM VDSTATUS
                      WHERE TIPOSTATUS = 'INC'
                        AND STATUS = :STATUS;

CURSOR=CDELINVENLIN DELETE VDINVENLIN
                     WHERE CODINVEN = :CODINVEN
                       AND STATUS = VDST.FINLCREADO;
                       
CURSOR=CCONTINVENLIN SELECT COUNT(DISTINCT CODUBI)||' UBICACIONES A INVENTARIAR' MSG
                       FROM VDINVENLIN
                      WHERE CODINVEN = :CODINVEN;
                        
CURSOR=CCONTINVENLIN2 SELECT CODINVEN
                       FROM VDINVENLIN
                      WHERE CODINVEN = :CODINVEN;


CURSOR=CGENINVEN BEGIN VDINVEN.GENINVENTARIO(:CODINVEN); END;@


CURSOR=CSELNUBIAINVEN SELECT COUNT(DISTINCT CODUBI) NUBIAINVEN
                        FROM VDINVENLIN
                       WHERE CODINVEN = :CODINVEN;

CURSOR=CSELDIVIS SELECT CODDIV,DESDIV  FROM VDDIVIS;

CURSOR=CSELAREAS SELECT CODAREA,DESAREA  FROM VDAREA;

CURSOR=CSELCLASIF SELECT CODCLASIF,DESCLASIF FROM VDCLASIFICACIONES WHERE TABLACLASIF='VDARTIC';

ONLINE= {F1} Ayuda    {F2} Consulta    {F4} Crear Inventario    {Esc} Cerrar Pantalla    
        {F9} Borrar un registro    {F5} Borrar Pantalla    ;
