/*******************************************************************************
* Módulo : vdfortrig.c                                                         *
* Función: Permite cargar trigers dinamicamente                                *
*                                                                              *
*                                                                              *
* Autor	 : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/
#include "vdform.h"

#define CSELTRIGFORM "SELECT FUNTRIGER,LIBTRIGER "\
	                  " FROM VDTRIGFORMS "\
					  " WHERE TIPOTRIGER IN (:TIPOTRIGER,'A') AND ACTIVO='S' "
static v10cursors *vdseltrigform;

typedef struct {
	       char funtriger[LFUNTRIGER];
		   char libtriger[LLIBTRIGER];
		   char tipotriger[LTIPOTRIGER];
} vdtrigforms;

static vdtrigforms vdt;

static void finvdfortrig(void)
{
	liberacursor(vdseltrigform);
}

static void initvdfortrig(void)
{
	vdseltrigform=abrecursor(CSELTRIGFORM);
	definetodo(vdseltrigform,vdt.funtriger,sizeof(vdt.funtriger),V10CADENA,
		                     vdt.libtriger,sizeof(vdt.libtriger),V10CADENA,
							 NULL);
	bindtodo(vdseltrigform,"TIPOTRIGER",vdt.tipotriger,sizeof(vdt.tipotriger),V10CADENA,
		                    NULL);
	atexit(finvdfortrig);
}

static int fconviertefromdb(bloques *b,ftrigers *ft)
{
   fcampos *c=FORM(b)->cinput;
   char uniori[MAXCADENA],unidest[MAXCADENA];
   double factor;
   if (ft->nparam<2) {
       ft->msg="Debe especificar unidades origen y destino";
       return(-1);
   }
   if (c->tipo==V10DOUBLE) {
      sustituyevariablessc(b,ft->param[0],uniori);
      sustituyevariablessc(b,ft->param[1],unidest);
      factor=convierteunidades(*(double *)c->datoconv,uniori,unidest);
      *(double *)direccampoptr(b,c)=factor;
   }
   return(0);
}

static int fconvierte2db(bloques *b,ftrigers *ft)
{
   fcampos *c=FORM(b)->cinput;
   char uniori[MAXCADENA],unidest[MAXCADENA];
   double factor;
   if (ft->nparam<2) {
       ft->msg="Debe especificar unidades origen y destino";
       return(-1);
   }
   if (c->tipo==V10DOUBLE) {
      sustituyevariablessc(b,ft->param[0],uniori);
      sustituyevariablessc(b,ft->param[1],unidest);
      factor=convierteunidades(*(double *)direccampoptr(b,c),uniori,unidest);
      *(double *)c->datoconv=factor;
   }
   return(0);
}

static int fconvierteartfromdb(bloques *b,ftrigers *ft)
{
   fcampos *c=FORM(b)->cinput;
   char codart[LCADENA];
   int decimales=0;
   double factor;
   if (ft->nparam<1) {
       ft->msg="Debe especificar articulo";
       return(-1);
   }
   if (c->tipo==V10DOUBLE) {
      sustituyevariablessc(b,ft->param[0],codart);
      factor=conviertearticulo2host(*(double *)c->datoconv,codart,&decimales);
      *(double *)direccampoptr(b,c)=factor;
      *indicadorcampo(b,c,CINDDEC)=decimales;
   }
   return(0);
}

static int fconvierteinvartfromdb(bloques *b,ftrigers *ft)
{
   fcampos *c=FORM(b)->cinput;
   char codart[LCADENA];
   double factor;
   if (ft->nparam<1) {
       ft->msg="Debe especificar articulo";
       return(-1);
   }
   if (c->tipo==V10DOUBLE) {
      sustituyevariablessc(b,ft->param[0],codart);
      factor=conviertearticulo2v10(*(double *)c->datoconv,codart);
      *(double *)direccampoptr(b,c)=factor;
   }
   return(0);
}

static int fconvierteart2db(bloques *b,ftrigers *ft)
{
   fcampos *c=FORM(b)->cinput;
   char codart[LCADENA];
   double factor;
   if (ft->nparam<1) {
       ft->msg="Debe especificar articulo";
       return(-1);
   }
   if (c->tipo==V10DOUBLE) {
      sustituyevariablessc(b,ft->param[0],codart);
      factor=conviertearticulo2v10(*(double *)direccampoptr(b,c),codart);
      *(double *)c->datoconv=factor;
   }
   return(0);
}

static int fconvierteinvart2db(bloques *b,ftrigers *ft)
{
   fcampos *c=FORM(b)->cinput;
   char codart[LCADENA];
   double factor;
   if (ft->nparam<1) {
       ft->msg="Debe especificar articulo";
       return(-1);
   }
   if (c->tipo==V10DOUBLE) {
      sustituyevariablessc(b,ft->param[0],codart);
      factor=conviertearticulo2host(*(double *)direccampoptr(b,c),codart,NULL);
      *(double *)c->datoconv=factor;
   }
   return(0);
}

#define NPANTALLACOMEN "VDCOMEN"
static int fllamacomentario(bloques *b,ftrigers *ft)
{
    char mirowid[ROWIDLON];
    char pantalla[MAXPATH];
    long codcomen;
    char asigna[MAXCADENA],where[MAXCADENA];
    int ret;
    
    if (ft->nparam>0) {
        dameparametro(b,ft,0,V10LONG,&codcomen);
    } else {
        int nc;
        char buffer[MAXPATH];
        nc=damecampo(b,"CODCOMEN");
        if (nc<0) return(-1);
        bcampo2a(b,"CODCOMEN",buffer,0);
        codcomen=atoi(buffer);
    }
    if (ft->nparam>1) {
        dameparametro(b,ft,1,V10CADENA,mirowid);
    } else {
        int nc;
        nc=damecampo(b,"MIROWID");
        if (nc<0) return(-1);
        bcampo2a(b,"MIROWID",mirowid,0);
    }
    if (ft->nparam>2) {
        dameparametro(b,ft,2,V10CADENA,pantalla);
    } else {
        strcpy(pantalla,NPANTALLACOMEN);
    }
   sprintf(asigna,"CODCOMEN='%ld'",codcomen);
   sprintf(where,"TABLACOMEN=VD.DAMETABLAROWID('%s') ",mirowid);

   ret=fcejecutaform(b,pantalla,"S",where,"",asigna,"","","S");
   return(0);
}

#define CDAMEART "BEGIN "\
                  " :MICODART:=VDART.DAMEART(:CODART); "\
                 " END; "
static int ftraduceart(bloques *b,ftrigers *f)
{
   static v10cursors *cur;
   fcampos *c=FORM(b)->cinput;
   int ret;
   if (cur==NULL) {
       cur=abrecursordebug(CDAMEART,NODEPURA);
   }
   bindtodo(cur,"CODART",direccampoptr(b,c),c->lon,c->tipo,
                "MICODART",c->datoconv,c->lon,c->tipo,NULL);
   ret=ejecutacursor(cur);
   recuperacampo(b,c,c->datoconv);
   return(ret);
}

#define CTRADUCECAD "BEGIN "\
                     " :CADUCI:=VDART.FORMATCAD(:MICADUCI,:SENTIDO); "\
                    " END; "
static v10cursors *curcaduci;
static int fcaduci2db(bloques *b,ftrigers *f)
{
    fcampos *c=FORM(b)->cinput;
    int ret;
    int sentido=1;
    if (curcaduci==NULL) {
        curcaduci=abrecursor(CTRADUCECAD);
    }
    bindtodo(curcaduci,"MICADUCI",direccampoptr(b,c),c->lon,c->tipo,
                 "CADUCI",c->datoconv,c->lon,c->tipo,
                 "SENTIDO",&sentido,sizeof(sentido),V10LONG,NULL);
    ret=ejecutacursor(curcaduci);
    return(ret);
}

static int fcaducifromdb(bloques *b,ftrigers *f)
{
    fcampos *c=FORM(b)->cinput;
    int ret;
    int sentido=0;
    if (curcaduci==NULL) {
        curcaduci=abrecursor(CTRADUCECAD);
    }
    bindtodo(curcaduci,"MICADUCI",c->datoconv,c->lon,c->tipo,
                 "CADUCI",direccampoptr(b,c),c->lon,c->tipo,
                 "SENTIDO",&sentido,sizeof(sentido),V10LONG,NULL);
    ret=ejecutacursor(curcaduci);
    return(ret);
}

#define CINFOBLOQUEOS "SELECT VDART.INFOBLOQUEOS(:BLOQUEOS) FROM DUAL"
static int finfobloqueos(bloques *b,ftrigers *f)
{
    fcampos *c=FORM(b)->cinput;
    static char tooltip[MAXCADENA];
    char valorbloq[MAXCADENA];
    static v10cursors *cur;
    dametooltipcampo(b,c,tooltip);
    if (c->tipo==V10CADENA) {
        if (cur==NULL) cur=abrecursor(CINFOBLOQUEOS);
        definetodo(cur,valorbloq,sizeof(valorbloq),V10CADENA,
                       NULL);
        bindtodo(cur,"BLOQUEOS",direccampoptr(b,c),c->lon,c->tipo,
                     NULL);
        ejefetchcursor(cur);
        strcat(tooltip,"\n");
        strcat(tooltip,valorbloq);
    }
	if (!es_blanco(tooltip)) {
		if (!v10versionweb) {
		    v10tooltip((void *)f->msg,tooltip);
		} else f->msg=tooltip;
	}
    return(0);
}

static int fanalizaeanform(bloques *b,ftrigers *f)
{
    int np;
    fcampos *c;
    int nc,scan;
    nc=damecampo(b,f->param[0]);
    if (nc<0) {
        f->msg="FANALIZAEAN- NO EXISTE ORIGEN";
        return(-1);
    }
    c=b->c+nc;
    scan=*FSCAN(b,c);
    if (c->tipo!=V10CADENA) {
        f->msg="FANALIZAEAN- ORIGEN DEBE SER CADENA";
        return(-1);
    }
    for (np=1;np<f->nparam;np+=2) {
        int nc1;
        char cadena[MAXCADENA]="";
        fcampos *campo;
        nc1=damecampo(b,f->param[np+1]);
        if (nc1<0) {
            f->msg="FANALIZAEAN- DESTINO NO EXISTE";
            return(-1);
        }
        campo=b->c+nc1;
        if (damecampoean(direcncampo(b,f->param[0]),f->param[np],cadena)==0) {
            a2bcampo(b,f->param[np+1],cadena);
            *FSCAN(b,campo)=scan;
        }
    } 
    return(0);
}

static int ffficherobloque(bloques *b,ftrigers *f)  {
	char *fichero,*abrir,*textoquery,*abrirpantalla,*nbloque;
	int nc[5],ncerror,i;
	FILE *fich;

	ncerror=damecampo(b,"V10ERROR");
	for (i=0;i<5;i++) {		
		nc[i]=damecampo(b,f->param[i]);
		if (nc[i]<0) {
			sprintf(direccampo(b,ncerror),"ERROR: campo %s no existe",f->param[i]);
			return(-1);
		}
	}
	fichero=(char *)direccampo(b,nc[0]);
	textoquery=(char *)direccampo(b,nc[1]);
	abrir=(char *)direccampo(b,nc[2]);
	abrirpantalla=(char *)direccampo(b,nc[3]);
	nbloque=(char *)direccampo(b,nc[4]);
	fich=fopen(fichero,"w");
	if (!fich) {
		sprintf(direccampo(b,ncerror),"ERROR: no se puede abrir fichero\n %s\n para escritura",fichero);	
		return(-1);
	}
	fprintf(fich,textoquery);
	fclose(fich);
	if (*abrir=='S') invocaeditor(fichero,NULL);
	if (*abrirpantalla=='S')  fcejecutaform(b,nbloque,"S","","","","","","");
	return(0);
}

int miqueryauto(bloques *b,ftrigers *ft)
{
    if (CABECERA(formglobal->b[0])->antiguo==0) pushtecla(TECLATIMEOUT);
    return(0);
}

int fsleep(bloques *b,ftrigers *ft)
{
    long tiempo=1000;
    dameparametro(b,ft,0,V10LONG,&tiempo);
    Sleep(tiempo);
    return(0);
}

int inittrigersform(char *tipotriger)
{
    declaratriger("FCONVIERTEFROMDB",fconviertefromdb,NULL);
    declaratriger("FCONVIERTE2DB",fconvierte2db,NULL);
    declaratriger("FCONVIERTEARTFROMDB",fconvierteartfromdb,NULL);
    declaratriger("FCONVIERTEART2DB",fconvierteart2db,NULL);
    declaratriger("FCONVIERTEINVARTFROMDB",fconvierteinvartfromdb,NULL);
    declaratriger("FCONVIERTEINVART2DB",fconvierteinvart2db,NULL);
    declaratriger("FTRADUCEART",ftraduceart,NULL);
    declaratriger("FTRADUCEART",ftraduceart,NULL);
    declaratriger("FCADUCI2DB",fcaduci2db,NULL);
    declaratriger("FCADUCIFROMDB",fcaducifromdb,NULL);
    declaratriger("FINFOBLOQUEOS",finfobloqueos,NULL);
    declaratriger("FLLAMACOMENTARIO",fllamacomentario,NULL);
	declaratriger("FFICHEROBLOQUE",ffficherobloque,NULL);
    declaratriger("FSLEEP",fsleep,NULL);
	declaratriger("MIQUERYAUTO",miqueryauto,NULL);

	if (vdseltrigform==NULL) initvdfortrig();
	strcpy(vdt.tipotriger,tipotriger);
	ejecutacursorv(vdseltrigform);
	while (fetchcursor(vdseltrigform)==0) {
		  void *fun;
		  fun=damefundll(vdt.libtriger,vdt.funtriger);
		  if (fun) {
			  declaratriger(strmay(vdt.funtriger),fun,NULL);
		  } else {
			  v10log(LOGERROR,"La funcion %s no existe en la libreria %s\n",vdt.funtriger,vdt.libtriger);
		  }
	}
	return(0);
}
