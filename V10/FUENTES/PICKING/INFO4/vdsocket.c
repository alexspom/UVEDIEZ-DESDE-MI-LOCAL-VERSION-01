#include "info4.h"

#define TAMRECSOCKET 1024

static void initsocket(void)
{
#ifdef WIN32
  static int init;
  WSADATA ws;
  if (init!=0) return;
  init=1;
  WSAStartup(0x0002,&ws);
#else
	return;
#endif
}

static int vdioctl(SOCKET s, long cmd, unsigned long* argp)
{
#ifdef WIN32
  return(ioctlsocket(s,cmd,argp));
#else
  return(ioctl(s,cmd,argp));
  return 0;
#endif
}



static int cierrasocket(SOCKET soc)
{
   int ret;
   shutdown (soc, 2);
#ifdef WIN32
  ret=closesocket(soc);
#else
   ret=close(soc);
#endif
   return(ret);
}

static int errorsocket(void)
{
  int ret;
#ifdef WIN32
         ret=WSAGetLastError();
#else
		ret=errno;
#endif
  return(ret);
}

short dameport(char *servicio)
{
   short port;
   int err;
   struct servent   *pse;
   initsocket();
   if (atoi(servicio)==0) {
      pse=getservbyname(servicio,"tcp");
      if (pse==NULL) {
         err=errorsocket();
         v10log(LOGERROR,"Buscando port %s error %d\n",servicio,err);
         return(-1);
       }
      port=pse->s_port;
   } else port=htons((short)atoi(servicio));
  return(port);
}

static SOCKET damesocserver(short port)
{
    SOCKET soc;
    struct sockaddr_in sin;
    int err,opt=1;
    initsocket();
    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr=INADDR_ANY;
    sin.sin_port=port;
    soc=socket(AF_INET,SOCK_STREAM,0);
    setsockopt(soc,SOL_SOCKET,SO_REUSEADDR,(void *)&opt,sizeof(opt));
    err=bind(soc,(struct sockaddr*)&sin,sizeof(sin));
    if (err) {
       v10log(LOGERROR,"Haciendo bind error %d\n",err);
       cierrasocket(soc);
       return(INVALID_SOCKET);
    }
    err=listen(soc,1);
    if (err) {
       v10log(LOGERROR,"En listen error %d\n",err);
       cierrasocket(soc);
       return(INVALID_SOCKET);
    }
    return(soc);
}

static int llreabreservidor(vdsockets *vds)
{
   unsigned int len;
   SOCKET nsock;
   int ret;
   vds->soc=damesocserver(vds->port);
   if (vds->soc==INVALID_SOCKET) return(-1);
   vds->nrec=0;
   do {
     len=sizeof(vds->origen);
     nsock=accept(vds->soc,&vds->origen,&len);
     if (nsock!=INVALID_SOCKET) {
          len=sizeof(vds->destino);
          getsockname(nsock,&vds->destino,&len);
          ret=cierrasocket(vds->soc);
          if (ret) v10log(LOGERROR,"Error cerrando socket servidor %d\n",ntohs(vds->port));
          vds->soc=nsock;
      }
    } while (nsock==INVALID_SOCKET);
   vds->status=STSOCKABIERTO;
   v10log(LOGNORMAL,"Socket %d abierto\n",ntohs(vds->port));
   return(0);
}

int reabreservidor (vdsockets *vds)
{
  vds->status=STSOCKABRIENDO;
  pthread_create(&vds->thread,0,(void *(*)(void*))llreabreservidor,vds);
  return(0);
}

vdsockets *creaservidor(char *servicio)
{
  vdsockets *ret;
  ret=calloc(1,sizeof(vdsockets));
  ret->port=dameport(servicio);
  if (ret->port==-1) {
     free(ret);
     v10log(LOGNORMAL,"Debe definir servicio %s en services.\n",servicio);
     return(NULL);
   }
  ret->bufrec=calloc(1,TAMRECSOCKET);
  ret->tambufrec=TAMRECSOCKET;
  if (reabreservidor(ret)) {
     free(ret->bufrec);
     free(ret);
     return(NULL);
   }
  return(ret);
}

static void llreabrecliente(vdsockets *vds)
{
	int opt=1;
   vds->soc=socket(AF_INET,SOCK_STREAM,0);
   setsockopt(vds->soc,SOL_SOCKET,SO_REUSEADDR,(void *)&opt,sizeof(opt));
   vds->nrec=0;
   while (connect(vds->soc,&vds->destino,sizeof(vds->destino))!=0){
         Sleep(10);
     }
   v10log(LOGDEBUG,"Conectado\n",0);
   vds->status=STSOCKABIERTO;
}

int reabrecliente(vdsockets *vds)
{
  vds->status=STSOCKCONECTANDO;
  pthread_create(&vds->thread,0,(void *(*)(void*))llreabrecliente,vds);
  return(0);
}

vdsockets *creacliente(char *ordenador,char *servicio)
{
  vdsockets *ret;
  static struct hostent   *phe;
  ret=calloc(1,sizeof(vdsockets));
  ret->port=dameport(servicio);
  if (ret->port==-1) {
     free(ret);
     v10log(LOGNORMAL,"Debe definir servicio %s en services.\n",servicio);
     return(NULL);
   }
  phe=gethostbyname(ordenador);
  if (phe==NULL) final(("No existe host %s\n",ordenador));
  memcpy(&((struct sockaddr_in *)(&ret->destino))->sin_addr,*phe->h_addr_list,phe->h_length);
  ret->destino.sa_family=AF_INET;
  ((struct sockaddr_in *)(&ret->destino))->sin_port=ret->port;
  ret->bufrec=calloc(1,TAMRECSOCKET);
  ret->tambufrec=TAMRECSOCKET;
  if (reabrecliente(ret)) {
     free(ret->bufrec);
     free(ret);
     return(NULL);
   }
  return(ret);
}

int verificasocket(vdsockets *s)
{
  fd_set reading;
  struct timeval timeout;
  unsigned long lon;
  int ret;
  if (s==NULL) return(-1);
  if (s->status!=STSOCKABIERTO) return(-1);
  FD_ZERO(&reading);
  FD_SET((SOCKET)s->soc,&reading);
  timeout.tv_sec=0;timeout.tv_usec=0;
  ret=select((int)(s->soc)+1, &reading, NULL,NULL, &timeout);
  if (FD_ISSET(s->soc,&reading)==1 && ret>0) {
     ret=vdioctl((SOCKET)s->soc,FIONREAD,&lon);
     if (ret==SOCKET_ERROR || lon==0) {
        cierrasocket(s->soc);
        v10log(LOGERROR,"socket cerrado %d lon %d\n",ret,lon);
        s->status=STSOCKCERRADO;
        return(-1);
     } else if (lon!=0) return(lon);
  }
  return(0);
}

static int buffersocket(vdsockets *s)
{
  int ret;
  int pedir;
  ret=verificasocket(s);
  if (ret==-1) return(ret);
  pedir=s->tambufrec-s->nrec;
  if (pedir<=0) return(s->nrec);
  if (ret) {
     if (pedir>ret) pedir=ret;
     pedir=recv(s->soc,s->bufrec+s->nrec,pedir,0);
     s->nrec+=pedir;
  }
  return(s->nrec);
}

int haycarsocket(vdsockets *s)
{
  int ret;
  ret=buffersocket(s);
  if (ret==-1) return(0);
  return(s->nrec);
}

int sigcarsocket(vdsockets *s)
{
  if (haycarsocket(s)) {
     int ret;
     ret=s->bufrec[0];
     memcpy(s->bufrec,s->bufrec+1,s->nrec-1);
     s->nrec--;
     return(ret);
   }
  return(-1);
}

int leebufsocket(vdsockets *s,char *buffer,int len)
{
  int ret;
  if (len==0) {
     *buffer=0;
     return(0);
  }
  ret=haycarsocket(s);
  if (ret) {
     if (len>s->nrec)
        len=s->nrec;
     memcpy(buffer,s->bufrec,len);
     memcpy(s->bufrec,s->bufrec+len,s->nrec-len);
     s->nrec-=len;
     return(len);
   }
  return(0);
}

int leebufsocketw(vdsockets *s,char *buffer,int len)
{
  int ret;
  int llevo=0;
  while (llevo<len) {
        ret=leebufsocket(s,buffer+llevo,len-llevo);
        if (s->status!=STSOCKABIERTO) return(0);
        llevo+=ret;
    }
  return(len);
}

int sendvdsocket(vdsockets *s,char *donde,int bytes)
{
  int ret,llevo=0;
    ret = verificasocket(s);
    if (ret == -1) return(ret);
  if (s->status==STSOCKABIERTO) {
     while (bytes) {
           ret=send(s->soc,donde+llevo,bytes,0);
           if (ret==SOCKET_ERROR) {
              cierrasocket(s->soc);
              s->status=STSOCKCERRADO;
              break;
            }
           llevo+=ret;
           bytes-=ret;
           if (ret==0) break;
      }
   } else llevo=0;
  return(llevo);
}

