/*
* Módulo : V10FORVARIABLE.C                                             
* Objeto:  Funciones auxiliares para la gestion de campos de form como variables
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"

int bcampo2aex(bloques *b,char *ncampo,char *tex,int convierte,int formato)
{ 
    int opciones;
    char base[MAXNOMBREV10];
    int indicador;
    fcampos *c;
    void *ptr;
    indicador=damebase(ncampo,base);
    c=b->c+damecamposeguro(b,base);
    if (formato<0) opciones=c->format;
       else        opciones=formato;
    if (c->conv2bd!=NULL && convierte) {
        copiacampo(b,c,c->datoconv);
        FORM(b)->cinput=c;
        c->conv2bd->fun(b,c->conv2bd);
        ptr=c->datoconv;
    } else {
        if (indicador>0) ptr=direccampoind(b,c-b->c,indicador);
        else ptr=direccampoptr(b,c);
    }
    v10tipo2a(ptr,c->tipo,dameindcampo(b,c,"LPAN"),opciones,dameindcampo(b,c,"DECIMALES"),tex,0);
    return(0);
}

int bcampo2a(bloques *b,char *ncampo,char *tex,int convierte)
{
    return(bcampo2aex(b,ncampo,tex,convierte,-1));
}
int a2bcampo(bloques *b,char *ncampo,char *tex)
{ 
  fcampos *c=b->c+damecamposeguro(b,ncampo);
  switch(c->tipo) {
    case V10INT    :*(int *)direccampoptr(b,c)=atoi(tex);
                    break;
    case V10UINT   :*(unsigned int *)direccampoptr(b,c)=atoi(tex);
                    break;
    case V10SHORT  :*(short *)direccampoptr(b,c)=(short)atol(tex);
                    break;
    case V10USHORT :*(unsigned short *)direccampoptr(b,c)=(short)atol(tex);
                    break;
    case V10LONG   :*(long *)direccampoptr(b,c)=atol(tex);
                    break;
    case V10ULONG  :*(unsigned long *)direccampoptr(b,c)=atol(tex);
                    break;
    case V10FLOAT  :*(float *)direccampoptr(b,c)=(float)v10dval(tex,v10formatdef);
                    break;
    case V10DOUBLE :*(double *)direccampoptr(b,c)=v10dval(tex,v10formatdef);
                    break;
    case V10CHAR   :*(char *)direccampoptr(b,c)=*tex;
                    break;
    case V10BYTE   :*(char *)direccampoptr(b,c)=(char)atoi(tex);
                    break;
    case V10CADENA :strcpy(direccampoptr(b,c),tex);
                    break;
    case V10FECHA  :a2v10tipo(direccampoptr(b,c),c->tipo,0,10,tex);
                    break;
    case V10HORA   :*(v10horas *)direccampoptr(b,c)=atol(tex);
                    break;
    default        :final(("Tipo no definido en campo %s",c->nombre));
                    break;
            }
   if (c->change) {
      *FERROR(b,c)=ejecutaftriger(b,PPOSTCHANGE,c->change,c);
    }
  return(0);
}

static void duplicacomillas(char *cadena)
{
    char *aux=cadena,*fin;
    while ((fin=strchr(aux,'\''))!=NULL) {
        memmove(fin+1,fin,strlen(fin)+1);
        aux=fin+2;
    }
}
 
static int sustituyevariablesgen(bloques *b,char *origen,char *destino,int comillas,int convierte)
{
    char *ptro,*ptrodest;
    char variable[MAXNOMBREV10];
    ptro=v10translate(origen);
    ptrodest=destino;
    while (*ptro) {
        while (*ptro && *ptro!=':') {
            if (*ptro=='\'') {
                char *poscom;
                if (ptro[1]!='\'') {
                    *ptrodest++=*ptro;
                    poscom=ptro++;
                    while (*ptro && (*ptro!='\'')) *ptrodest++=*ptro++;
                    if (*ptro==0) {
                       if (!v10versionweb) 
                            mensajefcm(10,"Falta cerrar comillas %s",poscom);
                       break;
                    }
                } else ptro++;
            }
            *ptrodest++=*ptro;
            ptro++;
        }
        if (*ptro) {
            char *aux=variable;
            while (strchr(" ,;<>()+-*%&/.:[]{}$#@|!=\\\n\r",*++ptro)==NULL) {
                if ((*aux++=*ptro)==0) break;
            }
            *aux=0;
            if (aux!=variable) {
                char base[MAXNOMBREV10];
                damebase(variable,base);
                if (damecampo(b,base)>=0) {
                    if (comillas) *ptrodest++='\'';
                    bcampo2aex(b,variable,ptrodest,convierte,-1);
                    eliminasp(ptrodest);
                    if (v10usaansi) v10ansitooem(ptrodest,ptrodest); //(1)
                    if (comillas) duplicacomillas(ptrodest);
                    ptrodest+=strlen(ptrodest);
                    if (comillas) *ptrodest++='\'';
                    *ptrodest=0;
                } else {
					*ptrodest++ = ':';
                    strcpy(ptrodest,variable);
                    ptrodest+=strlen(ptrodest);
                }
            } else {
                *ptrodest++=':';
                *ptrodest=0;
            }
        }
    }
    *ptrodest=0;
    return(0);
}

int sustituyevariables(bloques *b,char *origen,char *destino)
{
    int ret;
    ret=sustituyevariablesgen(b,origen,destino,1,1);
    return(ret);
}

int sustituyevariablessc(bloques *b,char *origen,char *destino)
{
    int ret;
    ret=sustituyevariablesgen(b,origen,destino,0,1);
    return(ret);
}

void asignavariablesext(bloques *b,char *linea,int err)
{
    char *aux,*prin,*fin,achar,*igual;
    while (!es_blanco(linea)) {
        for (aux=linea;*aux!=0 && *aux!='=';aux++);
        if (*aux==0) {
            mensajefcm(10,"Asignacion sin terminar %s",linea);
            return;
        }
        igual=aux;
        *aux=0;
        aux++;
        if (*aux=='\'') {
            prin=++aux;
            while (*aux!=0 && (*aux!='\'' || aux[1]=='\'')) {
                if (*aux=='\'') strcpy(aux,aux+1);
                aux++;
            }
            if (*aux==0) {
                mensajefcm(10,"Cadena sin terminar %s en asignacion",linea);
                return;
            }
            fin=aux;
            aux++;
        } else {
            prin=aux;
            while (*aux!=0 && *aux!=' ') aux++;
            fin=aux;
        }
        achar=*fin;
        *fin=0;
        if (err) {
            a2bcampo(b,linea,prin);
        } else {
            if (damecampo(b,linea)>=0) {   
                a2bcampo(b,linea,prin);
            }
        }
        *fin=achar;
        *igual='=';
        while (*aux==' ') aux++;
        linea=aux;
    }
}

void asignavariables(bloques *b,char *linea)
{
    asignavariablesext(b,linea,1);
}