/*
* Módulo : V10FORLEX.C
* Objeto:  Analizador sintactico de formularios
*
*
* Autor  : Eduardo Alsina Alvarez
* Fecha  : 08-08-2007

* MODIFICACIONES
* ---------------------------
*/
%x SPINTADO
%x STEXTOSQL
%x SONLINE
%x STITULO
%x SOPMENU
%x STEXTOPLSQLD
%{
#pragma warning(disable: 4267)
#include "v10form.h"
#include "v10forparseaux.h"
#include "v10parse.h"
int numlin=0;
static char *restosql;
static void mensajepordefecto(char *cadena,...)
{
   va_list arg;
   va_start(arg,cadena);
   vmensajefcm(10,cadena,arg);
   va_end(arg);
}

void (*mensajeparser)(char *cadena,...)=mensajepordefecto;
typedef struct {
        char *nombre;
        int val;
      } identificadores;

static identificadores ident[]={ {"PREINSERT",PREINSERT},
                                 {"POSTINSERT",POSTINSERT},
                                 {"PREUPDATE",PREUPDATE},
                                 {"POSTUPDATE",POSTUPDATE},
                                 {"PREDELETE",PREDELETE},
                                 {"POSTDELETE",POSTDELETE},
                                 {"PREQUERY",PREQUERY},
                                 {"POSTQUERY",POSTQUERY},
                                 {"FINQUERY",FINQUERY},
                                 {"PREREGISTRO",PREREGISTRO},
                                 {"POSTREGISTRO",POSTREGISTRO},
                                 {"PREBLOQUE",PREBLOQUE},
                                 {"POSTBLOQUE",POSTBLOQUE},
                                 {"PREFORM",PREFORM},
                                 {"POSTFORM",POSTFORM},
                                 {"PRECOMMIT",PRECOMMIT},
                                 {"POSTCOMMIT",POSTCOMMIT},
                                 {"PREROLLBACK",PREROLLBACK},
                                 {"POSTROLLBACK",POSTROLLBACK},
                                 {"BEGINBLOQUE",BEGINBLOQUE},
                                 {"BEGINBLOQUEFRM",BEGINBLOQUEFRM},
                                 {"BEGINBLOQUEPAN",BEGINBLOQUEPAN},
                                 {"ENDBLOQUE",ENDBLOQUE},
                                 {"PADRE",PADRE},
                                 {"TABLA",TABLA},
                                 {"EXTRAPARSER",EXTRAPARSER},
                                 {"AYUDA",AYUDA},
                                 {"ONLINE",ONLINE},
                                 {"POSX",POSX},
                                 {"POSY",POSY},
                                 {"COLOR",LEXCOLOR},
                                 {"TITULO",TITULO},
                                 {"REGPAG",REGPAG},
                                 {"CAMPO",CAMPO},
                                 {"TECLA",TECLA},
                                 {"CONTEXTUAL",CONTEXTUAL},
                                 {"FTRIGER",FTRIGER},
                                 {"WHERE",WHERE},
                                 {"ORDERBY",ORDERBY},
                                 {"GROUPBY",GROUPBY},
                                 {"HAVING",HAVING},
                                 {"SELECT",SELECT},
                                 {"CURSOR",CURSOR},
                                 {"NOINSERT",NOINSERT},
                                 {"NOORAINS",NOORAINS},
                                 {"NOORADEL",NOORADEL},
                                 {"NOUPDATE",NOUPDATE},
                                 {"NODELETE",NODELETE},
                                 {"NOCOMMIT",NOCOMMIT},
                                 {"UPDATE",UPDATE},
                                 {"DELETE",PDELETE},
                                 {"INSERT",INSERT},
                                 {"SICOMMIT",SICOMMIT},
                                 {"NOQUERY",NOQUERY},
                                 {"NOLOCK",NOLOCK},
                                 {"AQUERY",AQUERY},
                                 {"PQUERY",PQUERY},
                                 {"TQUERY",TQUERY},
                                 {"SOLOQUERY",SOLOQUERY},
                                 {"TIMEOUT",TIMEOUT},
                                 {"NOENTER",NOENTER},
                                 {"NOINPUT",NOINPUT},
                                 {"AUTOENTER",AUTOENTER},
                                 {"UPPER",UPPER},
                                 {"LOWER",LOWER},
                                 {"MIXED",MIXED},
                                 {"AUXILIAR",AUXILIAR},
                                 {"VIRTUAL",VIRTUAL},
                                 {"OCULTO",OCULTO},
                                 {"LISTA",LISTA},
                                 {"NOPREF",NOPREF},
                                 {"PREFIJO",PREFIJO},
                                 {"SCAN",SCAN},
                                 {"AUTOTRANSMIT",AUTOTRANSMIT},
                                 {"POSTCHANGE",POSTCHANGE},
                                 {"PREFIELD",PREFIELD},
                                 {"POSTFIELD",POSTFIELD},
                                 {"PROTECT",PROTECT},
                                 {"DISPLAY",DISPLAY},
                                 {"PREPINTA",PREPINTA},
                                 {"POSTPINTA",POSTPINTA},
                                 {"ONPINTA",ONPINTA},
                                 {"TRADUCIBLE",TRADUCIBLE},
                                 {"TOOLTIP",TOOLTIP},
                                 {"FUNTOOLTIP",FUNTOOLTIP},
                                 {"CHECKBOX",CHECKBOX},
                                 {"BOTON",BOTON},
                                 {"BOTONERA",BOTONERA},
                                 {"ONCLICK",ONCLICK},
                                 {"ONRIGHTCLICK",ONRIGHTCLICK},
                                 {"ONCENTERCLICK",ONCENTERCLICK},
                                 {"ONMOUSEOVER",ONMOUSEOVER},
                                 {"ONMOUSEOUT",ONMOUSEOUT},
                                 {"ONDBCLICK",ONDBCLICK},
                                 {"ONMOUSEMOVE",ONMOUSEMOVE},
                                 {"TITULOCAMPO",TITULOCAMPO},
                                 {"NOROWID",NOROWID},
                                 {"COMBOX",COMBOX},
                                 {"COMBOXINDEX",COMBOXINDEX},
                                 {"COMBOXREGPAG",COMBOXREGPAG},
                                 {"CONVIERTE",CONVIERTE},
                                 {"WPOSX",WPOSX},
                                 {"WPOSY",WPOSY},
                                 {"WLONX",WLONX},
                                 {"WLONY",WLONY},
                                 {"WREGPAG",WREGPAG},
                                 {"WPIXELX",WPIXELX},
                                 {"WPIXELY",WPIXELY},
                                 {"INCLUDECSS",INCLUDECSS},
                                 {"INCLUDEHTML",INCLUDEHTML},
                                 {"ESTILOCSS",ESTILOCSS},
                                 {"COMBOXMULTIPLE",COMBOXMULTIPLE},
                                 {"WFRAME",WFRAME},
                                 {"COMBOXREADONLY",COMBOXREADONLY},
                                 {"WPLEGADO",WPLEGADO},
                                 {"WDESPLEGADO",WDESPLEGADO},
                                 {"WGRAFICA",WGRAFICA},
                                 {"INCLUDEFICHEROCSS",INCLUDEFICHEROCSS},
                                 {"INCLUDETDCSS",INCLUDETDCSS},
                                 {"WMARCOFRAME",WMARCOFRAME},
                                 {"WMARCOPESTANNA",WMARCOPESTANNA},
                                 {"WSINMARCO",WSINMARCO},
                                 {"BOTONOCULTO",BOTONOCULTO},
                                 {"BOTONDISABLED",BOTONDISABLED},
                                 {"INCLUDEFICHEROHTML",INCLUDEFICHEROHTML},
                                 {"PRETECLA",PRETECLA},
                                 {"POSTTECLA",POSTTECLA},
                                 {"AJAX",AJAX},
                                 {"SIDEBAROCULTO",SIDEBAROCULTO},
                                 {"SIDEBARVISIBLE",SIDEBARVISIBLE},
                                 {"COMPONENTE",COMPONENTE},
                                 {"FICHERO",FICHERO},
                                 {"INCLUDE",INCLUDE},
                                 {"NULL",TNULL}};

static int numident=sizeof(ident)/sizeof(identificadores);
#define MAX_INCLUDE_DEPTH 10
typedef struct {
    YY_BUFFER_STATE yyb;
    int numlin;
    char nombre[MAXPATH];
    FILE *entrada;
   } include_stacks;
include_stacks include_stack[MAX_INCLUDE_DEPTH];
int include_stack_ptr = 0;

static int buscaidentificador(char *yytext)
{
  int i;
  for (i=0;i<numident;i++) {
      if (strcmp(yytext,ident[i].nombre)==0) {
         yylval.entero=ident[i].val;
         return(ident[i].val);
       }
   }
  yylval.cad=strdup(yytext);
  return(IDENTIFICADOR);
}
static int yywrap(void)
{
  return(1);
}
static int nlineastexto(char *cadena)
{
  char *aux=cadena;
  int numlin=0;
  while (*aux) {
        if (*aux++=='\n') numlin++;
   }
  return(numlin);
}
static char *eliminacomentarios(char *cadena)
{
  char *aux=cadena,*ret;
  while (*aux=='#') {
        while (*aux && *aux!='\n') aux++;
        if (*aux=='\n') aux++;
   }
  ret=strdup(aux);
  return(ret);
}

static char *interpretacadena(char *cadena)
{
  char *ret,*ptr;
  ptr=ret=strdup(cadena);
  while ((ptr=strchr(ptr,'\\'))!=NULL) {
        switch (ptr[1]) {
         case '"':*ptr='"';
                strcpy(ptr+1,ptr+2);
            break;
         case '\\':*ptr='\\';
                strcpy(ptr+1,ptr+2);
            break;
          }
    ptr++;
   }
  return(ret);
}
%}

letras   [a-zA-Z_/]
digitos  [0-9]
alnum    [a-zA-Z_0-9\.:\\\$\/\#\~ÁÉÍÓÚáéíóúñÑ]
blanco   [ \t]
punto    \.
other    .

%%
^#.*                                                        ;
{letras}{alnum}*                                           return buscaidentificador(yytext);
"-"?{digitos}+({punto}{digitos}*)?((e|E)("+"|"-")?{digitos}+)? yylval.doble=atof(yytext);return NUMERO;
{punto}{digitos}+((e|E)("+"|"-")?{digitos}+)?              yylval.doble=atof(yytext);return NUMERO;
\"([^"])*\"                                        {include_stack[include_stack_ptr].numlin+=nlineastexto(yytext);
                                                            yylval.cad=interpretacadena(yytext);
                                                            return LEXCADENA;
                                                           }
<SOPMENU>\"([^"])*\"                               {include_stack[include_stack_ptr].numlin+=nlineastexto(yytext);
                                                            yylval.cad=interpretacadena(yytext);
                                                            return LEXCADENA;
                                                           }
{blanco}+                                                  ;
\r                                                         ;
\n                                                         ++include_stack[include_stack_ptr].numlin;
^#[^\n\r]*[\n\r]                                             ++include_stack[include_stack_ptr].numlin;
<SOPMENU>^#[^\n\r]*[\n\r]                                  ++include_stack[include_stack_ptr].numlin;
<SOPMENU>[\n\r]                                            ++include_stack[include_stack_ptr].numlin;
<SPINTADO>[^|]*"|"                                         {include_stack[include_stack_ptr].numlin+=nlineastexto(yytext);
                                                            yylval.cad=eliminacomentarios(yytext);
                                                            BEGIN(0);
                                                            return(PINTADO_PANTALLA);
                                                           }
<STEXTOPLSQLD>[^@]*"@"                                     {include_stack[include_stack_ptr].numlin+=nlineastexto(yytext);
                                                            yylval.cad=calloc(strlen(yytext)+strlen(restosql)+1,1);
                                                            strcpy(yylval.cad,restosql);
                                                            strcat(yylval.cad,yytext);
                                                            yylval.cad[strlen(yylval.cad)-1]=0;
                                                            free(restosql);
                                                            BEGIN(0);
                                                            return(TEXTO_SQL);
                                                           }
<STEXTOSQL>[^;]*";"                                        {include_stack[include_stack_ptr].numlin+=nlineastexto(yytext);
                                                            ltrim(yytext);
                                                            if (strncmp(yytext,"BEGIN",5)==0 || strncmp(yytext,"DECLARE",7)==0) {
                                                               restosql=strdup(yytext);
                                                               BEGIN(STEXTOPLSQLD);
                                                             } else {
                                                               yylval.cad=strdup(yytext);
															   {char *aux;while ((aux=strchr(yylval.cad,9))!=NULL) *aux=' ';}
                                                               yylval.cad[strlen(yylval.cad)-1]=0;
                                                               BEGIN(0);
                                                               return(TEXTO_SQL);
                                                             }
                                                           }
<SONLINE>[^;]*";"                                          {include_stack[include_stack_ptr].numlin+=nlineastexto(yytext);
                                                            yylval.cad=strdup(yytext);
                                                            yylval.cad[strlen(yylval.cad)-1]=0;
                                                            BEGIN(0);
                                                            return(TEXTO_ONLINE);
                                                           }
<STITULO>[^\n]*                                            yylval.cad=strdup(yytext);BEGIN(0);return(TEXTO_TITULO);
<SOPMENU>[^,"\n]*                                          yylval.cad=strdup(yytext);BEGIN(0);return(OPMENU);
<SOPMENU>","                                               return(*yytext);
<<EOF>> {
            if ( --include_stack_ptr < 0 ) {
                if (yyin) fclose(yyin);
                yy_delete_buffer( YY_CURRENT_BUFFER );
                yyterminate();
                yyin=NULL;
        return(LEXEOF);
            } else {
                if (yyin) fclose(yyin);
                yyin=NULL;
                yy_delete_buffer( YY_CURRENT_BUFFER );
                yy_switch_to_buffer(
                include_stack[include_stack_ptr].yyb );
                }
            }

.                                                          return(*yytext);
%%

void lexerror(char *cadena)
{
  if (include_stack_ptr<0) {
     sprintf(cadena,"Final de fichero inexperado");
  } else {
     sprintf(cadena,"Fichero %s linea %d token %s",include_stack[include_stack_ptr].nombre,include_stack[include_stack_ptr].numlin,yytext);
  }
}

void lexbegin(int start)
{
  BEGIN(start);
}

void terminalex(void)
{
 while ( --include_stack_ptr >0 ) {
       if (yyin) fclose(yyin);
       yyin=NULL;
       yy_delete_buffer( YY_CURRENT_BUFFER );
       yy_switch_to_buffer(
                     include_stack[include_stack_ptr].yyb );
    }
 if (yyin) {
    if (yyin) fclose(yyin);
    yy_delete_buffer( YY_CURRENT_BUFFER );
    yyin=NULL;
  }
}

int creabuffer(char *nombre)
{
  FILE *entrada;
  YY_BUFFER_STATE y;
  entrada=fopenpath(nombre,"r");
  if (entrada==NULL) {
     mensajeparser("Error fichero %s no existe\n",nombre);
     return(-1);
   }
  y=yy_create_buffer(entrada,YY_BUF_SIZE);
  include_stack[include_stack_ptr++].yyb = YY_CURRENT_BUFFER;
  strcpy(include_stack[include_stack_ptr].nombre,nombre);
  include_stack[include_stack_ptr].numlin=1;
  include_stack[include_stack_ptr].entrada=entrada;
  yy_switch_to_buffer(y);
  return(0);
}

int creabuffercadena(char *cadena)
{
  YY_BUFFER_STATE y;
  include_stack[include_stack_ptr++].yyb = YY_CURRENT_BUFFER;
  y=yy_scan_string(cadena);
  strcpy(include_stack[include_stack_ptr].nombre,"CADENA");
  include_stack[include_stack_ptr].numlin=1;
  include_stack[include_stack_ptr].entrada=NULL;
//  yy_switch_to_buffer(y);
  yyin=NULL;
  return(0);
}

int initlexcadena(char *cadena)
{
  if (include_stack_ptr>=0) terminalex();
  creabuffercadena(cadena);
  yyout=stdout;
  return(0);
}

int initlex(char *cadena)
{
  if (include_stack_ptr>=0) terminalex();
  yyin=fopenpath(cadena,"r");
  if (yyin==NULL) {
     mensajeparser("Error fichero %s no existe",cadena);
     return(-1);
   }
  yy_set_bol(1);
  include_stack_ptr=0;
  strcpy(include_stack[include_stack_ptr].nombre,cadena);
  include_stack[include_stack_ptr].numlin=1;
  include_stack[include_stack_ptr].entrada=yyin;
  yyrestart(yyin);
  yyout=stdout;
  return(0);
}

