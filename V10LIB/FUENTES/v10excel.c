/*
* Módulo : V10FOROLE.C
* Objeto:  Interfase de FORMS con EXCEL
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

int setvalorstring(IDispatch *pdispWs, char *lpszRef, char *valor)
{
	VARIANTARG vargRng;
	BOOL fResult;
	if (!getproperty(pdispWs, "Range", &vargRng,NULL,V10CADENA,lpszRef,-1)) return FALSE;
	fResult = putproperty(vargRng.pdispVal, "Value", NULL,NULL,V10CADENA,valor,-1);
	ReleaseVariant(&vargRng);
	ClearAllArgs();
	return fResult;
}

int setvalorarray(IDispatch *pdispWs, char *lpszRef, SAFEARRAY *psa)
{
    VARIANTARG vargRng;
    BOOL fResult;
	if (!getproperty(pdispWs, "Range", &vargRng,NULL,V10CADENA,lpszRef,-1)) return FALSE;
	ClearAllArgs();
    AddArgumentarray(NULL, psa);
    fResult = Invoke(vargRng.pdispVal, "Value", NULL, DISPATCH_PROPERTYPUT, 0);
    ReleaseVariant(&vargRng);
    ClearAllArgs();
    return fResult;
}

int getvalorstring(IDispatch *pdispWs, char *lpszRef, char *valor)
{
    VARIANTARG vargRng;
    VARIANTARG ret;
    BOOL fResult;
	if (!getproperty(pdispWs, "Range", &vargRng,NULL,V10CADENA,lpszRef,-1)) return FALSE;
    fResult = getproperty(vargRng.pdispVal, "Value", &ret,-1);
    variant2string(&ret,valor);
    ReleaseVariant(&vargRng);
    ReleaseVariant(&ret);
    return fResult;
}

int getvalorarray(IDispatch *pdispWs, char *lpszRef,VARIANTARG  *valor)
{
    VARIANTARG vargRng;
    VARIANTARG ret;
    BOOL fResult;
    ClearAllArgs();
    AddArgumentString(NULL, 0, lpszRef);
    if (!Invoke(pdispWs, "Range", &vargRng, DISPATCH_PROPERTYGET, DISP_FREEARGS)) return FALSE;
    ClearAllArgs();
    fResult = getproperty(vargRng.pdispVal, "Value", &ret, -1);
	*valor = ret;
    ReleaseVariant(&vargRng);
    return fResult;
}

int getvalorvararg(IDispatch *pdispWs, char *lpszRef,VARIANTARG *ret)
{
    VARIANTARG vargRng;
    BOOL fResult;
	if (!getproperty(pdispWs, "Range", &vargRng,NULL,V10CADENA,lpszRef,-1)) return FALSE;
    fResult = getproperty(vargRng.pdispVal, "Formula", ret,-1);
    ReleaseVariant(&vargRng);
    return fResult;
}

int gettipo(IDispatch *pdispWs, char *lpszRef)
{
    VARIANTARG vargRng;
    VARIANTARG ret;
    VARTYPE vt;
    int tipo;
	if (!getproperty(pdispWs, "Range", &vargRng,NULL,V10CADENA,lpszRef,-1)) return FALSE;
    getproperty(vargRng.pdispVal, "Value", &ret,-1);
    vt = (VARTYPE)(ret.vt & 0xfff);		// mask off flags
    switch (vt) {
			case VT_EMPTY:
			case VT_DISPATCH:
			case VT_BSTR:
         case VT_ERROR:
            tipo=V10CADENA;
				break;
         case VT_DATE:
			case VT_BOOL:
         case VT_I4:
			case VT_I2:tipo=V10LONG;
                    break;
         case VT_CY:
			case VT_R8:tipo=V10DOUBLE;
                    break;
			default: tipo=V10CADENA;
				mensajefcm(10,"ReleaseVariant: Unknown type");
				break;
    }
    ReleaseVariant(&vargRng);
    ReleaseVariant(&ret);
    return tipo;
}

void pasadirexcel(int col,int fila, char *cadena)
{
    if (col>'Z'-'A') {
        sprintf(cadena,"%c%c%d",(col)/('Z'-'A'+1)+'A'-1,((col)%('Z'-'A'+1))+'A',fila);
    } else {
        sprintf(cadena,"%c%d",col+'A',fila);
    }
}

void pasarangoexcel(int colori,int filaori,int coldest,int filadest, char *cadena)
{
    pasadirexcel(colori,filaori,cadena);
    strcat(cadena,":");
    pasadirexcel(coldest,filadest,cadena+strlen(cadena));
}

IDispatch *damerangoexcel(IDispatch *hoja,int colori,int filaori,int coldest,int filadest)
{
    VARIANTARG ret;
    char direxcel[MAXLRANGO];
    pasarangoexcel(colori,filaori,coldest,filadest,direxcel);
	if (!getproperty(hoja, "Range", &ret,NULL,V10CADENA,direxcel,-1)) return FALSE;
    ClearAllArgs();
    return(ret.pdispVal);
}

void visibleexcel(IDispatch *id,BOOL visible)
{
	putproperty(id, "Visible",NULL, NULL,V10INT,TRUE,-1);
}

void salvaexcel(IDispatch *wb,char *nombre)
{
    VARIANTARG varg1;    
    AddArgumentString("Filename", 0,nombre);
    Invoke(wb, "SaveAs", &varg1, DISPATCH_METHOD, 0);
    ReleaseVariant(&varg1);
    ClearAllArgs(); 
}

int cargaexcel(IDispatch *id,IDispatch **wb,IDispatch **hoja,char *nombre)
{
    VARIANTARG varg1,varg2;
    int ret;
    if (getproperty(id, "Workbooks", &varg1, (char *)-1)) {
        ClearAllArgs();
        if (!es_blanco(nombre)) {
            AddArgumentString("Filename", 0, nombre);
            ret=Invoke(varg1.pdispVal, "Open", &varg2, DISPATCH_METHOD, 0);
        }  else {
            AddArgumentInt2("Template",  xlWorksheet);
            ret=Invoke(varg1.pdispVal, "Add", &varg2, DISPATCH_METHOD, 0);
		}
		ReleaseVariant(&varg1);
        if (ret==FALSE) {
            return(-1);
        }
        *wb = varg2.pdispVal;
        ClearAllArgs();
        AddArgumentInt2(NULL, 1);
        Invoke(*wb, "Worksheets", &varg2, DISPATCH_PROPERTYGET, 0);
        *hoja = varg2.pdispVal;
        ClearAllArgs();
        return(0);
    }
    return(-1);
}

IDispatch *anadehoja(IDispatch *wb,int after,char *plantilla)
{
    int ret;
    VARIANTARG varg;
    char nombreplantilla[MAXPATH];
    ClearAllArgs();
    AddArgumentInt2("After",after);
    if (!es_blanco(plantilla)) {
        ret=damenombrecompleto(plantilla,nombreplantilla);
        if (ret) strcpy(nombreplantilla,"");
    } else strcpy(nombreplantilla,"");
    if (!es_blanco(nombreplantilla)) AddArgumentString("Type",0,nombreplantilla);
    ret=Invoke(wb, "Add", &varg, DISPATCH_METHOD, 0);
    ClearAllArgs();
    if (ret==TRUE) return varg.pdispVal;
    return(NULL);
}

int numhojas(IDispatch *wb)
{
    VARIANTARG varg;
    int ret;
    ClearAllArgs();
    ret=Invoke(wb, "Count", &varg, DISPATCH_METHOD, 0);
    ret=(int)variant2double(&varg);
    ReleaseVariant(&varg);
    return(ret);
}

