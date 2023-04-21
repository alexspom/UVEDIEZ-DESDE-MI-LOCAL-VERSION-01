
//Funciones definidas en V10PARSEAUX.C
extern forms *forparse;
extern bloques *bloqueparse;
extern fcampos *campoparse;
extern fbotones *botonparse;
extern formenus *formenu;
extern int defcolor;
extern int protegidoform;
extern int enbloque;

//Funciones definidas en V10PARSE.C

#define INITIAL 0
#define SPINTADO 1
#define STEXTOSQL 2
#define SONLINE   3
#define STITULO   4
#define SOPMENU   5
int yyparse(void);

//Funciones definidas en V10PARSEAUX.C
int esta_protegido(char *cadena);
void quitacomillas(char **dest,char *ori);
void fichero2vi(char *texto,v10dialogs *vi);
int terminabloque(bloques *b);
void tratadefbloque(char *nombre);
void eliminaretornos(char *cadena);
void yyerror(char *msg);
ftrigers *dametrigerdll(char *libreria,char *funcion);

#define TERMINAVENTANA '|'

V10ORAIMPORT void (*mensajeparser)(char *cadena,...);

// Funciones definidas en V10LEX.L
int yylex(void);
void lexerror(char *cadena);
void lexbegin(int start);
int creabuffer(char *nombre);
int initlexcadena(char *cadena);
int initlex(char *cadena);
void terminalex(void);
