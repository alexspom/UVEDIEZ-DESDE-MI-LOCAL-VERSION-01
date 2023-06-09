/*
* M�dulo :  v10serverAJAX.c
* Objeto:   Servidor AJAX  de v10
* 
* 
* Autor	 : Francisco Jos� Guerrero S�nchez
* Fecha  : 13-06-2010

* MODIFICACIONES
* ---------------------------
*/
#include "v10wwwform.h"

extern servidorsockssls *v10nuevoservidor;

static v10ajax *dameajax(bloques *b,char *idajax)
{
    int na;
    for (na=0;na<b->nbajax;na++) if (strcmp(b->ajax[na].id,idajax)==0) return b->ajax+na;
    return NULL;
}


int trataajax(v10dialogs *v,v10httpeventos *ev)
{
    v10ajax *ajax;
    bloques *b;
    char respuesta[MAXCADENA]="";
    int ret;
    b=v10damebloqueactual();
    if (b==NULL)  {
        v10httprespuesta(OK,ev->sock,NULL,"",NULL,0);
        return(-1);
    }
    if (b!=ev->b) {
        v10httprespuesta(OK,ev->sock,NULL,"",NULL,0);
        return(-1);
    }
    ajax=dameajax(b,ev->antvalor);
    if (ajax==NULL) {
        v10httprespuesta(OK,ev->sock,NULL,"",NULL,0);
        return(-1);
    }
    if (strcmp(ajax->tipo,"Q")==0) {
        v10query2html(ajax->nombre, respuesta);
        v10httprespuesta(OK,ev->sock,NULL,respuesta,NULL,0);
        return(-1);
    }
    if (strcmp(ajax->tipo,"F")==0) {
        int (*func)(char *, char *)=NULL;
        func=damefundll(ajax->modulo,ajax->nombre);
        if (!func) sprintf(respuesta,"</BR></BR> <b><font size='2' face='Verdana' color='white'>Error: No se encuentra la funci�n %s en el m�dulo %s</font></b>",ajax->nombre,ajax->modulo);
           else func(ajax->params, respuesta);	
        v10httprespuesta(OK,ev->sock,NULL,respuesta,NULL,0);
        return(-1);
    }
    if (strcmp(ajax->tipo,"C")==0) {
        ret = v10cursor2html(ajax->nombre, ajax->params, respuesta);
        ajax->ultimaeje = damecent();
        if (ret>=0) {
           v10httprespuesta(OK,ev->sock,NULL,respuesta,NULL,0);
           b->ajaxactivo=0;
           b->ajaxsock=NULL;
        } else {
            b->ajaxactivo = 1;
            b->ajaxsock = ev->sock;
        }
        return(-1);
    }
    return(-1);
}

int atiendeGetAJAX(int numsesion,v10sockssls *v10server, char *peticion) 
{	
    char respuesta[MAXCADENA]="",accesoAJAX[MAXPATH]="";
    bloques *b=v10damebloqueactual();
    *respuesta = 0;
    // si eslistener y tiene proxy, envia see_other, al servidor y puerto, con esta conexi�n
    if (eslistener) {
        strcopia(accesoAJAX,peticion+5,(int)(strstr(peticion,"HTTP/1.") - (peticion +5)));		
        v10log(LOGNORMAL,"Reenv�o a SERVERAJAX con accesoAJAX=%s\0",accesoAJAX);
        return(v10httprespuesta(SEE_OTHER_AJAX,v10server,NULL,NULL,accesoAJAX,0));		
    } else { // si no, envia la respuesta, tras generar lo que corresponda, Query o Funci�n
        if (b) {
            b->ajaxactivo = 1;
            b->ajaxsock = v10server;
        }
	}
  return(0);
}

