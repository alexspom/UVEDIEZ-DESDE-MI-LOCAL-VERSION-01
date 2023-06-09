## M�dulo   : RPPU4.PAN
# Funci�n  : Formulario de regularizaci�n de cantidades
#
# Creaci�n : 30-09-2014
# Autor    : FPD
###########################################
PICKING TOUR (ORIGEN)
_10_______ _10_______
PICKING TOUR (ORIGEN)

ORIGEN:   _20_________________

ARTICULO: _20_________________
_40____________________________

REGULARIZA @L@@@@@ UNIDADES

 CANTIDAD QUE QUEDA: _______
    (BLANCO: NO VALIDA)
|

PREQUERY=FEJECUTA("CACERO","",
                  "CREGULA","",
                  "+CSELDEFCONFI","")

POSTQUERY=FEJECUTA("CVERIFICAVALIDA","\n TECLEA CANTIDAD\n ENTRE 0-99999\n O BLANCO",
                   "-CNOVALIDA","\n NO SE PUEDE\n DAR DE ALTA STOCK\n AL HABER SERVIDO\n CON FALTAS",
                   "CPASACERO","",
                   FIF("CVUELVE",
                       FEJECUTA(FPOSICIONABLOQUE("RPPU3.PAN"))),"",
                   "+CREGMAS","",
                   "CERROR","\n ERROR AL CREAR\n STOCK",
                   "+CREGDEFECTUOSO","",
                   "CERROR","\n ERROR AL DESCONTAR\n DEFECTUOSOS",
                   "CDUMMY","",
                   FIF("CDEMENOS",
                       FEJECUTA("+CREGNEGATIVA","",
                                "CERROR","\n ERROR AL REGULARIZAR")),"",
                   FIF("CDEMENOS2",
                       FEJECUTA("+CREGNEGATIVA2","",
                                "CERROR","\n ERROR AL REGULARIZAR")),"",
                   "+CREGMAS1","",
                   "CERROR","\n ERROR AL CREAR\n STOCK",
                   "CUPDRECARGAR","\n ERROR MARCANDO \n UBICACION PARA RECARGA",
                   "CUPDMOVSERV","\n ERROR TRATANDO\n CANTIDAD SERVIDA",
                   "CUPDMOVPDTE","\n ERROR ACTUALIZANDO\n MOVIMIENTO PENDIENTE",
                   FIF("CHAYCANTIDAD",FRECOGESTKSYNC("ACTSTKORIGEN",":CODMOV",":CODRECURSO"),
                       FEJECUTA("CANULAMOV"," ERROR\n ANULANDO MOVIMIENTO",
                                "CANULAMOVPDTE"," ERROR\n ANULANDO MOVIMIENTO\n PENDIENTE")),"",
                   FCOMMIT," ERROR\n HACIENDO COMMIT",
                   FIF("CSELOPNO",
                       FEJECUTA("CDESASIGNAMOV","\n ERROR\n QUITANDO MOVIMIENTO",
                                FCOMMIT," ERROR\n HACIENDO COMMIT",
                                FIF("CSEL2ETAPAS",FPOSICIONABLOQUE("RPPU10.PAN"),
                                                  FPOSICIONABLOQUE("RPPU8.PAN"))),
                       FEJECUTA(FIF("CSELMOVASIG",FPOSICIONABLOQUE("RPPU1.PAN"),
                                                  FEJECUTA(FIF("CDAMEOTROMOV",FEJECUTA(+FCOMMIT,"",FPOSICIONABLOQUE("RPPU1.PAN"),"\n ERROR\n CARGANDO PANTALLA"),
                                                                              FIF("CSEL2ETAPAS",FPOSICIONABLOQUE("RPPU10.PAN"),
                                                                                                FPOSICIONABLOQUE("RPPU8.PAN"))),"")),"")),"\n ERROR\n EN OPCION 0")

CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=CODMAT,VIRTUAL,OCULTO 
CAMPO=CODMOV,VIRTUAL,OCULTO
CAMPO=CODMATORI,VIRTUAL,OCULTO
CAMPO=PINTAUBI,VIRTUAL,NOENTER
CAMPO=CODUBIORI,VIRTUAL,OCULTO
CAMPO=CODUBIDEST,VIRTUAL,OCULTO
CAMPO=CODART,VIRTUAL,NOENTER
CAMPO=DESART1,VIRTUAL,NOENTER
CAMPO=CODLOT,VIRTUAL,OCULTO
CAMPO=UNIEMB,VIRTUAL,OCULTO
CAMPO=NCAJAS,VIRTUAL,OCULTO
CAMPO=SERVCAJA,VIRTUAL,OCULTO
CAMPO=UNIDSUELTAS,VIRTUAL,OCULTO
CAMPO=SERVPICO,VIRTUAL,OCULTO
CAMPO=UNIDADESHOST,VIRTUAL,OCULTO
CAMPO=TOTALUNID,VIRTUAL,OCULTO,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=DEFECTUOSO,VIRTUAL,OCULTO
CAMPO=OPCION,VIRTUAL,OCULTO
CAMPO=MSGERROR,VIRTUAL,OCULTO
CAMPO=LONGERROR,VIRTUAL,OCULTO
CAMPO=SERVIDAS,VIRTUAL,OCULTO
CAMPO=REGU,NOENTER
CAMPO=OPCVALIDA
CAMPO=VALIDA,VIRTUAL,OCULTO
CAMPO=SKORIG,VIRTUAL,OCULTO
CAMPO=CERO,VIRTUAL,OCULTO
CAMPO=MAXDEFECTUOSO,VIRTUAL,OCULTO
CAMPO=NEWCODMOV,OCULTO,"@L@@@@@@@"
CAMPO=DEST,OCULTO,"_"
CAMPO=AJUSTEPOS,OCULTO,"_10_"
CAMPO=AJUSTENEG,OCULTO,"_10_"
CAMPO=AJUSTEDEF,OCULTO,"_10_"
CAMPO=ORDENSTK,VIRTUAL,OCULTO
CAMPO=RET,OCULTO,"@@"
CAMPO=CODAREA,VIRTUAL,OCULTO
CAMPO=CODPERFIL,VIRTUAL,OCULTO

CURSOR=CACERO SELECT NULL OPCVALIDA FROM DUAL;

CURSOR=CREGULA SELECT :SKORIG-:SERVIDAS-:DEFECTUOSO REGU FROM DUAL;

CURSOR=CVERIFICAVALIDA SELECT TO_NUMBER(:OPCVALIDA) VALIDA 
                         FROM DUAL 
                        WHERE TO_NUMBER(:OPCVALIDA) BETWEEN 0 AND 99999
                           OR :OPCVALIDA IS NULL;

CURSOR=CNOVALIDA SELECT :OPCVALIDA FROM DUAL
                  WHERE :TOTALUNID>:SERVIDAS+:DEFECTUOSO
                         AND :OPCVALIDA IS NOT NULL AND :VALIDA>0;

CURSOR=CPASACERO SELECT DECODE(:OPCVALIDA,NULL,'N','S') CERO FROM DUAL;

CURSOR=CVUELVE SELECT :CERO FROM DUAL WHERE :CERO='N';

CURSOR=CREGMAS BEGIN
                 IF (:DEFECTUOSO+:SERVIDAS>:SKORIG) THEN
                   :RET:=0;
                   :NEWCODMOV:=0;
                   VDSTK.REGULARIZASTK(:CODMATORI,:ORDENSTK,:AJUSTEPOS,'REGULARIZA',(:DEFECTUOSO+:SERVIDAS)-:SKORIG,NULL,:MSGERROR,:NEWCODMOV,:RET);
				   UPDATE VDMOVIM SET CODRECURSO=:CODRECURSO WHERE CODMOV=:NEWCODMOV;
                   :SKORIG:=:DEFECTUOSO+:SERVIDAS;
                   UPDATE VDUBICA SET SWTUBIMARCADA='S' 
                    WHERE (CODUBI=:CODUBIORI OR CODUBI IN (SELECT DISTINCT CNT.CODUBI FROM VDCONTE CNT,VDSTOCK STK 
                                                            WHERE CNT.CODMAT=STK.CODMAT AND STK.CODART=:CODART)) AND
                          CODUBI NOT IN (SELECT UB1.CODUBI FROM VDUBICA UB1 WHERE CODAREA IN ('DEFECTUOSO','DEVOLUCION'));
                 END IF;
               END;@

CURSOR=CREGDEFECTUOSO DECLARE
                        MICODMATDEST VDCONTE.CODMAT%TYPE;
                      BEGIN
                        IF :DEFECTUOSO=0 THEN RETURN;
                        END IF;
                        :RET:=0;
                        :NEWCODMOV:=0;
                        :SKORIG:=:SKORIG-:DEFECTUOSO;
                        UPDATE VDMOVIM SET CANTIDAD=CANTIDAD-:DEFECTUOSO WHERE CODMOV=:CODMOV;
                        SELECT CODMAT INTO MICODMATDEST FROM VDCONTE WHERE CODUBI='DEFECTUOSO' AND TIPOCONTE='VIRTUAL' AND ROWNUM<2;
                        VDMOV.CREAMOV(:NEWCODMOV,'CU',:AJUSTEDEF,VDST.FMOVRECODEPO,:CODMATORI,'DEFECTUOSO',MICODMATDEST,
                                       MICODART=>:CODART,MICANTIDAD=>:DEFECTUOSO,MIUNIEMB=>:UNIEMB,MIBLOQUEOSDEST=>'0000020000',MICODRECURSO=>:CODRECURSO);
                        IF :NEWCODMOV=0 THEN 
                          :RET:=1;
                          :MSGERROR:='ERROR CREANDO MOVIMIENTO';
                        ELSE 
                          :RET:=VDACTSTOCK.EJECUTAMOV(:NEWCODMOV,:MSGERROR);
                        END IF;
                      END;@

CURSOR=CERROR SELECT :RET FROM DUAL WHERE :RET=0;

CURSOR=CDEMENOS SELECT :SERVIDAS FROM DUAL WHERE :SERVIDAS<:TOTALUNID-:DEFECTUOSO AND :SERVCAJA<:NCAJAS;

CURSOR=CDEMENOS2 SELECT :SERVIDAS FROM DUAL WHERE :SERVIDAS<:TOTALUNID-:DEFECTUOSO AND :SERVCAJA=:NCAJAS;

CURSOR=CREGNEGATIVA BEGIN
                      IF (:SKORIG-:SERVIDAS>0) THEN
                        :RET:=0;
                        :NEWCODMOV:=0;
                        VDSTK.REGULARIZASTK(:CODMATORI,:ORDENSTK,:AJUSTENEG,'REGULARIZA',(-1)*(:SKORIG-:SERVIDAS),NULL,:MSGERROR,:NEWCODMOV,:RET);
						UPDATE VDMOVIM SET CODRECURSO=:CODRECURSO WHERE CODMOV=:NEWCODMOV;
                        :SKORIG:=:SERVIDAS;
                        UPDATE VDUBICA SET SWTUBIMARCADA='S' 
                         WHERE (CODUBI=:CODUBIORI OR CODUBI IN (SELECT DISTINCT CNT.CODUBI FROM VDCONTE CNT,VDSTOCK STK 
                                                                 WHERE CNT.CODMAT=STK.CODMAT AND STK.CODART=:CODART)) AND
                               CODUBI NOT IN (SELECT UB1.CODUBI FROM VDUBICA UB1 WHERE CODAREA IN ('DEFECTUOSO','DEVOLUCION'));
                      END IF;
                    END;@

CURSOR=CREGNEGATIVA2 BEGIN
                       :RET:=0;
                       :NEWCODMOV:=0;
                       VDSTK.REGULARIZASTK(:CODMATORI,:ORDENSTK,:AJUSTENEG,'REGULARIZA',(-1)*(:TOTALUNID-:SERVIDAS),NULL,:MSGERROR,:NEWCODMOV,:RET);
						UPDATE VDMOVIM SET CODRECURSO=:CODRECURSO WHERE CODMOV=:NEWCODMOV;
                      :SKORIG:=:SKORIG-(:TOTALUNID-:SERVIDAS);
                       UPDATE VDUBICA SET SWTUBIMARCADA='S' 
                        WHERE (CODUBI=:CODUBIORI OR CODUBI IN (SELECT DISTINCT CNT.CODUBI FROM VDCONTE CNT,VDSTOCK STK 
                                                                WHERE CNT.CODMAT=STK.CODMAT AND STK.CODART=:CODART)) AND
                              CODUBI NOT IN (SELECT UB1.CODUBI FROM VDUBICA UB1 WHERE CODAREA IN ('DEFECTUOSO','DEVOLUCION'));
                     END;@


CURSOR=CREGMAS1 BEGIN
                  IF (:VALIDA>0 AND :CERO='S') THEN
                    :RET:=0;
                    :NEWCODMOV:=0;
                    VDSTK.REGULARIZASTK(:CODMATORI,:ORDENSTK,:AJUSTEPOS,'REGULARIZA',:VALIDA,NULL,:MSGERROR,:NEWCODMOV,:RET);
						UPDATE VDMOVIM SET CODRECURSO=:CODRECURSO WHERE CODMOV=:NEWCODMOV;
                    UPDATE VDUBICA SET SWTUBIMARCADA='S' 
                      WHERE (CODUBI=:CODUBIORI OR CODUBI IN (SELECT DISTINCT CNT.CODUBI FROM VDCONTE CNT,VDSTOCK STK 
                                                             WHERE CNT.CODMAT=STK.CODMAT AND STK.CODART=:CODART)) AND
                           CODUBI NOT IN (SELECT UB1.CODUBI FROM VDUBICA UB1 WHERE CODAREA IN ('DEFECTUOSO','DEVOLUCION'));
                  END IF;
                END;@


CURSOR=CDIVIDEERROR BEGIN :MSGERROR:=VD.DIVERRORRADIO(:V10ERROR,:LONGERROR);
                    END;@

CURSOR=CSELOPNO SELECT :OPCION OPCION
                  FROM DUAL
                 WHERE :OPCION='N';

CURSOR=CDESASIGNAMOV DECLARE RET NUMBER; BEGIN RET:=VDPLANMOV.DESASIGNAMOV(:CODRECURSO,1); END;@


CURSOR=CDEST SELECT :DEST FROM DUAL WHERE :DEST='S';

CURSOR=CDAMEOTROMOV DECLARE RET NUMBER;
                        BEGIN RET:=VDPLANMOV.ASIGNAMOVPERFIL(:CODRECURSO,:CODPERFIL);
                        IF RET=-1 THEN RAISE NO_DATA_FOUND;
                        END IF;
                    END;@

CURSOR=CSELMOVASIG SELECT CODMOV FROM VDMOVIM MOV,VDRECURSO REC
                          WHERE MOV.STATUS=VDST.FMOVASIGNADO
                            AND MOV.CODRECURSO=REC.CODRECURSO
                            AND REC.CODRECURSO=:CODRECURSO
                            AND REC.CODPERFIL=:CODPERFIL; 

CURSOR=CSELDEFCONFI SELECT VD.GETPROP('AJUSTE+') AJUSTEPOS,
                           VD.GETPROP('AJUSTE-') AJUSTENEG,
                           VD.GETPROP('AJUSTED') AJUSTEDEF
                      FROM DUAL;

CURSOR=CDUMMY SELECT :SKORIG FROM DUAL;

CURSOR=CSELOPINTER SELECT :OPCION OPCION
                     FROM DUAL
                    WHERE :OPCION='3';

CURSOR=CSELMOVINTER SELECT MOV.CODMOV NEWCODMOV
                     FROM VDMOVIM MOV, VDARTIC ART,VDUBICA UBI,VDRECURSO REC
                    WHERE MOV.STATUS=VDST.FMOVENUBIINTER
                          AND MOV.CODMATORI != MOV.CODMATDEST
                          AND MOV.CODMATTEMP=:CODMAT
                          AND MOV.CODRECURSO=:CODRECURSO
                          AND MOV.CODRECURSO=REC.CODRECURSO 
                          AND REC.CODPERFIL=:CODPERFIL
                          AND MOV.CODART=ART.CODART
                          AND MOV.CODUBIDEST=UBI.CODUBI
                    ORDER BY UBI.ORDENMOVIM;

CURSOR=CCOPIAMOV DECLARE
                   V_MOVIM VDMOVIM%ROWTYPE;
                 BEGIN
                   :RET:=0;
                   SELECT * INTO V_MOVIM FROM VDMOVIM WHERE CODMOV=:NEWCODMOV;
                   SELECT VDSECMOVIM.NEXTVAL INTO V_MOVIM.CODMOV FROM DUAL;
                   V_MOVIM.CODMATORI:=:CODMAT;
                   V_MOVIM.CODUBIORI:='INTER';
                   V_MOVIM.CODMATTEMP:=NULL;
                   V_MOVIM.CODUBITEMP:=NULL;
                   V_MOVIM.CODMOVESP:=:NEWCODMOV;
                   V_MOVIM.STATUS:=VDST.FMOVPDTEMOVIM;
                   INSERT INTO VDMOVIM VALUES V_MOVIM;
                   UPDATE VDMOVIM SET CODUBIDEST='INTER',CODMATDEST=:CODMAT
                    WHERE CODMOV=:NEWCODMOV;
                   EXCEPTION WHEN NO_DATA_FOUND THEN :RET:=1;
                             WHEN OTHERS THEN :RET:=1;
                 END;@

CURSOR=CSEL2ETAPAS SELECT :CODAREA FROM DUAL WHERE :CODAREA IN ('INTERRP');

CURSOR=CUPDRECARGAR UPDATE VDUBICA SET RECARGAR='S' WHERE CODUBI=:CODUBIORI AND :OPCVALIDA=0;

CURSOR=CUPDMOVSERV UPDATE VDMOVIM SET CANTIDAD=:SERVIDAS WHERE CODMOV=:CODMOV AND :SERVIDAS!=CANTIDAD;

CURSOR=CUPDMOVPDTE UPDATE VDMOVIM SET CANTIDAD=:SERVIDAS WHERE CODMOVESP=:CODMOV AND :SERVIDAS!=CANTIDAD;

CURSOR=CHAYCANTIDAD SELECT :RET FROM DUAL WHERE :SERVIDAS>0;

CURSOR=CANULAMOV UPDATE VDMOVIM SET STATUS=VDST.FMOVANULADO WHERE CODMOV=:CODMOV;

CURSOR=CANULAMOVPDTE UPDATE VDMOVIM SET STATUS=VDST.FMOVANULADO WHERE CODMOVESP=:CODMOV;
