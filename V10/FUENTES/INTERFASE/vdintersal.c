#include "vdinterfase.h"


static int dameformatocampo(vdinterfaselins *lin,char *donde)
{
    switch (*lin->tipodato) {
        case 'C': padcar(donde,lin->longitud,'_');
                  return(0);
        case 'N': padcar(donde,lin->longitud-lin->decimales,'#');
                  if (lin->decimales) {
                      strcat(donde,".");
                      padcar(donde+strlen(donde),lin->decimales,'#');
                  }
                  return(0);
    }
    return(-1);
}

void carganombreinterfase(bloques *b,char *tipointerfase,char *formato)
{
    piece(b->nombre,tipointerfase," ",1);
    piece(b->nombre,formato," ",2);
}

static char *leeinterfases(bloques *b,char *funcion,char *param)
{
    char tipointerfase[LTIPOINTERFASE],formato[LFORMATO],interfase[MAXPATH];
    vdinterfasecabs vdcab;
    vdinterfaselins vdlin;
    char analiza[MAXCADENA]="";
    int ret,i;
    for (i=1;i<=numpieces(param,";");i++) {
        piece(param,interfase,";",i);
        piece(interfase,tipointerfase," ",1);
        piece(interfase,formato," ",2);
        ret=INTCselvdinterfasecab(tipointerfase,formato,&vdcab);
        if (ret) {
            v10log(LOGERROR,"No existe la cabecera de interfase %s %s\n",tipointerfase,formato);
        }
        ret=INTLbuscatipoformato(tipointerfase,formato,&vdlin);
        while (ret==0) {
            char formato[MAXCADENA]="";
            if (damecampo(b,vdlin.campo)<0) {
                dameformatocampo(&vdlin,formato);
                sprintf(analiza+strlen(analiza),"CAMPO=%s,OCULTO,AUXILIAR,\"%s\"\n",vdlin.campo,formato);
            }
            ret=INTLnexttipoformato(&vdlin);
        }
    }
    if (!es_blanco(analiza)) creabuffercadena(analiza);
    return(0);
}

static int creacamposinterfase(bloques *b)
{
    char tipointerfase[LTIPOINTERFASE],formato[LFORMATO];
    vdinterfasecabs vdcab;
    vdinterfaselins vdlin;
    char analiza[MAXCADENA]="";
    int ret;
    if (damecampo(b,ERRORINTER)<0) {
        sprintf(analiza+strlen(analiza),"CAMPO="ERRORINTER",AUXILIAR,OCULTO,\"@L@@@@@@@@\"\n");
    }
    if (damecampo(b,SALIDAINTER)<0) {
        sprintf(analiza+strlen(analiza),"CAMPO="SALIDAINTER",AUXILIAR,OCULTO,\"_409600\"\n");
    }
    if (damecampo(b,SECUENCIALINTER)<0) {
        sprintf(analiza+strlen(analiza),"CAMPO="SECUENCIALINTER",AUXILIAR,OCULTO,\"_4096\"\n");
    }
    carganombreinterfase(b,tipointerfase,formato);
    ret=INTCselvdinterfasecab(tipointerfase,formato,&vdcab);
    if (ret) {
        v10log(LOGDEBUG,"No existe la cabecera de interfase %s %s\n",tipointerfase,formato);
    }
    ret=INTLbuscatipoformato(tipointerfase,formato,&vdlin);
    while (ret==0) {
        char formato[MAXCADENA]="";
        if (damecampo(b,vdlin.campo)<0) {
            dameformatocampo(&vdlin,formato);
            sprintf(analiza+strlen(analiza),"CAMPO=%s,OCULTO,AUXILIAR,\"%s\"\n",vdlin.campo,formato);
        }
        ret=INTLnexttipoformato(&vdlin);
    }
    if (!es_blanco(analiza)) creabuffercadena(analiza);
    return(0);
}

int ejecutainterfaseparam(char *nombre,char *param)
{
    forms *f;
    f=leeforminter(nombre,"");
    if (f==NULL) return(-1);
    asignavariables(f->b[0],param);
    trataforminter(f);
    liberaform(f);
    return(0);
}

static void initinterfase(void)
{
    static int init=0;
    if (init) return;
    init=1;
    initform();
    funcionproteccion=dameproteccionvd;
    inittriguser();
    inittrigersform("I");
    leedefines("VDST.H");
    damecaracextracampo=leedefectocampo;
    damedefaulttabla=creacamposinterfase;
    extraparser=leeinterfases;
    inittrigerinter();
}

VDEXPORT void interfasesalida(procesos *proceso)
{
    char pantalla[MAXPATH],parametro[MAXPATH];
    initinterfase();
    ejecutaimmediato("BEGIN VDUSER.SETUSER('INTERFASE');END;");
    piece(proceso->proc.param,pantalla,"#",1);
    piece(proceso->proc.param,parametro,"#",2);
    ejecutainterfaseparam(pantalla,parametro);
}

