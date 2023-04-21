#include "eos.h"
#include <fcntl.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#ifndef __NETOS__
//#include <sys/ioctl.h>
#endif

#ifdef __NETOS__
#include "bsp.h"
#include "nastatus.h"
#include <sysClock.h>
#endif

int es_blanco(char *cadena)
{
	if (cadena==NULL) return(1);
	while (*cadena)
		if (*cadena++!=' ')
			return(0);
	return(1);
}

char *trunca(char *cadena,unsigned leng)
{
	if (strlen(cadena)>leng) cadena[leng]='\0';
	return(cadena);
}

char *pad(char *cadena,unsigned leng)
{
	if (leng<strlen(cadena)) trunca(cadena,leng);
	else
	{
		memset(cadena+strlen(cadena),' ',leng-strlen(cadena));
		cadena[leng]='\0';
	}
	return(cadena);
}

v10horas damecent()
{
#ifndef __NETOS__
	struct timeval tv={0,0};
	if (gettimeofday(&tv, NULL)==0){
		tv.tv_sec&=0x00ffffff;
		tv.tv_sec*=100;
		tv.tv_sec+=tv.tv_usec/10000;
// 		return(tv.tv_sec);
	}
	else escribe_log(2, "Error en damecent: %s\n", strerror(errno));
	return(tv.tv_sec);
#else
	unsigned long pruebatime=0/*, frecuencia=0*/;
//	frecuencia = NABspTicksPerSecond;
	pruebatime=tx_time_get();
	return(pruebatime);
#endif
}
char pp[100];
void initv10log(char *ficherolog)//,char* ficheroerr)
{
	int i;
	i=strlen(ficherolog);
	if (i) strcpy(pp,"");
}
/*
void escribe_log(int visto,char *format,...)
{
	char buffer[MAXCADENA];
	va_list arg;
	va_start(arg,format);
 	vsprintf(buffer,format,arg);
	printf("%s",buffer);
}
*/
int puerto232[MAXPUERTOS];
int initpuerto232(int port,int velocidad,int datos,int paridad,int stop)
{
	char error[]={"Error en la función \"initpuerto232\""};
	char dev[100];
	struct termios newtio;
#ifdef __NETOS__
	int ret=0;
	bzero(dev, sizeof(dev));
	bzero(&newtio, sizeof(newtio));
	sprintf(dev,"/com/%d",port);
#else
	bzero(dev, sizeof(dev));
	sprintf(dev,"/dev/ttyS%d",port);
#endif
#ifndef __NETOS__
        //escribe_log(LOGERROR, "Intentando abrir el puerto %s.Puerto %d \n",dev,port);
	puerto232[port]=open(dev, O_RDWR | O_NOCTTY| O_NONBLOCK);
//         escribe_log(LOGERROR, "Abriendo el puerto %s. Vale %d en puerto %d \n",dev,puerto232[port], port);
// 	escribe_log(LOGDEPURALL, "initpuerto232: Pedido abrir puerto %d (%s) me dan como HANDLE %d\n", port,dev, puerto232[port]);
#else
	puerto232[port]=open(dev, O_RDWR | O_NONBLOCK);
#endif
	if (puerto232[port]<0)
	{
		perror(error);
		escribe_log(LOGERROR, "El puerto %s %d no se ha abierto. ",dev,port);
		return -1;
	}
	else escribe_log (LOGDEPURALL,"Puerto %s %d abierto %d\n",  dev,port, puerto232[port]);
	tcgetattr(puerto232[port],&newtio);
#ifndef __NETOS__
	newtio.c_cflag = B57600 | CS8 | CLOCAL | CREAD;//CRTSCTS |
//	newtio.c_cflag = B57600 | CS8 | CLOCAL | CREAD;//CRTSCTS |
// 	newtio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;//CRTSCTS |
#else
	newtio.c_cflag = CS8 | CLOCAL | CREAD;
	newtio.baud = 57600;
#endif
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;

#ifndef __NETOS__
	//inicializar los caracteres de control:
	newtio.c_cc[VDISCARD] = 0;
	newtio.c_cc[VEOF] = 4;
	newtio.c_cc[VEOL] = 0;
	newtio.c_cc[VEOL2] = 0;
	newtio.c_cc[VERASE] = 0;
	newtio.c_cc[VINTR] = 0;
	newtio.c_cc[VKILL] = 0;
	newtio.c_cc[VLNEXT] = 0;
	newtio.c_cc[VMIN] = 1;
	newtio.c_cc[VQUIT] = 0;
	newtio.c_cc[VREPRINT] = 0;
	newtio.c_cc[VSWTC] = 0;
	newtio.c_cc[VSTART] = 0;
	newtio.c_cc[VSTOP] = 0;
	newtio.c_cc[VSUSP] = 0;
	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VWERASE] = 0;
	tcflush(puerto232[port], TCIOFLUSH);//limpia la linea
	tcsetattr (puerto232[port], TCSANOW, &newtio);
// 	printf ("csetarrt devuelve %d\n",tcsetattr(puerto232[port],TCSANOW,&newtio));//activa los atributos del puerto
	return(0);
#else
	ret=tcflush(puerto232[port], TCIOFLUSH);//limpia la linea
	if (ret!=0)
	{
		sprintf(error, "Error en tcflush. %d\n", getErrno());
		escribe_log(LOGERROR, error);
	}
	else {
		ret=tcsetattr(puerto232[port],TCSANOW,&newtio);//activa los atributos del puerto
		if (ret!=0)
		{
			sprintf(error, "Error en tcsetattr. %d\n", getErrno());
			escribe_log(LOGERROR, error);
		}
	}
	return(ret);
#endif

}

void encolae(int port,char ch)
{
	write(puerto232[port],&ch,1);
}/*
void encolae(int port,char ch)
{
	write(puerto232[port],&ch,1);
}*/

int sig_carr(int port)
{
//	char error[]={"Error en sig_carr"};
	int ret=-1;
	static unsigned char ch;
	ret=read(puerto232[port],&ch,1);
	if (ret==-1)
		return(-1);
	return(ch);
}

int hay_tecla(void)
{
	return(0);
}

int tecla(void)
{
	return(0);
}

HANDLE damepuerto232(int puerto)
{
//	escribe_log(LOGERROR, "damepuerto232: Lo que me piden es el puerto de %d y vale %d\n", puerto, puerto232[puerto]);
	return (puerto232[puerto]);
}
