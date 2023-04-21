#include "v10wwwform.h"

int recibidologin=0;
static int windowcreada=0;

int v10openbrowserwindow() 
{
    *v10html = 0;
	recibidologin=0;
	if (windowcreada) return(0);
	windowcreada=1;
	strcat(v10html,"<html><head><title>Grupo V10 Software</title></head>");
	strcat(v10html,"<BODY language=\"javascript\">");
	sprintf(v10html+strlen(v10html),"<script>window.open('%s','%d','scrollbars=no,status=yes,toolbar=no,location=no,menubar=no,resizable=no,directories=no,width=%dpx,height=%dpx,alwaysRaised=no'); </script>", 
		"v10.html",getpid(),v10htmlconf.resolucionx,v10htmlconf.resoluciony); //"v10.html" // top.close();
	strcat(v10html,"</BODY></HTML>");
	v10httprespuesta(OK,v10formserver,NULL,v10html,NULL,0);
	while (recibidologin==0)  Sleep(10);
	v10log(LOGNORMAL, "%s", "Recibida peticion openbrowser\n");
	return(1);
}


    int v10wwwabrelink(char *link) 
{
	v10wwwmensajeabrelink(link);
	return(0);
}