/****
* VDPEDIDOS.C
*                                                    
* Propósito: Procesos y algoritmos en C propios del tratamiento de pedidos 
*                                            
* Autor  : FGS
* Fecha  : 5-3-2008                                                        
******
*  Modificaciones:
****/

#include "vdpedidos.h"


static VERSIONPEDIDOAGE versionpedage[MAXAGE];
static int numagepedido;
static int maxlinbu;
static int nlineas=0;
static int ncajas=0;
static int terminadas=0;
static long primerbultouni;
static double pesopedido;
static double volumenpedido;
static double numuni=0L;
static double volumen=0L;
static char minimizacajaszona[LSWITCH];
static char trataordenmovim[LSWITCH];
static vdcajavols ptr_cajas[MAXCAJAS];
static linarts slinart;
static linarts *ptr_lineas;
static linarts **ptr_ptrs;


static int funcionsort(const void *a,const void *b) {
  return(*(long *)a<*(long *)b);
}

static void ordena(long *largo,long *ancho,long *alto) {
  long dimcaja[3];

  dimcaja[0]=*largo;
  dimcaja[1]=*ancho;
  dimcaja[2]=*alto;
  qsort(dimcaja,3,sizeof(long),funcionsort);
  *largo=dimcaja[0];
  *ancho=dimcaja[1];
  *alto=dimcaja[2];
}

static int leecajas(vdpedidocabs *pec,vdbultocabs *buc) {
    int ret;

    memset(ptr_cajas,0,sizeof(ptr_cajas));
    ncajas=0;
	ret=CAJAVOLbuscademayoramenor(buc->tipovol,&ptr_cajas[ncajas]);
    if(ret) {
		v10logcomen(LOGERROR,pec->comenpec,"leecajas - ERROR Volumetria %s de bulto %s no tiene cajas /n",buc->tipovol,buc->codbulto);
        return(FAILURE);
    }
    do {
        ptr_cajas[ncajas].altura=ptr_cajas[ncajas].altocaja;
        ordena(&ptr_cajas[ncajas].largocaja,&ptr_cajas[ncajas].anchocaja,&ptr_cajas[ncajas].altocaja);
        ptr_cajas[ncajas].volumencaj=(double)ptr_cajas[ncajas].maxllenado*(double)ptr_cajas[ncajas].altocaja*(double)ptr_cajas[ncajas].largocaja*(double)ptr_cajas[ncajas].anchocaja/100.0;
        if (++ncajas>=MAXCAJAS) {
			v10logcomen(LOGERROR,pec->comenpec,"leecajas - ERROR Alcanzado límite de %ld cajas en volumetría %s de bulto %s /n",MAXCAJAS,buc->tipovol,buc->codbulto);
			return(FAILURE);
        }
    }while(CAJAVOLnextdemayoramenor(&ptr_cajas[ncajas])==SUCCESS);

    return(SUCCESS);
}

static int tomadatos(vdpedidocabs *pec,vdbultocabs *buc) {
    int ret;
	long ordenmovim=0;
    vdcajavols *ptr=ptr_cajas;
    vdartics art;
	vdbultos bulto;

    v10log(LOGNORMAL,"tomadatos -     Leyendo artículos de bulto para volumetría %s \n",buc->tipovol);
    if(ret=BULTObuscabultolinordenmovim(buc->codbulto,&bulto)) {
		v10logcomen(LOGERROR,pec->comenpec,"tomadatos - ERROR Bulto %s no tiene líneas /n",buc->codbulto);
        return(FAILURE);
    }
    nlineas=0;
    terminadas=0;
    numuni=0;
    volumen=0;

    do {
        memset(&slinart,0,sizeof(slinart));
		ret=ARTselcodart(bulto.codart,&art);
        if (ret){
	        v10log(LOGERROR,"tomadatos - ERROR Seleccionando artículo %s de bulto %s /n",bulto.codart,buc->codbulto);
            return(FAILURE);
        }
        strcpy(slinart.codart,bulto.codart);
        strcpy(slinart.codlot,bulto.codlot);
        strcpy(slinart.unidadeshost,art.unidadeshost);
        strcpy(slinart.unidades,art.unidades);
        slinart.seqlinea=bulto.seqlinea;
        slinart.codmov=bulto.codmov;
        slinart.unipaq=art.unipaq;
        slinart.pesouni=art.pesouni;
        slinart.pedidav10=bulto.cantpedida;
		slinart.pedida=conviertearticulo2host(bulto.cantpedida,bulto.codart);
        slinart.numuni=slinart.pedida;
        slinart.altura=art.altouni;
        slinart.largouni=art.largouni;
        slinart.anchouni=art.anchouni;
        slinart.altouni=art.altouni;
        ordena(&slinart.largouni,&slinart.anchouni,&slinart.altouni);
        if (*art.swttumbable=='S') {
            slinart.altura=slinart.altouni;
        }
        if (!art.coefuni) slinart.coefuni=100;
        else slinart.coefuni=art.coefuni;
        slinart.volumenuni=(double)art.altouni*art.anchouni*art.largouni*(1+1.0-slinart.coefuni/100.0);
        //PAQUETES
        if (slinart.unipaq) {
            slinart.altura=art.altopaq;
            slinart.largopaq=art.largopaq;
            slinart.anchopaq=art.anchopaq;
            slinart.altopaq=art.altopaq;
            ordena(&slinart.largopaq,&slinart.anchopaq,&slinart.altopaq);
            if (*art.swttumbable=='S') {
                slinart.altura=slinart.altopaq;
            }
            if (!art.coefpaq) slinart.coefpaq=100;
            else slinart.coefpaq=art.coefpaq;
            slinart.volumenpaq=(double)art.altopaq*art.anchopaq*art.largopaq*(1+1.0-slinart.coefpaq/100.0);
            if (slinart.volumenpaq==0) {
				v10logcomen(LOGERROR,pec->comenpec,"tomadatos - ERROR Artículo %s tiene paquetes y el volumen del paquete es 0 /n",bulto.codart);
                return(FAILURE);
            }
            slinart.paqbulto=floor(ptr->volumencaj/slinart.volumenpaq);
            slinart.pesopaq=art.pesopaq;
            if (slinart.paqbulto*slinart.pesopaq>ptr->maxpeso) {
                slinart.paqbulto=floor(ptr->maxpeso/slinart.pesopaq);
            }
            if (slinart.paqbulto==0) slinart.paqbulto=1;
			slinart.volbulto=slinart.paqbulto*slinart.volumenpaq;
            slinart.pedida=slinart.numuni;
            slinart.unibulto=slinart.paqbulto*slinart.unipaq;
            slinart.npaquetes=floor(slinart.pedida/slinart.unipaq);
			slinart.nsueltas=fmod(slinart.pedida,slinart.unipaq);
        }else {  
			//UNIDADES
            slinart.volumenpaq=0;
            slinart.paqbulto=0;
            if (slinart.volumenuni==0) {
				v10logcomen(LOGERROR,pec->comenpec,"tomadatos - ERROR Artículo %s tiene volúmen de unidad 0 /n",bulto.codart);
                return(FAILURE);
            }
            slinart.unibulto=floor(ptr->volumencaj/slinart.volumenuni);
            if (slinart.unibulto*slinart.pesouni>ptr->maxpeso) {
                slinart.unibulto=floor(ptr->maxpeso/slinart.pesouni);
            }
            if (slinart.unibulto==0) slinart.unibulto=1;
            slinart.npaquetes=0;
            slinart.nsueltas=slinart.pedida;
			slinart.volbulto=slinart.unibulto*slinart.volumenuni;
        }

        if (slinart.nsueltas) {
            slinart.maxlargo=slinart.largouni;
            slinart.maxancho=slinart.anchouni;
            slinart.maxalto=slinart.altouni;
        }
        if (slinart.npaquetes) {
            slinart.maxlargo=slinart.largopaq;
            slinart.maxancho=slinart.anchopaq;
            slinart.maxalto=slinart.altopaq;
        }else 
			if (slinart.unipaq >0) 
				slinart.altura=slinart.altouni;

        if ((slinart.npaquetes*slinart.volumenpaq+slinart.nsueltas*slinart.volumenuni)> ptr->volumencaj ||
            (slinart.npaquetes * slinart.pesopaq + slinart.nsueltas* slinart.pesouni )> ptr->maxpeso ) {
            slinart.nbultos=(long)floor(slinart.pedida/slinart.unibulto);
            slinart.numuni-=slinart.nbultos*slinart.unibulto;
            if (slinart.npaquetes) slinart.npaquetes-=slinart.nbultos*slinart.paqbulto;
            else slinart.nsueltas-=slinart.nbultos*slinart.unibulto;
        } else {
            slinart.nbultos=0;
        }
        numuni+=slinart.numuni;
        if (slinart.npaquetes || slinart.nsueltas) {
            if ((slinart.npaquetes*slinart.volumenpaq+slinart.nsueltas*slinart.volumenuni)>((ptr->volumencaj/100)*ptr->minllenado)/(ptr->maxllenado/100.0)) {
                slinart.homogeneo=1;
                slinart.volpico=0;
                slinart.terminada=TERMINFASE1+1;
                terminadas++;
            } else {
                slinart.homogeneo=0;
                slinart.volpico=slinart.npaquetes*slinart.volumenpaq+slinart.nsueltas*slinart.volumenuni;
                slinart.pesopico=slinart.npaquetes*slinart.pesopaq+slinart.nsueltas*slinart.pesouni;
                slinart.terminada=0;
                volumen+=slinart.volpico;
            }
        } else {
            slinart.homogeneo=1;
            slinart.volpico=0;
            slinart.terminada=TERMINFASE1+1;
            terminadas++;
        }
        slinart.npicos=1;
        if (ptr->maxpicos==1) {
            slinart.terminada=TERMINFASE1;
            terminadas++;
        }
        slinart.sig=NULL;
        slinart.genera=1;
        slinart.bulto=nlineas+1;
		slinart.ordenmovim=ordenmovim++;
// COMENTADO HASTA QUE SE CREEN LAS TABLAS DE DISPLAYS
//		ejefetch_cursor(vdselcodinfozona);
        ptr_lineas[nlineas]=slinart;
        nlineas++;
        if (nlineas>=maxlinbu) {
			v10logcomen(LOGERROR,pec->comenpec,"tomadatos - ERROR Alcanzado máximo número de líneas por bulto (%ld) para bulto %s /n",MAXLINBU,buc->codbulto);
            return(FAILURE);
        }
	    v10log(LOGNORMAL,"tomadatos - Determinados %ld bultos de unidades completos, %lf paquetes y %lf unidades sueltas para artículo %s\n",slinart.nbultos,slinart.npaquetes,slinart.nsueltas,slinart.codart);
    }while(BULTOnextbultolinordenmovim(&bulto)==SUCCESS);

    return(SUCCESS);
}

static int fcompara(const void *a,const void *b) {
    const linarts * const *l1=a;
    const linarts * const *l2=b;

    if ((*l1)->terminada<(*l2)->terminada) return(1);
    if ((*l1)->terminada>(*l2)->terminada) return(-1);
	if (!strcmp(trataordenmovim,"S")) {
       if ((*l1)->ordenmovim<(*l2)->ordenmovim) return(-1);
       if ((*l1)->ordenmovim>(*l2)->ordenmovim) return(1);
	}
    if (((*l1)->nbultos+(*l1)->homogeneo)<((*l2)->nbultos+(*l2)->homogeneo)) return(1);
    if (((*l1)->nbultos+(*l1)->homogeneo)>((*l2)->nbultos+(*l2)->homogeneo)) return(-1);
    if ((*l1)->volpico<(*l2)->volpico) return(1);
    if ((*l1)->volpico>(*l2)->volpico) return(-1);
    if ((*l1)->pedida<(*l2)->pedida) return(-1);
    return(1);
}

static void calculapico(int i,int j,int fase) {
    linarts *nuevo;

    if (ptr_ptrs[i]->sig!=NULL) {
        nuevo=ptr_ptrs[i]->sig;
        while(nuevo->sig!=NULL) 
			nuevo=nuevo->sig;
        nuevo->sig=ptr_ptrs[j];
    } else {
        ptr_ptrs[i]->sig=ptr_ptrs[j];
    }

    ptr_ptrs[i]->pesopico+=ptr_ptrs[j]->pesopico;
    ptr_ptrs[i]->volpico+=ptr_ptrs[j]->volpico;
    ptr_ptrs[i]->numuni+=ptr_ptrs[j]->numuni;
    ptr_ptrs[i]->npicos++;
    if (ptr_ptrs[i]->npicos>=ptr_cajas[0].maxpicos ) {
        ptr_ptrs[i]->terminada=fase;
        terminadas++;
    }
    if (ptr_ptrs[j]->maxlargo>ptr_ptrs[i]->maxlargo) ptr_ptrs[i]->maxlargo=ptr_ptrs[j]->maxlargo;
    if (ptr_ptrs[j]->maxancho>ptr_ptrs[i]->maxancho) ptr_ptrs[i]->maxancho=ptr_ptrs[j]->maxancho;
    if (ptr_ptrs[j]->maxalto>ptr_ptrs[i]->maxalto) ptr_ptrs[i]->maxalto=ptr_ptrs[j]->maxalto;
    if (ptr_ptrs[j]->altura>ptr_ptrs[i]->altura) ptr_ptrs[i]->altura=ptr_ptrs[j]->altura;
    ptr_ptrs[j]->maxlargo=0;
    ptr_ptrs[j]->maxancho=0;
    ptr_ptrs[j]->maxalto=0;
    ptr_ptrs[j]->genera=0;
    ptr_ptrs[j]->bulto=ptr_ptrs[i]->bulto;
    ptr_ptrs[j]->terminada=fase+2;
    terminadas++;
    ptr_ptrs[j]->volpico=0;
    ptr_ptrs[j]->numuni=0;
}

static int calculabultosaux(vdpedidocabs *pec,int *ult_terminadas,int terminadafase,int bultosi,int bultosj,int mismazona) {
    int i,j;

    if (terminadas>=nlineas) 
		return(SUCCESS);
    qsort((void *)(ptr_ptrs+*ult_terminadas),nlineas-*ult_terminadas,sizeof(linarts *),fcompara);
    *ult_terminadas=terminadas;

    for(i=0;i<nlineas;i++) {
		if (ptr_ptrs[i]->terminada) 
			continue;
        if (ptr_ptrs[i]->nbultos || bultosi==0) {
		    v10log(LOGNORMAL,"calculabultosaux - Tratando referencia %s con %ld bultos de %lf unidades y %f unidades sueltas\n",
                              ptr_ptrs[i]->codart,ptr_ptrs[i]->nbultos,ptr_ptrs[i]->unibulto,ptr_ptrs[i]->nsueltas);
            if (!ptr_ptrs[i]->volpico) {
				v10logcomen(LOGERROR,pec->comenpec,"calculabultosaux - ERROR Volúmen del pico es 0 /n");
		        return(FAILURE);
            }
            for(j=i+1;j<nlineas ;j++) {
				if (ptr_ptrs[j]->terminada) 
					continue;
				if (mismazona==1 && ptr_ptrs[i]->codinfozona!=ptr_ptrs[j]->codinfozona) 
					continue;
                if (!ptr_ptrs[j]->nbultos || bultosj==0) {
					if ((ptr_ptrs[i]->volpico+ptr_ptrs[j]->volpico)<=ptr_cajas[0].volumencaj &&
                        (ptr_ptrs[i]->pesopico+ptr_ptrs[j]->pesopico)<=ptr_cajas[0].maxpeso) {
					   v10log(LOGNORMAL,"calculabultosaux - Tratando referencia %s con  %f unidades sueltas\n",
					                     ptr_ptrs[i]->codart,ptr_ptrs[i]->numuni);
                       calculapico(i,j,terminadafase);
                       if (ptr_ptrs[i]->terminada) 
						   break;
					}
                }
            }

        }
    }

    return(SUCCESS);
}

static int calculabultos(vdpedidocabs *pec) {
    int ret,i,
        ult_terminadas = 0;

    for(i=0;i<nlineas;i++) 
		ptr_ptrs[i]=ptr_lineas+i;

    switch (atoi(minimizacajaszona)) {
		case 1: if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE2,1,0,0))return(ret);
			    if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE3,1,1,0))return(ret);
				if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE6,0,0,0))return(ret);
				break;
		case 2: if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE2,1,0,1))return(ret);
			    if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE4,1,0,0))return(ret);
				if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE3,1,1,1))return(ret);
				if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE5,1,1,0))return(ret);
				if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE6,0,0,1))return(ret);
				if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE6,0,0,0))return(ret);
				break;
		case 3: if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE2,1,0,1))return(ret);
			    if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE3,1,1,1))return(ret);
				if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE4,1,0,0))return(ret);
				if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE5,1,1,0))return(ret);
				if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE6,0,0,1))return(ret);
				if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE6,0,0,0))return(ret);
				break;
		case 4:	if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE2,1,0,1))return(ret);
				if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE3,1,1,1))return(ret);
				if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE6,0,0,1))return(ret);
				if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE4,1,0,0))return(ret);
				if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE5,1,1,0))return(ret);
				if (ret=calculabultosaux(pec,&ult_terminadas,TERMINFASE6,0,0,0))return(ret);
				break;
	}
    for(i=0;i<nlineas;i++){
        if (!ptr_ptrs[i]->terminada && !ptr_ptrs[i]->genera) {
		    v10log(LOGNORMAL,"calculabultos - Se fuerza generación de bulto. Linea de bulto para artículo %s sin terminar \n",ptr_ptrs[i]->codart);
            ptr_ptrs[i]->genera=1;
        }
    }

    return(SUCCESS);
}

static int rellenacabecera(vdbultocabs *bucnuevo,vdbultocabs *buc,vdbultolins *bulnuevo)
{
	int ret=0;
	char digitoean[2]="";
	vdbultos bulto;

    memset(bucnuevo,0,sizeof(vdbultocabs));
    strcpy(bucnuevo->coddiv,buc->coddiv);
    bucnuevo->anoped=buc->anoped;
    strcpy(bucnuevo->codped,buc->codped);
    bucnuevo->seqped=buc->seqped;
    strcpy(bucnuevo->tipobulto,buc->tipobulto);
    strcpy(bucnuevo->tipovol,buc->tipovol);
    strcpy(bucnuevo->swtanular,buc->swtanular);
    bucnuevo->pesoteorico=buc->pesoteorico;
    bucnuevo->pesoreal=0;
    bucnuevo->status=STBUCPDTEETIQ;
	strncpy(digitoean,buc->codbulto,1);
    ret=BULTObuscacodbulto(digitoean,buc->coddiv,&bulto);
	if (ret) 
        return(ret);
    strcpy(bucnuevo->codbulto,bulto.codbulto);
    strcpy(bulnuevo->codbulto,bulto.codbulto);
    bucnuevo->feccreado=getdate();
    cent2a(gettime(),0,':',bucnuevo->horacreado);

	return(0);
}

static int rellenalinea(char *codbulto,vdbultolins *ptr_bultolin,linarts *ptr,double cantidad)
{
    int flag=0;
    int lencodbulto=strlen(codbulto);
    int ret=0;
	char limpiamov[2]="S";
    vdbultolins bulaux,blin;
	vdbultos bulto;
	vdmovauxs movim;

    memset(ptr_bultolin,0,sizeof(vdbultolins));
    strcpy(ptr_bultolin->codbulto,codbulto);
    strcpy(ptr_bultolin->codart,ptr->codart);
    strcpy(ptr_bultolin->codlot,ptr->codlot);
    ret=BULTObuscasecuencia(codbulto,&bulto);
	if (ret) {
		v10log(LOGERROR,"rellenalinea - ERROR Obteniendo siguiente secuencial de linea de bulto para bulto\n",codbulto);
        return(ret);
	}
	ptr_bultolin->seqlinea=bulto.secuencia;
	ptr_bultolin->cantpedida=conviertearticulo2v10(cantidad,ptr->codart);
    ret=BULbuscacodmov(ptr->codmov,&bulaux);
    savepoint("rellenalinea");
    do {
			ret=MOVAUXprocpartemov(bulaux.codmov,bulaux.cantpedida-ptr_bultolin->cantpedida,ptr_bultolin->codmov,limpiamov,&movim);
            if (ret) {
				v10log(LOGNORMAL,"rellenalinea - ERROR ORACLE %ld No puedo crear movimiento independiente para artículo %s en bulto %s \n",ret,ptr_bultolin->codart,codbulto);
                return(ret);
            } else {
				ptr_bultolin->codmov=movim.nuevomov;
                flag=1;
			}
            ret=BULbuscacodmov(ptr_bultolin->codmov,&blin);
            if (ret) {
                v10log(LOGERROR,"rellenalinea - No existe linea con el nuevo movimiento %ld\n",ptr_bultolin->codmov);
                return(ret);
            }
            BULdel(&blin,0);
    } while(BULnextcodmov(&bulaux)==SUCCESS);

    if (!flag) 
		ptr_bultolin->codmov=ptr->codmov;
    ptr_bultolin->cantservida=0;
    ptr_bultolin->status=STBULASERVIR;
	v10log(LOGNORMAL,"rellenalinea - Introduciendo en bulto %s, %lf unidades de la referencia %s \n",codbulto,ptr_bultolin->cantpedida,ptr->codart);
    return(0);
}

static int damecaja(double volumen,double peso,long maxlargo,long maxancho,long maxalto,long altura)
{
    int ret = -1;
    int indice ;

    for(indice=0;indice<ncajas;indice++){
         if (ptr_cajas[indice].volumencaj>=volumen && ptr_cajas[indice].maxpeso>=peso &&
             ptr_cajas[indice].largocaja>=maxlargo && ptr_cajas[indice].anchocaja>=maxancho &&
             ptr_cajas[indice].altocaja>=maxalto && ptr_cajas[indice].altura>=altura) 
			ret=indice;
    }
    return(ret);
}

static int insertacompletos(vdpedidocabs *pec,vdbultocabs *buc,linarts *ptr)
{
    int ret=0;
    int numerocaja;
    long cuantos=ptr->nbultos;
    double volumen,
		   peso_sueltas;
	char digitoean[2]="";
    vdbultocabs buc1;
    vdbultolins bul1;
	vdbultos bulto;

    ret=rellenacabecera(&buc1,buc,&bul1);
	if (ret) {
		v10logcomen(LOGERROR,pec->comenpec,"insertacompletos - ERROR Obteniendo nuevo código de bulto para bulto %s \n",buc->codbulto);
        return(ret);
	}
    if (ptr->paqbulto) {
        volumen=ptr->paqbulto*ptr->volumenpaq;
        peso_sueltas=ptr->paqbulto*ptr->pesopaq;
    } else {
        volumen=ptr->unibulto*ptr->volumenuni;
        peso_sueltas=ptr->unibulto*ptr->pesouni;
    }
    if (ptr->npaquetes){
  	   numerocaja=damecaja(volumen,peso_sueltas,ptr->largopaq,ptr->anchopaq,ptr->altopaq,ptr->altopaq);
  	 } else {
  	   numerocaja=damecaja(volumen,peso_sueltas,ptr->largouni,ptr->anchouni,ptr->altouni,ptr->altouni);
	 }
    numerocaja=damecaja(volumen,peso_sueltas,ptr->maxlargo,ptr->maxancho,ptr->maxalto,ptr->altura);
    if (numerocaja!=-1) {
        strcpy(buc1.tipocaja,ptr_cajas[numerocaja].tipocaja);
        buc1.pesoteorico=ptr_cajas[numerocaja].pesocaja+ptr_cajas[numerocaja].pesorelleno+peso_sueltas;
        buc1.volumen=(double)ptr_cajas[numerocaja].altocaja * (double)ptr_cajas[numerocaja].largocaja * (double)ptr_cajas[numerocaja].anchocaja /1000.0;

    } else {
		v10log(LOGERROR,"insertacompletos - ERROR Referencia %s demasiado grande. Volumetría %s de bulto %s no tiene cajas para este tamaño.\n",ptr->codart,buc->tipovol,buc->codbulto);
        return(FAILURE);
    }

    while (cuantos) {
        buc1.nbulto=primerbultouni++;
		ret=BUCinsert(&buc1,NOVERIFICA);
		if (ret) {
 			v10logcomen(LOGERROR,pec->comenpec,"insertacompletos - ERROR ORACLE %ld Insertando bulto %s \n",ret,buc1.codbulto);
			return(ret);
		}
        v10log(LOGNORMAL,"insertacompletos -      Bulto completo  %s, Volumetria %s Caja %s  Anular precintos %s \n",buc1.codbulto,buc1.tipovol,buc1.tipocaja,buc1.swtanular);
        pesopedido+=buc1.pesoteorico;
		volumenpedido+=buc1.volumen;
        ret=rellenalinea(buc1.codbulto,&bul1,ptr,ptr->unibulto);
        if (ret) return(ret);
		ret=BULinsert(&bul1,NOVERIFICA);
        if (ret) {
			v10logcomen(LOGERROR,pec->comenpec,"insertacompletos - ERROR ORACLE %ld Insertando líneas de bulto %s y artículo %s \n",ret,bul1.codbulto,bul1.codart);
            return(ret);
        }
        if (--cuantos) {
			strncpy(digitoean,buc->codbulto,1);
			ret=BULTObuscacodbulto(digitoean,buc->coddiv,&bulto);
			if (ret) {
				v10logcomen(LOGERROR,pec->comenpec,"insertacompletos - ERROR Obteniendo nuevo código de bulto para bulto\n",buc->codbulto);
				return(ret);
			}
			strcpy(buc1.codbulto,bulto.codbulto);
		}
    }

    return(ret);
}

static int insertahomogeneo(vdpedidocabs *pec,vdbultocabs *buc,linarts *ptr)
{
    int ret;
    vdbultocabs buc1;
    vdbultolins bul1;
    double volumen;
    double peso_sueltas;
    int numerocaja;

    ret=rellenacabecera(&buc1,buc,&bul1);
	if (ret) {
		v10logcomen(LOGERROR,pec->comenpec,"insertahomogeneo - ERROR Obteniendo nuevo código de bulto para bulto %s \n",buc->codbulto);
        return(ret);
	}
    buc1.nbulto=primerbultouni++;
    volumen=ptr->nsueltas*ptr->volumenuni+ptr->npaquetes*ptr->volumenpaq;
    peso_sueltas=ptr->nsueltas*ptr->pesouni+ptr->npaquetes*ptr->pesopaq;
    numerocaja=damecaja(volumen,peso_sueltas,ptr->maxlargo,ptr->maxancho,ptr->maxalto,ptr->altura);
    if (numerocaja!=-1) {
        strcpy(buc1.tipocaja,ptr_cajas[numerocaja].tipocaja);
        buc1.pesoteorico=ptr_cajas[numerocaja].pesocaja+ptr_cajas[numerocaja].pesorelleno+peso_sueltas;
        buc1.volumen=(double)ptr_cajas[numerocaja].altocaja * (double)ptr_cajas[numerocaja].largocaja * (double)ptr_cajas[numerocaja].anchocaja /1000.0;
    } else {
		v10log(LOGERROR,"insertahomogeneo - ERROR Referencia %s demasiado grande. Volumetría %s de bulto %s no tiene cajas para este tamaño.\n",ptr->codart,buc->tipovol,buc->codbulto);
        return(FAILURE);
    }
    ret=rellenalinea(buc1.codbulto,&bul1,ptr,ptr->nsueltas+ptr->npaquetes*ptr->unipaq);
    if (ret) return(ret);
	ret=BUCinsert(&buc1,NOVERIFICA);
	if (ret) {
		v10logcomen(LOGERROR,pec->comenpec,"insertahomogeneo - ERROR ORACLE %ld Insertando bulto %s \n",ret,buc1.codbulto);
		return(ret);
	}
    v10log(LOGNORMAL,"insertahomogeneo -      Bulto homogéneo %s, Volumetria %s Caja %s  Anular precintos %s \n",buc1.codbulto,buc1.tipovol,buc1.tipocaja,buc1.swtanular);
    pesopedido+=buc1.pesoteorico;
	volumenpedido +=buc1.volumen;
	ret=BULinsert(&bul1,NOVERIFICA);
    if (ret) {
		v10logcomen(LOGERROR,pec->comenpec,"insertahomogeneo - ERROR ORACLE %ld Insertando líneas de bulto %s y artículo %s \n",ret,bul1.codbulto,bul1.codart);
        return(ret);
    }

    return(ret);
}

static int insertapico(vdpedidocabs *pec,vdbultocabs *buc,linarts *ptr)
{
    vdbultocabs buc1;
    vdbultolins bul1;
    linarts *ptr_actual,*ptr_completos=NULL;
    double peso_sueltas=0.0;
    int numerocaja;
    int ret;


    ret=rellenacabecera(&buc1,buc,&bul1);
	if (ret) {
		v10logcomen(LOGERROR,pec->comenpec,"insertapico - ERROR Obteniendo nuevo código de bulto para bulto %s \n",buc->codbulto);
        return(ret);
	}
    buc1.nbulto=primerbultouni++;
    numerocaja=damecaja(ptr->volpico,ptr->pesopico,ptr->maxlargo,ptr->maxancho,ptr->maxalto,ptr->altura);
    if (numerocaja==-1){
		v10log(LOGERROR,"insertapico - ERROR Referencia %s demasiado grande. Volumetría %s de bulto %s no tiene cajas para este tamaño.\n",ptr->codart,buc->tipovol,buc->codbulto);
        return(FAILURE);
    }
    strcpy(buc1.tipocaja,ptr_cajas[numerocaja].tipocaja);
    buc1.pesoteorico=ptr_cajas[numerocaja].pesocaja+ptr_cajas[numerocaja].pesorelleno;
    buc1.volumen=(double)ptr_cajas[numerocaja].altocaja * (double)ptr_cajas[numerocaja].largocaja * (double)ptr_cajas[numerocaja].anchocaja /1000.0;
	ret=BUCinsert(&buc1,NOVERIFICA);
	if (ret) {
		v10logcomen(LOGERROR,pec->comenpec,"insertapico - ERROR ORACLE %ld Insertando bulto %s \n",ret,buc1.codbulto);
		return(ret);
	}
    v10log(LOGNORMAL,"insertapico -      Bulto pico %s, Volumetria %s Caja %s  Anular precintos %s \n",buc1.codbulto,buc1.tipovol,buc1.tipocaja,buc1.swtanular);
	volumenpedido+=buc1.volumen;
    for(ptr_actual=ptr;ptr_actual;ptr_actual=ptr_actual->sig){
		if (ptr_actual->nbultos && ptr_actual!=ptr) {
			if (ptr_completos) {
				v10log(LOGERROR,"insertapico - ERROR Mas de dos picos con bultos completos \n");
				return(-1);
			} else 
				ptr_completos=ptr_actual;
		}
        peso_sueltas+=ptr_actual->nsueltas*ptr_actual->pesouni+ptr_actual->npaquetes*ptr_actual->pesopaq;
        ret=rellenalinea(buc1.codbulto,&bul1,ptr_actual,ptr_actual->nsueltas+ptr_actual->npaquetes*ptr_actual->unipaq);
        if (ret) return(ret);
		ret=BULinsert(&bul1,NOVERIFICA);
        if (ret) {
			v10logcomen(LOGERROR,pec->comenpec,"insertapico - ERROR ORACLE %ld Insertando líneas de bulto %s y artículo %s \n",ret,bul1.codbulto,bul1.codart);
            return(ret);
        }
    }
	ret=BUCselvdbultocab(buc1.codbulto,&buc1);
	if (ret){
		v10logcomen(LOGERROR,pec->comenpec,"insertapico - ERROR ORACLE %ld Seleccionando datos de bulto %s \n",ret,buc1.codbulto);
		return(ret);
	}
	buc1.pesoteorico+=peso_sueltas;
	pesopedido+=buc1.pesoteorico;

	ret=BUCactualizavolumenypeso(&buc1,NOVERIFICA);
	if (ret){
		v10logcomen(LOGERROR,pec->comenpec,"insertapico - ERROR ORACLE %ld Actualizando volumen y peso de bulto %s \n",ret,buc1.codbulto);
		return(ret);
	}
	if (ptr_completos)  {
		ret=insertacompletos(pec,buc,ptr_completos);
		if (ret) return(ret);
	}

	return(0);
}

static int creabultos(vdpedidocabs *pec,vdbultocabs *buc)
{
    int ret;
    int i ;

    for(i=0;i<nlineas;i++) {
        if (ptr_ptrs[i]->genera==0) continue;
        if (ptr_ptrs[i]->nbultos){
            if(ret=insertacompletos(pec,buc,ptr_ptrs[i]))
				return(ret);
        }
        if (ptr_ptrs[i]->homogeneo) {
            if (ptr_ptrs[i]->nsueltas || ptr_ptrs[i]->npaquetes) {
                if(ret=insertahomogeneo(pec,buc,ptr_ptrs[i]))
					return(ret);
            }
        } else {
            if (ptr_ptrs[i]->volpico) {
                if(ret=insertapico(pec,buc,ptr_ptrs[i]))
					return(ret);
            } else {
				v10logcomen(LOGERROR,pec->comenpec,"creabultos - ERROR Linea tratada sin bultos que crear/n");
		        return(FAILURE);
            }
        }
    }
    return(0);
}

static int calculavolumetriabulto(vdpedidocabs *pec,vdbultocabs *buc) {
    int ret;
	vdbultos bulto;

    ret=BULTObuscalineabulto(buc->codbulto,&bulto);
	maxlinbu=ret==0?bulto.lineabulto:MAXLINBU;
    v10log(LOGNORMAL,"calculavolumetriabulto - Bulto %s con tipo de volumetria %s\n",buc->codbulto,buc->tipovol);
    v10log(LOGNORMAL,"calculavolumetriabulto - \t\tLeyendo cajas de tipo de volumetria %s\n",buc->tipovol);

    ret=leecajas(pec,buc);
	if(ret)
		return(ret);
    ptr_lineas=(linarts *)calloc(maxlinbu,sizeof(linarts));
    if (!ptr_lineas){
        v10log(LOGERROR,"calculavolumetriabulto - ERROR Obteniendo memoria para bulto %s /n",buc->codbulto);
        return(FAILURE);
    }
    ret=tomadatos(pec,buc);
    if (!ret) {
        ptr_ptrs=(linarts **)calloc(nlineas,sizeof(linarts *));
        if (!ptr_ptrs){
            v10log(LOGERROR,"calculavolumetriabulto - ERROR Obteniendo memoria para bulto %s y líneas %ld /n",buc->codbulto,nlineas);
            free(ptr_lineas);
            ptr_lineas=NULL;
            return(FAILURE);
        }
        ret=calculabultos(pec);
        if (!ret) 
			ret=creabultos(pec,buc);
        free(ptr_ptrs);
        ptr_ptrs=NULL;
    }
    free(ptr_lineas);
    ptr_lineas=NULL;
    return(ret);
}

static int actualizabultounivoldinamica(vdpedidocabs *pec,vdbultocabs *buc,vdcajavols *vol) {
    int ret=0;
	char digitoean[2]="";
    vdbultocabs bucnuevo;
    vdbultolins bul,bulnuevo;
	vdbultos bulto;

    ret=BULbuscalinbulto(buc->codbulto,&bul);
	if (ret) {
		v10logcomen(LOGERROR,pec->comenpec,"actualizabultounivoldinamica - ERROR Bulto %s sin líneas \n",buc->codbulto);
        return(ret);
    }
    buc->volumen=(double)vol->altocaja*vol->largocaja*vol->anchocaja/1000; // calculado en centímetros cúbicos
    bucnuevo=*buc;
    strcpy(bucnuevo.tipocaja,vol->tipocaja);
    bucnuevo.status=STBUCPDTEETIQ;
    bucnuevo.nbulto=primerbultouni++;
	strncpy(digitoean,buc->codbulto,1);
    ret=BULTObuscacodbulto(digitoean,buc->coddiv,&bulto);
	if (ret) {
		v10logcomen(LOGERROR,pec->comenpec,"actualizabultounivoldinamica - ERROR Obteniendo nuevo código de bulto para bulto\n",buc->codbulto);
        return(ret);
	}
	strcpy(bucnuevo.codbulto,bulto.codbulto);
	ret=BUCinsert(&bucnuevo,NOVERIFICA);
    if (ret) {
 		v10logcomen(LOGERROR,pec->comenpec,"actualizabultounivoldinamica - ERROR ORACLE %ld Insertando bulto %s \n",ret,bucnuevo.codbulto);
        return(ret);
    }
    do {
        bulnuevo=bul;
        strcpy(bulnuevo.codbulto,bucnuevo.codbulto);
		ret=BULdel(&bul,NOVERIFICA);
        if (ret) {
			v10logcomen(LOGERROR,pec->comenpec,"actualizabultounivoldinamica - ERROR ORACLE %ld Borrando linea de bulto %s \n",ret,buc->codbulto);
            return(ret);
        }
		ret=BULinsert(&bulnuevo,NOVERIFICA);
        if (ret) {
			v10logcomen(LOGERROR,pec->comenpec,"actualizabultounivoldinamica - ERROR ORACLE %ld Insertando líneas de bulto %s y artículo %s \n",ret,bulnuevo.codbulto,bulnuevo.codart);
            return(ret);
        }
    }while(BULnextlinbulto(&bul)==SUCCESS);

    if(ret=BUCdel(buc,NOVERIFICA)){
		v10logcomen(LOGERROR,pec->comenpec,"actualizabultounivoldinamica - ERROR ORACLE %ld Borrando bulto %s \n",ret,buc->codbulto);
    }
    return(ret);    
}

// Calcula volumetría de los bultos de un pedido
// PARAM1: Estructura del pedido al que calcular volumetría de bultos. 
// PARAM2: Indicador para calcular peso de caja completa y contenedor. 
// PARAM3: Indicador para calcular volumen de caja completa y contenedor. 
// PARAM4: Indicador para minimizar el número de entradas en zona de los 
//         bultos de picking de unidades.
// PARAM5: Indicador para tener en cuenta el campo ordenmovim de la ubicación
//         en el cálculo de la volumetría de los bultos de unidades.
VDEXPORT int vdcalculovolumetria(void *ptr,char *param) {
	int ret;
	vdpedidocabs *pec=ptr;
	vdbultocabs buc;
	vdcolcambiovols ccv;
	vdbultos bulto,bultoemba,bultocnt;
	
    vdstatuss staped;
    char chequeabultos[LSWITCH];

	v10log(LOGNORMAL,"vdcalculovolumetria: Procesando volumetria para pedido. %s \n",PEClog(pec));
    ret=BUCbuscabultosdeunpedido(pec->coddiv,pec->anoped,pec->codped,pec->seqped,&buc);
    if (ret) {
		v10log(LOGERROR,"vdcalculovolumetria: No se encuentran bultos para pedido. %s \n",PEClog(pec));
        return(ret);
    }
    pesopedido=0.0;
	volumenpedido=0.0;

	//Comprobar parámetros recibidos
	ret=numpieces(param,"#");
    if (ret < 4) {
        v10log(LOGERROR,"vdcalculovolumetria: Número de parámetros incorrecto, recibe %d necesita 4\n", ret);
		return(0);
	}
   	piece(param,minimizacajaszona,"#",1);
	piece(param,trataordenmovim,"#",2);
	piece(param,chequeabultos,"#",3);
    if (ret=damestabreviada("vdcalculovolumetria",param, 4, "#",NULL, "PEC", &staped, STPECPREPARANDO)) {
		v10logcomen(LOGERROR,pec->comenpec,"vdcalculovolumetria - ERROR Status PEC %s de pedido no existe para algoritmo vdcalculovolumetria \n",staped.dabstatus);
		return(ret);
	}

    savepoint("vdcalculovolumetria");
    ret=BULTOprocrenumerabultos(pec->coddiv,pec->anoped,pec->codped,pec->seqped,
		                        BULCNT,BULCNT,BULEMBA,0,&bulto);
    if (bulto.ret) {
		v10log(LOGERROR,"vdcalculovolumetria - ERROR Renumerando bultos de contenedores para pedido. %s \n",PEClog(pec));
        rollbacksavepoint("vdcalculovolumetria");
        return(bulto.ret);
    }
	ret=BULTObuscaultimobulto(pec->coddiv,pec->anoped,pec->codped,pec->seqped,"C",&bultocnt);
	if (ret){
		v10log(LOGERROR,"vdcalculovolumetria - ERROR Buscando último bulto de contenedores existente para pedido. %s \n",PEClog(pec));
        rollbacksavepoint("vdcalculovolumetria");
        return(ret);
	}
    ret=BULTOprocrenumerabultos(pec->coddiv,pec->anoped,pec->codped,pec->seqped,
		                        BULEMBA-bultocnt.ultimobulto,BULEMBA,BULUNI,0,&bulto);
    if (bulto.ret) {
		v10log(LOGERROR,"vdcalculovolumetria - ERROR Renumerando bultos de embalajes para pedido. %s \n",PEClog(pec));
        rollbacksavepoint("vdcalculovolumetria");
        return(bulto.ret);
    }
	ret=BULTObuscaultimobulto(pec->coddiv,pec->anoped,pec->codped,pec->seqped,"E",&bultoemba);
	if (ret){
		v10log(LOGERROR,"vdcalculovolumetria - ERROR Buscando último bulto de embalajes existente para pedido. %s \n",PEClog(pec));
        rollbacksavepoint("vdcalculovolumetria");
        return(ret);
	}
 	if (bultocnt.ultimobulto>bultoemba.ultimobulto)
		primerbultouni=bultocnt.ultimobulto+1;
	else
		primerbultouni=bultoemba.ultimobulto+1;
		
	do {
        if (*buc.tipobulto!='U') {
            BULTOprocvolumetriacajasycnt(buc.codbulto,0,&bulto);
			if (bulto.ret) {
				v10logcomen(LOGERROR,pec->comenpec,"vdcalculovolumetria - ERROR No se puede calcular volumen y peso del bulto %s para pedido. %s \n",buc.codbulto,PEClog(pec));
		        return(FAILURE);
			}
            continue;
        }
        if (*buc.tipovol==0) {
			v10logcomen(LOGERROR,pec->comenpec,"vdcalculovolumetria - ERROR Bulto %s sin volumetría para pedido. %s \n",buc.codbulto,PEClog(pec));
            return(FAILURE);
        }
		if (!es_blanco(pec->colcambiovol)) {
			ret=CCVbuscatipovolorig(pec->colcambiovol,buc.tipovol,&ccv);
			if (ret==0) {
		    	strcpy(buc.tipovol,ccv.tipovoldest);
                v10log(LOGNORMAL,"vdcalculovolumetria - Reemplazando volumetría origen %s por volumetría %s\n",ccv.tipovolorig,ccv.tipovoldest);
			}
		}
        if(CAJAVOLbuscademayoramenor(buc.tipovol,&ptr_cajas[0])){
 			v10logcomen(LOGERROR,pec->comenpec,"vdcalculovolumetria - ERROR Volumetría %s de bulto %s no tiene cajas para pedido. %s \n",buc.tipovol,buc.codbulto,PEClog(pec));
            return(FAILURE);
        }
        if (*ptr_cajas[0].voldinamica=='S') {
            v10log(LOGNORMAL,"vdcalculovolumetria - Detectada volumetría %s dinámica en bulto %s\n",buc.tipovol,buc.codbulto);
            if (ret=actualizabultounivoldinamica(pec,&buc,&ptr_cajas[0])) {
                rollbacksavepoint("vdcalculovolumetria");
                return(ret);
            }
            continue;
        }
        ret=calculavolumetriabulto(pec,&buc);
        if(!ret){
            BULTOprocborracabeceraylineas(buc.codbulto,0,&bulto);
            if (bulto.ret) {
	 			v10logcomen(LOGERROR,pec->comenpec,"vdcalculovolumetria - ERROR Borrando cabecera y líneas de bulto %s para pedido. %s \n",buc.codbulto,PEClog(pec));
				ret=bulto.ret;
			}
        }
        if (ret) {
            rollbacksavepoint("vdcalculovolumetria");
			v10log(LOGERROR,"vdcalculovolumetria - ERROR Calculando volumetría de bulto %s para pedido. %s \n",buc.codbulto,PEClog(pec));
            return(ret);
        }
    }while(BUCnextbultosdeunpedido(&buc)==SUCCESS);

    if (*chequeabultos !='N' && *chequeabultos !='n'){             
		ret=BULTOselchequeavolumetria(pec->coddiv,pec->anoped,pec->codped,pec->seqped,&bulto);
        if (!ret){
 			v10logcomen(LOGERROR,pec->comenpec,"vdcalculovolumetria - ERROR No se ha generado correctamente la volumetría para el artículo %s. Cantidad a servir no cuadra con cantidad en bultos para pedido. %s \n",bulto.codart,PEClog(pec));
            rollbacksavepoint("vdcalculovolumetria");
            return(FAILURE);
        }
    }
    pec->pesopedido+=pesopedido;
    pec->volumenpedido+=volumenpedido;
    ret=PECactualizavolumenypeso(pec,NOVERIFICA);
	if (ret){
		v10logcomen(LOGERROR,pec->comenpec,"vdcalculovolumetria - ERROR ORACLE %ld Actualizando volumen y peso para pedido. %s \n",ret,PEClog(pec));
        rollbacksavepoint("vdcalculovolumetria");
		return(ret);
	}

    pec->status=staped.status;
    return(ret);
}

// Algoritmo que genera bultos a pedido
// parámetros
// PARAM1: Estructura del pedido al que crear bultos. 
// PARAM2: Flujo para Contenedores. 
// PARAM3: Flujo para Embalajes.
// PARAM4: Flujo para Unidades.
// PARAM5: Dígito EAN de la unidad de envío.
// PARAM6: Estado en el que dejar el pedido si todo ha ido correctamente
VDEXPORT int vdcreabultos(void *ptr,char *param) {
 
	vdpedidocabs *pec=ptr;
	vdbultos bulto;
    vdstatuss sta;
	char flucnt[LTAREA],fluemba[LTAREA],fluprepicking[LTAREA],flupickinv[LTAREA],fluuni[LTAREA];
	char digitoean[2];
	int nbcnt=BULCNT,nbemba=BULEMBA,nbuni=BULUNI;
    int ret;
	
	//Comprobar parámetros recibidos
	ret=numpieces(param,"#");
    if (ret < 7) {
        v10log(LOGERROR,"vdcreabultos: Número de parámetros incorrecto, recibe %d necesita 7\n", ret);
		return(0);
	}
    piece(param,flucnt,"#",1);  
    piece(param,fluemba,"#",2);
	piece(param,fluprepicking,"#",3);
	piece(param,flupickinv,"#",4);
    piece(param,fluuni,"#",5); 
    piece(param,digitoean,"#",6);
    if (ret=damestabreviada("vdcreabultos",param, 7, "#",NULL, "PEC", &sta, 0)) {
		v10logcomen(LOGERROR,pec->comenpec,"vdcreabultos - ERROR Status PEC %s de pedido no existe para algoritmo vdcreabultos \n",sta.dabstatus);
		return(-1);
	}
    BULTOproccreabultos(pec->coddiv,pec->anoped,pec->codped,pec->seqped,flucnt,fluemba,fluprepicking, flupickinv,fluuni,digitoean,0,&bulto);
	if (bulto.ret==-1) 
		return(bulto.ret);
	pec->status=sta.status;
	ret=PECactualizastatus(pec,NOVERIFICA);
	return(0);
}

// graba el comentario en un pedido, de un tipo concreto
static void PECgrabacomentario(procesos *proceso, char *comen,char *tipocomen,vdpedidocabs *pec) {
    
    vdcomens com;
    char msjerror[MAXCADENA]="";

    memset(&com,0,sizeof(com));

    if (*comen) {
        if (*tipocomen==0) v10log(LOGERROR,"%s: NO SE PUEDEN TRATAR COMENTARIOS de la Cabecera de Pedido. %s\n\tNO SE HA INDICADO TIPO\n",proceso->proc.proceso,PEClog(pec));            
        else {
            if (pec->codcomen==0) v10log(LOGERROR,"%s: NO SE PUEDEN TRATAR COMENTARIOS de tipo %s de la cabecera de Pedido. %s\n\tCODCOMEN del pedido es 0\n",proceso->proc.proceso,tipocomen,PEClog(pec));            
            else {
                strcopia(com.comentario,comen,strlen(comen));
                v10comenrelogin("VDPEDIDOCAB",pec->codcomen,tipocomen,0,com.comentario,msjerror);                 
          }
        }
    }    
}

static int buscaversionpedidoage(char *codage) {
	int nage;

	for (nage=0;nage<numagepedido;nage++) {
		if (strcmp(versionpedage[nage].agencia,codage)==0) 
			return(versionpedage[nage].versionpedido);
	}
	
	return(NOFOUND);
}

//la agencia, y conservarage="N" si no encontramos una agencia valida, nos quedamos con la que trae el pedido y no dejamos
//el pedido en error
static int asignagepedmisc(vdpedidocabs *pec,char *conservaragehost) {
	
	int ret;
	vdasiages pedido;
    char codageori[LCODAGE];

	if (!es_blanco(pec->codage) && !strcmp(conservaragehost,"S")) {
		v10log(LOGNORMAL,"asignagepedmisc: Se conserva la agencia existente en el pedido. %s \n",PEClog(pec));
		return SUCCESS;
	}
	ret=ASIAGEseldatospedido(pec->dp,pec->codpais,pec->coddiv,pec->anoped,pec->codped,pec->seqped,&pedido);
	if (ret) {
		v10log(LOGERROR,"asignagepedmisc: No se pueden determinar los datos del pedido. %s \n",PEClog(pec));
		return(ret);
	}
	strcpy(codageori,pec->codage);
    ret=ASIAGEselagepedmisc(pec->coddiv,pec->tipopedido,pec->dp,pedido.zonageo,pec->codcliente,pedido.pesopedido,
			                  pedido.bultospedido,pedido.volpedido,pec->urgencia,pec->prioridad,
							  codageori,pec->codpais,&pedido);
	if (ret || es_blanco(pedido.agepedmisc)) {
		v10log(LOGERROR,"asignagepedmisc: No se encuentra agencia asociada para pedido. \n",PEClog(pec));
		return(FAILURE);
	}
	strcpy(pec->codage,pedido.agearticulo);
	ret=PECactualizacodage(pec,NOVERIFICA);
	if (ret) {
		v10log(LOGERROR,"asignagepedmisc: Error %ld actualizando pedido. %s \n",ret,PEClog(pec));
		return(ret);
	}
	v10log(LOGNORMAL,"asignagepedmisc: Encontrada la agencia %s para pedido. %s \n",pedido.agepedmisc,PEClog(pec));
	return(0);
}


static int asignagencia(vdpedidocabs *pec,char* creaversion,char *conservaragehost,int maxagepedido,long status) {
	int numversion,
		ret;
	char clasifartic[LCODCLASIF]="",
		 clasifasigna[LCODCLASIF]="";
	vdasiages pedido;
	vdpedidolins pel;
	vdartics art;
	vdclaseartics cla;
	vdpedidocabs pecnv;
	vdpedidos ped;
    char codageori[LCODAGE];

	if (!es_blanco(pec->codage) && !strcmp(conservaragehost,"S")) {
		v10log(LOGNORMAL,"asignagencia: Se conserva la agencia existente en el pedido. %s \n",PEClog(pec));
		return SUCCESS;
	}
	// se obtiene número máximo de agencias que se pueden asociar a un pedido,
	// lo que conlleva diferentes versiones de pedido
	// máximo valor permitido - 100
	if (maxagepedido==0) maxagepedido=MAXAGE-1;
	numagepedido=0;
	ret=ASIAGEseldatospedido(pec->dp,pec->codpais,pec->coddiv,pec->anoped,pec->codped,pec->seqped,&pedido);
	if (ret) {
		v10log(LOGERROR,"asignagencia: No se pueden determinar los datos del pedido. %s \n",PEClog(pec));
		return(ret);
	}
	strcpy(codageori,pec->codage);
	// se obtiene primera línea del pedido a tratar
	memset(&pel,0,sizeof(pel));
	ret=PELbuscapedido(pec->coddiv,pec->anoped,pec->codped,pec->seqped,&pel);
	if (ret) {
		v10log(LOGERROR,"asignagencia: No se pueden obtener líneas del pedido. %s \n",PEClog(pec));
		return(ret);
	}

	do {
		// se obtiene artículo para la línea actual del pedido
        memset(&art,0,sizeof(art));
		ret=ARTselcodart(pel.codart,&art);
		if (ret) {
			v10log(LOGERROR,"asignagencia: No se puede obtener artículo de línea %ld del pedido. %s \n",pel.seqlinea,PEClog(pec));
			return(ret);
		}
		v10log(LOGNORMAL,"asignagencia: Tratando artículo %s de pedido. %s \n",pel.codart,PEClog(pec));
		// se obtiene clasificación utilizada para asignar agencias (opcional)
		if (damepropcadena("CLASIFASIGNAGE"))
			strcpy(clasifartic,damepropcadena("CLASIFASIGNAGE"));
		if (es_blanco(clasifartic)) 
			strcpy(clasifartic,"ASIGNAGE");
		memset(&cla,0,sizeof(cla));
		ret=CLAselcodartclasif(art.codart,clasifartic,&cla);
        if (ret) {
			v10log(LOGDEBUG,"asignagencia: Articulo %s no tiene clasificacion. \n",pel.codart);
		}
	    ret=ASIAGEselageartic(pec->coddiv,pec->tipopedido,pec->dp,pedido.zonageo,pec->codcliente,pedido.pesopedido,
			                  pedido.bultospedido,pedido.volpedido,pec->urgencia,pec->prioridad,art.codart,art.coddiv,
							  cla.codclase,codageori/*pec->codage*/,pec->codpais,&pedido);
		if (ret || es_blanco(pedido.agearticulo)) {
			v10log(LOGERROR,"asignagencia: Articulo %s no tiene asociada agencia para pedido. \n",pel.codart,PEClog(pec));
			return(FAILURE);
		}
        // se comprueba si la agencia ha sido tratada con anterioridad
        // obteniendo en ese caso la versión del pedido asociada
        numversion = buscaversionpedidoage(pedido.agearticulo);
        if (numversion==NOFOUND) {
            if (numagepedido == maxagepedido) {
				v10log(LOGERROR,"asignagencia: No se admiten mas versiones de pedido por agencia para pedido. \n",PEClog(pec));
				return(FAILURE);
            }
            strcpy(versionpedage[numagepedido].agencia,pedido.agearticulo);
            if (numagepedido) {
				if (strcmp(creaversion,"S")) {
                      v10log(LOGERROR,"asignagencia: La configuracion no permite crear versión por agencias para el pedido. %s \n",PEClog(pec));
                      return(FAILURE);
				}
				ret=PECselvdpedidocab(pec->coddiv,pec->anoped,pec->codped,pec->seqped,&pecnv);
				if (ret) {
					v10log(LOGERROR,"asignagencia: No se puede obtener pedido. %s \n",PEClog(pec));
					return(ret);
				} else {
					// insertar nueva versión del pedido
					ret = PEDIDOselnuevaversion(pecnv.coddiv,pecnv.anoped,pecnv.codped,&ped);
					if (ret) {
						v10log(LOGERROR,"asignagencia: Error %ld obteniendo nuevo número de versión del pedido. %s \n",ret,PEClog(pec));
						return(ret);
					}
					pecnv.seqped=ped.nuevaversion;
					pecnv.status=status;
					strcpy(pecnv.codage,pedido.agearticulo);
					ret = PECinsert(&pecnv,NOVERIFICA);
					if (ret) {
						v10log(LOGERROR,"asignagencia: Error %ld insertando pedido. %s \n",ret,PEClog(pec));
						return(ret);
					}
					v10log(LOGNORMAL,"asignagencia: Encontrada la agencia %s para pedido. %s \n",pedido.agearticulo,PEClog(pec));
					versionpedage[numagepedido].versionpedido=pecnv.seqped;
                }
			} else {
				// modificar agencia en versión actual del pedido
				strcpy(pec->codage,pedido.agearticulo);
				ret=PECactualizacodage(pec,NOVERIFICA);
				if (ret) {
					v10log(LOGERROR,"asignagencia: Error %ld actualizando pedido. %s \n",ret,PEClog(pec));
					return(ret);
				}
				v10log(LOGNORMAL,"asignagencia: Encontrada la agencia %s para pedido. %s \n",pedido.agearticulo,PEClog(pec));
				versionpedage[numagepedido].versionpedido=pec->seqped;
            }
			numversion=versionpedage[numagepedido].versionpedido;
			numagepedido++;
        }
        if (pel.seqped != numversion) {
			// asociar la línea del pedido con su versión
			pel.seqped=numversion;
			ret=PELactualizaseqped(&pel,NOVERIFICA);
			if (ret) {
				v10log(LOGERROR,"asignagencia: Error %ld actualizando línea %ld del pedido. %s \n",ret,pel.seqlinea,PEClog(pec));
				return(ret);
			}
			v10log(LOGNORMAL,"asignagencia: Actualizada línea %ld a versión %ld de pedido. %s \n",pel.seqlinea,pel.seqped,PEClog(pec));
       }
	} while (PELnextpedido(&pel)==SUCCESS);

	return(0);
}

// Asigna agencia de transporte a un pedido
// PARAM1: (ptr) puntero al pedido
// PARAM2: Estado en el que dejar el pedido si todo ha ido correctamente
// PARAM3: Estado en el que dejar las nuevas versiones de pedido creadas 
VDEXPORT int vdasignagencia(void *ptr,char *param) {
	int ret,maxagepedido;
	char agenciahost[LCODAGE]="",
		 creaversion[LSWITCH],
		 conservaragehost[LSWITCH],
		 maxage[LCADENASMALL];
    vdstatuss stasa,stversion;
    vdpedidocabs *pec=ptr;

	ret=numpieces(param,"#");
    if (ret < 5) {
        v10log(LOGERROR,"vdasignagencia: Número de parámetros incorrecto, recibe %d necesita 5\n", ret);
		return(0);
	}
    if (ret=damestabreviada("vdasignagencia",param, 1, "#", pec, "PEC", &stasa, STPECPDTESERIE)) return(ret);
    if (ret=damestabreviada("vdasignagencia",param, 2, "#", pec, "PEC", &stversion, STPECPDTESERIE)) return(ret);
    piece(param,creaversion,"#",3);
    piece(param,conservaragehost,"#",4);
    piece(param,maxage,"#",5);
	maxagepedido=atoi(maxage);

	if (!es_blanco(pec->codage)) strcpy(agenciahost,pec->codage);
	ret=asignagencia(pec,creaversion,conservaragehost,maxagepedido,stversion.status);
	if (ret==SUCCESS)
		pec->status=stasa.status;
    else {	
		if (!es_blanco(agenciahost)) strcpy(pec->codage,agenciahost);
	}

	return(ret);
}

// Asigna agencia de transporte a un pedido miscelaneo
// PARAM1: (ptr) puntero al pedido
// PARAM2: Estado en el que dejar el pedido si todo ha ido correctamente
VDEXPORT int vdasignagepedmisc(void *ptr,char *param) {
	
	int ret;
	char agenciahost[LCODAGE]="",
		 conservaragehost[LSWITCH];
    vdstatuss stasa;
    vdpedidocabs *pec=ptr;

	ret=numpieces(param,"#");
    if (ret < 2) {
        v10log(LOGERROR,"vdasignagepedmisc: Número de parámetros incorrecto, recibe %d necesita 2\n", ret);
		return(0);
	}
    if (ret=damestabreviada("vdasignagepedmisc",param, 1, "#", pec, "PEC", &stasa, STPECPDTESERIE)) return(ret);
    piece(param,conservaragehost,"#",2);

	if (!es_blanco(pec->codage))
		strcpy(agenciahost,pec->codage);
	ret=asignagepedmisc(pec,conservaragehost);
	if (ret==SUCCESS)
		pec->status=stasa.status;
    else {	
		if (!es_blanco(agenciahost))
			strcpy(pec->codage,agenciahost);
	}
	return(ret);
}

// Crea versión de un pedido, si procede
// PARAM1: (ptr) puntero al pedido
// PARAM2: Estado en el que dejar el pedido si todo ha ido correctamente
VDEXPORT int vdcreaversiones(void *ptr,char *param) {
	int ret;
    vdstatuss stfinpedido;
	vdpedidos ped;
    vdpedidocabs *pec=ptr;

    if (ret=damestabreviada("vdcreaversiones",param, 1, "#", NULL, "PEC", &stfinpedido, STPECFINALIZADO)) return(ret);
    
	ret=PEDIDOproccreaversion(pec->coddiv,pec->anoped,pec->codped,pec->seqped,"",ret,&ped);
    if (ret) {
		v10log(LOGERROR,"vdcreaversiones: Error ejecutando VDPED.CREAVERSION(%s,%ld)\n",pec->codped,stfinpedido.status);
		return(ret);
	}

    if (*ped.comentario) strcpy(pec->comenpec,ped.comentario);
	if (ped.ret==0) pec->status=stfinpedido.status;
    return(ped.ret);
}


// Finaliza un pedido
// PARAM1: (ptr) puntero al pedido
// PARAM2: Estado en el que dejar el pedido si todo ha ido correctamente
// PARAM3: Estado para finalizar la serie de preparación
// PARAM4: Estado para finalizar la serie de expedición
VDEXPORT int vdfinpedido(void *ptr,char *param) {
	int ret;
    vdstatuss stfinpedido,
		      stfinserieprep,
			  stfinserieexp;
	vdpedidos ped;
    vdpedidocabs *pec=ptr;

    if (ret=damestabreviada("vdfinpedido",param, 1, "#", NULL, "PEC", &stfinpedido, STPECFINALIZADO)) return(ret);
    if (ret=damestabreviada("vdfinpedido",param, 2, "#", NULL, "SPR", &stfinserieprep, STSPRFINALIZADA)) return(ret);
    if (ret=damestabreviada("vdfinpedido",param, 3, "#", NULL, "SEX", &stfinserieexp, STSEXFINALIZADA)) return(ret);

	ret=PEDIDOprocfinpedido(pec->coddiv,pec->anoped,pec->codped,pec->seqped,stfinpedido.status,stfinserieprep.status,
		                stfinserieexp.status,ret,&ped);
    if (ret) {
		v10log(LOGERROR,"vdfinpedido: Error ejecutando VDPED.FINPEDIDO(%s,%ld)\n",pec->codped,stfinpedido.status);
		return(ret);
	}

	return(ped.ret);
}

static int paramslanzapedidosstd(vdpedidocabs *pec,
                                 char *param,procesos **proceso,vddemandatipos *demt,
                                 vdstatuss *stdemc,char *codubiexped,char *agrupalinea,
                                 char *tipocomendemanda) {
    int ret=0;
    char procesoreserva[LPROCESO]="";

    if ((ret=piece(param,procesoreserva,"#",1))<0) {
        v10log(LOGERROR,"lanzapedidosstd: no se ha informado proceso de reserva para pedido. %s\n",PEClog(pec));
        return(ret);
    }

      // busca el proceso de reserva
    *proceso=buscaproceso(procesoreserva);
    if (*proceso==NULL || (*proceso)->fnproceso==NULL){
        v10log(LOGERROR,"lanzapedidosstd: NO EXISTE FUNCION O PROCESO %s que realice la reserva del pedido %s.\n",procesoreserva,PEClog(pec));
        return(ret);
    }


    memset(demt,0,sizeof(vddemandatipos));
    if ((ret=piece(param,demt->tipodemanda,"#",2)) < 0) {
        v10log(LOGERROR,"lanzarecargasstd: no se ha informado tipo de demanda para reserva del pedido %s.\n",PEClog(pec));        
        return(ret);
    }

    if (ret=DEMTselvddemandatipo(demt->tipodemanda, demt)) {
        v10log(LOGERROR,"paramslanzarecargasstd: No existe tipo de demanda %s\n",demt->tipodemanda);
        return(ret);
    }
    
    
    if (ret=damestabreviada("lanzapedidosstd:",param, 3, "#",NULL, "DEL", stdemc, STDECPDTERESERV)) return(ret);
    piece(param,codubiexped,"#",4); 
    if (piece(param,agrupalinea,"#",5)<0) *agrupalinea='S';  
  
    // se guarda el tipo de comentarios que se va a guardar en la demanda
    piece(param,tipocomendemanda,"#",7);    
    return(ret);  
}


// mueve los comentarios de las líneas de  demanda a las líneas de pedido, del tipo especificado
static void muevecomenDEML2PEL(vdpedidocabs *pec, char *listacodcomen, char *tipocomen) {
    vdplsqlcomens plsqlcomen;
    PLSQLCOMENprocmuevecomendeml2pel(pec->coddiv,pec->anoped,pec->codped,pec->seqped,listacodcomen,tipocomen,&plsqlcomen);
}


// borra los comentarios de este tipo, de las líneas del pedido pasado
static void borracomenPEL(vdpedidocabs *pec,char *tipocomen) {    
    int ret;
    vdpedidolins pel;
 
    ret=PELbuscapedido(pec->coddiv,pec->anoped,pec->codped,pec->seqped,&pel);
    while (ret==0) {
        v10deletecomenportipo(pel.codcomen, tipocomen, NULL);
        ret=PELnextpedido(&pel);
    }
}


// ALGORITMO. Recoge los parámetros, genera la demanda y lanza el proceso de reserva en memoria
// PARAM 1: Proceso que realiza la reserva
// PARAM 2: Tipo de demanda del pedido
// PARAM 3: Estado con el que se crea la cabecera de Demanda
// PARAM 4: Ubicación forzada de destino de las líneas de demanda
// PARAM 5: Si se agrupan las líneas por articulo, dentro del mismo pedidohost.

// Parámetros para pasarle al proceso que ejecuta en memoria para reservar la demanda al completo
// PARAM 6: evaluar todas las lineas de la demanda
// PARAM 7: tipo de comentario, de la cabecera de demanda y cabecera de pedido
// PARAM 8: código de clasif. para montar con la clase del artículo el discriminante 

VDEXPORT int vdlanzapedidosstd(void *ptr,char *param) {
    int ret,i,numparams;
    char codubiexped[LCODUBI]="",agrupalinea[2]="";
    char procesoreserva[LPROCESO]="",tipodemanda[LTIPODEMANDA]="",tipocomendemanda[LTIPOCOMEN]="";
    char parami[MAXCADENA]="";
    procesos *proceso;
    vdstatuss stdemc;
    vdpedidocabs *pec=ptr;
    vddemandatipos demt;
    vddemandacabs demc;     
    
    savepoint("lanzapedidosstd");

    // carga los parámetros del algoritmo
    if (ret=paramslanzapedidosstd(pec,param,&proceso,&demt,&stdemc,codubiexped,agrupalinea,tipocomendemanda)) return(ret);  
    
    memset(&demc,0,sizeof(demc));
    if (ret=creademandapedido(pec,demt.tipodemanda,stdemc.status,codubiexped,"T"/*pec->backorder*/,agrupalinea,demc.coddemanda)) {
        rollbacksavepoint("lanzapedidosstd");   
        v10log(LOGERROR,"lanzapedidosstd: Error al generar la demanda de tipo %s para pedido. %s\n",demt.tipodemanda,PEClog(pec));
        return(ret);
    }
    strcpy(demc.tipodemanda,demt.tipodemanda);
    
   
    // forma los parámetros a pasarle al proceso de reserva
   	numparams=numpieces(param,"#");    
    sprintf(proceso->proc.param,"%s#%s#%c\0",demc.coddemanda,demc.tipodemanda,'N');
    // primer parámetro de proceso empieza en la posición 6
    for (i=6;i<=numparams;i++) {
        piece(param,parami,"#",i);
        sprintf(proceso->proc.param+strlen(proceso->proc.param),"#%s\0",parami);
    }
    
    // ejecuta la tarea de reserva
    (proceso->fnproceso)(proceso);
    
    // busca la demanda que se ha intentado reservar
    if ((ret=DEMCselvddemandacab(demc.tipodemanda,demc.coddemanda,&demc))) {
        rollbacksavepoint("lanzapedidosstd");      
        v10log(LOGERROR,"lanzapedidosstd: Demanda %s no existe despues de ejecutar proceso de reserva %s\n",
            DEMClog(&demc), procesoreserva);
        return(ret);
    }
    
    if (demc.status!=STDECRESERVADA) {
        vddems demaux;
        // pasar pedidos de las líneas de demandas a las de pedidos
        memset(&demaux,0,sizeof(demaux));
        DEMbuscalistacodcomen(demc.coddemanda,demc.tipodemanda,&demaux);       
        rollbacksavepoint("lanzapedidosstd");  
        borracomenPEL(pec,tipocomendemanda);
        muevecomenDEML2PEL(pec, demaux.vdextra,tipocomendemanda);      
        *pec->coddemanda=0;
        *pec->tipodemanda=0;
        pec->status=STPECPDTESTOCK;   
        v10log(LOGNORMAL,"vdlanzapedidosstd: pedido %s pasa a estado %ld\n",PEClog(pec),STPECPDTESTOCK);
    }else {
        borracomenPEL(pec,tipocomendemanda);     
        strcpy(pec->coddemanda,demc.coddemanda);
        strcpy(pec->tipodemanda,demc.tipodemanda);
        pec->status=STPECRESERVADO;   
        v10log(LOGNORMAL,"vdlanzapedidosstd: pedido %s pasa a estado %ld\n",PEClog(pec),STPECRESERVADO);

        // me falta actualizar fecreserva en el pedido, ya no es fecaper, es la nueva

        pec->fecreserva=getdate();
        cent2a(gettime(),0,':',pec->horareserva);
        ret=PECactualizareserva(pec,NOVERIFICA);
        if (ret) {
            rollbacksavepoint("lanzapedidosstd");
            v10log(LOGERROR,"lanzapedidosstd: Error al actualizar fechay hora de la reserva del pedido. %s\n",PEClog(pec));
            return(ret);
        }
    }
    
    ret=PECactualizastatusydemanda(pec,NOVERIFICA);
    if (ret) {
        rollbacksavepoint("lanzapedidosstd");
        v10log(LOGERROR,"lanzapedidosstd: Error al actualizar estado del pedido. %s\n",PEClog(pec));
    }
    return(ret);
}



static int ejecutaalgoritmos(procesos *proceso,vdpedidocabs *pec) {
    
    int ret;
    vdseriepreps spr;
	vdagencias ag;
    
	memset(&ag,0,sizeof(ag));
	memset(&spr,0,sizeof(spr));
	AGselcodage(pec->codage,&ag);
    SPRselvdserieprep(pec->codserieprep,&spr);
	ret=VDEXECejecuta(proceso,pec,"#","%s#%s#%s#%s#%s#%s#%s#%s#%s",pec->tipopedido,pec->coddiv,pec->codage,ag.grupoage,pec->codareaexped,spr.swtpickinginv,pec->backorder,spr.swtpickingagr,pec->swtmiscelaneo);  
    return(ret);   
}


// PROCESO. Busca pedidos en un estado ordenados por prioridad, para ejecutar un algoritmo
// 1:   estado de los pedidos
// 2:   tipo de comentario del pedido
// 3:   resetear los comentarios del tipo para este pedido
VDEXPORT void vdbuscapedstprio(procesos *proceso) {
    int ret;
    char msjerror[MAXCADENA]="",borracomentarios[2]="";    
    char tipocomen[LTIPOCOMEN]="";
    vdstatuss sta;
    vdpedidocabs pec; 
    vdpedidos ped;

    if (ret=damestabreviada("vdbuscapedstprio",proceso->proc.param, 1, "#", NULL, "PEC", &sta, 0)) return;
    if (PEDIDObuscastatusprio(sta.status,&ped)) return;
    
    ret=numpieces(proceso->proc.param,"#");
    piece(proceso->proc.param,tipocomen,"#",2);   
    if ((ret=piece(proceso->proc.param,borracomentarios,"#",3)) < 0) *borracomentarios='N';

    do { 

        PECselvdpedidocab(ped.coddiv,ped.anoped,ped.codped,ped.seqped,&pec);

        savepoint("vdbuscapedstprio");

        if (ret=PEClock(&pec,NOWAIT,VALIDA,"STATUS",NULL)){
            v10log(LOGERROR,"vdbuscapedstprio: Error bloqueando cabecera de pedidos. %s\n\t%s\n",PEClog(&pec),
                ret==VD_EERRBLOQUEO ? "El campo status ha sido modificado por otro proceso":"Error Oracle bloqueando campo status" );
            rollbacksavepoint("vdbuscapedstprio");        
            continue;
        }      
         
        *pec.comenpec=0;
        v10log(LOGNORMAL,"vdbuscapedstprio: Procesando cabecera de pedido. %s\n",PEClog(&pec));
        ret=ejecutaalgoritmos(proceso,&pec);        
        if (ret) {
            rollbacksavepoint("vdbuscapedstprio");
            pec.status=-pec.status;
            ret=PECactualizastatus(&pec,0);
            if (ret) {
                 rollback();
                 v10log(LOGERROR,"vdbuscapedstprio: error %ld actualizado a estado %ld pedido. %s \n",ret,pec.status,PEClog(&pec));               
             }  
            v10log(LOGERROR,"vdbuscapedstprio: ERROR %ld procesando pedido. %s \n",ret,PEClog(&pec));                             
        }

        if (*pec.comenpec) {
            if (*borracomentarios=='S') v10deletecomenportipo(pec.codcomen, tipocomen, NULL);       
            PECgrabacomentario(proceso, pec.comenpec,tipocomen,&pec);
        }
        commit();
    }while (PEDIDOnextstatusprio(&ped)==0);
}

// Proceso que busca pedidos en un estado concreto y llama al algoritmo que corresponda
// parámetros
// PARAM1: estado de los pedidos
// PARAM2: tipo de comentario
// PARAM3: resetear los comentarios del tipo para este pedido
VDEXPORT void vdbuscapedst(procesos *proceso) {
    int ret;
    char msjerror[MAXCADENA]="",borracomentarios[LSWITCH]="";    
    vdpedidocabs pec;
    char tipocomen[LTIPOCOMEN]=""; 
    vdstatuss sta;
    
    if (ret=damestabreviada("vdbuscapedst",proceso->proc.param, 1, "#", NULL, "PEC", &sta, 0)) return;
    if (PECbuscastatus(sta.status,&pec)) return;
    
    ret=numpieces(proceso->proc.param,"#");
    piece(proceso->proc.param,tipocomen,"#",2);   
    if ((ret=piece(proceso->proc.param,borracomentarios,"#",3)) < 0) *borracomentarios='N';

    do { 

        savepoint("vdbuscapedst");

        if (ret=PEClock(&pec,NOWAIT,VALIDA,"STATUS",NULL)){
            v10log(LOGERROR,"vdbuscapedst: Error bloqueando cabecera de pedidos. %s\n\t%s\n",PEClog(&pec),
                ret==VD_EERRBLOQUEO ? "El campo status ha sido modificado por otro proceso":"Error Oracle bloqueando campo status" );
            rollbacksavepoint("vdbuscapedst");        
            continue;
        }      
         
        *pec.comenpec=0;
        v10log(LOGNORMAL,"vdbuscapedst: Procesando cabecera de pedido. %s\n",PEClog(&pec));
        ret=ejecutaalgoritmos(proceso,&pec);        
        if (ret) {
            rollbacksavepoint("vdbuscapedst");
            pec.status=-pec.status;
            ret=PECactualizastatus(&pec,0);
            if (ret) {
                 rollback();
                 v10log(LOGERROR,"vdbuscapedst: error %ld actualizado a estado %ld pedido. %s \n",ret,pec.status,PEClog(&pec));               
            }  
            v10log(LOGERROR,"vdbuscapedst: ERROR %ld procesando pedido. %s \n",ret,PEClog(&pec));                             
        }
 
        // siempre guarda el comentario
        if (*pec.comenpec) {
            if (*borracomentarios=='S') v10deletecomenportipo(pec.codcomen, tipocomen, NULL);       
            PECgrabacomentario(proceso, pec.comenpec,tipocomen,&pec);
        }
 
        commit();
    }while (PECnextstatus(&pec)==SUCCESS);
}


// Proceso que procesa pedidos en un estado concreto y llama al algoritmo que corresponda
// parámetros
// PARAM1: estado de los pedidos
// PARAM2: tipo de comentario
// PARAM3: resetear los comentarios del tipo para este pedido
// PARAM4: semáforo, se comprueba en el vdexec
VDEXPORT void vdprocesapedst(procesos *proceso) {
    int ret;
    char msjerror[MAXCADENA]="",borracomentarios[LSWITCH]="";    
    vdpedidocabs pec;
    char tipocomen[LTIPOCOMEN]=""; 
    vdstatuss sta;
    
    if (ret=damestabreviada("vdprocesapedst",proceso->proc.param, 1, "#", NULL, "PEC", &sta, 0)) return;
    if (PECbuscastatus(sta.status,&pec)) return;
    
    ret=numpieces(proceso->proc.param,"#");
    piece(proceso->proc.param,tipocomen,"#",2);   
    if ((ret=piece(proceso->proc.param,borracomentarios,"#",3)) < 0) *borracomentarios='N';

    do { 
        savepoint("vdprocesapedst");
        if (ret=PEClock(&pec,NOWAIT,VALIDA,"STATUS",NULL)){
            v10log(LOGERROR,"vdprocesapedst:Error bloqueando cabecera de pedido. %s\n\t%s\n",PEClog(&pec),
                   ret==VD_EERRBLOQUEO ? "El campo status ha sido modificado por otro proceso":"Error Oracle bloqueando campo status" );
            rollbacksavepoint("vdprocesapedst");        
            continue;
        }      
        *pec.comenpec=0;
        v10log(LOGNORMAL,"vdprocesapedst: Procesando cabecera de pedido. %s\n",PEClog(&pec));

        ret=ejecutaalgoritmos(proceso,&pec);
        if (ret) {
            rollbacksavepoint("vdprocesapedst");
            pec.status=-pec.status;
            v10log(LOGERROR,"vdprocesapedst: ERROR %ld procesando pedido. %s \n",ret,PEClog(&pec));                    
        }
        ret=PECactualizastatus(&pec,0);
        if (ret) {
            rollback();
            v10log(LOGERROR,"vdprocesapedst: ERROR %ld actualizando a estado %ld pedido. %s \n",ret,pec.status,PEClog(&pec));
        }               

        if (*pec.comenpec) {
            if (*borracomentarios=='S') v10deletecomenportipo(pec.codcomen, tipocomen, NULL);
            PECgrabacomentario(proceso, pec.comenpec,tipocomen,&pec);
        }

        commit();
    }while (PECnextstatus(&pec)==SUCCESS);
}
