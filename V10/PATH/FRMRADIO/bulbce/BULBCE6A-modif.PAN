#
GESTION DE BULBCE CON ETIQUETA
_10_______ _10_______
CAJA COMPLETA

NO HAY MOVIMIENTOS
QUE TRATAR

|

PREQUERY=FEJECUTA("+CSELDEF","",
                  "+CSELLONGERROR","",
                  "+CREGMAS","",
                  "CERROR","\n\n ERROR AL CREAR\n STOCK",
                  "+CREGDEFECTUOSO","",
                  "CERROR","\n\n  ERROR AL DESCONTAR\n DEFECTUOSOS",
                  FIF("CDEMENOS",
                       FEJECUTA("+CREGNEGATIVA","",
                                "CERROR","\n\n  ERROR AL REGULARIZAR")),"",
                  "+CREGMAS1","",
                  "CERROR","\n\n  ERROR AL CREAR\n STOCK",
                  "CCONGELAMOVS","\n\n  ERROR CONGELANDO\n MOVIMIENTOS DE\n UBICACION :CODUBIORIGT",
                  FCOMMIT,"",
                  FIF("-CMOVCONGELADOS",FEJECUTA("+CSELUBI","","CUPDBULTOS","\n\n  ERROR ACTUALIZANDO BULTOS",FCOMMIT,"\n\n ERROR\n HACIENDO COMMIT",
                                                 +FPOSICIONABLOQUE("VDPICKCCERRCONGELA.PAN"),""),FSUCCESS),"\n\n NO HAY\n MOVIMIENTOS\n CONGELADOS",
                  FPOSICIONABLOQUE("BULBCE6B.PAN"),"\n\n ERROR\n CARGANDO BLOQUE\n BULBCE5")
												 

# DEFINICION DE CAMPOS

CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=PINTAUBI,VIRTUAL,OCULTO
CAMPO=CODUBIORIGT,VIRTUAL,OCULTO
CAMPO=CODARTT,VIRTUAL,OCULTO
CAMPO=DESARTT,VIRTUAL,OCULTO
CAMPO=UNIEMB,VIRTUAL,OCULTO
CAMPO=CAJAS,VIRTUAL,OCULTO
CAMPO=CANTIDAD,VIRTUAL,OCULTO
CAMPO=SKORIG,VIRTUAL,OCULTO
CAMPO=SKMOVTO,VIRTUAL,OCULTO
CAMPO=SERVIDA,VIRTUAL,OCULTO
CAMPO=UNISERVIDA,OCULTO,"@L@@@@@@"
CAMPO=DEFECTUOSO,VIRTUAL,OCULTO
CAMPO=VALIDA,VIRTUAL,OCULTO
CAMPO=CERO,VIRTUAL,OCULTO
CAMPO=CTRLCALIDAD,VIRTUAL,OCULTO
CAMPO=CODDIV,VIRTUAL,OCULTO
CAMPO=ANOPED,VIRTUAL,OCULTO
CAMPO=SEQPED,VIRTUAL,OCULTO
CAMPO=CODPED,VIRTUAL,OCULTO
CAMPO=NBULTO,VIRTUAL,OCULTO
CAMPO=CODMATT,VIRTUAL,OCULTO
CAMPO=NBACABADOS,VIRTUAL,OCULTO
CAMPO=PUERTO,VIRTUAL,OCULTO
CAMPO=CODMATUBI,VIRTUAL,OCULTO
CAMPO=NEWCODMOV,OCULTO,"@L@@@@@@@"
CAMPO=ORDENSTK,VIRTUAL,OCULTO
CAMPO=CODUBIDEST,VIRTUAL,OCULTO
CAMPO=AJUSTEPOS,VIRTUAL,OCULTO
CAMPO=AJUSTENEG,VIRTUAL,OCULTO
CAMPO=AJUSTEDEF,VIRTUAL,OCULTO
CAMPO=CODUBI,OCULTO,"_12_"
CAMPO=CODPREPARACION,VIRTUAL,OCULTO
CAMPO=CODMOV,OCULTO,"@L@@@@@@@"
CAMPO=LONGERROR,OCULTO,"@@@"
CAMPO=NUMALBA,OCULTO,"@@@"
CAMPO=RET,OCULTO,"@@"
CAMPO=MSGERROR,VIRTUAL,OCULTO
CAMPO=CODARTANT,VIRTUAL,OCULTO
CAMPO=DESARTT1,VIRTUAL,OCULTO
CAMPO=CODAREAORI,VIRTUAL,OCULTO
CAMPO=OPCION,VIRTUAL,OCULTO
CAMPO=CONTADOR,OCULTO,"@@@@"


CURSOR=CSELDEF SELECT 0 RET,0 NUMALBA,0 CONTADOR FROM DUAL;

CURSOR=CREGDEFECTUOSO   DECLARE
                          MICODMATDEST VDCONTE.CODMAT%TYPE;
                        BEGIN
                        IF :DEFECTUOSO=0 THEN RETURN;
                        END IF;
                        :RET:=0;
                        :NEWCODMOV:=0;
                        :SKORIG:=:SKORIG-:DEFECTUOSO;
                        SELECT CODMAT INTO MICODMATDEST FROM VDCONTE WHERE CODUBI='DEFECTUOSO' AND TIPOCONTE='VIRTUAL' AND ROWNUM<2;
                        VDMOV.CREAMOV(:NEWCODMOV,'CU',:AJUSTEDEF,VDST.FMOVRECODEPO,:CODMATUBI,'DEFECTUOSO',MICODMATDEST,
                                       MICODART=>:CODARTT,MICANTIDAD=>:DEFECTUOSO,MIUNIEMB=>:UNIEMB,MIBLOQUEOSDEST=>'0000020000',MICODRECURSO=>:CODRECURSO);
                        IF :NEWCODMOV=0 THEN 
                          :RET:=1;
                          :MSGERROR:='ERROR CREANDO MOVIMIENTO';
                        ELSE
                          :RET:=VDACTSTOCK.EJECUTAMOV(:NEWCODMOV,:MSGERROR);
                        END IF;
                        VDLOG.PONMENSAJE('BULBCE6A','CREGDEFECTUOSO: ERROR ' || :MSGERROR);
                      END;@

#                      VDSTK.REGULARIZASTK(:CODMATUBI,:ORDENSTK,:AJUSTEDEF,'REGULARIZA',:DEFECTUOSO,NULL,:MSGERROR,:NEWCODMOV,:RET);

CURSOR=CERROR SELECT :RET FROM DUAL WHERE :RET=0;

CURSOR=CDEMENOS SELECT :SERVIDA FROM DUAL WHERE :SERVIDA<:CAJAS;

CURSOR=CREGMAS BEGIN
                 IF (:DEFECTUOSO+(:SERVIDA*:UNIEMB)+:SKMOVTO>:SKORIG) THEN
                   :RET:=0;
                   :NEWCODMOV:=0;
                   VDSTK.REGULARIZASTK(:CODMATUBI,:ORDENSTK,:AJUSTEPOS,'REGULARIZA',(:DEFECTUOSO+(:SERVIDA*:UNIEMB)+:SKMOVTO)-:SKORIG,NULL,:MSGERROR,:NEWCODMOV,:RET);
                   :SKORIG:=:DEFECTUOSO+(:SERVIDA*:UNIEMB)+:SKMOVTO;
                   VDLOG.PONMENSAJE('BULBCE6A','CREGMAS: ERROR ' || :MSGERROR);
                   UPDATE VDUBICA SET SWTUBIMARCADA='S' 
                         WHERE (CODUBI=:CODUBIORIGT OR CODUBI IN (SELECT DISTINCT CNT.CODUBI FROM VDCONTE CNT,VDSTOCK STK 
                                                                  WHERE CNT.CODMAT=STK.CODMAT AND STK.CODART=:CODARTT)) AND
                               CODUBI NOT IN (SELECT UB1.CODUBI FROM VDUBICA UB1 WHERE CODAREA IN ('DEFECTUOSO','DEVOLUCION'));
                 END IF;
               END;@

#                           SGLINVEN.MARCAINVENART(:CODARTT,'REGULARIZACION CAJAS',0,:NEWCODMOV,:CODUBIORIGT);

CURSOR=CREGNEGATIVA BEGIN
                      IF (:SKORIG-(:SERVIDA*:UNIEMB)>0 AND :DEFECTUOSO=0) THEN
                        :RET:=0;
                        :NEWCODMOV:=0;
                        VDSTK.REGULARIZASTK(:CODMATUBI,:ORDENSTK,:AJUSTENEG,'REGULARIZA',(-1)*(:SKORIG-(:SERVIDA*:UNIEMB)),NULL,:MSGERROR,:NEWCODMOV,:RET);
                        :SKORIG:=(:SERVIDA*:UNIEMB);
                        VDLOG.PONMENSAJE('BULBCE6A','CREGNEGATIVA: ERROR ' || :MSGERROR);
                        UPDATE VDUBICA SET SWTUBIMARCADA='S' 
                          WHERE (CODUBI=:CODUBIORIGT OR CODUBI IN (SELECT DISTINCT CNT.CODUBI FROM VDCONTE CNT,VDSTOCK STK 
                                                                   WHERE CNT.CODMAT=STK.CODMAT AND STK.CODART=:CODARTT)) AND
                               CODUBI NOT IN (SELECT UB1.CODUBI FROM VDUBICA UB1 WHERE CODAREA IN ('DEFECTUOSO','DEVOLUCION'));
                      END IF;
                    END;@

#                         SGLINVEN.MARCAINVEN(:CODUBIORIGT,'REGULARIZACION CAJAS',0,:NEWCODMOV);

CURSOR=CREGMAS1 BEGIN
                  IF (:VALIDA>0 AND :CERO='S') THEN
                    :RET:=0;
                    :NEWCODMOV:=0;
                    VDSTK.REGULARIZASTK(:CODMATUBI,:ORDENSTK,:AJUSTEPOS,'REGULARIZA',:VALIDA,NULL,:MSGERROR,:NEWCODMOV,:RET);
                    VDLOG.PONMENSAJE('BULBCE6A','CREGMAS1: ERROR ' || :MSGERROR);
                    UPDATE VDUBICA SET SWTUBIMARCADA='S' 
                        WHERE (CODUBI=:CODUBIORIGT OR CODUBI IN (SELECT DISTINCT CNT.CODUBI FROM VDCONTE CNT,VDSTOCK STK 
                                                                  WHERE CNT.CODMAT=STK.CODMAT AND STK.CODART=:CODARTT)) AND
                               CODUBI NOT IN (SELECT UB1.CODUBI FROM VDUBICA UB1 WHERE CODAREA IN ('DEFECTUOSO','DEVOLUCION'));
                  END IF;
                END;@
#                           SGLINVEN.MARCAINVENART(:CODARTT,'REGULARIZACION CAJAS',0,:NEWCODMOV,:CODUBIORIGT);

CURSOR=CFALTANANULAR SELECT :CAJAS 
                        FROM VDMOVIM MOV
                       WHERE MOV.TAREA LIKE 'PEDEMBA%' 
                         AND MOV.STATUS = VDST.FMOVPDTESTOCK
                         AND MOV.CODRECURSO = :CODRECURSO
                         AND MOV.CODUBIDEST = :CODUBIDEST 
                         AND MOV.CODART     = :CODARTT
                         AND MOV.UNIEMB     = :UNIEMB
                         AND MOV.CODPREPARACION = :CODPREPARACION;

CURSOR=CCONGELAMOVS DECLARE
                      CURSOR C1 IS SELECT MOV.* 
                                      FROM VDMOVIM MOV
                                   WHERE MOV.TAREA LIKE 'PEDEMBA%' 
                                      AND MOV.STATUS = VDST.FMOVASIGNADO
                                      AND MOV.CODRECURSO = :CODRECURSO
                                      AND MOV.CODUBIORI  = :CODUBIORIGT 
                                      AND MOV.CODUBIDEST = :CODUBIDEST 
                                      AND MOV.CODMATORI  = :CODMATT 
                                      AND MOV.CODART     = :CODARTT 
                                      AND MOV.UNIEMB     = :UNIEMB
                                      AND MOV.CODPREPARACION = :CODPREPARACION
                                   ORDER BY DECODE(NVL(NUMEROSERIE,'-'),'-',1,0),
                                            DECODE(NVL(BULTO,'-'),'-',1,0),
                                            DECODE(PRECIOUNI,0,1,0),
                                            DECODE(NVL(TIPOEMBA,'-'),'-',1,0),
                                            DECODE(NVL(CODRECEP,'-'),'-',1,0),
                                            DECODE(NVL(MARCASTK,'-'),'-',1,0),
                                            DECODE(NVL(BLOQUEOSORI,'-'),'-',1,0),
                                            DECODE(NVL(CODLOT,'-'),'-',1,0);
                     CONGELADOS NUMBER;                                   
                   BEGIN
                     UPDATE VDMOVIM SET STATUS=VDST.FMOVASIGNADO,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS 
                      WHERE STATUS=VDST.FMOVPRESENTADO AND CODRECURSO=:CODRECURSO;
                     CONGELADOS:=0;
                     FOR I IN C1 LOOP
                       VDMOV.LIMPIAMOV(I.CODMOV);
                       IF (VDMOV.CONGELA(I.CODMOV)=0) THEN
                         CONGELADOS:=CONGELADOS+1;
                         VDLOG.PONMENSAJE('BULBCE6A','CCONGELAMOVS: CONGELADO MOVTO ' || I.CODMOV);
                         UPDATE VDMOVIM SET STATUS=VDST.FMOVPRESENTADO,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS WHERE CODMOV=I.CODMOV;
                       ELSE
                         VDLOG.PONERROR('BULBCE6A','CCONGELAMOVS: NO SE PUEDE CONGELAR MOVTO ' || I.CODMOV);
                         UPDATE VDMOVIM SET STATUS=VDST.FMOVPDTESTOCK,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS WHERE CODMOV=I.CODMOV; 
                       END IF;
                     END LOOP;
                     UPDATE VDMOVIM SET STATUS=VDST.FMOVPDTESTOCK,CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS 
                      WHERE STATUS=VDST.FMOVASIGNADO 
                        AND CODRECURSO = :CODRECURSO
                        AND CODUBIORI  = :CODUBIORIGT 
                        AND CODUBIDEST = :CODUBIDEST 
                        AND CODMATORI  = :CODMATT 
                        AND CODART     = :CODARTT 
                        AND UNIEMB     = :UNIEMB
                        AND CODPREPARACION = :CODPREPARACION;

                     UPDATE VDBULTOCAB SET SWTANULAR='S',CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS
                      WHERE CODBULTO IN (SELECT BUC.CODBULTO FROM VDBULTOCAB BUC,VDBULTOLIN BUL 
                                          WHERE BUC.STATUS+0=VDST.FBUCBULABANETI AND 
                                                BUC.CODBULTO=BUL.CODBULTO AND
                                                BUL.CODMOV IN (SELECT MOV.CODMOV 
                                                                 FROM VDMOVIM MOV
                                                                WHERE MOV.TAREA LIKE 'PEDEMBA%' 
                                                                  AND MOV.STATUS = VDST.FMOVPDTESTOCK
                                                                  AND MOV.CODRECURSO = :CODRECURSO                                                         
                                                                  AND MOV.CODUBIDEST = :CODUBIDEST 
                                                                  AND MOV.CODART     = :CODARTT
                                                                  AND MOV.UNIEMB     = :UNIEMB
                                                                  AND MOV.CODPREPARACION = :CODPREPARACION));
                   END;@       

CURSOR=CMOVCONGELADOS SELECT :CAJAS 
                        FROM VDMOVIM MOV
                       WHERE MOV.TAREA LIKE 'PEDEMBA%' 
                         AND MOV.STATUS = VDST.FMOVPRESENTADO
                         AND MOV.CODRECURSO = :CODRECURSO
                         AND MOV.CODUBIORI  = :CODUBIORIGT 
                         AND MOV.CODUBIDEST = :CODUBIDEST 
                         AND MOV.CODMATORI  = :CODMATT 
                         AND MOV.CODART     = :CODARTT
                         AND MOV.UNIEMB     = :UNIEMB
                         AND MOV.CODLOT IS NOT NULL
                         AND MOV.CODPREPARACION = :CODPREPARACION
                      GROUP BY CODLOT,UNIEMB; 

CURSOR=CSELUBI SELECT :CODUBIORIGT CODUBI FROM DUAL;

CURSOR=CSELMOVSAJECUTAR SELECT MOV.CODMOV
                          FROM VDMOVIM MOV
                         WHERE MOV.STATUS = #STMOVPRESENTADO 
                           AND MOV.TAREA LIKE 'PEDEMBA%'
                           AND MOV.CODUBIORI = :CODUBIORIGT
                           AND MOV.CODRECURSO = :CODRECURSO
                           AND MOV.CODUBIDEST = :CODUBIDEST 
                           AND MOV.CODMATORI  = :CODMATT
                           AND MOV.CODART = :CODARTT
                           AND MOV.UNIEMB = :UNIEMB
                           AND MOV.CODPREPARACION = :CODPREPARACION;                                   

CURSOR=CDIVIDEERROR BEGIN :MSGERROR:=VD.DIVERRORRADIO(:V10ERROR,:LONGERROR);
                    END;@

CURSOR=CACABABULTOS DECLARE
                      RET NUMBER;
                    BEGIN
                      RET:=VDBULTO.ACABABULTOS(:CODMOV,:CODRECURSO,VDST.FBUCPREPARADO,VDST.FBUCABASCULA,VDST.FBUCAMANIPULAR);
                    END;@

CURSOR=CSELMOV SELECT 'N' CERO                       
                     FROM VDMOVIM MOV,VDARTIC ART, VDUBICA UBI
                    WHERE MOV.STATUS IN (VDST.FMOVASIGNADO,VDST.FMOVPRESENTADO) 
                          AND MOV.CODRECURSO = :CODRECURSO 
                          AND MOV.TAREA LIKE 'PEDEMBA%'
                          AND ART.CODART = MOV.CODART
                          AND MOV.CODUBIORI = UBI.CODUBI
                    ORDER BY UBI.ORDENSALIDA,MOV.CODPREPARACION,DECODE(MOV.STATUS,VDST.FMOVPRESENTADO,0,1);

CURSOR=CSELLONGERROR SELECT VD.GETPROP('LONGITUDERROR') LONGERROR FROM DUAL;

CURSOR=CUPDBULTOS UPDATE VDBULTOCAB SET STATUS=VDST.FBUCBULABAN,SWTLLEVAALB=' ',SWTANULAR='N',
                                        CODOPEMODIF=:CODOPE,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS
                      WHERE CODBULTO IN (SELECT BUC.CODBULTO FROM VDBULTOCAB BUC,VDBULTOLIN BUL 
                                          WHERE BUC.STATUS+0=VDST.FBUCBULABANETI AND 
                                                BUC.CODBULTO=BUL.CODBULTO AND
                                                BUL.CODMOV IN (SELECT MOV.CODMOV 
                                                                 FROM VDMOVIM MOV
                                                                WHERE MOV.TAREA LIKE 'PEDEMBA%' 
                                                                  AND MOV.STATUS = VDST.FMOVPDTESTOCK
                                                                  AND MOV.CODRECURSO = :CODRECURSO                                                         
                                                                  AND MOV.CODUBIDEST = :CODUBIDEST 
                                                                  AND MOV.CODART     = :CODARTT
                                                                  AND MOV.UNIEMB     = :UNIEMB
                                                                  AND MOV.CODPREPARACION = :CODPREPARACION));
