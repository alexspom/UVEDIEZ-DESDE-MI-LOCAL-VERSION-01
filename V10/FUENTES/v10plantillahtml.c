#include "vdform.h"
#include "v10wwwform.h"

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
				   LPSTR cmd, int cmdshow)
{
	static char nombrefrm[MAXCADENA];
	HWND ventanaact;
	forms *f;
	int i;

	v10hinst=hinst;
	v10hprev=hprev;
	
	strcat(TITULOVENTANA,"Generador de Plantilla de Formulario");
	COLUMNASPANTALLA=99;
	ventanaact=FindWindow(NULL,TITULOVENTANA);
	if (ventanaact!=NULL) exit(0); // ya existe el programa
    trataparamstd(_argc,_argv,trataparampremain,NULL);
    initapptxt(hinst,hprev,SW_SHOWMAXIMIZED,TITULOVENTANA,CW_USEDEFAULT,CW_USEDEFAULT,
        0,0,COLUMNASPANTALLA,LINEASPANTALLA,ESTILOV10,0,NULL,0,0,NULL);    
    trataparamstd(_argc,_argv,trataparammain,trataparamoracle,NULL);	v10usaansi=1;
	damecaracextracampo=leedefectocampo;
	damecaracextrabloque=leedefectobloque;
	inittriger();
	inittriguser();
	inittrigcolores();
	//inittrigersform("P");
	usa_colores("PICVENT");
	initv10log("v10plantillahtml.log");
	f=leeform(_argv[2],NULL);
	formglobal=f;
	v10form2plantillahtml(f,_argv[3]);
	for (i=0;i<f->nbloques;i++) v10bloque2plantillahtml(f->b[i],_argv[3]);
	return(0);
} 
