/*
* Módulo : V10FORDIALOG.C
* Objeto:  Tratamiento de dialogos en formularios
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10wwwform.h"
int(*psemueveelraton)(bloques *b);

#define PONVALORIND(b,c,var,ind) (var=((*indicadorcampo(b,c,ind)==-1||c->virtual)?var:*indicadorcampo(b,c,ind)))
void recargadefectos(bloques *b,fcampos *c)
{
    if (b->enterquery) return;
	PONVALORIND(b,c,c->noupdate,CINDNOUPDATE);
	if (c->v) {
		if (c->tipo==V10DOUBLE || c->tipo==V10FLOAT) PONVALORIND(b,c,c->v->dec,CINDDEC);
		PONVALORIND(b,c,c->v->formato,CINDFORMATO);
//	    PONVALORIND(b,c,c->v->lpan,CINDLPAN);
		PONVALORIND(b,c,c->v->enter,CINDENTER);
		PONVALORIND(b,c,c->v->noinput,CINDNOINPUT);
		PONVALORIND(b,c,c->v->invisible,CINDINVISIBLE);
		PONVALORIND(b,c,c->v->autoenter,CINDAUTOENTER);
		c->v->color=*indicadorcampo(b,c,CINDCOLOR);
	}
}

void llactualizabloque(bloques *b)
{
  if (!b->invisible) { 
	 int ncamp;
	 for (ncamp=0;ncamp<b->ncamp ;ncamp++) recargadefectos(b,b->c+ncamp);
     if (b->fprepinta) ejecutaftriger(b,PPREPINTA,b->fprepinta,NULL);
     actualizadialog(&b->vi);   
     if (b->fpostpinta) ejecutaftriger(b,PPOSTPINTA,b->fpostpinta,NULL);
   }
}

void STDactualizabloque(bloques *b)
{
	llactualizabloque(b);
}

int procesateclacampo(bloques *b,fcampos *c,int ret)
{
    int nt;
    for (nt=0;nt<c->nteclas;nt++) {
        if (c->teclas[nt].t==ret) {
            if (c->teclas[nt].trig->fun)
                ret=c->teclas[nt].trig->fun(b,c->teclas[nt].trig);
            else                      ret=0;
            return(ret);
        }
    }
    if (ret==CS_F(10) && b->contextual==NULL) ret=S_F(10);
    if (ret==S_F(10)) {
        if (c->contextual) {
            ret=ejecutaftriger(b,PCONTEXTUAL,c->contextual,c);
        }            
    }
    if (ret==MOUSEPOS) {        
        if (mousepos.action==DOBLECLICK) if (c->feventos.ondbclick) ejecutaftriger(b,DOBLECLICK,c->feventos.ondbclick,c);
        if (mousepos.action==CLICK) if (c->feventos.onclick) ejecutaftriger(b,DOBLECLICK,c->feventos.onclick,c);
    }
    return(ret);
}

void preparaenter(bloques *b)
{
  v10inputs *v;
  for (v=b->vi.prim;v<=b->vi.ult;v++) {
      fcampos *c=v->trigerdatos;
	  if (b->enterquery) {
	     if (c->tabla || c->where) v->enter=1;
	        else                   v->enter=0;		
         v->noinput=0;
      } else {
         if (c->noupdate || (b->noupdate && c->tabla)) {
            if (CABECERA(b)->antiguo) v->enter=0;
               else                   v->enter=c->enter;
         } else {
             v->enter=c->enter; 
		     PONVALORIND(b,c,c->v->enter,CINDENTER);
         }
         v->noinput = c->noinput;
         PONVALORIND(b, c, c->v->noinput, CINDNOINPUT);
      }
   }
}

int enterq(bloques *b)
{
  if (b->noquery) return(0);
  if (b->enterquery==1) {
     preparaenter(b);
     memcpy(b->buffer,b->bufuquery,(unsigned)b->tamano);
     actualizabloque(b);
     return(0);
   }
  b->enterquery=ENTERQ;
  preparaenter(b);
  borrabloque(b,NULL);
  if (!entrablebloque(b)) {
      b->enterquery=0;
      preparaenter(b);
  }
  return(0);
}

static int abortaquery(bloques *b, ftrigers *ft)
{
  if (v10versionweb) b->modif=0;
  FORM(b)->nivel=NIVEL_BLOQUE;
  b->enterquery=0;
  preparaenter(b);
  borrabloque(b,ft);
  return(0);
}

int finputcampo(bloques *b)
{
  int ret=0,pulsada=0;
  void *copia=NULL;
  int modif,postret=0,ejepostret=0;
  /*actualizabloque(b);*/
  if (!v10versionweb) actualizabloque(b);
  FORM(b)->nivel=NIVEL_CAMPO;
  while (FORM(b)->nivel == NIVEL_CAMPO) {
      fcampos *c = b->vi.act->trigerdatos;
      FORM(b)->validar = 1;
      FORM(b)->cinput = c;
      if (copia) free(copia);
      copia = salvacampo(b, c);
      preparaenter(b);
      if (c->pref&& !b->enterquery) {
          ejecutaftriger(b, PPREFIELD, c->pref, c);
      }
      pulsada = ret = blinput(&b->vi);
      if (ret == MOUSEPOS) {
//	       if (c->change) *FERROR(b,c)=-1;
          if (mousepos.action == DOBLECLICK) ret = tecla();
      }
      ret = procesateclacampo(b, c, ret);
      if (ret == MOUSEPOS) {
          if (mousepos.action == DOBLECLICK) continue;
      }
      if (v10versionweb) {
         if (ret == MOUSEPOS && psemueveelraton(b) <= 1) continue;
       }
	    if (ret<=0) continue;
        switch (ret) {
           case cuu:siginput(&b->vi);
                    break;
           case cua:antinput(&b->vi);
                    break;
           case C_F(11):b->noinput=1;
			            FORM(b)->nivel=NIVEL_REGISTRO;
                        ret=0;
                        break;
           case C_F(9):  forminfo(FORM(b));
                         ret=0;
                         break;
         }
		
		postret=ejepostret=0;
        if (!b->enterquery) {
			if (procesapreteclabloque(b,ret)) ret=0;
            ret=procesateclabloque(b,ret);
            if (pulsada==TECLATIMEOUT && ret==0) continue;
            switch (ret) {
                 case F(2): selectpagina(b,NULL);
                            break;
                 case F(3): borrabloque(b,NULL);
                            break;
                 case F(7): insertregistro(b,NULL);
                            break;
                 case F(8): borraregistro(b,NULL);
                            break;
                 case F(9): deleteregistro(b,NULL);
                            break;
                 case C_F(2):enterq(b);
                             ret=0;
                             break;
                 case C_F(3):countquery(b,NULL);
                             ret=0;
                             break;
                 case C_F(7):copiaregistro(b,NULL);
                             break;
				 case esc:   FORM(b)->validar=0;
					         break;

            }
			postret=ret; 

        } else {
            int salir=0;
            switch (ret) {
                  case F(2):  b->enterquery=ENTERQ;
                              preparaenter(b);
							  selectpagina(b,NULL);
							  if (v10versionweb) b->vi.act=b->vi.ultinp;							  
                              salir=1;
                              break;
                  case esc :  b->enterquery=ENTERQ;		   
							  abortaquery(b,NULL);
                              b->enterquery=0;	
							  ret=0;
                              break;
                  case C_F(2):b->enterquery=1;	
							  if (!b->noquery) enterq(b);
							  b->enterquery=ENTERQ;
                              break;
                  default   : b->enterquery=ENTERQ;
							  break;
                 }
             if (salir) break;
                else    continue;
         }
		
        if (b->s->lppag>1) {
           if (b->vi.ultinp==b->vi.prim && b->vi.act==b->vi.ult && ret==stab) {
              ret=cuu;
			  ejepostret=1;
              FORM(b)->nivel=NIVEL_REGISTRO;
            }
           if (b->vi.ultinp==b->vi.ult && b->vi.act==b->vi.prim && (ret==tab||ret==13)) {
              ret=cua;
			  ejepostret=1;
              FORM(b)->nivel=NIVEL_REGISTRO;
            }
         }
        if ((((ret>255) && (ret!=stab)) || ret==esc) && FORM(b)->nivel==NIVEL_CAMPO) FORM(b)->nivel=NIVEL_REGISTRO;
        if (ret==F(5)) FORM(b)->validar=0;
        modif=0;
        if (comparacampo(b,c,copia) && !esnuloregistro(b) && FORM(b)->validar) {
           if (c->noupdate && CABECERA(b)->antiguo) {
              recuperacampo(b,c,copia);
              posicionadialog(&b->vi,direccampoptr(b,c));
              FORM(b)->nivel=NIVEL_CAMPO;
              warning(("Campo no modificable"));
            } else {
              modif=1;
            }
         }
        if ((modif || *FERROR(b,c))&&!esnuloregistro(b) ) {
           if (FORM(b)->validar) {
              if (c->change) {
                 if ((*FERROR(b,c)=ejecutaftriger(b,PPOSTCHANGE,c->change,c))!=0) {
                    recuperacampo(b,c,copia);
                    if (b->vi.ultinp->enter) posicionadialog(&b->vi,direccampoptr(b,c));
                    FORM(b)->nivel=NIVEL_CAMPO;
                    modif=0;
                  }
               }
            } else if (c->change) *FERROR(b,c)=-1;
         }
        if (c->postf && FORM(b)->validar) {
           ret=ejecutaftriger(b,PPOSTFIELD,c->postf,c);
         }
        if (modif) {
           if (!b->noinsert || CABECERA(b)->antiguo) {
              CABECERA(b)->modif=1;
              if (!b->nocommit) {
                 FORM(b)->modif=1;
                 b->modif=1;
               }
            }
         }
	// cambia de tecla o sigue a este nivel, y se puedeejecutar el post
	if ((ejepostret ||  FORM(b)->nivel==NIVEL_CAMPO) &&  postret) postret=procesapostteclabloque(b,postret);
  }
  if (copia) free(copia);
  return(ret);
}
