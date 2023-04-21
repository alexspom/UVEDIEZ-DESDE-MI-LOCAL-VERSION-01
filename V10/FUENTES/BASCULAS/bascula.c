#include  "vd.h"
#include "execproc/vdexec.h"
#include "vdbasculas.h"

#define MAXBASCULAS 50
#define MAXCARBASC  50


int TIMEOUTBASC=100;
int REINTBASC=3;

typedef struct {
            vdbasculass basc;
            v10socks *sock;
            v10horas ultcomm;
			int reint;
            char buffer[MAXCARBASC];
            char *ptr;
} basculas;

static basculas basc[MAXBASCULAS];
static int numbasc;
static int inicializado;

static void logbascula(v10socks *soc,int op,int bytes,char *buffer)
{
   // v10sockprintf(soc,"%s\n","user anonymous");
}

static void initunabasc(int nb)
{
    basculas *b=basc+nb;
    b->sock=v10socknuevocliente(b->basc.dirip,b->basc.puertotcp,1,4096,NULL,logbascula,NULL,NULL,NULL);
    b->ptr=b->buffer;
	b->reint = 0;
}

static void initbascula(void)
{
    vdbasculass b;
    int ret;
	TIMEOUTBASC=damepropentero("TIMEOUTBASC");
	REINTBASC=damepropentero("REINTBASC");
    ret=BASbuscatodo(&b);
    while (ret==0) {
        basc[numbasc].basc=b;
        v10log(LOGNORMAL,"Cargando bascula %d direccion ip %s puerto %s\n",b.numbasc,b.dirip,b.puertotcp);
//        if (*b.activa=='S') initunabasc(numbasc);
        ret=BASnexttodo(&b);
        numbasc++;
    }
    inicializado=1;
}

static void pidepesobasc(int nb)
{
    basculas *b=basc+nb;
    if (b->sock == NULL) return;
    if (*b->basc.activa=='N' || b->reint>=REINTBASC) {
		b->reint=0;
        if (b->sock) {
            v10log(LOGNORMAL,"Desconectando bascula %d por estar inactiva\n",b->basc.numbasc);
            v10socklibera(b->sock);
            b->sock=NULL;
        }
        b->basc.status=STBASLEIDO;
		*b->basc.datos=0;
        BASactualizastatusypeso(&b->basc,0);
        commit();
        return;
    }
    b->basc.status=STBASSOLICITADO;
    b->ptr=b->buffer;
    BASactualizastatusypeso(&b->basc,0);
    commit();
    b->reint++;
    while (v10socksigcar(b->sock)!=-1);
    if (b->sock && b->sock->status==STSOCKREADY) {
        v10log(LOGNORMAL,"Solicitado peso a bascula %d\n",b->basc.numbasc);
        v10sockprintf(b->sock, "%s", "S\n");
    }
    b->ultcomm=damecent();
}

static int damenumbasc(int bas)
{
    int nb;
    for (nb=0;nb<numbasc;nb++) {
        if (basc[nb].basc.numbasc==bas) return(nb);
    }
    return(-1);
}

static void analizapesobasc(basculas *b)
{
    double peso;
	b->reint = 0;
	b->ptr = b->buffer;
	if (strstr(b->buffer, "S"))
		peso = atof(b->buffer + 7);
	else
		peso = 0;
	if (strstr(b->buffer,"kg")) peso*=1000;
    v10log(LOGNORMAL,"Recibido peso %lf de bascula %d buffer %s\n",peso,b->basc.numbasc,b->buffer);
    sprintf(b->basc.datos,"%06.0lf",peso);
    b->basc.status=STBASLEIDO;
    BASactualizastatusypeso(&b->basc,0);
    commit();
}


static void tratabasculas(void)
{
    int nb,ret;
    vdbasculass bas;
    for (nb=0;nb<numbasc;nb++) {
        basculas *b=basc+nb;
        int ch;
        if (b->basc.status==STBASSOLICITADO && damecent()-b->ultcomm>TIMEOUTBASC) {
            v10log(LOGNORMAL,"Timeout en bascula %d resolicitando peso\n",b->basc.numbasc);
            pidepesobasc(nb);
        }
		if (b->basc.status == STBASSOLICITADO) {
			if (!strcmp(b->basc.activa, "S") && b->sock==NULL)
                initunabasc(damenumbasc(b->basc.numbasc));
			if (b->sock != NULL) {
				while ((ch = v10socksigcar(b->sock)) != -1) {
					if (ch == '\n') {
						b->ptr = 0;
						analizapesobasc(b);
						if (b->sock) {
							v10log(LOGNORMAL, "Desconectando bascula %d\n", b->basc.numbasc);
							v10socklibera(b->sock);
							b->sock = NULL;
							break;
						}
					}
					*b->ptr++ = ch;
					if (b->ptr - b->buffer >= MAXCARBASC) b->ptr = b->buffer;
				}
			}
		}
    }
    ret=BASbuscastatus(STBASREQUERIDO,&bas);
    while (ret==0) {
        if (*bas.activa == 'A') {
            bas.status = STBASLEIDO;
            BASactualizastatusypeso(&bas, 0);
            commit();
        } else {
            nb = damenumbasc(bas.numbasc);
            if (nb >= 0) {
                basc[nb].basc = bas;
                if (basc[nb].sock == NULL && *basc[nb].basc.activa == 'S') initunabasc(nb);
                pidepesobasc(nb);
            }
        }
        ret=BASnextstatus(&bas);
    }

}


VDEXPORT int procesobasc(procesos *proceso)
{
    if (inicializado==0) initbascula();
    tratabasculas();
    return(0);
}