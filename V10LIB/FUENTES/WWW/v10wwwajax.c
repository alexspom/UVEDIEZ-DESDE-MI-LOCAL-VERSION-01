#include "v10wwwform.h"

#define SIDEBARAJAX "SIDEBAR"

static void llAJAX2HTML(bloques *b, v10ajax *ajax) 
{
	char idAJAX[MAXNOMBREV10]="";
	if (ajax->frecuencia<0) return;
    ajax->ultimaeje=0;
	sprintf(idAJAX,"AJAX%s",ajax->id);	
	sprintf(v10datoshtml+strlen(v10datoshtml),"var %s;\nif (v10lib) %s=v10lib.objAJAX();\n else %s=objAJAX();\nvar t%s;\n",idAJAX,idAJAX,idAJAX,idAJAX);	
	sprintf(v10datoshtml+strlen(v10datoshtml),"function leerDatos%s()\n{\n", idAJAX);
	sprintf(v10datoshtml+strlen(v10datoshtml),"   if (%s.readyState == 4) {\n", idAJAX);
	if (*(ajax->tipo)=='C') sprintf(v10datoshtml+strlen(v10datoshtml)," try {eval(%s.responseText); } catch (e) {};\n ", idAJAX);
	if (!es_blanco(ajax->objetojs)) sprintf(v10datoshtml+strlen(v10datoshtml),"    %s\n", ajax->objetojs);
	if (ajax->frecuencia>0)	sprintf(v10datoshtml+strlen(v10datoshtml),"    t%s = setTimeout('get%s()',%lf);\n", idAJAX, idAJAX,ajax->frecuencia*10);
	strcat(v10datoshtml,"   }\n}\n");
	sprintf(v10datoshtml+strlen(v10datoshtml),"function get%s()\n{\n", idAJAX);
    sprintf(v10datoshtml+strlen(v10datoshtml)," %s.open('GET',\"/ajax&%s&\");\n", idAJAX,ajax->id);
	sprintf(v10datoshtml+strlen(v10datoshtml),"   clearTimeout(t%s);\n   %s.onreadystatechange = leerDatos%s;\n   %s.send(null);\n}\n",idAJAX,idAJAX,idAJAX,idAJAX);
	sprintf(v10datoshtml+strlen(v10datoshtml),"get%s();",idAJAX);
}

static void conf2AJAXHTML(bloques *b,char *cad) 
{
	v10ajax aj;
	char ret[MAXCADENA]="";
	memset(&aj,0,sizeof(v10ajax));
	*ret=0;
	piece(cad,ret,";",1);
	aj.id=strdup(ret);
	*ret=0;
	piece(cad,ret,";",2);
	aj.objetojs=strdup(ret);
	*ret=0;
	piece(cad,ret,";",3);
	aj.tipo=strdup(ret);
	*ret=0;
	piece(cad,ret,";",4);
	aj.modulo=strdup(ret);
	*ret=0;
	piece(cad,ret,";",5);
	aj.nombre=strdup(ret);
	*ret=0;
	piece(cad,ret,";",6);
	aj.params=strdup(ret);
	*ret=0;
	piece(cad,ret,";",7);
	aj.frecuencia = atol(ret);
	llAJAX2HTML(b,&aj);
	free(aj.id);
	free(aj.tipo);
	free(aj.objetojs);
	free(aj.nombre);
	free(aj.modulo);
	free(aj.params);
}

void AJAXform2HTML(bloques *b) 
{
    int i;
    double minima = 99999999;
    b->ajaxactivo = 0;
    b->ajaxsock = NULL;
	if (b->sidebaroculto!=1 && 
		(v10httpconf.AJAXsidebarFRMvisible==2  || b->sidebaroculto==2)) {// SIDEBAR visible
		int found=0;
		for (i=0;i<b->nbajax;i++) {
			if (!strcmp(b->ajax[i].id,SIDEBARAJAX)) {
				found=1;
			}
		}
		// no se encuentra redefinido el AJAX del SIDEBAR
		if (found==0) conf2AJAXHTML(b,v10httpconf.AJAXsidebarFRM);
	}
	if (b->nbajax==0) return;
	for (i=0;i<b->nbajax;i++) {
		if (!strcmp(b->ajax[i].id,SIDEBARAJAX)) continue;
        if (b->ajax[i].frecuencia<minima) minima = b->ajax[i].frecuencia;
    }
    sprintf(v10datoshtml + strlen(v10datoshtml), "var ajaxsock;\nif (v10lib) ajaxsock=v10lib.objAJAX();\n else ajaxsock=objAJAX();\nvar tajaxsock;\n");
    sprintf(v10datoshtml + strlen(v10datoshtml), "function leerDatosajax()\n{\n");
    sprintf(v10datoshtml + strlen(v10datoshtml), "   if (ajaxsock.readyState == 4) {\n");
    sprintf(v10datoshtml + strlen(v10datoshtml),      " try {eval(ajaxsock.responseText); } catch (e) {};\n ");
//    if (!es_blanco(ajax->objetojs)) sprintf(v10datoshtml + strlen(v10datoshtml), "    %s\n", ajax->objetojs);
    sprintf(v10datoshtml + strlen(v10datoshtml),   "    tajaxsock = setTimeout('getajax()',%lf);\n", minima * 5);
    strcat(v10datoshtml,                          "   }\n}\n");
    sprintf(v10datoshtml + strlen(v10datoshtml), "function getajax()\n{\n");
    if (es_blanco(v10httpconf.prefijoservicio)) {
        sprintf(v10datoshtml + strlen(v10datoshtml), " ajaxsock.open('GET',\"/ajax&\");\n");
    } else {
        sprintf(v10datoshtml + strlen(v10datoshtml), " ajaxsock.open('GET',\"/srv%d/ajax&\");\n", v10httpconf.v10puertov10form % 1000);
    }
    sprintf(v10datoshtml + strlen(v10datoshtml), " clearTimeout(tajaxsock);\n"\
                                                 " ajaxsock.onreadystatechange = leerDatosajax;\n"\
                                                 " ajaxsock.send(null);\n"\
                                                 " }\n");
    sprintf(v10datoshtml + strlen(v10datoshtml), "getajax();");
}

void AJAXmenu2HTML() 
{
	if (v10httpconf.AJAXsidebarMENUvisible==2) {
		conf2AJAXHTML(NULL,v10httpconf.AJAXsidebarMENU);
	}
}
