/*
* Módulo : V10FORPIDEVAR.C
* Objeto:  Pide variables cuando el where contiene el simbolo &
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"

#define LFORMATO    200
#define MAXWHERES   500
#define TAMWHERE    MAXCADENA
#define MAXVARWHERE 100

typedef struct {
          char *nombre;
		  union {
                 WCHAR    *wvalor;
                 char     *cvalor;
				 long     lvalor;
				 double   dvalor;
				 v10dates fevalor;
		   } val;
		  int  tipo;
        } vwheres;
static vwheres vw[MAXWHERES];
static int numwheres;

static void finwhere(void)
{
  int i;
  for (i=0;i<numwheres;i++) {
      free(vw[i].nombre);
      if (vw[i].tipo==V10CADENA) free(vw[i].val.cvalor);
      if (vw[i].tipo==V10WCADENA) free(vw[i].val.wvalor);
   }
  numwheres=0;
}  

static int numwhere(char *nombre)
{
  int i;
  for (i=0;i<numwheres;i++) {
      if (strcmp(vw[i].nombre,nombre)==0) return(i);
   }
  return(-1);
}

static void liberavalor(int campo)
{
	vwheres *v=vw+campo;
	switch (v->tipo) {
	case V10CADENA:if (v->val.cvalor) free(v->val.cvalor);
		           v->val.cvalor=NULL;
		           break;
	case V10WCADENA:if (v->val.wvalor) free(v->val.wvalor);
		           v->val.wvalor=NULL;
		           break;
	}
}
//OJO UNICODE
static void asignavalor(int ncampo,char *valor)
{
    vwheres *v=vw+ncampo;
    switch (v->tipo) {
    case V10LONG: if (valor==NULL) v->val.lvalor=0;
		           else          v->val.lvalor=*(long *)valor;
    case V10DOUBLE: if (valor==NULL) v->val.dvalor=0;
		           else          v->val.dvalor=*(double *)valor;
    case V10CADENA:if (valor==NULL) {
					v->val.cvalor=calloc(1,TAMWHERE);
                } else {
                    v->val.cvalor=strdup(valor);
                }
                break;
    case V10FECHA: if (valor==NULL) v->val.fevalor=0;
		           else          v->val.fevalor=*(v10dates *)valor;
        break;
    }
}

static void copiavalor(int i,char *valor)
{
	vwheres *v=vw+i;
	if (valor==NULL) return;
	switch (v->tipo) {
	case V10LONG:v->val.lvalor=*(long *)valor;
		        break;
	case V10DOUBLE:v->val.dvalor=*(double *)valor;
		        break;
	case V10CADENA:strcpy(v->val.cvalor,valor);
		        break;
	case V10FECHA:v->val.fevalor=*(v10dates *)valor;
		        break;
	}
}


static void recuperavalor(int i,char *valor)
{
	vwheres *v=vw+i;
	if (valor==NULL) return;
	switch (v->tipo) {
	case V10LONG:*(long *)valor=v->val.lvalor;
		        break;
	case V10DOUBLE:*(double *)valor=v->val.dvalor;
		        break;
	case V10CADENA:strcpy(valor,v->val.cvalor);
		        break;
	case V10FECHA:*(v10dates *)valor=v->val.fevalor;
		        break;
	}
}

static int nuevowhere(char *nombre,char *valor,int tipo)
{
  int i;
  i=numwhere(nombre);
  if (i==-1) {
	 i=numwheres++;
     if (i==0) atexit(finwhere);
     vw[i].nombre=strdup(nombre);
	 if (tipo!=-1) vw[i].tipo=tipo;
	    else       vw[i].tipo=V10CADENA;
	 asignavalor(i,valor);
  } else {
	  if (vw[i].tipo!=tipo && tipo!=-1) {
		  liberavalor(i);
		  vw[i].tipo=tipo;
		  asignavalor(i,valor);
	  } else copiavalor(i,valor);
  }
  return(i);
}

static void sustituyesub(char *cadena)
{
  while (*cadena) {
        if (*cadena=='_') *cadena=' ';
        cadena++;
   }
}

static void anadevariable(char *nombre,int *variables,int *nvar,int tipo)
{
  int i;
  int numero;
  sustituyesub(nombre);
  numero=nuevowhere(nombre,NULL,tipo);
  for (i=0;i<*nvar;i++) if (variables[i]==numero) return;
  variables[(*nvar)++]=numero;
}

static void anadevalor(char *nombre,char *donde,char **prin,int fechajuliana)
{
  int numero;
  vwheres *v;
  char buffer[MAXCADENA];
  sustituyesub(nombre);
  numero=numwhere(nombre);
  if (numero==-1) return;
  v=vw+numero;
  strins(donde,"'");
  switch (v->tipo) {
  case V10LONG:sprintf(buffer,"%ld",v->val.lvalor);
	          break;
  case V10DOUBLE:sprintf(buffer,"%lf",v->val.dvalor);
	          break;
  case V10CADENA:strcpy(buffer,v->val.cvalor);
	          break;
  case V10FECHA :if (fechajuliana==0) jul2a(v->val.fevalor,"DD-MM-Y.YY",buffer);
	             else            sprintf(buffer,"%ld",v->val.fevalor);
	          break;
  }
  strins(donde+1,buffer);
  strins(donde+1+strlen(buffer),"'");
  *prin+=strlen(buffer)+2;
}

static void dameformato(int num,char *donde)
{
	vwheres *v=vw+num;
	switch (v->tipo) {
      case V10LONG:strcpy(donde,"@L,@@@@@@@");
		            break;
      case V10DOUBLE:strcpy(donde,"#L,##########.######");
		            break;
      case V10CADENA:strcpy(donde,"_1000_____________________________________");
                  break;
      case V10FECHA: strcpy(donde,"¿D-MM-Y.YY");
		            break;
	}

}

static void llpidevwhere(char *where,int (*dametipo)(char *nombre,void *dato),void *datotipo)
{
  char *aux,*ptr=where;
  int variables[MAXVARWHERE];
  char mivariable[MAXCADENA];
  char destino[MAXCADENA]="";
  int nvar=0,i;
  tpixels *copiapant;
  forms *antform=formglobal;
  while ((aux=strchr(ptr,'&'))!=NULL) {
        char *prin=aux+1,*fin,achar;
        int tipo=-1;
        if (strchr("¿_@#",*prin)) {
           switch (*prin) {
             case '¿':tipo=V10FECHA;
                      break;
             case '@':tipo=V10LONG;
                     break;
             case '#':tipo=V10DOUBLE;
                    break;
             case '_':tipo=V10CADENA;
                     break;
           }
          prin++;
         }
        if (*prin=='"') {
           prin++;
           if ((fin=strchr(prin,'"'))==NULL) final(("Comilla sin terminar"));
           ptr=fin+1;
         } else {
           fin=prin+strcspn(prin," )|+-*/,");
           ptr=fin;
         }
        achar=*fin;
        *fin=0;
        strcpy(mivariable,prin);
        *fin=achar;
		if (dametipo && tipo==-1) {
			tipo=dametipo(mivariable,datotipo);
		}
      if (tipo==-1) tipo=V10CADENA;
      anadevariable(mivariable,variables,&nvar,tipo);
   }
  if (nvar==0) return;
  if (FORMCON==-1) {
     FORMCON=damecon();
   }
  for (i=0;i<nvar;i++) {
	  char formato[LFORMATO];
	  dameformato(variables[i],formato);
      sprintf(destino+strlen(destino),"CAMPO=CAMPO%d,OCULTO,\"%s\"\n",i,formato);
    }
  sprintf(destino+strlen(destino),"BEGINBLOQUEPAN=VARIABLES\nASIGNACION DE VARIABLES DE CONSULTA\n\n");
  for (i=0;i<nvar;i++) {
      char formato[LFORMATO];
      vwheres *v=vw+variables[i];
      dameformato(variables[i],formato);
      sprintf(destino+strlen(destino),"%-20.20s : %-50.50s\n",v->nombre,formato);
   }
  sprintf(destino+strlen(destino),"|\nSOLOQUERY\nNOQUERY\nPOSX=10\nCOLOR=VARIABLE\n");
  if (nvar<20) {
     sprintf(destino+strlen(destino),"POSY=%d\n",20-nvar);
   }
  for (i=0;i<nvar;i++) {
      sprintf(destino+strlen(destino),"CAMPO=CAMPO%d,VIRTUAL\n",i);
    }
  sprintf(destino+strlen(destino),"TECLA=F4,FPULSATECLAS(\"ESC\")\nENDBLOQUE\n");
  formglobal=leeformcadena("VARIABLES",destino,FWINDOWS);
  for (i=0;i<nvar;i++) {
      char campo[MAXCADENA];
      char *dir;
      sprintf(campo,"CAMPO%d",i);
      dir=direcncampo(formglobal->b[0],campo);
	   recuperavalor(variables[i],dir);
   }
  copiapant=salvavd(&formglobal->b[0]->vi.w);
  finputform(formglobal);
  recuperavd(&formglobal->b[0]->vi.w,copiapant);
  for (i=0;i<nvar;i++) {
      char campo[MAXCADENA];
      char *dir;
      sprintf(campo,"CAMPO%d",i);
      dir=direcncampo(formglobal->b[0],campo);
      copiavalor(variables[i],dir);
   }
  liberaform(formglobal);
  formglobal=antform;
  ptr=where;
  while ((aux=strchr(ptr,'&'))!=NULL) {
        char *prin=aux+1,*fin,achar;
        while (strchr("¿_@#",*prin)) prin++;
        if (*prin=='"') {
           prin++;
           if ((fin=strchr(prin,'"'))==NULL) final(("Comilla sin terminar"));
         } else {
           fin=prin+strcspn(prin," )|+-*/,");
         }
        achar=*fin;
        *fin=0;
        strcpy(mivariable,prin);
        *fin=achar;
        if (*fin=='"') fin++;
        strcpy(aux,fin);
        anadevalor(mivariable,aux,&prin,1);
   }
}

void pidevwhere(char *where)
{
	llpidevwhere(where,NULL,NULL);
}
