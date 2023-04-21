#include "v10wwwform.h"



int maxfilas, maxcolumnas;
static void v10incluyebloque(int nbloque, bloques *b, char *patron);

int entrablecampo(fcampos *c)
{
	bloques *b = c->b;
	if (!c->b || !entrablebloque(c->b) || b->noinput) return(0);
	if ((c->v->enter && c->v->noinput == 0) || b->enterquery || (CABECERA(b)->antiguo == 0)) {
		if ((((c->tabla && b->noupdate) || c->noupdate) && CABECERA(b)->antiguo) || c->oculto != 0 || (c->enter == 0 && !b->enterquery)) return(0);
		if (b->enterquery && !c->tabla && c->where == 0) return(0);
		return(1);
	}
	return(0);
}

static void damepatronplantillabloque(bloques *b, char *miplantilla)
{
	char *ptr, mifichero[MAXPATH] = "";
	*miplantilla = 0;
	strcpy(mifichero, b->fichero);
	ptr = strchr(mifichero, '.');
	if (ptr) *ptr = 0;
	sprintf(miplantilla, "<!--PLANTILA=plantilla.%s.pan.html-->", mifichero);
}

static void damenombreplantillabloque(bloques *b, char *miplantilla)
{
	char *ptr, mifichero[MAXPATH] = "";
	*miplantilla = 0;
	strcpy(mifichero, b->fichero);
	ptr = strchr(mifichero, '.');
	if (ptr)  *ptr = 0;
	sprintf(miplantilla, "plantilla.%s.pan.html", mifichero);
}

static void dametextoinclude(int nbloque, char *texto, char *patronini, char *patronfinal, char *textoinclude)
{
	char *ptrini, *ptrfinal, patronori[MAXPATH] = "", patrondest[MAXPATH] = "";
	*textoinclude = 0;
	ptrini = strstr(texto, patronini);
	ptrfinal = strstr(texto, patronfinal);
	if (ptrini && ptrini) strcopia(textoinclude, ptrini + strlen(patronini), ptrfinal - (ptrini + strlen(patronfinal)) + 2);
	else return;
	sprintf(patronori, "id=\"lbbl-1");
	sprintf(patrondest, "id=\"lbbl%d", nbloque);
	while (strstr(textoinclude, patronori)) v10reemplazapatron(textoinclude, patronori, patrondest, 1);
	sprintf(patronori, "id=\"bl-1");
	sprintf(patrondest, "id=\"bl%d", nbloque);
	while (strstr(textoinclude, patronori)) v10reemplazapatron(textoinclude, patronori, patrondest, 1);
	sprintf(patronori, "id=\"tdbl-1");
	sprintf(patrondest, "id=\"tdbl%d", nbloque);
	while (strstr(textoinclude, patronori)) v10reemplazapatron(textoinclude, patronori, patrondest, 1);
	sprintf(patronori, "id=\"trbl-1");
	sprintf(patrondest, "id=\"trbl%d", nbloque);
	while (strstr(textoinclude, patronori)) v10reemplazapatron(textoinclude, patronori, patrondest, 1);
	sprintf(patronori, "id=\"tbbl-1");
	sprintf(patrondest, "id=\"tbbl%d", nbloque);
	while (strstr(textoinclude, patronori)) v10reemplazapatron(textoinclude, patronori, patrondest, 1);
	sprintf(patronori, "&bl-1");
	sprintf(patrondest, "&bl%d", nbloque);
	while (strstr(textoinclude, patronori)) v10reemplazapatron(textoinclude, patronori, patrondest, 1);
}

// campos de pantalla monoregistro
void v10campos2html(int nbloque, bloques *b, int incluyevalores, formtabs *ftab, char *ptrout)
{
	int i = 0, ncol = 1;
	char valor[MAXCADENA] = "";
	maxfilas = 1;
	if (!b->invisible) {
		int ncamp = 0;
		for (ncamp = 0; ncamp<b->ncamp; ncamp++) if (b->c[ncamp].ftab == ftab) recargadefectos(b, b->c + ncamp);
	}
	if (incluyevalores) {
		sprintf(ptrout + strlen(ptrout), "<!-- %s.PAN tab %s con valores cargados-->\n", b->nombre, ftab ? ftab->nombre : "SINTAB");
		if (ftab == b->ftab) initvbloque(b);
	}
	if (incluyevalores) damevbloquei(b, 0);
	for (i = 0; i<b->ncamp; i++) {
		fcampos *c = b->c + i;
		if (!c->v || c->v->invisible) continue; // oculto	
		if (c->ftab != ftab) {
			ncol++;
			continue;
		}
		v10ora2campo(incluyevalores, nbloque, b, c, 1, c->nombre, 1, valor);
		if (entrablecampo(c) && c->checkbox) {
			if (strcmp(c->checkbox->valor_false, valor) && strcmp(c->checkbox->valor_true, valor)) {
				strcpy(valor, c->checkbox->valor_false);
				a2input(c->v, valor);
			}
			v10checkbox2html(ptrout + strlen(ptrout), nbloque, 0, 1, ncol, b, b->c + i, incluyevalores);
		}
		else if (entrablecampo(c)) v10input2html(ptrout + strlen(ptrout), nbloque, 1, ncol, b, c, incluyevalores);
		else v10inputnoenter2html(ptrout + strlen(ptrout), nbloque, 1, ncol, b, c, incluyevalores);
		ncol++;
	}
	if (b == v10damebloqueactual()) maxcolumnas = ncol - 1;
	if (incluyevalores && ftab == b->ftab) finvbloque(b);
}


/*
static void imagenespestanna(int bloque, bloques *b) {
int i,offset=0;

for (i=0;i<formglobal->nbloques;i++) {
sprintf(v10datoshtml+strlen(v10datoshtml),"<div saltabloque=\"bl%d\" class=\"v10pestanna\" title=\"%s\" style=\"left: %ipx; top: %ipx; width: %ipx;",i,formglobal->b[i]->vi.titulo, LEFTPESTANNA+offset-1, TOPPESTANNA-32,70);
if (formglobal->b[i]==v10damebloqueactual()) strcat(v10datoshtml,"background-color:#E6E6E6;color: darkblue;  z-index: 1000;");
else strcat(v10datoshtml,"background-color:darkgray; color: white; z-index: 50;");
if (i==0) strcat(v10datoshtml,"border-left:1px double darkgray;");
else  strcat(v10datoshtml,"border-left:3px outset white;");
sprintf(v10datoshtml+strlen(v10datoshtml),"\">Bloque %2d</div>\n",i);
offset+=70;
}

}
*/

static void damenuevotop(bloques *b, int *nuevotop)
{
	bloques *bp, *bact;
	int ancho, largo, left, top;
	bact = b;
	bp = b->padre;
	while (bp) {
		if (bp->wtemplegado &&  bp->vi.w.y1 <  bact->vi.w.y1)  { // al estar plegado, descuento el alto de este bloque + 25
			v10damedimensionesbloque(bp, &left, &top, &ancho, &largo);
			(*nuevotop) -= (largo - 10);
		}
		bact = bp;
		bp = bact->padre;
	}
}

void v10bloquei2html(int nbloque, bloques *b, int tipodatos)
{
	int ancho, largo, left, top;
	char miplantilla[MAXPATH] = "", mititulo[MAXCADENA] = "";
	char clasepantarribaizq[MAXPATH] = "", anchuratdplegada[MAXPATH] = "", miclasetd[MAXPATH] = "";
	char *ptrout = v10datoshtml + strlen(v10datoshtml);
	if (tipodatos != SUSTITUYEPLANTILLA) {
		memset(clasepantarribaizq, 0, MAXPATH);
		strcpy(clasepantarribaizq, (b == v10damebloqueactual()) ? "v10pantarribaizq" : "v10pantarribanoselizq");
		b->wtemplegado = 0;
		v10damedimensionesbloque(b, &left, &top, &ancho, &largo);
		if (b != v10damebloqueactual()) {
			if (b->wplegado>0) {
				if (b != v10damebloqueactual()) strcat(clasepantarribaizq, (b->wplegado == 1) ? "mas" : "menos");
				*miclasetd = 0;
				strcat(miclasetd, (b->wplegado == 1) ? "desplegar=\"1\"" : (b->wplegado == 2) ? "plegar=\"1\"" : "");
				if (b->wplegado == 1) b->wtemplegado = 1;
			}
			else {
				if (b->padre && b->padre->wplegado == 1) b->wtemplegado = 1;
			}
		}
		if (b->wtemplegado == 1) {
			sprintf(anchuratdplegada, "style=\"width:%dpx;\"", ancho - 47);
			sprintf(miclasetd + strlen(miclasetd), "class=\"%s\"", clasepantarribaizq);
		}
		damenuevotop(b, &top);
		if (b == v10damebloqueactual()) b->wtemplegado = 0;
		if (tipodatos == ENPLANTILLAPAN) top = left = 100;
		if (b->wtipomarco == MARCONORMAL || b->wtemplegado == 1) { // MUESTRA EL MARCO NORMAL DEL BLOQUE
			//sprintf(ptrout+strlen(ptrout),"<table tbbloque=\"%d\" style=\"position:absolute;top:%dpx;left:%dpx\" border=\"0\" cellpadding=\"0\" CELLSPACING=\"0\" onclick=\"fonclick()\">\n",nbloque,top,left);
			//11-03-2014 Se añade modificación para trabajar con el diseño sin imagenes (light versión) - E.Arana
			sprintf(ptrout + strlen(ptrout), "<table tbbloque=\"%d\" class=\"bordered\" style=\"border-collapse: collapse;border-spacing: 0;position:absolute;top:%dpx;left:%dpx\" border=\"0\" cellpadding=\"0\" CELLSPACING=\"0\" onclick=\"fonclick()\">\n", nbloque, top -38 , left);
			sprintf(ptrout + strlen(ptrout), "<thead><tr class=\"%s\"><th %s id=\"bl%d\"></th><th id=\"bl%d\"class=\"%s\" %s><span id=\"bl%d\" class=\"%s\">\n",
				clasepantarribaizq, miclasetd, nbloque, nbloque,
				(b == v10damebloqueactual()) ? "v10pantarribamed" : "v10pantarribanoselmed", anchuratdplegada, nbloque,
				(b == v10damebloqueactual()) ? "v10titulopantallas" : "v10titulopantallasnosel");
			memset(mititulo, 0, sizeof(mititulo));
			strcpy(mititulo, v10translate(b->vi.titulo));
			v10ansitohtml(v10wwwoem2ansi(mititulo));
			strcat(ptrout, mititulo);
			if (b->enterquery) strcat(ptrout, " (EQ) ");
			sprintf(ptrout + strlen(ptrout), "<!--v10mensajebl%d--></span></th><td %s id=\"bl%d\" class=\"%s\"></td></tr>", nbloque, (b == v10damebloqueactual()) ? "scr=1" : "", nbloque, (b == v10damebloqueactual()) ? ((b->visiblescroll) ? "v10pantarribaderscroll" : "v10pantarribader") : "v10pantarribanoselder");
			if (b->wtemplegado == 1){
				strcat(ptrout, "</table>");
				return; // no muestra los datos
			}
			strcat(ptrout, "<tbody><tr><td> </td>");
			sprintf(ptrout + strlen(ptrout), " <td  id=\"bl%d\" style=\"width:%dpx;height:%dpx\">\n", nbloque, ancho - 37, largo);
			strcat(ptrout, "</td><td> </td></tr></tbody></table>\n");
			if (b != v10damebloqueactual()) b->visiblescroll = 0;

			if (b->nformtabs == 0) sprintf(ptrout + strlen(ptrout), "\t<fieldset id=\"fsbl%d\"  class=\"v10fieldset\" style=\"position:absolute;top:%dpx;left:%dpx;width:%dpx;height:%dpx;border:%dpx;%s\">\n",
				nbloque, top - 16, left, ancho - 16, largo, (b->wtipomarco == MARCOFRAME || b->wtipomarco == MARCOPESTANA) ? 1 : 0, (b->visiblescroll == 1) ? "overflow-x:scroll" : "");
		}
		else {
			if (b->wtipomarco == MARCOFRAME || b->wtipomarco == MARCOPESTANA)
				sprintf(ptrout + strlen(ptrout), "\t<fieldset id=\"fsbl%d\"  class=\"v10fieldsetbloq\" style=\"z-index:%d;position:absolute;top:%dpx;left:%dpx;width:%dpx;height:%dpx;%s\">\n",
				nbloque, 10 + nbloque, top, left, ancho, largo, (b->visiblescroll == 1) ? "overflow-x:scroll" : "");
			else
				sprintf(ptrout + strlen(ptrout), "\t<fieldset id=\"fsbl%d\" dummy=\"1\"  class=\"v10fieldset\" style=\"position:absolute;top:%dpx;left:%dpx;width:%dpx;height:%dpx;%s\">\n",
				nbloque, top, left, ancho, largo, (b->visiblescroll == 1) ? "overflow-x:scroll" : "");

		}
	}
	switch (tipodatos) {
	case SUSTITUYEPLANTILLA: // se indicaba en la plantilla FRM que existia la plantilla, pero no existe,
		// por lo que se generan los datos
		v10labels2html(nbloque, b, NULL);
		if (b->regpag>1) v10tabla2html(nbloque, b, 1, NULL);
		else v10campos2html(nbloque, b, 1, NULL, ptrout + strlen(ptrout));
		if (b == v10damebloqueactual()) v10botones2html(nbloque, b, SUSTITUYEPLANTILLA);
		break;

	case SINPLANTILLA: { // se generan los datos, si existe plantilla del bloque, los inserta de ahí
		char v10datospan[MAXCADENAHTML] = "", v10datosinclude[MAXCADENAHTML] = "";
		damenombreplantillabloque(b, miplantilla);
		//memset(v10datospan,0,sizeof(v10datospan));			
		*v10datospan = 0;
		if (leefichero(miplantilla, v10datospan)>0) { // existe una plantilla generada para este bloque
			// inserta los datos desde la plantilla, para este bloque
			dametextoinclude(nbloque, v10datospan, INCLUDEDATA, ENDINCLUDEDATA, v10datosinclude);
			strcat(ptrout, v10datosinclude);
			if (b == v10damebloqueactual()) { // inserta desde la plantilla la botonera/botones
				dametextoinclude(nbloque, v10datospan, INCLUDEBOTONES, ENDINCLUDEBOTONES, v10datosinclude);
				strcat(v10botoneshtml, v10datosinclude);
			}
		}
		else { // como no existe la plantilla, genera los datos, sin mas
			if (b->nformtabs == 0) {
				v10labels2html(nbloque, b, NULL);
				if (b->regpag>1) v10tabla2html(nbloque, b, 1, NULL);
				else v10campos2html(nbloque, b, 1, NULL, ptrout + strlen(ptrout));
			}
			else {
				int i;
				sprintf(ptrout + strlen(ptrout), "<div id='tabContainer'>\n");
				sprintf(ptrout + strlen(ptrout), "<div id='tabs'>\n");
				sprintf(ptrout + strlen(ptrout), " <ul>\n");
				for (i = 0; i<b->nformtabs; i++) {
					sprintf(ptrout + strlen(ptrout), "<li id='tabHeader_%02d%d'>%s</li>", nbloque, i + 1, b->ftab[i].nombre);
				}
				sprintf(ptrout + strlen(ptrout), " </ul>\n");
				sprintf(ptrout + strlen(ptrout), "</div>\n");
				sprintf(ptrout + strlen(ptrout), "<div id='tabscontent'>\n");
				for (i = 0; i<b->nformtabs; i++) {
					sprintf(ptrout + strlen(ptrout),
						"<div class='tabpage' id='tabpage_%02d%d'>\n",
						nbloque, i + 1);
					sprintf(ptrout + strlen(ptrout),
						"<fieldset id='fsbl%02d%d'  class='v10fieldset' style='top:%dpx;left:%dpx;width:%dpx;height:%dpx;border:0px;'>\n",
						nbloque, i, top, left + 2, ancho - 16, largo);
					v10labels2html(nbloque, b, b->ftab + i);
					if (b->regpag>1) v10tabla2html(nbloque, b, 1, b->ftab + i);
					else v10campos2html(nbloque, b, 1, b->ftab + i, ptrout + strlen(ptrout));
					sprintf(ptrout + strlen(ptrout), "</fieldset>\n");
					sprintf(ptrout + strlen(ptrout), "</div>\n");
				}
				sprintf(ptrout + strlen(ptrout), "</div>\n");
				sprintf(ptrout + strlen(ptrout), "</div>\n");
			}
			if (b == v10damebloqueactual()) v10botones2html(nbloque, b, SINPLANTILLA);
		}
		break;
	}
					   break;
	case ENPLANTILLAFRM: // inserta un referencia a la plantilla del PAN
		// se utiliza cuando se genera la plantilla de un FRM
		damepatronplantillabloque(b, miplantilla);
		strcat(ptrout, miplantilla);
		strcat(ptrout, "\n");
		break;
	case ENPLANTILLAPAN: // genera los datos de la plantilla del PAN, delimitando los datos incrustable en 
		// la plantilla del FRM al referenciar al mismo 
		sprintf(ptrout + strlen(ptrout), "\n%s\n", INCLUDEDATA);
		v10labels2html(nbloque, b, NULL);
		if (b->regpag>1) v10tabla2html(nbloque, b, 0, NULL);
		else v10campos2html(nbloque, b, 0, NULL, ptrout + strlen(ptrout));
		sprintf(ptrout + strlen(ptrout), "\n%s\n", ENDINCLUDEDATA);
		v10botones2html(nbloque, b, ENPLANTILLAPAN);
		break;
	}
	if (tipodatos != SUSTITUYEPLANTILLA) {
		if (b->wtipomarco == MARCOFRAME) {
			strcpy(mititulo, v10translate(b->vi.titulo));
			v10ansitohtml(v10wwwoem2ansi(mititulo));
			sprintf(ptrout + strlen(ptrout), "<legend>%s</legend>", mititulo);
		}
		if (b->nformtabs == 0) strcat(ptrout, "</fieldset>\n");
		v10frames2html(b, nbloque, top + 22, left + 3);
	}
}

void v10bloque2plantillahtml(bloques *b, char *ruta)
{
	FILE *fout;
	char destino[MAXPATH] = "", v10plantilla[MAXPATH] = "";
	damenombreplantillabloque(b, v10plantilla);
	v10log(LOGNORMAL, "Generando plantilla para bloque %s en ruta %s\n", b->nombre, ruta);
	sprintf(destino, "%s\\%s", ruta, v10plantilla);
	fout = fopenpath(destino, "r");
	if (fout) {
		v10log(LOGERROR, "No se puede machacar plantila de bloque %s al existir\n", b->nombre);
		fclose(fout);
		return;
	}
	*v10html = 0;
	*v10botoneshtml = 0;
	*v10datoshtml = 0;
	if (leeficheropath(PLANTILLABLOQUE, v10html) == 0) {
		final(("No se puede abrir plantilla base %s", PLANTILLABLOQUE));
		return; // no existe la plantilla por defecto
	}
	v10bloquei2html(-1, b, ENPLANTILLAPAN);
	v10reemplazapatron(v10html, PATRONDATOS, v10datoshtml, 1);
	v10botones2html(-1, b, ENPLANTILLAPAN);
	v10reemplazapatron(v10html, PATRONBOTONES, v10botoneshtml, 1);
	fout = fopen(destino, "w");
	if (!fout) final(("No se puede abrir fichero %s", destino));
	fprintf(fout, "%s", v10html);
	fclose(fout);
	v10log(LOGNORMAL, "Generada con éxito plantilla para bloque %s en fichero %s\n", b->nombre, destino);
}

void v10bloques2html(forms *f, int tipodatos)
{
	int i;
	v10recolocaform(f);
	for (i = 0; i<f->nbloques; i++) v10bloquei2html(i, f->b[i], tipodatos);
}

static void v10incluyebloque(int nbloque, bloques *b, char *patron)
{
	// inserta los datos de la plantilla, sustituye el id de los objetos, el valor de nbloque
	// si el bloque es el bloque actual, tb incluye la botonera
	char fichplantilla[MAXPATH] = "";
	char v10datospan[MAXCADENAHTML] = "";
	*v10datoshtml = 0;
	*v10datospan = 0;
	*v10botoneshtml = 0;
	damenombreplantillabloque(b, fichplantilla);
	if (leefichero(fichplantilla, v10datospan) == 0) { // si no existe la plantilla, se generan los datos 		
		v10bloquei2html(nbloque, b, SUSTITUYEPLANTILLA);
		v10reemplazapatron(v10html, patron, v10datoshtml, 1);
		v10reemplazapatron(v10html, PATRONBOTONES, v10botoneshtml, 1);
	}
	else { // va a incluir los datos de la plantilla
		char v10datosinclude[MAXCADENAHTML] = "";
		v10log(LOGNORMAL, "Cargada plantilla %s\n", fichplantilla);
		dametextoinclude(nbloque, v10datospan, INCLUDEDATA, ENDINCLUDEDATA, v10datosinclude);
		v10reemplazapatron(v10html, patron, v10datosinclude, 1);
		*v10datosinclude = 0;
		if (b == v10damebloqueactual()) { // si es la plantilla del bloque actual, integro sus botones de la plantilla
			dametextoinclude(nbloque, v10datospan, INCLUDEBOTONES, ENDINCLUDEBOTONES, v10datosinclude);
			v10reemplazapatron(v10html, PATRONBOTONES, v10datosinclude, 1);
		}
	}
}

void v10incluyebloques(forms *f)
{
	int i;
	char mipatron[MAXPATH];
	for (i = 0; i<f->nbloques; i++) {
		damepatronplantillabloque(f->b[i], mipatron);
		if (strstr(v10html, mipatron))  v10incluyebloque(i, f->b[i], mipatron);
	}
}




