#include "vd.h"
#include "execproc/vdexec.h"
#include "vdbasculas.h"

#define MAXBASCULAS 50
#define MAXCARBASC  50


extern int TIMEOUTBASC;
extern int REINTBASC;

typedef struct {
            vdbasculass basc;
            int port;
            v10horas ultcomm;
			int init;
			int reint;
            char buffer[MAXCARBASC];
            char *ptr;
} basculas;

static basculas basc[MAXBASCULAS];
static int numbasc;
static int inicializado;

static void logbascula(v10socks *soc,int op,int bytes,char *buffer)
{
    v10sockprintf(soc,"%s\n","user anonymous");
}

static void initunabasc(int nb)
{
    basculas *b=basc+nb;
	if (b->init) return;
	b->init=1;
	initpuerto232(b->basc.puerto232,b->basc.velocidad,2,7,0);
    b->ptr=b->buffer;
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
		if (b.puerto232>=0) {
			v10log(LOGNORMAL,"Cargando bascula %d direccion ip %s puerto %s\n",b.numbasc,b.dirip,b.puertotcp);
			if (*b.activa=='S') initunabasc(numbasc);
		}
        ret=BASnexttodo(&b);
        numbasc++;
    }
    inicializado=1;
}

static void pidepesobasc(int nb)
{
    basculas *b=basc+nb;
    if (*b->basc.activa=='N' || b->reint>=REINTBASC) {
		b->reint=0;
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
    while (damecar232(b->basc.puerto232)>0);
    printf232(b->basc.puerto232,"%s","S\r\n");
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
    char *inipeso,*fin;
    double peso;
	if (es_blanco(b->buffer)) return;
	b->reint=0;
    b->ptr=b->buffer+1;
	while (*b->ptr==' ') b->ptr++;
	inipeso=b->ptr;
	fin=strchr(b->ptr,' ');
	if (fin==0) return;
	*fin=0;
	peso=atof(inipeso)*1000;
    v10log(LOGNORMAL,"Recibido peso %lf de bascula %d\n",peso,b->basc.numbasc);
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
		if (b->basc.puerto232<0) continue;
        if (b->basc.status==STBASSOLICITADO && damecent()-b->ultcomm>TIMEOUTBASC) {
            v10log(LOGNORMAL,"Timeout en bascula %d resolicitando peso\n",b->basc.numbasc);
            pidepesobasc(nb);
        }
        while ((ch=damecar232(b->basc.puerto232))!=-1) {
                if (ch=='\n') {
                    *b->ptr=0;
					v10log(LOGNORMAL,"Recibido de la bascula %s\n",b->buffer);
                    analizapesobasc(b);
					b->ptr=b->buffer;
                }
                *b->ptr++=ch;
                if (b->ptr-b->buffer>=MAXCARBASC) b->ptr=b->buffer;
        }
    }
    ret=BASbuscastatus(STBASREQUERIDO,&bas);
    while (ret==0) {
        nb=damenumbasc(bas.numbasc);
        if (nb>=0) {
            basc[nb].basc=bas;
            if (*basc[nb].basc.activa=='S') initunabasc(nb);
            pidepesobasc(nb);
        }
        ret=BASnextstatus(&bas);
    }

}


VDEXPORT int procesobasc232(procesos *proceso)
{
    if (inicializado==0) initbascula();
    tratabasculas();
    return(0);
}