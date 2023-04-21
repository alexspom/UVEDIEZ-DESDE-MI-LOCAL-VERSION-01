#include "infopc.h"

static char file[MAXPATH];
static int line;
         /* "file" y "line" permiten que el usuario mantenga un puntero
            de error consistente en un fichero y en una l¡nea. Es
	    responsabilidad del usuario el mantenimiento y actualizaci¢n
	    del puntero. */
void pon_puntero_error(char *fichero,int linea)
{
  strcpy(file,fichero);
  line=linea;
}

void mifinal(char *formato,...)
{
  va_list lista_param_variable;

  va_start(lista_param_variable,formato);
  vprintf(formato,lista_param_variable);
  exit(-1);
  va_end(lista_param_variable);
}

void vescribe_log(int visto,char *format,va_list arg)
{
	char buffer[MAXCADENA];
   if (maxnivellog<visto) return;
 	vsprintf(buffer,format,arg);
	printf("%s",buffer);
}

/*void escribe_log(int visto,char *format,...)
{
	char buffer[MAXCADENA];
	va_list arg;
	va_start(arg,format);
 	vsprintf(buffer,format,arg);
	printf("%s",buffer);
} */
void escribe_err(char *format,...)
{
	char buffer[MAXCADENA];
	va_list arg;
	va_start(arg,format);
 	vsprintf(buffer,format,arg);
	printf("%s",buffer);
}

horas llevocent()
{
  SYSTEMTIME time;
  GetLocalTime(&time);
  return((horas)time.wHour*360000+(horas)time.wMinute*6000+time.wSecond*100+time.wMilliseconds/10);
}

char *strcopia(char *dest,char *source,unsigned len)
{
  strncpy(dest,source,len-1);
  dest[len]=0;
  return(dest);
}

int es_blanco(char *dest)
{
  while (*dest) {
        if (*dest!=' ') return(0);
     }
  return(1);
}    
