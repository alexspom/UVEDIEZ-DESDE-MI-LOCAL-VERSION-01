/*
* M�dulo : V10MENSAJE.C
* Objeto:  Presenta mensajes en pantalla
*
*
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

int MENSAQUITATRIGERTIMEOUT = 0;
int MENSAQUITATRIGERVIVO = 0;
int debugmsg=0;

void datoslinmsg(char *origen,char *destino,int *maxlen,int *numlin)
{
    char *ptr=origen;
    int lon=0,lin=1,posx=0;
    while (*ptr) {
	    if (*ptr == '\\' && (ptr[1] == 'n' || ptr[1] == 'r')) {
            if (destino) *destino++='\n';
            lin++;
            ptr+=2;
            posx=0;
            continue;
        }
	    if (*ptr == '\n' || *ptr == '\r') {
            if (destino) *destino++='\n';
            lin++;
            posx=0;
            ptr++;
            continue;
        }
        if (destino) *destino++=*ptr;
        ptr++;
        posx++;
        if (posx>lon) lon=posx;
    }
    if (maxlen) *maxlen=lon;
    if (numlin) *numlin=lin;
    if (destino) *destino=0;
}


int STDconfirmasn(int x,int y,char *cadena)
{
    int i,cx,cy,longitud;
    int si = 0;
    int salir = 0;
    windows w;
    unsigned timeout;
    void *triger;
    void *trigervivo;
    int raton=0;
    int lin;  //(1)

    if (MENSAQUITATRIGERTIMEOUT) {
        dametimeoutteclado(&timeout,&triger);
        timeoutteclado(0,NULL);
    }
    if (MENSAQUITATRIGERVIVO) {
        trigervivo=dametrigervivo();
        pontrigervivo(NULL);
    }
    poncolorv(&w,CNORMAL);
    datoslinmsg(cadena,cadena,&longitud,&lin);
    creaventana("CONFIRMACION",&w,x,y,x+longitud,y+lin+2,"MENSAJES");
    v10printf(&w," ");
    v10printf(&w,cadena);
    v10printf(&w,"\n\n");
    pos_curv(&w,&cx,&cy);
    while(!salir) {
        pon_curv(&w,cx,cy);
        poncolorv(&w,CNOENTER);
        for(i=0;i<(longitud-7-longitud%2)/2;i++) v10printf(&w," ");
        if (si) {
            if (raton) poncolorv(&w,CINPUTINAC);
            else poncolorv(&w,CINPUTACT);
        } else {
            poncolorv(&w,CNOENTER);
        }
        v10printf(&w,v10translate(" SI "));
        poncolorv(&w,CNORMAL);
        if (longitud%2) v10printf(&w," ");
        v10printf(&w," ");
        if (!si) {
            if (raton) poncolorv(&w,CINPUTINAC);
            else poncolorv(&w,CINPUTACT);
        } else {
            poncolorv(&w,CNOENTER);
        }
        v10printf(&w,v10translate(" NO "));
        raton=0;
        switch(STDtecla()) {
           case 's':
           case 'S': si=1;
                     salir=1;
                     break;
           case 'n':
           case 'N': si=0;
                     salir=1;
                     break;
           case cr: salir=1;
                    break;
           case esc: si=-1;
                     salir=1;
                     break;
           case cui:
           case cud: si=!si;
                     poncolorv(&w,CNORMAL);
                     break;
           case MOUSEPOS: if (mousepos.posx>=((longitud-7-longitud%2)/2) && mousepos.posx<=(((longitud-7-longitud%2)/2)+3) && mousepos.posy==2+lin-1) {
                             raton=1;
                             si = 1;
                             if (mousepos.action==DOBLECLICK) salir=1;
                          }
                          if (mousepos.posx>=(((longitud-7-(longitud+1)%2)/2)+5) && mousepos.posx<=(((longitud-7-(longitud+1)%2)/2)+8) && mousepos.posy==2+lin-1) {
                             raton=1;
                             si = 0;
                             if (mousepos.action==DOBLECLICK) salir=1;
                          }
                          break;
        }
    }
    if (MENSAQUITATRIGERTIMEOUT) timeoutteclado(timeout,triger);
    if (MENSAQUITATRIGERVIVO) pontrigervivo(trigervivo);
    liberaventana(&w);
    return(si);
}


int confirmasnf(int x,int y,char *cadena,...)
{
    va_list arg;
    char *buffer;
    int ch;
    buffer=(char *)calloc(1,MAXCADENA);
    va_start(arg,cadena);
    cadena=v10translate(cadena);
    vsprintf(buffer,cadena,arg);
    ch=confirmasn(x,y,buffer);
    va_end(arg);
    free(buffer);
    return(ch);
}


int confirmasnfc(int y,char *cadena,...)
{
    va_list arg;
    char *buffer;
    unsigned x,ch;

    buffer=(char *)calloc(1,MAXCADENA);
    va_start(arg,cadena);
    cadena=v10translate(cadena);
    vsprintf(buffer,cadena,arg);
    datoslinmsg(buffer,NULL,&x,NULL);
    if (COLUMNASPANTALLA-2>x) x=(COLUMNASPANTALLA-x)/2;
    else x=1;
    ch=confirmasn(x,y,buffer);
    va_end(arg);
    free(buffer);
    return(ch);
}


void STDvmensajefm(int x,int y,char *cadena,va_list arg)
{
    windows vmensaje;
    char *buffer;
    unsigned timeout;
    void *triger;
    void *trigervivo;
    int ok = 0;
    int lon,lin;

    if (MENSAQUITATRIGERTIMEOUT) {
        dametimeoutteclado(&timeout,&triger);
        timeoutteclado(0,NULL);
    }
    if (MENSAQUITATRIGERVIVO) {
        trigervivo=dametrigervivo();
        pontrigervivo(NULL);
    }
    buffer=(char *)calloc(1,MAXCADENA);
        cadena=v10translate(cadena);
        vsprintf(buffer,cadena,arg);
    datoslinmsg(buffer,buffer,&lon,&lin);
    creaventana("Mensaje",&vmensaje,x,y,x+max(lon,9)-1,y+1+lin,"MENSAJES");
    poncolorv(&vmensaje,CNORMAL);
    v10printf(&vmensaje,"%s",buffer);
    pon_curv(&vmensaje,max(lon,9)/2-2,1+lin);
    poncolorv(&vmensaje,CINPUTACT);
    v10printf(&vmensaje," %s ",v10translate("OK"));
	do {
        switch(STDtecla()) {
          case cr: ok = 1;
				   debugmsg=-1;	
                   break;
          case MOUSEPOS: if (mousepos.posx>=(max(lon,9)/2-2) && mousepos.posx<=(max(lon,9)/2+1) && mousepos.posy==1+lin) {
                            if (mousepos.action==DOBLECLICK) ok = 1;
                          }
						 debugmsg=-1;				
						 break;
		  case A_F(1):  {
						if (debugmsg==0) 	debugmsg=1;	
						else  debugmsg=0;
						ok=1;
					}
        }
    } while(!ok);
    pon_curv(&vmensaje,max(strlen(buffer),9)/2-2,2);
    poncolorv(&vmensaje,CINPUTINAC);
    v10printf(&vmensaje," %s ",v10translate("OK"));
    liberaventana(&vmensaje);
    free(buffer);
    if (MENSAQUITATRIGERTIMEOUT) timeoutteclado(timeout,triger);
    if (MENSAQUITATRIGERVIVO) pontrigervivo(trigervivo);
}

void mensajefm(int x,int y,char *cadena,...)
{
    va_list arg;
    va_start(arg,cadena);
    vmensajefm(x,y,cadena,arg);
    va_end(arg);
}

void vmensajefcm(int y,char *cadena,va_list arg)
{
    char *buffer;
    unsigned x,lon;

    buffer=(char *)calloc(1,MAXCADENA);
    cadena=v10translate(cadena);
    vsprintf(buffer,cadena,arg);
    datoslinmsg(buffer,NULL,&lon,NULL);
    if (COLUMNASPANTALLA-2>lon) x=(COLUMNASPANTALLA-lon)/2;
    else x=1;
    mensajefm(x,y,buffer,NULL);
    free(buffer);
}

void mensajefcm(int y,char *cadena,...)
{
    va_list arg;
    va_start(arg,cadena);
    vmensajefcm(y,cadena,arg);
    va_end(arg);
}

void mensajesistema(long err)
{
    char buffer[MAXCADENA];
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,err,0,buffer,1000,NULL);
    mensajefcm(10,buffer);
}

void dameerrsistema(long err,char *donde)
{
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,err,0,donde,1000,NULL);
}


