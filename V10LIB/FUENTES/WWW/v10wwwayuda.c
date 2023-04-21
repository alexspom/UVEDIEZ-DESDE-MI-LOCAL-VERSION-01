#include "v10wwwform.h"

int muestraayuda=0;
static char topicayuda[MAXPATH];


void ayudaform(forms *f, char *v10html) 
{
	char micadena[MAXCADENA]="";
	if (muestraayuda) {		
		if (v10damebloqueactual()->ayuda && *v10damebloqueactual()->ayuda) {			
			sprintf(topicayuda,"%s/%s.htm",v10httpconf.rutahelp,v10damebloqueactual()->ayuda);
			v10carespeciales(topicayuda,' ',"_");
		} else sprintf(topicayuda,"%s/%s",v10httpconf.rutahelp,"Bienvenido_a_V10.htm");
		sprintf(micadena,"<script>open('/html/ayuda.html','v10ayuda','toolbar=no,location=no,directories=no,status=no,menubar=no,scrollbars=yes,resizable=no,width=1024,height=700px,left=1px,top=1px,alwaysRaised=no');</script>");
		v10reemplazapatron(v10html,PATRONHELP,micadena,1);
		muestraayuda=0;
	}
}


void ayudamenu(menus *m, char *v10html) 
{
    char micadena[MAXCADENA]="";
	if (muestraayuda) {
		if (*m->titulo) {			
			sprintf(topicayuda,"%s/%s.htm",v10httpconf.rutahelp,m->titulo);			
			v10carespeciales(topicayuda,' ',"_");
		} else sprintf(topicayuda,"%s/%s",v10httpconf.rutahelp,"Bienvenido_a_V10.htm");
		sprintf(micadena,"<script>open('/html/ayuda.html','v10ayuda','toolbar=no,location=no,directories=no,status=no,menubar=no,scrollbars=yes,resizable=no,width=1024,height=700px,left=1px,top=1px,alwaysRaised=no');</script>",v10httpconf.v10serverhtml);
		v10reemplazapatron(v10html,PATRONHELP,micadena,1);
		muestraayuda=0;
	}
}

static void dametextoayudaincluye(char *texto, char *patronini, char *patronfinal, char *textoinclude) 
{
	char *ptrini,*ptrfinal;
    *textoinclude = 0;
	ptrini=strstr(texto,patronini);
	ptrfinal=strstr(texto,patronfinal);
	if (ptrini && ptrini) strcopia(textoinclude,ptrini+strlen(patronini),ptrfinal-(ptrini+strlen(patronfinal))+1);
	else return;	
	
}

void capturatopicayuda(char *fichero) 
{
	char *ptr;
	ptr=strchr(fichero,'&');
	if (ptr) {
		sprintf(topicayuda,"%s/%s",v10httpconf.rutahelp,ptr+1);
		*ptr=0;
	}
}
void v10contenidoayuda(int comando,v10sockssls *v10server,char *fichero) 
{
	char datos[MAXCADENAHTML]="";
	char textoayuda[MAXCADENAHTML]="",textoaincluir[MAXCADENAHTML]="";
	leeficheropath(trim(fichero),datos);
	leeficheropath(topicayuda,textoayuda);
	if (*textoayuda==0) {
		sprintf(topicayuda,"%s/%s",v10httpconf.rutahelp,"Bienvenido_a_V10.htm");
		leeficheropath(topicayuda,textoayuda);
	}
	dametextoayudaincluye(textoayuda,"<BODY>","</BODY>",textoaincluir);
	v10reemplazapatron(datos,"<!--V10TEXTOAYUDA-->",textoaincluir,1);
	v10httprespuesta(comando,v10server,NULL,datos,NULL,0);	
}

void v10indiceayuda(int comando,v10sockssls *v10server,char *fichero) {
	char datos[MAXCADENAHTML]="";	
    HANDLE handle; 	
	char nombre[MAXPATH],nombremostrado[MAXPATH]="",miref[MAXPATH]="",*ptr; 
	WIN32_FIND_DATA finddata;	
	char opciones[MAXCADENAHTML]="";
	char filtro[MAXPATH]="";
	
	ptr=strchr(fichero,'&');
	if (ptr) {
		strcpy(filtro,ptr+1);
		*ptr=0;
	}
	sprintf(nombre,"%s/*%s*.htm",v10httpconf.rutahelp,filtro);
	handle=FindFirstFileEx(nombre,FindExInfoStandard,&finddata,FindExSearchLimitToDirectories,NULL,0);
	while (handle && handle!= INVALID_HANDLE_VALUE) {		
		if (*finddata.cFileName!='.') {
			strcpy(nombremostrado,finddata.cFileName);
			strcpy(miref,finddata.cFileName);			
			v10carespeciales(nombremostrado,'_'," ");			
			v10ansitohtml(nombremostrado);			
			v10ansitohtml(miref);
			ptr=strstr(nombremostrado,".htm");
			if (ptr) *ptr=0;						
			sprintf(opciones+strlen(opciones),"<option miref='./ayuda.html&%s'>%s</option>",miref,nombremostrado);
		}		
		if (FindNextFile(handle,&finddata)==0) break;
	}
	FindClose(handle);
	*filtro=0;
	leeficheropath(trim(fichero),datos);
	v10reemplazapatron(datos,"<!--V10TOPICS-->",opciones,1);
	v10httprespuesta(comando,v10server,NULL,datos,NULL,0);	
//	v10httprespuesta(comando,v10server,NULL,datos); PIBE	
}