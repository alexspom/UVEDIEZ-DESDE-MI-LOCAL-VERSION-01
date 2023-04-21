#ifndef _V10SOCKSSL 
#define _V10SOCKSSL 1
#include "ssl.h"
#include "v10.h"

#ifndef __LINUX__
#ifdef _V10SSLDLL
  #define V10SSLIMPORT __declspec(dllimport)
#else
  #define V10SSLIMPORT __declspec( dllexport )
#endif
#endif

#define STPIPEERRSSL 5

struct V10SOCKSSL;

typedef struct V10SOCKSSL {
       v10socks *v10sock;
	   SSL_CTX *ctx;			// entorno criptográfico
	   SSL *ssl;				  // entorno SSL
} v10sockssls;

typedef struct LISTASOCKSSLS {
         struct LISTASOCKSSLS *next,*prev;
         v10sockssls   *valor;
} listasockssls;


typedef struct SERVIDORSOCKSSLS {
	servidorsocks	 *servidorsock;
	listasockssls    *listapend;  // Lista de conexiones recibidas pendientes de tratar
	listasockssls    *listaopen;  // Lista de conexiones abiertas que trata el servidor
} servidorsockssls;


// SSL
#define BUFSIZZ 1024
#define CABRESPUESTA "HTTP/1.0 200 OK\n"
#define RESPUESTADATE "Date:"
#define RESPUESTACONTTYPE "Content-Type: text/html\n"
#define RESPUESTACONTLEN "Content-Length:"

V10SSLIMPORT servidorsockssls *v10socksslnuevoservidor(char *servicio,int conservar,trigsocks fnopen,trigsocks fnreconecta,trigsocks fnread,
                             trigsocks fnbreak,trigsocks fnclose);
V10SSLIMPORT v10sockssls *v10sockssldameconexion(servidorsockssls *ns);
V10SSLIMPORT void v10sockssllibera(v10sockssls *p);
V10SSLIMPORT void v10socksslcierraservidor(servidorsockssls *servidor);
V10SSLIMPORT int  v10socksslhaycar(v10sockssls *p);
V10SSLIMPORT int  v10socksslsigcar(v10sockssls *p);
V10SSLIMPORT int  v10socksslread(v10sockssls *p,char *buffer,int len);
V10SSLIMPORT char *v10socksslgets(char *donde,int n,v10sockssls *p);
V10SSLIMPORT int  v10socksslescribe(v10sockssls *p,void *buffer,int tam);
V10SSLIMPORT int  v10socksslencola(v10sockssls *p,int ch);
V10SSLIMPORT int  v10socksslencolac(v10sockssls *p,char *cadena);
V10SSLIMPORT int  vv10socksslprintf(v10sockssls *p,char *format,va_list arg);
V10SSLIMPORT int  v10socksslprintf(v10sockssls *p,char *format,...);
V10SSLIMPORT int  v10sockssllisto(v10sockssls *p);
V10SSLIMPORT void v10socksslnuggle(v10sockssls *p,int on);
V10SSLIMPORT void v10initssl(int ssl, char *_keyfile, char *_certfile, char *_password, char *_dhfile, char *_ca_list);


#endif

