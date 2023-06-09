#include "v10wwwform.h"
#define MAXOPCIONES 30
#define MAXMENUTRIGERS 50

char v10html[MAXCADENAHTML*2]="";
char v10javascript[MAXCADENAHTML*2]="";
char menucontextual[MAXCADENAHTML*2]="";
char v10datoshtml[MAXCADENAHTML]="";
char v10botoneshtml[MAXCADENA]="";
extern double timeoutact;

static int primeralista;
static int micontador=0;

extern v10htmlconfigs v10htmlconf;
static void v10opc2html(menus *m);
static char rutaopcion[MAXPATH];
static int opcionactual=1;

static v10cursors *vdcgetuser;

#define CGETUSER "SELECT NOMBRE, APELLIDO1, APELLIDO2 "\
				 " FROM VDUSUARIO "\
				 " WHERE CODOPE = VDUSER.GETUSER "
				 
static v10cursors *vdcgetuser;				 


/*static */menus *menuactual;
static int dameopcionmenu(menus *m,int *pos,int indice,opmenus **op);

static int dameopcion(opmenus *m, int *pos, int indice, opmenus **op)
{
	int ret;	
	*pos=*pos+1;
	if (indice==*pos) {
		*op=m;	
		return(1);
	}	
	if (m->tipo=='M') {
		ret=dameopcionmenu((menus *)m->param,pos,indice,op);
		if (ret) return(ret);
	}

	return(0);		
}

static int dameopcionmenu(menus *m, int *pos, int indice, opmenus **op)
{
	int i,ret;
	for (i=0;i<m->numop;i++) {
		ret=dameopcion(m->op+i,pos,indice,op);
		if (ret) return(ret);
	}
	return(0);
}

int v10wwwelige(char *opcion)
{
	// pendiente el men� definitivo
	int pos=0;
	opmenus *op=NULL;
	dameopcionmenu(menuactual,&pos,atoi(opcion),&op);
	opcionactual=pos;
	if (op) eligeop(op); 
	return(0); 
}

/*
static void v10helpmenu2html(menus *m,char *sesion)
{
	char miayuda[MAXCADENA]="";
	strcpy(miayuda,m->titulo);	
	v10carespeciales(v10wwwoem2ansi(miayuda),32,"&#160");
	sprintf(v10javascript+strlen(v10javascript),"\nv10lib.v10ayudahtml(\'%s\',\'%s/%s.htm\',%d,%d,%d,%d);",
		sesion,v10httpconf.v10serverhelp,miayuda,v10htmlconf.ayudaposx,v10htmlconf.ayudaposy,v10htmlconf.ayudatamanox,v10htmlconf.ayudatamanoy);
}
*/

static void v10menu2javascript(menus *m)
{
    *v10javascript = 0;
	memset(v10javascript,0,sizeof(v10javascript));
	//sprintf(v10javascript+strlen(v10javascript),"var inodo=tree_defaults.getNode(%d);",opcionactual);
	//v10helpmenu2html(m,v10httpconf.idsesion);
	sprintf(v10javascript+strlen(v10javascript),"%d;",opcionactual);
	
	sprintf(v10javascript+strlen(v10javascript),"v10lib.pontimeout(0,%lf);",timeoutact);
	sprintf(menucontextual,"v10lib.creamenucont(%d);",protegidoform);	
}

static void v10nuevaopc2html(opmenus *m, int numopcion, int esprimera, int esultima)
{
	char tipo=m->tipo;
	if (esprimera) {
		//if (primeralista) strcat(v10html,"\n<ul id=\"tree_defaults\">");	
		if (primeralista) strcat(v10html,"\n<ul id=\"main-menu\" class=\"sm sm-simple\">");	
		else strcat(v10html,"\n<ul>");	
		primeralista=0;
	}
	strcat(v10html,"<li>");	
	if (tipo=='M') {
        sprintf(v10html+strlen(v10html),"<a href=\"#\" id=\"%d\">%s</a>",micontador,m->nombreop);		
		//sprintf(v10html+strlen(v10html),"<label id='%d'>%s</label>",micontador,m->nombreop);		
		//sprintf(v10html+strlen(v10html),"<label id=\"%d\" onclick=\"return enviarevento(this);\">%s</label>",micontador,m->nombreop);		
		v10opc2html((menus *)m->param);			
	} else {	
		sprintf(v10html+strlen(v10html),"<a href=\"#\" id=\"%d\" onclick=\"return enviarevento(this);\">%s</a>",micontador,m->nombreop);			
		//sprintf(v10html+strlen(v10html),"<label id='%d'>%s</label>",micontador,m->nombreop);		
		//sprintf(v10html+strlen(v10html),"<label id=\"%d\" onclick=\"return enviarevento(this);\">%s</label>",micontador,m->nombreop);			
		
	} 	
	strcat(v10html,"</li>\n");
	if (esultima) strcat(v10html,"</ul>");

	// onkeyup en el body,y mandar window.event.srcElement.ruta (es un span) como encolo un onclick en posicion actual
	// onclick en el nodo
}

static void v10opc2html(menus *m) 
{
	int i;
	char *ptr;
	for (i=0;i<m->numop;i++) {
		micontador++;
        sprintf(rutaopcion + strlen(rutaopcion), ".%d", i + 1);
		v10nuevaopc2html(m->op+i,i+1,(i==0),(i==m->numop-1));
		ptr=strrchr(rutaopcion,'.');
		if (ptr) *ptr=0;
	}
}

void v10menu2html(menus *m) 
{
	int ret;
	char miplantilla[MAXPATH]="";
	char nombre[MAXCADENA] = "";
	char apellido1[MAXCADENA]="";
	char apellido2[MAXCADENA]="";
	char minombre[MAXCADENA]="";
	if (v10htmlconf.ventanalogin) v10openbrowserwindow();
	do {
		if (v10htmlenviado) return;
		//memset(v10datoshtml,0,sizeof(v10datoshtml));
        *v10datoshtml = 0;
		//memset(v10html,0,sizeof(v10html)); 
        *v10html = 0;
		menuactual=m;
		memset(rutaopcion,0,sizeof(rutaopcion));
		primeralista=1;
		micontador=0;
		v10opc2html(m);
		v10menu2javascript(m);
		wwwtratamensajespost(v10javascript);
		*miplantilla=0;
		if (*v10httpconf.prefijoplantilla) sprintf(miplantilla,"%s%s",v10httpconf.prefijoplantilla,PLANTILLAMENU);
		else strcat(miplantilla,PLANTILLAMENU);
		v10cargaplantillahtml(NULL,miplantilla,v10datoshtml);
		v10reemplazapatron(v10datoshtml,PATRONTITULO,m->titulo,1);
#ifndef __LINUX__
		ayudamenu(m,v10datoshtml);
#endif
		v10reemplazapatron(v10datoshtml,PATRONOPCIONES,v10html,1);
		v10reemplazapatron(v10datoshtml,PATRONJAVASCRIPTONLOAD ,v10javascript,1);
		v10reemplazapatron(v10datoshtml,PATRONJAVASCRIPTONSCRIPTS,menucontextual,1);
		v10reemplazapatron(v10datoshtml,PATRONIDSESION,v10httpconf.idsesion,1);    
        creavaruser(v10datoshtml);
		
		//funci�n necesaria para mostrar el nombre real del usuario en el men� principal de la aplicaci�n. Pibe.
		//<!--NOMBREREAL--> Inicio
		vdcgetuser=abrecursor(CGETUSER);
	    definetodo(vdcgetuser,
			             nombre,sizeof(nombre),V10CADENA,
			             apellido1,sizeof(apellido1),V10CADENA,
			             apellido2,sizeof(apellido2),V10CADENA,
					     NULL);
		ejefetchcursor(vdcgetuser);
		liberacursor(vdcgetuser);
		sprintf(minombre,"%s %s %s",nombre, apellido1, apellido2);
		v10reemplazapatron(v10datoshtml,PATRONINFOUSERTITULO,minombre,1);	
        //<!--NOMBREREAL--> Fin.
		
		
		strcpy(v10html,v10datoshtml);
		wwwtratamensajesprev(v10datoshtml);
		if ( v10httpconf.AJAXsidebarMENUvisible==2) {	
			//memset(v10datoshtml,0,sizeof(v10datoshtml));
            *v10datoshtml = 0;
			sidebarMenu();
			//memset(v10datoshtml,0,sizeof(v10datoshtml));
            *v10datoshtml = 0;
			AJAXmenu2HTML();
			v10reemplazapatron(v10html,PATRONAJAX,v10datoshtml,1);
		}

		v10httprespuesta(OK,v10formserver,NULL,v10html,NULL,0);
		v10htmlenviado=1;
		ret=v10htmlevento(NULL); // est� en V10ev.c
	} while (ret==0);
}

