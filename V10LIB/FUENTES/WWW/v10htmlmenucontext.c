#include "v10wwwform.h"

int v10wwwmenucontex(formenus *f)
{
	char mititulo[MAXPATH]="",misopciones[MAXCADENA]="",miopcion[MAXCADENA]="";
	// se pone en modo modal, cuidado
	// trata teclas cuu y cua, esc y enter, click sobre una opcion,  doble click, y mouseover/out
	int i;
   	
	sprintf(mititulo,"Zoom: %s",f->titulo);
	for (i=0;i<f->nopciones;i++) {
        char estilo[MAXPATH]="opczoom";
        if (f->op[i].ft==NULL) strcpy(estilo,"opczoominact");
		sprintf(misopciones+strlen(misopciones),"<tr class=\"%s\"><td opc=%d >",estilo,i+1);
		strcpy(miopcion,v10translate(f->op[i].opcion));
		v10ansitohtml(miopcion);
		strcat(misopciones,miopcion);
		strcat(misopciones,"</td></tr>");      
   }
   return(v10wwwmensajezoom(formglobal,mititulo,misopciones));
}