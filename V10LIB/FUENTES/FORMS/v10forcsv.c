/*
* M�dulo : V10FOROLE.C
* Objeto:  Interfase de FORMS con EXCEL
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"


#define MAXOLECOLS 400
typedef struct {
          fcampos *c;
          char *nombreusuario;
        } olecols;

static olecols col[MAXOLECOLS];
static int ncol;

static char nomficherocsv[MAXPATH]="",nomcsvsinruta[MAXPATH]="";



static int pasacsvbloque(bloques *b,FILE *salida,int hijos,int *fila,int primero,int copiar);

static int pasacsvunregistro(bloques *b,FILE *salida,int hijos,int *fila,int primero,int copiar)
{
    int nb;
    int i=0;
    int nc;
    int ncolreal=0;
    forms *f=FORM(b);
    for (nc=0;nc<ncol;nc++) {
        int numc=damecampo(b,col[nc].c->nombre);
        fcampos *c;
        if (numc==-1) continue;
        if (b->c+numc!=col[nc].c) continue;
        c=b->c+numc;
        if (primero==0 && c->virtual) continue;
        ncolreal++;
    }
    for (nc=0;nc<ncol;nc++) {
        int numc;
        void *dir;
        fcampos *c;
        if (col[nc].c==NULL) continue;
        numc=damecampo(b,col[nc].c->nombre);
        if (numc==-1) continue;            
        if (b->c+numc!=col[nc].c) continue;
        c=b->c+numc;
        if (primero==0 && c->virtual) continue;
        dir=direcncampo(b,col[nc].c->nombre);
        i++;
        switch (col[nc].c->tipo) {
          case  V10FECHA:{char mifecha[20];
                      jul2a(*(v10dates *)dir,"DD-MM-Y.YY",mifecha);
                      fprintf(salida,"%s;",mifecha);
                      break;
                     }
          case V10LONG:fprintf(salida,"%ld;",*(long *)dir);
                      break;
          case V10INT: fprintf(salida,"%d;",*(int *)dir);
                      break;
          case V10FLOAT:fprintf(salida,"%f;",*(float *)dir);
                      break;
          case V10DOUBLE:fprintf(salida,"%lf;",*(double *)dir);
                      break;
          case V10CADENA:fprintf(salida,"%s;",(char *)dir);
                         break;
          case V10WCADENA:fprintf(salida,"%wZ;",dir);
                         break;
       }
    }
    (*fila)++;
    if (hijos) {
        for (nb=0;nb<f->nbloques;nb++) {
            if (f->b[nb]->padre==b) {
                bloques *bh=f->b[nb];
                pasacsvbloque(bh,salida,hijos-1,fila,0,copiar);
            }
        }
    }
    fprintf(salida,"\n");
    return(0);
}

static void pasacsvcab(bloques *b,FILE *salida,int *fila,int primero)
{
    int nc;
    int i=0;
    for (nc=0;nc<ncol;nc++) {
        int numc=damecampo(b,col[nc].c->nombre);
        fcampos *c;
        if (numc==-1) continue;
        c=b->c+numc;                       
        if (b->c+numc!=col[nc].c) continue;
        if (primero==0 && c->virtual) continue;
        i++;
        if (es_blanco(col[nc].nombreusuario)) {
            fprintf(salida,"%s;", col[nc].c->nombre);
        } else {
            fprintf(salida,"%s;", col[nc].nombreusuario);
        }
        
    }
    fprintf(salida,"\n");
    (*fila)++;
}

static int pasacsvbloque(bloques *b,FILE *salida,int hijos,int *fila,int primero,int copiar)
{
    int lin;
    int antlin=b->s->clin;
    if (hijos==0) {
        b->invisible=1;
        b->s->clin=b->s->numero-1;
        while (leeregistroi(b,b->s->clin)==0) {
            b->s->clin++;
            b->s->numero++;
            b->s->numlin++;
        }
        if (b->noinsert && b->s->numero>1) {
            b->s->numero--;
            b->s->numlin--;
        }
    }
    b->s->clin=antlin;
    b->invisible=0;
    pasacsvcab(b,salida,fila,primero);
    if (hijos) {
        lin=b->s->clin;
        leeregistroi(b,lin);
        if (!esnuloregistro(b)) {
            pasacsvunregistro(b,salida,hijos,fila,primero,copiar);
            if (lin==b->s->numero-1 && !esnuloregistro(b)) {
                b->s->numero++;
                b->s->numlin++;
                if (b->s->ulin-b->s->plin<b->s->lppag-1) b->s->ulin++;
            }
        }
    } else {
        for (lin=0;lin<b->s->numero;lin++) {
            leeregistroi(b,lin);
            if (esnuloregistro(b)) continue;
            pasacsvunregistro(b,salida,hijos,fila,primero,copiar);
            if (lin==b->s->numero-1 && !esnuloregistro(b)) {
                b->s->numero++;
                b->s->numlin++;
                if (b->s->ulin-b->s->plin<b->s->lppag-1) b->s->ulin++;
            }
        }
    }
    leeregistroi(b,b->s->clin);
    return(0);
}

static void anadecamposbloque(bloques *b,int hijos)
{
    int nc;
    int nb;
    for (nc=0;nc<b->ncamp;nc++) {
        fcampos *c=b->c+nc;
        if (c->oculto && es_blanco(c->titulo)) continue;
        col[ncol].c=c;
        if (!es_blanco(c->titulo)) col[ncol].nombreusuario=strdup(c->titulo);
        else {
            if (traducecamposole) col[ncol].nombreusuario=strdup(traducecamposole(c->nombre,0));
            else                  col[ncol].nombreusuario=strdup(c->nombre);
        }
        ncol++;
    }
    if (hijos==0) return;
    for (nb=0;nb<b->form->nbloques;nb++) {
        bloques *b1=b->form->b[nb];
        if (b1->padre==b) anadecamposbloque(b1,hijos-1);
    }
}


static void dameficherocsv(bloques *b,char *nombre)
{
    int fileret;
    char mifecha[MAXPATH],mihora[MAXPATH];
    memset(mihora,0,MAXPATH);
    memset(mifecha,0,MAXPATH);
    cent2a(gettime(),6,'-',mihora);
    jul2a(damedate(),"Y.YYMMDD",mifecha);
    sprintf(nomficherocsv,"%s/%s-%s-%s%s.csv",rutaxls,b->nombre,v10wwwuser,mifecha,mihora);
    sprintf(nomcsvsinruta,"/%s-%s-%s%s.csv",b->nombre,v10wwwuser,mifecha,mihora);
    fileret=access(nomficherocsv,0);
    if (fileret==0) unlink(nomficherocsv);
    strcpy(nombre,nomficherocsv);
}

static void presentacsvweb(bloques *b)
{		
    if (funcxls) funcxls(nomcsvsinruta);
}

static int pasacsvforms(bloques *b,ftrigers *ft,int fila)
{
    int i,copiar=0;
    int hijos=0;
    char nombre[MAXPATH]="forms.csv";
    FILE *salida;
    ncol=0;
    if (ft->nparam>1) hijos=atoi(ft->param[1]);
    if (ft->nparam>2) strcpy(nombre,ft->param[2]);
	if (v10versionweb) {
        dameficherocsv(b,nombre);
	} 
    anadecamposbloque(b,hijos);
    salida=fopen(nombre,"w");
    pasacsvbloque(b,salida,hijos,&fila,1,copiar);
    fclose(salida);
	for (i=0;i<ncol;i++) free(col[i].nombreusuario);
	if (v10versionweb) {
        presentacsvweb(b);
	} 
    return(0);
}


static int fpasacsv(bloques *b,ftrigers *ft)
{
    if (ft->nparam==0) {
        mensajefcm(10,"Debe dar nombre de aplicacion OLE");
        return(-1);
    }
    pasacsvforms(b,ft,1);
    return(0);
}

void initcsvfrm(void)
{
    declaratriger("FPASACSV",fpasacsv,NULL);
}


