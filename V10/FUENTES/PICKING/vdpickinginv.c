/****
* vdpicking - Fichero donde estan implementadas las funciones de control general del picking inverso
*
* Propósito: Controlar las pulsaciones de teclas y ticks de los displays
*
****/

#include "vdinfopicking.h"

int idinfogest=-1;

// FUNCION: dimetecla    
// AUTOR: 
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
// AUTOR: 
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


#define CSELDISC "SELECT VDECOINV.DISCRIMINANTE(:IDINFOPICK,:MIDISP,:MITECLA) FROM DUAL"
static v10cursors *v10seldisc;
#define CSELSCAN "BEGIN VDECOINV.TRATASCANINFO(:IDINFOGEST);COMMIT;END;"
static v10cursors *v10selscan;
#define CSELTICK "BEGIN VDECOINV.TRATATICK(:IDINFOGEST);COMMIT;END;"
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
    v10seldisc=abrecursor(CSELDISC);
    definetodo(v10seldisc,disp.discriminante,sizeof(disp.discriminante),V10CADENA,NULL);
    bindtodo(v10seldisc,"IDINFOPICK",&disp.idinfopick,sizeof(disp.idinfopick),V10LONG,
                        "MIDISP",&disp.numdisp,sizeof(disp.numdisp),V10LONG,
                        "MITECLA",&disp.tecla,sizeof(disp.tecla),V10LONG,
                        NULL);
    v10selscan=abrecursor(CSELSCAN);
	bindtodo(v10selscan,"IDINFOGEST",&idinfogest,sizeof(idinfogest),V10INT,NULL);
	v10seltick=abrecursor(CSELTICK);
	bindtodo(v10seltick,"IDINFOGEST",&idinfogest,sizeof(idinfogest),V10INT,NULL);
}
// FUNCION: tratainfotecla    
// AUTOR: 
// PARAMETROS : 
//      proceso:   Registro de la estructura PTRPROCESOS
//      tec:       Registro de la estructura vdinfomensajes con la tecla pulsada
// DESCRIPCION: Función que trata la pulsación de una tecla tanto en los controladores de zona 
//              como en los displays de picking y realiza la llamada al proceso correspondiente
static int tratainfotecla(procesos *proceso, vdinfomensajes *tec)
{
    disp.idinfopick=tec->idinfopick;
    disp.numdisp=tec->numdisp;
    disp.tecla=tec->nmensaje;
    if (v10seldisc==NULL) initvdpicking();
    ejefetchcursor(v10seldisc);
    v10log(LOGNORMAL,"Detectada tecla %d en display %d discriminante %s\n",tec->nmensaje,tec->numdisp,disp.discriminante);
    VDEXECejecuta(proceso,tec,"#","%s",disp.discriminante);
    return(0);
}

VDEXPORT procesatecladisp(vdinfomensajes *tec,char *param)
{
    v10cursors *v10dinamico;
    char sql[LDISCRIMINANTE];
    disp.idinfopick=tec->idinfopick;
    disp.numdisp=tec->numdisp;
    disp.tecla=tec->nmensaje;
    v10log(LOGNORMAL,"Procesando tecla %d de display %d parametro %s\n",tec->nmensaje,tec->numdisp,param);
    sprintf(sql,"BEGIN EXECUTE IMMEDIATE 'BEGIN %s; END;' USING OUT :RET,:IDINFOPICK,:NUMDISP,:NUMTEC; END;",param);
    v10dinamico=abrecursornombre("procesatecladisp",sql);
    bindtodo(v10dinamico,"IDINFOPICK",&disp.idinfopick,sizeof(disp.idinfopick),V10LONG,
                         "NUMDISP",&disp.numdisp,sizeof(disp.numdisp),V10LONG,
                         "NUMTEC",&disp.tecla,sizeof(disp.tecla),V10LONG,
                         "RET",&disp.ret,sizeof(disp.ret),V10LONG,
                         NULL);
    ejecutacursor(v10dinamico);
    liberacursor(v10dinamico);
    return(0);
}

// FUNCION: procesatecla    
// AUTOR: 
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


// FUNCION: procesoinfo4    
// AUTOR: 
// PARAMETROS : 
//      proceso:   Registro de la estructura PTRPROCESOS
// DESCRIPCION: Proceso principal del picking.
//              Gestiona los ticks de los controladores de zona y de los displays de picking
//              Gestiona las querys del fichero de configuración sql 
//              Realiza la llamada a los procesos que controlan los displays de zona y de picking
VDEXPORT int vdpickinv(procesos *proceso)
{
    int ret=0;
	static int bucles;

    vdzonass ifzotick;
    vdinfodisps ifditick;
    vdinfomensajes tec;

    if (idinfogest==-1) {
        char mitick[LPARAM];
        leedefines("vdst.h");
        idinfogest=atoi(proceso->proc.param);
		initvdpicking();
    }
    // Trata las teclas pulsadas
    ret=procesatecla(proceso);
    if (ret==0) commit();
    else rollback();
	if (bucles % 2) ejecutacursor(v10selscan);
	else         ejecutacursor(v10seltick);
	bucles++;
	return(0);
}

// FUNCION: vacio    
// AUTOR: 
// PARAMETROS : 
//      proceso:   Registro de la estructura PTRPROCESOS
// DESCRIPCION: Proceso por defecto para cuando se pulsa una tecla y no se quiere realizar ninguna acción.
VDEXPORT int vacio(void)
{
    return(0);
}

