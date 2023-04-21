/*
* Módulo :  v10httpget.c
* Objeto:   Trata comando http GETs enviados por el cliente
* 
* 
* Autor	 : Francisco José Guerrero Sánchez
* Fecha  : 25-09-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10wwwform.h"

int atiendeGET(int numsesion,v10sockssls *v10server, char *peticion, int eslistener,int soloheader) 
{	
	char cadenaacceso[MAXCADENA],*inacceso;
	char fichero[MAXPATH]="";	
	char *inifichero,*finfichero,*ptr;
	if (strstr(peticion,"GET / HTTP/1.1")) return(funcdebug(numsesion,v10server,"No se puede acceder al root del servidor Web"));
	if (strstr(peticion,"..")) return(funcdebug(numsesion,v10server,"No se puede incluir .. en el URL solicitado"));
//	sprintf(cadenaacceso,"GET /%s",v10httpconf.acceso);	
    sprintf(cadenaacceso, "/%s", v10httpconf.acceso);
    if (strstr(peticion, "ajax")) return(atiendeGetAJAX(numsesion, v10server, peticion));
	// es la página de entrada en la aplicación en el listener
	if ((inacceso=strstr(strmay(peticion),strmay(cadenaacceso))))  {
        if (inacceso - peticion < 20) {
            if (eslistener) {
                creav10form(numsesion);
                Sleep(1000);
                v10httprespuesta(SEE_OTHER, v10server, NULL, NULL, NULL, 0);
                s[numsesion].status = STFIN;
                return(0);
            } else { // peticion inicial de entrada en v10form.exe
		    	v10log(LOGNORMAL, "%s", "Recibida cadena de acceso\n");    
                v10formserver = v10server;
                recibidologin = 1;
                return(0);
            }
        }
	}
	inifichero=strchr(peticion,'/')+1;
	finfichero=strstr(inifichero,"HTTP");
	strcopia(fichero,inifichero,(int)(finfichero-inifichero));
	v10log(LOGNORMAL,"Sesion %d Solicita Fichero %s\n",numsesion,fichero);
	trim(fichero);
	if ((ptr=strchr(fichero,'&'))) *ptr=0; // elimino la parte de ?HOST&
	if (eslistener) {
		if (stricmp(fichero,v10httpconf.rutainicial) && 
			  stricmp(fichero,v10httpconf.libreriaV10) /*&& stricmp(fichero+1,v10httpconf.libreriamenuV10) && stricmp(fichero+1,v10httpconf.ficheromenujs)*/) {
            char msg[MAXPATH];
            sprintf(msg, "El fichero %s solicitado no está permitido enviarlo", fichero);
			return(funcdebug(numsesion,v10server,msg));
		}
	}
	traduceutf8(fichero);
	v10log(LOGNORMAL,"Sesion %d Enviara Fichero %s\n",numsesion,fichero);
#ifndef __LINUX__    
	if (strstr(fichero,"AYUDA.HTML&")) capturatopicayuda(fichero);
	if (strstr(fichero,"AYUDAINDICE.HTML")) v10indiceayuda(OK,v10server,fichero);	
	if (strstr(fichero,"AYUDACONTENIDO.HTML")) v10contenidoayuda(OK,v10server,fichero);
	else 
#endif
        return(v10httprespuesta(OK,v10server,fichero,NULL,NULL,soloheader));
	return(0);
}
