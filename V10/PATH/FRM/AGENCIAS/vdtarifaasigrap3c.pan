# Módulo   : VDTARIFADIV.PAN
# Función  : Asignación de tarifas a divisiones
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
# (1) 15-04-2008: Adaptar pantallas a las especificaciones de Movianto. Sergio Rojo
ASIGNACION DE TARIFAS
Añadir División                        ClaseTarifa  Validez
   _   _20_______ _40_________________    _         ¿D-MM-Y.YY ¿D-MM-Y.YY 
                                                                         |

SOLOQUERY
#AQUERY

SELECT=SELECT CODDIV, DESDIV,'C' CLASETARIFA 
         FROM VDDIVIS
        WHERE CODDIV NOT IN (SELECT CODDIV FROM VDTARIFADIV WHERE SEQTARIFA=:SEQTARIFA AND CODAGE=:CODAGE);

ORDERBY= CODDIV ASC;

POSTQUERY=FEJECUTA("CINICIALIZA","No puedo seleccionar datos",
                   FPOSICIONACAMPO(FSUCCESS,"SWTPEDMUL"),"")


PREUPDATE=FEJECUTA("@CSELSWTPEDMUL","\n Error en cursor CSELSWTPEDMUL \n\n",
                   "CSELCODTARIFA","Error en cursor CSELCODTARIFA.",
                   "-CSELREGVENTA","ERROR, \n\nExisten divisiones de Venta para la tarifa :SEQTARIFA. ",
                   "CASIGNATARIFADIV","\n Error al asignar la division a la tarifa \n\n",
                   FPULSATECLAS("F3","F2"),""
                   )
                   
                   

CAMPO=SWTPEDMUL,AUXILIAR,UPPER,POSTCHANGE=FVERIFICA("SN","Debe introducir S o N"),TITULO("Añadir")
CAMPO=SEQTARIFA,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODAGE,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODDIV,TOOLTIP("Código de la división"),TITULO("División")
CAMPO=DESDIV,NOENTER,TOOLTIP("Designación de la división")
CAMPO=CLASETARIFA,NOENTER,AUXILIAR,UPPER,POSTCHANGE=FVERIFICA("CV","Debe introducir C(oste) o V(enta)"),TOOLTIP("Clase de la tarifa debe ser C(oste) o V(enta)"),
                  TITULO("Clase Tarifa")
CAMPO=FECDESDE,AUXILIAR,TOOLTIP("Fecha inicio de validez de la tarifa"),TITULO("Validez"),COMBOX("CALENDARIO")
CAMPO=FECHASTA,AUXILIAR,TOOLTIP("Fecha de final de validez de la tarifa"),COMBOX("CALENDARIO")

CAMPO=CODTARIFA,OCULTO,"_20___"

CURSOR=CSELCODTARIFA SELECT :CODTARIFA FROM VDTARIFA WHERE SEQTARIFA=:SEQTARIFA;

CURSOR=CSELREGVENTA SELECT SEQTARIFA FROM VDTARIFADIV WHERE SEQTARIFA=:SEQTARIFA AND CLASETARIFA='V' GROUP BY SEQTARIFA;

CURSOR=CINICIALIZA SELECT 'N' SWTPEDMUL FROM DUAL;

CURSOR=CSELSWTPEDMUL SELECT :SWTPEDMUL SWTPEDMUL FROM DUAL WHERE :SWTPEDMUL='S';


CURSOR=CASIGNATARIFADIV  Insert into VDTARIFADIV (SEQTARIFA,CODAGE, CODDIV, FECDESDE, FECHASTA, 
                                                  CODTARIFA, CODOPEMODIF, FECMODIF, HORAMODIF, CLASETARIFA)
                                          Values (:SEQTARIFA,:CODAGE, :CODDIV, :FECDESDE,:FECHASTA, 
                                                  :CODTARIFA,VDUSER.GETUSER,VD.FECHASYS, VD.HORASYS, :CLASETARIFA);
                         
AYUDA=ASIGNACION RAPIDA DE AGENCIAS A TARIFAS



ONLINE={F1} Ayuda  {F4} Confirmar Cambios  {F6} Cambio de pantalla
                {F9} Borrar Registro {May-F10} Menú contextual;
