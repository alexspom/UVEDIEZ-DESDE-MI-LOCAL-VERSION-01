/*
* Módulo : EXCEL2ORACLE.C                                              
* Objeto:  Importar una hoja Excel en una tabla ORACLE
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007
* Exporta una sentancia SQL a EXCEL

* MODIFICACIONES
* ---------------------------
*/
#include "forms\v10form.h"

int nodebugdrop(int oraerr,v10cursors *v10)
{
	if (oraerr==942) return(1);
	return(0);
}

int main(int argc,char *argv[])
{
    int borrar = 0, std = 1;
    initv10log("EXCEL2ORACLE.LOG");
    if (argc<4) final(("Uso EXEL2ORACLE -OUUSR/PWD FICHEXCEL TABLAORACLE [BORRAR(0 NO BORRAR/1 DROP/2 TRUNCATE)] [STANDAR(0/1)]"));
    if (argc>4) borrar=atoi(argv[4]);
    if (argc>5) std=atoi(argv[5]);
	handleoraerr=nodebugdrop;
    excel2ora(argv[2],argv[3],borrar,std);
    return(0);
}

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
                   LPSTR cmd, int cmdshow)
{
    int ret;
	strcpy(TITULOVENTANA,"IMPORTACION DE FICHEROS EXCEL 1.0");    
	initv10lib(hinst,hprev);
    trataparamstd(__argc,__argv,trataparammain,trataparamoracle,NULL);
    ret=main(__argc,__argv);
    return(ret);
}
