/*
* Módulo : EOSWIN.C
* Objeto: Funciones especificas de windows para displays de la gama EOS
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-12-2007

* MODIFICACIONES
* --
*/
#include "eos.h"


int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine)(void*), void *arg)
{
  HANDLE ret;
  ret=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE )start_routine,arg,0,thread);
  if (ret!=NULL) {
     CloseHandle(ret);
     return(0);
   }
  return(GetLastError());
}

int nanosleep(const struct timeval *reqt,struct timeval *remt)
{
  Sleep(reqt->tv_sec*1000+reqt->tv_usec/1000);
  return(0);
}

int usleep(int useconds)
{
  Sleep(useconds/1000);
  return(0);
}


