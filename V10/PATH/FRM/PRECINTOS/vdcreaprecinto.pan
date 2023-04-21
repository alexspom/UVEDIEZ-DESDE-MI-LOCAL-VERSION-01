#CERRAR PRECINTOS
CREAR NUEVO PRECINTO

 
 
  Nuevo Precinto:  _________
									
 

  Tipo Precinto:   _________________________ 

 
 
  Ubicación:       _20___________
                      
|
TABLA=DUAL
NOQUERY
NOLOCK
NOORAINS
NOUPDATE
NODELETE
NOCOMMIT
POSX=1
POSY=6
REGPAG=1
WLONX=1250
WLONY=900
INCLUDEFICHEROCSS="vertis.css"
INCLUDEFICHEROHTML="botoneratactil.html"
INCLUDEHTML="<SCRIPT> var eventoforzado=1; window.document.getElementById('tactil').style.top=550+'px'; window.document.getElementById('tactil').style.left=970+'px'; </SCRIPT>"

CAMPO=CODPRECINTO,AUXILIAR,NOUPDATE,WPOSX=180,WLONX=130,INCLUDECSS="HEIGHT:46px;font-family:Tahoma;font-size:28pt;"
CAMPO=TIPOPRECINTO,AUXILIAR,NOUPDATE,COMBOX("CTIPOPRECINTO"),WPOSX=180,WLONX=130,INCLUDECSS="HEIGHT:46px;font-family:Tahoma;font-size:18pt;"
CAMPO=CODUBIAUX,AUXILIAR,NOUPDATE,WPOSX=180,WLONX=130,INCLUDECSS="HEIGHT:46px;font-family:Tahoma;font-size:28pt;"
CAMPO=KK,AUXILIAR,NOUPDATE,OCULTO,"_"

TECLA=F4,FEJECUTA("-CSELPRECNUEVO","Precinto ya existe",
                  "CCODPRECINTONULL","Código de Precinto no puede ser nulo",
                  "CCODUBINULL","Código de Ubicación no puede ser nulo",
                  "CINSERTA","ERROR EN CINSERTA",
                  FIMPRIME("ETIQ","VDPRECINTO.GEN;VDPRECINTO.VSQ;CSELPRECINTO","CODPRECINTO=:CODPRECINTO",""),":V10ERROR",
                  FCOMMIT,"",
                  %FFAILURE,"Nuevo precinto :CODPRECINTO creado",                 
                  FPULSATECLAS("F5"))

TECLA=10001,FEJECUTA("CPONPRECINTO","")

CURSOR=CSELPRECNUEVO SELECT :CODPRECINTO FROM VDPRECINTO WHERE CODPRECINTO=:CODPRECINTO;

CURSOR=CCODPRECINTONULL SELECT :KK FROM DUAL WHERE :CODPRECINTO IS NOT NULL;

CURSOR=CCODUBINULL SELECT :KK FROM DUAL WHERE :CODUBIAUX IS NOT NULL;

CURSOR=CINSERTA INSERT INTO VDPRECINTO VALUES (:CODPRECINTO,VDVST.FPRCABIERTO,:CODUBIAUX,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,
                                               NULL,0,NULL,NULL,0,NULL,NULL,0,NULL,VDSECCOMEN.NEXTVAL,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,
                                               '1-'||:TIPOPRECINTO||'-NOAPTO');

CURSOR=CPONPRECINTO SELECT VDSEQPRECINTO.NEXTVAL CODPRECINTO FROM DUAL;
          
CURSOR=CTIPOPRECINTO SELECT CODCLASE TIPOPRECINTO FROM VDCLASES WHERE CODCLASIF='DESTRUCCION';          

BOTON=SALIR,1050,120,120,120,"Salir",vertis\vertissalir.png,27,"Salir de la pantalla",INCLUDECSS="border-style:outset;background-color:transparent"
#BOTON=SALIR,1050,120,120,80,"Salir",NO,27,"Salir de la pantalla" 
BOTON=VALIDAR,1050,260,120,120,"Confirmar",vertis\vertisok.png,F4,"Confirmar cambios" ,INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=PONPRECINTO,1050,400,120,120,"Pon Num. Precinto",vertis\vertisnuevoprecinto.png,10001,"Obtiene el numero número de precinto automáticamente" ,INCLUDECSS="border-style:outset;background-color:transparent"
ONLINE={F4} Confirmar {Esc} Salir;