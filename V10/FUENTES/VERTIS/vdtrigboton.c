#include "vdform.h"

//#define PBOTON     20000

static void liberaboton(fbotones *b)
{
    if (b->grupo) free(b->grupo);
    free(b->nombre);
    free(b->texto);
    free(b->image);
    free(b->tooltip);
    b->grupo = b->nombre = b->texto = b->image = b->tooltip = NULL;
}

static int damepostecla(bloques *b, int tecla) {
    int i;
    for (i = 0; i<b->nteclas; i++)
        if (b->teclas[i].t == tecla) return(i);
    return(-1);
}

static void liberatecla(fteclas *t)
{
    t->t = 0;
    if (t->trig)		free(t->trig);
    if (t->trigpre)		free(t->trigpre);
    if (t->trigpost)	free(t->trigpost);
    t->trig = t->trigpre = t->trigpost = NULL;
    t->b = NULL;
}

static void eliminabotones(bloques *b, char *grupo, int teclas)
{
    int i, j;
    int nb = 0, nbinicio = -1, nbfinal = 0, nbgrupo = 0;
    int nteclainicio = -1, nteclafinal = 0;

    // busca el primer y ultimo boton del grupo (siempre van en correlativo)
    for (i = 0; i<b->numbotones; i++) {
        if (b->fb[i].grupo && !strcmp(b->fb[i].grupo, grupo)) {
            if (nbinicio == -1) nbinicio = i;
        } else { // salto de grupo
            if (nbinicio>-1 && nbfinal == 0) nbfinal = i - 1;
        }
    }
    if (nbinicio>-1 && nbfinal == 0) nbfinal = b->numbotones - 1;

    if (nbfinal == 0)  return;
    nbgrupo = (nbfinal - nbinicio) + 1;
    if (nbgrupo == 0) return; // no ha encontrado botón del grupo
    // las teclas del grupo tb se habran definido en correlativo
    if (teclas) {
        nteclainicio = damepostecla(b, b->fb[nbinicio].tecla);
        nteclafinal = damepostecla(b, b->fb[nbfinal].tecla);
    }
    /* libera los botones */
    for (i = nbinicio; i <= nbfinal; i++) liberaboton(b->fb + i);
    /* libera las teclas */
    if (nteclainicio>0) for (i = nteclainicio; i <= nteclafinal; i++) liberatecla(b->teclas + i);

    b->numbotones = b->numbotones - nbgrupo;
    if (nteclainicio>0 && teclas) {
        if (nbgrupo == b->nteclas) { // se han liberado todas las teclas
            free(b->teclas);
            b->teclas = NULL;
            b->nteclas = 0;
        } else {
            fteclas *teclasaux;
            int totalteclas = b->nteclas - nbgrupo;
            teclasaux = calloc(totalteclas, sizeof(fteclas));
            j = 0;
            for (i = 0; i<b->nteclas; i++) { // paso solo las teclas que no he liberado
                if (b->teclas[i].t) teclasaux[j++] = b->teclas[i];
            }
            memset(b->teclas, 0, b->nteclas*sizeof(fteclas));
            free(b->teclas);
            b->teclas = teclasaux;
            b->nteclas = totalteclas;
        }
    }
}


int fcalculaboton(bloques *b, ftrigers *ft)
{
    char *destino;
    int modif, error = 0;
    destino = direcncampo(b, ft->param[1]);
    modif = strcmp(destino, ft->param[0]);
    strcpy(destino, ft->param[0]);
    if (modif) {
        fcampos *c = b->c + damecampo(b, ft->param[1]);
        if (c->change) {
            b->form->cinput = c;
            *FERROR(b, c) = ejecutaftriger(b, PPOSTCHANGE, c->change, c);
            if (*FERROR(b, c)) error = *FERROR(b, c);
        }
    }
    return error;
}

int fbotoneradummy(bloques *b, ftrigers *ft) {
    return(0);
}

int fsigboton(bloques *b, ftrigers *ft)
{
    char cpboton[MAXCADENA];
    int regx, *pboton;
    dameparametro(b, ft, 0, V10CADENA, cpboton);
    dameparametro(b, ft, 1, V10LONG, &regx);
    pboton = direcncampo(b, cpboton);
    *pboton = (*pboton) + regx;
    ejecutaftriger(b, PPREREGISTRO, b->fpreregistro, NULL);
    return 0;
}

int fantboton(bloques *b, ftrigers *ft)
{
    char cpboton[MAXCADENA];
    int regx, *pboton;
    dameparametro(b, ft, 0, V10CADENA, cpboton);
    dameparametro(b, ft, 1, V10LONG, &regx);
    pboton = direcncampo(b, cpboton);
    *pboton = (*pboton) - regx;
    ejecutaftriger(b, PPREREGISTRO, b->fpreregistro, NULL);
    return 0;
}

void lldeclarabotonex(bloques *b, fbotones *fb, char *grupo, char *nombre, char *texto, char *tooltip, int mitecla, int posx, int posy, int lonx, int lony, char *estilocss, char *includecss, char *imagen)
{
    memset(fb, 0, sizeof(fbotones));
    fb->grupo = strdup(grupo);
    fb->nombre = strdup(nombre);
    fb->texto = strdup(texto);
    fb->image = strdup(imagen);
    fb->tooltip = strdup(tooltip);
    fb->tecla = mitecla;
    fb->posx = posx;
    fb->posy = posy;
    fb->lonx = lonx;
    fb->lony = lony;
    if (*estilocss) sprintf(fb->estilocss, "%s", estilocss);
    if (*includecss) sprintf(fb->includecss, "%s", includecss);
}

static void lldeclaraboton(bloques *b, fbotones *fb, char *grupo, char *nombre, char *texto, char *tooltip, int mitecla, int posx, int posy,
                           int lonx, int lony, char *estilocss, char *includecss)
{
    lldeclarabotonex(b, fb, grupo, nombre, texto, tooltip, mitecla, posx, posy, lonx, lony, estilocss, includecss, "NO");
}

int fcreaboton(bloques *b, ftrigers *ft)
{
    int px, py, lonx, lony, tecla;
    char nombrebot[MAXNOMBREV10];
    char estilocss[MAXNOMBREV10] = "", includecss[MAXNOMBREV10] = "";
    dameparametro(b, ft, 0, V10CADENA, nombrebot);
    eliminabotones(b, nombrebot, 0);
    dameparametro(b, ft, 1, V10LONG, &px);
    dameparametro(b, ft, 2, V10LONG, &py);
    dameparametro(b, ft, 3, V10LONG, &lonx);
    dameparametro(b, ft, 4, V10LONG, &lony);
    dameparametro(b, ft, 5, V10LONG, &tecla);
    dameparametro(b, ft, 6, V10CADENA, estilocss);
    dameparametro(b, ft, 7, V10CADENA, includecss);
    // if (b->fb) b->fb = realloc(b->fb, (b->numbotones + 1)*sizeof(fbotones));
    lldeclaraboton(b, b->fb + b->numbotones, nombrebot, nombrebot, nombrebot, nombrebot, tecla, px, py, lonx, lony, estilocss, includecss);
    b->numbotones++;
    return(0);
}

int fcreabotonex(bloques *b, ftrigers *ft)
{
    int px, py, lonx, lony, tecla;
    char grupo[MAXPATH], nombrebot[MAXPATH], imagen[MAXPATH];
    char estilocss[MAXPATH] = "", includecss[MAXPATH] = "";
    char borrar[MAXPATH]="";
    dameparametro(b, ft, 0, V10CADENA, grupo);
    dameparametro(b, ft, 1, V10CADENA, nombrebot);
    dameparametro(b, ft, 2, V10CADENA, imagen);
    dameparametro(b, ft, 3, V10LONG, &px);
    dameparametro(b, ft, 4, V10LONG, &py);
    dameparametro(b, ft, 5, V10LONG, &lonx);
    dameparametro(b, ft, 6, V10LONG, &lony);
    dameparametro(b, ft, 7, V10LONG, &tecla);
    dameparametro(b, ft, 8, V10CADENA, estilocss);
    dameparametro(b, ft, 9, V10CADENA, includecss);
    dameparametro(b, ft, 10, V10CADENA, borrar);
    if (*borrar!='N') eliminabotones(b, grupo, 0);
    //  if (b->fb) b->fb = realloc(b->fb, (b->numbotones + 1)*sizeof(fbotones));
    lldeclarabotonex(b, b->fb + b->numbotones, grupo, nombrebot, nombrebot, nombrebot, tecla, px, py, lonx, lony, estilocss, includecss, imagen);
    b->numbotones++;
    return(0);
}

int fcreabotones(bloques *b, ftrigers *ft)
{
    int ret, i, tecbase, offx, offy;
    int PBOTON = 20000;
    int pboton = 0, maxboton = 20;
    char estilocss[MAXNOMBREV10] = "", includecss[MAXNOMBREV10] = "", ncursor[MAXNOMBREV10], campoorigen[MAXNOMBREV10], campotool[MAXNOMBREV10], campodestino[MAXNOMBREV10];
    int nbot = 0, nbpan = 0;
    int px, py, lonx, lony, regx, maxy, sigbot;
    char grupo[MAXNOMBREV10], nboton[MAXBOTONES][MAXNOMBREV10], tboton[MAXBOTONES][MAXPATH], cpboton[MAXNOMBREV10];
    char triger[MAXNOMBREV10];

    dameparametro(b, ft, 0, V10CADENA, grupo);
    eliminabotones(b, grupo, 1);


    dameparametro(b, ft, 1, V10CADENA, ncursor);
    dameparametro(b, ft, 2, V10CADENA, cpboton);
    dameparametro(b, ft, 5, V10CADENA, campodestino);
    dameparametro(b, ft, 6, V10LONG, &px);
    dameparametro(b, ft, 7, V10LONG, &py);
    dameparametro(b, ft, 8, V10LONG, &lonx);
    dameparametro(b, ft, 9, V10LONG, &lony);
    dameparametro(b, ft, 10, V10LONG, &regx);
    dameparametro(b, ft, 11, V10LONG, &maxy);
    dameparametro(b, ft, 12, V10LONG, &offx);
    dameparametro(b, ft, 13, V10LONG, &offy);
    dameparametro(b, ft, 14, V10LONG, &PBOTON);
    dameparametro(b, ft, 15, V10CADENA, estilocss);
    dameparametro(b, ft, 16, V10CADENA, includecss);
    dameparametro(b, ft, 16, V10CADENA, triger);
    if (es_blanco(triger)) strcpy(triger, "FCALCULABOTON");

    ret = ejecutafcursor(b, ncursor);
    pboton = *(long *)direcncampo(b, cpboton);
    sigbot = 0;

    while (ret == 0) {
        if (nbot >= pboton && nbot <= pboton + maxboton) {
            dameparametro(b, ft, 3, V10CADENA, campoorigen);
            dameparametro(b, ft, 4, V10CADENA, campotool);
            strcpy(nboton[nbpan], campoorigen);
            strcpy(tboton[nbpan], campotool);
            nbpan++;
            if (nbpan >= maxy*regx) {
                sigbot = 1;
                break;
            }
        }
        nbot++;
        ret = fetchfcursor(b, ncursor);
    }


    if (nbpan) { // se deben  generar botones en la pantalla
        int totalbotones = b->numbotones + nbpan, totalteclas = b->nteclas + nbpan;
        if (pboton>0) { totalbotones++; totalteclas++; }
        if (sigbot>0) { totalbotones++; totalteclas++; }
        //   if (b->fb) b->fb = realloc(b->fb, (totalbotones)*sizeof(fbotones));
        else       b->fb = calloc(totalbotones, sizeof(fbotones));
        if (b->teclas) b->teclas = realloc(b->teclas, (totalteclas)*sizeof(fteclas));
        else           b->teclas = calloc(totalteclas, sizeof(fteclas));

        // reg, numero del nuevo boton dentro de la lista de nuevos botones
        tecbase = PBOTON + 2;
        for (i = b->numbotones; i<b->numbotones + nbpan; i++) {
            fbotones *fb = b->fb + i;
            int reg = i - b->numbotones;
            lldeclaraboton(b, fb, grupo, nboton[reg], nboton[reg], tboton[reg], tecbase + (i - b->numbotones), px + (reg%regx)*(lonx + offx), py + (reg / regx)*(lony + offy), lonx, lony, estilocss, includecss);
        }

        for (i = b->nteclas; i<b->nteclas + nbpan; i++) {
            memset(b->teclas + i, 0, sizeof(fteclas));
            b->teclas[i].t = tecbase + (i - b->nteclas);
            b->teclas[i].b = b;
            b->teclas[i].trig = duplicatriger(b, dametriger(triger));
            anadeparamtriger(b->teclas[i].trig, nboton[i - b->nteclas], campodestino, NULL);
        }

        if (pboton>0) {
            char nombreant[MAXNOMBREV10] = "", tooltipant[MAXNOMBREV10] = "";
            sprintf(nombreant, "Ant %s", grupo);
            sprintf(tooltipant, "Anterior %s", grupo);

            lldeclaraboton(b, b->fb + b->numbotones + nbpan, grupo, nombreant, "<< Ant", tooltipant, tecbase - 2, px, py + maxy*(lony + offy), lonx, lony, estilocss, includecss);
            memset(b->teclas + i, 0, sizeof(fteclas));
            b->teclas[i].t = tecbase - 2;
            b->teclas[i].b = b;
            b->teclas[i].trig = duplicatriger(b, dametriger("FBOTONERADUMMY"));
            b->teclas[i].trigpost = duplicatriger(b, dametriger("FANTBOTON"));
            anadeparamtriger(b->teclas[i].trigpost, cpboton, ft->param[10], NULL);
            b->numbotones++;
            b->nteclas++;
            i++;
        }
        if (sigbot>0) {
            char nombresgte[MAXNOMBREV10] = "", tooltipsgte[MAXNOMBREV10] = "";
            sprintf(nombresgte, "Sig %s", grupo);
            sprintf(tooltipsgte, "Siguiente %s", grupo);

            lldeclaraboton(b, b->fb + b->numbotones + nbpan, grupo, nombresgte, "Sig >>", tooltipsgte, tecbase - 1, px + (regx - 1)*(lonx + offx), py + maxy*(lony + offy), lonx, lony, estilocss, includecss);
            memset(b->teclas + i, 0, sizeof(fteclas));
            b->teclas[i].t = tecbase - 1;
            b->teclas[i].b = b;
            b->teclas[i].trig = duplicatriger(b, dametriger("FBOTONERADUMMY"));
            b->teclas[i].trigpost = duplicatriger(b, dametriger("FSIGBOTON"));
            anadeparamtriger(b->teclas[i].trigpost, cpboton, ft->param[10], NULL);
            b->numbotones++;
            b->nteclas++;
        }
        b->numbotones += nbpan;
        b->nteclas += nbpan;
    }
    return(0);
}

int fborrabotones(bloques *b, ftrigers *ft)
{
    char grupo[MAXNOMBREV10] = "";
    int eliminar = 1;
    dameparametro(b, ft, 0, V10CADENA, grupo);
    dameparametro(b, ft, 1, V10LONG, &eliminar);
    eliminabotones(b, grupo, eliminar);
    return(0);
}


void inittrigboton(void)
{
    declaratriger("FCREABOTONES", fcreabotones, NULL);
    declaratriger("FCREABOTON", fcreaboton, NULL);
    declaratriger("FCREABOTONEX", fcreabotonex, NULL);
    declaratriger("FCALCULABOTON", fcalculaboton, NULL);
    declaratriger("FSIGBOTON", fsigboton, NULL);
    declaratriger("FANTBOTON", fantboton, NULL);
    declaratriger("FBORRABOTONES", fborrabotones, NULL);
    declaratriger("FBOTONERADUMMY", fbotoneradummy, NULL);
}