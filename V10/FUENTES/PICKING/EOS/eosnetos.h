/*
* Módulo : EOSNETOS.H
* Objeto: Include para los displays EOS específico para NET+OS
*
*
* Autor	 : José Carlos Santos
* Fecha  : 01-02-2009

* MODIFICACIONES
* --
*/


#ifndef EOSNETOS_H_
#define EOSNETOS_H_

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include "sockapi.h"

typedef long long v10horas;

typedef int HANDLE;

#define FALSE 0
#define TRUE 1

int maxnivellog;

#define final(x) {printf x;exit;}

#define esperamensaje(x) {struct timespec tiempo={0,x};nanosleep(&tiempo,NULL);}
#define duerme(x) tx_thread_sleep(x)

#define DISPOSITIVO	"/dev/puertos_serie"
extern int puerto232[];

//Copiado de winsock.h

//typedef u_int           SOCKET;

# define INVALID_SOCKET	(SOCKET) (~0)
//# define SOCKET_ERROR			(-1)

//Niveles estandar de LOGS
//#define LOGERROR      1
//#define LOGAVISO      2
//#define LOGPROGRESO   3
//#define LOGDEPURA     5
#define LOGDEPURALL   7
//#define LOGDEPURALIB  9

#define LOGERROR   0
#define LOGWARNING 1
#define LOGNORMAL  2
#define LOGDEBUG   3

#define NOPARITY    0

/*
#define LOGERROR    0
#define LOGWARNING  1
#define LOGPROGRESO 2*/

#define NOPARITY    0

#define ONESTOPBIT  0

#define MAXPATH 256
#define MAXCADENA 8192
#define MAXBUFFER 10240


void initv10log(char *ficherolog);//,char *ficheroerr);
void escribe_log(int visto,char *format,...);

int initpuerto232(int port,long velocidad,int paridad,int datos,int stop);
HANDLE damepuerto232(int puerto);

void encolae(int port,char ch);
int sig_carr(int port);

int es_blanco(char *cadena);
char *pad (char *cadena, unsigned leng);
char *trunca(char *cadena,unsigned leng);

v10horas damecent();

#endif /*EOSNETOS_H_*/

