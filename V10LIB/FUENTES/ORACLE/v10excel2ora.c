/*
* Módulo : EXCEL2ORACLE.C                                              
* Objeto:  Importar una hoja Excel en una tabla ORACLE
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "forms\v10form.h"


typedef struct {
            char nombre[MAXNOMBREV10];
            char buffer[MAXOLECADENA];
            int  v10tipo;
         } excelcampos;
static excelcampos ec[MAXCAMPOS];
static int nec;

static int leefila(IDispatch *hoja,int fila,int nc)
{
  SAFEARRAY *psa;
  VARIANTARG *pvargBase,ret;
  VARIANTARG *pvarg;
  int i,nulo=1;
  char rango[100];
  pasarangoexcel(0,fila,nc-1,fila,rango);
  getvalorarray(hoja,rango,&ret);
  psa=ret.parray;
  SafeArrayAccessData(psa,(void HUGEP* FAR*)  &pvargBase);
  pvarg=pvargBase;
  for (i=0;i<nc;i++) {
      char valor[MAXOLECADENA];
      variant2string(pvarg,valor);
      if (es_blanco(valor)) strcpy(valor,"");
        else                nulo=0;
      strcpy(ec[i].buffer,valor);
      trim(ec[i].buffer);
      pvarg++;
   }
  SafeArrayUnaccessData(psa);
  ReleaseVariant(&ret);
  return(nulo);
}

static void sustituyecar(char *cadena,char origen,char destino)
{
  char *aux;
  while ((aux=strchr(cadena,origen))!=NULL) {
        if (destino) *aux=destino;
           else      strcpy(aux,aux+1);
   }
}


#define CSELVERIF "SELECT TABLE_NAME FROM USER_TABLES WHERE TABLE_NAME=UPPER(:TABLE_NAME)"
#define CSELTIPO "SELECT DATA_TYPE FROM USER_TAB_COLUMNS WHERE TABLE_NAME=UPPER(:TABLE_NAME) AND COLUMN_NAME=UPPER(:COLUMN_NAME)"

static void tratacampos(IDispatch *hoja,char *destino,int crear,int std)
{
  char valor[100],valor1[100];
  char sql[MAXCADENA],insert[MAXCADENA],tipodato[MAXNOMBREV10];
  int i,fila,ret,ncamp;
  int nc;
  v10cursors *drop,*vdins,*vdseltipo=NULL;
  if (crear==0) {
     static v10cursors *vdverif;
     vdverif=abrecursor(CSELVERIF);
     definetodo(vdverif,destino,MAXNOMBREV10,V10CADENA,
                         NULL);
     bindtodo(vdverif,"TABLE_NAME",destino,MAXNOMBREV10,V10CADENA,
                         NULL);
     if (ejefetchcursor(vdverif)!=0) crear=1;
     liberacursor(vdverif);
   }
  if (crear) {
     if (crear==1) sprintf(valor,"DROP TABLE %s",destino);
	 else sprintf(valor, "TRUNCATE TABLE %s", destino);
     drop=llparsecursornombre(valor,"drop tempexcel",0);
     ejecutacursor(drop);
     liberacursor(drop);
   }
  for (nec=0;nec<MAXCAMPOS;nec++) {
      char rango[100];
      pasadirexcel(nec,1,rango);
      getvalorstring(hoja,rango,valor);
      if (es_blanco(valor)) {
         pasadirexcel(nec,2,rango);
         getvalorstring(hoja,rango,valor1);
         if (es_blanco(valor1)) break;
      }
      trim(valor);
      valor[MAXNOMBREV10-1]=0;
      if (traducecamposole) {
          strcpy(ec[nec].nombre,traducecamposole(valor,1));
      } else {
          sustituyecar(valor,' ','_');
          sustituyecar(valor,'/','_');
          sustituyecar(valor,'(',0);
          sustituyecar(valor,')',0);
          sustituyecar(valor, '.', '_');
          sustituyecar(valor, '.', '_');
          sustituyecar(valor, '-', '_');
          sustituyecar(valor, '?', '_');
          sustituyecar(valor, 'Ó', 'O');
          sustituyecar(valor, 'ú', 'U');
          sustituyecar(valor, 'í', 'I');
          sustituyecar(valor, 'Á', 'A');
          sustituyecar(valor, 'á', 'A');
          sustituyecar(valor, 'é', 'E');
          sustituyecar(valor, 'º', 'O');
          sustituyecar(valor,'ó','O');
          strmay(valor);
          strcopia(ec[nec].nombre,valor,30);
      }
      ec[nec].nombre[25] = 0;
      if (isdigit(ec[nec].nombre[0])) ec[nec].nombre[0] = 'C';
      for (nc = 0; nc < nec; nc++) if (strcmp(ec[nec].nombre, ec[nc].nombre) == 0) sprintf(ec[nec].nombre, "%s_%d", ec[nec].nombre,nec);
      pasadirexcel(nec,2,rango);
      ec[nec].v10tipo=gettipo(hoja,rango);
   }
  sprintf(sql,"CREATE TABLE %s (",destino);
  sprintf(insert,"INSERT INTO %s (",destino);
  ncamp=0;
  for (i=0;i<nec;i++) {
      if (!es_blanco(ec[i].nombre)) {
          sprintf(insert+strlen(insert),"%s%s",ncamp?",":"",ec[i].nombre);
          ncamp++;
      }
  }
  sprintf(insert+strlen(insert),") VALUES (");
  ncamp=0;
  for (i=0;i<nec;i++) {
      strcpy(tipodato,"");
      if (es_blanco(ec[i].nombre)) continue;
      if (std==0) {
         sprintf(sql+strlen(sql),"%s\"%s\" VARCHAR2(%ld)",ncamp?",":"",ec[i].nombre,MAXOLECADENA-1);
       } else {
         switch (ec[i].v10tipo) {
           case V10DOUBLE:
           case V10LONG:if (crear==0) {
                             if (vdseltipo==NULL) {
                                vdseltipo=abrecursor(CSELTIPO);
                              }
                             definetodo(vdseltipo,tipodato,sizeof(tipodato),V10CADENA,NULL);
                             bindtodo(vdseltipo,"TABLE_NAME",destino,MAXNOMBREV10,V10CADENA,
                                                 "COLUMN_NAME",ec[i].nombre,sizeof(ec[i].nombre),V10CADENA,
                                                 NULL);
                             ret=ejefetchcursor(vdseltipo);
                             if (ret) continue;
                          }
                        sprintf(sql+strlen(sql),"%s\"%s\" NUMBER",ncamp?",":"",ec[i].nombre);
                       break;
           case V10CADENA:
                          sprintf(sql+strlen(sql),"%s\"%s\" VARCHAR2(%ld)",ncamp?",":"",ec[i].nombre,MAXOLECADENA-1);
                          break;
          }
       }
      if (strcmp(tipodato,"DATE")==0) sprintf(insert+strlen(insert),"%sTO_DATE(LTRIM(TRUNC(:%s)),'J')",ncamp?",":"",ec[i].nombre,ec[i].nombre,ec[i].nombre);
      else                            sprintf(insert+strlen(insert),"%s:%s",ncamp?",":"",ec[i].nombre);
      ncamp++;
   }
  sprintf(sql+strlen(sql),")");
  sprintf(insert+strlen(insert),")");
  if (crear==1) ejecutaimmediato(sql);
  ejecutaimmediato("ALTER SESSION SET NLS_NUMERIC_CHARACTERS='.,'");
  if (vdseltipo) liberacursor(vdseltipo);
  vdins=parsecursornombre(insert,"INSERT TEMPEXCEL");
  for (i=0;i<nec;i++) {
      if (!es_blanco(ec[i].nombre)) bindcursor(vdins,ec[i].nombre,ec[i].buffer,sizeof(ec[i].buffer),V10CADENA);
   }
  leefila(hoja,2,nec);
  for (fila=2;;fila++) {
      int nulo;
      nulo=leefila(hoja,fila,nec);
      if (nulo) break;
//      oradebug=255;
      for (i=0;i<nec;i++) {
          if (ec[i].v10tipo==V10DOUBLE||ec[i].v10tipo==V10LONG) while (strchr(ec[i].buffer,'.')) *strchr(ec[i].buffer,'.')=',';
      }
      ret=ejecutacursor(vdins);
      if (ret) {
         v10log(LOGERROR,"Error ORACLE %d insertando fila %d\n",ret,fila);
       }
      if ((fila%100)==0) v10log(LOGNORMAL,"Tratando fila %d\n",fila);
      hay_tecla();
   }
  v10log(LOGNORMAL,"Tratadas %d filas\n",fila-2);
  commit();
  liberacursor(vdins);
}

int excel2ora(char *nombre,char *destino,int crear,int std)
{
    IDispatch *id,*hoja,*wb;
    int ret;
    id=startole("Excel.Application",0);
    if (id==NULL) {
        mensajefcm(10,"Aplicacion %s no instalada","Excel");
        finole();
        return(-1);
    }
	ret = cargaexcel(id, &wb, &hoja, nombre);
    if (ret==0) {
		int nhoja;
		liberaidispatch(hoja);
		for (nhoja=0;nhoja<100;nhoja++) {
            VARIANTARG varg2;
			ClearAllArgs();
			AddArgumentInt2(NULL, nhoja+1);
			Invoke(wb, "Worksheets", &varg2, DISPATCH_PROPERTYGET, 0);
			hoja = varg2.pdispVal;
			if (hoja==NULL) break;
			if (nhoja>0) crear=0;
			tratacampos(hoja,destino,crear,std);
            crear = 0;
			ClearAllArgs();
			liberaidispatch(hoja);
            break;
		}
		ClearAllArgs();
		AddArgumentInt2(NULL, 0);
		Invoke(wb, "Close", NULL, DISPATCH_METHOD, 0);
		ClearAllArgs();
		liberaidispatch(wb);
	}
	ClearAllArgs();
	Invoke(id, "Quit", NULL, DISPATCH_METHOD, 0);
	liberaidispatch(id);
    finole();
    return(0);
}