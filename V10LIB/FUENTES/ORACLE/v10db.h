#include "v10ora.h"

#ifndef __V10DB__H
#define __V10DB__H
#define NOSELECT 24333
#define FUNCOMMIT   54
#define FUNROLLBACK 55

#define MAXLUSER    101

#define ERRINVALIDA "1003,942,1001"
#define MAXLOGIN    500
#define EXTRA (arrlogin[numlogins-1].extra)
#define DRIVERDB (arrlogin[numlogins-1].driver)

typedef struct {
    char nombre[MAXPATH];
	void (*dbinit)(void);
	void (*dameerrorlda)(void   *error,char *mensaje);
	void (*dameerrorcur)(v10cursors *c,char *mensaje);
	void (*damelasterror)(char *buffer);
	int (*dbcommit)(void);
	int (*dbrollback)(void);
	int (*dblogout)(void);
	int (*dblogin)(char *usuario,char *password,char *condb);
	int (*dbparsecursor)(v10cursors *ret,char *sql,char *nombre,const char *funcion,const char *file,int line,int error,int debug);
	int (*dbejecutacursor)(v10cursors *c);
	void (*dbpreparaarrayfetch)(v10cursors *cur,int nelem);
	int (*dbdefinecursor)(v10cursors *cur,int ncamp,void *var,int lon,int v10tipo);
	int (*dbbindcursor)(v10cursors *c,char *ncamp,void *var,int lon,int v10tipo);
	int (*dbv10tipo)(int oratipo,int lonoracle,int precision,int escala,int *lon);
	int (*dbfetchcursor)(v10cursors *cur);
	int (*dbejefetchcursor)(v10cursors *cur);
	int (*dbejecutacursorarray)(v10cursors *cur,int iter);
	int (*dbarreglainvalido)(v10cursors *cur);
	int (*dbcancelacursor)(v10cursors *cur);
	int (*dbliberacursor)(v10cursors *cur);
	int (*dbejecutaimmediatof)(char *sql,int debug,const char *funcion,const char *file,int line);
	int insertinto;
} dbdrivers;

typedef struct {
			   dbdrivers  *driver;
			   void       *extra;
              } logins;

V10ORAIMPORT logins    *arrlogin;
V10ORAIMPORT int numlogins;
void verificanulos(v10cursors *cur);
V10ORAIMPORT void pondefaultdrv(dbdrivers *drv);
V10ORAIMPORT dbdrivers *damedefaultdrv(void);
V10ORAIMPORT void getlastdberror(char *buffer);

//Definido en v10oraargv.c
dbdrivers *damedbdriver(char *cadena);
#endif