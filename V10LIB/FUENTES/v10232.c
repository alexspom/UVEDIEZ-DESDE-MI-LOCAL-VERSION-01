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


static HANDLE port232[MAXPUERTOS232];
static int init232;


void STDfin232(void)
{
  int i;
  for (i=0;i<MAXPUERTOS232;i++) {
      if (port232[i] && port232[i]!=INVALID_HANDLE_VALUE) {
		  FlushFileBuffers(port232[i]);
		  CloseHandle(port232[i]);
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
		FlushFileBuffers(port232[com]);
		CloseHandle(port232[com]);
        port232[com]=0;
	}
}

int STDinitpuerto232(int com,int velocidad,int paridad,int bits,int parada)
{
  COMMTIMEOUTS cm;
  DCB dcb;
  int ret;
  char nombre[12];
  if (init232==0) {
     init232=1;
     atexit(fin232);
   }
  sprintf(nombre,"\\\\.\\COM%d",com+1);
  port232[com]=CreateFile(nombre,GENERIC_WRITE| GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
  if (port232[com]==INVALID_HANDLE_VALUE) {
	  port232[com]=0;
	  return(1);
  }
  memset(&cm,0,sizeof(cm));
  ret=SetCommTimeouts(port232[com],&cm);
  if (ret==0) {
      ret=GetLastError();
      v10log(LOGERROR,"En puerto %d error %d al hacer SetCommTimeouts\n",com,ret);
  }
  ret=GetCommState(port232[com],&dcb);
  if (ret==0) {
      ret=GetLastError();
      v10log(LOGERROR,"En puerto %d error %d al hacer GetCommState\n",com,ret);
  } 
  dcb.fDtrControl=DTR_CONTROL_DISABLE;
  dcb.fOutxCtsFlow=0;
  dcb.fOutxDsrFlow=0;
  dcb.BaudRate=velocidad;
  dcb.ByteSize=(char)bits;
  dcb.Parity=(char)paridad;
 // dcb.StopBits = (char)parada;
  ret=SetCommState(port232[com],&dcb);
  if (ret==0) {
      ret=GetLastError();
      v10log(LOGERROR,"En puerto %d error %d al hacer SetCommState\n",com,ret);
  }
  SetupComm(port232[com],10000,10000);
  return(0);
}

void STDestado232(int puerto,long *velocidad,int *paridad,int *parada,int *datos)
{
  DCB dcb;
  GetCommState(port232[puerto],&dcb);
  if (velocidad) *velocidad=dcb.BaudRate;
  if (paridad) *paridad=dcb.Parity;
  if (parada) *parada=dcb.StopBits;
  if (datos) *datos=dcb.ByteSize;
}

void trataerror232(int com)
{
  DWORD err;
  COMSTAT cs;
  err=GetLastError();
  v10log(LOGERROR,"Error %d escribiendo en puerto %d\n",err,com);
  ClearCommBreak(port232[com]);
  ClearCommError(port232[com],&err,&cs);
}

void STDencolach232(int com,int ch)
{
  DWORD escrito;
  char c;
  if (port232[com]==0) return;
  c=(char)ch;
  if (WriteFile(port232[com],&c,1,&escrito,NULL)==FALSE) trataerror232(com);
}

void STDencolaecad232(int com,char *cadena)
{
  DWORD escrito;
  if (port232[com]==0) return;
  if (WriteFile(port232[com],cadena,strlen(cadena),&escrito,NULL)==FALSE) trataerror232(com);
}

DWORD STDescribebuffer232(int com,void *msg, int tam)
{
  DWORD escrito=0;
  if (port232[com]==0) return(escrito);
  if (WriteFile(port232[com],msg,tam,&escrito,NULL)==FALSE) trataerror232(com);
  return(escrito);
}    

int STDhaycar232(int com)
{
  DWORD error;
  COMSTAT stat;
  if (port232[com]==0) return(0);
  ClearCommError(port232[com],&error,&stat);
  return(stat.cbInQue);
}

int STDdamecar232(int com)
{
  DWORD leido;
  char ch;
  if (port232[com]==0) return(-1);
  if (haycar232(com)==0) return(-1);
  if (ReadFile(port232[com],&ch,1,&leido,NULL)==FALSE) {
     trataerror232(com);
     return(-1);
   }
  if (leido==0) return(-1);
  return(ch);
}

void STDponst232(int com,long velocidad,int paridad,int stop,int bits)
{
  DCB dcb;
  if (port232[com]==0) return;
  GetCommState(port232[com],&dcb);
  dcb.BaudRate=velocidad;
  dcb.ByteSize=(char)bits;
  dcb.Parity=(char)paridad;
  dcb.StopBits=(char)stop;
  SetCommState(port232[com],&dcb);
}

void STDprintf232(int com,char *format,...)
{
  va_list arg;
  char *donde;
  if (port232[com]==0) return;
  va_start(arg,format);
  donde=calloc(1,MAXCADENA);
  vsprintf(donde,format,arg);
  encolaecad232(com,donde);
  free(donde);
  va_end(arg);
}

void STDprotocolo232(int port,int xon)
{
  DCB dcb;
  if (port232[port]==NULL) return;
  GetCommState(port232[port],&dcb);
  dcb.fOutX=xon;
  dcb.fInX=xon;
  SetCommState(port232[port],&dcb);
}


void STDpondtr232(int com,int valor) 
{
    DCB dcb;
    HANDLE mipuerto;
    int ret;
    mipuerto = damepuerto232(com);
    ret = GetCommState(mipuerto,&dcb);
    dcb.fDtrControl = valor;
    ret = SetCommState(mipuerto,&dcb);
}

void STDponrts232(int com,int valor) 
{
    DCB dcb;
    HANDLE mipuerto;
    int ret;
    mipuerto = damepuerto232(com);
    ret = GetCommState(mipuerto,&dcb);
    dcb.fRtsControl = valor;
    ret = SetCommState(mipuerto,&dcb);
}

