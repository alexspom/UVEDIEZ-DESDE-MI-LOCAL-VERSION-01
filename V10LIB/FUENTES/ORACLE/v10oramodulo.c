/*
* Módulo : V10ORAMODULO 
* Objeto:  Tratamiento de modulo y accion
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10ora.h"


typedef struct {
       char module[LMODULE];
       char action[LACTION];
    } modules;

static modules mod;

#define CSETMODULE "BEGIN DBMS_APPLICATION_INFO.SET_MODULE(:MODULE,:ACTION); END;"
static v10cursors *v10setmodule;
#define CSETACTION "BEGIN DBMS_APPLICATION_INFO.SET_ACTION(:ACTION); END;"
static v10cursors *v10setaction;

unsigned nolockform=0;
static modules mod;

static void finoramodulo(void)
{
  liberacursor(v10setmodule);
  liberacursor(v10setaction);
}


static void initoramodulo(void)
{
  v10setmodule=abrecursor(CSETMODULE);
  bindtodo(v10setmodule,"MODULE",mod.module,sizeof(mod.module),V10CADENA,
                        "ACTION",mod.action,sizeof(mod.action),V10CADENA,
                        NULL);
  pondebugcursor(v10setmodule,0);
  v10setaction=abrecursor(CSETACTION);
  bindtodo(v10setaction,"ACTION",mod.action,sizeof(mod.action),V10CADENA,
                        NULL);
  pondebugcursor(v10setaction,0);
  atexit(finoramodulo);
}

int setmodule(char *module,char *action)
{
#ifdef __LINUX__
   return(0);
#endif
   if (v10setmodule==NULL) initoramodulo();
   if (strlen(module)>LMODULE-1) strcpy(mod.module,module+strlen(module)-LMODULE);
      else                          strcpy(mod.module,module);
   strcpy(mod.action,action);
   ejecutacursorv(v10setmodule);
   return(0);
}

int setaction(char *action)
{
#ifdef __LINUX__
   return(0);
#endif
   if (v10setaction==NULL) initoramodulo();
   strcpy(mod.action,action);
   ejecutacursorv(v10setaction);
   return(0);
}