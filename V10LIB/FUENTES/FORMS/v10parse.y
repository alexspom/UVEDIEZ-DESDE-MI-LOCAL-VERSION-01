/*
* Módulo : V10PARSE.Y
* Objeto:  Analizador sintactico de formularios
*
*
* Autor  : Eduardo Alsina Alvarez
* Fecha  : 08-08-2007

* MODIFICACIONES
* ---------------------------
*/
%token PINTADO_PANTALLA
%token OPMENU
%token TEXTO_SQL
%token TEXTO_TITULO
%token TEXTO_ONLINE
%token PREINSERT
%token POSTINSERT
%token PREUPDATE
%token POSTUPDATE
%token PREDELETE
%token POSTDELETE
%token PREQUERY
%token POSTQUERY
%token FINQUERY
%token PREREGISTRO
%token POSTREGISTRO
%token PREBLOQUE
%token POSTBLOQUE
%token PREFORM
%token POSTFORM
%token PRECOMMIT
%token POSTCOMMIT
%token PREROLLBACK
%token POSTROLLBACK
%token BEGINBLOQUE
%token BEGINBLOQUEFRM
%token BEGINBLOQUEPAN
%token ENDBLOQUE
%token PADRE
%token TABLA
%token EXTRAPARSER
%token AYUDA
%token ONLINE
%token POSX
%token POSY
%token LEXCOLOR
%token TITULO
%token REGPAG
%token CAMPO
%token TECLA
%token CONTEXTUAL
%token FTRIGER
%token WHERE
%token ORDERBY
%token GROUPBY
%token HAVING
%token SELECT
%token CURSOR
%token NOINSERT
%token NOORAINS
%token NOORADEL
%token NOUPDATE
%token NODELETE
%token NOCOMMIT
%token UPDATE
%token INSERT
%token PDELETE
%token SICOMMIT
%token NOQUERY
%token NOLOCK
%token AQUERY
%token PQUERY
%token TQUERY
%token SOLOQUERY
%token TIMEOUT
%token NOENTER
%token NOINPUT
%token AUTOENTER
%token UPPER
%token LOWER
%token MIXED
%token AUXILIAR
%token VIRTUAL
%token OCULTO
%token LISTA
%token NOPREF
%token PREFIJO
%token SCAN
%token AUTOTRANSMIT
%token POSTCHANGE
%token PREFIELD
%token POSTFIELD
%token PROTECT
%token DISPLAY
%token PREPINTA
%token POSTPINTA
%token ONPINTA
%token TRADUCIBLE
%token TOOLTIP
%token FUNTOOLTIP
%token BOTON
%token BOTONERA
%token NOROWID
%token TNULL
%token IDENTIFICADOR
%token LEXCADENA
%token NUMERO
%token LEXEOF
%token CHECKBOX
%token ONCLICK
%token ONRIGHTCLICK
%token ONCENTERCLICK
%token ONMOUSEOVER
%token ONMOUSEOUT
%token ONDBCLICK
%token ONMOUSEMOVE
%token NEGATIVO
%token TITULOCAMPO
%token COMBOX
%token COMBOXINDEX
%token COMBOXREGPAG
%token CONVIERTE
%token WPOSX
%token WPOSY
%token WLONX
%token WLONY
%token WREGPAG
%token WPIXELX
%token WPIXELY		
%token INCLUDECSS
%token INCLUDEHTML		
%token ESTILOCSS	
%token COMBOXMULTIPLE	
%token WFRAME	 
%token COMBOXREADONLY
%token WPLEGADO
%token WDESPLEGADO
%token WGRAFICA
%token INCLUDEFICHEROCSS
%token INCLUDETDCSS
%token WMARCOFRAME
%token WMARCOPESTANNA
%token WSINMARCO
%token BOTONOCULTO
%token BOTONDISABLED
%token INCLUDEFICHEROHTML
%token PRETECLA
%token POSTTECLA
%token AJAX
%token SIDEBAROCULTO
%token SIDEBARVISIBLE
%token COMPONENTE

%start modulo
%union {
         char *cad;
         int  entero;
         double doble;
         struct {
             void *ptr;
             int  tipo;
             int protegido;
           } dato;

}
%{
#include "v10form.h"
#include "V10forparseaux.h"
#define INITIAL 0
#define SPINTADO 1
#define STEXTOSQL 2
#define SONLINE   3
#define STITULO   4
#define SOPMENU   5
static char buffer[10*MAXCADENA];
%}
%%
modulo : lista_frm |
         menu |
         cuerpo_bloque  {if (funcionparsebloque) funcionparsebloque(bloqueparse);
                         if (terminabloque(bloqueparse)) return(-1);
                         forparse->nbloques++;
                         enbloque=0;
                         };
lista_frm : definidor_frm lista_frm |
                       ;

definidor_frm : definidor_campo |
                triger_form |
                INCLUDECSS   '=' LEXCADENA	 {strcpy(forparse->includecss,$3.cad); free($3.cad);} |
                INCLUDEFICHEROCSS '=' LEXCADENA	 {strcpy(forparse->includeficherocss,$3.cad); free($3.cad);} |                       
                INCLUDEHTML '=' LEXCADENA	 {strcpy(forparse->includehtml,$3.cad); free($3.cad);} |           
                INCLUDEFICHEROHTML '=' LEXCADENA	 {strcpy(forparse->includeficherohtml,$3.cad); free($3.cad);} |                                
                definidor_bloque;

triger_form : PREFORM '=' definidor_triger {if (forparse->preform) liberatriger(forparse->preform);
                                            forparse->preform=$3.dato.ptr;} |
               POSTFORM '=' definidor_triger {if (forparse->postform) liberatriger(forparse->postform);
                                              forparse->postform=$3.dato.ptr;} |
               PRECOMMIT '=' definidor_triger {if (forparse->precommit) liberatriger(forparse->precommit);
                                               forparse->precommit=$3.dato.ptr;} |
               POSTCOMMIT '=' definidor_triger {if (forparse->postcommit) liberatriger(forparse->postcommit);
                                                forparse->postcommit=$3.dato.ptr;}|
               PREROLLBACK '=' definidor_triger {if (forparse->prerollback) liberatriger(forparse->prerollback);
                                                 forparse->prerollback=$3.dato.ptr;} |
               POSTROLLBACK '=' definidor_triger {if (forparse->postrollback) liberatriger(forparse->postrollback);
                                                  forparse->postrollback=$3.dato.ptr;};

unacadena_parser : LEXCADENA {quitacomillas(&$$.cad,$1.cad);free($1.cad);} |
                LEXCADENA cadena_parser {char *temp;
                                         quitacomillas(&temp,$1.cad);
                                         $$.cad=calloc(1,strlen(temp)+strlen($2.cad)+1);
                                         strcpy($$.cad,temp);
                                         strcat($$.cad,$2.cad);
                                         free($1.cad);
                                         free($2.cad);
                                         free(temp);};

cadena_parser : unacadena_parser {strcpy(buffer,$1.cad);
                                  sustituyedefines(buffer);
                                  free($1.cad);
                                  $$.cad=strdup(buffer);
                                 };

texto_sql : TEXTO_SQL {strcpy(buffer,$1.cad);
                       eliminaretornos(buffer);
                       sustituyedefines(buffer);
                       free($1.cad);
                       $$.cad=strdup(buffer);
                      };

definidor_campo: nombre_campo modificadores_campo {if (enbloque) {
                                                      if (funcionparsecampo) funcionparsecampo(bloqueparse,campoparse);
                                                      if (campoparse->nteclas) campoparse->teclas=realloc(campoparse->teclas,campoparse->nteclas*sizeof(fteclas));
                                                         else {
                                                              free(campoparse->teclas);
                                                              campoparse->teclas=NULL;
                                                          }
                                                      bloqueparse->ncamp++;
                                                   }  else       forparse->ncamp++;
                                                  };

nombrecampo : IDENTIFICADOR {$$.cad=$1.cad;}|
              CAMPO         {$$.cad=strdup("CAMPO");}|
              TABLA         {$$.cad=strdup("TABLA");};

nombre_campo  :  CAMPO '='nombrecampo {char *extra;
                                       int nc;
                                       if (enbloque) {
                                          if ((nc=damecampo(bloqueparse,$3.cad))!=-1) {
                                             campoparse=bloqueparse->c+nc;
                                             //warning(("En bloque %s campo %s duplicado\n",bloqueparse->fichero,$3.cad));
                                          } else {
                                             campoparse=bloqueparse->c+bloqueparse->ncamp;
                                             campoparse->b=bloqueparse;
                                          }
                                        } else {
                                          if ((nc=damecampoform(forparse,$3.cad))!=-1) {
                                             campoparse=forparse->c+nc;
                                             //warning(("En form campo %s duplicado\n",$3.cad));
                                          } else {
                                             campoparse=forparse->c+forparse->ncamp;
                                             campoparse->b=NULL;
                                          }
                                        }
                                       campoparse->f=forparse;
                                       strcpy(campoparse->nombre,$3.cad);
									                     campoparse->capitaliza=-1;
									                     campoparse->noupdate=-1;
                                       if (enbloque) {
                                          campoparse->enter=1;
                                          campoparse->tabla=1;
                                          campoparse->teclas=calloc(MAXFTECLAS,sizeof(fteclas));
                                        }
                                       if (damecaracextracampo) {
                                          extra=damecaracextracampo(campoparse);
                                          if (!es_blanco(extra)) creabuffercadena(extra);                                            
                                          free(extra);
                                       }
                                       free($3.cad);
                                      };

definidor_bloque :  nombre_bloque cuerpo_bloque ENDBLOQUE {if (funcionparsebloque) funcionparsebloque(bloqueparse);
                                                           /*damecaracextrabloque(forparse,bloqueparse,2);*/
                                                           if (terminabloque(bloqueparse)) return(-1);
                                                           forparse->nbloques++;
                                                           enbloque=0;}|
                    nombre_bloqueinter modificadores_bloque ENDBLOQUE{if (funcionparsebloque) funcionparsebloque(bloqueparse);
                                                                      if (terminabloque(bloqueparse)) return(-1);
                                                                      forparse->nbloques++;
                                                                      enbloque=0;}|
                    nombre_bloquepan cuerpo_bloque ENDBLOQUE{if (funcionparsebloque) funcionparsebloque(bloqueparse);
                                                                      if (terminabloque(bloqueparse)) return(-1);
                                                                      forparse->nbloques++;
                                                                      enbloque=0;};
                                                                                                                      

nombre_bloqueinter   :     BEGINBLOQUEFRM '=' IDENTIFICADOR {tratadefbloque($3.cad);
                                                               free($3.cad);};
nombre_bloquepan   :     BEGINBLOQUEPAN '=' IDENTIFICADOR {tratadefbloque($3.cad);
                                                               free($3.cad);};
                                                               
nombre_bloque   :     BEGINBLOQUE '=' IDENTIFICADOR {
                                                     tratadefbloque($3.cad);
                                                     if (creabuffer($3.cad)) {
                                                        yyerror("No existe fichero");
                                                        free($3.cad);
                                                        return(-1);
                                                      }                                                     
                                                      free($3.cad);
                                                    };

pintado_pantalla : PINTADO_PANTALLA {fichero2vi($1.cad,&bloqueparse->vi);free($1.cad);};

cuerpo_bloque   :     pintado_pantalla modificadores_bloque ;

modificadores_bloque : modificadores_bloque modificador_bloque |
                       {
                         char *extra;
                         if (damecaracextrabloque) {
                           extra=damecaracextrabloque(forparse,bloqueparse,1);
                           if (!es_blanco(extra)) creabuffercadena(extra);
                           free(extra);
                         }                       
                       };

nombre_tecla : IDENTIFICADOR  {$$.doble=traducetecla($1.cad);
                               if ($$.doble==0) mensajefcm(10,"Tecla no existe %s",$1.cad);
                               free($1.cad);} |
               NUMERO         {$$.doble=$1.doble;};

numeroneg : NUMERO {
                    $$.doble=$1.doble;
                   } |
            NEGATIVO {
                      $$.doble=$1.doble;
                     };


modificador_bloque  :  PADRE '=' IDENTIFICADOR      {if ((bloqueparse->padre=damebloque(forparse,$3.cad))==NULL) {
                                                        mensajeparser("Bloque %s no definido",$3.cad);
                                                        return(-1);
                                                      }
                                                     free($3.cad);
                                                     }|
                       TABLA '=' IDENTIFICADOR      {
                                                     strcpy(bloqueparse->nombre,$3.cad);
                                                     free($3.cad);
                                                     if (damedefaulttabla) damedefaulttabla(bloqueparse);
                                                     }|
                       TABLA '=' IDENTIFICADOR IDENTIFICADOR {
                                                              strcpy(bloqueparse->nombre,$3.cad);
                                                              strcat(bloqueparse->nombre," ");
                                                              strcat(bloqueparse->nombre,$4.cad);
                                                              free($3.cad);
                                                              free($4.cad);
                                                              if (damedefaulttabla) damedefaulttabla(bloqueparse);
                                                            }|
                       EXTRAPARSER '(' cadena_parser ',' cadena_parser ')' {
                                                                            if (extraparser) {
                                                                               char *extra;
                                                                               extra=extraparser(bloqueparse,$3.cad,$5.cad);
                                                                               if (!es_blanco(extra)) {
                                                                                  creabuffercadena(extra);
                                                                                  free(extra);
                                                                                }                                                                                  
                                                                             }
                                                                            free($3.cad);
                                                                            free($5.cad);
                                                                           }|
                       NOROWID                      {bloqueparse->norowid=1;}|
                       POSX '=' NUMERO              {int x,desp;
                                                     x=bloqueparse->vi.w.x1;
                                                     desp=(int)$3.doble;
                                                     bloqueparse->vi.w.x1=desp;
                                                     bloqueparse->vi.w.x2+=desp-x; } |
                       POSY '=' NUMERO              {int y,desp;
                                                     y=bloqueparse->vi.w.y1;
                                                     desp=(int)$3.doble;
                                                     bloqueparse->vi.w.y1=desp;
                                                     bloqueparse->vi.w.y2+=desp-y; } |
                       INCLUDETDCSS '=' LEXCADENA	 {strcpy(bloqueparse->includetdcss,$3.cad); free($3.cad);} |
                       INCLUDECSS   '=' LEXCADENA	 {strcpy(bloqueparse->includecss,$3.cad); free($3.cad);} |
                       INCLUDEFICHEROCSS '=' LEXCADENA	 {strcpy(bloqueparse->includeficherocss,$3.cad); free($3.cad);} |                       
                       INCLUDEHTML '=' LEXCADENA	 {strcpy(bloqueparse->includehtml,$3.cad); free($3.cad);} |  
                       INCLUDEFICHEROHTML '=' LEXCADENA	 {strcpy(bloqueparse->includeficherohtml,$3.cad); free($3.cad);} |                         
                       WMARCOFRAME 		{ bloqueparse->wtipomarco=1; } |
                       WMARCOPESTANNA	{ bloqueparse->wtipomarco=2; } |
                       WSINMARCO 			{ bloqueparse->wtipomarco=3; } |
                       WPLEGADO											{ bloqueparse->wplegado = 1; } |
                       WDESPLEGADO                  { bloqueparse->wplegado = 2; } |    
                       WPOSX '=' NUMERO              {bloqueparse->vipx.posx=(int)$3.doble;} |
                       WPOSY '=' NUMERO              {bloqueparse->vipx.posy=(int)$3.doble;} |
                       WLONX '=' NUMERO             {bloqueparse->vipx.lonx=(int)$3.doble;} |
                       WLONY '=' NUMERO              {bloqueparse->vipx.lony=(int)$3.doble;} |
                       WREGPAG '=' NUMERO            {bloqueparse->wregpag=(int)$3.doble;} |
                       WPIXELX '=' NUMERO            {bloqueparse->pxcol=(int)$3.doble;} |
                       WPIXELY '=' NUMERO            {bloqueparse->pxfila=(int)$3.doble;} |
                       WFRAME '(' NUMERO ','  NUMERO ','  NUMERO ','  NUMERO ',' LEXCADENA ',' LEXCADENA ')' {
													bloqueparse->framesfile[bloqueparse->nbframesfile].posx=(int)$3.doble;
													bloqueparse->framesfile[bloqueparse->nbframesfile].posy=(int)$5.doble;
													bloqueparse->framesfile[bloqueparse->nbframesfile].lonx=(int)$7.doble;
													bloqueparse->framesfile[bloqueparse->nbframesfile].lony=(int)$9.doble;
													strcopia(bloqueparse->framesfile[bloqueparse->nbframesfile].nombre,$11.cad,strlen($11.cad)); free($11.cad);
													strcopia(bloqueparse->framesfile[bloqueparse->nbframesfile].includecss,$13.cad,strlen($13.cad)); free($13.cad);													
													bloqueparse->nbframesfile++;}|
                       LEXCOLOR '=' IDENTIFICADOR   {
                                                     poncolorbloque(bloqueparse,$3.cad);
                                                     defcolor=1;
                                                     free($3.cad); } |
					   UPPER            {bloqueparse->capitaliza=FORMATOUPPER;}|
					   LOWER            {bloqueparse->capitaliza=FORMATOLOWER;}|
					   MIXED            {bloqueparse->capitaliza=0;}|
                       definidor_titulo             |
                       REGPAG '=' NUMERO            {bloqueparse->regpag=(int)$3.doble;} |
                       TIMEOUT '=' definidor_triger ',' NUMERO {if (bloqueparse->ftimeout) liberatriger(bloqueparse->ftimeout);
                                                                bloqueparse->ftimeout=$3.dato.ptr;
                                                                if (bloqueparse->ftimeout!=NULL) {
                                                                   bloqueparse->timeout=(long)$5.doble;
                                                                 }
                                                               } |
                        PRETECLA '=' nombre_tecla ',' definidor_triger {int tec,i;
                                                                    ftrigers *ft;
                                                                    tec=(int)$3.doble;
                                                                    ft=$5.dato.ptr;
                                                                    if (ft) {
                                                                       for (i=0;i<bloqueparse->nteclas;i++) if (bloqueparse->teclas[i].t==tec) break;
                                                                       if (i<bloqueparse->nteclas && bloqueparse->teclas[i].trigpre) {                                                                      
																		  																		liberatriger(bloqueparse->teclas[i].trigpre);
																		  																		bloqueparse->teclas[i].trigpre=NULL;
																	   																	 }
																	  																	 bloqueparse->teclas[i].trigpre=ft;
                                                                       if (i==bloqueparse->nteclas) {
                                                                       	 bloqueparse->teclas[i].t=tec;
                                                                       	 bloqueparse->teclas[i].b=bloqueparse;
                                                                         bloqueparse->nteclas++; 
                                                                       }
                                                                     }
                                                                    } |       
                       POSTTECLA '=' nombre_tecla ',' definidor_triger {int tec,i;
                                                                    ftrigers *ft;
                                                                    tec=(int)$3.doble;
                                                                    ft=$5.dato.ptr;
                                                                    if (ft) {
                                                                       for (i=0;i<bloqueparse->nteclas;i++) if (bloqueparse->teclas[i].t==tec) break;
                                                                       if (i<bloqueparse->nteclas && bloqueparse->teclas[i].trigpost) {                                                                      
																		  																		liberatriger(bloqueparse->teclas[i].trigpost);
																		  																		bloqueparse->teclas[i].trigpost=NULL;
																	   																	 }
																	  																	 bloqueparse->teclas[i].trigpost=ft;
                                                                       if (i==bloqueparse->nteclas) {
                                                                       	 bloqueparse->teclas[i].t=tec;
                                                                       	 bloqueparse->teclas[i].b=bloqueparse;
                                                                         bloqueparse->nteclas++; 
                                                                       }
                                                                     }
                                                                    } |                                                                  
                       TECLA '=' nombre_tecla ',' definidor_triger {int tec,i;
                                                                    ftrigers *ft;
                                                                    tec=(int)$3.doble;
                                                                    ft=$5.dato.ptr;
                                                                    if (ft) {
                                                                       for (i=0;i<bloqueparse->nteclas;i++) if (bloqueparse->teclas[i].t==tec) break;
                                                                       if (i<bloqueparse->nteclas && bloqueparse->teclas[i].trig) {
																		  																		liberatriger(bloqueparse->teclas[i].trig);
																		  																		bloqueparse->teclas[i].trig=NULL;
																	   																	}
																	  																	 bloqueparse->teclas[i].trig=ft;
																	  																	 if (i==bloqueparse->nteclas) {
                                                                         bloqueparse->teclas[i].t=tec;
                                                                         bloqueparse->teclas[i].b=bloqueparse;
                                                                         bloqueparse->nteclas++;
                                                                       }
                                                                     }
                                                                    } |
                       proteccion_bloque |
                       modificador_oracle |
                       AQUERY                                       {bloqueparse->aquery=1;} |
                       PQUERY                                       {bloqueparse->pquery=1;} |
                       TQUERY                                       {bloqueparse->tquery=1;} |
                       SOLOQUERY                                    {bloqueparse->soloquery=1;
                                                                     bloqueparse->norowid=1;
                                                                     bloqueparse->noinsert=1;
                                                                     bloqueparse->noorains=1;
                                                                     bloqueparse->nooradel=1;
                                                                     bloqueparse->noupdate=1;
                                                                     bloqueparse->nodelete=1;
                                                                     bloqueparse->nolock=1;} |
                       modificador_online |
                       definidor_campo |
                       definidor_cursor |
                       PREINSERT '=' definidor_triger       {if ($3.dato.ptr) {
                                                                if (bloqueparse->fpreinsert) liberatriger(bloqueparse->fpreinsert);
                                                                bloqueparse->fpreinsert=$3.dato.ptr;
                                                              }
                                                            }|
                       CONTEXTUAL '=' definidor_triger      {if ($3.dato.ptr) {
                                                                if (bloqueparse->contextual) liberatriger(bloqueparse->contextual);
                                                                bloqueparse->contextual=$3.dato.ptr;
                                                              }
                                                            }|
                       POSTINSERT '=' definidor_triger     {if ($3.dato.ptr) {
                                                                if (bloqueparse->fpostinsert) liberatriger(bloqueparse->fpostinsert);
                                                                bloqueparse->fpostinsert=$3.dato.ptr;
                                                              }
                                                            }|
                       PREUPDATE '=' definidor_triger      {if ($3.dato.ptr) {
                                                                if (bloqueparse->fpreupdate) liberatriger(bloqueparse->fpreupdate);
                                                                bloqueparse->fpreupdate=$3.dato.ptr;
                                                              }
                                                            }|
                       POSTUPDATE '=' definidor_triger     {if ($3.dato.ptr) {
                                                                if (bloqueparse->fpostupdate) liberatriger(bloqueparse->fpostupdate);
                                                                bloqueparse->fpostupdate=$3.dato.ptr;
                                                              }
                                                            }|
                       PREDELETE '=' definidor_triger      {if ($3.dato.ptr) {
                                                                if (bloqueparse->fpredelete) liberatriger(bloqueparse->fpredelete);
                                                                bloqueparse->fpredelete=$3.dato.ptr;
                                                              }
                                                            }|
                       POSTDELETE '=' definidor_triger     {if ($3.dato.ptr) {
                                                                if (bloqueparse->fpostdelete) liberatriger(bloqueparse->fpostdelete);
                                                                bloqueparse->fpostdelete=$3.dato.ptr;
                                                              }
                                                            }|
                       FINQUERY  '=' definidor_triger      {if ($3.dato.ptr) {
                                                                if (bloqueparse->ffinquery) liberatriger(bloqueparse->ffinquery);
                                                                bloqueparse->ffinquery=$3.dato.ptr;
                                                              }
                                                            }|
                       PREBLOQUE '=' definidor_triger      {if ($3.dato.ptr) {
                                                                if (bloqueparse->fprebloque) liberatriger(bloqueparse->fprebloque);
                                                                bloqueparse->fprebloque=$3.dato.ptr;
                                                              }
                                                            }|
                       POSTBLOQUE '=' definidor_triger     {if ($3.dato.ptr) {
                                                                if (bloqueparse->fpostbloque) liberatriger(bloqueparse->fpostbloque);
                                                                bloqueparse->fpostbloque=$3.dato.ptr;
                                                              }
                                                            }|
                       PREQUERY '=' definidor_triger       {if ($3.dato.ptr) {
                                                                if (bloqueparse->fprequery) liberatriger(bloqueparse->fprequery);
                                                                bloqueparse->fprequery=$3.dato.ptr;
                                                              }
                                                            }|
                       POSTQUERY '=' definidor_triger      {if ($3.dato.ptr) {
                                                                if (bloqueparse->fpostquery) liberatriger(bloqueparse->fpostquery);
                                                                bloqueparse->fpostquery=$3.dato.ptr;
                                                              }
                                                            }|
                       PREREGISTRO '=' definidor_triger    {if ($3.dato.ptr) {
                                                                if (bloqueparse->fpreregistro) liberatriger(bloqueparse->fpreregistro);
                                                                bloqueparse->fpreregistro=$3.dato.ptr;
                                                              }
                                                            }|
                       POSTREGISTRO '=' definidor_triger   {if ($3.dato.ptr) {
                                                                if (bloqueparse->fpostregistro) liberatriger(bloqueparse->fpostregistro);
                                                                bloqueparse->fpostregistro=$3.dato.ptr;
                                                              }
                                                            }|
                       PRECOMMIT '=' definidor_triger      {if ($3.dato.ptr) {
                                                                if (bloqueparse->fprecommit) liberatriger(bloqueparse->fprecommit);
                                                                bloqueparse->fprecommit=$3.dato.ptr;
                                                              }
                                                            }|
                       POSTCOMMIT '=' definidor_triger     {if ($3.dato.ptr) {
                                                                if (bloqueparse->fpostcommit) liberatriger(bloqueparse->fpostcommit);
                                                                bloqueparse->fpostcommit=$3.dato.ptr;
                                                              }
                                                            }|
                       PREROLLBACK '=' definidor_triger      {if ($3.dato.ptr) {
                                                                if (bloqueparse->fprerollback) liberatriger(bloqueparse->fprerollback);
                                                                bloqueparse->fprerollback=$3.dato.ptr;
                                                              }
                                                            }|
                       POSTROLLBACK '=' definidor_triger     {if ($3.dato.ptr) {
                                                                if (bloqueparse->fpostrollback) liberatriger(bloqueparse->fpostrollback);
                                                                bloqueparse->fpostrollback=$3.dato.ptr;
                                                              }
                                                            }|
                       PREPINTA '=' definidor_triger       {if ($3.dato.ptr) {
                                                                if (bloqueparse->fprepinta) liberatriger(bloqueparse->fprepinta);
                                                                bloqueparse->fprepinta=$3.dato.ptr;
                                                              }
                                                            }|
                       POSTPINTA '=' definidor_triger      {if ($3.dato.ptr) {
                                                                if (bloqueparse->fpostpinta) liberatriger(bloqueparse->fpostpinta);
                                                                bloqueparse->fpostpinta=$3.dato.ptr;
                                                              }
                                                            }|
                       ONPINTA '=' definidor_triger        {if ($3.dato.ptr) {
                                                                if (bloqueparse->fonpinta) liberatriger(bloqueparse->fonpinta);
                                                                bloqueparse->fonpinta=$3.dato.ptr;
                                                              }
                                                            }|

                       ONCLICK '=' definidor_triger        {if ($3.dato.ptr) {
                                                                if (bloqueparse->feventos.onclick) liberatriger(bloqueparse->feventos.onclick);
                                                                bloqueparse->feventos.onclick=$3.dato.ptr;
                                                              }
                                                            }|
                       ONRIGHTCLICK '=' definidor_triger   {if ($3.dato.ptr) {
                                                                if (bloqueparse->feventos.onrightclick) liberatriger(bloqueparse->feventos.onrightclick);
                                                                bloqueparse->feventos.onrightclick=$3.dato.ptr;
                                                              }
                                                            }|
                       ONCENTERCLICK '=' definidor_triger  {if ($3.dato.ptr) {
                                                                if (bloqueparse->feventos.oncenterclick) liberatriger(bloqueparse->feventos.oncenterclick);
                                                                bloqueparse->feventos.oncenterclick=$3.dato.ptr;
                                                              }
                                                            }|
                       ONMOUSEOVER '=' definidor_triger    {if ($3.dato.ptr) {
                                                                if (bloqueparse->feventos.onmouseover) liberatriger(bloqueparse->feventos.onmouseover);
                                                                bloqueparse->feventos.onmouseover=$3.dato.ptr;
                                                              }
                                                            }|
                       ONMOUSEOUT '=' definidor_triger     {if ($3.dato.ptr) {
                                                                if (bloqueparse->feventos.onmouseout) liberatriger(bloqueparse->feventos.onmouseout);
                                                                bloqueparse->feventos.onmouseout=$3.dato.ptr;
                                                              }
                                                            }|
                       ONDBCLICK '=' definidor_triger      {if ($3.dato.ptr) {
                                                                if (bloqueparse->feventos.ondbclick) liberatriger(bloqueparse->feventos.ondbclick);
                                                                bloqueparse->feventos.ondbclick=$3.dato.ptr;
                                                              }
                                                            }|
                       ONMOUSEMOVE '=' definidor_triger    {if ($3.dato.ptr) {
                                                                if (bloqueparse->feventos.onmousemove) liberatriger(bloqueparse->feventos.onmousemove);
                                                                bloqueparse->feventos.onmousemove=$3.dato.ptr;
                                                              }
                                                            }|
                       WGRAFICA '=' IDENTIFICADOR ',' NUMERO ',' NUMERO ',' NUMERO ',' NUMERO ',' NUMERO {
                       																					fstats *fs=bloqueparse->stats + bloqueparse->nbstats;
                                                                fs->nombre = $3.cad;
                                                                fs->posx=(int)$5.doble;
                                                                fs->posy=(int)$7.doble;
                                                                fs->lonx=(int)$9.doble;
                                                                fs->lony=(int)$11.doble;  
                                                                fs->enmarcado = (int)$13.doble;  
                                                                bloqueparse->nbstats++;                     
                       					                           } |                                     
                       definidor_boton |
					             BOTONERA '=' IDENTIFICADOR {fbotoneras *fbot=bloqueparse->fbot+bloqueparse->numbotoneras;
                                                   if (duplicabotonera($3.cad,fbot)) {
                                                      mensajefcm(10,"No existe botonera %s\n",$3.cad);
                                                      free($3.cad);
                                                      return(-1);
                                                   }
                                                   free($3.cad);
                                                   bloqueparse->numbotoneras++;}|
                       BOTONERA '=' IDENTIFICADOR ',' numeroneg ',' NUMERO  ',' numeroneg ',' NUMERO  lista_botones {fbotoneras *fbot=bloqueparse->fbot+bloqueparse->numbotoneras;
                                        fbot->nombre=$3.cad;
                                        fbot->posx=(int)$5.doble;
                                        fbot->posy=(int)$7.doble;
                                        fbot->lonx=(int)$9.doble;
                                        fbot->lony=(int)$11.doble;
                                        bloqueparse->numbotoneras++;} |
                                        
                      AJAX '(' IDENTIFICADOR ',' cadena_parser ',' cadena_parser ',' cadena_parser ',' cadena_parser ',' cadena_parser ',' numeroneg ')' {
                      						v10ajax *aj = bloqueparse->ajax+ bloqueparse->nbajax; 
                      						aj->id 			 = $3.cad;                      					
                      						aj->objetojs = $5.cad;
                      						aj->tipo 		 = $7.cad;
                      						aj->modulo 	 = $9.cad;
                      						aj->nombre   = $11.cad;
                      						aj->params   = $13.cad;
                      						aj->frecuencia  = (int)$15.doble;                      						                 						                      						                      						
                      						bloqueparse->nbajax++;
                      					} |
                      SIDEBAROCULTO 	{ bloqueparse->sidebaroculto = 1;}|
                      SIDEBARVISIBLE  { bloqueparse->sidebaroculto = 2;}|
                      COMPONENTE '(' IDENTIFICADOR ',' cadena_parser ',' cadena_parser ',' cadena_parser ',' cadena_parser ',' NUMERO ')' {
                      					  v10comphtml *co = bloqueparse->comphtml + bloqueparse->nbcomphtml; 
                      						co->id       = $3.cad;
                      						co->tipo 		 = $5.cad;
                      						co->modulo 	 = $7.cad;
                      						co->nombre   = $9.cad;
                      						co->params   = $11.cad;
                      						co->visible  = (int)$13.doble;                      						                 						                      						                      						
                      						bloqueparse->nbcomphtml++;
                      }  ;

modificador_boton:  INCLUDECSS '=' LEXCADENA	 {strcpy(botonparse->includecss,$3.cad);free($3.cad);} |
                    ESTILOCSS '=' LEXCADENA	 {strcpy(botonparse->estilocss,$3.cad); free($3.cad);} |
                    BOTONOCULTO '=' NUMERO {botonparse->oculto=(int)$3.doble;} |
                    BOTONDISABLED '=' NUMERO {botonparse->disabled=(int)$3.doble;};
                  
modificadores_boton: ',' modificador_boton modificadores_boton |
                        	;


nombre_boton: BOTON '=' IDENTIFICADOR ',' {
               fbotones *b=bloqueparse->fb+bloqueparse->numbotones;
               bloqueparse->numbotones++;
               b->nombre=$3.cad;
               botonparse = b;};

nombre_boton_dupl: BOTON '=' IDENTIFICADOR {$$.cad = $3.cad;};


definidor_boton:  nombre_boton_dupl {
										fbotones *b=bloqueparse->fb+bloqueparse->numbotones;
                 		if (duplicaboton($1.cad,b)) {
                     mensajefcm(10,"No existe boton %s\n",$1.cad);
                     free($1.cad);
                     return(-1);
                  	}
                  	free($1.cad);
                  	bloqueparse->numbotones++;
                  } |
                  nombre_boton numeroneg ',' NUMERO ',' NUMERO ',' NUMERO ',' cadena_parser ',' IDENTIFICADOR ',' nombre_tecla modificadores_boton
                                                            {  
                                                             botonparse->posx=(int)$2.doble;
                                                             botonparse->posy=(int)$4.doble;
                                                             botonparse->lonx=(int)$6.doble;
                                                             botonparse->lony=(int)$8.doble;
                                                             botonparse->texto=$10.cad;
                                                             botonparse->image=$12.cad;
                                                             botonparse->tecla=(int)$14.doble;
                                                             }|
                  nombre_boton numeroneg ',' NUMERO ',' NUMERO ',' NUMERO ',' cadena_parser ',' IDENTIFICADOR ',' nombre_tecla ',' cadena_parser modificadores_boton
                                                            {
                                                             botonparse->posx=(int)$2.doble;
                                                             botonparse->posy=(int)$4.doble;
                                                             botonparse->lonx=(int)$6.doble;
                                                             botonparse->lony=(int)$8.doble;
                                                             botonparse->texto=$10.cad;
                                                             botonparse->image=$12.cad;
                                                             botonparse->tecla=(int)$14.doble;
                                                             botonparse->tooltip=strdup(v10translate($16.cad));
                                                             free($16.cad);
                                                             };

lista_botones : ',' IDENTIFICADOR lista_botones {fbotoneras *fbot=bloqueparse->fbot+bloqueparse->numbotoneras;
                                                 fbotones *fb;
                                                 fb=damebotonbloque(bloqueparse,$2.cad);
                                                 if (fb==NULL) {
                                                    mensajeparser("no existe boton %s",$2.cad);
                                                    free($2.cad);
                                                    return(-1);
                                                 }
                                                 free($2.cad);
                                                 fbot->b[fbot->numbotones]=fb;
                                                 fbot->numbotones++;}|
                                               { fbotoneras *fbot=bloqueparse->fbot+bloqueparse->numbotoneras;
                                                 fbot->b=calloc(MAXBOTONES,sizeof(fbotones **));
                                                 fbot->numbotones=0;};

identificador_triger     : IDENTIFICADOR {ftrigers *ft;
                                          char *aux;
                                          aux=strchr($1.cad,'.');
                                          if (aux) {
                                             *aux=0;
                                             ft=dametrigerdll($1.cad,aux+1);
                                             $$.dato.tipo=1;
                                             *aux='.';
                                           } else {
                                             ft=dametriger($1.cad);
                                             $$.dato.tipo=0;
                                           }
                                          if (ft==NULL) {
                                             mensajeparser("No encuentro triger %s",$1.cad);
                                             free($1.cad);
                                             return(-1);
                                           }
                                          free($1.cad);
                                          $$.dato.ptr=ft;
                                         };

definicion_triger : lista_mod_triger identificador_triger    {ftrigers *ft;
                                                              ft=$2.dato.ptr;
                                                              ft=duplicatriger(bloqueparse,ft);
                                                              ft->opciones=$1.entero;
                                                              $$.dato.ptr=ft;
                                                              if ($2.dato.tipo) {
                                                                 liberatriger($2.dato.ptr);
                                                               }
                                                             } |
                    lista_mod_triger identificador_triger '(' lista_parametros ')' {ftrigers *ft,*ft1;
                                                                                    ft1=$2.dato.ptr;
                                                                                    ft=$4.dato.ptr;
                                                                                    ft->b=bloqueparse;
                                                                                    ft->fun=ft1->fun;
                                                                                    ft->nombre=strdup(ft1->nombre);
                                                                                    ft->param=realloc(ft->param,ft->nparam*sizeof(void *));
                                                                                    ft->tipoparam=realloc(ft->tipoparam,ft->nparam*sizeof(int));
                                                                                    ft->opciones=$1.entero;
                                                                                    $$.dato.ptr=ft;
                                                                                    if ($2.dato.tipo) {
                                                                                       liberatriger($2.dato.ptr);
                                                                                      }}|
                    TNULL {$$.dato.ptr=NULL;};

modificador_triger : '-' {$$.entero=CINVERSO;} |
                     '$' {$$.entero=CIGNORE;} |
                     '%' {$$.entero=CSOLOMEN;} |
                     '@' {$$.entero=CTERMINA;} |
                     '+' {$$.entero=CSUCCESS;} |
                     '!' {$$.entero=CPREGUNTA;} |
                     '&' {$$.entero=CFUNCION;};

lista_mod_triger : modificador_triger lista_mod_triger {$$.entero=$1.entero | $2.entero;} |
                             {$$.entero=0;};

triger_protegido : condicion_proteccion ',' definicion_triger {$$.dato.protegido=$1.entero;
                                                               $$.dato.ptr=$3.dato.ptr;
                                                              }|
                   definicion_triger                          {$$.dato.ptr=$1.dato.ptr;
                                                               $$.dato.protegido=0;};

definidor_triger : triger_protegido {if ($1.dato.protegido) {
                                        liberatriger($1.dato.ptr);
                                        $$.dato.ptr=NULL;
                                      } else {
                                        $$.dato.ptr=$1.dato.ptr;
                                      }
                                      $$.dato.protegido=$1.dato.protegido;
                                    };


lista_parametros : parametro                              {ftrigers *ft;
                                                           ft=calloc(1,sizeof(ftrigers));
                                                           ft->param=calloc(MAXPARAM,sizeof(void *));
                                                           ft->tipoparam=calloc(MAXPARAM,sizeof(int));
                                                           ft->nparam=1;
                                                           ft->param[0]=$1.dato.ptr;
                                                           ft->tipoparam[0]=$1.dato.tipo;
                                                           $$.dato.ptr=ft;
                                                          } |
                   lista_parametros ',' parametro         {ftrigers *ft=$1.dato.ptr;
                                                           if (ft->nparam>=MAXPARAM) {
                                                              mensajeparser("desmasiados parametros en triger");
                                                              return(-1);
                                                            }
                                                           ft->param[ft->nparam]=$3.dato.ptr;
                                                           ft->tipoparam[ft->nparam]=$3.dato.tipo;
                                                           ft->nparam++;
                                                           $$.dato.ptr=ft;
                                                           };

parametro : cadena_parser {$$.dato.ptr=$1.cad;$$.dato.tipo=PARAMCADENA;}|
            definicion_triger {$$.dato.ptr=$1.dato.ptr;$$.dato.tipo=PARAMTRIGER;};

modificadores_campo: ',' modificador_campo modificadores_campo|
                     ;

lista_privilegios : cadena_parser {$$.entero=esta_protegido($1.cad);free($1.cad);}|
                    cadena_parser ',' lista_privilegios {if ($1.entero) $$.entero=$1.entero;
                                                  else        $$.entero=$3.entero;
                             free($1.cad);};


condicion_proteccion : PROTECT   {if (protegidoform<1) $$.entero=1; else $$.entero=0;}|
                       PROTECT '(' lista_privilegios ')' {$$.entero=$3.entero;};

modificador_where: WHERE '=' {lexbegin(STEXTOSQL);};

opciones_combox:  cadena_parser  {  if (campoparse->combox.nopc>=MAXOPMENUS) {
                                     mensajeparser("Solo se admiten un máximo de %d opciones en un Combox",MAXOPMENUS);
                                     return(-1);
                                   }
                                   v10ansitooem($1.cad,$1.cad);
                                   campoparse->combox.opc[campoparse->combox.nopc]=strdup($1.cad);
                                   campoparse->combox.nopc++;
                                } |
                  cadena_parser ',' opciones_combox {  if (campoparse->combox.nopc>=MAXOPMENUS) {
                                                        mensajeparser("Solo se admiten un máximo de %d opciones en un Combox",MAXOPMENUS);
                                                        return(-1);
                                                      }
                                                      v10ansitooem($1.cad,$1.cad);
                                                      campoparse->combox.opc[campoparse->combox.nopc]=strdup($1.cad);
                                                      campoparse->combox.nopc++;
                                                   };

modificador_campo: NOENTER   {campoparse->enter=0;}|
                   NOENTER  '(' lista_privilegios ')' {if ($3.entero) {
                                                         campoparse->enter=0;
                                                       }
                                                      } |
                   INCLUDECSS '=' LEXCADENA	 {strcpy(campoparse->includecss,$3.cad); free($3.cad);} |                                                      
                   ESTILOCSS '=' LEXCADENA	 {strcpy(campoparse->estilocss,$3.cad); free($3.cad);} |                                                                         
	              	 NOINPUT   {campoparse->noinput=1;}|
                   NOINPUT  '(' lista_privilegios ')' {if ($3.entero) {
                                                         campoparse->noinput=1;
                                                       }
                                                      } |
                   modificador_where texto_sql {campoparse->where=$2.cad;}|
                   AUTOENTER {campoparse->autoenter=1;}|
                   UPPER     {campoparse->capitaliza=FORMATOUPPER;}|
                   LOWER     {campoparse->capitaliza=FORMATOLOWER;}|
                   MIXED     {campoparse->capitaliza=0;}|
                   TRADUCIBLE {campoparse->traducible=strdup("");}|
                   TRADUCIBLE'(' cadena_parser ')' {campoparse->traducible=strdup("$3.cad");}|
                   TOOLTIP '(' cadena_parser ')' {if (v10usaansi) v10ansitooem($3.cad,$3.cad);
                                                  campoparse->tooltip=strdup(v10translate($3.cad));
                                                  free($3.cad);}|
                   FUNTOOLTIP '=' definidor_triger   {if (campoparse->funtooltip) liberatriger(campoparse->funtooltip);
                                                    campoparse->funtooltip=$3.dato.ptr;}|
                   NOPREF    {campoparse->nopref=1;}|
                   AUXILIAR  {campoparse->tabla=0;}|
                   NOUPDATE  {campoparse->noupdate=1;}|
                   NOUPDATE  '(' lista_privilegios ')' {if ($3.entero) campoparse->noupdate=1;}|
                   UPDATE    {campoparse->noupdate=0;}|
                   UPDATE    '(' lista_privilegios ')' {if ($3.entero==0) campoparse->noupdate=0;}|
                   SCAN      {campoparse->scan=1;}|
                   SCAN '(' NUMERO ')'     {campoparse->scan=(int)$3.doble;}|
                   PREFIJO '=' IDENTIFICADOR {campoparse->prefijo=$3.cad;}|
                   AUTOTRANSMIT {campoparse->autotransmit=1;}|
                   condicion_proteccion {if ($1.entero) campoparse->noupdate=1;}|
                   DISPLAY   {if (protegidoform<1) {
                                 campoparse->noupdate=1;
                                 campoparse->invisible=1;
                               }
                             }|
                   DISPLAY '(' lista_privilegios ')' {if ($3.entero) {
                                                         campoparse->noupdate=1;
                                                         campoparse->invisible=1;
                                                       }
                                                      } |
                   VIRTUAL   {if (enbloque==0) {
                                 mensajeparser("Campo %s virtual en FRM",campoparse->nombre);
                                 return(-1);
                               }
                              campoparse->virtual=1;
                              strcpy(campoparse->nvirtual,campoparse->nombre);
                             }|
                   VIRTUAL '(' cadena_parser ')' {if (enbloque==0) {
                                                     mensajeparser("Campo %s virtual en FRM",campoparse->nombre);
                                                     return(-1);
                                                   }
                                                  campoparse->virtual=1;
                                                  strcpy(campoparse->nvirtual,$3.cad);
                                                  free($3.cad);
                                                 }|
                   OCULTO {campoparse->oculto=1;}|
                   cadena_parser          {if (campoparse->oculto==0) {
                                              mensajeparser("campo %s con formato no oculto",campoparse->nombre);
                                            } else {
                                             if (v10usaansi) v10ansitooem($1.cad,$1.cad);
                                             analizatokendia($1.cad,NULL,&campoparse->tipo,&campoparse->format,&campoparse->dec,&campoparse->lvar,&campoparse->lvar,NULL);
                                             campoparse->lon=tamv10tipo(campoparse->tipo,campoparse->lvar+1);
                                             if (campoparse->virtual) {
                                                mensajefcm(10,"En bloque %s Campo %s virtual oculto con formato",bloqueparse->fichero,campoparse->nombre);
                                             }
                                             free($1.cad);
                                            }
                                           }|
                   TITULO '(' cadena_parser ')' {campoparse->titulo=strdup($3.cad);}|                   
                   WPOSX '=' NUMERO {  campoparse->vipx.posx = (int)$3.doble; } |
                   WPOSY '=' NUMERO {  campoparse->vipx.posy = (int)$3.doble; } |
                   WLONX '=' NUMERO {  campoparse->vipx.lonx = (int)$3.doble; } |
                   WLONY '=' NUMERO {  campoparse->vipx.lony = (int)$3.doble; } |
                   POSTCHANGE '=' definidor_triger {if ($3.dato.ptr) {
                                                       if (campoparse->change) liberatriger(campoparse->change);
                                                       campoparse->change=$3.dato.ptr;;
                                                     }
                                                    }|
                   CONTEXTUAL '=' definidor_triger {if ($3.dato.ptr) {
                                                       if (campoparse->contextual) liberatriger(campoparse->contextual);
                                                       campoparse->contextual=$3.dato.ptr;;
                                                     }
                                                    }|
                   PREFIELD '=' definidor_triger   {if ($3.dato.ptr) {
                                                       if (campoparse->pref) liberatriger(campoparse->pref);
                                                       campoparse->pref=$3.dato.ptr;
                                                     }
                                                    }|
                   POSTFIELD '=' definidor_triger  {if ($3.dato.ptr) {
                                                       if (campoparse->postf) liberatriger(campoparse->postf);
                                                       campoparse->postf=$3.dato.ptr;;
                                                     }
                                                    }|
                   PREPINTA '=' definidor_triger   {if ($3.dato.ptr) {
                                                       if (campoparse->prepinta) liberatriger(campoparse->prepinta);
                                                       campoparse->prepinta=$3.dato.ptr;;
                                                     }
                                                    }|
                   POSTPINTA '=' definidor_triger  {if ($3.dato.ptr) {
                                                       if (campoparse->postpinta) liberatriger(campoparse->postpinta);
                                                       campoparse->postpinta=$3.dato.ptr;;
                                                     }
                                                    }|
				   CONVIERTE '=' definidor_triger ';' definidor_triger
				                                   {if ($3.dato.ptr) {
                                                       if (campoparse->convfrombd) liberatriger(campoparse->convfrombd);
                                                       campoparse->convfrombd=$3.dato.ptr;
                                                     }
												    if ($5.dato.ptr) {
                                                       if (campoparse->conv2bd) liberatriger(campoparse->conv2bd);
                                                       campoparse->conv2bd=$5.dato.ptr;
                                                     }
												   }|
                   ONPINTA '=' definidor_triger    {if ($3.dato.ptr) {
                                                       if (campoparse->onpinta) liberatriger(campoparse->onpinta);
                                                       campoparse->onpinta=$3.dato.ptr;
                                                     }
                                                    }|
                   ONCLICK '=' definidor_triger    {if ($3.dato.ptr) {
                                                       if (campoparse->feventos.onclick) liberatriger(campoparse->feventos.onclick);
                                                       campoparse->feventos.onclick=$3.dato.ptr;
                                                     }
                                                    }|
                   ONRIGHTCLICK '=' definidor_triger   {if ($3.dato.ptr) {
                                                           if (campoparse->feventos.onrightclick) liberatriger(campoparse->feventos.onrightclick);
                                                           campoparse->feventos.onrightclick=$3.dato.ptr;
                                                        }
                                                       }|
                   ONCENTERCLICK '=' definidor_triger  {if ($3.dato.ptr) {
                                                           if (campoparse->feventos.oncenterclick) liberatriger(campoparse->feventos.oncenterclick);
                                                           campoparse->feventos.oncenterclick=$3.dato.ptr;
                                                        }
                                                       }|
                   ONMOUSEOVER '=' definidor_triger    {if ($3.dato.ptr) {
                                                           if (campoparse->feventos.onmouseover) liberatriger(campoparse->feventos.onmouseover);
                                                          campoparse->feventos.onmouseover=$3.dato.ptr;
                                                         }
                                                       }|
                   ONMOUSEOUT '=' definidor_triger     {if ($3.dato.ptr) {
                                                           if (campoparse->feventos.onmouseout) liberatriger(campoparse->feventos.onmouseout);
                                                           campoparse->feventos.onmouseout=$3.dato.ptr;
                                                         }
                                                       }|
                   ONDBCLICK '=' definidor_triger    {if ($3.dato.ptr) {
                                                         if (campoparse->feventos.ondbclick) liberatriger(campoparse->feventos.ondbclick);
                                                         campoparse->feventos.ondbclick=$3.dato.ptr;
                                                       }
                                                      }|
                   ONMOUSEMOVE '=' definidor_triger    {if ($3.dato.ptr) {
                                                           if (campoparse->feventos.onmousemove) liberatriger(campoparse->feventos.onmousemove);
                                                           campoparse->feventos.onmousemove=$3.dato.ptr;
                                                        }
                                                       }|
                   CHECKBOX '(' cadena_parser ',' cadena_parser ')' {
                                                                    campoparse->checkbox=calloc(1,sizeof(checkboxes));
                                                                    campoparse->checkbox->activo=1;
                                                                    v10ansitooem($3.cad,$3.cad);
                                                                    campoparse->checkbox->valor_false=strdup($3.cad);
                                                                    v10ansitooem($5.cad,$5.cad);
                                                                    campoparse->checkbox->valor_true=strdup($5.cad);
                                                                    }|
                   COMBOX '(' opciones_combox ')' {
                                                   campoparse->combox.activo=1;
                                                   campoparse->combox.multiple=0;
                                                   campoparse->combox.index=0;
                                                  }|
                   COMBOXMULTIPLE '(' opciones_combox ')' {
                                                   campoparse->combox.activo=1;
                                                   campoparse->combox.multiple=1;
                                                   campoparse->combox.index=0;
                                                  }|                                                  
                   COMBOXREADONLY {
                                    if (campoparse->combox.activo==0) {
                                    	mensajeparser("Modificador de campo COMBOXREADONLY antes de definir el COMBOX");
                                      return(-1);
                                    }
                                    campoparse->combox.readonly=1; 
                   
                                  } |
                   COMBOXINDEX '=' NUMERO {
                                           if (campoparse->combox.activo==0) {
                                              mensajeparser("Modificador de campo INDEXCOMBOX antes de definir el COMBOX");
                                              return(-1);
                                            }
                                           if ((int)$3.doble>campoparse->combox.nopc-1) {
                                              mensajeparser("Índice seleccionado para el COMBOX supera las opciones (%d)",campoparse->combox.nopc);
                                             return(-1);
                                            }
                                           campoparse->combox.index=(int)$3.doble;
                                          }|
          				COMBOXREGPAG '=' NUMERO {
                                           if (campoparse->combox.activo==0) {
                                              mensajeparser("Modificador de campo REGPAGCOMBOX antes de definir el COMBOX");
                                              return(-1);
                                            }                                          
                                           campoparse->combox.regpag=(int)$3.doble;
                                          }|                                          

                   TECLA '=' nombre_tecla ',' definidor_triger {int tec,i;
                                                                 ftrigers *ft;
                                                                 tec=(int)$3.doble;
                                                                 ft=$5.dato.ptr;                                                               
                                                                 if (ft) {
                                                                    if (enbloque) {
                                                                       for (i=0;i<campoparse->nteclas;i++) if (campoparse->teclas[i].t==tec) break;
                                                                       if (i<campoparse->nteclas) liberatriger(campoparse->teclas[i].trig);
                                                                       ft=$5.dato.ptr;
                                                                       campoparse->teclas[i].trig=ft;
                                                                       campoparse->teclas[i].t=tec;
                                                                       campoparse->teclas[i].b=bloqueparse;
                                                                       if (i==campoparse->nteclas) campoparse->nteclas++;
                                                                      } else liberatriger(ft);
                                                                  }
                                                                 }|
                  REGPAG '=' NUMERO {
                                        campoparse->regpag=(int)$3.doble;  
                                    };

modificador_oracle : nombre_modificador_oracle texto_sql {switch ($1.entero) {
                                                            case WHERE:if (bloqueparse->where) free(bloqueparse->where);
                                                                       bloqueparse->where=$2.cad;
                                                                       break;
                                                            case ORDERBY:if (bloqueparse->orderby) free(bloqueparse->orderby);
                                                                       bloqueparse->orderby=$2.cad;
                                                                       break;
                                                            case GROUPBY:if (bloqueparse->groupby) free(bloqueparse->groupby);
                                                                       bloqueparse->groupby=$2.cad;
                                                                       break;
                                                            case HAVING:if (bloqueparse->having) free(bloqueparse->having);
                                                                       bloqueparse->having=$2.cad;
                                                                       break;
                                                            case SELECT:if (bloqueparse->select) free(bloqueparse->select);
                                                                       bloqueparse->extraselect=$2.cad;
                                                                       break;
                                                           }
                                                        };

nombre_modificador_oracle : WHERE '=' {$$.entero=$1.entero;lexbegin(STEXTOSQL);} |
                     ORDERBY '=' {$$.entero=$1.entero;lexbegin(STEXTOSQL);} |
                     GROUPBY '=' {$$.entero=$1.entero;lexbegin(STEXTOSQL);} |
                     HAVING '=' {$$.entero=$1.entero;lexbegin(STEXTOSQL);} |
                     SELECT '=' {$$.entero=$1.entero;lexbegin(STEXTOSQL);};

modificador_online : nombre_modificador_online TEXTO_ONLINE {if (bloqueparse->online) free(bloqueparse->online);
                                                             bloqueparse->online=$2.cad;};

nombre_modificador_online : ONLINE '=' {$$.entero=$1.entero;lexbegin(SONLINE);};

palabra_protegida : NOINSERT {$$=$1;}|
                    NOENTER  {$$=$1;}|
                    NODELETE {$$=$1;}|
                    NOUPDATE {$$=$1;}|
                    NOORAINS {$$=$1;}|
                    NOORADEL {$$=$1;}|
                    NOCOMMIT {$$=$1;}|
                    NOLOCK   {$$=$1;}|
                    NOQUERY  {$$=$1;}|
                    UPDATE   {$$=$1;}|
                    INSERT   {$$=$1;}|
                    PDELETE   {$$=$1;}|
                    SICOMMIT {$$=$1;};

proteccion_bloque : palabra_protegida {switch ($1.entero) {
                                        case NOINSERT:bloqueparse->noinsert=1;
                                                      break;
                                        case NOENTER:bloqueparse->noenter=1;
                                                      break;
                                        case NOQUERY:bloqueparse->noquery=1;
                                                      break;
                                        case NODELETE:bloqueparse->nodelete=1;
                                                      break;
                                        case NOUPDATE:bloqueparse->noupdate=1;
                                                      break;
                                        case NOORAINS:bloqueparse->noorains=1;
                                                      break;
                                        case NOORADEL:bloqueparse->nooradel=1;
                                                      break; 
                                        case NOCOMMIT:bloqueparse->nocommit=1;
                                                      break;
                                        case NOLOCK:bloqueparse->nolock=1;
                                                      break;
                                        case UPDATE:bloqueparse->noupdate=0;
                                                      break;
                                        case INSERT:bloqueparse->noinsert=0;
                                                      break;
                                        case PDELETE:bloqueparse->nodelete=0;
                                                      break;
                                        case SICOMMIT:bloqueparse->sicommit=1;
                                                      break;
                                       }
                                      }|
                    palabra_protegida ',' condicion_proteccion {if ($3.entero) {
                                                                   switch ($1.entero) {
                                                                      case NOINSERT:bloqueparse->noinsert=1;
                                                                                    break;
                                                                      case NOENTER:bloqueparse->noenter=1;
                                                                                   break;
                                                                      case NOQUERY:bloqueparse->noquery=1;
                                                                                   break;
                                                                      case NODELETE:bloqueparse->nodelete=1;
                                                                                    break;
                                                                      case NOUPDATE:bloqueparse->noupdate=1;
                                                                                    break;
                                                                      case NOORAINS:bloqueparse->noorains=1;
                                                                                    break;
                                                                      case NOORADEL:bloqueparse->nooradel=1;
                                                                                    break;
                                                                      case NOCOMMIT:bloqueparse->nocommit=1;
                                                                                    break;
                                                                      case NOLOCK:bloqueparse->nolock=1;
                                                                                  break;
                                                                      case SICOMMIT:bloqueparse->sicommit=1;
                                                                                    break;
                                                                     }
                                                                   }
                                                                 }|
                    condicion_proteccion {if ($1.entero) {
                                              bloqueparse->noinsert=1;
                        bloqueparse->noupdate=1;
                        bloqueparse->nodelete=1;
                       }};


nombre_titulo : TITULO '=' {$$=$1;lexbegin(STITULO);} |
                AYUDA '=' {$$=$1;lexbegin(STITULO);};

definidor_titulo : nombre_titulo TEXTO_TITULO {switch($1.entero) {
                                                   case TITULO:if (bloqueparse->vi.titulo) free(bloqueparse->vi.titulo);
                                                               bloqueparse->vi.titulo=$2.cad;
                                                               break;
                                                   case AYUDA :if (bloqueparse->ayuda) free(bloqueparse->ayuda);
                                                               bloqueparse->ayuda=$2.cad;
                                                               break;
                                                }
                                             };


definidor_cursor : nombre_cursor texto_sql {if (buscafcursor(bloqueparse,bloqueparse->fcur[bloqueparse->ncur].nombre)!=NULL) {
                                               mensajeparser("Cursor duplicado %s en bloque %s",bloqueparse->fcur[bloqueparse->ncur].nombre,bloqueparse->nombre);
                                               return(-1);
                                             }
                                            if (bloqueparse->ncur>=MAXFCURSORES-1) final(("demasiados cursores %ld",MAXFCURSORES));
                                            bloqueparse->fcur[bloqueparse->ncur].sql=$2.cad;
                                            bloqueparse->fcur[bloqueparse->ncur].b=bloqueparse;
                                            bloqueparse->ncur++;};

nombre_cursor : CURSOR '=' IDENTIFICADOR {lexbegin(STEXTOSQL);
                                          strcpy(bloqueparse->fcur[bloqueparse->ncur].nombre,$3.cad);
                                          free($3.cad);};


menu : lista_opciones;

lista_opciones : opcion_menu lista_opciones |
                opcion_menu;

nombre_triger : cadena_parser {lexbegin(SOPMENU);$$.cad=$1.cad;};

triger_cadenas : nombre_triger                     {ftrigers *ft;
                                                    ft=dametriger($1.cad);
                                                    free($1.cad);
                                                    if (ft==NULL) {
                                                       mensajeparser("No encuentro triger %s",$1.cad);
                                                       return(-1);
                                                     }
                                                    $$.dato.ptr=duplicatriger(formenu->b,ft);} |
                nombre_triger ',' lista_parametros  {ftrigers *ft,*ft1;
                                                     ft1=dametriger($1.cad);
                                                     if (ft1==NULL) {
                                                        mensajeparser("No encuentro triger %s",$1.cad);
                                                        return(-1);
                                                      }
                                                     ft=$3.dato.ptr;
                                                     ft->b=formenu->b;
                                                     ft->fun=ft1->fun;
                                                     ft->nombre=$1.cad;
                                                     ft->param=realloc(ft->param,ft->nparam*sizeof(void *));
                                                     ft->tipoparam=realloc(ft->tipoparam,ft->nparam*sizeof(int));
                                                     $$.dato.ptr=ft;};


opcion_menu : OPMENU ',' triger_cadenas {if ($3.dato.ptr) {
                                            formenu->op[formenu->nopciones].opcion=$1.cad;
                                            formenu->op[formenu->nopciones].ft=$3.dato.ptr;
                                            formenu->nopciones++;
                                            if (funcionparsezoom) funcionparsezoom(formenu,formenu->op+formenu->nopciones-1,0);
                                          } else free($1.cad);}|
              OPMENU ',' definidor_triger {formenu->op[formenu->nopciones].opcion=$1.cad;
                                           formenu->op[formenu->nopciones].ft=$3.dato.ptr;
                                           formenu->nopciones++;
                                           if (funcionparsezoom) funcionparsezoom(formenu,formenu->op+formenu->nopciones-1,$3.dato.protegido);
                                           lexbegin(SOPMENU);};

%%
