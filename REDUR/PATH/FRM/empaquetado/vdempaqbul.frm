CAMPO=CODMESA,OCULTO,"_20"
PREFORM=FEJECUTA("+CSELMESA","")
BEGINBLOQUE=VDEMPAQBUL.PAN
  CURSOR=CSELMESA SELECT VDUSER.GETHOSTNAME CODMESA FROM DUAL;
ENDBLOQUE
BEGINBLOQUE=VDBULLIN.PAN
  PADRE=VDEMPAQBUL.PAN
  POSY=8
  REGPAG=30
ENDBLOQUE 