#include "v10etiqueta.h"


int main(int argc,char *argv[])
{
    idatos *idatoart=NULL;
    int ret;
    leevsq("VDETIART.VSQ");
    ret=imprimeetiqueta("ZPL",&idatoart,"CSELART","VDARTIC.GEN","KK",1,-1,0,5,"CODART",V10CADENA,2,"1","CODLOT",V10CADENA,2,"A",NULL);
    if (ret) mensajefcm(10,"No puedo imprimir etiqueta");
    return(0);
}

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
                   LPSTR cmd, int cmdshow)
{
    int ret;
    v10hinst=hinst;
    v10hprev=hprev;
    trataparamstd(_argc,_argv,trataparampremain,NULL);
    initapptxt(hinst,hprev,SW_SHOWMAXIMIZED,TITULOVENTANA,CW_USEDEFAULT,CW_USEDEFAULT,
        0,0,COLUMNASPANTALLA,LINEASPANTALLA,ESTILOV10,0,NULL,0,0,NULL);
    trataparamstd(_argc,_argv,trataparammain,trataparamoracle,NULL);
    ret=main(_argc,_argv);
    return(ret);
}