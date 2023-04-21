/*******************************************************************************
* Módulo : vdinterent.c                                                      *
* Función: Guarda en las tablas definitivas los datos que se hayan guardado en *
*          las tablas intermedias de interfases, el valor de cada campo        *
*          dependerá de si tiene o no función asociada el campo o el registro  *
*          completo.                                                           *
*                                                                              *
* Autor  : ICC                                                                 *
* Revisado por:                                                                *
* Fecha  : 14-04-2008                                                          *
********************************************************************************
* Histórico de cambios
* ====================* 
* (1) ICC. 28-11-2008. Tratamiento de error cuando se parametriza el campo accion 
*          como incluido y no viene en el fichero
* (2) ICC. 28-11-2008. Si error, se sale para hacer el Rollback
*******************************************************************************/

#include "vdinterfase.h"


char error='N';
char cAccion='X';
int nt=0; //Estructuras totales a crear, depende de la tabla VDINTERFASETAB

typedef struct {
        char tipointerfase[LTIPOINTERFASE];
		char formato[LFORMATO];
        long codinterfase;
	} antregistro;
antregistro ant;   

long codinterfaseesphijo[100];

int h=0; //contador del array de interfases que esperan a cargar sus hijos.

typedef struct {
        char        azTabla[LTABLA];
		char        azTablaAlias[LTABLAALIAS];
        diccionario *dic;
		void        *ptr;
		char        azLibreria[LLIBRERIA];
        char        azFuncIns[100];
        char        azFuncDel[100];
		char        azFuncUpd[100];
		char        azFuncSel[100];
		char        azFuncSelPK[100];
		char        azCursorIns[100];
		char        azCursorDel[100];
		char        azCursorUpd[100];
		char        azCursorSelPK[100];
		int tto;     //indicador de si se ha actualizado o no
} vddics;
static vddics stvddics[50];


//Actualiza el status y el mensaje de la línea de interfase
VDEXPORT void actstatuslin(vdinterfcargalins *icl, char error) {

	if (error=='S') {
		rollback();
		strcat(icl->mensaje,"\n");
		v10log(LOGERROR,"%s",icl->mensaje);
	    ICLactualizastmsg(icl, NOVERIFICA);
	    commit();
	}else {
		strcpy(icl->mensaje,"");
		icl->status = STICLPROCESADO;
		ICLactualizastmsg(icl, NOVERIFICA);
	}
        

	return;
}

//Actualiza el status de la cabecera de interfase
VDEXPORT void actstatuscab(long codinterfase, char error, char cCompruebaHijo) {

	vdinterfcargacabs icc;
	vdinterfasecabs intc;

	if (ICCselvdinterfcargacab(codinterfase,&icc)) {
		v10log(LOGERROR,"\nERROR seleccionando la cabecera de interfase con codinterfase %d", codinterfase);
		return;
	}

	if (error == 'S') {
		rollback();
		icc.status = (-1)*icc.status;
		v10log(LOGNORMAL,"Fichero %s con errores, código de interfase %d\n\n", icc.fichero,icc.codinterfase);
		
		if (ICCactualizastatus(&icc,NOVERIFICA))
			v10log(LOGERROR,"\nERROR al actualizar la tabla de cabeceras de interfase con codinterfase %d\n",  icc.codinterfase);
		commit();
	}
    else {
		icc.status = 200;
		
		if (ICCactualizastatus(&icc,NOVERIFICA))
		    v10log(LOGERROR,"\nERROR al actualizar la tabla de cabeceras de interfase con codinterfase %d\n",  icc.codinterfase);

		if (cCompruebaHijo=='N') {
			commit();
			v10log(LOGNORMAL,"Fichero %s cargado sin errores, código de interfase %d\n\n", icc.fichero,icc.codinterfase);
		} else {
			INTCselvdinterfasecab(icc.tipointerfase,icc.formato, &intc);

	   	    // Si tiene un hijo, este todavía no se ha tratado, ya que se tratan en orden, con lo que todavía no se hace commit
		    if (INTCselhijo(icc.tipointerfase,icc.formato, &intc)) {
  			    commit();
		  	    v10log(LOGNORMAL,"Fichero %s cargado sin errores, código de interfase %d\n\n", icc.fichero,icc.codinterfase);
			}
		    else { 
			    v10log(LOGNORMAL,"Fichero %s sin errores, esperando a la carga de sus hijos,código de interfase %d,\n interfase: %s hijo: %s\n\n", icc.fichero,icc.codinterfase, intc.tipointerfase, intc.formato);
			    codinterfaseesphijo[h]=icc.codinterfase;
			    h++;
			}
		}
	}


return;
}
// Cargamos la estructura de cada tabla con los diccionarios, estructuras de datos y funciones a utilizar.
static int cargadics(void) {

	diccionario *(*fFuncionDic)(void);
	char funcion[LFUNCION];
	char buffer[MAXCADENA];

	vdinterfasetabs intt;

	//Recorre las estructuras a declarar
    if (INTTbuscatodo(&intt)) return -1;

	nt=0;
	do {
		memset(&buffer,0,MAXCADENA);
		stvddics[nt].ptr=calloc(MAXCADENA,1);
	    memcpy(stvddics[nt].ptr,&buffer,MAXCADENA);

		strcpy(stvddics[nt].azTabla, intt.tabla);
		strcpy(stvddics[nt].azTablaAlias,intt.tablaalias);
		sprintf(funcion, "%sdamediccionario", intt.abreviatura);
		strcpy(stvddics[nt].azLibreria, intt.libreria);
		fFuncionDic=damefundll(intt.libreria, funcion);
		if (fFuncionDic==0) {
			v10log(LOGERROR,"\nNo se han creado el cursor %s para la tabla %s\n\n", funcion, intt.tabla);
			return -1;
		}
		stvddics[nt].dic=fFuncionDic();
		sprintf(stvddics[nt].azFuncIns, "%sinsert", intt.abreviatura);
		sprintf(stvddics[nt].azFuncDel, "%sdel", intt.abreviatura);
		sprintf(stvddics[nt].azFuncUpd, "%sactualiza%s", intt.abreviatura,strmin(intt.tabla));
		sprintf(stvddics[nt].azFuncSelPK, "%sinter",intt.abreviatura);
		sprintf(stvddics[nt].azCursorIns, "INS%s",intt.abreviatura);
		sprintf(stvddics[nt].azCursorDel, "DEL%s",intt.abreviatura);
		sprintf(stvddics[nt].azCursorUpd, "UPDA%s",intt.abreviatura);
		sprintf(stvddics[nt].azCursorSelPK, "SEL%s%s",intt.abreviatura,strmay(intt.tabla));
		sprintf(stvddics[nt].azFuncSel, "%sselrowid", intt.abreviatura);
		stvddics[nt].tto=0;
		
		nt++;
	} while (!(INTTnexttodo(&intt)));

	strcpy(stvddics[nt].azTabla, "FUNCION");
	strcpy(stvddics[nt].azTablaAlias, "FUNCION");
	nt++;
	strcpy(stvddics[nt].azTabla, "DUMMY");
	strcpy(stvddics[nt].azTablaAlias, "DUMMY");

return 0;
}

//Busca la posición donde se encuentran los datos de la tabla a cargar
static int BuscaDic(char *tabla) {

	int  i=0;

	for (i=0;i<nt;i++) {
		if (!(strcmp(tabla, stvddics[i].azTablaAlias))) {
		    stvddics[i].tto=1;
			return i;
		}
	}

return (-1);
}

//Cargar datos en las estructuras de las tablas.
static int CargaEstr(vdinterfasecabs *intc, vdinterfcargalins *icl) {

	char *(*fFuncionCampo)(char *valor, char *campo, vdinterfcargalins *icl);
	char *(*fFuncionCampoP)(char *valor, char *campo, vdinterfcargalins *icl, char *params);
	char tabla_ant[LTABLA];
	char azVar[512];
	char azVar2[512];
	char azCampo[512];
	char cSep;
	int inicio=0, i=0, sep=0, orden_ant=0, longitud=0, longitud_ant=0;
	int  cont=1; //se utiliza cuando no es de longitud fija y siempre se empieza en el segundo campo, porque el primero es el tipo de registro
	vdinterfaselins intl;

	memset(&intl,0,sizeof(vdinterfaselins));
	memset(azVar,0,sizeof(azVar));
	memset(azVar2,0,sizeof(azVar2));
	memset(azCampo,0,sizeof(azCampo));

	if (INTLbuscatipoformato(icl->tipointerfase, icl->formato, &intl)) {
		sprintf(icl->mensaje, "No está definido el tipo de interfase %s para el formato %s", icl->tipointerfase, icl->formato);
		return -1;
	}
	if (cAccion != 'M') {
		if ((strcmp(intl.campo, "ACCION")) || (*intl.swtactivo =='N'))
//			cAccion = 'C';
			cAccion = 'A';
		else
		    cAccion = icl->registro[0];
	}
	if (strcmp(intc->separador,"")) sep=1;

	do {
       // (1i)
/*       if (!(strcmp(intl.campo, "ACCION"))) {
			if (((cAccion=='M') ||(cAccion=='C') ||(cAccion=='B') ) && 
				((icl->registro[1]==*intc->separador) || (strcmp(intc->separador,"")!=0 ))) {
				inicio = inicio + intl.longitud + sep;
			    continue; //saltamos el campo acción
			}else{
				strcpy(icl->mensaje, "CargaEstr: Interfase parametrizada con campo ACCION y no se ha incluido en el registro");
				return -1;
			}
		}*/
        // (1f)
		if (!(strcmp(intl.campo, "ACCION"))) {//RIK cambio modificación (1) por lo que hay en Movianto
			inicio = inicio + intl.longitud + sep;
			continue; //saltamos el campo acción
		}

		//Si el orden es el mismo o está inactivo, no avanzamos.
		if ((orden_ant != intl.orden) && (orden_ant != 0) && (*intl.swtactivo =='S')) {
			inicio = inicio + longitud_ant + sep;
		    cont++;
		}
		//Calcular la longitud del campo
		if ((*intc->swtlongfija== 'N') && (*intl.accion != 'A')) {
			piece(icl->registro, azCampo, intc->separador, cont);
			longitud=(int)strlen(azCampo);
		}
		else longitud = intl.longitud;

		if (*intl.swtactivo =='S') {
			orden_ant = intl.orden;
			longitud_ant = longitud;
		}
	if ((*intl.swtactualiza == 'N') && (cAccion == 'M')) continue;

    if ((!(strcmp(intl.tabla,""))) || (!(strcmp(intl.tabla,"DUMMY")))) continue; //No se guarda el dato, se usará después en la parte no estándar
		
		switch(intl.accion[0]) {
			case 'I': //Ignorar, vendrá en el fichero pero no se tratará, ni se guardará su valor por defecto.
				continue;
				break;
			case 'D': //En caso de venir vacío se tomará el valor por defecto.
				if (strcmp(intl.swtactivo, "S")) continue;
				break;
			case 'A'://Añadir, si el campo está inactivo, se guarda el valor por defecto.
				strcpy(azVar2,"");
				break;
			default:
				sprintf(icl->mensaje, "No está definido el procedimiento para la acción %s", intl.accion);
				return -1;
		}
		
		//Ejecuta la función para obtener el valor del campo o validar este
		if ((strcmp(intl.funcion,"")) && (strcmp(intl.libreria,""))) {
			strncpy(azVar, icl->registro+inicio, intl.longitud);
			azVar[intl.longitud]='\0';
			trim(azVar);

			
			if (strcmp(intl.parametros,"")) {//Se han informado parámetros
				fFuncionCampoP=damefundll(intl.libreria, intl.funcion);
				if (!fFuncionCampo) {
					sprintf(icl->mensaje, "CargaEstr: no encuentra la función %s en la librería %s", intl.funcion, intl.libreria);
	                return -1;
		        }
				strcpy(azVar2, fFuncionCampoP(azVar, intl.campo, icl, intl.parametros));
			}else {
				fFuncionCampo=damefundll(intl.libreria, intl.funcion);
				if (!fFuncionCampo) {
					sprintf(icl->mensaje, "CargaEstr: no encuentra la función %s en la librería %s", intl.funcion, intl.libreria);
	                return -1;
		        }
				strcpy(azVar2, fFuncionCampo(azVar, intl.campo, icl));
			}
			if (!(strcmp(azVar2, "-1")) ) return -1;
		}
		//Comprobar si el separador es correcto
		if (strcmp(intc->separador,"") && (intl.orden > 1) && (*intl.accion != 'A')) {
			cSep=icl->registro[inicio-1];
			if (cSep != intc->separador[0]) {
				sprintf(icl->mensaje, "CargaEstr: separador %c, no es el esperado (%s)", cSep, intc->separador);
				return -1;
			}
		}
	  if (strcmp(intl.tabla, "FUNCION")) {
		//Si cambia la tabla busca la posición donde se encuentra
		if (strcmp(intl.tabla, tabla_ant))  i=BuscaDic(intl.tabla);
		if (i<0) {
			sprintf(icl->mensaje, "CargaEstr: no se ha declarado el diccionario de la tabla %s", intl.tabla);
			return -1;
		}	
		
		//Carga los datos en la estructura
		if ( (*intl.funcion && *intl.libreria) || (*intl.accion== 'A') ){
			DICbuff2tabla(stvddics[i].dic, intl.campo, 1, (int)strlen(azVar2), intl.decimales, intl.defecto, azVar2, stvddics[i].ptr);
		}
		else {
			DICbuff2tabla(stvddics[i].dic, intl.campo, inicio+1, longitud, intl.decimales, intl.defecto, icl->registro, stvddics[i].ptr);
		}
	  }
		
		memset(&intl,0,sizeof(vdinterfaselins));
	} while(!(INTLnexttipoformato(&intl))); //Fin del while por campo.



return 0;
}

//Ejecuta la función general y carga la estructura al llamar a la función.
int cargarpers(int n, vdinterfasecabs *intc, vdinterfcargalins *icl) {

	int (*fFuncionGral)( char *tabla, diccionario *dic, char *ptr, vdinterfcargalins *icl);


	if ( (*intc->funcion && *intc->libreria) ) {
		fFuncionGral=damefundll(intc->libreria, intc->funcion);
        if (!fFuncionGral) {
            sprintf(icl->mensaje, "ERROR, no encuentra la función %s en la librería %s", intc->funcion, intc->libreria);
            return -1;
        }
		if (fFuncionGral(stvddics[n].azTabla, stvddics[n].dic, stvddics[n].ptr, icl)) {
			return -1;
		}
	}

return 0;
}

//Buscar por clave primaria
//Posibles errores:
// -1: error general.
// -2: no existen datos.
//
static int selporclave(int n, vdinterfcargalins *icl) {

   int (*fFuncionPK)(char *buffer);

   fFuncionPK=damefundll(stvddics[n].azLibreria, stvddics[n].azFuncSelPK);
   if (!fFuncionPK) {
	   sprintf(icl->mensaje, "ERROR, no encuentra la función %s en la librería %s", stvddics[n].azFuncSelPK,stvddics[n].azLibreria);
       return -1;
   } 
   if (fFuncionPK(stvddics[n].ptr)) {
 	   getcurerrornombre(stvddics[n].azCursorSelPK,icl->mensaje);
	   if (strstr( strmay(icl->mensaje), "NO SE HA ENCONTRADO NINGÚN DATO" )) return (-1);
	   else return (-2);
   }

return 0;
}
//Graba los comentarios que pudiesen haberse guardado durante la carga del registro.
static int grabacomen(vdinterfcargalins *icl) {

	vdartics *art;
	vdpedidocabs *pec;
	vdpedidolins *pel;
	vdlotess *lot;
	long codcomen=0;
	char msgerror[100];
	int n,x;

	memset(&art,0,sizeof(art));
	memset(&pec,0,sizeof(pec));
	memset(&pel,0,sizeof(pel));
	memset(&lot,0,sizeof(lot));

	for (n=0; n<comens.n; n++) { //Recorre todos los comentarios guardados		
	    for (x=0;x<nt;(x++)) { //Busca la posición en la estructura de carga de datos
			if (!strcmp(stvddics[x].azTabla, comens.coms[n].azTabla)) {
				if (!selporclave(x, icl)) {
					if (!strcmp(comens.coms[n].azTabla, "VDPEDIDOCAB")) {
						pec=stvddics[x].ptr;
						codcomen = pec->codcomen;
					} else if (!strcmp(comens.coms[n].azTabla, "VDPEDIDOLIN")) {
						pel=stvddics[x].ptr;
						codcomen = pel->codcomen;
					} else if (!strcmp(comens.coms[n].azTabla, "VDARTIC")) {
						art=stvddics[x].ptr;
						codcomen = art->codcomen;
					} else if (!strcmp(comens.coms[n].azTabla, "VDLOTES")) {
						lot=stvddics[x].ptr;
						codcomen = lot->codcomen;
					} else {
						sprintf(icl->mensaje, "No se pueden guardar comentarios para la tabla %s", comens.coms[n].azTabla);
						return -1;
					}				
					if (v10comen(comens.coms[n].azTabla, codcomen, comens.coms[n].azTipocomen, 1, comens.coms[n].azComentario, msgerror)) {
						strcpy(icl->mensaje, msgerror);
						return -1;
					}
					break;
				}
			}
		}
	}
	//Limpia la estructura de comentarios.
	for (n=0; n<comens.n; n++) {
		memset(&comens.coms[n],0,sizeof(comens.coms[n]));
	}
	comens.n=0;

	return 0;
}

//Carga datos en las tablas correspondientes
static int cargardatos(int n, vdinterfasecabs *intc, vdinterfcargalins *icl) {

	int (*fFuncion)(char *abuffer, int verifica);

	int suma=1;
	int inicio=0;
	int ret=0;
	
	vdintlauxs intlaux;
	memset(&intlaux,0,sizeof(intlaux));

    if (cAccion=='B') {
		suma=-1;
		inicio = nt-1;
	}
	
	//Dependiendo de si inserta, modifica o borra, tendrá que ir en orden creciente o decreciente.
	for (n=inicio;n<nt;(n+=suma)) {
		if (stvddics[n].tto == 1){
			if (!(strcmp(stvddics[n].azTabla, "FUNCION"))) continue;

			if (!(strcmp(stvddics[n].azTabla, "DUMMY"))) {
				if (cargarpers(n, intc, icl)) return (-1);
				continue;
			}
			if (cargarpers(n, intc, icl)) return (-1);
			ret=selporclave(n, icl);
			if (ret==-1) return -1;

			switch(cAccion) {
//			case 'C':
			case 'A':
		    case 'M': //Crear o Modificar
				if (ret == -2) { //Insertar
					//if (cargarpers(n, intc, icl)) return (-1);

					fFuncion=damefundll(stvddics[n].azLibreria, stvddics[n].azFuncIns);
                       if (!fFuncion) {
                           sprintf(icl->mensaje, "ERROR, no encuentra la función %s en la librería %s", stvddics[n].azFuncIns,stvddics[n].azLibreria);
                           return -1;
                       } 
					if (fFuncion(stvddics[n].ptr, NOVERIFICA)) {
						getcurerrornombre(stvddics[n].azCursorIns,icl->mensaje);
						return (-1);
					}
				} else { //	Modificar
					if (*intc->swtactualiza=='N') {
						strcpy(icl->mensaje, "ERROR, ya existe y no se puede modificar, por definición");
                        return (-1);
                    } 
					cAccion='M';
					if (CargaEstr(intc, icl)) return(-1);
					if (cargarpers(n, intc, icl)) return (-1);

					fFuncion=damefundll(stvddics[n].azLibreria, stvddics[n].azFuncUpd);
                    if (!fFuncion) {
                           sprintf(icl->mensaje, "ERROR, no encuentra la función %s en la librería %s", stvddics[n].azFuncUpd, stvddics[n].azLibreria);
                           return (-1);
                    } 
					if (fFuncion(stvddics[n].ptr, NOVERIFICA)) {
						getcurerrornombre(stvddics[n].azCursorUpd,icl->mensaje);
						return (-1);
					}
				}
				break;
			case 'B': //Borrar
				if (ret== -2) {
					sprintf(icl->mensaje, "ERROR, No existe el registro en %s o no se encuentra la clave primaria al completo, falla al borrar", stvddics[n].azTabla);
					return (-1);
				}

				fFuncion=damefundll(stvddics[n].azLibreria, stvddics[n].azFuncDel);
                   if (!fFuncion) {
                       sprintf(icl->mensaje, "ERROR, no encuentra la función %s en la librería %s", stvddics[n].azFuncDel, stvddics[n].azLibreria);
                       return (-1);
                   } 

				if (fFuncion(stvddics[n].ptr, NOVERIFICA)) {
			  	    getcurerrornombre(stvddics[n].azCursorDel,icl->mensaje);
					return (-1);
				}
				break;
			default:
				return (-1);
				} //Fin del switch
		}//Fin de tto=1
		if ((n==0) && (cAccion=='B') ) n=nt+1;
	}//Fin del for

	//Cargar comentarios
	if (grabacomen(icl)) return -1;

return (0);
}


VDEXPORT int vdtratareg(void *ptr, char *param) {
	
	int ret=0, n=0;
	
	vdintlauxs *intlaux=ptr;
	vdstatuss stc;
	vdstatuss stl;
	vdinterfcargalins icl;
	vdinterfasecabs intc;

	memset(&intc,0,sizeof(intc));
	memset(&icl,0,sizeof(icl));
	memset(&stc,0,sizeof(stc));
	memset(&stl,0,sizeof(stl));

    if ((ret=damestabreviada("\nvdtratareg", param, 1, "#", NULL, "ICC", &stc, STICCPENDPROCES))) return (-1);
	if ((ret=damestabreviada("\nvdtratareg", param, 2, "#", NULL, "ICL", &stl, STICLPENDPROCES))) return (-1);
   
	//Carga los diccionarios para las tablas
	if (cargadics()) {
		v10log(LOGERROR,"%s","\nvdtratareg: No existen tablas a mantener definidas\n");
        return (-1);
	}

	//Inicializa variables
	ant.codinterfase=0;
	if ((strcmp(ant.tipointerfase, intlaux->tipointerfase)))
	    error='N';

	if ((strcmp(ant.tipointerfase, intlaux->tipointerfase)) || (strcmp(ant.formato, intlaux->formato))) 
		INTCselvdinterfasecab(intlaux->tipointerfase,intlaux->formato, &intc);

	//Tratar registros pendientes de procesar 
	if (ICLbuscabuscareg(intlaux->tipointerfase,intlaux->formato,stl.status,stc.status,&icl)) {
        v10log(LOGERROR,"\nvdtratareg: no existen líneas pendientes de servir para la interfase %s, formato %s y status %d\n", intlaux->tipointerfase,intlaux->formato,stl.status);
        return (-1);
	}
	do {	
		v10log(LOGNORMAL,"vdtratareg: Tratando código de interfase %d, registro %d \n",icl.codinterfase,icl.numreg);
		if (icl.codinterfase != ant.codinterfase){	
			if (ant.codinterfase > 0)  actstatuscab(ant.codinterfase, (char )error,'S');
			error='N';
			ant.codinterfase = icl.codinterfase;
		}

		cAccion ='X';
		if (CargaEstr(&intc, &icl)) {
			error='S';
			actstatuslin(&icl, 'S');
			break; // (2)
		}		
        if (cargardatos(n, &intc, &icl))
			error='S';
		
		actstatuslin(&icl, (char )error);

		if (error=='S') break;

	} while (!(ICLnextbuscareg(&icl))); //Fin del while que lee línea a línea.

	actstatuscab(icl.codinterfase, (char )error,'S');

	for (n=0;n<nt;n++) free(stvddics[n].ptr);

  return (0);
}

void vdactpadres(void) {

	vdinterfcargalins icl;
	int i=0;

	memset(&icl,0,sizeof(icl));
	
	
	for (i=0;i<h;i++) {
		//actualiza líneas
		ICLbuscacodinterfase(codinterfaseesphijo[i],&icl);
		do { 
			actstatuslin(&icl, 'N');
		}while(!(ICLnextcodinterfase(&icl)));
		//actualiza cabeceras
		actstatuscab(codinterfaseesphijo[i], (char )error, 'N');
	}
	for (i=0;i<h;i++) codinterfaseesphijo[i]=0;
	h=0;

	return;

}

static int ejecutaalgoritmosinterf(procesos *proceso,vdintlauxs *intlaux) {

  int ret;
 
  ret=VDEXECejecuta(proceso,intlaux,"#","%s#%s",intlaux->tipointerfase,intlaux->formato);

  if (ret==VD_ESINALG) v10log(LOGERROR,"ejecutaalgoritmosinterf: No existe algoritmo Activo para procesar el fichero con tipointerfase %s y formato %s\n",intlaux->tipointerfase,intlaux->formato);
      
  return(ret);
}

//Busca si hay líneas de interfase pendientes de tratar.
VDEXPORT void vdbuscaint(procesos *proceso) {

	vdstatuss stc;
	vdstatuss stl;
	vdintlauxs intlaux;
	vdinterfasecabs intc;

	int ret=0;

	memset(&ant,0,sizeof(ant));

	if ((ret=damestabreviada("vdbuscaint",proceso->proc.param, 1, "#", NULL, "ICC", &stc, STICCPENDPROCES))) return;
	if ((ret=damestabreviada("vdbuscaint",proceso->proc.param, 2, "#", NULL, "ICL", &stl, STICLPENDPROCES))) return;

	if (INTLAUXbuscareggral(stl.status,stc.status, &intlaux)) return;
	v10log(LOGNORMAL,"vdbuscaint: Tratando fichero de interfase de tipo %s y formato %s\n",intlaux.tipointerfase,intlaux.formato);
	do {
		if ((strcmp(intlaux.tipointerfase, ant.tipointerfase)) || (strcmp(intlaux.formato, ant.formato))) {
			ret=ejecutaalgoritmosinterf(proceso,&intlaux) ;
			if (ret && ret!=VD_ESINALG) {
				v10log(LOGERROR,"vdBuscaInt: ERROR procesando las líneas con tipointerfase %s y formato %s\n",intlaux.tipointerfase,intlaux.formato);
	           }
			if ((!(strcmp(ant.tipointerfase, intlaux.tipointerfase))) && (h>0) ) {
				if (INTCselhijo(ant.tipointerfase,ant.formato, &intc))
					vdactpadres();
			    else rollback();
			}
  		
			strcpy(ant.tipointerfase,intlaux.tipointerfase);
			strcpy(ant.formato,intlaux.formato);
		}
	}while(!(INTLAUXnextreggral(&intlaux)));

	if (( h> 0) & (INTCselhijo(ant.tipointerfase,ant.formato, &intc)) ) 
		vdactpadres();


return;

}
