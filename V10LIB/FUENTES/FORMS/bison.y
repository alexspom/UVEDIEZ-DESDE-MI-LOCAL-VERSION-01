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

%token <cad> PINTADO_PANTALLA
%token <cad> OPMENU
%token <cad> TEXTO_SQL
%token <cad> TEXTO_TITULO
%token <cad> TEXTO_ONLINE
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
%token <cad> TABLA
%token EXTRAPARSER
%token <entero> AYUDA
%token <entero> ONLINE
%token POSX
%token POSY
%token LEXCOLOR
%token <entero> TITULO
%token REGPAG
%token <cad> CAMPO
%token TECLA
%token CONTEXTUAL
%token FTRIGER
%token <entero> WHERE
%token <entero> ORDERBY
%token <entero> GROUPBY
%token <entero> HAVING
%token <entero> SELECT
%token CURSOR
%token <entero> NOINSERT
%token <entero> NOORAINS
%token <entero> NOORADEL
%token <entero> NOUPDATE
%token <entero> NODELETE
%token <entero> NOCOMMIT
%token <entero> UPDATE
%token <entero> INSERT
%token <entero> PDELETE
%token <entero> SICOMMIT
%token <entero> NOQUERY
%token <entero> NOLOCK
%token AQUERY
%token PQUERY
%token TQUERY
%token SOLOQUERY
%token TIMEOUT
%token <entero> NOENTER
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
%token <entero> PROTECT
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
%token <cad> IDENTIFICADOR
%token <cad> LEXCADENA
%token <doble> NUMERO
%token LEXEOF
%token CHECKBOX
%token ONCLICK
%token ONRIGHTCLICK
%token ONCENTERCLICK
%token ONMOUSEOVER
%token ONMOUSEOUT
%token ONDBCLICK
%token ONMOUSEMOVE
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
%token FICHERO
%token INCLUDE

%type <dato> triger_form
%type <dato> definidor_triger
%type <cad> unacadena_parser
%type <cad> cadena_parser
%type <cad> texto_sql
%type <cad> nombrecampo
%type <doble> nombre_tecla
%type <cad> nombre_boton_dupl
%type <dato> identificador_triger
%type <entero> lista_mod_triger
%type <entero> modificador_triger
%type <dato> lista_parametros
%type <dato> definicion_triger
%type <dato> triger_protegido
%type <entero> condicion_proteccion
%type <dato> parametro
%type <entero> lista_privilegios
%type <entero> nombre_modificador_oracle
%type <entero> palabra_protegida
%type <entero> nombre_modificador_online
%type <entero> nombre_titulo
%type <cad> nombre_triger
%type <dato> triger_cadenas

%code{
#pragma warning(disable: 4267)
#include "v10form.h"
#include "V10forparseaux.h"
#define INITIAL 0
#define SPINTADO 1
#define STEXTOSQL 2
#define SONLINE   3
#define STITULO   4
#define SOPMENU   5
static char buffer[10*MAXCADENA];
}
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
                INCLUDECSS   '=' cadena_parser	 {strcpy(forparse->includecss,$3); free($3);} |
                INCLUDEFICHEROCSS '=' cadena_parser	 {strcpy(forparse->includeficherocss,$3); free($3);} |
                INCLUDEHTML '=' cadena_parser	 {strcpy(forparse->includehtml,$3); free($3);} |
                INCLUDEFICHEROHTML '=' cadena_parser	 {strcpy(forparse->includeficherohtml,$3); free($3);} |
                definidor_bloque;

triger_form : PREFORM '=' definidor_triger {if (forparse->preform) liberatriger(forparse->preform);
                                            forparse->preform=$3.ptr;} |
               POSTFORM '=' definidor_triger {if (forparse->postform) liberatriger(forparse->postform);
                                              forparse->postform=$3.ptr;} |
               PRECOMMIT '=' definidor_triger {if (forparse->precommit) liberatriger(forparse->precommit);
                                               forparse->precommit=$3.ptr;} |
               POSTCOMMIT '=' definidor_triger {if (forparse->postcommit) liberatriger(forparse->postcommit);
                                                forparse->postcommit=$3.ptr;}|
               PREROLLBACK '=' definidor_triger {if (forparse->prerollback) liberatriger(forparse->prerollback);
                                                 forparse->prerollback=$3.ptr;} |
               POSTROLLBACK '=' definidor_triger {if (forparse->postrollback) liberatriger(forparse->postrollback);
                                                  forparse->postrollback=$3.ptr;};

unacadena_parser : LEXCADENA {quitacomillas(&$$,$1);free($1);} |
                LEXCADENA cadena_parser {char *temp;
                                         quitacomillas(&temp,$1);
                                         $$=calloc(1,strlen(temp)+strlen($2)+1);
                                         strcpy($$,temp);
                                         strcat($$,$2);
                                         free($1);
                                         free($2);
                                         free(temp);};

cadena_parser : unacadena_parser {strcpy(buffer,$1);
                                  sustituyedefines(buffer);
                                  free($1);
                                  $$=strdup(buffer);
                                 };

texto_sql : TEXTO_SQL {strcpy(buffer,$1);
                       eliminaretornos(buffer);
                       sustituyedefines(buffer);
                       free($1);
                       $$=strdup(buffer);
                      };

definidor_campo: nombre_campo modificadores_campo {if (enbloque) {
                                                      if (funcionparsecampo) funcionparsecampo(bloqueparse,campoparse);
                                                      if (campoparse->nteclas) campoparse->teclas=realloc(campoparse->teclas,campoparse->nteclas*sizeof(fteclas));
                                                         else {
                                                              free(campoparse->teclas);
                                                              campoparse->teclas=NULL;
                                                          }
                                                   } 
                                                  };

nombrecampo : IDENTIFICADOR {$$=$1;}|
              CAMPO         {$$=strdup("CAMPO");}|
              TABLA         {$$=strdup("TABLA");}|
              FICHERO       {$$=strdup("FICHERO");};

nombre_campo  :  CAMPO '=' nombrecampo {char *extra;
                                       int nc;
                                       if (enbloque) {
                                          if ((nc=damecampo(bloqueparse,$3))!=-1) {
                                             campoparse=bloqueparse->c+nc;
                                             //warning(("En bloque %s campo %s duplicado\n",bloqueparse->fichero,$3));
                                          } else {
                                             campoparse=bloqueparse->c+bloqueparse->ncamp;
                                             bloqueparse->ncamp++;
                                             campoparse->b=bloqueparse;
                                          }
                                        } else {
                                          if ((nc=damecampoform(forparse,$3))!=-1) {
                                             campoparse=forparse->c+nc;
                                             //warning(("En form campo %s duplicado\n",$3));
                                          } else {
                                             campoparse=forparse->c+forparse->ncamp; 
											 forparse->ncamp++;
                                             campoparse->b=NULL;
                                          }
                                        }
                                       campoparse->f=forparse;
                                       strcpy(campoparse->nombre,$3);
									                     campoparse->capitaliza=-1;
									                     campoparse->noupdate=-1;
                                       if (enbloque) {
                                          campoparse->enter=1;
                                          campoparse->tabla=1;
                                          campoparse->teclas=calloc(MAXFTECLAS,sizeof(fteclas));
                                        }
                                       if (damecaracextracampo) {
                                          extra=damecaracextracampo(campoparse);
                                          if (!es_blanco(extra)) {										     
									         v10log(LOGNORMAL,"Leyendo caracteristicas del campo %s\n",campoparse->nombre);
											 creabuffercadena(extra);
									         v10log(LOGNORMAL,"Leidas caracteristicas del campo %s\n",campoparse->nombre);
										  }
                                          free(extra);
                                       }
                                       free($3);
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


nombre_bloqueinter   :     BEGINBLOQUEFRM '=' IDENTIFICADOR {tratadefbloque($3);
                                                               free($3);};
nombre_bloquepan   :     BEGINBLOQUEPAN '=' IDENTIFICADOR {tratadefbloque($3);
                                                               free($3);};

nombre_bloque   :     BEGINBLOQUE '=' IDENTIFICADOR {
                                                     tratadefbloque($3);
                                                     if (creabuffer($3)) {
                                                        yyerror("No existe fichero");
                                                        free($3);
                                                        return(-1);
                                                      }
                                                      free($3);
                                                    };

pintado_pantalla : PINTADO_PANTALLA {fichero2vi($1,&bloqueparse->vi);free($1);};

cuerpo_bloque   :     pintado_pantalla modificadores_bloque ;

modificadores_bloque : modificadores_bloque modificador_bloque |
                       {
                         char *extra;
                         if (damecaracextrabloque) {
                           extra=damecaracextrabloque(forparse,bloqueparse,1);
                           if (!es_blanco(extra)) {
							   v10log(LOGNORMAL,"Leyendo caracteristicas del bloque %s\n",bloqueparse->nombre);
							   creabuffercadena(extra);							   
						       v10log(LOGNORMAL,"Leidas caracteristicas del bloque %s\n",bloqueparse->nombre);
							}
                           free(extra);
                         }
                       };

nombre_tecla : IDENTIFICADOR  {$$=traducetecla($1);
                               if ($$==0) mensajefcm(10,"Tecla no existe %s",$1);
                               free($1);} |
               NUMERO         {$$=$1;};



modificador_bloque  :  PADRE '=' IDENTIFICADOR      {if ((bloqueparse->padre=damebloque(forparse,$3))==NULL) {
                                                        mensajeparser("Bloque %s no definido",$3);
                                                        return(-1);
                                                      }
                                                     free($3);
                                                     }|
                       TABLA '=' IDENTIFICADOR      {
                                                     strcpy(bloqueparse->nombre,$3);
                                                     free($3);
                                                     if (damedefaulttabla) damedefaulttabla(bloqueparse);
                                                     }|
                       TABLA '=' IDENTIFICADOR IDENTIFICADOR {
                                                              strcpy(bloqueparse->nombre,$3);
                                                              strcat(bloqueparse->nombre," ");
                                                              strcat(bloqueparse->nombre,$4);
                                                              free($3);
                                                              free($4);
                                                              if (damedefaulttabla) damedefaulttabla(bloqueparse);
                                                            }|
                       EXTRAPARSER '(' cadena_parser ',' cadena_parser ')' {
                                                                            if (extraparser) {
                                                                               char *extra;
                                                                               extra=extraparser(bloqueparse,$3,$5);
                                                                               if (!es_blanco(extra)) {
                                                                                  creabuffercadena(extra);
                                                                                  free(extra);
                                                                                }
                                                                             }
                                                                            free($3);
                                                                            free($5);
                                                                           }|
                       NOROWID                      {bloqueparse->norowid=1;}|
                       POSX '=' NUMERO              {int x,desp;
                                                     x=bloqueparse->vi.w.x1;
                                                     desp=(int)$3;
                                                     bloqueparse->vi.w.x1=desp;
                                                     bloqueparse->vi.w.x2+=desp-x; } |
                       POSY '=' NUMERO              {int y,desp;
                                                     y=bloqueparse->vi.w.y1;
                                                     desp=(int)$3;
                                                     bloqueparse->vi.w.y1=desp;
                                                     bloqueparse->vi.w.y2+=desp-y; } |
                       INCLUDETDCSS '=' cadena_parser	 {strcpy(bloqueparse->includetdcss,$3); free($3);} |
                       INCLUDECSS   '=' cadena_parser	 {strcpy(bloqueparse->includecss,$3); free($3);} |
                       INCLUDEFICHEROCSS '=' cadena_parser	 {strcpy(bloqueparse->includeficherocss,$3); free($3);} |
                       INCLUDEHTML '=' cadena_parser	 {strcpy(bloqueparse->includehtml,$3); free($3);} |
                       INCLUDEFICHEROHTML '=' cadena_parser	 {strcpy(bloqueparse->includeficherohtml,$3); free($3);} |
                       WMARCOFRAME 		{ bloqueparse->wtipomarco=1; } |
                       WMARCOPESTANNA	{ bloqueparse->wtipomarco=2; } |
                       WSINMARCO 			{ bloqueparse->wtipomarco=3; } |
                       WPLEGADO											{ bloqueparse->wplegado = 1; } |
                       WDESPLEGADO                  { bloqueparse->wplegado = 2; } |
                       WPOSX '=' NUMERO              {bloqueparse->vipx.posx=(int)$3;} |
                       WPOSY '=' NUMERO              {bloqueparse->vipx.posy=(int)$3;} |
                       WLONX '=' NUMERO             {bloqueparse->vipx.lonx=(int)$3;} |
                       WLONY '=' NUMERO              {bloqueparse->vipx.lony=(int)$3;} |
                       WREGPAG '=' NUMERO            {bloqueparse->wregpag=(int)$3;} |
                       WPIXELX '=' NUMERO            {bloqueparse->pxcol=(int)$3;} |
                       WPIXELY '=' NUMERO            {bloqueparse->pxfila=(int)$3;} |
                       WFRAME '(' NUMERO ','  NUMERO ','  NUMERO ','  NUMERO ',' cadena_parser ',' cadena_parser ')' {
													bloqueparse->framesfile[bloqueparse->nbframesfile].posx=(int)$3;
													bloqueparse->framesfile[bloqueparse->nbframesfile].posy=(int)$5;
													bloqueparse->framesfile[bloqueparse->nbframesfile].lonx=(int)$7;
													bloqueparse->framesfile[bloqueparse->nbframesfile].lony=(int)$9;
													strcpy(bloqueparse->framesfile[bloqueparse->nbframesfile].nombre,$11); free($11);
													strcpy(bloqueparse->framesfile[bloqueparse->nbframesfile].includecss,$13); free($13);
													bloqueparse->nbframesfile++;}|
                       LEXCOLOR '=' IDENTIFICADOR   {
                                                     poncolorbloque(bloqueparse,$3);
                                                     defcolor=1;
                                                     free($3); } |
					   UPPER            {bloqueparse->capitaliza=FORMATOUPPER;}|
					   LOWER            {bloqueparse->capitaliza=FORMATOLOWER;}|
					   MIXED            {bloqueparse->capitaliza=0;}|
                       definidor_titulo             |
                       REGPAG '=' NUMERO            {bloqueparse->regpag=(int)$3;} |
                       TIMEOUT '=' definidor_triger ',' NUMERO {if (bloqueparse->ftimeout) liberatriger(bloqueparse->ftimeout);
                                                                bloqueparse->ftimeout=$3.ptr;
                                                                if (bloqueparse->ftimeout!=NULL) {
                                                                   bloqueparse->timeout=(long)$5;
                                                                 }
                                                               } |
                        PRETECLA '=' nombre_tecla ',' definidor_triger {int tec,i;
                                                                    ftrigers *ft;
                                                                    tec=(int)$3;
                                                                    ft=$5.ptr;
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
                                                                    tec=(int)$3;
                                                                    ft=$5.ptr;
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
                                                                    tec=(int)$3;
                                                                    ft=$5.ptr;
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
                       PREINSERT '=' definidor_triger       {if ($3.ptr) {
                                                                if (bloqueparse->fpreinsert) liberatriger(bloqueparse->fpreinsert);
                                                                bloqueparse->fpreinsert=$3.ptr;
                                                              }
                                                            }|
                       CONTEXTUAL '=' definidor_triger      {if ($3.ptr) {
                                                                if (bloqueparse->contextual) liberatriger(bloqueparse->contextual);
                                                                bloqueparse->contextual=$3.ptr;
                                                              }
                                                            }|
                       POSTINSERT '=' definidor_triger     {if ($3.ptr) {
                                                                if (bloqueparse->fpostinsert) liberatriger(bloqueparse->fpostinsert);
                                                                bloqueparse->fpostinsert=$3.ptr;
                                                              }
                                                            }|
                       PREUPDATE '=' definidor_triger      {if ($3.ptr) {
                                                                if (bloqueparse->fpreupdate) liberatriger(bloqueparse->fpreupdate);
                                                                bloqueparse->fpreupdate=$3.ptr;
                                                              }
                                                            }|
                       POSTUPDATE '=' definidor_triger     {if ($3.ptr) {
                                                                if (bloqueparse->fpostupdate) liberatriger(bloqueparse->fpostupdate);
                                                                bloqueparse->fpostupdate=$3.ptr;
                                                              }
                                                            }|
                       PREDELETE '=' definidor_triger      {if ($3.ptr) {
                                                                if (bloqueparse->fpredelete) liberatriger(bloqueparse->fpredelete);
                                                                bloqueparse->fpredelete=$3.ptr;
                                                              }
                                                            }|
                       POSTDELETE '=' definidor_triger     {if ($3.ptr) {
                                                                if (bloqueparse->fpostdelete) liberatriger(bloqueparse->fpostdelete);
                                                                bloqueparse->fpostdelete=$3.ptr;
                                                              }
                                                            }|
                       FINQUERY  '=' definidor_triger      {if ($3.ptr) {
                                                                if (bloqueparse->ffinquery) liberatriger(bloqueparse->ffinquery);
                                                                bloqueparse->ffinquery=$3.ptr;
                                                              }
                                                            }|
                       PREBLOQUE '=' definidor_triger      {if ($3.ptr) {
                                                                if (bloqueparse->fprebloque) liberatriger(bloqueparse->fprebloque);
                                                                bloqueparse->fprebloque=$3.ptr;
                                                              }
                                                            }|
                       POSTBLOQUE '=' definidor_triger     {if ($3.ptr) {
                                                                if (bloqueparse->fpostbloque) liberatriger(bloqueparse->fpostbloque);
                                                                bloqueparse->fpostbloque=$3.ptr;
                                                              }
                                                            }|
                       PREQUERY '=' definidor_triger       {if ($3.ptr) {
                                                                if (bloqueparse->fprequery) liberatriger(bloqueparse->fprequery);
                                                                bloqueparse->fprequery=$3.ptr;
                                                              }
                                                            }|
                       POSTQUERY '=' definidor_triger      {if ($3.ptr) {
                                                                if (bloqueparse->fpostquery) liberatriger(bloqueparse->fpostquery);
                                                                bloqueparse->fpostquery=$3.ptr;
                                                              }
                                                            }|
                       PREREGISTRO '=' definidor_triger    {if ($3.ptr) {
                                                                if (bloqueparse->fpreregistro) liberatriger(bloqueparse->fpreregistro);
                                                                bloqueparse->fpreregistro=$3.ptr;
                                                              }
                                                            }|
                       POSTREGISTRO '=' definidor_triger   {if ($3.ptr) {
                                                                if (bloqueparse->fpostregistro) liberatriger(bloqueparse->fpostregistro);
                                                                bloqueparse->fpostregistro=$3.ptr;
                                                              }
                                                            }|
                       PRECOMMIT '=' definidor_triger      {if ($3.ptr) {
                                                                if (bloqueparse->fprecommit) liberatriger(bloqueparse->fprecommit);
                                                                bloqueparse->fprecommit=$3.ptr;
                                                              }
                                                            }|
                       POSTCOMMIT '=' definidor_triger     {if ($3.ptr) {
                                                                if (bloqueparse->fpostcommit) liberatriger(bloqueparse->fpostcommit);
                                                                bloqueparse->fpostcommit=$3.ptr;
                                                              }
                                                            }|
                       PREROLLBACK '=' definidor_triger      {if ($3.ptr) {
                                                                if (bloqueparse->fprerollback) liberatriger(bloqueparse->fprerollback);
                                                                bloqueparse->fprerollback=$3.ptr;
                                                              }
                                                            }|
                       POSTROLLBACK '=' definidor_triger     {if ($3.ptr) {
                                                                if (bloqueparse->fpostrollback) liberatriger(bloqueparse->fpostrollback);
                                                                bloqueparse->fpostrollback=$3.ptr;
                                                              }
                                                            }|
                       PREPINTA '=' definidor_triger       {if ($3.ptr) {
                                                                if (bloqueparse->fprepinta) liberatriger(bloqueparse->fprepinta);
                                                                bloqueparse->fprepinta=$3.ptr;
                                                              }
                                                            }|
                       POSTPINTA '=' definidor_triger      {if ($3.ptr) {
                                                                if (bloqueparse->fpostpinta) liberatriger(bloqueparse->fpostpinta);
                                                                bloqueparse->fpostpinta=$3.ptr;
                                                              }
                                                            }|
                       ONPINTA '=' definidor_triger        {if ($3.ptr) {
                                                                if (bloqueparse->fonpinta) liberatriger(bloqueparse->fonpinta);
                                                                bloqueparse->fonpinta=$3.ptr;
                                                              }
                                                            }|

                       ONCLICK '=' definidor_triger        {if ($3.ptr) {
                                                                if (bloqueparse->feventos.onclick) liberatriger(bloqueparse->feventos.onclick);
                                                                bloqueparse->feventos.onclick=$3.ptr;
                                                              }
                                                            }|
                       ONRIGHTCLICK '=' definidor_triger   {if ($3.ptr) {
                                                                if (bloqueparse->feventos.onrightclick) liberatriger(bloqueparse->feventos.onrightclick);
                                                                bloqueparse->feventos.onrightclick=$3.ptr;
                                                              }
                                                            }|
                       ONCENTERCLICK '=' definidor_triger  {if ($3.ptr) {
                                                                if (bloqueparse->feventos.oncenterclick) liberatriger(bloqueparse->feventos.oncenterclick);
                                                                bloqueparse->feventos.oncenterclick=$3.ptr;
                                                              }
                                                            }|
                       ONMOUSEOVER '=' definidor_triger    {if ($3.ptr) {
                                                                if (bloqueparse->feventos.onmouseover) liberatriger(bloqueparse->feventos.onmouseover);
                                                                bloqueparse->feventos.onmouseover=$3.ptr;
                                                              }
                                                            }|
                       ONMOUSEOUT '=' definidor_triger     {if ($3.ptr) {
                                                                if (bloqueparse->feventos.onmouseout) liberatriger(bloqueparse->feventos.onmouseout);
                                                                bloqueparse->feventos.onmouseout=$3.ptr;
                                                              }
                                                            }|
                       ONDBCLICK '=' definidor_triger      {if ($3.ptr) {
                                                                if (bloqueparse->feventos.ondbclick) liberatriger(bloqueparse->feventos.ondbclick);
                                                                bloqueparse->feventos.ondbclick=$3.ptr;
                                                              }
                                                            }|
                       ONMOUSEMOVE '=' definidor_triger    {if ($3.ptr) {
                                                                if (bloqueparse->feventos.onmousemove) liberatriger(bloqueparse->feventos.onmousemove);
                                                                bloqueparse->feventos.onmousemove=$3.ptr;
                                                              }
                                                            }|
                       WGRAFICA '=' IDENTIFICADOR ',' NUMERO ',' NUMERO ',' NUMERO ',' NUMERO ',' NUMERO {
                       																					fstats *fs=bloqueparse->stats + bloqueparse->nbstats;
                                                                fs->nombre = $3;
                                                                fs->posx=(int)$5;
                                                                fs->posy=(int)$7;
                                                                fs->lonx=(int)$9;
                                                                fs->lony=(int)$11;
                                                                fs->enmarcado = (int)$13;
                                                                bloqueparse->nbstats++;
                       					                           } |
                       definidor_boton |
					             BOTONERA '=' IDENTIFICADOR {fbotoneras *fbot=bloqueparse->fbot+bloqueparse->numbotoneras;
                                                   if (duplicabotonera($3,fbot)) {
                                                      mensajefcm(10,"No existe botonera %s\n",$3);
                                                      free($3);
                                                      return(-1);
                                                   }
                                                   free($3);
                                                   bloqueparse->numbotoneras++;}|
                       BOTONERA '=' IDENTIFICADOR ',' NUMERO ',' NUMERO  ',' NUMERO ',' NUMERO  lista_botones 
                                     {fbotoneras *fbot=bloqueparse->fbot+bloqueparse->numbotoneras;
                                        fbot->nombre=$3;
                                        fbot->posx=(int)$5;
                                        fbot->posy=(int)$7;
                                        fbot->lonx=(int)$9;
                                        fbot->lony=(int)$11;
                                        bloqueparse->numbotoneras++;} |
                       INCLUDE '=' IDENTIFICADOR  {if (creabuffer($3)) {
                                                        yyerror("No existe fichero");
                                                        free($3);
                                                        return(-1);
                                                      }
                                                      free($3);
                                                      }|
                      AJAX '(' IDENTIFICADOR ',' cadena_parser ',' cadena_parser ',' cadena_parser ',' cadena_parser ',' cadena_parser ',' NUMERO ')' {
                      						v10ajax *aj = bloqueparse->ajax+ bloqueparse->nbajax;
                      						aj->id 			 = $3;
                      						aj->objetojs = $5;
                      						aj->tipo 		 = $7;
                      						aj->modulo 	 = $9;
                      						aj->nombre   = $11;
                      						aj->params   = $13;
                      						aj->frecuencia  = (int)$15;
                      						bloqueparse->nbajax++;
                      					} |
                      SIDEBAROCULTO 	{ bloqueparse->sidebaroculto = 1;}|
                      SIDEBARVISIBLE  { bloqueparse->sidebaroculto = 2;}|
                      COMPONENTE '(' IDENTIFICADOR ',' cadena_parser ',' cadena_parser ',' cadena_parser ',' cadena_parser ',' NUMERO ')' {
                      					  v10comphtml *co = bloqueparse->comphtml + bloqueparse->nbcomphtml;
                      						co->id       = $3;
                      						co->tipo 		 = $5;
                      						co->modulo 	 = $7;
                      						co->nombre   = $9;
                      						co->params   = $11;
                      						co->visible  = (int)$13;
                      						bloqueparse->nbcomphtml++;
                      }  ;

modificador_boton:  INCLUDECSS '=' cadena_parser	 {strcpy(botonparse->includecss,$3);free($3);} |
                    ESTILOCSS '=' cadena_parser	 {strcpy(botonparse->estilocss,$3); free($3);} |
                    BOTONOCULTO '=' NUMERO {botonparse->oculto=(int)$3;} |
                    BOTONDISABLED '=' NUMERO {botonparse->disabled=(int)$3;};

modificadores_boton: ',' modificador_boton modificadores_boton |
                        	;


nombre_boton: BOTON '=' IDENTIFICADOR ',' {
               fbotones *b=bloqueparse->fb+bloqueparse->numbotones;
               bloqueparse->numbotones++;
               b->nombre=$3;
               botonparse = b;};

nombre_boton_dupl: BOTON '=' IDENTIFICADOR {$$ = $3;};


definidor_boton:  nombre_boton_dupl {
										fbotones *b=bloqueparse->fb+bloqueparse->numbotones;
                 		if (duplicaboton($1,b)) {
                     mensajefcm(10,"No existe boton %s\n",$1);
                     free($1);
                     return(-1);
                  	}
                  	free($1);
                  	bloqueparse->numbotones++;
                  } |
                  nombre_boton NUMERO ',' NUMERO ',' NUMERO ',' NUMERO ',' cadena_parser ',' IDENTIFICADOR ',' nombre_tecla modificadores_boton
                                                            {
                                                             botonparse->posx=(int)$2;
                                                             botonparse->posy=(int)$4;
                                                             botonparse->lonx=(int)$6;
                                                             botonparse->lony=(int)$8;
                                                             botonparse->texto=$10;
                                                             botonparse->image=$12;
                                                             botonparse->tecla=(int)$14;
                                                             }|
                  nombre_boton NUMERO ',' NUMERO ',' NUMERO ',' NUMERO ',' cadena_parser ',' IDENTIFICADOR ',' nombre_tecla ',' cadena_parser modificadores_boton
                                                            {
                                                             botonparse->posx=(int)$2;
                                                             botonparse->posy=(int)$4;
                                                             botonparse->lonx=(int)$6;
                                                             botonparse->lony=(int)$8;
                                                             botonparse->texto=$10;
                                                             botonparse->image=$12;
                                                             botonparse->tecla=(int)$14;
                                                             botonparse->tooltip=strdup(v10translate($16));
                                                             free($16);
                                                             };

lista_botones : ',' IDENTIFICADOR lista_botones {fbotoneras *fbot=bloqueparse->fbot+bloqueparse->numbotoneras;
                                                 fbotones *fb;
                                                 fb=damebotonbloque(bloqueparse,$2);
                                                 if (fb==NULL) {
                                                    mensajeparser("no existe boton %s",$2);
                                                    free($2);
                                                    return(-1);
                                                 }
                                                 free($2);
                                                 fbot->b[fbot->numbotones]=fb;
                                                 fbot->numbotones++;}|
                                               { fbotoneras *fbot=bloqueparse->fbot+bloqueparse->numbotoneras;
                                                 fbot->b=calloc(MAXBOTONES,sizeof(fbotones **));
                                                 fbot->numbotones=0;};

identificador_triger     : IDENTIFICADOR {ftrigers *ft;
                                          char *aux;
                                          aux=strchr($1,'.');
                                          if (aux) {
                                             *aux=0;
                                             ft=dametrigerdll($1,aux+1);
                                             $$.tipo=1;
                                             *aux='.';
                                           } else {
                                             ft=dametriger($1);
                                             $$.tipo=0;
                                           }
                                          if (ft==NULL) {
                                             mensajeparser("No encuentro triger %s",$1);
                                             free($1);
                                             return(-1);
                                           }
                                          free($1);
                                          $$.ptr=ft;
                                         };

definicion_triger : lista_mod_triger identificador_triger    {ftrigers *ft;
                                                              ft=$2.ptr;
                                                              ft=duplicatriger(bloqueparse,ft);
                                                              ft->opciones=$1;
                                                              $$.ptr=ft;
                                                              if ($2.tipo) {
                                                                 liberatriger($2.ptr);
                                                               }
                                                             } |
                    lista_mod_triger identificador_triger '(' lista_parametros ')' {ftrigers *ft,*ft1;
                                                                                    ft1=$2.ptr;
                                                                                    ft=$4.ptr;
                                                                                    ft->b=bloqueparse;
                                                                                    ft->fun=ft1->fun;
                                                                                    ft->nombre=strdup(ft1->nombre);
                                                                                    ft->param=realloc(ft->param,ft->nparam*sizeof(void *));
                                                                                    ft->tipoparam=realloc(ft->tipoparam,ft->nparam*sizeof(int));
                                                                                    ft->opciones=$1;
                                                                                    $$.ptr=ft;
                                                                                    if ($2.tipo) {
                                                                                       liberatriger($2.ptr);
                                                                                      }}|
                    TNULL {$$.ptr=NULL;};

modificador_triger : '-' {$$=CINVERSO;} |
                     '$' {$$=CIGNORE;} |
                     '%' {$$=CSOLOMEN;} |
                     '@' {$$=CTERMINA;} |
                     '+' {$$=CSUCCESS;} |
                     '!' {$$=CPREGUNTA;} |
                     '&' {$$=CFUNCION;};

lista_mod_triger : modificador_triger lista_mod_triger {$$=$1 | $2;} |
                             {$$=0;};

triger_protegido : condicion_proteccion ',' definicion_triger {$$.protegido=$1;
                                                               $$.ptr=$3.ptr;
                                                              }|
                   definicion_triger                          {$$.ptr=$1.ptr;
                                                               $$.protegido=0;};

definidor_triger : triger_protegido {if ($1.protegido) {
                                        liberatriger($1.ptr);
                                        $$.ptr=NULL;
                                      } else {
                                        $$.ptr=$1.ptr;
                                      }
                                      $$.protegido=$1.protegido;
                                    };


lista_parametros : parametro                              {ftrigers *ft;
                                                           ft=calloc(1,sizeof(ftrigers));
                                                           ft->param=calloc(MAXPARAM,sizeof(void *));
                                                           ft->tipoparam=calloc(MAXPARAM,sizeof(int));
                                                           ft->nparam=1;
                                                           ft->param[0]=$1.ptr;
                                                           ft->tipoparam[0]=$1.tipo;
                                                           $$.ptr=ft;
                                                          } |
                   lista_parametros ',' parametro         {ftrigers *ft=$1.ptr;
                                                           if (ft->nparam>=MAXPARAM) {
                                                              mensajeparser("desmasiados parametros en triger");
                                                              return(-1);
                                                            }
                                                           ft->param[ft->nparam]=$3.ptr;
                                                           ft->tipoparam[ft->nparam]=$3.tipo;
                                                           ft->nparam++;
                                                           $$.ptr=ft;
                                                           };

parametro : cadena_parser {$$.ptr=$1;$$.tipo=PARAMCADENA;}|
            definicion_triger {$$.ptr=$1.ptr;$$.tipo=PARAMTRIGER;};

modificadores_campo: ',' modificador_campo modificadores_campo|
                     ;

lista_privilegios : cadena_parser {$$=esta_protegido($1);free($1);}|
                    cadena_parser ',' lista_privilegios {if (esta_protegido($1)) $$=esta_protegido($1);
                                                  else        $$=$3;
                             free($1);};


condicion_proteccion : PROTECT   {if (protegidoform<1) $$=1; else $$=0;}|
                       PROTECT '(' lista_privilegios ')' {$$=$3;};

modificador_where: WHERE '=' {lexbegin(STEXTOSQL);};

opciones_combox:  cadena_parser  {  if (campoparse->combox.nopc>=MAXOPMENUS) {
                                     mensajeparser("Solo se admiten un máximo de %d opciones en un Combox",MAXOPMENUS);
                                     return(-1);
                                   }
                                   v10ansitooem($1,$1);
                                   campoparse->combox.opc[campoparse->combox.nopc]=strdup($1);
                                   campoparse->combox.nopc++;
                                } |
                  cadena_parser ',' opciones_combox {  if (campoparse->combox.nopc>=MAXOPMENUS) {
                                                        mensajeparser("Solo se admiten un máximo de %d opciones en un Combox",MAXOPMENUS);
                                                        return(-1);
                                                      }
                                                      v10ansitooem($1,$1);
                                                      campoparse->combox.opc[campoparse->combox.nopc]=strdup($1);
                                                      campoparse->combox.nopc++;
                                                   };

modificador_campo: NOENTER   {campoparse->enter=0;}|
                   NOENTER  '(' lista_privilegios ')' {if ($3) {
                                                         campoparse->enter=0;
                                                       }
                                                      } |
                   INCLUDECSS '=' cadena_parser	 {strcpy(campoparse->includecss,$3); free($3);} |
                   ESTILOCSS '=' cadena_parser	 {strcpy(campoparse->estilocss,$3); free($3);} |
	               NOINPUT   {campoparse->noinput=1;}|
                   NOINPUT  '(' lista_privilegios ')' {if ($3) {
                                                         campoparse->noinput=1;
                                                       }
                                                      } |
                   modificador_where texto_sql {campoparse->where=$2;}|
                   AUTOENTER {campoparse->autoenter=1;}|
                   UPPER     {campoparse->capitaliza=FORMATOUPPER;}|
                   LOWER     {campoparse->capitaliza=FORMATOLOWER;}|
                   MIXED     {campoparse->capitaliza=0;}|
                   TRADUCIBLE {campoparse->traducible=strdup("");}|
                   TRADUCIBLE'(' cadena_parser ')' {campoparse->traducible=strdup("$3");}|
                   TOOLTIP '(' cadena_parser ')' {if (v10usaansi) v10ansitooem($3,$3);
                                                  campoparse->tooltip=strdup(v10translate($3));
                                                  free($3);}|
                   FUNTOOLTIP '=' definidor_triger   {if (campoparse->funtooltip) liberatriger(campoparse->funtooltip);
                                                    campoparse->funtooltip=$3.ptr;}|
                   NOPREF    {campoparse->nopref=1;}|
                   AUXILIAR  {campoparse->tabla=0;}|
                   NOUPDATE  {campoparse->noupdate=1;}|
                   NOUPDATE  '(' lista_privilegios ')' {if ($3) campoparse->noupdate=1;}|
                   UPDATE    {campoparse->noupdate=0;}|
                   UPDATE    '(' lista_privilegios ')' {if ($3==0) campoparse->noupdate=0;}|
                   SCAN      {campoparse->scan=1;}|
                   SCAN '(' NUMERO ')'     {campoparse->scan=(int)$3;}|
                   PREFIJO '=' IDENTIFICADOR {campoparse->prefijo=$3;}|
                   AUTOTRANSMIT {campoparse->autotransmit=1;}|
                   condicion_proteccion {if ($1) campoparse->noupdate=1;}|
                   DISPLAY   {if (protegidoform<1) {
                                 campoparse->noupdate=1;
                                 campoparse->invisible=1;
                               }
                             }|
                   DISPLAY '(' lista_privilegios ')' {if ($3) {
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
                                                  strcpy(campoparse->nvirtual,$3);
                                                  free($3);
                                                 }|
                   OCULTO {campoparse->oculto=1;}|
                   cadena_parser          {if (campoparse->oculto==0) {
                                              mensajeparser("campo %s con formato no oculto",campoparse->nombre);
                                            } else {
                                             if (v10usaansi) v10ansitooem($1,$1);
                                             analizatokendia($1,NULL,&campoparse->tipo,&campoparse->format,&campoparse->dec,&campoparse->lvar,&campoparse->lvar,NULL);
                                             campoparse->lon=tamv10tipo(campoparse->tipo,campoparse->lvar+1);
                                             if (campoparse->virtual) {
                                                mensajefcm(10,"En bloque %s Campo %s virtual oculto con formato",bloqueparse->fichero,campoparse->nombre);
                                             }
                                             free($1);
                                            }
                                           }|
                   TITULO '(' cadena_parser ')' {campoparse->titulo=strdup($3);}|
                   WPOSX '=' NUMERO {  campoparse->vipx.posx = (int)$3; } |
                   WPOSY '=' NUMERO {  campoparse->vipx.posy = (int)$3; } |
                   WLONX '=' NUMERO {  campoparse->vipx.lonx = (int)$3; } |
                   WLONY '=' NUMERO {  campoparse->vipx.lony = (int)$3; } |
                   POSTCHANGE '=' definidor_triger {if ($3.ptr) {
                                                       if (campoparse->change) liberatriger(campoparse->change);
                                                       campoparse->change=$3.ptr;;
                                                     }
                                                    }|
                   CONTEXTUAL '=' definidor_triger {if ($3.ptr) {
                                                       if (campoparse->contextual) liberatriger(campoparse->contextual);
                                                       campoparse->contextual=$3.ptr;;
                                                     }
                                                    }|
                   PREFIELD '=' definidor_triger   {if ($3.ptr) {
                                                       if (campoparse->pref) liberatriger(campoparse->pref);
                                                       campoparse->pref=$3.ptr;
                                                     }
                                                    }|
                   POSTFIELD '=' definidor_triger  {if ($3.ptr) {
                                                       if (campoparse->postf) liberatriger(campoparse->postf);
                                                       campoparse->postf=$3.ptr;;
                                                     }
                                                    }|
                   PREPINTA '=' definidor_triger   {if ($3.ptr) {
                                                       if (campoparse->prepinta) liberatriger(campoparse->prepinta);
                                                       campoparse->prepinta=$3.ptr;;
                                                     }
                                                    }|
                   POSTPINTA '=' definidor_triger  {if ($3.ptr) {
                                                       if (campoparse->postpinta) liberatriger(campoparse->postpinta);
                                                       campoparse->postpinta=$3.ptr;;
                                                     }
                                                    }|
				   CONVIERTE '=' definidor_triger ';' definidor_triger
				                                   {if ($3.ptr) {
                                                       if (campoparse->convfrombd) liberatriger(campoparse->convfrombd);
                                                       campoparse->convfrombd=$3.ptr;
                                                     }
												    if ($5.ptr) {
                                                       if (campoparse->conv2bd) liberatriger(campoparse->conv2bd);
                                                       campoparse->conv2bd=$5.ptr;
                                                     }
												   }|
                   ONPINTA '=' definidor_triger    {if ($3.ptr) {
                                                       if (campoparse->onpinta) liberatriger(campoparse->onpinta);
                                                       campoparse->onpinta=$3.ptr;
                                                     }
                                                    }|
                   ONCLICK '=' definidor_triger    {if ($3.ptr) {
                                                       if (campoparse->feventos.onclick) liberatriger(campoparse->feventos.onclick);
                                                       campoparse->feventos.onclick=$3.ptr;
                                                     }
                                                    }|
                   ONRIGHTCLICK '=' definidor_triger   {if ($3.ptr) {
                                                           if (campoparse->feventos.onrightclick) liberatriger(campoparse->feventos.onrightclick);
                                                           campoparse->feventos.onrightclick=$3.ptr;
                                                        }
                                                       }|
                   ONCENTERCLICK '=' definidor_triger  {if ($3.ptr) {
                                                           if (campoparse->feventos.oncenterclick) liberatriger(campoparse->feventos.oncenterclick);
                                                           campoparse->feventos.oncenterclick=$3.ptr;
                                                        }
                                                       }|
                   ONMOUSEOVER '=' definidor_triger    {if ($3.ptr) {
                                                           if (campoparse->feventos.onmouseover) liberatriger(campoparse->feventos.onmouseover);
                                                          campoparse->feventos.onmouseover=$3.ptr;
                                                         }
                                                       }|
                   ONMOUSEOUT '=' definidor_triger     {if ($3.ptr) {
                                                           if (campoparse->feventos.onmouseout) liberatriger(campoparse->feventos.onmouseout);
                                                           campoparse->feventos.onmouseout=$3.ptr;
                                                         }
                                                       }|
                   ONDBCLICK '=' definidor_triger    {if ($3.ptr) {
                                                         if (campoparse->feventos.ondbclick) liberatriger(campoparse->feventos.ondbclick);
                                                         campoparse->feventos.ondbclick=$3.ptr;
                                                       }
                                                      }|
                   ONMOUSEMOVE '=' definidor_triger    {if ($3.ptr) {
                                                           if (campoparse->feventos.onmousemove) liberatriger(campoparse->feventos.onmousemove);
                                                           campoparse->feventos.onmousemove=$3.ptr;
                                                        }
                                                       }|
                   CHECKBOX '(' cadena_parser ',' cadena_parser ')' {
                                                                    campoparse->checkbox=calloc(1,sizeof(checkboxes));
                                                                    campoparse->checkbox->activo=1;
                                                                    v10ansitooem($3,$3);
                                                                    campoparse->checkbox->valor_false=strdup($3);
                                                                    v10ansitooem($5,$5);
                                                                    campoparse->checkbox->valor_true=strdup($5);
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
                                           if ((int)$3>campoparse->combox.nopc-1) {
                                              mensajeparser("Índice seleccionado para el COMBOX supera las opciones (%d)",campoparse->combox.nopc);
                                             return(-1);
                                            }
                                           campoparse->combox.index=(int)$3;
                                          }|
          		   COMBOXREGPAG '=' NUMERO {
                                           if (campoparse->combox.activo==0) {
                                              mensajeparser("Modificador de campo REGPAGCOMBOX antes de definir el COMBOX");
                                              return(-1);
                                            }
                                           campoparse->combox.regpag=(int)$3;
                                          }|

                   TECLA '=' nombre_tecla ',' definidor_triger {int tec,i;
                                                                 ftrigers *ft;
                                                                 tec=(int)$3;
                                                                 ft=$5.ptr;
                                                                 if (ft) {
                                                                    if (enbloque) {
                                                                       for (i=0;i<campoparse->nteclas;i++) if (campoparse->teclas[i].t==tec) break;
                                                                       if (i<campoparse->nteclas) liberatriger(campoparse->teclas[i].trig);
                                                                       ft=$5.ptr;
                                                                       campoparse->teclas[i].trig=ft;
                                                                       campoparse->teclas[i].t=tec;
                                                                       campoparse->teclas[i].b=bloqueparse;
                                                                       if (i==campoparse->nteclas) campoparse->nteclas++;
                                                                      } else liberatriger(ft);
                                                                  }
                                                                 }|
                  REGPAG '=' NUMERO {
                                        campoparse->regpag=(int)$3;
                                    }|
                  FICHERO           {
                                        campoparse->fichero=1;
                                        strcpy(campoparse->nombrefijo,"");
                                    }|
                  FICHERO '(' cadena_parser ')' {
                                        campoparse->fichero=1;
                                        strcpy(campoparse->nombrefijo,$3);
                                    };

modificador_oracle : nombre_modificador_oracle texto_sql {switch ($1) {
                                                            case WHERE:if (bloqueparse->where) free(bloqueparse->where);
                                                                       bloqueparse->where=$2;
                                                                       break;
                                                            case ORDERBY:if (bloqueparse->orderby) free(bloqueparse->orderby);
                                                                       bloqueparse->orderby=$2;
                                                                       break;
                                                            case GROUPBY:if (bloqueparse->groupby) free(bloqueparse->groupby);
                                                                       bloqueparse->groupby=$2;
                                                                       break;
                                                            case HAVING:if (bloqueparse->having) free(bloqueparse->having);
                                                                       bloqueparse->having=$2;
                                                                       break;
                                                            case SELECT:if (bloqueparse->select) free(bloqueparse->select);
                                                                       bloqueparse->extraselect=$2;
                                                                       break;
                                                           }
                                                        };

nombre_modificador_oracle : WHERE '=' {$$=$1;lexbegin(STEXTOSQL);} |
                     ORDERBY '=' {$$=$1;lexbegin(STEXTOSQL);} |
                     GROUPBY '=' {$$=$1;lexbegin(STEXTOSQL);} |
                     HAVING '=' {$$=$1;lexbegin(STEXTOSQL);} |
                     SELECT '=' {$$=$1;lexbegin(STEXTOSQL);};

modificador_online : nombre_modificador_online TEXTO_ONLINE {if (bloqueparse->online) free(bloqueparse->online);
                                                             bloqueparse->online=$2;};

nombre_modificador_online : ONLINE '=' {$$=$1;lexbegin(SONLINE);};

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

proteccion_bloque : palabra_protegida {switch ($1) {
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
                    palabra_protegida ',' condicion_proteccion {if ($3) {
                                                                   switch ($1) {
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
                    condicion_proteccion {if ($1) {
                                              bloqueparse->noinsert=1;
                        bloqueparse->noupdate=1;
                        bloqueparse->nodelete=1;
                       }};


nombre_titulo : TITULO '=' {$$=$1;lexbegin(STITULO);} |
                AYUDA '=' {$$=$1;lexbegin(STITULO);};

definidor_titulo : nombre_titulo TEXTO_TITULO {switch($1) {
                                                   case TITULO:if (bloqueparse->vi.titulo) free(bloqueparse->vi.titulo);
                                                               bloqueparse->vi.titulo=$2;
                                                               break;
                                                   case AYUDA :if (bloqueparse->ayuda) free(bloqueparse->ayuda);
                                                               bloqueparse->ayuda=$2;
                                                               break;
                                                }
                                             };


definidor_cursor : nombre_cursor texto_sql {if (buscafcursor(bloqueparse,bloqueparse->fcur[bloqueparse->ncur].nombre)!=NULL) {
                                               mensajeparser("Cursor duplicado %s en bloque %s",bloqueparse->fcur[bloqueparse->ncur].nombre,bloqueparse->nombre);
                                               return(-1);
                                             }
                                            if (bloqueparse->ncur>=MAXFCURSORES-1) final(("demasiados cursores %ld",MAXFCURSORES));
                                            bloqueparse->fcur[bloqueparse->ncur].sql=$2;
                                            bloqueparse->fcur[bloqueparse->ncur].b=bloqueparse;
                                            bloqueparse->ncur++;};

nombre_cursor : CURSOR '=' IDENTIFICADOR {lexbegin(STEXTOSQL);
                                          strcpy(bloqueparse->fcur[bloqueparse->ncur].nombre,$3);
                                          free($3);};


menu : lista_opciones;

lista_opciones : opcion_menu lista_opciones |
                opcion_menu;

nombre_triger : cadena_parser {lexbegin(SOPMENU);$$=$1;};

triger_cadenas : nombre_triger                     {ftrigers *ft;
                                                    ft=dametriger($1);
                                                    free($1);
                                                    if (ft==NULL) {
                                                       mensajeparser("No encuentro triger %s",$1);
                                                       return(-1);
                                                     }
                                                    $$.ptr=duplicatriger(formenu->b,ft);} |
                nombre_triger ',' lista_parametros  {ftrigers *ft,*ft1;
                                                     ft1=dametriger($1);
                                                     if (ft1==NULL) {
                                                        mensajeparser("No encuentro triger %s",$1);
                                                        return(-1);
                                                      }
                                                     ft=$3.ptr;
                                                     ft->b=formenu->b;
                                                     ft->fun=ft1->fun;
                                                     ft->nombre=$1;
                                                     ft->param=realloc(ft->param,ft->nparam*sizeof(void *));
                                                     ft->tipoparam=realloc(ft->tipoparam,ft->nparam*sizeof(int));
                                                     $$.ptr=ft;};


opcion_menu : OPMENU ',' triger_cadenas {if ($3.ptr) {
                                            formenu->op[formenu->nopciones].opcion=$1;
                                            formenu->op[formenu->nopciones].ft=$3.ptr;
                                            formenu->nopciones++;
                                            if (funcionparsezoom) funcionparsezoom(formenu,formenu->op+formenu->nopciones-1,0);
                                          } else free($1);}|
              OPMENU ',' definidor_triger {formenu->op[formenu->nopciones].opcion=$1;
                                           formenu->op[formenu->nopciones].ft=$3.ptr;
                                           formenu->nopciones++;
                                           if (funcionparsezoom) funcionparsezoom(formenu,formenu->op+formenu->nopciones-1,$3.protegido);
                                           lexbegin(SOPMENU);};

%%
