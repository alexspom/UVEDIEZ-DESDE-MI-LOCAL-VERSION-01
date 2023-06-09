/*
* M�dulo : V10INPUT.C                                            
* Objeto:  Entrada de datos estandar V10
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10.h"


#define MARCA A_F(2)
#define COPIA A_F(3)
#define COPIA1 A_F(4)
#define COPIA2 A_F(5)
#define MAX_ELEM  20
#define MAXCADINP (10*MAXCADENA)
int menulista_desactivado=0;
static int raton_encampo=1;
static int marbloque=0,marmod;
static int pmarca;
static menulistas *pbloque,*pmod,*pult;

static char salir;
static int opciones;
static char bufferinput[MAXCADINP],*tex;
static int pun;


static void llmarca(void)
{
   pmarca=pun;
   marbloque=1;
}

static int terminamarca(menulistas *p, int clipboard)
{
   int lon,principio;
   char ant;
   if (menulista_desactivado) return(0);
   if (pun==pmarca) {marbloque=0;return(0);}
   if (pun>pmarca) {
      lon=pun-pmarca;
      principio=pmarca;
    } else  {
      lon=pmarca-pun;
      principio=pun;
    }
   ant=tex[principio+lon];
   tex[principio+lon]=0;
   mete_en_menulista(p,tex+principio);
   if (clipboard) mete_en_clipboard(tex+principio);
   tex[principio+lon]=ant;
   marbloque=0;
   return(1);
}
static void copiamarca(menulistas *p,int num,v10inputs *v)
{
  int lon,sitio;
  lon=strlen(valor_menulista(p,num));
  sitio=v->lvar-pun;
  if (lon>sitio) {
     strcopia(tex+pun,valor_menulista(p,num),sitio);
     pun+=sitio;
   } else {
     strncpy(tex+pun,valor_menulista(p,num),lon);
     pun+=lon;
   }
}

static int valida(int x ,v10inputs *v)
{
 int val=0;
 switch (v->tipo) {
   case V10CHAR  :
   case V10CADENA:if (v->formato&FORMATONUM) {
	              val=((x>='0' && x<='9')|| x=='.'|| x==',');
				  break;
			   }
	           if (v->formato&FORMATORAW) {
				   x=toupper(x);
	               val=((x>='0' && x<='9')|| (x>='A' && x<='F'));
				   break;
			   }
			   val=((x>=0)&&(x<=255));
	           break;
   case V10FECHA :val=(((x>='0')&&(x<='9'))||(x=='-')||(x=='/')||(x=='H')||(x=='A')||(x=='M'));break;
   case V10HORA  :val=(((x>='0')&&(x<='9'))||(x=='-')||(x==':')
                    ||(pasacarmay(x)=='P')||(pasacarmay(x)=='M'));break;
   case V10BYTE  :
   case V10INT   :
   case V10SHORT:
   case V10LONG  :if (x>='A') x=toupper(x)-'A'+'0'+10;
               val=((x>='0')&&(x<='0'+v->dec-1))||(x=='-');
               if (opciones&COMADECIMAL) val=val||(x==',');
                else val=val||(x=='.');
	       break;
   case V10UINT   :
   case V10USHORT:
   case V10ULONG  :if (x>='A') x=toupper(x)-'A'+'0'+10;
               val=((x>='0')&&(x<='0'+v->dec-1));
               if (opciones&COMADECIMAL) val=val||(x==',');
                else val=val||(x=='.');
	       break;
   case V10DOUBLE:
   case V10FLOAT :val=((x>='0')&&(x<='9'))||(x=='-')||(x==',')||(x=='.');
               break;
   default    :final(("Tipo %d no definido",v->tipo));
               break;
  }
 return(val);
}

int seveventana(v10inputs *v,int tx,int ty)
{
  if (v->posx+tx<0||v->posx+tx+v->lpan-1>=WANCHO(v->w)) return(0);
  if (v->posy+ty<0||v->posy+ty>=WALTO(v->w)) return(0);
  return(1);
}

static void sustituyepass(char *temp)
{
  char *aux=temp+strlen(temp)-1;
  while (aux>=temp && *aux==' ') aux--;
  while (aux>=temp) *aux--='*';
}

static void poncursor(v10inputs *v ,char cambiado,int tx,int ty)
{
  char temp[MAXCADINP];
  strcpy(temp,tex);
  if (v->password) sustituyepass(temp);
  if (!seveventana(v,tx,ty)) return;
  if (pun-v->pcar>=v->lpan) {
     cambiado=1;
     v->pcar=pun-v->lpan;
     if (temp[pun]) v->pcar++;
   } else if (pun<v->pcar) {
             cambiado=1;
             v->pcar=pun;
           }
   if (cambiado) {
      poncolorv(v->w,CINPUTACT);
      imprimevp(v->w,v->posx+tx,v->posy+ty,temp+v->pcar,0,v->lpan);
      poncolorv(v->w,CNORMAL);
    }
   if (cambiado||marbloque) {
      poncolorv(v->w,CINPUTACT);
      if (!marbloque||pun==pmarca) {
         imprimevp(v->w,v->posx+tx,v->posy+ty,temp+v->pcar,0,v->lpan);
       } else {
         int prin,fin,llevo;
	      if (pun>pmarca) {prin=pmarca;fin=pun;}
            else         {prin=pun;fin=pmarca;}
         if (fin>v->pcar+v->lpan) fin=v->pcar+v->lpan;
         llevo=v->pcar;
         if (prin>v->pcar) {
            imprimevp(v->w,v->posx+tx,v->posy+ty,temp+llevo,0,prin-llevo);
            llevo=prin;
	       }
         poncolorv(v->w,CMARCA);
         imprimevp(v->w,v->posx+tx+llevo-v->pcar,v->posy+ty,temp+llevo,0,fin-llevo);
         llevo=fin;
         poncolorv(v->w,CINPUTACT);
         if (llevo<v->pcar+v->lpan) imprimevp(v->w,v->posx+tx+llevo-v->pcar,v->posy+ty,temp+llevo,0,v->pcar-llevo+v->lpan);
       }
      poncolorv(v->w,CNORMAL);
    }
   v->w->cursorx=v->posx+pun-v->pcar+tx;
   v->w->cursory=v->posy+ty;
   pon_curf(v->w);
}

int input2a(v10inputs *v,char *tex,int edit)
{
  v10tipo2a(v->dato,v->tipo,v->lvar,v->formato,v->dec,tex,edit);
  if (esv10tiponum(v->tipo) && strlen(tex)>v->lpan) {
      while (*tex==' ' && strlen(tex)>v->lpan) strcpy(tex,tex+1);
  }
  return(!esnulov10tipo(v->dato,v->tipo));
}

static void initinp(v10inputs *v)
{
  opciones=v10formatdef|(v->formato&MARCAMILES);
  if (v->tipo==V10CADENA) {
     tex=v->dato;
     strcpy(v->ant,v->dato);
   }  else              tex=bufferinput;
  marmod=input2a(v,tex,1);
  pmarca=0;
  if (marmod) {
     pun=(unsigned)(irfin(tex)-tex);
     if (v->password==0) marmod=terminamarca(pmod,0);
   }
  v->pcar=0;
  pun=0;
  salir=0;
}

int a2input(v10inputs *v,char *tex)
{
  int ret;
  trim(tex);
  ret=a2v10tipo(v->dato,v->tipo,v->formato,v->dec,tex);
  if (comparav10tipo(v->dato,v->ant,v->tipo)) v->modif=-1;
     else                                    v->modif=0;
  copiav10tipo(v->ant,v->dato,v->tipo,v->lvar);
  return(ret);
}

static void actualiza(v10inputs *v,int tx,int ty)
{
  char temp[MAXCADINP];
  if (marbloque && v->password==0) terminamarca(pbloque,0);
  opciones=v10formatdef|(v->formato&MARCAMILES);
  if (a2input(v,tex)) salir=1;
     else                  salir=0;
  strcpy(temp,tex);
  if (v->password) sustituyepass(temp);
  if (v->modif && v->password==0) {
     pmarca=0;
     pun=(unsigned)(irfin(tex)-tex);
     terminamarca(pult,0);
   }
  input2a(v,tex,0);
  poncolorv(v->w,CINPUTINAC);
  pad(tex,v->lvar);
  strcpy(temp,tex);
  if (v->password) sustituyepass(temp);
  if (seveventana(v,tx,ty)) imprimevp(v->w,v->posx+tx,v->posy+ty,temp,0,v->lpan);
  trim(tex);
  poncolorv(v->w,CNORMAL);
}

static void fininput(void)
{
  if (pbloque) {
     libera_menulista(pbloque);
     pbloque=NULL;
   }
  if (pmod) {
     libera_menulista(pmod);
     pmod=NULL;
   }
  if (pult) {
     libera_menulista(pult);
     pult=NULL;
   }
}

static int tratafechas(int pul,v10inputs *v,int tx,int ty)
{
  int ret=0;
  v10dates f=0;
  switch (pul) {
    case 'H': f=damedate();
              ret=1;
              break;
    case 'A': f=damedate()-1;
              ret=1;
              break;
    case 'M': f=damedate()+1;
              ret=1;
              break;
   }
  if (ret) {
     if (v->formato & F4ANO) jul2a(f,"DD-MM-Y.",tex);
        else                 jul2a(f,"DD-MM-YY",tex);
     poncursor(v,1,tx,ty);
   }
  return(ret);
}

int reposicionavraton(v10inputs *v,int tx,int ty)
{
  if (!enrango(mousepos.posy,v->posy+ty+v->w->y1,v->posy+ty+v->w->y1)) {
     return(-1);
   }
  if (!enrango(mousepos.posx,v->posx+tx+v->w->x1-1,v->posx+v->lpan+tx+v->w->x1)) {
     return(-1);
   }
  if (mousepos.posx<v->posx+tx+v->w->x1 && v->pcar>0) {
     v->pcar--;
     mousepos.posx++;
   }
  return(mousepos.posx-v->posx-tx-v->w->x1);
}

static int meteventanaclipboard(v10inputs *v)
{
  tex=bufferinput;
  input2a(v,tex,0);
  eliminasp(tex);
  mete_en_clipboard(tex);
  return(0);
}

int tratascrollv(v10inputs *v,int tx,int ty)
{
  if (mousepos.boton==BOTOND) {
     creamenuclipboard(mousepos.posx,mousepos.posy,1,0);
     if (hay_tecla()==cinse) {
        if (tecla()==cinse) {
           meteventanaclipboard(v);
         }
      }
     return(0);
   }
  if (!enrango(mousepos.posy,v->posy+ty+v->w->y1,v->posy+ty+v->w->y1)) {
     return(-1);
   }
  if (!enrango(mousepos.posx,v->posx+tx+v->w->x1-1,v->posx+v->lpan+tx+v->w->x1)) {
     return(-1);
   }
  if (mousepos.posx<=v->posx+tx+v->w->x1 && v->pcar>0) {
     v->pcar--;
   }
  if (mousepos.posx==v->posx+v->lpan+tx+v->w->x1-1 && v->pcar<v->lvar-v->lpan) {
     v->pcar++;
   }
  lpresenta(v,tx,ty);
  return(0);
}

int llinput(v10inputs *v,int tx,int ty)
{
 int pul=0;
 int maxpun = 0;
 int primera=1;
 v->pcar=0;
 if (pbloque==NULL) {
    pbloque=crea_menulista("INPUTB.PIC",MAX_ELEM);
    carga_menulista(pbloque);
    atexit(fininput);
  }
 if (pmod==NULL) {
    pmod=crea_menulista("INPUTM.PIC",MAX_ELEM);
    carga_menulista(pmod);
  }
 if (pult==NULL) {
    pult=crea_menulista("INPUTU.PIC",MAX_ELEM);
    carga_menulista(pult);
  }
 initinp(v);
 v->modif=-1;
 poncursor(v,1,tx,ty);
 if (ins) wset_cursor(v->w->hwnd,CURSORSOLIDO);
    else  wset_cursor(v->w->hwnd,CURSORNORMAL);
	
 while (!salir) {
   if (pun>maxpun) maxpun=pun;
   pul=tecla();
   switch(pul) {
      case scui:if (!marbloque && v->password==0) llmarca();
      case cui:if (pun) {
                  pun--;
                  poncursor(v,0,tx,ty);
                } 
               break;
      case scud:if (!marbloque && v->password==0) llmarca();
      case cud:if (pun<v->lvar) {
                  pun++;
                  poncursor(v,0,tx,ty);
                }
              break;
      case inse:ins=(!ins);
                if (ins) wset_cursor(v->w->hwnd,CURSORSOLIDO);
                   else  wset_cursor(v->w->hwnd,CURSORNORMAL);
                break;
      case dele:if (pun<v->lvar) {
                   strdel(tex,pun,1);
                   poncursor(v,1,tx,ty);
                }
                break;
	  case shome: if (marbloque==0) {
		             pmarca=pun;
					 marbloque=1;
				  }
      case home:pun=0;
                poncursor(v,0,tx,ty);
		        break;
	  case shend: if (marbloque==0) {
		             pmarca=pun;
					 marbloque=1;
				  }
      case end :pun=(unsigned)(irfin(tex)-tex);
                poncursor(v,0,tx,ty);
                break;
      case CTRL('C'):
      case cinse:if (marbloque && v->password==0) {
                        terminamarca(pbloque,1);
                        poncursor(v,1,tx,ty);
                      }
                  break;
      case copiatodo:  meteventanaclipboard(v);
                       break;
      case CTRL('V'):
      case sinse:if (v->password==0 && v->noinput==0) apilaclipboard(esv10tiponum(v->tipo),v->formato);
                  break;
      case sdele:
      case cdele:if (marbloque && v->noinput==0) {
                        if (pun>pmarca) {
                            strdel(tex,pmarca,pun-pmarca);
						    pun=pmarca;
                        }
                        if (pun<pmarca) strdel(tex,pun,pmarca-pun);
                        marbloque=0;
                        poncursor(v,1,tx,ty);
                      }
                  break;
      case CTRL('X'):if (marbloque && v->noinput==0) {
		                terminamarca(pbloque,1);
                        if (pun>pmarca) {
                            strdel(tex,pmarca,pun-pmarca);
						    pun=pmarca;
                        }
                        if (pun<pmarca) {
                            strdel(tex,pun,pmarca-pun);
                        }
                        marbloque=0;
                        poncursor(v,1,tx,ty);
                      }
                  break;
      case ccud:pun=(unsigned)(sigpal(&tex[pun])-tex);
                  poncursor(v,0,tx,ty);
                  break;
      case ccui:pun=(unsigned)(antpal(tex,&tex[pun])-tex);
                  poncursor(v,0,tx,ty);
                  break;
      case chome:if (v->noinput==0) {
                     strfill(tex,' ',v->lvar);
                     pun=0;
                     poncursor(v,1,tx,ty);
                 }
                 break;
      case cend :if (v->noinput==0) {
                     memset(&tex[pun],' ',v->lvar-pun);
                     poncursor(v,1,tx,ty);
                 }
                 break;
      case MARCA:if (marbloque && v->password==0) {
                    terminamarca(pbloque,1);
                    poncursor(v,1,tx,ty);
                  } else       llmarca();
                 break;
      case COPIA:{int ret;
                  if (v->noinput) break;
                  ret=saca_menu(pbloque,38,3);
                  if (ret>=0) {
                     copiamarca(pbloque,ret,v);
                     poncursor(v,1,tx,ty);
                   }
                  break;
                 }
      case COPIA1:{int ret;
                  if (v->noinput) break;
                   ret=saca_menu(pmod,38,3);
                   if (ret>=0) {
                      copiamarca(pmod,ret,v);
                      poncursor(v,1,tx,ty);
                    }
                   break;
                  }
      case COPIA2:{int ret;
                  if (v->noinput) break;
                   ret=saca_menu(pult,38,3);
                   if (ret>=0) {
                      copiamarca(pult,ret,v);
                      poncursor(v,1,tx,ty);
                    }
                   break;
                 }
      case MUEVERATON:if (v->tipo!=V10CADENA  && raton_encampo==0) break;
                      if (!marbloque) llmarca();
                      {int px;
                       px=reposicionavraton(v,tx,ty);
                       if (px>=0) {
                          pun=v->pcar+px;
                          poncursor(v,0,tx,ty);
                        }
                       }
                       break;
      case MOUSEPOS:if (mousepos.boton==BOTONI) {
                       int px;
                       if (marbloque && v->password==0) {
                          terminamarca(pbloque,0);
                          poncursor(v,1,tx,ty);
                        }
                       px=reposicionavraton(v,tx,ty);
                       if (px>=0) {
                          pun=v->pcar+px;
                          if (raton_encampo==0) pun=0;
                          poncursor(v,1,tx,ty);
                        } else {
                          actualiza(v,tx,ty);
                        }
                       if (mousepos.action==DOBLECLICK) {
                           actualiza(v,tx,ty);
                           salir=1;
                       }
                      }
                     break;
      case MOUSEPOSD:if (mousepos.boton==BOTOND) {
                        if (!enrango(mousepos.posy,v->posy+ty+v->w->y1,v->posy+ty+v->w->y1) || !enrango(mousepos.posx,v->posx+tx+v->w->x1-1,v->posx+v->lpan+tx+v->w->x1)) {
                           actualiza(v,tx,ty);
                         } else {
                           if (v->password==0) creamenuclipboard(mousepos.posx,mousepos.posy,marbloque,1);
                         }
                      }
                     break;
      default:if (pul>255 || pul==10) {
                 actualiza(v,tx,ty);
                 break;
               }
              if (v->formato&FORMATOUPPER) pul=pasacarmay(pul);
              if (v->formato&FORMATOLOWER) pul=pasacarmin(pul);
              if (v->tipo==V10INT || v->tipo==V10SHORT ||v->tipo==V10LONG ||
                  v->tipo==V10UINT || v->tipo==V10USHORT ||v->tipo==V10ULONG ||
                  v->tipo==V10BYTE || v->tipo==V10FECHA || v->tipo==V10HORA) pul=pasacarmay(pul);
              switch (pul) {
                     case back:if (pun) {
                                  strdel(tex,--pun,1);
                                  poncursor(v,1,tx,ty);
                                }
                               break;
                     case tab:
					 case lf:
                     case  cr:
                     case esc:actualiza(v,tx,ty);
                              if (!salir) {
                                 initinp(v);
                                 poncursor(v,1,tx,ty);
                               }
                              break;
                      case ' ':if (v->noinput) break;
                               if (v->tipo!=V10CADENA) {
                                  memset(&tex[pun],' ',v->lvar-pun);
                                  poncursor(v,1,tx,ty);
                                  break;
                                }
                      default: if (v->noinput) break;
                               if (valida(pul,v)) {
                                  if (v->tipo!=V10CADENA) {
                                     if ( primera) {
                                        memset(&tex[pun],' ',v->lvar-pun);
                                        poncursor(v,1,tx,ty);
                                      }
                                     if (opciones&COMADECIMAL) {
                                        if (pul=='.') pul=',';
                                      } else {
                                        if (pul==',') pul='.';
                                      }
                                   }
                                  if (v->tipo==V10FECHA) {
                                     if (tratafechas(pul,v,tx,ty)) break;
                                   }
                                  if (pun<v->lvar) {
                                     if (ins) {
                                        strinserta(tex,pun,1);
                                        tex[pun++]=(char)pul;
                                        poncursor(v,1,tx,ty);
                                      } else {
                                        tex[pun++]=(char)pul;
                                        poncursor(v,1,tx,ty);
                                      }
                                   }
                                  if (pun==v->lvar && v->autoenter) {
                                     actualiza(v,tx,ty);
                                     if (!salir) {
                                        initinp(v);
                                        poncursor(v,1,tx,ty);
                                      } else pul=cr;
                                   }
                                }
                  }
	   }
     if (v->tipo==V10CADENA || (pul!=MUEVERATON && pul!=MOUSEPOS && pul!=MOUSEPOSD)) primera=0;
    }
   wset_cursor(v->w->hwnd,SINCURSOR);
   return(pul);
}

void llpresenta(v10inputs *v,int tx,int ty,int tinta)
{
  if (v->invisible) return;
  if (v->posx+tx+v->lpan<=0) return;
  if (v->posx+tx>=WANCHO(v->w)) return;
  if (v->posy+ty<0||v->posy+ty>=WALTO(v->w)) return;
  if (v->pcar<0) v->pcar=0;
  tex=bufferinput;
  input2a(v,tex,0);
  if (v->formato&FORMATONULL) *tex=0;
  pad(tex,v->lvar);
  if (v->password) sustituyepass(tex);
  poncolorv(v->w,tinta);
  tex+=v->pcar;
  if (v->posx+tx<0) {
     imprimevp(v->w,0,v->posy+ty,tex-tx-v->posx,0,v->lpan+tx+v->posx);
   } else {
      if (v->posx+tx+v->lpan>=WANCHO(v->w)) imprimevp(v->w,v->posx+tx,v->posy+ty,tex,0,WANCHO(v->w)-tx-v->posx);
         else imprimevp(v->w,v->posx+tx,v->posy+ty,tex,0,v->lpan);
     }
  trim(tex);
  poncolorv(v->w,CNORMAL);
}

void STDlpresenta(v10inputs *v,int tx,int ty)
{
   v->pcar=0;
   if (v->color>0) {
	   llpresenta(v,tx,ty,v->color);
   } else {
     if (v->enter) llpresenta(v,tx,ty,CINPUTINAC);
        else       llpresenta(v,tx,ty,CNOENTER);
   }
}
