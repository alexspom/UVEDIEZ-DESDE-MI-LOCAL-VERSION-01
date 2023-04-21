#include "v10wwwform.h"

void v10frames2html(bloques *b,int nbloque,int top,int left) 
{
	int i;
	char mileyenda[MAXPATH]="",miincludecss[MAXCADENA]="";
	for (i=0;i<b->nbframes;i++) {
		v10ansitohtml(v10wwwoem2ansi(b->frames[i].nombre));
		sprintf(v10datoshtml+strlen(v10datoshtml),"<fieldset id=\"fsbl%d\"  class=\"%s\" style=\"position:absolute;top:%dpx;left:%dpx;width:%dpx;height:%dpx\">",
			nbloque,(b->frames[i].lony)==0?"v10fieldset3":"v10fieldset2",top+42+b->frames[i].posy,left+b->frames[i].posx,b->frames[i].lonx,b->frames[i].lony);
		sprintf(v10datoshtml+strlen(v10datoshtml),"<legend>%s</legend></fieldset>",b->frames[i].nombre);	
	
	}
	for (i=0;i<b->nbframesfile;i++) {
		v10ansitohtml(b->framesfile[i].nombre);
		*miincludecss=0;
		if (*b->framesfile[i].includecss) strcpy(miincludecss,b->framesfile[i].includecss);
		sprintf(v10datoshtml+strlen(v10datoshtml),"<fieldset id=\"fsbl%d\"  class=\"%s\" style=\"position:absolute;top:%dpx;left:%dpx;width:%dpx;height:%dpx;%s\">",
			nbloque,(b->framesfile[i].lony)==0?"v10fieldset3":"v10fieldset2",top+42+b->framesfile[i].posy,left+b->framesfile[i].posx,b->framesfile[i].lonx,b->framesfile[i].lony,miincludecss);
		if (strcmp(b->framesfile[i].nombre,"\"\"")) {			
			strcpy(mileyenda, b->framesfile[i].nombre);
			sprintf(v10datoshtml+strlen(v10datoshtml),"<legend>%s</legend></fieldset>",mileyenda);	
		} else	strcat(v10datoshtml,"</fieldset>");	
	}
}
