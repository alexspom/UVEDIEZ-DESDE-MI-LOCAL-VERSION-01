/*
* Módulo : V10ORAWORD.C
* Objeto:  Funciones para interfasar ORACLE con WORD
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-05-2008

* MODIFICACIONES
* ---------------------------
*/

#include "oracle\v10ora.h"

#define wdWord9TableBehavior    1
#define wdAutoFitContent        1
#define wdTableFormatGrid3     18
#define wdCell                 12
#define wdDeleteCellsEntireRow  2

static void cambiaretorno(char *cadena)
{
    char *aux;
    while ((aux=strstr(cadena,"\\n"))!=NULL) {
        *aux='\n';
        strcpy(aux+1,aux+2);
    }
}

int cadenaword(IDispatch *doc,char *estilo,char *cadena)
{  
    VARIANTARG varg2;
    IDispatch *rango;
    int pos;
    cambiaretorno(cadena);
    invocametodo(doc, "Range", &varg2, -1);
    rango = varg2.pdispVal;
    getproperty(rango, "End", &varg2,-1);
    pos=varg2.lVal;
    liberaidispatch(rango);
    invocametodo(doc, "Range", &varg2, "start",V10LONG,pos-1,"end",V10LONG,pos-1,-1);
    rango = varg2.pdispVal;
    if (!es_blanco(estilo)) putproperty(rango, "Style", NULL, NULL,V10CADENA,estilo,-1);
    putproperty(rango, "Text", NULL, NULL,V10CADENA,cadena,-1);
    getproperty(rango, "End", &varg2, -1);
    pos=varg2.lVal;
    liberaidispatch(rango);
    return(pos);
}

IDispatch *creatabla(IDispatch *doc,int filas,int columnas,char *estilotabla,char *estilotitulo,char *titulo,char *comentario)
{
  VARIANTARG varg2;
  char mitit[MAXCADENA];
  IDispatch *rango,*tables,*table;
  int pos;
  sprintf(mitit,"%s\n",titulo);
  pos=cadenaword(doc,estilotitulo,mitit);
  if (comentario) {
      pos=cadenaword(doc,"Normal","\n");
      pos=cadenaword(doc,"Normal",comentario);
      pos=cadenaword(doc,"Normal","\n\n");
  }
  invocametodo(doc, "Range", &varg2, "start",V10LONG,pos,"end",V10LONG,pos,-1);
  rango = varg2.pdispVal;
  getproperty(doc, "Tables", &varg2, -1);
  tables = varg2.pdispVal;
  invocametodo(tables, "Add", &varg2,"range",V10IDISPATCH,rango,
                                     "numrows",V10INT,filas,
                                     "numcolumns",V10INT,columnas,-1);
  table = varg2.pdispVal;
  if (!es_blanco(estilotabla)) putproperty(table,"Style",NULL,NULL,V10CADENA,estilotabla,-1);
  liberaidispatch(tables);
  return(table);
}

void pasacursorword(IDispatch *id,IDispatch *doc,v10cursors *v10sel,char *estilotabla,char *estilotitulo,char *titulo,char *comentario)
{
  VARIANTARG varg2;
  IDispatch *rango,*cell,*table,*seleccion,*fila,*columna;
  int nc,nreg=0;
  char **campos;
  table=creatabla(doc,2,v10sel->ndef,estilotabla,estilotitulo,titulo,comentario);
  invocametodo(table,"autoformat",NULL,"format",V10INT,wdTableFormatGrid3,
                     "applyheadingrows",V10INT,TRUE,"autofit",V10INT,TRUE,-1);
  invocametodo(table,"cell",&varg2,"row",V10INT,1,
                                   "column",V10INT,1,
                                   -1);
  cell = varg2.pdispVal;
  getproperty(cell,"row",&varg2,-1);
  fila=varg2.pdispVal;
  putproperty(fila,"Headingformat",NULL,NULL,V10INT,TRUE,-1);
  liberaidispatch(fila);
  getproperty(cell,"Range",&varg2,-1);
  rango = varg2.pdispVal;
  invocametodo(rango, "Select", &varg2, -1);
  liberaidispatch(rango);
  getproperty(id, "Selection", &varg2,-1);
  seleccion = varg2.pdispVal;
  campos=calloc(v10sel->ndef,sizeof(char *));
  for (nc=1;nc<=v10sel->ndef;nc++) {
      putproperty(seleccion, "Style", NULL, NULL,V10CADENA,"Normal",-1);
      putproperty(seleccion, "Text", NULL, NULL,V10CADENA,v10sel->def[nc-1].nombre,-1);
      invocametodo(seleccion, "moveright", &varg2, "unit",V10INT,wdCell,"count",V10INT,1,-1);
      campos[nc-1]=calloc(1,MAXCADENA);
      definecursor(v10sel,nc,campos[nc-1],MAXCADENA-1,V10CADENA);
   }
  if (ejecutacursor(v10sel)==0) {
     while (fetchcursor(v10sel)==0) {
           for (nc=1;nc<=v10sel->ndef;nc++) {
               cambiaretorno(campos[nc-1]);
               putproperty(seleccion, "Text", NULL,NULL,V10CADENA,campos[nc-1],-1);
               if (nreg==0) {
                  putproperty(seleccion, "Style", NULL, NULL,V10CADENA,"Normal",-1);
                }
               invocametodo(seleccion, "moveright", &varg2,"unit",V10INT,wdCell,"count",V10INT,1,-1);
            }
           nreg++;
      }
   }
  for (nc=1;nc<=v10sel->ndef;nc++) {
      free(campos[nc-1]);
   }
  free(campos);
  invocametodo(table, "cell", &varg2,"row",V10INT,nreg+2,
                                     "column",V10INT,1,-1);
  cell = varg2.pdispVal;
  invocametodo(cell,"Delete",NULL,"ShiftCells",V10INT,wdDeleteCellsEntireRow,-1);
  getproperty(table,"columns",&varg2,-1);
  columna=varg2.pdispVal;
  invocametodo(columna,"Autofit",NULL,-1);
  liberaidispatch(cell);
  liberaidispatch(seleccion);
  liberaidispatch(table);
}
void pasaselectword(IDispatch *id,IDispatch *doc,char *select,char *estilotabla,char *estilotitulo,char *titulo,char *comentario)
{
  v10cursors *v10sel;
  v10sel=abrecursornombre(titulo,select);
  pasacursorword(id,doc,v10sel,estilotabla,estilotitulo,titulo,comentario);
  liberacursor(v10sel);
}

