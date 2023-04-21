/*
* Módulo : V10ORAEXCEL.C
* Objeto:  Funciones para interfasar ORACLE con EXCEL
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/

#pragma warning(disable: 4267)
#include "forms\v10form.h"


typedef struct {
          campooras  *col;
          VARIANTARG valor;
} valores;

static valores val[MAXCAMPOS];
static int ncol;


static int pasacab(v10cursors *cur,IDispatch *id)
{        
    int nc;
    char cadena[MAXLRANGO],nombre[MAXNOMBREV10];
    for (nc=0;nc<ncol;nc++) {
        pasadirexcel(nc,1,cadena);
        if (traducecamposole) strcpy(nombre,traducecamposole(val[nc].col->nombre,0));
           else               strcpy(nombre,val[nc].col->nombre);
        setvalorstring(id, cadena, nombre);        
    }
    return TRUE;
}

static int pasaunregistro(v10cursors *cur,IDispatch *id,int fila,int copiar)
{
    int nc,ret;
    int ncolreal=0;
    SAFEARRAY *psa;
    SAFEARRAYBOUND saBound;
    VARIANTARG *pvargBase;
    VARIANTARG *pvarg;
    OLECHAR lpsz[MAXOLECADENA];
    char direxcel[MAXLRANGO];
    saBound.lLbound = 0;
    saBound.cElements = ncol;
    psa = SafeArrayCreate(VT_VARIANT, 1, &saBound);
    if (psa == NULL) return FALSE;
    SafeArrayAccessData(psa,(void HUGEP* FAR*)  &pvargBase);
    pvarg = pvargBase;
    if (copiar) {
        IDispatch *rango;
        rango=damerangoexcel(id,0,fila,ncol-1,fila);
        ret = Invoke(rango, "PasteSpecial", NULL,  DISPATCH_METHOD, 0);
        liberaidispatch(rango);
    }
    for (nc=0;nc<ncol;nc++,pvarg++) {
        void *dir;          
        ClearVariant(pvarg);
        if (val[nc].col) {
            dir=val[nc].col->dato; 
            switch (val[nc].col->tipo) {
                     case  V10FECHA:{char mifecha[20];
                                 jul2a(*(v10dates *)dir,"DD-MM-Y.YY",mifecha);
                                 pvarg->vt = VT_BSTR;
                                 MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,mifecha,-1,lpsz,MAXOLECADENA-1);
                                 pvarg->bstrVal = SysAllocString(lpsz);
                                 break;
                                }
                     case V10LONG:pvarg->vt = VT_R8;
                                 pvarg->dblVal=*(long *)dir;
                                 break;
                     case V10INT:   pvarg->vt = VT_R8;
                                 pvarg->dblVal=*(int *)dir;
                                 break;
                     case V10FLOAT: pvarg->vt = VT_R8;
                                 pvarg->dblVal=*(float *)dir;
                                 break;
                     case V10DOUBLE:pvarg->vt = VT_R8;
                                 pvarg->dblVal=*(double *)dir;
                                 break;
                     case V10CADENA:{char *midir;
                                 pvarg->vt = VT_BSTR;
                                 midir=calloc(1,strlen(dir)+2);
                                 if (val[nc].col->oratipo!=OCIDATE) strcpy(midir,"'");
                                 strcpy(midir+strlen(midir),dir);
                                 MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,midir,-1,lpsz,MAXOLECADENA-1);
                                 free(midir);
                                 pvarg->bstrVal = SysAllocString(lpsz);
                                 break;}
          }
        } else {
            pasarangoexcel(nc,fila,nc,fila,direxcel);
            getvalorvararg(id,direxcel,pvarg);
        }
    }
    pasarangoexcel(0,fila,ncol-1,fila,direxcel);
    ClearAllArgs();
    SafeArrayUnaccessData(psa);
    setvalorarray(id,direxcel,psa);
    return(0);
}


int bloqcur2excel(bloques *b, v10cursors *cur, char *plantilla, char *destino, int salir)
{
	IDispatch *id, *wb, *hoja, *columna;
	int ret, copiar = 0;
	char nombreplantilla[MAXPATH];
	VARIANTARG varg2;
	id = startole("Excel.Application", 1);
	if (id == NULL) {
		mensajefcm(10, "Aplicacion %s no instalada", "Excel");
		finole();
		return(-1);
	}
	if (es_blanco(plantilla)) strcpy(nombreplantilla, plantilla);
	else {
		ret = damenombrecompleto(plantilla, nombreplantilla);
		if (ret) strcpy(nombreplantilla, "");
	}
	ret = cargaexcel(id, &wb, &hoja, nombreplantilla);
	if (ret) {
		finole();
		return(ret);
	}
	if (es_blanco(nombreplantilla)) {
		for (ncol = 0; ncol<cur->ndef; ncol++) val[ncol].col = cur->def + ncol;
		pasacab(cur, hoja);
    } else {
		for (ncol = 0; ncol<MAXCAMPOS; ncol++) {
			char valor[100];
			char rango[MAXLRANGO];
			int nc;
			pasadirexcel(ncol, 1, rango);
			getvalorstring(hoja, rango, valor);
			if (es_blanco(valor)) break;
			trim(valor);
			valor[MAXNOMBREV10 - 1] = 0;
			for (nc = 0; nc<cur->ndef; nc++) {
				char *nombre;
				if (traducecamposole) nombre = traducecamposole(cur->def[nc].nombre, 0);
				else               nombre = cur->def[nc].nombre;
				if (strcmp(valor, nombre) == 0) {
					val[ncol].col = cur->def + nc;
					break;
				}
			}
			if (nc >= cur->ndef) {
				val[ncol].col = NULL;
				pasadirexcel(ncol, 2, rango);
				getvalorvararg(hoja, rango, &val[ncol].valor);
				copiar = 1;
			}
		}
		if (copiar) {
			IDispatch *rango;
			rango = damerangoexcel(hoja, 0, 2, ncol - 1, 2);
			ClearAllArgs();
			ret = Invoke(rango, "Copy", NULL, DISPATCH_METHOD, 0);
			liberaidispatch(rango);
		}
	}
	preparaarrayfetch(cur, 1000);
	ejecutacursor(cur);
	while (fetchcursor(cur) == 0) {
		pasaunregistro(cur, hoja, procesadascursor(cur) + 1, copiar);
		v10log(LOGDEBUG, "Precesando registro %ld\n", procesadascursor(cur));
	}
	getproperty(hoja, "columns", &varg2, -1);
	columna = varg2.pdispVal;
	invocametodo(columna, "Autofit", NULL, -1);
	liberaidispatch(columna);
	if (!es_blanco(destino)) {
		salvaexcel(wb, destino);
	}
	if ((salir  && !es_blanco(destino)) || v10versionweb) {
		if (v10versionweb && b) {
			presentaxlsweb(b, id, wb);
        } else {
			Invoke(id, "Quit", NULL, DISPATCH_METHOD, 0);
		}
    } else {
		visibleexcel(id, TRUE);
	}
	liberaidispatch(hoja);;
	liberaidispatch(wb);
	liberaidispatch(id);
	finole();
	return(0);
}
int cur2excel(v10cursors *cur,char *plantilla,char *destino,int salir)
{
    return(bloqcur2excel(NULL,cur,plantilla,destino,salir));
}
    
int bloqsql2excel(bloques *b,char *sql,char *plantilla,char *destino,int salir)
{
    v10cursors *cur;
    int ret;
    cur=abrecursornombre("SQL2EXCEL",sql);
    definetododinamico(cur);
    ret=bloqcur2excel(b,cur,plantilla,destino,salir);
    liberacursor(cur);
    return(ret);
}

int sql2excel(char *sql,char *plantilla,char *destino,int salir)
{
    return(bloqsql2excel(NULL,sql,plantilla,destino,salir));
}
