#include "../execproc/vdexec.h"

#define MAXCURSORESPER 200

typedef struct PERCURSORES {
              procesos   *proc;
              v10cursors *cur;
              v10horas   intervalo;
              v10horas   hulteje;
              v10dates   fulteje;
              v10horas   hproxeje;
              v10horas   fproxeje;
              int        numeje;
              int        filas;
              int        errores;
              v10horas   tiempoeje;
} vdpercursores;

static vdpercursores per[MAXCURSORESPER];
static int numcursores;

static void initperiodico(char *param,procesos *proc)
{
    char fichero[MAXPATH],*aux;
    int i,j;
    char propiedad[LPROPIEDAD];
    v10horas intervalo;
    for (i=0;i<numpieces(param,"#");i++) {
        piece(param,fichero,"#",i+1);
        if ((aux=strchr(fichero,'$'))!=NULL) {
            *aux=0;
            intervalo=atof(aux+1);
            if (intervalo<proc->proc.periodo && intervalo>0) proc->proc.periodo=(long)intervalo;
        } else intervalo=0;
        leevsq(fichero);
        for (j=numcursores;;j++) {
            v10cursors *cur;
            cur=damevsqnum(j);
            if (cur==NULL) break;
            per[j].proc=proc;
            per[j].cur=cur;
            per[j].intervalo=intervalo;
            sprintf(propiedad,"TSQL%s",cur->nombre);
            intervalo=damepropdoble(propiedad);
            if (intervalo>0) per[j].intervalo=intervalo;
            numcursores++;
        }
    }
}

#define TDIA (100*60*60*24)
void recalculatiempo(vdpercursores *lp)
{
    lp->hproxeje=gettime()+lp->intervalo;
    lp->fproxeje=damedate();
    if (lp->hproxeje>TDIA) {
        lp->fproxeje++;
        lp->hproxeje-=TDIA;
    }
}

static void ejecutaperiodico(procesos *proc)
{
	int i,ret;
	v10dates fecact=damedate();
	v10horas  hact=gettime();
	for (i=0;i<numcursores;i++) {
		vdpercursores *lp=per+i;
		v10horas hinicio;
        if (lp->proc!=proc) continue;
		if (lp->fproxeje<fecact || (lp->fproxeje==fecact && lp->hproxeje<=hact)) {
			v10log(LOGDEBUG,"Ejecutando cursor %s\n",lp->cur->nombre);
			hinicio=damecent();
            lp->hulteje=hact;
            lp->fulteje=fecact;
			ret=ejecutacursor(lp->cur);
			if (ret) {
				lp->errores++;
				rollback();
			} else commit();
			lp->tiempoeje+=damecent()-hinicio;
			lp->numeje++;
			lp->filas+=procesadascursor(lp->cur);
			v10log(LOGDEBUG,"  Error %ld Tratadas %ld filas tiempo %lf cs.\n",ret,procesadascursor(lp->cur),damecent()-hinicio);
			recalculatiempo(lp);
		}
	}
}

VDEXPORT void procesoperiodico(procesos *proc) 
{
    if (proc->ejecuciones==1) initperiodico(proc->proc.param,proc);
    ejecutaperiodico(proc);
}