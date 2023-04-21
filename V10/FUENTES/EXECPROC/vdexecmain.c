/*******************************************************************************
* Función Módulo principal del ejecutor de procesos                            *
* Módulo  vdexecprocmain.c                                                     *
*                                                                              *
* Autor  JCSR	                                                               *
* Revisado por:                                                                *
* Fecha 01-11-2007                                                             *
********************************************************************************/

#include "vdexec.h"


#define TIMMEDIATO 200
#define LNOMBREAPLICACION 300

static int timmediato;


static void revisaejecucioninmediata(void)
{
    int i;    
    
    for (i=0;i<damenumprocesos();i++) {
        procesos *miproceso=dameprocesoi(i);
		if (miproceso->proc.periodo<=timmediato) continue;
        if (PROselejecutainmediato (miproceso->proc.proceso,&(miproceso->proc))==0) {
            //Si hay que ejecutarlo inmediatamente quitamos la marca de ejecución, actualizamos,
            strcpy(miproceso->proc.ejecutainmediato,"");
            PROactualizaejecutainmediato(&miproceso->proc,0);
            commit();
            // y hacemos que el intervalo sea mínimo, para asegurarnos de que en la siguiente comprobación salga que
            // ya es hora de volver a ejecutarlo.
            miproceso->ultejecucion-=miproceso->proc.periodo;
        }
    }
}


static void tituloprocesos(void)
{
    int i;
    char cadena[LNOMBREAPLICACION]="EJECUTADOR DE PROCESOS V10.- PROCESOS(S):";
    char usuario[MAXCADENA];
    
    for(i=0;strlen(cadena)<LNOMBREAPLICACION && (i<damenumprocesos());i++) {
        sprintf(cadena+strlen(cadena) ," %s - ",dameprocesoi(i)->proc.proceso);
    }
    
    if (!es_blanco(ORADB)) sprintf(usuario,"%s@%s",ORAUSR,ORADB);
    else                strcpy(usuario,ORAUSR);
    sprintf(cadena+strlen(cadena)-3," BB.DD.: %s. N. LOG: %ld",usuario,maxnivellog);
    
    if (strlen(cadena) < COLUMNASPANTALLA) {
        memset(cadena+strlen(cadena),' ',COLUMNASPANTALLA - strlen(cadena));
        cadena[COLUMNASPANTALLA] = 0;
    }
    
    initform();
    pintapantallav10(cadena);
}



int main(int argc,char *argv[])
{
    int i;
    int hayproceso,buclestotal=0;
    char *usuariofijo;
    v10horas ultimmediato=0;
    trataparamstd(argc, argv, trataparampremain,  NULL);
	initv10lib(v10hinst, v10hprev);
	trataparamstd(argc, argv, trataparammain, trataparamoracle, NULL);
	ponv10traduce();	
	trataparamstd(argc, argv, cargaparamproceso, NULL);
	cargahandleoraerr(argv[0],argv, argc);
	initlogoracle();	
    asignatecla(ALT('L'),(void *)editalog);
    if (damenumprocesos()==0) final(("No se han informado procesos a ejecutar o estos no se han podido cargar."));
    tituloprocesos();    
	timmediato=damepropentero("TIMMEDIATO");
	if (timmediato==0) timmediato=TIMMEDIATO;  		
    usuariofijo=dameusuariofijo();
    if (!es_blanco(usuariofijo)) VDEXECsetusuario(usuariofijo);
    for(;;) {	
        hayproceso=0;
        if (hay_tecla()) {
            int ret;
            ret=tecla();
            if (ret>='0' && ret<='9') {
                maxnivellog=ret-'0';
                ponnivel(maxnivellog);
            }
            if (ret==A_F(10)) {
               v10log(LOGERROR,"%s","Programa abortado por el usuario, pulsado AF(10)\n");
               return(0);
            }
        }        
        if (damecent()-ultimmediato>timmediato) {
            revisaejecucioninmediata(); //Miramos si hay que hacer una ejecución inmediata.
            ultimmediato=damecent();
        }

        buclestotal++;
        for(i=0;i<damenumprocesos();i++) {
            procesos *miproceso=dameprocesoi(i);
            if (miproceso->fnproceso && (miproceso->ejecuciones<miproceso->proc.ejecuciones || miproceso->proc.ejecuciones==0) && miproceso->proc.periodo>0) {               
                hayproceso=1;
                if (damecent()- miproceso->ultejecucion >= miproceso->proc.periodo) {
                    int antlogoracle;
                    PROselvdprocesos (miproceso->proc.proceso,&miproceso->proc);
					if (*miproceso->proc.activo=='N') {
                        miproceso->ultejecucion=damecent();
						v10log(LOGNORMAL,"Proceso %s no se ejecuta por no estar activo\n",miproceso->proc.proceso);
						continue;
					}
                    if (damelogdiferido()) antlogoracle=quitalogoracle(1);
                    if (es_blanco(usuariofijo)) {
                        if (damenumprocesos()>1 || miproceso->ejecuciones<1) {
                            VDEXECsetusuario(miproceso->proc.proceso);
                        }
                    }
                    if (actualizasid) {		
                        funcactualizasid();
                        actualizasid=0;
                    }
                    // si puede levantar semáfoto,ok, sino, continue
                    if (!es_blanco(miproceso->proc.codsemaforo)) {
                        if (damesemaforo(miproceso->proc.codsemaforo)) {
                            if (miproceso->locksemaforo==0) {
                                v10log(LOGNORMAL,"Proceso %s no se ejecuta al no poder bloquear semáforo %s\n",
                                    miproceso->proc.proceso,miproceso->proc.codsemaforo);
                                miproceso->locksemaforo=1;
                            }
                            continue;	//Levantamos el semáforo, si lo hay, y si está levantado saltamos a la siguiente ejecución del bucle.
                        }
                        commit();
                    }
                    if (miproceso->locksemaforo==1) {
                        v10log(LOGNORMAL,"Proceso %s ejecuta al liberarse el semáforo %s\n",
                            miproceso->proc.proceso,miproceso->proc.codsemaforo);                     
                    }
                    miproceso->locksemaforo=0;
                    v10log(LOGDEBUGAPI,"Ejecucion número %ld del proceso %s\n",++(miproceso->ejecuciones),miproceso->proc.proceso);
                    if ((miproceso->ejecuciones%10000)==0) v10log(LOGNORMAL,"Ejecucion número %ld del proceso %s total %d\n",++(miproceso->ejecuciones),miproceso->proc.proceso,buclestotal);
                    miproceso->fnproceso(miproceso);                     
                    rollback();					
                    if (!es_blanco(miproceso->proc.codsemaforo)) {
                        liberasemaforo(miproceso->proc.codsemaforo); //Dejamos el semáforo bajado para el siguiente.
                        commit();
                    }
                    if (damelogdiferido()) quitalogoracle(antlogoracle);
                    miproceso->ultejecucion=damecent();
                    v10log(LOGDEBUGAPI,"Finalizada ejecucion %ld del proceso %s\n",miproceso->ejecuciones,miproceso->proc.proceso);                
                }                
            }
        }
        if (hayproceso==0) {
            v10log(LOGERROR,"%s","No se encuentra proceso a ejecutar\n");
            return(0);
        }
        Sleep(5);
    }
    return(0);
}


#ifndef __LINUX__	
int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
                   LPSTR cmd, int cmdshow)
{
    int ret;
	v10hinst = hinst;
	v10hprev = hprev;
	SetErrorMode(SetErrorMode(0) | SEM_NOGPFAULTERRORBOX);
    ret=main(__argc,__argv);
    return(ret);
}

#endif	
