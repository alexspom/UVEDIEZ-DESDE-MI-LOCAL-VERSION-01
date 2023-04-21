/*******************************************************************************
* Módulo : VDEAN128.C                                                          *
* Función: Tratamiento de codigos EAN128                                       *
*                                                                              *
*                                                                              *
* Autor	 : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 08-08-2008                                                          *
********************************************************************************

*******************************************************************************/

#include "vd.h"


#define MAXIDEAN    100  // Maximo numero de codigos EAN
#define GS       0x1D

typedef struct {
         char codidean[LCODIDEAN];
         long lcodidean;
         int variable; // 0 Fija 1 Variable 2 Con dígito para indicar longitud
         int longitud;
       } ideans;
static ideans idean;
#define CSELEAN "SELECT CODIDEAN,LCODIDEAN,VARIABLE,LONGITUD "\
                 "FROM VDEANID "
static v10cursors *curean;
static int numidean;
static ideans ie[MAXIDEAN];

static void fincursoresvdean128(void)
{
    liberacursor(curean);
}

static void initcursoresvdean128(void)
{
  curean=abrecursor(CSELEAN);
  definetodo(curean,idean.codidean,sizeof(idean.codidean),V10CADENA,
                    &idean.lcodidean,sizeof(idean.lcodidean),V10LONG,
                    &idean.variable,sizeof(idean.variable),V10LONG,
                    &idean.longitud,sizeof(idean.longitud),V10LONG,
                    NULL);                   
  ejecutacursor(curean);
  while (fetchcursor(curean)==0) {
        ie[numidean]=idean;
        numidean++;
   }
  atexit(fincursoresvdean128);
}

static int buscacodigo(char *codidean)
{
  int i;
  for (i=0;i<numidean;i++) {
      if (strncmp(ie[i].codidean,codidean,strlen(ie[i].codidean))==0) return(i);
   }
  return(-1);
}

static int damelean(char *codidean)
{
  int i;
  ideans *ide;
  i=buscacodigo(codidean);
  if (i<0) return(-1);
  ide=ie+i;
  if (ide->variable==1) return(-1);
  if (ide->variable==2) return(codidean[ide->lcodidean]+ide->lcodidean+1);
  return(ide->longitud+ide->lcodidean);
}

static char *saltainicioean(char *codigo)
{
  if (codigo[0]==GS) return(codigo+1);
  return(codigo);
}

static int lldamecampoean(char *codigo,char *codidean,char *donde)
{
  int lon,cod;
  char *sigcod,*inicod;
  if (curean==NULL) initcursoresvdean128();
  inicod=saltainicioean(codigo);
  cod=buscacodigo(inicod);
  if (cod==-1) lon=-1;
     else lon=damelean(ie[cod].codidean);
  if (lon==-1) sigcod=strchr(inicod,GS);
     else      sigcod=inicod+lon;
  if (strcmp(ie[cod].codidean,codidean)==0) {
     if (donde) {
        if (sigcod==NULL) sigcod=inicod+strlen(inicod);
        inicod=inicod+ie[cod].lcodidean;
        strcopia(donde,inicod,sigcod-inicod);
        trim(donde);
		//if (strcmp(codigo,"240")) while (*donde=='0') strcpy(donde,donde+1);
      }
     return(0);
   }
  if (sigcod==NULL) return(-1);
  return(lldamecampoean(sigcod,codidean,donde));
}

int damecampoean(char *codigo,char *codidean,char *donde)
{
	char temp[MAXCADENA],*aux;
	strcpy(temp,codigo);
	while ((aux=strstr(temp,"]C1"))!=NULL) {
		*aux=GS;
		strcpy(aux+1,aux+3);
	}
	return(lldamecampoean(temp,codidean,donde));
}

