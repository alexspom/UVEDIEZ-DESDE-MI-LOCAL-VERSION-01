CAMPO=POSICION,AUXILIAR,OCULTO,"#L#"
CAMPO=BLOQUEOACTUAL,AUXILIAR,OCULTO,"_"
CAMPO=NUEVOBLOQUEO,AUXILIAR,OCULTO,"_"
CAMPO=TIPOACCION,AUXILIAR,OCULTO,"_50________"
CAMPO=MENSAJE,AUXILIAR,OCULTO,"_1024__________________________"
BEGINBLOQUE=VDLOTES.PAN
  PREREGISTRO=PRESEHIJO
  NOINSERT
  NODELETE
  NOUPDATE
  CAMPO=MITITULO,AUXILIAR,OCULTO,"_256_____________"
  CAMPO=POSICION,AUXILIAR,VIRTUAL,OCULTO
  CAMPO=BLOQUEOACTUAL,AUXILIAR,VIRTUAL,OCULTO
  CAMPO=NUEVOBLOQUEO,AUXILIAR,VIRTUAL,OCULTO
  CAMPO=TIPOACCION,AUXILIAR,VIRTUAL,OCULTO
  CAMPO=MENSAJE,AUXILIAR,VIRTUAL,OCULTO
  WHERE=EXISTS (SELECT 1 FROM VDSTOCK STK WHERE STK.CODART=VDLOTES.CODART AND STK.CODLOT=VDLOTES.CODLOT AND SUBSTR(STK.BLOQUEOS,:POSICION,1)=:BLOQUEOACTUAL);

	CURSOR=CPRUEBA SELECT 2 POSICION, 0 BLOQUEOACTUAL, 1 NUEVOBLOQUEO, 'BLOQUEO' TIPOACCION FROM DUAL;	
  PREBLOQUE=FEJECUTA("CPRUEBA","")
  TITULO=LISTA DE LOTES CON CONTENEDORES LIBRES A BLOQUEAR
  
  REGPAG=20
  POSY=2    
	CURSOR=CFORMATITULO SELECT TRIM(:TIPOACCION) || ' DE CONTENEDORES DEL LOTE ' || :CODLOT || ' Y ARTICULO ' || :CODART MITITULO FROM DUAL;
ENDBLOQUE
BEGINBLOQUE=VDLIBCONTES.PAN 
  PADRE=VDLOTES.PAN
  PREQUERY=QUERYHIJO
  POSY=25
  REGPAG=30
  BOTON=INFORME,750,480,100,100,"Tratar Lote",vertis\cajaaprecinto.png,F4,"Tratar Lote",INCLUDECSS="border-style:outset;background-color:transparent" 
  TITULO=LISTA DE CONTENEDORES LIBRES A BLOQUEAR
ENDBLOQUE    