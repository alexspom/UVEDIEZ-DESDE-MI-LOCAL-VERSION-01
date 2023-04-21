/**************************************************************************
* M�dulo : borralog.c													  *
* Funci�n: Borrar ficheros con m�s antiguos que las horas especificadas   *
* Autor	:  												                  *
* Fecha  : 01-04-2009													  *
***************************************************************************
*Hist�rico de cambios
********************
****************************************************************************/
#include "v10ora.h"
/*int meses[]={31,28,31,30,31,30,31,31,30,31,30,31};

long vddamemesydia(long numdias,SYSTEMTIME *st)
{
	while(numdias>0){
		if (numdias<st->wDay) {
			st->wDay-=(unsigned short)numdias;
			break;
		}
		numdias-=st->wDay;
		st->wMonth--;
		if (st->wMonth<1){
			st->wYear--;
			st->wMonth=12;
		}
		st->wDay=meses[st->wMonth-1];
	}
	return(st->wMonth);
}

void borrafichero(WIN32_FIND_DATA *pfd,char *drive,char *dir) {
  SYSTEMTIME stUTC, stLocal;
  char name[MAXPATH];

  FileTimeToSystemTime(&pfd->ftLastWriteTime, &stUTC);
  SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

  sprintf(name,"%s%s%s",drive,dir,pfd->cFileName);
  unlink(name);
  v10log(LOGNORMAL,"\tBorrado fichero %-32.32s\n"
	               "\t\t\t\t\t\t\t\t\t\t\tcon fecha de �ltima escritura %02d-%02d-%02d %02d:%02d:%02d\n"
	               "\t\t\t\t\t\t\t\t\t\t\tRuta completa: %s\n",
		pfd->cFileName,stLocal.wDay, stLocal.wMonth, stLocal.wYear, stLocal.wHour, stLocal.wMinute, stLocal.wSecond,name);
}
*/
// Par�metros: Horas Path_M�scara
int main(int argc,char *argv[])
{
    strcpy(TITULOVENTANA,"BORRADOR DE LOGs V10. VERSION 1.0");
    initv10lib(v10hinst,v10hprev);
    trataparamstd(argc,argv,trataparampremain,trataparammain,trataparamoracle,NULL);
	/*WIN32_FIND_DATA fd;
	SYSTEMTIME st;
	FILETIME ft;
	HANDLE h;
	int lNumDias,lResto,lHoras;
	int flag=0;
	char drive[5];
	char dir[MAXPATH];
	char name[MAXPATH];
	char ext[MAXPATH];
	v10horas tinit;

	if (argc < 3) {
		v10log(LOGNORMAL,"USO : VDBORRALOG horas_antiguo mascara\n");
		return(-1);
	}
	_splitpath(argv[2], drive, dir, name, ext);
	//El objetivo es obtener la fecha a partir de la cual borrar y entonces borrar ficheros m�s antiguos
	lHoras = atol(argv[1]);
	lNumDias=lHoras/24;   	        //Dias enteros
	lResto=lHoras%24;
	GetLocalTime(&st);
	//Normalizaci�n a un a�o
	st.wYear -=(lNumDias/365);		// A�os a restar
	lNumDias = lNumDias % 365;	    // Normalizado a un a�o

	//Restamos a la fecha actual las horas especificadas. Si la fecha del fichero es mayor
	// que la fecha obtenida no hay que borrar. En caso contrario borrar
	if (st.wHour > lResto) st.wHour -= (short)lResto;
	else {
		lNumDias++;
		st.wHour = (24-(lResto-st.wHour));
	}
	vddamemesydia(lNumDias,&st);

	if (FALSE==SystemTimeToFileTime(&st,&ft)) return(-1);
	v10log(LOGNORMAL,"Analizando ficheros ...\n");
	h = FindFirstFile((LPCSTR)argv[2],&fd);
	while (h != INVALID_HANDLE_VALUE) {
		if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)==0) {
	       v10log(LOGNORMAL,"Analizando fichero %s\n", fd.cFileName);
		   if (CompareFileTime(&fd.ftLastWriteTime,&ft )==-1) borrafichero(&fd,drive,dir);
		}
		if (!FindNextFile(h,&fd)) h=INVALID_HANDLE_VALUE;
	}
	tinit=damecent();
	do {
		// espera 5 segundos
		if (hay_tecla()) tecla();
		Sleep(10);
	} while (damecent()-tinit<500);*/
    tecla();
	return(0);
}

#ifndef __LINUX__
int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
                   LPSTR cmd, int cmdshow)
{
    int ret;
    ret=main(__argc,__argv);
    return(ret);
}
#endif