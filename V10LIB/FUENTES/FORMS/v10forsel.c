/*
* Módulo : V10FORSEL.C
* Objeto:  Tratamiento de seleccion de registros en formularios
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"   



int numtimeoutform=0;

static void pasaforebloque(virtsels *s)
{
    bloques *b=s->dato;
    int margens;
    int desde;
    margens=b->s->v.y1-b->s->v1->y1;
    for (desde=0;desde<b->s->linreg;desde++) {
        recuperapantallaansi(b->vi.contenido+(margens+desde)*b->vi.largo-b->vi.despx,
            b->vi.w.x1,b->vi.w.y1+desde+b->vi.despy+margens,
            b->vi.w.x2,b->vi.w.y1+desde+b->vi.despy+margens);
    }
}

void reajustapagina(v10dialogs *vi,void *dato)
{
    bloques *b=dato;
    grabaregistro(b,VIRTPOS(b->s));
    muestradialog(&b->vi,0);  
    representapagina(b->s);
    STDpintapaginabloque(b->s,1);
}

void STDpintapaginabloque(virtsels *s,int resaltado)
{
    bloques *b=s->dato;
    int antresal=b->resaltado;
    b->resaltado=resaltado;
    b->vi.despy=(s->clin-s->plin)*s->linreg;
    asignacolorbloque(b,b->color);
    pasaforebloque(s);
    leeregistroi(b,VIRTPOS(s));
    if (!es_blanco(direcncampo(b,"V10_COLOR"))) {
        asignacolorbloque(b,direcncampo(b,"V10_COLOR"));
        pasaforebloque(s);
    }
    if (b->noinsert && !CABECERA(b)->antiguo && VIRTPOS(s)>0) return;
    preparaenter(b);
    switch (resaltado) {
  case 0: if (VIRTPOS(s)%2) {
      b->vi.w.t.t[CINPUTINAC]=b->vi.w.t.t[FORMIMPAR];
      b->vi.w.t.t[CNOENTER]=b->vi.w.t.t[FORMIMPARNE];
          } else {
              b->vi.w.t.t[CINPUTINAC]=b->vi.w.t.t[FORMNORMAL];
              b->vi.w.t.t[CNOENTER]=b->vi.w.t.t[FORMPARNE];
          }
          break;
  case 1: b->vi.w.t.t[CINPUTINAC]=b->vi.w.t.t[FORMRESAL];
      b->vi.w.t.t[CNOENTER]=b->vi.w.t.t[FORMRESALNE];
      break;
  case 2: b->vi.w.t.t[CINPUTINAC]=b->vi.w.t.t[FORMFUERA];
      b->vi.w.t.t[CNOENTER]=b->vi.w.t.t[FORMFUERANE];
      break;
    }
    if ((VIRTPOS(s)==s->numero-1 && !esnuloregistro(b)) && (b->quedan || !b->noinsert)) {
        s->numero++;
        s->numlin++;
        if (s->ulin-s->plin<s->lppag-1) s->ulin++;
    }
    llactualizabloque(b);
    b->resaltado=antresal;
}

int selectpagina(bloques *b, ftrigers *ft)
{
    int ret;
    if (b->noquery) return(IGNORAR);
	if (b->modif &&  FORM(b)->preguntar == 1) {
        if (b->enquery!=0 || b->s->numlin>=2 || b->s->clin>0) {
            if ((ret=commitsino(FORM(b)))!=0) return(ret);
        } 
        FORM(b)->preguntar=1;
    }
    b->enterquery=0;
    b->modif=0;
    mirasimodif(FORM(b));
    b->s->numero=b->s->numlin=1;
    b->s->plin=b->s->ulin=b->s->clin=0;
    FORM(b)->nivel=NIVEL_FORM;
    FORM(b)->validar=0;
    if (b->fprequery) {
        ret=ejecutaftriger(b,PPREQUERY,b->fprequery,NULL);
        if (ret) return(ret);
    }
    if ((ret=genselect(b))!=0) {
        b->aquery=0;
        return(ret);
    }
    ret=ejecutacursor(b->select);
    if (ret) {
        cursordebug(b->select);
        FORM(b)->oraerr=ret;
        b->aquery=0;
    } else {
        b->enquery=1;
        b->quedan=1;
        if (b->tquery) {
            if (!v10versionweb)
                b->invisible=1;
            while (leeregistroi(b,b->s->clin)==0){
                b->s->clin++;
                b->s->numero++;
                b->s->numlin++;
            }
            if (b->noinsert && b->s->numero>1) {
                b->s->numero--;
                b->s->numlin--;
            }
            b->s->clin=0;
            if (!v10versionweb)
                b->invisible=0;
        }
        if (b==b->form->b[b->form->act]) b->s->marco=0;
        else                          b->s->marco=1;
        representapagina(b->s);

        if (!v10versionweb) STDpintapaginabloque(b->s,2);
        else pintapaginabloque(b->s,2);

        if (b->tquery && b->ffinquery) {
            ret=ejecutaftriger(b,PFINQUERY,b->ffinquery,NULL);
        }
    }
    return(ret);
}

// si devuelve !=0, es que ha habido error al ejecutarlo
int procesapreteclabloque(bloques *b,int ret) {
	int nt,tecla; 
	
	if (ret==0) return(ret);
	tecla=ret;
	ret=0;

    for (nt=0;nt<b->nteclas;nt++) {
        if (b->teclas[nt].t==tecla) {
			if (b->teclas[nt].trigpre) {
				if (b->teclas[nt].trigpre->fun) {
					ret=b->teclas[nt].trigpre->fun(b,b->teclas[nt].trigpre);
					if (ret && b->teclas[nt].trigpre->msg) {
						char destino[MAXCADENA];
						sustituyevariables(b,b->teclas[nt].trigpre->msg,destino);
						mensajefcm(10,destino);
						ret=-1;
					}
				} else ret=-1;
			}
            return(ret);
        }
    }
	return(ret);
}

int procesaposttecla(int ret) {
	if (formglobal)	return(procesapostteclabloque(formglobal->b[formglobal->act],ret));
	else return(ret);
}

// si devuelve !=0, es que ha habido error al ejecutarlo
int procesapostteclabloque(bloques *b,int ret) {
	int nt,tecla;

	if (ret==0) return(ret);
	tecla=ret;
	ret=0;

    for (nt=0;nt<b->nteclas;nt++) {
        if (b->teclas[nt].t==tecla) {
			if (b->teclas[nt].trigpost) {
				if (b->teclas[nt].trigpost->fun) {
					ret=b->teclas[nt].trigpost->fun(b,b->teclas[nt].trigpost);
					if (ret && b->teclas[nt].trigpost->msg) {
						char destino[MAXCADENA];
						sustituyevariables(b,b->teclas[nt].trigpost->msg,destino);
						mensajefcm(10,destino);
						ret=-1;
					}
				} else ret=-1;
			}
            return(ret);
        }
    }
	return(ret);
}


int procesateclabloque(bloques *b,int ret)
{
    int nt;
	
	if (ret==0) return(ret);

    for (nt=0;nt<b->nteclas;nt++) {
        if (b->teclas[nt].t==ret) {
			if (b->teclas[nt].trig) {				
				if (b->teclas[nt].trig->fun) {
					ret=b->teclas[nt].trig->fun(b,b->teclas[nt].trig);
					if (ret==0) { // el triger dá exito, ejecuta posttecla si lo tiene
						if (b->teclas[nt].trigpost && b->teclas[nt].trigpost->fun) {
							ret=b->teclas[nt].trigpost->fun(b,b->teclas[nt].trigpost);
							if (ret) {
								char destino[MAXCADENA];
								sustituyevariables(b,b->teclas[nt].trigpost->msg,destino);
								mensajefcm(10,destino);		
								ret=0;
							}
						}
					} else {
						ret=0; // no se sigue tratando
						if (b->teclas[nt].trig->msg) {
							char destino[MAXCADENA];
							sustituyevariables(b,b->teclas[nt].trig->msg,destino);
							mensajefcm(10,destino);							
						}
					}
				} else ret=0; // no tiene funcion asignada
			}
            return(ret);
        }
    }
    if (ret==S_F(10) || ret==CS_F(10)) {
        if (b->contextual) {
            ret=ejecutaftriger(b,PCONTEXTUAL,b->contextual,NULL);
        }            
    }
    return(ret);
}

int deleteregistro(bloques *b, ftrigers *ft)
{
    if (b->nodelete && CABECERA(b)->antiguo==1) return(0);
    if (VIRTPOS(b->s)==b->s->numero-1 && CABECERA(b)->antiguo==0) {
        borraregistro(b,NULL);
        return(0);
    }
    marcadelete(b);
    if (!b->nocommit) {
        b->modif=1;
        FORM(b)->modif=1;
    }
    if (b->s->numero) {
        b->s->numero--;
        /*if (v10versionweb)*/ b->s->numlin--;	
        if (b->s->ulin>=b->s->numero) b->s->ulin--;
        if (b->s->clin>=b->s->numero) b->s->clin--;
        if (b->s->plin>=b->s->numero) b->s->plin--;
    }
	representapagina(b->s);
    FORM(b)->nivel=NIVEL_BLOQUE;
    FORM(b)->validar=0;
    return(0);
}

int STDinsertregistro(bloques *b, ftrigers *ft)
{
    if (b->noinsert) return(0);
    grabaregistro(b,VIRTPOS(b->s));
    insertaregistro(b);
    b->s->clin++;
    b->s->numero++;
    b->s->numlin++;
    if (b->s->clin-b->s->plin>b->s->lppag-1) {
        b->s->plin++;
        b->s->ulin++;
    }
    if (b->s->ulin-b->s->plin<b->s->lppag-1) b->s->ulin++;
    representapagina(b->s);
    FORM(b)->nivel=NIVEL_BLOQUE;
    FORM(b)->validar=1;
    return(0);
}

int copiaregistro(bloques *b, ftrigers *ft)
{
    virtsels *s=b->s;
    if (b->noinsert) return(0);
    if (!esnuloregistro(b)) insertregistro(b,NULL);
    if (VIRTPOS(s)) {
        leeregistroi(b,VIRTPOS(s)-1);
        CABECERA(b)->antiguo=0;
        CABECERA(b)->modif=1;
        if (!b->nocommit) {
            b->modif=1;
            FORM(b)->modif=1;
        }
        grabareg(b,VIRTPOS(s));
        if (v10versionweb==0)
            actualizabloque(b);
    }
    return(0);
}



int finputregistro(bloques *b)
{
    int ret=0,retpos=0;
    if (b->fpreregistro) {
        ret=ejecutaftriger(b,PPREREGISTRO,b->fpreregistro,NULL);
        if (ret) {
            FORM(b)->nivel=NIVEL_FORM;
            b->s->salir=1;
            return(0);
        }
    }
    FORM(b)->nivel=NIVEL_REGISTRO;
    FORM(b)->validar=1;
    while (FORM(b)->nivel==NIVEL_REGISTRO) {
        if (entrablebloque(b) && b->noinput==0) {
            ret=finputcampo(b);
			retpos=ret;
        } else  {
            int salir=0;
            while (!salir) {
                if (!v10versionweb) ret=tecla();
                else  ret=finputregistroaux(b);
				if (procesapreteclabloque(b,ret)) ret=0;
                ret=procesateclabloque(b,ret);
				retpos=ret;
                switch (ret) {
                     case cr:ret=F(10);
                         salir=1;
                         break;
                     case F(5):
                     case esc:salir=1;
                              FORM(b)->validar=0;
                              break;
                     case C_F(9):forminfo(FORM(b));
                         break;
                     case stab:{							  
                         v10dialogs *v=&b->vi;
                         v10inputs *v1;
                         if (v10versionweb) break;
                         for (v1=v->ult;v1>v->prim;v1--) {
                             if (seveventana(v1,v->despx,v->despy)) {
                                 break;
                             }
                         }
                             for (;v1>v->prim;v1--)
                                 if (!seveventana(v1,v->despx,v->despy)) {
                                     ajustaventana(v,v1);
                                     break;
                                 }
                                 if (!seveventana(v1,v->despx,v->despy)) {
                                     ajustaventana(v,v1);
                                     break;
                                 }
                                 break;
                               }
                     case tab:{
                         v10dialogs *v=&b->vi;
                         v10inputs *v1;
                         if (v10versionweb) break;
                         for (v1=v->prim;v1<v->ult;v1++)
                             if (seveventana(v1,v->despx,v->despy)) {
                                 break;
                             }
                             for (;v1<=v->ult;v1++)
                                 if (!seveventana(v1,v->despx,v->despy)) {
                                     ajustaventana(v,v1);
                                     break;
                                 }
                                 break;
                              }
                     case C_F(10):b->noinput=0;
                         salir=1;
                         ret=0;
                         break;
                     case C_F(11):b->noinput=0;
                         salir=1;
                         ret=0;
                         break;
                     case F(3):   borrabloque(b,NULL);
                         salir=1;
                         b->form->nivel=NIVEL_REGISTRO;
						 break;
					 case F(9): deleteregistro(b, NULL);
						 break;
                     case C_F(2):enterq(b);
                         ret=0;
                         salir=1;
                         break;
                     case C_F(3):countquery(b,NULL);
                         ret=0;
                         break;
                    /* ojo con esto */
                    case F(2): selectpagina(b,NULL);
                         break;
                     case cud: if (v10versionweb) break;
                         if (b->vi.despx+b->vi.largo>WANCHO(&(b->vi.w))) {
                             b->vi.despx--;
                             reajustapagina(&b->vi,b);
                         }
                         break;
                     case cui: if (v10versionweb) break;
                         if (b->vi.despx<0) {
                             b->vi.despx++;
                             reajustapagina(&b->vi,b);
                         }
                         break;

                     case MOUSEPOSD:
                     case MOUSEPOS: {
                         v10inputs *v;
                         if (v10versionweb) {
                             ret=reposicionadialograton(&b->vi);
                             salir=1;
                             break;
                         }
                         for (v=b->vi.prim;v<b->vi.ult;v++) v->enter=0;
                         if (reposicionadialograton(&b->vi)!=0) {
                             if (mousepos.action!=DOBLECLICK) ret=0;
                             else                          salir=1;
                         } else salir=1;
                                    }
                                    break;
                     default:salir=1;
                }
				if (!salir) if (procesapostteclabloque(b,retpos)) retpos=0;
			}
            if (ret) posicionadialog(&b->vi,NULL);
        }
        if (v10versionweb) {
            if (ret==MOUSEPOS) ret=reposicionaregraton(&b->vi);
        }
        if ((ret>255||ret==esc) && FORM(b)->nivel==NIVEL_REGISTRO) FORM(b)->nivel=NIVEL_BLOQUE;
        if (FORM(b)->validar && FORM(b)->nivel!=NIVEL_REGISTRO) {
            fcampos *c;
            if ((c=primerinvalido(b))!=NULL) {
                posicionadialog(&b->vi,direccampoptr(b,c));
                FORM(b)->nivel=NIVEL_REGISTRO;
            }
        }
		if (FORM(b)->nivel==NIVEL_REGISTRO) retpos=procesapostteclabloque(b,retpos);
	}
    grabaregistro(b,VIRTPOS(b->s));
    if (!v10versionweb) STDpintapaginabloque(b->s,0);
    else pintapaginabloque(b->s,0);
    if (FORM(b)->validar) {
        if (b->fpostregistro) {
            ret=ejecutaftriger(b,PPOSTREGISTRO,b->fpostregistro,NULL);
            return(ret);
        }
    }
	
    return(ret);
}

int teclapaginabloque(virtsels *s)
{
    int ret;
    bloques *b=s->dato;
    if (b->noinsert && !CABECERA(b)->antiguo && VIRTPOS(s)>0) {
        if (s->clin==s->ulin) s->ulin--;    
        s->clin--;
        if (s->plin>s->clin) s->plin--;
        return(0);
    }
    ret=finputregistro(b);
	if (FORM(b)->nivel<NIVEL_BLOQUE) {
		if (procesapostteclabloque(b,ret)) ret=0;
		s->salir=-1;
	}
    if (!v10versionweb) {
        ult_pul=(ret==MOUSEPOSMV?0:ret);
        return(ult_pul);
    } else
        return(ret);
}

int paginabloque(bloques *b)
{
    int ret;
    int cx,cy;
    char ntimeout[MAXNOMBREV10];
    if (b->ftimeout && v10versionweb==0) {
        numtimeoutform++;
        sprintf(ntimeout,"FTIMEOUT%d",numtimeoutform);
        declarav10timernt(ntimeout,(void (*)(v10timers *))(b->ftimeout->fun),b->timeout,TIMERTIMEOUT,b->ftimeout);
    }
    if (!v10versionweb) {	
        curr_cursor(&cx,&cy);
    }
    if (FORM(b)->validar) {
        if (b->fprebloque) {
            ret=ejecutaftriger(b,PPREBLOQUE,b->fprebloque,NULL);
            if (ret) return(ret);
        }
        if (b->aquery && !b->enterquery ) {
            borraregistro(b,NULL);
            if (selectpagina(b,NULL)) {
                if (v10versionweb) resetencolados();
                if (hay_tecla()) tecla();
                return(F(6));
            }
        }
    }
    FORM(b)->nivel=NIVEL_BLOQUE;
    if (!v10versionweb) {
        if (!es_blanco(b->ayuda)) v10ponayuda(b->ayuda);
        if (b->online) pintaonline(b->online);
    }
    if (1) {
        char nombre[MAXCADENA];
        sprintf(nombre,"FORM: %s/%s",b->form->nombre,b->fichero);
        setmodule(nombre,"");
    }
    while (FORM(b)->nivel==NIVEL_BLOQUE) {
        ret=reselecciona(b->s,pprocesaposttecla);
        if (!v10versionweb)
            ret=ult_pul;		  	   
        else
            if (ret==DESPLAZA) 
                ret=0;
        if ((ret>255 || ret==esc || ret==-1) && FORM(b)->nivel==NIVEL_BLOQUE) FORM(b)->nivel=NIVEL_FORM;
		//if (procesapostteclabloque(b,ret)) ret=0;
	}
    if (!v10versionweb) {
        if (!es_blanco(b->ayuda)) v10quitaayuda();
        if (b->online) borraonline();
    }

    if (!v10versionweb) STDpintapaginabloque(b->s,2);
    else pintapaginabloque(b->s,2);

    fgotoxy(cx,cy);
    if (b->ftimeout && v10versionweb==0) {
        numtimeoutform--;
        liberav10timer(ntimeout);
    }
    if (FORM(b)->validar) {
        if (b->fpostbloque) {
            ret=ejecutaftriger(b,PPOSTBLOQUE,b->fpostbloque,NULL);
            return(ret);
        }
    }
    setmodule("","");   
    return(ret);
}

int presentabloque(bloques *b,int query)
{
    int cx,cy;
    int antlock=b->nolock;
    int antinput=b->s->hayinput;
    curr_cursor(&cx,&cy);
    b->nolock=1;
    b->s->hayinput=0;
    if (b->aquery && (!b->enquery || b->padre!=NULL) && query) {
        if (b->modif) {
            if (commitsino(FORM(b))) return(-1);
            b->modif=0;
        }
        muestradialog(&b->vi,0);
        borraregistro(b,NULL);
        selectpagina(b,NULL); 
    } else  muestradialog(&b->vi,0);
    b->s->ulin=b->s->plin-1;
    llselecciona(b->s);
    if (!v10versionweb) STDpintapaginabloque(b->s,2);
    else pintapaginabloque(b->s,2);
    fgotoxy(cx,cy);
    b->nolock=antlock;
    b->s->hayinput=antinput;
    return(0);
}

int STDreposratonform(forms *f)
{
    int nb;
    for (nb=0;nb<f->nbloques;nb++) {
        bloques *b=f->b[nb];
        if (reposicionaraton(b->s)) {
            if (entrablebloque(b)!=0) encolatecla(MOUSEPOS);
            return(nb);
        }
    }
    return(-1);
}

static int strlensb(char *cadena)
{
    int i;
    for (i=strlen(cadena)-1;i>=0;i--) if (cadena[i]!=' ') return(i+1);
    return(i+1);
}

char *dametooltipcampo(bloques *b,fcampos *c,char *donde)
{
    if (c->tooltip) sustituyevariables(b,c->tooltip,donde); 
    else         strcpy(donde,"");
    if (c->lvar>c->v->lpan && c->tipo==V10CADENA) {//OJO UNICODE
        if (c->v->lpan<strlensb(direcncampo(b,c->nombre))) {
            if (!es_blanco(donde)) strcat(donde,"\n");
            strcat(donde,direcncampo(b,c->nombre));
            trim(donde);
        }
    }
    return(donde);
}

static void verificatooltip(mouseposs *pr)
{
    int nc,nb;
    char tooltipvariable[MAXCADENA];

    for (nb=0;nb<formglobal->nbloques;nb++) {
        bloques *b=formglobal->b[nb];
        for (nc=0;nc<b->ncamp;nc++) {
            fcampos *c;
            c=b->c+nc;
            if (NULL==c->v) continue;
            if (pr->posx >= (c->v->w->x1 + c->v->posx )+b->vi.despx           &&
                pr->posx < (c->v->w->x1 + c->v->posx ) + c->v->lpan+b->vi.despx &&
                (pr->posy == c->v->w->y1 + c->v->posy+b->vi.despy) ) {
                    if (c->tooltip || (c->lvar>c->v->lpan && c->tipo==V10CADENA)) {
                        if (c->funtooltip) {
                            fcampos *ant=formglobal->cinput;
                            formglobal->cinput=c;
                            c->funtooltip->msg=(char *)pr;
                            c->funtooltip->fun(b,c->funtooltip);
                            formglobal->cinput=ant;
                        } else {
                            dametooltipcampo(b,c,tooltipvariable);
                            if (!es_blanco(tooltipvariable)) v10tooltip(pr,tooltipvariable);
                        }
                    }
                    break;
            }
        }
    }
}


int finputform(forms *f)
{
    int ret=0;
    int nb;
    void *anttecladespues;
    static int nivel;
    void *antfuntooltip;
	bloques *bant;
    nivel++;
    anttecladespues=triger_tecla_despues;
    triger_tecla_despues=teclaform;
    f->act=-1;
    for (nb=0;nb<f->nbloques;nb++) {
        bloques *b=f->b[nb];
        int presentar=1;
        b->s->marco=1;
        b->vi.marco=1;
        if (!b->noenter && f->act==-1) {
            presentar=0;
            f->act=nb;
        }
        presentabloque(f->b[nb],presentar);
        if (b->pquery) selectpagina(b,NULL);
    }
    if (f->act==-1) {
        mensajefcm(10,"No hay bloque entrable");
        return(-1);
    }
    f->validar=1;
    f->nivel=NIVEL_FORM;
	if (f->preform) {
		ret = ejecutaftriger(f->b[0], 0,f->preform, NULL);
		if (ret) return (ret);
	}
    if (!v10versionweb) antfuntooltip=ponfunciontooltip(verificatooltip);    
    while (f->nivel==NIVEL_FORM) {
        if (!v10versionweb) {
            f->b[f->act]->vi.marco=0;
            f->b[f->act]->s->marco=0;
            renmarca(&f->b[f->act]->vi.w,0,f->b[f->act]->vi.titulo);
            flechasdialog(&f->b[f->act]->vi);
        }
        f->validar=1;
        ret=paginabloque(f->b[f->act]);
        if (!v10versionweb) {
            f->b[f->act]->vi.marco=1;
            f->b[f->act]->s->marco=1;
            renmarca(&f->b[f->act]->vi.w,1,f->b[f->act]->vi.titulo);
            flechasdialog(&f->b[f->act]->vi);
        }
		bant = f->b[f->act];
        switch (ret) {
               case F(4) :if (commitform(f,NULL)) f->validar=0;
                          else             f->validar=1;
                          break;
               case F(5) :rollbackform(f,NULL);
                   f->act=0;
                   f->validar=1;
                   break;
               case F(6) :do {
                   if (f->act<f->nbloques-1)   f->act++;
                   else                       f->act=0;
                          } while (f->b[f->act]->noenter==1);
                   break;
               case C_F(6) :do {
                   if (f->act>0)   f->act--;
                   else            f->act=f->nbloques-1;
                            } while (f->b[f->act]->noenter==1);
                   break;
               case MOUSEPOS :{int nb;
                   nb=reposratonform(f);
                   if (nb>=0) f->act=nb;
                              }
                              break;
               case F(10) :
               case esc     :if (f->modif) {
                   if (commitsino(f)) {
                       f->nivel=NIVEL_FORM;
                       f->preguntar=1;
                       break;
                   }
                             }
                             f->nivel=NIVEL_EXTERNO;
                             f->validar=0;
                             break;
        }
		if (procesapostteclabloque(bant,ret)) ret=0;
		
    }
    if (f->validar || 1) {
        if (f->postform) ret=f->postform->fun(f->b[0],f->postform);
    }
    if (!v10versionweb)
        ponfunciontooltip(antfuntooltip);
    nivel--;
    if (nivel==0) rollback();
    triger_tecla_despues=anttecladespues;
    return(ret);
}
