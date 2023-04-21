/*
* Módulo : V10TOOLTIP.C
* Objeto:  Gestion de tooltips
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"


static HBITMAP hbmpsave;
static RECT rcsave;	
static POINT pti,ptf;
#define TOOLTIP_TIMER		1

long v10tiempotooltip=200;
void (*funciontooltip)(mouseposs *raton); 


static int v10haytooltip(void)
{
	  return(NULL !=hbmpsave);
}

static void CALLBACK ctltooltip(HWND  hwnd,UINT  uMsg,UINT  idEvent,DWORD  dwTime)
{
    if (ptf.x==pti.x && ptf.y==pti.y) {
       if (FALSE==v10haytooltip()){
          if (MOUSEPOSMV != hay_tecla()){
             extrawins *t=dameextrawin(hwnd);
             mousepos.boton=0;
             mousepos.action=0;
             mousepos.posx=pti.x/t->anchofont+t->origenx;
             mousepos.posy=pti.y/t->altofont+t->origeny;
             mousepos.winx=pti.x;
             mousepos.winy=pti.y;
             mousepos.hwnd=hwnd;
            if (funciontooltip) funciontooltip(&mousepos);
          }
       }
    } else {
      pti.x=ptf.x ;
      pti.y=ptf.y;
    }
}      

void *ponfunciontooltip(void *funcion)
{
    void *ret=funciontooltip;
    funciontooltip=funcion;
    return(ret);
}

void v10limpiatooltip(HWND hwnd)
{
    HDC hdcsave;  
    extrawins *t=dameextrawin(hwnd);
    if (t==0) return;
	  if (!hbmpsave) return;
    t->hdc=GetDC(hwnd);
    hdcsave=CreateCompatibleDC(t->hdc);
    SelectObject(hdcsave,hbmpsave);
	BitBlt(t->hdc,rcsave.left,rcsave.top,abs(rcsave.right-rcsave.left),abs(rcsave.bottom-rcsave.top),
    				hdcsave,0,0,SRCCOPY);
    DeleteDC(hdcsave);
    DeleteObject(hbmpsave);
    hbmpsave=NULL; 
	pti.x=pti.y=0;
}


int v10tooltip(mouseposs *raton,char *texto)
{
    int piezas,maximox,maximoy,m;
    int oldmode;
    COLORREF clr;
    SIZE size;
    HDC hdc,hdcsave;
    HBRUSH hbr,hbrold;
    RECT rc,rctext;
	POINT pt;
	HWND hwnd;
    defvents *dv;
    int i;
    char *traducido;
    char buffer[MAXCADENA];
    i=damepaleta("TOOLTIP");
    dv=defvent+i;
    if (hbmpsave) return(FALSE);
	if (!texto) return(FALSE);
    traducido=v10translate(texto);
	hwnd=raton->hwnd;
    if (NULL==(hdc=GetDC(hwnd))) return(FALSE);
	if (NULL== (hdcsave=CreateCompatibleDC(hdc))) {
       ReleaseDC(hwnd,hdc);
       return(FALSE);
    }
    piezas=numpieces(traducido ,"\n" );
    for (m=maximox=maximoy=0;m<piezas;m++) {
    	piece(traducido,buffer,"\n" ,m+1);
	    if (*buffer==0) continue;
        GetTextExtentPoint32(hdc,buffer,strlen(buffer),&size);
        maximox= maximox>size.cx ? maximox : size.cx;
        maximoy= maximoy>size.cy ? maximoy : size.cy;
     }
    if (maximox ==0 || maximoy==0) {	
       ReleaseDC(hwnd,hdc);
	   DeleteDC(hdcsave);
	   return(FALSE);
	 }
    maximoy *=piezas;
    pt.x=raton->winx;pt.y=raton->winy;
    rctext.left=max(0,pt.x +size.cy );
    rctext.top =max(0,pt.y + size.cy);
    rctext.right=rctext.left + maximox;
    rctext.bottom = rctext.top+maximoy;
    GetClientRect(hwnd,&rc);
    if (rctext.right >rc.right) {
       m=(rctext.right-rctext.left)+size.cy;
       if (rctext.left>=m) {
    	  rctext.left -= m;
          rctext.right-=m;
        } else {
          rctext.left=max(0,pt.x-maximox/2);
          rctext.right=min(rc.right,pt.x+maximox/2);
          rctext.top+=size.cy;
          rctext.bottom+=size.cy;
        }
     }
    if (rctext.bottom>rc.bottom) {
        rctext.top=pt.y-size.cy-maximoy;
        rctext.bottom=rctext.top+maximoy;
     }
    rcsave=rctext;
    hbmpsave=CreateCompatibleBitmap(hdc,rctext.right-rctext.left,rctext.bottom-rctext.top);
    SelectObject(hdcsave,hbmpsave);
    BitBlt(hdcsave,0,0,(rctext.right-rctext.left),(rctext.bottom-rctext.top),hdc,rctext.left,rctext.top,SRCCOPY);
    hbr=CreateSolidBrush(dv->t.t[1].papel);
    hbrold=SelectObject(hdc,hbr);
    FillRect(hdc,&rctext,hbr);
    oldmode=SetBkMode(hdc,TRANSPARENT);
    clr=SetTextColor(hdc,dv->t.t[1].tinta);
	{char *ptr;
	for (ptr=traducido;*ptr;ptr++) *ptr=pasacharoem(*ptr);
	}
    DrawText(hdc,traducido,strlen(traducido),&rctext,DT_LEFT);
    SetTextColor(hdc,clr);
    SelectObject(hdc,hbrold);
    DeleteObject(hbr);
    SetBkMode(hdc,oldmode);
    ReleaseDC(hwnd,hdc);
    DeleteDC(hdcsave);
    return(TRUE);
}
           

void creatooltip(HWND hwnd)
{
    if (hwnd==NULL) return;
    if (v10tiempotooltip>0) SetTimer(hwnd,TOOLTIP_TIMER,v10tiempotooltip*10,(TIMERPROC)ctltooltip);
}

void destruyetooltip(HWND hwnd)
{
    if (hwnd==NULL) return;
    KillTimer(hwnd,TOOLTIP_TIMER);
}

void mueveratontooltip(HWND hwnd,int x,int y)
{
    if (TRUE==v10haytooltip()) v10limpiatooltip(hwnd);
    ptf.x=x;
    ptf.y=y;
}