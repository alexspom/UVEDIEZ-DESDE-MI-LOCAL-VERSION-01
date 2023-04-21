# Módulo   : VDDEFBLOQUEINFO.PAN
# Función  : Mantenimiento detallado de propiedades por defecto de bloques
#
# Creación : 18-12-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
CARACTERISTICAS POR DEFECTO DEl BLOQUE DE DATOs

 Bloque:     _40_____________________________________ Grupo: _32_____________________ Tipo: _   

 PosX:       @L@@  
 PosY:       @L@@  
 REGPAG:     @L@@    

 Modo Query: _ ______________________

 Capitaliza: _ ______________________

 Título:     _1024________________________________________________________________________________________________

 Where:      _1024________________________________________________________________________________________________

 OrderBy:    _1024________________________________________________________________________________________________

 Ins         _ _1024_________________ => _1024____________________________________________________________________
 Del         _ _1024_________________ => _1024____________________________________________________________________
 Upd         _ _1024_________________ => _1024____________________________________________________________________ 
 Ent         _ _1024_________________ => _1024____________________________________________________________________
 OrIns       _ _1024_________________ => _1024____________________________________________________________________

 Ayuda:      _1024________________________________________________________________________________________________
 Context:    _1024________________________________________________________________________________________________  
 Teclas:     _1024________________________________________________________________________________________________           

 Online:     _1024________________________________________________________________________________________________

 Adicc:      _1024________________________________________________________________________________________________

 Ult.Modificación: _32________ ¿D-MM-Y.YY ________
|


TABLA=VDDEFBLOQUE

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")


CAMPO=NBLOQUE,NOUPDATE
CAMPO=GRUPOBLOQUE
CAMPO=TIPOPANTALLA,TOOLTIP("Tipo de pantallas a las que se aplican los defectos puede ser F(orms) R(adios) o A(mbos)")
CAMPO=NUMPOSX,TOOLTIP("Coordenada X en el que comienza la pantalla")
CAMPO=NUMPOSY,TOOLTIP("Coordenada Y en el que comienza la pantalla")
CAMPO=NUMREGPAG,TOOLTIP("Número de registros de la pantalla")
CAMPO=MODOQUERY,TOOLTIP("Modo de query de la pantalla: A(query), P(query), T(query) o NULO"),POSTCHANGE=FDESIGNACION("CDESMODOQUERY","")
CAMPO=DESMODOQUERY,NOENTER,AUXILIAR
CAMPO=CAPITALIZA,TOOLTIP("Capitalización del campo U(pper) L(ower) M(ixed)"),POSTCHANGE=FDESIGNACION("CDESCAPITALIZA","")
CAMPO=DESCAPITALIZA,NOENTER,AUXILIAR
CAMPO=TITULOBLOQUE,TOOLTIP("Título del bloque de datos")
CAMPO=TWHERE,TOOLTIP("Texto where de la pantalla, anteponiéndole un signo + lo concatena a la where en fichero de la misma")
CAMPO=TORDERBY,TOOLTIP("Criterio de ordenación de la pantalla")

CAMPO=CNOINSERT,TOOLTIP("Si tiene protegido para no INSERT"),POSTCHANGE=FDESIGNACION("CDESCCINSERT",""),CHECKBOX("","S")
CAMPO=PRIVINSERT,TOOLTIP("Privilegios para Insertar registros"),POSTCHANGE=FDESIGNACION("CDESCCINSERT",""),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=DESCCINSERT,NOENTER,AUXILIAR
CAMPO=CNODELETE,TOOLTIP("Si tiene protegido para no DELETE"),POSTCHANGE=FDESIGNACION("CDESCCDELETE",""),CHECKBOX("","S")
CAMPO=PRIVDELETE,TOOLTIP("Privilegios para Insertar registros"),POSTCHANGE=FDESIGNACION("CDESCCDELETE",""),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=DESCCDELETE,NOENTER,AUXILIAR
CAMPO=CNOUPDATE,TOOLTIP("Si tiene protegido para no UPDATE"),POSTCHANGE=FDESIGNACION("CDESCCUPDATE",""),CHECKBOX("","S")
CAMPO=PRIVUPDATE,TOOLTIP("Privilegios para Insertar registros"),POSTCHANGE=FDESIGNACION("CDESCCUPDATE",""),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=DESCCUPDATE,NOENTER,AUXILIAR
CAMPO=CNOENTER,TOOLTIP("Si tiene protegido para no ENTER"),POSTCHANGE=FDESIGNACION("CDESCCNOENTER",""),CHECKBOX("","S")
CAMPO=PRIVNOENTER,TOOLTIP("Privilegios para Insertar registros"),POSTCHANGE=FDESIGNACION("CDESCCNOENTER",""),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=DESCCNOENTER,NOENTER,AUXILIAR
CAMPO=CNOORAINS,TOOLTIP("Si tiene protegido para no ORAINS"),POSTCHANGE=FDESIGNACION("CDESCCORAINS",""),CHECKBOX("","S")
CAMPO=PRIVORAINS,TOOLTIP("Privilegios para Insertar registros"),POSTCHANGE=FDESIGNACION("CDESCCORAINS",""),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=DESCCORAINS,NOENTER,AUXILIAR
CAMPO=FAYUDA,TOOLTIP("Topic en la ayuda de V10 (.HLP)")
CAMPO=FCONTEXTUAL,TOOLTIP("Función a ejecutar al pulsar Shift+F10")
CAMPO=FTECLA,TOOLTIP("Funciones programables para puslaciones de teclas especiales")
CAMPO=AYUDAONLINE,MIXED,TOOLTIP("Ayuda online del Bloque. Si se antepone un signo + se concatena a la ayuda online por defecto")
CAMPO=FAUXILIAR,TOOLTIP("Propiedades adiccionales a añadir a la pantalla")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CLISTAPRIV SELECT '"'||PRIVILEGIO||'"',COMENTARIO FROM VDPRIVILEGIO ORDER BY PRIVILEGIO;

CURSOR=CDESMODOQUERY SELECT DECODE(:MODOQUERY,'A','AQUERY',
                                              'P','PQUERY', 
                                              'T','TQUERY', NULL) DESMODOQUERY FROM DUAL;
                                              
CURSOR=CDESCAPITALIZA SELECT DECODE(:CAPITALIZA,'U','UPPER',
                                                'L','LOWER',
                                                'M','MIXED',NULL) DESCAPITALIZA FROM DUAL;      
                                                
CURSOR=CDESCCINSERT SELECT DECODE(:CNOINSERT, 'S','NOINSERT',NULL) || 
                           DECODE(:CNOINSERT, 'S',
                             DECODE( :PRIVINSERT,NULL,NULL,
                                DECODE(LENGTH(:PRIVINSERT),0,NULL,',(') ||                                                                                       
                                DECODE(LENGTH(:PRIVINSERT),0,NULL,:PRIVINSERT) ||                                                                                       
                                DECODE(LENGTH(:PRIVINSERT),0,NULL,')')),NULL) DESCCINSERT FROM DUAL;
  
CURSOR=CDESCCDELETE SELECT DECODE(:CNODELETE, 'S','NODELETE',NULL) || 
                           DECODE(:CNODELETE, 'S',
                             DECODE( :PRIVDELETE,NULL,NULL,
                                DECODE(LENGTH(:PRIVDELETE),0,NULL,',(') ||                                                                                       
                                DECODE(LENGTH(:PRIVDELETE),0,NULL,:PRIVDELETE) ||                                                                                       
                                DECODE(LENGTH(:PRIVDELETE),0,NULL,')')),NULL) DESCCDELETE FROM DUAL;
  
  
CURSOR=CDESCCUPDATE SELECT DECODE(:CNOUPDATE, 'S','NOUPDATE',NULL) || 
                           DECODE(:CNOUPDATE, 'S',
                             DECODE( :PRIVUPDATE,NULL,NULL,
                                DECODE(LENGTH(:PRIVUPDATE),0,NULL,',(') ||                                                                                       
                                DECODE(LENGTH(:PRIVUPDATE),0,NULL,:PRIVUPDATE) ||                                                                                       
                                DECODE(LENGTH(:PRIVUPDATE),0,NULL,')')),NULL) DESCCUPDATE FROM DUAL; 
                           
CURSOR=CDESCCNOENTER SELECT DECODE(:CNOENTER, 'S','NOENTER',NULL) || 
                            DECODE(:CNOENTER, 'S',
                              DECODE( :PRIVNOENTER,NULL,NULL,
                                DECODE(LENGTH(:PRIVNOENTER),0,NULL,',(') ||                                                                                       
                                DECODE(LENGTH(:PRIVNOENTER),0,NULL,:PRIVNOENTER) ||                                                                                       
                                DECODE(LENGTH(:PRIVNOENTER),0,NULL,')')),NULL) DESCCNOENTER FROM DUAL;                                             
                                                    

CURSOR=CDESCCORAINS SELECT DECODE(:CNOORAINS, 'S','NOORAINS',NULL) || 
                           DECODE(:CNOORAINS, 'S',
                              DECODE( :PRIVORAINS,NULL,NULL,
                                DECODE(LENGTH(:PRIVORAINS),0,NULL,',(') ||                                                                                       
                                DECODE(LENGTH(:PRIVORAINS),0,NULL,:PRIVORAINS) ||                                                                                       
                                DECODE(LENGTH(:PRIVORAINS),0,NULL,')')),NULL) DESCCORAINS FROM DUAL;   
                                
CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;





