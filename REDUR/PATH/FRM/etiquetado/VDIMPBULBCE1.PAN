##############################################################################
#  Módulo  : VDIMPBULBCE1.PAN                                                #
#  Función :                                                                 #
#                                                                            #
#  Autor : FPD                                                               #
#  Fecha : 14-10-14                                                          #
#  Revisador por  :                                                          #
#  Fecha revisión :                                                          #
##############################################################################
TERMINAL DE RADIO
                       
                Terminal      Altura
                _________       _
                                                      |



SOLOQUERY
SELECT=SELECT :CODRECURSO,MAXALT,NVL(:ALTURA,'N') ALTURA FROM VDRECURSO;

NOINSERT
NODELETE
NOUPDATE
NOLOCK


WHERE=ORDER BY CODRECURSO;
PREQUERY=FEJECUTA("CVERTERM","TIENE QUE ESCRIBIR CODIGO DE TERMINAL",
                  "-CVERRESERVANDOSE","SE ESTA GENERANDO UNA SERIE\n\n ESPERE POR FAVOR")

				  
PRECOMMIT=FEJECUTA("-CVERRESERVANDOSE","SE ESTA GENERANDO UNA SERIE\n\n ESPERE POR FAVOR")

CURSOR=CSELTERM SELECT CODRECURSO FROM VDRECURSO WHERE CODRECURSO!='REDUR' AND CODRECURSO NOT LIKE 'PRUEBA%';

CAMPO=CODRECURSO,AUXILIAR,POSTCHANGE=FDESIGNACION("CALTURA","\n TERMINAL NO EXISTE "),COMBOX("CSELTERM")
CAMPO=ALTURA,AUXILIAR,VIRTUAL,TECLA=CR,FPULSATECLAS("F2","F6"),CHECKBOX("N","S")                                            
CAMPO=MAXALT,NOUPDATE,OCULTO,"@L@"
CAMPO=LLEVO,AUXILIAR,NOENTER,OCULTO,"@L@@@@"
CAMPO=TPESO,AUXILIAR,NOENTER,OCULTO,"#,###.#"
CAMPO=CODSERIEASIG,AUXILIAR,OCULTO,"@L@@@@"
CAMPO=TMANIPESPE,AUXILIAR,NOENTER,OCULTO,"_____________________"
CAMPO=NUMALBA,AUXILIAR,OCULTO,"@L@@@@"
CAMPO=CODPREPARACION,AUXILIAR,OCULTO,"@L@@@@@@@"

CURSOR=CVERRESERVANDOSE SELECT :CODRECURSO FROM VDPEDIDOCAB WHERE STATUS BETWEEN VDST.FPECRESERVADO AND VDST.FPECPREPARANDO-1 AND STATUS!=VDST.FPECPDTESTOCK AND STATUS!=VDST.FPECPDTELANZAR;

CURSOR=CCONTRABAJO SELECT :LLEVO FROM VDMOVIM WHERE CODRECURSO=:CODRECURSO AND STATUS BETWEEN VDST.FMOVASIGNADO AND VDST.FMOVACTUALIZA-1 AND TAREA='PEDEMBA';

CURSOR=CVERTERM SELECT :CODRECURSO FROM DUAL WHERE :CODRECURSO IS NOT NULL;

CURSOR=CALTURA SELECT MAXALT
                 FROM VDRECURSO
                WHERE CODRECURSO=:CODRECURSO;

CURSOR=CSELREC SELECT :CODRECURSO FROM DUAL; 
					   
TECLA=SF10,FEJECUTAFORM("VDRECURSO","S","CODRECURSO=:CODRECURSO")


AYUDA=GESTIÓN MANUAL DE BULABANES
ONLINE=     {F1} Ayuda          {F2} Consulta          {F4} Confirmar cambios       {F5} Borrar pantalla
                               {May-F10} Menú                 {Esc} Salir;

