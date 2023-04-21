#include "v10wwwform.h"
#define MAXHANDLERS 50

static evhandlers evhdls[MAXHANDLERS];
static int nbhdls=0,ponatexit=0;


static void v10delhandler(void) 
{
	while (nbhdls>0) {
		free(evhdls[nbhdls].ev);	
		nbhdls--;	
	}
}

void v10addhandler(char *ev,int (*fun)(v10dialogs *v,v10httpeventos *),int esajax) 
{
	if (nbhdls==MAXHANDLERS) {
		final(("No se pueden añadir mas manejadores de eventos"));
		return;
	}
	if (ponatexit==0) {
		atexit(v10delhandler);		
		ponatexit=1;
	}
    evhdls[nbhdls].ev = strdup(ev);
    evhdls[nbhdls].fun = fun;
    evhdls[nbhdls].esajax = esajax;
	nbhdls++;

}



evhandlers *v10gethandler(char *ev) 
{
	int i;
	for (i=0;i<nbhdls;i++) {
		if (!stricmp(ev,evhdls[i].ev)) return evhdls+i;
	}
	return(NULL);
}



