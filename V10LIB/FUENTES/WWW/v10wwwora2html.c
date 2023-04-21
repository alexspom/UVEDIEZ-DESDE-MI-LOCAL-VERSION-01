#include "v10wwwform.h"

#define OBJINPUT 1
#define OBJCELDA 2


static void damevalorcampo(fcampos *c, int esinput, char *valor)
{
    int decimales;
    decimales = dameindcampo(c->b, c, "DECIMALES");
	v10tipo2a(c->v->dato,c->tipo,c->lvar,c->format,decimales,valor,1);
	if (esinput) { // los valores de oracle ya son ansi, no se transorma previamente
		v10ansitohtml(trim(valor));
	} else {
		if (strlen(valor)==0) strcpy(valor," ");
		else trim(valor);
		v10ansitohtml(valor);
	}	
}

char *v10ora2campo(int incluyevalores,int nbloque,bloques *b,fcampos *c,int fila,char *nombre, int esinput, char *valor) 
{
	*valor=0;
	if (incluyevalores) damevalorcampo(c, esinput, valor);
	else sprintf(valor,"&bl%d_%02d_%s&",nbloque,fila,nombre);
	return(valor);
}

void v10mascarav2html(int nbloque,int fila,bloques *b) 
{
	int i,tipoobj;
	fcampos *c;
	char mascara[MAXPATH]="",valor[MAXCADENA]="";
    sprintf(mascara,"&bl%d_%02d_",nbloque,fila);
    if (strstr(v10html,mascara)==NULL) return;
	for (i=0;i<b->ncamp;i++) {
		c=b->c+i;
		if (!c->v || c->v->invisible) continue; // oculto
		sprintf(mascara,"&bl%d_%02d_%s&",nbloque,fila,c->nombre);
        *valor = 0;
		tipoobj=OBJCELDA;
		if (b->regpag==1) tipoobj=OBJINPUT;
		else {
			if ((b->s->clin-b->s->plin)==fila-1) // fila actual y campo entrable
				if (entrablecampo(b->c+i)) tipoobj=OBJINPUT;
		}
		damevalorcampo(c, (tipoobj==OBJINPUT)?1:0, valor);
		v10reemplazapatron(v10html,mascara,valor,1);
	}
}


void initvbloque(bloques *b) 
{
	if (b->enterquery==ENTERQ || !b->enterquery) {
		if ((debug>0 && b->s->ulin>0) || !debug) {
			grabaregistro(b,VIRTPOS(b->s)); 
		}
	}
	if (b->enterquery==ENTERQ) memcpy(b->buffer,b->bufuquery,(unsigned)b->tamano); 
}

int limitvbloque(bloques *b,int i) 
{
	if (b->s->ulin==-1) b->s->ulin=0;
	if (b->s->plin+i<=b->s->ulin) return(0);
	else return(1);
}

int damevbloquei(bloques *b,int i) 
{
	if (b->regpag==1) {
		if (b->enterquery==ENTERQ || !b->enterquery)
			if ((debug>0 && b->s->ulin>0) || !debug) leeregistroi(b,b->s->plin+i);
	} else leeregistroi(b,b->s->plin+i);
	if (b->noinsert && !CABECERA(b)->antiguo && (b->s->plin+i)>0)  return(0);
	return(1);
}

void finvbloque(bloques *b) 
{
	if (b->enterquery==ENTERQ || !b->enterquery)
		if ((debug>0 && b->s->ulin>0) || !debug) leeregistroi(b,VIRTPOS(b->s));	
	if (b->enterquery==ENTERQ) b->enterquery=1;
	if (b->s->clin<b->s->plin) b->s->plin=b->s->clin; 
	leeregistroi(b,b->s->clin);	
}
