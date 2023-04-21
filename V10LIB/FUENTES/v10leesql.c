/*
* Módulo : V10LEESQL.C                                             
* Objeto:  Lectura de SQL a partir de ficheros de texto
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10db.h"

#define MAXFICCURSORES  200
#define MAXTOKEN        200
#define SEPARADORES    " =,;.()"

static v10cursors *(ficcursor[MAXFICCURSORES]);
static int ncursores;

static void finleecur(void)
{
    int i;
    for (i=0;i<ncursores;i++) {
        if (ficcursor[i]) liberacursor(ficcursor[i]);
        ficcursor[i]=0;
    }
}

static char *lee_tok(char *linea)
{
    char *aux;
    aux=linea;
    while (*aux) {
        if (strchr(SEPARADORES,*aux)!=NULL) break;
        aux++;
    }
    return(aux);
}

static void lee_nombre(char *linea,char *donde)
{
    char *aux;
    aux=lee_tok(linea);
    if (*aux==0) {
        strcpy(donde,linea);
        *linea=0;
    } else {
        *aux=0;
        strcpy(donde,linea);
        strcpy(linea,aux+1);
    }
}

static char *lee_linea(char *linea,int maxlon,FILE *fich,int *numlin)
{ 
    char *aux,*ret;
    while ((ret=fgetss(linea,maxlon,fich))!=NULL) {
        (*numlin)++;
        if (*linea=='#') continue;
        if (es_blanco(linea)) continue;
        if ((aux=strchr(linea,'\n'))!=NULL) *aux=0;
        sustituyedefines(linea);
        return(ret);
    }
    return(NULL);
}

static char *lee_sql(FILE *entrada,char *linea,char *nombre,int *numlin)
{
    char *ret,*ptro,*aux;
    char term=';';
    ptro=ret=calloc(1,MAXSQL);
    strcpy(ptro,linea);
    if (strstr(linea,"BEGIN")||strstr(linea,"DECLARE")) term='@';
    while ((aux=strchr(ptro,term))==NULL) {
        if (lee_linea(linea,MAXCADENA-1,entrada,numlin)==NULL) final(("Sql sin terminar %s",nombre));
        ptro+=strlen(ptro);
        if ((ptro-ret)+strlen(linea)>=MAXSQL) final(("Sql muy largo o no terminado en ;\n%s",ret));
        strcpy(ptro,linea);
        if (*ptro==' ') ptro++;
        ltrim(ptro);
    }
    *aux=0;
    ret=realloc(ret,strlen(ret)+1);
    return(ret);
}

v10cursors *damevsq(char *nombre)
{
    int i;
    for (i=0;i<ncursores;i++) {
        if (strcmp(ficcursor[i]->nombre,nombre)==0) return(ficcursor[i]);
    }
    return(NULL);
}  

v10cursors *damevsqnum(int num)
{
    if (num>=ncursores) return(NULL);
    return(ficcursor[num]);
}

void leevsq(char *nombre)
{
    FILE *entrada;
    char linea[MAXCADENA];
    char tok[MAXTOKEN],*aux;
    static int init=0;
    int numlin=0;
    char nombrecompleto[MAXPATH];
    if (init==0) {
        atexit(finleecur);
        init=1;
    }
    entrada=fopenseguro(nombre,"r");
    damenombrecompleto(nombre,nombrecompleto);
	while (lee_linea(linea, MAXCADENA - 1, entrada, &numlin)) {
		if (es_blanco(linea)) continue;
        lee_nombre(linea,tok);
        if (strcmp(tok,"CURSOR")!=0) final(("%s inesperado",tok));
        lee_nombre(linea,tok);
        if (damevsq(tok)!=NULL) final(("Cursor %s repetido",tok));
        aux=lee_sql(entrada,linea,tok,&numlin);
        ficcursor[ncursores]=parsecursornombref(aux,tok,"leevsq",nombrecompleto,numlin,DEPURADEFECTO);
        if (ficcursor[ncursores]==NULL) final(("Analizando cursor %s",tok));
        v10log(LOGNORMAL,"Analizado cursor %s\n",tok);
        ncursores++;
        free(aux);
    }
    v10log(LOGNORMAL,"Leidos %d cursores\n",ncursores);
    fclose(entrada);
}

v10cursors *damevsqseguro(char *nombre)
{
    v10cursors *ret;
    ret=damevsq(nombre);
    if (ret==NULL) final(("Cursor %s no definido",nombre));
    return(ret);
}
