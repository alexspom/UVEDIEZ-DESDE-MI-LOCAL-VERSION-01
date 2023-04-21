#CERRAR PRECINTOS
CREAR NUEVO PRECINTO

 
  Precinto:        _________
  
  
  
 
  Nuevo Precinto:  _________								
 
 
 
 
 
  Ubicación:       _20___________
                      
|
TABLA=DUAL
NOQUERY
NOLOCK
NOORAINS
NOUPDATE
NODELETE
NOCOMMIT

INCLUDEFICHEROCSS="vertis.css"
INCLUDEFICHEROHTML="botoneratactil.html"
INCLUDEHTML="<SCRIPT> var eventoforzado=1; window.document.getElementById('tactil').style.top=550+'px'; window.document.getElementById('tactil').style.left=970+'px'; </SCRIPT>"

CAMPO=CODPRECINTOOLD,VIRTUAL("CODPRECINTO"),NOENTER,INCLUDECSS="HEIGHT:46px;font-family:Tahoma;font-size:28pt;",WPOSX=180,WLONX=130
CAMPO=CODPRECINTO,AUXILIAR,WPOSX=180,WLONX=130,INCLUDECSS="HEIGHT:46px;font-family:Tahoma;font-size:28pt;"
CAMPO=CODUBI,AUXILIAR,WPOSX=180,WLONX=130,INCLUDECSS="HEIGHT:46px;font-family:Tahoma;font-size:28pt;"
CAMPO=KK,AUXILIAR,NOUPDATE,OCULTO,"_"
CAMPO=TIPOPRECINTO,AUXILIAR,VIRTUAL,OCULTO

CURSOR=CPONCODUBI SELECT :CODUBI CODUBIAUX FROM DUAL;


TECLA=F4,FEJECUTA("CCIERRAVIEJO","",
                  FIF("CCODPRECINTONULL",
                     FEJECUTA("-CSELPRECNUEVO","Precinto ya existe",
                              "CCODUBINULL","Código de Ubicación no puede ser nulo",
                              "CINSERTA","ERROR EN CINSERTA",
                              FIMPRIME("ETIQ","VDPRECINTO.GEN;VDPRECINTO.VSQ;CSELPRECINTO","CODPRECINTO=:CODPRECINTO",""),":V10ERROR",
                              FCOMMIT,"",
                              %FFAILURE,"Precinto :CODPRECINTOOLD cerrado y nuevo precintio :CODPRECINTO Creado"),
                     FEJECUTA(FCOMMIT,"",
                              %FFAILURE,"Precinto :CODPRECINTOOLD cerrado")),"Si informa un nuevo precinto debe indicar su ubicación",                
                  FPULSATECLAS("F5"))

TECLA=10001,FEJECUTA("CPONPRECINTO","")

CURSOR=CCIERRAVIEJO UPDATE VDPRECINTO SET  STATUS=VDVST.FPRCCERRADO,
                                           CODOPECIERRA=VDUSER.GETUSER,
                                           FECCIERRA=VD.FECHASYS,
                                           HORACIERRA=VD.HORASYS,
                                           CODOPEMODIF=VDUSER.GETUSER,
                                           FECMODIF=VD.FECHASYS,
                                           HORAMODIF=VD.HORASYS
                            WHERE CODPRECINTO=:CODPRECINTOOLD;

CURSOR=CCODPRECINTONULL SELECT :KK FROM DUAL WHERE :CODPRECINTO IS NOT NULL;

CURSOR=CSELPRECNUEVO SELECT :CODPRECINTO FROM VDPRECINTO WHERE CODPRECINTO=:CODPRECINTO;

CURSOR=CCODUBINULL SELECT :KK FROM DUAL WHERE :CODUBI IS NOT NULL;

CURSOR=CINSERTA INSERT INTO VDPRECINTO VALUES (:CODPRECINTO,VDVST.FPRCABIERTO,:CODUBI,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,
                                               NULL,0,NULL,NULL,0,NULL,NULL,0,NULL,VDSECCOMEN.NEXTVAL,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,:TIPOPRECINTO);

CURSOR=CPONPRECINTO SELECT VDSEQPRECINTO.NEXTVAL CODPRECINTO FROM DUAL;
          

BOTON=SALIR,1050,120,120,120,"Salir",vertis\vertissalir.png,27,"Salir de la pantalla" ,INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=VALIDAR,1050,260,120,120,"Cerrar Precinto",vertis\vertiscerrar.png,F4,"Cerrar Precinto" ,INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=PONPRECINTO,1050,400,120,120,"Pon Num. Precinto",vertis\vertisnuevoprecinto.png,10001,"Obtiene el numero número de precinto automáticamente" ,INCLUDECSS="border-style:outset;background-color:transparent"
ONLINE={F4} Confirmar {Esc} Salir;