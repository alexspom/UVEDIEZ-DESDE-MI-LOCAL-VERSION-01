#include "v10wwwform.h"

void v10boton2html(int nbloque, bloques *b,fbotones *fboton, int botonera,int posx, int posy, int alto) 
{
	char mitexto[MAXCADENA]="";
	char teclaespecial[MAXCADENA]="",combinacion[MAXCADENA]="";
	char includecssextra[MAXCADENA]="",estilocssextra[MAXCADENA]="";	
	if (fboton->oculto) return;
	v10comb(combinacion,fboton->tecla);
	if (!strcmp(combinacion,"ctrl"))  strcpy(teclaespecial,"onkeyup_ctrl");
	else if (!strcmp(combinacion,"shift")) strcpy(teclaespecial,"onkeyup_shift");
	else if (!strcmp(combinacion,"alt")) strcpy(teclaespecial,"onkeyup_alt");
	else strcpy(teclaespecial,"onkeyup");
	strcpy(mitexto,fboton->texto);
	v10ansitohtml(trim(mitexto));
	//v10carespeciales(trim(fboton->texto),' ',"&nbsp"));
	// si es una imagen tiene otro estilo distinto, sin bordes
	sprintf(v10botoneshtml+strlen(v10botoneshtml),"<input name=\"%s\"id =\"bl%d%s\"tecla=\"%i\"teclaespecial=\"%s\"title=\"%s\" NOTAB ",
		    fboton->nombre,nbloque,fboton->nombre,v10ansi2js(fboton->tecla),teclaespecial,fboton->tooltip?fboton->tooltip:fboton->nombre);
	if (*fboton->estilocss) strcpy(estilocssextra,fboton->estilocss);
	if (*fboton->includecss) strcpy(includecssextra,fboton->includecss);

	if (strcmp(fboton->image,"NO")) sprintf(v10botoneshtml+strlen(v10botoneshtml),"type=\"image\" class=\"v10buttonimg %s\" src=\"%s/%s\"",estilocssextra,v10httpconf.v10serverimg,fboton->image);
    else sprintf(v10botoneshtml+strlen(v10botoneshtml),"type=\"button\" class=%s value=\"%s\"",!es_blanco(estilocssextra)?estilocssextra:"""v10button""",mitexto);

	sprintf(v10botoneshtml+strlen(v10botoneshtml)," style=\"width:%ipx",(!strcmp(fboton->image,"NO"))?fboton->lonx+2:fboton->lonx);
	// si no pertenece a una botonera
	if (fboton->disabled) strcat(v10botoneshtml,";cursor:not-allowed");
	if (botonera==0) sprintf(v10botoneshtml+strlen(v10botoneshtml),";height:%ipx;position:absolute;top:%ipx;left:%ipx;%s\"",
								fboton->lony,fboton->posy+v10y2px(0,1),fboton->posx+v10x2px(0,1),includecssextra);
	else sprintf(v10botoneshtml+strlen(v10botoneshtml),";height:%ipx;position:absolute;top:%ipx;left:%ipx;%s\"",alto,posy,posx,includecssextra);
	/*strcat(v10datoshtml," onmouseover=\"v10lib.fonmouseover();\"");
	strcat(v10datoshtml," onmouseout=\"v10lib.fonmouseout();\"");*/
	
	if (fboton->disabled) strcat(v10botoneshtml, " disabled=\"disabled\" ");
	strcat(v10botoneshtml,"/>\n");
}


static void v10botonenbotonera(fbotoneras *fbotonera,int numboton,int *posx,int *posy, int *ancho,int *alto) {
	int numbotonactual;

	// siempre coge ancho del botón
	// lonx = -1 vertical, altura la del botón
	// lonx =  0 horizontal, altura la del botón
	// lonx >  0 lonx botones por fila, la altura de la fila a lony en píxeles

	numbotonactual= (fbotonera->numbotones - (numboton+1));
	switch (fbotonera->lonx) {
	  case -1:  // vertical
		  *posx=fbotonera->posx;
		  *posy= fbotonera->posy + *alto;
		  *alto+= fbotonera->lony;
		  break;
	  case 0: // horizontal
		  *posx=fbotonera->posx + *ancho;
		  *ancho += fbotonera->b[numboton]->lonx;
		  *posy=fbotonera->posy;
		  break;
	  default: // mosaico lonx botones por fila        
		  if (numbotonactual % fbotonera->lonx == 0) { // nueva fila
			  *ancho=0;
			  *alto += fbotonera->lony;
		  }
		  *posx= fbotonera->posx + *ancho;
		  *ancho += fbotonera->b[numboton]->lonx;        
		  *posy=fbotonera->posy+*alto;
		  break;
	}
}


static void v10botonera2html(int nbloque,bloques *b) {
	int i,j,posx,posy,ancho,alto;
	fbotoneras *fbotonera;

	for (i=0;i<b->numbotoneras;i++) {
		fbotonera=b->fbot+i;
		posx=posy=ancho=alto=0;
		for (j=fbotonera->numbotones-1;j>=0;j--) {
			v10botonenbotonera(fbotonera,j,&posx,&posy,&ancho,&alto);      
			v10boton2html(nbloque,b,fbotonera->b[j],1,posx,posy,fbotonera->lony);    
		}    
	}
}


void v10botones2html(int nbloque, bloques *b,int tipodatos) {
	int i;		
    *v10botoneshtml = 0;
	if (tipodatos==ENPLANTILLAPAN) strcat(v10botoneshtml,"<!--V10INCLUDEBOTONES-->\n");
	v10botonera2html(nbloque,b);
	for (i=0;i<b->numbotones;i++) {
		fbotones *fboton=b->fb+i;	
		if (fboton->posx<0 || fboton->posy<0) continue;
		v10boton2html(nbloque,b,fboton,0,0,0,0);	}   
	if (tipodatos==ENPLANTILLAPAN) strcat(v10botoneshtml,"<!--V10ENDINCLUDEBOTONES-->\n");
}

void v10cargabotoneradef(void) 
{
	char *ptrini,*ptrfinal,textoinclude[MAXCADENAHTML];	
	if (!strstr(v10html,PATRONBOTONERADEF)) return;
    *textoinclude = 0;
    *v10datoshtml = 0;
	leefichero("botoneradef.html",v10datoshtml);
	ptrini=strstr(v10datoshtml,INCLUDEDATA);
	ptrfinal=strstr(v10datoshtml,ENDINCLUDEDATA);
	if (ptrini && ptrfinal) strcopia(textoinclude,ptrini+strlen(INCLUDEDATA),ptrfinal-(ptrini+strlen(INCLUDEDATA)));	
	v10reemplazapatron(v10html,PATRONBOTONERADEF,textoinclude,1);	
}


