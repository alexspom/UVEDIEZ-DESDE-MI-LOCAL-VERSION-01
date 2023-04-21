#include "vdinfopicking.h"
//(1) FGS. Tratamiento de display mirror, definido en vdinfoharddisp.
static int idinfopick=-1;

typedef struct {
	     vdinfohards iha;
         void (*vdinfoinit)(int idinfopick);
         int (*vdinfoprint)(int iddisplay,char *cadena,char *luces);
         int (*vddametecla)(vdinfomensajes *men);
         void (*vdtickinfo)(void);
} infohards;

static infohards ifh;

static void initipinfoprocesa(int idinfopick)
{
    HMODULE libreria;
    char    fichero[MAXPATH];
	int ret;
    
	ret=IHAselvdinfohard(idinfopick,&ifh.iha);
    if (ret) final(("No existe idinfopick %d\n",idinfopick));
    damenombrecompleto(ifh.iha.libproceso,fichero);

    libreria = LoadLibrary( fichero );

    if( libreria == NULL )
        final(("Imposible cargar la libreria %s", fichero));
    ifh.vdinfoinit=(void*)GetProcAddress(libreria, "vdinfoinit");
    if (ifh.vdinfoinit==NULL) final(("No puedo cargar funcion vdinfoinit en libreria %s",fichero));
    ifh.vdinfoprint=(void*)GetProcAddress(libreria, "vdinfoprint");
    if (ifh.vdinfoprint==NULL) final(("No puedo cargar funcion vdinfoprint en libreria %s",fichero));
    ifh.vddametecla=(void*)GetProcAddress(libreria, "vddametecla");
     if (ifh.vddametecla==NULL) final(("No puedo cargar funcion vddametecla en libreria %s",fichero));
    ifh.vdtickinfo=(void*)GetProcAddress(libreria, "vdtickinfo");
    if (ifh.vdtickinfo==NULL) final(("No puedo cargar funcion vdtickinfo en libreria %s",fichero));
	logoracle=NULL;
}


static void tratadatosorigen(int idinfopick)
{
    int ret;
	vdinfoharddisps ihd;
    ret=IHDbuscarango(idinfopick,STIHDPENDIENTE,ifh.iha.rangolineas,&ihd);
    while (ret==0) {
		v10log(LOGNORMAL,"Presentando en display %d-%d datos %s luces %s\n",ihd.idinfopick,ihd.numdisp,ihd.texto,ihd.luces);
		if (IHDlock(&ihd,0,0)==0) {
			IHDselvdinfoharddisp(ihd.idinfopick,ihd.numdisp,&ihd);
			if (es_blanco(ihd.texto) && es_blanco(ihd.luces)) {
				v10log(LOGNORMAL,"Display %d-%d datos %s luces %s a APAGADO\n",ihd.idinfopick,ihd.numdisp,ihd.texto,ihd.luces);
				ihd.status=STIHDAPAGADO;
			}
			else ihd.status=STIHDPRESENTADO;
			IHDactualizastatus(&ihd,0);
			ifh.vdinfoprint(ihd.numdisp,ihd.texto,ihd.luces);
			if (ihd.idinfopickm>0) {
				v10log(LOGNORMAL,"Presentando en display espejo %d-%d del display %d-%d datos %s luces %s\n",ihd.idinfopickm,ihd.numdispm,ihd.idinfopick,ihd.numdisp,ihd.texto,ihd.luces);
				ifh.vdinfoprint(ihd.numdispm,ihd.texto,ihd.luces);
			}
		}
		ret=IHDnextrango(&ihd);
	}
   commit();
}

static void restauradatosorigen(int idinfopick)
{
    int ret;
	vdinfoharddisps ihd;
    ret=IHDbuscarango(idinfopick,STIHDPRESENTADO,ifh.iha.rangolineas,&ihd);

    while (ret==0) {		   
		   v10log(LOGNORMAL,"Restaurando en display %d-%d datos %s luces %s\n",ihd.idinfopick,ihd.numdisp,ihd.texto,ihd.luces);
           ifh.vdinfoprint(ihd.numdisp,ihd.texto,ihd.luces);
 /*       {int i; for (i = 0; i < 100; i++) {
            ifh.vdinfoprint(ihd.numdisp, "", ihd.luces);
            ifh.vdinfoprint(ihd.numdisp, ihd.texto, ihd.luces);
            ifh.vdtickinfo();
            }
        }*/
		   if (ihd.idinfopickm>0) {
			   v10log(LOGNORMAL,"Restaurando en display espejo %d-%d del display %d-%d datos %s luces %s\n",ihd.idinfopickm,ihd.numdispm,ihd.idinfopick,ihd.numdisp,ihd.texto,ihd.luces);
		       ifh.vdinfoprint(ihd.numdispm,ihd.texto,ihd.luces);
		   }
		   ret=IHDnextrango(&ihd);
    }
}

#define CUPDASTDISP "UPDATE VDINFOHARDDISP SET ESTADOBOT=:ESTADO WHERE IDINFOPICK=:IDINFOPICK AND NUMDISP=:NUMDISP AND ESTADOBOT!=:ESTADO"
static void actualizamidisp(int idinfopick,int numdisp,int causa)
{
	static v10cursors *v10updastdisp;
	static int sidinfopick,snumdisp,sestado;
	if (v10updastdisp==NULL) {
		v10updastdisp=abrecursor(CUPDASTDISP);
		bindtodo(v10updastdisp,"IDINFOPICK",&sidinfopick,sizeof(sidinfopick),V10LONG,
			                   "NUMDISP",&snumdisp,sizeof(snumdisp),V10LONG,
							   "ESTADO",&sestado,sizeof(sestado),V10LONG,
							   NULL);
	}
	sidinfopick=idinfopick;
	snumdisp=numdisp;
	sestado=causa;
	ejecutacursor(v10updastdisp);
}

static void tratateclas(int idinfopick)
{
    vdinfomensajes men;
	vdinfoharddisps ihdmaster; // contiene el display maestro, el display es espejo de otro display (maestro)
    vdinfoharddisps ihd;
	int ret;
	memset(&men,0,sizeof(men));
    while (ifh.vddametecla(&men)!=0) {
        switch (men.nmensaje) {
        case TESTADOBOT:actualizamidisp(idinfopick, men.numdisp, men.causa);
            break;
        case TREFRESCA:ret=IHDselvdinfoharddisp(idinfopick, men.numdisp, &ihd);
                       if (ret==0) ifh.vdinfoprint(ihd.numdisp, ihd.texto, ihd.luces);
            break;
        default:
		  men.idinfopick=idinfopick;
		  // es display mirror
		  if (IHDbuscadispmirror(men.idinfopick,men.numdisp,&ihdmaster)==0) {
				vdinfoencolatecla(ihdmaster.idinfopick,ihdmaster.numdisp,men.nmensaje,men.causa);
		  } else  vdinfoencolatecla(men.idinfopick,men.numdisp,men.nmensaje,men.causa);
		}
	   commit();
    }

}


VDEXPORT void infotratahard(procesos *proceso)
{
    char idinfo[MAXPATH];

    if (idinfopick==-1) {
       piece(proceso->proc.param,idinfo,"#",1);
       idinfopick=atoi(idinfo);
       initipinfoprocesa(idinfopick);
        v10log(LOGNORMAL, "Inicializado el sistema de displays\n", 0);
       ifh.vdinfoinit(idinfopick);
       restauradatosorigen(idinfopick);
    }
    tratadatosorigen(idinfopick);
    tratateclas(idinfopick);
    ifh.vdtickinfo();
}

