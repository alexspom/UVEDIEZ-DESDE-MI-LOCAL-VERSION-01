#include "vdservisu.h"

// ejecución automática de un servicio
#define MAXVISU 50
#define IDDLE		0
#define CONECTADO	1

typedef struct {
	v10socks *servidor;
	int status;	
} visuconexs;

static servidorsocks *servidorvisu;
static visuconexs vc[MAXVISU];

static void tratacomandovisu(int ncliente,visuconexs *mivc) {

	char buffer[MAXCADENA], bufferdest[MAXCADENA],tecla[3]="  ",ch;
	static int lon=0,tec;
	static int encomando=0;
	
	if (v10sockhaycar(mivc->servidor)) Sleep(100);
	while (v10sockhaycar(mivc->servidor)) {	
		if (encomando==0) {
			lon=v10sockread(mivc->servidor,tecla,sizeof(short));
			tec=*((short *)tecla);
			lon=0;
			if (tec==ALT('M')) {				
				memset(buffer,0,MAXCADENA);	
				encomando=1;
			} 
		} else {
			ch=v10socksigcar(mivc->servidor);
			if (ch=='$') {
				encomando=0;
				break;
			} else buffer[lon++]=ch;
		}
	}
	if (encomando==0 && lon) {
		if (strstr(trim(buffer),"MENU")) {			
			servicios2char(bufferdest);
			tec=ALT('M');
			v10sockescribe(mivc->servidor,&tec,sizeof(short));
			v10sockprintf(mivc->servidor,bufferdest);
			v10log(LOGNORMAL,"Cliente visualiza %d solicita menu de servicios\n",ncliente+1);
		}	
	}
}


static void trataconexiones(void) {
	visuconexs *mivc;
	int i;

	for (i=0;i<MAXVISU;i++) {
		mivc=vc+i;
		if (mivc->status==CONECTADO) {
			if (mivc->servidor->status==STSOCKROTA) {
				v10socklibera(mivc->servidor);
				memset(mivc,0,sizeof(visuconexs));
				v10log(LOGNORMAL,"Se cierra conexión de cliente visualiza %d\n",i+1);
				continue;
			}
			if (v10sockhaycar(mivc->servidor)>0) tratacomandovisu(i,mivc);			
		}
	}
}

static int nuevaconexion(v10socks *s) {
	int i;
	for (i=0;i<MAXVISU;i++) {
		if (vc[i].status==IDDLE) {
			vc[i].servidor=s;
			vc[i].status=CONECTADO;
			v10log(LOGNORMAL,"Creada conexion de cliente visualiza número %d\n",i+1);
			return(0);
		}
	}
	v10log(LOGERROR,"%s","No hay mas conexiones de visualizaciones disponibles\n");
	return(-1);
}

void tratavisualiza(void *a) 
{
	v10socks *nuevocliente;
	char cservervisu[10]="";
	servidorvisu=NULL;
	memset(vc,0,sizeof(visuconexs)*MAXVISU);
	sprintf(cservervisu,"%d", servervisu);
	do { 
		servidorvisu=v10socknuevoservidor(cservervisu,0,NULL,NULL,NULL,NULL,NULL);
		if (!servidorvisu) v10log(LOGERROR,"Error arrancando servidor de visualizadores, en puerto %d\n",servervisu);
		else  v10log(LOGNORMAL,"Arrancado servidor de visualizadores, en puerto %d\n",servervisu);
	} while (!servidorvisu);
	 
	do {
		Sleep(10);
		hay_tecla();
		nuevocliente=v10sockdameconexion(servidorvisu);
		if (nuevocliente) nuevaconexion(nuevocliente);
		trataconexiones();
	} while (1);
}

void cierraservervisualiza(void) {
	/*int i;
	if (servidorvisu) v10sockcierraservidor(servidorvisu);
	for (i=0;i<MAXVISU;i++) {
		if (vc[i].status!=IDDLE && vc[i].servidor) {
			v10socklibera(vc[i].servidor);
			vc[i].status=IDDLE;
		}
	}*/
}