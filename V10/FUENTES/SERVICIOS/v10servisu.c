#include "vd.h"

#define MAXSERVICIOS 100
#define MITIMER "refrescavisu"
typedef struct {
	char codgruposerv[LCODGRUPOSERV];
	char arranquegrupo[LARRANQUE];
	char codservicio[LCODSERVICIO];
	char activo[LACTIVO];
	char puertopant[6];
	char puertolog[6];
	char pid[10];
	char status[5];
} menuservs;

static menuservs arrser[MAXSERVICIOS];
static int numservicios;
static int seract;
static v10socks *pmx=NULL;
static char horamenu[9]="";
static v10horas ultmenu;
#define INTMENU 2000


static int leecarespera(v10socks *p)
{
    int ret;
    while ((ret=v10socksigcar(p))==-1) if (p->status!=STSOCKREADY) return(-1);
    return(ret);
}

static int leeshortespera(v10socks *p)
{
    int c1,c2;
    c1=leecarespera(p);
    if (c1==-1) return(-1);
    c2=leecarespera(p);
    if (c1==-1) return(-1);
    return (c2<<8)+c1;
}


static void liberaventanarem(v10socks *p)
{
    v10socklibera(p);
}

static void tratacliente(v10socks *p)
{
    int columnas,filas,i;
    char *ptr;
    v10horas inicio;
    extrawins *t=dameextrawin(hwnddefecto);
    columnas=leecarespera(p);
    if (columnas==-1) return;
    filas=leecarespera(p);
    if (filas==-1) return;
    inicio=gettime();
    for (i=0;i<filas;i++) {
        int ret,leer;
        ptr=((char *)t->texto)+t->columnas*i*sizeof(tpixels);
        leer=columnas*sizeof(tpixels);
        while (leer>0) {
            ret=v10sockread(p,ptr,leer);
            ptr+=ret;
            leer-=ret;
            if (gettime()-inicio>200) break;
        }
    }
    InvalidateRect(hwnddefecto,NULL,0);
}

static void mandacar(v10socks *p,int op,int lon,char *buffer)
{
  int tec=0;
  v10sockescribe(p,&tec,sizeof(short));
}

static void ponbreak(v10socks *p,int op,int lon,char *buffer)
{
    cls(0,0,COLUMNASPANTALLA-1,LINEASPANTALLA-1,0);
    v10log(LOGNORMAL,"Perdida conexion\n");
}

static int visudirecto(char *maquina,char *puerto,char *servicio,int mx) 
{
	int tec;
    int reint;
    v10socks *p;
    char titulo[MAXPATH];
	if (mx) sprintf(titulo,"VISUALIZANDO ORDENADOR: %-30.30s               SERVICIO: %-30.30s        Servicio %d de %d",maquina,servicio,seract+1,numservicios);
	else sprintf(titulo,"VISUALIZANDO SERVICIO: %-30.30s               ORDENADOR: %-30.30s        Puerto: %s",servicio,maquina,puerto);
    SetWindowText(hwnddefecto,titulo);
    p=v10socknuevocliente(maquina,puerto,1,TAMRECSERVER*2,NULL,mandacar,NULL,ponbreak,NULL);
    if (p==NULL) {
		mensajefcm(10," Servicio: %s\n No existe puerto %s en maquina %s\n",servicio,puerto,maquina);			
		if (mx) return(ALT('M'));
		else return(ALT('T'));
    }
    while (1) {
        tec=0;
        reint=0;
        while (!hay_tecla() && reint<30) {
            Sleep(10); 
            reint++;
        }
        if (hay_tecla()) tec=tecla();
        if (tec==ALT('T') || (mx && (tec==ALT('M')))) break;
        if (tec==scuu) {
            tec=stab;
            break;
        }
        if (tec==scua) {
            tec=tab;
            break;
        }
        v10log(LOGDEBUG,"Encolo tecla %d\n",tec);
        if (tec!=A_F(10)) {
            if (v10sockhaycar(p)) tratacliente(p);
            if (p->status==STSOCKREADY)  v10sockescribe(p,&tec,sizeof(short));
		} 
    }
   liberaventanarem(p);
   return(tec);
}


static void pideservicios(char *maquina, char *puerto)
{
	int i,tec,lon,encomando=0,servrecib;
	v10horas ultcent;
	char buffer[MAXCADENA]="",subbuffer[MAXCADENA]="",ctecla[3]="  ",ch;

	if (pmx && pmx->status==STSOCKROTA) {
		mensajefcm(10,"Pideservicios: Rota conexión con puerto %s en maquina %s\n",puerto,maquina);			
		v10socklibera(pmx);
		pmx=NULL;
	}

	while (!pmx) {
		pmx=v10socknuevocliente(maquina,puerto,0,TAMRECSERVER*2,NULL,mandacar,NULL,ponbreak,NULL);
		if (pmx==NULL) {
			mensajefcm(10,"Pideservicios: No existe puerto %s en maquina %s\n",puerto,maquina);			
			continue;
		}
		ultcent=damecent();
		while (pmx->status!=STSOCKREADY) {
			Sleep(10);
			if (hay_tecla()) tecla();
			if (damecent()-ultcent>500) {				
				mensajefcm(10,"Multiplexor de Visualiza:\n\n No se puede conectar socket a puerto %s:%s \n",maquina,puerto);
				ultcent=damecent();
			}
		}
		break;
	}
	
	tec=ALT('M');
	v10sockescribe(pmx,&tec,sizeof(short));
	v10sockprintf(pmx,"MENU$");	
	while (!v10sockhaycar(pmx)) Sleep(100);	
	while (1) {	
		if (v10sockhaycar(pmx)) {
			if (encomando==0) {
				lon=v10sockread(pmx,ctecla,sizeof(short));
				tec=*((short *)ctecla);
				lon=0;
				if (tec==ALT('M')) {				
					memset(buffer,0,MAXCADENA);	
					encomando=1;
				} 
			} else {
				ch=v10socksigcar(pmx);
				if (ch=='$') {
					encomando=0;
					break;
				} else buffer[lon++]=ch;
			}
		}
	}

	numservicios=0;
	servrecib=numpieces(buffer,"#");
	ultmenu=damecent();
	cent2a(ultmenu,0,':',horamenu);	
	for (i=0;i<servrecib;i++) {
		memset(subbuffer,0,sizeof(subbuffer));
		piece(buffer,subbuffer,"#",i+1);
		piece(subbuffer,arrser[numservicios].codgruposerv,";",1);
		piece(subbuffer,arrser[numservicios].arranquegrupo,";",2);
		piece(subbuffer,arrser[numservicios].codservicio,";",3);
		piece(subbuffer,arrser[numservicios].activo,";",4);
		piece(subbuffer,arrser[numservicios].puertopant,";",5);
		piece(subbuffer,arrser[numservicios].puertolog,";",6);
		piece(subbuffer,arrser[numservicios].pid,";",7);
		piece(subbuffer,arrser[numservicios].status,";",8);
		numservicios++;
	}
}



static void presservicios(virtsels *s,int resaltado)
{
	windows *w=&s->v;
	int pos=VIRTPOS(s);
	if (resaltado) poncolorv(w,CINPUTACT);
	   else        poncolorv(w,CINPUTINAC);
  	v10printf(w,"%2d   %-30.30s %-30.30s %-5.5s %-5.5s   %-8.8s   %-4.4s",pos+1,arrser[pos].codgruposerv,arrser[pos].codservicio,
		arrser[pos].puertopant,arrser[pos].puertolog,arrser[pos].pid,arrser[pos].status);
	poncolorv(w,CINPUTINAC);
}

static int teclaservicios(virtsels *s)
{
    int ret;
    ret=tecla();
	if (ret==ALT('T')) exit(0);
	if (ret==ALT('M')) encolatecla(ALT('M'));
	if (ret==tab) ret=cua;
	if (ret==cua && s->clin+1==numservicios) ret=home;
	if (ret==stab) ret=cuu;
	if (ret==cuu && s->clin==0) ret=end;	
    return(ret);
}

static void actualizatitulo(char *maquina) {	
	char horaactual[9]="",titulo[MAXPATH]="";	

	cent2a(damecent(),0,':',horaactual);	
	sprintf(titulo," MENU DE VISUALIZADOR EN EQUIPO: \'%s\'                                             Cargado en hora %s.    Hora actual: %s.   Tiempo Refresco: %d seg.",maquina,horamenu,horaactual,INTMENU/100);
    SetWindowText(hwnddefecto,titulo);	
}


static void encolateclamenu(v10timers *lt) {
	if (damecent()-ultmenu>INTMENU) encolatecla(ALT('M'));
	else actualizatitulo(lt->dato);
}

static void menuservicios(char *maquina,char *puerto)
{
	windows w;
	char titulomenu[MAXCADENA]="";

	cls(0,0,COLUMNASPANTALLA-1,LINEASPANTALLA-1,0);	
	sprintf(titulomenu,"Num %-30.30s %-30.30s %-5.5s %-5.5s   %-8.8s   %-4.4s       ","Grupo de Servicios","Servicio","PPant","PLog","Pid","Stat");
	initvn(&w,2,3,108,50,"DEFECTO");		
	pideservicios(maquina,puerto);
	actualizatitulo(maquina);
	pintaonline("{Atl+M} Refresca Menú {Alt+T} Salir {cua/tab} Opción abajo {cuu/Shift+tab} Opción arriba {Enter/DBclick} Visualiza servicio");
	declarav10timernt(MITIMER,encolateclamenu,100,TIMERTIMEOUT,maquina);
	seract=selecciona(1,1,1,1,0,&w,numservicios,1,1,98,titulomenu,presservicios,teclaservicios,seract,NULL);
	liberav10timer(MITIMER);
	if (hay_tecla() && tecla()==ALT('M')) seract=-1;
}


// Se conecta a multiplexor: VDVISUSERV ORDENADOR PUERTO TIPO
// Se conecta directamente al servicio: VDVISUSERV ORDENADOR PUERTO TIPO DESSERVICIO
int main(int argc,char *argv[])
{
	int ret;
    strcpy(TITULOVENTANA, "VISUALIZA");
    initv10lib(v10hinst, v10hprev);
    trataparamstd(argc, argv, trataparammain, NULL, NULL);
    if (argc<4) final(("Uso visualiza ORDENADOR PUERTO  TIPO(P/L) (SERVICIO)"));
	if (argc==5) { // conectarse a un puerto en concreto sin multiplexar
		visudirecto(argv[1],argv[2],argv[4],0);
		return(0);
	}

	menuservicios(argv[1],argv[2]);
	while (1) {
		if (seract>=0) {
			cls(0,0,COLUMNASPANTALLA-1,LINEASPANTALLA-1,0);		
			ret=visudirecto(argv[1],*argv[2]=='L'?arrser[seract].puertolog:arrser[seract].puertopant,arrser[seract].codservicio,1);		  
			if (ret==tab) {
                while (1) {
				    seract++;
                    if (atoi(arrser[seract].puertopant)!=0) break;
    				if (seract>=numservicios-1) seract=0;
                }
	    		continue;
               
			}
			if (ret==stab) {
                while (1) {
				    seract--;
				    if (seract<0) seract=numservicios-1;
                    if (atoi(arrser[seract].puertopant)!=0) break;
                }
				continue;
			}
			if (ret==ALT('M')) menuservicios(argv[1],argv[2]);
			if (ret==ALT('T')) break;
		} else {
			seract=0;		
			menuservicios(argv[1],argv[2]);
		}
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
  COLUMNASPANTALLA = 140;
  LINEASPANTALLA = 60;  
  ret=main(__argc,__argv);
  return(ret);
}
#endif