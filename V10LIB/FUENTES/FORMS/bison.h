
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PINTADO_PANTALLA = 258,
     OPMENU = 259,
     TEXTO_SQL = 260,
     TEXTO_TITULO = 261,
     TEXTO_ONLINE = 262,
     PREINSERT = 263,
     POSTINSERT = 264,
     PREUPDATE = 265,
     POSTUPDATE = 266,
     PREDELETE = 267,
     POSTDELETE = 268,
     PREQUERY = 269,
     POSTQUERY = 270,
     FINQUERY = 271,
     PREREGISTRO = 272,
     POSTREGISTRO = 273,
     PREBLOQUE = 274,
     POSTBLOQUE = 275,
     PREFORM = 276,
     POSTFORM = 277,
     PRECOMMIT = 278,
     POSTCOMMIT = 279,
     PREROLLBACK = 280,
     POSTROLLBACK = 281,
     BEGINBLOQUE = 282,
     BEGINBLOQUEFRM = 283,
     BEGINBLOQUEPAN = 284,
     ENDBLOQUE = 285,
     PADRE = 286,
     TABLA = 287,
     EXTRAPARSER = 288,
     AYUDA = 289,
     ONLINE = 290,
     POSX = 291,
     POSY = 292,
     LEXCOLOR = 293,
     TITULO = 294,
     REGPAG = 295,
     CAMPO = 296,
     TECLA = 297,
     CONTEXTUAL = 298,
     FTRIGER = 299,
     WHERE = 300,
     ORDERBY = 301,
     GROUPBY = 302,
     HAVING = 303,
     SELECT = 304,
     CURSOR = 305,
     NOINSERT = 306,
     NOORAINS = 307,
     NOORADEL = 308,
     NOUPDATE = 309,
     NODELETE = 310,
     NOCOMMIT = 311,
     UPDATE = 312,
     INSERT = 313,
     PDELETE = 314,
     SICOMMIT = 315,
     NOQUERY = 316,
     NOLOCK = 317,
     AQUERY = 318,
     PQUERY = 319,
     TQUERY = 320,
     SOLOQUERY = 321,
     TIMEOUT = 322,
     NOENTER = 323,
     NOINPUT = 324,
     AUTOENTER = 325,
     UPPER = 326,
     LOWER = 327,
     MIXED = 328,
     AUXILIAR = 329,
     VIRTUAL = 330,
     OCULTO = 331,
     LISTA = 332,
     NOPREF = 333,
     PREFIJO = 334,
     SCAN = 335,
     AUTOTRANSMIT = 336,
     POSTCHANGE = 337,
     PREFIELD = 338,
     POSTFIELD = 339,
     PROTECT = 340,
     DISPLAY = 341,
     PREPINTA = 342,
     POSTPINTA = 343,
     ONPINTA = 344,
     TRADUCIBLE = 345,
     TOOLTIP = 346,
     FUNTOOLTIP = 347,
     BOTON = 348,
     BOTONERA = 349,
     NOROWID = 350,
     TNULL = 351,
     IDENTIFICADOR = 352,
     LEXCADENA = 353,
     NUMERO = 354,
     LEXEOF = 355,
     CHECKBOX = 356,
     ONCLICK = 357,
     ONRIGHTCLICK = 358,
     ONCENTERCLICK = 359,
     ONMOUSEOVER = 360,
     ONMOUSEOUT = 361,
     ONDBCLICK = 362,
     ONMOUSEMOVE = 363,
     NEGATIVO = 364,
     TITULOCAMPO = 365,
     COMBOX = 366,
     COMBOXINDEX = 367,
     COMBOXREGPAG = 368,
     CONVIERTE = 369,
     WPOSX = 370,
     WPOSY = 371,
     WLONX = 372,
     WLONY = 373,
     WREGPAG = 374,
     WPIXELX = 375,
     WPIXELY = 376,
     INCLUDECSS = 377,
     INCLUDEHTML = 378,
     ESTILOCSS = 379,
     COMBOXMULTIPLE = 380,
     WFRAME = 381,
     COMBOXREADONLY = 382,
     WPLEGADO = 383,
     WDESPLEGADO = 384,
     WGRAFICA = 385,
     INCLUDEFICHEROCSS = 386,
     INCLUDETDCSS = 387,
     WMARCOFRAME = 388,
     WMARCOPESTANNA = 389,
     WSINMARCO = 390,
     BOTONOCULTO = 391,
     BOTONDISABLED = 392,
     INCLUDEFICHEROHTML = 393,
     PRETECLA = 394,
     POSTTECLA = 395,
     AJAX = 396,
     SIDEBAROCULTO = 397,
     SIDEBARVISIBLE = 398,
     COMPONENTE = 399
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{


         char *cad;
         int  entero;
         double doble;
         struct {
             void *ptr;
             int  tipo;
             int protegido;
           } dato;




} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


