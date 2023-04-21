/****
* VDCR10EXPORTAINFORME.C
*                                                    
* Propósito: Exporta un informe a fichero                                                   
*                                                                              
*                                                                              
* Autor  : FGS                                                          
* Fecha  : 12-05-2008                                                         
******
*  Modificaciones:
****/


#include "vdcr10.h"

static void creaproceso(char *ficheroexport,char *ejecutable,char *msjerror) {
    char cadenaexec[MAXPATH]=""; 
   /*STARTUPINFO si; 
    PROCESS_INFORMATION pi;
    LPVOID lpMsgBuf;   
    DWORD FlagsMens = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
    
    memset(&pi, 0, sizeof(pi));
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si); 
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOW;
    */
    sprintf(cadenaexec,"start %s %s",ejecutable,ficheroexport);
    system(cadenaexec);
    /*
    if(CreateProcess( NULL,cadenaexec,NULL,NULL,FALSE, 0,NULL,NULL,&si,&pi )==0) {
        FormatMessage(FlagsMens,NULL,GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf,0,NULL );
        sprintf(msjerror,"creaproceso: Error en CREATEPROCESS \'%s\'\n"\
                "                      %s",cadenaexec,lpMsgBuf);
        LocalFree(lpMsgBuf);
    }*/
}

static void damedllformato(char *fichero, char *dllformato, char *ejecutable ) {

    memset(dllformato,0,sizeof(dllformato));
    memset(ejecutable,0,sizeof(ejecutable));    

    if (strstr( strmay(fichero), ".PDF" )) {
        strcpy(ejecutable,"AcroRd32.exe");    
        strcpy(dllformato,"u2fpdf");
        return;
    }
    if (strstr( strmay(fichero), ".XLS" )) {
        strcpy(ejecutable,"excel.exe");
        strcpy(dllformato,"crxf_xls.dll");
        return;
    }
    if (strstr( strmay(fichero), ".DOC" )) {
        strcpy(ejecutable,"winword.exe");
        strcpy(dllformato,"u2fwordw");
        return;
    }
    if (strstr( strmay(fichero), ".XML" )) {
        strcpy(ejecutable,"notepad.exe");
        strcpy(dllformato,"u2fxml");
        return;
    }
    if (strstr( strmay(fichero), ".HTM" )) {
        strcpy(ejecutable,"iexplorer.exe");
        strcpy(dllformato,"u2fhtml");
        return;
    }
}


int CR10exportainforme( cr10impresiones *imp, char *msjerror) {

    PEExportOptions  op;    
    UXDDiskOptions   diskop;
    char dllformato[MAXPATH]="";
    char ejecutable[MAXPATH]="";

    op.StructSize = sizeof (PEExportOptions); 
    op.formatType = PE_UNCHANGED;    
    op.destinationType = PE_UNCHANGED;
    op.formatOptions = 0;
    *op.formatDLLName = 0;
    op.destinationOptions = 0;
    op.nFormatOptionsBytes = 0;
    op.nDestinationOptionsBytes = 0;
    op.unicodeFormatOptions = PEFALSE;
    op.unicodeDestinationOptions = PEFALSE;
    
    damedllformato(imp->fichexport,dllformato,ejecutable);
    
    if (*dllformato==0) PEGetExportOptions ( imp->id, &op);
    else {
        diskop.structSize=sizeof (UXDDiskOptionsSize);        
        diskop.fileName=imp->fichexport;
        strcpy( op.formatDLLName, dllformato );
        op.formatType = 0;
        strcpy( op.destinationDLLName, "u2ddisk.dll" );
        op.destinationType = UXDDiskType;
        op.destinationOptions = &diskop;    
    }

    if( PEExportTo( imp->id,&op) == 0 ){
        sprintf(msjerror,"CR10exportainforme: Error al exportar informe %s a fichero %s\n", imp->informe,imp->fichexport );
        return(-1);
    }    

     return(0);
}




int CR10exportaeimprimeinforme( cr10impresiones *imp, char *msjerror) {

    int ret;
    char dllformato[MAXPATH]="";
    char ejecutable[MAXPATH]="";

    ret=CR10exportainforme(imp,msjerror);
    if (ret) return(ret);

    damedllformato(imp->fichexport,dllformato,ejecutable);
  
    PEEnableProgressDialog( imp->id, PEFALSE );
    
    // con TRUE hace una llamáda síncrona, esperando a que finalice de generar el informe
    // para continuar
   	ret = PEStartPrintJob( imp->id, TRUE );
    if( ret == 0 ){
        sprintf(msjerror,"CR10exportaeimprimeinforme: Error al exportar informe %s con driver %s\nError: %s\n", 
            imp->informe,dllformato,CR10error(imp,imp->id));
        return(-1);
    }

    v10log(LOGNORMAL,"CR10exportaeimprimeinforme: IMPRESO informe %s, exportado a fichero %s con driver\n",
            imp->informe,imp->fichexport,dllformato);

  
    if (*dllformato && *ejecutable && imp->abrirfichero==1) creaproceso(imp->fichexport,ejecutable,msjerror);

    return(0);
}