#include "v10wwwform.h"

static int recolocarbloques=0;
#define TOPVENTANA 1
#define LEFTVENTANA 0
#define LIMITEVENTANA 50


void v10recolocaform(forms *f) 
{
	int i,mintop=0,minbottom=0,topbloque=0,bottombloque=0;
	bloques *b;
	recolocarbloques=0;
	for (i=0;i<f->nbloques;i++) {
		b=f->b[i];
		topbloque=b->vi.w.y1-1;
		bottombloque=b->vi.w.y1-1 + ((b->vi.w.y2+3) -  (b->vi.w.y1));
		if (mintop==0 || topbloque<mintop) mintop=topbloque;
		if (minbottom<bottombloque) minbottom=bottombloque;
	}
	if (minbottom-mintop<=LIMITEVENTANA) recolocarbloques=1;
}

double damepxcol(bloques *b) 
{
	if (b && b->pxcol) return((double)b->pxcol);
	else return(v10htmlconf.pixelescol);
}

int damepxfila(bloques *b) 
{
	if (b && b->pxfila) return(b->pxfila);
	else return(v10htmlconf.pixelesfila);
}

void v10damedimensionesbloque(bloques *b, int *left, int *top, int *ancho, int *largo) 
{
	*ancho=v10x2pxsm((b->vi.w.x2+4) - (b->vi.w.x1),damepxcol(b)); 
	if (b->maxlontaby==0) *largo=v10y2pxsm(((b->vi.w.y2+3) -  (b->vi.w.y1))-1,damepxfila(b)); 
    else                  *largo=v10y2pxsm(b->maxlontaby,damepxfila(b)); 
	if (recolocarbloques==0) {
		*top=v10y2px(b->vi.w.y1-1,damepxfila(b));   
		*left=v10x2px(b->vi.w.x1,damepxcol(b));  
	} else {
		int nuevotop,mintop;    
		mintop=b->form->b[0]->vi.w.y1-1;
		nuevotop=TOPVENTANA+((b->vi.w.y1-1)-mintop);;
		*top=v10y2px(nuevotop,damepxfila(b));
		*left=v10x2px(b->vi.w.x1,damepxcol(b));
	}
	if (b->vipx.posx) *left=b->vipx.posx;
	if (b->vipx.posy) *top=b->vipx.posy;
	if (b->vipx.lonx) *ancho=b->vipx.lonx;
	if (b->vipx.lony) *largo=b->vipx.lony;
}
