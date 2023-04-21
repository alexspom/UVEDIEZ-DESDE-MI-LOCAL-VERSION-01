/****
* vdpicking - Fichero donde estan implementadas las funciones de control general del picking
* 
* Propósito: Controlar las pulsaciones de teclas y ticks de los displays
*                                            
****/

#include "vdinfopicking.h"

int idinfogest=-1;

// FUNCION: dimetecla    
// PARAMETROS : 
//      ptr:   Puntero a un registro de la estructura vdinfomensajes.
//      param: Parámetros del proceso.
// DESCRIPCION: Muestra la tecla pulsada en un display
VDEXPORT int dimetecla(void *ptr,char *param)
{
	vdinfomensajes *tec=ptr;
	if (tec->nmensaje==TTICK) return(0);
	v10log(LOGNORMAL,"Pulsada tecla %d de display %d %d\n",tec->nmensaje,tec->idinfopick,tec->numdisp);
	if (tec->nmensaje==3) vdinfoprintf(tec->idinfopick,tec->numdisp,"");
    else vdinfoprintf(tec->idinfopick,tec->numdisp,"T %d$2",tec->nmensaje);
	return(0);
}


// FUNCION: tratadisplay    
// PARAMETROS : 
//      proceso:   Registro de la estructura PTRPROCESOS
// DESCRIPCION: Proceso principal de los displays de picking
//              Es llamado desde el proceso vdinfo4 cada vez que se pulsa una tecla o se realiza un tick 
//              en alguno de los displays de picking 
VDEXPORT void tratadisplay(procesos *proceso)
{
    vdinfodisps    ipd;
    vdzonass    ipz;
    char param[MAXCADENA];
    vdinfomensajes tec;
    char idinfopick[4], numdisp[8], nmensaje[6];
    vdstatuss sta,staz;
    int ret;

    // Recogemos los parametros del proceso
    if ((void *)proceso->proc.param==NULL) return;
    piece(proceso->proc.param,idinfopick,"#",1);
    piece(proceso->proc.param,numdisp,"#",2);
    piece(proceso->proc.param,nmensaje,"#",3);
    memset(&tec,0,sizeof(tec));
    tec.idinfopick = atoi(idinfopick);
    tec.numdisp = atoi(numdisp);
    tec.nmensaje = atoi(nmensaje);

    ret=IDIselvdinfodisp(tec.idinfopick,tec.numdisp,&ipd);
    if (ret) return;
    STAselvdstatus("IDI",ipd.status,&sta);
    ret=ZONselvdzonas(ipd.codzona,&ipz);
    memset(&staz,0,sizeof(staz));
    STAselvdstatus("ZON",ipz.status,&staz);

    sprintf(param,"%ld#%ld#%ld#%s#%s#%s",ipd.idinfopick,ipd.numdisp,ipd.codzona,sta.dabstatus,staz.dabstatus,damenombretecla(tec.nmensaje));
    v10log(LOGNORMAL,"\nEn tratadisplay %s\n",param);
    if (VDEXECejecuta(proceso,&tec,"#", "%ld#%ld#%ld#%s#%s#%s", ipd.idinfopick,ipd.numdisp,ipd.codzona,sta.dabstatus,staz.dabstatus,damenombretecla(tec.nmensaje))!=0) rollback();
    else commit();
}


char cseldisc[LPARAM];
static v10cursors *v10seldisc;

char cseldisc[LPARAM];
static v10cursors *v10seldisc;

char cselscan[LPARAM];
static v10cursors *v10selscan;
char cseltick[LPARAM];
static v10cursors *v10seltick;
typedef struct {
            long      idinfopick;
            long      numdisp;
            long      tecla;
            char      discriminante[LDISCRIMINANTE];
            long      ret;
} displays;
static displays disp;
static void initvdpicking(void)
{
    v10seldisc = abrecursornombre("CSELDISC", cseldisc);
    bindtodo(v10seldisc, "IDINFOPICK", &disp.idinfopick, sizeof(disp.idinfopick), V10LONG,
             "NUMDISP", &disp.numdisp, sizeof(disp.numdisp), V10LONG,
             "TECLA", &disp.tecla, sizeof(disp.tecla), V10LONG,
             "RET", disp.discriminante, sizeof(disp.discriminante), V10CADENA,
             NULL);
    v10selscan = abrecursornombre("CSELSCAN", cselscan);
    bindtodo(v10selscan, "IDINFOGEST", &idinfogest, sizeof(idinfogest), V10INT, NULL);
    v10seltick = abrecursornombre("CSELTICK", cseltick);
    bindtodo(v10seltick, "IDINFOGEST", &idinfogest, sizeof(idinfogest), V10INT, NULL);
}

static int tratainfotecla(procesos *proceso, vdinfomensajes *tec)
{
    int ret = 0;
    disp.idinfopick=tec->idinfopick;
    disp.numdisp=tec->numdisp;
    disp.tecla=tec->nmensaje;
    if (v10seldisc==NULL) initvdpicking();
    ejefetchcursor(v10seldisc);
    v10log(LOGNORMAL,"Detectada tecla %d en display %d discriminante %s\n",tec->nmensaje,tec->numdisp,disp.discriminante);
    if (!es_blanco(disp.discriminante)) {
        ret=VDEXECejecuta(proceso, tec, "#", "%s", disp.discriminante);
    }
    return(ret);
}

#define CPROCESA "BEGIN :RET:=VDECOUNI.PROCESATECLA(:IDINFOPICK,:NUMDISP,:TECLA,:SENTENCIA); END;"
static v10cursors *v10procesa;

VDEXPORT procesatecladisp(vdinfomensajes *tec, char *param)
{
	disp.idinfopick = tec->idinfopick;
	disp.numdisp = tec->numdisp;
	disp.tecla = tec->nmensaje;
	strcpy(disp.discriminante, param);
	v10log(LOGNORMAL, "Procesando tecla %d de display %d parametro %s\n", tec->nmensaje, tec->numdisp, param);
	if (v10procesa == NULL) {
		v10procesa = abrecursor(CPROCESA);
		bindtodo(v10procesa, "IDINFOPICK", &disp.idinfopick, sizeof(disp.idinfopick), V10LONG,
			"NUMDISP", &disp.numdisp, sizeof(disp.numdisp), V10LONG,
			"TECLA", &disp.tecla, sizeof(disp.tecla), V10LONG,
			"SENTENCIA", disp.discriminante, sizeof(disp.discriminante), V10CADENA,
			"RET", &disp.ret, sizeof(disp.ret), V10LONG,
			NULL);
	}
	ejecutacursor(v10procesa);
	return(disp.ret);
}

// FUNCION: procesatecla    
// PARAMETROS : 
//      proceso:   Registro de la estructura PTRPROCESOS
// DESCRIPCION: Recoge la tecla que se ha pulsado en un display de zona o de picking
VDEXPORT int procesatecla(procesos *proceso)
{
    int            ret;
    vdinfomensajes tec;
    
    while ((ret=vdinfodametecla(idinfogest,&tec))==0) {
        commit();
        ret=tratainfotecla(proceso,&tec);
        if (ret==0) commit();
        else     rollback();
    }
    return(0);
}

v10horas ttick;


// FUNCION: vdpick    
// PARAMETROS : 
//      proceso:   Registro de la estructura PTRPROCESOS
// DESCRIPCION: Proceso principal del picking.
//              Gestiona los ticks de los controladores de zona y de los displays de picking
//              Gestiona las querys del fichero de configuración sql 
//              Realiza la llamada a los procesos que controlan los displays de zona y de picking
VDEXPORT int vdpick(procesos *proceso)
{
    int ret=0;
	static int bucles;

    vdzonass ifzotick;
    vdinfodisps ifditick;
    vdinfomensajes tec;

    if (idinfogest == -1) {
        char mitick[LPARAM];
        //		logoracle=NULL;
        idinfogest = dameparamproclong(proceso, 1);
        dameparamproc(proceso, cseldisc, 4);
        dameparamproc(proceso, cselscan, 5);
        dameparamproc(proceso, cseltick, 6);
        initvdpicking();
        v10log(LOGNORMAL, "IDINFOGEST: %d\n", idinfogest);
    }
    // Trata las teclas pulsadas
    ret=procesatecla(proceso);
    if (ret==0) commit();
    else rollback();
    // Trata las lecturas de scanner
    if (bucles % 2) {
        ret=ejecutacursor(v10selscan);
    }  else  {
        ret=ejecutacursor(v10seltick);
    }
    if (ret == 0) commit();
    else rollback();
	bucles++;
    return(0);
}

// FUNCION: vacio    
// PARAMETROS : 
//      proceso:   Registro de la estructura PTRPROCESOS
// DESCRIPCION: Proceso por defecto para cuando se pulsa una tecla y no se quiere realizar ninguna acción.
VDEXPORT int vacio(void)
{
    return(0);
}

