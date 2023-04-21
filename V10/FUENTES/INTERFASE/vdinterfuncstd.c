/*******************************************************************************
* Módulo : vdinterffuncstd.c                                                   *
* Función: Funciones estándar sobre campos a cargar en las interfases.         *
*                                                                              *
* Autor  : ICC                                                                 *
* Revisado por:                                                                *
* Fecha  : 05-05-2008                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/
#include "vdinterfase.h"

typedef struct {
	char dia[3];
	char mes[3];
	char anno[5];
	v10dates fecha;
}Fecha;

//Funciones de transformación de la fecha según el formato de entrada
static char *fcjul(char *funcion, char *formato, char *campo, char *valor, vdinterfcargalins *icl, Fecha *fc) {

	fc->fecha=f2jul(atoi(fc->dia), atoi(fc->mes),atoi(fc->anno));
	if ((fc->fecha < 0) || (fc->fecha > 9999999)) {	
      sprintf(icl->mensaje, "%s: El formato del campo %s no es %s, valor: %s\n", funcion, campo, formato, valor);
	  return VDERROR;
	}
	sprintf(valor, "%07ld",fc->fecha);

	return valor;
}

//Formato: AAAAMMDD a juliano
VDEXPORT char *fcaaaammdd(char *valor, char *campo, vdinterfcargalins *icl) {
	
	Fecha fc;

	memset(&fc,0,sizeof(fc));

	strncpy(fc.anno,valor,4);
	strncpy(fc.mes,valor+4,2);
	strncpy(fc.dia,valor+6,2);	
	
	return(fcjul("fcaaaammdd", "AAAAMMDD", campo, valor, icl, &fc));

}

//Formato: DDMMAAAA a juliano
VDEXPORT char *fcddmmaaaa(char *valor, char *campo, vdinterfcargalins *icl) {

	Fecha fc;

	memset(&fc,0,sizeof(fc));

    strncpy(fc.dia,valor,2);
	strncpy(fc.mes,valor+2,2);
	strncpy(fc.anno,valor+6,4);

	return(fcjul("fcddmmaaaa", "DDMMAAAA", campo, valor, icl, &fc));
	
}
//Formato: AAAA/MM/DD a juliano
VDEXPORT char *fcaaaammddsep(char *valor, char *campo, vdinterfcargalins *icl) {

	Fecha fc;

	memset(&fc,0,sizeof(fc));
    
	strncpy(fc.anno, valor, 4);
	strncpy(fc.mes,valor+5,2);
	strncpy(fc.dia,valor+8,2);

	return(fcjul("fcaaaammddsep", "AAAA/MM/DD", campo, valor, icl, &fc));
}

//Formato: DD/MM/AAAA a juliano
VDEXPORT char *fcddmmaaaasep(char *valor, char *campo, vdinterfcargalins *icl) {

	Fecha fc;
    char sep[2];
	int n=0;
	memset(&fc,0,sizeof(fc));
    
	for (n=2;n<6;n=n+3) {
		strncpy(sep, valor+n,1);
		if (*sep != '/') {
			sprintf(icl->mensaje, "\nEl separador de fecha en el campo %s no es el correcto, sino %s\n", campo, sep);
			return VDERROR;
		}
	}

	strncpy(fc.dia,valor,2);
	strncpy(fc.mes,valor+3,2);
	strncpy(fc.anno,valor+6,4);

	return(fcjul("fcddmmaaaasep", "DD/MM/AAAA", campo, valor, icl, &fc));
	
}


//Formato: juliano a DD/MM/AAAA
VDEXPORT char *fcjulsepddmmaaaa(char *valor, char *campo, vdinterfcargalins *icl) {

	Fecha fc;

	memset(&fc,0,sizeof(fc));
    
	strncpy(fc.dia,valor,2);
	strncpy(fc.mes,valor+3,2);
	strncpy(fc.anno,valor+6,4);

	return(fcjul("fcddmmaaaasep", "DD/MM/AAAA", campo, valor, icl, &fc));
	
}


//Formato: DD/MM/AAAA a AAAAMMDD
VDEXPORT char *fcddmmaaaasepaaaammdd(char *valor, char *campo, vdinterfcargalins *icl) {

	Fecha fc;
	char sep[2];
	int n=0;

	memset(&fc,0,sizeof(fc));

	for (n=2;n<6;n=n+3) {
		strncpy(sep, valor+n,1);
		if (*sep != '/') {
			sprintf(icl->mensaje, "\nEl separador de fecha en el campo %s no es el correcto, sino %s\n", campo, sep);
			return VDERROR;
		}
	}

	strncpy(fc.dia,valor,2);
	strncpy(fc.mes,valor+3,2);
	strncpy(fc.anno,valor+6,4);

	sprintf(valor, "%s%s%s", fc.anno,fc.mes,fc.dia);

	return valor;
}

  
VDEXPORT char *fcsysdate(char *valor, char *campo, vdinterfcargalins *icl) {
	
	sprintf(valor, "%07ld",damedate());

	return valor;

}

  
VDEXPORT char *fcsysdatecsep(char *valor, char *campo, vdinterfcargalins *icl) {


    jul2a(damedate(),"Y.YY",valor);


	return valor;

}

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


//Devuelve el código de comentario del pedido, si no existe crea un nuevo código de comentario.
//Desde el registro, tiene que cachear la query, con lo que es menos optimo que la función calccodcomenped2
VDEXPORT long calccodcomenped(vdinterfcargalins *icl) {

	vdpedidorigcabs poc;
	vdintlauxs intlaux;

	INTLAUXbuscadameroid("VDPEDIDORIGCAB", "VDPEDIDORIGCAB", icl->tipointerfase, icl->formato, icl->registro, &intlaux);
	
	if (!(strcmp(intlaux.rowidaux, "-3"))) {
		sprintf(icl->mensaje, "\nERROR, en el PL al acceder por clave primaria a VDPEDIDORIGCAB");
        return (-1);
	} else if (!(strcmp(intlaux.rowidaux, "-1"))) {
		sprintf(icl->mensaje, "\nERROR, No se encuentra la clave primaria de VDPEDIDORIGCAB en el registro");
        return (-1);
	}

	if (!(strcmp(intlaux.rowidaux, "-2"))) {
		if (COMselvdseccomen(&poc.codcomen)) {
		   strcpy(icl->mensaje, "ERROR obteniendo el código de comentario de la secuencia seccomen");
		   return -1;
		}
	} else POCselrowid(intlaux.rowidaux,&poc);


	return poc.codcomen;

}

//Devuelve el código de comentario del pedido, si no existe crea un nuevo código de comentario.
//A partir del pedido que ya tiene cacheada la query.
VDEXPORT long calccodcomenped2(char *codped, char *coddiv, int anoped, vdinterfcargalins *icl) {

	vdpedidorigcabs poc;

	memset(&poc,0,sizeof(poc));

	strcpy(poc.codped, codped);
	strcpy(poc.coddiv, coddiv);
	poc.anoped=anoped;

	if (POCinter(&poc)) {
		getcurerrornombre("SELPOCVDPEDIDORIGCAB",icl->mensaje);
	   if (strstr( strmay(icl->mensaje), "NO SE HA ENCONTRADO NINGÚN DATO" )) return (-1);
    }

	if (poc.codcomen==0) {
		if (COMselvdseccomen(&poc.codcomen)) {
		   strcpy(icl->mensaje, "ERROR obteniendo el código de comentario de la secuencia seccomen");
		   return -1;
		}
	}


	return poc.codcomen;

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

//Formatea la hora recibida añadiendo el separador ":"
VDEXPORT char *formatohora(char *valor, char *campo, vdinterfcargalins *icl) {

	char hora[LHORAMODIF]="";

	sprintf(hora,"%2.2s:%2.2s:%2.2s",valor,valor+2,valor+4);
	strcpy (valor,hora);

	return valor;
}
