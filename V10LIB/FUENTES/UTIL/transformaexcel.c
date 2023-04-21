
#include "forms\v10form.h"

#define xlExcel8 56

int transformaexcel(char *nombre, char *destino)
{
    IDispatch *id, *hoja, *wb;
    VARIANTARG varg1;
    int ret;
    id = startole("Excel.Application", 0);
    if (id == NULL) {
        mensajefcm(10, "Aplicacion %s no instalada", "Excel");
        finole();
        return(-1);
    }
    ret = cargaexcel(id, &wb, &hoja, nombre);
    ClearAllArgs();
    AddArgumentString("Filename", 0, destino);
    AddArgumentInt2("FileFormat",xlExcel8);
    Invoke(wb, "SaveAs", &varg1, DISPATCH_METHOD, 0);
    ReleaseVariant(&varg1);
    ClearAllArgs();
    Invoke(id, "Quit", NULL, DISPATCH_METHOD, 0);
    liberaidispatch(hoja);;
    liberaidispatch(wb);
    liberaidispatch(id);
    finole();
    return(0);
}

int main(int argc, char *argv[])
{
    initv10log("TRANSFORMAEXCEL.LOG");
    if (argc<3) final(("Uso TRANSFORMAEXCEL FICHEXCEL DESTINO"));
    transformaexcel(argv[1], argv[2]);
    return(0);
}

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
                   LPSTR cmd, int cmdshow)
{
    int ret;
    strcpy(TITULOVENTANA, "TRANSFORMACION DE FICHEROS EXCEL 1.0");
    initv10lib(hinst, hprev);
    trataparamstd(__argc, __argv, trataparammain, NULL);
    ret = main(__argc, __argv);
    return(ret);
}
