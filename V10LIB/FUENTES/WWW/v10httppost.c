/*
* M�dulo :  v10httppost.c
* Objeto:   Trata comando http POSTs enviados por el cliente
* 
* 
* Autor	 : Francisco Jos� Guerrero S�nchez
* Fecha  : 25-09-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10wwwform.h"

static v10sockssls *sockeventohttp;
static v10httpeventos v10newev; // evento recibido
static int hayeventohttp;

#define SESION		"sesion="
#define OBJETO		"idobjeto="
#define EVENTO		"evento="
#define VALOR		"valor="
#define ANTID		"antid="
#define ANTVALOR	"antvalor="
#define FINPOST		"%26FINPOST%26"
#define SEPARADOR	'&'

static void extradata2campoi(char *extradata,char *campo,char *valor) 
{
	char *ptr,*ptrf;
	*valor=0;
	ptr=strstr(extradata,campo);
	if (!ptr) return; 
	ptrf=strchr(ptr+strlen(campo),SEPARADOR);
	if (!ptrf) return; 
	ptr+=strlen(campo);
	if (ptr==ptrf) return;
	strcopia(valor,ptr,(int)(ptrf-ptr));
	//	v10log(LOGNORMAL,"Asignado valor %s a campo %s\n",valor,campo);
}


static void extradata2campos(char *extradata) 
{
    extradata2campoi(extradata,SESION,v10newev.sesion);
	extradata2campoi(extradata,OBJETO,v10newev.objeto);
	extradata2campoi(extradata,EVENTO,v10newev.evento);
	extradata2campoi(extradata,VALOR,v10newev.valor);
	extradata2campoi(extradata,ANTID,v10newev.antid);
	extradata2campoi(extradata,ANTVALOR,v10newev.antvalor);
}


static int extradata2newev(char *extradata) 
{
	char *ptr;
	int off=strlen(FINPOST);
	char buffer[MAXCADENA]="";
	ptr=strstr(extradata,FINPOST);
	if (!ptr) return(-1);
	*buffer=0;
	if (strlen(ptr+off)>0) strcpy(buffer,ptr+off);
	*ptr=SEPARADOR;
	*(ptr+1)=0;
	extradata2campos(extradata);
	if (strlen(buffer)) strcpy(extradata,buffer);
	else *extradata=0;
	return(0);
}

int v10httpesperaevento(v10dialogs *v,v10httpeventos *_v10ev,int enajax)
{
	static v10horas tiempoinicial;
	tiempoinicial=damecent();
	do {
        bloques *b;
        b=v10damebloqueactual();
        if (b) {
            int na;
            for (na=0;na<b->nbajax;na++) {
                v10ajax *ajax=b->ajax+na;
                if (b->ajaxactivo) {
                    if (damecent()-ajax->ultimaeje>ajax->frecuencia) {
                        v10httpeventos ev;
                        ev.b=ajax->b;
                        strcpy(ev.antvalor,ajax->id);
                        strcpy(ev.evento,"ajax");
                        ev.sock=b->ajaxsock;
                        v10evencolaevento(&ev);
                        b->ajaxactivo=0;
                    }
                }
            }
        }
		if (hay_tecla()){
			STDencolatecla(0);
		} 
        if (v10evencolados()) {
            if (enajax) return(0);
            else if (v10evencoladosnoajax()) return(0);
        }
		if (hayeventohttp == SEMAFON2) {
			v10log(LOGNORMAL, "%s", "Detectado evento\n");
            memcpy(_v10ev, &v10newev, sizeof(v10newev));
            _v10ev->sock = sockeventohttp;
            _v10ev->b = b;
			hayeventohttp=SEMAFIDDLE;
			break;
		}
		if (v10httpconf.tiempoespera>0 && damecent()-tiempoinicial>v10httpconf.tiempoespera*6000 ) {
			v10log(LOGNORMAL, "%s", "Sobrepasado tiempo de espera, se sale de la sesi�n\n");
			v10evencola("","Salir","","","");   
			return(-1);
		}
		Sleep(1);
	} while (1);
	return(1);
}


void atiendePOST(int numsesion, v10sockssls *v10server, char *peticion,char *extradata, int eslistener) 
{
    char cadenaacceso[MAXPATH] = "";
    v10log(LOGNORMAL, "AtiendePost: Server cambia de valor de %p a %p\n", v10formserver, v10server);
    v10formserver=v10server;
	//v10log(LOGNORMAL,"%s",peticion);
	if (!strstr(extradata, v10httpconf.idsesion) && eslistener) {
		funcdebug(numsesion,v10server,"No encontrado identificador de sesion");
		return;
    }
//    sprintf(cadenaacceso, "POST /%s HTTP/1.1", v10httpconf.acceso);
    sprintf(cadenaacceso, "POST %s/%s HTTP/1.1", es_blanco(v10httpconf.prefijoservicio) ? "" : "/", v10httpconf.acceso);
	if (!strstr(strmay(peticion),strmay(cadenaacceso)) && eslistener) {
		funcdebug(numsesion,v10server,"No encontrado cadena a acceso");
		return;
	}
	if (extradata2newev(extradata)==0) {
		hayeventohttp=SEMAFON1;
		sockeventohttp=v10server;
		hayeventohttp=SEMAFON2;
	}
}
