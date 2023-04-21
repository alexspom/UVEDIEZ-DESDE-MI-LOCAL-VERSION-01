/***************************************************************************
                          eoslinux.h  -  description
                             -------------------
    email                :
 ***************************************************************************/

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
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/select.h>
#include <asm/ioctls.h>
#include <termios.h>
#include <sys/ipc.h>

#include <sys/shm.h>
#include <sys/ioctl.h>

typedef long long v10horas;
typedef int BOOL;
typedef int HANDLE;
typedef double DWORD;
#define FALSE 0
#define TRUE 1

int maxnivellog;

#define final(x) {printf x;exit;}

#define esperamensaje(x) {struct timespec tiempo={0,x};nanosleep(&tiempo,NULL);}

#define DISPOSITIVO	"/dev/puertos_serie"
#define MAXPUERTOS 20
int puerto232[MAXPUERTOS];

//Copiado de winsock.h

typedef u_int           SOCKET;

# define INVALID_SOCKET	(SOCKET) (~0)
# define SOCKET_ERROR			(-1)

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
#define closesocket close

void initv10log(char *ficherolog);//,char *ficheroerr);
void escribe_log(int visto,char *format,...);

int initpuerto232(int port,tcflag_t velocidad,int paridad,int datos,int stop);
HANDLE damepuerto232(int puerto);

void encolae(int port,char ch);
int sig_carr(int port);

int es_blanco(char *cadena);
char *pad(char *cadena,unsigned leng);
void miescribelog(int nivel,char *format,...);

v10horas damecent();

