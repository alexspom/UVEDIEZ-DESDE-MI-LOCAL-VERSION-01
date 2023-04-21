/*
* Módulo : V10SOCK.C
* Objeto:  Manejo de sockets tcp/ip
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"



static void cierrasocket(SOCKET soc)
{
    shutdown(soc,2);
    closesocket(soc);
}

static void anadealista(listasocks **raiz,listasocks *nuevo)
{
    if (*raiz==NULL) {
        *raiz=nuevo;
        nuevo->next=nuevo;
        nuevo->prev=nuevo;
    } else {
        nuevo->prev=(*raiz)->prev;
        (*raiz)->prev=nuevo;
        nuevo->prev->next=nuevo;
        nuevo->next=*raiz;
    }
}

static void eliminadelista(listasocks **raiz,listasocks *nuevo)
{
    if (*raiz==nuevo) {
        if (nuevo->next==nuevo) *raiz=NULL;
        else {
            *raiz=nuevo->next;
            (*raiz)->prev=nuevo->prev;
            nuevo->prev->next=*raiz;
        }
    } else {
        nuevo->prev->next=nuevo->next;
        nuevo->next->prev=nuevo->prev;
    }
}


static void initsocket(void)
{
#ifndef __LINUX__
  static int init;
  WSADATA ws;
  if (init!=0) return;
  init=1;
  WSAStartup(0x0002,&ws);
#endif
}

static int getipcport(char *service,char *protocol,short *port)
{
  int ret;
  struct servent   *pse;
  hay_tecla();
  pse=getservbyname(service,protocol);
  if (pse==NULL) {
     ret=WSAGetLastError();
     return(ret);
   }
  *port=pse->s_port;
  return(0);
}

static SOCKET damesocserver(char *servicio,char *protocolo,int *miport)
{
    SOCKET soc;
    struct sockaddr_in sin;
    int err;
	int reuse = 1;
    short port;
    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr=INADDR_ANY;
    if (atoi(servicio)==0) {
       err=getipcport(servicio,protocolo,&port);
       if (err) {
          v10log(LOGERROR,"Buscando port %s error %d\n",servicio,err);
          return(INVALID_SOCKET);
       }
    } else port=htons((short)atoi(servicio));
    sin.sin_port=port;
    if (miport) *miport=port;
    soc=socket(AF_INET,SOCK_STREAM,0);
	setsockopt(soc,SOL_SOCKET,SO_REUSEADDR,(const char*)&reuse,sizeof(reuse));
#ifdef __LINUX__
	setsockopt(soc, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse));
#endif
    err=bind(soc,(struct sockaddr*)&sin,sizeof(sin));
    if (err) {
       v10log(LOGERROR,"Haciendo bind en puerto %d error %d\n",port,err);
       closesocket(soc);
       return(INVALID_SOCKET);
    }
    err=listen(soc,50);
    if (err) {
       v10log(LOGERROR,"En listen error %d\n",err);
       closesocket(soc);
       return(INVALID_SOCKET);
    }
    return(soc);
}

static void rompesock(v10socks *p)
{
    if (p==NULL) return;
    if (p->soc!=INVALID_SOCKET) {
        cierrasocket(p->soc);
        p->soc=INVALID_SOCKET;
        p->status=STSOCKROTA;
        if (p->fnbreak) p->fnbreak(p,SOCKBREAK,0,NULL);
    }
}

static void reintentapipe(v10socks *p)
{
    struct sockaddr_in sin;
    memcpy(&sin,&p->destino,sizeof(struct sockaddr));
    p->soc=socket(AF_INET,SOCK_STREAM,0);
    if (connect(p->soc,(struct sockaddr *)&sin,sizeof(sin))==0) {
	    v10log(LOGDEBUG, "%s", "Conectado\n");
        if (p->numrecon==0 && p->fnopen) p->fnopen(p,SOCKOPEN,0,NULL);
        if (p->fnreconecta) p->fnreconecta(p,SOCKOPEN,0,NULL);
        p->numrecon++;
        p->nrec=0;
        p->status=STSOCKREADY;
    }  else {
        closesocket(p->soc);
        Sleep(10);
    }
}

static void tratav10sock(v10socks *p)
{
    fd_set reading;
    int num;
    unsigned long lon;
    int ret;
    int encrit=0;
    struct timeval timeout;
    while (p->status!=STSOCKROTA || p->reconecta) {
        if (p->status==STSOCKREADY) {
            FD_ZERO(&reading);
            FD_SET(p->soc,&reading);
            timeout.tv_sec=0;timeout.tv_usec=10000;
            if (encrit) {
                LeaveCriticalSection(&p->critsock);
                encrit=0;
            }
            num=select(p->soc+1,&reading,NULL,NULL,&timeout);
            if (num==0) continue;
            EnterCriticalSection(&p->critsock);
            encrit=1;
            ret=ioctlsocket(p->soc,FIONREAD,&lon);
            if (ret==SOCKET_ERROR || lon==0) {
                rompesock(p);
            } else {
                if (p->nrec>=p->tamrec) {
                    if (encrit) LeaveCriticalSection(&p->critsock);
                    v10log(LOGDEBUG,"SOCKET: Suspendida thread %p Recibidos %d tamano %d\n",p->threadtrata,p->nrec,p->tamrec);
                    p->suspendida=1;
                    SuspendThread(p->threadtrata);
                    p->suspendida=0;
                    v10log(LOGDEBUG,"SOCKET: Activada thread %p Recibidos %d tamaño %d\n",p->threadtrata,p->nrec,p->tamrec);
                    if (encrit) EnterCriticalSection(&p->critsock);
                }
                lon=p->tamrec-p->nrec;
                ret=recv(p->soc,p->bufrec+(p->nrec),lon,0);
                if (ret==SOCKET_ERROR) {
                    rompesock(p);
                } else {
                    if (p->fnread) {
                        p->fnread(p,SOCKREAD,ret,p->bufrec);
                    } else {
                        p->nrec+=ret;
                    }
                }
            }
        }
        if (p->status==STSOCKCONCLSOCK ||(p->status==STSOCKROTA && p->reconecta)) {
            p->status=STSOCKCONCLSOCK;
            if (encrit) {
                LeaveCriticalSection(&p->critsock);
            }
            reintentapipe(p);
            EnterCriticalSection(&p->critsock);
            encrit=1;

        }
    }
    if (p->soc!=INVALID_SOCKET) {
        cierrasocket(p->soc);
        p->soc=INVALID_SOCKET;
    }
    if (encrit) LeaveCriticalSection(&p->critsock);
    if (p->fnclose) p->fnclose(p,SOCKCLOSE,0,NULL);
    p->threadtrata=NULL;
}

static void trataclosecliente(v10socks *p,int op,int lon,char *buffer)
{
    servidorsocks *padre=p->servidor;
    listasocks *l;
    EnterCriticalSection(&padre->critopen);
    l=padre->listaopen;
    while (l) {
        if (l->valor==p) {
            eliminadelista(&padre->listaopen,l);
            free(l);
            padre->nconopen--;
	        v10log(LOGDEBUG, "%s", "Desconectado cliente\n");
            break;
        }
        if (l->next==padre->listaopen) break;
        l=l->next;
    }
    LeaveCriticalSection(&padre->critopen);
    if (padre->fnclose) padre->fnclose(p,op,lon,buffer);
}

static v10socks *creav10sock(int tamrec,trigsocks fnopen,trigsocks fnreconecta,trigsocks fnread,trigsocks fnbreak,
                           trigsocks fnclose)
{
    v10socks *ret;
    ret=calloc(1,sizeof(v10socks));
    ret->tamrec=tamrec;
    ret->bufrec=calloc(1,tamrec);
    ret->fnopen=fnopen;
    ret->fnreconecta=fnreconecta;
    ret->fnread=fnread;
    ret->fnbreak=fnbreak;
    ret->fnclose=fnclose;
    InitializeCriticalSection(&ret->critsock);
    return(ret);
}

static void trataopen(servidorsocks *nuevo)
{
    SOCKET nsock;
    int len;
    struct sockaddr origen;
    listasocks *l;
    char cadorigen[MAXPATH];
    while (nuevo->status!=STSOCKSERROMPE) {
          len=sizeof(origen);
          nsock=accept(nuevo->soc,&origen,&len);
          if (nsock==INVALID_SOCKET) continue;
          EnterCriticalSection(&nuevo->critopen);
          l=calloc(1,sizeof(listasocks));
          l->valor=creav10sock(nuevo->tamrec,nuevo->fnopen,nuevo->fnreconecta,nuevo->fnread,nuevo->fnbreak,nuevo->fnclose);
          memcpy(&l->valor->origen,&origen,sizeof(origen));
          len=sizeof(struct sockaddr);
          getsockname(nsock,&l->valor->destino,&len);
          l->valor->soc=nsock;
          l->valor->status=STSOCKREADY;
          l->valor->reconecta=0;
          l->valor->servidor=nuevo;
          if (nuevo->fnopen) nuevo->fnopen(l->valor,SOCKOPEN,0,NULL);
          if (nuevo->conservar==0) {
              anadealista(&nuevo->listapend,l);
              nuevo->nconpend++;
          } else {
              anadealista(&nuevo->listaopen,l);
              nuevo->nconopen++;
              l->valor->fnclose=trataclosecliente;
          }
          l->valor->threadtrata=CreateThread(NULL,10000,(void *)tratav10sock,(void *)l->valor,0,NULL);
          LeaveCriticalSection(&nuevo->critopen);
          v10log(LOGDEBUG,"Conectado cliente %s pendientes %d abiertos %d\n",v10sockpintaorigen(l->valor,cadorigen),nuevo->nconpend,nuevo->nconopen);
    }
    nuevo->threadopen=NULL;
    if (nuevo->soc!=INVALID_SOCKET) {
        closesocket(nuevo->soc);
        nuevo->soc=INVALID_SOCKET;
    }
}

servidorsocks *v10socknuevoservidor(char *servicio,int conservar,trigsocks fnopen,trigsocks fnreconecta,trigsocks fnread,
                             trigsocks fnbreak,trigsocks fnclose)
{
    servidorsocks *nuevo;
    initsocket();
    nuevo=calloc(1,sizeof(servidorsocks));
    nuevo->soc=damesocserver(servicio,"tcp",&nuevo->port);
    if (nuevo->soc!=INVALID_SOCKET) {
        InitializeCriticalSection(&nuevo->critopen);
        nuevo->conservar=conservar;
        nuevo->fnopen=fnopen;
        nuevo->fnreconecta=fnreconecta;
        nuevo->fnread=fnread;
        nuevo->fnbreak=fnbreak;
        nuevo->fnclose=fnclose;
        nuevo->tamrec=TAMRECSERVER;
	    nuevo->threadopen = CreateThread(NULL, 10000, (void *)trataopen, (void *)nuevo, 0, NULL);
    } else {
        free(nuevo);
        nuevo=NULL;
    }
    return(nuevo);
}

v10socks *v10sockdameconexion(servidorsocks *ns)
{
    v10socks *ret;
    if (ns->nconpend>0) {
        if (ns->listapend) {
            EnterCriticalSection(&ns->critopen);
            ret=ns->listapend->valor;
            eliminadelista(&ns->listapend,ns->listapend);
            ns->nconpend--;
            LeaveCriticalSection(&ns->critopen);
            return(ret);
        }
    }
    return(NULL);
}

static int gethostaddres(char *host,struct sockaddr_in *sin)
{
  int ret;
  struct hostent   *phe;
  hay_tecla();
  phe=gethostbyname(host);
  if (phe==NULL) {
     ret=WSAGetLastError();
     return(ret);
   }
  memcpy(&sin->sin_addr,*phe->h_addr_list,phe->h_length);
  return(0);
}

v10socks *v10socknuevocliente(char *host,char *service,int reconecta,int tamrec,trigsocks fnopen,trigsocks fnreconecta,
                       trigsocks fnread,trigsocks fnbreak,trigsocks fnclose)
{
    v10socks *ret;
    struct sockaddr_in sin;
    short port=0;
    initsocket();
    v10log(LOGNORMAL,"Conectando con %s servicio %s protocolo tcp\n",host,service);
    sin.sin_family=AF_INET;
    if (gethostaddres(host,&sin)==0) {
       v10log(LOGNORMAL,"Encontrado host %s\n",inet_ntoa(sin.sin_addr));
       if (atoi(service)==0) getipcport(service,"tcp",&port);
       else                  port=htons((short)atoi(service));
       if (port!=0) {
          v10log(LOGNORMAL,"Encontrado servicio %d\n",ntohs(port));
          sin.sin_port=port;
          hay_tecla();
          ret=creav10sock(tamrec,fnopen,fnreconecta,fnread,fnbreak,fnclose);
          ret->reconecta=reconecta;
          ret->port=port;
          memcpy(&ret->destino,&sin,sizeof(ret->destino));
          ret->status=STSOCKCONCLSOCK;
	       ret->threadtrata = CreateThread(NULL, 10000, (void *)tratav10sock, (void *)ret, 0, NULL);
          return(ret);
       } else
         v10log(LOGERROR,"NO ENCONTRADO servicio %d\n",ntohs(port));
    }  else
       v10log(LOGERROR,"NO ENCONTRADO host %s\n",inet_ntoa(sin.sin_addr));
   return(NULL);
}

static void liberalista(listasocks **head,void (*funlibera)(v10socks *p))
{
    listasocks *p;
    p=*head;
    while (p) {
        listasocks *aux=p->next;
        funlibera(p->valor);
        eliminadelista(head,p);
        free(p);
        if (*head==NULL) break;
        p=aux;
    }
}

void v10socklibera(v10socks *p)
{
    int i;
    p->reconecta=0;
    p->status=STSOCKROTA;
    if (p->soc!=INVALID_SOCKET) {
        cierrasocket(p->soc);
        p->soc=INVALID_SOCKET;
    }
    for (i=0;i<NUMREINTCIERRA;i++) {
        if (p->threadtrata==NULL) break;
        Sleep(1);
    }
    EnterCriticalSection(&p->critsock);
    if (p->threadtrata) TerminateThread(p->threadtrata,0);
    if (p->bufrec) free(p->bufrec);
    LeaveCriticalSection(&p->critsock);
    DeleteCriticalSection(&p->critsock);
    free(p);
}

void v10sockcierraservidor(servidorsocks *servidor)
{
    int i;
    servidor->status=STSOCKSERROMPE;
    if (servidor->soc!=INVALID_SOCKET) {
        closesocket(servidor->soc);
        servidor->soc=INVALID_SOCKET;
    }
    for (i=0;i<NUMREINTCIERRA;i++) {
        if (servidor->threadopen==NULL) break;
        Sleep(1);
    }
    EnterCriticalSection(&servidor->critopen);
    if (servidor->threadopen) TerminateThread(servidor->threadopen,0);
    liberalista(&servidor->listapend,v10socklibera);
    if (servidor->conservar) liberalista(&servidor->listaopen,v10socklibera);
    closesocket(servidor->soc);
    LeaveCriticalSection(&servidor->critopen);
    DeleteCriticalSection(&servidor->critopen);
    free(servidor);
}

int v10sockhaycar(v10socks *p)
{
    if (p->suspendida && p->nrec<p->tamrec) ResumeThread(p->threadtrata);
    return(p->nrec);
}

int v10socksigcar(v10socks *p)
{
    int ret;
    if (p == NULL) return(-1);
    if (p->suspendida && p->nrec<p->tamrec) ResumeThread(p->threadtrata);
    if (p->nrec==0) return (-1);
    EnterCriticalSection(&p->critsock);
    if (p->nrec==0) ret=-1;
    else {
        ret=p->bufrec[0];
        memcpy(p->bufrec,p->bufrec+1,p->nrec-1);
        p->nrec--;
        ResumeThread(p->threadtrata);
    }
    LeaveCriticalSection(&p->critsock);
    return(ret);
}

int v10sockread(v10socks *p,char *buffer,int len)
{
    if (p->suspendida && p->nrec<p->tamrec) ResumeThread(p->threadtrata);
    if (p->nrec==0) return (0);
    EnterCriticalSection(&p->critsock);
    if (p->nrec==0) len=0;
    else {
    	  if (len>p->nrec) len=p->nrec;
    	  memcpy(buffer,p->bufrec,len);
    	  if (len<p->nrec) memcpy(p->bufrec,p->bufrec+len,p->nrec-len);
          p->nrec-=len;
          ResumeThread(p->threadtrata);
    }
    LeaveCriticalSection(&p->critsock);
    return(len);
}

char *v10sockgets(char *donde,int n,v10socks *p)
{
	char *aux;
	if (p->nrec==0) return(NULL);
    EnterCriticalSection(&p->critsock);
	if ((aux=memchr(p->bufrec,'\n',p->nrec))==NULL) {
		if ((aux=memchr(p->bufrec,'\r',p->nrec))==NULL) {
			 LeaveCriticalSection(&p->critsock);
			 return(NULL);
			}
	}
	if (aux-p->bufrec<n) n=aux-p->bufrec;
	strcopia(donde,p->bufrec,n);
	p->nrec-=n+1;
	memcpy(p->bufrec,aux+1,p->nrec);
	LeaveCriticalSection(&p->critsock);
    return(donde);
}

int v10sockescribe(v10socks *p,void *buffer,int tam)
{
    int ret;
    int mandado=0;
    while (tam) {
        ret=send(p->soc,buffer,tam,0);
        if (ret==SOCKET_ERROR) {
            rompesock(p);
            return(ret);
        }
        if (ret>0) {
            tam-=ret;
            mandado+=ret;
        }
    }
    return(mandado);
}

int v10sockencola(v10socks *p,int ch)
{
    return(v10sockescribe(p,(char *)&ch,1));
}

int v10sockencolac(v10socks *p,char *cadena)
{
    return(v10sockescribe(p,cadena,strlen(cadena)));
}

int vv10sockprintf(v10socks *p,char *format,va_list arg)
{
    char cadena[MAXCADENA];
    int ret;
    ret=vsprintf(cadena,format,arg);
    return(v10sockescribe(p,cadena,ret));
}

int v10sockprintf(v10socks *p,char *format,...)
{
    va_list arg;
    int ret;
    va_start(arg,format);
    ret=vv10sockprintf(p,format,arg);
    va_end(arg);
    return(ret);
}

int v10socklisto(v10socks *p)
{
  if (p->status==STSOCKREADY) return(1);
  return(0);
}

void v10socknuggle(v10socks *p,int on) 
{
  setsockopt((SOCKET)p->soc,IPPROTO_TCP,TCP_NODELAY,(char *)&on,sizeof(on));
}

void v10sockopt(v10socks *p,int level,int opcion,char *valor,int len) 
{
  setsockopt((SOCKET)p->soc,level,opcion,valor,len);
}

char *v10sockpintadir(SOCKADDR *origen,char *donde)
{	
    unsigned char *ptr=origen->sa_data+2;
    sprintf(donde,"%03d.%03d.%03d.%03d",*ptr,ptr[1],ptr[2],ptr[3]);
	return(donde);
}

char *v10sockpintaorigen(v10socks *p,char *donde)
{	
	return(v10sockpintadir(&p->origen,donde));
}

char *v10sockpintadestino(v10socks *p,char *donde)
{	
	return(v10sockpintadir(&p->destino,donde));
}
