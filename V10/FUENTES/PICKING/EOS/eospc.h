#include "eos.h"
#include "eosdll.h"

extern tecladisps tecdisp[MAXTECLAS];
extern int numetherbox;
extern int numteclasdisp;
extern int tipoidentdisp;
extern int MODIFICADOINFO;

//Funciones definidas en INFOPCDISP.C
void cambianumdisp(long primero,long anterior,long nuevo);
displays *revisadisp(long serie,long numdisp,int tipo);

//Funciones definidas en INFOETH.C
void initeth(etherboxs *eth,int tciclo,int tenvtrama,int timeouttrama,int timeoutwho,int limitacionlinea);
int pdisplin(ethlineas *lin);
int dimedatosdisp(int ndisp,int *neth,int *nlin,int *numdisp);
void ticketh(etherboxs *eth);
void pidestatusdisp(ethlineas *lin,int numdisp);
void pidestatuseth(etherboxs *eth);



