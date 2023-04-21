
#include <io.h>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include <windowsx.h>
#include <ole2ver.h>
#include <process.h>
#define midir HANDLE
#define PTHREAD_MUTEX_INITIALIZER 0
#ifdef __V10WINDLL
  #define V10WINIMPORT __declspec(dllexport)
#else
  #define V10WINIMPORT __declspec(dllimport)
#endif
#ifdef __V10WINDLL
  #define V10IMPORT __declspec(dllexport)
#else
  #define V10IMPORT __declspec(dllimport)
#endif

#define SEMICOLON ';'
#define BACKSLASH '\\'
#define ESTILOV10   (WS_OVERLAPPEDWINDOW|WS_HSCROLL|WS_VSCROLL)


//Funciones definidas en V10ENCRIPTA.C
#include "wincrypt.h"

#define MAXHASH 50

#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)

V10IMPORT int damehash(char *origen,char *hash);
V10IMPORT int compruebahash(char *origen,char *hash);
V10IMPORT HCRYPTKEY dameclave(char *pass);
V10IMPORT int genfirma(HCRYPTKEY keysesion,char *priv,char *pub);
V10IMPORT int encriptasesion(HCRYPTKEY hkey,char *cadena,char *destino);
V10IMPORT int desencriptasesion(HCRYPTKEY hkey,char *cadena,char *destino);
V10IMPORT int recodificafirma(char *oldpwd,char *newpwd,char *cpriv);
V10IMPORT HCRYPTKEY dameclavepublica(char *pub);
V10IMPORT HCRYPTKEY dameclaveprivada(HCRYPTKEY hkey,char *priv);
V10IMPORT int firmadatosh(HCRYPTKEY hpriv,char *cadena,char *destino);
V10IMPORT int firmadatos(HCRYPTKEY hpriv,char *cadena,char *destino);
V10IMPORT int verificafirmah(HCRYPTKEY hpub,char *cadena,char *firma);
V10IMPORT int verificafirma(HCRYPTKEY hpub,char *cadena,char *firma);



//Funciones definidas en V10OLE.C
// use this flag when adding arguments to indicate that the arg
// contents should NOT automatically be freed/released.
#define DISPARG_NOFREEVARIANT 0x01
#define V10IDISPATCH 30

#define DISP_FREEARGS 0x01
#define DISP_NOSHOWEXCEPTIONS 0x02
#define MAXOLECADENA 4000
V10IMPORT void ClearVariant(VARIANTARG *pvarg);
V10IMPORT void ReleaseVariant(VARIANTARG *pvarg);
V10IMPORT void ClearAllArgs(void);
V10IMPORT void AddArgumentCommon(char *lpszArgName, WORD wFlags, VARTYPE vt);
V10IMPORT BOOL AddArgumentDispatch(char *lpszArgName, WORD wFlags, IDispatch * pdisp);
V10IMPORT BOOL AddArgumentInt2(char *lpszArgName, int i);
V10IMPORT BOOL AddArgumentInt4(char *lpszArgName, int i);
V10IMPORT BOOL AddArgumentDouble(char *lpszArgName, double d);
V10IMPORT BOOL AddArgumentarray(char *lpszArgName, SAFEARRAY *psa);
V10IMPORT BOOL AddArgumentString(char *lpszArgName, WORD wFlags, char *cadena);
V10IMPORT BOOL AddArgumentBool(char *lpszArgName, BOOL b);
V10IMPORT BOOL Invoke(IDispatch *pdisp, char *funcion, VARIANTARG * pvargReturn,WORD wInvokeAction,WORD wFlags);
V10IMPORT void variant2string(VARIANTARG *pvarg,char *donde);
V10IMPORT double variant2double(VARIANTARG *pvarg);
V10IMPORT int invocametodoex(IDispatch *id,char *funcion,VARIANTARG *resul,short op,va_list arg);
V10IMPORT int invocametodo(IDispatch *id,char *funcion,VARIANTARG *resul,...);
V10IMPORT int getproperty(IDispatch *id,char *funcion,VARIANTARG *resul,...);
V10IMPORT int putproperty(IDispatch *id,char *funcion,VARIANTARG *resul,...);
V10IMPORT void liberaidispatch(IDispatch *id);
V10IMPORT void finole(void);
V10IMPORT IDispatch *startole(char *nombre,int reusar);

//Funciones definidas en V10EXCEL.C
#define xlWorksheet -4167
#define xl3DColumn -4100
#define xlRows 1
#define MAXLRANGO  20
V10IMPORT int setvalorstring(IDispatch *pdispWs, char *lpszRef, char *valor);
V10IMPORT int setvalorarray(IDispatch *pdispWs, char *lpszRef, SAFEARRAY *psa);
V10IMPORT int getvalorstring(IDispatch *pdispWs, char *lpszRef, char *valor);
V10IMPORT int getvalorarray(IDispatch *pdispWs, char *lpszRef,VARIANTARG  *valor);
V10IMPORT int getvalorvararg(IDispatch *pdispWs, char *lpszRef,VARIANTARG *ret);
V10IMPORT int gettipo(IDispatch *pdispWs, char *lpszRef);
V10IMPORT void pasadirexcel(int col,int fila, char *cadena);
V10IMPORT void pasarangoexcel(int colori,int filaori,int coldest,int filadest, char *cadena);
V10IMPORT IDispatch *damerangoexcel(IDispatch *hoja,int colori,int filaori,int coldest,int filadest);
V10IMPORT void visibleexcel(IDispatch *id,BOOL visible);
V10IMPORT void salvaexcel(IDispatch *wb,char *nombre);
V10IMPORT int cargaexcel(IDispatch *id,IDispatch **wb,IDispatch **hoja,char *nombre);
V10IMPORT IDispatch *anadehoja(IDispatch *wb,int after,char *plantilla);
V10IMPORT int numhojas(IDispatch *wb);
//Funciones definidas en V10VISUALIZA.C
/*
V10IMPORT servidorsocks *arrancaserverlog(char *puerto);
V10IMPORT servidorsocks *arrancaserverpantalla(char *puerto);
*/

#ifdef __V10ORACLEDLL
   #define V10ORACLEIMPORT __declspec(dllexport)
#else
   #define V10ORACLEIMPORT __declspec( dllimport )
#endif

#ifdef _V10SSLDLL
  #define V10SSLIMPORT __declspec(dllimport)
#else
  #define V10SSLIMPORT __declspec( dllexport )
#endif

__declspec( dllimport ) oermsg(int err,char *msg);

