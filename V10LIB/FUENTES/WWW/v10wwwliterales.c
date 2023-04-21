#include "v10wwwform.h"

#define MAXCOLUMNASPANTALLA 200

static int buscaliteral(char *texto) {
	char *ptr;  
	ptr=texto;
	do {
		ptr++;
        if (*ptr=='\\') break;
		if (strlen(ptr)==0) break;
		if (*ptr==' ' &&  (strlen(ptr+1)>0 && *(ptr+1)==' ' ) && 
			(strlen(ptr+2)>0 && *(ptr+2)==' ' ))
			break;
	} while (1);

	return((int)(ptr-texto));
}


static void v10insertalabel(bloques *b,char *texto,int left,int top,int nbloque) 
{
	v10wwwoem2ansi(texto);
	v10ansitohtml(texto);
	if (b->regpag==1) sprintf(v10datoshtml+strlen(v10datoshtml),
		"<label id=\"lbbl%d\" style=\"left:%dpx;top:%dpx\">%s</label>\n",
		nbloque,left,top,texto);
	else sprintf(v10datoshtml+strlen(v10datoshtml),
		"<label id=\"lbbl%d\" style=\"left:%dpx;top:%dpx;width:%dpx\">%s</label>\n",
		nbloque,left,top,v10x2pxsm(strlen(texto),damepxcol(b)),texto);
}


static void v10buscalabels(int nbloque,bloques *b,int *cx,int cy,int ancla,char *textofila) 
{
	int largoliteral=0;
	char *ptr;
	char textonewlabel[MAXCADENA]="";
	int len,top,left,x,y;
    formtabs *ftab;
	delrecuadrooem(textofila);
	while (*cx<b->vi.largo) {
		ptr=textofila;
		while ( *ptr==' ')  {
			*cx+=1;
			if (strlen(ptr)<=1) break;
			ptr++;
		}
		ltrim(textofila);
		if (strlen(textofila)==0) return; // fin del recorrido
		largoliteral=buscaliteral(textofila);
		if (largoliteral==0) return;
		strcopia(textonewlabel,textofila,largoliteral);
        if (*textonewlabel=='\\') *textonewlabel=' ';
        damepostab(b,*cx,cy,&x,&y,&ftab);
		//top=v10y2pxsm(y,damepxfila(b));
		top=v10y2pxsm(cy,damepxfila(b));
		left=v10x2pxsm(ancla+*cx,damepxcol(b));
		if (*textonewlabel) v10insertalabel(b,textonewlabel,left,top,nbloque);
		len=strlen(textofila+largoliteral);
		memmove(textofila,textofila+largoliteral,len);
		textofila[len]=0;		
		*cx+=largoliteral;	
	}
}


#define MAXFRAMES 30

static fframes f[MAXFRAMES];
static int nf=0;
	
static void cargaframes(bloques *b,int fila,int ancla,char *texto) 
{
	int car=0,col,iframe,numcar,inombre;	
	for (col=0;col<strlen(texto);col++) {
		car = texto[col];		
		if (car == pasaoemchar(v10marco[SUPIZQ][1])) {	// esquina superior izquierda
			f[nf].posinix=col;
			f[nf].posiniy=fila;
			f[nf].estado=1;
			texto[col]=' ';
			nf++;
		}
		if (car == pasaoemchar(v10marco[SUPDER][1])) { // esquina superior derecha
								// busca frame en curso abierto a falta de este car�cter, para cerrarlo
			for (iframe=nf-1;iframe>=0;iframe--) {
				texto[col]=' ';
				if (f[iframe].estado==1 && f[iframe].posiniy==fila) { 
					*(f[iframe].nombre)=0;
					numcar=0;
					for (inombre=f[iframe].posinix;inombre<col;inombre++) {
						if (texto[inombre]==pasaoemchar(v10marco[BARRAVER][1]) || texto[inombre]==pasaoemchar(v10marco[BARRAHOR][1])) texto[inombre]=' ';
						else f[iframe].nombre[numcar++]=texto[inombre];
						texto[inombre]=' ';
					}				
					f[iframe].nombre[numcar]=0;
					ltrim(trim(f[iframe].nombre));
					f[iframe].posfinx=col;
					f[iframe].posx = v10x2pxsm(ancla+f[iframe].posinix,damepxcol(b));// - ((int)(v10htmlconf.pixelescol/2));
					f[iframe].posy = v10y2pxsm(fila,damepxfila(b));
					f[iframe].lonx = v10x2pxsm((f[iframe].posfinx - f[iframe].posinix)+1,damepxcol(b)) + ((int)(v10htmlconf.pixelescol/2));								
					f[iframe].estado=2;
					break;
				}
			}
		}
		if (car == pasaoemchar(v10marco[INFIZQ][1])) {
			texto[col]=' ';
			for (iframe=nf-1;iframe>=0;iframe--) {
				if (f[iframe].estado==2 && f[iframe].posinix==col) { 
					f[iframe].posfiny=fila;
					f[iframe].estado=3;
					break;
				}
			}
		}
		if (car == pasaoemchar(v10marco[INFDER][1])) {
			texto[col]=' ';
			for (iframe=nf-1;iframe>=0;iframe--) {
				if (f[iframe].estado==3 && f[iframe].posfinx==col && f[iframe].posfiny==fila) { 	
					f[iframe].lony = v10y2pxsm(f[iframe].posfiny-f[iframe].posiniy,damepxfila(b))+(v10htmlconf.pixelesfila/2);												
					f[iframe].estado=4;
					break;
				}
			}
		}
		if (car==pasaoemchar(v10marco[BARRAVER][1]) || car==pasaoemchar(v10marco[BARRAHOR][1])) texto[col]=' ';
	}
}

void damelabelfila(bloques *b,int fila,int ancla,char *texto) 
{
	int i;
	tpixels *inicar,*car;
	inicar=(tpixels *) (b->vi.contenido+(fila*b->vi.largo));
	if (!inicar) return;
	for (i=0;i<b->vi.largo;i++) {
		car=inicar+i;		
		texto[i]=car->ch;
	}    
	texto[i]=0;
	cargaframes(b,fila,ancla,texto);	
	trim(texto);
}

void v10labels2html(int nbloque,bloques *b,formtabs *ftab) 
{
	int cx,cy,i,inicio,fin;
	char labelsfila[MAXCADENAHTML];
	int ancla=b->s->v.x1-b->s->v1->x1;	
	if (b->wtitulos && b->regpag>1) return;
	memset(f,0,MAXFRAMES * sizeof(fframes));
	nf=0;
    if (ftab==NULL) {
        inicio=0;
        fin=b->vi.alto;
    } else {
        inicio=ftab->posy;
        fin=ftab->posy+ftab->lony;
    }
	for (cy=inicio;cy<fin;cy++) {
		cx=0;
		damelabelfila(b,cy,ancla,labelsfila); // obtengo los literales de la fila
		v10buscalabels(nbloque,b,&cx,cy,ancla,labelsfila); 
	}
    if (ftab==b->ftab) {
        if (b->frames) free(b->frames);
        b->frames=calloc(MAXFRAMES,sizeof(fframes));
        b->nbframes=0;	
        for (i=0;i<nf;i++) {
            if (f[i].estado>1) {
                b->frames[b->nbframes].posx=f[i].posx;
                b->frames[b->nbframes].posy=f[i].posy;
                b->frames[b->nbframes].lonx=f[i].lonx;			
                if (f[i].estado==2 || f[i].estado==3) b->frames[b->nbframes].lony=0;
                else b->frames[b->nbframes].lony=f[i].lony;
                strcpy(b->frames[b->nbframes].nombre,f[i].nombre);
                b->nbframes++;
            }
        }
    }
	// pasa frames cargados en distintos estados, a los frames del bloque
}