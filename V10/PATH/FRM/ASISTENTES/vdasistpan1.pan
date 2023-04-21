# Módulo   : VDASISPAN.PAN
# Función  : Generación automática de pantallas
#
# Creación : 31-08-2009
# Autor    : FGS
###########################################
# Histórico de cambios:
GENERACION AUTOMATICA DE PANTALLAS

 Autor:    ____  Grupo: _32___________ Comentarios: _256_______________________________________________________________________
 Bloque:   _40________________________   Path: _256____________________________________________________________________________
 Fichero:  _256________________________________________________________________________________________________________________

 POSX: @L@@      WPOSX  @L@@   WLONX  @L@@  WPIXELX  @L@  PLEGADO _  DESPLEGADO _    
 POSY: @L@@      WPOSY  @L@@   WLONY  @L@@  WPIXELY  @L@  INCLUDECSS _256____________________ INCLUDEHTML _256_________________              
 REGPAG: @L@@    WREGPAG: @L@@

 Modo Query: _  _______________ Capitaliza: _  __________ Título:  _1024________________________________________________________
 Soloquery:  _  Tabla:  _32______________ 
 Select:     _1024____________________________________________________________________________________________________



 Where:      _1024_____________________________________________________________________________________________________________
 OrderBy:    _1024_____________________________________________________________________________________________________________
 GroupBy:    _1024_____________________________________________________________________________________________________________
 Ins         _ _1024_________________ => _1024____________________________________________________________________
 Del         _ _1024_________________ => _1024____________________________________________________________________
 Upd         _ _1024_________________ => _1024____________________________________________________________________ 
 Ent         _ _1024_________________ => _1024____________________________________________________________________
 OrIns       _ _1024_________________ => _1024____________________________________________________________________
                                                                                                                    _ Abrir Pantalla
 Ayuda:      _1024________________________________________________________________________________________________  _ Abrir Fichero
 Context:    _1024________________________________________________________________________________________________  
 Teclas:     _1024________________________________________________________________________________________________           
 Online:     _1024________________________________________________________________________________________________
 Adicc:      _1024________________________________________________________________________________________________
|


TABLA=VDTMPBLOQUE

CAMPO=AUTOR
CAMPO=GRUPOBLOQUE,COMBOX("CGRUPOBLOQUE")
CAMPO=COMENTARIO
CAMPO=NBLOQUE,POSTCHANGE=FDESIGNACION("CFICHERO","ERROR GENERANDO NOMBRE DE FICHERO")
CAMPO=PATHBLOQUE,POSTCHANGE=FDESIGNACION("CFICHERO","ERROR GENERANDO NOMBRE DE FICHERO"),COMBOX("CDAMEPATHS")
CAMPO=FICHERO,NOENTER
CAMPO=NUMPOSX,TOOLTIP("Coordenada X en el que comienza la pantalla")
CAMPO=NUMWPOSX,TOOLTIP("Coordenada X en píxeles en el que comienza la pantalla")
CAMPO=NUMWLONX,TOOLTIP("Longitud X en píxeles de la pantalla")
CAMPO=NUMWPIXELX,TOOLTIP("Número de píxeles por columna de la pantalla")
CAMPO=VPLEGADO,CHECKBOX("","S")
CAMPO=VDESPLEGADO,CHECKBOX("","S")
CAMPO=NUMPOSY,TOOLTIP("Coordenada Y en el que comienza la pantalla")
CAMPO=NUMWPOSY,TOOLTIP("Coordenada Y en píxeles en el que comienza la pantalla")
CAMPO=NUMWLONY,TOOLTIP("Longitud Y en píxeles de la pantalla")
CAMPO=NUMWPIXELY,TOOLTIP("Número de píxeles por FILA de la pantalla")
CAMPO=VINCLUDECSS
CAMPO=VINCLUDEHTML
CAMPO=NUMREGPAG
CAMPO=NUMWREGPAG
CAMPO=MODOQUERY,TOOLTIP("Modo de query de la pantalla: A(query), P(query), T(query) o NULO"),POSTCHANGE=FDESIGNACION("CDESMODOQUERY",""),COMBOX("A","P","T")
CAMPO=DESMODOQUERY,AUXILIAR,NOENTER
CAMPO=CAPITALIZA,TOOLTIP("Capitalización del campo U(pper) L(ower) M(ixed)"),POSTCHANGE=FDESIGNACION("CDESCAPITALIZA",""),COMBOX("U","L","M")
CAMPO=DESCAPITALIZA,NOENTER,AUXILIAR
CAMPO=TITULOBLOQUE,TOOLTIP("Título del bloque de datos")
CAMPO=TSOLOQUERY,CHECKBOX("","S")
CAMPO=TTABLA,COMBOX("CSELTABLAS"),COMBOXREGPAG=15
#,POSTCHANGE=FDESIGNACION("CCAMPOSENTER","")
CAMPO=TSELECT,REGPAG=4
CAMPO=TWHERE,TOOLTIP("Texto where de la pantalla, anteponiéndole un signo + lo concatena a la where en fichero de la misma")
CAMPO=TORDERBY,TOOLTIP("Criterio de ordenación de la pantalla")
CAMPO=TGROUPBY,TOOLTIP("Criterio de agrupamiento de la pantalla")
CAMPO=CNOINSERT,TOOLTIP("Si tiene protegido para no INSERT"),POSTCHANGE=FDESIGNACION("CDESCCINSERT",""),CHECKBOX("","S")
CAMPO=PRIVINSERT,TOOLTIP("Privilegios para Insertar registros"),POSTCHANGE=FDESIGNACION("CDESCCINSERT",""),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=DESCCINSERT,AUXILIAR,NOENTER
CAMPO=CNODELETE,TOOLTIP("Si tiene protegido para no DELETE"),POSTCHANGE=FDESIGNACION("CDESCCDELETE",""),CHECKBOX("","S")
CAMPO=PRIVDELETE,TOOLTIP("Privilegios para Insertar registros"),POSTCHANGE=FDESIGNACION("CDESCCDELETE",""),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=DESCCDELETE,AUXILIAR,NOENTER
CAMPO=CNOUPDATE,TOOLTIP("Si tiene protegido para no UPDATE"),POSTCHANGE=FDESIGNACION("CDESCCUPDATE",""),CHECKBOX("","S")
CAMPO=PRIVUPDATE,TOOLTIP("Privilegios para Insertar registros"),POSTCHANGE=FDESIGNACION("CDESCCUPDATE",""),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=DESCCUPDATE,AUXILIAR,NOENTER
CAMPO=CNOENTER,TOOLTIP("Si tiene protegido para no ENTER"),POSTCHANGE=FDESIGNACION("CDESCCNOENTER",""),CHECKBOX("","S")
CAMPO=PRIVNOENTER,TOOLTIP("Privilegios para Insertar registros"),POSTCHANGE=FDESIGNACION("CDESCCNOENTER",""),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=DESCCNOENTER,AUXILIAR,NOENTER
CAMPO=CNOORAINS,TOOLTIP("Si tiene protegido para no ORAINS"),POSTCHANGE=FDESIGNACION("CDESCCORAINS",""),CHECKBOX("","S")
CAMPO=PRIVORAINS,TOOLTIP("Privilegios para Insertar registros"),POSTCHANGE=FDESIGNACION("CDESCCORAINS",""),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=DESCCORAINS,AUXILIAR,NOENTER
CAMPO=FABREPANTALLA,AUXILIAR,CHECKBOX("","S")
CAMPO=FAYUDA,TOOLTIP("Topic en la ayuda de V10 (.HLP)")
CAMPO=FABREFICHERO,AUXILIAR,CHECKBOX("","S")
CAMPO=FCONTEXTUAL,TOOLTIP("Función a ejecutar al pulsar Shift+F10")
CAMPO=FTECLA,TOOLTIP("Funciones programables para puslaciones de teclas especiales")
CAMPO=AYUDAONLINE,MIXED,TOOLTIP("Ayuda online del Bloque. Si se antepone un signo + se concatena a la ayuda online por defecto")
CAMPO=FAUXILIAR,TOOLTIP("Propiedades adiccionales a añadir a la pantalla")
CAMPO=MAXORDEN,AUXILIAR,OCULTO,"@L@@@"
CAMPO=MSJERROR,AUXILIAR,OCULTO,"_4096______"
CAMPO=TEXTOQUERY,AUXILIAR,OCULTO,"_4096_________"
CAMPO=NOMBREVIEW,AUXILIAR,OCULTO,"_1024___________"
CAMPO=TEXTOFICHERO,AUXILIAR,OCULTO,"_65536_______"      
              
CURSOR=CDAMEPATHS SELECT  'I:\V10\PATH\FRM\' FROM DUAL
                    UNION
                  SELECT  'I:\V10\PATH\FRM\'||NVL(:GRUPOBLOQUE,'DEFECTO')||'\' FROM DUAL;
                  
CURSOR=CGENERATEXTOFICHERO DECLARE
                           TEXTOCAMPOS VARCHAR2(32767):=NULL;
                           TITULOSCAMPOS VARCHAR2(16384):=NULL;
                           FORMATOCAMPOS VARCHAR2(16384):=NULL;
                           LISTACAMPOS VARCHAR2(16384):=NULL;
                           CABECERAFICHERO VARCHAR2(32767):=NULL;
                           CUERPOFICHERO VARCHAR2(32767):=NULL;       
                           LON NUMBER(3);                    
                           CURSOR C1 IS SELECT * FROM VDTMPCAMPOS WHERE MIUSER=VDUSER.GETUSER AND NBLOQUE=:NBLOQUE AND INCLUIR='S' ORDER BY ORDEN;
                         BEGIN
                          CABECERAFICHERO := '# Módulo   : ' || :NBLOQUE || '.PAN' || CHR(10) ||
                                             '# Función  : ' || :COMENTARIO || CHR(10) ||
                                             '#' || CHR(10) ||
                                             '# Creación : ' || TO_CHAR(TO_DATE(VD.FECHASYS,'J'),'DD-MM-YYYY') || CHR(10) ||
                                             '# Autor    : ' || :AUTOR || CHR(10) ||
                                             '# Fichero generado por el Asistente de Generación de Pantallas V10 ' || CHR(10) ||
                                             '###########################################' || CHR(10) ||
                                             '# Histórico de cambios:' || CHR(10);
                           
                           IF :TTABLA IS NOT NULL THEN CUERPOFICHERO:=CUERPOFICHERO || 'TABLA=' || :TTABLA || CHR(10); END IF;                       
                           IF :TSOLOQUERY = 'S' THEN 
                             CUERPOFICHERO:=CUERPOFICHERO || 'SOLOQUERY' || CHR(10); 
                             IF LENGTH(:TSELECT)>0 THEN
                               :TEXTOQUERY := RTRIM(:TSELECT) || ';';
                               CUERPOFICHERO:=CUERPOFICHERO || 'SELECT = ' || :TEXTOQUERY || CHR(10); 
                             END IF;
                           ELSE 
                             CUERPOFICHERO:= CUERPOFICHERO || 'PREINSERT=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")' || CHR(10)
                                                           || 'PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")' || CHR(10);
                             CUERPOFICHERO:=   CUERPOFICHERO || CHR(10) || 'CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;' || CHR(10);
                           END IF;
                           IF :TWHERE IS NOT NULL THEN
                               CUERPOFICHERO:=CUERPOFICHERO||'WHERE='||:TWHERE||';' || CHR(10);
                            END IF;
                           IF :TORDERBY IS NOT NULL THEN
                               CUERPOFICHERO:=CUERPOFICHERO||'ORDERBY='||:TORDERBY||';' || CHR(10);
                            END IF;
                           IF :TGROUPBY IS NOT NULL THEN
                               CUERPOFICHERO:=CUERPOFICHERO||'GROUPBY='||:TGROUPBY||';' || CHR(10);
                            END IF;
                           IF NVL(:NUMWPOSX,0)>0 THEN CUERPOFICHERO:=CUERPOFICHERO || 'WPOSX=' || :NUMWPOSX || CHR(10); END IF;
                           IF NVL(:NUMWPOSY,0)>0 THEN CUERPOFICHERO:=CUERPOFICHERO || 'WPOSY=' || :NUMWPOSY || CHR(10); END IF;
                           IF NVL(:NUMWLONX,0)>0 THEN CUERPOFICHERO:=CUERPOFICHERO || 'WLONX=' || :NUMWLONX || CHR(10); END IF;
                           IF NVL(:NUMWLONY,0)>0 THEN CUERPOFICHERO:=CUERPOFICHERO || 'WLONY=' || :NUMWLONY || CHR(10); END IF;
                           IF NVL(:NUMWPIXELX,0)>0 THEN CUERPOFICHERO:=CUERPOFICHERO || 'WPIXELX=' || :NUMWPIXELX || CHR(10); END IF;
                           IF NVL(:NUMWPIXELY,0)>0 THEN CUERPOFICHERO:=CUERPOFICHERO || 'WPIXELY=' || :NUMWPIXELY || CHR(10); END IF;
                           IF NVL(:NUMWREGPAG,0)>0 THEN CUERPOFICHERO:=CUERPOFICHERO || 'WREGPAG=' || :NUMWREGPAG || CHR(10); END IF;
                           IF :VPLEGADO = 'S' THEN CUERPOFICHERO:=CUERPOFICHERO || 'WPLEGADO' || CHR(10); END IF;
                           IF :VDESPLEGADO = 'S' THEN CUERPOFICHERO:=CUERPOFICHERO || 'WDESPLEGADO' || CHR(10); END IF;
                           IF :VINCLUDECSS IS NOT NULL THEN CUERPOFICHERO:=CUERPOFICHERO || 'INCLUDECSS="' || :VINCLUDECSS || '"' || CHR(10); END IF;
                           IF :VINCLUDEHTML IS NOT NULL THEN CUERPOFICHERO:=CUERPOFICHERO || 'INCLUDEHTML="' || :VINCLUDEHTML || '"' || CHR(10); END IF;                            
                           TITULOSCAMPOS:=TITULOSCAMPOS || NVL(:TITULOBLOQUE,'TITULO INDEFINIDO') || CHR(10);
                           FOR I IN C1 LOOP  
                              IF NVL(I.COCULTO,'N')<>'S' THEN  
                                LON:=LENGTH(I.FORMATOCAMPO);
                                TITULOSCAMPOS := TITULOSCAMPOS || RPAD(I.NCAMPO,LON,' ') || ' ';   
                                FORMATOCAMPOS := FORMATOCAMPOS || I.FORMATOCAMPO || ' ';
                              END IF;                              
                              LISTACAMPOS:= LISTACAMPOS || 'CAMPO=' || I.NCAMPO;
                              
                              IF NVL(I.COCULTO,'N')='S' THEN
                              	LISTACAMPOS:= LISTACAMPOS  || ',' || 'OCULTO';
                              	IF NVL(I.CVIRTUAL,'N')<>'S' THEN 
                              	  LISTACAMPOS:= LISTACAMPOS  || ',' || '"'||I.FORMATOCAMPO||'"';
                              	END IF;
                              END IF;
                              IF NVL(I.CAUXILIAR,'N')='S' THEN 
                                LISTACAMPOS:= LISTACAMPOS  || ',' || 'AUXILIAR';
                              END IF;
                              IF NVL(I.CVIRTUAL,'N')='S' THEN
                                LISTACAMPOS:= LISTACAMPOS  || ',' || 'VIRTUAL';
                                IF I.CCVIRTUAL IS NOT NULL THEN
                                  LISTACAMPOS:= LISTACAMPOS || '("'|| I.CCVIRTUAL ||'")';
                                END IF;
                              END IF;                              
                              IF I.CPROTECT IS NOT NULL THEN
                               LISTACAMPOS:= LISTACAMPOS || ',PROTECT("'|| I.CPROTECT ||'")';
                              END IF;                             
                              IF I.CPREFIJO IS NOT NULL THEN
                               LISTACAMPOS:= LISTACAMPOS || ',PREFIJO='||I.CPREFIJO;
                              END IF;                              
                              IF I.CTITULO IS NOT NULL THEN
                               LISTACAMPOS:= LISTACAMPOS || ',TITULO("'|| I.CTITULO ||'")';                              
                              END IF;
                              IF NVL(I.CNOENTER,'N')='S' THEN
                                LISTACAMPOS:= LISTACAMPOS || ',NOENTER';
                                IF I.PRIVNOENTER IS NOT NULL THEN
                                  LISTACAMPOS:= LISTACAMPOS || '("' || I.PRIVNOENTER || '")';
                                END IF;
                              END IF;                              
                              IF NVL(I.CNOUPDATE,'N')='S' THEN
                                LISTACAMPOS:= LISTACAMPOS || ',NOUPDATE';
                                IF I.PRIVNOUPDATE IS NOT NULL THEN
                                  LISTACAMPOS:= LISTACAMPOS || '("' || I.PRIVNOUPDATE || '")';
                                END IF;
                              END IF;
                              IF I.CCHECKBOX IS NOT NULL THEN
                                 LISTACAMPOS:= LISTACAMPOS || ',CHECKBOX(' || I.CCHECKBOX || ')';
                              END IF;
                              IF I.CTOOLTIP IS NOT NULL THEN 
                                LISTACAMPOS:= LISTACAMPOS || ',TOOLTIP("' || I.CTOOLTIP || '")';
                              END IF;
                              IF I.CCAPITALIZA IS NOT NULL THEN
                              	IF NVL(I.CCAPITALIZA,'-')='U' THEN
                              	  LISTACAMPOS:= LISTACAMPOS || ',UPPER';
                              	END IF;
                              	IF NVL(I.CCAPITALIZA,'-')='M' THEN
                              	  LISTACAMPOS:= LISTACAMPOS || ',MIXED';
                              	END IF;
                              	IF NVL(I.CCAPITALIZA,'-')='L' THEN
                              	  LISTACAMPOS:= LISTACAMPOS || ',LOWER';
                              	END IF;                              	
                              END IF;
                              LISTACAMPOS:= LISTACAMPOS || CHR(10);
                           END LOOP;
                           FORMATOCAMPOS := FORMATOCAMPOS || CHR(10) || '|';
                           TEXTOCAMPOS:= TITULOSCAMPOS || CHR(10) || FORMATOCAMPOS || CHR(10);
                           :TEXTOFICHERO := CABECERAFICHERO ||  TEXTOCAMPOS || CHR(10) || CUERPOFICHERO || CHR(10) || '# LISTA DE CAMPOS DE LA PANTALLA' || CHR(10) || LISTACAMPOS ||  CHR(10) ||  '# PARTE PERSONALIZADA DE LA PANTALLA ';
                         END;@
                         
                         

CURSOR=CDAMENOMBREVIEW SELECT 'TMPCAMPOS' || VDUSER.GETUSER NOMBREVIEW,NULL MSJERROR,
                       RTRIM(:TSELECT)||(CASE WHEN :TGROUPBY IS NULL THEN NULL ELSE ' GROUP BY '||:TGROUPBY END) TEXTOQUERY FROM DUAL; 
                  
CURSOR=CANALIZASQL DECLARE
                     SENTENCIACREAR VARCHAR2(4096):=NULL;
                     SENTENCIABORRAR VARCHAR2(4096):=NULL;
                   BEGIN   
                     SENTENCIABORRAR:='DROP VIEW ' || :NOMBREVIEW;
                     SENTENCIACREAR:='CREATE VIEW ' || :NOMBREVIEW || ' AS ' || :TEXTOQUERY;
  
                     BEGIN
                       EXECUTE IMMEDIATE(SENTENCIABORRAR);
                       EXCEPTION WHEN OTHERS THEN NULL;
                     END;
  
                     EXECUTE IMMEDIATE(SENTENCIACREAR);
                     EXCEPTION WHEN OTHERS THEN
                      :MSJERROR := 'ERROR ' || SQLCODE|| '- ' || SQLERRM;
                  END;@
                  
CURSOR=CBORRAVIEW DECLARE
                  BEGIN
                     EXECUTE IMMEDIATE('DROP VIEW ' || :NOMBREVIEW);
                     EXCEPTION WHEN OTHERS THEN
                      :MSJERROR := 'ERROR ' || SQLCODE|| '- ' || SQLERRM;
                  END;@                  

CURSOR=CHAYERROR SELECT :MSJERROR FROM DUAL WHERE :MSJERROR IS NOT NULL;

CURSOR=CCAMPOSENTER SELECT DECODE(:TSOLOQUERY,'S',1,0) TSELECT__ENTER FROM DUAL;
 
CURSOR=CFICHERO SELECT :PATHBLOQUE || :NBLOQUE || '.PAN' FICHERO FROM DUAL;

CURSOR=CGRUPOBLOQUE SELECT DISTINCT GRUPOBLOQUE FROM VDDEFBLOQUE;
CURSOR=CLISTAPRIV SELECT '"'||PRIVILEGIO||'"',COMENTARIO FROM VDPRIVILEGIO ORDER BY PRIVILEGIO;

CURSOR=CSELTABLAS SELECT TAB.TABLE_NAME,SUBSTR(COM.COMMENTS,1,150) FROM USER_TABLES TAB, USER_TAB_COMMENTS COM  
                              WHERE COM.TABLE_NAME(+)=TAB.TABLE_NAME AND
                                    (TAB.TABLE_NAME LIKE NVL(:TTABLA,'%') OR (INSTR(NVL(:TTABLA,'-'),'%')=0)) 
                              ORDER BY TAB.TABLE_NAME;
                            
CURSOR=CNBLOQUENULL SELECT :NBLOQUE FROM DUAL WHERE :NBLOQUE IS NULL;

CURSOR=CDEFBLOQUE SELECT NBLOQUE FROM VDDEFBLOQUE WHERE NBLOQUE=:NBLOQUE; 

CURSOR=CUPDDEFBLOQUE UPDATE VDDEFBLOQUE SET 
                              TIPOPANTALLA='F',GRUPOBLOQUE=NVL(:GRUPOBLOQUE,GRUPOBLOQUE), NUMPOSX=:NUMPOSX,NUMPOSY=:NUMPOSY,NUMREGPAG=:NUMREGPAG,AYUDAONLINE=:AYUDAONLINE,TITULOBLOQUE=:TITULOBLOQUE,
                              MODOQUERY=:MODOQUERY,
                              FCONTEXTUAL=:FCONTEXTUAL,
                              FTECLA=:FTECLA,
                              CAPITALIZA=:CAPITALIZA,
                              TWHERE=:TWHERE,TORDERBY=:TORDERBY,
                              CNOINSERT=:CNOINSERT,PRIVINSERT=:PRIVINSERT,
                              CNODELETE=:CNODELETE,PRIVDELETE=:PRIVDELETE,
                              CNOENTER=:CNOENTER,PRIVNOENTER=:PRIVNOENTER,CNOUPDATE=:CNOUPDATE,PRIVUPDATE=:PRIVUPDATE,CNOORAINS=:CNOORAINS,PRIVORAINS=:PRIVORAINS,
                              FAYUDA=:FAYUDA,FAUXILIAR=:FAUXILIAR,CODOPEMODIF=VDUSER.GETUSER,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS 
                           WHERE NBLOQUE =:NBLOQUE;

CURSOR=CINSDEFBLOQUE INSERT INTO VDDEFBLOQUE(NBLOQUE, GRUPOBLOQUE, TIPOPANTALLA,NUMPOSX, NUMPOSY, NUMREGPAG,AYUDAONLINE, TITULOBLOQUE, MODOQUERY, 
                             FCONTEXTUAL, FTECLA, CAPITALIZA,TWHERE,TORDERBY,CNOINSERT,PRIVINSERT,CNODELETE, PRIVDELETE,CNOENTER,PRIVNOENTER,CNOUPDATE, 
                             PRIVUPDATE, CNOORAINS, PRIVORAINS,FAYUDA, FAUXILIAR, CODOPEMODIF,FECMODIF, HORAMODIF, CODCOMEN) 
                         (SELECT :NBLOQUE,:GRUPOBLOQUE,'F',:NUMPOSX,:NUMPOSY,:NUMREGPAG,:AYUDAONLINE,:TITULOBLOQUE,:MODOQUERY,
                                 :FCONTEXTUAL,:FTECLA,:CAPITALIZA,:TWHERE,:TORDERBY,:CNOINSERT,:PRIVINSERT,:CNODELETE,:PRIVDELETE,:CNOENTER,:PRIVNOENTER,:CNOUPDATE,
                                 :PRIVUPDATE,:CNOORAINS,:PRIVORAINS,:FAYUDA,:FAUXILIAR,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,0 
                                               FROM DUAL);                       
             
                            
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

CURSOR=CDAMEMAXORDEN SELECT NVL(MAX(ORDEN),0) MAXORDEN FROM VDTMPCAMPOS WHERE MIUSER=VDUSER.GETUSER AND NBLOQUE=:NBLOQUE;

CURSOR=CTABLA SELECT :TSOLOQUERY FROM DUAL WHERE NVL(:TSOLOQUERY,'N')<>'S';

CURSOR=CABREPANTALLA SELECT :FABREPANTALLA FROM DUAL WHERE NVL(:FABREPANTALLA,'N')='S';

CURSOR=CINSCAMPOSTABLAS DECLARE
                          CURSOR C1 IS SELECT VDUSER.GETUSER,:NBLOQUE,'S' INCLUIR,COL.COLUMN_NAME,:MAXORDEN+(ROWNUM*10) SUORDEN,
                                                DECODE(COL.COLUMN_NAME,'FECMODIF','¿D-MM-Y.YY',
                                                      DECODE(DATA_TYPE,'VARCHAR2',DECODE(SIGN(DATA_LENGTH-22),1,'_'||RPAD(DATA_LENGTH,21,'_'),RPAD('_',DATA_LENGTH,'_')),
                                                                       'TIMESTAMP(6)','________________________',
                                                                       'NUMBER',DECODE(DATA_SCALE,0,'@'||RPAD('L',DATA_PRECISION-1,'@'),
                                                                                                    '#L'||RPAD('#',NVL(DATA_PRECISION,17)-2,'#')||'.'||RPAD('#',DATA_SCALE,'#')))) FORMATOCAMPO,
                                                COL.COLUMN_NAME TITULO,NULL PREFIJO,NULL CVIRTUAL,NULL CCVRTUAL,NULL COCULTO,NULL CPROTECT,NULL CNOENTER,
                                                NULL PRIVNOENTER,NULL CNOUPDATE,NULL PRIVNOUPDATE,NULL CCHECKBOX,NULL CAUXILIAR,NULL CCAPITALIZA,COMMENTS
                                                                                                FROM                                                                                                 
                                                                                                (SELECT COL.*,COM.COMMENTS 
                                                                                                 FROM ALL_TAB_COLUMNS COL,USER_COL_COMMENTS COM
                                                                                                  WHERE COL.TABLE_NAME = DECODE(NVL(:TSOLOQUERY,'N'),'S',:NOMBREVIEW,:TTABLA) AND
                                                                                                        COM.TABLE_NAME(+) = COL.TABLE_NAME AND
                                                                                                        COM.COLUMN_NAME(+) = COL.COLUMN_NAME AND
                                                                                                        OWNER=USER                                                
                                                                                                  ORDER BY COL.COLUMN_ID) COL;                        
                        BEGIN
													FOR I IN C1 LOOP
													  IF SUBSTR(I.COLUMN_NAME,1,3)='FEC' AND LENGTH(I.FORMATOCAMPO)=7 THEN
													     I.FORMATOCAMPO:= '¿D-MM-Y.YY';
													  END IF;
													  INSERT INTO VDTMPCAMPOS  VALUES I;
													END LOOP;		
                        END;@   
                    

CURSOR=CTABLAOK SELECT :TTABLA FROM DUAL WHERE (NVL(:TSOLOQUERY,'N')='S' AND LENGTH(RTRIM(:TSELECT))>0) OR :TTABLA IS NOT NULL;                                                                                               


TECLA=F10,FEJECUTAFORM("VDASISTPAN2","S","","","TTABLA=:TABLE_NAME","SELECCION DE TABLA","S")
TECLA=F8,FEJECUTA("CTABLAOK","DEBE INFORMAR TABLA O SELECT SI ES SOLOQUERY",
                  "CDAMEMAXORDEN","",
                  FIF("CTABLA","CINSCAMPOSTABLAS",
                               FEJECUTA("CDAMENOMBREVIEW","ERROR EN CDAMENOMBREVIEW",
                                        "CANALIZASQL","ERROR EN CANALIZASQL",
                                        "-CHAYERROR",":MSJERROR",
                                        "CINSCAMPOSTABLAS","ERROR EN CINSCAMPOSTABLAS",
                                        "CBORRAVIEW","ERROR EN CBORRAVIEW",
                                        "-CHAYERROR",":MSJERROR")),":MSJERROR",
                  FCOMMIT,"",
                  FPULSATECLAS("F6","F3","F2"))
# %FFAILURE,"POR FALTA DE TIEMPO NO SE GENERA EL FICHERO\n FALTA PROGRAMAR EL TRIGER FFICHEROBLOQUE"
# GENERA EL FICHERO
# AÑADIR O ACTUALIZAR VDDEFBLOQUE
# GENERAR EL FICHERO MEDIANTE UN TRIGGER, BUSCA DE TABLA VDTMPCAMPOS CON INCLUIR='S', ORDENADO POR ORDEN
# AÑADIR CSELMODIF, Y SI ES INSERT O UPDATE (NO ES NO ...)                  
TECLA=F7, FEJECUTA("-CNBLOQUENULL","ERROR\n NOMBRE DE BLOQUE ES NULO",
                   "CTABLAOK","DEBE INFORMAR TABLA O SELECT SI ES SOLOQUERY",
                   FIF("CDEFBLOQUE","CUPDDEFBLOQUE","CINSDEFBLOQUE"),"ERROR AL INSERTAR/ACTUALIZAR EN VDDEFBLOQUE",
                   FCOMMIT,"",
                   "CGENERATEXTOFICHERO","ERROR EN CGENERATEXTOFICHERO",
                   FFICHEROBLOQUE("FICHERO","TEXTOFICHERO","FABREFICHERO","FABREPANTALLA","NBLOQUE"),":V10ERROR",
                   %FFAILURE,"FICHERO GENERADO")                 
BOTON=P2,855,217,110,30,"Incluir Campos >>",NO,F8,"Inserta Campos en la lista de campos"
BOTON=P2,825,400,150,35,"Generar Fichero",NO,F7,"Genera el fichero e inserta en la tabla de propiedades de bloque por defecto"
BOTON=P3,855,178,35,35,"Tablas",mizoom.png,F10,"Buscar nombre de tabla",ESTILOCSS="background-color:transparent;border-width:0px"
