/*
* Módulo :  v10wwwpunteros.c
* Objeto:   Asignación de funciones www a punteros a funciones
* 
* 
* Autor	 : Francisco José Guerrero Sánchez
* Fecha  : 25-09-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10wwwform.h"
// estos valores se cargan en cargahtmlform
v10htmlconfigs v10htmlconf={"V10",0,1,1024,768,14,7.1,0,800,600,1,1,1,"colores.css"};
char usuarioactual[100];
double timeoutact;

static void (*funcargahtmlconf)(char *, void *)=NULL;
int (*v10cargadatos)(int nstat, bloques *b,char *nombre, char *v10datoscharts)=NULL;

static char *v10wwwdamehostname(void) {
	return(v10httpconf.hostname);
}

static void cargahtmlconfactual(void) {
	if (funcargahtmlconf) funcargahtmlconf(usuarioactual,(void *)&v10htmlconf);
}

static int dummy0(void *a) {return(0);}
static void dummy1(void *a,int b) {}
static void dummy2(void *a,int b,int c) {}
static void dummy4(void *a) {}
static void dummy5(int a,int b) {}


void v10punterosweb(void (*func)(char *, void *), 
					int (*func2)(int,void *,char *, char *),
					double timeout)
{
	ENTERQ=1;	
	timeoutact = timeout;					// timeout en segundos
	v10log(LOGNORMAL,"Timeout es %lf\n",timeoutact);
	llselecciona								=		dummy0; 
	lpresenta									=		dummy2;
	muestradialog								=		dummy1; 
	actualizadialog								=		dummy4; 
	limpiamensaje								=		dummy4; 
	fgotoxy										=		dummy5;

	funcargahtmlconf							=		func;
	// este puntero carga la configuración del usuario actualmente conectado	
	cargahtmlconf								=		cargahtmlconfactual;
	tecla										=		v10evento; 
	presentamenu								=	(void *)	v10menu2html;
	reposicionaraton							=	(void *)	v10wwwreposicionaraton; 	
	blinput										=	(void *)	v10wwwblinput;	
	pintapaginabloque							=	(void *)	v10wwwpintapaginabloque;
	reposicionadialograton						=	(void *)	v10wwwreposicionadialograton;
	actualizabloque								=	(void *)	v10wwwactualizabloque;	
	finputregistroaux							=	(void *)	v10finputregistroaux;
	commitsino									=	(void *)	v10wwwcommitsino;
	llbloquearegistroaux						=	(void *)	v10llbloquearegistroaux;
	reposicionaregraton							=	(void *)	v10wwwreposicionaregraton;
	reposratonform								=	(void *)	v10wwwreposratonform;
	guardatodosenter							=	(void *)	v10guardatodosenter;
	frecalcpadreaux								=	(void *)	v10frecalcpadreaux;
	encolatecla									=		v10evtecla;
	pushtecla									=		v10evpushtecla;
	fejecutaformaux								=	(void *)	v10wwwfejecutaformaux;
	mensajeform									=	(void *)	v10wwwmensajeform;
	fdesignacionaux								=	(void *)	v10wwwactualizabloque;	
	/* zooms */
	presentamenucontex							=	(void *)	v10wwwmenucontex;	
	/* edición de querys */
	editwhere									=		v10wwwmensajewhere;
	selwhere									=		v10wwwselwhere;
	/* mensajes */
	vmensajefm									=		v10wwwvmensajefm;
	confirmasn									=		v10wwwconfirmasn;
	v10error									=		v10wwwerror;		// en v10wwwaborta (ok)
	ldadebug									=		v10wwwldadebug;		// en v10wwwdebug
	cursordebug									=	(void *)	v10wwwcursordebug;  // en v10wwwdebug
	formerror									=	(void *)	v10wwwformerror;	// en v10formsg, clave duplicada
	forminfo									=	(void *)	v10wwwforminfo;		// en v10formsg, CF9	
	borraregistroaux = (void *) dummy0;
	reinicia									=		v10reiniciaform;
	pabrelink									=		v10wwwabrelink;
	confexcel2fichero(v10httpconf.idsesion,0,v10httpconf.rutaxls, v10wwwmensajexls);
	confpdf2fichero(v10httpconf.idsesion,0,v10httpconf.rutapdf, v10wwwmensajepdf);
	v10cargadatos								= (void *)		func2;
	damehostname								=		v10wwwdamehostname;
    psemueveelraton= semueveelraton;
	v10ponhandlers();
}

