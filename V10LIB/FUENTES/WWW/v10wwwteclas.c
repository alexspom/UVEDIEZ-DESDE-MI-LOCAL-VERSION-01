#include "v10wwwform.h"

#define TCTRL    0
#define TSHIFT   1
#define TALT     2
#define TNORMAL  3
#define TIGNORAR 4

#define TECLAMENU 93

typedef struct {
	int tecla;
	int tipo; 
} teclasjs;

static teclasjs teclasfinales[V10MAXTECLAS];
static int numteclasfinales=0;

static void addtecla(int tecla, int tipo ) 
{
	teclasfinales[numteclasfinales].tecla=tecla;
	teclasfinales[numteclasfinales++].tipo=tipo;
}

static int tipoteclas2js(int tipo) 
{
	char cond[100]="";
	int numopciones,i;

	switch (tipo) {
	case TCTRL: strcat(cond,V10WWWCONTROL);
		break;
	case TSHIFT: strcat(cond,V10WWWSHIFT);
		break;
	case TALT: strcat(cond,V10WWWALT);
		break;
	}

	if (tipo==TCTRL || tipo==TSHIFT || tipo==TALT) sprintf(v10datoshtml+strlen(v10datoshtml),"  if (v10lib.%s) { ",cond);
	else strcat(v10datoshtml,"  if (!v10lib.shift && !v10lib.ctrl && !v10lib.alt) {");

	numopciones=0;
	for (i=0;i<numteclasfinales;i++) {
		if (teclasfinales[i].tipo==tipo) {
			if (numopciones==0) sprintf(v10datoshtml+strlen(v10datoshtml),"\n    if ( t==%d",teclasfinales[i].tecla);
			else  sprintf(v10datoshtml+strlen(v10datoshtml)," || t==%d",teclasfinales[i].tecla);      
			numopciones++;
		}
	}
	if (numopciones>0) strcat(v10datoshtml," ) return(true);");
	strcat(v10datoshtml,"\n  }\n");
    return(0);
}

static void teclas2script() 
{
    *v10datoshtml = 0;
	strcat(v10datoshtml,"\n function validatecla(t) {\n");
	tipoteclas2js(TCTRL);
	tipoteclas2js(TSHIFT);
	tipoteclas2js(TALT);
	tipoteclas2js(TNORMAL);
	tipoteclas2js(TIGNORAR);
	strcat(v10datoshtml,"return(false);\n}\n");
	numteclasfinales=0;
}


void v10jsteclas(forms *f) {
	bloques *b=v10damebloqueactual();
	int numteclas=0,i,j,tipo,ch;
	int teclas[V10MAXTECLAS];
	char comb[100];
	// recoge las teclas de los campos y bloques
	for (i=0;i<b->nteclas;i++) teclas[numteclas++]=b->teclas[i].t;
	for (i=0;i<b->ncamp;i++) {
		if (!b->c || !b->c[i].v || b->c[i].v->invisible) continue;
		if (entrablecampo(b->c+i)) {
			for (j=0;j<b->c[i].nteclas;j++)
				teclas[numteclas++]=b->c[i].teclas[j].t;			
		}
	}	
	// trata teclas especiales 
	for (i=0;i<numteclas;i++) {
		tipo=TNORMAL;
		ch=v10ansi2js(teclas[i]);
		if (ch<100 && ch!=9) continue;

		if (!strcmp((char *)v10comb(comb,teclas[i]),V10WWWSHIFT)) tipo=TSHIFT;
		else if (!strcmp((char *)v10comb(comb,teclas[i]),V10WWWALT)) tipo=TALT;
		else if (!strcmp((char *)v10comb(comb,teclas[i]),V10WWWCONTROL)) tipo=TCTRL;

		for (j=0;j<numteclasfinales;j++) if (teclasfinales[j].tecla==ch && teclasfinales[j].tipo==tipo) break;
		if (j<numteclasfinales) continue;
		if (tipo==TNORMAL && (ch==tab || ch==esc))  tipo=TIGNORAR;
		addtecla(ch, tipo);
	}

	addtecla(v10ansi2js(C_F(2)),TCTRL); // enterquery
	addtecla(v10ansi2js(C_F(3)),TCTRL); // count registros
	addtecla(v10ansi2js(C_F(4)),TCTRL); // edita consulta pregrabada
	addtecla(v10ansi2js(C_F(5)),TCTRL); // menú consultas pregrabadas
	addtecla(v10ansi2js(C_F(6)),TCTRL);
	addtecla(v10ansi2js(C_F(7)),TCTRL);  
	addtecla(v10ansi2js(C_F(9)),TCTRL); // información de errores del bloqye
	addtecla(v10ansi2js('a'),   TCTRL);
	addtecla(v10ansi2js(S_F(10)),TSHIFT);
	addtecla(v10ansi2js(tab),   TSHIFT);
	addtecla(v10ansi2js('D'),   TALT);
	addtecla(v10ansi2js(esc),   TNORMAL);
	addtecla(v10ansi2js(cr),    TNORMAL);
	addtecla(v10ansi2js(F(2)),  TNORMAL); 
	addtecla(v10ansi2js(F(3)),  TNORMAL);
	addtecla(v10ansi2js(F(4)),  TNORMAL);
	addtecla(v10ansi2js(F(5)),  TNORMAL);
	addtecla(v10ansi2js(F(6)),  TNORMAL);
	addtecla(v10ansi2js(F(7)),  TNORMAL);
	addtecla(v10ansi2js(F(9)),  TNORMAL);
	addtecla(v10ansi2js(F(10)), TNORMAL);
	addtecla(TECLAMENU,         TNORMAL);
	addtecla(v10ansi2js(cua),   TIGNORAR);
	addtecla(v10ansi2js(cuu),   TIGNORAR);
	addtecla(v10ansi2js(pgup),  TIGNORAR);
	addtecla(v10ansi2js(pgdn),  TIGNORAR);
	addtecla(v10ansi2js(tab),   TIGNORAR);
	addtecla(v10ansi2js(esc),   TIGNORAR);
	teclas2script();		
	sprintf(v10datoshtml+strlen(v10datoshtml),"v10lib.creamenucont(%d);\n",protegidoform);
	v10reemplazapatron(v10html,PATRONJAVASCRIPTONSCRIPTS,v10datoshtml,1);	
}



