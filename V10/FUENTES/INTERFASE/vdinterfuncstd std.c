/*******************************************************************************
* Módulo : vdinterffuncstd.c                                                   *
* Función: Funciones estándar sobre campos a cargar en las interfases.         *
*                                                                              *
* Autor  : ICC                                                                 *
* Revisado por:                                                                *
* Fecha  : 05-05-2008                                                          *
********************************************************************************
* Histórico de cambios                                                         *
* ====================
* 23-11-2009 Función comentario.
* 03-12-2009 Creación de funciones genéricas de fechas, y eliminación de las   
*            específicas por formato.
*******************************************************************************/
#include "vdinterfase.h"

//#include "I:\V10\FUENTES\AUTO\GENCLIBRE\vdinterfases.h"
/*
typedef struct {
	char dia[3];
	char mes[3];
	char anno[5];
	v10dates fecha;
}Fecha;
*/

//Función para transformar fechas y horas, Parámetros:
// 1.- Formato fecha de entrada
// 2.- Formato fecha de salida
VDEXPORT char *transfechashoras(char *valor, char *campo, vdinterfcargalins *icl, char *param) {

	char azFmtoEnt[31];
	char azFmtoSal[31];
	vdintlauxs intlaux;

	memset(&intlaux,0,sizeof(intlaux));

	piece(param,azFmtoEnt,"#",1);
	piece(param,azFmtoSal,"#",2);

	if (INTLAUXseltransfecha(valor,azFmtoEnt,azFmtoSal,&intlaux)) {
		sprintf(icl->mensaje, "Error al transformar la fecha %s del formato %s al formato %s", valor,azFmtoEnt,azFmtoSal);
		return "-1";
	}

	return intlaux.fechasal;
}

//Función que obtiene la fecha y hora del día, Parámetros:
// 1.- Formato fecha de salida
VDEXPORT char *fechasys(char *valor, char *campo, vdinterfcargalins *icl, char *param) {

	char azFmtoSal[31];
	char azFecha[31];
	vdintlauxs intlaux;

	memset(&intlaux,0,sizeof(intlaux));

	piece(param,azFmtoSal,"#",1);
	jul2a(getdate(),"Y.YYMMDD",azFecha);
	strcat(azFecha," ");
	cent2a(gettime(),0,':',azFecha+strlen(azFecha));

	if (INTLAUXseltransfecha(azFecha,"YYYYMMDD HH24:MI:SS",azFmtoSal,&intlaux)) {
		sprintf(icl->mensaje, "Error al transformar la fecha del día %s al formato %s", azFecha, azFmtoSal);
		return "-1";
	}

	return intlaux.fechasal;
}
// duplicada???
VDEXPORT char *horasysdate(char *valor, char *campo, vdinterfcargalins *icl) {

    cent2a(gettime(),0,':',valor);

	return valor;

}

//Otras funciones
//Valida que el valor introducido sea S o N
VDEXPORT char *valorsn(char *valor, char *campo, vdinterfcargalins *icl) {


  if ((strcmp(valor, "S")) && (strcmp(valor, "N"))) {
	  sprintf(icl->mensaje, "\nvalorSN: El valor del campo %s es %s, debiendo ser S o N\n", campo, valor);
	  return VDERROR;
  }   

	return valor;
}

//Valida que exista el código de división
VDEXPORT char *valcoddiv(char *valor, char *campo, vdinterfcargalins *icl) {

	vddiviss div;

	if (DIVselvddivis(trim(valor), &div)) {
  	   sprintf(icl->mensaje, "\nvalcoddiv: No existe el código de división %s\n", valor);
	   return VDERROR;
	}   

	return valor;
}

//Valida que exista el pais en la tabla de paises
VDEXPORT char *valpais(char *valor, char *campo, vdinterfcargalins *icl) {

	vdpaiss pais;

	if (!strcmp(valor,"")) {
		strcpy(valor,"ESPAÑA");
	}
	if (PAISbuscadespais(trim(valor), &pais)) {
  	   sprintf(icl->mensaje, "\nvalpais: No existe el pais %s en la tabla de paises\n", valor);
	   return VDERROR;
	}   
	strcpy(valor,pais.codpais);

	return valor;
}

//Función que pasa a mayúsculas
VDEXPORT char *Mayusculas(char *valor, char *campo, vdinterfcargalins *icl) {

	strcmp(valor, strmay(valor));

	return valor;
}

//Función para guardar un comentario en la estructura de comentarios.
VDEXPORT char *comentario(char *valor, char *campo, vdinterfcargalins *icl, char *param) {

	piece(param,comens.coms[comens.n].azTabla,"#",1);
	piece(param,comens.coms[comens.n].azTipocomen,"#",2);
	strcpy(comens.coms[comens.n].azComentario, valor);
	comens.n++;
	
	return valor;
}

//Los valores que nos pasan por parámetro debe ser uno de ellos igual al valor del campo.
VDEXPORT char *valparam(char *valor, char *campo, vdinterfcargalins *icl, char *param) {

  char averif[40];
  int i=0;

  for (i=0;i<numpieces(param,"#");i++) {
   	piece(param,averif,"#",i+1);
	  if (!strcmp(valor, averif)) return valor;
	}
	
	sprintf(icl->mensaje, "\nvalparam: Se esperaba uno de los valores %s, y en el fichero se ha informado %s \n", param, valor);
	
	return VDERROR;
}

//Transforma un dato en el que corresponda. Se agrupan las condiciones siendo cada parámetro separado por #:
// valorp$azif$azelse : si el valor del parámetro coincide con el valor del campo, guarda el primer valor, sino el siguiente.
VDEXPORT char *transdato(char *valor, char *campo, vdinterfcargalins *icl, char *param) {

	char valorini[40];
	char cadena[40];
	char valorp[40];
	int i=0;

	strcpy(valorini, valor);
	strcpy(valor,"");

	for (i=0;i<numpieces(param,"#");i++) {
        piece(param,cadena,"#",i+1);
		piece(cadena,valorp,"$", 1);
		if (!strcmp(valorini,valorp))
			piece(cadena,valor,"$", 2);
		else 
			piece(cadena,valor,"$", 3);

		if (strcmp(valor,"")) return valor;
	}

	sprintf(icl->mensaje, "\ntransdato: Dato a transformar sin valor definido, valor %s, comparar con %s \n",  valor, param);
	
	return VDERROR;

}
VDEXPORT char *valtotreg(char *valor, char *campo, vdinterfcargalins *icl, char *param) {

	vdinterfcargacabs icc, iccd;
	vdinterfcargalins icld;
	char formato[20];
       
	ICCselvdinterfcargacab(icl->codinterfase,&icc);

	piece(param,formato,"#",1);
	ICCselfmtofich(formato,icc.fichero,&iccd);
	ICLselnumlineas(iccd.codinterfase,&icld);
	
	if (atoi(valor) != icld.gencount) {
		sprintf(icl->mensaje, "\nvaltotreg: El fichero informa que vamos a recibir %s registros de tipo %s, y sin embargo hemos recibido %lf \n", valor, formato, icld.gencount);
	    return VDERROR;
	}

	return valor;
}

//Elimina los blancos a la derecha
VDEXPORT char *btrim(char *valor, char *campo, vdinterfcargalins *icl) {
	
	return trim(valor);
}

//Elimina los ceros a la izquierda para los campos numéricos.
VDEXPORT char *elimceros(char *valor, char *campo, vdinterfcargalins *icl) {

	sprintf(valor, "%d", atol(valor));

	return valor;
}
