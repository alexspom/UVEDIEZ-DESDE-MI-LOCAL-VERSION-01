/*******************************************************************************
* Módulo : vddefcampoaux.c                                                     *
* Función: Modulo auxiliar para definir caracteristicas por defecto de campos  *
*                                                                              *
*                                                                              *
* Autor	 : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/
#include "vdform.h"

static void transformaespacios(char *cadena) {
	char *ptr=cadena;
	do {
		ptr=strstr(ptr,"\\n");
		if (!ptr) break;
		*ptr='\n';
		*(ptr+1)=' ';
		ptr+=2;
	} while (1);	
}

static int fcargapantalla(bloques *b,ftrigers *ft) {
	char fichero[MAXPATH]="",titulo[MAXCADENA]="";

	memset(fichero,0,sizeof(fichero));
	dameparametro(b,ft,0,V10CADENA,fichero);
	sprintf(titulo,"PREVISUALIZACION DE BLOQUE %s",fichero);
	fcejecutaform(b,fichero,"N","","","","",titulo,"S");	
	return(0);
}

static int feditapantalla(bloques *b,ftrigers *ft) {
	char fichero[MAXPATH]="",pathb[MAXPATH]="";

	memset(fichero,0,sizeof(fichero));
	dameparametro(b,ft,0,V10CADENA,fichero);
	if (!strstr(fichero,".PAN")) strcat(fichero,".PAN");
	damenombrecompleto(fichero, pathb);
	invocaeditor(pathb,NULL);
	return(0);
}

static void ponproteciones(char *carac,char *protect,char *priv, char *militeral) {
	if (*protect=='S') {
		strcat(carac,militeral);
		if (!es_blanco(priv)) sprintf(carac+strlen(carac),",PROTECT(%s)",priv);
		strcat(carac,"\n");
	}
}
	

char *leedefectobloque(forms *f,bloques *b,int paso)
{
	static int inittrigger=0;
    vddefbloques deb;
	vddefbloques debdefecto;
	char nombrebloque[MAXPATH]="",*ptr,ayudaonline[MAXCADENA]="";
    int ret;
    char tipopantalla[LTIPOPANTALLA];
    char *carac;

	if (inittrigger==0) {
		declaratriger("FEDITAPANTALLA",feditapantalla,NULL);
		declaratriger("FCARGAPANTALLA",fcargapantalla,NULL);
		inittrigger=1;
	}

	carac=calloc(1,MAXCADENA);
    if (f->tipo==FWINDOWS) {
        strcpy(tipopantalla,"F");
        strcpy(carac,damepropcadena("EXTRABLOQUE"));
    }  else {
        strcpy(tipopantalla,"R");
        strcpy(carac,damepropcadena("EXTRABLOQUERAD"));
	}
	traduceentorno(carac, ayudaonline);
	strcpy(carac, ayudaonline);
	strcpy(ayudaonline, "");
	strcopia(nombrebloque,b->fichero,strlen(b->fichero));
	ptr=strchr(nombrebloque,'.');
	if (ptr) *ptr=0;
	ret=DEBselvddefbloque(nombrebloque,tipopantalla,&deb);
    if (ret) {
        ret=DEBselvddefbloque(nombrebloque,"A",&deb);
        if (ret) return(carac);
    }

	switch (paso) {
		case 1:
			memset(&debdefecto,0,sizeof(debdefecto));
			ret=DEBselvddefbloque("DEFECTO","F",&debdefecto);
			strcat(carac,"\n");
			if (deb.numposx>0) sprintf(carac+strlen(carac),"POSX=%d\n",deb.numposx);
			if (deb.numposy>0) sprintf(carac+strlen(carac),"POSY=%d\n",deb.numposy);
			if (deb.numregpag>0) sprintf(carac+strlen(carac),"REGPAG=%d\n",deb.numregpag);
			if (*deb.titulobloque) sprintf(carac+strlen(carac),"TITULO=%s\n",deb.titulobloque);
			if (*deb.modoquery) sprintf(carac+strlen(carac),"%sQUERY\n",deb.modoquery);
		
			if (!es_blanco(deb.ayudaonline) || !es_blanco(debdefecto.ayudaonline)) {
				transformaespacios(debdefecto.ayudaonline);		
				transformaespacios(deb.ayudaonline);
				if (*deb.ayudaonline=='+') sprintf(ayudaonline,"ONLINE=%s %s",debdefecto.ayudaonline,deb.ayudaonline+1);
				else {
					if (*deb.ayudaonline==0) sprintf(ayudaonline,"ONLINE=%s",debdefecto.ayudaonline);
					else sprintf(ayudaonline,"ONLINE=%s",deb.ayudaonline);
				}
				ptr=strstr(ayudaonline,"<br>");
				if (ptr) {
					strcopia(carac+strlen(carac),ayudaonline,ptr-ayudaonline);
					strcat(carac,"\n");
					strcopia(carac+strlen(carac),ptr+4,strlen(ptr+4));					
				} else strcat(carac,ayudaonline);		
				//strcat(carac,"\n");
				if (!strchr(carac,';')) strcat(carac,";");
			}
			if (*deb.fcontextual) sprintf(carac+strlen(carac),"CONTEXTUAL=%s\n",deb.fcontextual);
			if (*deb.ftecla) sprintf(carac+strlen(carac),"TECLA=%s\n",deb.ftecla);
    		if (!es_blanco(deb.capitaliza)) sprintf(carac+strlen(carac),"%s",*deb.capitaliza=='U'?"UPPER\n":(*deb.capitaliza=='L'?"LOWER\n":"MIXED\n"));
			if (!es_blanco(deb.fayuda)) sprintf(carac+strlen(carac),"AYUDA=%s\n",deb.fayuda);
			
			ponproteciones(carac,deb.cnoinsert,deb.privinsert,"NOINSERT");
			ponproteciones(carac,deb.cnodelete,deb.privdelete,"NODELETE");
			ponproteciones(carac,deb.cnoupdate,deb.privupdate,"NOUPDATE");
			ponproteciones(carac,deb.cnoenter,deb.privnoenter,"NOENTER");
			ponproteciones(carac,deb.cnoorains,deb.privorains,"NOORAINS");



			if (!es_blanco(deb.fauxiliar)) sprintf(carac+strlen(carac),"%s\n",deb.fauxiliar);
			break;
		case 2:
			if (*deb.twhere) {
				//if (!strchr(deb.twhere,';')) strcat(deb.twhere,";");
				if (*deb.twhere=='+') {
					if (b->where) sprintf(b->where+strlen(b->where)," %s",deb.twhere+1);
					else b->where=strdup(deb.twhere+1);
				}
				else if (!b->where) b->where=strdup(deb.twhere);
					else if (*b->where==0) strcat(b->where,deb.twhere);
			}

			if (*deb.torderby && !b->orderby) {
				b->orderby=strdup(deb.torderby);
				//if (!strchr(b->orderby,';')) strcat(b->orderby,";");
			}
			break;
	}
	return(carac);
}