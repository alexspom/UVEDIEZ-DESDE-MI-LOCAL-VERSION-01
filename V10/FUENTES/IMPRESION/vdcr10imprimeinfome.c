/****
* VDCR10IMPRIMEINFORME.C
*                                                    
* Propósito: Selecciona si procede, abre y establece la impresora para la impresión del informe                                                     
*                                                                              
*                                                                              
* Autor  : FGS                                                          
* Fecha  : 12-05-2008                                                         
******
*  Modificaciones:
****/


#include "vdcr10.h"
#include "vdimpresion.h"


#if defined (__cplusplus)
extern "C" // incrusto código C en C++
{
#endif

int CR10previsualizainforme(cr10impresiones *imp, char *msjerror )
{
    if (v10versionweb) {
        char nombre[MAXPATH];
        dameficheropdf("PREVISUAL",imp->fichexport,nombre);
        imp->abrirfichero=0;
        CR10exportainforme(imp,msjerror);
        strcpy(imp->fichexport,nombre);
        ponmensajepdf(imp->fichexport);
    } else {
	    PEOutputToWindow (imp->id,"VISOR DE INFORMES V10", CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
		    WS_MAXIMIZE|WS_VISIBLE | WS_THICKFRAME | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, 0 );
    }
    return(0);
}

int CR10pideimpresora(cr10impresiones *imp, char *msjerror ) 
{
    int ret = 0;
	PRINTDLG	wimpresoras;
	LPDEVMODE   modoimpresora;
	LPDEVNAMES  impresora;
	memset( &wimpresoras, 0, sizeof( PRINTDLG));
	wimpresoras.lStructSize = sizeof(PRINTDLG);
	ret = PrintDlg( &wimpresoras );
	if( ret ){
		modoimpresora   = (LPDEVMODE )GlobalLock( wimpresoras.hDevMode  );
		impresora       = (LPDEVNAMES)GlobalLock( wimpresoras.hDevNames );

        // asigna esta impresora al informe
		PESelectPrinter ( imp->id,  (LPSTR)impresora + impresora->wDriverOffset, 
									(LPSTR)impresora + impresora->wDeviceOffset, 
									(LPSTR)impresora + impresora->wOutputOffset,
									modoimpresora );
		GlobalUnlock( wimpresoras.hDevMode );
		GlobalFree  ( wimpresoras.hDevMode );
		GlobalUnlock( wimpresoras.hDevNames );
		GlobalFree  ( wimpresoras.hDevNames );
    } else {
        sprintf(msjerror,"CR10pideimpresora: Error al abrir cuadro de diálogo de selección de impresoras\nError: %s\n", CR10error(imp,imp->id));
	    return(-1);
    }
    ret = PEOutputToPrinter( imp->id, (short) imp->copias );
    if( ret == 0 ){
        sprintf(msjerror,"CR10pideimpresora: Error al asignar la salida a impresora seleccionada por cuadro de diálogo\nError: %s\n", CR10error(imp,imp->id));
	    return(-1);
    }
    return(0);
}

#define MAXWINIMPRE 4048

/*
typedef struct _PRINTER_INFO_2 {
  LPTSTR    pServerName;
  LPTSTR    pPrinterName;
  LPTSTR    pShareName;
  LPTSTR    pPortName;
  LPTSTR    pDriverName;
  LPTSTR    pComment;
  LPTSTR    pLocation;
  LPDEVMODE pDevMode;
  LPTSTR    pSepFile;
  LPTSTR    pPrintProcessor;
  LPTSTR    pDatatype;
  LPTSTR    pParameters;
  PSECURITY_DESCRIPTOR pSecurityDescriptor;
  DWORD     Attributes;
  DWORD     Priority;
  DWORD     DefaultPriority;
  DWORD     StartTime;
  DWORD     UntilTime;
  DWORD     Status;
  DWORD     cJobs;
  DWORD     AveragePPM;
} PRINTER_INFO_2, *PPRINTER_INFO_2; 

  */

int CR10asignaimpresora(cr10impresiones *imp,char *msjerror ) {

    int ret;
    DWORD lon,nbytes;
    char impdefecto[MAXWINIMPRE]="";
  	char            orientacion[MAXCADENA];
    HANDLE          himpre;
    HGLOBAL			miimpresora;
	DEVMODE        *modoimpresora;  
    PRINTER_INFO_2 *impreinfo; // informaciónw WIN32 sobre la impresora
    PRINTER_INFO_9 *impreinfo9; // informaciónw WIN32 sobre la impresora
    PRINTER_DEFAULTS printerdef={NULL,NULL,PRINTER_ACCESS_USE};

    // captura la impresora por defecto de equipo local
    if (!strcmp(imp->codimpre,PORDEFECTO)) {
        GetProfileString  ( "Windows", "Device", ",,,", impdefecto , MAXWINIMPRE );
        piece( impdefecto, imp->salidaimpresora, ",", 1);
    }
    // obtiene el manejador de la impresora
    if (OpenPrinter( imp->salidaimpresora, &himpre, &printerdef) == FALSE) {
		sprintf(msjerror,"CR10asignaimpresora: No se encuentra impresora %s\n",imp->salidaimpresora);
        return(-1);
	}
    // obtiene la longitud de la información de la impresora para reservar la memoria
    GetPrinter(himpre, 2, NULL, 0, &lon);
    impreinfo = (PRINTER_INFO_2*)GlobalAlloc( GPTR, lon );
    // obtiene la información de la impresora
    if(GetPrinter( himpre, 2, (LPBYTE)impreinfo, lon, &nbytes) == 0){
		ret=GetLastError();
       GlobalFree  ( impreinfo );
       ClosePrinter( himpre  );
       sprintf(msjerror,"CR10asignaimpresora: Error al obtener información de Windows sobre impresora %s %d\n", imp->salidaimpresora,ret);
       return(-1);
    }
    miimpresora = GlobalAlloc(GHND, sizeof(*impreinfo->pDevMode)+impreinfo->pDevMode->dmDriverExtra);
    modoimpresora = (DEVMODE*)GlobalLock(miimpresora); // WIN32, bloquea el objeto de mi impresora en la memoria de Window
    // accedemos a la formula ORIENTATION del informe, para ver si la orientación de la impresora
    // debe ser landscape o portrait
	*orientacion=0;
    CR10damevalorcampo(imp,"ORIENTATION",orientacion, msjerror);
    if (orientacion[1]=='L') impreinfo->pDevMode->dmOrientation= DMORIENT_LANDSCAPE;
	else impreinfo->pDevMode->dmOrientation= DMORIENT_PORTRAIT;
    memcpy(modoimpresora, impreinfo->pDevMode, sizeof(*impreinfo->pDevMode)+impreinfo->pDevMode->dmDriverExtra);
    GetPrinter(himpre, 9, NULL, 0, &lon);
	impreinfo9 = (PRINTER_INFO_9*)GlobalAlloc( GPTR, lon );
	if (impreinfo9) {
		// obtiene la información de la impresora
		if(GetPrinter( himpre, 9, (LPBYTE)impreinfo9, lon, &nbytes) == 0){ 
			GlobalFree  ( impreinfo );
			GlobalFree  ( impreinfo9 );
			ClosePrinter( himpre  );
			sprintf(msjerror,"CR10asignaimpresora: Error al obtener información de Windows sobre impresora %s\n", imp->salidaimpresora);
			return(-1);
		}
		if (impreinfo9->pDevMode) {
			if (orientacion[1]=='L') impreinfo9->pDevMode->dmOrientation= DMORIENT_LANDSCAPE;
			else impreinfo9->pDevMode->dmOrientation= DMORIENT_PORTRAIT;
			ret=SetPrinter(himpre,9,(LPBYTE)impreinfo9,0);
			if (ret==0) {
				ret=GetLastError();
				v10log(LOGERROR,"Error en Setprinter %d\n",ret);
			}
		}
		GlobalFree( impreinfo9 );
	}
    ClosePrinter(himpre); // cierra el manejador de la impresora, pues es impreinfo ya tiene la inf. necesaria sobre esta
    GlobalUnlock( miimpresora );
    // asignamos la impresora al informe
	ret = PESelectPrinter ( imp->id, impreinfo->pDriverName, impreinfo->pPrinterName, impreinfo->pPortName, modoimpresora );
	GlobalFree( impreinfo );
	GlobalFree( modoimpresora );
    ret = PEOutputToPrinter( imp->id, (short) imp->copias );
    if( ret == 0 ){
        sprintf(msjerror,"CR10asignaimpresora: Error al asignar la salida a impresora seleccionada por cuadro de diálogo\nError: %s\n", CR10error(imp,imp->id));
	    return(-1);
    }
    return(0);
}


int CR10imprime(char *codimpre, char *salida, int copias, cr10impresiones *imp, char *msjerror) 
{
    int ret;
    ret=CR10revisaconexionamotor(msjerror);
    if (ret) return(ret);
    strcpy(imp->codimpre,codimpre);
    strcpy(imp->salidaimpresora,salida);
    imp->copias=copias;
    v10log(LOGDEBUG,"CR10imprimeinforme: Informe %s, a imprimir %d copias por impresora %s con salida en %s\n",
            imp->informe,imp->copias,imp->codimpre,imp->salidaimpresora);
    if (!strcmp(codimpre,PREVISUALIZA))                 ret=CR10previsualizainforme(imp,msjerror);
    else if (!strcmp(codimpre,EXPORTAFICHERO))          ret=CR10exportainforme(imp,msjerror);
         else if (!strcmp(codimpre,PORDEFECTO))         ret=CR10asignaimpresora(imp,msjerror);
              else if (!strcmp(codimpre,SELECCIONA))    ret=CR10pideimpresora(imp,msjerror);
                   else                                 ret=CR10asignaimpresora(imp,msjerror);
    if (ret) return(ret);
    // deshabilita el cuadro de díalogo de progreso y cancel
    PEEnableProgressDialog( imp->id, PEFALSE );
    // con TRUE hace una llamáda síncrona, esperando a que finalice de generar el informe
    // para continuar
   	ret = PEStartPrintJob( imp->id, TRUE );
    if( ret == 0 ){
        sprintf(msjerror,"CR10imprimeinforme: Error al enviar informe %s a impresora %s %s\nError: %s\n", 
            imp->informe,imp->codimpre,imp->salidaimpresora,CR10error(imp,imp->id));
        return(-1);
    }
    v10log(LOGNORMAL,"CR10imprimeinforme: IMPRESO informe %s, %d copias por impresora %s con salida en %s\n",
            imp->informe,imp->copias,imp->codimpre,imp->salidaimpresora);
    return(0);
}

#if defined (__cplusplus)
}
#endif




