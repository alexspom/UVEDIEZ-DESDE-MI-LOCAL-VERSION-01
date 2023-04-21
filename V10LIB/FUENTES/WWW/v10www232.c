/*
* Módulo :  V10www232.C
* Objeto:   Manejo de Puerto Serie en Web
* 
* 
* Autor	 : Francisco José Guerrero Sánchez
* Fecha  : 15-09-2007

* MODIFICACIONES
* ---------------------------
*/

#define INITPIPES 50000;


#define STCERRADO 	0
#define STPENDIENTE 	1
#define STABIERTO 	2

#define RECVIDDLE		0
#define RECVINI		1
#define RECVCMD		2
#define RECVCOMM		3
#define RECVDATA		4
#define RECVEND		5

#define CLIENTEOK 	0

typedef struct remoteport232 {
   int st;
   int velocidad;
	int paridad;
	int bits;
	int parada;
	int xon;
   char buffer[MAXCADENA];
   char buffersal[MAXCADENA];
   int nbufsal;
   int nbuf;
   int write;
   horas ultwrite;
   int bloqueo;
} remoteport232;


static remoteport232 port232[MAXPUERTOS];
static lwpipes2 *serverCOMM=NULL;
static int init232=-1;
static char portCOMM[6];

static int strecv=0,icom;
static char scom[3],data[MAXCADENA];
static int ncom=0,ndata=0;
static int inithebra=0;

// TCP

static int tcpCOMMOK(void) {
  if (serverCOMM && serverCOMM->status==STPIPEREADY) return 1;
   else return 0;
}

static int tcpCOMMopen(void) {
  if (tcpCOMMOK()) return 0;
  if (serverCOMM && serverCOMM->status==STPIPEROTA) {
     terminapipe2(serverCOMM);
     serverCOMM=NULL;
  }
  if (!serverCOMM) {
     serverCOMM=crealwpipe2serversock(portCOMM,4096);
     if (serverCOMM) {//(1)
       escribe_log(1,"Socket servidor COMM abierto\n");
      // Sleep(1000);
       return 0;
     }
     else {
       escribe_log(1,"No puedo abrir servidor COMM");
       return 1;
     }
  }
  return 0;
}

static void submit232(void)
{
  if (tcpCOMMOK())
    lwpipe2printf(serverCOMM,"<[S00,0]>");
  else
    escribe_log(1,"No puedo enviar SUBMIT");
}

static void tcpCOMMrecv(void) {
  char ch,cmd;
  int sescape=0;
  tcpCOMMopen();
  if (tcpCOMMOK()==0) return;
  while (haycarpipe2(serverCOMM)) {
    ch=(char)sigcarpipe2(serverCOMM);
    switch (strecv) {
      case RECVIDDLE:
                if (ch=='<') strecv=RECVINI;
                break;
      case RECVINI:
                if (ch=='[') {
                  strecv=RECVCMD;
                  ncom=0;
                } else
                  strecv=RECVIDDLE;
                break;

      case RECVCMD:
			      switch (ch) {
         			case 'D':  //<[0%2d,XXXXXXXXXXXXX...]>
                  case 'O':  //<[0%2d,X]>
                    cmd=ch;
                    strecv=RECVCOMM;
                    break;
                  default:
                    strecv=RECVIDDLE;
               }
               break;

      case RECVCOMM:
                if (ncom==2) {
                  if (ch==',') {
                    strecv=RECVDATA;
                    scom[ncom]=0;
                    icom=atoi(scom);
                    ndata=0;
                    memset(data,0,MAXCADENA);
                  } else
                    strecv=RECVIDDLE;
                } else
                  scom[ncom++]=ch;
                break;

      case RECVDATA:
                if (ch=='\\' && sescape==0) {
                  sescape=1;
                  break;
                }
                if (ch==']' && sescape==0) {
                  strecv=RECVEND;
                  break;
                }
                sescape=0;
                data[ndata++]=ch;
                break;

      case RECVEND:
                if (ch=='>') {
                  if (cmd=='D') {
                    memcpy(port232[icom].buffer+port232[icom].nbuf,data,ndata);
                    port232[icom].nbuf+=ndata;
                    escribe_log(1,"Recibo %s\n",data);
                    if (port232[icom].write==0) {
                      escribe_log(1,"Envio SUBMIT\n");
                      submit232();
                    }
                    port232[icom].write=0;
                  } else {
                    if (port232[icom].st==STPENDIENTE && cmd=='O') {
                      if (data[0]=='1') {
                          escribe_log(LOGPROGRESO,"ABRIENDO PUERTO COM%d",icom+1);
						  port232[icom].st=STABIERTO;
                      }
                      else  {
                         port232[icom].st=STCERRADO;
                         mensajefcm(10,"ERROR ABRIENDO PUERTO COM%d",icom+1);
                      }
                    }
                  }
                }
                strecv=RECVIDDLE;
                break;
    }
  }
}
// FIN TCP


int haypuerto232(void) {
  int i;
 // if (bloqueado232==1) return(0);
  if (init232!=CLIENTEOK) return(0);
  for (i=0;i<MAXPUERTOS;i++) {
    if (port232[i].st>STCERRADO) return(1);
  }
  return(0);
}


void webfin232(void)
{
  int i;
  for (i=0;i<MAXPUERTOS;i++) {
    if (port232[i].st>STCERRADO) webcierrapuerto232(i);
  }
  if (serverCOMM) {
    terminapipe2(serverCOMM);
    serverCOMM=NULL;
  }
}


int isinit232(void) {
  return init232;
}


int poninit232(int puerto,int ret) {
  if (init232==-1) {
    init232=ret;
    sprintf(portCOMM,"%d\0",puerto);
    serverCOMM=NULL;
    atexit(webfin232);
    return(1);
  }
  return(0);
}



int webinitpuerto232(int com,int velocidad,int paridad,int bits,int parada)
{
  if (init232!=CLIENTEOK) return(1);
//  mensajefcm(10,"Abro COMM");
  port232[com].velocidad=velocidad;
  port232[com].paridad=paridad;
  port232[com].bits=bits;
  port232[com].parada=parada;
  memset(port232[com].buffer,0,MAXCADENA);
  memset(port232[com].buffersal,0,MAXCADENA);
  port232[com].nbuf=0;
  port232[com].nbufsal=0;
  port232[com].write=0;
  port232[com].bloqueo=0;

  tcpCOMMopen();
  Sleep(500);
  if (tcpCOMMOK()) {
    port232[com].st=STPENDIENTE;
   // mensajefcm(10,"Envio inicio");
    lwpipe2printf(serverCOMM,"<[O%2d,%6d,%1d,%1d,%1d,%1d]>",
                             com,
                             port232[com].velocidad,
                             port232[com].paridad,
                             port232[com].bits,
                             port232[com].parada,
                             port232[com].xon);
  //  Sleep(1000);
    while (!haycarpipe2(serverCOMM)) esperamensaje(1);
    tcpCOMMrecv();
    return (port232[com].st==STABIERTO?0:1);
  }
  else
    escribe_log(1,"No puedo establecer comunicacion remota con puerto %d\n",com);
  return(0);
}



void webestado232(int puerto,long *velocidad,int *paridad,int *parada,int *datos)
{
  if (port232[puerto].st==STCERRADO) {
    *velocidad=-1;
	*paridad=-1;
	*parada=-1;
   *datos=-1;
	return;
  }
  if (velocidad) *velocidad=port232[puerto].velocidad;
  if (paridad) *paridad=port232[puerto].paridad;
  if (parada) *parada=port232[puerto].paridad;
  if (datos) *datos=port232[puerto].bits;
}

static void transformacadena(char *cadena,char *ret) {
  int i,index=0;
  memset(ret,0,MAXCADENA);
  for (i=0;i<strlen(cadena);i++) {
    if (cadena[i]=='\\') {
      ret[index++]='\\';
      ret[index++]='\\';
      continue;
    }
    if (cadena[i]==']') {
      ret[index++]='\\';
      ret[index++]=']';
      continue;
    }
    ret[index++]=cadena[i];
  }
}

static void hwrite232(void *param) {
  int i;
  do {
    Sleep(10);
    for (i=0;i<MAXPUERTOS;i++) {
      if (port232[i].st!=STABIERTO) continue;
      if (port232[i].bloqueo==1 || port232[i].nbufsal==0) continue;
      port232[i].bloqueo=1;
      if (llevocent()-port232[i].ultwrite>10 || port232[i].nbufsal>4096) {
          port232[i].buffersal[port232[i].nbufsal]=0;
          escribe_log(1,"Envío de RS232(%d): %s\n",i+1,port232[i].buffersal);
          lwpipe2printf(serverCOMM,"<[D%2d,%s]>",i,port232[i].buffersal);
          port232[i].write=1;
          port232[i].nbufsal=0;
          memset(port232[i].buffersal,0,MAXCADENA);
      }
      port232[i].bloqueo=0;
    }
  } while (1);
}

void webencolae(int com,int ch)
{
  char cadena[2];
  char datos[MAXCADENA];

//  if (bloqueado232==1) return;
  if (port232[com].st!=STABIERTO) return;
  tcpCOMMopen();
  if (tcpCOMMOK()) {
    if (inithebra==0) {
       inithebra=1;
       _beginthread(hwrite232,0,NULL);
    }

    cadena[0]=(char)ch;
    cadena[1]=0;
    transformacadena(cadena,datos);
    //port232[com].write=1;
    //lwpipeprintf(serverCOMM,"<[D%2d,%s]>",com,datos);
    while (port232[com].bloqueo!=0); // me espero
    port232[com].bloqueo=1;
    memcpy(port232[com].buffersal+port232[com].nbufsal,datos,strlen(datos));
    port232[com].nbufsal+=strlen(datos);
    port232[com].ultwrite=llevocent();
    port232[com].bloqueo=0;
  }
  else
    escribe_log(1,"No puedo establecer comunicacion remota con puerto %d\n",com);
}



void webencolaec(int com,char *cadena)
{
  char datos[MAXCADENA];

//  if (bloqueado232==1) return;
  if (port232[com].st!=STABIERTO) return;
  tcpCOMMopen();
  if (tcpCOMMOK()) {
    if (inithebra==0) {
       inithebra=1;
       _beginthread(hwrite232,0,NULL);
    }
    transformacadena(cadena,datos);
    //port232[com].write=1;
    //lwpipeprintf(serverCOMM,"<[D%2d,%s]>",com,datos);
    while (port232[com].bloqueo!=0); // me espero
    port232[com].bloqueo=1;
    memcpy(port232[com].buffersal+port232[com].nbufsal,datos,strlen(datos));
    port232[com].nbufsal+=strlen(datos);
    port232[com].ultwrite=llevocent();
    port232[com].bloqueo=0;
  }
  else
    escribe_log(1,"No puedo establecer comunicacion remota con puerto %d\n",com);
}



int webhaycar232(int com)
{
//  if (bloqueado232==1) return(0);
  if (port232[com].st!=STABIERTO) return(0);
  tcpCOMMrecv();
  if (tcpCOMMOK()==0) {
    escribe_log(1,"No puedo establecer comunicacion remota con puerto %d\n",com);
  }
  return port232[com].nbuf;
}


int websig_carr(int com)
{
  char ch,aux[MAXCADENA];

//  if (bloqueado232==1) return(-1);
  if (port232[com].st!=STABIERTO) return(-1);
  tcpCOMMrecv();
  if (tcpCOMMOK()==0) {
    escribe_log(1,"No puedo establecer comunicacion remota con puerto %d\n",com);
  }
  if (port232[com].nbuf>0) {
    ch=port232[com].buffer[0];
    port232[com].nbuf--;
    memcpy(aux,port232[com].buffer+1,port232[com].nbuf);
    memset(port232[com].buffer,0,MAXCADENA);
    memcpy(port232[com].buffer,aux,port232[com].nbuf);
    return(ch);
  } else
    return(-1);
}


void webpon232(int com,long velocidad,int paridad,int stop,int bits)
{
  if (port232[com].st!=STABIERTO) return;
  port232[com].velocidad=velocidad;
  port232[com].paridad=paridad;
  port232[com].parada=stop;
  port232[com].bits=bits;
  if (tcpCOMMOK()) {
    port232[com].st=STPENDIENTE;
    lwpipe2printf(serverCOMM,"<[R%2d,%6d,%1d,%1d,%1d,%1d]>",
                             com,
                             port232[com].velocidad,
                             port232[com].paridad,
                             port232[com].bits,
                             port232[com].parada,
                             port232[com].xon);
  }
  else
    escribe_log(1,"No puedo establecer comunicacion remota con puerto %d\n",com);
}


void webprintf232(int com,char *format,...)
{
  va_list arg;
  char *donde;
//  if (bloqueado232==1) return;
  if (port232[com].st!=STABIERTO) return;
  va_start(arg,format);
  donde=calloc(1,MAXCADENA);
  vsprintf(donde,format,arg);
  webencolaec(com,donde);
  free(donde);
  va_end(arg);
}

DWORD webescribebuffer232(int com,void *msg, int tam)
{
  DWORD escrito=0;
  int i;
  if (port232[com].st!=STABIERTO) return(0);
  for (i=0;i<tam;i++) 
    webencolae(com,((char *)msg)[i]);
  return(tam);
} 


void webprotocolo232(int com,int xon)
{
  if (port232[com].st!=STABIERTO) return;
  port232[com].xon=xon;
}

void webcierrapuerto232(int com) {
 if (tcpCOMMOK()) {
    lwpipe2printf(serverCOMM,"<[C%2d,0]>",com);
    port232[com].st=STCERRADO;
  }
  else
    escribe_log(1,"No puedo establecer comunicacion remota con puerto %d\n",com);
}

void bloqueo232(void) {
 if (init232) return;
 tcpCOMMopen();
 if (!tcpCOMMOK()) return;
/* if (antbloqueo232!=bloqueado232) {
   antbloqueo232=bloqueado232; */
   if (bloqueado232==1) {
    lwpipe2printf(serverCOMM,"<[L00,0]>");
   } else { 
    lwpipe2printf(serverCOMM,"<[U00,0]>");
   }
// }

}
