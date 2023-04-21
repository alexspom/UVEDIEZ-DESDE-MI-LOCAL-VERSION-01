/*
* Módulo : V10PUNTEROS.C
* Objeto:  Virtualiza las funciones de presentacion para poder definir diferentes drivers de presentacion
*            Previstos:
*               Windows
*                Texto curses linux
*                Web
*                Telnet
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

 
 
int dummy(void)
{
   return 0;
}

int (*confirmasn)(int x,int y,char *cadena)=STDconfirmasn;
void (*vmensajefm)(int x,int y,char *cadena,va_list arg)=STDvmensajefm;


void (*fgotoxy)(int cx,int cy)=STDfgotoxy;
void (*v10error)(char *formato,va_list lista_param_variable,short salir)=STDv10error;
int (*tecla)(void)=STDtecla;
int (*encolatecla)(int valor)=STDencolatecla;
int (*llselecciona)(void *s)=(void *)STDllselecciona;
void (*pintapaginabloque)(void *s,int resaltado)=(void *)dummy;
int (*pushtecla)(int key)=STDpushtecla;
int(*reposicionaraton)(void *s) = (void *)STDreposicionaraton;
void(*lpresenta)(void *, int, int) = (void *)STDlpresenta;
 
void(*muestradialog)(void *vi, int guarda) = (void *)STDmuestradialog;
void(*actualizadialog)(void *v) = (void *)STDactualizadialog;
int(*blinput)(void *vi) = (void *)STDblinput;
int(*reposicionadialograton)(void *vi) = (void *)STDreposicionadialograton;

int (*initpuerto232)(int com,int velocidad,int paridad,int bits,int parada)=STDinitpuerto232;
void (*estado232)(int puerto,long *velocidad,int *paridad,int *parada,int *datos)=STDestado232;
void (*encolach232)(int com,int ch)=STDencolach232;
void (*encolaecad232)(int com,char *cadena)=STDencolaecad232;
int (*haycar232)(int com)=STDhaycar232;
int (*damecar232)(int com)=STDdamecar232;
void (*ponst232)(int com,long velocidad,int paridad,int stop,int bits)=STDponst232;
void (*printf232)(int com,char *format,...)=STDprintf232;
void (*protocolo232)(int port,int xon) = STDprotocolo232;
void (*pondtr232)(int com,int valor)=STDpondtr232;
void (*ponrts232)(int com,int valor) = STDponrts232;
void (*cierrapuerto232)(int com)=STDcierrapuerto232;
void (*fin232)(void)=STDfin232;
DWORD  (*escribebuffer232)(int com,void *msg, int tam)=STDescribebuffer232;
char *(*damehostname)(void)=STDnombreordenador;




