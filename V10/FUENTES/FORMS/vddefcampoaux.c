/*******************************************************************************
* Módulo : vddefcampoaux.c                                                     *
* Función: Modulo auxiliar para definir caracteristicas por defecto de campos  *
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

#define MAXDEFCAMPOS 2000
static int numcampos;
static vddefcampos sdefc[MAXDEFCAMPOS];

static int damecaraccampo(char *nombre,char *tipopantalla,vddefcampos *defc)
{
	int i;
	int ret;
	for (i=0;i<numcampos;i++) {
		if (strcmp(nombre,sdefc[i].ncampo)==0) {
			if (*tipopantalla==*sdefc[i].tipopantalla) {
			    *defc=sdefc[i];
				return 0;
			}
			if (*sdefc[i].tipopantalla=='N') return(-1);
		}
	}
   ret=DECselncampo(nombre,tipopantalla,defc);
   if (ret==0) {
	   sdefc[numcampos]=*defc;
	   numcampos++;
	   return 0;
   }
   ret=DECselncampo(nombre,"A",defc);
   if (ret==0) {
	   sdefc[numcampos]=*defc;
	   numcampos++;
	   return 0;
   }
   strcpy(sdefc[numcampos].ncampo,nombre);
   strcpy(sdefc[numcampos].tipopantalla,"N");
   numcampos++;
   return ret;
}

char *leedefectocampo(fcampos *campo)
{
    vddefcampos defc;
    int ret;
    char tipopantalla[LTIPOPANTALLA];
    char *carac;
    carac=calloc(1,MAXCADENA);
    if (campo->f->tipo==FWINDOWS) strcpy(tipopantalla,"F");
    else                          strcpy(tipopantalla,"R");
	ret=damecaraccampo(campo->nombre,tipopantalla,&defc);
	if (ret) return carac;
    if (!es_blanco(defc.ttitulo)) sprintf(carac,",TITULO(\"%s\")",defc.ttitulo);
    if (!es_blanco(defc.ttooltip)) sprintf(carac+strlen(carac),",TOOLTIP(\"%s\")",defc.ttooltip);
    if (!es_blanco(defc.fconvierte)) sprintf(carac+strlen(carac),",CONVIERTE=%s",defc.fconvierte);
    if (!es_blanco(defc.capitaliza)) sprintf(carac+strlen(carac),",%s",*defc.capitaliza=='U'?"UPPER":(*defc.capitaliza=='L'?"LOWER":"MIXED"));
    if (*defc.estraducible=='S') sprintf(carac+strlen(carac),",TRADUCIBLE");
    if (*defc.esscan=='S') sprintf(carac+strlen(carac),",SCAN");
    if (!es_blanco(defc.fpostchange)) sprintf(carac+strlen(carac),",POSTCHANGE=%s",defc.fpostchange);
    if (!es_blanco(defc.ftecla)) sprintf(carac+strlen(carac),",TECLA=%s",defc.ftecla);
    if (!es_blanco(defc.privmodif)) sprintf(carac+strlen(carac),",NOUPDATE(\"%s\")",defc.privmodif);
    if (!es_blanco(defc.privver)) sprintf(carac+strlen(carac),",DISPLAY(\"%s\")",defc.privver);
    if (!es_blanco(defc.ftooltip)) sprintf(carac+strlen(carac),",FUNTOOLTIP=%s",defc.ftooltip);
	if (!es_blanco(defc.fcontextual)) sprintf(carac+strlen(carac),",CONTEXTUAL=%s",defc.fcontextual);
	if (!es_blanco(defc.fauxiliar)) sprintf(carac+strlen(carac),",%s",defc.fauxiliar);

    return(carac);
}