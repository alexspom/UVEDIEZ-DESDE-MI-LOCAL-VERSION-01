/****
* PLANIFICADOR.C - 
* 
* Propósito: Ejecutar la tareas planificadas en un fichero plano de configuración
*           
* Autor    : MGM
* Fecha    : 19-11-2007
****
* Modificaciones:
***/

#include "v10planificador.h"

static PLANIF plan[MAXPLANIF];
static PARAM  params;
static char version[LEN_PAN];
static windows wsel,wtareas,wparam;

static int LDEBUG;
static int NUMERO_DELAYS_RELECTURA = MINUTO;
static long NUM_TAREAS;

static int salir=0, inicio=1, cursor=0;
static char ConfArr[2], ConfParo[2], UMIntervalo[2];

static char fichplanif[2*MAXPATH];
static char ficheroLogAnt[MAXPATH];


// Función que devuelve la siguiente ejecución de una tarea
static int proximointervalo(LPPLANIF lpPlan)
{
  v10horas ret;
  v10horas ret1;
  v10horas lAux;
  char *hora;

  // se adelanta la hora de ejecucion al siguiente intervalo
  ret=a2cent(lpPlan->szHoraProxEjec);
  if (ret < 0) {
    v10log(sock,"Error sumando intervalo de %.0lf %s a Hora %s en programa %s\n"
                 "            Se elimina programa del planificador\n",
                  lpPlan->lIntervaloEjecucion,
          strcmp(UMIntervalo,"M") == 0 ? "minutos" : "segundos", 
          lpPlan->szHoraProxEjec,lpPlan->szPrograma);
    *lpPlan->szPrograma=0;
    return(-1);
  }else {
      lAux = a2cent(lpPlan->szHoraLimite);

      if (!strcmp(UMIntervalo,"M"))
        ret+=lpPlan->lIntervaloEjecucion*6000;
    else
      ret+=lpPlan->lIntervaloEjecucion*100;

    if (ret>lAux){
      // si la hora excede del límite el próximo intervalo de ejecución será la hora de inicio
      strcpy(lpPlan->szHoraProxEjec,lpPlan->szHoraInicio);
      lpPlan->lCad = 1;
    }else {
      hora = cent2a(ret,6,':',lpPlan->szHoraProxEjec);
      ret1 = a2cent(hora);
      //if ( 0 < cent2a(ret,6,':',lpPlan->szHoraProxEjec)){
      if (0 > ret1){
            v10log(sock,"Error transformando segundos %.0lf en Hora de planificación  en programa %s\n"
                      "            Se elimina programa del planificador\n",
                    ret,lpPlan->szPrograma);
              *lpPlan->szPrograma=0;
              return(-1);
          }
    }
  }
  return( 0 );
}

// Función que ejecuta automáticamente las tareas en función de su planificación
static int ejecutaplan(LPPLANIF lplpPlan)
{
  int retorno = -1;
  int i;
  v10horas ret;
  v10horas lTimeInSeconds,lTimeProgInSec,lTimeLimit,lTimeInit;
  time_t timer;
  struct tm *tblock;
  char cDay;
  LPPLANIF lpPlan;

  // Obtengo el día y la hora actuales
  timer = time(NULL);
  tblock = localtime(&timer);
  switch(tblock->tm_wday) {
      case 0:
          cDay='D';
          break;
        case 1:
          cDay='L';
            break;
        case 2:
          cDay='M';
            break;
        case 3:
          cDay='X';
            break;
        case 4:
          cDay='J';
            break;
        case 5:
          cDay='V';
            break;
        case 6:
          cDay='S';
            break;
        default:
          return(retorno);
  }

  // Segundo de la hora actual
  lTimeInSeconds=(tblock->tm_hour * 360000 + tblock->tm_min*6000 + tblock->tm_sec*100);
  // Recorremos todas las tareas del fichero de configuración
  for (i=0;i<NUM_TAREAS;i++) {

    // Tarea a analizar
    lpPlan=lplpPlan+i;

    // Si la tarea no tiene un programa asociado no se ejecuta
    if (*lpPlan->szPrograma == 0) continue;

    // La tarea está caducada.
    // pero la hora actual es menor que la ultima ejecución -> nuevo día
    // Liberamos la tarea
    if(lpPlan->lCad==1 && lTimeInSeconds < a2cent(lpPlan->szHoraUltEjec)) {
      v10log(sock,"Anulada caducidad de la tarea \"%s\"\n",lpPlan->descripcion);
          lpPlan->lCad = 0;
          strcpy(lpPlan->szHoraProxEjec,lpPlan->szHoraInicio);
    }

    // Tarea caducada. Ha pasado el tiempo de ejecutarse
    if (lpPlan->lCad == 1) continue;

    // El día actual no está en la lista de días en que se ha de ejecutar
      if (NULL == strchr(lpPlan->szDiasEjecucion,cDay)) continue;

        // Primera ejecucion
    if (lTimeInSeconds >=0 && lTimeInSeconds <=1)
          strcpy(lpPlan->szHoraProxEjec,lpPlan->szHoraInicio);

        //
    lTimeLimit=a2cent(lpPlan->szHoraLimite);
    lTimeProgInSec=a2cent(lpPlan->szHoraProxEjec);
    ret = ceil((lTimeProgInSec+0.5)/100) - ceil((lTimeInSeconds+0.5)/100);

    // lTimeInSeconds = Hora actual
    // lTimeLimit = Hora límite de la tarea a ejecutar
    // La hora actual ha pasado del límite de la tarea... no toca ejecutarla ahora
    if (ret>0) continue;

    if (ret < 0) {
          if (-ret<params.timeout && lpPlan->lIntervaloEjecucion!=0 ){
        v10log(sock,"Tiempo de ejecución tarea %s dentro del timeout válido (%.0lf segundos) alcanzado\n",
                            lpPlan->szPrograma, params.timeout);
        ret = 0;
      }
          // Avanzamos al siguiente intervalo
      while ((lTimeProgInSec < lTimeInSeconds) &&  (lTimeLimit > lTimeInSeconds) ) {
              if (0<proximointervalo(lpPlan)) break;
        lTimeProgInSec=a2cent(lpPlan->szHoraProxEjec);
        lTimeInit=a2cent(lpPlan->szHoraInicio);
        if (lTimeProgInSec==lTimeInit) break;
                // Escribimos la hora de la próxima ejecución
        if (LDEBUG && lTimeProgInSec > lTimeInSeconds && lpPlan->activa==1)
                  v10log(1,"Tarea \"%s\" se ejecutará a las %s\n",
                       lpPlan->descripcion,lpPlan->szHoraProxEjec);
      }
    }

    // Si es la hora de ejecucion ejecutamos la tarea
    if (ret==0 && !lpPlan->lEjecutado) {
      //Ejecución del programa
      if (lpPlan->activa == 1){   
          char hora[9];
          cent2a(gettime(),0,':',hora);
          strcpy(lpPlan->szHoraUltEjec, hora);
          ret=WinExec(lpPlan->szPrograma,SW_MINIMIZE);
          v10log(1,"Ejecución %s de \"%s\"\n", (ret > 31 ? "CORRECTA" : "INCORRECTA"),lpPlan->descripcion);
     }

      proximointervalo(lpPlan);
      retorno = 0;
      lpPlan->lEjecutado=1;
      lpPlan->lUltimaEjecucion = lTimeProgInSec;
    }else if (lpPlan->lEjecutado) {
      if (fabs(lpPlan->lUltimaEjecucion - lTimeInSeconds) > params.timeout)
      lpPlan->lEjecutado=0;
    }
  }
  return(retorno);
}


// Título de la ventana del planificador
static void triger() 
{
	char hora[9];
	cent2a(gettime(),0,':',hora);
    imprimep(0,0,0x00ffffff,0x7f,"PLANIFICADOR DE TAREAS                                                                                                              ",0,COLUMNASPANTALLA);
	imprimep(COLUMNASPANTALLA-9,0,0x00ffffff,0x7f,hora,0,8);
}                                     

// Función que pinta los parámetros del fichero de configuración en la ventana de detalle
static void pintaparametros(void)
{
    char nombrelog[MAXPATH];
    dimenombrelog(nombrelog);
    clv(&wparam);
    v10printf(&wparam,"\n");
    v10printf(&wparam,"\tFichero de tareas: %s \n", fichplanif );
    v10printf(&wparam,"\tFichero de LOG: %s \n", nombrelog );
    v10printf(&wparam,"\tMinutos de relectura del fichero de tareas: %ld \n", params.minutosRelectura );
    v10printf(&wparam,"\tLog Continuo: %s \n", params.logContinuo == 1 ? "SI" : "NO" );
    v10printf(&wparam,"\tConfirmacion de ejecucion en el ARRANQUE: %s \n", strcmp(params.confArranque,"N")==0 ? "NO" : "SI" );
    v10printf(&wparam,"\tConfirmacion de ejecucion en el PARO: %s \n", strcmp(params.confParo,"N")==0 ? "NO" : "SI" );
    v10printf(&wparam,"\tTIMEOUT para ejecutar una tarea: %.0lf seg. \n", params.timeout );
    v10printf(&wparam,"\tUnidad de medida del Intervalo de tiempo para \n\tejecutar una tarea: %s (%s) \n", params.unimedIntervalo,strcmp(params.unimedIntervalo,"M")==0 ? "Minutos" : "Segundos" );
}


// Función desde la que se abren las ventanas del planificador
static int init_wins(void)
{
  char szAux[LEN_PAN]="";
//  char nombrelog[MAXPATH],nombrepant[MAXPATH];

  v10usaansi=1;

    // Abrimos la ventana del título
  triger();
  pontrigervivo(triger);
  
  // Inicio de la ventana de Detalle
  initvn(&wtareas,30,2,120,13,"TAREAS");
  poncolorv(&wtareas,CNORMAL);

  // Inicio de la ventana de Parametros
  initvn(&wparam,30,16,98,24,"TAREAS");
  enmarca(&wparam,1," PARAMETROS ");
  poncolorv(&wparam,CNORMAL);

  // Abrir el fichero log
  initv10logparam(strcat("planificador",".log"),1,27,COLUMNASPANTALLA-2,(LINEASPANTALLA-27)-3);
  return( 0 );
}

// Función que pinta el detalle de las tareas
static void pintadetalles(PLANIF tarea)
{
    char texto[32]; 
    
    clv(&wtareas);
    enmarca(&wtareas,1," DETALLE TAREA ");   
    v10printf(&wtareas,"\n");
    
    switch(tarea.activa){
    case 0:
        strcpy(texto,"INACTIVA");
        break;
    case 1:
        strcpy(texto,"ACTIVA");
        break;
    default:
        strcpy(texto,"INACTIVA");
        break;
    }
    v10printf(&wtareas,"    %s\n\n\t\t%s\n",tarea.descripcion, texto);
    v10printf(&wtareas,"\t%s\n",tarea.szPrograma);
    v10printf(&wtareas,"\tDias de ejecución: %s\n",tarea.szDiasEjecucion);
    v10printf(&wtareas,"\tHora inicio: %s\tHora fin: %s\n",tarea.szHoraInicio,tarea.szHoraLimite);
    v10printf(&wtareas,"\tIntervalo de ejecución: %.0lf %s.\n\n",tarea.lIntervaloEjecucion, strcmp(UMIntervalo,"M") == 0 ? "min" : "seg");
    v10printf(&wtareas,"\tPróxima ejecución: %s\n",tarea.szHoraProxEjec);
    v10printf(&wtareas,"\tÚltima ejecución: %s\n",tarea.szHoraUltEjec);
}

// Función que lee los parámetros del fichero de configuración
static void leeparam(char *fichplanif, PARAM *parametros)
{
	FILE *f;
	char szBuff[STRING_PAR];
	char szAux1[STRING_PAR];
	char szAux2[STRING_PAR];
	char straux[STRING_PAR]="PLANIFICADOR";
	char *aux;
	int logContinuo=0,ficheroLog=0,minutosRelectura=0,confArranque=0,confParo=0,timeout=0;
	int nnombrepipe=0; 
	int ret,i;
	int unimedIntervalo=0;

	int remoteplanif=0; 

	// Parámetros por defecto
	parametros[0].logContinuo = 1;
	parametros[0].minutosRelectura = 5;
	strcpy(parametros[0].confArranque,"N");
	strcpy(parametros[0].confParo,"N");
	parametros[0].timeout=MAX_TIMEOUT;
	strcpy(parametros[0].unimedIntervalo,"M"); 

	// Abrimos el fichero de tareas
	if (NULL == (f = fopen(fichplanif,"r"))) {
		v10log(1,"Error abriendo %s\n"
			"USO:planificador [FICHERO_PLANIFICACION]",fichplanif);
		return;
	}

	// Leemos los parámetros
	while (fgets(szBuff,sizeof(szBuff),f)) {
		if (*szBuff=='#' || *szBuff=='\n') continue;
		if (*szBuff=='$') break;

		// Nombre del parámetro
		if (0 > (ret=piece(szBuff,szAux1,"=",1))) {
			v10log(1,"El nombre de parametro especificado:\n            %s\n"
				"es incorrecto.\n",szBuff);
			break;
		}

		if (ret < 0) continue;

		// Valor del parámetro
		aux=strstr(szBuff, "=")+1;
		if (0 > (ret=piece(aux,szAux2,"\n",1))) {
			v10log(1,"El contenido del parametro especificado:\n            %s\n"
				"es incorrecto.\n",szBuff);
			break;
		}

		if (ret < 0) continue;

		// Formateamos el parámetro y su valor
		i=0;
		while (isspace(szAux1[i])){
			aux = &szAux1[i+1];
			i++;
		}

		if(szAux1[0]==' ') strcpy(szAux1,aux);
		if(strchr( szAux1,' ')){
			strcpy(szBuff,szAux1);
			piece(szBuff,szAux1," ",1);
		}

		i=0;
		while (isspace(szAux2[i])){
			aux = &szAux2[i+1];
			i++;
		}
		if(szAux2[0]==' ') strcpy(szAux2,aux);
		if(strchr( szAux2 , ' ')){
			strcpy(szBuff,szAux2);
			piece(szBuff,szAux2," ",1);
		}

		// Asignamos los valores definitivos a los parámetros
		if(strcmp(szAux1,"LOG_CONTINUO")==0){
			if(strcmp("-",szAux2)) parametros[0].logContinuo = atoi(szAux2);
			else parametros[0].logContinuo = 1;
			logContinuo++;
		}
		if(strcmp(szAux1,"MINUTOS_RELECTURA")==0){
			if(strcmp("-",szAux2)) parametros[0].minutosRelectura = atoi(szAux2);
			else parametros[0].minutosRelectura = 5;
			minutosRelectura++;
		}
		if(strcmp(szAux1,"CONF_ARRANQUE")==0){
			if(strcmp("-",szAux2)) strcpy(parametros[0].confArranque,szAux2);
			else strcpy(parametros[0].confArranque,"N");
			confArranque++;
		}
		if(strcmp(szAux1,"CONF_PARO")==0){
			if(strcmp("-",szAux2)) strcpy(parametros[0].confParo,szAux2);
			else strcpy(parametros[0].confParo,"N");
			confParo++;
		}
		if(strcmp(szAux1,"TIMEOUT")==0){
			if(strcmp("-",szAux2)) parametros[0].timeout = atoi(szAux2);
			else parametros[0].timeout = MAX_TIMEOUT;
			timeout++;
		}
		if(strcmp(szAux1,"UNIMED_INTERVALO")==0){
			if(strcmp("-",szAux2)) strcpy(parametros[0].unimedIntervalo,szAux2);
			else strcpy(parametros[0].unimedIntervalo,"M");    

			unimedIntervalo++;
		}
	}
	fclose( f );

	// Abrimos las ventanas del planificador
	if (inicio) init_wins();
	else v10log(1,"RELECTURA del fichero de planificacion %s\n",fichplanif);

	LDEBUG=params.logContinuo;

	NUMERO_DELAYS_RELECTURA = MINUTO * (params.minutosRelectura>=1 ? params.minutosRelectura : DEFAULT_INTERVAL_READ); 
	strcpy (ConfArr, params.confArranque);
	strcpy (ConfParo, params.confParo);
	strcpy (UMIntervalo, params.unimedIntervalo); 

	if(LDEBUG) {
		v10log(1,"FICHERO DE PLANIFICACION: %s\n            LOG CONTINUO: %s\n            RELECTURA DEL FICHERO %s CADA %ld MINUTOS\n            CONFIRMACION TAREAS EN EL ARRANQUE=%s\n            CONFIRMACION TAREAS EN EL PARO=%s\n\n            TIMEOUT PARA EJECUCIÓN: %.0lf\n            UNIDAD DE MEDIDA DE INTERVALO DE EJECUCIÓN: %s (%s)\n",
			fichplanif,(params.logContinuo==0 ? "NO":"SI"),fichplanif,params.minutosRelectura, (strcmp(params.confArranque,"N")==0 ? " NO":" SI"), (strcmp(params.confParo,"N")==0 ? " NO":" SI"),params.timeout,params.unimedIntervalo,strcmp(params.unimedIntervalo,"M") == 0 ? "Minutos" : "Segundos");

		if(!(logContinuo && timeout && ficheroLog && minutosRelectura && confArranque && confParo && unimedIntervalo)){ 
			v10log(sock,"Error en el numero de parametros definidos:\n");
			if(!logContinuo)
				v10log(sock,"            LOG_CONTINUO no definido, asignado valor por defecto\n");
			if(!minutosRelectura)
				v10log(sock,"            MINUTOS_RELECTURA no definido, asignado valor por defecto\n");
			if(!confArranque)
				v10log(sock,"            CONF_ARRANQUE no definido, asignado valor por defecto\n");
			if(!confParo)
				v10log(sock,"            CONF_PARO no definido, asignado valor por defecto\n");
			if(!timeout)
				v10log(sock,"            TIMEOUT no definido, asignado valor por defecto\n");
			if(!unimedIntervalo)
				v10log(sock,"            UNIMED_INTERVALO no definido, asignado valor por defecto\n");
			if(!nnombrepipe)
				v10log(sock,"            MASTERPLANIF no definido, no se permiten ejecuciones remotas\n");
			if(!remoteplanif)
				v10log(sock,"            REMOTEPLANIF no definido, asignado valor por defecto\n");
		}
	}

	// Pintamos los parámetros en la ventana de detalle
	pintaparametros();
}

// Función que lee las tareas del fichero de configuración 
static void leeplan(char *fichplanif,LPPLANIF lplpPlan)
{
  FILE *f;
  char szBuff[STRING_PAR];
  char szAux[STRING_PAR];
  char szAux2[8], szAux3[MAXPATH];
  int  i, j;
  int n = 0,m;
  int ret;
  int param = 1;

  // Abrir fichero de configuración para lectura
  if (NULL == (f = fopen(fichplanif,"r"))) {
	  v10log(1,"Error abriendo %s\n"
		  "USO:planificador [FICHERO_PLANIFICACION]",fichplanif);
	  return;
  }

  // Leemos el fichero de parámetros
  while (fgets(szBuff,sizeof(szBuff),f)) {
	  if (param) {
		  // ascii 36 = $
		  if(strchr(szBuff,36)) param=0;
		  continue;
	  }
	  if (*szBuff=='#' || *szBuff=='\n') continue;

	  if(!param){
		  for (m=0; m<MAX_ITEMS; m++) {
			  if (0 > (ret=piece(szBuff,szAux,"#",m+1))) {
				  v10log(1,"La orden planificada:\n            %s\n"
					  "es incorrecta en la subpieza %ld.\n", szBuff, m+1);
				  break;
			  }
			  if (ret < 0) continue;
			  switch (m) {
		  case 0:
			  strcpy(lplpPlan[n].descripcion, szAux);
			  break;
		  case 1:
			  if ( !strcmp(szAux,"S") ) lplpPlan[n].activa = 1;
			  else lplpPlan[n].activa = 0;
			  break;
		  case 2:
			  strcpy(lplpPlan[n].szPrograma, szAux);
			  break;
		  case 3:
			  strcpy(lplpPlan[n].szDiasEjecucion, szAux);
			  break;
		  case 4:
			  strcpy(lplpPlan[n].szHoraInicio, szAux);
			  strcpy(lplpPlan[n].szHoraProxEjec, lplpPlan[n].szHoraInicio);
			  break;
		  case 5:
			  lplpPlan[n].lIntervaloEjecucion = atol(szAux);
			  break;
		  case 6:
			  if (!strcmp(szAux,"-") || *szAux==0)
				  strcpy(lplpPlan[n].szHoraLimite, "23:59:59");
			  else
				  strcpy(lplpPlan[n].szHoraLimite, szAux);
			  break;
		  default:
			  break;
			  }
		  }
	  }
	  // Escribimos en el log si es necesario
	  if (LDEBUG) {
		  if (NULL!=strchr(lplpPlan[n].szDiasEjecucion,'A'))
			  v10log(1,"Tarea \"%s\" se ejecutará al arranque.\n",
			  lplpPlan[n].descripcion);
		  if (NULL!=strchr(lplpPlan[n].szDiasEjecucion,'P')) 
			  v10log(1,"Tarea \"%s\" se ejecutará al paro.\n",
			  lplpPlan[n].descripcion);

		  if (NULL!=strchr(lplpPlan[n].szDiasEjecucion,'L') || NULL!=strchr(lplpPlan[n].szDiasEjecucion,'M') ||
			  NULL!=strchr(lplpPlan[n].szDiasEjecucion,'X') || NULL!=strchr(lplpPlan[n].szDiasEjecucion,'J') ||
			  NULL!=strchr(lplpPlan[n].szDiasEjecucion,'V') || NULL!=strchr(lplpPlan[n].szDiasEjecucion,'S') ||
			  NULL!=strchr(lplpPlan[n].szDiasEjecucion,'D')) {
				  for (i=0, j=0; i<strlen(lplpPlan[n].szDiasEjecucion); i++) {
					  if (lplpPlan[n].szDiasEjecucion[i]!='A' && lplpPlan[n].szDiasEjecucion[i]!='P') {
						  szAux2[j]=lplpPlan[n].szDiasEjecucion[i];
						  j++;
					  }
				  } 
				  szAux2[j]='\0';
				  sprintf (szAux3, "\n            a intervalos de %.0lf %s y la hora límite es %s\n",
					  lplpPlan[n].lIntervaloEjecucion, 
					  strcmp(UMIntervalo,"M") == 0 ? "minutos" : "segundos", 
					  lplpPlan[n].szHoraLimite);
				  v10log(1,"Tarea %s \n            se ejecutará a las %s cada %s%s",
					  lplpPlan[n].szPrograma, lplpPlan[n].szHoraInicio, szAux2,
					  lplpPlan[n].lIntervaloEjecucion!=0 ? szAux3 : "\n");
		  }
	  }
	  // Se ha alcanzado el número máximo de tareas
	  if (++n == MAXPLANIF) {
		  v10log(1,"Se ha alcanzado el máximo número de tareas [%ld] permitido.\n",n);
		  break;
	  }
  }
  NUM_TAREAS = n;
  fclose( f );
}
// Función que pinta las tareas en la ventana de tareas así como su color en función de si están activas o no.
static void pintatarea(virtsels *s, int resaltado)
{
    PLANIF *p=s->dato;
    int ind=VIRTPOS(s);
    
    poncolorv(&s->v,CNORMAL);
    v10printf(&s->v,"  ");
    if (resaltado) poncolorv(&s->v,CMARCOR);
    else {
        if (p[ind].activa == 0) poncolorv(&s->v,CMARCA);
        else poncolorv(&s->v,CNORMAL);
    }
    v10printf(&s->v,"%s",p[ind].descripcion);
    pintadetalles(p[ind]);
}

// Función que busca si se pulsa una tecla clave sobre la ventana de tareas
static int teclatarea(virtsels *s)
{
    PLANIF *p=s->dato;
    int ind=VIRTPOS(s);
    
    v10horas hult=damecent();
    while (damecent() - hult < 100) {
        Sleep(INTERVALO_DELAY);
        
        // Miramos si se ha pulsado alguna tecla y la recogemos
        if (hay_tecla()) {
            int ret = tecla();
            
            // Alt('E') - Ejecución inmediata de la tarea.
            if ( ret == ALT('E') ) {
                char hora[9];
                cent2a(gettime(),0,':',hora);
                strcpy(p[ind].szHoraUltEjec, hora);
                if (p[ind].activa==1){
                    // Si la tarea está activa la ejecutamos
                    ret = WinExec(p[ind].szPrograma, SW_MINIMIZE);
                    v10log(1,"Ejecución %s de \"%s\"\n",
                        (ret > 31 ? "CORRECTA" : "INCORRECTA"),p[ind].descripcion);
                }
                else 
                    // Si la tarea no está activa no dejamos ejecutar
                    v10log(1,"Tarea \"%s\" INACTIVA\n",p[ind].descripcion);
            }
                        
            // A_F(10). Fin del planificador
            if ( ret == A_F(10) ) {
                salir = 1;
                return(esc);
            }
            
            // A_F(8). Relectura del planificador
            if ( ret == A_F(8) ) {
                memset(&plan,0,sizeof(plan));
                leeparam(fichplanif,&params);
                leeplan(fichplanif,&plan[0]);
            }
            
            // ALT('A'). Cambio la tarea de activa a inactiva y viceversa
            if ( ret == ALT('A') ) {
                if (p[ind].activa==1) p[ind].activa = 0;
                else if (p[ind].activa==0) p[ind].activa = 1;
            }
            
            // ALT('T'). Edito el fichero de tareas.
            if ( ret == ALT('T') ) {
                invocaeditor(fichplanif,NULL);
            }
            
            return( ret );
        }
    }
    return( esc );
}


// Función que ejecuta las tareas en el arranque y el paro del planificador
static void func_arr_paro(void)
{
    int i, ret, sn;
    LPPLANIF lpPlan;
    
    v10log (1, "Ejecución de las tareas en %s.\n",  (inicio == 1 ? "ARRANQUE" : "PARO"));
    
    // Pedimos confirmación de la ejecución de las tareas en el arranque y en el paro
    if (inicio) {
        if (*ConfArr != 'N' && *ConfArr != 'n') {
            sn = confirmasnfc(7," ¿Realmente quiere ejecutar tareas en el ARRANQUE? ");
            if (sn != 1) {
                v10log (1, "Se ha pulsado NO a la confirmación de de la ejecución de las tareas en el ARRANQUE.\n");
                return;
            }
        }
    } else {
        if (*ConfParo != 'N' && *ConfParo != 'n') {
            sn = confirmasnfc(7," ¿Realmente quiere ejecutar tareas en el PARO? ");
            if (sn != 1) {
                v10log (1, "Se ha pulsado NO a la confirmación de de la ejecución de las tareas en el PARO.\n");
                return;
            }
        }
    }
    
    
    for ( i = 0; i < NUM_TAREAS; i++ ) {
        lpPlan = &plan[i];
        
        if (inicio) {
            // Ejecutamos las tareas en el arranque
            if (NULL != strchr(lpPlan->szDiasEjecucion, 'A')) {
                char hora[9];
                cent2a(gettime(),0,':',hora);
                strcpy(lpPlan->szHoraUltEjec, hora);
                if (lpPlan->activa){
                    ret = WinExec(lpPlan->szPrograma, SW_MINIMIZE);
                    v10log(1, "Ejecución %s de \"%s\" en el ARRANQUE\n",
                        (ret > 31 ? "CORRECTA" : "INCORRECTA"), lpPlan->descripcion);
                }
            }
        } else {
            // Ejecutamos las tareas en el paro
            if (NULL != strchr(lpPlan->szDiasEjecucion, 'P')) {
                char hora[9];
                cent2a(gettime(),0,':',hora);
                strcpy(lpPlan->szHoraUltEjec, hora);
                if (lpPlan->activa){
                    ret = WinExec(lpPlan->szPrograma, SW_MINIMIZE);
                    v10log( 1, "Ejecución %s de \"%s\" en el PARO\n",
                        (ret > 31 ? "CORRECTA" : "INCORRECTA"), lpPlan->descripcion);
                }
            }
        }
    }
    v10log (1, "Fin de la ejecución de las tareas en %s.\n",  (inicio == 1 ? "ARRANQUE" : "PARO"));
}

// Trata los parámetros propios del planificador
static int trataparamplanif(char *cadena)
{
    switch (toupper(*cadena)) {
          case 'F' :strcpy(fichplanif,cadena+1);   
                    break;
    }

    return(0);
}


int main(int argc,char *argv[])
{
    int n,m,ret;
    
    
    trataparamstd(argc,argv,trataparampremain,NULL);
    initv10lib(v10hinst,v10hprev);
    trataparamstd(argc,argv,trataparammain,NULL);
    
    
    // Buscamos el fichero de configuración
    strcpy(fichplanif,FILE_PROC);
    trataparamstd(argc,argv,trataparamplanif,NULL);
    
    // Accedemos al fichero de configuración
    if (0!=access(fichplanif,04)) {
        v10log(1,"Error abriendo %s\n"
            "USO:planificador [FICHERO_PLANIFICACION [LOG_CONTINUO(1-0) [MINUTOS_RELECTURA_FICHERO] ] ] [Confirmación Arranque(S/N)] [Confirmación Paro(S/N)]",fichplanif);
        mensajefcm (10, " Fichero\n %s \n no se encuentra. ", fichplanif);
        return(-1);
    }
    pintaonline("{Alt-T} Edicion fichero tareas {Alt-F8} Relectura fichero tareas {Alt-E} Ejecutar tarea {Alt-A} Desactivar tarea {Alt-F10} Salir");
    
    for(n=m=0;;) {
        if ( m == 0) {
            if (LDEBUG) memset(&plan, 0, sizeof(plan));
            
            // Leemos los parámetros del fichero de configuración
            leeparam(fichplanif,&params);
            
            // lectura de las tareas
            v10log( 1, "Lectura de las tareas a ejecutar en %s \n", fichplanif);
            leeplan( fichplanif, &plan[0]);
        }
        
        // Control a la ventana de seleccion
        initvn(&wsel,1,2,27,24,"TAREAS");
        clv(&wsel);
        
        // Pintamos la ayuda si se solicita, sino los detalles de cada tarea
        pintadetalles(plan[cursor]);
        
        // Pintamos las características de las tareas
        cursor = selecciona( 0, 2, 0, 0, 1, &wsel, NUM_TAREAS, 1, 1,
            WANCHO(&wsel), "TAREAS", pintatarea, teclatarea, cursor, plan);
        
        // Releemos el fichero de configuración si hemos llegado al tiempo de relectura
        if (++m >= NUMERO_DELAYS_RELECTURA) m=0;
        
        // Ejecución de las tareas en el arranque y en el paro del planificador
        if (inicio) {
            func_arr_paro();
            inicio = 0;
            atexit(func_arr_paro);
        }
        
        // Ejecutamos las tareas
        ret=ejecutaplan(plan);
        
        if (salir) {
            v10log (1, "Ejecucion detenida por el usuario {Alt-F10}\n");
            break;
        }
    }
    
    return(0);
}

#ifndef __LINUX__

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
           LPSTR cmd, int cmdshow)
{
  int ret;
  initv10lib(hinst,hprev); 
  initv10lib(hinst,hprev);
  ret=main(_argc,_argv);
  return(ret);
}
#endif


