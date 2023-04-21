# Módulo   : VDSIMULADISPZONA
# Función  : Simulador del display de zona
#
# Creación : 24-08-2008
# Autor    : MGM
###########################################
MANTENIMIENTO DEL DISPLAY DE ZONA
 Id:  @L@    Numdisp:  @L@@@@@  Ge.: @L@          Estado: @L@@  _40________________________
 
         Texto: _256_____________________
                                                   
 

 Teclas: _256_______________________________________________________________________________

 Luces:  +  -   AZUL VERDE ROJA FUNC  
         _  _    _     _     _   _    _256__________________________________________________
           
 VdExtra: _256___________________     Ultima modificación   _32________ ¿D-MM-Y.YY ________

|

TABLA=VDINFOHARDDISP

CAMPO=IDINFOPICK,NOUPDATE,TOOLTIP("Número de infopick hardware al que se refiere el display")
CAMPO=NUMDISP,VIRTUAL,NOUPDATE,TOOLTIP("Número de display en la red InfoPick.\nEste Código y el anterior forman la clave primaria.")
CAMPO=IDINFOGEST,TOOLTIP("Identificador del programa que gestiona la zona")
CAMPO=STATUS,POSTCHANGE=FEJECUTA("CDESSTATUS","No existe el status"),TOOLTIP("Status del display")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripción del status del display")
CAMPO=TEXTO,TOOLTIP("Texto que se muestra en el display")
CAMPO=TECLAS,TOOLTIP("Teclas encoladas en el display")
CAMPO=LMAS,AUXILIAR,NOENTER,TOOLTIP("Indicador de tecla de mas")
CAMPO=LMENOS,AUXILIAR,NOENTER,TOOLTIP("Indicador de tecla de menos")
CAMPO=LAZUL,AUXILIAR,NOENTER,TOOLTIP("Indicador de luz azul")
CAMPO=LVERDE,AUXILIAR,NOENTER,TOOLTIP("Indicador de luz verde")
CAMPO=LROJA,AUXILIAR,NOENTER,TOOLTIP("Indicador de luz roja")
CAMPO=LFUNC,AUXILIAR,NOENTER,TOOLTIP("Indicador de tecla de funcion")
CAMPO=LUCES,POSTCHANGE=FEJECUTA("CDAMELUCES","")
CAMPO=VDEXTRA,TOOLTIP("Información adicional del display")
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificación")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro")

PREINSERT=FEJECUTA("CSELMODIF","No puedo poner fecha/hora modificacion")
PREUPDATE=FEJECUTA("CSELMODIF","No puedo poner fecha/hora modificacion")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE TIPOSTATUS = 'IHD' AND STATUS = :STATUS;

CURSOR=CESZONA SELECT :IDINFOPICK FROM VDZONAS WHERE IDINFOPICK=:IDINFOPICK AND NUMDISP=:NUMDISP;

CURSOR=CDAMELUCES SELECT VD.PIECE(:LUCES,',',1) LMAS, VD.PIECE(:LUCES,',',2) LMENOS,
			VD.PIECE(:LUCES,',',3) LAZUL, VD.PIECE(:LUCES,',',4) LVERDE,
			VD.PIECE(:LUCES,',',5) LROJA, VD.PIECE(:LUCES,',',6) LFUNC FROM DUAL;

CURSOR=CENCOLAV SELECT :TECLAS||'#' || '0$1'  TECLAS FROM DUAL;
CURSOR=CENCOLAMAS SELECT :TECLAS||'#' || '1$1'  TECLAS FROM DUAL;
CURSOR=CENCOLAMENOS SELECT :TECLAS||'#' || '2$1'  TECLAS FROM DUAL;
CURSOR=CENCOLAF SELECT :TECLAS||'#' || '3$1'  TECLAS FROM DUAL;
CURSOR=CENCOLAINIT SELECT :TECLAS||'#' || '1000$1'  TECLAS FROM DUAL;
CURSOR=CENCOLATICK SELECT :TECLAS||'#' || '1001$1'  TECLAS FROM DUAL;

TECLA=SF2,FEJECUTA("CENCOLAV","",FPULSATECLAS("F4"),"")
TECLA=SF3,FEJECUTA("CENCOLAMAS","",FPULSATECLAS("F4"),"")
TECLA=SF4,FEJECUTA("CENCOLAMENOS","",FPULSATECLAS("F4"),"")
TECLA=SF5,FEJECUTA("CENCOLAF","",FPULSATECLAS("F4"),"")
TECLA=SF6,FEJECUTA("CENCOLAINIT","",FPULSATECLAS("F4"),"")
TECLA=SF7,FEJECUTA("CENCOLATICK","",FPULSATECLAS("F4"),"")


