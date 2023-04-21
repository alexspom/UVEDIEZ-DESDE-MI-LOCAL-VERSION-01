##############################################################################
#  Módulo  : VDFMDDECOMERRORMAT.PAN                                          #
#  Función : LEER UNA MATRICULA PARA HACER EL MOVIMIENTO DE UN FMD ERRONEO   #
#                                                                            #
#  Autor : DFL                                                               #
#  Fecha : 16-07-2018                                                        #
#  Revisador por  :                                                          #
#  Fecha revisión :                                                          #
##############################################################################
#  Histórico de cambios
#  --------------------
#
##############################################################################
MATRICULA PARA ARTICULOS CON FMD EN ERROR
 Escanear la matricula para separar los artículos con FMD-ERRONEA

          Matricula: _40___________________________ 
|

NOQUERY
NOCOMMIT
NOINSERT
NOUPDATE
NODELETE

POSX=2
POSY=3

CAMPO=CODART,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODLOT,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODBULTO,AUXILIAR,VIRTUAL,OCULTO

CAMPO=CODMAT,AUXILIAR,POSTCHANGE=FDESIGNACION("CSELNOTNULL","",
                                              FIF("CVERMAT","CVERBLOQ","CCREAMAT"), "ERROR EN MATRICULA",
                                              "CMOVART","ERROR AL HACER EL MOVIMIENTO",
                                              FCOMMIT,"",
                                              FPULSATECLAS("ESC")
                                              )
 


#CURSORES
#########
CURSOR=CSELNOTNULL SELECT :CODMAT FROM DUAL WHERE :CODMAT IS NOT NULL;

CURSOR=CVERMAT SELECT :CODMAT FROM VDCONTE WHERE CODMAT=:CODMAT;

CURSOR=CCREAMAT BEGIN 
                    IF VDFMD.CREAMAT(:CODMAT, VD.GETPROP('FMDTIPOCONTENEW'), VD.GETPROP('FMDCODUBIMATNEW')) <> 0 THEN RAISE NO_DATA_FOUND; END IF;                         
                END;@

CURSOR=CVERBLOQ SELECT  :CODMAT 
                  FROM VDCONTE CON
                  LEFT OUTER JOIN VDSTOCK STK ON
                    CON.CODMAT = STK.CODMAT
                  WHERE CON.CODMAT = :CODMAT
                    AND NVL(SUBSTR(STK.BLOQUEOS,3,1),'1') <> '0'; 

CURSOR=CMOVART BEGIN
                  IF VDFMD.SEPARARFMDERROR(:CODMAT,:CODART, :CODLOT,:CODBULTO)!=0 THEN RAISE NO_DATA_FOUND;
				   END IF;
				  COMMIT;
               END;@


ONLINE=     {F1} Ayuda {F2} Consulta {F4} Confirmar cambios {F5} Borrar pantalla {F9} Borrar registro
                                    {May-F10} Menú {Esc} Salir;
