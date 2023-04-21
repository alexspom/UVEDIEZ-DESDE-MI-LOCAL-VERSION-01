/*
* Módulo : V10FORSELTABLA.C
* Objeto:  Permite seleccionar datos en una select
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"

#define MAXDISPCADENA 20
#define MAXPRECDOUBLE 14
#define MAXSCALEDOUBLE 6
static char *dameformatooracampo(v10cursors *cur,campooras *c)
{
    static char formato[MAXCADENA];
    switch (c->oratipo) {
        case OCICHAR: if (c->oralen>MAXDISPCADENA) sprintf(formato,"_%ld______________________",c->oralen);
                        else                      strfill(formato,'_',c->oralen);
                        break;
        case OCINUMBER: if (strncmp(c->nombre,"FEC",3)==0) {
                           sprintf(formato,"¿D-MM-YY");
                           break;
                        }
                        if (c->prec==0 && c->scale==0){
                           c->prec=MAXPRECDOUBLE;
                           c->scale=MAXSCALEDOUBLE;
                        }
                        if (c->prec<8 && c->scale==0)  {
                           strfill(formato,'@',c->prec);
                           if (c->prec>1) formato[1]='L';
                        } else {
                            strfill(formato,'#',c->prec+(c->scale!=0?1:0));
                            if (c->prec>1) formato[1]='L';
                            if (c->scale) formato[strlen(formato)-c->scale-1]='.';
                        }
                        break;
    }
    return(formato);
}
//OJO UNICODE
static int fselmultiple(bloques *b,ftrigers *ft)
{
    char destino[MAXCADENA];
    char varrango[MAXCADENA],varorigen[MAXCADENA],select[MAXCADENA],titulo[MAXCADENA],ncampos[MAXCADENA];
    tpixels *copia;
    forms *antform=formglobal;
    v10cursors *cur;
    int nc;
    dameparametro(b,ft,0,V10CADENA,varrango);
    dameparametro(b,ft,1,V10CADENA,varorigen);
    dameparametro(b,ft,2,V10CADENA,select);
    dameparametro(b,ft,3,V10CADENA,titulo);
    dameparametro(b,ft,4,V10CADENA,ncampos);
    cur=parsecursornombre(select,"SELMULTIPLE");
    if (cur==NULL) {
        mensajefcm(10,"No puedo abrir select %s",select);
        return(-1);
    }
    sprintf(destino,"CAMPO=%s,AUXILIAR,OCULTO,\"_1024\"\nCAMPO=ALGUNONO,OCULTO,\"_\"\nCAMPO=ALGUNOSI,OCULTO,\"_\"\n",varrango);
    sprintf(destino+strlen(destino),"BEGINBLOQUEPAN=SELMULT %s\n",titulo);
    sprintf(destino+strlen(destino),"%s\n",ncampos);
    for (nc=0;nc<cur->ndef;nc++) {
        sprintf(destino+strlen(destino),"%s ",dameformatooracampo(cur,cur->def+nc));
    }
    sprintf(destino+strlen(destino),"_\n|\nSOLOQUERY\nREGPAG=20\nTQUERY\nPQUERY\nPOSTQUERY=FEJECUTA(\"CPONSEL\",\"No puedo poner a seleccionar\",FMODIFICA,\"\")\n");
    sprintf(destino+strlen(destino),"PRECOMMIT=FEJECUTA(\"CBORRARANGO\",\"No puedo borrar rango\")\n");
    sprintf(destino+strlen(destino),"PREUPDATE=FEJECUTA(\"CACTRANGO\",\"No puedo poner en rango\")\n");
    sprintf(destino+strlen(destino),"POSTCOMMIT=FEJECUTA(\"CTERMINARANGO\",\"No puedo terminar rango\",FPULSATECLAS(\"F10\"),\"\")\n");
    sprintf(destino+strlen(destino),"SELECT=%s;\n",select);
    sprintf(destino+strlen(destino),"CAMPO=%s,AUXILIAR,VIRTUAL,OCULTO\n",varrango);
    for (nc=0;nc<cur->ndef;nc++) {
        sprintf(destino+strlen(destino),"CAMPO=%s\n",cur->def[nc].nombre);
    }
    sprintf(destino+strlen(destino),"CAMPO=SEL,AUXILIAR,UPPER,POSTCHANGE=FVERIFICA(\"SN\")\n"
                                    "CAMPO=ALGUNONO,VIRTUAL,AUXILIAR,OCULTO\n"
                                    "CAMPO=ALGUNOSI,VIRTUAL,AUXILIAR,OCULTO\n");
    sprintf(destino+strlen(destino),"CURSOR=CBORRARANGO SELECT '' %s,'' ALGUNONO,'' ALGUNOSI FROM DUAL;\n",varrango);
    sprintf(destino+strlen(destino),"CURSOR=CPONSEL SELECT DECODE(VD.CONTIENE(:%s,:%s),1,'S','N') SEL FROM DUAL;\n",varrango,varorigen);
    sprintf(destino+strlen(destino),"CURSOR=CACTRANGO SELECT :%s||DECODE(:%s,NULL,NULL,DECODE(:SEL,'S',',',''))||DECODE(:SEL,'S',:%s,'') %s,\n"
                                                       " NVL(:ALGUNONO,DECODE(:SEL,'N','S','')) ALGUNONO,\n"
                                                       " NVL(:ALGUNOSI,DECODE(:SEL,'S','S','')) ALGUNOSI FROM DUAL;\n",varrango,varrango,varorigen,varrango);

    sprintf(destino+strlen(destino),"CURSOR=CTERMINARANGO SELECT DECODE(:ALGUNONO,NULL,NULL,DECODE(:ALGUNOSI,NULL,'-',:%s)) %s"
                                                           " FROM DUAL;\n",varrango,varrango);
    sprintf(destino+strlen(destino),"ENDBLOQUE\n");
    liberacursor(cur);
    formglobal=leeformcadena("SELMULTIPLE",destino,FWINDOWS);
    if (formglobal) {
        char destino[MAXCADENA];
        rellenadefault();
        copia=salvapantallad(0,0,COLUMNASPANTALLA,LINEASPANTALLA);
        bcampo2a(b,varrango,destino,1);
        a2bcampo(formglobal->b[0],varrango,destino);
        formglobal->preguntar=1;
        finputform(formglobal);
        bcampo2a(formglobal->b[0],varrango,destino,1);
        a2bcampo(b,varrango,destino);
        liberaform(formglobal);
        recuperapantallad(0,0,COLUMNASPANTALLA,LINEASPANTALLA,copia);
    }
    formglobal=antform;
    return(0);
}

static int fselsimple(bloques *b,ftrigers *ft)
{
    char destino[MAXCADENA];
    char varorigen[MAXCADENA],select[MAXCADENA],titulo[MAXCADENA],ncampos[MAXCADENA];
    tpixels *copia;
    forms *antform=formglobal;
    v10cursors *cur;
    int nc;
    dameparametro(b,ft,0,V10CADENA,varorigen);
    dameparametro(b,ft,1,V10CADENA,select);
    dameparametro(b,ft,2,V10CADENA,titulo);
    dameparametro(b,ft,3,V10CADENA,ncampos);
    cur=parsecursornombre(select,"SELMULTIPLE");
    if (cur==NULL) {
        mensajefcm(10,"No puedo abrir select %s",select);
        return(-1);
    }
    sprintf(destino,"BEGINBLOQUEPAN=SELSIMPLE %s\n",titulo);
    sprintf(destino+strlen(destino),"%s\n",ncampos);
    for (nc=0;nc<cur->ndef;nc++) {
        sprintf(destino+strlen(destino),"%s ",dameformatooracampo(cur,cur->def+nc));
    }
    trim(destino);
    sprintf(destino+strlen(destino),"\n|\nSOLOQUERY\nREGPAG=20\nPQUERY\n");
    sprintf(destino+strlen(destino),"SELECT=%s;\n",select);
    for (nc=0;nc<cur->ndef;nc++) {
        sprintf(destino+strlen(destino),"CAMPO=%s\n",cur->def[nc].nombre);
    }
    sprintf(destino+strlen(destino),"ENDBLOQUE\n");
    liberacursor(cur);
    formglobal=leeformcadena("SELSIMPLE",destino,FWINDOWS);
    if (formglobal) {
        char destino[MAXCADENA];
        rellenadefault();
        copia=salvapantallad(0,0,COLUMNASPANTALLA,LINEASPANTALLA);
        formglobal->preguntar=1;
        finputform(formglobal);
        bcampo2a(formglobal->b[0],varorigen,destino,1);
        a2bcampo(b,varorigen,destino);
        liberaform(formglobal);
        recuperapantallad(0,0,COLUMNASPANTALLA,LINEASPANTALLA,copia);
    }
    formglobal=antform;
    return(0);
}

void initformseltabla(void)
{
    declaratriger("FSELMULTIPLE",fselmultiple,NULL);
    declaratriger("FSELSIMPLE",fselsimple,NULL);
}
