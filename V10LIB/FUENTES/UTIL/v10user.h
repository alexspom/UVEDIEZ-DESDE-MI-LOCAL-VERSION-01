#include "forms\v10form.h"

#define MAXFILE            255
#define MAXTABLAS          512
#define MAXCOLUMNS         250
#define LAPLICACION        4

#define TIPOCHAR         1
#define TIPOVARCHAR2     2
#define TIPONUMBER       3
#define TIPODATE         4
#define TIPOLONG         5
#define TIPOTIMESTAMP    6

#define LTIPODATE       21
#define LTIPOTIMESTAMP  31

#define LCOMENTARIO 500

typedef struct {
                char table_name[MAXNOMBREV10];
                char column_name[MAXNOMBREV10];
                char data_type[9+1];
                int tipo;
                long longitud;
                long data_length;
                long data_precision;
                long data_scale;
                char nullable[1+1];
                char nullablel[8+1];
                long column_id;
                long default_length;
                char v10mensaje[MAXNOMBREV10];
                char data_default[LCOMENTARIO];
                char comentario[LCOMENTARIO];
	       } columns;

typedef struct {
                char table_name[MAXNOMBREV10];
                char tablespace_name[MAXNOMBREV10];
                char cluster_name[MAXNOMBREV10];
                long pct_free;
                long pct_used;
                long ini_trans;
                long max_trans;
                long pct_increase;
                char backed_up[1+1];
                int ncolumns;
                columns *column[MAXCOLUMNS];
                char    comentario[LCOMENTARIO];
	       } tables;

typedef struct {
                char *nombre;
                char username[MAXNOMBREV10];
                long user_id;
                char aplicacion[LAPLICACION];
                char hficsal[MAXFILE];
                char sthficsal[MAXFILE];
                char dficsal[MAXFILE];
                char sficsal[MAXFILE];
				char sqlficsal[MAXFILE];
                char tficsal[MAXNOMBREV10];
                char status[MAXNOMBREV10];
                int ntables;
                tables *table[MAXTABLAS];
	       } users;
extern users user;

typedef struct {
                int con_tables;
                int con_columns;
	       } cfgs;
extern cfgs cfg;


/* Funciones definidas en USERINIT.C */
void userinit(int argc,char *argv[]);

/* Funciones definidas en USERUSER.C */
int anade_user(void);

/* Funciones definidas en USERTABL.C */
int anadetables(int todas);

/* Funciones definidas en USERCOLU.C */
int anadecolumns(void);

/* Funciones definidas en USERCHK.C */
int chequeadatos(void);

/* Funciones definidas en USERIMP.C */
void imprimesth(int generah,int extension);
void imprimeh(int generah,int extension);
void imprimestr(void);
void imprimesql(int generah,int extension);
