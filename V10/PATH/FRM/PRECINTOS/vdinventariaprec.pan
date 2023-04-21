INVENTARIAR PRECINTOS CERRADOS



                      Precinto  Tipo                   Ubicaci�n    Cierre                             Inv.
                      _________ _______________________ _20_________ _______________ �D-MM-YY ________   _
|

TABLA=VDPRECINTO
WHERE=STATUS=VDVST.FPRCCERRADO AND EXISTS (SELECT 1 FROM VDDEVOLLIN DVL WHERE DVL.CODPRECINTO = VDPRECINTO.CODPRECINTO AND STATUS=VDVST.FDVLAPTO);
NOUPDATE
NOINSERT
NODELETE



PREUPDATE=FEJECUTA("@CCHECKINVEN","",
                   "CINVENTARIAPREC","No puedo mandar a destruir el precinto",
                   "CPONDVLINVENTARIO","ERROR EN CPONDVLDESTRUIDA",
                   "CUPDDEVOLCAB","ERROR EN CUPDDEVOLCAB",
                   FCOMMIT,"",
                   "CLIMPIAUBI","",
                   FIMPRIME("INFORME","PRECINTOINVENTARIO.rpt","PRECINTO=:CODPRECINTO","",""),"ERROR :V10ERROR",
                   FCOMMIT,"")
                                            
POSTCOMMIT=FEJECUTA(%FFAILURE,"PRECINTOS DESTRUIDOS",FPULSATECLAS("F3"),"")

CAMPO=CODPRECINTO,TECLA=CR,FPULSATECLAS("F2"),TITULO("Precinto")
#,POSTCHANGE=FEJECUTA("CTIPOPRECINTO","")
CAMPO=TIPOPRECINTO,TITULO("Tipo de Precinto"),NOENTER
CAMPO=CODUBI,NOENTER,TITULO("Ubicaci�n")
CAMPO=CODOPECIERRA,TITULO("Cierre")
CAMPO=FECCIERRA
CAMPO=HORACIERRA
CAMPO=INVENTARIAR,AUXILIAR,POSTCHANGE=FEJECUTA(FVERIFICA("SN ","Debe introducir S(i) o N(o)"),"",
                                            "-CDEVOLPDTES","EL PRECINTO TIENE MERCANCIA DE DEVOLUCIONES PENDIENTES DE CONFIRMAR PROTOCOLO",
                                            "-CMERCANCIANOAPTA","EL PRECINTO TIENE MERCANCIA NO APTA"),TITULO("Inv"),WLONX=12,INCLUDECSS="font-size:25px"

CURSOR=CMERCANCIANOAPTA SELECT :CODPRECINTO FROM VDDEVOLLIN DVL WHERE CODPRECINTO=:CODPRECINTO AND STATUS = VDVST.FDVLNOAPTO AND NVL(:INVENTARIAR,'N')='S';

CURSOR=CTIPOPRECINTO SELECT VDDEVOL.DAMETIPOPRECINTO(:CODPRECINTO) TIPOPRECINTO FROM DUAL;

CURSOR=CCHECKINVEN SELECT :INVENTARIAR FROM DUAL WHERE NVL(:INVENTARIAR,'N')='S';

CURSOR=CDEVOLPDTES SELECT :CODPRECINTO FROM VDDEVOLLIN DVL, VDDEVOLCAB DVC 
                       WHERE DVL.CODPRECINTO = :CODPRECINTO AND DVC.SEQDEVOL=DVL.SEQDEVOL AND DVC.STATUS < VDVST.FDVCVALPROTO AND NVL(:INVENTARIAR,'N')='S';

CURSOR=CPONDVLINVENTARIO UPDATE VDDEVOLLIN SET STATUS = VDVST.FDVLINVENTARIO, CODOPEINVEN=VDUSER.GETUSER,
                                              FECINVEN = VD.FECHASYS, HORAINVEN = VD.HORASYS 
                                         WHERE CODPRECINTO = :CODPRECINTO AND STATUS = VDVST.FDVLAPTO; 

 
CURSOR=CUPDDEVOLCAB UPDATE VDDEVOLCAB DVC 
                          SET STATUS = VDVST.FDVCFINALIZADA, 
                              CODOPEFIN = VDUSER.GETUSER, FECFIN = VD.FECHASYS, HORAFIN = VD.HORASYS, 
                              CODOPEMODIF = VDUSER.GETUSER, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS 
         									WHERE STATUS = VDVST.FDVCVALPROTO AND
         									      SEQDEVOL IN (SELECT DISTINCT SEQDEVOL FROM VDDEVOLLIN WHERE CODPRECINTO=:CODPRECINTO)
         									      AND NOT EXISTS (SELECT 1 FROM VDDEVOLLIN DVL WHERE DVL.SEQDEVOL = DVC.SEQDEVOL AND DVL.STATUS BETWEEN VDVST.FDVLAPTO AND VDVST.FDVLNOAPTO);


CURSOR=CLIMPIAUBI UPDATE  VDPRECINTO SET CODUBI=NULL WHERE STATUS=VDVST.FPRCINVENTARIO AND CODPRECINTO=:CODPRECINTO AND :INVENTARIAR='S';



CURSOR=CINVENTARIAPREC UPDATE VDPRECINTO SET STATUS=VDVST.FPRCINVENTARIO,
                                            CODOPEINVEN=VDUSER.GETUSER,
                                            FECINVEN=VD.FECHASYS,
                                            HORAINVEN=VD.HORASYS,
                                            CODOPEMODIF=VDUSER.GETUSER,
                                            FECMODIF=VD.FECHASYS,
                                            HORAMODIF=VD.HORASYS
                       WHERE STATUS=VDVST.FPRCCERRADO AND CODPRECINTO=:CODPRECINTO AND :INVENTARIAR='S';

BOTON=SALIR,1000,100,120,120,"Salir",vertis\vertissalir.png,27,"Salir de la pantalla" ,INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=VALIDAR,850,100,120,120,"Inventariar",vertis\vertisinventario.png,F4,"Inventariar Precinto" ,INCLUDECSS="border-style:outset;background-color:transparent"
ONLINE={F4} Confirmar {Esc} Salir;