#include "vdform.h"

typedef struct {
	      char nombrecolor[LNOMBRECOLOR];
		  long tinta1;
		  long papel1;
		  long tinta2;
		  long papel2;
		  long tinta3;
		  long papel3;
		  long tinta4;
		  long papel4;
		  long tinta5;
		  long papel5;
		  long tinta6;
		  long papel6;
		  long tinta7;
		  long papel7;
		  long tinta8;
		  long papel8;
		  long tinta9;
		  long papel9;
		  long tinta10;
		  long papel10;
		  long tinta11;
		  long papel11;
		  long tinta12;
		  long papel12;
		  long tinta13;
		  long papel13;
		  long tinta14;
		  long papel14;
		  long tinta15;
		  long papel15;
		  long tinta16;
		  long papel16;
		  long tinta17;
		  long papel17;
		  long tinta18;
		  long papel18;
		  long tinta19;
		  long papel19;
		  long tinta20;
		  long papel20;
		  long tinta21;
		  long papel21;
		  long tinta22;
		  long papel22;
		  long tinta23;
		  long papel23;
		  long tinta24;
		  long papel24;
		  long tinta25;
		  long papel25;
		  long tinta26;
		  long papel26;
		  long tinta27;
		  long papel27;
		  long tinta28;
		  long papel28;
		  long tinta29;
		  long papel29;
		  long tinta30;
		  long papel30;
} vdcolores;
static vdcolores vdc;
static char temacolores[LTEMA];

#define CSELCOLOR "SELECT NOMBRECOLOR,TINTA1,PAPEL1,TINTA2,PAPEL2,TINTA3,PAPEL3,TINTA4,PAPEL4,TINTA5,PAPEL5, "\
                                   "  TINTA6,PAPEL6,TINTA7,PAPEL7,TINTA8,PAPEL8,TINTA9,PAPEL9,TINTA10,PAPEL10, "\
								   "  TINTA11,PAPEL11,TINTA12,PAPEL12,TINTA13,PAPEL13,TINTA14,PAPEL14,TINTA15,PAPEL15, "\
								   "  TINTA16,PAPEL16,TINTA17,PAPEL17,TINTA18,PAPEL18,TINTA19,PAPEL19,TINTA20,PAPEL2, "\
								   "  TINTA21,PAPEL21,TINTA22,PAPEL22,TINTA23,PAPEL23,TINTA24,PAPEL24,TINTA25,PAPEL25, "\
								   "  TINTA26,PAPEL26,TINTA27,PAPEL27,TINTA28,PAPEL28,TINTA29,PAPEL29,TINTA30,PAPEL30 "\
					" FROM VDDEFCOLOR "\
					" WHERE TEMA=:TEMA "
static v10cursors *vdselcolor;

static void finvdformcolor(void)
{
	liberacursor(vdselcolor);
}

static void initvdformcolor(void)
{
	vdselcolor=abrecursor(CSELCOLOR);
	definetodo(vdselcolor,vdc.nombrecolor,sizeof(vdc.nombrecolor),V10CADENA,
		                  &vdc.tinta1,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel1,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta2,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel2,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta3,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel3,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta4,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel4,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta5,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel5,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta6,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel6,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta7,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel7,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta8,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel8,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta9,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel9,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta10,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel10,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta11,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel11,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta12,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel12,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta13,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel13,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta14,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel14,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta15,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel15,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta16,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel16,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta17,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel17,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta18,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel18,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta19,sizeof(vdc.tinta1),V10LONG,
		                  &vdc.papel19,sizeof(vdc.papel1),V10LONG,
		                  &vdc.tinta20,sizeof(vdc.tinta2),V10LONG,
		                  &vdc.papel20,sizeof(vdc.papel2),V10LONG,
		                  &vdc.tinta21,sizeof(vdc.tinta2),V10LONG,
		                  &vdc.papel21,sizeof(vdc.papel2),V10LONG,
		                  &vdc.tinta22,sizeof(vdc.tinta2),V10LONG,
		                  &vdc.papel22,sizeof(vdc.papel2),V10LONG,
		                  &vdc.tinta23,sizeof(vdc.tinta2),V10LONG,
		                  &vdc.papel23,sizeof(vdc.papel2),V10LONG,
		                  &vdc.tinta24,sizeof(vdc.tinta2),V10LONG,
		                  &vdc.papel24,sizeof(vdc.papel2),V10LONG,
		                  &vdc.tinta25,sizeof(vdc.tinta2),V10LONG,
		                  &vdc.papel25,sizeof(vdc.papel2),V10LONG,
		                  &vdc.tinta26,sizeof(vdc.tinta2),V10LONG,
		                  &vdc.papel26,sizeof(vdc.papel2),V10LONG,
		                  &vdc.tinta27,sizeof(vdc.tinta2),V10LONG,
		                  &vdc.papel27,sizeof(vdc.papel2),V10LONG,
		                  &vdc.tinta28,sizeof(vdc.tinta2),V10LONG,
		                  &vdc.papel28,sizeof(vdc.papel2),V10LONG,
		                  &vdc.tinta29,sizeof(vdc.tinta2),V10LONG,
		                  &vdc.papel29,sizeof(vdc.papel2),V10LONG,
		                  &vdc.tinta30,sizeof(vdc.tinta2),V10LONG,
		                  &vdc.papel30,sizeof(vdc.papel2),V10LONG,
						  NULL);
	bindtodo(vdselcolor,"TEMA",temacolores,sizeof(temacolores),V10CADENA,NULL);
    atexit(finvdformcolor);
}

int cargacolores(char *tema)
{
	int ret;
	int nc=0;
    if (vdselcolor==NULL) initvdformcolor();
	strcpy(temacolores,tema);
    ret=ejecutacursor(vdselcolor);
	memset(&defvent,0,sizeof(defvent));
	while (fetchcursor(vdselcolor)==0) {
		defvents *df=defvent+nc;
		strcpy(df->nombre,vdc.nombrecolor);
		df->t.t[0].tinta=vdc.tinta1;
		df->t.t[0].papel=vdc.papel1;
		df->t.t[1].tinta=vdc.tinta1;
		df->t.t[1].papel=vdc.papel1;
		df->t.t[2].tinta=vdc.tinta2;
		df->t.t[2].papel=vdc.papel2;
		df->t.t[3].tinta=vdc.tinta3;
		df->t.t[3].papel=vdc.papel3;
		df->t.t[4].tinta=vdc.tinta4;
		df->t.t[4].papel=vdc.papel4;
		df->t.t[5].tinta=vdc.tinta5;
		df->t.t[5].papel=vdc.papel5;
		df->t.t[6].tinta=vdc.tinta6;
		df->t.t[6].papel=vdc.papel6;
		df->t.t[7].tinta=vdc.tinta7;
		df->t.t[7].papel=vdc.papel7;
		df->t.t[8].tinta=vdc.tinta8;
		df->t.t[8].papel=vdc.papel8;
		df->t.t[9].tinta=vdc.tinta9;
		df->t.t[9].papel=vdc.papel9;
		df->t.t[10].tinta=vdc.tinta10;
		df->t.t[10].papel=vdc.papel10;
		df->t.t[11].tinta=vdc.tinta11;
		df->t.t[11].papel=vdc.papel11;
		df->t.t[12].tinta=vdc.tinta12;
		df->t.t[12].papel=vdc.papel12;
		df->t.t[13].tinta=vdc.tinta13;
		df->t.t[13].papel=vdc.papel13;
		df->t.t[14].tinta=vdc.tinta14;
		df->t.t[14].papel=vdc.papel14;
		df->t.t[15].tinta=vdc.tinta15;
		df->t.t[15].papel=vdc.papel15;
		df->t.t[16].tinta=vdc.tinta16;
		df->t.t[16].papel=vdc.papel16;
		df->t.t[17].tinta=vdc.tinta17;
		df->t.t[17].papel=vdc.papel17;
		df->t.t[18].tinta=vdc.tinta18;
		df->t.t[18].papel=vdc.papel18;
		df->t.t[19].tinta=vdc.tinta19;
		df->t.t[19].papel=vdc.papel19;
		df->t.t[20].tinta=vdc.tinta20;
		df->t.t[20].papel=vdc.papel20;
		df->t.t[21].tinta=vdc.tinta21;
		df->t.t[21].papel=vdc.papel21;
		df->t.t[22].tinta=vdc.tinta22;
		df->t.t[22].papel=vdc.papel22;
		df->t.t[23].tinta=vdc.tinta23;
		df->t.t[23].papel=vdc.papel23;
		df->t.t[24].tinta=vdc.tinta24;
		df->t.t[24].papel=vdc.papel24;
		df->t.t[25].tinta=vdc.tinta25;
		df->t.t[25].papel=vdc.papel25;
		df->t.t[26].tinta=vdc.tinta26;
		df->t.t[26].papel=vdc.papel26;
		df->t.t[27].tinta=vdc.tinta27;
		df->t.t[27].papel=vdc.papel27;
		df->t.t[28].tinta=vdc.tinta28;
		df->t.t[28].papel=vdc.papel28;
		df->t.t[29].tinta=vdc.tinta29;
		df->t.t[29].papel=vdc.papel29;
		df->t.t[30].tinta=vdc.tinta30;
		df->t.t[30].papel=vdc.papel30;
		nc++;
	}
	return(0);
}

static int fcargatema(bloques *b,ftrigers *ft)
{
	char tema[LTEMA];
	memset(tema,0,sizeof(tema));
	dameparametro(b,ft,0, V10CADENA, tema);
	return(cargacolores(tema));
}

static int fcargatemaypaleta(bloques *b,ftrigers *ft)
{
	char tema[LTEMA],paleta[MAXNOMBREV10]="";
	memset(tema,0,sizeof(tema));
	dameparametro(b,ft,0, V10CADENA, tema);
	dameparametro(b,ft,1, V10CADENA, paleta);

	cargacolores(tema);
	return(asignacolorbloque(b,paleta));
}

static int fcargapaleta(bloques *b,ftrigers *ft)
{
	char paleta[MAXNOMBREV10]="";
	dameparametro(b,ft,0, V10CADENA, paleta);
	return(asignacolorbloque(b,paleta));
}

// a V10_COLOR le carga una paleta
// a __COLOR le carga un color de la paleta del bloque de datos

void inittrigcolores() {
	cargacolores(TEMAESTANDAR);
	declaratriger("FCARGATEMA",fcargatema,NULL);
	declaratriger("FCARGATEMAYPALETA",fcargatemaypaleta,NULL);
	declaratriger("FCARGAPALETA",fcargapaleta,NULL);
}
