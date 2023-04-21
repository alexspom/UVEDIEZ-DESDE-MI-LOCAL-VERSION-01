# Módulo   : VDLOTES.PAN
# Función  : Mantenimiento de lotes
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
CREACION DE NUEVO LOTE

  Artículo _40________________ 
  _100_____________________________________


  
  Lote      _40___________________   

  
  Caducidad ________      (DDMMYYYY)


|
TABLA=DUAL
NOUPDATE
NOINSERT
NODELETE
NOQUERY
WPOSY=180
WPOSX=400
WLONX=400
WLONY=310

REGPAG=1


TECLA=F4,FEJECUTA("+CSELBLOQUEO","",
                  "CCHECKFORMATOCADUCI","EL FORMATO DE LA FECHA DE CADUCIDAD\n DEBE SER DIA,MES,AÑO (DDMMAAAA)",
                  "CSELRETEST","ERROR AL CALCULAR FECHA RETEST",
                  "CINSERTALOTE","ERROR INSERTANDO LOTE",
                  FCOMMIT,"",
				          FPULSATECLAS("ESC"))

CAMPO=CODART,VIRTUAL,AUXILIAR,TOOLTIP("Código del artículo"),INCLUDECSS="height:26px;COLOR:DARKBLUE;font-style:bold;font-size:14pt;border-style:ridge;background-color:#F7BE81;",WPOSY=-2,WLONX=28
CAMPO=DESART,VIRTUAL,NOENTER,TOOLTIP("Designación del artículo"),INCLUDECSS="height:26px;COLOR:DARKBLUE;font-style:bold;font-size:14pt;border-style:ridge;background-color:#F7BE81;",WPOSY=12,WLONX=6
CAMPO=CODLOT,AUXILIAR,POSTCHANGE=FVALNOCERO("Debe informar un lote"),NOUPDATE,TOOLTIP("Lote"),TITULO("Lote"),INCLUDECSS="height:26px;COLOR:DARKBLUE;font-style:bold;font-size:14pt;border-style:ridge;background-color:#F7BE81;",WPOSY=-2,WLONX=20
CAMPO=CADUCI,AUXILIAR,TOOLTIP("Caducidad en formato DDMMAAAA"),TITULO("Caduci"),INCLUDECSS="height:26px;COLOR:DARKBLUE;font-style:bold;font-size:14pt;border-style:ridge;background-color:#F7BE81;",WPOSY=-2,WLONX=28
CAMPO=FORMATOOK,AUXILIAR,OCULTO,"_8_"
CAMPO=RETEST,OCULTO,"________",TOOLTIP("Fecha de retest del lote en formato DDMMAAAA")
CAMPO=BLOQLOTE,NOENTER,OCULTO,"__________",TOOLTIP("Bloqueos del lote")

CURSOR=CSELDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;

CURSOR=CSELBLOQUEO SELECT '0' || DECODE(SWTANALISIS,'S','1','0') || '00000000' BLOQLOTE
                     FROM VDARTIC
                    WHERE CODART = :CODART;

CURSOR=CCHECKFORMATOCADUCI SELECT TO_CHAR(TO_DATE(:CADUCI,'YYYYMMDD'),'YYYYMMDD') FORMATOOK FROM DUAL WHERE :CADUCI IS NOT NULL AND TO_NUMBER(SUBSTR(:CADUCI,1,4))> 2000;

CURSOR=CSELRETEST SELECT DECODE(UNIRETEST,'A',TO_CHAR(ADD_MONTHS(TO_DATE(:CADUCI,'YYYYMMDD'),-12*TRETEST),'YYYYMMDD'),
                                          'M',TO_CHAR(ADD_MONTHS(TO_DATE(:CADUCI,'YYYYMMDD'),-TRETEST),'YYYYMMDD'),
                                          'D',TO_CHAR(TO_DATE(:CADUCI,'YYYYMMDD')-TRETEST),'YYYYMMDD') RETEST
                    FROM VDARTIC 
                   WHERE CODART = :CODART AND UNIRETEST IN ('A','M','D');

CURSOR=CINSERTALOTE INSERT INTO VDLOTES VALUES (:CODART,:CODLOT,NULL,:CADUCI,:RETEST,:BLOQLOTE,1,'S','N',0,NULL,'VERTIS',VD.FECHASYS, VD.HORASYS);

BOTON=LOTE,450,370,120,120,"Crear Lote",vertis\vertisguardar.png,F4,"Crear Lote" ,INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=LOTE,600,370,120,120,"Salir",vertis\vertissalir.png,ESC,"Salir" ,INCLUDECSS="border-style:outset;background-color:transparent"