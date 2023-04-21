/*
* Módulo : V10USERTABLE.C
* Objeto:  Carga de las tablas del usuario
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10user.h"

#define SELTABLES     "SELECT UT.TABLE_NAME,TABLESPACE_NAME,CLUSTER_NAME, "\
                            " PCT_FREE,PCT_USED,INI_TRANS,MAX_TRANS, "\
                            " PCT_INCREASE,BACKED_UP,CO.COMMENTS "\
                      " FROM USER_TABLES UT,USER_TAB_COMMENTS CO "\
                      " WHERE CO.TABLE_NAME=UT.TABLE_NAME "\
                      " ORDER BY UT.TABLE_NAME "
static v10cursors *v10seltables;
static tables table;



static void fincursorestables(void)
{
  liberacursor(v10seltables);
}


static void initcursorestables(void)
{
  v10seltables=abrecursor(SELTABLES);
  definetodo(v10seltables,table.table_name,sizeof(table.table_name),V10CADENA,
                          table.tablespace_name,sizeof(table.tablespace_name),V10CADENA,
                          table.cluster_name,sizeof(table.cluster_name),V10CADENA,
                          &table.pct_free,sizeof(table.pct_free),V10LONG,
                          &table.pct_used,sizeof(table.pct_used),V10LONG,
                          &table.ini_trans,sizeof(table.ini_trans),V10LONG,
                          &table.max_trans,sizeof(table.max_trans),V10LONG,
                          &table.pct_increase,sizeof(table.pct_increase),V10LONG,
                          table.backed_up,sizeof(table.backed_up),V10CADENA,
                          table.comentario,sizeof(table.comentario),V10CADENA,NULL);
  preparaarrayfetch(v10seltables,10);
  atexit(fincursorestables);
}

int anadetables(int todas)
{
  int ret = 0;

  v10log(LOGNORMAL,"Buscando tablas del usuario...\n");
  if (!v10seltables) initcursorestables();
  if (ejecutacursor(v10seltables)) {
    cursordebug(v10seltables);
    ret=-1;
  } else {
    user.ntables=0;
    while(fetchcursor(v10seltables)==0) {
      if (!todas) {
        if (strnicomp(table.table_name,user.aplicacion,strlen(user.aplicacion))!=0) {
          v10log(LOGNORMAL,"  TABLA: %s, NO %s, descartada!!\n",table.table_name,user.aplicacion);
          continue;
        }
      }
      user.table[user.ntables]=calloc(1,sizeof(tables));
      *user.table[user.ntables]=table;
      user.ntables++;
      if (user.ntables>MAXTABLAS) final(("MAXTABLAS pequeño"));
      v10log(LOGNORMAL,"  TABLA: %s\n",table.table_name);
      if (hay_tecla()) {
        if (tecla()==esc) final(("Abortado por usuario"));
      }
    }
  }
  return(ret);
}
