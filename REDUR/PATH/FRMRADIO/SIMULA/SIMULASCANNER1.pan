SELECCION DE SCANNER A SIMULAR
 _10_______ _10_______
 
 Red     @L@ __________________________________
 Scanner @L@
 
 Lectura: _2000__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

|

POSTQUERY=FEJECUTA(FIF("CESNUL",FPOSICIONABLOQUE("SIMULASCANNER.PAN")),"",
                   "CGRABALECTURA","NO PUEDO GRABAR LECTURA",
                   FCOMMIT,"",
                   FPOSICIONABLOQUE("SIMULASCANNER1.PAN"),"")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=REDSCAN,VIRTUAL,NOENTER
CAMPO=DESCRED,VIRTUAL,NOENTER
CAMPO=SCANNER,NOENTER,VIRTUAL
CAMPO=TEXTO,SCAN,AUTOENTER

CURSOR=CESNUL SELECT :TEXTO FROM DUAL WHERE :TEXTO IS NULL;

CURSOR=CGRABALECTURA BEGIN
                      VDLOG.PONMENSAJE('SIMULASCANNER','LECTURAS '||VD.NUMPIECES(:TEXTO,' '));
                      FOR I IN 1..VD.NUMPIECES(:TEXTO,' ') LOOP
                         IF LENGTH(NVL(VD.PIECE(:TEXTO,' ',I),'0'))<2 THEN CONTINUE;
                          END IF;
                         VDLOG.PONMENSAJE('SIMULASCANNER',' '||VD.PIECE(:TEXTO,' ',I));
                         INSERT INTO VDSCANLECT (SEQACCION, REDSCAN, SCANNER,  TEXTO, STATUS, CODOPEMODIF,   FECMODIF, HORAMODIF, CODCOMEN) 
                           VALUES (VDSECSCANLECT.NEXTVAL,:REDSCAN,:SCANNER,VD.PIECE(:TEXTO,' ',I),100,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,0);
                      END LOOP;
                       :TEXTO:=NULL;
                      END;@