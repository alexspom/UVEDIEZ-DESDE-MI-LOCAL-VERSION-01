/****
* VDRESERVADEMANDAS.C
*                                                    
* Propósito: Algoritmos de Reserva de Demandas de traslado
*                        
* Autor  : FGS
* Fecha  : 11-3-2008                                                        
******
*  Modificaciones:
****/

#include "execproc/vdexec.h"


// ALGORITMO. Realiza la reserva de una línea de demanda de traslado por un flujo.
// PARAM 1: Tarea de Flujos
// PARAM 2: EMBALAJESCOMPLETOS, Reserva embalajes completos
// PARAM 3: SOLOPARCIALES, no intenta reservar contenedores completos
// PARAM 4: UNIAGRUPA de la ubic. en el área destino, para generar los movtos, si no viene informadada
// PARAM 5: MONOFORMATO, todo lo que reserva de un cotenedor tiene que tener el mismo formato
VDEXPORT int vdresdemlstd(void *ptr,char *param) {
    int ret=0;
    char tarea[MAXCADENA]="";
    char embalajescompletos[2]="",soloparciales[2]="";
    char uniagrupa[2]="",monoformato[2]="",revisarcompleto[2]="";
    vddemandalins *deml=ptr;
    vdress res;
    
    if ((ret=piece(param,tarea,"#",1))<0) {
        v10log(LOGERROR,"%s","reservastd: no se ha informado tarea de reserva.\n");
        return(ret);
    }
       
    piece(param,embalajescompletos,"#",2);
    if (*embalajescompletos==0) *embalajescompletos='N';

    piece(param,soloparciales,"#",3);
    if (*soloparciales==0) *soloparciales='N';

    piece(param,uniagrupa,"#",4);
    piece(param,monoformato,"#",5);
    if (*monoformato==0) *monoformato='N';
    piece(param,revisarcompleto,"#",6);
    if (*revisarcompleto==0) *revisarcompleto='N';

    memset(&res,0,sizeof(res));

    ret= RESprocreservastd(deml->coddemanda,deml->tipodemanda,deml->lindemanda,
                           deml->cantidad,tarea,embalajescompletos,soloparciales,uniagrupa,monoformato,revisarcompleto,
                           res.comentario,res.reservado,&res);
    if (ret) {
        v10log(LOGERROR,"%s","reservastd: Error ORACLE ejecutando RESprocreservastd\n");
    } else {
        strcopia(deml->comendeml,res.comentario,strlen(res.comentario));
        deml->reservado=res.reservado;
    }

    return(ret);
}




// ALGORITMO.Para una línea de demanda, genera un movto con la cantidad y lo criterios de esta
// PARAM 1: TAREA: tarea de los movtos a crear
// PARAM 2: CONCEPTO: concepto de los movtos a crear
// PARAM 3: STATUS: status con el que se crean los movtos 
VDEXPORT int vdresdemlpeddif(void *ptr,char *param) {
    int ret=0;
    char tareauni[LTAREA]="",tareaemba[LTAREA]="",tareaconte[LTAREA]="",codconce[LCODCONCE]="",codubiori[LCODUBI]="";
	vdstatuss stmov;
    vddemandalins *deml=ptr;
    vdress res;

	// recoge los parámetros
    memset(&res,0,sizeof(vdress));
	 if ((ret=piece(param,codubiori,"#",1))<0) {
        v10log(LOGERROR,"%s","vdresdemlpeddif: no se ha informado de la ubic. origen de los movtos a crear.\n");
        return(ret);
    }
    if ((ret=piece(param,tareauni,"#",2))<0) {
        v10log(LOGERROR,"%s","vdresdemlpeddif: no se ha informado la tareauni de los movtos a crear.\n");
        return(ret);
    }

	if ((ret=piece(param,tareaemba,"#",3))<0) {
        v10log(LOGERROR,"%s","vdresdemlpeddif: no se ha informado la tareaemba de los movtos a crear.\n");
        return(ret);
    }
	if ((ret=piece(param,tareaconte,"#",4))<0) {
        v10log(LOGERROR,"%s","vdresdemlpeddif: no se ha informado la tareaconte de los movtos a crear.\n");
        return(ret);
    }
    if ((ret=piece(param,codconce,"#",5))<0) {
        v10log(LOGERROR,"%s","vdresdemlpeddif: no se ha informado el concepto de los movtos a crear.\n");
        return(ret);
    }
	if ( (ret=damestabreviada("vdresdemlpeddif",param, 6, "#", NULL, "MOV", &stmov, 0))) return(ret);    
    ret=RESprocreservapedidodif(deml->coddemanda,deml->tipodemanda,deml->lindemanda,
                                deml->cantidad,codubiori,tareauni,tareaemba,tareaconte,codconce,stmov.status,res.comentario,res.reservado,&res);
    if (ret) {
        v10log(LOGERROR,"%s","vdresdemlpeddif: Error ORACLE ejecutando RESprocreservapedidodif\n");
    } else {
        strcopia(deml->comendeml,res.comentario,strlen(res.comentario));
        deml->reservado=res.reservado;
    }
    return(ret);
}

// ALGORITMO. Realiza la reserva de una línea de demanda de traslado por un flujo.
// PARAM 1: Flujo Contenedores 
// PARAM 2: Flujo embalajes 
// PARAM 3: Flujo unidades
// PARAM 4: UNIAGRUPAEMBALAJES de la ubic. en el área destino, para generar los movtos del FLUJO EMABALAJES, si no viene informadada
// PARAM 5: UNIAGRUPAUNIDADES de la ubic. en el área destino, para generar los movtos del FLUJO UNIDADES, si no viene informadada
// PARAM 6: MONOFORMATO, todo lo que reserva de un cotenedor tiene que tener el mismo formato
VDEXPORT int vdresdemlpedstd(void *ptr, char *param) {
    int ret = 0;
    char tareaconte[MAXCADENA] = "", tareaemba[MAXCADENA] = "", tareauni[MAXCADENA] = "", tareauniinv[MAXCADENA] = "", tareaprepick[MAXCADENA] = "";
    char uniagrupaemba[2] = "", uniagrupauni[2] = "", monoformato[2] = "", revisarcompleto[2] = "";
    vddemandalins *deml = ptr;
    vdress res;

    memset(&res, 0, sizeof(vdress));
    if ((ret = piece(param, tareaconte, "#", 1))<0) {
        v10log(LOGERROR,"%s","reservapedidostd: no se ha informado tarea de reserva de CONTENEDORES.\n");
        return(ret);
    }

    if ((ret = piece(param, tareaemba, "#", 2))<0) {
        v10log(LOGERROR,"%s","reservapedidostd: no se ha informado tarea de reserva de EMBALAJES.\n");
        return(ret);
    }

    piece(param, tareauniinv, "#", 3);
    piece(param, tareaprepick, "#", 4);

    if ((ret = piece(param, tareauni, "#", 5))<0) {
        v10log(LOGERROR,"%s","reservapedidostd: no se ha informado tarea de reserva de UNIDADES.\n");
        return(ret);
    }

    piece(param, uniagrupaemba, "#", 6);
    piece(param, uniagrupauni, "#", 7);
    piece(param, monoformato, "#", 8);
    if (*monoformato == 0) *monoformato = 'N';
    piece(param, revisarcompleto, "#", 9);
    if (*revisarcompleto == 0) *revisarcompleto = 'N';

    // recoger los parámetros
    ret = RESprocreservapedidostd(deml->coddemanda, deml->tipodemanda, deml->lindemanda,
                                  deml->cantidad, tareaconte, tareaemba, tareauniinv, tareaprepick, tareauni,
                                  uniagrupaemba, uniagrupauni, monoformato, revisarcompleto, res.comentario, res.reservado, &res);
    if (ret) {
        v10log(LOGERROR,"%s","reservapedidostd: Error ORACLE ejecutando RESprocreservapedidostd\n");
    } else {
        strcopia(deml->comendeml, res.comentario, strlen(res.comentario));
        deml->reservado = res.reservado;
    }

    return(ret);
}

// ALGORITMO. Realiza la reserva de una línea de demanda de traslado por un flujo.
// PARAM 1: Flujo Contenedores 
// PARAM 2: Flujo embalajes 
// PARAM 3: Flujo unidades
// PARAM 4: UNIAGRUPAEMBALAJES de la ubic. en el área destino, para generar los movtos del FLUJO EMABALAJES, si no viene informadada
// PARAM 5: UNIAGRUPAUNIDADES de la ubic. en el área destino, para generar los movtos del FLUJO UNIDADES, si no viene informadada
// PARAM 6: MONOFORMATO, todo lo que reserva de un cotenedor tiene que tener el mismo formato
VDEXPORT int vdresdemlpedext(void *ptr, char *param) {
    int ret = 0;
    char tareaconte[MAXCADENA] = "", tareaemba[MAXCADENA] = "", tareauni[MAXCADENA] = "", tareauniinv[MAXCADENA] = "", tareaprepick[MAXCADENA] = "";
    char uniagrupaemba[2] = "", uniagrupauni[2] = "", monoformato[2] = "", revisarcompleto[2] = "";
    char parametro[MAXPATH];
    double diferconte, diferemba, diferuni;
    vddemandalins *deml = ptr;
    vdress res;

    memset(&res, 0, sizeof(vdress));
    if ((ret = piece(param, tareaconte, "#", 1))<0) {
        v10log(LOGERROR,"%s","reservapedidostd: no se ha informado tarea de reserva de CONTENEDORES.\n");
        return(ret);
    }

    if ((ret = piece(param, tareaemba, "#", 2))<0) {
        v10log(LOGERROR,"%s","reservapedidostd: no se ha informado tarea de reserva de EMBALAJES.\n");
        return(ret);
    }

    piece(param, tareauniinv, "#", 3);
    piece(param, tareaprepick, "#", 4);

    if ((ret = piece(param, tareauni, "#", 5))<0) {
        v10log(LOGERROR,"%s","reservapedidostd: no se ha informado tarea de reserva de UNIDADES.\n");
        return(ret);
    }

    piece(param, uniagrupaemba, "#", 6);
    piece(param, uniagrupauni, "#", 7);
    piece(param, monoformato, "#", 8);
    if (*monoformato == 0) *monoformato = 'N';
    piece(param, revisarcompleto, "#", 9);
    if (*revisarcompleto == 0) *revisarcompleto = 'N';
    piece(param, parametro, "#", 10);
    diferconte = atof(parametro);
    piece(param, parametro, "#", 11);
    diferemba = atof(parametro);
    piece(param, parametro, "#", 12);
    diferuni = atof(parametro);
    // recoger los parámetros
    ret = RESprocreservapedidoext(deml->coddemanda, deml->tipodemanda, deml->lindemanda,
                                  deml->cantidad, tareaconte, tareaemba, tareauniinv, tareaprepick, tareauni,
                                  uniagrupaemba, uniagrupauni, monoformato, revisarcompleto, res.comentario, res.reservado,diferconte,diferemba,diferuni,&res);
    if (ret) {
        v10log(LOGERROR,"%s","reservapedidostd: Error ORACLE ejecutando RESprocreservapedidostd\n");
    } else {
        strcopia(deml->comendeml, res.comentario, strlen(res.comentario));
        deml->reservado = res.reservado;
    }

    return(ret);
}

