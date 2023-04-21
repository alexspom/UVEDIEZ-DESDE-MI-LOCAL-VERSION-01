#include "v10sockssl.h"

/* (1) Compatibilidad SSL, en ese caso de tener que utilizarse SSL en la WEB, 
       descomentar la macro V10_SSL, y meter runtime de visual C++ 8.0 
	   para poder cargar dlls libeay32.dll y ssleay32.dll */
#define V10_SLL 1

static char* pass;
static int initctx=0;
static int sslactivo = 0;
char keyfile[MAXPATH] = "d:\\openssl\\examples\\server.pem";
char certfile[MAXPATH] = "d:\\openssl\\examples\\server.pem";
char password[MAXPATH]=  "meliton";
char dhfile[MAXPATH]=  "d:\\openssl\\examples\\dh1024.pem";
char ca_list[MAXPATH]=  "d:\\openssl\\examples\\root.pem"; //root.pem"

// inicializa la librería SSL con parámetros de la micros7
V10SSLIMPORT void v10initssl(int ssl, char *_keyfile, char *_certfile,char *_password, char *_dhfile, char *_ca_list ) {

    sslactivo = ssl;
    strcpy(keyfile, _keyfile);
    strcpy(certfile, _certfile);
	strcpy(password,_password);
	strcpy(dhfile,_dhfile);
	strcpy(ca_list,_ca_list);
}

// Funciones Criptográficas SSL

/*The password code is not thread safe*/
static int password_cb(char *buf,int num, int rwflag,void *userdata) 
{	
	int lon=strlen((char *)pass)+1;
	if (num < lon)  return(0);
	strcpy(buf,pass);
	return(strlen(pass));
}


#ifdef V10_SLL
static SSL_CTX *initialize_ctx(char *certfile, char *keyfile, char *password)  {
	
	SSL_METHOD *meth;
	SSL_CTX *ctx;
    int ret;
    
	if(!initctx){
		// Global system initialization
		SSL_library_init();
		SSL_load_error_strings();
		initctx=1;
	}
   
	// Create our context
	meth=SSLv23_method();
	ctx=SSL_CTX_new(meth);

	// Load our keys and certificates
	if((ret=SSL_CTX_use_certificate_chain_file(ctx,certfile))!=1) v10log(LOGNORMAL,"Can't read certificate file %s\n",keyfile);

	pass=password;	
	SSL_CTX_set_default_passwd_cb(ctx,password_cb);
	if((ret=SSL_CTX_use_PrivateKey_file(ctx,keyfile,SSL_FILETYPE_PEM))!=1) v10log(LOGNORMAL,"Can't read key file %s con password %s\n",keyfile,password);

    // Load the CAs we trust
	if((ret=SSL_CTX_load_verify_locations(ctx,ca_list,0))!=1) v10log(LOGNORMAL,"Can't read CA list %s\n",ca_list);
#if (OPENSSL_VERSION_NUMBER < 0x00905100L)
	SSL_CTX_set_verify_depth(ctx,1);
#endif    
	return ctx;
}
 
static void destroy_ctx(SSL_CTX *ctx)  {
	SSL_CTX_free(ctx);
}

static void load_dh_params(SSL_CTX *ctx,char *file)
{
	DH *ret=0;
	BIO *bio;

	if ((bio=BIO_new_file(file,"r")) == NULL) v10log(LOGNORMAL,"%s","Couldn't open DH file");

	ret=PEM_read_bio_DHparams(bio,NULL,NULL,NULL);
	BIO_free(bio);
	if(SSL_CTX_set_tmp_dh(ctx,ret)<0) v10log(LOGNORMAL,"%s","Couldn't set DH parameters");
}


static void generate_eph_rsa_key(SSL_CTX *ctx)
{
	RSA *rsa;

	rsa=RSA_generate_key(512,RSA_F4,NULL,NULL);
	if (!SSL_CTX_set_tmp_rsa(ctx,rsa)) v10log(LOGNORMAL,"%s","Couldn't set RSA key");
	RSA_free(rsa);
}
#endif

// Fin de la parte SSL

static void cierrasocket(SOCKET soc)
{
	shutdown(soc,2);
  closesocket(soc);
}

static void anadealista(listasockssls **raiz,listasockssls *nuevo)
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

static void eliminadelista(listasockssls **raiz,listasockssls *nuevo)
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
	int reuse = 1;
	struct sockaddr_in sin;
	int err;
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
  setsockopt(soc, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse));
#ifdef __LINUX__
  setsockopt(soc, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse));
#endif
  err=bind(soc,(struct sockaddr*)&sin,sizeof(sin));
  if (err) {
		v10log(LOGNORMAL,"Haciendo bind ssl en puerto %d error %d\n",port,err);
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

static void rompepipe(v10sockssls *p)
{
	if (p==NULL) return;
	if (p->v10sock->soc!=INVALID_SOCKET) {
#ifdef V10_SLL
		if (sslactivo) SSL_free(p->ssl); 
#endif
		cierrasocket(p->v10sock->soc);
		p->v10sock->soc=INVALID_SOCKET;
		p->v10sock->status=STSOCKROTA;
		if (p->v10sock->fnbreak) p->v10sock->fnbreak(p->v10sock,SOCKBREAK,0,NULL);
	}
}

static void reintentapipe(v10sockssls *p)
{
    struct sockaddr_in sin;
    memcpy(&sin,&p->v10sock->destino,sizeof(struct sockaddr));
    p->v10sock->soc=socket(AF_INET,SOCK_STREAM,0);
    if (connect(p->v10sock->soc,(struct sockaddr *)&sin,sizeof(sin))==0) {
        v10log(LOGNORMAL,"%s","Conectado\n");
        if (p->v10sock->numrecon==0 && p->v10sock->fnopen) p->v10sock->fnopen(p->v10sock,SOCKOPEN,0,NULL);
        if (p->v10sock->fnreconecta) p->v10sock->fnreconecta(p->v10sock,SOCKOPEN,0,NULL);
        p->v10sock->numrecon++;
        p->v10sock->nrec=0;
        p->v10sock->status=STSOCKREADY;
    }  else {
        closesocket(p->v10sock->soc);
        Sleep(10);
    }
}

static void erroresSSL(v10sockssls *p,int ret) {
	switch (ret) {
		case SSL_ERROR_ZERO_RETURN:
			v10log(LOGNORMAL, "%s", "SSL_ERROR_ZERO_RETURN");
			break;
		case SSL_ERROR_WANT_READ:
			v10log(LOGNORMAL, "%s", "SSL_ERROR_WANT_READ");
			break;
		case SSL_ERROR_WANT_CONNECT:
			v10log(LOGNORMAL, "%s", "SSL_ERROR_WANT_CONNECT");
			break;
		case SSL_ERROR_WANT_ACCEPT:
			v10log(LOGNORMAL, "%s", "SSL_ERROR_WANT_ACCEPT");
			break;
		case SSL_ERROR_WANT_X509_LOOKUP:
			v10log(LOGNORMAL, "%s", "SSL_ERROR_WANT_X509_LOOKUP");
			break;
		case SSL_ERROR_SYSCALL:
			v10log(LOGNORMAL, "%s", "SSL_ERROR_SYSCALL");
			rompepipe(p);
			break;
		case SSL_ERROR_SSL:
			v10log(LOGNORMAL, "%s", "SSL_ERROR_SSL");
			rompepipe(p);
			break;					
		}
}

static void tratav10sock(v10sockssls *p)
{
	fd_set reading;
  int num;
  unsigned long lon;
  int ret,bytes=0;
#ifdef V10_SLL
   char buf[1024];
#endif
  int encrit=0;
  struct timeval timeout;
  while (p->v10sock->status!=STSOCKROTA || p->v10sock->reconecta) {
		if (p->v10sock->status==STSOCKREADY) {
			FD_ZERO(&reading);
			FD_SET(p->v10sock->soc,&reading);
			timeout.tv_sec=50;timeout.tv_usec=0;
			if (encrit) {
				LeaveCriticalSection(&p->v10sock->critsock);
				encrit=0;
			}
			num=select(p->v10sock->soc+1,&reading,NULL,NULL,&timeout);
			if (num==0) continue;
			EnterCriticalSection(&p->v10sock->critsock);
			encrit=1;
			ret=ioctlsocket(p->v10sock->soc,FIONREAD,&lon);
			if (ret==SOCKET_ERROR || lon==0) {
				//rompepipe(p);
                p->v10sock->status=STSOCKSEMIROTA;
			    if (encrit) LeaveCriticalSection(&p->v10sock->critsock);
                p->v10sock->threadtrata=NULL;
                return;
			} else {
				if (p->v10sock->nrec>=p->v10sock->tamrec) {
					if (encrit) LeaveCriticalSection(&p->v10sock->critsock);
					v10log(LOGNORMAL,"Suspendida thread %p Recibidos %d tamaño %d\n",p->v10sock->threadtrata,p->v10sock->nrec,p->v10sock->tamrec);
					p->v10sock->suspendida=1;
					SuspendThread(p->v10sock->threadtrata);
					p->v10sock->suspendida=0;
					v10log(LOGNORMAL,"Activada thread %p Recibidos %d tamaño %d\n",p->v10sock->threadtrata,p->v10sock->nrec,p->v10sock->tamrec);
					if (encrit) EnterCriticalSection(&p->v10sock->critsock);
				}
				lon=p->v10sock->tamrec-p->v10sock->nrec;

#ifdef V10_SLL
				if (sslactivo) {
					memset(buf,0,sizeof(buf));
					bytes = SSL_read(p->ssl, buf, sizeof(buf));  //SSL
					if (bytes<=0) {	
						ret=SSL_get_error(p->ssl,bytes) ;	
						erroresSSL(p,ret);
						ret=0;						
					} else {
						ret=bytes;
						memcpy(p->v10sock->bufrec+(p->v10sock->nrec),buf,bytes);
					} 
				} else 
#endif
					ret=recv(p->v10sock->soc,p->v10sock->bufrec+(p->v10sock->nrec),lon,0);
				if (p->v10sock->fnread) p->v10sock->fnread(p->v10sock,SOCKREAD,ret,p->v10sock->bufrec);
				else p->v10sock->nrec+=ret;                  				
			}
		}
		if (p->v10sock->status==STSOCKCONCLSOCK ||(p->v10sock->status==STSOCKROTA && p->v10sock->reconecta)) {
			p->v10sock->status=STSOCKCONCLSOCK;
			if (encrit) {
				LeaveCriticalSection(&p->v10sock->critsock);
			}
			reintentapipe(p);
			EnterCriticalSection(&p->v10sock->critsock);
			encrit=1;
		}
  }
  if (p->v10sock->soc!=INVALID_SOCKET) {
		cierrasocket(p->v10sock->soc);
		p->v10sock->soc=INVALID_SOCKET;
	}
  if (encrit) LeaveCriticalSection(&p->v10sock->critsock);
  v10log(LOGNORMAL,"Thread sale ident %x %d reconecta %d\n",p->v10sock->threadtrata,p->v10sock->status,p->v10sock->reconecta);
  if (p->v10sock->fnclose) p->v10sock->fnclose(p->v10sock,SOCKCLOSE,0,NULL);
  p->v10sock->threadtrata=NULL;
}



static v10sockssls *creav10sock(int tamrec,trigsocks fnopen,trigsocks fnreconecta,trigsocks fnread,trigsocks fnbreak,
                           trigsocks fnclose)
{
  v10sockssls *ret;
  ret=calloc(1,sizeof(v10sockssls));
  ret->v10sock=calloc(1,sizeof(v10socks));
  ret->v10sock->tamrec=tamrec;
  ret->v10sock->bufrec=calloc(1,tamrec);
  ret->v10sock->fnopen=fnopen;
  ret->v10sock->fnreconecta=fnreconecta;
  ret->v10sock->fnread=fnread;
  ret->v10sock->fnbreak=fnbreak;
  ret->v10sock->fnclose=fnclose;
#ifdef V10_SLL
  if (sslactivo) {
		ret->ctx=initialize_ctx(certfile,keyfile,password);
		load_dh_params(ret->ctx,dhfile);
  }
#endif
  InitializeCriticalSection(&ret->v10sock->critsock);
  return(ret);
}

static void trataopen(servidorsockssls *nuevo)
{
	SOCKET nsock;
  int len;
  struct sockaddr origen;
  listasockssls *l;
  while (nuevo->servidorsock->status!=STSOCKSERROMPE) {
		len=sizeof(origen);
		nsock=accept(nuevo->servidorsock->soc,&origen,&len);
		if (nsock==INVALID_SOCKET) continue;
		EnterCriticalSection(&nuevo->servidorsock->critopen);

		l=calloc(1,sizeof(listasockssls));
		l->valor=creav10sock(nuevo->servidorsock->tamrec,nuevo->servidorsock->fnopen,nuevo->servidorsock->fnreconecta,nuevo->servidorsock->fnread,nuevo->servidorsock->fnbreak,nuevo->servidorsock->fnclose);
		memcpy(&l->valor->v10sock->origen,&origen,sizeof(origen));
		len=sizeof(struct sockaddr);
		getsockname(nsock,&l->valor->v10sock->destino,&len);
		l->valor->v10sock->soc=nsock;

#ifdef 	V10_SSL
		if (sslactivo) {
			int ret;
			l->valor->ssl=SSL_new(l->valor->ctx);	
			SSL_set_fd(l->valor->ssl, (SOCKET)l->valor->v10sock->soc);
			ret=SSL_accept(l->valor->ssl);
			if(ret<=0) {
				ret=SSL_get_error(l->valor->ssl,ret) ;	
				erroresSSL(l->valor,ret);
				nuevo->servidorsock->status=STPIPEERRSSL;
				LeaveCriticalSection(&nuevo->servidorsock->critopen);		
				return;
			}	
		}
#endif

		l->valor->v10sock->status=STSOCKREADY;
		l->valor->v10sock->reconecta=0;
		l->valor->v10sock->servidor=nuevo->servidorsock;
		if (nuevo->servidorsock->fnopen) nuevo->servidorsock->fnopen(l->valor->v10sock,SOCKOPEN,0,NULL);
		if (nuevo->servidorsock->conservar==0) {
			anadealista(&nuevo->listapend,l);
			nuevo->servidorsock->nconpend++;
		} else {
			anadealista(&nuevo->listaopen,l);
			nuevo->servidorsock->nconopen++;
		}
		l->valor->v10sock->threadtrata=CreateThread(NULL,10000,(void *)tratav10sock,(void *)l->valor,0,NULL);
		LeaveCriticalSection(&nuevo->servidorsock->critopen);
//		v10log(LOGNORMAL,"Conectado pendientes %d abiertos %d\n",nuevo->servidorsock->nconpend,nuevo->servidorsock->nconopen);
	}

	nuevo->servidorsock->threadopen=NULL;
	if (nuevo->servidorsock->soc!=INVALID_SOCKET) {
		closesocket(nuevo->servidorsock->soc);
		nuevo->servidorsock->soc=INVALID_SOCKET;
	}
}

servidorsockssls *v10socksslnuevoservidor(char *servicio,int conservar,trigsocks fnopen,trigsocks fnreconecta,trigsocks fnread,
                             trigsocks fnbreak,trigsocks fnclose)
{
	servidorsockssls *nuevo;
  initsocket();
  nuevo=calloc(1,sizeof(servidorsockssls));
	nuevo->servidorsock=calloc(1,sizeof(servidorsocks));
  
	nuevo->servidorsock->soc=damesocserver(servicio,"tcp",&nuevo->servidorsock->port);
  if (nuevo->servidorsock->soc!=INVALID_SOCKET) {
	InitializeCriticalSection(&nuevo->servidorsock->critopen);
    nuevo->servidorsock->conservar=conservar;
    nuevo->servidorsock->fnopen=fnopen;
    nuevo->servidorsock->fnreconecta=fnreconecta;
    nuevo->servidorsock->fnread=fnread;
    nuevo->servidorsock->fnbreak=fnbreak;
    nuevo->servidorsock->fnclose=fnclose;
    nuevo->servidorsock->tamrec=TAMRECSERVER;
    nuevo->servidorsock->threadopen=CreateThread(NULL,10000,(void *)trataopen,(void *)nuevo,0,NULL);
  } else {
		free(nuevo->servidorsock);
    free(nuevo);
    nuevo=NULL;
  }
  return(nuevo);
}


v10sockssls *v10sockssldameconexion(servidorsockssls *ns)
{
	v10sockssls *ret;
	if (ns->servidorsock->nconpend>0) {
		if (ns->listapend) {
			EnterCriticalSection(&ns->servidorsock->critopen);
			ret=ns->listapend->valor;
			eliminadelista(&ns->listapend,ns->listapend);
			ns->servidorsock->nconpend--;
			LeaveCriticalSection(&ns->servidorsock->critopen);
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


static void liberalista(listasockssls **head,void (*funlibera)(v10sockssls *p))
{
	listasockssls *p;
	p=*head;
	while (p) {
		listasockssls *aux=p->next;
		funlibera(p->valor);
		eliminadelista(head,p);
		free(p);
		if (*head==NULL) break;
		p=aux;
  }
}


void v10sockssllibera(v10sockssls *p)
{
	int i;
    if (p->v10sock == NULL) return;
	p->v10sock->reconecta=0;
	p->v10sock->status=STSOCKROTA;
	if (p->v10sock->soc!=INVALID_SOCKET) {
		cierrasocket(p->v10sock->soc);
		p->v10sock->soc=INVALID_SOCKET;
  }
	for (i=0;i<NUMREINTCIERRA;i++) {
		if (p->v10sock) if (p->v10sock->threadtrata==NULL) break;
		Sleep(1);
  }
//  EnterCriticalSection(&p->v10sock->critsock);rik
#ifndef __LINUX__
 	__try {
#endif
        EnterCriticalSection(&p->v10sock->critsock);
#ifndef __LINUX__
    } __except(EXCEPTION_EXECUTE_HANDLER) {return;};
#endif
   if (p->v10sock->threadtrata) TerminateThread(p->v10sock->threadtrata,0);
  if (p->v10sock->bufrec) free(p->v10sock->bufrec);
  LeaveCriticalSection(&p->v10sock->critsock);
  DeleteCriticalSection(&p->v10sock->critsock);
#ifdef 	V10_SSL
  if (p->ctx) destroy_ctx(p->ctx); 
#endif
  v10log(LOGNORMAL,"Libera %x\n",p);
  free(p->v10sock);
  memset(p,0,sizeof(v10sockssls));
}


void v10socksslcierraservidor(servidorsockssls *servidor)
{
	int i;
	servidor->servidorsock->status=STSOCKSERROMPE;
	if (servidor->servidorsock->soc!=INVALID_SOCKET) {
		closesocket(servidor->servidorsock->soc);
    servidor->servidorsock->soc=INVALID_SOCKET;
  }
  for (i=0;i<NUMREINTCIERRA;i++) {
		if (servidor->servidorsock->threadopen==NULL) break;
		Sleep(1);
  }
	EnterCriticalSection(&servidor->servidorsock->critopen);
	if (servidor->servidorsock->threadopen) TerminateThread(servidor->servidorsock->threadopen,0);
	liberalista(&servidor->listapend,v10sockssllibera);
	if (servidor->servidorsock->conservar) liberalista(&servidor->listaopen,v10sockssllibera);
	closesocket(servidor->servidorsock->soc);
	LeaveCriticalSection(&servidor->servidorsock->critopen);
	DeleteCriticalSection(&servidor->servidorsock->critopen);
	free(servidor->servidorsock);
	free(servidor);

}


int v10socksslhaycar(v10sockssls *p)
{
	if (!p || !p->v10sock) return(0);
	if (p->v10sock->suspendida && p->v10sock->nrec<p->v10sock->tamrec) ResumeThread(p->v10sock->threadtrata);
	return(p->v10sock->nrec);
}


int v10socksslsigcar(v10sockssls *p)
{
	int ret;
	if (p->v10sock->suspendida && p->v10sock->nrec<p->v10sock->tamrec) ResumeThread(p->v10sock->threadtrata);
  if (p->v10sock->nrec==0) return (-1);
  EnterCriticalSection(&p->v10sock->critsock);
  if (p->v10sock->nrec==0) ret=-1;
  else {
		ret=p->v10sock->bufrec[0];
    memcpy(p->v10sock->bufrec,p->v10sock->bufrec+1,p->v10sock->nrec-1);
    p->v10sock->nrec--;
    ResumeThread(p->v10sock->threadtrata);
  }
  LeaveCriticalSection(&p->v10sock->critsock);
  return(ret);
}


int v10socksslread(v10sockssls *p,char *buffer,int len)
{
	if (p->v10sock->suspendida && p->v10sock->nrec<p->v10sock->tamrec) ResumeThread(p->v10sock->threadtrata);
	if (p->v10sock->nrec<=0) return (0);
	EnterCriticalSection(&p->v10sock->critsock);
	if (p->v10sock->nrec<=0) len=0;
	else {
		if (len>p->v10sock->nrec) len=p->v10sock->nrec;
		memcpy(buffer,p->v10sock->bufrec,len);
		if (len<p->v10sock->nrec) memcpy(p->v10sock->bufrec,p->v10sock->bufrec+len,p->v10sock->nrec-len);
		p->v10sock->nrec-=len;
        ResumeThread(p->v10sock->threadtrata);
     }
  LeaveCriticalSection(&p->v10sock->critsock);
  return(len);
}


char *v10socksslgets(char *donde,int n,v10sockssls *p)
{
	char *aux;
	if (p->v10sock->nrec==0) return(NULL);
    EnterCriticalSection(&p->v10sock->critsock);
	if ((aux=memchr(p->v10sock->bufrec,'\n',p->v10sock->nrec))==NULL) {
		if ((aux=memchr(p->v10sock->bufrec,'\r',p->v10sock->nrec))==NULL) {
			 LeaveCriticalSection(&p->v10sock->critsock);
			 return(NULL);
			}
	}
	if (aux-p->v10sock->bufrec<n) n=(int)(aux-p->v10sock->bufrec);
	strcopia(donde,p->v10sock->bufrec,n);
	p->v10sock->nrec-=n+1;
	memcpy(p->v10sock->bufrec,aux+1,p->v10sock->nrec);
	LeaveCriticalSection(&p->v10sock->critsock);
  return(donde);
}

int v10socksslescribe(v10sockssls *p,void *buffer,int tam)
{
	int ret;
  int mandado=0;
  while (tam) {
#ifdef V10_SSL
		if (sslactivo)
			ret=SSL_write(p->ssl, buffer, tam);
		else
#endif
		ret=send(p->v10sock->soc,buffer,tam,0);

    if ((ret==0 && sslactivo) || ret==SOCKET_ERROR) {
			rompepipe(p);
      return(ret);
    }
    if (ret>0) {
			tam-=ret;
      mandado+=ret;
    }
  }
  return(mandado);
}

int v10socksslencola(v10sockssls *p,int ch)
{
	return(v10socksslescribe(p,(char *)&ch,1));
}

int v10socksslencolac(v10sockssls *p,char *cadena)
{
	return(v10socksslescribe(p,cadena,strlen(cadena)));
}

int vv10socksslprintf(v10sockssls *p,char *format,va_list arg)
{
	char cadena[MAXCADENA];
	int ret;
	ret=vsprintf(cadena,format,arg);
	return(v10socksslescribe(p,cadena,ret));
}

int v10socksslprintf(v10sockssls *p,char *format,...)
{
	va_list arg;
	int ret;
	va_start(arg,format);
	ret=vv10socksslprintf(p,format,arg);
	va_end(arg);	
	return(ret);
}

int v10sockssllisto(v10sockssls *p)
{
  if (p->v10sock->status==STSOCKREADY) return(1);
  return(0);
}

void v10socksslnuggle(v10sockssls *p,int on) 
{
  setsockopt((SOCKET)p->v10sock->soc,IPPROTO_TCP,TCP_NODELAY,(char *)&on,sizeof(on));
}
