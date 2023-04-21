#include "eos.h"


int dame232(int port)
{
    static char buffer[MAXCADENA],*ptr=buffer;
#ifdef __WIN32__
    static DWORD hay;
    int leer;
#else
    static int hay;
#endif
    BOOL ret;
    HANDLE hp=damepuerto232(port);
    if (hay) {
        hay--;
        return(*ptr++);
    }
    ptr=buffer;
#ifdef __WIN32__
    if ((leer=haycar232(port))==0) return(-1);
    ret=ReadFile(hp,buffer,leer,&hay,NULL);
    if (ret==FALSE) {
        ret=GetLastError();
        escribe_log(LOGERROR,"Error %d en Read File\n",ret);
#endif
#ifndef __WIN32__
    ret=read(hp, buffer, MAXCADENA);
    if (ret>=0) {
        hay=ret;
    }
    else {
#endif
#ifdef __LINUX__
         if (errno=!11 & errno!=0) escribe_log(LOGERROR,"Error en Read File: %d %s %d \n", ret, strerror(errno), errno);
//          else escribe_log(LOGDEBUG,"Error en Read File: %d %s %d \n", ret, strerror(errno), errno);
#endif
#ifdef __NETOS__
		ret=getErrno();
#endif
        return(-1);
    }
    if (hay) {
        hay--;
        return(*ptr++);
    }
    return(-1);
}

void reset232(int port)
{
#ifdef __LINUX__
	if (port<MAXPORTEAL) {
        tcflush(puerto232[port], TCIOFLUSH);//limpia la linea
        close (puerto232[port]);
        initpuerto232(port,BAUDRATE,NOPARITY,8,ONESTOPBIT);
	}
#endif
}

