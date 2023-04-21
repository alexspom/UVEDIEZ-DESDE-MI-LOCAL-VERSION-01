#include "../execproc/vdexec.h"

VDEXPORT void vdserverAJAX(procesos *proceso) {
	char fichero[MAXPATH]="v10listener.cfg"; 	
	int ret;

	if (*proceso->proc.param) piece(proceso->proc.param,fichero,"#",1); 
	v10serverAJAX(fichero);
	do {	
		if (hay_tecla()) ret=tecla();
		Sleep(1);
	} while (1);
	
}

VDEXPORT int includefichero(char *param,char *html) {
	FILE *entrada;
	int lon;
	*html = 0;

	entrada=fopenpath(param,"r");
	if (!entrada) {
		sprintf(html,"Error: no se encuentra fichero %s\n",param);
		return(0);
	}
	fseek(entrada,0,SEEK_END);
	lon=ftell(entrada);
	fseek(entrada,0,SEEK_SET);
	fread(html,lon,1,entrada);
	fclose(entrada);
	return(lon);

}