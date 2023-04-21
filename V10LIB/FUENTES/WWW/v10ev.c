#include "v10wwwform.h"

v10httpeventos evactual;
static v10horas flagcent;

// obtiene el campo del evento
fcampos *v10evdamecampo(bloques *b,v10httpeventos *ev) 
{
	int nc,noculto=0;
	int ncampo=v10evdamecolumna(ev);
	// noculto empieza por 0, y ncampo por 1
	if (!b) return(NULL);	
	if (ncampo<0) return(NULL);
	for (nc=0;nc<b->ncamp;nc++) {
		if (b->c[nc].oculto) continue;
		if (noculto==ncampo-1) return(b->c+nc);			  		   
		noculto++;
	}	  
	return(NULL);
}

// obtiene el bloque del objeto del evento
bloques *v10evdamebloque(v10httpeventos *ev) 
{
	forms *f=v10dameformactual();
	char cadena[MAXPATH]="";
	int nbloque;
	v10httpeventos *miev;
	char *ptrfila,*ptrbl;
	if (f==NULL) return(NULL);  
	miev=ev;
	if (miev==NULL) miev=&evactual;
	ptrbl=strstr(miev->objeto,"bl");
	if (!ptrbl) return(NULL);
	ptrfila=strstr(ptrbl,"f");
	if (ptrfila) strcopia(cadena,ptrbl+2,(int)(ptrfila-(ptrbl+2)));  
	else strcpy(cadena,ptrbl+2);
	nbloque=atoi(cadena);
	if (nbloque>=0) return(f->b[nbloque]);  
	return(NULL);
}

// obtiene la fila del objeto del evento
// la fila empieza por 1
int v10evdamefila(v10httpeventos *ev) 
{
	v10httpeventos *miev;
	char *ptrfila,*ptrcol;
	char cadena[MAXPATH]="";
	miev=ev;
	if (miev==NULL) miev=&evactual;
	ptrfila=strstr(miev->objeto,"f");
	if (!ptrfila) return(-1);
	ptrcol=strstr(miev->objeto,"c");
	if (ptrcol) strcopia(cadena,ptrfila+1,(int)(ptrcol-(ptrfila+1)));
	else  strcpy(cadena,ptrfila+1);
	return(atoi(cadena));
}

// obtiene la columna del objeto el evento
// la columna empieza por 1
int v10evdamecolumna(v10httpeventos *ev) 
{
	v10httpeventos *miev;
	char *ptrcol;
	char cadena[MAXPATH]="";
	miev=ev;
	if (miev==NULL) miev=&evactual;
	ptrcol=strstr(miev->objeto,"c");
	if (!ptrcol)  return(-1);
	strcpy(cadena,ptrcol+1);
	return(atoi(cadena));
}

int v10evtipo(v10httpeventos *ev) 
{
	if (v10evdamefila(NULL)<0) return(EVBLOQUE);
	else return(EVCAMPO);
}

int v10evcamposidem(v10httpeventos *ev) 
{
	//  v10httpeventos *miev;
	forms *f=v10dameformactual();
	bloques *b=f->b[f->act],*b_ev=v10evdamebloque(ev);	
	fcampos *act=v10campoactual(b),*f_ev=v10evdamecampo(b_ev,ev);
	if (b_ev==b && act==f_ev)	return(1);
	else 	return(0);
}

int v10evfilasidem(bloques *b,v10httpeventos *ev)  
{
	int fila=v10evdamefila(ev);
	if (b->regpag==1 || b->s->clin==b->s->plin+(fila-1)) return(1);
	else return(0);
}

void v10ev2ascii(v10httpeventos *ev)
{
	v10log(LOGNORMAL, "%s", "Evento recibido\n");
	v10log(LOGNORMAL,"\n\tObjeto: %s\n\tEvento: %s\n\tDato: %s\n\tAntid: %s\n\tAntvalor: %s\n",
		   ev->objeto,ev->evento,ev->valor,ev->antid,ev->antvalor);
	v10evtoansi(ev->sesion);  
	v10evtoansi(ev->objeto);
	v10evtoansi(ev->evento);
	v10evtoansi(ev->valor);
	v10evtoansi(ev->antid);
	v10evtoansi(ev->antvalor);
	v10log(LOGNORMAL, "%s", "Fin Evento recibido\n");
}

static int v10muestrafechas(char pul,v10inputs *v,int tx,int ty,v10httpeventos *ev)
{
	int ret=0;
	v10dates f=0;
	switch (toupper(pul)) {
	case 'H': f=damedate();
		ret=1;
		break;
	case 'A': f=damedate()-1;
		ret=1;
		break;
	case 'M': f=damedate()+1;
		ret=1;
		break;
	}
	if (ret) {
		if (v->formato & F4ANO) jul2a(f,"DD-MM-Y.",evactual.antvalor);
		else                 jul2a(f,"DD-MM-YY",evactual.antvalor);
	}
	return(ret);
}

void v10evdamevalor(v10dialogs *vi,v10httpeventos *mievento) 
{
	int lon;
    v10inputs *v1;
    bloques *b = v10evdamebloque(mievento);
    fcampos *c = v10evdamecampo(b, mievento);

	if (!vi) return;
	v1=vi->act;
    if (v1->tipo == V10FECHA && strlen(mievento->antvalor) == 1) v10muestrafechas(*mievento->antvalor, v1, 0, 0,mievento);
    if (c && c->checkbox) {
        if (*mievento->antvalor == 'X') strcpy(mievento->antvalor, "S");
        if (*mievento->antvalor == ' ') strcpy(mievento->antvalor, "N");
        if (*mievento->antvalor == 'u') strcpy(mievento->antvalor, "N");

    }
	lon=tamv10tipo(v1->tipo,v1->lvar+1);
	memcpy(v1->ant,v1->dato,lon);
	if (v1->enter) {
		memset(v1->dato,0,lon);	
        trim(mievento->antvalor);
        a2v10tipo(mievento->antvalor, v1->tipo, v1->formato, v1->dec, mievento->antvalor);
        memcpy(v1->dato, mievento->antvalor, lon);
        if (v1->tipo == V10CADENA) ((char *)v1->dato)[lon-1] = 0;
	}   
}

static void v10evponencampo(v10httpeventos *ev, char *id) 
{
	char *antid=strdup(id);
	memset(ev,0,sizeof(*ev)); 
	strcpy(ev->evento,	"reposiciona"); 
	strcpy(ev->objeto,antid); // del campo activo al enviar la página
    evactual = *ev;
	free(antid);
}

static void v10evponencampoactual(v10dialogs *vi,v10httpeventos *ev) 
{
	forms *f=v10dameformactual();
	bloques *b;
	int col,fila;
	if (!f) return;
	if (strlen(ev->antid)==0) return;
	b=f->b[f->act];
	// antidactual, antid cuando se envio la página
	if (!strcmp(idanterior,ev->antid) && strcmp(ev->evento,"onbdlclick")==0) return;
	fila=v10evdamefila(ev);
	col=v10evdamecolumna(ev);
	if (col<0 || fila<0) return;
	v10evencolaevento(ev); 
	v10evponencampo(ev,ev->antid);  
	if (b->regpag==1 || fila<0 || b->s->clin==b->s->plin+(fila-1)) return;
}

int v10runhander(v10dialogs *vi,v10httpeventos *ev)
{
	int ret=0;
	evhandlers *evhdl;
	evhdl=v10gethandler(ev->evento) ;
	v10log(LOGDEBUG,"Buscando handler para evento %s %p handler %p\n",ev->evento,ev,evhdl);
    if (evhdl) {
        if (ev->sock && ev->sock != v10formserver && evhdl->esajax == 0) {
            v10log(LOGNORMAL, "v10runhandler: Server cambia de valor de %p a %p evento %s\n", v10formserver, ev->sock, ev->evento);
            v10formserver = ev->sock;
        }
        ret = evhdl->fun(vi, ev);
    }
	v10log(LOGDEBUG,"Fin handler para evento %s\n",ev->evento); 	
	return(ret);
}

void trataevbloques(v10httpeventos *ev) 
{	
	int i; 
	bloques *bev=v10evdamebloque(ev),*b=v10damebloqueactual();
    if (b) {
        int nc;
        nc = damecampo(b, "V10OBJETO");
        if (nc >= 0) {
            char *dir;
            dir = direccampo(b, nc);
            strcpy(dir, ev->objeto);
        }
    }
	if (!bev) return;
	if (!strcmp(ev->evento,"onclick") || !strcmp(ev->evento,"check")) { 
		if 	(v10evdamefila(ev)<0)	{ // si el evento es onclick, y de tipo bloque, determina el campo en el que lo posiciona
			if (bev==b) strcpy(ev->objeto,ev->antid);
			else {
				for (i=0;i<bev->form->nbloques;i++) if (bev->form->b[i]==bev) break;
				sprintf(ev->objeto,"bl%df1c1",i);
			}
		}
	}
}

int v10htmlevento(v10dialogs *vi)
{
	int ret=-1;
	v10httpeventos ev;
    int hayev;
	flagcent=damecent();
	if (v10htmlencurso>1) {v10htmlencurso=0; v10htmlenviado=0; return(0);}
	v10htmlenviado=0;
	v10htmlencurso=0;
	while (ret<0) {
		if (v10evencolados() && (vi || !v10dameformactual())) {
			ret=v10evrunencolados(vi);
			if (ret>=0) break;
		} else { 
			hayev=v10httpesperaevento(vi,&ev,1);
			if (hayev==1) {
                int fila, col;
				v10ev2ascii(&ev);
				trataevbloques(&ev);
                evactual = ev;
                fila = v10evdamefila(&ev);
                col = v10evdamecolumna(&ev);
                if (fila >= 0 && col >= 0) {
                    v10evponencampoactual(vi, &ev);
                } else {
                    strcpy(ev.objeto, ev.antid);
                    evactual = ev;
                    fila = v10evdamefila(&ev);
                    col = v10evdamecolumna(&ev);
                    if (fila >= 0 && col >= 0) {
                        v10evponencampoactual(vi, &ev);
                    }
                }
				ret=v10runhander(vi,&ev);
			} else ret=-1;
		}
	}
	if (vi) {
		v10wwwreposicionadialograton(vi);
		return v10evposterior(vi,ret);
	} else return(ret);
}

// si tiene un evento encolado, al recibir el nuevo, no trata el nievo, trata el encolado 
int v10htmleventodummy(v10dialogs *vi)
{
	int ret=-1;
	v10httpeventos ev;
    int hayev;
	flagcent=damecent();	
	if (oradebug) return(v10htmlevento(vi));	
	if (v10htmlencurso<=1) {
		v10htmlenviado=0;
		v10htmlencurso=0;
	}
	while (ret<0) {	
			hayev=v10httpesperaevento(vi,&ev,1);
           	if (v10evencolados()) {
				ret=v10evrunencolados(vi);
				if (ret>0 && (vi || !v10dameformactual())) break;
            }
            if (hayev==1) {	
                v10ev2ascii(&ev);
                trataevbloques(&ev);
                memcpy(&evactual,&ev,sizeof(ev));					
                v10evponencampoactual(vi,&ev);
                ret=v10runhander(vi,&ev);
                memcpy(&ev,&evactual,sizeof(ev));
                break;
            } else ret=-1;
	}
	if (vi) {
		v10wwwreposicionadialograton(vi);
		return v10evposterior(vi,ret);
	} else return(ret);
}

int v10evento(void) 
{
	return(v10htmlevento(&v10damebloqueactual()->vi));
}
