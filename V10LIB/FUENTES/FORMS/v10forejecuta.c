/*
* Módulo : V10FOREJECUTA.C
* Objeto:  Triger de ejecucion de nuevo formulario
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"

#define SUAVIZADO 0.60

static int decrementa(int valor,double decremento)
{
    int r,g,b;
    r=valor&0xff;
    g=(valor>>8)&0xff;
    b=(valor>>16)&0xff;
    r=(int)(r*decremento);
    g=(int)(g*decremento);
    b=(int)(b*decremento);
    if (r<0) r=0;
    if (g<0) g=0;
    if (b<0) b=0;
    return (r+(g<<8)+(b<<16));
}

static void suavizapantalla(int x1,int y1,int x2,int y2)
{
    extrawins *t=dameextrawin(hwnddefecto);
    int i,j;
    for (i=x1;i<x2;i++) {
        for (j=y1;j<y2;j++) {
            tpixels *tp=t->texto+j*t->columnas+i;
            tp->c.papel=decrementa(tp->c.papel,SUAVIZADO);
            tp->c.tinta=decrementa(tp->c.tinta,SUAVIZADO);
        }
    }
    InvalidateRect(hwnddefecto,NULL,0);
}
#define TIPOWHERE 1
#define TIPOORDER 2
void tratamodselect(bloques *b,char *nuevosql, int tipo)
{
    int np = numpieces(nuevosql, ";");
    char parsql[MAXCADENA];
    char *antsql;
    bloques *bn;
    int i;
    char *destino;
    destino = calloc(1, MAXCADENA);
    for (i = 0; i < np; i++) {
        bn = formglobal->b[i];
        switch (tipo) {
            case TIPOWHERE:antsql = bn->where;
                break;
            case TIPOORDER:antsql = bn->orderby;
                break;
            default:v10log(LOGERROR, "Tipo %d no definido\n", tipo);
                free(destino);
                return;
        }
        piece(nuevosql, parsql, ";", i+1);
        formglobal->preguntar = 1;
        if (!es_blanco(parsql)) {
            sustituyevariables(b, parsql, destino);
            if (*destino == '\'') {
                strcpy(destino, destino + 1);
                destino[strlen(destino) - 1] = 0;
                strcpy(parsql, destino);
                sustituyevariables(b, parsql, destino);
            }
            if (*parsql == '+') {
                strcpy(destino, destino + 1);
                if (antsql) {
                    switch (tipo) {
                        case TIPOWHERE:strins(destino, " AND ");
                            break;
                        case TIPOORDER:strins(destino, " , ");
                            break;
                            strins(destino, antsql);
                    }
                }
            }
            switch (tipo) {
                case TIPOWHERE:if (bn->where) free(bn->where);
                    bn->where = strdup(destino);
                    break;
                case TIPOORDER:if (bn->orderby) free(bn->orderby);
                    bn->orderby = strdup(destino);
                    break;
            }
            bn->pquery = 1;
        }
    }
    free(destino);
}

int fcejecutaform(bloques *b, char *pantalla, char *opciones, char *where, char *order, char *asigna, char *devuelve, char *titulo, char *aquery)
{
	char *destino;
	tpixels *copia;
	int ret;
	int error;
	char ntimeout[MAXNOMBREV10];
	forms *antform = formglobal;
	bloques *bn;
	destino = calloc(1, MAXCADENA);
	copia = salvapantallad(0, 0, COLUMNASPANTALLA, LINEASPANTALLA);
	suavizapantalla(0, 1, COLUMNASPANTALLA, LINEASPANTALLA);
	eszoom++;
	if (*opciones == 'M') *opciones = 'S';
	if (b->ftimeout && v10versionweb == 0) {
		sprintf(ntimeout, "FTIMEOUT%d", numtimeoutform);
		numtimeoutform--;
		liberav10timer(ntimeout);
	}
	formglobal = leeform(pantalla, opciones);
	if (formglobal) {
		bn = formglobal->b[0];
		formglobal->preguntar = 1;
        if (!es_blanco(where)) tratamodselect(b, where, TIPOWHERE);
        if (!es_blanco(order)) tratamodselect(b, order, TIPOORDER);
		if (!es_blanco(asigna)) {
			sustituyevariables(b, asigna, destino);
			asignavariables(bn, destino);
		}
		if (!es_blanco(titulo)) {
			free(bn->vi.titulo);
			sustituyevariables(b, titulo, destino);
			if (v10usaansi) v10ansitooem(destino, destino);
			bn->vi.titulo = strdup(destino);
		}
		if (!es_blanco(aquery)) {
			if (*aquery == 'S') bn->pquery = 1;
			else              bn->pquery = 0;
		}
		free(destino);

		if (!fejecutaformaux) {
			ret = finputform(formglobal);
		}
		else {
			fejecutaformaux(antform, formglobal, &ret);
		}

		destino = calloc(1, MAXCADENA);
		if (!es_blanco(devuelve)) {
			sustituyevariables(bn, devuelve, destino);
		}
		liberaform(formglobal);
		error = 0;
	}
	else error = -1;
	formglobal = antform;
	recuperapantallad(0, 0, COLUMNASPANTALLA, LINEASPANTALLA, copia);
	rellenadefault();
	if (!es_blanco(devuelve)) {
		if (ret == F(10)) {
			asignavariables(b, destino);
			actualizadialog(&b->vi);
		}
	}
	if (b->ftimeout && v10versionweb == 0) {
		numtimeoutform++;
		sprintf(ntimeout, "FTIMEOUT%d", numtimeoutform);
		declarav10timernt(ntimeout, (void(*)(v10timers *))(b->ftimeout->fun), b->timeout, TIMERTIMEOUT, b->ftimeout);
	}
	free(destino);
	eszoom--;
	return(error);
}

int fejecutaform(bloques *b,ftrigers *f)
{
    char *opciones=strdup(f->param[1]);
    char pantalla[MAXPATH]="",where[MAXCADENA]="",order[MAXCADENA]="";
    char *asigna=NULL,*devuelve=NULL,*titulo=NULL,*aquery=NULL;
    int ret;
    dameparametro(b,f,0,V10CADENA,pantalla);
    if (f->nparam>2) strcpy(where,f->param[2]);
    if (f->nparam>3) asigna=f->param[3];
    if (f->nparam>4) devuelve=f->param[4];
	if (f->nparam>5) titulo = f->param[5];
	if (f->nparam>6) aquery = f->param[6];
	if (f->nparam>7) strcpy(order, f->param[7]);
    ret=fcejecutaform(b,pantalla,opciones,where,order,asigna,devuelve,titulo,aquery);
    free(opciones);
    return(ret);
}