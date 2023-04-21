/*
* Módulo : V10USERCOLU.C
* Objeto:  Carga de las columnas del usuario
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10user.h"


#define SELTABCOLUMNS     "SELECT UC.TABLE_NAME,UC.COLUMN_NAME,DATA_TYPE, "\
                                " DATA_LENGTH,DATA_PRECISION,DATA_SCALE, "\
                                " NULLABLE,COLUMN_ID,DEFAULT_LENGTH,COMMENTS,DATA_DEFAULT "\
                           " FROM SYS.DBA_TAB_COLUMNS UC,SYS.DBA_COL_COMMENTS CO"\
                           " WHERE UC.TABLE_NAME=:TABLE_NAME AND UC.TABLE_NAME=CO.TABLE_NAME AND "\
                                " UC.COLUMN_NAME=CO.COLUMN_NAME AND UC.OWNER=USER AND CO.OWNER=USER"\
                           " ORDER BY UC.TABLE_NAME,COLUMN_ID "
static v10cursors *vdseltabcolumns;
static columns column;
static char table_name[30+1];



static void fincursorescolumns(void)
{
  liberacursor(vdseltabcolumns);
}


static void initcursorescolumns(void)
{
  vdseltabcolumns=abrecursor(SELTABCOLUMNS);
  definetodo(vdseltabcolumns,column.table_name,sizeof(column.table_name),V10CADENA,
                              column.column_name,sizeof(column.column_name),V10CADENA,
                              column.data_type,sizeof(column.data_type),V10CADENA,
                              &column.data_length,sizeof(column.data_length),V10LONG,
                              &column.data_precision,sizeof(column.data_precision),V10LONG,
                              &column.data_scale,sizeof(column.data_scale),V10LONG,
                              column.nullable,sizeof(column.nullable),V10CADENA,
                              &column.column_id,sizeof(column.column_id),V10LONG,
                              &column.default_length,sizeof(column.default_length),V10LONG,
                              column.comentario,sizeof(column.comentario),V10CADENA,
                              column.data_default,sizeof(column.data_default),V10CADENA,NULL);
  bindtodo(vdseltabcolumns,"TABLE_NAME",table_name,sizeof(table_name),V10CADENA,NULL);
  preparaarrayfetch(vdseltabcolumns,30);
  atexit(fincursorescolumns);
}

int anadecolumns(void)
{
	int i = 0;
	int ret = 0;
	
	v10log(2,"Buscando columnas de las tablas...\n");
	if (!vdseltabcolumns) initcursorescolumns();
	while (i<user.ntables) {
		strcpy(table_name,user.table[i]->table_name);
		v10log(3," Buscando columnas de la tabla %s...\n",table_name);
		ejecutacursor(vdseltabcolumns);
		user.table[i]->ncolumns=0;
		memset(&column,0,sizeof(columns));
		while (fetchcursor(vdseltabcolumns)==0) {
			char *aux;
			if ((aux=strchr(column.data_default,'\n'))!=NULL) *aux=0;
			trim(column.data_default);
			user.table[i]->column[user.table[i]->ncolumns]=calloc(1,sizeof(columns));
			if (stricomp(column.data_type,"CHAR")==0) {
				column.tipo=TIPOCHAR;
				column.longitud=column.data_length+1;
				column.data_scale=0;
			}
			if (stricomp(column.data_type,"VARCHAR2")==0) {
				column.tipo=TIPOVARCHAR2;
				column.longitud=column.data_length+1;
				column.data_scale=0;
			}
			if (stricomp(column.data_type,"BLOB")==0) {
				column.tipo=TIPOVARCHAR2;
				column.longitud=column.data_length+1;
				column.data_scale=0;
			}
			if (stricomp(column.data_type, "CLOB") == 0) {
				column.tipo = TIPOVARCHAR2;
				column.longitud = column.data_length + 1;
				column.data_scale = 0;
			}
			if (stricomp(column.data_type, "XMLTYPE") == 0) {
				column.tipo = TIPOVARCHAR2;
				column.longitud = column.data_length + 1;
				column.data_scale = 0;
			}
			if (stricomp(column.data_type, "RAW") == 0) {
				column.tipo=TIPOVARCHAR2;
				column.longitud=(column.data_length*2)+1;
				column.data_scale=0;
			}
			if (stricomp(column.data_type,"NUMBER")==0) {
				column.tipo=TIPONUMBER;
				column.longitud=column.data_precision+1;
				column.data_length=column.data_precision;
			}
			if (stricomp(column.data_type,"DATE")==0) {
				column.tipo=TIPODATE;
				column.longitud=LTIPODATE;
				column.data_scale=0;
			}
			if (stricomp(column.data_type,"TIMESTAMP")==0) {
				column.tipo=TIPOTIMESTAMP;
				column.longitud=LTIPOTIMESTAMP;
				column.data_scale=0;
			}
			if (stricomp(column.data_type,"LONG")==0) {
				column.tipo=TIPOLONG;
				column.longitud=0;
			}
			if (!column.tipo) warning(("Tipo %s no definido",column.data_type));
			if (*column.nullable=='N') strcpy(column.nullablel,"NOT NULL");
			if (*column.nullable=='Y') strcpy(column.nullablel,"        ");
			*(user.table[i]->column[user.table[i]->ncolumns])=column;
			user.table[i]->ncolumns++;
			if (user.table[i]->ncolumns>MAXCOLUMNS) final(("MAXCOLUMNS pequeño"));
			v10log(4,"  COLUMN: %s\n",column.column_name);
			memset(&column,0,sizeof(columns));
		}
		i++;
	}
	return(ret);
}
