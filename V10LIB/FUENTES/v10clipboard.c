/*
* Módulo : V10CLIPBOARD.C
* Objeto:  Tratamiento del clipboard de WINDOWS
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"


void mete_en_clipboard(char *cadena)
{
  HGLOBAL hmem;
  char *ptr;
  char micadena[MAXCADENA];
  OpenClipboard(hwnddefecto);
  EmptyClipboard();
  hmem=GlobalAlloc(GHND,strlen(cadena)+1);
  ptr=GlobalLock(hmem);
  if (v10usaansi==0) v10oemtoansi(cadena,micadena);
  else strcpy(micadena,cadena);
  strcpy(ptr,micadena);
  GlobalUnlock(hmem);
  SetClipboardData(CF_TEXT,hmem);
  CloseClipboard();
}

void apilaclipboard(int estiponum,int formato)
{
  HGLOBAL hmem;
  char *ptr,*p1,p2[2];
  OpenClipboard(hwnddefecto);
  hmem=GetClipboardData(CF_TEXT);
  if (hmem) {
     ptr=GlobalLock(hmem);
     for (p1=ptr;*p1;p1++) {
         *p2=*p1;p2[1]=0;
         if (v10usaansi==0) v10ansitooem(p2,p2);
         if (estiponum) {
             if (formato & COMADECIMAL) {
                 if (*p2=='.') continue;
             } else {
                 if (*p2==',') continue;
             }
         }
         encolatecla(*p2);
     }
     GlobalUnlock(hmem);
   }
  CloseClipboard();
}
