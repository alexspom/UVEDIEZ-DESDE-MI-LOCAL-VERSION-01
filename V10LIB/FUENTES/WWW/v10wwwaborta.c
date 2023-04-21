/*
* Módulo :  V10wwwCritico.C
* Objeto:   Errores Críticos de Pltaforma Web
* 
* 
* Autor	 : Francisco José Guerrero Sánchez
* Fecha  : 25-09-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10wwwform.h"
unsigned long wwwwarning_time = 0;
static char file[MAXPATH];
static int line;

#define MAXCADENA_V10WWCRITICO 1024

void v10wwwerror(char *formato,va_list lista_param_variable,short salir)
{

	char msj[MAXCADENA_V10WWCRITICO]="",msj2[MAXCADENA_V10WWCRITICO]="";
	static int exitencurso;

	if (exitencurso) {  
		Sleep(10);
		return;
	}

	formato=v10translate(formato);  
	vv10log(LOGERROR,formato,lista_param_variable);

	if (salir)  strcpy(msj,"!!!! ERROR !!!! Causa: \\n\\n");
	else strcpy(msj,"!!!! WARNING !!!! Causa: \\n\\n");	

	vsprintf(msj2,formato,lista_param_variable);
	v10log(LOGERROR,"%s",msj2);
	v10carespeciales(msj2,'\\',"\\\\"); 

	strcat(msj,msj2);
	if (*file) sprintf(msj+strlen(msj),"\\n\\nFichero: %s Linea: %d",v10carespeciales(file,'\\',"\\\\"),line);  
	if (salir) {
		strcat(msj,"\\n\\nPrograma abortado, pulse Aceptar para finalizar");
		exitencurso=1;
		if (prefinal) prefinal(msj);
		exitencurso=0;
	} else {
		if (!wwwwarning_time) {
			strcat(msj,"\\n\\nPara continuar, pulse Aceptar");
			if (prewarning) prewarning(msj);
		}
		else {
			v10horas conta = gettime();
			while ((gettime()-conta < wwwwarning_time) && ((hay_tecla()==0)));
		}
	}
	v10wwwmensajegen("Mensaje de Error",msj);
	if (salir) exit(1);
}
