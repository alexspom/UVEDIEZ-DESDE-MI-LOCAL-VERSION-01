/*
* Módulo : V10FORASXLSX.C
* Objeto:  Interfase de FORMS con EXCEL con el paquete AS_XLSX
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2019

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"


#define MAXOLECOLS 400
typedef struct {
          fcampos *c;
          char *nombreusuario;
          char valorcelda[MAXCADENA];
          double valor;
        } olecols;

static olecols col[MAXOLECOLS];
static int ncol;

static char nomficheroxls[MAXPATH]="";


#define CASXLSX "BEGIN AS_XLSX.CELLC(:COLUMNA,:FILA,:VALOR); END;"
static v10cursors *casxlsx;
static v10cursors *cfilaas;
#define CSALVAAS "BEGIN AS_XLSX.SAVE(:DIRECTORIO,:FICHERO); END;"
static v10cursors *csalvaas;
#define CINICIOXLS "BEGIN AS_XLSX.NEW_SHEET; END;"
static v10cursors *cinicioxls;

typedef struct {
    int fila;
    int col;
    char valorcelda[MAXCADENA];
    char directorio[MAXPATH];
    char fichero[MAXPATH];
} valorasxls;

static valorasxls valoras;

static void initforasxlsx(void)
{
    casxlsx=abrecursor(CASXLSX);
    bindtodo(casxlsx,"COLUMNA",&valoras.col,sizeof(valoras.col),V10LONG,
        "FILA",&valoras.fila,sizeof(valoras.fila),V10LONG,
        "VALOR",valoras.valorcelda,sizeof(valoras.valorcelda),V10CADENA,NULL
    );
    csalvaas=abrecursor(CSALVAAS);
    bindtodo(csalvaas,"DIRECTORIO",valoras.directorio,sizeof(valoras.directorio),V10CADENA,
        "FICHERO",valoras.fichero,sizeof(valoras.fichero),V10CADENA,NULL
    );
    cinicioxls=abrecursor(CINICIOXLS);
}

static void ponvalorcelda(int fila,int col,char *valor)
{
    if (casxlsx==NULL) initforasxlsx();
    valoras.fila=fila;
    valoras.col=col;
    strcpy(valoras.valorcelda,valor);
    ejecutacursor(casxlsx);
}

static void salvaas(char *fichero)
{
    if (csalvaas==NULL) initforasxlsx();
    strcpy(valoras.fichero,fichero);
    strcpy(valoras.directorio,"XLSDIR");
    ejecutacursor(csalvaas);
}

static void inicioxls(bloques *b)
{
    char sql[MAXCADENA];
    int nc,i=0;
    if (cinicioxls==NULL) initforasxlsx();
    sprintf(sql,"BEGIN ");
    for (nc=0;nc<ncol;nc++) {
        int numc;
        if (col[nc].c==NULL) continue;
        numc=damecampo(b,col[nc].c->nombre);
        if (numc==-1) continue;
        if (b->c+numc!=col[nc].c) continue;
        i++;
        switch (col[nc].c->tipo) {
            case  V10FECHA:
                sprintf(sql+strlen(sql),"AS_XLSX.CELLC(%d,:FILA,:VALOR%d);",i,i);
                break;
            case V10LONG:
            case V10INT:
            case V10FLOAT:
            case V10DOUBLE:
                sprintf(sql+strlen(sql),"AS_XLSX.CELL(%d,:FILA,:VALOR%d);",i,i);
                break;
            case V10CADENA: 
                sprintf(sql+strlen(sql),"AS_XLSX.CELLC(%d,:FILA,:VALOR%d);",i,i);
                break;
        }
    }
    sprintf(sql+strlen(sql)," END;");
    cfilaas=abrecursornombre("CFILAAS",sql);
    bindcursor(cfilaas,"FILA",&valoras.fila,sizeof(valoras.fila),V10LONG);
    i=0;
    for (nc=0;nc<ncol;nc++) {
        int numc;
        char var[MAXPATH];
        if (col[nc].c==NULL) continue;
        numc=damecampo(b,col[nc].c->nombre);
        if (numc==-1) continue;
        if (b->c+numc!=col[nc].c) continue;
        i++;
        sprintf(var,"VALOR%d",i);
        switch (col[nc].c->tipo) {
            case  V10FECHA:
                bindcursor(cfilaas,var,col[nc].valorcelda,sizeof(col[nc].valorcelda),V10CADENA);
                break;
            case V10LONG:
            case V10INT:
            case V10FLOAT:
            case V10DOUBLE:
                bindcursor(cfilaas,var,&col[nc].valor,sizeof(col[nc].valor),V10DOUBLE);
                break;
            case V10CADENA:
                bindcursor(cfilaas,var,col[nc].valorcelda,sizeof(col[nc].valorcelda),V10CADENA);
                break;
        }
        
    }
    ejecutacursor(cinicioxls);
}

static void ponvalorfila(int fila)
{
    valoras.fila=fila;
    ejecutacursor(cfilaas);
}

static int pasaasbloque(bloques *b,int hijos,int *fila,int primero,int copiar);

static int pasaasunregistro(bloques *b,int hijos,int *fila,int primero,int copiar)
{
    int nb;
    int i=0;
    int nc;
    forms *f=FORM(b);
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
          case  V10FECHA:jul2a(*(v10dates *)dir,"DD-MM-Y.YY",col[nc].valorcelda);
                      break;
          case V10LONG:col[nc].valor=*(long *)dir;
                      break;
          case V10INT: col[nc].valor=*(int *)dir;
                      break;
          case V10FLOAT: col[nc].valor=*(float *)dir;
                      break;
          case V10DOUBLE:col[nc].valor=*(double *)dir;
              break;
          case V10CADENA: strcpy(col[nc].valorcelda,(char *)dir);
                      break;
       }
     //   ponvalorcelda(*fila,i,valor);
    }
    ponvalorfila(*fila);
    (*fila)++;
    if (hijos) {
        for (nb=0;nb<f->nbloques;nb++) {
            if (f->b[nb]->padre==b) {
                bloques *bh=f->b[nb];
                pasaasbloque(bh,hijos-1,fila,0,copiar);
            }
        }
    }
    return(0);
}

static void pasaascab(bloques *b,int *fila,int primero)
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
            ponvalorcelda(*fila,i, col[nc].c->nombre);
        } else {
            ponvalorcelda(*fila,i,col[nc].nombreusuario);
        }
        
    }
    (*fila)++;
}

static int pasaasbloque(bloques *b,int hijos,int *fila,int primero,int copiar)
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
    pasaascab(b,fila,primero);
    if (hijos) {
        lin=b->s->clin;
        leeregistroi(b,lin);
        if (!esnuloregistro(b)) {
            pasaasunregistro(b,hijos,fila,primero,copiar);
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
            pasaasunregistro(b,hijos,fila,primero,copiar);
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

void presentaasweb(bloques *b)
{
    char mifecha[MAXPATH],mihora[MAXPATH];
    memset(mihora,0,MAXPATH);
    memset(mifecha,0,MAXPATH);
    cent2a(gettime(),6,'-',mihora);
    jul2a(damedate(),"Y.YYMMDD",mifecha);
    sprintf(nomficheroxls,"%s-%s-%s%s.xlsx",b->nombre,v10wwwuser,mifecha,mihora);
    salvaas(nomficheroxls);
    sprintf(nomficheroxls,"/%s-%s-%s%s.xlsx",b->nombre,v10wwwuser,mifecha,mihora);		
    if (funcxls) funcxls(nomficheroxls);
}

static int pasaasforms(bloques *b,ftrigers *ft,int fila)
{
    int ret,i,copiar=0;
    int hijos=0;
    char *nombre="",nombreplantilla[MAXPATH];
    ncol=0;
    if (ft->nparam>1) hijos=atoi(ft->param[1]);
    if (ft->nparam>2) nombre=ft->param[2];
    if (es_blanco(nombre)) strcpy(nombreplantilla,nombre);
    else {
        ret=damenombrecompleto(nombre,nombreplantilla);
        if (ret) strcpy(nombreplantilla,"");
    }
    anadecamposbloque(b,hijos);
    inicioxls(b);
    pasaasbloque(b,hijos,&fila,1,copiar);
	for (i=0;i<ncol;i++) free(col[i].nombreusuario);
    presentaasweb(b);
    return(0);
}


static int fpasaas(bloques *b,ftrigers *ft)
{
    if (ft->nparam==0) {
        mensajefcm(10,"Debe dar nombre de aplicacion OLE");
        return(-1);
    }
    pasaasforms(b,ft,1);
    return(0);
}

void initasfrm(void)
{
    declaratriger("FPASAAS",fpasaas,NULL);
}
