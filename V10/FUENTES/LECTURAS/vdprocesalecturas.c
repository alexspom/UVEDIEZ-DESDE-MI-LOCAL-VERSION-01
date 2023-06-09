#include "vdlecturas.h"

typedef struct {
	     vdinfolecturass ilt;
         int (*vdinithardlectura)(int idinfolectura);
         int (*vddamecaracter)(void);
} infolecturas;

#define STNOCONECTADA -1
#define STIDDLE 0
#define STSCANER 1
#define STDATA 2

int status;
int scan;
char lectura[LTEXTO];
int indice;

static int idinfoletura=-1;
static infolecturas ifhl;


static void initvdinfoprocesa(int idinfolectura)
{
    HMODULE libreria;
    char    fichero[MAXPATH];
	int ret;
    
	ret=ILTselvdinfolecturas(idinfolectura,&ifhl.ilt);
	if (ret) final(("No existe idinfolectura %d\n",idinfolectura));
    ifhl.vdinithardlectura=damefundll(ifhl.ilt.libproceso,"vdinithardlectura");
    if (ifhl.vdinithardlectura==NULL) final(("No puedo cargar funcion vdinithardlectura en libreria %s",ifhl.ilt.libproceso));
    ifhl.vddamecaracter=damefundll(ifhl.ilt.libproceso,"vddamecaracter");
    if (ifhl.vddamecaracter==NULL) final(("No puedo cargar funcion vddamecaracter en libreria %s",ifhl.ilt.libproceso));
  /*  damenombrecompleto(ifhl.ilt.libproceso,fichero);

    libreria = LoadLibrary( fichero );

    if( libreria == NULL )
        final(("Imposible cargar la libreria %s", fichero));
   
	ifhl.vdinithardlectura=(void*)GetProcAddress(libreria, "vdinithardlectura");
    if (ifhl.vdinithardlectura==NULL) final(("No puedo cargar funcion vdinithardlectura en libreria %s",fichero));
   
	ifhl.vddamecaracter=(void*)GetProcAddress(libreria, "vddamecaracter");
    if (ifhl.vddamecaracter==NULL) final(("No puedo cargar funcion vddamecaracter en libreria %s",fichero));*/
   
}


static void reset_lh(void) {
	scan=0;
	indice=0;
	memset(lectura,0,LTEXTO);
	status=STIDDLE;
}

static void inserta_lectura(void)
{
	int espejo=0,ret;
    vdscanlects sc;
	vdscanmirrors scm;
    
	memset(&sc,0,sizeof(sc));
	    // Recogemos la secuencia de lectura
    ret=SCMbuscascmaestros(idinfoletura,scan,&scm);
	if (ret==0) espejo=1; // es un escanner espejo de otro
	else {
		scm.redscan=idinfoletura;
		scm.scanner=scan;
	}
	do {
		if (SCLselvdsecscanlect(&sc.seqaccion)) {
		    rollback();	   
			v10log(LOGNORMAL,"%s","\t\tError al calcular la secuencia de la tabla\n");
			return;
		}
		if (espejo==0) {
			v10log(LOGNORMAL,"Red de Escaner: %ld ESCANER: %ld LECTURA: %s\n",
				ifhl.ilt.idinfolectura,scan,lectura);
		} else {			
			v10log(LOGNORMAL,"Red de Escaner: %ld ESCANER: %ld LECTURA: %s (ESPEJO)  => Escaner Maestro: (Red) %ld  (Escaner) %ld\n",
				ifhl.ilt.idinfolectura,scan,lectura,scm.redscan,scm.scanner);
		}
		sc.redscan=	scm.redscan;
		sc.scanner= scm.scanner;
		strcpy(sc.texto,lectura);
		sc.status=100;
		strcpy(sc.codopemodif,"INFOLECTURAS");    
		if (!SCLinsert(&sc,NOVERIFICA)) {
		    commit();
			v10log(LOGNORMAL,"%s","\t\tConfirmada inserci�n\n");
		}
		else {
		    rollback();	   
			v10log(LOGNORMAL,"%s","\t\tError al insertar en tabla\n");
    	}
		if (espejo==1) {
			ret=SCMnextscmaestros(&scm);
			if (ret) espejo=0;
		}
	} while (espejo==1);
   
}


static void abreconexioneshard(void)
{
	// Dispositivo asociado a la Red
	reset_lh();
	if (ifhl.vdinithardlectura(idinfoletura)!=0) {
		status=STNOCONECTADA;
		v10log(LOGDEBUG,"Red de Escaner %ld. Error Abriendo Conexi�n\n",idinfoletura);
	} else
		v10log(LOGNORMAL,"Red de Escaner %ld. Abierta Conexi�n\n",idinfoletura);
}



int tratalecturas(void) {

	int ch;
	vdinfolecturass *ilt=&ifhl.ilt;
	if (status==STNOCONECTADA) {
		abreconexioneshard();
		return 0;
	}
	do {
		ch= ifhl.vddamecaracter();
		if (ch) {
			switch (status) {
			
				case STIDDLE:

					if (ch==atoi(ilt->chstx)) { // inicio trama
						reset_lh();
						status=STSCANER;	
						// NO HAY IDENTIFICADOR DE ESCANER
						if (ilt->lonidscan==0) {
							status=STDATA;
							scan=0;
						}
					} else 
						v10log(LOGNORMAL,"Red de Escaner %ld. Recibe caracter %c no tratado\n",idinfoletura,(char)ch);
					break;

				case STSCANER:

					if (ch==atoi(ilt->chstx)) {
						v10log(LOGDEBUG,"Red de Escaner %ld. Detecta STX antes de recibir id. scaner\n",idinfoletura);
						reset_lh();
						break;
					}

					if (ch==atoi(ilt->chsoh)) { // se encuentra SOH
						// se encuentra en la posici�n adecuada
						if (ilt->lonidscan==indice+1) {
							scan=atoi(lectura);
							memset(lectura,0,LTEXTO);
							status=STDATA;
							indice=0;
						} else { // no se encuentra en la posici�n adecuada
							v10log(LOGNORMAL,"Red de Escaner %ld. Llega caracter SOH (%d) sin llegar a longitud de escaner\n",idinfoletura,atoi(ilt->chsoh));
							reset_lh();
						}

					} else { // ya supera la longitud preestablecida											
						if (indice+1>ilt->lonidscan) {
								v10log(LOGNORMAL,"Red de Escaner %ld. Longitud del ID Scan supera la m�xima permitida %d\n",idinfoletura,ilt->lonidscan);
								reset_lh();
						} else {	
							lectura[indice++]=(char)ch;
							// longitud fija sin SOH
							if (indice>=ilt->lonidscan && strlen(ilt->chsoh)==0) {
								scan=atoi(lectura);
								memset(lectura,0,LTEXTO);
								status=STDATA;
								indice=0;
							}
						}
					}
					
					break;

				case STDATA: 

					if (ch==atoi(ilt->chstx)) {
						v10log(LOGDEBUG,"Red de Escaner %ld. Detecta STX antes de recibir EXT. Pierde Datos %s\n",idinfoletura,lectura);
						reset_lh();
						break;
					}
					// detecta caracter final
					if (ch==atoi(ilt->chetx)) {
						// supera longitud maxima establecida
						if (ilt->londata>0 && indice>ilt->londata) {
							v10log(LOGNORMAL,"Red de Escaner %ld. Longitud del Datos Recibidos %s supera la m�xima permitida %d\n",idinfoletura,lectura,ilt->londata);
						} else {
							if (scan<999) inserta_lectura();
						}
						reset_lh();
						return(0);
					} else {
						lectura[indice++]=(char)ch;
						
					}
				}	// end switch 
		}	

	} while (ch);
	
	return (-1);	
}



VDEXPORT void tratalecturasred(procesos *proceso)
{
    char idinfo[MAXPATH];
    if (idinfoletura==-1) {
       piece(proceso->proc.param,idinfo,"#",1);
       idinfoletura=atoi(idinfo);
       initvdinfoprocesa(idinfoletura);   
       abreconexioneshard();
    }
    tratalecturas();    
}

VDEXPORT void tratalecturashost(procesos *proceso)
{
	vdordenadoress ord;
	int ret;

	memset(&ord,0,sizeof(ord));
	strcpy(ord.ordenador,damehostname());

	ret=ORDselvdordenadores(ord.ordenador,&ord);
	if (ret) {
		v10log(LOGERROR,"Error obteniendo informacion del ordenador %s\n",ord.ordenador);
		return;
	}
    if (idinfoletura==-1) {
		idinfoletura=ord.idinfolectura;
		initvdinfoprocesa(idinfoletura);   
		abreconexioneshard();
	}
    tratalecturas();    
}

