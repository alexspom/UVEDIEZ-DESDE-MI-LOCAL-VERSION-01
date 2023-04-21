#include "vd.h"

#define LAPLICACION 3
#define MAXCOLUMNS          350
#define MAXCLAVES           100
#define MAXDIGLON           9


#define TIPOCHAR         1
#define TIPOVARCHAR2     2
#define TIPONUMBER       3
#define TIPODATE         4
#define TIPOLONG         5
#define TIPOVOIDPTR      6
#define TIPORAW          7
#define TIPOTIME         8

#define MAXLNOMBRE        31
#define LDATATYPE         10
#define LNULLABLE         2

typedef struct {
         char column_name[2*MAXLNOMBRE];
         char nombrec[MAXLNOMBRE];
         char tipoc[MAXLNOMBRE];
         char tipovd[MAXLNOMBRE];
         char data_type[LDATATYPE];
         int  tipo;
         long longitud;
         long data_length;
         long data_precision;
         long data_scale;
         char nullable[LNULLABLE];
         long column_id;
         long default_length;
		 int  tabla;
//		 int  solobind;
    } columns;

typedef struct {
         char    nombre[MAXLNOMBRE];
         char    nombrec[MAXLNOMBRE];
         int     numcol;
         columns **col;
       } defupdates;

typedef struct {
         char    nombre[MAXLNOMBRE];
         char    nombrec[MAXLNOMBRE];
         int     numcol;
         int     numcolselect;     
         columns **col;
         int     solobind[MAXCOLUMNS];
         columns **colselect;  
         columns **colbind;
         int     lock;
         int     nowait;
         int     recorre;
         int     recorreproc;
         char    *select;
         char    *where;
         char    *order;
         char    *table;
         char    *groupby;
         char    *gencount;
         char    *genmax;
         char    *genmin;
         char    *gensum;
		 int     noretvd;  
        } defselects;

typedef struct {
        char    nombre[MAXLNOMBRE];
        char    nombrec[MAXLNOMBRE];
        columns *col;
} defsecuens;

typedef struct {
	   char       aplicacion[LAPLICACION];
       char       table_name[MAXLNOMBRE];
       char       nombrec[MAXLNOMBRE];
       char		  nombrecorig[MAXLNOMBRE];
       char       abreviado[MAXLNOMBRE];
       char		  abreviadoorig[MAXLNOMBRE];
       char       abreviadoc[MAXLNOMBRE];
       char       abreviadocorig[MAXLNOMBRE];
       char       ntypedef[MAXLNOMBRE];
       char       ntypedeforig[MAXLNOMBRE];
       char       nstatic[MAXLNOMBRE];
       char		  nstaticorig[MAXLNOMBRE];
       int        numdic;
       int        numcol;
       int        numcolorig;
       columns    *col;
       int        numprimaria;
       columns    **primaria;
       int        numsel;
       defselects sel[MAXCLAVES];
       int        numup;
       defupdates up[MAXCLAVES];
       int        insert;
       int        delete;
       int        numsecuen;
       defsecuens sec[MAXCLAVES];
       int        lock;
       char       ampliaapi[MAXLNOMBRE];
       char    *gencount;
       char    *genmax;
       char    *genmin;
       char    *gensum;
       int        numagrup;
       int        numcount;
       int        numsum;
       int        oradebug;
       int        rowid;
       int        interfase;
} tablas;

// Funciones definidas en GENCH.C
void generah(tablas *tabla);  
char damecampomaxmin(char *dest,char **listacampos); 

// Funciones definidas en GENCC.C
void generac(tablas *tabla);

// Funciones definidas en GENCOLU.C
columns *busca_columnaextra(defselects *s,char *nombre);
columns *busca_columna(tablas *tabla,char *nombre);
//static char *lee_tok(char *linea);
