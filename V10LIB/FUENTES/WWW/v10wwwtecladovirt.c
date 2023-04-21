#include "v10wwwform.h"

#define IMGTECVIRT "<img  src=\"../img/teclado.png\" NOTAB onclick=\"v10lib.muestratecladovirt()\" style=\"z-index:9999;position:relative;width:40px;left:975px;top:12px;\">\n"

void v10cargatecladovirtual(void) {
	char *ptrini,*ptrfinal,textoinclude[MAXCADENAHTML];	

	if (v10httpconf.tecladovirtual) {
		if (!strstr(v10html,PATRONTECLADOVIRTUAL)) return;
        *textoinclude = 0;
        *v10datoshtml = 0;
		leefichero("tecladovirtual.html",v10datoshtml);
		ptrini=strstr(v10datoshtml,INCLUDEDATA);
		ptrfinal=strstr(v10datoshtml,ENDINCLUDEDATA);
		if (ptrini && ptrini) strcopia(textoinclude,ptrini+strlen(INCLUDEDATA),ptrfinal-(ptrini+strlen(ENDINCLUDEDATA))+1);	
		v10reemplazapatron(v10html,PATRONTECLADOVIRTUAL,textoinclude,1);	
		if (strstr(v10html,PATRONIMGTECLADOVIRTUAL)) v10reemplazapatron(v10html,PATRONIMGTECLADOVIRTUAL,IMGTECVIRT,1);
	}
}