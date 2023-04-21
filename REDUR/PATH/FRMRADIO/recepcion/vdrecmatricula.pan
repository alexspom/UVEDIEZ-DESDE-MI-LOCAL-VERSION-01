# Módulo   : VDRECMATRICULA.PAN
# Función  : RECEPCIÓN DE MERCANCÍA: Selección de la matrícula donde se va a ubicar el stock.
#            Validaciones:
#              - El contenedor (=matrícula) no debe tener stock creado. En caso de no ser
#                multiartículo, no debe existir en el pulmón y no debe estar validada la recepción.
#              - Multiartículo: indicar de si el palet va a ser multiartículo o no. 
#                Valores posibles: S o N. Por defecto N.
#              - Nº Bultos: en caso de trazabilidad de bulto, se deberá indicar el número de 
#                bultos que se van a recepcionar en el palet que se está recepcionando. 
#                No se valida en esta pantalla  
#            
# Creación : 31-01-2008
# Autor    : ICC
###########################################
# Histórico de cambios:<div></div>
# 
SELECCION DE MATRICULA
 _10_______ _10_______

 PULMON  _12___________
 _11________ _20______________
 _11________ _20______________
 
 /* LEER MATRICULA */
 
 DATOS PALET
 
 MATRICULA: _20_________________ 
 
 _15____________ _
 


|


PREQUERY=FEJECUTA("CLIMPIAR","\nERROR,\nAL LIMPIAR LOS CAMPOS",
                  "COCULTACAMPOS","\nERROR,\nEL TIPO DE ORDEN DE RECEPCION\n:TIPORDREC NO EXISTE",
                  FPOSICIONACAMPO(FSUCCESS,"CODMAT"),"\nERROR,\nAL POSICIONARSE EN EL CAMPO")

POSTQUERY=FEJECUTA(FIF("CSELNOTCEROMAT",FPOSICIONABLOQUE("1"),FSUCCESS),"",
	               "-CVALCODMAT", "\nERROR,\nMATRICULA EN USO,\nLEA OTRA MATRICULA",
                   FPOSICIONABLOQUE("VDRECARTICULO.PAN"),"\nNO SE PUEDE POSICIONAR\nEN EL SIG. BLOQUE")

CAMPO=BLOQUEOS,OCULTO,VIRTUAL
CAMPO=BLOQUEOSORIG,OCULTO,VIRTUAL
CAMPO=TIPORDREC,OCULTO,VIRTUAL
CAMPO=CODDIV,OCULTO,VIRTUAL
CAMPO=DESDIV,OCULTO,VIRTUAL
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=PULMON,NOENTER,VIRTUAL
CAMPO=NCODORDREC,NOENTER
CAMPO=CODORDREC,VIRTUAL,NOENTER
CAMPO=NCODPROTO,NOENTER
CAMPO=CODPROTO,VIRTUAL,NOENTER
CAMPO=CODMAT,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA("CELIMINA00", "ERROR AL TRATAR MATRICULA",
                                                FIF("CSELNOTCEROMAT",FPOSICIONABLOQUE("1")),"",
												"CVERLONMAT", "LEA MATRICULA CORRECTA",
                                                FIF("CESCARRO",FEJECUTA("CPONERMULTI","NO PUEDE SELECCIONARSE\nMULTIARTICULO",
                                                               FIF("CSELNOTCEROMAT",FPOSICIONABLOQUE("0"),FSUCCESS), "\nERROR,\nDEBE INFORMARSE\nLA MATRICULA DEL PALET",
                                                               "-CVALCODMAT", "\nERROR,\nMATRICULA EN USO,\nLEA OTRA MATRICULA"),
												      FEJECUTA(FIF("CSELNOTCEROMAT",FPOSICIONABLOQUE("1"),FSUCCESS), "\nERROR,\nDEBE INFORMARSE\nLA MATRICULA DEL PALET")), "")

CAMPO=NMULTIARTICULO
CAMPO=MULTIARTICULO,UPPER,POSTCHANGE=FVERIFICA("SN","EL CAMPO DEBE SER S(SI) O N(NO)")
#,POSTCHANGE=FVALNOCERO("\nERROR,\nDEBE LEER LA MATRICULA")
CAMPO=NBULTOS,OCULTO, "####"
CAMPO=CONTBULTOS,OCULTO, "###"
CAMPO=DUMMY,OCULTO,"#"
CAMPO=CODALBTRAN,OCULTO,VIRTUAL
CAMPO=CODALBPROVE,OCULTO,VIRTUAL
CAMPO=CODAGE,OCULTO,VIRTUAL

CURSOR=CVERLONMAT SELECT :CODMAT FROM DUAL WHERE LENGTH(:CODMAT)=VD.GETPROP('LONMAT');

CURSOR=CPONERMULTI SELECT 'S' MULTIARTICULO FROM DUAL;

CURSOR=CESCARRO SELECT 1 DUMMY
                FROM VDCONTE
                WHERE CODMAT = :CODMAT
                AND TIPOCONTE = VD.GETPROP('TIPOCONTECARRO');

#Todavía no se sabe el artículo, con lo que se toma el valor del primer registro.
CURSOR=COCULTACAMPOS SELECT DECODE(:CODORDREC, NULL, 1, 0) NCODORDREC__INVISIBLE,
                            DECODE(:CODORDREC, NULL, 1, 0) CODORDREC__INVISIBLE,
                            DECODE(:CODPROTO, NULL, 1, 0) NCODPROTO__INVISIBLE,
                            DECODE(:CODPROTO, NULL, 1, 0) CODPROTO__INVISIBLE,
                            DECODE(MULTIARTICULO, 'S', 0, 1) NMULTIARTICULO__INVISIBLE,
                            DECODE(MULTIARTICULO, 'S', 0, 1) MULTIARTICULO__INVISIBLE,
                            'ORD. REC  :' NCODORDREC, 'PROTOCOLO :' NCODPROTO,  'MULTIARTICULO :' NMULTIARTICULO     
                       FROM VDTIPORDRECLIN
                      WHERE TIPORDREC = :TIPORDREC;

CURSOR=CLIMPIAR SELECT '' CODMAT, 'N' MULTIARTICULO, 0 NBULTOS, 0 CONTBULTOS
           FROM DUAL;

CURSOR=CSELNOTNULL SELECT 1 DUMMY FROM DUAL 
                    WHERE :CODMAT IS NULL AND :MULTIARTICULO ='N' AND :NBULTOS = 0;

CURSOR=CSELNOTCEROMAT SELECT :CODMAT FROM DUAL WHERE :CODMAT IS NULL;
               
CURSOR=CVALCODMAT SELECT 1 DUMMY
                    FROM VDSTOCK STK, VDCONTE CNT
                   WHERE STK.CODMAT = :CODMAT              
                     AND STK.CODMAT = CNT.CODMAT
                     AND ((:MULTIARTICULO ='S' AND CNT.CODUBI != :PULMON)OR :MULTIARTICULO ='N');
					 
CURSOR=CELIMINA00 SELECT CASE WHEN LENGTH(:CODMAT)=20 THEN SUBSTR(:CODMAT,3) ELSE :CODMAT END CODMAT FROM DUAL;	
