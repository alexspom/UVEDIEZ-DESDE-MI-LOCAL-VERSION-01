/*
* Módulo : V10DIALOG.C
* Objeto:  Tratamiento bajo nivel de cuadros de dialogo
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/

#define TIPOMARCO 0

#include "v10.h"


void initbloque(v10dialogs *v)
{
  v->ult=v->prim=v->act=v->ultinp=NULL;
  v->despx=0;v->despy=0;
}

static v10inputs *posvi(v10dialogs *vi,void *var)
{
  v10inputs *v1;
  if (var==NULL) return(vi->prim);
  v1=vi->prim;
  while (v1<=vi->ult) {
    if (v1->dato==var) return(v1);
    v1++;
   }
  return(NULL);
}

void flechasdialog(v10dialogs *vi)
{
  colventanas tmarco;
  if (vi->marco==0) {
      tmarco=vi->w.t.t[CMARCOR];
  } else {
      tmarco=vi->w.t.t[CMARCON];
  }
  if (vi->despx<0) wplot(vi->w.hwnd,vi->w.x1,vi->w.y1-1,'\x11',tmarco.tinta,tmarco.papel);
     else wplot(vi->w.hwnd,vi->w.x1,vi->w.y1-1,pasaoemchar(v10marco[BARRAHOR][vi->marco]),tmarco.tinta,tmarco.papel);
  if (vi->despx+vi->largo>WANCHO(&(vi->w))) wplot(vi->w.hwnd,vi->w.x2,vi->w.y1-1,'\x10',tmarco.tinta,tmarco.papel);
     else wplot(vi->w.hwnd,vi->w.x2,vi->w.y1-1,pasaoemchar(v10marco[BARRAHOR][vi->marco]),tmarco.tinta,tmarco.papel);
}

static void pasaforev10dialogsf(v10dialogs *v)
{
  int desde;
  for (desde=0;desde<WALTO(&v->w);desde++) {
      wrecuperapantallaansi(v->w.hwnd,v->contenido+desde*v->largo-v->despx,v->w.x1,v->w.y1+desde,v->w.x2,v->w.y1+desde);
    }
}

static void pasaforevi(v10dialogs *v)
{
  pasaforev10dialogsf(v);
  flechasdialog(v);
}

void STDmuestradialog(v10dialogs *vi ,int guarda)
{
  if (guarda) if (vi->pantalla_debajo==0L) vi->pantalla_debajo=salvavd(&vi->w);
  enmarca(&vi->w,vi->marco,vi->titulo);
  pasaforevi(vi);
}

static void presentadialog(v10dialogs *vi ,int guarda)
{
  muestradialog(vi,guarda);
  actualizadialog(vi);
}

static void borradialog(v10dialogs *vi)
{
  if (vi->pantalla_debajo) {
     recuperavd(&vi->w,vi->pantalla_debajo);
     vi->pantalla_debajo=0L;
   }
}


static void memasignav(v10inputs *v,int lon)
{
  v->ant=calloc(lon,1);
  v->def=calloc(lon,1);
  memcpy(v->ant,v->dato,lon);
}

static void asignav(v10inputs *v ,void *a)
/* Recibe una ventana y el dato a asignar.*/
{
  v->dato=a;
  if (v->activa==0) memasignav(v,tamv10tipo(v->tipo,v->lvar+1));
  v->activa=-1;
}

static void liberav(v10inputs *v)
{
  if (v->ant) {
     free(v->ant);
     v->ant=NULL;
   }
  if (v->def) {
     free(v->def);
     v->def=NULL;
   }
}

void vasignadialog(v10dialogs *vi ,va_list ap)
{
  v10inputs *p;
  void *arg;
  int i=0;
  p=vi->prim;
  while ((arg=va_arg(ap,void *))!=NULL) {
        if (p>vi->ult) {
           final(("Demasiadas variables"));
           break;
         } else {
           asignav(p,arg);
           p++;
         }
     i++;
    }
   vi->numinput=i;
   if (p<=vi->ult) final(("Pocas variables"));
}

void pasignadialog(v10dialogs *vi ,void **ap)
{
  v10inputs *p;
  void *arg;
  int i=0;
  p=vi->prim;
  while ((arg=*ap++)!=NULL) {
        if (p>vi->ult) {
           final(("Demasiadas variables"));
           break;
         } else {
           asignav(p,arg);
           p++;
         }
     i++;
    }
   vi->numinput=i;
   if (p<=vi->ult) final(("Pocas variables"));
}

void asignadialog(v10dialogs *vi,...)
{
  va_list ap;
  va_start(ap,vi);
  vasignadialog(vi,ap);
}

void liberadialog(v10dialogs *vi)
{
    v10inputs *p;
    if (vi->prim) {
        p=vi->prim;
        while (p<=vi->ult) {
            liberav(p);
            p=p+1;
        }
        free(vi->prim);
        vi->prim=vi->ult=vi->act=vi->ultinp=NULL;
    }
    if (vi->contenido) {
        free(vi->contenido);
        vi->contenido=NULL;
    }
}

/* MODIFICA COMPORTAMIENTO DE LA VENTANA */
int enumeradialog(v10dialogs *vi,void *var,char **lista)
{
    v10inputs *v;
    v=posvi(vi,var);
    if (v==NULL) return(1);
    v->seleccion=1;
    v->lista=lista;
    return(0);
}

void entrabledialog(v10dialogs *vi,void *var,int permite)
{
    v10inputs *v;
    v=posvi(vi,var);
    if (v==NULL) return;
    if (v->invisible) permite=0;
    v->enter=permite;
}

void autoenterdialog(v10dialogs *vi,void *var,int permite)
{
    v10inputs *v;
    v=posvi(vi,var);
    if (v==NULL) return;
    v->autoenter=permite;
}

void STDactualizadialog(v10dialogs *v)
{
    v10inputs *v1=v->prim;
    poncolorv(&v->w,CINPUTINAC);
    while (v1<=v->ult) {
        if (v1->fpresenta) (*v1->fpresenta)(v1,v->despx,v->despy);
        else if (v1->seleccion) presinp(v1,v->despx,v->despy);
        else      lpresenta(v1,v->despx,v->despy);
        v1++;
    }
    poncolorv(&v->w,CNORMAL);
}

void ajustaventana(v10dialogs *vi,v10inputs *v)
{
    if (!seveventana(v,vi->despx,vi->despy)) {
        if (v->posx+vi->despx<0) vi->despx=-v->posx;
        if (v->posx+vi->despx+v->lpan>=WANCHO(v->w)) vi->despx=WANCHO(v->w)-v->posx-v->lpan;
        if (vi->reajusta) vi->reajusta(vi,vi->reajdato);
        else           presentadialog(vi,0);
    }
}

int STDreposicionadialograton(v10dialogs *vi)
{
  v10inputs *v;
  if (!enrango(mousepos.posy,vi->prim->posy+vi->despy+vi->w.y1,vi->ult->posy+vi->despy+vi->w.y1)|| !enrango(mousepos.posx,vi->w.x1,vi->w.x2)) {
     vi->salir=1;
     return(0);
   }
  if (mousepos.posx==vi->w.x1-1||mousepos.posx==vi->w.x2+1) return(0);
  for (v=vi->prim;v<=vi->ult;v++) {
      if (reposicionavraton(v,vi->despx,vi->despy)!=-1) {
         if (v->enter!=0 && v->invisible==0) {
            vi->act=v;
            encolatecla(MOUSEPOS);
          } else {
            if (v->invisible==0) {
               tratascrollv(v,vi->despx,vi->despy);
             }
          }
         return(1);
       }
   }
  return(1);
}

int STDblinput(v10dialogs *v)
{
  int ret;
  v10inputs *v1=v->act;
  if (v1==0L) final(("Haciendo input sobre NULL"));
  if (v1->enter==0 || v1->invisible) {
     if (v->ultinp==v1-1) {ret=cr;}
      else if (v->ultinp==v1+1) {ret=stab;}
       else if (v1==v->ult) {v->ultinp=v1;v->act=v1-1;return(cr);}
        else {v->ultinp=v->prim;v->act=v->prim+1;return(cr);}
    } else {
      if (!seveventana(v1,v->despx,v->despy)) ajustaventana(v,v1);
      if (v1->finput) ret=(*v1->finput)(v1,v->despx,v->despy);
         else
            if (v1->seleccion==0) ret=llinput(v1,v->despx,v->despy);
              else	    ret=selecinp(v1,v->despx,v->despy);
    }
  if (v1->modif) v->modificado=-1;
  if (v1->modif||(v1->vtriger==0)) {
     if ((v1->triger!=NULL)&&(v1->activa!=1)) {
        v1->activa=1;v1->vtriger=(*v1->triger)(v1->trigerdatos,v);
        v1->activa=-1;
      }
  }
  v->ultinp=v1;
  switch(ret) {
    case cuu:
    case stab:if (v1>v->prim) v->act=v1-1;
               else v->act=v->ult;
              break;
    case cua  :if ((v1->triger==0L)||(v1->vtriger)) {
                  if (v1!=v->ult) v->act=v1+1;
                  else v->act=v->prim;
               }
                break;
    case tab:
    case  cr:if ((v->act->triger==NULL)||(v->act->vtriger)) {
                 if (v->act!=v->ult) v->act=v->act+1;
                 else v->act=v->prim;
             }
             break;
	case F(4):
    case esc:v->salir=1;
             break;
    case MOUSEPOS:if (reposicionadialograton(v)) {
                     if (ret==CLICK) ret=0;
                  }
                  break;
    case MOUSEPOSD:if (reposicionadialograton(v)) {
                     if (ret==CLICK) ret=0;
                   }
                   break;
  }
   return(ret);
}

int vinputnm(v10dialogs *vi)
{
  int ret=0,cx,cy;
  curr_cursor(&cx,&cy);
  vi->salir=0;
  while (!vi->salir) {
        ret=blinput(vi);
   }
  fgotoxy(cx,cy);
  return(ret);
}

int dialoginput(v10dialogs *vi)
{
  int ret;
  renmarca(&vi->w,vi->marco,vi->titulo);
  ret=vinputnm(vi);
  renmarca(&vi->w,vi->marco,vi->titulo);
  return(ret);
}

int dialoginputpres(v10dialogs *vi)
{
  int ret;
  presentadialog(vi,1);
  actualizadialog(vi);
  ret=dialoginput(vi);
  borradialog(vi);
  return(ret);
}

void posicionadialog(v10dialogs *vi,void *var)
{
  v10inputs *v1;
  if (var==NULL) {
     vi->act=vi->prim;
     vi->ultinp=vi->ult;
     return;
    }
  v1=vi->prim;
  while (v1<=vi->ult) {
    if (v1->dato==var) {
       vi->act=v1;
       return;
      }
    v1++;
   }
  vi->act=vi->prim;
}


int v10dialogsalir(void *a,v10dialogs *vi)
{
  vi->salir=1;
  return(ult_pul);
}

void antinput(v10dialogs *vi)
{
  if (vi->act!=vi->prim) vi->act--;
     else                vi->act=vi->ult;
}

void siginput(v10dialogs *vi)
{
  if (vi->act!=vi->ult) vi->act++;
     else               vi->act=vi->prim;
}
