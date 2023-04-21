/*******************************************************************************
* Módulo : VDRADTRIG.C                                                         *
* Función: Definición de trigers de radio                                      *
*                                                                              *
* Autor  : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/
#include "vdradio.h"

static int fejecutaradio(bloques *b, ftrigers *f)
{
	int ret = SUCCESS;
	int nc;
	long opcion;
	if (f == NULL) return(ret);
	v10log(LOGDEBUG, "fejecutaradio - Inicio trigers bloque %s\n", b->fichero);
	for (nc = 0; nc<f->nparam; nc += 2) {
		ret = fejecutaparam(b, f, nc, &opcion);
		if ((opcion & CTERMINA) && ret) {
			ret = 0;
			v10log(LOGDEBUG, "fejecutaradio - opcion & termina trigers afirmativo en bloque %s\n", b->fichero);
			break;
		}
		if (ret) {
			if (nc + 1 >= f->nparam) {
				mensajefcm(10, "Triger fejecuta con numero impar de parametros\n");
				return(-1);
			}
			if (!es_blanco(f->param[nc + 1])) f->msg = f->param[nc + 1];
			break;
		}
		if (b->form->nivel == NIVEL_FORM) {
			v10log(LOGNORMAL, "fejecutaradio - Nivel FORM. Fin cadena de trigers en bloque %s\n", b->fichero);
			break;
		}
	}
	v10log(LOGDEBUG, "fejecutaradio - Fin trigers bloque %s\n", b->fichero);
	return(ret);
}

static int fdesignacionradio(bloques *b, ftrigers *ft)
{
	int ret;
	conexiones *c = numcon(b->form->extraform);
	ret = fejecutaradio(b, ft);
	if (FORM(b)->nivel == NIVEL_BLOQUE && ret == 0) {
		ponindicadoresbloque(b);
		dr.pasaformaterm(c, 0);
	}
	return(ret);
}

static int fpulsateclasradio(bloques *b, ftrigers *ft)
{
	forms *f = b->form;
	conexiones *c;
	int nt;
	c = numcon(f->extraform);
	if (!c) return(-1);
	for (nt = 0; nt<ft->nparam; nt++) {
		int valor;
		valor = traducetecla(ft->param[nt]);
		if (valor == 0) valor = *ft->param[nt];
		encolateclaconexion(c, valor);
	}
	return(0);
}

int fmandaaradio(bloques *b, ftrigers *ft)
{
	forms *f = b->form;
	conexiones *conex;
	char destino[MAXCADENA];
	conex = numcon(f->extraform);
	if (conex == NULL) return(-1);
	dameparametro(b, ft, 0, V10CADENA, destino);
	v10sockprintf(conex->v10sock, "%s", destino);
	return(0);
}

int fcargaterminal(bloques *b, ftrigers *ft)
{
	forms *f = b->form;
	conexiones *c = numcon(f->extraform);
	strcpy(c->op.codope, direcncampo(b, ft->param[0]));
	RECselcodrecurso(c->rec.codrecurso, &c->rec);
	strcpy(c->rec.codope, c->op.codope);
	RECactualizacodope(&c->rec, NOVERIFICA);
	c->pideusr = OPVERIFICADO;
	USUselcodope(c->op.codope, &c->op);
	vduser = c->op;
	ponuserdb();
	ponrecurso(c->rec.codrecurso);
	f->act = LOADFRM;
	return(0);
}

int fdesconecta(conexiones *c)
{
	c->pideusr = OPPENDIENTE;
	rollback();
	logoutterminal(c);
	commit();
	return(0);
}

int fdesconectausuario(bloques *b, ftrigers *ft)
{
	forms *f = FORM(b);
	conexiones *c = numcon(f->extraform);
	fdesconecta(c);
	f->nivel = NIVEL_FORM;
	return(0);
}

int fhelpradio(bloques *b, ftrigers *ft)
{
	v10inputs *v = b->vi.act;
	fcampos *camp = v->trigerdatos;
	conexiones *c = numcon(b->form->extraform);
	char destino[MAXCADENA] = "\n\n";
	if (camp->tooltip) {
		sustituyevariables(b, camp->tooltip, destino + strlen(destino));
		strcat(destino, "\n");
	}
	if (b->online) strcat(destino, b->online);
	if (es_blanco(destino)) return(0);
	vmensajeradioc(c, 1, destino, NULL);
	c->rec.status = STRECMENSAJE;
	RECactualizastatus(&c->rec, NOVERIFICA);
	return(0);
}

static int fcargaform(bloques *b, ftrigers *ft)
{
	forms *f = b->form;
	conexiones *c = numcon(b->form->extraform);
	vdrecursos *rec = &c->rec;
	if (ft->nparam == 0) {
		ft->msg = "EL NOMBRE DE FORM A EJECUTAR ES OBLIGATORIO";
		return(-1);
	}
	if (!rec) return(-1);
	v10log(LOGNORMAL, "fcargarfrm - Inicio bloque %s recurso %s\n", ft->param[0], rec->codrecurso);
	rollback();
	if (NULL == ft->param[0])return(-1);
	strcpy(rec->npantalla, ft->param[0]);

	f->act = -3;
	f->nivel = NIVEL_FORM;
	v10log(LOGNORMAL, "fcargarfrm - Fin bloque %s recurso %s\n", ft->param[0], rec->codrecurso);

	return(0);
}
#define PLANIFICA "DECLARE RET NUMBER; BEGIN RET:=VDPLANMOV.ASIGNAMOVPERFIL(:CODRECURSO,:CODPERFIL); END;"
static int fcargaperfil(bloques *b, ftrigers *ft)
{
	forms *f = b->form;
	conexiones *c = numcon(b->form->extraform);
	vdrecursos *rec = &c->rec;
	vdperfiltareas pft;
	static v10cursors *v10planifica;
	int ret;
	if (ft->nparam == 0) {
		ft->msg = "EL NOMBRE DEL PERFIL A EJECUTAR ES OBLIGATORIO";
		return(-1);
	}
	if (v10planifica == NULL) {
		v10planifica = abrecursor(PLANIFICA);
	}
	if (!rec) return(-1);
	v10log(LOGNORMAL, "fcargarperfil - Inicio perfil %s recurso %s\n", ft->param[0], rec->codrecurso);
	if (NULL == ft->param[0]) return(-1);
	dameparametro(b, ft, 0, V10CADENA, rec->codperfil);
	ret = PERselcodperfil(rec->codperfil, &pft);
	if (ret == 0) {
		if (*pft.formplanif == 'N') {
			bindtodo(v10planifica, "CODRECURSO", rec->codrecurso, sizeof(rec->codrecurso), V10CADENA,
				"CODPERFIL", pft.codperfil, sizeof(pft.codperfil), V10CADENA,
				NULL);
			ret=ejecutacursor(v10planifica);
			if (ret == 0) commit();
			else rollback();
		}
		strcpy(rec->npantalla, pft.npantalla);
		f->act = -3;
		f->nivel = NIVEL_FORM;
		v10log(LOGNORMAL, "fcargarfrm - Fin bloque %s recurso %s\n", ft->param[0], rec->codrecurso);
	}
	else {
		v10log(LOGNORMAL, "fcargarfrm - No existe perfil %s recurso %s\n", ft->param[0], rec->codrecurso);
	}
	return(ret);
}

void declaratecladriver(int tec, int(*funcion)(conexiones *c))
{
	int nt;
	for (nt = 0; nt<dr.nteclas; nt++) {
		if (tec == dr.tec[nt].t) break;
	}
	dr.tec[nt].t = tec;
	dr.tec[nt].funcion = funcion;
	if (nt >= dr.nteclas) dr.nteclas++;
}

static int ftecleo(bloques *b, ftrigers *ft)
{
	v10inputs *v = b->vi.act;
	fcampos *camp = v->trigerdatos;
	int ret;
	conexiones *c = numcon(b->form->extraform);
	vdrecursos *rec = &c->rec;
	ret = *FSCAN(b, camp);
	if (ret) return(0);
	if ((*rec->tecleo = 'S')) return(0);
	return(-1);
}

static int fanalizaeanrad(bloques *b, ftrigers *f)
{
	int np;
	fcampos *c;
	int nc, scan;
	conexiones *con = numcon(b->form->extraform);
	nc = damecampo(b, f->param[0]);
	if (nc<0) {
		f->msg = "FANALIZAEAN- NO EXISTE ORIGEN";
		return(-1);
	}
	c = b->c + nc;
	scan = *FSCAN(b, c);
	if (c->tipo != V10CADENA) {
		f->msg = "FANALIZAEAN- ORIGEN DEBE SER CADENA";
		return(-1);
	}
	for (np = 1; np<f->nparam; np += 2) {
		int nc1;
		char cadena[MAXCADENA] = "";
		fcampos *campo;
		nc1 = damecampo(b, f->param[np + 1]);
		if (nc1<0) {
			f->msg = "FANALIZAEAN- DESTINO NO EXISTE";
			return(-1);
		}
		campo = b->c + nc1;
		if (damecampoean(direcncampo(b, f->param[0]), f->param[np], cadena) == 0) {
			a2bcampo(b, f->param[np + 1], cadena);
			*FSCAN(b, campo) = scan;
			if (campo->change) {
				*FERROR(b, campo) = ejecutatrigerradio(con, b, campo->change, PPOSTCHANGE, campo, 1);
			}
		}
	}
	return(0);
}

static int damenumerobloque(forms *f, char *nombre)
{
	unsigned nbloque;
	if (!isdigit(*nombre) && *nombre != '-') {
		for (nbloque = 0; nbloque<f->nbloques; nbloque++) {
			bloques *b1 = f->b[nbloque];
			if (strcmp(b1->fichero, nombre) == 0) return(nbloque);
		}
		return(nbloque);
	}
	return(atoi(nombre));
}

static int fposicionabloque(bloques *b, ftrigers *ft)
{
	forms *f = b->form;
	int nbloque;
	char nombre[MAXNOMBREV10];

	dameparametro(b, ft, 0, V10CADENA, nombre);
	nbloque = damenumerobloque(f, nombre);
	if (nbloque<0) {
		f->act = nbloque;
		f->nivel = NIVEL_FORM;
		return(0);
	}
	if (nbloque >= (int)f->nbloques) {
		v10log(LOGERROR, "fposicionabloque - ERROR: no se encuentra bloque %s en form %s\n", nombre, f->nombre);
		f->act = 0;
		return(-1);
	}
	f->nivel = NIVEL_FORM;
	f->act = nbloque;
	v10log(LOGNORMAL, "fposicionabloque - Fin bloque %s\n", f->b[f->act]->fichero);
	return(0);
}

static int flimpiabloque(bloques *b, ftrigers *ft)
{
	forms *f = b->form;
	bloques *b1 = b;
	v10log(LOGNORMAL, "flimpiabloque - Inicio bloque %s\n", b->nombre);
	if (ft->nparam >= 1) {
		unsigned nb = damenumerobloque(f, ft->param[0]);
		if (nb>f->nbloques || nb<0) {
			ft->msg = "Numero de bloque muy alto";
			return(-1);
		}
		b1 = f->b[nb];
	}
	pordefectoregistro(b1);
	b1->vi.act = b1->vi.prim;
	v10log(LOGNORMAL, "flimpiabloque - Fin bloque %s\n", b->nombre);
	return(0);
}

static int fpresentapantalla(bloques *b, ftrigers *ft)
{
	conexiones *con = numcon(b->form->extraform);
	dr.pasaformaterm(con, 0);
	return 0;
}


static int fprequery(bloques *b, ftrigers *ft)
{
    conexiones *c = numcon(b->form->extraform);
    if (ejecutatrigerradio(c, b, b->fprequery, PPREQUERY, NULL, 1)) return(-1);
    return(0);
}

void inittrigradio(void)
{
	inittriger();
	cambiafuntriger("FPULSATECLAS", fpulsateclasradio);
	cambiafuntriger("FEJECUTA", fejecutaradio);
	cambiafuntriger("FDESIGNACION", fdesignacionradio);
	declaratriger("FMANDAARADIO", fmandaaradio, NULL);
	declaratriger("FCARGATERMINAL", fcargaterminal, NULL);
	declaratriger("FCARGAFORM", fcargaform, NULL);
	declaratriger("FCARGAPERFIL", fcargaperfil, NULL);
	declaratriger("FHELPRADIO", fhelpradio, NULL);
	declaratriger("FANALIZAEANRAD", fanalizaeanrad, NULL);
	declaratriger("FPOSICIONABLOQUE", fposicionabloque, NULL);
	declaratriger("FLIMPIABLOQUE", flimpiabloque, NULL);
	declaratriger("FFUERZASCAN", ffuerzascan, NULL);
	declaratriger("FLEEARTICULO", fleearticulo, NULL);
    declaratriger("FDESCONECTAUSUARIO", fdesconectausuario, NULL);
    declaratriger("FPRESENTAPANTALLA", fpresentapantalla, NULL);
    declaratriger("FPREQUERY", fprequery, NULL);
	defineteclaformdef(F(1), "FHELPRADIO");
	declaratecladriver(esc, fdesconecta);
	inittriguser();
}


