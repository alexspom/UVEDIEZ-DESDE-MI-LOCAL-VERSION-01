/*
* Módulo : V10FORPARSEAUX.C
* Objeto:  Funciones auxiliares para del parse de formularios
*
*
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"
#include "v10forparseaux.h"
#include "v10parse.h"


forms *forparse;
bloques *bloqueparse;
fcampos *campoparse;
fbotones *botonparse;
formenus *formenu;
int defcolor = 0;
int protegidoform = -1;

char *(*extraparser)(bloques *b, char *funcion, char *param);
char *(*damecaracextracampo)(fcampos *campo);
char *(*damecaracextrabloque)(forms *f, bloques *b, int paso);
int(*damedefaulttabla)(bloques *b);
int(*funcionproteccion)(char *cadena);
int(*funcionparsecampo)(bloques *b, fcampos *c);
int(*funcionparsebloque)(bloques *b);
int(*funcionparsetecla)(bloques *b, fteclas *f, int protegido);
int(*funcionparsezoom)(formenus *m, opcionesmenu *op, int protegido);
int enbloque = 0;
int eszoom = 0;
int defcapitaliza = 0;

typedef struct {
    char nombre[MAXNOMBREV10];
    int tipo;
    int lon;
} camposextra;
static camposextra ce[CAMPOSEXTRA] = { { "MIROWID", V10CADENA, ROWIDLON },
{ "V10_COLOR", V10CADENA, MAXNOMBREV10 },
{ "V10ERROR", V10CADENA, MAXMSGV10 },
{ "V10ORAERR", V10LONG, sizeof(long)},
{ "V10EVAJAX", V10LONG, sizeof(long) } };

static void mirasitrad(char *fichero, char *texto)
{
    FILE *trad;
    char nombre[MAXPATH];
    int ch;
    if (es_blanco(idiomav10)) return;
    sprintf(nombre, "%s#%s", fichero, idiomav10);
    trad = fopenpath(nombre, "r");
    if (trad == NULL) return;
    while ((ch = fgetc(trad)) == '#') {
        while ((ch = fgetc(trad)) != EOF) if (ch == '\n') break;
    }
    *texto++ = (char)ch;
    while ((ch = fgetc(trad)) != EOF) *texto++ = (char)ch;
    *texto = 0;
    fclose(trad);
}

#define MAXDEFTECLA 100
static fteclas deftecla[MAXDEFTECLA];
static int ndeftecla;

static void finteclaformdef(void)
{
    int i;
    for (i = 0; i<ndeftecla; i++) liberatriger(deftecla[i].trig);
}

ftrigers *defineteclaformdef(int mitecla, char *ntriger)
{
    int i;
    ftrigers *ft;
    for (i = 0; i<ndeftecla; i++) if (deftecla[i].t == mitecla) break;
    if (i<ndeftecla) liberatriger(deftecla[i].trig);
    deftecla[i].t = mitecla;
    ft = dametriger(ntriger);
    if (ft == NULL) return(NULL);
    if (ndeftecla == 0) atexit(finteclaformdef);
    deftecla[i].trig = duplicatriger(NULL, ft);
    ft = deftecla[i].trig;
    if (i >= ndeftecla) ndeftecla++;
    return(ft);
}

void anadeparamtriger(ftrigers *ft, ...)
{
    int npar = 0, np;
    va_list arg;
    if (!ft) return;
    va_start(arg, ft);
    while (va_arg(arg, char *)) npar++;
    va_start(arg, ft);
    if (ft->nparam) {
        liberatrigermsg(ft);
    }
    ft->param = calloc(npar, sizeof(void *));
    ft->tipoparam = calloc(npar, sizeof(int));
    ft->nparam = npar;
    for (np = 0; np<npar; np++) {
        ft->param[np] = strdup(va_arg(arg, char *));
        ft->tipoparam[np] = PARAMCADENA;
    }
}

static void initv10forparseaux(void)
{
    static int init = 0;
    ftrigers *ft;
    if (init) return;
    ft = defineteclaformdef(F(11), "FPASAOLE");
    anadeparamtriger(ft, "Excel.Application", "0", NULL);
    ft = defineteclaformdef(F(12), "FPASAOLE");
    anadeparamtriger(ft, "Excel.Application", "1", NULL);
    ft = defineteclaformdef(S_F(11), "FPASACSV");
    anadeparamtriger(ft, "Excel.Application", "0", "FORMS.CSV", NULL);
    ft=defineteclaformdef(A_F(11),"FPASAAS");
    anadeparamtriger(ft,"Excel.Application","0","FORMS.XLSX",NULL);
    ft = defineteclaformdef(S_F(12), "FPASACSV");
    anadeparamtriger(ft, "Excel.Application", "1", "FORMS.CSV", NULL);
    init = 1;
}

int esta_protegido(char *cadena)
{
    if (funcionproteccion) return(funcionproteccion(cadena));
    return(1);
}

void quitacomillas(char **dest, char *ori)
{
    char *aux;
    *dest = strdup(ori + 1);
    while ((aux = strstr(*dest, "\\n")) != 0) {
        *aux = '\n'; strcpy(aux + 1, aux + 2);
    }
    (*dest)[strlen(*dest) - 1] = 0;
}

void damepostab(bloques *b, int x, int y, int *posx, int *posy, formtabs **ftab)
{
    int i;
    for (i = 0; i<b->nformtabs; i++) {
        formtabs *ft = b->ftab + i;
        if (y >= ft->posy && y <= ft->posy + ft->lony) {
            *posx = x;
            *posy = y - ft->posy;
            *ftab = ft;
            return;
        }
    }
    *posx = x;
    *posy = y;
    *ftab = NULL;
}

void fichero2vi(char *texto, v10dialogs *vi)
{
    int i;
    char *cadena;
    int maxlon = 0, numlin = 0;
    int v10dialogslon; /* longitud visible */
    char *donde;
    char *aux;
    char buffertrad[MAXCADENA * 4];
    char destino[MAXCADENA];
    strcpy(buffertrad, texto);
    mirasitrad(bloqueparse->fichero, buffertrad);
    cadena = buffertrad;
    aux = strchr(cadena, '\n');
    if (aux) *aux = 0;
    if (v10usaansi) {
        v10ansitooem(cadena, destino);
    } else strcpy(destino, cadena);
    vi->titulo = strdup(destino);
    if (aux) {
        cadena = aux + 1;
        *aux = '\n';
    } else  cadena += strlen(cadena);
    while (cadena) {
        aux = strchr(cadena, '\n');
        if (aux) *aux = 0;
        if (strncmp(cadena, "TAB=", 4) == 0) {
            if (bloqueparse->ftab == NULL) bloqueparse->ftab = calloc(MAXTABS, sizeof(formtabs));
            bloqueparse->ftab[bloqueparse->nformtabs].nombre = strdup(cadena + 4);
            bloqueparse->ftab[bloqueparse->nformtabs].posx = 0;
            bloqueparse->ftab[bloqueparse->nformtabs].posy = numlin;
            bloqueparse->ftab[bloqueparse->nformtabs].protegido = 0;
            bloqueparse->nformtabs++;
            if (aux) *aux = '\n';
            strcpy(cadena, aux + 1);
            continue;
        }
        if (maxlon<strlen(cadena)) maxlon = strlen(cadena);
        if (strchr(cadena, TERMINAVENTANA)) {
            v10dialogslon = (unsigned)(strchr(cadena, TERMINAVENTANA) - cadena) + 1;
            break;
        }
        numlin++;
        if (aux) {
            cadena = aux + 1;
            *aux = '\n';
        } else  cadena += strlen(cadena);
    }
    maxlon++;
    if ((donde = calloc(numlin, maxlon)) == 0L) final(("Sin memoria"));
    i = 0;
    cadena = buffertrad;
    aux = strchr(cadena, '\n');
    if (aux) *aux = 0;
    if (aux) {
        cadena = aux + 1;
        *aux = '\n';
    } else  cadena += strlen(cadena);
    while (cadena) {
        aux = strchr(cadena, '\n');
        if (aux) *aux = 0;
        if (strchr(cadena, TERMINAVENTANA)) break;
        if (v10usaansi) {
            v10ansitooem(cadena, destino);
        } else strcpy(destino, cadena);
        pad(destino, maxlon - 1);
        strcpy(donde + i*maxlon, destino);
        if (aux) {
            cadena = aux + 1;
            *aux = '\n';
        } else  cadena += strlen(cadena);
        i++;
    }
    vi->largo = maxlon - 1;
    vi->alto = numlin;
    if (v10dialogslon <= 1) v10dialogslon = maxlon - 1;
    if (v10dialogslon>COLUMNASPANTALLA - 2 && forparse->tipo == FWINDOWS) v10dialogslon = COLUMNASPANTALLA - 2;
    initvf(&vi->w, 1, 1, v10dialogslon, numlin, 1);
    interpretadialogo(vi, donde);
    for (i = 0; i<bloqueparse->nformtabs; i++) {
        formtabs *ft = bloqueparse->ftab + i;
        if (i<bloqueparse->nformtabs - 1) ft->lony = ft[1].posy - ft->posy;
        else ft->lony = numlin - ft->posy;
        if (bloqueparse->maxlontaby<ft->lony) bloqueparse->maxlontaby = ft->lony;
    }
    free(donde);
}

static char *defext(char *nombre, char *ext)
{
    if ((strchr(nombre, '.')) == NULL) strcat(nombre, ext);
    return(nombre);
}


static int camposvisiblesform(bloques *b)
{
    int ret = 0;
    int i;
    for (i = 0; i<b->ncamp; i++) {
        fcampos *c = b->c + i;
        if (c->oculto == 0) ret++;
    }
    return(ret);
}

static int enlaza_vi_bloque(bloques *b)
{
    int ncamp, nvis = 0;
    v10inputs *v = b->vi.prim;
    if (v == NULL) return(-1);
    for (ncamp = 0; ncamp<b->ncamp; ncamp++) {
        fcampos *c = b->c + ncamp;
        if (c->oculto) continue;
        nvis++;
        if (v>b->vi.ult) {
            mensajeparser("Pocos campos arriba hay %d abajo hay %d fichero %s", nvis - 1, camposvisiblesform(b), b->fichero);
            return(-1);
        }
        c->v = v;
        if (b->noenter) v->enter = 0;
        if (c->capitaliza == -1) {
            if (b->capitaliza == -1) c->capitaliza = defcapitaliza;
            else                c->capitaliza = b->capitaliza;
        }
        if (!esv10tiponum(v->tipo)) v->formato |= c->capitaliza;
        v->enter = c->enter;
        v->noinput = c->noinput;
        v->invisible = c->invisible;
        v->autoenter = c->autoenter;
        v->trigerdatos = c;
        c->tipo = v->tipo;
        c->lvar = v->lvar;
        c->format = v->formato;
        c->dec = v->dec;
        c->lon = tamv10tipo(c->tipo, v->lvar + 1);
        v++;
    }
    if (v <= b->vi.ult) {
        mensajeparser("Has pintado muchos campos. Abajo hay %d visibles en bloque %s", nvis, b->fichero);
        return(-1);
    }
    return(0);
}

static void tamano_bloque(bloques *b)
{
    int ncamp;
    unsigned tam;
    tam = ROWIDLON + sizeof(cabregs);
    for (ncamp = 0; ncamp<b->ncamp; ncamp++) {
        fcampos *c = b->c + ncamp;
        if (c->virtual == 0) {
          if (c->tipo != V10CADENA) {
	          int align;
	          align = tam%c->lon;
	          if (align) tam = tam - align + c->lon;
          }
            c->off = tam;
            tam += c->lon + NUMINDCAMPO*sizeof(int);
        }
    }
    b->tamano = tam;
    b->buffer = calloc(1, 2 * tam);
    b->ant = calloc(1, tam);
    b->bufuquery = calloc(1, tam);
}

static void tamano_form(forms *f)
{
    int ncamp;
    unsigned tam;
    if (f->modif) return;
    f->modif = 1;
    tam = 0;
    for (ncamp = 0; ncamp<f->ncamp; ncamp++) {
        fcampos *c = f->c + ncamp;
        if (c->virtual == 0) {
            c->off = tam;
            tam += c->lon + NUMINDCAMPO*sizeof(int);
        }
    }
    f->tam = tam;
    if (tam) {
        f->buffer = calloc(1, tam);
        f->ant = calloc(1, tam);
        f->bufuquery = calloc(1, tam);
    }
}

#define CSELTOOLTIP "SELECT COMMENTS FROM USER_COL_COMMENTS WHERE :TABLA=TABLE_NAME AND COLUMN_NAME=:CAMPO"
static void dametooltip(bloques *b, fcampos *c)
{
    static char mitooltip[MAXPATH], mitabla[MAXPATH], micampo[MAXPATH];
    static v10cursors *v10seltooltip;
    int ret;
    if (b->soloquery) return;
    if (c->tabla==0) return;
    if (v10seltooltip == NULL) {
        v10seltooltip = abrecursor(CSELTOOLTIP);
        definetodo(v10seltooltip, mitooltip, sizeof(mitooltip), V10CADENA, NULL);
        bindtodo(v10seltooltip, "TABLA",mitabla, sizeof(mitabla), V10CADENA,
                                "CAMPO",micampo, sizeof(micampo), V10CADENA, NULL);
    }
    strcpy(mitabla, b->nombre);
    strcpy(micampo, c->nombre);
    ret = ejefetchcursor(v10seltooltip);
    if (ret == 0 && !es_blanco(mitooltip)) {
        c->tooltip = strdup(mitooltip);
    }
}
static int prepara_campos(bloques *b)
{
    void **pcampos;
    v10dialogs *vi = &b->vi;
    tpixels *ptr;
    int ncamp;
    int visibles = 0, updatable = 0;
    int ancho, alto;
    ptr = vi->contenido;
    for (ancho = 0; ancho<vi->largo; ancho++) {
        for (alto = 0; alto<vi->alto; alto++) {
            ptr->c = vi->w.t.t[1];
            ptr++;
        }
    }
    for (ncamp = 0; ncamp<CAMPOSEXTRA; ncamp++) {
        fcampos *c = b->c + ncamp;
        c->tipo = ce[ncamp].tipo;
        strcpy(c->nombre, ce[ncamp].nombre);
        c->lon = ce[ncamp].lon;
        c->oculto = 1;
        c->virtual = 0;
        c->tabla = 0;
        c->noupdate = 1;
        c->b = b;
    }
    if (b->soloquery || b->norowid) b->c[0].tabla = 0;
    else           b->c[0].tabla = 1;
    if (b->form->tipo != FINTERFASE) if (enlaza_vi_bloque(b)) return(-1);
    for (ncamp = 0; ncamp<b->ncamp; ncamp++) {
        fcampos *c = b->c + ncamp;
        if (c->titulo && c->v && !c->invisible) b->wtitulos = 1;
        if (c->virtual) {
            int ncamp;
            fcampos *cp;
            if (b->padre == NULL) {
                if ((ncamp = damecampoform(b->form, c->nvirtual)) == -1) {
                    mensajeparser("Campo virtual %s en bloque no hijo %s", c->nombre, b->fichero);
                    return(-1);
                } else {
                    cp = b->form->c + ncamp;
                }
            } else {
                ncamp = damecampo(b->padre, c->nvirtual);
                if (ncamp<0) {
                    mensajeparser("No existe campo %s en bloque %s", c->nvirtual, b->fichero);
                    return(-1);
                }
                cp = b->padre->c + ncamp;
            }
            c->tipo = cp->tipo;
            c->lon = cp->lon;
            c->lvar = cp->lvar;
            c->off = ncamp;
        }
        if (c->noupdate == -1) {
            if (c->tabla) c->noupdate = b->noupdate;
            else       c->noupdate = 0;
        } else if (c->noupdate == 0 && c->tabla) updatable = 1;
        if (c->oculto && c->lon == 0) {
            mensajeparser("campo oculto sin formato %s en bloque %s", c->nombre, b->fichero);
            return(-1);
        }
        if (c->convfrombd || c->conv2bd) c->datoconv = calloc(1, c->lon);
        if (es_blanco(c->tooltip)) {
            dametooltip(b, c);
        }
    }
    if (updatable == 1) b->noupdate = 0;
    tamano_bloque(b);
    if (b->form->tipo != FINTERFASE) {
        int i;
        if ((pcampos = calloc(250, sizeof(pcampos))) == 0L) final(("Sin memoria"));
        for (ncamp = 0; ncamp<b->ncamp; ncamp++) {
            fcampos *c = b->c + ncamp;
            if (c->oculto) continue;
            pcampos[visibles++] = direccampo(b, ncamp);
        }
        pcampos[visibles] = 0L;
        pasignadialog(&b->vi,pcampos);
        for (i = 0; i<b->ncamp; i++) {
            fcampos *fc = b->c + i;
            int x, y;
            if (fc->v == NULL) continue;
            damepostab(b, fc->v->posx, fc->v->posy, &x, &y, &fc->ftab);
        }
        free(pcampos);
    }
    return(0);
}

static void reajustacontenido(bloques *b, int total)
{
    v10dialogs *vi = &b->vi;
    colventanas color = vi->w.t.t[CNORMAL];
    vi->contenido = realloc(vi->contenido, (vi->largo)*(total)*sizeof(tpixels));
    if (total>vi->alto) {
        int lin, col;
        for (lin = vi->alto; lin<total; lin++) {
            for (col = 0; col<vi->largo; col++) {
                vi->contenido[lin*(vi->largo) + col].ch = ' ';
                vi->contenido[lin*(vi->largo) + col].c = color;
            }
        }
    }
    vi->alto = total;
    b->vi.w.y2 = b->vi.w.y1 + total - 1;
}

static void calcula_margenes(bloques *b)
{
    int total;
    virtsels *s;
    int reajusta;
    int margens, lin_reg, margend, margeni;
    if (b->vi.w.x2 >= COLUMNASPANTALLA - 1) b->vi.w.x2 = COLUMNASPANTALLA - 2;
    b->vi.reajusta = reajustapagina;
    b->vi.reajdato = b;
    margend = WANCHO(&b->vi.w);
    s = calloc(1, sizeof(virtsels));
    if (b->vi.prim->posy == b->vi.ult->posy) {
        margens = b->vi.prim->posy;
        lin_reg = b->vi.ult->posy - b->vi.prim->posy + 1;
    } else {
        margens = 0;
        lin_reg = b->vi.ult->posy + 1;
    }
    if (b->regpag == 0) {
        total = WALTO(&b->vi.w) - margens;
        b->regpag = total / lin_reg;
        reajusta = 0;
    } else {
        total = b->regpag*lin_reg + margens;
        reajusta = 1;
    }
    if (defcolor == 0) {
        if (eszoom == 0) {
            if (b->regpag == 1) poncolorbloque(b, "MONOREG");
            else          poncolorbloque(b, "MULTIREG");
        } else {
            if (b->regpag == 1) poncolorbloque(b, "MONOZOO");
            else          poncolorbloque(b, "MULTIZOO");
        }
    }
    if (reajusta) reajustacontenido(b, total);
    margeni = total - (total / lin_reg)*lin_reg;
    initselec(s, 0, margens, 0, margeni, 1, &b->vi.w, 1, lin_reg, 1, margend, b->vi.titulo, STDpintapaginabloque, teclapaginabloque, 0, b);
    s->hayinput = 1;
    b->s = s;
    b->vi.despy = 0;
}

int terminabloque(bloques *b)
{
    tamano_form(b->form);
    if (b->ncur) b->fcur = realloc(b->fcur, b->ncur*sizeof(fcursores));
    else {
        free(b->fcur);
        b->fcur = NULL;
    }
    if (b->vi.w.y1<2) {
        b->vi.w.y1++;
        b->vi.w.y2++;
    }
    if (b->ncamp == 0) {
        mensajeparser("Forms sin campos %s", b->fichero);
        return(-1);
    }
    b->c = realloc(b->c, b->ncamp*sizeof(fcampos));
    if (b->nteclas) {
        b->teclas = realloc(b->teclas, b->nteclas*sizeof(fteclas));
    } else {
        free(b->teclas);
        b->teclas = NULL;
    }
    if (b->ntrigers) {
        b->ftriger = realloc(b->ftriger, b->ntrigers*sizeof(ftrigers *));
    } else {
        free(b->ftriger);
        b->ftriger = NULL;
    }
    /*  if (b->numbotones) {
    b->fb=realloc(b->fb,b->numbotones*sizeof(fbotones));
    } else {
    free(b->fb);
    b->fb=NULL;
    }*/
    /*  if (b->numbotoneras) {
    b->fbot=realloc(b->fbot,b->numbotoneras*sizeof(fbotoneras));
    } else {
    free(b->fbot);
    b->fbot=NULL;
    }*/
    if (b->nbframesfile) {
        b->framesfile = realloc(b->framesfile, b->nbframesfile*sizeof(fframes));
    } else {
        free(b->framesfile);
        b->framesfile = NULL;
    }

    if (b->nbstats) {
        b->stats = realloc(b->stats, b->nbstats*sizeof(fstats));
    } else {
        free(b->stats);
        b->stats = NULL;
    }

    if (b->nbajax) {
        int na;
        b->ajax = realloc(b->ajax, b->nbajax*sizeof(v10ajax));
        for (na = 0; na < b->nbajax; na++) b->ajax[na].b = b;
    } else {
        free(b->ajax);
        b->ajax = NULL;
    }

    if (b->nbcomphtml) {
        b->comphtml = realloc(b->comphtml, b->nbcomphtml*sizeof(v10comphtml));
    } else {
        free(b->comphtml);
        b->comphtml = NULL;
    }

    if (v10versionweb && b->wregpag && b->regpag>1) b->regpag = b->wregpag;
    if (b->form->tipo != FINTERFASE) calcula_margenes(b);
    if (b->norowid) {
        b->noinsert = 1;
        b->noupdate = 1;
        b->nodelete = 1;
        b->nolock = 1;
    }
    if (prepara_campos(b)) return(-1);
    if (b->form->tipo == FWINDOWS) abreficheroaux(b);
    pordefectoregistro(b);
    return(0);
}

void tratadefbloque(char *nombre)
{
    int nt = 0;
    if (forparse->tipo != FINTERFASE) lexbegin(SPINTADO);
    bloqueparse = creabloque();
    forparse->b[forparse->nbloques] = bloqueparse;
    bloqueparse->c = calloc(MAXCAMPOS, sizeof(fcampos));
    bloqueparse->teclas = calloc(MAXFTECLAS, sizeof(fteclas));
    bloqueparse->ftriger = calloc(MAXFTRIGERS, sizeof(ftrigers *));
    bloqueparse->fb = calloc(MAXBOTONES, sizeof(fbotones));
    bloqueparse->fbot = calloc(MAXBOTONERAS, sizeof(fbotoneras));
    bloqueparse->framesfile = calloc(MAXBOTONERAS, sizeof(fframes));
    bloqueparse->stats = calloc(MAXSTATS, sizeof(fstats));
    bloqueparse->ajax = calloc(MAXAJAX, sizeof(v10ajax));
    bloqueparse->comphtml = calloc(MAXCOMPHTML, sizeof(v10comphtml));
    bloqueparse->nbstats = 0;
    bloqueparse->nbframesfile = 0;
    bloqueparse->nbframes = 0;
    bloqueparse->nbajax = 0;
    bloqueparse->nbcomphtml = 0;
    if (forparse->tipo == FWINDOWS) initv10forparseaux();
    for (nt = 0; nt<ndeftecla; nt++) {
        bloqueparse->teclas[nt].t = deftecla[nt].t;
        bloqueparse->teclas[nt].trig = duplicatriger(bloqueparse, deftecla[nt].trig);
    }
    bloqueparse->fcur = calloc(MAXFCURSORES, sizeof(fcursores));
    bloqueparse->ncamp = CAMPOSEXTRA;
    strcpy(bloqueparse->fichero, nombre);
    if (forparse->tipo != FINTERFASE) defext(bloqueparse->fichero, ".PAN");
    bloqueparse->form = forparse;
    bloqueparse->capitaliza = -1;
    enbloque = 1;
    defcolor = 0;
    bloqueparse->nteclas = nt;
}

void eliminaretornos(char *cadena)
{
    char *aux;
    while ((aux = strchr(cadena, '\n')) != NULL) {
        char *prin = aux + 1;
        while (*prin == ' ' && prin[1] == ' ') prin++;
        strcpy(aux, prin);
    }
}



void yyerror(char *msg)
{
    char cadena[100];
    lexerror(cadena);
    v10log(1, "%s error %s\n", cadena, msg);
    mensajeparser("%s error %s", cadena, msg);
}

static forms *leepan(char *nombre)
{
    if (initlex(nombre)) {
        liberaform(forparse);
        forparse = NULL;
        bloqueparse = NULL;
        campoparse = NULL;
        enbloque = 0;
        return(NULL);
    }
    lexbegin(SPINTADO);
    tratadefbloque(nombre);
    if (yyparse() != 0) {
        terminalex();
        liberaform(forparse);
        forparse = NULL;
        bloqueparse = NULL;
        campoparse = NULL;
        enbloque = 0;
        return(NULL);
    }
    return(forparse);
}

static forms *leeformex(char *nombre, char *opciones, int tipo)
{
    char nombrecompleto[MAXPATH];
    int soloconsulta = 0;
    FILE *test;
    int protegido = protegidoform;
    enbloque = 0;
    if (opciones) {
        strmay(opciones);
        soloconsulta = *opciones == 'N' ? 1 : 0;
        if (*opciones == 'P') {
            if (isdigit(opciones[1])) protegidoform = opciones[1] - '0';
            else                   protegidoform = 1;
        }
    }
    if (protegido>protegidoform) protegidoform = protegido;
    forparse = calloc(1, sizeof(forms));
    forparse->tipo = tipo;
    forparse->c = calloc(MAXCAMPOS, sizeof(fcampos));
    strcpy(forparse->nombre, nombre);
    forparse->act = 0;
    initvn(&forparse->wmensaje, 0, LINEASPANTALLA - 3, COLUMNASPANTALLA - 1, LINEASPANTALLA - 3, "MENSAJE");
    forparse->sucio = 0;
    strcpy(nombrecompleto, nombre);
    defext(nombrecompleto, ".FRM");
    test = fopenpath(nombrecompleto, "r");
    if (test == NULL) {
        strcpy(nombrecompleto, nombre);
        defext(nombrecompleto, ".PAN");
        forparse = leepan(nombrecompleto);
    } else {
        fclose(test);
        if (initlex(nombrecompleto)) {
            liberaform(forparse);
            forparse = NULL;
            bloqueparse = NULL;
            campoparse = NULL;
            enbloque = 0;
        }
        v10log(LOGNORMAL, "Empiezo a leer forms %s\n", nombrecompleto);
        lexbegin(0);
        if (yyparse() != 0) {
            terminalex();
            liberaform(forparse);
            forparse = NULL;
            bloqueparse = NULL;
            campoparse = NULL;
            enbloque = 0;
        }
        v10log(LOGNORMAL, "Termino parse forms %s\n", nombrecompleto);
    }
    protegidoform = protegido;
    if (forparse) {
        if (soloconsulta) {
            int i;
            for (i = 0; i<forparse->nbloques; i++) {
                bloques *b = forparse->b[i];
                b->noupdate = 1;
                b->nodelete = 1;
                b->noinsert = 1;
                b->nocommit = 1;
                b->nolock = 1;
            }
        }
        if (forparse->ncamp == 0) {
            free(forparse->c);
            forparse->c = NULL;
        } else {
            forparse->c = realloc(forparse->c, forparse->ncamp*sizeof(fcampos));
        }
        tamano_form(forparse);
        forparse->modif = 0;
    }

    return(forparse);
}

forms *leeformcadena(char *nombre, char *cadena, int tipo)
{
    enbloque = 0;
    forparse = calloc(1, sizeof(forms));
    forparse->tipo = tipo;
    forparse->c = calloc(MAXCAMPOS, sizeof(fcampos));
    strcpy(forparse->nombre, nombre);
    forparse->act = 0;
    initvn(&forparse->wmensaje, 0, LINEASPANTALLA - 3, COLUMNASPANTALLA - 1, LINEASPANTALLA - 3, "MENSAJE");
    forparse->sucio = 0;
    if (initlexcadena(cadena)) {
        liberaform(forparse);
        forparse = NULL;
        bloqueparse = NULL;
        campoparse = NULL;
        enbloque = 0;
    }
    lexbegin(0);
    if (yyparse() != 0) {
        terminalex();
        liberaform(forparse);
        forparse = NULL;
        bloqueparse = NULL;
        campoparse = NULL;
        enbloque = 0;
    }
    if (forparse) {
        if (forparse->ncamp == 0) {
            free(forparse->c);
            forparse->c = NULL;
        } else {
            forparse->c = realloc(forparse->c, forparse->ncamp*sizeof(fcampos));
        }
        tamano_form(forparse);
        forparse->modif = 0;
    }
    return(forparse);
}

forms *leeform(char *nombre, char *opciones)
{
    forms *ret;
    ret = leeformex(nombre, opciones, FWINDOWS);
    return(ret);
}

forms *leeformtelnet(char *nombre, char *opciones)
{
    forms *ret;
    ret = leeformex(nombre, opciones, FTELNET);
    return(ret);
}

forms *leeforminter(char *nombre, char *opciones)
{
    forms *ret;
    ret = leeformex(nombre, opciones, FINTERFASE);
    return(ret);
}


formenus *leemenu(bloques *b, char *nombre)
{
    if (initlex(nombre)) return(NULL);
    formenu = calloc(1, sizeof(formenus));
    bloqueparse = b;
    formenu->titulo = strdup(nombre);
    formenu->b = b;
    formenu->op = calloc(MAXOPMENUS, sizeof(opcionesmenu));
    lexbegin(SOPMENU);
    if (yyparse() != 0) {
        terminalex();
        liberaforcontext(formenu);
        return(NULL);
    }
    return(formenu);
}


ftrigers *dametrigerdll(char *libreria, char *funcion)
{
    void *fun;
    ftrigers *ft;
    fun = damefundll(libreria, funcion);
    if (fun == NULL) return(NULL);
    ft = calloc(1, sizeof(ftrigers));
    ft->nombre = strdup(funcion);
    ft->fun = fun;
    return(ft);
}

