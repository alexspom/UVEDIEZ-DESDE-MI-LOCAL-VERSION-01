/*****************************************************************
*																 *
* Módulo:  Infoconf.c											 *
* Función: Configuración en info3; lectura de los parámetros	 *
*		   de configuración										 *
*																 *	
*																 *
* Autor: Francisco J. Guerrero									 *
* Fecha: 29-1-2010												 *
*																 *		
******************************************************************/

#include "info3.h"

typedef struct {
           char *nombre;
           void *ptr;
           int tipo;
        } defvars;

#define TYPE_INT	0 // tipo de datos de los parametros de configuración 
#define TYPE_LONG	1
#define TYPE_CHAR	2
#define TYPE_SCHAR	3
#define TYPE_VCONF	4

extern char send_conf;

static defvars dvar[]={{"MAXERROR",&infotconfig.maxerror,TYPE_INT},
				{"DELAYCAB"	,&infotconfig.delaycab	,TYPE_VCONF},
				{"DELAYCAR"	,&infotconfig.delaycar	,TYPE_VCONF},
				{"HARDCHECK",&infotconfig.hardcheck	,TYPE_INT},
				{"TPULSA"	,&infotconfig.tpulsa	,TYPE_LONG},
				{"TSUELTA"	,&infotconfig.tsuelta	,TYPE_LONG},
				{"PREPEAT"	,&infotconfig.prepeat	,TYPE_LONG},
				{"SREPEAT"	,&infotconfig.srepeat	,TYPE_LONG},
				{"TPARPADE"	,&infotconfig.tparpade	,TYPE_LONG},
				{"TPARPADA"	,&infotconfig.tparpada	,TYPE_LONG},
				{"ESPWHO"	,&infotconfig.espwho	,TYPE_INT},
				{"ESPERA"	,&infotconfig.espera	,TYPE_INT},
				{"ESPRESET"	,&infotconfig.espreset	,TYPE_INT},
				{"ESPRESET1",&infotconfig.espreset1	,TYPE_VCONF},
				{"ESPRESET2",&infotconfig.espreset2	,TYPE_VCONF},
				{"FICHWHO"	,&infotconfig.fichwho	,TYPE_INT},
                {"RELEECONF",&infotconfig.releeconf	,TYPE_INT},			
				{"RATIOERR"	,&infotconfig.ratioerr	,TYPE_INT},
				{"STATSGAP"	,&infotconfig.statsgap	,TYPE_INT},
				{"QUEUE"	,&infotconfig.queue		,TYPE_INT},
				{"SHOWSTATS",&infotconfig.showstats	,TYPE_INT},
				{"QUANTUM",  &infotconfig.quantum	,TYPE_LONG},
				{"QUEUE_TIMEOUT",  &infotconfig.queue_timeout,TYPE_INT},
				{"WATCHDOG",  &infotconfig.watchdog	,TYPE_LONG},
				{"TARJ-1"	,infotconfig.tarj		,TYPE_CHAR},
                {"TARJ-2"	,infotconfig.tarj+1		,TYPE_CHAR},
				{"TARJ-3"	,infotconfig.tarj+2		,TYPE_CHAR},
				{"TARJ-4"	,infotconfig.tarj+3		,TYPE_CHAR},
				{"TARJ-5"	,infotconfig.tarj+4		,TYPE_CHAR},
				{"TARJ-6"	,infotconfig.tarj+5		,TYPE_CHAR},
				{"TARJ-7"	,infotconfig.tarj+6		,TYPE_CHAR},
				{"TARJ-8"	,infotconfig.tarj+7		,TYPE_CHAR},
				{"TARJ-9"	,infotconfig.tarj+8		,TYPE_CHAR},
				{"TARJ-10"	,infotconfig.tarj+9		,TYPE_CHAR},
				{"TARJ-11"	,infotconfig.tarj+10	,TYPE_CHAR},
				{"TARJ-12"	,infotconfig.tarj+11	,TYPE_CHAR},
				{"TARJ-13"	,infotconfig.tarj+12	,TYPE_CHAR},
				{"TARJ-14"	,infotconfig.tarj+13	,TYPE_CHAR},
				{"TARJ-15"	,infotconfig.tarj+14	,TYPE_CHAR},
				{"SERV-1"	,infotconfig.services		,TYPE_CHAR},
                {"SERV-2"	,infotconfig.services+1		,TYPE_CHAR},
				{"SERV-3"	,infotconfig.services+2		,TYPE_CHAR},
				{"SERV-4"	,infotconfig.services+3		,TYPE_CHAR},
				{"SERV-5"	,infotconfig.services+4		,TYPE_CHAR},
				{"SERV-6"	,infotconfig.services+5		,TYPE_CHAR},
				{"SERV-7"	,infotconfig.services+6		,TYPE_CHAR},
				{"SERV-8"	,infotconfig.services+7		,TYPE_CHAR},
				{"SERV-9"	,infotconfig.services+8		,TYPE_CHAR},
				{"SERV-10"	,infotconfig.services+9		,TYPE_CHAR},
				{"SERV-11"	,infotconfig.services+10	,TYPE_CHAR},
				{"SERV-12"	,infotconfig.services+11	,TYPE_CHAR},
				{"SERV-13"	,infotconfig.services+12	,TYPE_CHAR},
				{"SERV-14"	,infotconfig.services+13	,TYPE_CHAR},
				{"SERV-15"	,infotconfig.services+14	,TYPE_CHAR},
				{"NPORT-1"	,infotconfig.puertos		,TYPE_INT},
                {"NPORT-2"	,infotconfig.puertos+1		,TYPE_INT},
				{"NPORT-3"	,infotconfig.puertos+2		,TYPE_INT},
				{"NPORT-4"	,infotconfig.puertos+3		,TYPE_INT},
				{"NPORT-5"	,infotconfig.puertos+4		,TYPE_INT},
				{"NPORT-6"	,infotconfig.puertos+5		,TYPE_INT},
				{"NPORT-7"	,infotconfig.puertos+6		,TYPE_INT},
				{"NPORT-8"	,infotconfig.puertos+7		,TYPE_INT},
				{"NPORT-9"	,infotconfig.puertos+8		,TYPE_INT},
				{"NPORT-10"	,infotconfig.puertos+9		,TYPE_INT},
				{"NPORT-11"	,infotconfig.puertos+10	,TYPE_INT},
				{"NPORT-12"	,infotconfig.puertos+11	,TYPE_INT},
				{"NPORT-13"	,infotconfig.puertos+12	,TYPE_INT},
				{"NPORT-14"	,infotconfig.puertos+13	,TYPE_INT},
				{"NPORT-15"	,infotconfig.puertos+14	,TYPE_INT},
				{"ACELERA"	,&infotconfig.acelera	,TYPE_INT},
				{"TIPODIR"	,&infotconfig.tipodir	,TYPE_INT},
	           };


int asignavariable(char *cadena)
{
  char *aux;
  int i;
  aux=strchr(cadena,'=');
  if (aux==NULL) {
     warning(("Variable %s no existe",cadena));
     return -1;
   }
  *aux++=0;
  trim(cadena);
  trim(aux);
  for (i=0;i<(sizeof(dvar)/sizeof(defvars));i++) {
      if (strcmp(cadena,dvar[i].nombre)==0) {
         switch (dvar[i].tipo) {
           
			case TYPE_INT:if (*(int *)dvar[i].ptr!=atoi(aux)) {
                       v10log(LOGNORMAL,"Asignando %s a %s\n",aux,cadena);
                       *(int *)dvar[i].ptr=atoi(aux);
					} 
                    break;                   
           
		   case TYPE_LONG:if (*(long *)dvar[i].ptr!=atol(aux)) {
                       v10log(LOGNORMAL,"Asignando %s a %s\n",aux,cadena);
                       *(long *)dvar[i].ptr=atoi(aux);
                     }
                    break;
           
		   case TYPE_CHAR:if (!(*(char *)dvar[i].ptr) || strcmp((*(char **)dvar[i].ptr),aux)!=0) {
						v10log(LOGNORMAL,"Asignando %s a %s\n",aux,cadena);
						if (*(char **)dvar[i].ptr) free(*(char **)dvar[i].ptr);
						*(char **)dvar[i].ptr=strdup(aux);
					 }
                     break;

		   case TYPE_SCHAR:if (!dvar[i].ptr || strcmp(dvar[i].ptr,aux)!=0) {
						v10log(LOGNORMAL,"Asignando %s a %s\n",aux,cadena);
						strcopia(dvar[i].ptr,aux,strlen(aux));
					 }
                     break;

           case TYPE_VCONF:if (*(int *)dvar[i].ptr!=atoi(aux)) {
                       v10log(LOGNORMAL,"Asignando %s a %s\n",aux,cadena);
                       *(int *)dvar[i].ptr=atoi(aux);
					   send_conf=1;
					} 
                    break;                   
          }
         break;
      }
   }
   return 0; 	
}

void leeconf(char *nombre)
{
  static v10horas hlect;
  FILE *entrada;
  char buffer[200];
  if (damecent()-hlect<infotconfig.releeconf) return;
  hlect=damecent();
  entrada=fopenpath(nombre,"r");
  if (entrada==NULL) return;
  while (fgetss(buffer,sizeof(buffer)-1,entrada)) {
        asignavariable(buffer);
   }
  if (send_conf) infograbaconfig();   
//select_channel();
  fclose(entrada);
}

