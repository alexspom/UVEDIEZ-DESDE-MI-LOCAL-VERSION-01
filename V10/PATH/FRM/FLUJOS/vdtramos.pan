#Módulo: VDCAMINOS.PAN
#Función: Mantenimiento de tramos de los caminos
#
# Creación : 13-11-2007
# Autor    : ICC
###########################################
# Histórico de cambios:
 MANTENIMIENTO TRAMOS DE LOS CAMINOS 
                                                                      Forzar palet                                    
 Nº ORIGEN          DESTINO        Prioridad Bloqueado MuevePalet MueveParcial    completo  Ultima modificación                
 __ _20____________ _20____________   @@@@        _         _           _              _      _32_________ ¿D-MM-Y.YY ________         
|
TABLA=VDTRAMOS
ORDERBY=NTRAMO,PRIOTRAMO;

PREUPDATE=FEJECUTA("-CCHEQUEAVALORES1","SI FORZAR PALET COMPLETO ES U o E, MUEVAPARCIAL DEBE VALER S",
                   "-CCHEQUEAVALORES2","SI FORZAR PALET COMPLETO ES ' ' o C, MUEVAPALET DEBE VALER S",
                   "-CCHEQUEAVALORES3","SI FORZAR PALET COMPLETO ES A, MUEVEPALET Y MUEVEPARCIAL DEBEN VALER S",
                   "-CCHEQUEAVALORES4","EN LOS TRAMOS FINALES FORZAR PALET COMPLETO DEBE SER BLANCO",                   
                   "CSELMODIF","ERROR recuperando operario")
                   
PREINSERT=FEJECUTA("-CCHEQUEAVALORES1","SI FORZAR PALET COMPLETO ES U o E, MUEVAPARCIAL DEBE VALER S",
                   "-CCHEQUEAVALORES2","SI FORZAR PALET COMPLETO ES ' ' o C, MUEVAPALET DEBE VALER S",
                   "-CCHEQUEAVALORES3","SI FORZAR PALET COMPLETO ES A, MUEVEPALET Y MUEVEPARCIAL DEBEN VALER S",
                   "-CCHEQUEAVALORES4","EN LOS TRAMOS FINALES FORZAR PALET COMPLETO DEBE SER BLANCO",                   
                   "CSELMODIF","ERROR recuperando operario")

CAMPO=CODCAMINO,VIRTUAL,OCULTO
CAMPO=NTRAMO,WLONX=10,TOOLTIP("Número de tramo del camino"),TITULO("Nº")
CAMPO=CODAREAORI,TOOLTIP("Código de área origen"),COMBOX("CSELAREA"), POSTCHANGE=FEJECUTA("CVERIFAREAORI", "NO EXISTE EL AREA ORIGEN"),TITULO("Origen")
CAMPO=CODAREADEST,TOOLTIP("Código de área destino"), COMBOX("CSELAREA"),POSTCHANGE=FEJECUTA("CVERIFAREADEST", "NO EXISTE EL AREA DESTINO"),TITULO("Destino")
CAMPO=PRIOTRAMO,WLONX=60,TOOLTIP("Prioridad de ese tramo"),TITULO("Prioridad")
CAMPO=BLOQUEADO,WLONX=60,TOOLTIP("Indica si el tramo está bloqueado"),
                 POSTCHANGE=FVERIFICA("SN","ERROR, valores permitidos: S(i) o N(o)"),TITULO("Bloqueado")
CAMPO=MUEVEPALET,WLONX=70,TOOLTIP("Indica si el tramo permite que se muevan contenedores"),
                 POSTCHANGE=FVERIFICA("SN","ERROR, valores permitidos: S(i) o N(o)"),TITULO("MuevePalet")
CAMPO=MUEVEPARCIAL,WLONX=80,TOOLTIP("Indica si el tramo permite que se muevan unidades y/o embalajes"),
                  POSTCHANGE=FVERIFICA("SN","ERROR, valores permitidos: S(i) o N(o)"),TITULO("MueveParcial")
CAMPO=FUERZAPALET,WLONX=50,TOOLTIP(" C o blanco-Fuerza a que se mueva palet,\n E-Fuerza a que se muevan embalajes,\n U-Fuerza que se muevan unidades,\n A-Fuerza a que se mueva en primer lugar palet, si no se puede, entonces embalajes"),
                  POSTCHANGE=FVERIFICA(" CEUA","ERROR, valores permitidos: Blanco, C, E, U, A"),TITULO("Palet Comp"),WLONX=70
CAMPO=CODOPEMODIF, NOENTER, TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF, NOENTER, TOOLTIP("Es la fecha  en que se efectuó alguna modificación a los datos del registro.")
CAMPO=HORAMODIF, NOENTER, TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro.")

CURSOR=CSELMODIF SELECT VD.HORASYS HORAMODIF, VD.FECHASYS FECMODIF, VDUSER.GETUSER CODOPEMODIF FROM DUAL;

CURSOR=CVERIFAREAORI SELECT CODAREA CODAREAORI FROM VDAREA  WHERE CODAREA=:CODAREAORI;

CURSOR=CVERIFAREADEST SELECT CODAREA CODAREADEST FROM VDAREA  WHERE CODAREA=:CODAREADEST;

CURSOR=CSELAREA SELECT CODAREA CODAREAORI, CODAREA CODAREADEST FROM VDAREA ORDER BY CODAREA;

CURSOR=CCHEQUEAVALORES1 SELECT :FUERZAPALET FROM DUAL WHERE NVL(:FUERZAPALET,'C') IN ('U','E') AND NVL(:MUEVEPARCIAL,'N')='N';

CURSOR=CCHEQUEAVALORES2 SELECT :FUERZAPALET FROM DUAL WHERE NVL(:FUERZAPALET,'C')='C' AND NVL(:MUEVEPALET,'N')='N' 
                        AND EXISTS (SELECT 1 FROM VDTRAMOS WHERE CODCAMINO=:CODCAMINO AND NTRAMO>:NTRAMO);

CURSOR=CCHEQUEAVALORES3 SELECT :FUERZAPALET FROM DUAL WHERE NVL(:FUERZAPALET,'C')='A' AND (NVL(:MUEVEPARCIAL,'N')='N');

CURSOR=CCHEQUEAVALORES4 SELECT :FUERZAPALET FROM DUAL WHERE :FUERZAPALET IS NOT NULL AND
                                     NOT EXISTS (SELECT 1 FROM VDTRAMOS WHERE CODCAMINO=:CODCAMINO AND NTRAMO>:NTRAMO);


