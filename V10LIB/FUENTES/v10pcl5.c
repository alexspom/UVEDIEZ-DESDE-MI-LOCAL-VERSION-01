
#include "v10.h"


unsigned   BARTYPE=CODE128;
unsigned   PRTNUM=HPLS300;
unsigned   CHKSUM=1;
unsigned   PASSES=1;
unsigned   OFFSET=0;

int           netiqhp=0;
static long   dppm=118;
// (1)static int    hpmx1=60,hpmy1=130;       
static int    maxetiqhpx=2,maxetiqhpy=2;   // (1)
static int    hpmx1=0,hpmy1=130;
static int    init;


FILE *PRN;

void cierraimpresora(void)
{
  if (PRN==NULL) return;
  if (netiqhp) {
     fprintf(PRN,"\014");
     netiqhp=0;
   }
  fclose(PRN);
  PRN=NULL;
}


void abreimpresora(void)
{
  char *aux,nfichero[MAXPATH];
  if (PRN) return;
  aux=getenv("PRINTER");
  if (aux==NULL) {
     aux="LPT1";
   }
  strcpy(nfichero,aux);
  redireccionareport("",nfichero);
  PRN = fopens(nfichero, "w+b");
  if (init==0) {
     atexit(cierraimpresora);
     init=1;
   }
}


#pragma warn -par
int limpialaser(char *param, void *dato)
{
  cierraimpresora();
  return(0);
}

#pragma warn +par

void ponresol(int resol)
{
  fprintf(PRN,"\033*t%dR",resol);
}


void cambiamaxetiq(int maxx,int maxy)
{
  abreimpresora();
  if (maxx!=maxetiqhpx || maxy!=maxetiqhpy) {
     if (netiqhp) {
        fprintf(PRN,"\014");
        netiqhp=0;
      }
     maxetiqhpx=maxx;
     maxetiqhpy=maxy;
   }
}


void asignaimpresora(FILE *salida)
{
   PRN=salida;
}


int imprimebarrast(char *string,char *tex,int height)
{
  int length;
  char *cadena;
  if (PRN==NULL) abreimpresora();
  length = barsize(BARTYPE,string,tex,PRTNUM,OFFSET,height,CHKSUM,PASSES);
  if (length<10) {
     printf("Error %d\n",length);
     exit(1);
    }
  cadena=calloc(1,length);
  length = bar_code(cadena,BARTYPE,string,tex,PRTNUM,OFFSET,height,
	             CHKSUM,PASSES);
  fwrite(cadena,1,length,PRN);
  free(cadena);
  return(length);
}


int imprimebarras(char *string,int height)
{
  int length;
  length = imprimebarrast(string,"",height);
  return(length);
}


void posprinter(long x,long y)
{
  if (PRN==NULL) abreimpresora();
  x-=hpmx1;
  y-=hpmy1;
  if (x<0) x=0;
  if (y<0) y=0;
  fprintf(PRN,"\033*p%lux%luY",(x*dppm)/100,(y*dppm)/100);
}


void ponalto(int y)
{
  if (PRN==NULL) abreimpresora();
  fprintf(PRN,"\033(s%dV",y);
}


void cambiadireccion(int dir)
{
   fprintf(PRN,"\033&a%dP",dir);
}


void fillrect(long x,long y,int porcentaje)
{
  if (PRN==NULL) abreimpresora();
  fprintf(PRN,"\033*c%lua%lub%dg2P",(x*dppm)/100,(y*dppm)/100,porcentaje);
}


void rectangulo(long x1,long y1,long ancho,long alto)
{
  posprinter(x1,y1);
  fillrect(ancho,alto,100);
}


void hpmarco(long x1,long y1,long ancho,long alto,long grueso)
{
  rectangulo(x1,y1,ancho+grueso,grueso);
  rectangulo(x1,y1+alto,ancho+grueso,grueso);
  rectangulo(x1,y1,grueso,alto+grueso);
  rectangulo(x1+ancho,y1,grueso,alto+grueso);
}


void calculaxyetiq(long *x,long *y)
{
   int netx,nety;
   netx=netiqhp%maxetiqhpx;
   nety=netiqhp/maxetiqhpx;
   *x=2100/maxetiqhpx*netx+(netx?hpmx1/2:hpmx1);
   *y=2970/maxetiqhpy*nety+hpmy1/2;
}


void tiraetiq(void)
{
   netiqhp++;
   if (netiqhp==maxetiqhpx*maxetiqhpy) {
      fprintf(PRN,"\014");
      netiqhp=0;
    }
   fflush(PRN);
}


void ejes(long x,long y)
{
  int lx;
  rectangulo(hpmx1,y-1,2000,2);
  for (lx=(hpmx1+9)/10;lx<210;lx++) {
      if ((lx%100)==0) rectangulo(lx*10,y-20,3,40);
        else {
          if (lx%10) rectangulo(lx*10,y-5,1,10);
             else    rectangulo(lx*10,y-10,2,20);
         }
    }
  rectangulo(x-1,hpmy1,2,2800);
  for (lx=(hpmy1+9)/10;lx<297;lx++) {
      if ((lx%100)==0) rectangulo(x-20,lx*10,40,3);
        else {
          if (lx%10) rectangulo(x-5,lx*10,10,1);
             else    rectangulo(x-10,lx*10,20,2);
         }
    }
}

void pintamarcas(void)
{
  rectangulo(hpmx1,1485,50,1);
  rectangulo(650,1485,100,1);
  rectangulo(1350,1485,100,1);
  rectangulo(2000,1485,50,1);
  rectangulo(700,hpmy1,1,50);
  rectangulo(700,1435,1,100);
  rectangulo(700,2900,1,100);
  rectangulo(1400,hpmy1,1,50);
  rectangulo(1400,1435,1,100);
  rectangulo(1400,2900,1,100);
}