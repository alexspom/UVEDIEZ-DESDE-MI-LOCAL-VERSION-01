#include "v10wwwform.h"

static char v10plantilla[MAXPATH]="";
int filaactiva;  // fila activa en el bloque actual al enviar la página, desde vi->clin, empieza en 1
int colactiva;   // columna o número de campo activo en el bloque actual al enviar la página, empezando por el 1
int ventanamodal=0;
int v10htmlenviado=0;
int v10htmlencurso=0;
char idanterior[100]; // id del elemento activo al enviar la página, puede no tener foco si es noenter
int debug=0;

static void cargaincludehtml(bloques *b, char *v10html) 
{
	char data1 [MAXCADENAHTML]="",data2[MAXCADENAHTML]="",data[MAXCADENAHTML*2]="";
	char nomfichero[MAXPATH]="";	
	if (*b->form->includeficherohtml) {
		strcpy(nomfichero,b->form->includeficherohtml);
		if (leeficheropath(nomfichero,data1)>0) strcat(data, data1);
	}
	if (*b->form->includehtml) {
		*data2=0;
		strcpy(data2,b->form->includehtml);
		strcat(data, "\n");
		strcat(data, data2); 
	}
	if (*b->includeficherohtml) {
		strcpy(nomfichero,b->includeficherohtml);
		if (leeficheropath(nomfichero,data2)>0) {
			 strcat(data, "\n");
			 strcat(data, data2);
		}
	}
	if (*b->includehtml) {
		*data2=0;
		strcpy(data2,b->includehtml);
		strcat(data, "\n");
		strcat(data, data2); 
	}
	if (strlen(data)>0) v10reemplazapatron(v10html,PATRONINCLUDEHTML,data,1);
}

static void cargaincludecss(bloques *b, char *v10html) 
{
	char cadena [MAXCADENA]="";
	char nomfichero[MAXPATH]="";
	char textocss[MAXPATH]="";
	if (*b->form->includeficherocss) {
		strcpy(nomfichero,b->form->includeficherocss);
		sprintf(cadena+strlen(cadena),"<link rel=\"stylesheet\"type=\"text/css\" href=\"../html/%s\"/>\n",nomfichero);
	}
	if (*b->includeficherocss) {
		strcpy(nomfichero,b->includeficherocss);
		sprintf(cadena+strlen(cadena),"<link rel=\"stylesheet\"type=\"text/css\" href=\"../html/%s\"/>\n",nomfichero);
	}
	if (*b->includecss || *b->form->includecss) {
		strcat(cadena,"<style>");
		if (*b->form->includecss) {
			strcpy(textocss,b->form->includecss);
			v10cadespeciales(textocss,"\\n","\n");	
			sprintf(cadena+strlen(cadena),"%s\n",textocss);
		}		
		if (*b->includecss) {
			strcpy(textocss,b->includecss);
			v10cadespeciales(textocss,"\\n","\n");	
			sprintf(cadena+strlen(cadena),"%s\n",textocss);
		}
		strcat(cadena,"</style>");
	}
	v10reemplazapatron(v10html,PATRONINCLUDECSS,cadena,1);
}

void v10form2javascript(forms *f,int timeout) 
{
	v10jsteclas(f); 
	v10jsonload(f,timeout);
} 

void v10bloquei2valores(int nbloque,bloques *b) 
{
	int i=0;
	char mascara[MAXCADENA]="";
	sprintf(mascara,"<!-- %s.PAN con valores cargados-->",b->nombre);
	if (strstr(v10html,mascara)) return;
	initvbloque(b);
	while (limitvbloque(b,i)==0) {	
		if (!damevbloquei(b,i++)) return;
		v10mascarav2html(nbloque,i,b);
	}
	finvbloque(b);
}


void v10form2valores(forms *f) 
{
	int i;
	for (i=0;i<f->nbloques;i++) {
		if (f->b[i]->wtemplegado==0) v10bloquei2valores(i,f->b[i]);
}
}


void v10form2htmlestatico(forms *f) 
{
	int ncampo;
	int ncampo1;
	bloques *b;
	sprintf(v10plantilla,"plantilla.%s.frm.html",f->nombre);
    *v10botoneshtml = 0;	
    *v10html = 0;
	if (*v10httpconf.prefijoplantilla) { // se ha informado un prefijo de plantilla
		sprintf(v10plantilla,"%splantilla.%s.frm.html",v10httpconf.prefijoplantilla,f->nombre);
		if (leefichero(v10plantilla,v10html)>0) { // mira si existe la plantilla del FRM, si existe ... 
			v10log(LOGNORMAL,"Cargada plantilla %s\n",v10plantilla);
			v10incluyebloques(f); // sustituye los include de plantillas de bloques, por estos			
			return;	
		}
	}
	sprintf(v10plantilla,"plantilla.%s.frm.html",f->nombre);
	if (leefichero(v10plantilla,v10html)>0) { // mira si existe la plantilla del FRM, si existe ... 
		v10log(LOGNORMAL,"Cargada plantilla %s\n",v10plantilla);
		v10incluyebloques(f); // sustituye los include de plantillas de bloques, por estos			
		return;	
	}				
    *v10datoshtml = 0;
	sprintf(v10plantilla,"%s%s",v10httpconf.prefijoplantilla,PLANTILLAFRM);
	if (leefichero(v10plantilla,v10html)==0) {
		if (leefichero(PLANTILLAFRM,v10html)==0) return; // no existe la plantilla por defecto	
	}	
	v10bloques2html(f,SINPLANTILLA);	
	//v10log(LOGNORMAL,"Paso 0.9\n");
	b = f->b[f->act];
	ncampo=damecampo(b,"V10HTML");
	ncampo1=damecampo(b,"V10HTML1");
	if (ncampo>-1) {
		char destino[MAXCADENAHTML]="";
		strcopia(destino,direccampo(b,ncampo),b->c[ncampo].lon);		
		if (strlen(destino)>0)	v10reemplazapatron(v10html,"<!--CAMPOV10HTML-->",destino,1);
	}	
	if (ncampo1>-1) {
		char destino[MAXCADENAHTML]="";
		strcopia(destino,direccampo(b,ncampo1),b->c[ncampo1].lon);		
		if (strlen(destino)>0)	v10reemplazapatron(v10html,"<!--CAMPOV10HTML1-->",destino,1);
	}
#ifndef __LINUX__
	ayudaform(f,v10html);
#endif
	v10reemplazapatron(v10html,PATRONDATOS,v10datoshtml,1);
	v10reemplazapatron(v10html,PATRONBOTONES,v10botoneshtml,1);  		
}


void v10form2plantillahtml(forms *f,char *ruta) 
{
	FILE *fout;
	char destino[MAXPATH]="",*ptr=NULL;
	formglobal=f;
	ptr=strchr(f->nombre,'.');
	if (ptr) *ptr=0;
	sprintf(v10plantilla,"plantilla.%s.frm.html",f->nombre);
	v10log(LOGNORMAL,"Generando plantilla para form %s en ruta %s\n",f->nombre,ruta);
	sprintf(destino,"%s\\%s",ruta,v10plantilla);
	fout=fopenpath(destino,"r");
	if (fout) {
		v10log(LOGERROR,"No se puede machacar plantilla de form %s al existir\n",f->nombre);
		fclose(fout);
		return;
	}
    *v10datoshtml = 0;
	if (leeficheropath(PLANTILLAFRM,v10html)==0) {
		final(("No se puede abrir plantilla base %s",PLANTILLAFRM));
		return; // no existe la plantilla por defecto
	}
	v10bloques2html(f,ENPLANTILLAFRM);
	v10reemplazapatron(v10html,PATRONDATOS,v10datoshtml,1);
	fout=fopen(destino,"w");
	if (!fout) final(("No se puede abrir fichero %s",destino));
	fprintf(fout,"%s",v10html);
	fclose(fout);
	v10log(LOGNORMAL,"Generada con éxito plantilla para form %s en fichero %s\n",f->nombre,destino);
}

void (*dameusuario)(char *donde)=NULL;
void creavaruser(char *v10html)
{
    char usuario[MAXCADENA];
    char usuariov10[MAXCADENA] = "SINUSU";
    char destino[MAXCADENA];
    strcpy(usuario, ORAUSR);
    if (!es_blanco(ORADB)) {
        strcat(usuario, "@");
        strcat(usuario, ORADB);
    }
    if (dameusuario) dameusuario(usuariov10);
	sprintf(destino, "<script languaje=""javascript"">var userdb='%s';var userv10='%s';var host='%s';var pidform=%ld;</script>", usuario, usuariov10, v10httpconf.hostname,getpid());
    v10reemplazapatron(v10html, PATRONUSER, destino, 1);
}

void v10form2html(forms *f,int timeout) 
{
	//char *ptr;
	v10horas inienvio=damecent();
	v10log(LOGNORMAL, "%s", "Inicio envío\n");
	if (v10htmlenviado) return;	
	ventanamodal=0;
	v10htmlencurso++;
    *v10html = 0;
	v10form2htmlestatico(f); // html estático (o carga plantilla FRM)
	wwwtratamensajesprev(v10datoshtml);
	v10form2valores(f);      // valores de Oracle a los campos 
	//v10log(LOGNORMAL,"Paso 2\n");
	v10cargabotoneradef();	
	v10cargatecladovirtual();
    *v10datoshtml = 0;
	v10form2javascript(f,timeout);   // javascript a insertar 
	//v10log(LOGNORMAL,"Paso 3\n");
    *v10datoshtml = 0;
	v10online2html(v10damebloqueactual(),v10datoshtml,0); // ayuda online en javascript
	//v10log(LOGNORMAL,"Paso 4\n");
	v10reemplazapatron(v10html,PATRONJAVASCRIPTONLINE,v10datoshtml,1);
	//v10log(LOGNORMAL,"Paso 5\n");	
	v10reemplazapatron(v10html,PATRONIDSESION,v10httpconf.idsesion,1);
    creavaruser(v10html);
	//v10log(LOGNORMAL,"Paso 6\n");
	if (*v10damebloqueactual()->includehtml || *v10damebloqueactual()->includeficherohtml || *f->includehtml || *f->includeficherohtml ) 
		cargaincludehtml(v10damebloqueactual(),v10html);
	if (*v10damebloqueactual()->includecss || *f->includecss || *v10damebloqueactual()->includeficherocss || *f->includeficherocss) 
		cargaincludecss(v10damebloqueactual(),v10html);		
	v10statsform(f);
	if (v10htmlencurso<=1) {
		if (v10damebloqueactual()->sidebaroculto!=1 && (v10httpconf.AJAXsidebarFRMvisible==2  || v10damebloqueactual()->sidebaroculto==2)) {
			*v10datoshtml = 0;
			sidebarForm();		
		}	
        *v10datoshtml = 0;
		AJAXform2HTML(v10damebloqueactual());
		v10reemplazapatron(v10html,PATRONAJAX,v10datoshtml,1);
	}
	v10log(LOGNORMAL, "Html calculado. Tiempo de envío %lf segundos\n", (damecent() - inienvio) / 100);
	if (v10htmlenviado) return;
	v10httprespuesta(OK,v10formserver,NULL,v10html,NULL,0); 
	v10htmlenviado=1;
	v10log(LOGNORMAL,"Html enviado. Tiempo de envío %lf segundos\n",(damecent()-inienvio)/100);
}