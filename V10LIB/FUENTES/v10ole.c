
#pragma warning(disable: 4267)
#include "v10.h"

#define MAX_DISP_ARGS 10
#define EPOCHOLE 2415019



/*
 *  Arrays of argument information, which are used to build up the arg list
 *  for an IDispatch call.  These arrays are statically allocated to reduce
 *  complexity, but this code could be easily modified to perform dynamic
 *  memory allocation.
 *
 *  When arguments are added they are placed into these arrays.  The
 *  Vargs array contains the argument values, and the lpszArgNames array
 *  contains the name of the arguments, or a NULL if the argument is unnamed.
 *  Flags for the argument such as NOFREEVARIANT are kept in the wFlags array.
 *
 *  When Invoke is called, the names in the lpszArgNames array are converted
 *  into the DISPIDs expected by the IDispatch::Invoke function.  The
 *  IDispatch::GetIDsOfNames function is used to perform the conversion, and
 *  the resulting IDs are placed in the DispIds array.  There is an additional
 *  slot in the DispIds and lpszArgNames arrays to allow for the name and DISPID
 *  of the method or property being invoked.
 *
 *  Because these arrays are static, it is important to call the ClearArgs()
 *  function before setting up arguments.  ClearArgs() releases any memory
 *  in use by the argument array and resets the argument counters for a fresh
 *  Invoke.
 */
static int        g_iArgCount;
static int        g_iNamedArgCount;
static VARIANTARG g_aVargs[MAX_DISP_ARGS];
static DISPID     g_aDispIds[MAX_DISP_ARGS + 1];       // one extra for the member name
static char       *g_alpszArgNames[MAX_DISP_ARGS + 1]; // used to hold the argnames for GetIDs
static LPOLESTR   oleargs[MAX_DISP_ARGS+1];
static WORD       g_awFlags[MAX_DISP_ARGS];


/*******************************************************************
 *
 *  GENERAL UTILITY ROUTINES FOR VARIANT AND ARG-ARRAY MANAGEMENT
 *
 *******************************************************************/

/*
 *  ClearVariant
 *
 *  Zeros a variant structure without regard to current contents
 */
void ClearVariant(VARIANTARG *pvarg)
{
	pvarg->vt = VT_EMPTY;
	pvarg->wReserved1 = 0;
	pvarg->wReserved2 = 0;
	pvarg->wReserved3 = 0;
	pvarg->lVal = 0;
}
/*
 *  ReleaseVariant
 *
 *  Clears a particular variant structure and releases any external objects
 *  or memory contained in the variant.  Supports the data types listed above.
 */
void ReleaseVariant(VARIANTARG *pvarg)
{
	VARTYPE vt;
	VARIANTARG _huge *pvargArray;
	long lLBound, lUBound, l;
	vt = (VARTYPE)(pvarg->vt & 0xfff);		// mask off flags
	// check if an array.  If so, free its contents, then the array itself.
	if (V_ISARRAY(pvarg)) {
		// variant arrays are all this routine currently knows about.  Since a
		// variant can contain anything (even other arrays), call ourselves
		// recursively.
		if (vt == VT_VARIANT) {
			SafeArrayGetLBound(pvarg->parray, 1, &lLBound);
			SafeArrayGetUBound(pvarg->parray, 1, &lUBound);
			if (lUBound > lLBound) {
				lUBound -= lLBound;
				SafeArrayAccessData(pvarg->parray,(void HUGEP* FAR*) &pvargArray);
				for (l = 0; l < lUBound; l++) {
					ReleaseVariant(pvargArray);
					pvargArray++;
             }
				SafeArrayUnaccessData(pvarg->parray);
          }
       } else {
			mensajefcm(10,"ReleaseVariant: Array contains non-variant type");
       }
		// Free the array itself.
		SafeArrayDestroy(pvarg->parray);
    }	else {
		switch (vt) {
			case VT_DISPATCH:
				liberaidispatch(pvarg->pdispVal);
				break;
			case VT_BSTR:
				SysFreeString(pvarg->bstrVal);
				break;
            case VT_NULL:
            case VT_DATE:
            case VT_EMPTY:
            case VT_I4:
			case VT_I2:
			case VT_CY:
			case VT_BOOL:
			case VT_R8:
			case VT_ERROR:		// to avoid erroring on an error return from Excel
				// no work for these types
				break;
			default:
				mensajefcm(10,"ReleaseVariant: Unknown type");
				break;
	    }
    }
	ClearVariant(pvarg);
}
/*
 *  ClearAllArgs
 *
 *  Clears the existing contents of the arg array in preparation for
 *  a new invocation.  Frees argument memory if so marked.
 */
void ClearAllArgs(void)
{
	int i;
	for (i = 0; i < g_iArgCount; i++) {
		if (g_awFlags[i] & DISPARG_NOFREEVARIANT) ClearVariant(&g_aVargs[i]);
		else                                      ReleaseVariant(&g_aVargs[i]);
    }
	g_iArgCount = 0;
	g_iNamedArgCount = 0;
}
/*******************************************************************
 *
 *					   ARGUMENT CONSTRUCTOR FUNCTIONS
 *
 *  Each function adds a single argument of a specific type to the list
 *  of arguments for the current invoke.  If appropriate, memory may be
 *  allocated to represent the argument.  This memory will be
 *  automatically freed the next time ClearAllArgs() is called unless
 *  the NOFREEVARIANT flag is specified for a particular argument.  If
 *  NOFREEVARIANT is specified it is the responsibility of the caller
 *  to free the memory allocated for or contained within the argument.
 *
 *  Arguments may be named.  The name string must be a C-style string
 *  and it is owned by the caller.  If dynamically allocated, the caller
 *  must free the name string.
 *
 *******************************************************************/

/*
 *  Common code used by all variant types for setting up an argument.
 */
void AddArgumentCommon(char *lpszArgName, WORD wFlags, VARTYPE vt)
{
	ClearVariant(&g_aVargs[g_iArgCount]);
	g_aVargs[g_iArgCount].vt = vt;
	g_awFlags[g_iArgCount] = wFlags;
	if (lpszArgName != NULL) {
		g_alpszArgNames[g_iNamedArgCount + 1] = lpszArgName;
		g_iNamedArgCount++;
    }
}

BOOL AddArgumentDispatch(char *lpszArgName, WORD wFlags, IDispatch * pdisp)
{
	AddArgumentCommon(lpszArgName, wFlags, VT_DISPATCH);
	g_aVargs[g_iArgCount++].pdispVal = pdisp;
	return TRUE;
}

BOOL AddArgumentInt2(char *lpszArgName, int i)
{
	AddArgumentCommon(lpszArgName, 0, VT_I2);
	g_aVargs[g_iArgCount++].iVal = (short)i;
	return TRUE;
}

BOOL AddArgumentInt4(char *lpszArgName, int i)
{
	AddArgumentCommon(lpszArgName, 0, VT_I4);
	g_aVargs[g_iArgCount++].lVal = i;
	return TRUE;
}

BOOL AddArgumentDouble(char *lpszArgName, double d)
{
	AddArgumentCommon(lpszArgName, 0, VT_R8);
	g_aVargs[g_iArgCount++].dblVal = d;
	return TRUE;
}

BOOL AddArgumentarray(char *lpszArgName, SAFEARRAY *psa)
{
    AddArgumentCommon(NULL, 0, VT_VARIANT | VT_ARRAY);
    g_aVargs[g_iArgCount++].parray = psa;
	return TRUE;
}




/*
 *  OLE and IDispatch use a BSTR as the representation of strings.
 *  This constructor automatically copies the passed-in C-style string
 *  into a BSTR.  It is important to not set the NOFREEVARIANT flag
 *  for this function, otherwise the allocated BSTR copy will probably
 *  get lost and cause a memory leak.
 */
BOOL AddArgumentString(char *lpszArgName, WORD wFlags, char *cadena)
{
	BSTR b;
   OLECHAR lpsz[MAXOLECADENA];
   MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,cadena,-1,lpsz,MAXOLECADENA-1);
	b = SysAllocString(lpsz);
	if (!b) return FALSE;
	AddArgumentCommon(lpszArgName, wFlags, VT_BSTR);
	g_aVargs[g_iArgCount++].bstrVal = b;
	return TRUE;
}

BOOL AddArgumentBool(char *lpszArgName, BOOL b)
{
	AddArgumentCommon(lpszArgName, 0,VT_BOOL);
	// Note the variant representation of True as -1
	g_aVargs[g_iArgCount++].boolVal =(VARIANT_BOOL) (b ? -1 : 0);
	return TRUE;
}
/*******************************************************************
 *
 *								INVOKE
 *
 *******************************************************************/
/*
 *  INVOKE
 *
 *  Invokes a method or property.  Takes the IDispatch object on which to invoke,
 *  and the name of the method or property as a C-String.  Arguments, if any,
 *  must have been previously setup using the AddArgumentXxx() functions.
 *
 *  Returns TRUE if the call succeeded.  Returns FALSE if an error occurred.
 *  A messagebox will be displayed explaining the error unless the DISP_NOSHOWEXCEPTIONS
 *  flag is specified.  Errors can be a result of unrecognized method or property
 *  names, bad argument names, invalid types, or runtime-exceptions defined
 *  by the recipient of the Invoke.
 *
 *  The argument list is reset via ClearAllArgs() if the DISP_FREEARGS flag is
 *  specified.  If not specified, it is up to the caller to call ClearAllArgs().
 *
 *  The return value is placed in pvargReturn, which is allocated by the caller.
 *  If no return value is required, pass NULL.  It is up to the caller to free
 *  the return value (ReleaseVariant()).
 *
 *  This function calls IDispatch::GetIDsOfNames for every invoke.  This is not
 *  very efficient if the same method or property is invoked multiple times, since
 *  the DISPIDs for a particular method or property will remain the same during
 *  the lifetime of an IDispatch object.  Modifications could be made to this code
 *  to cache DISPIDs.  If the target application is always the same, a similar
 *  modification is to statically browse and store the DISPIDs at compile-time, since
 *  a given application will return the same DISPIDs in different sessions.
 *  Eliminating the extra cross-process GetIDsOfNames call can result in a
 *  signficant time savings.
 */
static void ShowException(char *szMember, HRESULT hr, EXCEPINFO *pexcep, unsigned int uiArgErr)
{
	TCHAR szBuf[512];
	switch (GetScode(hr)) {
		case DISP_E_UNKNOWNNAME:
			wsprintf(szBuf, "%s: Unknown name or named argument.", szMember);
			break;
		case DISP_E_BADPARAMCOUNT:
			wsprintf(szBuf, "%s: Incorrect number of arguments.", szMember);
			break;
		case DISP_E_EXCEPTION:
			wsprintf(szBuf, "%s: Error %d: ", szMember, pexcep->wCode);
			break;
		case DISP_E_MEMBERNOTFOUND:
			wsprintf(szBuf, "%s: method or property not found.", szMember);
			break;
		case DISP_E_OVERFLOW:
			wsprintf(szBuf, "%s: Overflow while coercing argument values.", szMember);
			break;
		case DISP_E_NONAMEDARGS:
			wsprintf(szBuf, "%s: Object implementation does not support named arguments.",
						szMember);
		    break;
		case DISP_E_UNKNOWNLCID:
			wsprintf(szBuf, "%s: The locale ID is unknown.", szMember);
			break;
		case DISP_E_PARAMNOTOPTIONAL:
			wsprintf(szBuf, "%s: Missing a required parameter.", szMember);
			break;
		case DISP_E_PARAMNOTFOUND:
			wsprintf(szBuf, "%s: Argument not found, argument %d.", szMember, uiArgErr);
			break;
		case DISP_E_TYPEMISMATCH:
			wsprintf(szBuf, "%s: Type mismatch, argument %d.", szMember, uiArgErr);
			break;
		default:
			wsprintf(szBuf, "%s: Unknown error occured.", szMember);
			break;
	 }
	v10log(LOGERROR,"%s\n",szBuf);
}

BOOL Invoke(IDispatch *pdisp, char *funcion, VARIANTARG * pvargReturn,
			WORD wInvokeAction, WORD wFlags)
{
	HRESULT hr;
	DISPPARAMS dispparams;
	unsigned int uiArgErr;
	EXCEPINFO excep;
   OLECHAR szMember[MAXOLECADENA];
   int i;
	// Get the IDs for the member and its arguments.  GetIDsOfNames expects the
	// member name as the first name, followed by argument names (if any).
   MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,funcion,-1,szMember,MAXOLECADENA-1);
	oleargs[0] = szMember;
   for (i=1;i<g_iNamedArgCount+1;i++) {
       oleargs[i]=calloc(sizeof(OLECHAR),strlen(g_alpszArgNames[i])+1);
       MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,g_alpszArgNames[i],-1,oleargs[i],strlen(g_alpszArgNames[i])+1);
    }
	hr = (*(pdisp->lpVtbl->GetIDsOfNames))(pdisp, &IID_NULL, oleargs,
								1 + g_iNamedArgCount, LOCALE_SYSTEM_DEFAULT, g_aDispIds);
	if (FAILED(hr)) {
		if (!(wFlags & DISP_NOSHOWEXCEPTIONS)) ShowException(funcion, hr, NULL, 0);
		return FALSE;
    }
	if (pvargReturn != NULL) ClearVariant(pvargReturn);
	// if doing a property put(ref), we need to adjust the first argument to have a
	// named arg of DISPID_PROPERTYPUT.
	if (wInvokeAction & (DISPATCH_PROPERTYPUT | DISPATCH_PROPERTYPUTREF)) {
		g_iNamedArgCount = 1;
		g_aDispIds[1] = DISPID_PROPERTYPUT;
		pvargReturn = NULL;
       oleargs[1]=calloc(1,1);
    }
	dispparams.rgdispidNamedArgs = g_aDispIds + 1;
	dispparams.rgvarg = g_aVargs;
	dispparams.cArgs = g_iArgCount;
	dispparams.cNamedArgs = g_iNamedArgCount;
	excep.pfnDeferredFillIn = NULL;
	hr = (*(pdisp->lpVtbl->Invoke))(pdisp, g_aDispIds[0], &IID_NULL, LOCALE_SYSTEM_DEFAULT,
								wInvokeAction, &dispparams, pvargReturn, &excep, &uiArgErr);
	if (wFlags & DISP_FREEARGS) ClearAllArgs();
   for (i=1;i<g_iNamedArgCount+1;i++) free(oleargs[i]);
	if (FAILED(hr)) {
		// display the exception information if appropriate:
		if (!(wFlags & DISP_NOSHOWEXCEPTIONS))	ShowException(funcion, hr, &excep, uiArgErr);
		// free exception structure information
		SysFreeString(excep.bstrSource);
		SysFreeString(excep.bstrDescription);
		SysFreeString(excep.bstrHelpFile);
		return FALSE;
    }
	return TRUE;
}

void variant2string(VARIANTARG *pvarg,char *donde)
{
	VARTYPE vt;
	vt = (VARTYPE)(pvarg->vt & 0xfff);		// mask off flags
	// check if an array.  If so, free its contents, then the array itself.
	if (V_ISARRAY(pvarg)) {
      strcpy(donde,"");
    }	else {
		switch (vt) {
			case VT_EMPTY:
            strcpy(donde,"");
				break;
			case VT_DISPATCH:
            strcpy(donde,"");
				break;
			case VT_BSTR:
            if (WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,pvarg->bstrVal,-1,donde,MAXOLECADENA-1,NULL,NULL)==0)
               GetLastError();
				break;
         case VT_I4:sprintf(donde,"%d",pvarg->lVal);
                    break;
			case VT_I2:sprintf(donde,"%d",pvarg->iVal);
                    break;
			case VT_BOOL:sprintf(donde,"%d",pvarg->bVal);
                    break;
			case VT_R8:sprintf(donde,"%20.8lf",pvarg->dblVal);
                    trim(donde);
                    ltrim(donde);
                    {char *aux,*aux1;
                    aux1=aux=strchr(donde,'.');
                    if (aux==NULL) break;
                    do {
                        aux1++;
                       } while (*aux1=='0');
                    if (*aux1==0) *aux=0;
                    }
                    break;
			case VT_ERROR:strcpy(donde,"");
				break;
         case VT_DATE:sprintf(donde,"%20.8lf",pvarg->date+EPOCHOLE);
                      break;
         case VT_CY:sprintf(donde,"%20.8lf",(pvarg->cyVal.Lo+(pvarg->cyVal.Hi*4.0*(1<<30)))/10000.0);
                      break;
			default: strcpy(donde,"");
				mensajefcm(10,"ReleaseVariant: Unknown type");
				break;
	    }
    }
}

double variant2double(VARIANTARG *pvarg)
{
	VARTYPE vt;
    char donde[MAXOLECADENA];
	vt = (VARTYPE)(pvarg->vt & 0xfff);		// mask off flags
	// check if an array.  If so, free its contents, then the array itself.
    if (V_ISARRAY(pvarg)) { 
      return(0);
    }	else {
		switch (vt) {
			case VT_DISPATCH:
			case VT_EMPTY:
                return(0);
				break;
			case VT_BSTR:
               WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,pvarg->bstrVal,-1,donde,MAXOLECADENA-1,NULL,NULL);
               return(atof(donde));
				break;
            case VT_I4:return(pvarg->lVal);
                    break;
			case VT_I2:return(pvarg->iVal);
                    break;
			case VT_BOOL:sprintf(donde,"%d",pvarg->bVal);
                    break;
			case VT_R8:return(pvarg->dblVal);
                    break;
			case VT_ERROR:return(0);
				break;
            case VT_DATE:return(pvarg->date+EPOCHOLE);
                      break;
            case VT_CY:return((pvarg->cyVal.Lo+(pvarg->cyVal.Hi*4.0*(1<<30)))/10000.0);
                      break;
	    }
    }
  return(0);
}

int invocametodoex(IDispatch *id,char *funcion,VARIANTARG *resul,short op,va_list arg)
{
  char *nombre;
  int ret;
  ClearAllArgs();
  while ((nombre=va_arg(arg,char *))!=(char *)-1) {
        int tipo;
        int ival;
        long lval;
        double dval;
        char *cval;
        IDispatch *pid;
        tipo=va_arg(arg,int);
        switch (tipo) {
            case V10INT:ival=va_arg(arg,int);
                     AddArgumentInt2(nombre,ival);
                     break;
            case V10LONG:lval=va_arg(arg,long);
                        AddArgumentInt4(nombre,lval);
                        break;
            case V10DOUBLE:dval=va_arg(arg,double);
                        AddArgumentDouble(nombre,dval);
                        break;
            case V10CADENA:cval=va_arg(arg,char *);
                        AddArgumentString(nombre,0,cval);
                        break;
            case V10IDISPATCH:pid=va_arg(arg,IDispatch *);
                        AddArgumentDispatch(nombre,0,pid);
                        break;
         }
   }
  ret=Invoke(id,funcion,resul,op,0);
  return(ret);
}

int invocametodo(IDispatch *id,char *funcion,VARIANTARG *resul,...)
{
  va_list arg;
  int ret;
  va_start(arg,resul);
  ret=invocametodoex(id,funcion,resul,DISPATCH_METHOD,arg);
  return(ret);
}

int getproperty(IDispatch *id,char *funcion,VARIANTARG *resul,...)
{
  va_list arg;
  int ret;
  va_start(arg,resul);
  ret=invocametodoex(id,funcion,resul,DISPATCH_PROPERTYGET,arg);
  return(ret);
}

int putproperty(IDispatch *id,char *funcion,VARIANTARG *resul,...)
{
  va_list arg;
  int ret;
  va_start(arg,resul);
  ret=invocametodoex(id,funcion,resul,DISPATCH_PROPERTYPUT,arg);
  return(ret);
}

void liberaidispatch(IDispatch *id)
{
    (*(id->lpVtbl->Release))(id);
}


static int InitOLE(void)
{
	DWORD dwOleVer;
	dwOleVer = CoBuildVersion();
	// check the OLE library version
	if (rmm != HIWORD(dwOleVer)) {
		mensajefcm(10, "Incorrect version of OLE libraries.");
		return(-1);
	}
	if (FAILED(OleInitialize(NULL)))	{
		mensajefcm(10, "No puedo inicializar OLE.");
		return(-1);
	}
	return(0);
}

void finole(void)
{
    OleUninitialize();
}

IDispatch *startole(char *nombre,int reusar)
{
    IDispatch *ret;
    IUnknown *pUnk;
    CLSID clsoleApp;
    OLECHAR szMember[MAXOLECADENA];
    InitOLE();
    MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,nombre,-1,szMember,MAXOLECADENA-1);
    if (FAILED(CLSIDFromProgID(szMember, &clsoleApp))) {
        return(NULL);
    }
    if (reusar) GetActiveObject(&clsoleApp, NULL, (IUnknown**)&pUnk);
    else        pUnk=NULL;
    if (pUnk==NULL) {
       if (FAILED(CoCreateInstance(&clsoleApp, NULL, CLSCTX_LOCAL_SERVER, &IID_IDispatch,(void **)&ret))) {
          return(NULL);
        }
    } else {
        pUnk->lpVtbl->QueryInterface(pUnk,&IID_IDispatch, (void **)&ret);
        pUnk->lpVtbl->Release(pUnk);
    }
    return(ret);
}

