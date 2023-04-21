/**************************************************************************
* Módulo : borralog.c													  *
* Función: Borrar ficheros con más antiguos que las horas especificadas   *
* Autor	:  												                  *
* Fecha  : 01-04-2009													  *
***************************************************************************
*Histórico de cambios
********************
****************************************************************************/
#include "v10.h"
	
int main(int argc,char *argv[])
{
	char file1[MAXPATH],file2[MAXPATH];
	int inicio,tam;
	FILE *entrada,*salida;
	char *buffer;
	if (argc<5) final(("Us0 fichero_origen fichero_dest inicio bloques"));
	strcpy(file1,argv[1]);
	strcpy(file2,argv[2]);
	inicio=atoi(argv[3]);
	tam=atoi(argv[4]);
	entrada=fopen(file1,"rb");
	salida=fopen(file2,"r+b");
    buffer=calloc(tam,8192);
	fseek(entrada,inicio*8192,SEEK_SET);
	fseek(salida,inicio*8192,SEEK_SET);
	fread(buffer,8192,tam,entrada);
	fwrite(buffer,8192,tam,salida);
	fclose(entrada);
	fclose(salida);
	return(0);
}


int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
                   LPSTR cmd, int cmdshow)
{
    int ret;
	strcpy(TITULOVENTANA,"BORRADOR DE LOGs V10. VERSION 1.0");    
	initv10lib(hinst,hprev);
    trataparamstd(_argc,_argv,trataparammain,NULL,NULL);
    ret=main(_argc,_argv);
    return(ret);
}


