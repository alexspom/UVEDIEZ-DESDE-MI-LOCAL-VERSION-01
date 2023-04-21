/*******************************************************************************
* Módulo : VDCONFIAUX.C                                                        *
* Función: Gestion de la configuracion de V10                                  *
*                                                                              *
*                                                                              *
* Autor	 : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 12-02-2008                                                          *
********************************************************************************

*******************************************************************************/

#include "vd.h"


typedef struct {
	char propiedad[LPROPIEDAD];
	char instancia[LPROPIEDAD];
	char valor[LVALOR];
	long hereda;
	char defecto[LVALOR];
	char result[MAXCADENA];
} confis;
static confis cfg;
#define CDAMEPROP "SELECT VD.GETPROPEX(:PROPIEDAD,:INSTANCIA,:HEREDA,:DEFECTO) FROM DUAL"
static v10cursors *v10dameprop;

#define CRESUELVECONF "SELECT VD.RESUELVECONF(:RESULT,:INSTANCIA,:HEREDA) FROM DUAL"
static v10cursors *v10resuelveconf;

static void initconfiaux(void)
{
	v10dameprop = abrecursor(CDAMEPROP);
	definetodo(v10dameprop, cfg.valor, sizeof(cfg.valor), V10CADENA, NULL);
	bindtodo(v10dameprop, "PROPIEDAD", cfg.propiedad, sizeof(cfg.propiedad), V10CADENA,
		"INSTANCIA", cfg.instancia, sizeof(cfg.instancia), V10CADENA,
		"HEREDA", &cfg.hereda, sizeof(cfg.hereda), V10LONG,
		"DEFECTO", cfg.defecto, sizeof(cfg.defecto), V10CADENA, NULL);
	v10resuelveconf = abrecursor(CRESUELVECONF);
	definetodo(v10resuelveconf, cfg.result, sizeof(cfg.result), V10CADENA, NULL);
	bindtodo(v10resuelveconf, "RESULT", cfg.result, sizeof(cfg.result), V10CADENA,
		"INSTANCIA", cfg.instancia, sizeof(cfg.instancia), V10CADENA,
		"HEREDA", &cfg.hereda, sizeof(cfg.hereda), V10LONG, NULL);
}

char *getprop(char *propiedad, char *instancia, int hereda, char *defecto)
{
	int ret;
	memset(&cfg, 0, sizeof(cfg));
	if (v10dameprop == NULL) initconfiaux();
	strcpy(cfg.propiedad, propiedad);
	strcpy(cfg.instancia, instancia);
	if (es_blanco(cfg.instancia)) strcpy(cfg.instancia, "GLOBAL");
	strcpy(cfg.defecto, defecto);
	cfg.hereda = hereda;
	ret = ejefetchcursor(v10dameprop);
	return(cfg.valor);
}

int damepropenteroinst(char *propiedad, char *instancia)
{
	char *valor;
	valor = getprop(propiedad, instancia, 1, "");
	return(atoi(valor));
}


int damepropentero(char *propiedad)
{
	return(damepropenteroinst(propiedad, ""));
}

double damepropdobleinst(char *propiedad, char *instancia)
{
	char *valor;
	valor = getprop(propiedad, instancia, 1, "");
	return(atof(valor));
}

double damepropdoble(char *propiedad)
{
	return(damepropdobleinst(propiedad, ""));
}

v10dates damepropfechainst(char *propiedad, char *instancia)
{
	char *valor;
	valor = getprop(propiedad, instancia, 1, "");
	return(a2jul(1, valor));
}

v10dates damepropfecha(char *propiedad)
{
	return(damepropfechainst(propiedad, ""));
}

char *damepropcadenainst(char *propiedad, char *instancia)
{
	char *valor;
	valor = getprop(propiedad, instancia, 1, "");
	return(valor);
}

char *damepropcadena(char *propiedad)
{
	return(damepropcadenainst(propiedad, ""));
}

char *resuelveconf(char *cadena, char *instancia)
{
	int ret;
	memset(&cfg, 0, sizeof(cfg));
	if (v10resuelveconf == NULL) initconfiaux();
	strcpy(cfg.result, cadena);
	strcpy(cfg.instancia, instancia);
	if (es_blanco(cfg.instancia)) strcpy(cfg.instancia, "GLOBAL");
	strcpy(cfg.defecto, "");
	cfg.hereda = 1;
	ret = ejefetchcursor(v10resuelveconf);
	return(cfg.result);
}

v10horas dameprophorasinst(char *propiedad, char *instancia)
{
	char *valor;
	valor = getprop(propiedad, instancia, 1, "");
	return(atof(valor));
}

v10horas dameprophoras(char *propiedad)
{
	return(dameprophorasinst(propiedad, ""));
}

