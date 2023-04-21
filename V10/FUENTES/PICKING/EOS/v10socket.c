/*
* Módulo : V10SOCKET.C
* Objeto: Rutinas de sockets para compatibilidad de sistemas
*
*
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-12-2007

* MODIFICACIONES
* --
*/
#include "eos.h"

#define TAMRECSOCKET    1024

static void initsocket(void)
{
#ifdef __WIN32__
  static int init;
  WSADATA ws;
  if (init!=0) return;
  init=1;
  WSAStartup(0x0002,&ws);
#else
	return;
#endif
}

static int lwioctl(SOCKET s, long cmd, u_long* argp)
{
#ifdef __WIN32__
  return(ioctlsocket(s,cmd,argp));
#endif
#ifdef __LINUX__
  return(ioctl(s,cmd,argp));
#endif
#ifdef __NETOS__
	return(ioctl(s,cmd,(char*)argp));
#endif
}



static int cierrasocket(SOCKET soc)
{
   int ret;
   shutdown (soc, 2);
#ifdef __WIN32__
  ret=closesocket(soc);
#else
   ret=close(soc);
#endif
   return(ret);
}

static int errorsocket(void)
{
  int ret;
#ifdef __WIN32__
         ret=WSAGetLastError();
#else
		ret=errno;
#endif
  return(ret);
}

short dameport(char *servicio)
{
#ifndef __NETOS__
   short port;
   int err;
   struct servent   *pse;
   initsocket();
   if (atoi(servicio)==0) {
      pse=getservbyname(servicio,"tcp");
      if (pse==NULL) {
         err=errorsocket();
         miescribelog(LOGERROR,"Buscando port %s error %d\n",servicio,err);
         return(-1);
       }
      port=pse->s_port;
   } else port=htons((short)atoi(servicio));
  return(port);

#else

	int ret=0;
	/*
   short port;
   int err;
   struct servent   *pse;
   initsocket();
   if (atoi(servicio)==0) {
      pse=getservbyname(servicio,"tcp");
      if (pse==NULL) {
         err=errorsocket();
         miescribelog(LOGERROR,"Buscando port %s error %d\n",servicio,err);
         return(-1);
       }
      port=pse->s_port;
   } else port=htons((short)atoi(servicio));
  return(0);*/
  if (strlen(servicio)==6) ret=30000+atoi(&servicio[5]);
  else ret=31000+atoi(&servicio[3]);
//  if (strncmp(servicio, "LINEA1", strlen(servicio)-1)==0) ret=30000;
//  else if (strncmp(servicio, "LOG1", strlen(servicio)-1)==0) ret = 31000;
  return (ret);

#endif
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
       miescribelog(LOGERROR,"Haciendo bind error %d\n",err);
       cierrasocket(soc);
       return(INVALID_SOCKET);
    }
    err=listen(soc,1);
    if (err) {
       miescribelog(LOGERROR,"En listen error %d\n",err);
       cierrasocket(soc);
       return(INVALID_SOCKET);
    }
    return(soc);
}

static int llreabreservidor(v10sockets *v10s)
{
   int len;
   SOCKET nsock;
   int ret;
   v10s->soc=INVALID_SOCKET;
   while (v10s->soc==INVALID_SOCKET) {
          v10s->soc=damesocserver(v10s->port);
          if (v10s->soc==INVALID_SOCKET) usleep(1000);
   }
   v10s->nrec=0;
   do {
     len=sizeof(v10s->origen);
     nsock=accept(v10s->soc,&v10s->origen,&len);
     if (nsock!=INVALID_SOCKET) {
          len=sizeof(v10s->destino);
          getsockname(nsock,&v10s->destino,&len);
          ret=cierrasocket(v10s->soc);
          if (ret) miescribelog(LOGERROR,"Error cerrando socket servidor %d\n",ntohs(v10s->port));
          v10s->soc=nsock;
      }
    } while (nsock==INVALID_SOCKET);
   v10s->status=STSOCKABIERTO;
   miescribelog(LOGNORMAL,"Socket %d abierto\n",ntohs(v10s->port));
   return(0);
}

int reabreservidor (v10sockets *v10s)
{
  v10s->status=STSOCKABRIENDO;
  pthread_create(&v10s->thread,0,(void *(*)(void*))llreabreservidor,v10s);
  return(0);
}

v10sockets *creaservidor(char *servicio)
{
  v10sockets *ret;
  ret=calloc(1,sizeof(v10sockets));
  ret->port=dameport(servicio);
  if (ret->port==-1) {
     free(ret);
     miescribelog(LOGNORMAL,"Debe definir servicio %s en services.\n",servicio);
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

static void llreabrecliente(v10sockets *v10s)
{
	int opt=1;
   v10s->soc=socket(AF_INET,SOCK_STREAM,0);
   setsockopt(v10s->soc,SOL_SOCKET,SO_REUSEADDR,(void *)&opt,sizeof(opt));
   v10s->nrec=0;
   while (connect(v10s->soc,&v10s->destino,sizeof(v10s->destino))!=0){
//         miescribelog(LOGDEPURA,"No puedo conectar\n");
#ifdef __WIN32__
         Sleep(10);
#endif
#ifdef __LINUX__
		sleep(10);
#endif
#ifdef __NETOS__
	duerme (10);
#endif
     }
   miescribelog(LOGNORMAL,"Conectado\n");
   v10s->status=STSOCKABIERTO;
}

int reabrecliente(v10sockets *v10s)
{
  v10s->status=STSOCKCONECTANDO;
  pthread_create(&v10s->thread,0,(void *(*)(void*))llreabrecliente,v10s);
  return(0);
}

v10sockets *creacliente(char *ordenador,char *servicio)
{
  v10sockets *ret;
  static struct hostent   *phe;
  ret=calloc(1,sizeof(v10sockets));
  ret->port=dameport(servicio);
  if (ret->port==-1) {
     free(ret);
     miescribelog(LOGNORMAL,"Debe definir servicio %s en services.\n",servicio);
     return(NULL);
   }
#ifndef __NETOS__
  phe = gethostbyname(ordenador);
  if (phe==NULL) final(("No existe host %s\n",ordenador));
  memcpy(&((struct sockaddr_in *)(&ret->destino))->sin_addr,phe->h_addr,phe->h_length);
#endif
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

int verificasocket(v10sockets *s)
{
  fd_set reading;
  struct timeval timeout;
  unsigned long lon;
  int ret, kk=0;
  if (s==NULL) return(-1);
  if (s->status!=STSOCKABIERTO) return(-1);
  FD_ZERO(&reading);
  FD_SET((SOCKET)s->soc,&reading);
  timeout.tv_sec=0;timeout.tv_usec=0;
  ret=select((int)(s->soc)+1, &reading, NULL,NULL, &timeout);
//  miescribelog(LOGNORMAL,"Select devuelve %d\n",ret);
#ifdef __NETOS__
  if (FD_ISSET(s->soc,&reading) && ret>0) {
	return (1);
#else
  kk = FD_ISSET(s->soc,&reading);
  if (kk==1 && ret>0) {
#endif
     ret=lwioctl((SOCKET)s->soc,FIONREAD,&lon);
     if (ret==SOCKET_ERROR || lon==0) {
        cierrasocket(s->soc);
        miescribelog(LOGDEBUG,"socket cerrado %d lon %d\n",ret,lon);
        s->status=STSOCKCERRADO;
        return(-1);
     } else if (lon!=0) return(lon);
  }

  return(0);
}

static int buffersocket(v10sockets *s)
{
  int ret;
  int pedir;
  if (s->nrec) return(s->nrec);
  ret=verificasocket(s);
  if (ret==-1) return(ret);
  pedir=s->tambufrec-s->nrec;
  if (pedir<=0) return(s->nrec);
  if (ret) {
#ifndef __NETOS__
     if (pedir>ret) pedir=ret;
     pedir=recv(s->soc,s->bufrec+s->nrec,pedir,0);
     s->nrec+=pedir;
#else
     pedir=recv(s->soc,s->bufrec+s->nrec,pedir,0); //MSG_OOB specifies that you want recv to read any out-of-band
                                                         // data present on the socket, rather than the regular in-band data.
                                                         // Used with stream sockets only.
     if (pedir<0) {
     	ret=getErrno();
     	miescribelog(LOGERROR,"Error en buffersocket. Error %d\n",ret);
        cierrasocket(s->soc);
        s->status=STSOCKCERRADO;
        return(0);
     }
     else s->nrec+=pedir;
#endif
  }
  return(s->nrec);
}

int haycarsocket(v10sockets *s)
{
  int ret;
  ret=buffersocket(s);
  if (ret==-1) return(0);
  return(s->nrec);
}

int sigcarsocket(v10sockets *s)
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

int sigcarsocketw(v10sockets *s)
{
   int ret;
   while ((ret=sigcarsocket(s))==-1) {
         if (s->status!=STSOCKABIERTO) return(-1);
    }
   return(ret);
}

int leebufsocket(v10sockets *s,char *buffer,int len)
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

int leebufsocketw(v10sockets *s,char *buffer,int len)
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

int sendv10socket(v10sockets *s,char *donde,int bytes)
{
  int ret,llevo=0;
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

int vprintfv10socket(v10sockets *s,char *format,va_list arg)
{
  char buffer[MAXCADENA];
  int ret;
  ret=vsprintf(buffer,format,arg);
  sendv10socket(s,buffer,ret);
  return(ret);
}

int printfv10socket(v10sockets *s,char *format,...)
{
  int ret;
  va_list arg;
  va_start(arg,format);
  ret=vprintfv10socket(s,format,arg);
  va_end(arg);
  return(ret);
}

void liberav10socket(v10sockets *s)
{
	if (s==NULL) return;
	closesocket(s->soc);
	if (s->bufrec) free(s->bufrec);
	free(s);
}