CREACION DE INVENTARIOS
 謳컴컴컴컴컴컴� CABECERA 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켄
 � Designaci�n.   _40____________________________________________  Prioridad @L@ �
 읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
 謳컴컴컴컴컴컴� TIPO INVENTARIO 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
 � Ciclico _      \No inventariadas desde \풡-MM-Y.YY         \Veces contado ___ �
 읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴� 
 謳컴컴컴컴컴컴� UBICACIONES 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
 � HR _    \RP _    \PU _    \Solo vacias _    \Maximo ubicaciones a marcar @L@@ �
 � Ubiaciones   _4096___________________________________________________________ �
 � Solo con movimientos _ desde fecha 풡-MM-Y.YY                                 �
 읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴� 
 謳컴컴컴컴컴컴� ARTICULOS 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
 � Articulos    _4096___________________________________________________________ �
 읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴� 
|

WLONX=690
NOORAINS
NOQUERY
NODELETE
NOUPDATE
TABLA=VDINVENCAB

#PREINSERT=FEJECUTA("CINSINVEN","",
#                   %FFAILURE,"INVENTARIO :CODINVEN CREADO")
                   
POSTCOMMIT=FPULSATECLAS("F5")                   

CAMPO=CODINVEN,OCULTO,"@L@@@@@@@"
CAMPO=DESINVEN
CAMPO=PRIOINVEN,VIRTUAL

CAMPO=CICLICO,VIRTUAL,CHECKBOX("N","S")
CAMPO=NOINVENDESDE,VIRTUAL
CAMPO=VECESCONTADO,VIRTUAL

CAMPO=INCHR,VIRTUAL,CHECKBOX("N","S")
CAMPO=INCRP,VIRTUAL,CHECKBOX("N","S")
CAMPO=INCPU,VIRTUAL,CHECKBOX("N","S")
CAMPO=SOLOVACIAS,VIRTUAL,CHECKBOX("N","S")
CAMPO=MAXUBIAINVEN,VIRTUAL
CAMPO=CODUBIR,CONTEXTUAL=FEJECUTAFORM("TRADUCECSV","S","","","CODUBIR=:TOTAL")
CAMPO=SWTUBISINMOV,VIRTUAL,CHECKBOX("N","S")
CAMPO=FECDESDEUBIINV
CAMPO=CODARTR,CONTEXTUAL=FEJECUTAFORM("TRADUCECSV","S","","","CODARTR=:TOTAL")

CAMPO=NUMMARCADAS,AUXILIAR,VIRTUAL,OCULTO
CAMPO=TSEL,AUXILIAR,OCULTO,"_"


CURSOR=CINSINVEN DECLARE
                   CURSOR C1 IS SELECT UBI.CODUBI
                                 FROM VDUBICA UBI,VDCONTE CNT,VDSTOCK STK
                                 WHERE UBI.CODUBI=CNT.CODUBI AND STK.CODMAT=CNT.CODMAT AND
                                       VD.CONTIENECAD(:CODARTR,STK.CODART)>0 AND VD.CONTIENE(:CODAREAR,UBI.CODAREA)>0 AND
                                       VD.CONTIENECAD(:CODUBIR,UBI.CODUBI)>0 AND VD.CONTIENECAD(:CODMATR,CNT.CODMAT)>0 AND
                                       VD.CONTIENE(VD.GETPROP('AREASNOINVEN'),UBI.CODAREA)=0 AND
                                       UBI.TIPOUBI='R';
                   PROCESADAS NUMBER;
                   MISTATUSLIN NUMBER;
                   MISTATUSCAB NUMBER;
                 BEGIN
                    BEGIN
                       SELECT CODINVEN,STATUS INTO :CODINVEN,MISTATUSCAB FROM VDINVENCAB WHERE STATUS BETWEEN 50 AND 100 AND DESINVEN=:DESINVEN;
                       IF MISTATUSCAB=50 THEN MISTATUSLIN:=50;
                         ELSE MISTATUSLIN:=100;
                       END IF;
                       EXCEPTION WHEN NO_DATA_FOUND THEN
                          :CODINVEN:=VDSECINVEN.NEXTVAL;
                          MISTATUSLIN:=50;
                          MISTATUSCAB:=50;
                          INSERT INTO VDINVENCAB (CODINVEN, DATOSHOST, DESINVEN, CODDIVR, CODCLASE, CODCLASIFR, CODAREAR, CODUBIR, CODMATR, CODARTR, CODLOTR, SWTUBISINMOV, 
                                           FECDESDEUBIINV, SWTUBIMARCADAS, PUBIAINVEN,STATUS, CODOPEINS, FECINS, HORAINS, CODOPEVAL, FECVAL,  HORAVAL, CODCOMEN, CODOPEMODIF, 
                                           FECMODIF, HORAMODIF, FECINTERF, HORAINTERF, TIPOINVEN, PRIOINVEN) 
                                   VALUES (:CODINVEN,'',:DESINVEN,'','','',:CODAREAR,:CODUBIR,:CODMATR,:CODARTR,'',:SWTUBISINMOV,
                                           :FECDESDEUBIINV,'N',:PUBIAINVEN,MISTATUSCAB,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,'',0,'',0,VDUSER.GETUSER,
                                           VD.FECHASYS,VD.HORASYS,0,'','MANUAL',:PRIOINVEN);
                    END;
                  FOR I IN C1 LOOP
                      IF DBMS_RANDOM.VALUE(1,100)<=:PUBIAINVEN THEN
                          SMINVEN.INSERTAENINVEN(:CODINVEN,I.CODUBI,MISTATUSLIN);
                         ELSE
                          VDLOG.PONMENSAJE('PRUEBA','NO INSERTO');
                        END IF;
                   END LOOP;
                   SELECT COUNT(*) INTO PROCESADAS FROM VDINVENCONTEO WHERE CODINVEN=:CODINVEN;
                   IF PROCESADAS=0 THEN 
                       DELETE VDINVENCAB WHERE CODINVEN=:CODINVEN;
                       :CODINVEN:=0;
                    END IF;
                END;@
                
BOTON=B1,615,45,50,50,"P",restart.png,F2,"Mostrar seleccion",INCLUDECSS="background-color: transparent;border-width:0px"
BOTON=B3,615,110,50,50,"P",apply.png,F4,"Crear invetario",INCLUDECSS="background-color: transparent;border-width:0px"