#include "vd.h"

/* 2. SERVICE_AUTO_START; A service started automatically by the service control manager during system startup. For more information, see Automatically Starting Services.
   3. SERVICE_DEMAND_START; A service started by the service control manager when a process calls the StartService function. For more information, see Starting Services on Demand.
   4. SERVICE_DISABLED; A service that cannot be started. Attempts to start the service result in the error code ERROR_SERVICE_DISABLED.
*/

char nombreservicio[MAXCADENA]="";
char descripcion[MAXCADENA]="";
char ejecutable[MAXCADENA]="";
int modoarranque=2;
int borrar=0;
char ulterror[MAXCADENA]="";

char *damerror() {
	DWORD err;
	*ulterror=0;
	err=GetLastError();
	if (err>0) FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,err,0,ulterror,1000,NULL);
	return(ulterror);
}

static void borraservicio() {

   SC_HANDLE hService;

   // Open the SCM on this machine.
   SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);

   v10log(LOGNORMAL,"Intentando borrar servicio %s\n", nombreservicio);
    
   hService= OpenService(hSCM,nombreservicio,DELETE);
   if (hService==NULL) {
	 v10log(LOGERROR,"Error borrando servicio %s\n\tNo puedo acceder al servicio\n",nombreservicio);
	 return;
   }

   if (DeleteService(hService)==0) v10log(LOGERROR,"Error borrando servicio %s\n. %s",nombreservicio,damerror());
   else v10log(LOGNORMAL,"Borrado servicio %s\n",nombreservicio);
   
   // Close the service and the SCM
   CloseServiceHandle(hService);
   CloseServiceHandle(hSCM);
}

static void descripcionservicio() {
   SERVICE_DESCRIPTION desc;
   SC_HANDLE hService;

   // Open the SCM on this machine.
   SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);

   v10log(LOGNORMAL,"Intentando cambiar descripción de servicio %s\n", nombreservicio);
    
   hService= OpenService(hSCM,nombreservicio,SERVICE_CHANGE_CONFIG);
   if (hService==NULL) {
	 v10log(LOGERROR,"Error cambiando descripción de servicio servicio %s\n\tNo puedo acceder al servicio\n",nombreservicio);
	 return;
   }
   
   if (*descripcion) {
	   memset(&desc,0,sizeof(SERVICE_DESCRIPTION));
	   desc.lpDescription=strdup(descripcion);
	   if (ChangeServiceConfig2(hService,1,&desc)==0) v10log(LOGERROR,"Error cambiando la descripción del servicio\n\t%s",damerror());
	   else v10log(LOGNORMAL,"Cambiada la descripción del servicio\n");
	   free(desc.lpDescription);
   }
   
    
   // Close the service and the SCM
   CloseServiceHandle(hService);
   CloseServiceHandle(hSCM);
}


static void creaservicio() 
{
   SC_HANDLE hService;

   // Open the SCM on this machine.
   SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);

   v10log(LOGNORMAL,"Intentando crear servicio %s con ejecutable %s y modo de arranque %d\n",
	    nombreservicio, ejecutable, modoarranque);

   // Add this service to the SCM's database.
   hService = CreateService(hSCM, nombreservicio, nombreservicio, 0,
      SERVICE_WIN32_OWN_PROCESS, modoarranque, SERVICE_ERROR_IGNORE, 
      ejecutable, NULL, NULL, NULL, NULL, NULL);
   
   if (hService==NULL) v10log(LOGERROR,"Error creando servicio\n\t%s",damerror());
   else v10log(LOGNORMAL,"Creado servicio %s con ejecutable %s y modo de arranque %d\n",
			nombreservicio, ejecutable, modoarranque);
   
   // Close the service and the SCM
   CloseServiceHandle(hService);
   CloseServiceHandle(hSCM);
   descripcionservicio();
}


int trataparamservicio(char *cadena)
{
	if (toupper(*cadena)=='S')
		switch (toupper(cadena[1])) {
			case 'N' : strcpy(nombreservicio,strmay(cadena+2));
			     	   break;
			case 'C' : borrar=0;
					   break;
			case 'B' : borrar=1;
					   break;
			case 'D' : strcpy(descripcion,cadena+2);
					   break;
			case 'E' : strcpy(ejecutable,cadena+2);
					   break; 
			case 'A' : modoarranque=atoi(cadena+2);
					   break;
	}
    return(0);
}

/*
-Nnombre
-Eejecutable
-Amodo arranque
*/
int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
                   LPSTR cmd, int cmdshow)
{
	initv10lib(hinst,hprev);
    trataparamstd(__argc,__argv,trataparammain,trataparamservicio,NULL);
	if (borrar==1) borraservicio();
    else creaservicio();
	do {
		if (hay_tecla() && tecla()==A_F(10)) break;
		Sleep(10);
	} while (1);
    return(0);
}