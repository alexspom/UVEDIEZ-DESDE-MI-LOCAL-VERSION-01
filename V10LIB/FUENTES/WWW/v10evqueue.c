#include "v10wwwform.h"

#define MAXEVENCOLADOS 30

static v10httpeventos evqueue[MAXEVENCOLADOS+10];
static int ultqueue = 0;
CRITICAL_SECTION evqueuecritical; // manejo de la secci�n cr�tica entre hebras
static int v10initqueue = 0;


static void initcriticalqueue(void)
{
    if (v10initqueue) return;
    InitializeCriticalSection(&evqueuecritical);
    v10initqueue = 1;
} 

static void entraencritico(void)
{
    initcriticalqueue();
    EnterCriticalSection(&evqueuecritical);
}

static void saldecritico(void)
{
    initcriticalqueue();
    LeaveCriticalSection(&evqueuecritical);
}

void v10evencolaevento(v10httpeventos *ev)
{
	if (ultqueue>=MAXEVENCOLADOS) return;
    entraencritico();
	memcpy(evqueue+ultqueue,ev,sizeof(*ev));
	ultqueue++;
    saldecritico();
}


void v10evencola(char *objeto,char *evento,char *valor,char *antid,char *antvalor)
{
    static v10httpeventos newev;
    strcpy(newev.sesion, v10httpconf.idsesion);
    strcpy(newev.objeto, objeto);
    strcpy(newev.evento, evento);
    strcpy(newev.valor, valor);
    strcpy(newev.antid, antid);
    strcpy(newev.antvalor, antvalor);
    v10evencolaevento(&newev);
}


void v10evclick(void)
{
	bloques *b=v10damebloqueactual();		
	char idobjeto[MAXPATH]="";
	if (b->regpag>1) sprintf(idobjeto,"bl%df%dc%d",b->form->act,(b->s->clin-b->s->plin)+1,v10nbcampoactivo(b));
	else sprintf(idobjeto,"bl%df%dc%d",b->form->act,(b->s->clin-b->s->plin),v10nbcampoactivo(b));
	v10evencola(idobjeto,ONCLICK,"","","");
}

int v10evtecla(int t) 
{
	char kespecial[100]="",mievento[MAXPATH]="";
	bloques *b=v10damebloqueactual();
	v10inputs *v=b->vi.act;
	char valor[MAXCADENA]="";
	char aux[10]="";
    *valor = 0;
	v10tipo2a(v->dato,v->tipo,v->lvar,v->formato,v->dec,valor,1);
	v10comb(kespecial,t);
	if (*kespecial) sprintf(mievento,"%s_%s",ONKEYUPCOLA,kespecial);
	else strcat(mievento,ONKEYUPCOLA);
	v10evencola(b->fichero,mievento,ltoa(v10ansi2js(t),aux,10),"",valor);
    return(0);
}

int v10evpushtecla(int c)
{
	char valor[MAXCADENA]="";  
	char kespecial[100]="",mievento[MAXPATH]="";
	bloques *b=v10damebloqueactual();
	v10inputs *v=b->vi.act;
	char aux[100]="";
    *valor = 0;
	v10tipo2a(v->dato,v->tipo,v->lvar,v->formato,v->dec,valor,1);	
	v10comb(kespecial,c);
	if (*kespecial) sprintf(mievento,"%s_%s",ONKEYUPCOLA,kespecial);
	else strcat(mievento,ONKEYUPCOLA);
	v10evencola(b->fichero,ONKEYUPCOLA,ltoa(c,aux,10),"",valor);
    return(0);
}

int v10evrunencolados(v10dialogs *vi)
{
    v10httpeventos mievento;
    entraencritico();
    mievento = evqueue[0];
	ultqueue--;
	memcpy(evqueue,evqueue+1,sizeof(v10httpeventos)*ultqueue);  
    saldecritico();
    trataevbloques(&mievento);
    evactual = mievento;
    return(v10runhander(vi, &mievento));
}

int v10evencolados(void)
{
	return ultqueue;
}

int v10evencoladosnoajax(void)
{
    int i;
    for (i=0;i<ultqueue;i++) {
        if (strncmp(evqueue[i].evento,"ajax",4)) return(ultqueue);
    }
    return(0);
}

