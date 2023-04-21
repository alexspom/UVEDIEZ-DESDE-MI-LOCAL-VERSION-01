/*
* Módulo : V10TIPOS.C
* Objeto:  Funciones definidas sobre tipos V10
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"
#define LENGINDEF 30

int tamv10tipo(int tipo,int lon)
{
   switch (tipo) {                         
       case V10INT:     
       case V10UINT:    return(sizeof(int));   
       case V10SHORT:   
       case V10USHORT:  return(sizeof(short));
       case V10LONG:    
       case V10ULONG:   return(sizeof(long));
       case V10FLOAT:   return(sizeof(float));
       case V10DOUBLE:  return(sizeof(double));
       case V10CHAR:
       case V10BYTE:    return(sizeof(char));
       case V10CADENA:  return(lon);
       case V10FECHA:   return(sizeof(v10dates));
       case V10HORA:    return(sizeof(v10horas));
	   case V10DATE:    return(lon);
	   case V10RAW:     return(lon);
       default:final(("Tipo %d no definido",tipo));
    }
  return(-1);
}

int esv10tiponum(int tipo)
{
	switch (tipo) {
	   case V10INT:
	   case V10UINT:
	   case V10USHORT:
	   case V10LONG:
	   case V10ULONG:
	   case V10FLOAT:
	   case V10DOUBLE:
	   case V10BYTE: return(1);
	}
	return(0);
}


void v10tipo2a(void *dato,int tipo,int lvar,int formato,int dec,char *donde,int edit)
{
  switch(tipo) {
     case V10INT:    {int valor=*(int *)dato;
                      v10lformat(valor,lvar?lvar:LENGINDEF,formato,' ',donde,dec);
                      break;
					 }
    case V10UINT:  {unsigned int valor=*(unsigned int *)dato;
                    v10uformat(valor,lvar?lvar:LENGINDEF,formato,' ',donde,dec);
                    break;
				   }
    case V10SHORT: {int valor=*(short *)dato;
                    v10lformat(valor,lvar?lvar:LENGINDEF,formato,' ',donde,dec);
                    break;
				   }
    case V10USHORT:{unsigned int valor=*(unsigned short *)dato;
                    v10uformat(valor,lvar?lvar:LENGINDEF,formato,' ',donde,dec);
                    break;
				   }
    case V10LONG  :{long valor=*(long *)dato;
                   v10lformat(valor,lvar?lvar:LENGINDEF,formato,' ',donde,dec);
                   break;}
    case V10ULONG :{unsigned long valor=*(unsigned long *)dato;
                    v10uformat(valor,lvar?lvar:LENGINDEF,formato,' ',donde,dec);
                    break;
				   }
    case V10FLOAT :{float valor=*(float *)dato;
                    v10dformat(valor,dec,lvar?lvar:LENGINDEF,formato,' ',donde);
                    break;
				   }
    case V10DOUBLE:{double valor=*(double *)dato;
                    v10dformat(valor,dec,lvar?lvar:LENGINDEF,formato,' ',donde);
                    break;
				   }
    case V10CHAR:  *donde=*(char *)dato;
                   donde[1]=0;
                   break;
    case V10BYTE:  {char valor=*(char *)dato;
                    v10lformat(valor,lvar?lvar:LENGINDEF,formato,' ',donde,dec);
                    break;
				   }
    case V10CADENA:if (formato&FORMATONULL) break;
                   if (donde!=dato) strcpy(donde,dato);
                   switch (formato&(FORMATOUPPER|FORMATOLOWER)) {
                      case FORMATOUPPER:strmay(donde);
                                        break;
                      case FORMATOLOWER:strmin(donde);
                                        break;
				   }
                   break;
    case V10FECHA :{v10dates valor=*(v10dates *)dato;                           
                 if (formato & F4ANO) jul2a(valor,"DD-MM-Y.",donde);
                    else             jul2a(valor,"DD-MM-YY",donde);
                break;
              }
    case V10HORA  :
                cent2a(*(v10horas *)dato,0,':',donde);
                break;
   default    : final(("Tipo %d no definido",tipo));
                break;
            }
  if (esv10tiponum(tipo) && edit) eliminasp(donde);
  if (lvar && edit) pad(donde,lvar);
}

int a2v10tipo(void *dato,int tipo,int formato,int dec,char *donde)
{
  int ret = 1;

  switch(tipo) {   
    case V10INT   :*(int *)dato=(int)v10lval(donde,formato,dec);
                   break;
    case V10UINT   :*(unsigned int *)dato=(unsigned int)v10uval(donde,formato,dec);
                   break;
    case V10SHORT:  *(short *)dato=(short)v10lval(donde,formato,dec);
                   break;
    case V10USHORT:*(unsigned short *)dato=(unsigned short)v10uval(donde,formato,dec);
                   break;
    case V10LONG:  *(long *)dato=v10lval(donde,formato,dec);
                   break;
    case V10ULONG :*(unsigned long *)dato=v10uval(donde,formato,dec);
                   break;
    case V10FLOAT :*(float *)dato=(float)v10dval(donde,formato);
                   break;
    case V10DOUBLE:*(double *)dato=v10dval(donde,formato);
                   break;
    case V10CHAR:  *(char *)dato=*donde;
                   break;                
    case V10BYTE:  *(char *)dato=(char)v10lval(donde,formato,dec);
                   break;
    case V10CADENA:strcpy((char *)dato,donde);
                   break;
    case V10FECHA :{v10dates auxun=a2jul(1,donde);
                    if (auxun!=(unsigned)-1) *(v10dates *)dato=auxun;
                    if (auxun==(unsigned)-1) ret=0;
                    break;
                   }
    case V10HORA : {v10horas auxlon=a2cent(donde);
                    *(v10horas *)dato=auxlon;
                    break;
                   }
   default    :final(("Tipo %d no definido",tipo));
               break;
  }
  return(ret);
}

int comparav10tipo(void *t1,void *t2,int tipo)
{
  switch(tipo) {
    case V10INT     :return(*(int *)t1-*(int *)t2);
    case V10UINT    :return(*(unsigned int *)t1>*(unsigned int *)t2?1:*(unsigned int *)t1==*(unsigned int *)t2?0:-1);
    case V10SHORT   :return(*(short *)t1-*(short *)t2);
    case V10USHORT  :return(*(unsigned short *)t1>*(unsigned short *)t2?1:*(unsigned short *)t1==*(unsigned short *)t2?0:-1);
    case V10LONG    :return(*(long *)t1>*(long *)t2?1:*(long *)t1==*(long *)t2?0:-1);
    case V10ULONG   :return(*(unsigned long *)t1>*(unsigned long *)t2?1:*(unsigned long *)t1==*(unsigned long *)t2?0:-1);
    case V10FLOAT   :return(*(float *)t1>*(float *)t2?1:*(float *)t1==*(float *)t2?0:-1);
    case V10DOUBLE  :return(*(double *)t1>*(double *)t2?1:*(double *)t1==*(double *)t2?0:-1);
    case V10BYTE:
    case V10CHAR    :return(*(char *)t1>*(char *)t2?1:*(char *)t1==*(char *)t2?0:-1);
    case V10CADENA  :return(strcmp(t1,t2));
    case V10FECHA   :return(*(v10dates *)t1>*(v10dates *)t2?1:*(v10dates *)t1==*(v10dates *)t2?0:-1);
    case V10HORA    :return(*(v10horas *)t1>*(v10horas *)t2?1:*(v10horas *)t1==*(v10horas *)t2?0:-1);
    default         :final(("Tipo %d no definido",tipo));
   }
  return(0);
}

void copiav10tipo(void *t1,void *t2,int tipo,int lvar)
{
  memcpy(t1,t2,tamv10tipo(tipo,lvar));
}

int esnulov10tipo(void *var,int tipo)
{
  switch (tipo) {                                  
           case V10INT:     return (*(int *)var==0);
           case V10UINT:    return (*(unsigned int *)var==0);
           case V10SHORT:   return (*(short *)var==0);
           case V10USHORT:  return (*(unsigned short *)var==0);
           case V10LONG:    return (*(long *)var==0);
           case V10ULONG:   return (*(unsigned long *)var==0);
           case V10FLOAT:   return (*(float *)var==0.0);
           case V10DOUBLE:  return (*(double *)var==0.0);
           case V10CHAR:
           case V10BYTE:    return (*(char *)var==0);
           case V10FECHA:   return (*(v10dates *)var==0);
           case V10HORA:    return (*(v10horas *)var==0);
           case V10CADENA:  return(es_blanco(var));
           default:     final(("Tipo %d no definido",tipo));
        }
   return(-1);
}
