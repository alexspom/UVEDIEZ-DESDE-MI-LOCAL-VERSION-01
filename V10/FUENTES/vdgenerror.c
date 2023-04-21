#include "vd.h"



#define LABREVIADAEXT	(16+1)
#define LBUFFER			(512+1)


#define FILE_MENSADEF	"VDERROR.H"

#define SELMOD "SELECT MODULO,DESMODULO,ABREVIADA "\
	             " FROM VDMODULOS "\
				" ORDER BY MODULO"
static v10cursors *vdselmod;

#define SELMENSA "SELECT MEN.CODERROR,MEN.MENSAJE,MEN.TIPOERROR,MEN.ABREVIADA, "\
	                   " DECODE(MEN.TIPOERROR,'I',1,'W',2,3) VTIPO "\
						"FROM VDMENSAJES MEN "\
                    	"WHERE MEN.MODULO=:MODULO "\
                    	"ORDER BY MEN.MODULO,MEN.TIPOERROR,MEN.CODERROR"
static v10cursors *vdselmensa;

typedef struct {
	      long modulo;
		  char desmodulo[LDESMODULO];
		  char abmodulo[LABREVIADA];
		  long coderror;
		  char tipoerror[LTIPOERROR];
		  long vtipo;
		  char abreviada[LABREVIADA];
		  char mensaje[LMENSAJE];
} vdmensajes;
static vdmensajes vdm;


static void finvdgenerror(void)
{
    liberacursor(vdselmensa);
    liberacursor(vdselmod);
}

static void initvdgenerror(void)
{
	vdselmod=abrecursor(SELMOD);
	definetodo(vdselmod,&vdm.modulo,sizeof(vdm.modulo),V10LONG,
		                vdm.desmodulo,sizeof(vdm.desmodulo),V10CADENA,
						vdm.abmodulo,sizeof(vdm.abmodulo),V10CADENA,
						NULL);
    vdselmensa=abrecursor(SELMENSA);
    definetodo(vdselmensa,&vdm.coderror,sizeof(vdm.coderror),V10LONG,
		                   vdm.mensaje,sizeof(vdm.mensaje),V10CADENA,
						   vdm.tipoerror,sizeof(vdm.tipoerror),V10CADENA,
						   vdm.abreviada,sizeof(vdm.abreviada),V10CADENA,
						   &vdm.vtipo,sizeof(vdm.vtipo),V10LONG,
						   NULL);
	bindtodo(vdselmensa,"MODULO",&vdm.modulo,sizeof(vdm.modulo),V10LONG,
		                NULL);
	atexit(finvdgenerror);
}


////////////////Generación de include conteniendo definiciones de mensajes ///////////////

int generafichero(void)
{
    FILE *salida;
    long codigo;
    char fecha[20];

    if (!vdselmensa) initvdgenerror();
	jul2a(damedate(),"DD-MM-Y.YY",fecha);
    if (NULL== (salida=fopen(FILE_MENSADEF,"w+t"))) return(GetLastError());
    fprintf(salida,"/*************************************************************************************************\n"
              "* Módulo: "FILE_MENSADEF"\n"
              "* Propósito: Declaración de los identificadores de mensajes almacenados en la base de datos\n"
              "* Autor: Construcción automática\n"
              "* Fecha: %s\n"
              "**************************************************************************************************/\n\n\n",
              fecha);

	fprintf(salida,"#ifndef __VDERROR__H__\n#define __VDERROR__H__\n\n");

	ejecutacursor(vdselmod);
	while (fetchcursor(vdselmod)==0) {
		  fprintf(salida,"// Modulo %d %s\n",vdm.modulo,vdm.desmodulo);
          ejecutacursor(vdselmensa);
		  while (!fetchcursor(vdselmensa)) { 
                codigo=(vdm.vtipo << 30) | (vdm.modulo << 16) | vdm.coderror;
		        fprintf(salida,"#define VD_%s%s\t\t0x%lX\t\t/* %s */\n",vdm.tipoerror,vdm.abreviada,codigo,vdm.mensaje);
		  }

    }
	fprintf(salida,"\n\n#endif\n");
    fclose(salida);
    return(0);
}




int main(int argc, char **argv)
{
    imprimep(0,0,0x0000ffff,0x0000007f,"      GENERADOR DE defines DE ERROR ",0,100);
    if (argc < 2) final(("Uso: VDGENERROR usuario/password"));
    initv10log("MENSAGEN.LOG");

    generafichero();
  	return(0);
}

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
           LPSTR cmd, int cmdshow)
{
  int ret;
  initv10lib(hinst,hprev);
  trataparamstd(__argc,__argv,trataparammain,trataparamoracle,NULL);
  ret=main(__argc,__argv);
  return(ret);
}