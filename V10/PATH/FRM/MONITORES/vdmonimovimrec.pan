# Módulo   : VDMONIMOVIMREC.PAN
# Función  : Monitor de movimientos. Resumen de los recursos
#
# Creación : 04-08-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
RESUMEN DE RECURSOS
 Recurso                         A C Asig. Ubi. Origen  Ubi. Dest    Ult. Ubi
 _10_______ _40_________________ _ _ @L@@@ _12_________ _20_________ _20_________
|

SOLOQUERY
TABLA=REC

SELECT=SELECT DISTINCT REC.CODRECURSO, REC.DESRECURSO, REC.ACTIVO, REC.CONECTADO, REC.ULTCODUBI
         FROM VDRECURSO REC, VDRECTAREA TAR
        WHERE REC.CODRECURSO = TAR.CODRECURSO 
          AND VD.CONTIENECAD(:RANPERFIL,TAR.CODPERFIL) = 1
          AND TAR.ACTIVA = 'S';

ORDERBY=REC.CODRECURSO;


#CAMPO=RANPERFIL,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODRECURSO,NOENTER,TOOLTIP("Código del recurso"),POSTCHANGE=FDESIGNACION("+CSELMOVSASIG","","+CDATOSMOV",""),TITULO("Recurso")
CAMPO=DESRECURSO,NOENTER,TOOLTIP("Descripcion del recurso")
CAMPO=ACTIVO,NOENTER,TOOLTIP("Indica si el recurso esta activo o no"),TITULO("A")
CAMPO=CONECTADO,NOENTER,TOOLTIP("Indica si el recurso esta conectado al sistema"),TITULO("C")
CAMPO=MOVSASIG,AUXILIAR,NOENTER,TOOLTIP("Indica si el recurso esta conectado al sistema"),TITULO("Asig.")
CAMPO=CODUBIORI,AUXILIAR,NOENTER,TOOLTIP("Ubicacion origen del movimiento que tiene asignado el recurso"),TITULO("Ubi. Origen")
CAMPO=CODUBIDEST,AUXILIAR,NOENTER,TOOLTIP("Ubicacion destino del movimiento que tiene asignado el recurso"),TITULO("Ubi. Destino")
CAMPO=ULTCODUBI,NOENTER,TOOLTIP("Ultima ubicacion visitada por el recurso"),TITULO("Ult. Ubi.")


CURSOR=CSELDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS = :STATUS AND TIPOSTATUS = 'MOV';

CURSOR=CSELMOVSASIG SELECT COUNT(*) MOVSASIG FROM VDMOVIM WHERE CODRECURSO = :CODRECURSO AND STATUS <= VDST.FMOVDEPOSITADO; 

CURSOR=CDATOSMOV SELECT CODUBIORI,CODUBIDEST FROM VDMOVIM WHERE CODRECURSO = :CODRECURSO AND STATUS <= VDST.FMOVDEPOSITADO
                  ORDER BY STATUS DESC;


