/*
* Módulo : V10editorv10.C
* Objeto:  Invocacion de editorv10 externo de ficheros
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

char *editorv10;
int editormonofichero;

#ifndef __LINUX__

int ejecutacomando(char *cadena, char flags, char *dirini)
{
	int ret;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	memset(&si,0,sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = flags;
	ret = CreateProcess(NULL, cadena,  NULL, NULL, FALSE, 0, NULL, dirini, &si, &pi); 
	return (ret);
}
#endif

void vinvocaeditor(char *fichero,va_list arg)
{
	char comando[MAXCADENA];
    if (editorv10==NULL) {
       editorv10=getenv("V10EDITOR");
       if (editorv10==NULL) {
           editorv10="NOTEPAD";
           editormonofichero=1;
       } else {
           editormonofichero=0;
       }
    }
    if (editormonofichero==0) sprintf(comando,"\"%s\"",editorv10);
	do {
        if (editormonofichero) {
           sprintf(comando,"\"%s\" \"%s\"",editorv10,fichero);
           ejecutacomando(comando, SW_SHOW, NULL);
         } else {
		  sprintf(comando+strlen(comando)," \"%s\"",fichero);
         }
	} while ((fichero=va_arg(arg,char *))!=NULL);
    if (editormonofichero==0) ejecutacomando(comando, SW_SHOW, NULL);
}

void invocaeditormultiple(char **fichero,int numfich)
{
	char comando[MAXCADENA];
    int i;
    if (editorv10==NULL) {
       editorv10=getenv("V10EDITOR");
       if (editorv10==NULL) {
           editorv10="NOTEPAD";
           editormonofichero=1;
       } else {
           sprintf(comando,"\"%s\"",editorv10);
           editormonofichero=0;
       }
    }
    if (editormonofichero==0) sprintf(comando,"\"%s\"",editorv10);
    for (i=0;i<numfich;i++) {
        if (editormonofichero) {
           sprintf(comando,"\"%s\" \"%s\"",editorv10,fichero[i]);
           ejecutacomando(comando, SW_SHOW, NULL);
         } else {
		  sprintf(comando+strlen(comando)," \"%s\"",fichero[i]);
         }
	}
    if (editormonofichero==0) ejecutacomando(comando, SW_SHOW, NULL);
}

void invocaeditor(char *fichero,...)
{
	va_list arg;
	va_start(arg,fichero);
	vinvocaeditor(fichero,arg);
	va_end(arg);
}