#include "v10wwwform.h"

#define PATRONMENSAJES "<!--v10mensaje-->"
#define PATRONTITULOMSJ "<!--V10TITULO-->"
#define MSJPREVIO 1
#define MSJPOSTERIOR 2
#define PATRONOPCSELECT "<!--OPCIONESSELECT-->"
#define PATRONONLINEMSJ "<!--V10ONLINEMSJ-->"

#define PATDEBUGDEFINES "<!--v10defines-->"
#define PATDEBUGBINDS	"<!--v10binds-->"
#define PATDEBUGSELECT	"<!--v10select-->"
#define PATDEBUGCURSOR	"<!--v10oraerror-->"
#define PATRONCLIPBOARD "<!--v10clipboard-->"
extern char textodefines[MAXCADENAHTML];
extern char textobinds[MAXCADENAHTML];
extern char textoselect[MAXCADENAHTML];
extern char textocursor[MAXCADENAHTML];
extern char textoclipboard[MAXCADENAHTML];

#define MAXMENSAJES 100
typedef struct  {
	int tipo;
	char texto[MAXCADENAHTML];
	char online[MAXCADENA];	
	char titulo[MAXPATH];
	char fichero[MAXPATH];
	char id[MAXPATH];
	int redimensiona;
} wwwmensaje;

char *textowhere;
char *textoorder;
char *textohaving;
char *titulowhere;

wwwmensaje wwwmsjprev[MAXMENSAJES],wwwmsjpost[MAXMENSAJES];
static int nbmsjprev=0 ,nbmsjpost =0;

// tipos de mensaje
#define WWWMSGGEN		0
#define WWWMSGSCONFIRMA 1
#define WWWMSGZOOM		2
#define WWWMSGONLINE	3
#define WWWMSGWHERE     4
#define WWWMSGSELWHERE	5
#define WWWMSGINFO		6
#define WWWMSGCAMPOS	7
#define WWWMSGDEBUG		8
#define WWWMSGCURSORES	9
#define WWWMSGXLS		10
#define WWWMSGCOMBOX	11
#define WWWMSGCALENDARIO 12
#define WWWMSGLINK		 13
#define WWWMSGPDF		14


static void v10msjposicion(char *mimensaje,char *texto,char *idventana) 
{
	int longmax=0;
	char *ptr,*inicio;

	inicio=texto;
	while ((ptr=strstr(inicio,"<br />"))!=NULL) {
		if (ptr-inicio>longmax) longmax=(int)(ptr-inicio);
		inicio=ptr+4;
	}
	if (longmax==0) longmax=strlen(texto);

	if (longmax>20) longmax=strlen(texto);

	//anulo esta funcion, porque ya estoy diciendo la posicion del mensaje en el html // 09/04/2014 pibe.
//	if (longmax>20) {
//		strcat(mimensaje,"<script>\n");
//		leftventana-=v10x2pxsm((longmax-10)/2,damepxcol(0));
//		sprintf(mimensaje+strlen(mimensaje),"try { window.document.getElementById(\"%s\").style.left=\"%dpx\"; } catch (e) {};",
//					idventana,leftventana);		
//		strcat(mimensaje,"</script>\n");
//	}
}



// mensaje de aviso genérico
void v10wwwmensajegen(char *titulo,char *cadena) 
{
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGGEN;
	cadena=v10translate(cadena);
	strcpy(wwwmsjprev[nbmsjprev].titulo,titulo);
	strcpy(wwwmsjprev[nbmsjprev].texto,cadena);
	//if (debugmsg==1) // mensaje de V10ERROR
	v10cadespeciales(wwwmsjprev[nbmsjprev].texto,"\n","<br />"); 
	if (formglobal && *v10damebloqueactual()->htmlalert) strcpy(wwwmsjprev[nbmsjprev].fichero,v10damebloqueactual()->htmlalert);
		else strcpy(wwwmsjprev[nbmsjprev].fichero,"msjalert.html");	
	strcpy(wwwmsjprev[nbmsjprev].id,"msgalert");
	wwwmsjprev[nbmsjprev].redimensiona=1;
	nbmsjprev++;
	if (formglobal) {
		v10form2html(formglobal,0);
		v10htmleventodummy(&v10damebloqueactual()->vi);		
	} else {
		v10menu2html(menuactual);
	}
}

// mensaje de aviso con lista de argumentos
void v10wwwvmensajefm(int x,int y,char *cadena,va_list arg) 
{	
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGGEN;
	cadena=v10translate(cadena);
	if (debugmsg==0) strcpy(wwwmsjprev[nbmsjprev].titulo,"AVISO (Alt+F1 Modo debug)");
	else strcpy(wwwmsjprev[nbmsjprev].titulo,"MODO DEBUG AVISO (Alt+F1 Salir)");
	vsprintf(wwwmsjprev[nbmsjprev].texto,cadena,arg);
	//if (debugmsg==1) // mensaje de V10ERROR
	v10cadespeciales(wwwmsjprev[nbmsjprev].texto,"\n","<br />");
	if (formglobal && *v10damebloqueactual()->htmlalert) strcpy(wwwmsjprev[nbmsjprev].fichero,v10damebloqueactual()->htmlalert);
		else strcpy(wwwmsjprev[nbmsjprev].fichero,"msjalert.html");	
	strcpy(wwwmsjprev[nbmsjprev].id,"msgalert");
	wwwmsjprev[nbmsjprev].redimensiona=1;
	nbmsjprev++;
	if (formglobal) {
		v10form2html(formglobal,0);		
		v10htmleventodummy(&v10damebloqueactual()->vi);
	} else {
		v10menu2html(menuactual);
	}
}

// mensaje de confirmación, con 2 botones
int v10wwwconfirmasn(int x,int y,char *cadena) 
{
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGSCONFIRMA;
	cadena=v10translate(cadena);
	strcpy(wwwmsjprev[nbmsjprev].texto,cadena);
	v10cadespeciales(wwwmsjprev[nbmsjprev].texto,"\n","<br />");
	if (formglobal && *v10damebloqueactual()->htmlconfirm) strcpy(wwwmsjprev[nbmsjprev].fichero,v10damebloqueactual()->htmlconfirm);
		else strcpy(wwwmsjprev[nbmsjprev].fichero,"msjconfirma.html");	
	strcpy(wwwmsjprev[nbmsjprev].id,"msgconfirma");
	wwwmsjprev[nbmsjprev].redimensiona=1;
	nbmsjprev++;
	v10form2html(formglobal,0);
	return(v10htmleventodummy(NULL/*&v10damebloqueactual()->vi*/));
}

// mensaje de información en la barra de estados
static void llmensajeform(forms *f,char *cadena,va_list arg) 
{	
    memset(wwwmsjprev + nbmsjprev, 0, sizeof(wwwmensaje));
    if (nbmsjpost < MAXMENSAJES - 1) {
        wwwmsjpost[nbmsjpost].tipo = WWWMSGINFO;
        cadena = v10translate(cadena);
        vsprintf(wwwmsjpost[nbmsjpost].texto, cadena, arg);
        nbmsjpost++;
    }
}

void v10wwwmensajeform(forms *f,char *mensaje,...) {
	va_list arg;
	va_start(arg,mensaje);
	llmensajeform(f,mensaje,arg);
	va_end(arg);
}

// mensaje de zoom
int v10wwwmensajezoom(forms *f,char *titulo,char *cadena) 
{
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGZOOM;
	cadena=v10translate(cadena);
	strcpy(wwwmsjprev[nbmsjprev].titulo,titulo);
	strcpy(wwwmsjprev[nbmsjprev].texto,cadena);
	strcpy(wwwmsjprev[nbmsjprev].fichero,"msjzoom.html");
	strcpy(wwwmsjprev[nbmsjprev].id,"msgzoom");
	nbmsjprev++;
	v10form2html(formglobal,0);
	return(v10htmleventodummy(NULL));
}

// mensaje de información  del form (CF(9))
int v10wwwmensajeforminfo(char *titulo,char *cadena, char *online) 
{
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGGEN;
	cadena=v10translate(cadena);
	strcpy(wwwmsjprev[nbmsjprev].titulo,titulo);
	strcpy(wwwmsjprev[nbmsjprev].texto,cadena);
	strcpy(wwwmsjprev[nbmsjprev].online,online);
	strcpy(wwwmsjprev[nbmsjprev].fichero,"msjforminfo.html");
	strcpy(wwwmsjprev[nbmsjprev].id,"msgforminfo");
	nbmsjprev++;
	v10form2html(formglobal,0);
	return(v10htmleventodummy(NULL));
}

// ayuda online extendida
void v10wwwmensajeonline(char *titulo,char *cadena) 
{
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGONLINE;
	cadena=v10translate(cadena);
	strcpy(wwwmsjprev[nbmsjprev].titulo,titulo);
	strcpy(wwwmsjprev[nbmsjprev].texto,cadena);
	if (formglobal && *v10damebloqueactual()->htmlalert) strcpy(wwwmsjprev[nbmsjprev].fichero,v10damebloqueactual()->htmlalert);
		else strcpy(wwwmsjprev[nbmsjprev].fichero,"msjalert.html");	
	strcpy(wwwmsjprev[nbmsjprev].id,"msgalert");
	wwwmsjprev[nbmsjprev].redimensiona=1;
	nbmsjprev++;
	v10form2html(formglobal,0);
	v10htmleventodummy(NULL);
}

// edición de consultas (CF(4))
int v10wwwmensajewhere(char *ptextowhere,char *ptextoorder,char *ptextohaving,char *ptitulowhere) 
{
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGWHERE;  
	strcpy(wwwmsjprev[nbmsjprev].titulo,"Edición de consultas");  
	textowhere=ptextowhere;
	textoorder=ptextoorder;
	textohaving=ptextohaving;
	titulowhere=ptitulowhere;
	strcpy(wwwmsjprev[nbmsjprev].fichero,"msjwhere.html");
	strcpy(wwwmsjprev[nbmsjprev].id,"msgwhere");
	nbmsjprev++;
	v10form2html(formglobal,0);
	return(v10htmleventodummy(NULL));
}

// selección de consultas grabafas (CF(5))
int v10wwwmensajeselwhere(char *titulo,char *cadena) 
{
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGSELWHERE;
	cadena=v10translate(cadena);
	strcpy(wwwmsjprev[nbmsjprev].titulo,titulo);
	strcpy(wwwmsjprev[nbmsjprev].texto,cadena);
	strcpy(wwwmsjprev[nbmsjprev].fichero,"msjselwhere.html");
	strcpy(wwwmsjprev[nbmsjprev].id,"msgselwhere");
	nbmsjprev++;
	v10form2html(formglobal,0);
	return(v10htmleventodummy(NULL));
}

// muestra campos de la pantalla
void v10wwwmensajecampos(char *titulo,char *cadena) 
{
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGCAMPOS;
	//cadena=v10translate(cadena);
	strcpy(wwwmsjprev[nbmsjprev].titulo,titulo);
	strcpy(wwwmsjprev[nbmsjprev].texto,cadena);
	strcpy(wwwmsjprev[nbmsjprev].fichero,"msjcampos.html");
	strcpy(wwwmsjprev[nbmsjprev].id,"msgcampos");
	nbmsjprev++;
	v10form2html(formglobal,0);
	v10htmleventodummy(NULL);
}

int v10wwwmensajedebug(char *cadena,char *online) 
{
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGDEBUG;
	cadena=v10translate(cadena);
	strcpy(wwwmsjprev[nbmsjprev].texto,cadena);
	strcpy(wwwmsjprev[nbmsjprev].online,online);
	strcpy(wwwmsjprev[nbmsjprev].fichero,"msjdebug.html");
	strcpy(wwwmsjprev[nbmsjprev].id,"msgdebug");
	nbmsjprev++;
	v10form2html(formglobal,0);
	return(v10htmleventodummy(NULL));
}

int v10wwwmensajecursores(char *cadena) 
{
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGCURSORES;
	cadena=v10translate(cadena);
	strcpy(wwwmsjprev[nbmsjprev].texto,cadena);
	strcpy(wwwmsjprev[nbmsjprev].titulo,"Edición de Cursores");
	strcpy(wwwmsjprev[nbmsjprev].fichero,"msjcursores.html");
	strcpy(wwwmsjprev[nbmsjprev].id,"msgcursores");
	nbmsjprev++;
	v10form2html(formglobal,0);
	return(v10htmleventodummy(NULL));
}

void v10wwwmensajexls(char *fichero) 
{
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGXLS;
	strcpy(wwwmsjprev[nbmsjprev].texto,fichero);
	nbmsjprev++;
	
}

void v10wwwmensajepdf(char *fichero) 
{
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGPDF;
	strcpy(wwwmsjprev[nbmsjprev].texto,fichero);
	nbmsjprev++;
	
}

void v10wwwmensajecombox(char *texto,int multiple) 
{
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGCOMBOX;
	if (multiple) strcpy(wwwmsjprev[nbmsjprev].fichero,"msjcomboxmul.html");
	else strcpy(wwwmsjprev[nbmsjprev].fichero,"msjcombox.html");
	strcpy(wwwmsjprev[nbmsjprev].texto,texto);
	nbmsjprev++;	
}

void v10wwwmensajecalendario(char *texto) 
{
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGCALENDARIO;
	strcpy(wwwmsjprev[nbmsjprev].fichero,"msjcalendario.html");
	strcpy(wwwmsjprev[nbmsjprev].texto,texto);
	nbmsjprev++;	
}

void v10wwwmensajeabrelink(char *link) 
{
	memset(wwwmsjprev+nbmsjprev,0,sizeof(wwwmensaje));
	wwwmsjprev[nbmsjprev].tipo=WWWMSGLINK;
	strcpy(wwwmsjprev[nbmsjprev].texto,link);
	nbmsjprev++;
}

/*************************************
  TRATAMIENTO DE LOS MENSAJES AL GENERAR EL CÓDIGO HTML 
****************************************/

// mensajes en general, con un solo botón
static void tratamensajegen(char *cadena,wwwmensaje *msj) 
{
	char *ptrini,*ptrfinal,mimensaje[MAXCADENAHTML]="",midatosfichero[MAXCADENAHTML]="",textoinclude[MAXCADENAHTML];	
	ventanamodal=1;
	leefichero(msj->fichero,midatosfichero);
    *textoinclude = 0;
	ptrini=strstr(midatosfichero,INCLUDEDATA);
	ptrfinal=strstr(midatosfichero,ENDINCLUDEDATA);
	if (ptrini && ptrini) strcopia(textoinclude,ptrini+strlen(INCLUDEDATA),(ptrfinal-(ptrini+strlen(ENDINCLUDEDATA)))+2);
	strcat(mimensaje,textoinclude);
	v10ansitohtml(msj->texto);
	while (strstr(msj->texto,"\\n")) v10reemplazapatron(msj->texto,"\\n","<br />",1);		
	v10reemplazapatron(mimensaje,PATRONTEXTOMENSAJE,msj->texto,1);	
	v10reemplazapatron(mimensaje,PATRONTITULOMSJ,msj->titulo,1);
	if (*msj->online)   v10reemplazapatron(mimensaje,PATRONONLINEMSJ,msj->online,1);
	if (msj->redimensiona) v10msjposicion(mimensaje,msj->texto,msj->id);
	v10reemplazapatron(v10html,PATRONMENSAJE,mimensaje,1);
}

static void tratamensajecalendario(char *cadena,wwwmensaje *msj) 
{
	char *ptrini,*ptrfinal,mimensaje[MAXCADENAHTML]="",midatosfichero[MAXCADENAHTML]="",textoinclude[MAXCADENAHTML];	
	leefichero(msj->fichero,midatosfichero);
	ventanamodal=2;
    *textoinclude = 0;
	ptrini=strstr(midatosfichero,INCLUDEDATA);
	ptrfinal=strstr(midatosfichero,ENDINCLUDEDATA);
	if (ptrini && ptrini) strcopia(textoinclude,ptrini+strlen(INCLUDEDATA),(ptrfinal-(ptrini+strlen(ENDINCLUDEDATA)))+2);
	strcat(mimensaje,textoinclude);
	v10ansitohtml(msj->texto);
	while (strstr(msj->texto,"\\n")) v10reemplazapatron(msj->texto,"\\n","<br />",1);		
	v10reemplazapatron(mimensaje,PATRONTEXTOMENSAJE,msj->texto,1);	
	v10reemplazapatron(v10html,PATRONCALENDARIO,mimensaje,1);
}

static void tratamensajecombox(char *cadena,wwwmensaje *msj) 
{
	char *ptrini,*ptrfinal,mimensaje[MAXCADENAHTML]="",midatosfichero[MAXCADENAHTML]="",textoinclude[MAXCADENAHTML];	
	leefichero(msj->fichero,midatosfichero);
	ventanamodal=2;
    *textoinclude = 0;
	ptrini=strstr(midatosfichero,INCLUDEDATA);
	ptrfinal=strstr(midatosfichero,ENDINCLUDEDATA);
	if (ptrini && ptrini) strcopia(textoinclude,ptrini+strlen(INCLUDEDATA),(ptrfinal-(ptrini+strlen(ENDINCLUDEDATA)))+2);
	strcat(mimensaje,textoinclude);
	v10log(LOGNORMAL, "%s", "Empiezo Ansitohtml\n");
	v10ansitohtml(msj->texto);
	v10log(LOGNORMAL, "%s", "Termino Ansitohtml\n");
	while (strstr(msj->texto,"\\n")) v10reemplazapatron(msj->texto,"\\n","<br />",1);		
	v10reemplazapatron(mimensaje,PATRONTEXTOMENSAJE,msj->texto,1);	
	v10reemplazapatron(v10html,PATRONMENSAJE,mimensaje,1);
}
// mensaje de información en la barra de estados del navegador
static void tratamensajeform(char *cadena,wwwmensaje *msj) 
{
	if (formglobal){
		v10reemplazapatron(v10html,"<!--v10mensajeinfo-->",msj->texto,1);
		strcat(v10datoshtml,"window.document.getElementById('msginfo').style.visibility='visible';\n");
		strcat(v10datoshtml,"setTimeout(\"window.document.getElementById('msginfo').style.visibility='hidden'\",3000);\n");
	}

}

// edición de query actual, mensaje especial
static void tratamensajewhere(char *cadena,wwwmensaje *msj) 
{
	int i;
	char *ptrini,*ptrfinal,mimensaje[MAXCADENAHTML]="",midatosfichero[MAXCADENAHTML]="",textoinclude[MAXCADENAHTML];	
	char listaopciones[MAXCADENA]="";
	bloques *b;
	ventanamodal=1;
	leefichero(msj->fichero,midatosfichero);
    *textoinclude = 0;
	ptrini=strstr(midatosfichero,INCLUDEDATA);
	ptrfinal=strstr(midatosfichero,ENDINCLUDEDATA);
	if (ptrini && ptrini) strcopia(textoinclude,ptrini+strlen(INCLUDEDATA),(ptrfinal-(ptrini+strlen(ENDINCLUDEDATA)))+2);	
	strcat(mimensaje,textoinclude);
	v10ansitohtml(msj->texto);
	v10ansitohtml(textowhere);
	v10carespeciales(textowhere,'\n',"\\n");
	v10carespeciales(textowhere,'\r',"\\r");
	v10ansitohtml(textoorder);
	v10carespeciales(textoorder,'\n',"\\n");
	v10carespeciales(textoorder,'\r',"\\r");
	v10ansitohtml(textohaving);
	v10carespeciales(textohaving,'\n',"\\n");
	v10carespeciales(textohaving,'\r',"\\r");
	v10ansitohtml(titulowhere);
	v10carespeciales(titulowhere,'\n',"\\n");
	v10carespeciales(titulowhere,'\r',"\\r");
	while (strstr(msj->texto,"\\n")) v10reemplazapatron(msj->texto,"\\n","<br />",1);		
	sprintf(mimensaje+strlen(mimensaje),"<script>window.document.getElementById(\"where\").value=\"%s\"; "\
		                       "window.document.getElementById(\"order\").value=\"%s\"; "\
		                       "window.document.getElementById(\"having\").value=\"%s\"; "\
							   "window.document.getElementById(\"titulowhere\").value=\"%s\";</script>",
						textowhere,textoorder,textohaving,titulowhere);
	
	b=v10damebloqueactual();
	for (i=0;i<b->ncamp;i++) {		
		sprintf(listaopciones+strlen(listaopciones),"<option %s>%s</option>",(i==0)?"selected=\"true\"":"",b->c[i].nombre);
	}	
	v10reemplazapatron(mimensaje,PATRONOPCSELECT,listaopciones,1);
	v10reemplazapatron(v10html,PATRONMENSAJE,mimensaje,1);
}

// edición de query actual, mensaje especial
static void tratamensajedebug(char *cadena,wwwmensaje *msj) 
{
	char *ptrini,*ptrfinal,mimensaje[MAXCADENAHTML]="",midatosfichero[MAXCADENAHTML]="",textoinclude[MAXCADENAHTML];	
	
	ventanamodal=1;
	leefichero(msj->fichero,midatosfichero);
    *textoinclude = 0;
	ptrini=strstr(midatosfichero,INCLUDEDATA);
	ptrfinal=strstr(midatosfichero,ENDINCLUDEDATA);
	if (ptrini && ptrini) strcopia(textoinclude,ptrini+strlen(INCLUDEDATA),(ptrfinal-(ptrini+strlen(ENDINCLUDEDATA)))+2);	
	strcat(mimensaje,textoinclude);
	
	if (*textodefines) v10reemplazapatron(mimensaje,PATDEBUGDEFINES,textodefines,1);
	if (*textobinds) v10reemplazapatron(mimensaje,PATDEBUGBINDS,textobinds,1);
	v10reemplazapatron(mimensaje,PATRONCLIPBOARD,textoclipboard,1);
	v10reemplazapatron(mimensaje,PATDEBUGSELECT,textoselect,1);
	v10reemplazapatron(mimensaje,PATDEBUGCURSOR,textocursor,1);
	v10reemplazapatron(v10html,PATRONMENSAJE,mimensaje,1);
}


// abre ventana que abre fichero xls 
static void tratamensajexls(char *cadena,wwwmensaje *msj) 
{
	char mimensaje[MAXCADENAHTML]="",name[MAXPATH];
	static int secuen;
	sprintf(name,"Excel%d",secuen++);	
	sprintf(mimensaje,"<script>window.open('%s%s','%s','status=0,toolbar=0,location=0,menubar=0,directories=0,scrollbars=1');</script>",v10httpconf.v10serverxls,msj->texto,name);	
	v10reemplazapatron(v10html,PATRONMENSAJE,mimensaje,0);
}

// abre ventana que abre fichero pdf 
static void tratamensajepdf(char *cadena,wwwmensaje *msj) 
{
	char mimensaje[MAXCADENAHTML]="",name[MAXPATH];
	static int secuen;
	sprintf(name,"Acrobat%d",secuen++);	
	sprintf(mimensaje,"<script>window.open('%s%s','%s','status=0,toolbar=0,titlebar=1,location=0,resizable=1,menubar=0,directories=0,scrollbars=1');</script>\n",v10httpconf.v10serverpdf,msj->texto,name);	
	v10reemplazapatron(v10html,PATRONMENSAJE,mimensaje,0);
}

// abre ventana que abre fichero link
static void tratamensajelink(char *cadena,wwwmensaje *msj) 
{
	char mimensaje[MAXCADENAHTML]="";	
	/*,'status=0,toolbar=0,location=0,menubar=0,directories=0,scrollbars=1'*/
	sprintf(mimensaje,"<script>window.open('%s','V10Link');</script>",msj->texto);		
	v10reemplazapatron(v10html,PATRONMENSAJE,mimensaje,0);
}

int haymensajesprev(void) 
{
	return(nbmsjprev);
}

int haymensajespost(void) 
{
	return(nbmsjpost);
}

void wwwtratamensajesprev(char *cadena) 
{
	int i;
	while (nbmsjprev) {
		wwwmensaje ptrmsg=*wwwmsjprev;
		for (i=1;i<nbmsjprev;i++) {
			wwwmsjprev[i-1]=wwwmsjprev[i];
		}
		nbmsjprev--;
		switch (ptrmsg.tipo) {			
			case WWWMSGGEN:			// mensaje de aviso, solo con la opción de ok
			case WWWMSGZOOM:		// mensaje de zoom
			case WWWMSGONLINE:		// ayuda online extendida
			case WWWMSGSCONFIRMA:	// mensaje de confirmación, con las opciones SI y NO
			case WWWMSGSELWHERE:	// selección de consulta guardada		
			case WWWMSGCAMPOS:      // mensaje que muestra campos de la pantalla
			case WWWMSGCURSORES:    // mensaje de consulta de cursores			
				tratamensajegen(cadena,&ptrmsg);
				return;
			case WWWMSGCOMBOX:		// mensaje de selección de lista desplegable
				tratamensajecombox(cadena,&ptrmsg);
				return;
			case WWWMSGCALENDARIO:		
				tratamensajecalendario(cadena,&ptrmsg);
				return;
			case WWWMSGWHERE: 
				tratamensajewhere(cadena,&ptrmsg);
				return;			
			case WWWMSGDEBUG: 
				tratamensajedebug(cadena,&ptrmsg);
				return;		
			case WWWMSGXLS:
				tratamensajexls(cadena,&ptrmsg);
				break;		
			case WWWMSGPDF:
				tratamensajepdf(cadena,&ptrmsg);
				break;
				//return;		
			case WWWMSGLINK:
				tratamensajelink(cadena,&ptrmsg);
				return;		
		}
	}
}

void wwwtratamensajespost(char *cadena) 
{
	int i;
	for (i=0;i<nbmsjpost;i++) {
		switch (wwwmsjpost[i].tipo) {			
			case WWWMSGINFO:  tratamensajeform(cadena,wwwmsjpost+i);
							  nbmsjpost--;
							  return;
		}
	}
	nbmsjpost=0;	
}