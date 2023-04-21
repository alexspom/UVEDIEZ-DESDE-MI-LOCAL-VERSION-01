#include "vd.h"
#define MAXHANDLEORAERR 100

static vdoraerrs tablaoraerr[MAXHANDLEORAERR];
static char arranque[MAXCADENA]="";
static int nboraerr=0;
static int enexit=0;


static int reiniciaprog(void)
{
    int ret;
    char cadena[MAXCADENA];
    int i;

    sprintf(cadena, "%s", __argv[0]);
    for (i = 1; i<__argc; i++) {
        sprintf(cadena + strlen(cadena), " \"%s\"", __argv[i]);
    }
    ret = WinExec(cadena, 1);
    abort();
    return(ret);
}

static int vdhandleoraerr(int coderr,v10cursors *c)  {
	int i,ret;	
	vdoraerrs *oraerr=NULL;
	char error_oracle[MAXCADENA]="";
	int (*func)(int,void *,char *);

	for (i=0;i<nboraerr;i++) {
		if (contienenum(tablaoraerr[i].rangoerror,(double)coderr)>0) {
			oraerr = tablaoraerr + i;
			break;
		}
	}
	if (oraerr==NULL) return(0); // no se ha encontrado manejador del error
	
	if (enexit==0) { // no se ha ejecutado ya
		if (*oraerr->funcionalg) {
			if (!stricmp(oraerr->funcionalg,"system")) {
					STARTUPINFO si;
					PROCESS_INFORMATION pi;
					char lineacomando[MAXPATH]="";
					memset(&si,0,sizeof(STARTUPINFO));
#ifndef __LINUX__
					si.cb = sizeof(STARTUPINFO);
#endif				
					sprintf(lineacomando,"%s %d %s %s %s",oraerr->param,coderr,damehostname(),ORAUSR,ORADB);
					ret=CreateProcess( NULL,lineacomando,NULL,NULL,FALSE,0, NULL, NULL, &si, &pi ); 
			
			} else {
				func=damefundll(oraerr->libalgoritmo, oraerr->funcionalg);
				if (!func) v10log(LOGERROR,"No se encuentra funcion %s en librería %s\n",oraerr->funcionalg,oraerr->libalgoritmo);
				else func(coderr,c,oraerr->param);
			}
		}
	} 

	ret=0;
	if (c) getcurerror(c,error_oracle);
	switch (oraerr->nivelerr) {
		case 0: { // error fatal
				if (enexit==0) {		
					v10log(LOGERROR,"Programa finaliza por Error Oracle Fatal %ld en cursor\n\t%s\n",
                        coderr, c?c->nombre:"", error_oracle);			
					if (oraerr->tiempoespera>0) Sleep(oraerr->tiempoespera*1000);					
                    enexit = 1;   
#ifndef __LINUX__
                    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
#endif
					abort();				
				} else ret=1;
				break;
			}
		case 1: { // error debug
				v10log(LOGERROR,"Debug por Error Oracle %ld  en cursor %s\n\t%s\n",
						coderr,   c?c->nombre:"", error_oracle);
				if (oraerr->tiempoespera>0) Sleep(oraerr->tiempoespera*1000);
                ret = 1;
				break;			
        }
        case 2:  { // warning
            v10log(LOGERROR, "Warning por Error Oracle %ld en cursor %s\n\t%s\n",
                   coderr, c ? c->nombre : "", error_oracle);
            if (oraerr->tiempoespera>0) Sleep(oraerr->tiempoespera * 1000);
            ret = 2;
            break;
        }
        case 3:  { // reinicia
            v10log(LOGERROR, "Reiniciando programa por Error Oracle %ld en cursor %s\n\t%s\n",
                   coderr, c ? c->nombre : "", error_oracle);
            reiniciaprog();
            break;
        }
	}
	return(ret);	
} 

void cargahandleoraerr(char *programa,char **argv,int arg) {
	char *ptr;
	int ret,i;
	char exeoraerr[MAXPATH]="";
	vdoraerrs oraerr;
	strcat(arranque,"START ");
	for (i=0;i<arg;i++) {
		strcat(arranque,argv[i]);
		strcat(arranque," ");
	}
	// captura el nombre del ejecutable pasado
	ptr=strrchr(programa,'\\');
	if (ptr) strcpy(exeoraerr,ptr+1);
	else strcpy(exeoraerr,programa);
	ptr=strchr(exeoraerr,'.');
	if (ptr) *ptr=0;
	
	// carga los manejadores de error para el ejecutable en cuestion
	ret=ORAERRbuscahandleerror(strmay(exeoraerr),&oraerr);
	while (ret==0) {
		memcpy(tablaoraerr+nboraerr,&oraerr,sizeof(oraerr));
		nboraerr++;
		ret=ORAERRnexthandleerror(&oraerr);
	}
	
	if (nboraerr>0) {
		// el puntero de la librería apunta a la función de tratamiento de errores oracle
		handleoraerr = vdhandleoraerr;
	}
}
