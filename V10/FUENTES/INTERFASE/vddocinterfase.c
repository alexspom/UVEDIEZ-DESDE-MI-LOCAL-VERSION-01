#include "vdinterfase.h"

#define cdocuminter "SELECT ORDEN \"P.\",CAMPOHOST HOST,CAMPO V10,DESCCAMPO \"DESC.\",LONGITUD \"L.\",TIPODATO \"T.\",DECIMALES DEC,FORMATEO F,DEFECTO"\
    " FROM VDINTERFASELIN WHERE TIPOINTERFASE='%s' AND FORMATO='%s'"\
                            " ORDER BY ORDEN"
void documentainterfase(IDispatch *id,IDispatch *doc,char *tipointerfase,char *formato)
{
    char select[MAXCADENA],titulo[MAXCADENA],comentario[MAXCADENA];
    vdinterfasecabs vdcab;
    int ret;
    ret=INTCselvdinterfasecab(tipointerfase,formato,&vdcab);
    if (ret) {
        v10log(LOGERROR,"No existe interfase %s %s\n",tipointerfase,formato);
        return;
    }
    sprintf(comentario,"\nFichero de interfase %s Extensión %s\n",vdcab.preffichero,vdcab.extfichero);
    sprintf(select,cdocuminter,tipointerfase,formato);
    sprintf(titulo,"INTERFASE %s %s",tipointerfase,formato);    
    pasaselectword(id,doc,select,"Tabla interfase","Título 1",titulo,comentario);
}

void documentatodasinterfases(IDispatch *id,IDispatch *doc)
{
    int ret;
    vdinterfasecabs vdcab;
    ret=INTCbuscaraiz(&vdcab);
    while (ret==0) {
        documentainterfase(id,doc,vdcab.tipointerfase,vdcab.formato);
        ret=INTCnextraiz(&vdcab);
    }
}

int abreword(char *plantilla,IDispatch **id,IDispatch **doc)
{
    VARIANTARG varg1,varg2;
    *id=startole("word.Application",1);
    if (*id==NULL) {
        mensajefcm(10,"Aplicacion %s no instalada","word");
        finole();
        return(-1);
    }
    getproperty(*id, "Documents", &varg1,-1);
    if (!es_blanco(plantilla)) {
        invocametodo(varg1.pdispVal, "Add", &varg2,"TEMPLATE",V10CADENA,plantilla,-1);
    } else {
        invocametodo(varg1.pdispVal, "Add", &varg2,-1);
    }
    ReleaseVariant(&varg1);
    *doc = varg2.pdispVal;
    return(0);
}

#define CSELCOMTABLA " SELECT COMMENTS FROM USER_TAB_COMMENTS WHERE TABLE_NAME=:TABLA"
static v10cursors *v10selcomtabla;
typedef struct {
    char tabla[MAXPATH];
    char comentario[MAXPATH];
} comtablas;
static comtablas comt;
void documentatabla(char *tabla, IDispatch *id, IDispatch *doc)
{
    char titulo[MAXPATH], comglobal[MAXPATH];
    char select[MAXSQL];
    sprintf(titulo, "Tabla %s", tabla);
    if (v10selcomtabla == NULL) {
        v10selcomtabla = abrecursor(CSELCOMTABLA);
        definetodo(v10selcomtabla, comt.comentario, sizeof(comt.comentario), V10CADENA, NULL);
        bindtodo(v10selcomtabla, "TABLA", comt.tabla, sizeof(comt.tabla),V10CADENA, NULL);
    }
    strcpy(comt.tabla, tabla);
    *comt.comentario = 0;
    ejefetchcursor(v10selcomtabla);
    sprintf(select, "SELECT TA.COLUMN_NAME Columna,DECODE(DATA_TYPE,'VARCHAR2','ALFA','NUM') Tipo, "
                          " DECODE(DATA_TYPE,'VARCHAR2',TO_CHAR(DATA_LENGTH),TO_CHAR(DATA_PRECISION)||DECODE(DATA_SCALE,0,'','.'||DATA_SCALE)) Lon, "
                          " CO.COMMENTS Comentario"
                      " FROM USER_TAB_COLUMNS TA, USER_COL_COMMENTS CO "
                      " WHERE TA.TABLE_NAME='%s' AND TA.TABLE_NAME=CO.TABLE_NAME AND TA.COLUMN_NAME=CO.COLUMN_NAME"
                      " ORDER BY COLUMN_ID", tabla);
    pasaselectword(id, doc, select, "Tabla interfase", "Título 1", titulo, comt.comentario);

}

void documentamanipulaciones(IDispatch *id, IDispatch  *doc)
{
    documentatabla("VDMANIPTIPO", id, doc);
    documentatabla("VDMANIPTIPOPROCESO", id, doc);
    documentatabla("VDMANIPDEFCAB", id, doc);
    documentatabla("VDMANIPDEFLIN", id, doc);
    documentatabla("VDMANIPDEFTAREA", id, doc);
    documentatabla("VDMANIPDEFPROCESO", id, doc);
    documentatabla("VDMANIPCAB", id, doc);
    documentatabla("VDMANIPLIN", id, doc);
    documentatabla("VDMANIPTAREA", id, doc);
    documentatabla("VDMANIPPROCESO", id, doc);
    documentatabla("VDMANIPUSU", id, doc);
}

void documentaensayos(IDispatch *id, IDispatch  *doc)
{
    documentatabla("ALCENSAYO", id, doc);
    documentatabla("ALCENSAYOART", id, doc);
    documentatabla("ALCENSAYOINF", id, doc);
    documentatabla("ALCINTERLOC", id, doc);
    documentatabla("ALCSERVICIO", id, doc);
    documentatabla("ALCSERVICIOPER", id, doc);
    documentatabla("ALCCLIFACT", id, doc);
    documentatabla("ALCENSAYOPART", id, doc);
    documentatabla("ALCTIPODOC", id, doc);
    documentatabla("ALCENSAYODOC", id, doc);
}

int main(int argc,char *argv[])
{    
    IDispatch *id,*doc;
    if (abreword("C:\\PROYECTOS\\alcura\\alc\\doc\\template.dotx",&id,&doc)) return;
    documentamanipulaciones(id,doc);
    documentaensayos(id,doc);
    putproperty(doc, "Saved", NULL, NULL,V10INT,TRUE,-1);
    liberaidispatch(doc);
    putproperty(id, "Visible", NULL, NULL,V10INT,TRUE,-1);
    liberaidispatch(id);
    finole();
    return(0);
}

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
                   LPSTR cmd, int cmdshow)
{
    int ret;
    v10hinst=hinst;
    v10hprev=hprev;
    strcpy(TITULOVENTANA,"EXPORTACION DE SQL A WORD 1.0");
    onexit(ejecutaexit);
    trataparamstd(__argc,__argv,trataparampremain,NULL);
    initapptxt(hinst,hprev,SW_SHOWMAXIMIZED,TITULOVENTANA,CW_USEDEFAULT,CW_USEDEFAULT,
        0,0,COLUMNASPANTALLA,LINEASPANTALLA,ESTILOV10,0,NULL,0,0,NULL);
    trataparamstd(__argc,__argv,trataparammain,trataparamoracle,NULL);
    ret=main(__argc,__argv);
    return(ret);
}
