#include "v10wwwform.h"

int v10wwwselwhere(char **opciones,int primera,int x,int y) {
	int i=1;
	char misopciones[MAXCADENA]="",miopcion[MAXCADENA]="";
	while (opciones[i]!=NULL) {
		sprintf(misopciones + strlen(misopciones), "<tr class=\"opczoom\"><td opc=%d>", i);
		strcpy(miopcion,v10translate(opciones[i]));
		v10ansitohtml(v10wwwoem2ansi(miopcion));
		strcat(misopciones,miopcion);
		strcat(misopciones,"</tr></td>");   
		i++;
   }
   return(v10wwwmensajeselwhere(opciones[0],misopciones));
}
