/****
* VDFORTRIGPROC.C
*                                                    
* Propósito: Triggers de manejo de procesos y tareas                                                     
*                                                                              
*                                                                              
* Autor  : FGS                                                          
* Fecha  : 28-04-2008                                                         
******
*  Modificaciones:
****/

#include "vd.h"


VDEXPORT int vdlanzaproceso(char *cadenaexec,int sincrono,long timeout,char *msjerror)
{
#ifndef __LINUX__	
    STARTUPINFO si; 
    PROCESS_INFORMATION pi;
    DWORD stespera;
    LPVOID lpMsgBuf;
    DWORD FlagsMens = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
    
    memset(&pi, 0, sizeof(pi));
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si); 
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOW;
    
    if(CreateProcess( NULL,(LPSTR)cadenaexec,NULL,NULL,FALSE, 0,NULL,NULL,&si,&pi )==0) {
        FormatMessage(FlagsMens,NULL,GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf,0,NULL );
        sprintf(msjerror,"vdlanzaproceso: Error en CREATEPROCESS \'%s\'\n"\
            "                      %s",cadenaexec,lpMsgBuf);
        v10log(LOGERROR,"%s",msjerror);
        LocalFree(lpMsgBuf);
        return(-1);
    }
    
    if (!sincrono) WaitForSingleObject( pi.hProcess, 0 );
    else {
        if (timeout==0) WaitForSingleObject( pi.hProcess, INFINITE );
        else {
            stespera=WaitForSingleObject( pi.hProcess, timeout * 1000 ); // en milisegundos
            if(stespera==WAIT_TIMEOUT) {
                if (TerminateProcess(pi.hProcess,0)==0) {
                    FormatMessage(FlagsMens,NULL,GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf,0,NULL );
                    sprintf(msjerror,"vdlanzaproceso: Error en TERMINATEPROCESS \'%s\'\n"\
                        "                      %s",cadenaexec,lpMsgBuf);
                    v10log(LOGERROR,msjerror);
                    LocalFree(lpMsgBuf);
                    return(-1);
                }
            }
        }        
    }
#endif	
    return(0);
}


static int vdlanzaprocesobloque(bloques *b,char *cadenaexec,int sincrono,long timeout) {
    int ret;
    char msjerror[MAXCADENA]="";
    
    ret=vdlanzaproceso(cadenaexec,sincrono,timeout,msjerror);    
    if (ret) ponerrorbloque(b,msjerror); 
    return(ret);
}


VDEXPORT int flanzaprocesosync(bloques *b,ftrigers *ft) {
    long timeout=0; // espera en segundos al proceso
    char cadenaexec[MAXCADENA]="";
    
    if (ft->nparam<2) {
        ponerrorbloque(b,"Trigger FLANZAPROCESOSYNC necesita 2 parámetros:\n LINEA DE COMANDO Y TIMEOUT");
        return(-1);
    }
    
    dameparametro(b,ft,0,V10CADENA,cadenaexec);
    dameparametro(b,ft,1,V10LONG,&timeout);
    return(vdlanzaprocesobloque(b, cadenaexec, 1, timeout));
}


VDEXPORT int flanzaproceso(bloques *b,ftrigers *ft) {  
    char cadenaexec[MAXCADENA]="";
    
    if (ft->nparam<1) {
        ponerrorbloque(b,"Trigger FLANZAPROCESO necesita 1 parámetro:\n LINEA DE COMANDO");
        return(-1);
    }
    
    dameparametro(b,ft,0,V10CADENA,cadenaexec);
    return(vdlanzaprocesobloque(b, cadenaexec, 0, 0));
}


VDEXPORT int flanzatareassync(bloques *b,ftrigers *ft) {
    int nivellog;
    long timeout=0; // espera en segundos al proceso
    char listatareas[LPROCESO]="",fichlog[MAXPATH]="";
    char cadenaexec[MAXCADENA]="";
    char conexion[MAXCADENA]="";

    if (ft->nparam<4) {
        ponerrorbloque(b,"Trigger FLANZATAREASYNC necesita 4 parámetros:\n LISTA DE TAREA, FICHERO DE LOG, NIVEL LOG Y TIMEOUT EN SEG.");
        return(-1);
    }
    
    dameparametro(b,ft,0, V10CADENA, listatareas);    
    dameparametro(b,ft,1, V10CADENA, fichlog);
    dameparametro(b,ft,2, V10LONG,   &nivellog); 
    dameparametro(b,ft,3, V10LONG,    &timeout);
    
    sprintf(conexion,"%s/%s",ORAUSR,ORAPWD);
    if (strlen(ORADB)>0) {
        strcat(conexion,"@");
        strcat(conexion,ORADB);
    }

    sprintf(cadenaexec,"VDEXEC.EXE -OU%s -LN%s -LM%d %s ",conexion,fichlog,nivellog,listatareas);  
    return(vdlanzaprocesobloque(b, cadenaexec, 1, timeout));  
}


VDEXPORT int flanzatareas(bloques *b,ftrigers *ft) {
    int nivellog;
    char listatareas[MAXCADENA]="",fichlog[MAXPATH]="";
    char cadenaexec[MAXCADENA]="";
    char conexion[MAXCADENA]="";
    
    if (ft->nparam<3) {
        ponerrorbloque(b,"Trigger FLANZATAREA necesita 3 parámetros:\n LISTA DE TAREAS, FICHERO DE LOG Y NIVEL LOG");
        return(-1);
    }
    
    dameparametro(b,ft,0, V10CADENA, listatareas);    
    dameparametro(b,ft,1, V10CADENA, fichlog);
    dameparametro(b,ft,2, V10LONG, &nivellog); 
    
    sprintf(conexion,"%s/%s",ORAUSR,ORAPWD);
    if (strlen(ORADB)>0) {
        strcat(conexion,"@");
        strcat(conexion,ORADB);
    }

    sprintf(cadenaexec,"VDEXEC.EXE -OU%s  -LN%s -LM%d %s",conexion,fichlog,nivellog,listatareas);  
    return(vdlanzaprocesobloque(b, cadenaexec, 0, 0));  
}