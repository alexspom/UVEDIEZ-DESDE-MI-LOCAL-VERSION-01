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

static char nomficheroxls[MAXPATH]="";


int reusarexcel=1;

static int pasaolebloque(bloques *b,IDispatch *id,int hijos,int *fila,int primero,int copiar);

static int pasaoleunregistro(bloques *b,IDispatch *id,int hijos,int *fila,int primero,int copiar)
{
    int nb;
    int i=0;
    int nc;
    int ncolreal=0;
    SAFEARRAY *psa;
    SAFEARRAYBOUND saBound;
    VARIANTARG *pvargBase;
    VARIANTARG *pvarg;
    OLECHAR lpsz[MAXOLECADENA];
    char direxcel[MAXLRANGO];
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
    saBound.lLbound = 0;
    saBound.cElements = ncolreal;
    psa = SafeArrayCreate(VT_VARIANT, 1, &saBound);
    if (psa == NULL) return FALSE;
    SafeArrayAccessData(psa,(void HUGEP* FAR*)  &pvargBase);
    pvarg = pvargBase;
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
        ClearVariant(pvarg);
        switch (col[nc].c->tipo) {
          case  V10FECHA:{char mifecha[20];
                      jul2a(*(v10dates *)dir,"DD-MM-Y.YY",mifecha);
                      pvarg->vt = VT_BSTR;
                      MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,mifecha,-1,lpsz,MAXOLECADENA-1);
                      pvarg->bstrVal = SysAllocString(lpsz);
                      break;
                     }
          case V10LONG:pvarg->vt = VT_R8;
                      pvarg->dblVal=*(long *)dir;
                      break;
          case V10INT:   pvarg->vt = VT_R8;
                      pvarg->dblVal=*(int *)dir;
                      break;
          case V10FLOAT: pvarg->vt = VT_R8;
                      pvarg->dblVal=*(float *)dir;
                      break;
          case V10DOUBLE:pvarg->vt = VT_R8;
                      pvarg->dblVal=*(double *)dir;
                      break;
          case V10CADENA:{char *midir;
                      pvarg->vt = VT_BSTR;
                      midir=calloc(1,strlen(dir)+2);
                      if (((char *)dir)[0]>='0' &&((char *)dir)[0]<='9') strcpy(midir,"'");
                      strcat(midir,dir);
                      MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,midir,-1,lpsz,MAXOLECADENA-1);
                      free(midir);
                      pvarg->bstrVal = SysAllocString(lpsz);
                      break;}
          case V10WCADENA:pvarg->vt = VT_BSTR;
                          pvarg->bstrVal = SysAllocString(dir);
                          break;
       }
      pvarg++;
    }
    pasarangoexcel(0,*fila,i-1,*fila,direxcel);
    SafeArrayUnaccessData(psa);
    setvalorarray(id,direxcel,psa);
    (*fila)++;
    if (hijos) {
        for (nb=0;nb<f->nbloques;nb++) {
            if (f->b[nb]->padre==b) {
                bloques *bh=f->b[nb];
                pasaolebloque(bh,id,hijos-1,fila,0,copiar);
            }
        }
    }
    return(0);
}

static void pasaolecab(bloques *b,IDispatch *id,int *fila,int primero)
{
    int nc;
    char cadena[20];
    int i=0;
    for (nc=0;nc<ncol;nc++) {
        int numc=damecampo(b,col[nc].c->nombre);
        fcampos *c;
        if (numc==-1) continue;
        c=b->c+numc;                       
        if (b->c+numc!=col[nc].c) continue;
        if (primero==0 && c->virtual) continue;
        pasadirexcel(i,*fila,cadena);
        i++;
        if (es_blanco(col[nc].nombreusuario)) {
            setvalorstring(id, cadena, col[nc].c->nombre);
        } else {
            setvalorstring(id, cadena, col[nc].nombreusuario);
        }
        
    }
    (*fila)++;
}

static int pasaolebloque(bloques *b,IDispatch *id,int hijos,int *fila,int primero,int copiar)
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
    pasaolecab(b,id,fila,primero);
    if (hijos) {
        lin=b->s->clin;
        leeregistroi(b,lin);
        if (!esnuloregistro(b)) {
            pasaoleunregistro(b,id,hijos,fila,primero,copiar);
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
            pasaoleunregistro(b,id,hijos,fila,primero,copiar);
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

void presentaxlsweb(bloques *b,IDispatch *id,IDispatch *wb)
{
    int fileret;
    char mifecha[MAXPATH],mihora[MAXPATH];
    memset(mihora,0,MAXPATH);
    memset(mifecha,0,MAXPATH);
    cent2a(gettime(),6,'-',mihora);
    jul2a(damedate(),"Y.YYMMDD",mifecha);
    sprintf(nomficheroxls,"%s/%s-%s-%s%s.xlsx",rutaxls,b->nombre,v10wwwuser,mifecha,mihora);
    fileret=access(nomficheroxls,0);
    if (fileret==0) unlink(nomficheroxls);
    salvaexcel(wb,nomficheroxls);
    sprintf(nomficheroxls,"/%s-%s-%s%s.xlsx",b->nombre,v10wwwuser,mifecha,mihora);		
    if (funcxls) funcxls(nomficheroxls);
    Invoke(id, "Quit", NULL, DISPATCH_METHOD, 0);
}

static int pasaoleforms(bloques *b,ftrigers *ft,int fila)
{
    IDispatch *id,*hoja,*wb;
    int ret,i,copiar=0;
    int hijos=0;
    int reusar=reusaexcel;
    char *nombre="",nombreplantilla[MAXPATH];
    ncol=0;
    if (ft->nparam>1) hijos=atoi(ft->param[1]);
    if (ft->nparam>2) nombre=ft->param[2];
    if (ft->nparam>3) reusar=atoi(ft->param[2]);
    if (es_blanco(nombre)) strcpy(nombreplantilla,nombre);
    else {
        ret=damenombrecompleto(nombre,nombreplantilla);
        if (ret) strcpy(nombreplantilla,"");
    }
    id=startole(ft->param[0],reusar);
    if (id==NULL) {
        mensajefcm(10,"Aplicacion %s no instalada",ft->param[0]);
        finole();
        return(-1);
    }
    ret=cargaexcel(id,&wb,&hoja,nombreplantilla);
    if (ret) {
        finole();
        return(-1);
    }
    putproperty(hoja, "Visible",NULL, NULL,V10INT,TRUE,-1);
    if (es_blanco(nombreplantilla)) {
       anadecamposbloque(b,hijos);
    } else {
        for (ncol=0;ncol<MAXCAMPOS;ncol++) {
            char valor[100];
            char rango[MAXLRANGO];
            int nc;
            pasadirexcel(ncol,1,rango);
            getvalorstring(hoja,rango,valor);
            if (es_blanco(valor)) break;
            trim(valor);
            valor[MAXNOMBREV10-1]=0;
            for (nc=0;nc<b->ncamp;nc++) {
                char *nombre;
                if (traducecamposole) nombre=traducecamposole(b->c[nc].nombre,0);
                   else               nombre=b->c[nc].nombre;
                if (strcmp(valor,nombre)==0) {
                    col[ncol].c=b->c+nc;
                    col[nc].nombreusuario=strdup(nombre);
                    break;
                }
            }
            if (nc>=b->ncamp) {
                col[ncol].c=NULL;
                copiar=1;
            }
        }
        if (copiar) {
            IDispatch *rango;
            rango=damerangoexcel(hoja,0,2,ncol-1,2);
            ret = Invoke(rango, "Copy", NULL,  DISPATCH_METHOD, 0);
            liberaidispatch(rango);
        }
    }
    pasaolebloque(b,hoja,hijos,&fila,1,copiar);
	for (i=0;i<ncol;i++) free(col[i].nombreusuario);
    liberaidispatch(hoja);
	if (v10versionweb) {
        presentaxlsweb(b,id,wb);
	} else visibleexcel(id,TRUE);
	liberaidispatch(wb); 
	liberaidispatch(id);
    finole();
    return(0);
}


static int fpasaole(bloques *b,ftrigers *ft)
{
    int hijos=0;
    if (ft->nparam==0) {
        mensajefcm(10,"Debe dar nombre de aplicacion OLE");
        return(-1);
    }
    pasaoleforms(b,ft,1);
    return(0);
}

void initolefrm(void)
{
    declaratriger("FPASAOLE",fpasaole,NULL);
}

