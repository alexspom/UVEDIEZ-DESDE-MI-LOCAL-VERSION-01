#include "vd.h"

#define CSETHOST "BEGIN VDUSER.SETHOSTNAME(:HOST);END;"
static v10cursors *vdsethost;

void ponhostname(void)
{	
	char hostname[MAXPATH]="";
	
	strcpy(hostname,damehostname());
	vdsethost=abrecursordebug(CSETHOST,0);
	bindtodo(vdsethost,"HOST",hostname,sizeof(hostname),V10CADENA,		               
						NULL);
	ejecutacursor(vdsethost);	
    liberacursor(vdsethost);
    vdsethost=NULL;
}

void ponhostnameext(char *hostname)
{	
	vdsethost=abrecursordebug(CSETHOST,0);
	bindtodo(vdsethost,"HOST",hostname,strlen(hostname)+1,V10CADENA,		               
						NULL);
	ejecutacursor(vdsethost);	
    liberacursor(vdsethost);
    vdsethost=NULL;
}