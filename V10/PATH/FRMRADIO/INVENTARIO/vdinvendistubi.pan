#
# VDINVENDISTUBI.PAN: Inventario ok, pero en otra ubicación.
#
INVENTARIO
__________ __________

##### - ________________________________

  LA MATRICULA NO SE ENCUENTRA
  EN LA UBICACION _12_________
  SINO EN LA UBICACION 
  _12_________
  
  DESEA MOVERLA # ( 0 NO, 1 SI)
 
|

PREQUERY=FEJECUTA("CINICIALIZA", "")

POSTQUERY=FEJECUTA(FIF("CSELNOTNULL",FPOSICIONABLOQUE("VDINVENMAT.PAN"),FSUCCESS),"", 
                   "CVALCONFIRMA", "ERROR, CONFIRME CON\n1 PARA SI, 0 PARA NO",
                   "CCAMBIOUBI","ERROR CAMBIANDO A LA\nUBICACION :CODUBI\n:V10ERROR",
                   FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOVOUT",":CODRECURSO"),"",
                   "CUPDMOV","ERROR ACTUALIZANDO MOVIMIENTO :CODMOVOUT",
                   FCOMMIT,"",
                   FPOSICIONABLOQUE("VDINVENART.PAN"),"")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODINVEN,NOENTER,VIRTUAL
CAMPO=DESINVEN,NOENTER,VIRTUAL
CAMPO=CODUBI,NOENTER,VIRTUAL
CAMPO=CODUBITEORICA,NOENTER,VIRTUAL
CAMPO=CONFIRMA
CAMPO=CODMATLEIDA,OCULTO,VIRTUAL
CAMPO=FECINI,OCULTO,VIRTUAL
CAMPO=HORAINI,OCULTO,VIRTUAL
CAMPO=CODMOVOUT,OCULTO,"##########"


CURSOR=CINICIALIZA SELECT 0 CONFIRMA FROM DUAL;

CURSOR=CSELNOTNULL SELECT :CONFIRMA FROM DUAL 
                    WHERE :CONFIRMA = 0;

CURSOR=CVALCONFIRMA SELECT :CONFIRMA FROM DUAL
                     WHERE :CONFIRMA IN (0,1);

CURSOR=CCAMBIOUBI BEGIN
                    VDUBI.CAMBIOUBICONTE(:CODMATLEIDA, :CODUBI, 'REUBICAR',:CODMOVOUT, 'N','N','CUINV', 10, 1100, :CODRECURSO);
                  END;@

CURSOR=CUPDMOV UPDATE VDMOVIM
                  SET CODDOCUMENTO = :CODINVEN, 
                      CODOPEMODIF = VDUSER.GETUSER,
                      FECMODIF    = VD.FECHASYS,
                      HORAMODIF   = VD.HORASYS
                WHERE CODMOV = :CODMOVOUT;


ONLINE=F1 AYUDA F10 LOGOUT ;