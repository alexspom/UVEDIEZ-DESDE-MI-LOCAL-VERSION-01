/*
* Módulo :  v10wwwforcon.c
* Objeto:   Asignación de número a conexionesdel v10form.exe
* 
* 
* Autor	 : Francisco José Guerrero Sánchez
* Fecha  : 25-09-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10wwwform.h"

#ifndef __LINUX__
#pragma data_seg(".shared")
#endif

static int PUERTOSENUSO[MAXV10FORMS]={0};

#ifndef __LINUX__
#pragma data_seg()
#pragma comment(linker, "/SECTION:.shared,RWS")
#endif

void v10liberacon(int i)
{
	if (i>=0 && i< MAXV10FORMS) {
		PUERTOSENUSO[i]=0;
	}
}

int v10querycon(int port)
{
	int i,n=0;
	for (i=0;i<MAXV10FORMS;i++) {
		if (PUERTOSENUSO[i]==port) n++;
	}
	return(n);
}

static int checkpuerto(int puerto)
{
    SOCKET soc;
    struct sockaddr_in sin;
    int err;
    short port;
    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr=INADDR_ANY;
    port=htons(puerto);
    sin.sin_port=port;
    soc=socket(AF_INET,SOCK_STREAM,0);
    err=bind(soc,(struct sockaddr*)&sin,sizeof(sin));
    if (err) {
       v10log(LOGERROR,"Haciendo bind en puerto % error %d\n",puerto,err);
       closesocket(soc);
       return(-1);
    }
    closesocket(soc);
    return(0);
}


int v10damecon(int port)
{
	int i;
	for (i=0;i<MAXV10FORMS;i++) {
		if (PUERTOSENUSO[i]==0) {
			PUERTOSENUSO[i]=port;			
            if (checkpuerto(port+i)==0)return(i);
		}
	}
	return(-1);
}


