/*
* M�dulo : V10ENTORNO.C
* Objeto:  Tratamiento de variables de entorno
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

static char hostname[LNOMBREORDENADOR]="";

char *STDnombreordenador(void) 
{
    if (*hostname==0) {
#ifndef __LINUX__
        strcpy(hostname,getenv("COMPUTERNAME"));
#else
        gethostname(hostname,sizeof(hostname));
#endif
    }
  return(hostname);
}

void traduceentorno(char *cadena, char *destino)
{
	char *aux, *aux1, *var;
	strcpy(destino, "");
	while ((aux = strchr(cadena, '%')) != NULL) {
		*aux = 0;
		strcat(destino, cadena);
		cadena = aux + 1;
		if ((aux1 = strchr(cadena, '%')) != NULL) {
			*aux1 = 0;
			var = getenv(cadena);
			if (var) sprintf(destino + strlen(destino), "%s", var);
			*aux1 = '%';
			cadena = aux1 + 1;
		}
		else {
			sprintf(destino + strlen(destino), "%%%s", cadena);
			cadena += strlen(cadena);
		}
		*aux = '%';
	}
	strcat(destino, cadena);
}