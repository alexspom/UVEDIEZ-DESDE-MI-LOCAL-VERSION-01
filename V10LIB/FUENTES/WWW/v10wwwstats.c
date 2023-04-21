#include "v10wwwform.h"

#define REFCHARTS "<script type=\"text/javascript\" src=\"../html/EJSChart.js\"></script><link rel=\"stylesheet\"type=\"text/css\" href=\"../html/EJSChart.css\"/>"
#define DELAYCHARTS "<meta http-equiv=\"Page-Enter\" content=\"revealTrans(Duration=0.1,Transition=1)\">"

// patrones dentro de la plantilla del FRM
#define PATRONDELAYCHARTS   "<!--V10DELAYCHARTS-->"
#define PATRONREFCHARTS "<!--V10REFCHARTS-->"
#define PATRONCHARTS    "<!--V10CHARTS-->"

// patrones en el fichero jscharts.html
#define PATRONCHARTDIVS		"<!--V10CHARTDIVS-->"
#define PATRONEJSCCHARTS    "/*V10EJSCCHARTS*/"

extern int (*v10cargadatos)(int nstat,bloques *b,char *nombre, char *v10datoscharts);
// tengo que recoger la configuración de gráfica, eje y series de las tablas	
	// generar los arrays de datos, a partir de los datos de los bloques,
	// y generar las cadenas que sustituiré por los patrones

void v10statsform(forms  *f) {
	int i,j,nbstatsform=0;
	static int statsencurso=0;
	char v10inccharts[MAXCADENA*10]="";
	char v10datosdiv[MAXCADENAHTML]="";
	char v10datoscharts[MAXCADENAHTML]="";
	char v10filejscharts[MAXPATH]="";
	fstats *mistat;

	bloques *b;

	if (statsencurso) { 
		statsencurso=0;
		return;
	}
	statsencurso=1;

	for (i=0;i<f->nbloques;i++) {
		b=f->b[i];
		for (j=0;j<f->b[i]->nbstats;j++) {		
			mistat=b->stats+j;
			nbstatsform++;
			if (*v10inccharts==0) {
			  sprintf(v10filejscharts,"jscharts.html");
			  if (leefichero(v10filejscharts,v10inccharts)<=0) {
				 mensajeform(b,"No se encuentra fichero jscharts.html para gráfica %s\n",b->stats[j].nombre);	
				return;
			  }
			}
			if (mistat->enmarcado) {
				sprintf(v10datosdiv+strlen(v10datosdiv),
				"<table id=\"tstat%d\" idrel=\"stat%d\" class=\"proptabla1\" style=\"position:absolute;left:%dpx;top:%dpx;\" border=\"0\" cellpadding=\"0\" CELLSPACING=\"0\"> "\
				"<tr  onmousedown=\"v10lib.BeginDrag(\'tstat%d\')\" class=\"v10pantarribaizq\"><td></td><td class=\"v10pantarribamed\"></td><td class=\"v10pantarribader\"></td></tr> "\
				"<tr><td class=\"v10pantmedioizq\"></td> <td class=\"v10pantmediomed\" style=\"width:%dpx;height:%dpx\"></td><td class=\"v10pantmedioder\"></td></tr> "\
				"<tr><td class=\"v10pantabajoizq\"></td><td class=\"v10pantabajomed\"></td><td class=\"v10pantabajoder\"></td></tr></table> ",
				nbstatsform,nbstatsform,mistat->posx, mistat->posy,  nbstatsform,mistat->lonx, mistat->lony); 
			}		
			sprintf(v10datosdiv+strlen(v10datosdiv),"<div id=\"stat%d\" style=\"position:absolute;left:%dpx;top:%dpx;width:%dpx;height:%dpx;\"></div> ",		
			nbstatsform, mistat->posx+10, mistat->posy+20, mistat->lonx, mistat->lony);
			if (v10cargadatos(nbstatsform,b,mistat->nombre,v10datoscharts+strlen(v10datoscharts))) {
					mensajeform(b,"v10statsform: error en v10cargadatos\n");
					return;
			}		
		}
	}

	if (nbstatsform) {
		v10reemplazapatron(v10inccharts,PATRONCHARTDIVS,v10datosdiv,1);		
		v10reemplazapatron(v10inccharts,PATRONEJSCCHARTS,v10datoscharts,1);
		v10reemplazapatron(v10html,PATRONREFCHARTS,REFCHARTS,1);
		v10reemplazapatron(v10html,PATRONCHARTS,v10inccharts,1);
		v10reemplazapatron(v10html,PATRONDELAYCHARTS,DELAYCHARTS,1);
	}
	statsencurso=0;

}