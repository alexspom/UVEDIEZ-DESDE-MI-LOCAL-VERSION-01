#include "vdinfopicking.h"
#include "info4\infopc.h"

static int sidinfopick;

VDEXPORT void vdinfoinit(int idinfopick)
{
    int ret;
    vdinfohards iha;
    sidinfopick=idinfopick;
    ret=IHAselvdinfohard(idinfopick,&iha);
    initinfopick(iha.tciclo, iha.tenvtrama, iha.timeouttrama, iha.timeoutwho, iha.limitelinea, iha.rangolineas, iha.dirip1, iha.dirip2, iha.dirip3, iha.dirip4, iha.dirip5, NULL);
}

VDEXPORT int vdinfoprint(int iddisplay,char *cadena,char *luces)
{
    char numluz[20];
    int i=1,ret;
    ret=displayprintf(iddisplay,cadena);
	if (!es_blanco(luces)) {
       while (piece(luces,numluz,",",i)!=-1) {
           if (!es_blanco(numluz)) lucesdisplay(iddisplay,i-1,atoi(numluz));
		   i++;
	   }
	}
	for (;i<MAXLUCESDISPLAY;i++) lucesdisplay(iddisplay,i-1,0);
    return(ret);
}


VDEXPORT int vddametecla(vdinfomensajes *men)
{
    tecladisps mitec;
    if (haytecladisp()) {
        tecladisp(&mitec);
		memset(men,0,sizeof(*men));
		men->tipomensaje=INFOMENTECLA;
        men->numdisp=mitec.numdisp;
        men->nmensaje=mitec.boton;
        men->causa=mitec.causa;
		men->param=NULL;
		men->funlibera=NULL;
        return(1);
    }
    return(0);
}

VDEXPORT void vdtickinfo(void)
{
    tickhleth();
}
    
