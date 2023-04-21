#include "vd.h"

#define MAXCOLUMNS          100
#define MAXTABLES           150
#define MAXDIGLON           9

#define MAXLNOMBRE        21
#define LDATATYPE         21
#define LNULLABLE         2

#define GEXTRA      0
#define GCURSOR     1
#define GNOMBRE     2
#define GSELECT     3
#define GPROCEDURE  4
#define GORADEBUG   5

#define TIPOCHAR         96
#define TIPOVARCHAR2     1
#define TIPONUMBER       2
#define TIPODATE         12
#define TIPOLONG         8
#define TIPORAW          23
#define TIPOVOIDPTR      99
#define TIPOTIME         100
#define TIPOROWID        11

char nomabreviado[MAXLNOMBRE];
char nomabreviadoc[MAXLNOMBRE];

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
         char table_name[2*MAXLNOMBRE];    		 
    } columns;

typedef struct {
         char table_name[2*MAXLNOMBRE];
         char alias[MAXLNOMBRE];
    } tables;

typedef struct {
          char       nombre[MAXLNOMBRE];
          char       nombrec[MAXLNOMBRE];
          char       sql[MAXCADENA];
          columns    *coldef;
          int        numdef;
          columns    *colbind;
          int        numbind;
          tables     *tablas;
          int        numtablas;
          int        numcursor;
          int        tipocur;
}cursor;
extern int soradebug;

void generah(cursor *cursores, int numcur, columns *col, int numcolextra,char **lineash,int nlinh);
void generac(cursor *cursores, int numcur, columns *col, int numcolextra,char **lineasc,int nlinc);
