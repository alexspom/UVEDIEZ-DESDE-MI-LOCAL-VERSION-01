# M�dulo   : RPPU5.PAN
# Funci�n  : Pantalla de lectura de matr�cula de paletizaci�n
#
# Creaci�n : 24-09-2014
# Autor    : FPD
###########################################
# Hist�rico de cambios:
#
PICKING TOUR (ORIGEN)
_10_______ _10_______
PICKING TOUR (ORIGEN)




  LEA MATRICULA 
  ____________________


|

POSTQUERY=FEJECUTA(FIF("CISNULL",
                       FEJECUTA("CDESASIGNAMOV","\n ERROR\n QUITANDO MOVIMIENTO",+FCOMMIT,"",+FPOSICIONABLOQUE("-1"),"")),"",
                   "+CINSCONTE","\n MATRICULA NO EXISTE",
                   "-CSELCODMATUBI","\n MATRICULA OCUPADA",
                   "CUPDARECURSO","\n NO SE PUEDE\n ACTUALIZAR MATRICULA",
                   FCOMMIT,"",
                   FPOSICIONABLOQUE("RPPU1.PAN"),"")
                   

# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=CODMAT,VIRTUAL,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FFUERZASCAN("CNT"),"\n ERROR\n DEBE LEER\n EL PALLET",
                                                        "CELIMINA00", "\n ERROR \n AL TRATAR MATRICULA",
                                                        "CLONGMATRICULA","\n ERROR \n LONGITUD DE MATRICULA \n INCORRECTA")

CURSOR=CISNULL SELECT :CODMAT FROM DUAL WHERE :CODMAT IS NULL;
                 
CURSOR=CDESASIGNAMOV DECLARE RET NUMBER; BEGIN RET:=VDPLANMOV.DESASIGNAMOV(:CODRECURSO,1); END;@

CURSOR=CINSCONTE BEGIN
                   INSERT INTO VDCONTE
                           (CODMAT     , TIPOCONTE  , CNTSSCC    , CODUBI     , POSCONTE   , ALTURACONTE, 
                            STATUS     , FECENTRADA , HORAENTRADA, VDEXTRA    , CODCOMEN   , CODOPEMODIF, 
                            FECMODIF   , HORAMODIF  )
                           VALUES (:CODMAT , 'NORMAL'  , NULL  , NULL, (SELECT NVL(MAX(POSCONTE),0)+1 FROM VDCONTE WHERE CODUBI IS NULL), 1, 0, VD.FECHASYS, VD.HORASYS, 
                                   NULL, 0,  VDUSER.GETUSER,  VD.FECHASYS, VD.HORASYS);
                   EXCEPTION WHEN OTHERS THEN NULL;
                 END;@                   

CURSOR=CSELCODMAT SELECT CODMAT FROM VDCONTE WHERE CODMAT=:CODMAT;

CURSOR=CSELCODMATUBI SELECT CODMAT FROM VDCONTE WHERE CODMAT=:CODMAT AND CODUBI IS NOT NULL AND CODMAT IN (SELECT CODMAT FROM VDSTOCK);

CURSOR=CUPDARECURSO UPDATE VDRECURSO SET CODMAT=:CODMAT WHERE CODRECURSO=:CODRECURSO;

CURSOR=CELIMINA00 SELECT CASE WHEN LENGTH(:CODMAT)=20 AND :CODMAT LIKE '00%' THEN SUBSTR(:CODMAT,3) ELSE :CODMAT END CODMAT FROM DUAL;

CURSOR=CLONGMATRICULA SELECT :CODMAT FROM DUAL WHERE LENGTH(:CODMAT)=VD.GETPROP('LONMAT') OR :CODMAT IS NULL;
