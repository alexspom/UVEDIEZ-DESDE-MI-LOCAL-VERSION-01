#include "v10wwwform.h"

int leeficheropath(char *fichero,char *data) 
{
	FILE *entrada;
	long lon;
	entrada=fopenpath(fichero,"r");
	if (!entrada) {
		v10log(LOGNORMAL,"leeficheropath: No se encuentra fichero %s\n",fichero);
		return(0);
	}
	fseek(entrada,0,SEEK_END);
	lon=ftell(entrada);
	fseek(entrada,0,SEEK_SET);
	fread(data,lon,1,entrada);
	fclose(entrada);
	return(lon);
}

int leefichero(char *fichero,char *data) 
{
	FILE *entrada;
	int i;
	char miruta[MAXPATH]="",rutai[MAXPATH]="";
	long lon;
	for (i=1;i<=numpieces(v10httpconf.rutaplantillas,";");i++) {
		piece(v10httpconf.rutaplantillas,rutai,";",i);
		sprintf(miruta,"%s/%s",rutai,fichero);
        strmin(miruta);
		entrada=fopen(miruta,"rb");
		if (!entrada) continue;			
		fseek(entrada,0,SEEK_END);
		lon=ftell(entrada);
		fseek(entrada,0,SEEK_SET);
		fread(data,lon,1,entrada);
        data[lon] = 0;
		fclose(entrada);
		//v10log(1,"Cargado fichero %s \n",miruta);
		return(lon);
	}
	v10log(LOGDEBUG,"leefichero: No se encuentra fichero %s en ruta de plantilla %s\n",fichero,v10httpconf.rutaplantillas);
	return(0);
}

int v10cargaplantillahtml(char *plantillafrm,char *plantilladefecto,char *data) 
{
	if (plantillafrm) return(leefichero(plantillafrm,data));
	if (plantilladefecto) return(leefichero(plantilladefecto,data));
	return(-1);
}

void v10reemplazapatron(char *data,char *patron,char *texto,int elimina) 
{
	char *ptr,*ptr1;
	char buffer[MAXCADENAHTML]="";
	ptr=strstr(data,patron);
	if (!ptr) return;
	ptr1=ptr+strlen(patron);
	if (elimina) strcpy(buffer,ptr1);
	else         strcpy(buffer,ptr);
   // v10log(LOGNORMAL, "Reemplazapatron lon datos %d lon patron %d lon texto %d posicion %d\n", strlen(data), strlen(patron), strlen(texto), ptr - data);
	*ptr=0;
	strcat(data,texto);
	strcat(data,buffer);
}
