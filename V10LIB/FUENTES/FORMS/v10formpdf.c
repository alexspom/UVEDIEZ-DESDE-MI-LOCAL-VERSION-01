#include "v10form.h"

static char rutapdf[MAXPATH];
static void (*funcpdf)(char *)=NULL;

void dameficheropdf(char *informe,char *dondeconruta,char *dondesinruta)
{
    char mifecha[MAXPATH],mihora[MAXPATH];
    static int secuen;
    memset(mihora,0,MAXPATH);
    memset(mifecha,0,MAXPATH);
    cent2a(gettime(),6,'-',mihora);
    jul2a(damedate(),"Y.YYMMDD",mifecha);
    sprintf(dondeconruta,"%s/%s-%s-%s%s-%d.pdf",rutapdf,informe,v10wwwuser,mifecha,mihora,secuen);
    sprintf(dondesinruta,"/%s-%s-%s%s-%d.pdf",informe,v10wwwuser,mifecha,mihora,secuen);
    secuen++;
}

void ponmensajepdf(char *fichero)
{
    funcpdf(fichero);
}

void confpdf2fichero(char *_user,int _puerto, char *_rutapdf, void (* mifunc)(char *) ) 
{
    strcpy(v10wwwuser,_user);
    strcpy(rutapdf,_rutapdf);	
    funcpdf=mifunc;
}