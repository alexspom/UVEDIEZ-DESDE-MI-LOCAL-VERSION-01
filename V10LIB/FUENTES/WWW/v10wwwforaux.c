/*
* Módulo :  v10wwwforaux.c
* Objeto:   Funciones de Form auxiliares para la version www
* 
* 
* Autor	 : Francisco José Guerrero Sánchez
* Fecha  : 25-09-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10wwwform.h"



void v10wwwfejecutaformaux(forms *formanterior,forms *formactual,int *ret)
{	
	//cargahtmlconf();
	//cierraficherosform(formanterior);	
	(*ret)=finputform(formactual);	 
	//reabreficherosform(formanterior);	
	
}



/*
int webpresentamenu(formenus *f)
{
int ret=0;
if (ret!=-1 && !hay_encolados() && !haycarpipeSSL(FormPipe)) {
form2HTML(formglobal,DEBUGING,f); // formenus  
ret=HTMLevento(NULL); // devuelve el número de opción seleccionada	
}
return(ret);
}
*/


int v10wwwcommitsino(forms *f)
{
	char *opciones[]={"¿ Desea Confirmar cambios ?","Si","No",NULL};
	int ret=-1;
	int antpul=ult_pul;
	if (f->preguntar==0) return(0);
	while (ret<0) ret=confirmasn(1,1,*opciones);
	ult_pul=antpul;
	if (ret==1) ret=commitform(f,NULL);
	else     ret=0; 
	f->preguntar=0;
	return(ret);
}


void v10frecalcpadreaux(bloques *b,bloques *padre)
{
	static int refrescandofrm;
	if (!refrescandofrm) {
		//refrescandofrm=1;
		//actualizabloque(padre);  
		//refrescandofrm=1;		
		//v10htmlevento(&b->vi);  // equivale a HTMLevento
	}
}


int v10llbloquearegistroaux(bloques *b) 
{
	//  mensaje_form(FORM(b),"Bloqueando registro pulse ^A para abortar");      
	v10form2html(FORM(b),1);  
	if (v10htmlevento(&b->vi)==1) return -1;         				  
	return 0;
}


int v10finputregistroaux(bloques *b) 
{
	if (!v10evencoladosnoajax() && !v10socksslhaycar(v10formserver)) v10form2html(b->form,1); /*,eszoom,NULL);*/
	return (v10htmlevento(&b->vi));
}


void v10wwwpintapaginabloque(virtsels *s,int resaltado)
{
	bloques *b=s->dato;
	if (VIRTPOS(s)<0) return;
	leeregistroi(b,VIRTPOS(s));
	//v10log(LOGNORMAL, "Entro en pintapaginabloque %s\n", b->nombre);
	if (b->noinsert && !CABECERA(b)->antiguo && VIRTPOS(s)>0) return; /*{		
		s->numero--;
		s->numlin--;
		if (s->clin>=s->numero) {
			s->clin--;
			if (b->regpag==1) {
				s->ulin--;
				s->plin--;
			}
		}
		return;
	}	    */
    preparaenter(b);
	if ((VIRTPOS(s)==s->numero-1 && !esnuloregistro(b)) && (b->quedan || !b->noinsert)) {
		s->numero++;
		s->numlin++;
		if (s->ulin-s->plin<s->lppag-1) s->ulin++;
	} else 
		if (VIRTPOS(s)==s->numero-1 && !esnuloregistro(b) && b->s->plin>b->s->ulin && b->s->ulin==b->s->numlin-1) {
			b->s->plin=b->s->ulin;
			b->s->clin=b->s->plin;
		}
	//v10log(LOGNORMAL, "Salgo en pintapaginabloque %s\n", b->nombre);
}


void v10wwwactualizabloque(bloques *b)
{	
	v10log(LOGNORMAL,"v10formserver vale %x\n",v10formserver);
	if (!v10formserver->v10sock) {
		free(v10formserver);
		v10log(LOGERROR, "%s", "Se sale porque se ha cerrado v10formserver por error en https\n");
		exit(0);
	}
	if (!b->invisible && !v10evencoladosnoajax() && !v10socksslhaycar(v10formserver) && b->enterquery!=4) 
		v10form2html(FORM(b),1);
}


int v10camposnoenter(v10dialogs *v)
{
	v10inputs *v1;
	bloques *b=v10damebloqueactual();
	if (!entrablebloque(b)) return 1;
	for (v1=v->prim;v1<=v->ult;v1++)
		if (v1->enter) return 0;
	return 1;
}
