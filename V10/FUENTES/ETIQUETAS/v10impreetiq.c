#include "v10etiqueta.h"

#define SINCONEX	0
#define TCP			1
#define RS232		2
#define TCPALIVE	3

static idrivers idriver;
static tcpipetiq tcpip;

void cargadriver(char *driver,idrivers *id)
{
    memset(id,0,sizeof(*id));
    if (strcmp(driver,"ZPL")==0) {
        pondriverzplii(id);
        return;
    }    
    if (strcmp(driver,"ZPV")==0) {
        pondriverzpliiv(id);
        return;
    }    
    if (strcmp(driver,"Z30")==0) {
        pondriverzplii300(id);
        return;
    }
    if (strcmp(driver,"SAT")==0) {
        pondriversato(id);
        return;
    }
    if (strcmp(driver,"TEC")==0) {
        pondrivertec(id);
        return;
    }
    if (strcmp(driver,"MET")==0 || strcmp(driver,"METO")==0) {
        pondrivermeto(id);
        return;
    }
    if (strcmp(driver,"METII")==0 || strcmp(driver,"METOII")==0) {
        pondrivermeto2(id);
        return;
	}
	if (strcmp(driver, "MP") == 0 || strcmp(driver, "MP") == 0) {
		pondrivermarkpoint(id);
        return;
	}
    final(("Tipo de impresora %s desconocido",driver));
}

char *vimpetiqcadena(char *driver,idatos **idatoetiq,char *cursor,char *fichgen,int *lon,char *params)
{
    v10cursors *curetiq=NULL;
    char *bufferetiq,*charsalida;
    cargadriver(driver,&idriver);
    curetiq=damevsqseguro(cursor);
    bufferetiq=vgeneraetiqueta(idatoetiq,curetiq,params);
    if (bufferetiq==NULL) return(NULL);
    charsalida=realizaimpresionetiq(*idatoetiq,&idriver,bufferetiq,fichgen,lon);
    free(bufferetiq);
    return(charsalida);
}

static void liberatcpip(void) {
	if (tcpip.pipeenv)  v10socklibera(tcpip.pipeenv);
	memset(&tcpip,0,sizeof(tcpip));
}


static int verificaimpresora(idrivers *id,int tipoconex,int puerto)
{
    int ret;	
	v10horas tconex;

	switch (tipoconex) {
		case SINCONEX:
			return(STTERMICAOK);
		case RS232:
			if (id->statusimpre==NULL) return(0); 
			while ((ret=id->statusimpre(id,puerto,NULL))==STTERMICAENCURSO) esperamensaje(100);
			return(ret);
		case TCP:
		case TCPALIVE:			
			if (tcpip.pipeenv==NULL) {
				tcpip.pipeenv=v10socknuevocliente(tcpip.ip,tcpip.puertotcpenv,0,4096,NULL,NULL,NULL,NULL,NULL);
				if (tcpip.pipeenv) {
					struct linger ling;
					tconex=damecent();					
					ling.l_onoff=1;
					ling.l_linger=35000;
					v10sockopt(tcpip.pipeenv,SO_LINGER,SOL_SOCKET,(char *)&ling,sizeof(ling));
				}
			}
			if (tcpip.pipeenv) {
				do  { 
					if (tcpip.pipeenv->status==STSOCKREADY) 
						return (STTERMICAOK);
					Sleep(10);
				} while (damecent()-tconex<=200);
			} 			

			return(STTERMICAAPAGADA);
	}  
	return(0);
}

#ifndef __LINUX__

void PrintError(DWORD dwError,LPCTSTR lpString)
{
#define MAX_MSG_BUF_SIZE 512
	TCHAR *msgBuf;
	DWORD	cMsgLen;

	cMsgLen=FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|
		FORMAT_MESSAGE_ALLOCATE_BUFFER|40,NULL,dwError,
		MAKELANGID(0,SUBLANG_ENGLISH_US),(LPTSTR)&msgBuf,
		MAX_MSG_BUF_SIZE,NULL);
	printf(TEXT("%s Error [%d]:: %s\n"),lpString,dwError,msgBuf);
	LocalFree(msgBuf);
#undef MAX_MSG_BUF_SIZE
}

int RawDataToPrinter(char *szPrinterName,char *lpData,int dwCount)
{
	HANDLE     hPrinter;
	DOC_INFO_1 DocInfo;
	DWORD      dwJob;
	DWORD      dwBytesWritten;

	// Need a handle to the printer.
	if (!OpenPrinter(szPrinterName,&hPrinter,NULL)) {
		PrintError(GetLastError(),TEXT("OpenPrinter"));
		return FALSE;
	}

	// Fill in the structure with info about this "document."
	DocInfo.pDocName=TEXT("My Document");
	DocInfo.pOutputFile=NULL;
	DocInfo.pDatatype=TEXT("RAW");
	// Inform the spooler the document is beginning.
	if ((dwJob=StartDocPrinter(hPrinter,1,(LPBYTE)&DocInfo))==0) {
		PrintError(GetLastError(),TEXT("StartDocPrinter"));
		ClosePrinter(hPrinter);
		return FALSE;
	}
	// Start a page.
	if (!StartPagePrinter(hPrinter)) {
		PrintError(GetLastError(),TEXT("StartPagePrinter"));
		EndDocPrinter(hPrinter);
		ClosePrinter(hPrinter);
		return FALSE;
	}
	// Send the data to the printer.
	if (!WritePrinter(hPrinter,lpData,dwCount,&dwBytesWritten)) {
		PrintError(GetLastError(),TEXT("WritePrinter"));
		EndPagePrinter(hPrinter);
		EndDocPrinter(hPrinter);
		ClosePrinter(hPrinter);
		return FALSE;
	}
	// End the page.
	if (!EndPagePrinter(hPrinter)) {
		PrintError(GetLastError(),TEXT("EndPagePrinter"));
		EndDocPrinter(hPrinter);
		ClosePrinter(hPrinter);
		return FALSE;
	}
	// Inform the spooler that the document is ending.
	if (!EndDocPrinter(hPrinter)) {
		PrintError(GetLastError(),TEXT("EndDocPrinter"));
		ClosePrinter(hPrinter);
		return FALSE;
	}
	// Tidy up the printer handle.
	ClosePrinter(hPrinter);
	// Check to see if correct number of bytes were written.
	if (dwBytesWritten!=dwCount) {
		printf(TEXT("Wrote %d bytes instead of requested %d bytes.\n"),dwBytesWritten,dwCount);
		return FALSE;
	}
	return TRUE;
}
#endif

int vimprimeetiqueta(char *driver,idatos **idatoetiq,char *cursor,char *fichgen,char *salida,int verificastatus,
					 int tipoconex,char *dirip,int puerto,int velocidad,int numetiq,char *msjerror,char *params)
{
    char *charsalida;
    FILE *fsalida=NULL;
    int lon,ret=0;
	static int final;
	int esred=0;
	esred=strstr(salida,"\\http")==NULL?0:1;
	switch (tipoconex) {
		case SINCONEX:
			break;
		case TCP:
		case TCPALIVE:
			// si hay un socket abierto a esa dir/puerto, lo reaprovecho
			if (tcpip.pipeenv) {
				char mipuerto[MAXCADENA]="";
				ltoa(puerto,mipuerto,10);
				if (tcpip.pipeenv->status!=STSOCKREADY || 
					(strcmp(tcpip.ip,dirip) || strcmp(tcpip.puertotcpenv,mipuerto))) {
					liberatcpip();			
				} else break;
			}			
			strcpy(tcpip.ip,dirip);
			ltoa(puerto,tcpip.puertotcpenv,10);			
			break;
		case RS232:
			initpuerto232(puerto,velocidad,NOPARITY,8,ONESTOPBIT);
	}
    if (!es_blanco(salida)) {
        if (idriver.abre) idriver.abre(&idriver,salida,&fsalida);
		else if (esred==0)    {
			fsalida = fopen(salida, "wb");
			if (fsalida == NULL) return(-1);
		}
    }
	while (numetiq--) {
        while (verificastatus || tipoconex==TCP || tipoconex==TCPALIVE ) {
            int ret;
            ret=verificaimpresora(&idriver,tipoconex,puerto);
			if (ret==STTERMICAAPAGADA) {
				if (tipoconex==TCP || tipoconex==TCPALIVE) {
					sprintf(msjerror,"No puedo conectarme por TCPIP a impresora %s y puerto %s",tcpip.ip,tcpip.puertotcpenv);			
					liberatcpip();
				}
				if (tipoconex==RS232) {
					sprintf(msjerror,"No puedo conectarme por 232 a puerto %d",puerto);			
					cierrapuerto232(puerto);
				}
				v10log(LOGWARNING,"%s",msjerror);
				return(-1);
			}
            if (ret!=STTERMICAOK) {
                sprintf(msjerror,"vimprimeetiqueta: No puedo imprimir etiqueta a driver %s puerto %d error %d\n",driver,puerto,ret);
            	v10log(LOGWARNING,"%s",msjerror);			
			} else break;
        }
        charsalida=vimpetiqcadena(driver,idatoetiq,cursor,fichgen,&lon,params);
        if (charsalida==NULL) {
            ret=-1;
            break;
        }

		if (fsalida) {
			fwrite(charsalida,1,lon,fsalida);
			
		}
		if (esred) RawDataToPrinter(salida,charsalida,lon);
		if (tipoconex==TCP || tipoconex==TCPALIVE) v10sockescribe(tcpip.pipeenv,charsalida,lon);
		if (tipoconex==RS232) escribebuffer232(puerto,charsalida,lon);        
		free(charsalida);
    }
    if (fsalida) {
        if (idriver.cierra) idriver.cierra(&idriver,&fsalida);
           else             fclose(fsalida);
    }

	if (tipoconex==TCP) liberatcpip();
	if (final==0) {	atexit(liberatcpip); final=1; }
    if (tipoconex==RS232) cierrapuerto232(puerto);
    return(ret);
}