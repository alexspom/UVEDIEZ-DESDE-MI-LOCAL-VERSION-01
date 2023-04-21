/*******************************************************************************
* Módulo : vdinterfasescarga.c                                                 *
* Función: Carga las interfases de entrada estándar en las tablas de interfases*
*          intermedias.                                                        *
*                                                                              *
* Autor  : ICC                                                                 *
* Revisado por:                                                                *
* Fecha  : 14-04-2008                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/
#include "vdinterfase.h"

int iConLineas=0;
int iConLinTot=0;


int iInsCabInterf(char *azNombFichero, long *codinterfase, vdinterfasecabs *intc) {

	vdinterfcargacabs icc;

	memset(&icc,0,sizeof(icc));

	if (ICCselvdsecinterf(&icc.codinterfase)) {
		v10log(LOGERROR,"iInsCabInterf: error seleccionando el código de interfase para el fichero %s\n", icc.fichero);
	    return -1;
	}
	strcpy(icc.tipointerfase,intc->tipointerfase);
	strcpy(icc.formato, intc->formato);
	strcpy(icc.fichero, azNombFichero);
	icc.status = STICCPENDPROCES;
	if (ICCinsert(&icc,NOVERIFICA)) {
	    v10log(LOGERROR,"iInsCabInterf: error insertando la cabecera del fichero %s\n", icc.fichero);
	    return -1;
	}
	
	*codinterfase = icc.codinterfase;
	return 0;
}

//Guarda en las tablas de interfases las líneas de los ficheros
static int cargaregfich(char *azfichero, char *azNombFichero, vdinterfasecabs *intc) {

	char azLinea[LREGISTRO];
	int  sep=0;
	char formato[LFORMATO];

	vdinterfcargalins icl;
	vdinterfaselins intl;

	FILE *fd;

	memset(&intl,0,sizeof(intl));
	memset(&icl,0,sizeof(icl));
	memset(azLinea,0,sizeof(azLinea));

	if ((fd=fopen(azfichero, "r")) == NULL) {
		v10log(LOGERROR,"cargaregfich: no puedo abrir el fichero %s\n", azfichero);
        return -1;
	}
   //Si hay separador y se indica inicialmente el formato, hay que eliminar el separador cuando se inserte la línea.
	if (*intc->separador && (intc->longformato > 0) ) sep=1;

	strcpy(icl.tipointerfase, intc->tipointerfase);
	strcpy(icl.formato, intc->formato);
	icl.status = STICLPENDPROCES;

	//Inserta la línea
	iConLinTot=0;
	while (fgets(azLinea, LREGISTRO-1, fd) != NULL) {	

		iConLinTot++;
		if (intc->longformato > 0) {
			strncpy(formato, azLinea, intc->longformato);
			formato[intc->longformato]=0;
			if (strcmp(trim(formato), intc->formato)) continue;
		}
		if (icl.numreg == 0)
			if (iInsCabInterf(azNombFichero, &icl.codinterfase, intc)) {
				fclose(fd);//RIK cierro fichero porque si da error no puede llevarlo al bak. 09-03-2011
				return -1;
			}

		if (azLinea[strlen(azLinea)-1]=='\n') azLinea[strlen(azLinea)-1]=0;
		icl.numreg++;
		strncpy(icl.registro, azLinea+intc->longformato+sep, LREGISTRO);

		if (ICLinsert(&icl,NOVERIFICA)) {
			v10log(LOGERROR,"cargaregfich: no puedo insertar la línea nº %d del fichero %s\n", icl.numreg, azfichero);
			return -1;
		}
		iConLineas++;
		memset(azLinea,0,sizeof(azLinea));
	}//Fin del while que lee línea a línea.


	fclose(fd);

  return 0;
}

//Busca los ficheros a tratar y los carga en las tablas
VDEXPORT void vdcargaficheros(procesos *proceso) {

  WIN32_FIND_DATA fdata;
  HANDLE dhandle;
  char ruta[LBUZONIN+32];
  char semaforo[LBUZONIN+10];
  char azfichero[100];
  char azCont[LSECUENCIAL];
  char azPrefijo[LPREFFICHERO];
  char azFinFich[150];
  char nombredef[100];
  char azNombFichero[LPREFFICHERO+30];
  char cOk='N';
  char cErrorCarga='N';
  char fechafich[7],
       horafich[7],
       horaaux[9];
  int  iLong=0;

  vddiviss div;
  vdinterfasecabs intc;
  vdinterfasecabs intcx;
  vdinterfcargacabs icc;

  memset(&icc,0,sizeof(icc));
  memset(&intc,0,sizeof(intc));
  memset(&intcx,0,sizeof(intcx));
  memset(&div,0,sizeof(div));
  strcpy(azFinFich,"");

//Recupera los directorios donde se encuentran los ficheros
  if ((DIVbuscatodo(&div))) return;
  do {
  //Si no está informada la ruta, no carga los ficheros de esa división.
	  if (!(*div.buzonin)) continue;
       //Ver si está el semáforo levantado.
	  sprintf(semaforo,"%s\\SEMAFORO", div.buzonin);
	  if (!access(semaforo,0))  continue;	
      //Busca dentro de los directorios de entrada si hay algún fichero que tratar.
	  sprintf(ruta,  "%s\\*",div.buzonin);
	  if ((dhandle=FindFirstFile(ruta,&fdata)) == INVALID_HANDLE_VALUE) {
		  v10log(LOGERROR,"vdcargaficheros: No existe la ruta %s indicada en la división %s", div.buzonin, div.coddiv);
		  continue;
	  }
	  do {
		  //Valida que es un fichero a tratar.
		  if (INTCbuscatipofichero("E", &intc)) {
			  v10log(LOGERROR,"%s","vdcargaficheros: No se han definido interfases de entrada");
			  return;
		  }
		  do {
			  iLong = (int)strlen(intc.preffichero);
			  strncpy(azPrefijo, fdata.cFileName,iLong);
			  azPrefijo[iLong]=0;
			  if (!(strcmp(azPrefijo, intc.preffichero))) {
				  cOk='S';
				  break;
			  }
		  }while (!(INTCnexttipofichero(&intc)));

		  if (cOk == 'N') continue;

		  cOk='N';

		  strcpy(azNombFichero, fdata.cFileName); //Nombre por defecto.

		  if (*intc.formatofich == '1') { //Comprueba si el secuencial es el esperado.
			  strncpy(azFinFich, fdata.cFileName+iLong,50);
			  piece(azFinFich, azCont, ".",1);
			  if (intc.secuencial+1 != atoi(azCont) ) {
				  v10log(LOGERROR,"vdcargaficheros: el secuencial esperado para el tipo de fichero %s es %d y no %s\n", intc.preffichero,intc.secuencial+1, azCont);
				  continue;
			  }
		  } else if (*intc.formatofich == '0') { //Completa el nombre del fichero con la fecha y el día
			  jul2a(damedate(),"DDMMYY",fechafich);
			  cent2a(gettime(),0,':',horaaux);
			  sprintf(horafich,"%2.2s%2.2s%2.2s",horaaux,horaaux+3,horaaux+6);

			  sprintf(azNombFichero, "%s%s%s.%s", intc.preffichero, fechafich, horafich, intc.extfichero);
		  }

		  //Selecciona por el tipo de interfase obtenido, tratando cada uno de los tipo de registros que pudiese haber en el fichero
		  iConLineas=0;
		  cErrorCarga= 'N';
		  sprintf(azfichero,"%s\\%s", div.buzonin, fdata.cFileName);
		  INTCbuscatipointerfase(intc.tipointerfase,&intcx);
		  do {//En caso de que sólo haya un formato
			  if ((intc.longformato == 0) && (strcmp(intc.formato, intcx.formato))) continue;
			  if (cargaregfich(azfichero,azNombFichero, &intcx)) {
				  cErrorCarga= 'S';
				  break;
			  }
			  if (*intcx.formatofich == '1') { //Actualizar la secuencia del tipo de fichero
				  intcx.secuencial= atoi(azCont);
				  if (INTCactualizasecuencial(&intcx,NOVERIFICA)){
					  v10log(LOGERROR,"vdCargaFicheros: error actualizando el secuencial del fichero %s\n", icc.fichero);
					  continue;
				  }
			  }
		   } while (!(INTCnexttipointerfase(&intcx)));

          if (cErrorCarga=='S') {//Mueve el fichero al directorio err
			  rollback();
			  sprintf(nombredef, "%s\\ERR\\%s", div.buzonin, azNombFichero);
			  v10log(LOGERROR,"Fichero %s con errores, movido al directorio ERR, registros tratados %d, registros totales %d\n", azNombFichero, iConLineas, iConLinTot);
		  } else {//Mueve el fichero al directorio bak
			  sprintf(nombredef, "%s\\BAK\\%s", div.buzonin, azNombFichero);
			  v10log(LOGNORMAL,"Fichero %s cargado correctamente, registros tratados %d, registros totales %d\n", azNombFichero, iConLineas, iConLinTot);
		  }
		  MoveFile(azfichero,nombredef);
	  }while (FindNextFile(dhandle, &fdata));

	  commit();
      FindClose(dhandle);
  }while (!(DIVnexttodo(&div)));

  return;
}
