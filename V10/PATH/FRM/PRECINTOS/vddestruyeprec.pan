DESTRUIR PRECINTOS CERRADOS



                      Precinto  Tipo                    Ubicaci�n    Cierre                            Dest.
                      _________ _______________________ _20_________ _______________ �D-MM-YY ________   _
|

TABLA=VDPRECINTO
WHERE=STATUS=VDVST.FPRCCERRADO AND EXISTS (SELECT 1 FROM VDDEVOLLIN DVL WHERE DVL.CODPRECINTO = VDPRECINTO.CODPRECINTO AND STATUS IN (VDVST.FDVLNOAPTO,VDVST.FDVLREACOND)); 
NOUPDATE
NOINSERT
NODELETE



PREUPDATE=FEJECUTA("@CCHECKDESTRUIR","", 
                   "CDESTRUYEPREC","No puedo mandar a destruir el precinto",
                   "CPONDVLDESTRUIDA","ERROR EN CPONDVLDESTRUIDA",                                      
                   FCOMMIT,"",
                   "CLIMPIAUBI","",
                   FIMPRIME("INFORME","PRECINTODESTRUIR.RPT","PRECINTO=:CODPRECINTO","",""),"ERROR :V10ERROR",
                   FCOMMIT,"")

#                   "CUPDDEVOLCAB","ERROR EN CUPDDEVOLCAB",
                                            
POSTCOMMIT=FEJECUTA(FIF("CCHECKDESTRUIR", 
                        FEJECUTA(%FFAILURE,"PRECINTOS DESTRUIDOS",FPULSATECLAS("F3"),""),
                        FEJECUTA(FFAILURE,"NO HAY CAMBIOS QUE REALIZAR")),"")

CAMPO=CODPRECINTO,TECLA=CR,FPULSATECLAS("F2"),TITULO("Precinto")
#,POSTCHANGE=FEJECUTA("CTIPOPRECINTO","")
CAMPO=TIPOPRECINTO,NOENTER,TITULO("Tipo de Precinto")
CAMPO=CODUBI,NOENTER,TITULO("Ubicaci�n")
CAMPO=CODOPECIERRA,TITULO("Cierre")
CAMPO=FECCIERRA
CAMPO=HORACIERRA
CAMPO=DESTRUIR,AUXILIAR,POSTCHANGE=FEJECUTA(FVERIFICA("SN ","Debe introducir S(i) o N(o)"),"",
                                            "-CMERCANCIAAPTA","EL PRECINTO TIENE MERCANCIA EN ESTADO APTO"),TITULO("Des"),WLONX=12,INCLUDECSS="font-size:25px"
#"-CDEVOLPDTES","EL PRECINTO TIENE MERCANCIA DE DEVOLUCIONES PENDIENTES DE CONFIRMAR PROTOCOLO",

CURSOR=CMERCANCIAAPTA SELECT :CODPRECINTO FROM VDDEVOLLIN WHERE CODPRECINTO=:CODPRECINTO AND STATUS = VDVST.FDVLAPTO AND NVL(:DESTRUIR,'N')='S';

CURSOR=CCHECKDESTRUIR SELECT :DESTRUIR FROM DUAL WHERE NVL(:DESTRUIR,'N')='S';

CURSOR=CTIPOPRECINTO SELECT VDDEVOL.DAMETIPOPRECINTO(:CODPRECINTO) TIPOPRECINTO FROM DUAL;

# DEBE DE CAMBIAR EL ESTADO DE LAS LINEAS
# COMPROBAR QUE NO TENGA LINEAS DE DEVOUCIONES  < 400 (CONFIRMADAS PROTOCOLO)
# SI DEVOLUCIONES DE SUS LINEAS SIN LINEAS ENTRE 100 Y 200, SE PONEN A 500
CURSOR=CDEVOLPDTES SELECT :CODPRECINTO FROM VDDEVOLLIN DVL, VDDEVOLCAB DVC 
                       WHERE DVL.CODPRECINTO = :CODPRECINTO AND DVC.SEQDEVOL=DVL.SEQDEVOL AND DVC.STATUS < VDVST.FDVCVALPROTO AND NVL(:DESTRUIR,'N')='S';

CURSOR=CPONDVLDESTRUIDA UPDATE VDDEVOLLIN SET STATUS = VDVST.FDVLDESTRUIDA, CODOPEDESTRUYE=VDUSER.GETUSER,
                                              FECDESTRUYE = VD.FECHASYS, HORADESTRUYE = VD.HORASYS 
                                         WHERE CODPRECINTO = :CODPRECINTO AND STATUS BETWEEN VDVST.FDVLAPTO AND VDVST.FDVLNOAPTO; 

CURSOR=CUPDDEVOLCAB UPDATE VDDEVOLCAB DVC 
                          SET STATUS = VDVST.FDVCFINALIZADA,  
                              CODOPEFIN = VDUSER.GETUSER, FECFIN = VD.FECHASYS, HORAFIN = VD.HORASYS, 
                              CODOPEMODIF = VDUSER.GETUSER, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS 
         									WHERE STATUS = VDVST.FDVCVALPROTO AND 
         									      SEQDEVOL IN (SELECT DISTINCT SEQDEVOL FROM VDDEVOLLIN WHERE CODPRECINTO=:CODPRECINTO)
         									      AND NOT EXISTS (SELECT 1 FROM VDDEVOLLIN DVL WHERE DVL.SEQDEVOL = DVC.SEQDEVOL AND DVL.STATUS BETWEEN VDVST.FDVLAPTO AND VDVST.FDVLNOAPTO);

CURSOR=CLIMPIAUBI UPDATE  VDPRECINTO SET CODUBI=NULL WHERE STATUS=VDVST.FPRCDESTRUIDO AND CODPRECINTO=:CODPRECINTO AND :DESTRUIR='S';

CURSOR=CDESTRUYEPREC UPDATE VDPRECINTO SET STATUS=VDVST.FPRCDESTRUIDO,
                                            CODOPEDESTRUYE=VDUSER.GETUSER,
                                            FECDESTRUYE=VD.FECHASYS,
                                            HORADESTRUYE=VD.HORASYS,
                                            CODOPEMODIF=VDUSER.GETUSER,
                                            FECMODIF=VD.FECHASYS,
                                            HORAMODIF=VD.HORASYS
                       WHERE STATUS=VDVST.FPRCCERRADO AND CODPRECINTO=:CODPRECINTO AND :DESTRUIR='S';

BOTON=SALIR,1000,100,120,120,"Salir",vertis\vertissalir.png,27,"Salir de la pantalla" ,INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=VALIDAR,850,100,120,120,"Destruir",vertis\vertisdestruir2.png,F4,"Destruir Precintos" ,INCLUDECSS="border-style:outset;background-color:transparent"
                       
ONLINE={F4} Confirmar {Esc} Salir;