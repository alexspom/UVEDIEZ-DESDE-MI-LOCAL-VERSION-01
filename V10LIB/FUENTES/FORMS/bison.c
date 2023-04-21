
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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
     TITULOCAMPO = 364,
     COMBOX = 365,
     COMBOXINDEX = 366,
     COMBOXREGPAG = 367,
     CONVIERTE = 368,
     WPOSX = 369,
     WPOSY = 370,
     WLONX = 371,
     WLONY = 372,
     WREGPAG = 373,
     WPIXELX = 374,
     WPIXELY = 375,
     INCLUDECSS = 376,
     INCLUDEHTML = 377,
     ESTILOCSS = 378,
     COMBOXMULTIPLE = 379,
     WFRAME = 380,
     COMBOXREADONLY = 381,
     WPLEGADO = 382,
     WDESPLEGADO = 383,
     WGRAFICA = 384,
     INCLUDEFICHEROCSS = 385,
     INCLUDETDCSS = 386,
     WMARCOFRAME = 387,
     WMARCOPESTANNA = 388,
     WSINMARCO = 389,
     BOTONOCULTO = 390,
     BOTONDISABLED = 391,
     INCLUDEFICHEROHTML = 392,
     PRETECLA = 393,
     POSTTECLA = 394,
     AJAX = 395,
     SIDEBAROCULTO = 396,
     SIDEBARVISIBLE = 397,
     COMPONENTE = 398,
     FICHERO = 399,
     INCLUDE = 400
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


/* Copy the second part of user declarations.  */


/* Unqualified %code blocks.  */


#pragma warning(disable: 4267)
#include "v10form.h"
#include "v10forparseaux.h"
#define INITIAL 0
#define SPINTADO 1
#define STEXTOSQL 2
#define SONLINE   3
#define STITULO   4
#define SOPMENU   5
static char buffer[10*MAXCADENA];




#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  47
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   986

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  158
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  263
/* YYNRULES -- Number of states.  */
#define YYNSTATES  630

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   400

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   155,     2,     2,   151,   152,   156,     2,
     147,   149,     2,   154,   148,   150,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   157,
       2,   146,     2,     2,   153,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    12,    13,    15,    17,
      21,    25,    29,    33,    35,    39,    43,    47,    51,    55,
      59,    61,    64,    66,    68,    71,    73,    75,    77,    79,
      83,    87,    91,    95,    99,   103,   107,   109,   112,   115,
     116,   118,   120,   124,   128,   133,   140,   142,   146,   150,
     154,   158,   162,   166,   170,   172,   174,   176,   178,   180,
     184,   188,   192,   196,   200,   204,   208,   223,   227,   229,
     231,   233,   235,   239,   245,   251,   257,   263,   265,   267,
     269,   271,   273,   275,   277,   279,   281,   285,   289,   293,
     297,   301,   305,   309,   313,   317,   321,   325,   329,   333,
     337,   341,   345,   349,   353,   357,   361,   365,   369,   373,
     377,   381,   385,   389,   393,   407,   409,   413,   426,   430,
     447,   449,   451,   466,   470,   474,   478,   482,   486,   487,
     492,   496,   498,   514,   532,   536,   537,   539,   542,   548,
     550,   552,   554,   556,   558,   560,   562,   564,   567,   568,
     572,   574,   576,   578,   582,   584,   586,   590,   591,   593,
     597,   599,   604,   607,   609,   613,   615,   620,   624,   628,
     630,   635,   638,   640,   642,   644,   646,   648,   653,   658,
     662,   664,   666,   668,   673,   675,   680,   682,   687,   691,
     693,   695,   697,   702,   704,   709,   711,   713,   718,   722,
     726,   730,   734,   738,   742,   746,   750,   754,   758,   764,
     768,   772,   776,   780,   784,   788,   792,   796,   803,   808,
     813,   815,   819,   823,   829,   833,   835,   840,   843,   846,
     849,   852,   855,   858,   861,   864,   866,   868,   870,   872,
     874,   876,   878,   880,   882,   884,   886,   888,   890,   892,
     896,   898,   901,   904,   907,   910,   914,   916,   919,   921,
     923,   925,   929,   933
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     159,     0,    -1,   160,    -1,   208,    -1,   174,    -1,   161,
     160,    -1,    -1,   166,    -1,   162,    -1,   121,   146,   164,
      -1,   130,   146,   164,    -1,   122,   146,   164,    -1,   137,
     146,   164,    -1,   169,    -1,    21,   146,   189,    -1,    22,
     146,   189,    -1,    23,   146,   189,    -1,    24,   146,   189,
      -1,    25,   146,   189,    -1,    26,   146,   189,    -1,    98,
      -1,    98,   164,    -1,   163,    -1,     5,    -1,   168,   192,
      -1,    97,    -1,    41,    -1,    32,    -1,   144,    -1,    41,
     146,   167,    -1,   172,   174,    30,    -1,   170,   175,    30,
      -1,   171,   174,    30,    -1,    28,   146,    97,    -1,    29,
     146,    97,    -1,    27,   146,    97,    -1,     3,    -1,   173,
     175,    -1,   175,   177,    -1,    -1,    97,    -1,    99,    -1,
      31,   146,    97,    -1,    32,   146,    97,    -1,    32,   146,
      97,    97,    -1,    33,   147,   164,   148,   164,   149,    -1,
      95,    -1,    36,   146,    99,    -1,    37,   146,    99,    -1,
     131,   146,   164,    -1,   121,   146,   164,    -1,   130,   146,
     164,    -1,   122,   146,   164,    -1,   137,   146,   164,    -1,
     132,    -1,   133,    -1,   134,    -1,   127,    -1,   128,    -1,
     114,   146,    99,    -1,   115,   146,    99,    -1,   116,   146,
      99,    -1,   117,   146,    99,    -1,   118,   146,    99,    -1,
     119,   146,    99,    -1,   120,   146,    99,    -1,   125,   147,
      99,   148,    99,   148,    99,   148,    99,   148,   164,   148,
     164,   149,    -1,    38,   146,    97,    -1,    71,    -1,    72,
      -1,    73,    -1,   205,    -1,    40,   146,    99,    -1,    67,
     146,   189,   148,    99,    -1,   138,   146,   176,   148,   189,
      -1,   139,   146,   176,   148,   189,    -1,    42,   146,   176,
     148,   189,    -1,   203,    -1,   198,    -1,    63,    -1,    64,
      -1,    65,    -1,    66,    -1,   200,    -1,   166,    -1,   206,
      -1,     8,   146,   189,    -1,    43,   146,   189,    -1,     9,
     146,   189,    -1,    10,   146,   189,    -1,    11,   146,   189,
      -1,    12,   146,   189,    -1,    13,   146,   189,    -1,    16,
     146,   189,    -1,    19,   146,   189,    -1,    20,   146,   189,
      -1,    14,   146,   189,    -1,    15,   146,   189,    -1,    17,
     146,   189,    -1,    18,   146,   189,    -1,    23,   146,   189,
      -1,    24,   146,   189,    -1,    25,   146,   189,    -1,    26,
     146,   189,    -1,    87,   146,   189,    -1,    88,   146,   189,
      -1,    89,   146,   189,    -1,   102,   146,   189,    -1,   103,
     146,   189,    -1,   104,   146,   189,    -1,   105,   146,   189,
      -1,   106,   146,   189,    -1,   107,   146,   189,    -1,   108,
     146,   189,    -1,   129,   146,    97,   148,    99,   148,    99,
     148,    99,   148,    99,   148,    99,    -1,   182,    -1,    94,
     146,    97,    -1,    94,   146,    97,   148,    99,   148,    99,
     148,    99,   148,    99,   183,    -1,   145,   146,    97,    -1,
     140,   147,    97,   148,   164,   148,   164,   148,   164,   148,
     164,   148,   164,   148,    99,   149,    -1,   141,    -1,   142,
      -1,   143,   147,    97,   148,   164,   148,   164,   148,   164,
     148,   164,   148,    99,   149,    -1,   121,   146,   164,    -1,
     123,   146,   164,    -1,   135,   146,    99,    -1,   136,   146,
      99,    -1,   148,   178,   179,    -1,    -1,    93,   146,    97,
     148,    -1,    93,   146,    97,    -1,   181,    -1,   180,    99,
     148,    99,   148,    99,   148,    99,   148,   164,   148,    97,
     148,   176,   179,    -1,   180,    99,   148,    99,   148,    99,
     148,    99,   148,   164,   148,    97,   148,   176,   148,   164,
     179,    -1,   148,    97,   183,    -1,    -1,    97,    -1,   187,
     184,    -1,   187,   184,   147,   190,   149,    -1,    96,    -1,
     150,    -1,   151,    -1,   152,    -1,   153,    -1,   154,    -1,
     155,    -1,   156,    -1,   186,   187,    -1,    -1,   194,   148,
     185,    -1,   185,    -1,   188,    -1,   191,    -1,   190,   148,
     191,    -1,   164,    -1,   185,    -1,   148,   197,   192,    -1,
      -1,   164,    -1,   164,   148,   193,    -1,    85,    -1,    85,
     147,   193,   149,    -1,    45,   146,    -1,   164,    -1,   164,
     148,   196,    -1,    68,    -1,    68,   147,   193,   149,    -1,
     121,   146,   164,    -1,   123,   146,   164,    -1,    69,    -1,
      69,   147,   193,   149,    -1,   195,   165,    -1,    70,    -1,
      71,    -1,    72,    -1,    73,    -1,    90,    -1,    90,   147,
     164,   149,    -1,    91,   147,   164,   149,    -1,    92,   146,
     189,    -1,    78,    -1,    74,    -1,    54,    -1,    54,   147,
     193,   149,    -1,    57,    -1,    57,   147,   193,   149,    -1,
      80,    -1,    80,   147,    99,   149,    -1,    79,   146,    97,
      -1,    81,    -1,   194,    -1,    86,    -1,    86,   147,   193,
     149,    -1,    75,    -1,    75,   147,   164,   149,    -1,    76,
      -1,   164,    -1,    39,   147,   164,   149,    -1,   114,   146,
      99,    -1,   115,   146,    99,    -1,   116,   146,    99,    -1,
     117,   146,    99,    -1,    82,   146,   189,    -1,    43,   146,
     189,    -1,    83,   146,   189,    -1,    84,   146,   189,    -1,
      87,   146,   189,    -1,    88,   146,   189,    -1,   113,   146,
     189,   157,   189,    -1,    89,   146,   189,    -1,   102,   146,
     189,    -1,   103,   146,   189,    -1,   104,   146,   189,    -1,
     105,   146,   189,    -1,   106,   146,   189,    -1,   107,   146,
     189,    -1,   108,   146,   189,    -1,   101,   147,   164,   148,
     164,   149,    -1,   110,   147,   196,   149,    -1,   124,   147,
     196,   149,    -1,   126,    -1,   111,   146,    99,    -1,   112,
     146,    99,    -1,    42,   146,   176,   148,   189,    -1,    40,
     146,    99,    -1,   144,    -1,   144,   147,   164,   149,    -1,
     199,   165,    -1,    45,   146,    -1,    46,   146,    -1,    47,
     146,    -1,    48,   146,    -1,    49,   146,    -1,   201,     7,
      -1,    35,   146,    -1,    51,    -1,    68,    -1,    55,    -1,
      54,    -1,    52,    -1,    53,    -1,    56,    -1,    62,    -1,
      61,    -1,    57,    -1,    58,    -1,    59,    -1,    60,    -1,
     202,    -1,   202,   148,   194,    -1,   194,    -1,    39,   146,
      -1,    34,   146,    -1,   204,     6,    -1,   207,   165,    -1,
      50,   146,    97,    -1,   209,    -1,   212,   209,    -1,   212,
      -1,   164,    -1,   210,    -1,   210,   148,   190,    -1,     4,
     148,   211,    -1,     4,   148,   189,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   207,   207,   208,   209,   214,   214,   217,   218,   219,
     220,   221,   222,   223,   225,   227,   229,   231,   233,   235,
     238,   239,   248,   254,   261,   271,   272,   273,   274,   276,
     318,   323,   327,   333,   335,   338,   348,   350,   352,   353,
     366,   369,   373,   379,   384,   392,   404,   405,   410,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   440,   444,   445,
     446,   447,   448,   449,   455,   473,   491,   509,   510,   511,
     512,   513,   514,   522,   523,   524,   525,   530,   535,   540,
     545,   550,   555,   560,   565,   570,   575,   580,   585,   590,
     595,   600,   605,   610,   615,   620,   625,   631,   636,   641,
     646,   651,   656,   661,   666,   676,   677,   685,   693,   700,
     711,   712,   713,   724,   725,   726,   727,   729,   729,   733,
     739,   742,   752,   762,   775,   786,   790,   811,   820,   833,
     835,   836,   837,   838,   839,   840,   841,   843,   844,   846,
     849,   852,   862,   871,   882,   883,   885,   885,   888,   889,
     894,   895,   897,   899,   907,   916,   917,   921,   922,   923,
     924,   928,   929,   930,   931,   932,   933,   934,   935,   938,
     940,   941,   942,   943,   944,   945,   946,   947,   948,   949,
     950,   951,   956,   961,   968,   976,   977,   989,   990,   991,
     992,   993,   994,   999,  1004,  1009,  1014,  1019,  1024,  1034,
    1039,  1044,  1049,  1054,  1059,  1064,  1069,  1074,  1082,  1087,
    1092,  1100,  1111,  1119,  1135,  1138,  1142,  1147,  1166,  1167,
    1168,  1169,  1170,  1172,  1175,  1177,  1178,  1179,  1180,  1181,
    1182,  1183,  1184,  1185,  1186,  1187,  1188,  1189,  1191,  1220,
    1245,  1252,  1253,  1255,  1266,  1275,  1280,  1282,  1283,  1285,
    1287,  1295,  1310,  1316
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PINTADO_PANTALLA", "OPMENU",
  "TEXTO_SQL", "TEXTO_TITULO", "TEXTO_ONLINE", "PREINSERT", "POSTINSERT",
  "PREUPDATE", "POSTUPDATE", "PREDELETE", "POSTDELETE", "PREQUERY",
  "POSTQUERY", "FINQUERY", "PREREGISTRO", "POSTREGISTRO", "PREBLOQUE",
  "POSTBLOQUE", "PREFORM", "POSTFORM", "PRECOMMIT", "POSTCOMMIT",
  "PREROLLBACK", "POSTROLLBACK", "BEGINBLOQUE", "BEGINBLOQUEFRM",
  "BEGINBLOQUEPAN", "ENDBLOQUE", "PADRE", "TABLA", "EXTRAPARSER", "AYUDA",
  "ONLINE", "POSX", "POSY", "LEXCOLOR", "TITULO", "REGPAG", "CAMPO",
  "TECLA", "CONTEXTUAL", "FTRIGER", "WHERE", "ORDERBY", "GROUPBY",
  "HAVING", "SELECT", "CURSOR", "NOINSERT", "NOORAINS", "NOORADEL",
  "NOUPDATE", "NODELETE", "NOCOMMIT", "UPDATE", "INSERT", "PDELETE",
  "SICOMMIT", "NOQUERY", "NOLOCK", "AQUERY", "PQUERY", "TQUERY",
  "SOLOQUERY", "TIMEOUT", "NOENTER", "NOINPUT", "AUTOENTER", "UPPER",
  "LOWER", "MIXED", "AUXILIAR", "VIRTUAL", "OCULTO", "LISTA", "NOPREF",
  "PREFIJO", "SCAN", "AUTOTRANSMIT", "POSTCHANGE", "PREFIELD", "POSTFIELD",
  "PROTECT", "DISPLAY", "PREPINTA", "POSTPINTA", "ONPINTA", "TRADUCIBLE",
  "TOOLTIP", "FUNTOOLTIP", "BOTON", "BOTONERA", "NOROWID", "TNULL",
  "IDENTIFICADOR", "LEXCADENA", "NUMERO", "LEXEOF", "CHECKBOX", "ONCLICK",
  "ONRIGHTCLICK", "ONCENTERCLICK", "ONMOUSEOVER", "ONMOUSEOUT",
  "ONDBCLICK", "ONMOUSEMOVE", "TITULOCAMPO", "COMBOX", "COMBOXINDEX",
  "COMBOXREGPAG", "CONVIERTE", "WPOSX", "WPOSY", "WLONX", "WLONY",
  "WREGPAG", "WPIXELX", "WPIXELY", "INCLUDECSS", "INCLUDEHTML",
  "ESTILOCSS", "COMBOXMULTIPLE", "WFRAME", "COMBOXREADONLY", "WPLEGADO",
  "WDESPLEGADO", "WGRAFICA", "INCLUDEFICHEROCSS", "INCLUDETDCSS",
  "WMARCOFRAME", "WMARCOPESTANNA", "WSINMARCO", "BOTONOCULTO",
  "BOTONDISABLED", "INCLUDEFICHEROHTML", "PRETECLA", "POSTTECLA", "AJAX",
  "SIDEBAROCULTO", "SIDEBARVISIBLE", "COMPONENTE", "FICHERO", "INCLUDE",
  "'='", "'('", "','", "')'", "'-'", "'$'", "'%'", "'@'", "'+'", "'!'",
  "'&'", "';'", "$accept", "modulo", "lista_frm", "definidor_frm",
  "triger_form", "unacadena_parser", "cadena_parser", "texto_sql",
  "definidor_campo", "nombrecampo", "nombre_campo", "definidor_bloque",
  "nombre_bloqueinter", "nombre_bloquepan", "nombre_bloque",
  "pintado_pantalla", "cuerpo_bloque", "modificadores_bloque",
  "nombre_tecla", "modificador_bloque", "modificador_boton",
  "modificadores_boton", "nombre_boton", "nombre_boton_dupl",
  "definidor_boton", "lista_botones", "identificador_triger",
  "definicion_triger", "modificador_triger", "lista_mod_triger",
  "triger_protegido", "definidor_triger", "lista_parametros", "parametro",
  "modificadores_campo", "lista_privilegios", "condicion_proteccion",
  "modificador_where", "opciones_combox", "modificador_campo",
  "modificador_oracle", "nombre_modificador_oracle", "modificador_online",
  "nombre_modificador_online", "palabra_protegida", "proteccion_bloque",
  "nombre_titulo", "definidor_titulo", "definidor_cursor", "nombre_cursor",
  "menu", "lista_opciones", "nombre_triger", "triger_cadenas",
  "opcion_menu", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,    61,    40,    44,    41,
      45,    36,    37,    64,    43,    33,    38,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   158,   159,   159,   159,   160,   160,   161,   161,   161,
     161,   161,   161,   161,   162,   162,   162,   162,   162,   162,
     163,   163,   164,   165,   166,   167,   167,   167,   167,   168,
     169,   169,   169,   170,   171,   172,   173,   174,   175,   175,
     176,   176,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   178,   178,   178,   178,   179,   179,   180,
     181,   182,   182,   182,   183,   183,   184,   185,   185,   185,
     186,   186,   186,   186,   186,   186,   186,   187,   187,   188,
     188,   189,   190,   190,   191,   191,   192,   192,   193,   193,
     194,   194,   195,   196,   196,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   198,   199,   199,
     199,   199,   199,   200,   201,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   203,   203,
     203,   204,   204,   205,   206,   207,   208,   209,   209,   210,
     211,   211,   212,   212
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     0,     1,     1,     3,
       3,     3,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     2,     1,     1,     2,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     1,     2,     2,     0,
       1,     1,     3,     3,     4,     6,     1,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,    14,     3,     1,     1,
       1,     1,     3,     5,     5,     5,     5,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,    13,     1,     3,    12,     3,    16,
       1,     1,    14,     3,     3,     3,     3,     3,     0,     4,
       3,     1,    15,    17,     3,     0,     1,     2,     5,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     0,     3,
       1,     1,     1,     3,     1,     1,     3,     0,     1,     3,
       1,     4,     2,     1,     3,     1,     4,     3,     3,     1,
       4,     2,     1,     1,     1,     1,     1,     4,     4,     3,
       1,     1,     1,     4,     1,     4,     1,     4,     3,     1,
       1,     1,     4,     1,     4,     1,     1,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     5,     3,
       3,     3,     3,     3,     3,     3,     3,     6,     4,     4,
       1,     3,     3,     5,     3,     1,     4,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     2,     2,     2,     2,     3,     1,     2,     1,     1,
       1,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       6,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     2,     6,
       8,     7,   157,    13,    39,     0,     0,    39,     4,     3,
     256,   258,   148,   148,   148,   148,   148,   148,   148,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     5,     0,
      24,     0,     0,     0,    37,   257,   160,   139,    20,   140,
     141,   142,   143,   144,   145,   146,    22,   259,   150,   148,
       0,   151,   263,     0,   260,   262,    14,    15,    16,    17,
      18,    19,    35,    33,    34,    27,    26,    25,    28,    29,
       9,    11,    10,    12,     0,     0,     0,     0,     0,   182,
     184,   165,   169,   172,   173,   174,   175,   181,   193,   195,
     180,     0,   186,   189,     0,     0,     0,   191,     0,     0,
       0,   176,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   220,   225,   196,   190,     0,   157,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    31,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   235,   239,   240,   238,   237,
     241,   244,   245,   246,   247,   243,   242,    79,    80,    81,
      82,     0,   236,    68,    69,    70,     0,     0,     0,     0,
       0,    46,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    57,
      58,     0,     0,     0,    54,    55,    56,     0,     0,     0,
       0,   120,   121,     0,     0,    84,    38,     0,   131,   115,
     250,    78,     0,    83,     0,   248,    77,     0,    71,    85,
       0,    32,    30,     0,    21,   147,   136,   137,   148,   148,
       0,     0,     0,   148,   162,     0,     0,     0,     0,     0,
       0,     0,   148,   148,   148,     0,   148,   148,   148,     0,
       0,   148,     0,   148,   148,   148,   148,   148,   148,   148,
       0,     0,     0,   148,     0,     0,     0,     0,     0,     0,
       0,     0,    23,   171,   156,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,     0,     0,     0,   252,   234,     0,     0,     0,
     251,     0,     0,   148,   228,   229,   230,   231,   232,     0,
     148,   148,   148,   148,     0,     0,   148,   148,   148,   148,
     148,   148,   148,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   227,   233,     0,   253,   254,   158,     0,
     148,   149,   154,   155,   261,   152,     0,   224,    40,    41,
       0,   203,     0,     0,     0,     0,     0,   188,     0,   202,
     204,   205,     0,   206,   207,   209,     0,     0,   179,     0,
     210,   211,   212,   213,   214,   215,   216,   163,     0,   221,
     222,     0,   198,   199,   200,   201,   167,   168,     0,     0,
      86,    88,    89,    90,    91,    92,    96,    97,    93,    98,
      99,    94,    95,   100,   101,   102,   103,    42,    43,     0,
      47,    48,    67,    72,     0,    87,   255,     0,   104,   105,
     106,   130,   116,   107,   108,   109,   110,   111,   112,   113,
      59,    60,    61,    62,    63,    64,    65,    50,    52,     0,
       0,    51,    49,    53,     0,     0,     0,     0,   118,     0,
     249,     0,   161,     0,   148,   197,   148,   183,   185,   166,
     170,   194,   187,   192,   177,   178,     0,     0,   218,   148,
     219,   226,    44,     0,   148,     0,   129,     0,     0,     0,
     148,   148,     0,     0,     0,   159,   138,   153,   223,     0,
     164,   208,     0,    76,    73,     0,     0,     0,    74,    75,
       0,     0,     0,   217,    45,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   135,     0,     0,     0,     0,
       0,     0,   117,     0,     0,     0,     0,     0,   135,     0,
     114,     0,     0,     0,   134,    66,     0,   122,   128,     0,
       0,   132,   119,     0,     0,     0,     0,   128,   128,     0,
       0,     0,     0,     0,   133,   127,   123,   124,   125,   126
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    17,    18,    19,    20,    66,   388,   313,    21,    89,
      22,    23,    24,    25,    26,    27,    28,    51,   400,   246,
     618,   611,   247,   248,   249,   592,   267,    68,    69,    70,
      71,    72,   394,   395,    50,   389,    73,   147,   428,   148,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
      29,    30,    74,    75,    31
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -495
static const yytype_int16 yypact[] =
{
      19,  -495,  -139,  -111,   -97,   -85,   -73,   -71,   -67,   -41,
     -34,   -25,   -18,   -16,   -15,   -14,   -13,    69,  -495,    29,
    -495,  -495,   -23,  -495,  -495,   126,   126,  -495,  -495,  -495,
    -495,   132,   -69,   -60,   -60,   -60,   -60,   -60,   -60,    40,
      41,    42,   -17,    44,    44,    44,    44,  -495,  -495,   842,
    -495,   597,   113,   114,   735,  -495,    -2,  -495,    44,  -495,
    -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,   -52,
      49,  -495,  -495,     0,     4,  -495,  -495,  -495,  -495,  -495,
    -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,
    -495,  -495,  -495,  -495,     6,     1,     8,     9,    11,    13,
      14,    15,    16,  -495,  -495,  -495,  -495,  -495,    17,  -495,
    -495,    12,    18,  -495,    21,    22,    23,    24,    26,    27,
      28,    30,    31,    33,    34,    36,    37,    38,    39,    43,
      45,    46,    47,    50,    51,    53,    54,    55,    56,    57,
      58,    59,    48,  -495,    60,  -495,  -495,   165,   -23,    62,
      63,    64,    65,    66,    67,    70,    71,    72,    74,    75,
      76,    77,    78,    79,    80,    81,  -495,    82,    83,    68,
      84,    85,    86,    87,    88,    89,    90,    93,    95,    96,
      97,    99,   100,   102,   103,  -495,  -495,  -495,  -495,  -495,
    -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,
    -495,   104,  -495,  -495,  -495,  -495,   105,   106,   107,   108,
     109,  -495,   110,   115,   116,   118,   119,   120,   121,   123,
     124,   125,   127,   128,   129,   134,   135,   136,   112,  -495,
    -495,   137,   138,   139,  -495,  -495,  -495,   140,   141,   142,
     143,  -495,  -495,   144,   146,  -495,  -495,    91,  -495,  -495,
    -495,  -495,   165,  -495,   168,    32,  -495,   170,  -495,  -495,
     165,  -495,  -495,    44,  -495,  -495,  -495,   147,   -37,   -88,
      44,    94,   -65,   -60,  -495,    44,    44,    44,    44,    44,
     101,   173,   -60,   -60,   -60,    44,   -60,   -60,   -60,    44,
      44,   -60,    44,   -60,   -60,   -60,   -60,   -60,   -60,   -60,
      44,   190,   194,   -60,   196,   197,   198,   199,    44,    44,
      44,    44,  -495,  -495,  -495,   -60,   -60,   -60,   -60,   -60,
     -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,
     -60,   -60,   122,   202,    44,  -495,  -495,   201,   204,   207,
    -495,   206,   -65,   -60,  -495,  -495,  -495,  -495,  -495,   209,
     -60,   -60,   -60,   -60,   210,   211,   -60,   -60,   -60,   -60,
     -60,   -60,   -60,   212,   213,   214,   215,   216,   217,   218,
      44,    44,   219,   222,    44,    44,    44,   -65,   -65,   223,
     224,   225,   153,  -495,  -495,   238,  -495,  -495,   161,   175,
     -88,  -495,  -495,  -495,   162,  -495,   176,  -495,  -495,  -495,
     178,  -495,   179,   180,   181,   182,   183,  -495,   184,  -495,
    -495,  -495,   185,  -495,  -495,  -495,   186,   187,  -495,   192,
    -495,  -495,  -495,  -495,  -495,  -495,  -495,   193,   200,  -495,
    -495,   188,  -495,  -495,  -495,  -495,  -495,  -495,   203,   205,
    -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,
    -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,   230,   226,
    -495,  -495,  -495,  -495,   227,  -495,  -495,   229,  -495,  -495,
    -495,   231,   232,  -495,  -495,  -495,  -495,  -495,  -495,  -495,
    -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,   233,
     234,  -495,  -495,  -495,   235,   236,   237,   239,  -495,   248,
    -495,    44,  -495,   -77,   -88,  -495,   -60,  -495,  -495,  -495,
    -495,  -495,  -495,  -495,  -495,  -495,    44,    44,  -495,   -60,
    -495,  -495,  -495,    44,   -60,   249,  -495,   251,   252,   254,
     -60,   -60,    44,    44,   257,  -495,  -495,  -495,  -495,   258,
    -495,  -495,   259,  -495,  -495,   261,   262,   263,  -495,  -495,
     264,   265,   266,  -495,  -495,   274,   279,   287,    44,    44,
     267,   269,   270,   271,   272,   273,   307,   315,   323,   328,
      44,    44,   280,   288,   289,   290,   291,   292,    44,   342,
      44,   343,    44,    44,   295,   296,   297,   298,   299,   300,
     352,   353,  -495,    44,   354,    44,   355,   303,   296,   306,
    -495,   304,   308,   -65,  -495,  -495,   357,  -495,   310,   311,
      -1,  -495,  -495,   313,   316,   317,   318,   319,   319,    44,
      44,   362,   366,   -47,  -495,  -495,  -495,  -495,  -495,  -495
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -495,  -495,   167,  -495,  -495,  -495,   -32,  -221,   -21,  -495,
    -495,  -495,  -495,  -495,  -495,  -495,    52,   160,  -340,  -495,
    -495,  -494,  -495,  -495,  -495,  -410,  -495,  -264,  -495,   293,
    -495,    73,  -184,  -141,   320,  -257,   -48,  -495,  -303,  -495,
    -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,  -495,
    -495,   435,  -495,  -495,  -495
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      67,   146,   464,   250,   391,   393,   250,   438,    57,    32,
      58,    90,    91,    92,    93,    85,    56,   145,   402,   403,
     404,   405,     1,     2,    86,    56,   264,    57,   412,    58,
     245,   383,   398,   245,   399,    33,    57,   494,   495,   387,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    34,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    57,
      12,    35,    59,    60,    61,    62,    63,    64,    65,    47,
      12,   504,   536,    36,   613,    37,   614,    52,    53,    38,
      87,    59,    60,    61,    62,    63,    64,    65,   615,   616,
      59,    60,    61,    62,    63,    64,    65,    58,    59,    60,
      61,    62,    63,    64,    65,    39,    76,    77,    78,    79,
      80,    81,    40,    59,    60,    61,    62,    63,    64,    65,
     613,    41,   614,   624,   625,    49,   393,    88,    42,     1,
      43,    44,    45,    46,   615,   616,     2,    82,    83,    84,
      13,    14,    58,   261,   262,   263,   266,   271,   268,    15,
      13,    14,   269,   270,   272,   273,    16,   274,   280,    15,
     275,   276,   277,   278,   279,   281,    16,   282,   283,   284,
     312,   285,   286,   287,   288,   384,   386,   289,   290,   291,
     385,   292,   293,   294,   295,   296,    48,    54,   604,   297,
     382,   298,   299,   397,   300,   310,   301,   302,   407,   303,
     304,   305,   306,   307,   308,   309,   503,   311,   315,   316,
     317,   318,   319,   320,   540,   334,   321,   322,   323,   457,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     335,   336,   337,   338,   339,   340,   341,   392,   396,   342,
     393,   343,   344,   345,   535,   346,   347,   406,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   416,   417,   372,
     419,   357,   358,   608,   359,   360,   361,   362,   427,   363,
     364,   365,   408,   366,   367,   368,   436,   437,   427,   439,
     369,   370,   371,   373,   374,   375,   376,   377,   378,   429,
     379,   380,   381,   430,   390,   432,   433,   434,   435,   458,
     460,   499,   459,   461,   462,   463,   466,   471,   472,   501,
     504,   480,   481,   482,   483,   484,   485,   486,   489,   490,
     496,   497,   498,    56,   502,   505,   506,   522,   507,   508,
     509,   510,   511,   512,   513,   514,   515,   500,   487,   488,
     516,   517,   491,   492,   493,   519,   401,   534,   544,   518,
     545,   546,   520,   547,   521,   409,   410,   411,   392,   413,
     414,   415,   265,   537,   418,   560,   420,   421,   422,   423,
     424,   425,   426,   561,   523,   524,   431,   525,   562,   526,
     527,   528,   529,   530,   531,   532,   563,   533,   440,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   552,   572,   553,   554,   555,
     556,   557,   558,   559,   573,   566,   465,   567,   568,   569,
     570,   571,   574,   467,   468,   469,   470,   575,   578,   473,
     474,   475,   476,   477,   478,   479,   579,   580,   581,   582,
     583,   585,   587,   590,   591,   593,   594,   595,   596,   597,
     598,   603,   606,   600,   602,   605,   609,   607,   610,   619,
     612,   628,   620,   621,   622,   629,    55,   623,   314,     0,
       0,     0,   392,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   539,   427,     0,     0,     0,     0,
       0,   542,     0,     0,     0,     0,     0,     0,     0,     0,
     550,   551,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   564,   565,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   576,   577,
       0,     0,     0,     0,     0,     0,   584,     0,   586,     0,
     588,   589,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   599,     0,   601,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   617,   538,
       0,     0,     0,     0,     0,     0,     0,   626,   627,     0,
       0,     0,   541,     0,     0,     0,     0,   543,     0,     0,
       0,     0,     0,   548,   549,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,     0,     0,
     162,   163,   164,   165,     0,     0,     0,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,    12,   177,
     178,     0,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,     0,     0,   203,   204,
     205,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    56,     0,   206,   207,   208,     0,     0,     0,
     209,   210,   211,     0,     0,     0,     0,     0,     0,   212,
     213,   214,   215,   216,   217,   218,     0,     0,     0,     0,
       0,   219,   220,   221,   222,   223,   224,   225,   226,   227,
       0,     0,   228,     0,   229,   230,   231,   232,   233,   234,
     235,   236,     0,     0,   237,   238,   239,   240,   241,   242,
     243,     0,   244,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,     0,     0,   162,   163,
     164,   165,     0,     0,     0,     0,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,    12,   177,   178,     0,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,     0,     0,   203,   204,   205,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      56,     0,   206,   207,   208,     0,     0,     0,   209,   210,
     211,     0,     0,     0,     0,     0,     0,   212,   213,   214,
     215,   216,   217,   218,     0,     0,     0,     0,     0,   219,
     220,   221,   222,   223,   224,   225,   226,   227,     0,     0,
     228,     0,   229,   230,   231,   232,   233,   234,   235,   236,
       0,     0,   237,   238,   239,   240,   241,   242,   243,     0,
     244,    94,    95,     0,    96,    97,     0,    98,     0,     0,
       0,     0,     0,     0,     0,     0,    99,     0,     0,   100,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     101,   102,   103,   104,   105,   106,   107,   108,   109,     0,
     110,   111,   112,   113,   114,   115,   116,    56,   117,   118,
     119,   120,   121,   122,   123,     0,     0,     0,     0,     0,
      58,     0,     0,   124,   125,   126,   127,   128,   129,   130,
     131,     0,   132,   133,   134,   135,   136,   137,   138,   139,
       0,     0,     0,   140,     0,   141,   142,     0,   143,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   144
};

static const yytype_int16 yycheck[] =
{
      32,    49,   342,    51,   268,   269,    54,   310,    96,   148,
      98,    43,    44,    45,    46,    32,    85,    49,   275,   276,
     277,   278,     3,     4,    41,    85,    58,    96,   285,    98,
      51,   252,    97,    54,    99,   146,    96,   377,   378,   260,
      21,    22,    23,    24,    25,    26,    27,    28,    29,   146,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    96,
      41,   146,   150,   151,   152,   153,   154,   155,   156,     0,
      41,   148,   149,   146,   121,   146,   123,    25,    26,   146,
      97,   150,   151,   152,   153,   154,   155,   156,   135,   136,
     150,   151,   152,   153,   154,   155,   156,    98,   150,   151,
     152,   153,   154,   155,   156,   146,    33,    34,    35,    36,
      37,    38,   146,   150,   151,   152,   153,   154,   155,   156,
     121,   146,   123,   617,   618,   148,   390,   144,   146,     3,
     146,   146,   146,   146,   135,   136,     4,    97,    97,    97,
     121,   122,    98,    30,    30,   147,    97,   146,   148,   130,
     121,   122,   148,   147,   146,   146,   137,   146,   146,   130,
     147,   147,   147,   147,   147,   147,   137,   146,   146,   146,
       5,   147,   146,   146,   146,     7,     6,   147,   147,   146,
     148,   147,   146,   146,   146,   146,    19,    27,   598,   146,
      99,   146,   146,    99,   147,   147,   146,   146,    97,   146,
     146,   146,   146,   146,   146,   146,   390,   147,   146,   146,
     146,   146,   146,   146,   517,   147,   146,   146,   146,    97,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   269,   270,   146,
     504,   146,   146,   146,   501,   146,   146,   279,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   289,   290,   147,
     292,   146,   146,   603,   146,   146,   146,   146,   300,   146,
     146,   146,    99,   146,   146,   146,   308,   309,   310,   311,
     146,   146,   146,   146,   146,   146,   146,   146,   146,    99,
     147,   147,   146,    99,   147,    99,    99,    99,    99,    97,
      99,   148,   334,    99,    97,    99,    97,    97,    97,   148,
     148,    99,    99,    99,    99,    99,    99,    99,    99,    97,
      97,    97,    97,    85,   149,   149,   148,    97,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   385,   370,   371,
     148,   148,   374,   375,   376,   157,   273,    99,    99,   149,
      99,    99,   149,    99,   149,   282,   283,   284,   390,   286,
     287,   288,    69,   504,   291,    99,   293,   294,   295,   296,
     297,   298,   299,    99,   148,   148,   303,   148,    99,   148,
     148,   148,   148,   148,   148,   148,    99,   148,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   148,    99,   149,   149,   148,
     148,   148,   148,   148,    99,   148,   343,   148,   148,   148,
     148,   148,    99,   350,   351,   352,   353,    99,   148,   356,
     357,   358,   359,   360,   361,   362,   148,   148,   148,   148,
     148,    99,    99,   148,   148,   148,   148,   148,   148,    97,
      97,   148,   148,    99,    99,   149,    99,   149,   148,   146,
     149,    99,   146,   146,   146,    99,    31,   148,   148,    -1,
      -1,    -1,   504,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   516,   517,    -1,    -1,    -1,    -1,
      -1,   523,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     532,   533,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   558,   559,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   570,   571,
      -1,    -1,    -1,    -1,    -1,    -1,   578,    -1,   580,    -1,
     582,   583,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   593,    -1,   595,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   610,   506,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   619,   620,    -1,
      -1,    -1,   519,    -1,    -1,    -1,    -1,   524,    -1,    -1,
      -1,    -1,    -1,   530,   531,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    -1,    -1,
      23,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    -1,    -1,    71,    72,
      73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    -1,    87,    88,    89,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,   102,
     103,   104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,
      -1,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      -1,    -1,   125,    -1,   127,   128,   129,   130,   131,   132,
     133,   134,    -1,    -1,   137,   138,   139,   140,   141,   142,
     143,    -1,   145,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    -1,    -1,    23,    24,
      25,    26,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    -1,    -1,    71,    72,    73,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    -1,    87,    88,    89,    -1,    -1,    -1,    93,    94,
      95,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,   114,
     115,   116,   117,   118,   119,   120,   121,   122,    -1,    -1,
     125,    -1,   127,   128,   129,   130,   131,   132,   133,   134,
      -1,    -1,   137,   138,   139,   140,   141,   142,   143,    -1,
     145,    39,    40,    -1,    42,    43,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    -1,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,   101,   102,   103,   104,   105,   106,   107,
     108,    -1,   110,   111,   112,   113,   114,   115,   116,   117,
      -1,    -1,    -1,   121,    -1,   123,   124,    -1,   126,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   144
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    41,   121,   122,   130,   137,   159,   160,   161,
     162,   166,   168,   169,   170,   171,   172,   173,   174,   208,
     209,   212,   148,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,     0,   160,   148,
     192,   175,   174,   174,   175,   209,    85,    96,    98,   150,
     151,   152,   153,   154,   155,   156,   163,   164,   185,   186,
     187,   188,   189,   194,   210,   211,   189,   189,   189,   189,
     189,   189,    97,    97,    97,    32,    41,    97,   144,   167,
     164,   164,   164,   164,    39,    40,    42,    43,    45,    54,
      57,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      78,    79,    80,    81,    82,    83,    84,    86,    87,    88,
      89,    90,    91,    92,   101,   102,   103,   104,   105,   106,
     107,   108,   110,   111,   112,   113,   114,   115,   116,   117,
     121,   123,   124,   126,   144,   164,   194,   195,   197,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    23,    24,    25,    26,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    42,    43,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    71,    72,    73,    87,    88,    89,    93,
      94,    95,   102,   103,   104,   105,   106,   107,   108,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   125,   127,
     128,   129,   130,   131,   132,   133,   134,   137,   138,   139,
     140,   141,   142,   143,   145,   166,   177,   180,   181,   182,
     194,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,    30,    30,   147,   164,   187,    97,   184,   148,   148,
     147,   146,   146,   146,   146,   147,   147,   147,   147,   147,
     146,   147,   146,   146,   146,   147,   146,   146,   146,   147,
     147,   146,   147,   146,   146,   146,   146,   146,   146,   146,
     147,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     147,   147,     5,   165,   192,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   147,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   147,   146,   146,   146,   146,   146,   146,   147,
     147,   146,    99,   165,     7,   148,     6,   165,   164,   193,
     147,   185,   164,   185,   190,   191,   164,    99,    97,    99,
     176,   189,   193,   193,   193,   193,   164,    97,    99,   189,
     189,   189,   193,   189,   189,   189,   164,   164,   189,   164,
     189,   189,   189,   189,   189,   189,   189,   164,   196,    99,
      99,   189,    99,    99,    99,    99,   164,   164,   196,   164,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,    97,    97,   164,
      99,    99,    97,    99,   176,   189,    97,   189,   189,   189,
     189,    97,    97,   189,   189,   189,   189,   189,   189,   189,
      99,    99,    99,    99,    99,    99,    99,   164,   164,    99,
      97,   164,   164,   164,   176,   176,    97,    97,    97,   148,
     194,   148,   149,   190,   148,   149,   148,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   148,   148,   149,   157,
     149,   149,    97,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,    99,   193,   149,   191,   189,   164,
     196,   189,   164,   189,    99,    99,    99,    99,   189,   189,
     164,   164,   148,   149,   149,   148,   148,   148,   148,   148,
      99,    99,    99,    99,   164,   164,   148,   148,   148,   148,
     148,   148,    99,    99,    99,    99,   164,   164,   148,   148,
     148,   148,   148,   148,   164,    99,   164,    99,   164,   164,
     148,   148,   183,   148,   148,   148,   148,    97,    97,   164,
      99,   164,    99,   148,   183,   149,   148,   149,   176,    99,
     148,   179,   149,   121,   123,   135,   136,   164,   178,   146,
     146,   146,   146,   148,   179,   179,   164,   164,    99,    99
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:

    {if (funcionparsebloque) funcionparsebloque(bloqueparse);
                         if (terminabloque(bloqueparse)) return(-1);
                         forparse->nbloques++;
                         enbloque=0;
                         ;}
    break;

  case 9:

    {strcpy(forparse->includecss,(yyvsp[(3) - (3)].cad)); free((yyvsp[(3) - (3)].cad));;}
    break;

  case 10:

    {strcpy(forparse->includeficherocss,(yyvsp[(3) - (3)].cad)); free((yyvsp[(3) - (3)].cad));;}
    break;

  case 11:

    {strcpy(forparse->includehtml,(yyvsp[(3) - (3)].cad)); free((yyvsp[(3) - (3)].cad));;}
    break;

  case 12:

    {strcpy(forparse->includeficherohtml,(yyvsp[(3) - (3)].cad)); free((yyvsp[(3) - (3)].cad));;}
    break;

  case 14:

    {if (forparse->preform) liberatriger(forparse->preform);
                                            forparse->preform=(yyvsp[(3) - (3)].dato).ptr;;}
    break;

  case 15:

    {if (forparse->postform) liberatriger(forparse->postform);
                                              forparse->postform=(yyvsp[(3) - (3)].dato).ptr;;}
    break;

  case 16:

    {if (forparse->precommit) liberatriger(forparse->precommit);
                                               forparse->precommit=(yyvsp[(3) - (3)].dato).ptr;;}
    break;

  case 17:

    {if (forparse->postcommit) liberatriger(forparse->postcommit);
                                                forparse->postcommit=(yyvsp[(3) - (3)].dato).ptr;;}
    break;

  case 18:

    {if (forparse->prerollback) liberatriger(forparse->prerollback);
                                                 forparse->prerollback=(yyvsp[(3) - (3)].dato).ptr;;}
    break;

  case 19:

    {if (forparse->postrollback) liberatriger(forparse->postrollback);
                                                  forparse->postrollback=(yyvsp[(3) - (3)].dato).ptr;;}
    break;

  case 20:

    {quitacomillas(&(yyval.cad),(yyvsp[(1) - (1)].cad));free((yyvsp[(1) - (1)].cad));;}
    break;

  case 21:

    {char *temp;
                                         quitacomillas(&temp,(yyvsp[(1) - (2)].cad));
                                         (yyval.cad)=calloc(1,strlen(temp)+strlen((yyvsp[(2) - (2)].cad))+1);
                                         strcpy((yyval.cad),temp);
                                         strcat((yyval.cad),(yyvsp[(2) - (2)].cad));
                                         free((yyvsp[(1) - (2)].cad));
                                         free((yyvsp[(2) - (2)].cad));
                                         free(temp);;}
    break;

  case 22:

    {strcpy(buffer,(yyvsp[(1) - (1)].cad));
                                  sustituyedefines(buffer);
                                  free((yyvsp[(1) - (1)].cad));
                                  (yyval.cad)=strdup(buffer);
                                 ;}
    break;

  case 23:

    {strcpy(buffer,(yyvsp[(1) - (1)].cad));
                       eliminaretornos(buffer);
                       sustituyedefines(buffer);
                       free((yyvsp[(1) - (1)].cad));
                       (yyval.cad)=strdup(buffer);
                      ;}
    break;

  case 24:

    {if (enbloque) {
                                                      if (funcionparsecampo) funcionparsecampo(bloqueparse,campoparse);
                                                      if (campoparse->nteclas) campoparse->teclas=realloc(campoparse->teclas,campoparse->nteclas*sizeof(fteclas));
                                                         else {
                                                              free(campoparse->teclas);
                                                              campoparse->teclas=NULL;
                                                          }
                                                   } 
                                                  ;}
    break;

  case 25:

    {(yyval.cad)=(yyvsp[(1) - (1)].cad);;}
    break;

  case 26:

    {(yyval.cad)=strdup("CAMPO");;}
    break;

  case 27:

    {(yyval.cad)=strdup("TABLA");;}
    break;

  case 28:

    {(yyval.cad)=strdup("FICHERO");;}
    break;

  case 29:

    {char *extra;
                                       int nc;
                                       if (enbloque) {
                                          if ((nc=damecampo(bloqueparse,(yyvsp[(3) - (3)].cad)))!=-1) {
                                             campoparse=bloqueparse->c+nc;
                                             //warning(("En bloque %s campo %s duplicado\n",bloqueparse->fichero,$3));
                                          } else {
                                             campoparse=bloqueparse->c+bloqueparse->ncamp;
                                             bloqueparse->ncamp++;
                                             campoparse->b=bloqueparse;
                                          }
                                        } else {
                                          if ((nc=damecampoform(forparse,(yyvsp[(3) - (3)].cad)))!=-1) {
                                             campoparse=forparse->c+nc;
                                             //warning(("En form campo %s duplicado\n",$3));
                                          } else {
                                             campoparse=forparse->c+forparse->ncamp; 
											 forparse->ncamp++;
                                             campoparse->b=NULL;
                                          }
                                        }
                                       campoparse->f=forparse;
                                       strcpy(campoparse->nombre,(yyvsp[(3) - (3)].cad));
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
                                       free((yyvsp[(3) - (3)].cad));
                                      ;}
    break;

  case 30:

    {if (funcionparsebloque) funcionparsebloque(bloqueparse);
                                                           /*damecaracextrabloque(forparse,bloqueparse,2);*/
                                                           if (terminabloque(bloqueparse)) return(-1);
                                                           forparse->nbloques++;
                                                           enbloque=0;;}
    break;

  case 31:

    {if (funcionparsebloque) funcionparsebloque(bloqueparse);
                                                                      if (terminabloque(bloqueparse)) return(-1);
                                                                      forparse->nbloques++;
                                                                      enbloque=0;;}
    break;

  case 32:

    {if (funcionparsebloque) funcionparsebloque(bloqueparse);
                                                                      if (terminabloque(bloqueparse)) return(-1);
                                                                      forparse->nbloques++;
                                                                      enbloque=0;;}
    break;

  case 33:

    {tratadefbloque((yyvsp[(3) - (3)].cad));
                                                               free((yyvsp[(3) - (3)].cad));;}
    break;

  case 34:

    {tratadefbloque((yyvsp[(3) - (3)].cad));
                                                               free((yyvsp[(3) - (3)].cad));;}
    break;

  case 35:

    {
                                                     tratadefbloque((yyvsp[(3) - (3)].cad));
                                                     if (creabuffer((yyvsp[(3) - (3)].cad))) {
                                                        yyerror("No existe fichero");
                                                        free((yyvsp[(3) - (3)].cad));
                                                        return(-1);
                                                      }
                                                      free((yyvsp[(3) - (3)].cad));
                                                    ;}
    break;

  case 36:

    {fichero2vi((yyvsp[(1) - (1)].cad),&bloqueparse->vi);free((yyvsp[(1) - (1)].cad));;}
    break;

  case 39:

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
                       ;}
    break;

  case 40:

    {(yyval.doble)=traducetecla((yyvsp[(1) - (1)].cad));
                               if ((yyval.doble)==0) mensajefcm(10,"Tecla no existe %s",(yyvsp[(1) - (1)].cad));
                               free((yyvsp[(1) - (1)].cad));;}
    break;

  case 41:

    {(yyval.doble)=(yyvsp[(1) - (1)].doble);;}
    break;

  case 42:

    {if ((bloqueparse->padre=damebloque(forparse,(yyvsp[(3) - (3)].cad)))==NULL) {
                                                        mensajeparser("Bloque %s no definido",(yyvsp[(3) - (3)].cad));
                                                        return(-1);
                                                      }
                                                     free((yyvsp[(3) - (3)].cad));
                                                     ;}
    break;

  case 43:

    {
                                                     strcpy(bloqueparse->nombre,(yyvsp[(3) - (3)].cad));
                                                     free((yyvsp[(3) - (3)].cad));
                                                     if (damedefaulttabla) damedefaulttabla(bloqueparse);
                                                     ;}
    break;

  case 44:

    {
                                                              strcpy(bloqueparse->nombre,(yyvsp[(3) - (4)].cad));
                                                              strcat(bloqueparse->nombre," ");
                                                              strcat(bloqueparse->nombre,(yyvsp[(4) - (4)].cad));
                                                              free((yyvsp[(3) - (4)].cad));
                                                              free((yyvsp[(4) - (4)].cad));
                                                              if (damedefaulttabla) damedefaulttabla(bloqueparse);
                                                            ;}
    break;

  case 45:

    {
                                                                            if (extraparser) {
                                                                               char *extra;
                                                                               extra=extraparser(bloqueparse,(yyvsp[(3) - (6)].cad),(yyvsp[(5) - (6)].cad));
                                                                               if (!es_blanco(extra)) {
                                                                                  creabuffercadena(extra);
                                                                                  free(extra);
                                                                                }
                                                                             }
                                                                            free((yyvsp[(3) - (6)].cad));
                                                                            free((yyvsp[(5) - (6)].cad));
                                                                           ;}
    break;

  case 46:

    {bloqueparse->norowid=1;;}
    break;

  case 47:

    {int x,desp;
                                                     x=bloqueparse->vi.w.x1;
                                                     desp=(int)(yyvsp[(3) - (3)].doble);
                                                     bloqueparse->vi.w.x1=desp;
                                                     bloqueparse->vi.w.x2+=desp-x; ;}
    break;

  case 48:

    {int y,desp;
                                                     y=bloqueparse->vi.w.y1;
                                                     desp=(int)(yyvsp[(3) - (3)].doble);
                                                     bloqueparse->vi.w.y1=desp;
                                                     bloqueparse->vi.w.y2+=desp-y; ;}
    break;

  case 49:

    {strcpy(bloqueparse->includetdcss,(yyvsp[(3) - (3)].cad)); free((yyvsp[(3) - (3)].cad));;}
    break;

  case 50:

    {strcpy(bloqueparse->includecss,(yyvsp[(3) - (3)].cad)); free((yyvsp[(3) - (3)].cad));;}
    break;

  case 51:

    {strcpy(bloqueparse->includeficherocss,(yyvsp[(3) - (3)].cad)); free((yyvsp[(3) - (3)].cad));;}
    break;

  case 52:

    {strcpy(bloqueparse->includehtml,(yyvsp[(3) - (3)].cad)); free((yyvsp[(3) - (3)].cad));;}
    break;

  case 53:

    {strcpy(bloqueparse->includeficherohtml,(yyvsp[(3) - (3)].cad)); free((yyvsp[(3) - (3)].cad));;}
    break;

  case 54:

    { bloqueparse->wtipomarco=1; ;}
    break;

  case 55:

    { bloqueparse->wtipomarco=2; ;}
    break;

  case 56:

    { bloqueparse->wtipomarco=3; ;}
    break;

  case 57:

    { bloqueparse->wplegado = 1; ;}
    break;

  case 58:

    { bloqueparse->wplegado = 2; ;}
    break;

  case 59:

    {bloqueparse->vipx.posx=(int)(yyvsp[(3) - (3)].doble);;}
    break;

  case 60:

    {bloqueparse->vipx.posy=(int)(yyvsp[(3) - (3)].doble);;}
    break;

  case 61:

    {bloqueparse->vipx.lonx=(int)(yyvsp[(3) - (3)].doble);;}
    break;

  case 62:

    {bloqueparse->vipx.lony=(int)(yyvsp[(3) - (3)].doble);;}
    break;

  case 63:

    {bloqueparse->wregpag=(int)(yyvsp[(3) - (3)].doble);;}
    break;

  case 64:

    {bloqueparse->pxcol=(int)(yyvsp[(3) - (3)].doble);;}
    break;

  case 65:

    {bloqueparse->pxfila=(int)(yyvsp[(3) - (3)].doble);;}
    break;

  case 66:

    {
													bloqueparse->framesfile[bloqueparse->nbframesfile].posx=(int)(yyvsp[(3) - (14)].doble);
													bloqueparse->framesfile[bloqueparse->nbframesfile].posy=(int)(yyvsp[(5) - (14)].doble);
													bloqueparse->framesfile[bloqueparse->nbframesfile].lonx=(int)(yyvsp[(7) - (14)].doble);
													bloqueparse->framesfile[bloqueparse->nbframesfile].lony=(int)(yyvsp[(9) - (14)].doble);
													strcpy(bloqueparse->framesfile[bloqueparse->nbframesfile].nombre,(yyvsp[(11) - (14)].cad)); free((yyvsp[(11) - (14)].cad));
													strcpy(bloqueparse->framesfile[bloqueparse->nbframesfile].includecss,(yyvsp[(13) - (14)].cad)); free((yyvsp[(13) - (14)].cad));
													bloqueparse->nbframesfile++;;}
    break;

  case 67:

    {
                                                     poncolorbloque(bloqueparse,(yyvsp[(3) - (3)].cad));
                                                     defcolor=1;
                                                     free((yyvsp[(3) - (3)].cad)); ;}
    break;

  case 68:

    {bloqueparse->capitaliza=FORMATOUPPER;;}
    break;

  case 69:

    {bloqueparse->capitaliza=FORMATOLOWER;;}
    break;

  case 70:

    {bloqueparse->capitaliza=0;;}
    break;

  case 72:

    {bloqueparse->regpag=(int)(yyvsp[(3) - (3)].doble);;}
    break;

  case 73:

    {if (bloqueparse->ftimeout) liberatriger(bloqueparse->ftimeout);
                                                                bloqueparse->ftimeout=(yyvsp[(3) - (5)].dato).ptr;
                                                                if (bloqueparse->ftimeout!=NULL) {
                                                                   bloqueparse->timeout=(long)(yyvsp[(5) - (5)].doble);
                                                                 }
                                                               ;}
    break;

  case 74:

    {int tec,i;
                                                                    ftrigers *ft;
                                                                    tec=(int)(yyvsp[(3) - (5)].doble);
                                                                    ft=(yyvsp[(5) - (5)].dato).ptr;
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
                                                                    ;}
    break;

  case 75:

    {int tec,i;
                                                                    ftrigers *ft;
                                                                    tec=(int)(yyvsp[(3) - (5)].doble);
                                                                    ft=(yyvsp[(5) - (5)].dato).ptr;
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
                                                                    ;}
    break;

  case 76:

    {int tec,i;
                                                                    ftrigers *ft;
                                                                    tec=(int)(yyvsp[(3) - (5)].doble);
                                                                    ft=(yyvsp[(5) - (5)].dato).ptr;
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
                                                                    ;}
    break;

  case 79:

    {bloqueparse->aquery=1;;}
    break;

  case 80:

    {bloqueparse->pquery=1;;}
    break;

  case 81:

    {bloqueparse->tquery=1;;}
    break;

  case 82:

    {bloqueparse->soloquery=1;
                                                                     bloqueparse->norowid=1;
                                                                     bloqueparse->noinsert=1;
                                                                     bloqueparse->noorains=1;
                                                                     bloqueparse->nooradel=1;
                                                                     bloqueparse->noupdate=1;
                                                                     bloqueparse->nodelete=1;
                                                                     bloqueparse->nolock=1;;}
    break;

  case 86:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fpreinsert) liberatriger(bloqueparse->fpreinsert);
                                                                bloqueparse->fpreinsert=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 87:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->contextual) liberatriger(bloqueparse->contextual);
                                                                bloqueparse->contextual=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 88:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fpostinsert) liberatriger(bloqueparse->fpostinsert);
                                                                bloqueparse->fpostinsert=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 89:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fpreupdate) liberatriger(bloqueparse->fpreupdate);
                                                                bloqueparse->fpreupdate=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 90:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fpostupdate) liberatriger(bloqueparse->fpostupdate);
                                                                bloqueparse->fpostupdate=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 91:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fpredelete) liberatriger(bloqueparse->fpredelete);
                                                                bloqueparse->fpredelete=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 92:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fpostdelete) liberatriger(bloqueparse->fpostdelete);
                                                                bloqueparse->fpostdelete=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 93:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->ffinquery) liberatriger(bloqueparse->ffinquery);
                                                                bloqueparse->ffinquery=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 94:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fprebloque) liberatriger(bloqueparse->fprebloque);
                                                                bloqueparse->fprebloque=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 95:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fpostbloque) liberatriger(bloqueparse->fpostbloque);
                                                                bloqueparse->fpostbloque=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 96:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fprequery) liberatriger(bloqueparse->fprequery);
                                                                bloqueparse->fprequery=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 97:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fpostquery) liberatriger(bloqueparse->fpostquery);
                                                                bloqueparse->fpostquery=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 98:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fpreregistro) liberatriger(bloqueparse->fpreregistro);
                                                                bloqueparse->fpreregistro=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 99:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fpostregistro) liberatriger(bloqueparse->fpostregistro);
                                                                bloqueparse->fpostregistro=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 100:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fprecommit) liberatriger(bloqueparse->fprecommit);
                                                                bloqueparse->fprecommit=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 101:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fpostcommit) liberatriger(bloqueparse->fpostcommit);
                                                                bloqueparse->fpostcommit=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 102:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fprerollback) liberatriger(bloqueparse->fprerollback);
                                                                bloqueparse->fprerollback=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 103:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fpostrollback) liberatriger(bloqueparse->fpostrollback);
                                                                bloqueparse->fpostrollback=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 104:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fprepinta) liberatriger(bloqueparse->fprepinta);
                                                                bloqueparse->fprepinta=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 105:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fpostpinta) liberatriger(bloqueparse->fpostpinta);
                                                                bloqueparse->fpostpinta=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 106:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->fonpinta) liberatriger(bloqueparse->fonpinta);
                                                                bloqueparse->fonpinta=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 107:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->feventos.onclick) liberatriger(bloqueparse->feventos.onclick);
                                                                bloqueparse->feventos.onclick=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 108:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->feventos.onrightclick) liberatriger(bloqueparse->feventos.onrightclick);
                                                                bloqueparse->feventos.onrightclick=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 109:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->feventos.oncenterclick) liberatriger(bloqueparse->feventos.oncenterclick);
                                                                bloqueparse->feventos.oncenterclick=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 110:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->feventos.onmouseover) liberatriger(bloqueparse->feventos.onmouseover);
                                                                bloqueparse->feventos.onmouseover=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 111:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->feventos.onmouseout) liberatriger(bloqueparse->feventos.onmouseout);
                                                                bloqueparse->feventos.onmouseout=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 112:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->feventos.ondbclick) liberatriger(bloqueparse->feventos.ondbclick);
                                                                bloqueparse->feventos.ondbclick=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 113:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                                if (bloqueparse->feventos.onmousemove) liberatriger(bloqueparse->feventos.onmousemove);
                                                                bloqueparse->feventos.onmousemove=(yyvsp[(3) - (3)].dato).ptr;
                                                              }
                                                            ;}
    break;

  case 114:

    {
                       																					fstats *fs=bloqueparse->stats + bloqueparse->nbstats;
                                                                fs->nombre = (yyvsp[(3) - (13)].cad);
                                                                fs->posx=(int)(yyvsp[(5) - (13)].doble);
                                                                fs->posy=(int)(yyvsp[(7) - (13)].doble);
                                                                fs->lonx=(int)(yyvsp[(9) - (13)].doble);
                                                                fs->lony=(int)(yyvsp[(11) - (13)].doble);
                                                                fs->enmarcado = (int)(yyvsp[(13) - (13)].doble);
                                                                bloqueparse->nbstats++;
                       					                           ;}
    break;

  case 116:

    {fbotoneras *fbot=bloqueparse->fbot+bloqueparse->numbotoneras;
                                                   if (duplicabotonera((yyvsp[(3) - (3)].cad),fbot)) {
                                                      mensajefcm(10,"No existe botonera %s\n",(yyvsp[(3) - (3)].cad));
                                                      free((yyvsp[(3) - (3)].cad));
                                                      return(-1);
                                                   }
                                                   free((yyvsp[(3) - (3)].cad));
                                                   bloqueparse->numbotoneras++;;}
    break;

  case 117:

    {fbotoneras *fbot=bloqueparse->fbot+bloqueparse->numbotoneras;
                                        fbot->nombre=(yyvsp[(3) - (12)].cad);
                                        fbot->posx=(int)(yyvsp[(5) - (12)].doble);
                                        fbot->posy=(int)(yyvsp[(7) - (12)].doble);
                                        fbot->lonx=(int)(yyvsp[(9) - (12)].doble);
                                        fbot->lony=(int)(yyvsp[(11) - (12)].doble);
                                        bloqueparse->numbotoneras++;;}
    break;

  case 118:

    {if (creabuffer((yyvsp[(3) - (3)].cad))) {
                                                        yyerror("No existe fichero");
                                                        free((yyvsp[(3) - (3)].cad));
                                                        return(-1);
                                                      }
                                                      free((yyvsp[(3) - (3)].cad));
                                                      ;}
    break;

  case 119:

    {
                      						v10ajax *aj = bloqueparse->ajax+ bloqueparse->nbajax;
                      						aj->id 			 = (yyvsp[(3) - (16)].cad);
                      						aj->objetojs = (yyvsp[(5) - (16)].cad);
                      						aj->tipo 		 = (yyvsp[(7) - (16)].cad);
                      						aj->modulo 	 = (yyvsp[(9) - (16)].cad);
                      						aj->nombre   = (yyvsp[(11) - (16)].cad);
                      						aj->params   = (yyvsp[(13) - (16)].cad);
                      						aj->frecuencia  = (int)(yyvsp[(15) - (16)].doble);
                      						bloqueparse->nbajax++;
                      					;}
    break;

  case 120:

    { bloqueparse->sidebaroculto = 1;;}
    break;

  case 121:

    { bloqueparse->sidebaroculto = 2;;}
    break;

  case 122:

    {
                      					  v10comphtml *co = bloqueparse->comphtml + bloqueparse->nbcomphtml;
                      						co->id       = (yyvsp[(3) - (14)].cad);
                      						co->tipo 		 = (yyvsp[(5) - (14)].cad);
                      						co->modulo 	 = (yyvsp[(7) - (14)].cad);
                      						co->nombre   = (yyvsp[(9) - (14)].cad);
                      						co->params   = (yyvsp[(11) - (14)].cad);
                      						co->visible  = (int)(yyvsp[(13) - (14)].doble);
                      						bloqueparse->nbcomphtml++;
                      ;}
    break;

  case 123:

    {strcpy(botonparse->includecss,(yyvsp[(3) - (3)].cad));free((yyvsp[(3) - (3)].cad));;}
    break;

  case 124:

    {strcpy(botonparse->estilocss,(yyvsp[(3) - (3)].cad)); free((yyvsp[(3) - (3)].cad));;}
    break;

  case 125:

    {botonparse->oculto=(int)(yyvsp[(3) - (3)].doble);;}
    break;

  case 126:

    {botonparse->disabled=(int)(yyvsp[(3) - (3)].doble);;}
    break;

  case 129:

    {
               fbotones *b=bloqueparse->fb+bloqueparse->numbotones;
               bloqueparse->numbotones++;
               b->nombre=(yyvsp[(3) - (4)].cad);
               botonparse = b;;}
    break;

  case 130:

    {(yyval.cad) = (yyvsp[(3) - (3)].cad);;}
    break;

  case 131:

    {
										fbotones *b=bloqueparse->fb+bloqueparse->numbotones;
                 		if (duplicaboton((yyvsp[(1) - (1)].cad),b)) {
                     mensajefcm(10,"No existe boton %s\n",(yyvsp[(1) - (1)].cad));
                     free((yyvsp[(1) - (1)].cad));
                     return(-1);
                  	}
                  	free((yyvsp[(1) - (1)].cad));
                  	bloqueparse->numbotones++;
                  ;}
    break;

  case 132:

    {
                                                             botonparse->posx=(int)(yyvsp[(2) - (15)].doble);
                                                             botonparse->posy=(int)(yyvsp[(4) - (15)].doble);
                                                             botonparse->lonx=(int)(yyvsp[(6) - (15)].doble);
                                                             botonparse->lony=(int)(yyvsp[(8) - (15)].doble);
                                                             botonparse->texto=(yyvsp[(10) - (15)].cad);
                                                             botonparse->image=(yyvsp[(12) - (15)].cad);
                                                             botonparse->tecla=(int)(yyvsp[(14) - (15)].doble);
                                                             ;}
    break;

  case 133:

    {
                                                             botonparse->posx=(int)(yyvsp[(2) - (17)].doble);
                                                             botonparse->posy=(int)(yyvsp[(4) - (17)].doble);
                                                             botonparse->lonx=(int)(yyvsp[(6) - (17)].doble);
                                                             botonparse->lony=(int)(yyvsp[(8) - (17)].doble);
                                                             botonparse->texto=(yyvsp[(10) - (17)].cad);
                                                             botonparse->image=(yyvsp[(12) - (17)].cad);
                                                             botonparse->tecla=(int)(yyvsp[(14) - (17)].doble);
                                                             botonparse->tooltip=strdup(v10translate((yyvsp[(16) - (17)].cad)));
                                                             free((yyvsp[(16) - (17)].cad));
                                                             ;}
    break;

  case 134:

    {fbotoneras *fbot=bloqueparse->fbot+bloqueparse->numbotoneras;
                                                 fbotones *fb;
                                                 fb=damebotonbloque(bloqueparse,(yyvsp[(2) - (3)].cad));
                                                 if (fb==NULL) {
                                                    mensajeparser("no existe boton %s",(yyvsp[(2) - (3)].cad));
                                                    free((yyvsp[(2) - (3)].cad));
                                                    return(-1);
                                                 }
                                                 free((yyvsp[(2) - (3)].cad));
                                                 fbot->b[fbot->numbotones]=fb;
                                                 fbot->numbotones++;;}
    break;

  case 135:

    { fbotoneras *fbot=bloqueparse->fbot+bloqueparse->numbotoneras;
                                                 fbot->b=calloc(MAXBOTONES,sizeof(fbotones **));
                                                 fbot->numbotones=0;;}
    break;

  case 136:

    {ftrigers *ft;
                                          char *aux;
                                          aux=strchr((yyvsp[(1) - (1)].cad),'.');
                                          if (aux) {
                                             *aux=0;
                                             ft=dametrigerdll((yyvsp[(1) - (1)].cad),aux+1);
                                             (yyval.dato).tipo=1;
                                             *aux='.';
                                           } else {
                                             ft=dametriger((yyvsp[(1) - (1)].cad));
                                             (yyval.dato).tipo=0;
                                           }
                                          if (ft==NULL) {
                                             mensajeparser("No encuentro triger %s",(yyvsp[(1) - (1)].cad));
                                             free((yyvsp[(1) - (1)].cad));
                                             return(-1);
                                           }
                                          free((yyvsp[(1) - (1)].cad));
                                          (yyval.dato).ptr=ft;
                                         ;}
    break;

  case 137:

    {ftrigers *ft;
                                                              ft=(yyvsp[(2) - (2)].dato).ptr;
                                                              ft=duplicatriger(bloqueparse,ft);
                                                              ft->opciones=(yyvsp[(1) - (2)].entero);
                                                              (yyval.dato).ptr=ft;
                                                              if ((yyvsp[(2) - (2)].dato).tipo) {
                                                                 liberatriger((yyvsp[(2) - (2)].dato).ptr);
                                                               }
                                                             ;}
    break;

  case 138:

    {ftrigers *ft,*ft1;
                                                                                    ft1=(yyvsp[(2) - (5)].dato).ptr;
                                                                                    ft=(yyvsp[(4) - (5)].dato).ptr;
                                                                                    ft->b=bloqueparse;
                                                                                    ft->fun=ft1->fun;
                                                                                    ft->nombre=strdup(ft1->nombre);
                                                                                    ft->param=realloc(ft->param,ft->nparam*sizeof(void *));
                                                                                    ft->tipoparam=realloc(ft->tipoparam,ft->nparam*sizeof(int));
                                                                                    ft->opciones=(yyvsp[(1) - (5)].entero);
                                                                                    (yyval.dato).ptr=ft;
                                                                                    if ((yyvsp[(2) - (5)].dato).tipo) {
                                                                                       liberatriger((yyvsp[(2) - (5)].dato).ptr);
                                                                                      };}
    break;

  case 139:

    {(yyval.dato).ptr=NULL;;}
    break;

  case 140:

    {(yyval.entero)=CINVERSO;;}
    break;

  case 141:

    {(yyval.entero)=CIGNORE;;}
    break;

  case 142:

    {(yyval.entero)=CSOLOMEN;;}
    break;

  case 143:

    {(yyval.entero)=CTERMINA;;}
    break;

  case 144:

    {(yyval.entero)=CSUCCESS;;}
    break;

  case 145:

    {(yyval.entero)=CPREGUNTA;;}
    break;

  case 146:

    {(yyval.entero)=CFUNCION;;}
    break;

  case 147:

    {(yyval.entero)=(yyvsp[(1) - (2)].entero) | (yyvsp[(2) - (2)].entero);;}
    break;

  case 148:

    {(yyval.entero)=0;;}
    break;

  case 149:

    {(yyval.dato).protegido=(yyvsp[(1) - (3)].entero);
                                                               (yyval.dato).ptr=(yyvsp[(3) - (3)].dato).ptr;
                                                              ;}
    break;

  case 150:

    {(yyval.dato).ptr=(yyvsp[(1) - (1)].dato).ptr;
                                                               (yyval.dato).protegido=0;;}
    break;

  case 151:

    {if ((yyvsp[(1) - (1)].dato).protegido) {
                                        liberatriger((yyvsp[(1) - (1)].dato).ptr);
                                        (yyval.dato).ptr=NULL;
                                      } else {
                                        (yyval.dato).ptr=(yyvsp[(1) - (1)].dato).ptr;
                                      }
                                      (yyval.dato).protegido=(yyvsp[(1) - (1)].dato).protegido;
                                    ;}
    break;

  case 152:

    {ftrigers *ft;
                                                           ft=calloc(1,sizeof(ftrigers));
                                                           ft->param=calloc(MAXPARAM,sizeof(void *));
                                                           ft->tipoparam=calloc(MAXPARAM,sizeof(int));
                                                           ft->nparam=1;
                                                           ft->param[0]=(yyvsp[(1) - (1)].dato).ptr;
                                                           ft->tipoparam[0]=(yyvsp[(1) - (1)].dato).tipo;
                                                           (yyval.dato).ptr=ft;
                                                          ;}
    break;

  case 153:

    {ftrigers *ft=(yyvsp[(1) - (3)].dato).ptr;
                                                           if (ft->nparam>=MAXPARAM) {
                                                              mensajeparser("desmasiados parametros en triger");
                                                              return(-1);
                                                            }
                                                           ft->param[ft->nparam]=(yyvsp[(3) - (3)].dato).ptr;
                                                           ft->tipoparam[ft->nparam]=(yyvsp[(3) - (3)].dato).tipo;
                                                           ft->nparam++;
                                                           (yyval.dato).ptr=ft;
                                                           ;}
    break;

  case 154:

    {(yyval.dato).ptr=(yyvsp[(1) - (1)].cad);(yyval.dato).tipo=PARAMCADENA;;}
    break;

  case 155:

    {(yyval.dato).ptr=(yyvsp[(1) - (1)].dato).ptr;(yyval.dato).tipo=PARAMTRIGER;;}
    break;

  case 158:

    {(yyval.entero)=esta_protegido((yyvsp[(1) - (1)].cad));free((yyvsp[(1) - (1)].cad));;}
    break;

  case 159:

    {if (esta_protegido((yyvsp[(1) - (3)].cad))) (yyval.entero)=esta_protegido((yyvsp[(1) - (3)].cad));
                                                  else        (yyval.entero)=(yyvsp[(3) - (3)].entero);
                             free((yyvsp[(1) - (3)].cad));;}
    break;

  case 160:

    {if (protegidoform<1) (yyval.entero)=1; else (yyval.entero)=0;;}
    break;

  case 161:

    {(yyval.entero)=(yyvsp[(3) - (4)].entero);;}
    break;

  case 162:

    {lexbegin(STEXTOSQL);;}
    break;

  case 163:

    {  if (campoparse->combox.nopc>=MAXOPMENUS) {
                                     mensajeparser("Solo se admiten un máximo de %d opciones en un Combox",MAXOPMENUS);
                                     return(-1);
                                   }
                                   v10ansitooem((yyvsp[(1) - (1)].cad),(yyvsp[(1) - (1)].cad));
                                   campoparse->combox.opc[campoparse->combox.nopc]=strdup((yyvsp[(1) - (1)].cad));
                                   campoparse->combox.nopc++;
                                ;}
    break;

  case 164:

    {  if (campoparse->combox.nopc>=MAXOPMENUS) {
                                                        mensajeparser("Solo se admiten un máximo de %d opciones en un Combox",MAXOPMENUS);
                                                        return(-1);
                                                      }
                                                      v10ansitooem((yyvsp[(1) - (3)].cad),(yyvsp[(1) - (3)].cad));
                                                      campoparse->combox.opc[campoparse->combox.nopc]=strdup((yyvsp[(1) - (3)].cad));
                                                      campoparse->combox.nopc++;
                                                   ;}
    break;

  case 165:

    {campoparse->enter=0;;}
    break;

  case 166:

    {if ((yyvsp[(3) - (4)].entero)) {
                                                         campoparse->enter=0;
                                                       }
                                                      ;}
    break;

  case 167:

    {strcpy(campoparse->includecss,(yyvsp[(3) - (3)].cad)); free((yyvsp[(3) - (3)].cad));;}
    break;

  case 168:

    {strcpy(campoparse->estilocss,(yyvsp[(3) - (3)].cad)); free((yyvsp[(3) - (3)].cad));;}
    break;

  case 169:

    {campoparse->noinput=1;;}
    break;

  case 170:

    {if ((yyvsp[(3) - (4)].entero)) {
                                                         campoparse->noinput=1;
                                                       }
                                                      ;}
    break;

  case 171:

    {campoparse->where=(yyvsp[(2) - (2)].cad);;}
    break;

  case 172:

    {campoparse->autoenter=1;;}
    break;

  case 173:

    {campoparse->capitaliza=FORMATOUPPER;;}
    break;

  case 174:

    {campoparse->capitaliza=FORMATOLOWER;;}
    break;

  case 175:

    {campoparse->capitaliza=0;;}
    break;

  case 176:

    {campoparse->traducible=strdup("");;}
    break;

  case 177:

    {campoparse->traducible=strdup("$3");;}
    break;

  case 178:

    {if (v10usaansi) v10ansitooem((yyvsp[(3) - (4)].cad),(yyvsp[(3) - (4)].cad));
                                                  campoparse->tooltip=strdup(v10translate((yyvsp[(3) - (4)].cad)));
                                                  free((yyvsp[(3) - (4)].cad));;}
    break;

  case 179:

    {if (campoparse->funtooltip) liberatriger(campoparse->funtooltip);
                                                    campoparse->funtooltip=(yyvsp[(3) - (3)].dato).ptr;;}
    break;

  case 180:

    {campoparse->nopref=1;;}
    break;

  case 181:

    {campoparse->tabla=0;;}
    break;

  case 182:

    {campoparse->noupdate=1;;}
    break;

  case 183:

    {if ((yyvsp[(3) - (4)].entero)) campoparse->noupdate=1;;}
    break;

  case 184:

    {campoparse->noupdate=0;;}
    break;

  case 185:

    {if ((yyvsp[(3) - (4)].entero)==0) campoparse->noupdate=0;;}
    break;

  case 186:

    {campoparse->scan=1;;}
    break;

  case 187:

    {campoparse->scan=(int)(yyvsp[(3) - (4)].doble);;}
    break;

  case 188:

    {campoparse->prefijo=(yyvsp[(3) - (3)].cad);;}
    break;

  case 189:

    {campoparse->autotransmit=1;;}
    break;

  case 190:

    {if ((yyvsp[(1) - (1)].entero)) campoparse->noupdate=1;;}
    break;

  case 191:

    {if (protegidoform<1) {
                                 campoparse->noupdate=1;
                                 campoparse->invisible=1;
                               }
                             ;}
    break;

  case 192:

    {if ((yyvsp[(3) - (4)].entero)) {
                                                         campoparse->noupdate=1;
                                                         campoparse->invisible=1;
                                                       }
                                                      ;}
    break;

  case 193:

    {if (enbloque==0) {
                                 mensajeparser("Campo %s virtual en FRM",campoparse->nombre);
                                 return(-1);
                               }
                              campoparse->virtual=1;
                              strcpy(campoparse->nvirtual,campoparse->nombre);
                             ;}
    break;

  case 194:

    {if (enbloque==0) {
                                                     mensajeparser("Campo %s virtual en FRM",campoparse->nombre);
                                                     return(-1);
                                                   }
                                                  campoparse->virtual=1;
                                                  strcpy(campoparse->nvirtual,(yyvsp[(3) - (4)].cad));
                                                  free((yyvsp[(3) - (4)].cad));
                                                 ;}
    break;

  case 195:

    {campoparse->oculto=1;;}
    break;

  case 196:

    {if (campoparse->oculto==0) {
                                              mensajeparser("campo %s con formato no oculto",campoparse->nombre);
                                            } else {
                                             if (v10usaansi) v10ansitooem((yyvsp[(1) - (1)].cad),(yyvsp[(1) - (1)].cad));
                                             analizatokendia((yyvsp[(1) - (1)].cad),NULL,&campoparse->tipo,&campoparse->format,&campoparse->dec,&campoparse->lvar,&campoparse->lvar,NULL);
                                             campoparse->lon=tamv10tipo(campoparse->tipo,campoparse->lvar+1);
                                             if (campoparse->virtual) {
                                                mensajefcm(10,"En bloque %s Campo %s virtual oculto con formato",bloqueparse->fichero,campoparse->nombre);
                                             }
                                             free((yyvsp[(1) - (1)].cad));
                                            }
                                           ;}
    break;

  case 197:

    {campoparse->titulo=strdup((yyvsp[(3) - (4)].cad));;}
    break;

  case 198:

    {  campoparse->vipx.posx = (int)(yyvsp[(3) - (3)].doble); ;}
    break;

  case 199:

    {  campoparse->vipx.posy = (int)(yyvsp[(3) - (3)].doble); ;}
    break;

  case 200:

    {  campoparse->vipx.lonx = (int)(yyvsp[(3) - (3)].doble); ;}
    break;

  case 201:

    {  campoparse->vipx.lony = (int)(yyvsp[(3) - (3)].doble); ;}
    break;

  case 202:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                       if (campoparse->change) liberatriger(campoparse->change);
                                                       campoparse->change=(yyvsp[(3) - (3)].dato).ptr;;
                                                     }
                                                    ;}
    break;

  case 203:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                       if (campoparse->contextual) liberatriger(campoparse->contextual);
                                                       campoparse->contextual=(yyvsp[(3) - (3)].dato).ptr;;
                                                     }
                                                    ;}
    break;

  case 204:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                       if (campoparse->pref) liberatriger(campoparse->pref);
                                                       campoparse->pref=(yyvsp[(3) - (3)].dato).ptr;
                                                     }
                                                    ;}
    break;

  case 205:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                       if (campoparse->postf) liberatriger(campoparse->postf);
                                                       campoparse->postf=(yyvsp[(3) - (3)].dato).ptr;;
                                                     }
                                                    ;}
    break;

  case 206:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                       if (campoparse->prepinta) liberatriger(campoparse->prepinta);
                                                       campoparse->prepinta=(yyvsp[(3) - (3)].dato).ptr;;
                                                     }
                                                    ;}
    break;

  case 207:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                       if (campoparse->postpinta) liberatriger(campoparse->postpinta);
                                                       campoparse->postpinta=(yyvsp[(3) - (3)].dato).ptr;;
                                                     }
                                                    ;}
    break;

  case 208:

    {if ((yyvsp[(3) - (5)].dato).ptr) {
                                                       if (campoparse->convfrombd) liberatriger(campoparse->convfrombd);
                                                       campoparse->convfrombd=(yyvsp[(3) - (5)].dato).ptr;
                                                     }
												    if ((yyvsp[(5) - (5)].dato).ptr) {
                                                       if (campoparse->conv2bd) liberatriger(campoparse->conv2bd);
                                                       campoparse->conv2bd=(yyvsp[(5) - (5)].dato).ptr;
                                                     }
												   ;}
    break;

  case 209:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                       if (campoparse->onpinta) liberatriger(campoparse->onpinta);
                                                       campoparse->onpinta=(yyvsp[(3) - (3)].dato).ptr;
                                                     }
                                                    ;}
    break;

  case 210:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                       if (campoparse->feventos.onclick) liberatriger(campoparse->feventos.onclick);
                                                       campoparse->feventos.onclick=(yyvsp[(3) - (3)].dato).ptr;
                                                     }
                                                    ;}
    break;

  case 211:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                           if (campoparse->feventos.onrightclick) liberatriger(campoparse->feventos.onrightclick);
                                                           campoparse->feventos.onrightclick=(yyvsp[(3) - (3)].dato).ptr;
                                                        }
                                                       ;}
    break;

  case 212:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                           if (campoparse->feventos.oncenterclick) liberatriger(campoparse->feventos.oncenterclick);
                                                           campoparse->feventos.oncenterclick=(yyvsp[(3) - (3)].dato).ptr;
                                                        }
                                                       ;}
    break;

  case 213:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                           if (campoparse->feventos.onmouseover) liberatriger(campoparse->feventos.onmouseover);
                                                          campoparse->feventos.onmouseover=(yyvsp[(3) - (3)].dato).ptr;
                                                         }
                                                       ;}
    break;

  case 214:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                           if (campoparse->feventos.onmouseout) liberatriger(campoparse->feventos.onmouseout);
                                                           campoparse->feventos.onmouseout=(yyvsp[(3) - (3)].dato).ptr;
                                                         }
                                                       ;}
    break;

  case 215:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                         if (campoparse->feventos.ondbclick) liberatriger(campoparse->feventos.ondbclick);
                                                         campoparse->feventos.ondbclick=(yyvsp[(3) - (3)].dato).ptr;
                                                       }
                                                      ;}
    break;

  case 216:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                                           if (campoparse->feventos.onmousemove) liberatriger(campoparse->feventos.onmousemove);
                                                           campoparse->feventos.onmousemove=(yyvsp[(3) - (3)].dato).ptr;
                                                        }
                                                       ;}
    break;

  case 217:

    {
                                                                    campoparse->checkbox=calloc(1,sizeof(checkboxes));
                                                                    campoparse->checkbox->activo=1;
                                                                    v10ansitooem((yyvsp[(3) - (6)].cad),(yyvsp[(3) - (6)].cad));
                                                                    campoparse->checkbox->valor_false=strdup((yyvsp[(3) - (6)].cad));
                                                                    v10ansitooem((yyvsp[(5) - (6)].cad),(yyvsp[(5) - (6)].cad));
                                                                    campoparse->checkbox->valor_true=strdup((yyvsp[(5) - (6)].cad));
                                                                    ;}
    break;

  case 218:

    {
                                                   campoparse->combox.activo=1;
                                                   campoparse->combox.multiple=0;
                                                   campoparse->combox.index=0;
                                                  ;}
    break;

  case 219:

    {
                                                   campoparse->combox.activo=1;
                                                   campoparse->combox.multiple=1;
                                                   campoparse->combox.index=0;
                                                  ;}
    break;

  case 220:

    {
                                    if (campoparse->combox.activo==0) {
                                    	mensajeparser("Modificador de campo COMBOXREADONLY antes de definir el COMBOX");
                                      return(-1);
                                    }
                                    campoparse->combox.readonly=1;

                                  ;}
    break;

  case 221:

    {
                                           if (campoparse->combox.activo==0) {
                                              mensajeparser("Modificador de campo INDEXCOMBOX antes de definir el COMBOX");
                                              return(-1);
                                            }
                                           if ((int)(yyvsp[(3) - (3)].doble)>campoparse->combox.nopc-1) {
                                              mensajeparser("Índice seleccionado para el COMBOX supera las opciones (%d)",campoparse->combox.nopc);
                                             return(-1);
                                            }
                                           campoparse->combox.index=(int)(yyvsp[(3) - (3)].doble);
                                          ;}
    break;

  case 222:

    {
                                           if (campoparse->combox.activo==0) {
                                              mensajeparser("Modificador de campo REGPAGCOMBOX antes de definir el COMBOX");
                                              return(-1);
                                            }
                                           campoparse->combox.regpag=(int)(yyvsp[(3) - (3)].doble);
                                          ;}
    break;

  case 223:

    {int tec,i;
                                                                 ftrigers *ft;
                                                                 tec=(int)(yyvsp[(3) - (5)].doble);
                                                                 ft=(yyvsp[(5) - (5)].dato).ptr;
                                                                 if (ft) {
                                                                    if (enbloque) {
                                                                       for (i=0;i<campoparse->nteclas;i++) if (campoparse->teclas[i].t==tec) break;
                                                                       if (i<campoparse->nteclas) liberatriger(campoparse->teclas[i].trig);
                                                                       ft=(yyvsp[(5) - (5)].dato).ptr;
                                                                       campoparse->teclas[i].trig=ft;
                                                                       campoparse->teclas[i].t=tec;
                                                                       campoparse->teclas[i].b=bloqueparse;
                                                                       if (i==campoparse->nteclas) campoparse->nteclas++;
                                                                      } else liberatriger(ft);
                                                                  }
                                                                 ;}
    break;

  case 224:

    {
                                        campoparse->regpag=(int)(yyvsp[(3) - (3)].doble);
                                    ;}
    break;

  case 225:

    {
                                        campoparse->fichero=1;
                                        strcpy(campoparse->nombrefijo,"");
                                    ;}
    break;

  case 226:

    {
                                        campoparse->fichero=1;
                                        strcpy(campoparse->nombrefijo,(yyvsp[(3) - (4)].cad));
                                    ;}
    break;

  case 227:

    {switch ((yyvsp[(1) - (2)].entero)) {
                                                            case WHERE:if (bloqueparse->where) free(bloqueparse->where);
                                                                       bloqueparse->where=(yyvsp[(2) - (2)].cad);
                                                                       break;
                                                            case ORDERBY:if (bloqueparse->orderby) free(bloqueparse->orderby);
                                                                       bloqueparse->orderby=(yyvsp[(2) - (2)].cad);
                                                                       break;
                                                            case GROUPBY:if (bloqueparse->groupby) free(bloqueparse->groupby);
                                                                       bloqueparse->groupby=(yyvsp[(2) - (2)].cad);
                                                                       break;
                                                            case HAVING:if (bloqueparse->having) free(bloqueparse->having);
                                                                       bloqueparse->having=(yyvsp[(2) - (2)].cad);
                                                                       break;
                                                            case SELECT:if (bloqueparse->select) free(bloqueparse->select);
                                                                       bloqueparse->extraselect=(yyvsp[(2) - (2)].cad);
                                                                       break;
                                                           }
                                                        ;}
    break;

  case 228:

    {(yyval.entero)=(yyvsp[(1) - (2)].entero);lexbegin(STEXTOSQL);;}
    break;

  case 229:

    {(yyval.entero)=(yyvsp[(1) - (2)].entero);lexbegin(STEXTOSQL);;}
    break;

  case 230:

    {(yyval.entero)=(yyvsp[(1) - (2)].entero);lexbegin(STEXTOSQL);;}
    break;

  case 231:

    {(yyval.entero)=(yyvsp[(1) - (2)].entero);lexbegin(STEXTOSQL);;}
    break;

  case 232:

    {(yyval.entero)=(yyvsp[(1) - (2)].entero);lexbegin(STEXTOSQL);;}
    break;

  case 233:

    {if (bloqueparse->online) free(bloqueparse->online);
                                                             bloqueparse->online=(yyvsp[(2) - (2)].cad);;}
    break;

  case 234:

    {(yyval.entero)=(yyvsp[(1) - (2)].entero);lexbegin(SONLINE);;}
    break;

  case 235:

    {(yyval.entero)=(yyvsp[(1) - (1)].entero);;}
    break;

  case 236:

    {(yyval.entero)=(yyvsp[(1) - (1)].entero);;}
    break;

  case 237:

    {(yyval.entero)=(yyvsp[(1) - (1)].entero);;}
    break;

  case 238:

    {(yyval.entero)=(yyvsp[(1) - (1)].entero);;}
    break;

  case 239:

    {(yyval.entero)=(yyvsp[(1) - (1)].entero);;}
    break;

  case 240:

    {(yyval.entero)=(yyvsp[(1) - (1)].entero);;}
    break;

  case 241:

    {(yyval.entero)=(yyvsp[(1) - (1)].entero);;}
    break;

  case 242:

    {(yyval.entero)=(yyvsp[(1) - (1)].entero);;}
    break;

  case 243:

    {(yyval.entero)=(yyvsp[(1) - (1)].entero);;}
    break;

  case 244:

    {(yyval.entero)=(yyvsp[(1) - (1)].entero);;}
    break;

  case 245:

    {(yyval.entero)=(yyvsp[(1) - (1)].entero);;}
    break;

  case 246:

    {(yyval.entero)=(yyvsp[(1) - (1)].entero);;}
    break;

  case 247:

    {(yyval.entero)=(yyvsp[(1) - (1)].entero);;}
    break;

  case 248:

    {switch ((yyvsp[(1) - (1)].entero)) {
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
                                      ;}
    break;

  case 249:

    {if ((yyvsp[(3) - (3)].entero)) {
                                                                   switch ((yyvsp[(1) - (3)].entero)) {
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
                                                                 ;}
    break;

  case 250:

    {if ((yyvsp[(1) - (1)].entero)) {
                                              bloqueparse->noinsert=1;
                        bloqueparse->noupdate=1;
                        bloqueparse->nodelete=1;
                       };}
    break;

  case 251:

    {(yyval.entero)=(yyvsp[(1) - (2)].entero);lexbegin(STITULO);;}
    break;

  case 252:

    {(yyval.entero)=(yyvsp[(1) - (2)].entero);lexbegin(STITULO);;}
    break;

  case 253:

    {switch((yyvsp[(1) - (2)].entero)) {
                                                   case TITULO:if (bloqueparse->vi.titulo) free(bloqueparse->vi.titulo);
                                                               bloqueparse->vi.titulo=(yyvsp[(2) - (2)].cad);
                                                               break;
                                                   case AYUDA :if (bloqueparse->ayuda) free(bloqueparse->ayuda);
                                                               bloqueparse->ayuda=(yyvsp[(2) - (2)].cad);
                                                               break;
                                                }
                                             ;}
    break;

  case 254:

    {if (buscafcursor(bloqueparse,bloqueparse->fcur[bloqueparse->ncur].nombre)!=NULL) {
                                               mensajeparser("Cursor duplicado %s en bloque %s",bloqueparse->fcur[bloqueparse->ncur].nombre,bloqueparse->nombre);
                                               return(-1);
                                             }
                                            if (bloqueparse->ncur>=MAXFCURSORES-1) final(("demasiados cursores %ld",MAXFCURSORES));
                                            bloqueparse->fcur[bloqueparse->ncur].sql=(yyvsp[(2) - (2)].cad);
                                            bloqueparse->fcur[bloqueparse->ncur].b=bloqueparse;
                                            bloqueparse->ncur++;;}
    break;

  case 255:

    {lexbegin(STEXTOSQL);
                                          strcpy(bloqueparse->fcur[bloqueparse->ncur].nombre,(yyvsp[(3) - (3)].cad));
                                          free((yyvsp[(3) - (3)].cad));;}
    break;

  case 259:

    {lexbegin(SOPMENU);(yyval.cad)=(yyvsp[(1) - (1)].cad);;}
    break;

  case 260:

    {ftrigers *ft;
                                                    ft=dametriger((yyvsp[(1) - (1)].cad));
                                                    free((yyvsp[(1) - (1)].cad));
                                                    if (ft==NULL) {
                                                       mensajeparser("No encuentro triger %s",(yyvsp[(1) - (1)].cad));
                                                       return(-1);
                                                     }
                                                    (yyval.dato).ptr=duplicatriger(formenu->b,ft);;}
    break;

  case 261:

    {ftrigers *ft,*ft1;
                                                     ft1=dametriger((yyvsp[(1) - (3)].cad));
                                                     if (ft1==NULL) {
                                                        mensajeparser("No encuentro triger %s",(yyvsp[(1) - (3)].cad));
                                                        return(-1);
                                                      }
                                                     ft=(yyvsp[(3) - (3)].dato).ptr;
                                                     ft->b=formenu->b;
                                                     ft->fun=ft1->fun;
                                                     ft->nombre=(yyvsp[(1) - (3)].cad);
                                                     ft->param=realloc(ft->param,ft->nparam*sizeof(void *));
                                                     ft->tipoparam=realloc(ft->tipoparam,ft->nparam*sizeof(int));
                                                     (yyval.dato).ptr=ft;;}
    break;

  case 262:

    {if ((yyvsp[(3) - (3)].dato).ptr) {
                                            formenu->op[formenu->nopciones].opcion=(yyvsp[(1) - (3)].cad);
                                            formenu->op[formenu->nopciones].ft=(yyvsp[(3) - (3)].dato).ptr;
                                            formenu->nopciones++;
                                            if (funcionparsezoom) funcionparsezoom(formenu,formenu->op+formenu->nopciones-1,0);
                                          } else free((yyvsp[(1) - (3)].cad));;}
    break;

  case 263:

    {formenu->op[formenu->nopciones].opcion=(yyvsp[(1) - (3)].cad);
                                           formenu->op[formenu->nopciones].ft=(yyvsp[(3) - (3)].dato).ptr;
                                           formenu->nopciones++;
                                           if (funcionparsezoom) funcionparsezoom(formenu,formenu->op+formenu->nopciones-1,(yyvsp[(3) - (3)].dato).protegido);
                                           lexbegin(SOPMENU);;}
    break;



      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}





