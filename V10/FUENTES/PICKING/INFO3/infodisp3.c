/*****************************************************************
*																 *
* Módulo:  Infodisp.c											 *
* Función: Manejo de tarjetas con líneas de displays			 *
*																 *	
*																 *
* Autor: Francisco J. Guerrero									 *
* Fecha: 29-1-2010												 *
*																 *		
******************************************************************/

#include "info3.h"

static windows wcom; 
static int initwcom;
void infotchecksum(infotreddisps *r,infotdisplays *d,infotdefdisps *df);
void infottratared(infotsios *t,int red);

infotdefdisps infotdef[]={{"Fuente de alimentacion", 0, 0, 0, 0, 0, {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
					{"Display 2-3-3-2",        2, 3, 3, 2, 9, {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                    {"Controlador",           12, 0, 4, 3,26, {0,2,4,6,8,10,1,3,5,7,9,11,0,0,0,0,0,0,0,0,0}},
					{"Controlador Grande",    12, 0, 4, 3,26, {0,2,1,3,4,6,5,7,8,10,9,11,0,0,0,0,0,0,0,0,}},
					{"Bombero",				   2, 3, 0, 0, 9, {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
					{"Display Botones+Luz",	   0, 0, 4, 3, 2, {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}};					

infotconfigs infotconfig={19934, //maxerror
                          120,   //Delaycab
                          10,    //Delaycar
                          1,     //Hardcheck
                          0,	 //tpulsa
                          0,	 //tsuelta
                          1000000,  // prepeat
                          50000000, //srepeat
                          50,       // tparpade
                          30,       //tparpada
                          25,       // espera
                          0,		// Hora del ultimo parpadeo 	
						  2000,		// espwho
						  100,		// espreset
						  100,     //espreset1
                          100,     //espreset2
                          1,        // Leer fichero de who
                          600,      // Ratio de errores
						  100,		// statsgap
                          0,        // acelera
						  0,		// showstats
						  0,
						  10,
						  50,
						  1000,
						{ NULL,
						 NULL,
						 NULL,
						 NULL,
						 NULL,
						 NULL,
						 NULL,
						 NULL,
						 NULL,
						 NULL,
						 NULL,
						 NULL,
						 NULL,
						 NULL,
						 NULL }  // 15 tarjetas (dir_IP+puerto)           
					};


void infotgrabaconfig(infotsios *t)
{
  int i;
  configurations conf;
  conf.reset_miliseconds_1=infotconfig.espreset1;
  conf.reset_miliseconds_2=infotconfig.espreset2;
  conf.delay_car=(short)infotconfig.delaycar;
  conf.delay_cab=(short)infotconfig.delaycab;
  v10log(LOGNORMAL, "Enviando nueva configuracion a tarjetas: %-5d %-5d %-4d %-4d\n",conf.reset_miliseconds_1,conf.reset_miliseconds_2,conf.delay_car,conf.delay_cab);
  for (i=0;i<t->numred;i++)
	infohsend(CONF,t->r+i,0,sizeof(configurations),(char *)&conf);
  // send_conf=0;
}


int *whohard;
static int leewho(int NINFO,int ntarj,int red)
{
  FILE *entrada;
  int nred=0,nelem=0,nt;
  char buffer[MAXCADENA],nombre[MAXPATH];
  for (nt=0;nt<ntarj;nt++) red+=infopick.t[nt]->numred;
//  red+=ntarj*REDESTARJ;
  sprintf(nombre,"infwho%02d.txt",NINFO);
  entrada=fopenpath(nombre,"r");
  if (entrada==NULL) return(-1);
  whohard=calloc(sizeof(int),MAXELEMRED);
  while (fgets(buffer,sizeof(buffer),entrada)) {
        if (es_blanco(buffer)) continue;
        if (*buffer=='#') continue;
        if (atoi(buffer)==-1) {
           nred++;
           continue;
         }
        if (nred>red) break; 
        if (nred<red) continue;
        whohard[nelem++]=atoi(buffer);
    }
  fclose(entrada);
  whohard[nelem]=-1;
  return(0);
}


static int calculared(int ninfo,int ntarj,infotsios *t,int red,int pdisp)
{
  int i,numdisp,numelem;
  int dirsal=0;
  int ndisp;
  infotreddisps *r=t->r+red;
  numdisp=0;
    
  if (infotconfig.fichwho) {
     if (leewho(ninfo,ntarj,red)==0) {
        for (i=0;i<MAXELEMRED;i++) {
			if (whohard[i]==-1) break;
               r->buffer_entrada[i]=(char)whohard[i];
         }
         r->buffer_entrada[i]=0xff;
     }
   }
   
   // nuevo
   if (whohard) free(whohard);

   for (i=0;i<MAXELEMRED;i++) {
      int disp=r->buffer_entrada[i];
      if (disp=='0') break;
	  if (disp==0xff) break;
      if (disp>TIPOSDISP)
          final(("Tipo de display desconocido %d\n",disp));
      //  v10log(LOGNORMAL,"     Identificado %d %d %s\n",i+1,disp,infotdef[disp].nombre);
      if (disp!=0) numdisp++;
   }
  
  numelem=i;
  v10log(LOGNORMAL,"  Total displays red %d\n",numdisp);
//  hay_tecla();
  r->numdisp=numdisp;
  r->long_buffer=0;
  if (numdisp) r->d=calloc(numdisp,sizeof(infotdisplays));
  r->t=t;
  r->udisp=-1;
  r->stats.received_frames=0;
  r->stats.sent_frames=0;
  r->stats.nbover=0;
  r->stats.error=0;
  r->stats.pending=0;
  r->numerror=0;
  r->toterror=0;
  r->hulterror=0;
  ndisp=0;
  for (i=0;i<numelem;i++) {
      int disp=r->buffer_entrada[i];
      infotdisplays *d;
      if (disp==0) continue;
      d=r->d+ndisp;
      d->tipo=infotdef+disp;
      d->dirent=i*BYTESPORDISP;
	  d->dirsal=dirsal;
      d->r=r;
      d->bot=calloc(d->tipo->botones,sizeof(infotbotones));
      dirsal+=d->tipo->bytes;
	  r->long_buffer=dirsal;
	  ndisp++;
    }
  pintatarj(ntarj,r,red);
  return 0;
}


infotsios *infotidentifica(int ninfo,IPsv4 IPv4,int redes,v10socks *pipe[],int *pdisp)
{
  infotsios *t;
  static int ntarj=0;
  int i;
  v10log(LOGNORMAL,"Identificando displays en tarjeta %s\n",IPv4);
  if (initwcom==0) {
     //initvn(&wcom,1,27,NUMERO_COLUMNAS-3,42,"DEFECTO");
     initvn(&wcom,1,2,COLUMNASPANTALLA-2,10,"DEFECTO");
	 enmarca(&wcom,0,"Comunicacion");
	 wcom.t.t[CINPUTINAC].papel=0xFF00;wcom.t.t[CINPUTINAC].tinta=0x00FF00;
	 wcom.t.t[CINPUTACT].papel=0xFFFF;wcom.t.t[CINPUTACT].tinta=0xFFFF;
	 wcom.t.t[CMARCA].papel=0x7F;wcom.t.t[CMARCA].tinta=0xffffff;
	 wcom.t.t[CMARCON].papel=0xfF;wcom.t.t[CMARCON].tinta=0xffffff;
     initwcom=1;
  }
  //if (infopick.numcards<=2)
  //	wcom.cy=ntarj*2;
  //else
  	wcom.cursory=ntarj*2;	
  wcom.cursorx=0;
  poncolorv(&wcom,CNORMAL);
  v10printf(&wcom,"%s",IPv4);
  t=calloc(1,sizeof(infotsios));
  if (IPv4) t->dir_IP=strdup(IPv4);
	else t->dir_IP=NULL;
  
  t->tec=calloc(INFOTMAXTECLAS,sizeof(infotteclas));
  t->numteclas=0;
  t->numred=redes; 
  for (i=0;i<redes;i++) {
	  t->r[i].pipe=pipe[i];
	  t->r[i].t=t;
  }
  
  infotstop(t);
  infotgrabaconfig(t);
  infotreset(t);
  
  if (infotconfig.fichwho==0) 
      infotwho(t);
    
  for (i=0;i<t->numred;i++) {
	calculared(ninfo,ntarj,t,i,*pdisp);
	(*pdisp)+=t->r[i].numdisp;
  }

  infotstop(t);
  infotresetstats(t);
  infotlimpia(t);
  infotstart(t);
  ntarj++;
  return(t);
}


static void infotliberared(infotsios *t,int red)
{
  int i;
  infotreddisps *r=t->r+red;
  for (i=0;i<r->numdisp;i++) {
      infotdisplays *d=r->d+i;
      free(d->bot);
    }
  if (r->pipe) v10socklibera(r->pipe);
  if (r->d) free(r->d);
}


void infotlibera(infotsios *t)
{
  int i;
  if (t==NULL) return;
  infotstop(t);
  infotreset(t);
  if (t->dir_IP) free(t->dir_IP);
  for (i=0;i<t->numred;i++)
	infotliberared(t,i);
  free(t->tec);
  free(t);
}


static void printan16(char *donde,int dir,int ch)
{
  donde[dir+1]=(char)(infotan16[ch]>>8);
  donde[dir]=(char)(infotan16[ch]&0xff);
}


static int verificadisplay(infotsios *t,int red,int disp)
{
  infotreddisps *r;
  if (t==NULL) final(("Tarjeta no inicializada"));
  if (red<0 || red>t->numred-1) {
	  v10log(LOGERROR,"Numero de red erroneo red %d\n",red);
	  return(-1);
  }
  r=t->r+red;
  if (disp<0 || disp>=r->numdisp) {
	  v10log(LOGERROR,"display demasiado alto red %d display %d\n",red,disp);
	  return(-1);
  }
  return(0);
}


void infotinicializa(infotsios *t,int red,int disp)
{
  infotreddisps *r;
  infotdisplays *d;
  infotdefdisps *df;
  if (verificadisplay(t,red,disp)) return;
  r=t->r+red;
  d=r->d+disp;
  df=d->tipo;
  infotchecksum(r,d,df);
  infohsend(MOD_DISP,t->r+red,d->dirsal,df->bytes,t->r[red].buffer_salida+d->dirsal);
}

void infotimprime(infotsios *t,int red,int disp,char *cad)
{
  int i;
  infotreddisps *r;
  infotdisplays *d;
  infotdefdisps *df;
  char cadena[MAXDIGDISPLAY];
  if (verificadisplay(t,red,disp)) return;
  r=t->r+red;
  d=r->d+disp;
  df=d->tipo;
  strcopia(cadena,cad,df->digitosa+df->digitosn);
  pad(cadena,df->digitosa+df->digitosn);
  strcpy(d->valor,cadena);
  for (i=0;i<df->digitosa;i++) {
      int dir;
	  dir=d->dirsal+(df->baile[i]*2);
      printan16(t->r[red].buffer_salida,dir,cadena[i]);
    }
  for (i=df->digitosa;i<df->digitosa+df->digitosn;i++) {
        t->r[red].buffer_salida[d->dirsal+i+df->digitosa]=(char)infotascii8[cadena[i]];
    }
  
  infotchecksum(r,d,df);
  infohsend(MOD_DISP,t->r+red,d->dirsal,df->bytes,t->r[red].buffer_salida+d->dirsal);
}


void infotvprintf(infotsios *t,int red,int disp,char *format,va_list arg)
{
  char cadena[MAXCADENA];
  vsprintf(cadena,format,arg);
  infotimprime(t,red,disp,cadena);
}


void infotprintf(infotsios *t,int red,int disp,char *format,...)
{
  va_list arg;
  va_start(arg,format);
  infotvprintf(t,red,disp,format,arg);
  va_end(arg);
}


static void infotchecksum(infotreddisps *r,infotdisplays *d,infotdefdisps *df)
{
  int i;
 if (df==(infotdefdisps *)(infotdef+5)) {
	r->buffer_salida[d->dirsal+df->bytes-1]=(char)(255-r->buffer_salida[d->dirsal]);
  } else {
	r->buffer_salida[d->dirsal+df->bytes-1]=0;
	for (i=0;i<df->bytes-1;i++)
		r->buffer_salida[d->dirsal+df->bytes-1]+=(char)(r->buffer_salida[d->dirsal+i]);
  }
}


void infotponluz( infotsios *t,int red,int disp,int numluz,int valor)
{
  infotreddisps *r;
  infotdisplays *d;
  infotdefdisps *df;
  int dir;
  int bits;
  int antval;
  if (verificadisplay(t,red,disp)) return;
  r=t->r+red;
  d=r->d+disp;
  df=d->tipo;
  if (numluz<0 || numluz>=df->luces) return;
  dir=d->dirsal+df->bytes-2;
  bits=(1<<numluz)|((1<<numluz)<<4);
  antval=t->r[red].buffer_salida[dir];
  t->r[red].buffer_salida[dir]&=(char)~bits;
  if ((valor&2)==0)  bits=1<<numluz;
  if (valor) t->r[red].buffer_salida[dir]|=(char)bits;
  if (antval==t->r[red].buffer_salida[dir]) return;
  infotchecksum(r,d,df);
  infohsend(MOD_DISP,t->r+red,dir,2,t->r[red].buffer_salida+dir);
}


int infotstluz(infotsios *t,int red,int disp,int numluz)
{
  infotreddisps *r;
  infotdisplays *d;
  infotdefdisps *df;
  int dir;
  int bits;
  if (verificadisplay(t,red,disp)) return(0);
  r=t->r+red;
  d=r->d+disp;
  df=d->tipo;
  if (numluz<0 || numluz>=df->luces) return(0);
  dir=d->dirsal+df->bytes-2;
  bits=((t->r[red].buffer_salida[dir]>>numluz)&1)+2*(((t->r[red].buffer_salida[dir]>>numluz)>>4)&1);
  return(bits);
}


void infottoggleluz( infotsios *t,int red,int disp,int numluz,int valor,char *cadena,int parpadea)
{
  infotreddisps *r;
  infotdisplays *d;
  infotdefdisps *df;
  int dir;
  if (verificadisplay(t,red,disp)) return;
  r=t->r+red;
  d=r->d+disp;
  df=d->tipo;
  if (numluz<0 || numluz>=df->luces) return;
  dir=d->dirsal+df->bytes-2;
  if (valor<10) {
     if (valor==0) t->r[red].buffer_salida[dir]|=(char)(1<<numluz);
        else       t->r[red].buffer_salida[dir]&=(char)(~(1<<numluz));
   }
  infotchecksum(r,d,df);
  if (cadena) {
     if (valor==10) {
   	  dir+=256;
	     memcpy(cadena+(4*parpadea),&dir,2);
   	  dir-=256;
	     memcpy(cadena+(4*parpadea)+2,t->r[red].buffer_salida+dir,2);
      }	  
  }
  else 
	  infohsend(MOD_DISP,t->r+red,dir,2,t->r[red].buffer_salida+dir);
}


char *infotvalor(infotsios *t,int red,int disp)
{
  infotreddisps *r;
  infotdisplays *d;
  if (verificadisplay(t,red,disp)) return("");
  r=t->r+red;
  d=r->d+disp;
  return(d->valor);
}


int valorentdisp(infotsios *t,int red,int disp)
{
  infotreddisps *r;
  static int valor,check;
  verificadisplay(t,red,disp);
  r=t->r+red;
  valor=t->r[red].buffer_entrada[r->d[disp].dirent];
  check=t->r[red].buffer_entrada[r->d[disp].dirent+1];
  if (((~valor)&0xff)!=check) {
     valor=0;
   }
  return(valor);
}


int infotstatus(int ntarj,int red,infotreddisps *r) 
{
  int nd,valor;
  valor=0;
  for (nd=0;nd<r->numdisp;nd++)
	valor|=valorentdisp(infopick.t[ntarj],red,nd);
  return(valor);
}


int infotstdisplay(infotsios *t,int red,int disp)
{
  if (verificadisplay(t,red,disp)) return(0);
  return(valorentdisp(t,red,disp));
}


static int infotnextboton(infotsios *t,int red,int *valor)
{
  int st;
  int ndisp;
  infotreddisps *r;
  int ntarj;
  if (t==NULL) final(("Tarjeta no inicializada"));
  if (red<0 || red>t->numred-1) final(("Numero de red erroneo"));
  r=t->r+red;
  if (r->numdisp==0) return(r->udisp);
  ntarj=buscatarj(t);
  ndisp=(r->udisp+1)%r->numdisp;
  pintatarj(ntarj,r,red);
  
  st=0;
  while (ndisp!=r->udisp) {
  	  st=valorentdisp(t,red,ndisp);
	  if ((st&COMCORR)==0) {
	  } else {
		if (st&0xf) {
			r->udisp=ndisp;
            break;
        }
	  }
	  ndisp++;
	  if (ndisp==r->numdisp) {
		if (r->udisp==-1) break;
		ndisp=0;
	  }
  }
  if (r->udisp!=-1) {	
	  if ((st&0xf)==0) {
	  	  r->udisp=-1;
      } else {
	  	  if (valor) *valor=st;
	  }
  }
  return(r->udisp);
}


void infotencolatecla(infotsios *t,int red,int disp,int boton,int causa)
{
  if (t->numteclas>=INFOTMAXTECLAS) return;
  t->tec[t->numteclas].linea=red;
  t->tec[t->numteclas].disp=disp;
  t->tec[t->numteclas].boton=boton;
  t->tec[t->numteclas].causa=causa;
  t->numteclas++;
}


void infottratateclas(infotsios *t)
{
  int i;
  if (t==NULL) final(("Tarjeta no inicializada"));
  for (i=0;i<t->numred;i++)
	  if (t->r[i].numdisp!=0) break;
  if (i==t->numred) return;
  for (i=0;i<t->numred;i++)
	if (t->r[i].numdisp) infottratared(t,i);
}


int infothaytecla(infotsios *t)
{
  return(t->numteclas);
}


int infottecla(infotsios *t,infotteclas *donde)
{
  if (!infothaytecla(t)) return(0);
  *donde=t->tec[0];
  memcpy(t->tec,t->tec+1,(INFOTMAXTECLAS-t->numteclas)*sizeof(infotteclas));
  t->numteclas--;
  return(1);
}


static void estadoboton(infotbotones *b,int estado)
{
  b->estado=estado;
  b->horaestado=damecent();
}


static void infottratadisplay(infotsios *t,int red,int disp,int st)
{
  infotreddisps *r=t->r+red;
  int nb;
  infotdisplays *d;
  d=r->d+disp;
  if ((st&COMCORR)==0) return;
  for (nb=0;nb<d->tipo->botones;nb++) {
      infotbotones *b=d->bot+nb;
      if (st&(1<<nb)) {
         switch (b->estado) {
                case INFOTBNOPULSADO:estadoboton(b,INFOTBPULSANDO);
                                  //  break;
                case INFOTBPULSANDO:if (damecent()-b->horaestado<infotconfig.tpulsa) break;
									estadoboton(b,INFOTBPULSADO);
                                    b->hurepeat=damecent();
                                    b->numrep=0;
                                    infotencolatecla(t,red,disp,nb,INFOCPRIMERA);
                                    break;
                case INFOTBPULSADO:if (d->tipo==infotdef+2) break;
                                   if (nb==2) break;
                                   if (infotconfig.prepeat) {
                                      if (b->numrep && damecent()-b->hurepeat>=(b->sigrepeat<0?0:b->sigrepeat/100)) {
                                         v10horas i=-b->sigrepeat;
                                         do {
                                            infotencolatecla(t,red,disp,nb,INFOCREPEAT);
                                          } while (--i>=0);
                                         b->numrep++;
                                         b->hurepeat=damecent();
                                         if (infotconfig.acelera) {
                                            if (b->sigrepeat==0) b->sigrepeat=-1;
                                            if (b->sigrepeat>=0) b->sigrepeat=((b->sigrepeat-1)*100)/103;
                                               else              b->sigrepeat=((b->sigrepeat)*103)/100;
                                          }
                                       }
                                      if (b->numrep==0 && damecent()-b->horaestado>infotconfig.prepeat) {
                                         infotencolatecla(t,red,disp,nb,INFOCREPEAT);
                                         b->sigrepeat=infotconfig.srepeat*100;
                                         b->numrep++;
                                         b->hurepeat=damecent();
                                       }
                                    }
                                   break;
                case INFOTBSOLTANDO:estadoboton(b,INFOTBPULSADO);
                                    break;
                default           :estadoboton(b,INFOTBPULSANDO);
                                   break;
          }
       } else {
         switch (b->estado) {
                case INFOTBPULSANDO:estadoboton(b,INFOTBNOPULSADO);
                                    break;
                case INFOTBPULSADO:estadoboton(b,INFOTBSOLTANDO);
                                   break;
                case INFOTBSOLTANDO:if (damecent()-b->horaestado<infotconfig.tsuelta) break;
                                    estadoboton(b,INFOTBNOPULSADO);
                                    break;
                case INFOTBNOPULSADO:break;
                default           :estadoboton(b,INFOTBSOLTANDO);
                                   break;
          }
       }
     }
}


static void infotverificabotones(infotsios *t,int red)
{
  infotreddisps *r=t->r+red;
  int nd;
  for (nd=0;nd<r->numdisp;nd++) {
      int st,nb;
      infotdisplays *d=r->d+nd;
      for (nb=0;nb<d->tipo->botones;nb++) 
		  if (d->bot[nb].estado!=INFOTBNOPULSADO) break;
      if (nb==d->tipo->botones) continue;
      st=infotstdisplay(t,red,nd);
      infottratadisplay(t,red,nd,st);
   }
}


static void infottratared(infotsios *t,int red)
{
  int disp=0,pdisp=-1;
  infotreddisps *r;
  if (red<0 || red>t->numred-1) final(("Numero de red erroneo"));
  r=t->r+red;
  if (r->numdisp==0) return;
  if (damecent()-r->ultimo_tcpip>infotconfig.queue_timeout) envia_tcpip(r);
  infotverificabotones(t,red);
  while (pdisp!=disp) {
        int st;
        disp=infotnextboton(t,red,&st);
        if (disp==-1) return;
        if (pdisp==-1) pdisp=disp;
        infottratadisplay(t,red,disp,st);
     }
}

void infotTCPIP(infotsios *t,infotreddisps *r,int red)
{
	v10horas inicio_quantum,fin_quantum;

	//if (r->numdisp<=0) return;
	recupera_conexion(r);
	if (v10socklisto(r->pipe)==0) return;
	inicio_quantum=damecent();
	if (v10sockhaycar(r->pipe)) {
		while (v10sockhaycar(r->pipe)) {	
			if (infohreceive(t,r,red)==RESP_DISP) 
				return;
			fin_quantum=damecent();
			if (fin_quantum-inicio_quantum>infotconfig.quantum) return;
		}
    } else {
      if (r->stats_pend>0 && damecent()-r->stats_pend>infotconfig.watchdog) {
		  watchdog(r);
		  v10socklibera(r->pipe);
		  r->pipe=NULL;
	    }
    }
}


static void infottrataerror(infotreddisps *r,int red,unsigned long numerror)
{ 
  infohstop(r);
  v10log(LOGNORMAL,"Error grave: Tratando error %ld en la red %d de la tarjeta %s\n",numerror,red,r->t->dir_IP);
  infohreset(r);
  if (r->numdisp) infohsend(MOD_DISP,r,0,r->long_buffer,r->buffer_salida);
  infohstart(r);
  
}


void pintatarj(int nt, infotreddisps *r,int red)
{
  int valor,err;
  wcom.cursorx=14+((red%4)*35);
  wcom.cursory=nt*2+(red/4);
  if (r->numerror!=0) {
		if (r->numerror>infotconfig.maxerror) {
			infottrataerror(r,red,r->toterror);
			err=0;
		} else {
			if (r->numerror>infotconfig.maxerror/2) err=2;
			else err=1;
		} 
  } else err=0;

  if (r->pipe==NULL || v10socklisto(r->pipe)==0) err=3;
  poncolorv(&wcom,CNORMAL);
  v10printf(&wcom,"%c.",'A'+red);

  switch (err) {
    case 0:  poncolorv(&wcom,CINPUTINAC);
             break;
    case 1:  poncolorv(&wcom,CINPUTACT);
             break;
    case 2:  poncolorv(&wcom,CMARCA);
             break;
    case 3:  poncolorv(&wcom,CMARCON);
             break;
  }
    
  if (err!=-1) v10printf(&wcom,"%c",' ');
  else wcom.cursorx++;
  poncolorv(&wcom,CNORMAL);
  valor=infopick.t[nt]?infotstatus(nt,red,r):0;
  v10printf(&wcom,"%4d/%4d %8d-%5d-",r->numdisp,r->numdispreal,r->stats.sent_frames,r->toterror);
  if (valor!=0x00 && valor!=0x30) poncolorv(&wcom,CMARCA);		
  v10printf(&wcom,"%02x",valor);	
  poncolorv(&wcom,CNORMAL);
}


int buscatarj(infotsios *t)
{
  int ret;
  for (ret=0;ret<MAXTARJ;ret++) {
      if (infopick.t[ret]==t) return(ret);
  }
  return(ret);
}


void infotstart(infotsios *t)
{
 int i;
 for (i=0;i<t->numred;i++)
	 infohstart(t->r+i);
}


void infotstop(infotsios *t)
{
 int i;
 for (i=0;i<t->numred;i++)
	 infohstop(t->r+i);
}


void infotwho(infotsios *t)
{
 int i;
 Sleep(infotconfig.espreset1+infotconfig.espreset2+1000);
 for (i=0;i<t->numred;i++)
	 infohwho(t->r+i);	 
 Sleep(infotconfig.espwho); 
 for (i=0;i<t->numred;i++) {
	 infohsend(DAM_EST,t->r+i,0,MAX_BUFFER_REC,NULL);
	 infohreceive(t,t->r+i,i);		
 }
}


void infotreset(infotsios *t)
{
 int i;
 for (i=0;i<t->numred;i++) 
	 infohreset(t->r+i);
}


void infotresetn(int max_tarjetas) 
{
 int i;
 for (i=0;i<max_tarjetas;i++)
	 infotreset(infopick.t[i]);
}


void infotlongbuffer(infotsios *t) 
{
 int i;
 for (i=0;i<t->numred;i++)
	infohlongbuffer(t->r+i,0,0);
}


void infotlimpia(infotsios *t)
{
 int i;
 for (i=0;i<t->numred;i++)
	infohlimpia(t->r+i);
}


void infotresetstats(infotsios *t)
{
	int i;
	for (i=0;i<t->numred;i++)
		infohresetstats(t->r+i);
}


void infotreseterror(infotsios *t)
{
	int i;
	for (i=0;i<t->numred;i++)
		infohreseterror(t->r+i);
}


void tratastats(infotsios *t,infotreddisps *r,int red)
{
	if (damecent()-r->hulterror>infotconfig.ratioerr) r->numerror=0;
	pintatarj(buscatarj(t),r,red);
	if (infotconfig.showstats) 
		v10log(LOGNORMAL,"Estadísticas: %-15s-%2d-%9ld-%9ld-%2ld-%4ld\n",t->dir_IP,red,r->stats.sent_frames,r->stats.received_frames,/*,r->stats.pending,r->stats.error,r->stats.nbover,*/r->numerror,r->toterror);
}

