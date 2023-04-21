#include "v10wwwform.h"

void sidebarMenu(void) {	
	leefichero("v10sidebar.html",v10datoshtml);
	v10reemplazapatron(v10html,PATRONSIDEBAR,v10datoshtml,1);
}

void sidebarForm(void) {
	leefichero("v10sidebar.html",v10datoshtml);
	v10reemplazapatron(v10html,PATRONSIDEBAR,v10datoshtml,1);	
}
