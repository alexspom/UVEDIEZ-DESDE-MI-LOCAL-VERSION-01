/*******************************************************************************
* Funci�n Ejecutor de algoritmos est�ndar                                      *
* M�dulo  vdejecutaalgoritmos.c                                                *
*                                                                              *
* Autor  JCSR	                                                               *
* Revisado por:                                                                *
* Fecha 01-11-2007                                                             *
********************************************************************************

*******************************************************************************/
#include "vdexec.h"

#define DAMEPUNTUACION "SELECT VDPROC.PUNTUA(:CADENA, :PATRON, :SEP) PUNTOS FROM DUAL"
static v10cursors *vddamepuntuacion; 

#define CSELALG "SELECT VDPROC.DAMEMEJORALG(:PROCESO,:DISCRIMINANTE,:SEP) NOMBREALG FROM DUAL"
static v10cursors *vdselalg;

typedef struct {
    char proceso[LPROCESO];
    char nombrealg[LNOMBREALG];
	char cadena[LDISCRIMINANTE];
    char patron[LDISCRIMINANTE];
	char sep[2];
	double puntos;
} punts;

punts punt;

static void fin_cursores (void)
{
	liberacursor(vddamepuntuacion);
    liberacursor(vdselalg);
}

static void init_cursores (void)
{
    vddamepuntuacion=abrecursor(DAMEPUNTUACION);
    definetodo(vddamepuntuacion,&punt.puntos, sizeof(punt.puntos),V10DOUBLE,
                          NULL);
    bindtodo(vddamepuntuacion,"CADENA",punt.cadena,sizeof(punt.cadena),V10CADENA,
                          "PATRON",punt.patron,sizeof(punt.patron),V10CADENA,
                          "SEP",punt.sep,sizeof(punt.sep),V10CADENA,
						  NULL);
    vdselalg=abrecursor(CSELALG);
    definetodo(vdselalg,punt.nombrealg, sizeof(punt.nombrealg),V10CADENA,
                          NULL);
    bindtodo(vdselalg,"DISCRIMINANTE",punt.cadena,sizeof(punt.cadena),V10CADENA,
                      "PROCESO",punt.proceso,sizeof(punt.proceso),V10CADENA,
                      "SEP",punt.sep,sizeof(punt.sep),V10CADENA,
					  NULL);
	atexit(fin_cursores);
}

void audita(char* proceso, char* tipoculpable, char * culpable)
{
	char modulo[LCADENASMALL],accion[LCADENASMALL];
	sprintf(modulo,"PROCESO:%s",proceso);
	sprintf(accion,"%s: %s",tipoculpable, culpable);
	setmodule(modulo,accion);	

}

//Busca algoritmos que coincidan con el discriminante
static int vdbuscaalgoritmos(procesos *ptrproc,char *discriminante,char *sep, vdalgoritmoss *alg) 
{
	int ret;
	if (vdselalg==NULL) init_cursores ();
    strcpy(punt.proceso,ptrproc->proc.proceso);
    strcpy(punt.nombrealg,"");
    strcpy(punt.sep,sep);
    strcpy(punt.cadena,discriminante);
    ret=ejefetchcursor(vdselalg);
    if (ret || es_blanco(punt.nombrealg)) return(1);
    ret=ALGselalgproc(punt.proceso,punt.nombrealg,alg);
    return(ret);
}


static int ejecutaprepostalgoritmos (char* prepostcadena, vdalgoritmoss *alg,void *ptrparam, char *proceso)
{
	int ret=0;
    vdprepostalgoritmoss prepostal;
	int (*fnproceso)(void *,void *)=NULL;;

	if (PREPOSTbuscaalgoritmo(strcmp(prepostcadena,"pre")==0?"A":"D",alg->proceso,alg->nombrealg, &prepostal)==0){
		do{
			if (prepostal.libalgoritmo) fnproceso=damefundll(prepostal.libalgoritmo, prepostal.funcionalg);
			if (fnproceso) {
				audita(proceso, (strcmp(prepostcadena,"pre")==0?"PREALGORITMO":"POSTALGORITMO"),prepostal.funcionalg );
				ret=fnproceso(ptrparam,(void*) (prepostal.paramalg));
            } else {
                v10log(LOGERROR,"ejecutaprepostalgoritmos:Proceso %s, Algoritmo %s, su %salgoritmo %s no se puede cargar\n",
                     prepostal.proceso,prepostal.nombrealg,prepostcadena,prepostal.funcionalg);
                return(-1);
            }
            if (ret) {
               v10log(LOGERROR,"ejecutaprepostalgoritmos: Error ejecutando %salgoritmo %s con parametros %s\n",prepostcadena,prepostal.funcionalg,prepostal.paramalg);
               return(ret); 
            }
		}while ( !PREPOSTnextalgoritmo(&prepostal));
	}
    return(ret);
}

//Ejecuta los algoritmos cargados en ptralg
static int vdalgoritmos(procesos *proceso,vdalgoritmoss *alg,void *ptrparam)
{
	int ret=0;
	int (*fnproceso)(void *,void *,procesos *proceso,vdalgoritmoss *alg)=NULL;
	if (*alg->nombrealg==0){
		v10log(LOGERROR,"No existen algoritmos para ejecutar en el proceso %s\n",
							 proceso->proc.proceso);
		return(VD_ESINALG);
	}
//�Ejecuci�n de prealgoritmos si los hay. 
	ret=ejecutaprepostalgoritmos("pre", alg, ptrparam, proceso->proc.proceso);
    if (ret) return(ret);
//Ejecuci�n de algoritmo.
	v10log(LOGDEBUG,"Ejecutando algoritmo %s, funcion %s, parametros %s en el proceso %s\n",alg->nombrealg,alg->funcionalg,alg->paramalg,proceso->proc.proceso);
	fnproceso=damefundll(alg->libalgoritmo, alg->funcionalg); 
	if (fnproceso) {
		audita(proceso->proc.proceso, "ALGORITMO:", alg->funcionalg);
		ret=fnproceso(ptrparam,(void*) (alg->paramalg),proceso,alg);
    } else {
		v10log(LOGERROR,"Error ejecutando el algoritmo %s, funcion %s, parametros %s en el proceso %s\n",alg->nombrealg,alg->funcionalg,alg->paramalg,proceso->proc.proceso);
		return (-1);
	}    
    if (ret) {
     v10log(LOGERROR,"EXECalgoritmos: Error ejecutando algoritmo %s con funcion %s y parametros %s\n",alg->nombrealg,alg->funcionalg,alg->paramalg);
     return(ret);
    }
// Ejecuci�n de postalgoritmos si los hubiera o hubiese
	ret=ejecutaprepostalgoritmos("post", alg, ptrparam,  proceso->proc.proceso);		
	return(ret);
}


static int vejecuta(procesos *proceso,void *ptrparam,char *sep,char *format,va_list arg)
{
	int ret;
    char discriminante[LDISCRIMINANTE];
    vdalgoritmoss alg;
    memset(&alg,0,sizeof(alg));
    vsprintf(discriminante,format,arg);
    vdbuscaalgoritmos(proceso,discriminante,sep, &alg);
    ret=vdalgoritmos(proceso,&alg,ptrparam);
    return(ret);
}


VDEXPORT int VDEXECejecuta(procesos *proceso,void *ptrparam,char *sep,char *format,...)
{
    va_list arg;
    int ret;    
    va_start(arg,format);
    ret=vejecuta(proceso,ptrparam,sep,format,arg);
    va_end(arg);
    return(ret);
}

VDEXPORT void VDEXECejecutaproceso(char *proceso)
{
  procesos *proc;
  if ((proc=buscaproceso(proceso))){
    v10log(LOGDEBUG,"Ejecucion %ld del cargador %s\n",++(proc->ejecuciones),proc->proc.proceso);
		(*proc->fnproceso)(proc);
  }
}

VDEXPORT void dameparamproc(procesos *proceso, char *donde, int numparam)
{
    piece(proceso->proc.param, donde, "#", numparam);
}

VDEXPORT long dameparamproclong(procesos *proceso, int numparam)
{
    char donde[LPARAMALG];
    dameparamproc(proceso, donde, numparam);
    return(atol(donde));
}

VDEXPORT double dameparamprocdouble(procesos *proceso, int numparam)
{
    char donde[LPARAMALG];
    dameparamproc(proceso, donde, numparam);
    return(atof(donde));
}

