/*
* Módulo : SQL2EXCEL                                             
* Objeto:  Pasa una consulta SQL a una hoja Excel
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10form.h"

static char plantilla[MAXPATH],destino[MAXPATH];
static int salir;

int trataargsql2excel(char *param)
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


int main(int argc,char *argv[])
{
    trataparamstd(argc,argv,trataargsql2excel,NULL);
    return(0);
}

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
                   LPSTR cmd, int cmdshow)
{
    int ret;
    strcpy(TITULOVENTANA,"EXPORTACION DE SQL A EXCEL 1.0");
	initv10lib(v10hinst,v10hprev);
    trataparamstd(__argc,__argv,trataparammain,trataparamoracle,NULL);
    ret=main(__argc,__argv);
    return(ret);
}

