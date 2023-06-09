#ifndef __VDINTERFASE__H
#define __VDINTERFASE__H
#include "vdform.h"
#include "execproc/vdexec.h"

#define VDERROR "-1"

//Definicion de campos especiales de interfase
#define ERRORINTER      "ERRORINTER"
#define SALIDAINTER     "SALIDAINTER"
#define SECUENCIALINTER "SECUENCIALINTER"

//Definición de estructuras generales
typedef struct {
	char azTabla[33];
	char azTipocomen[LTIPOCOMEN];
	char azComentario[LCOMENTARIO];
}stcomentario;

typedef struct {
	stcomentario coms[99];
	int n;
}stcoms;

stcoms comens;

//Funciones definidas en VDINTERSAL.C
VDEXPORT void carganombreinterfase(bloques *b,char *tipointerfase,char *formato);


//Funciones definidas en VDINTERFRM.C
VDEXPORT int trataforminter(forms *f);

//Funciones definidas en VDINTERTRIG.C
VDEXPORT void inittrigerinter(void);

// funciones de tratamiento de campos de interfases estandard en vdinterfuncstd.c
VDEXPORT char *fcaaaammdd(char *valor, char *campo, vdinterfcargalins *icl);
VDEXPORT char *fcddmmaaaa(char *valor, char *campo, vdinterfcargalins *icl);
VDEXPORT char *fcaaaammddsep(char *valor, char *campo, vdinterfcargalins *icl);
VDEXPORT char *fcddmmaaaasep(char *valor, char *campo, vdinterfcargalins *icl);
VDEXPORT char *fcjulsepddmmaaaa(char *valor, char *campo, vdinterfcargalins *icl);
VDEXPORT char *fcddmmaaaasepaaaammdd(char *valor, char *campo, vdinterfcargalins *icl);
VDEXPORT char *fcsysdate(char *valor, char *campo, vdinterfcargalins *icl);
VDEXPORT char *fcsysdatecsep(char *valor, char *campo, vdinterfcargalins *icl);
VDEXPORT char *horasysdate(char *valor, char *campo, vdinterfcargalins *icl);
VDEXPORT char *valorsn(char *valor, char *campo, vdinterfcargalins *icl);
VDEXPORT char *valcoddiv(char *valor, char *campo, vdinterfcargalins *icl);
VDEXPORT long calccodcomenped(vdinterfcargalins *icl);
VDEXPORT long calccodcomenped2(char *codped, char *coddiv, int anoped, vdinterfcargalins *icl);
VDEXPORT char *valpais(char *valor, char *campo, vdinterfcargalins *icl);
VDEXPORT char *formatohora(char *valor, char *campo, vdinterfcargalins *icl);
VDEXPORT char *Mayusculas(char *valor, char *campo, vdinterfcargalins *icl);
//funciones definidas en VDINTERENT.C
VDEXPORT void actstatuslin(vdinterfcargalins *icl, char error);
VDEXPORT void actstatuscab(long codinterfase, char error, char cCompruebaHijo);
#endif