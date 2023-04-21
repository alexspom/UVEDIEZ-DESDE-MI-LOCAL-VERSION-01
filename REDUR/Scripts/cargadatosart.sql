
UPDATE VDARTIC SET (LARGOUNI,ANCHOUNI,ALTOUNI,PESOUNI)=(SELECT MIN(LONGITUD),MIN(ANCHO),MIN(ALTURA),MIN(PESO_BRUTO) FROM TEMPPESO WHERE MATERIAL=CODART)
 WHERE CODART IN (SELECT MATERIAL FROM TEMPPESO);
 
UPDATE VDARTIC SET (UNIEMB,EMBCONT)=(SELECT CAJA,LEAST(PALET/CAJA,999) FROM TEMCAJA WHERE MATERIAL=CODART)
 WHERE CODART IN (SELECT MATERIAL FROM TEMCAJA);
 
DECLARE
   MICODUBIDEST VDUBICA.CODUBI%TYPE;
   MICODMATDEST VDCONTE.CODMAT%TYPE;
   MICODUBIORI VDUBICA.CODUBI%TYPE;
   MICODMATORI VDCONTE.CODMAT%TYPE;
   MICODMOV NUMBER;
   ART VDARTIC%ROWTYPE;
   MSJERROR VARCHAR2(10000);
   RET NUMBER;
 BEGIN
   MICODUBIORI:='REGULARIZA';
   MICODUBIDEST:='INICIAL';
   MICODMATORI:=SMPKG.DAMECODMATVIRT(MICODUBIORI);
   MICODMATDEST:=SMPKG.DAMECODMATVIRT(MICODUBIDEST);
   FOR I IN (SELECT * FROM TEMPSTK) LOOP
          BEGIN
                SELECT * INTO ART FROM VDARTIC WHERE CODART=I.MATERIAL;
                EXCEPTION WHEN NO_DATA_FOUND THEN
                    VDLOG.PONMENSAJE('INSERTSTK','ARTICULO NO EXISTE',I.MATERIAL);
                    CONTINUE;
           END;
          IF I.LIBRE_UTILIZ_>0 THEN
              MICODMOV:=VDSECMOVIM.NEXTVAL;
              INSERT INTO VDMOVIM ( CODMOV, CODCONCE, DATOSHOST, CODUBIORI, CODUBITEMP, CODUBIDEST, CODMATORI, CODMATTEMP, CODMATDEST, 
                                                     TIPOCONTE, PRIOMOV, TAREA,   CODRECURSO, SOLOMUEVE, CODMOVESP,  CODMOVPPASO, CODDOCUMENTO, CODINTERFASE, 
                                                      CODPREPARACION, STATUS, BULTO,  CODART, CODLOT, CANTIDAD,  BLOQUEOSORI, BLOQUEOSDEST, TIPOEMBA, 
                                                      UNIEMB, EMBCONT, MARCASTK,  NUMEROSERIE, PRECIOUNI, PESOUNI,  CODRECEP, CODFLUJO, TIPODEMANDA, 
                                                      CODDEMANDA, LINDEMANDA, CODOPEINS,  MODULOINS, ACCIONINS, FECINS,  HORAINS, MODULOPLANMOV, ACCIONPLANMOV, 
                                                      FECPLANMOV, HORAPLANMOV, CODOPEEJEMOV,  MODULOINIMOV, ACCIONINIMOV, FECINIMOV,  HORAINIMOV, MODULOFINMOV, ACCIONFINMOV, 
                                                      FECFINMOV, HORAFINMOV, VDEXTRA, CODCOMEN, CODOPEMODIF, MODULOMODIF, 
                                                     ACCIONMODIF, FECMODIF, HORAMODIF,  CODBULTOORI, CODBULTODEST, FECINTER,  HORAINTER) 
                                   VALUES (MICODMOV,'REG+','',MICODUBIORI,'',MICODUBIDEST,MICODMATORI,'',MICODMATDEST,
                                                 'NORMAL',0,'INICIAL','','N',0,0,0,0,
                                                 0,2300,'',I.MATERIAL,'L1',I.LIBRE_UTILIZ_,'0000000000','0000000000','CAJA',
                                                 ART.UNIEMB,ART.EMBCONT,'','',0,0,'',0,'',
                                                 '','',VDUSER.GETUSER,'','',VD.FECHASYS,VD.HORASYS,'','',
                                                 0,'',VDUSER.GETUSER,'','',VD.FECHASYS,VD.HORASYS,'','',
                                                 VD.FECHASYS,VD.HORASYS,'',0,VDUSER.GETUSER,'',
                                                 '',VD.FECHASYS,VD.HORASYS,'','',0,'' );
                        RET:=VDACTSTOCK.EJECUTAMOV(MICODMOV,MSJERROR);
           END IF;
          IF I.IN_CONTROL_CAL>0 THEN
              MICODMOV:=VDSECMOVIM.NEXTVAL;
              INSERT INTO VDMOVIM ( CODMOV, CODCONCE, DATOSHOST, CODUBIORI, CODUBITEMP, CODUBIDEST, CODMATORI, CODMATTEMP, CODMATDEST, 
                                                     TIPOCONTE, PRIOMOV, TAREA,   CODRECURSO, SOLOMUEVE, CODMOVESP,  CODMOVPPASO, CODDOCUMENTO, CODINTERFASE, 
                                                      CODPREPARACION, STATUS, BULTO,  CODART, CODLOT, CANTIDAD,  BLOQUEOSORI, BLOQUEOSDEST, TIPOEMBA, 
                                                      UNIEMB, EMBCONT, MARCASTK,  NUMEROSERIE, PRECIOUNI, PESOUNI,  CODRECEP, CODFLUJO, TIPODEMANDA, 
                                                      CODDEMANDA, LINDEMANDA, CODOPEINS,  MODULOINS, ACCIONINS, FECINS,  HORAINS, MODULOPLANMOV, ACCIONPLANMOV, 
                                                      FECPLANMOV, HORAPLANMOV, CODOPEEJEMOV,  MODULOINIMOV, ACCIONINIMOV, FECINIMOV,  HORAINIMOV, MODULOFINMOV, ACCIONFINMOV, 
                                                      FECFINMOV, HORAFINMOV, VDEXTRA, CODCOMEN, CODOPEMODIF, MODULOMODIF, 
                                                     ACCIONMODIF, FECMODIF, HORAMODIF,  CODBULTOORI, CODBULTODEST, FECINTER,  HORAINTER) 
                                   VALUES (MICODMOV,'REG+','',MICODUBIORI,'',MICODUBIDEST,MICODMATORI,'',MICODMATDEST,
                                                 'NORMAL',0,'INICIAL','','N',0,0,0,0,
                                                 0,2300,'',I.MATERIAL,'L1',I.IN_CONTROL_CAL,'0000020000','0000020000','CAJA',
                                                 ART.UNIEMB,ART.EMBCONT,'','',0,0,'',0,'',
                                                 '','',VDUSER.GETUSER,'','',VD.FECHASYS,VD.HORASYS,'','',
                                                 0,'',VDUSER.GETUSER,'','',VD.FECHASYS,VD.HORASYS,'','',
                                                 VD.FECHASYS,VD.HORASYS,'',0,VDUSER.GETUSER,'',
                                                 '',VD.FECHASYS,VD.HORASYS,'','',0,'' );
                        RET:=VDACTSTOCK.EJECUTAMOV(MICODMOV,MSJERROR);
           END IF;
          IF I.BLOQUEADO>0 THEN
              MICODMOV:=VDSECMOVIM.NEXTVAL;
              INSERT INTO VDMOVIM ( CODMOV, CODCONCE, DATOSHOST, CODUBIORI, CODUBITEMP, CODUBIDEST, CODMATORI, CODMATTEMP, CODMATDEST, 
                                                     TIPOCONTE, PRIOMOV, TAREA,   CODRECURSO, SOLOMUEVE, CODMOVESP,  CODMOVPPASO, CODDOCUMENTO, CODINTERFASE, 
                                                      CODPREPARACION, STATUS, BULTO,  CODART, CODLOT, CANTIDAD,  BLOQUEOSORI, BLOQUEOSDEST, TIPOEMBA, 
                                                      UNIEMB, EMBCONT, MARCASTK,  NUMEROSERIE, PRECIOUNI, PESOUNI,  CODRECEP, CODFLUJO, TIPODEMANDA, 
                                                      CODDEMANDA, LINDEMANDA, CODOPEINS,  MODULOINS, ACCIONINS, FECINS,  HORAINS, MODULOPLANMOV, ACCIONPLANMOV, 
                                                      FECPLANMOV, HORAPLANMOV, CODOPEEJEMOV,  MODULOINIMOV, ACCIONINIMOV, FECINIMOV,  HORAINIMOV, MODULOFINMOV, ACCIONFINMOV, 
                                                      FECFINMOV, HORAFINMOV, VDEXTRA, CODCOMEN, CODOPEMODIF, MODULOMODIF, 
                                                     ACCIONMODIF, FECMODIF, HORAMODIF,  CODBULTOORI, CODBULTODEST, FECINTER,  HORAINTER) 
                                   VALUES (MICODMOV,'REG+','',MICODUBIORI,'',MICODUBIDEST,MICODMATORI,'',MICODMATDEST,
                                                 'NORMAL',0,'INICIAL','','N',0,0,0,0,
                                                 0,2300,'',I.MATERIAL,'L1',I.BLOQUEADO,'0000010000','0000010000','CAJA',
                                                 ART.UNIEMB,ART.EMBCONT,'','',0,0,'',0,'',
                                                 '','',VDUSER.GETUSER,'','',VD.FECHASYS,VD.HORASYS,'','',
                                                 0,'',VDUSER.GETUSER,'','',VD.FECHASYS,VD.HORASYS,'','',
                                                 VD.FECHASYS,VD.HORASYS,'',0,VDUSER.GETUSER,'',
                                                 '',VD.FECHASYS,VD.HORASYS,'','',0,'' );
                        RET:=VDACTSTOCK.EJECUTAMOV(MICODMOV,MSJERROR);
           END IF;
    END LOOP;
END;