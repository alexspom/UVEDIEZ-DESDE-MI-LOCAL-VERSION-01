/*******************************************************************************
* Módulo : vdconversionaux.c                                                   *
* Función: Rutinas auxiliares para manejo de conversiones                      *
*                                                                              *
*                                                                              *
* Autor	 : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/
#include "vd.h"

#define CCONVIERTEART "BEGIN :RET:=VDART.VD2HOSTD(:CANTIDAD,:CODART,:DECIMALES); END;"
static v10cursors *v10convierteart;

#define CCONVIERTEINVART "BEGIN :RET:=VDART.HOST2VD(:CANTIDAD,:CODART); END;"
static v10cursors *v10convierteinvart;

#define CCONVIERTE "BEGIN :RET:=VDART.CONVIERTED(:CANTIDAD,:UNIORI,:UNIDEST,:DECIMALES); END;"
static v10cursors *v10convierte;

typedef struct {
    double ret;
    double cantidad;
    int  decimales;
    char codart[LCODART];
    char uniori[LUNIDADES];
    char unidest[LUNIDADES];
} conversiones;

static conversiones sart;

static void finconversiones(void)
{
    liberacursor(v10convierteart);
    liberacursor(v10convierteinvart);
    liberacursor(v10convierte);
}

static void initconversiones(void)
{
    v10convierteart = abrecursordebug(CCONVIERTEART,0);
    bindtodo(v10convierteart, "RET", &sart.ret, sizeof(sart.ret), V10DOUBLE,
                              "CANTIDAD", &sart.cantidad, sizeof(sart.cantidad), V10DOUBLE,
                              "DECIMALES", &sart.decimales, sizeof(sart.decimales), V10INT,
                              "CODART", sart.codart, sizeof(sart.codart), V10CADENA,
                              NULL);
    v10convierteinvart = abrecursordebug(CCONVIERTEINVART, 0);
    bindtodo(v10convierteinvart, "RET", &sart.ret, sizeof(sart.ret), V10DOUBLE,
             "CANTIDAD", &sart.cantidad, sizeof(sart.cantidad), V10DOUBLE,
             "CODART", sart.codart, sizeof(sart.codart), V10CADENA,
             NULL);
    v10convierte = abrecursordebug(CCONVIERTE, 0);
    bindtodo(v10convierte, "RET", &sart.ret, sizeof(sart.ret), V10DOUBLE,
             "CANTIDAD", &sart.cantidad, sizeof(sart.cantidad), V10DOUBLE,
             "DECIMALES", &sart.decimales, sizeof(sart.decimales), V10INT,
             "UNIORI", sart.uniori, sizeof(sart.uniori), V10CADENA,
             "UNIDEST", sart.unidest, sizeof(sart.unidest), V10CADENA,
             NULL);
    atexit(finconversiones);
}

double convierteunidades(double cantidad,char *unidadorigen,char *unidaddestino)
{
    if (v10convierteart == NULL) initconversiones();
    strcpy(sart.uniori, unidadorigen);
    strcpy(sart.unidest, unidaddestino);
    sart.cantidad = cantidad;
    ejecutacursor(v10convierte);
    return sart.ret;
}

double conviertearticulo2host(double cantidad,char *codart,int *decimales)
{
    if (v10convierteart == NULL) initconversiones();
    strcpy(sart.codart, codart);
    sart.cantidad = cantidad;
    sart.decimales = 0;
    ejecutacursor(v10convierteart);
    if (decimales) *decimales = sart.decimales;
    return sart.ret;
}

double conviertearticulo2v10(double cantidad,char *codart)
{
    if (v10convierteart == NULL) initconversiones();
    strcpy(sart.codart, codart);
    sart.cantidad = cantidad;
    ejecutacursor(v10convierteinvart);
    return sart.ret;
}