#*****************************************************************
#Módulo: VDRECMATMANUAL.PAN
#Función: 
#Autor: ICC      
#Fecha: 25-02-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
DESCRIPCION DE LAS MATRICULAS DONDE SE VA A RECEPCIONAR

Matrícula          Tipo contenedor                 Altura   
_18_______________ _10_______ _40_________________ ######
|
TABLA=VDCONTE
WHERE=CODMAT IN (SELECT CODMAT
                   FROM VDSTOCK
                  WHERE CODRECEP = :CODRECEP);
                  
#SELECT=SELECT CODMAT, TIPOCONTE, CNTSSCC, CODUBI, ALTURACONTE, STATUS, FECENTRADA, HORAENTRADA, CODCOMEN,
#              CODOPEMODIF, FECMODIF, HORAMODIF, VDEXTRA
#         FROM (SELECT DISTINCT CNT.CODMAT, CNT.TIPOCONTE, CNT.CNTSSCC, CNT.CODUBI, CNT.ALTURACONTE, CNT.STATUS,
#                        CNT.FECENTRADA, CNT.HORAENTRADA, CNT.CODCOMEN, CNT.CODOPEMODIF, CNT.FECMODIF, CNT.HORAMODIF,
#                        CNT.VDEXTRA
#               FROM VDCONTE CNT, VDSTOCK STK
#              WHERE STK.CODRECEP  = :CODRECEP
#                AND STK.CODMAT    = CNT.CODMAT)
#        WHERE 1=1;

ORDERBY=CODMAT;


PREINSERT=FEJECUTA(FIF("CVALCODMAT",FEJECUTA("CVERSIERROR", "ERROR MATRICULA EN USO",
                                             "CVALTIPO", "ERROR TIPO DE RECEPCION NO PERMITE RECEPCION MULTIARTICULO")),"",
                   "INSCONTE", "ERROR INSERTANDO CONTENEDOR :CODMAT",
                   FCOMMIT,"")
                   
PREUPDATE=FEJECUTA("CSELMODIF","ERROR SELECCIONANDO FECHA Y USUARIO DE MODIFICACION")

CAMPO=CODRECEP,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODORDREC,VIRTUAL,AUXILIAR,OCULTO
CAMPO=TIPORDREC,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODDIV,VIRTUAL,AUXILIAR,OCULTO
CAMPO=PULMON,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODMAT,TOOLTIP("Matrícula del contenedor")
CAMPO=TIPOCONTE,POSTCHANGE=FDESIGNACION("CSELVDTIPOCONTEDESTIPOCONTE","ERROR AL EJECUTAR CURSOR CSELVDTIPOCONTEDESTIPOCONTE"),TOOLTIP("Tipo del contenedor")
CAMPO=DESTIPOCONTE,NOENTER,AUXILIAR,TOOLTIP("Descripción del tipo de contenedor")
CAMPO=CNTSSCC,OCULTO,"_20_",TOOLTIP("Código seriado de envío para bultos paletizados")
CAMPO=CODUBI,TOOLTIP("Ubicación del contenedor"),OCULTO,"_20_"
#CAMPO=POSCONTE,TOOLTIP("Posición del contenedor dentro de la ubicación")
CAMPO=ALTURACONTE,TOOLTIP("Altura real de contenedor")
CAMPO=STATUS,TOOLTIP("Indica si el contenedor está en situación de ser reubicado (0) o (distinto de 0) se ha detectado algún error de compatibilidad o flujo"),
      OCULTO,"#######"
#CAMPO=FECENTRADA,TOOLTIP("Fecha en la que se realiza la entrada, útil para FIFO")
#CAMPO=HORAENTRADA,TOOLTIP("Hora en la que se realiza la entrada, útil para FIFO")
CAMPO=VDEXTRA,OCULTO,"_255_",TOOLTIP("Datos adicionales útiles para el cliente")
CAMPO=CODCOMEN,OCULTO,"#########",TOOLTIP("")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),OCULTO,"_32_____"
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuó alguna modificación a los datos del registro"),OCULTO,"#######"
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro"),OCULTO,"_8_____"
CAMPO=DUMMY,AUXILIAR,OCULTO,"#"

CURSOR=CSELVDTIPOCONTEDESTIPOCONTE SELECT DESTIPOCONTE FROM VDTIPOCONTE WHERE TIPOCONTE=:TIPOCONTE;

CURSOR=CVALCODMAT SELECT DECODE(CODRECEP, :CODRECEP, 0, 1) DUMMY
                    FROM VDSTOCK
                   WHERE CODMAT = :CODMAT;

CURSOR=CVERSIERROR SELECT 1 DUMMY 
                     FROM DUAL
                    WHERE :DUMMY != 0;

CURSOR=CVALTIPO SELECT 1 DUMMY
                  FROM VDTIPORDRECLIN LTO, VDCLASEARTIC CLA
                 WHERE LTO.TIPORDREC     = :TIPORDREC
                   AND LTO.MULTIARTICULO = 'S';

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=INSCONTE INSERT INTO VDCONTE
                           (CODMAT  , TIPOCONTE  , CNTSSCC    , CODUBI     , POSCONTE   , ALTURACONTE, 
                            STATUS  , FECENTRADA , HORAENTRADA, VDEXTRA    , CODCOMEN   , CODOPEMODIF, 
                            FECMODIF, HORAMODIF)
                           (SELECT :CODMAT , :TIPOCONTE  , NULL  , :PULMON , COUNT(*)+1, :ALTURACONTE, 0, VD.FECHASYS, VD.HORASYS, 
                                   NULL, 0,  VDUSER.GETUSER,  VD.FECHASYS, VD.HORASYS
                              FROM VDCONTE
                             WHERE CODUBI = :PULMON);


TECLA=SF2,FEJECUTA("CCREAMOVANUL","ERROR CREANDO MOVIMIENTO Y ACTUALIZANDO LINEAS DE RECEPCION\n ASOCIADAS A LA MATRICULA :CODMAT",
                   FCOMMIT,"",
                   FFAILURE," ANULADA MATRICULA :CODMAT DE LA RECEPCION :CODRECEP ",
                   FPULSATECLAS("F3","F2"))                
  
CURSOR=CCREAMOVANUL DECLARE
                     CODMOV   VDMOVIM.CODMOV%TYPE:=0;
                     CURSOR C1 IS
                          SELECT STK.CODART, STK.CODLOT, STK.UNIEMB, STK.CANTIDAD, STK.BLOQSTOCK 
                            FROM VDSTOCK STK
                           WHERE STK.CODMAT   = :CODMAT;
                     BEGIN
                        FOR I IN C1 LOOP
                            CODMOV := 0;
                            VDMOV.CREAMOVTO (CODMOV, VD.GETPROP('TAREARECEP'), VD.GETPROP('REGULARIZA-'), VDST.FMOVRECOGIDO, :CODMAT, :CODUBI, :CODMAT, 
                                             I.CODART, I.CODLOT,I.UNIEMB,I.BLOQSTOCK,I.CANTIDAD,0,0, NULL);
                            UPDATE VDRECEPLIN
                               SET CANTIDADR = CANTIDDADR - I.CANTIDAD,
                                   CODOPEMODIF = VDUSER.GETUSER, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS 
                             WHERE CODRECEP  = :CODRECEP
                               AND CODDIV    = :CODDIV
                               AND CODART    = I.CODART
                               AND CODLOT    = I.CODLOT
                               AND BLOQSTOCK = I.BLOQSTOCK;     
                       END LOOP;
                     END;@


