/*
* Módulo : V10VIRTSEL.C
* Objeto:  Tratamiento de paginacion virtual
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"


static void flechaspagina(virtsels *s)
{
  int tinta,papel;
  if (s->marco==0) {
     tinta=s->v1->t.t[CMARCOR].tinta;
     papel=s->v1->t.t[CMARCOR].papel;
  } else {
     tinta=s->v1->t.t[CMARCON].tinta;
     papel=s->v1->t.t[CMARCON].papel;
  }
  if (s->modo>1) return;
  if (s->plin>0) wplot(s->v1->hwnd,s->v1->x2+1,s->v1->y1,'\x1E',tinta,papel);
  else wplot(s->v1->hwnd,s->v1->x2+1,s->v1->y1,pasaoemchar(v10marco[BARRAVER][s->marco]),tinta,papel);

  if (s->pcol>0) wplot(s->v1->hwnd,s->v1->x1,s->v1->y2+1,'\x11',tinta,papel);
  else wplot(s->v1->hwnd,s->v1->x1,s->v1->y2+1,pasaoemchar(v10marco[BARRAHOR][s->marco]),tinta,papel);

  if (s->ulin==(s->numlin)-1) wplot(s->v1->hwnd,s->v1->x2+1,s->v1->y2,pasaoemchar(v10marco[BARRAVER][s->marco]),tinta,papel);
  else
    if (s->sobran && (s->ulin==(s->numlin)-2) && (s->ccol>(s->sobran)-1)) wplot(s->v1->hwnd,s->v1->x2+1,s->v1->y2,pasaoemchar(v10marco[BARRAVER][s->marco]),tinta,papel);
    else wplot(s->v1->hwnd,s->v1->x2+1,s->v1->y2,'\x1F',tinta,papel);

  if (s->ucol==(s->numcol)-1) wplot(s->v1->hwnd,s->v1->x2,s->v1->y2+1,pasaoemchar(v10marco[BARRAHOR][s->marco]),tinta,papel);
  else
    if (s->sobran && (s->clin==(s->numlin)-1) && (s->ucol>=(s->sobran)-1)) wplot(s->v1->hwnd,s->v1->x2,s->v1->y2+1,pasaoemchar(v10marco[BARRAHOR][s->marco]),tinta,papel);
    else wplot(s->v1->hwnd,s->v1->x2,s->v1->y2+1,'\x10',tinta,papel);
}


static void presenta(virtsels *s)
{
   s->v.cursorx = (s->ccol - s->pcol) * s->colreg;
   s->v.cursory = (s->clin - s->plin) * s->linreg;
   pon_curf(&s->v);
}


void poncursorsel(virtsels *s)
{
  if (VIRTPOS(s) > s->numero - 1) return;
  presenta(s);
  if (s->pinta) (*s->pinta)(s,1);
  presenta(s);
}


static void quitacursor(virtsels *s)
{
  if (VIRTPOS(s) > s->numero - 1) return;
  presenta(s);
  if (s->pinta) (*s->pinta)(s,0);
}


static void representacolumna(virtsels *s)
{
  int j = 1;
  int auxlin = s->clin;
  s->clin=s->plin;
  while ((j<=s->lppag) && (s->clin<s->numlin) && (VIRTPOS(s)<=s->numero)) {
    quitacursor(s);
    s->clin++;
    j++;
  }
  s->clin=auxlin;
}


static void representalinea(virtsels *s)
{
  int j = 1;
  int auxcol = s->ccol;

  s->ccol=s->pcol;
  while ((j<=s->cppag) && (s->ccol<s->numcol) && (VIRTPOS(s)<s->numero)) {
    quitacursor(s);
    s->ccol++;
    j++;
  }
  s->ccol=auxcol;
}

void repintapagina(virtsels *s)
{
  int i = 1;
  int auxlin = s->clin;

  s->v.cursorx=s->v.cursory=0;
  s->clin=s->plin;

  while((i<=s->lppag) && (s->clin<s->numlin)) {
	  if (v10versionweb) {
		//s->ulin=s->clin;
		pintapaginabloque(s,0);
	} else
		representalinea(s);
	s->clin++;
    i++;
  }
  s->ulin=s->clin-1;
  if (auxlin>s->ulin) s->clin=s->ulin;
  else s->clin=auxlin;
  if (VIRTPOS(s)>s->numero) {
    if (s->clin>s->plin) s->clin--;
    else s->ccol--;
  }
  if (!v10versionweb) {
	  if (s->numcol>1 || s->lppag>1) quitacursor(s);
	  flechaspagina(s);
  } else
	  pintapaginabloque(s,0);
}

static int sigpag(virtsels *s)
{
  int aux;
  int ret = 0;

  if (s->ulin < s->numlin-1) {
    aux=s->clin-s->plin;
    s->plin=s->ulin+1;
    s->clin=s->ulin;
    s->clin=aux+s->plin;
    if (s->clin>s->numlin) s->clin=s->numlin;
    if (!v10versionweb) representapagina(s);
    ret=-1;
  }
  return(ret);
}


static int antpag(virtsels *s)
{
  int i = s->lppag;
  int ret = 0;
  if (s->plin) {
    if (i>s->plin) {
      i=s->plin;
      s->plin=0;
    }
    else s->plin-=i;
    if (s->plin+s->lppag <= s->ulin)
      s->ulin=s->plin+s->lppag-1;
    s->clin=s->clin-i;
    if (s->clin>s->ulin)
      s->clin=s->ulin;
    if (!v10versionweb) representapagina(s);
    ret=-1;
  }
  return(ret);
}


static void siglin(virtsels *s)
{
  if (VIRTPOS(s)+s->numcol>=s->numero) return;
  if (s->clin<s->numlin-1) {
    if (!v10versionweb) quitacursor(s);
    if (s->clin>=s->ulin) {
      if (s->ulin<s->numlin-1) {
		if (!v10versionweb) {
		  windows w;
		  winitvt(s->v1->hwnd,&w,s->v1->x1,s->v.y1,s->v1->x2,s->v.y2,&s->v.t);
		  scrollv(&w,s->linreg);
		}
        s->ulin++;
        s->plin++;
        s->clin++;
        if (!v10versionweb) representalinea(s);
      }
    }
    else s->clin++;
  }
  if (!v10versionweb) quitacursor(s);
}


static void antlin(virtsels *s)
{
  if (s->clin) {
    if (!v10versionweb) quitacursor(s);
    if (s->clin<=s->plin) {
      if (s->plin>0) {
		if (!v10versionweb) {
			windows w;
			winitvt(s->v1->hwnd,&w,s->v1->x1,s->v.y1,s->v1->x2,s->v.y2,&s->v.t);
			scrollv(&w,-s->linreg);
		}
        s->plin--;
        if (s->plin+s->lppag<=s->ulin)
          s->ulin--;
		s->clin--;
        if (!v10versionweb) representalinea(s);
      }
    }
    else {
      s->clin--;
    }
  }
  if (!v10versionweb) quitacursor(s);
}


static void sigcol(virtsels *s)
{
  if (VIRTPOS(s)>=s->numero-1) return;
  quitacursor(s);
  if (s->ccol<s->numcol-1) {
    if (s->ccol>=s->pcol+s->cppag-1) {
      if (s->pcol+s->cppag<s->numcol) {
        windows w;
        winitvt(s->v.hwnd,&w,s->v.x1,s->v1->y1,s->v.x2,s->v1->y2,&s->v.t);
        scrollh(&w,s->colreg);
        s->pcol++;
        s->ccol++;
        s->ucol++;
        representacolumna(s);
      }
    }
    else s->ccol++;
  }
  else {
    s->ccol=0;
    if (s->ccol<s->pcol) {
      s->pcol=0;
      s->ucol=s->pcol+s->cppag-1;
      representapagina(s);
    }
    siglin(s);
  }
  quitacursor(s);
}


static void antcol(virtsels *s)
{
  if (VIRTPOS(s)==0) return;
  quitacursor(s);
  if (s->ccol) {
    if (s->ccol<=s->pcol) {
      if (s->pcol>0) {
        windows w;
        winitvt(s->v.hwnd,&w,s->v.x1,s->v1->y1,s->v.x2,s->v1->y2,&s->v.t);
        scrollh(&w,-s->colreg);
        s->pcol--;
        s->ccol--;
        s->ucol--;
        representacolumna(s);
      }
    }
    else s->ccol--;
  }
  else {
    s->ccol=s->numcol-1;
    s->ucol=s->numcol-1;
    if (s->ccol>=s->pcol+s->cppag) {
      s->pcol=s->ccol-s->cppag+1;
      representapagina(s);
    }
    antlin(s);
  }
  quitacursor(s);
}

void representapagina(virtsels *s)
{
  if (!v10versionweb) clv(&s->v);
  repintapagina(s);
}

int enrango(int x,int x1,int x2)
{
  if (x<x1 || x>x2) return(0);
  return(1);
}

int STDreposicionaraton(virtsels *s)
{
  int nx;
  if (!enrango(mousepos.posx,s->v1->x1-1,s->v1->x2+1) || !enrango(mousepos.posy,s->v1->y1-1,s->v1->y2+1)) {
     s->salir=1;
     return(0);
   }
  if (mousepos.posx==s->v1->x2+1 && mousepos.posy==s->v1->y1) {
     antlin(s);
     return(1);
   }
  if (mousepos.posx==s->v1->x2+1 && mousepos.posy==s->v1->y2) {
     siglin(s);
     return(1);
   }
  if (!enrango(mousepos.posx,s->v.x1,s->v.x2) || !enrango(mousepos.posy,s->v.y1,s->v.y2)) {
     return(0);
   }
  nx=(mousepos.posy-s->v.y1)/s->linreg+s->plin;
  if (nx>s->ulin) nx=s->ulin;
  if (nx!=s->clin) {
     reposiciona(s,nx);
  	 // ENCOLATECLA ??
     if (mousepos.action==CLICK) pushtecla(MOUSEPOS);
   }
  if (mousepos.action==DOBLECLICK) pushtecla(cr);
  return(1);
}


int reselecciona(virtsels *s,int (*fprocesaposttecla)(int))
{
  int ch=0;

  s->salir=0;
  while (!s->salir) {
	if (!v10versionweb) {
		poncursorsel(s);
		flechaspagina(s);
	} else {
		representapagina(s);
	}
    if (s->tecla) ch=(*s->tecla)(s);
    else ch=tecla();
    if (ch!=0) {
      switch (ch) {
        case cuu:  antlin(s);
                   break;
        case cua:  siglin(s);
                   break;
        case cui:  if (v10versionweb) break;
				   if (s->numcol>1) antcol(s);
                   else s->salir=-1;
                   break;
        case cud:  if (v10versionweb) break;
				   if (s->numcol>1) sigcol(s);
                   else s->salir=-1;
                   break;
        case pgup: antpag(s);
		   break;
        case pgdn: sigpag(s);
                   break;
        case home: if (v10versionweb) break;
				   quitacursor(s);
                   s->clin=s->plin;
                   break;
        case end:  if (v10versionweb) break;
				   quitacursor(s);
                   s->clin=s->ulin;
                   break;
        case MOUSEPOS:
					  if (!v10versionweb)
						reposicionaraton(s);
					  else
                        s->salir=reposicionaraton(s);
                      break;
        default:   if (ESFUNC(ch)) {
                     s->salir=-1;
                     break;
                   }
                   switch(ch) {
                     case esc:
                     case tab:
                     case cr: s->salir=-1;
                              break;
                   }
      }
    }
	if (!s->salir && fprocesaposttecla) ch=fprocesaposttecla(ch);
  }
  return((v10versionweb)?ch:VIRTPOS(s));
}


int STDllselecciona(virtsels *s)
{
  tpixels *copia=NULL;

  if (s->hayinput)
    switch (s->modo) {
      case 0:  copia=salvavd(s->v1);
               enmarca(s->v1,s->marco,s->titulo);
               break;
      case 1:  renmarca(s->v1,s->marco,s->titulo);
               break;
    }
  if (sigpag(s)) {
    if (!s->hayinput) {
      flechaspagina(s);
      return(0);
    }
    reselecciona(s,NULL);
  }
  switch (s->modo) {
    case 0: recuperavd(s->v1,copia);
            break;
    case 1: renmarca(s->v1,1,s->titulo);
            break;
  }
  return(VIRTPOS(s));
}



void reposiciona(virtsels *s,int elemento)
    /* Presenta la p gina en la que est  el elemento elemento. */
{
  int representa;
  if (!v10versionweb) quitacursor(s);
  s->clin=elemento/s->numcol;
  s->ccol=elemento%s->numcol;
  representa=0;

  if (s->clin>=s->plin+s->lppag) {
    s->plin=s->clin-s->lppag/2+1;
    s->ulin=s->plin-1;
    representa=1;
  }
  if (s->clin<s->plin) {
    s->plin=s->clin;
    s->ulin=s->plin-1;
    representa=1;
  }

  if (s->ccol>=s->pcol+s->cppag) {
    s->pcol=s->ccol-s->cppag+1;
    representa=1;
  }
  if (s->ccol<s->pcol) {
    s->pcol=s->ccol;
    representa=1;
  }
  if (representa) sigpag(s);
  else if (!v10versionweb) quitacursor(s);
}


void initselec(virtsels *s,int miz,int msup,int mder,int minf,int modo,windows *v_user,int numero,int linreg,int col,int ancho,char *titulo,void *pinta,void *tecla,int princ,void *dato)
{
  int x1,y1,x2,y2;

  x1=v_user->x1+miz;
  y1=v_user->y1+msup;
  x2=v_user->x2-mder;
  y2=v_user->y2-minf;
  s->lppag=(y2-y1+1)/linreg;
  y2=y1+s->lppag*linreg-1;
  s->cppag=(x2-x1+1)/ancho;
  if (s->cppag==0) {
     s->cppag=1;
     ancho=x2-x1+1;
   }
  x2=x1+s->cppag*ancho-1;
  winitvt(v_user->hwnd,&s->v,x1,y1,x2,y2,&v_user->t);

  s->v1=v_user;
  s->modo=modo;
  s->titulo=titulo;
  s->pinta=(void (*)(void *,short))pinta;
  s->tecla=(int (*)(void *))tecla;
  s->dato=dato;

  s->numero=numero;

  s->numlin = (numero+col-1)/col;
  s->linreg = linreg;

  s->clin = princ / col;
  if (s->clin >= s->lppag) s->plin=s->clin-s->lppag+1;
  else s->plin = 0;
  s->ulin = s->plin - 1;

  s->numcol = col;
  s->colreg = ancho;
  if (s->cppag>s->numcol) s->cppag=s->numcol;

  s->ccol = princ % col;
  if (s->ccol >= s->cppag) s->pcol=s->ccol-s->cppag+1;
  else s->pcol=0;
  s->ucol=s->pcol+s->cppag-1;
  s->sobran=(numero%col);
  s->marco=0;
}


int selecciona(int miz,int msup,int mder,int minf,int modo,windows *v_user,int numero,int linreg,int col,int ancho,char *titulo,void *pinta,void *tecla,int princ,void *dato)
{
  int aux;
  int cursorx,cursory;
  virtsels s; 

  curr_cursor(&cursorx,&cursory);
  initselec(&s,miz,msup,mder,minf,modo,v_user,numero,linreg,col,ancho,titulo,pinta,tecla,princ,dato);
  s.hayinput=1;
  aux=llselecciona(&s);
  fgotoxy(cursorx,cursory);
  return(aux);
}


int presseleccion(int miz,int msup,int mder,int minf,int modo,windows *v_user,int numero,int linreg,int col,int ancho,char *titulo,void *pinta,void *tecla,int princ,void *dato)
{
  int aux;
  int cursorx,cursory;
  virtsels s;

  curr_cursor(&cursorx,&cursory);
  initselec(&s,miz,msup,mder,minf,modo,v_user,numero,linreg,col,ancho,titulo,pinta,tecla,princ,dato);
  s.hayinput=0;
  aux=llselecciona(&s);
  fgotoxy(cursorx,cursory);
  return(aux);
}
