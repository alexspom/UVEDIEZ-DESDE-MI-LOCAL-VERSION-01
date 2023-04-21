#include "v10wwwform.h"
#ifndef __LINUX__
extern int muestraayuda;
#endif


static int fselmenu(v10dialogs *v,v10httpeventos *ev)
{
	v10wwwelige(ev->valor);
	return(0);
}

static int freposiciona(v10dialogs *v,v10httpeventos *ev) 
{
	return(MOUSEPOS);
}

static int fonkeyupcola(v10dialogs *v,v10httpeventos *ev) 
{
	int ch;
	ch=v10js2ansi(ev->evento,atoi(ev->valor));
	if (!formglobal) return(0);
	return(ch);	
}

static int ffindebug(v10dialogs *v,v10httpeventos *ev) 
{
	STDpushtecla(ALT('D'));
	if (hay_tecla_normal()) STDtecla();	
	return(ALT('D'));
}

static int fayuda(v10dialogs *v,v10httpeventos *ev)  
{
#ifndef __LINUX__
	muestraayuda=1;
#endif
	if (formglobal) {
		v10evdamevalor(v,ev);    	  		
		v10js2ansi(ev->evento,atoi(ev->valor));
	}
	return(0);
}

static int fonkeyup(v10dialogs *v,v10httpeventos *ev) 
{
	int ch;
	//ultimoevento=llevocent();
	v10evdamevalor(v,ev);    	  		
	ch=v10js2ansi(ev->evento,atoi(ev->valor));
	if (ch==ALT('D')) {
		STDpushtecla(ch);
		if (hay_tecla_normal()) STDtecla();
		if (formglobal) { 
			v10form2html(formglobal,1);
			v10htmlenviado=v10htmlencurso=0;
			return -1;
		}
    } else if (ch==F(1)) {
        return(fayuda(v,ev));
    }
	if (!formglobal) return(0);
    if (ch == 4000) {
        encolatecla(cua);
        encolatecla(cua);
        ch = 40;
    }
	return(ch);	
}

static int fconfirma(v10dialogs *v,v10httpeventos *ev) 
{
	int ch;	
	ch=v10js2ansi(ev->evento,atoi(ev->valor));
	switch (ch) {
		case 'S':
		case 's': return(1);
		case 'N':
		case 'n': return(0);
		case 'cr': return(1);
		case 'esc': return(-1);
		default: return(-1);
	}
	return(ch);	
}


static int fondblclick(v10dialogs *v, v10httpeventos *ev)
{
    bloques *b = v10evdamebloque(ev);
    fcampos *c = v10evdamecampo(b, ev);
    //  ultimoevento=llevocent(); 
    v10evdamevalor(v,ev);
    if (!b) return(0);
    if (c && c->feventos.ondbclick) {
        c->feventos.ondbclick->fun(b, c->feventos.ondbclick);
    }
    return(0);
}

static int fonclick(v10dialogs *v, v10httpeventos *ev)
{
    bloques *b = v10evdamebloque(ev);
    fcampos *c = v10evdamecampo(b, ev);
    //  ultimoevento=llevocent(); 
    v10evdamevalor(v,ev);
    if (!b) return(0);
    if (c && c->feventos.onclick) {
        c->feventos.onclick->fun(b, c->feventos.onclick);
    }
    if (!strcmp(ev->valor, "scroll")) {
        v10damebloqueactual()->visiblescroll = (v10damebloqueactual()->visiblescroll == 0) ? 1 : 0;
        return(0);
    }
    if (!strcmp(ev->valor, "plegar")) {
        b->wplegado = 1;
        return(0);
    }
    if (!strcmp(ev->valor, "desplegar")) {
        b->wplegado = 2;
        return(0);
    }
    return(MOUSEPOS);
}

static int fsalir(v10dialogs *v, v10httpeventos *ev)
{
    forms *f = v10dameformactual();
    if (f) {
        int i;
        v10evencolaevento(ev);
        f->modif = 0;
        for (i = 0; i < f->nbloques; i++) f->b[i]->modif = 0;
    }
    _exit(3);
    return(0);
}

static int freiniciar(v10dialogs *v, v10httpeventos *ev)
{
    reiniciaform(NULL, NULL);
    return(0);
}

static int feditmenu(v10dialogs *v, v10httpeventos *ev)
{
    editamenus();
    return(0);
}


static int feditpan(v10dialogs *v, v10httpeventos *ev)
{
    char pathbloque[MAXPATH];
	damenombrecompleto(formglobal->b[formglobal->act]->fichero, pathbloque);  
	invocaeditor(pathbloque,NULL);
	return(0);
}


static int feditfrm(v10dialogs *v,v10httpeventos *ev) 
{
	char pathfrm[MAXPATH];
	char form[MAXCADENA]="";
	strcpy(form, formglobal->nombre);
	if (!strstr(strmay(form),".FRM")) strcat(form, ".FRM");
	damenombrecompleto(form, pathfrm);
	invocaeditor(pathfrm,NULL);
	return(0);
}


static int fedittodo(v10dialogs *v,v10httpeventos *ev) 
{
	int i,nb=0;
	char *fichero[20];
	char destino[MAXCADENA]="",form[MAXCADENA]="";
	strcat(form, formglobal->nombre);
	if (!strstr(strmay(form),".FRM")) strcat(form, ".FRM");
	damenombrecompleto(form, destino); 
	fichero[nb++]=strdup(destino);
	for (i=0;i<formglobal->nbloques;i++) {
		damenombrecompleto(formglobal->b[i]->fichero,destino);  
		fichero[nb++]=strdup(destino);
	}
	invocaeditormultiple(fichero,nb);
	for (i=0;i<nb;i++) free(fichero[i]);
	return(0);
}

static int fzoom(v10dialogs *v,v10httpeventos *ev) 
{
	int op=atoi(ev->valor);
	if (op==0) ult_pul = esc; // ha pulsado esc
	else ult_pul=cr;
	return(op-1);
}

static int fextonline(v10dialogs *v,v10httpeventos *ev) 
{
	char mititulo[MAXCADENA]="",mionline[MAXCADENA]="",titulocompleto[MAXCADENA]="";
	bloques *b=v10damebloqueactual();
	strcpy(mititulo,v10translate(b->vi.titulo));
	v10ansitohtml(v10wwwoem2ansi(mititulo));
	sprintf(titulocompleto,"Ayuda Online: %s",mititulo);	
	v10online2html(b,mionline,1);
	v10wwwmensajeonline(titulocompleto, mionline);
	return(0);
}

extern char *textowhere;
extern char *textoorder;
extern char *textohaving;
extern char *titulowhere;

static void editwherevalor(v10httpeventos *ev, char *lit,char *dest) 
{
	char *ptr1,*ptr2;
	ptr1=strstr(ev->antvalor,lit);
	ptr1+=strlen(lit);
	ptr2=strstr(ptr1,"&FIN&");
	strcopia(dest,ptr1,(int)(ptr2-ptr1));
}

static int feditwhere(v10dialogs *v,v10httpeventos *ev) 
{
	int ch;
	char *litwhere[]={"WHERE=","ORDER=","HAVING=","TITULO="};
	ch=v10js2ansi(ev->evento,atoi(ev->valor));
	if (ch==F(4))  {
		*textowhere=*textoorder=*textohaving=*titulowhere=0;
		editwherevalor(ev,litwhere[0],textowhere);
		editwherevalor(ev,litwhere[1],textoorder);
		editwherevalor(ev,litwhere[2],textohaving);
		editwherevalor(ev,litwhere[3],titulowhere);
	}
	return(ch);
}

static int fselwhere(v10dialogs *v,v10httpeventos *ev) 
{
	int ch;
	ch=v10js2ansi(ev->evento,atoi(ev->valor));	
	if (ch>0)  ult_pul=cr;
	else ult_pul=esc;
	return(ch-1);
}

static int fdelwhere(v10dialogs *v,v10httpeventos *ev) 
{
	int ch;
	ch=v10js2ansi(ev->evento,atoi(ev->valor));	
	if (ch>0)  ult_pul=dele;
	else ult_pul=esc;
	return(ch-1);
}

static int fposcursor(v10dialogs *v,v10httpeventos *ev) 
{
	int ret=atoi(ev->objeto);
	ult_pul=ev->valor[0];
	return(ret);
}

static int ftimeout(v10dialogs *v,v10httpeventos *ev) 
{
	bloques *b=v10damebloqueactual();
	if (!b) return(0);
	if (b->timeout) b->ftimeout->fun(b,b->ftimeout);
	return(0);
}

static int fabrecombox(v10dialogs *v,v10httpeventos *ev) 
{
	muestracombox=1;
	if (!strcmp(ev->objeto,ev->antid)) return(0);
	return(fonclick(v,ev));
}

static int fselectcombox(v10dialogs *v,v10httpeventos *ev) 
{
	strcpy(ev->antvalor,ev->valor);
	v10evdamevalor(v,ev); 
    v10evtecla(tab);
	/*v10evtecla(tab);   
	v10evtecla(stab);*/
	return(-1);
}

static int fcheck(v10dialogs *v,v10httpeventos *ev)  
{
	v10httpeventos evonclick;
	v10httpeventos evtecla;
	
	memcpy(&evonclick,ev,sizeof(evonclick));
	memcpy(&evtecla,ev,sizeof(evtecla));
	*evonclick.evento=0;
	strcat(evonclick.evento,"onclick");
	*evtecla.evento=0;
	strcat(evtecla.evento,"onkeyup");
	*evtecla.valor='3';
	strcpy(evtecla.antid,ev->objeto);
	strcpy(evtecla.antvalor,ev->valor);
	v10evencolaevento(&evonclick);
	if (v10evdamebloque(ev) == v10damebloqueactual()) v10evencolaevento(&evtecla);
	return(-1);	
}

static int fctrlcontextual(v10dialogs *v,v10httpeventos *ev)  
{
	v10evdamevalor(v,ev);    	  		
	v10js2ansi(ev->evento,atoi(ev->valor));
	return(CS_F(10));
}

static int fdebugmsg(v10dialogs *v,v10httpeventos *ev)  
{
	if (debugmsg==1) debugmsg=0; 
	else debugmsg=1;
	return(1);
}

static int ffinmsg(v10dialogs *v,v10httpeventos *ev)  
{ 
	debugmsg=-1;
	return(1);
}

static int fphpescape(v10dialogs *v, v10httpeventos *ev)
{
	v10evtecla(esc);
	return(-1);
}

void v10ponhandlers(void)
{
	v10addhandler("selmenu",fselmenu,0);
	v10addhandler("reposiciona",freposiciona,0);
	v10addhandler("onkeyup",fonkeyup,0);
	v10addhandler("onkeyupcola",fonkeyupcola,0);
	v10addhandler("onkeyup_shift",fonkeyup,0);
	v10addhandler("onkeyupcola_shift",fonkeyupcola,0);
	v10addhandler("onkeyup_alt",fonkeyup,0);
	v10addhandler("onkeyupcola_alt",fonkeyupcola,0);
	v10addhandler("onkeyup_ctrl",fonkeyup,0);
    v10addhandler("onkeyupcola_ctrl", fonkeyupcola,0);
    v10addhandler("onclick", fonclick, 0);
    v10addhandler("ondblclick", fondblclick, 0);
    v10addhandler("Salir", fsalir, 0);
    v10addhandler("Reiniciar", freiniciar, 0);
    v10addhandler("EditPan", feditpan, 0);
    v10addhandler("EditFrm", feditfrm, 0);
    v10addhandler("EditMenu", feditmenu, 0);
    v10addhandler("EditTodo", fedittodo, 0);
    v10addhandler("confirma", fconfirma, 0);
    v10addhandler("zoom", fzoom, 0);
    v10addhandler("extonline", fextonline, 0);
    v10addhandler("editwhere", feditwhere, 0);
    v10addhandler("selwhere", fselwhere, 0);
    v10addhandler("delwhere", fdelwhere, 0);
    v10addhandler("poscursor", fposcursor, 0);
    v10addhandler("timeout", ftimeout, 0);
    v10addhandler("abrecombox", fabrecombox, 0);
    v10addhandler("selectcombox", fselectcombox, 0);
    v10addhandler("check", fcheck, 0);
    v10addhandler("ctrlcontextual", fctrlcontextual, 0);
    v10addhandler("ayuda", fayuda, 0);
    v10addhandler("findebug", ffindebug, 0);
    v10addhandler("debugmsg", fdebugmsg, 0);
    v10addhandler("finmsg", ffinmsg, 0);
	v10addhandler("ajax",trataajax,1);
	v10addhandler("phpescape", fphpescape, 1);
}

