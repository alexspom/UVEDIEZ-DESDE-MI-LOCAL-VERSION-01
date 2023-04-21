/*
* Módulo : V10FORCURSOR.C
* Objeto:  Tratamiento de cursores en formularios
*
*
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"

fcursores *buscafcursor(bloques *b, char *nombre)
{
	int ncur;
	for (ncur = 0; ncur<b->ncur; ncur++) {
		if (stricmp(nombre, b->fcur[ncur].nombre) == 0) return(b->fcur + ncur);
	}
	return(NULL);
}

int describebloque(bloques *b, v10cursors *lc)
{
	int nc, ncamp;
	for (nc = 0; nc<lc->ndef; nc++) {
		char *aux = lc->def[nc].nombre;
		char base[MAXNOMBREV10];
		int indicador;
		if (*aux == ':') aux++;
		indicador = damebase(aux, base);
		if ((ncamp = damecampo(b, base)) == -1) {
			sprintf(ultimoerrorbloque, "NO EXISTE CAMPO\n %s \nEN CURSOR\n %s", aux, lc->nombre);
			mensajefcm(20, "NO EXISTE CAMPO\n %s \nEN CURSOR\n %s", aux, lc->nombre);
			return(-1);
		}
		else {
			if (indicador >= 0) {
				if (indicador<CINDOLD) definecursor(lc, nc + 1, direccampoind(b, ncamp, indicador), sizeof(int), V10INT);
				else definecursor(lc, nc + 1, direccampoind(b, ncamp, indicador), b->c[nc].lon, b->c[nc].tipo);
			}
			else {
				if (b->c[ncamp].convfrombd == NULL) definecursor(lc, nc + 1, direccampo(b, ncamp), b->c[ncamp].lon, b->c[ncamp].tipo);
				else                           definecursor(lc, nc + 1, b->c[ncamp].datoconv, b->c[ncamp].lon, b->c[ncamp].tipo);
			}
		}
	}
	return(0);
}


int conviertefromdb(bloques *b, v10cursors *lc)
{
	int nc, ncamp;
	for (nc = 0; nc<lc->ndef; nc++) {
		char *aux = lc->def[nc].nombre;
		char base[MAXNOMBREV10];
		int indicador;
		if (*aux == ':') aux++;
		indicador = damebase(aux, base);
		if ((ncamp = damecampo(b, base)) == -1) {
			sprintf(ultimoerrorbloque, "NO EXISTE CAMPO\n %s \nEN CURSOR\n %s", aux, lc->nombre);
			return(-1);
		}
		else {
			fcampos *c = b->c + ncamp;
			if (c->convfrombd == NULL) continue;
			if (indicador<0) {
				recuperacampo(b, c, c->datoconv);
				FORM(b)->cinput = c;
				c->convfrombd->fun(b, c->convfrombd);
			}
		}
	}
	return(0);
}

int convierte2db(bloques *b, v10cursors *lc)
{
	int nc, ncamp, ret;
	for (nc = 0; nc<lc->nbind; nc++) {
		char *aux = lc->bind[nc].nombre;
		char base[MAXNOMBREV10];
		int indicador;
		indicador = damebase(aux, base);
		if (indicador > 0) continue;
		if ((ncamp = damecampo(b, aux)) == -1) {
			sprintf(ultimoerrorbloque, "NO EXISTE CAMPO\n %s \nEN CURSOR\n %s", aux, lc->nombre);
			mensajefcm(20, "NO EXISTE CAMPO\n %s \nEN CURSOR\n %s", aux, lc->nombre);
			return(-1);
		}
		else {
			fcampos *c = b->c + ncamp;
			if (c->conv2bd == NULL) continue;
			copiacampo(b, c, c->datoconv);
			FORM(b)->cinput = c;
			ret = c->conv2bd->fun(b, c->conv2bd);
			if (ret) return(ret);
		}
	}
	return(0);
}

static int conviertepureout(bloques *b, v10cursors *lc)
{
	int nc, ncamp;
	for (nc = 0; nc<lc->nbind; nc++) {
		char *aux = lc->bind[nc].nombre;
		if ((ncamp = damecampo(b, aux)) == -1) {
			sprintf(ultimoerrorbloque, "NO EXISTE CAMPO\n %s \nEN CURSOR\n %s", aux, lc->nombre);
			return(-1);
		}
		else {
			fcampos *c = b->c + ncamp;
			if (c->convfrombd == NULL) continue;
			recuperacampo(b, c, c->datoconv);
			FORM(b)->cinput = c;
			c->convfrombd->fun(b, c->convfrombd);
		}
	}
	return(0);
}

static campooras *campobindbloque(v10cursors *c, char *n, int *indicador)
{
	int ncamp;
	if (c == NULL) return(NULL);
	for (ncamp = 0; ncamp<c->nbind; ncamp++) {
		char base[MAXNOMBREV10];
		*indicador = damebase(c->bind[ncamp].nombre, base);
		if (strcmp(base, n) == 0) return(c->bind + ncamp);
	}
	return(NULL);
}


v10cursors *bindbloque(bloques *b, char *sql, char *nombre)
{
	int i, nc;
	v10cursors *l;
	l = parsecursornombre(sql, nombre);
	if (l == NULL) return(NULL);
	for (i = 0; i<l->nbind; i++) {
		char *aux = l->bind[i].nombre;
		char base[MAXNOMBREV10];
		int indicador;
		if (*aux == ':') aux++;
		indicador = damebase(aux, base);
		if ((nc = damecampo(b, base)) == -1) {
			sprintf(ultimoerrorbloque, "NO EXISTE CAMPO\n %s \nEN CURSOR\n %s", aux, l->nombre);
			mensajefcm(20, "NO EXISTE CAMPO\n %s \nEN CURSOR\n %s", aux, l->nombre);
			return(l);
		}
		else {
			if (indicador >= 0) {
				if (indicador<CINDOLD) bindcursor(l, aux, direccampoind(b, nc, indicador), sizeof(int), V10INT);
				else bindcursor(l, aux, direccampoind(b, nc, indicador), b->c[nc].lon, b->c[nc].tipo);
			}
			else {
				if (b->c[nc].conv2bd == NULL) bindcursor(l, aux, direccampo(b, nc), b->c[nc].lon, b->c[nc].tipo);
				else                          bindcursor(l, aux, b->c[nc].datoconv, b->c[nc].lon, b->c[nc].tipo);
			}
		}
	}
	return(l);
}

v10cursors *bindquery(bloques *b, char *sql, char *nombre)
{
	int i, nc;
	v10cursors *l;
	return(bindbloque(b, sql, nombre));
	l = parsecursornombre(sql, nombre);
	if (l == NULL) return(NULL);
	for (i = 0; i<l->nbind; i++) {
		char *aux = l->bind[i].nombre;
		char base[MAXNOMBREV10];
		int indicador;
		fcampos *cb;
		if (*aux == ':') aux++;
		indicador = damebase(aux, base);
		if ((nc = damecampo(b, base)) == -1) {
			sprintf(ultimoerrorbloque, "NO EXISTE CAMPO\n %s \nEN CURSOR\n %s", aux, l->nombre);
			mensajefcm(20, "NO EXISTE CAMPO\n %s \nEN CURSOR\n %s", aux, l->nombre);
			return(l);
		}
		cb = b->c + nc;
		if (indicador < 0) {
			if (cb->tipo == V10CADENA && ((strchr((char *)direcuquerycampo(b, nc), '%') || strchr((char *)direcuquerycampo(b, nc), '_')) &&
				(*(char *)direcuquerycampo(b, nc) == '@')))   bindcursor(l, aux, (char *)(direcuquerycampo(b, nc)) + 1, cb->lon - 1, cb->tipo);
			else if (b->c[nc].conv2bd == NULL ||
				(cb->tipo == V10CADENA && (strchr((char *)direcuquerycampo(b, nc), '%') || strchr((char *)direcuquerycampo(b, nc), '_')))) bindcursor(l, aux, direcuquerycampo(b, nc), cb->lon, cb->tipo);
			else                  bindcursor(l, aux, b->c[nc].datoconv, b->c[nc].lon, b->c[nc].tipo);
		}
		else {
			bindcursor(l, aux, direccampoind(b, nc, indicador), sizeof(int), V10INT);
		}
	}
	return(l);
}

int ejecutafcursor(bloques *b, char *nombre)
{
	fcursores *fcur;
	int ret;
	int ncampoerr = damecampo(b, "V10ORAERR");
	if (ncampoerr != -1) {
		a2bcampo(b, "v10ORAERR", "0");
	}
	if ((fcur = buscafcursor(b, nombre)) == NULL) {
		mensajefcm(10, "No encuentro cursor %s", nombre);
		return(-1);
	}
	if (fcur->cur == NULL) {
		fcur->cur = bindbloque(b, fcur->sql, nombre);
		if (fcur->cur == NULL) {
			char error[MAXERRORORACLE] = "";
			getlastdberror(error);
			ponultimoerrorbloque("ERROR ABRIENDO\nCURSOR %s\n%s", nombre, error);
			return(1);
		}
		else ponultimoerrorbloque("");
		if (describebloque(b, fcur->cur)) {
			liberacursor(fcur->cur);
			fcur->cur = NULL;
			return(1);
		}
	}
	ret = convierte2db(b, fcur->cur);
	if (ret == 0) {
		if (funcioncursor(fcur->cur) == FSELECT) {
			ret = ejefetchcursor(fcur->cur);
			if (ncampoerr != -1 && ret == 0) {
				ret = *(long *)direccampo(b, ncampoerr);
			}
			if (ret) {
				FORM(b)->oraerr = ret;
			}
			else {
				conviertefromdb(b, fcur->cur);
			}
		}
		else {
			ret = ejecutacursor(fcur->cur);
			if (ncampoerr != -1 && ret == 0) {
				ret = *(long *)direccampo(b, ncampoerr);
			}
			if (ret) {
				FORM(b)->oraerr = ret;
				return(ret);
			}
			conviertepureout(b, fcur->cur);
		}
	}
	return(ret);
}


int fetchfcursor(bloques *b, char *nombre)
{
	fcursores *fcur;
	int ret;
	int ncampoerr = damecampo(b, "V10ORAERR");
	if (ncampoerr != -1) {
		a2bcampo(b, "v10ORAERR", "0");
	}
	if ((fcur = buscafcursor(b, nombre)) == NULL) {
		mensajefcm(10, "No encuentro cursor %s", nombre);
		return(-1);
	}
	if (fcur->cur == NULL) {
		final(("Intentando hacer fetch en un cursor de form no abierto"));
	}
	ret = fetchcursor(fcur->cur);
	conviertefromdb(b, fcur->cur);
	if (ncampoerr != -1 && ret == 0) {
		ret = *(long *)direccampo(b, ncampoerr);
	}
	return(ret);
}

long procesadasfcursor(bloques *b, char *nombre)
{
	fcursores *fcur;
	if ((fcur = buscafcursor(b, nombre)) == NULL) {
		mensajefcm(10, "No encuentro cursor %s", nombre);
		return(-1);
	}
	if (fcur->cur == NULL) return(0);
	return(procesadascursor(fcur->cur));
}

void liberafcursor(bloques *b, char *nombre)
{
	fcursores *fcur;
	if ((fcur = buscafcursor(b, nombre)) == NULL) {
		mensajefcm(10, "No encuentro cursor %s", nombre);
		return;
	}
	if (fcur->cur) {
		liberacursor(fcur->cur);
		fcur->cur = NULL;
	}
}


