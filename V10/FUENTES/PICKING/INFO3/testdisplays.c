/*****************************************************************
*																 *
* Módulo:  main.c												 *
* Función: Prueba de las librerías de info3						 *
*																 *	
*																 *
* Autor: Francisco J. Guerrero									 *
* Fecha: 29-1-2010												 *
*																 *	
******************************************************************/

#include "info3.h"

void limpiar(void)
{
 int i,j;

 for (i=0;i<infopick.numdisp;i++) {
	infotdisplays *disp;
	disp=infodisplay(i);
	if (disp->tipo->luces==0) continue;					
	infoimprime(i,"");
	for (j=0;j<disp->tipo->luces;j++) 
		infoponluz(i,j,0);
	}
}

static void circular(char *prueba,int *dig,int *digzona)
{
	infotdisplays *disp;
	int i,j;
	for (i=0;i<infopick.numdisp;i++) {
	   if (infodisplay(i)->tipo->luces==0) continue;			
		   disp=infodisplay(i);
		   for (j=0;j<12;j++)
			   prueba[j]=' ';
			   if (disp->tipo==infotdef+2 || disp->tipo==infotdef+3)
					prueba[*digzona]=255;
				else
					prueba[*dig]=255;
				infoimprime(i,prueba);
	}
	*digzona=(++*digzona)%12;
	*dig=(++*dig)%5;
}

int damenumdisp(int disp)
{
	int mint,mired,midisp,nt,nr,nd;
	if (infotconfig.tipodir==0) return disp;
	nd=0;
	datosdisp(disp,&mint,&mired,&midisp);
	for (nt=0;nt<mint;nt++) {
		infotsios *t=infopick.t[nt];
		for (nr=0;nr<t->numred;nr++) {
            infotreddisps *r=t->r+nr;
			if (nt==mint && nr==nr && disp<r->numdisp) {
				return(disp+nd);
			}
			nd+=r->numdisp;
		}
	}
   return(-1);
}

void testeo(int argc,char *argv[])
{
  int salir=0;
  int maximo_ciclos=50;
  infotdisplays *disp;
  char cadena_valor[MAXDIGDISPLAY];
  int i,j;
  int num_infopick=0,num_who=1;
  int bomberos=0;
  int dig=0,digzona=0;
  char prueba[12];	
  int bucle=0,ciclos=0;

  if (argc>1) num_infopick=atoi(argv[1]);
  if (argc>2) num_who=atoi(argv[2]);
  if (argc>3) maximo_ciclos=atoi(argv[3]);

  for (i=0;i<MAXDIGDISPLAY;i++)
	  cadena_valor[i]=255; // '8'; //254;	  

  if (num_infopick)
	sprintf(infotconfig.infopick,"INFOPICK%02d.TXT",num_infopick);
  else
    strcpy(infotconfig.infopick,"INFOPICK.TXT");

  leeconf(infotconfig.infopick);
  infoinit(num_who);
  
  for (i=0;i<infopick.numdisp; i++) {
	  int dir=damedirtipo(i);
	  if (!infodisplay(dir)->tipo->luces) {
		  infoimprime(dir,"");
		  continue;
	  }
	  infoprintf(dir,"%d",i+1);
	  for (j=0;j<infodisplay(dir)->tipo->luces;j++)
		  infoponluz(dir,j,1);
  }  
  while (!salir) {
		infotteclas tec;
		esperamensaje(infotconfig.espera);
		leeconf(infotconfig.infopick);
        if (hay_tecla()) {
			int ch;
			ch=tecla();
			switch (ch) {
				case '1': bucle=0;		
						  for (i=0;i<infopick.numdisp;i++) {
							  int dir=damedirtipo(i);
							  if (infodisplay(dir)->tipo->luces==0) continue;			
							  infoprintf(dir,"%d",i+1);
						  }
						  break;
				case '2': bucle=0;		
					for (i=0;i<infopick.numdisp;i++) {
						int dir=damedirtipo(i);
						if (infodisplay(dir)->tipo->luces==0) continue;			
						infoimprime(dir,cadena_valor);
					}
					break;
				case '3': bucle=0;		
						  for (i=0;i<infopick.numdisp;i++) {
						        int dir=damedirtipo(i);
								disp=infodisplay(dir);
								if (disp->tipo->luces==0) continue;			
								for (j=0;j<disp->tipo->luces;j++) 
									infoponluz(dir,j,(infostluz(dir,j)+1)%2);
							}
						   break;

				case '4': 	bucle=0;		
							limpiar();
                    		break;

				case '5': 	bucle=0;		
							for (i=0;i<infopick.numdisp;i++) {
						        int dir=damedirtipo(i);
								disp=infodisplay(dir);
								if (disp->tipo->luces==0) continue;										
								for (j=0;j<disp->tipo->luces;j++) 
								infoponluz(dir,j,2);
							}
						   break;
				case '6':	bomberos++;
							bucle=0;			   
							for (i=0;i<infopick.numdisp;i++) {
						       int dir=damedirtipo(i);
							   disp=infodisplay(dir);						  
							   if (disp->tipo->luces==0) 
								   ((bomberos%2)?infoimprime(dir,"~~~~~"):infoimprime(dir,""));								
						   }
						   break;	

				case '7':	bucle=0;		
							circular(prueba,&dig,&digzona);
							break;

				case '8':	bucle=1;
							ciclos=0;
							circular(prueba,&dig,&digzona);
							break;


				case A_F(10):
				case esc:	limpiar();
							salir=1;
							break;
				}
		}

		while (infotecla(&tec)) {
			disp=infodisplay(tec.disp);
            v10log(LOGNORMAL,"Botón %d pulsado en display %d\n",tec.boton,tec.disp+1);
            switch (tec.boton) {
				case 0: infoprintf(tec.disp,"%d",tec.disp+1);
						break;
				case 1:	infoimprime(tec.disp,cadena_valor);
						break;
                case 2: for (i=0;i<disp->tipo->luces;i++)
							infoponluz(tec.disp,i,(infostluz(tec.disp,i)+1)%2);
					    break;                
				case 3:	//infoprintf(tec.disp,"%d",disp->r->t->totcom);
						infoprintf(tec.disp,"%-ld-%-ld",disp->r->stats.sent_frames,disp->r->stats.received_frames);	
						break;                    
			}

		}
  
		
		if (bucle) {
			ciclos++;
			if (ciclos>maximo_ciclos) {
				ciclos=0;
				circular(prueba,&dig,&digzona);
			}
		}
  }		
}

int main(int argc,char *argv[])
{
	initv10logparam("INFOINTE.LOG",1,14,COLUMNASPANTALLA-2,LINEASPANTALLA-16);
	testeo(argc,argv);
	return(0);
}

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
           LPSTR cmd, int cmdshow)
{
  int ret;
  v10hinst=hinst;
  v10hprev=hprev;
  strcpy(TITULOVENTANA,"PROGRAMA DE TESTEO DE DISPLAYS");
  COLUMNASPANTALLA=150;
  initapptxt(hinst,hprev,cmdshow,TITULOVENTANA,CW_USEDEFAULT,CW_USEDEFAULT,
             0,0,COLUMNASPANTALLA,LINEASPANTALLA,ESTILOV10,0,NULL,0,0,NULL);
  ret=main(__argc,__argv);
  return(ret);
}   

