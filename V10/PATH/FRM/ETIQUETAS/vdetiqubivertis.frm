# MOdulo   : VDETIQUBIVERTIS.FRM
# Función  : ImpresiOn de etiquetas de ubicación en VERTIS
#
# Creación : 30-03-2011
# Autor    : FPD 
###########################################
# HistOrico de cambios:
INCLUDEFICHEROCSS="vertis.css"

CAMPO=SID, AUXILIAR, OCULTO,"@L@@@"
CAMPO=SERIAL, AUXILIAR, OCULTO, "@L@@@@"
CAMPO=TERMINAL, AUXILIAR, OCULTO, "__________________"

PREFORM=FEJECUTA("CDAMESID", "ERROR AVERIGUANDO SID", "CDELANTIGUO", "NO PUEDO BORRAR ENTRADAS ANTERIORES", FCOMMIT,"")

BEGINBLOQUE=VDETIQUBIVERTIS.PAN
  NOINSERT
  NODELETE
  NOUPDATE
  POSX=1
  POSY=1
  WPOSY=40
  WLONX=1230
  WLONY=900
	CAMPO=SID, AUXILIAR, VIRTUAL,OCULTO
	CAMPO=SERIAL, AUXILIAR, VIRTUAL,OCULTO
	CAMPO=TERMINAL, AUXILIAR, VIRTUAL,OCULTO

	CURSOR=CDAMESID BEGIN 
	                    VD.DAMESID (:SID, :SERIAL, :TERMINAL);
                  END;@

	CURSOR=CDELANTIGUO DELETE FROM VDCRETIQUETAS WHERE SID=:SID AND SERIAL=:SERIAL;
ENDBLOQUE    
BEGINBLOQUE=VDETIQLISTAUBIVERTIS.PAN
  PADRE=VDETIQUBIVERTIS.PAN
  PREQUERY=QUERYHIJO
  NOINSERT
  NODELETE
  NOUPDATE
  PQUERY
  TQUERY
  POSY=1
  POSX=63
  WPOSY=75
  WLONY=600
  WMARCOFRAME
  REGPAG=30
	CAMPO=SID, AUXILIAR, VIRTUAL,OCULTO
	CAMPO=SERIAL, AUXILIAR, VIRTUAL,OCULTO
	CAMPO=TERMINAL, AUXILIAR, VIRTUAL,OCULTO
	CURSOR=CDELANTIGUO DELETE FROM VDCRETIQUETAS WHERE SID=:SID AND SERIAL=:SERIAL;
	TECLA=SF9,FEJECUTAFORM("VDCRETIQUETAS","S","SID=:SID AND SERIAL=:SERIAL","","")
ENDBLOQUE  