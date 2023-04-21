#include "vd.h"

#define TIMEOUTLECT 500
v10socks *sck=NULL;

static vdinfolecturass ilt; 
static int sidinfolectura=0;
static v10horas ultlectura;
static int rota=0;

static void cierraconex (void)  
{
	if (sck) {
		v10socklibera(sck);
		sck=NULL;
	}
}

static int tickhard(void) 
{
    if (sck && sck->status==STSOCKREADY) {
        if (rota) {
            v10log(LOGNORMAL,"Red de Escaner %ld. Abierta conexión con el servidor %s:%s\n",sidinfolectura,ilt.dirip,ilt.puertotcp);
            rota=0;
        }
	    return(0);	
    }
	if (sck && sck->status==STSOCKROTA) {
		v10log(LOGNORMAL,"Red de Escaner %ld. Rota conexión con el servidor.Cierro Pipe %s:%s\n",sidinfolectura,ilt.dirip,ilt.puertotcp);
		v10socklibera(sck);
		sck=NULL;
        rota=1;
	}
	if (sck==NULL) {
        sck=v10socknuevocliente(ilt.dirip,ilt.puertotcp,0,4096,NULL,NULL,NULL,NULL,NULL);
        Sleep(100);
		if (sck && sck->status==STSOCKREADY) {
 			v10log(LOGNORMAL,"Red de Escaner %ld. Abierta conexión con el servidor %s:%s\n",sidinfolectura,ilt.dirip,ilt.puertotcp);
			return(0);
		} else return -1;		
	}
	return(-1);
}


VDEXPORT int vdinithardlectura(int idinfolectura)
{
	sidinfolectura=idinfolectura;
	atexit(cierraconex);
	ILTselvdinfolecturas(idinfolectura,&ilt);
	return (tickhard());
}


VDEXPORT int vddamecaracter(void) 
{
	if (tickhard()==0) {
        if (v10sockhaycar(sck)) {
            ultlectura=damecent();
            return v10socksigcar(sck);		
        }
        if (sck && sck->status==STSOCKREADY && (damecent()-ultlectura>TIMEOUTLECT)) {
            v10sockencola(sck,'\n');
            ultlectura=damecent();
        }
	}
	return (0);
}
