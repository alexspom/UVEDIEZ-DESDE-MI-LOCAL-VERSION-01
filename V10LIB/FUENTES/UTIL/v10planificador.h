/****
* PLANIFICADOR.H - 
* 
* Propósito: Fichero cabecera para el planificador
*           
* Autor	   : MGM
* Fecha    : 19-11-2007
****
* Modificaciones:
***/




#ifndef __PLANIFICADOR__H__
#define __PLANIFICADOR__H__

#include <time.h>
#include "v10.h"

#define FILE_PROC	            "PROCESOS.DAT"
#define MAXPLANIF	            100
#define MAX_TIMEOUT				    5
#define LEN_PAN					      100
#define INTERVALO_DELAY			  10 

#define MINUTO				        60
#define MAX_ITEMS			        7

#define DEFAULT_INTERVAL_READ	15
#define STRING_PAR				    512

typedef struct tagProcPlanif {
	char     szPrograma[MAXPATH];
	char     szDiasEjecucion[8];
	char     szHoraInicio[9];
	char     szHoraLimite[9];
	char     szHoraProxEjec[9];
	char     szHoraUltEjec[9];
	v10horas lIntervaloEjecucion;
	v10horas lUltimaEjecucion;
	v10horas lEjecutado;
	int      lCad;
	int      activa;
	char     descripcion[MAXPATH];
} PLANIF,*LPPLANIF;

typedef struct Parametros {
   int       logContinuo;
   int       minutosRelectura;
   char      confArranque[2];
   char      confParo[2];
   v10horas  timeout;
   char      unimedIntervalo[2];
} PARAM,*LPPPARAM;


#endif