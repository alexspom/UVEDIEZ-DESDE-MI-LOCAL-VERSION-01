/*
* Módulo : USERWORD                                             
* Objeto:  Documenta un usuario en WORD
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/

#include "oracle\v10ora.h"

static char plantilla[MAXPATH],destino[MAXPATH];
static int salir;

int trataargdocword(char *param)
{
    v10cursors *cursor;
    char *sql;
    switch (toupper(*param)) {
           case 'S':   switch (toupper(param[1])) {
                              case 'P':   strcpy(plantilla,param+2);
                                          v10log(LOGNORMAL,"Leida plantilla %s\n",plantilla);
                                          break;
                              case 'D':   strcpy(destino,param+2);
                                          v10log(LOGNORMAL,"Leido destino %s\n",destino);
                                          break;
                              case 'F':   leevsq(param+2);
                                          v10log(LOGNORMAL,"Leido fichero de cursores %s\n",param+2);
                                          break;
                              case 'C':   cursor=damevsq(param+2);
                                          v10log(LOGNORMAL,"Leido cursor %s\n",param+2);
                                          if (cursor) {
                                              definetododinamico(cursor);
                                              cur2excel(cursor,plantilla,destino,salir);
                                          }
                                          break;
                              case 'X':   if (!es_blanco(param+2)) salir=atoi(param+2);
                                             else                  salir=1;
                                          break;
                              case 'S':   sql=param+2;
                                          v10log(LOGNORMAL,"Leido sentencia %s\n",param+2);
                                          sql2excel(sql,plantilla,destino,salir);
                                          break;
                       }
    }
    return(0);
}


#define CSELPRIM "SELECT CONSTRAINT_NAME,CONSTRAINT_TYPE "\
                      " FROM USER_CONSTRAINTS "\
                      " WHERE CONSTRAINT_TYPE in ('P','U') AND TABLE_NAME=:TABLE_NAME"
#define CSELFOREIGN "SELECT U.CONSTRAINT_NAME,U.R_CONSTRAINT_NAME,U1.TABLE_NAME "\
                      " FROM USER_CONSTRAINTS U,USER_CONSTRAINTS U1 "\
                      " WHERE U.CONSTRAINT_TYPE='R' AND U1.CONSTRAINT_NAME=U.R_CONSTRAINT_NAME AND "\
                            " U.TABLE_NAME=:TABLE_NAME"
#define CSELCOLPRIM "SELECT COLUMN_NAME "\
                     " FROM USER_CONS_COLUMNS "\
                     " WHERE CONSTRAINT_NAME=:CONSTRAINT_NAME"
static void documentatabla(IDispatch *id,IDispatch *doc,char *tabla,char *comentario)
{
  char select[MAXCADENA],nombre[100];
  v10cursors *selprim,*selcolprim,*selforeign;
  char constraint_name[100],r_constraint_name[100],table_name1[100],table_name[100],column_name[100],constraint_type[100];
  sprintf(select,"select co.column_name NOMBRE,DECODE(CO.DATA_TYPE,'VARCHAR2','C','NUMBER','N') T,"
                              "DECODE(CO.DATA_TYPE,'VARCHAR2',TO_CHAR(DATA_LENGTH),DECODE(DATA_SCALE,0,TO_CHAR(DATA_PRECISION),DATA_PRECISION||'.'||DATA_SCALE)) L, "
							  "NULLABLE \"Ob\",comments COMENTARIOS "
                       "FROM user_tab_columns co,user_col_comments cm "
                       "where co.table_name=cm.table_name and co.column_name=cm.column_name and "
                             "co.table_name='%s' "
                       "ORDER BY CO.COLUMN_ID",tabla);
  sprintf(nombre,"TABLA %s",tabla);
  pasaselectword(id,doc,select,"TABLATABLA","Título 1",nombre,comentario);
  selprim=abrecursor(CSELPRIM);
  definetodo(selprim,constraint_name,sizeof(constraint_name),V10CADENA,
                        constraint_type,sizeof(constraint_type),V10CADENA,
                        NULL);
  bindtodo(selprim,"TABLE_NAME",table_name,sizeof(table_name),V10CADENA,
      NULL);
  selforeign=abrecursor(CSELFOREIGN);
  definetodo(selforeign,constraint_name,sizeof(constraint_name),V10CADENA,
                        r_constraint_name,sizeof(r_constraint_name),V10CADENA,
                        table_name1,sizeof(table_name1),V10CADENA,
                        NULL);
  bindtodo(selforeign,"TABLE_NAME",table_name,sizeof(table_name),V10CADENA,
      NULL);
  selcolprim=abrecursor(CSELCOLPRIM);
  definetodo(selcolprim,column_name,sizeof(column_name),V10CADENA,
                        NULL);
  bindtodo(selcolprim,"CONSTRAINT_NAME",constraint_name,sizeof(constraint_name),V10CADENA,
      NULL);
  strcpy(table_name,tabla);
  if (ejefetchcursor(selprim)==0) {
      char mitit[MAXCADENA];
      sprintf(mitit,"\n%s: %s \n",*constraint_type=='P'?"PRIMARY KEY":"UNIQUE KEY",constraint_name);
      cadenaword(doc,mitit,"Normal");
      ejecutacursor(selcolprim);
      while (fetchcursor(selcolprim)==0) {
          sprintf(mitit," %s",column_name);
          cadenaword(doc,mitit,"Normal");
      }
      cadenaword(doc,"\n","Normal");
  }
  ejecutacursor(selforeign);
  while (fetchcursor(selforeign)==0) {
      char mitit[MAXCADENA];
      sprintf(mitit,"\nFOREIGN: %s REFERENCIA A TABLA %s CLAVE %s\n",constraint_name,table_name1,r_constraint_name);
      cadenaword(doc,mitit,"Normal");
      ejecutacursor(selcolprim);
      while (fetchcursor(selcolprim)==0){
          sprintf(mitit," %s ",column_name);
          cadenaword(doc,mitit,"Normal");
      }
      cadenaword(doc,"\n","Normal");
  }
}

static void documentausuario(IDispatch *id,IDispatch *doc)
{
    v10cursors *seltabla;
    char tabla[MAXNOMBREV10],comentario[MAXCADENA];
    pasaselectword(id,doc,"select TA.TABLE_NAME TABLA,CO.COMMENTS COMENTARIOS"
        " FROM USER_TABLES TA,USER_TAB_COMMENTS CO "
        " WHERE TA.TABLE_NAME=CO.TABLE_NAME AND TA.TABLE_NAME NOT LIKE '%HIST'","Tabla con lista 1","Normal","TABLAS DEL USUARIO",NULL);
    seltabla=abrecursornombre("usuario","select ta.table_name,co.comments "
        " from user_tab_comments co,user_tables ta "
        " where ta.table_name=co.table_name(+) AND TA.TABLE_NAME NOT LIKE '%HIST'");
    definetodo(seltabla,tabla,sizeof(tabla),V10CADENA,
        comentario,sizeof(comentario),V10CADENA,
        NULL);
    ejecutacursor(seltabla);
    while (fetchcursor(seltabla)==0) {
        documentatabla(id,doc,tabla,comentario);
    }                                                                                             
    liberacursor(seltabla);
}

static int pasaole(char *aplicacion)
{
    VARIANTARG varg1, varg2;
    IDispatch *id,*doc;
    id=startole(aplicacion,1);
    if (id==NULL) {
        mensajefcm(10,"Aplicacion %s no instalada",aplicacion);
        finole();
        return(-1);
    }
    if (Invoke(id, "Documents", &varg1, DISPATCH_PROPERTYGET, 0)) {
        putproperty(id, "Visible", NULL, NULL,V10INT,TRUE,-1);
        invocametodo(varg1.pdispVal, "Add", &varg2,"TEMPLATE",V10CADENA,"DOCUSER.DOT",-1);
        ReleaseVariant(&varg1);
        doc = varg2.pdispVal;
        documentausuario(id,doc);
        putproperty(doc, "Saved", NULL, NULL,V10INT,TRUE,-1);
        liberaidispatch(doc);
    }
    putproperty(id, "Visible", NULL, NULL,V10INT,TRUE,-1);
    liberaidispatch(id);
  finole();
  return(0);
}



int main(int argc,char *argv[])
{
    trataparamstd(_argc,_argv,trataargdocword,NULL);
    pasaole("word.application");
    return(0);
}

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
                   LPSTR cmd, int cmdshow)
{
    int ret;
    strcpy(TITULOVENTANA,"DOCUMENTAR UN USUARIO");
	initv10lib(hinst,hprev);
    trataparamstd(_argc,_argv,trataparammain,trataparamoracle,NULL);
    ret=main(_argc,_argv);
    return(ret);
}

