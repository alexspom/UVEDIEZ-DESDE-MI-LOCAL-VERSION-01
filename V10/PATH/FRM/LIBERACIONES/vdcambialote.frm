CAMPO=POSICION,OCULTO,AUXILIAR,OCULTO,"#L#"
CAMPO=BLOQUEOACTUAL,AUXILIAR,OCULTO,"_"
CAMPO=NUEVOBLOQUEO,AUXILIAR,OCULTO,"_"
CAMPO=TIPOACCION,AUXILIAR,OCULTO,"_50________"
CAMPO=CODART,AUXILIAR,OCULTO,"_20_________"
CAMPO=CODLOT,AUXILIAR,OCULTO,"_20_________"
CAMPO=LITERAL,AUXILIAR,OCULTO,"_100"
CAMPO=MENSAJE,AUXILIAR,OCULTO,"_1024__________________________"
CAMPO=VALIDA,AUXILIAR,OCULTO,"_"
BEGINBLOQUE=VDLIBUNLOTE.PAN
    POSX=40
   CAMPO=MENSAJE,AUXILIAR,VIRTUAL,OCULTO
   CURSOR=CSELBLOQUEOS SELECT 2 POSICION, 2 BLOQUEOACTUAL, 0 NUEVOBLOQUEO, 'LIBERACION' TIPOACCION,'N' VALIDA FROM DUAL;	
   PREBLOQUE=FEJECUTA("CSELBLOQUEOS","","CSELLITERAL","")
   PREREGISTRO=PRESEHIJO
   TITULO=LIBERACION DE UN LOTE
   BOTON=INFORME,850,60,100,100,"Tratar Lote",vertis\cajaaprecinto.png,F4,"Tratar Lote",INCLUDECSS="border-style:outset;background-color:transparent" 
ENDBLOQUE

BEGINBLOQUE=VDLIBCONTES.PAN 
  PADRE=VDLIBUNLOTE.PAN
  PREQUERY=QUERYHIJO
  POSY=22
  POSX=40
  REGPAG=30
  TITULO=LISTA DE CONTENEDORES PENDIENTES DE CALIDAD A LIBERAR
  BOTON=INFORME,850,380,100,100,"Tratar Matricula",vertis\cajaaprecinto.png,F4,"Tratar Lote",INCLUDECSS="border-style:outset;background-color:transparent" 
ENDBLOQUE       