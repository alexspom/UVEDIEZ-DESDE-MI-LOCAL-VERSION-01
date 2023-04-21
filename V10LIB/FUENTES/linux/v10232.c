/*
* Módulo : v10232.C                                              
* Objeto:  Tratamiento de puertos serie
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"
#include <termios.h>


static HANDLE port232[MAXPUERTOS232];


void STDfin232(void)
{
  int i;
  for (i=0;i<MAXPUERTOS232;i++) {
      if (port232[i] && port232[i]!=INVALID_HANDLE_VALUE) {
		  close((size_t)port232[i]);
	  }
      port232[i]=0;
    }
}

HANDLE damepuerto232(int puerto)
{
  return(port232[puerto]);
}

void STDcierrapuerto232(int com) 
{
	if (port232[com] && port232[com]!=INVALID_HANDLE_VALUE) {
		close((size_t)port232[com]);
        port232[com]=0;
	}
}

typedef struct {
    int velreal;
    int valorlinux;
} vellinux;
static vellinux arrvel[] =  { {50, B50},{110, B110},{134, B134},{150, B150},{200, B200},{300, B300},{600, B600},{1200, B1200},{1800, B1800},{2400, B2400},{4800, B4800},{9600, B9600},
                              {19200, B19200},{38400, B38400}, {57600, B57600}, {115200, B115200},{230400,B230400} ,{460800, B460800}, {500000, B500000}, {576000, B576000}, {921600, B921600},
                              {1000000, B1000000}, {1152000, B1152000}, {1500000, B1500000}, {2000000, B2000000}, {2500000, B2500000}, {3000000, B3000000}, {3500000, B3500000}, {4000000, B4000000}, {-1, -1}};
    
static int damevelocidad(int velocidad)
{
    vellinux *ptr;
    for (ptr = arrvel; ptr->velreal > 0; ptr++) {
        if (velocidad==ptr->velreal) return ptr->valorlinux;        
    }    
    return(0);
}

int STDinitpuerto232(int com,int velocidad,int paridad,int bits,int parada)
{
	char error[] = { "Error en la funcion \"initpuerto232\"" };
	char dev[100];
	struct termios newtio;
    int ret;
    int valorlinux;
	memset(dev,0, sizeof(dev));
	sprintf(dev, "/dev/ttyUSB%d", com);
        //v10log(LOGERROR, "Intentando abrir el puerto %s.Puerto %d \n",dev,port);
	port232[com] = (HANDLE)open(dev, O_RDWR | O_NOCTTY | O_NONBLOCK);
//         v10log(LOGERROR, "Abriendo el puerto %s. Vale %d en puerto %d \n",dev,port232[port], port);
// 	v10log(LOGDEPURALL, "initport232: Pedido abrir puerto %d (%s) me dan como HANDLE %d\n", port,dev, port232[port]);
	if ((int)port232[com] < 0) {
		perror(error);
		v10log(LOGERROR, "El puerto %s %d no se ha abierto. ", dev, com);
		return -1;
	} else v10log(LOGNORMAL, "Puerto %s %d abierto %d\n", dev, com, port232[com]);
	tcgetattr((size_t)port232[com], &newtio);
	newtio.c_cflag =  CS8 | CLOCAL | CREAD;//CRTSCTS |
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;
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
    valorlinux = damevelocidad(velocidad);
    ret = cfsetispeed(&newtio, valorlinux);
    ret = cfsetospeed(&newtio, valorlinux);
    if (ret) v10log(LOGNORMAL, "Error poniendo terminal %d errno %d", ret, errno);
    ret = tcsetattr((size_t)port232[com], TCSANOW, &newtio);
    if (ret) v10log(LOGNORMAL, "Error poniendo terminal %d", 0);
// 	printf ("csetarrt devuelve %d\n",tcsetattr(port232[com],TCSANOW,&newtio));//activa los atributos del puerto
	return (0);
}

void STDestado232(int puerto,long *velocidad,int *paridad,int *parada,int *datos)
{
}

void trataerror232(int com)
{
}

void STDencolach232(int com,int ch)
{
	write((size_t)port232[com], &ch, 1);
}

void STDencolaecad232(int com,char *cadena)
{
	write((size_t)port232[com], cadena, strlen(cadena));
}

DWORD STDescribebuffer232(int com,void *msg, int tam)
{
	return(write((size_t)port232[com], msg, tam));
    return(0);
}    

int STDhaycar232(int com)
{
    return(0);
}

int STDdamecar232(int com)
{
	int ret = -1;
	unsigned char ch;
	ret = read((size_t)port232[com], &ch, 1);
	if (ret < 1)
		return (-1);
	return (ch);
}

void STDponst232(int com,long velocidad,int paridad,int stop,int bits)
{
}

void STDprintf232(int com,char *format,...)
{
	char destino[MAXCADENA];
	va_list arg;
	va_start(arg,format);
	vsprintf(destino, format, arg);
	STDencolaecad232(com, destino);
	va_end(arg);
}

void STDprotocolo232(int port,int xon)
{
}

void STDpondtr232(int com, int valor)
{
	int status;
	int fd;
	fd = (int)damepuerto232(com);
	if (ioctl(fd, TIOCMGET, &status) == -1) {
		perror("setRTS(): TIOCMGET");
    	v10log(LOGERROR, "ERROR AL PONER DTR COM %d VALOR %d\n", com, valor);
		return;
	}
	if (valor)
		status |= TIOCM_DTR; else
		status &= ~TIOCM_DTR;
	if (ioctl(fd, TIOCMSET, &status) == -1) {
		perror("setRTS(): TIOCMSET");
    	v10log(LOGERROR, "ERROR AL PONER DTR COM %d VALOR %d\n", com, valor);
		return ;
	}
    v10log(LOGNORMAL, "PONIENDO DTR COM %d VALOR %d\n", com, valor);
	return;

}

void STDponrts232(int com, int valor) 
{
	int status;
	int fd;
	fd = (int)damepuerto232(com);
	if (ioctl(fd, TIOCMGET, &status) == -1) {
		perror("setRTS(): TIOCMGET");
		return;
	}
	if (valor)
		status |= TIOCM_RTS; else
		status &= ~TIOCM_RTS;
	if (ioctl(fd, TIOCMSET, &status) == -1) {
		perror("setRTS(): TIOCMSET");
		return ;
	}
	return;
}


