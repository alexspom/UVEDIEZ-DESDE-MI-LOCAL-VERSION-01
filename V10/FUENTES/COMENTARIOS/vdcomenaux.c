/****
* VDCOMENAUX.C
*                                                    
* Propósito: Funciones C para insercción,actualización y busqueda de comentarios                          
*                                                                              
* Autor  : FGS e ICC                                                           
* Fecha  : 13-11-2007                                                          
******
*  Modificaciones:
****/

#include "execproc/vdexec.h"

// muestra el log y asigna el mismo al mensaje de error pasado
// PARAM 1: (nivel) nivel de log
// PARAM 2: (comentario) puntero al mensaje de error
// PARAM 3: (formato) formato del mensaje
// PARAM 4: (...) lista de variables a mostrar en el mensaje
VDEXPORT void v10logcomen(int nivel, char *comentario, char *format,...) {
    char mensaje[MAXCADENA]="";
    va_list arg;

    va_start(arg,format);
    format=v10translate(format);
  
    memset(mensaje,0,sizeof(mensaje));
    vsprintf(mensaje,format,arg);
    if (comentario) strcopia(comentario, mensaje, strlen(mensaje));
    v10log(nivel,"%s",mensaje); 
    va_end(arg);

}

// inserta un comentario, en la transacción actual o una independiente
// PARAM 1: (relogin) 0 transacción actual, 1 una independiente
// PARAM 2: (codcomen) codigo de comentario del objeto
// PARAM 3: (tipocomen) tipo de comentario del objeto
// PARAM 4: (lincomen) linea de comentario a insertar del tipo y objeto, si objeto añade 1 a la última existente
// PARAM 5: (comentario) texto a insertar
// PARAM 6: (msjerror) captura mensajes de error durante la insercción
static int v10creacomen(char *tabla,int relogin, long codcomen,char *tipocomen,long lincomen,char *comentario,char *msjerror) {
  // llama a las 
  int ret;  
  vdplsqlcomens plsql;
 
  ret=PLSQLCOMENproccreacomen(tabla,codcomen,tipocomen,lincomen,comentario,relogin,&plsql);
  if (ret) {
    v10logcomen(LOGERROR,msjerror,"ERROR ORACLE devuelto al ejecutar PLSQLCOMENproccreacomen");
    return(ret);
  }

  memset(&plsql,0,sizeof(plsql));
  ret=PLSQLCOMENbuscadameret(&plsql);
  if (ret) {
    v10logcomen(LOGERROR,msjerror,"ERROR ORACLE devuelto al ejecutar PLSQLCOMENbuscadameret");
    return(ret);
  }

  if (plsql.ret) v10logcomen(LOGERROR,msjerror,plsql.msjerror);
  return(plsql.ret);
}



VDEXPORT int v10comen(char *tabla,long codcomen,char *tipocomen,long lincomen, char *comentario,char *msjerror) {
    
    if (lincomen==0) { // si no nos fuerza el número de línea, partimos por salto de línea
        char lineacomen[MAXCADENA]="",*ptr;
        int ret;

        while ((ptr=strchr(comentario,'\n'))) {
             strcopia(lineacomen,comentario,ptr-comentario);
             ret=v10creacomen(tabla,0,codcomen,tipocomen,lincomen,lineacomen,msjerror);
             if (ret) return(ret);
             if (strlen(ptr)>1) comentario=ptr+1;
             else return(ret);
        }
        if (strlen(comentario)>0) ret=v10creacomen(tabla,0,codcomen,tipocomen,lincomen,comentario,msjerror);
        return(ret);
    
    } else return(v10creacomen(tabla,0,codcomen,tipocomen,lincomen,comentario,msjerror));
}



VDEXPORT int v10comenrelogin(char *tabla,long codcomen,char *tipocomen,long lincomen, char *comentario,char *msjerror) {
  return(v10creacomen(tabla,1,codcomen,tipocomen,lincomen,comentario,msjerror));

}


VDEXPORT int v10damecomen(long codcomen,char *tipocomen,long lincomen,char *msjerror,vdcomens *com) {
 
  int ret;
  vdplsqlcomens plsql;

  ret=PLSQLCOMENbuscadamecomen(codcomen,tipocomen,lincomen,&plsql);
  if (ret) {
    v10logcomen(LOGERROR,msjerror,"ERROR ORACLE devuelto al ejecutar PLSQLCOMENbuscadamecomen");
    return(ret);
  }

  if (plsql.ret) v10logcomen(LOGERROR,msjerror,plsql.msjerror);
  else  strcopia(com->comentario,plsql.comentario,strlen(plsql.comentario));
  return(plsql.ret);
}


VDEXPORT int v10comenpropcadena(long codcomen,char *tipocomen,char *comentario) {
  int ret;
  vdplsqlcomens plsql;

  ret=PLSQLCOMENbuscacomenpropcadena(codcomen,tipocomen,&plsql);
  if (ret) {
    v10log(LOGERROR,"%s","v10comenpropcadena:ERROR ORACLE devuelto al ejecutar PLSQLCOMENbuscacomenpropcadena");
    return(ret);
  }

  ret=PLSQLCOMENbuscadameret(&plsql);
  if (ret) {
    v10log(LOGERROR,"%s","v10comenpropcadena: ERROR ORACLE devuelto al ejecutar PLSQLCOMENbuscadameret");
    return(ret);
  }

  if (plsql.ret==0) strcopia(comentario,plsql.comentario,strlen(plsql.comentario));
  return(plsql.ret);

}


VDEXPORT int v10comenpropentero(long codcomen,char *tipocomen,long *valor) {
  int ret;
  vdplsqlcomens plsql;
  vdplsqlcomens plsql2;
  
  ret=PLSQLCOMENbuscacomenpropentero(codcomen,tipocomen,&plsql);
  if (ret) {
    v10log(LOGERROR,"%s","v10comenpropentero: ERROR ORACLE devuelto al ejecutar PLSQLCOMENbuscacomenpropentero");
    return(ret);
  }

  ret=PLSQLCOMENbuscadameret(&plsql2);
  if (ret) {
    v10log(LOGERROR,"%s","v10comenpropentero: ERROR ORACLE devuelto al ejecutar PLSQLCOMENbuscadameret");
    return(ret);
  }

  if (plsql2.ret==0) *valor=plsql.valor;
  return(plsql2.ret);
}


// borra todos los comentarios de un objeto de un tipo determinado
// PARAM 1: (codcomen) codigo de comentario del objeto
// PARAM 2: (tipocomen) tipo de comentario del objeto
// PARAM 3: (msjerror) captura mensajes de error durante la operación
VDEXPORT int v10deletecomenportipo(long codcomen, char *tipocomen,char *msjerror) {
  int ret;
  vdplsqlcomens plsql;

    
  ret=PLSQLCOMENprocborracomenportipo(codcomen,tipocomen,&plsql);
  if (ret) {
    v10logcomen(LOGERROR,msjerror,"ERROR ORACLE devuelto al ejecutar PLSQLCOMENprocborracomenportipo");
    return(ret);
  }

  memset(&plsql,0,sizeof(plsql));
  ret=PLSQLCOMENbuscadameret(&plsql);
  if (ret) {
    v10logcomen(LOGERROR,msjerror,"ERROR ORACLE devuelto al ejecutar PLSQLCOMENbuscadameret");
    return(ret);
  }

  if (plsql.ret) v10logcomen(LOGERROR,msjerror,plsql.msjerror);
  return(plsql.ret);
}


// algoritmo que envía un correo con el comentario
VDEXPORT int vdcomencorreo(void *ptr,char *param) {
    int ret,prioridad;
    char msjerror[MAXCADENA]="",tipocorreo[LTIPOCORREO]="",asunto[LASUNTO]="",cprioridad[10]="",mensaje[MAXCADENA]="";
    vdcomens *com=ptr;

    piece(param,tipocorreo,"#",1); 
    piece(param,asunto,"#",2); 
    piece(param,cprioridad,"#",3); 

    if (*cprioridad==0) prioridad=3;
    else prioridad=atoi(cprioridad);

    sprintf(mensaje," <br>"\
                    " <b>Código de comentario:</b> %ld<br>"\
                    " <b>Tipo de comentario:</b> %s<br>"\
                    " <b>Línea de comentario:</b> %d<br><br>"\
                    " <b>Comentario:</b><br><br><i>%s</i>",com->codcomen,com->tipocomen,com->lincomen,com->comentario);
                      

    ret=vdcorreo(tipocorreo,asunto,mensaje,
                 "", // mime
                 "", // directorio del adjunto
                "", // nombre del fichero adunto
                prioridad,0,"",msjerror);
    if (ret) v10log(LOGERROR,"vdcomencorreo: Error %s al insertar correo en cola de envío de correos\n",msjerror);
    return(ret);

}

// algoritmo que envía un "net send" con el comentario
VDEXPORT int vdcomennetsend(void *ptr,char *param) {    
    vdcomens *com=ptr;
    char destino[MAXPATH]="",sentencia[MAXCADENA]="";

    piece(param,destino,"#",1); 
    sprintf(sentencia,"net send %s \"Mensaje V10: %s\"",destino,com->comentario);
    system(sentencia);
    return(0);
}


// Proceso que busca comentarios por notificar ('S' u otro ), los trata, y si ok, los deja en 'F' u otro
// Param 1. valor del campo Notificar; por defecto a 'S'
// Param 2. valor final del campo Notificar; por defecto a 'F'
// Param 3. valor final del campo Notificar si ha habido Eddor; por defecto a 'E'
VDEXPORT void vdprocesacomennotif(procesos *proceso)
{  
    int ret;  
    char pdtenotif[2]="",notif[2]="",errnotif[2]="";
    vdcomens com;
    
    piece(proceso->proc.param,pdtenotif,"#",1);
    if (*pdtenotif==0) *pdtenotif='S';
    piece(proceso->proc.param,notif,"#",2);
    if (*notif==0) *notif='F';
    piece(proceso->proc.param,errnotif,"#",3);
    if (*errnotif==0) *errnotif='E';
    
    if (COMbuscapornotificar(pdtenotif,&com)) return;
     
    do {
        v10log(LOGNORMAL,"%s","===================================================================================================\n");   
        v10log(LOGNORMAL,"vdprocesacomennotif: Tratando comentario a notificar de Codcomen: %ld, Tipo: %s, Línea: %d\n\tTexto: %s\n",
                                               com.codcomen,com.tipocomen,com.lincomen,com.comentario);
         
        ret=VDEXECejecuta(proceso,&com,"#","%s",com.tipocomen);
        if (ret)  {
            v10log(LOGERROR,"vdprocesacomennotif: ERROR Tratando comentario a notificar de Codcomen: %ld, Tipo: %s, Línea: %d\n\tTexto: %s\n",
                                                  com.codcomen,com.tipocomen,com.lincomen,com.comentario);
            rollback();
            strcpy(com.notificar,errnotif);
        } else {    
            strcpy(com.notificar,notif);      
            v10log(LOGNORMAL,"vdprocesacomennotif: Tratado con ÉXITO comentario a notificar de Codcomen: %ld, Tipo: %s, Línea: %d\n\tTexto: %s\n",
                                                  com.codcomen,com.tipocomen,com.lincomen,com.comentario);
        }
        
        ret=COMactualizanotificar(&com,0);
        if (ret) {
            v10log(LOGERROR,"vdprocesacomennotif: ERROR Actualizando campo notificar de comentario a valor %s\n",com.notificar);
            rollback();            
        } else commit();
    } while (!COMnextpornotificar(&com));
}

