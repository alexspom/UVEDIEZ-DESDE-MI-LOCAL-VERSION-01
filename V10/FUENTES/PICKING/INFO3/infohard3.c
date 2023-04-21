/*****************************************************************
*																 *
* Módulo:  Infohard.c											 *
* Función: Intercambio de mensajes con líneas de displays		 *
*																 *	
*																 *
* Autor: Francisco J. Guerrero									 *
* Fecha: 29-1-2010												 *
*																 *		
******************************************************************/


#include "info3.h"

static CRITICAL_SECTION infohcritical; // manejo de la sección crítica entre hebras
static int infohinitcrit=0;

static void infohinit(void)
{
	if (infohinitcrit) return;
	InitializeCriticalSection(&infohcritical);
	infohinitcrit=1;
}


void watchdog(infotreddisps *r) 
{
	char nbred;
	infotsios *t;
	t=r->t;
	nbred='A'+(r-t->r);
	v10log(LOGNORMAL,"\n*******************************\nSalta Watchdog en Línea %c de tarjeta %s\n*******************************\n\n\n",nbred,t->dir_IP);
}

static int infohreceive_char(infotreddisps *r,v10socks *pipe)
{
	if (pipe->status==STSOCKROTA) return -1;  
	do {
		if (v10sockhaycar(pipe)) return v10socksigcar(pipe);
		if (r->stats_pend>0 && damecent()-r->stats_pend>infotconfig.watchdog) {
			watchdog(r);
			pipe->status=STSOCKROTA;
		}
		if (pipe->status==STSOCKROTA) break;
		Sleep(1);
	} while (1);
	return -1;
}


static int infohreceive_integer(infotreddisps *r,v10socks *pipe)
{
	char to_int[6];
	int to_return,i,ch;

	for (i=0;i<5;i++) {
		ch=infohreceive_char(r,pipe);
		if (ch<0) return -1;
		to_int[i]=(char)ch;
	}
	to_int[5]='\0';
	to_return=atoi(to_int);
	return to_return;
}


int infohreceive(infotsios *t,infotreddisps *r,int red)
{
	v10socks *pipe;
	int i;
	int inicio,longitud;
	int read_data;

	infohinit();
	EnterCriticalSection(&infohcritical);  
	pipe=r->pipe;
	read_data=infohreceive_char(r,pipe);
	if (read_data!=-1) { 	  
		r->stats_pend=damecent();
		switch (read_data) {
	  case RESP_DISP:{
		  inicio=infohreceive_integer(r,pipe);
		  longitud=infohreceive_integer(r,pipe);
		  if (inicio+longitud >=MAX_BUFFER_REC) {
			  v10log(LOGERROR,"Error recibiendo respuesta de display red %c\n",(r-t->r)+'A');
			  read_data=0;
			  break;
		  }
		  if (inicio==-1 || longitud==-1) {
			  read_data=0;
			  break;
		  }
		  //v10log(LOGNORMAL,"Tecla pulsada.....................\n");
		  for (i=inicio;i<inicio+longitud;i++)
			  r->buffer_entrada[i]=(char)infohreceive_char(r,pipe);
					 }
        r->numdispreal=longitud/2;
        pintatarj(buscatarj(t),r,red);
					 break;

	  case RESP_STATS: {
		  v10log(LOGNORMAL,"Recibiendo respuesta de estadistica %c\n",(r-t->r)+'A');
		  inicio=infohreceive_integer(r,pipe);
		  longitud=infohreceive_integer(r,pipe);
		  if (inicio+longitud !=sizeof(serial_stats)) {
			  v10log(LOGERROR,"Error recibiendo respuesta de estadistica %c\n",(r-t->r)+'A');
			  read_data=0;
			  break;
		  }
		  if (inicio==-1 || longitud==-1) {
			  read_data=0;
			  break;
		  }

		  for (i=inicio;i<inicio+longitud;i++)
			  ((char *)(&r->stats))[i]=(char)infohreceive_char(r,pipe);
		  tratastats(t,r,red);
					   }
					   break;

	  case ERROR_MSG: {
		  if (r->hulterror!=0 && damecent()-r->hulterror > infotconfig.ratioerr)
			  r->numerror=1;
		  else
			  r->numerror++;
		  inicio=infohreceive_integer(r,pipe);
		  longitud=infohreceive_integer(r,pipe);
		  r->hulterror=damecent();
		  r->toterror++;
		  pintatarj(buscatarj(t),r,red);
		  // v10log(LOGNORMAL,"Encontrado Error en la red %d\n",red);
		  //		hay_tecla();
					  }
		  break;

	  default: v10log(LOGERROR,"Recibido caracter no esperado %d %c\n",read_data,read_data);
		       break;
		}
	}
	else
		read_data=0;
	LeaveCriticalSection(&infohcritical);
	return read_data;
}

void envia_tcpip(infotreddisps *r) 
{
	if (r->numdisp==0) 
		return;
	if (r->ptr_tcpip) {
		recupera_conexion(r);
		EnterCriticalSection(&infohcritical);
		if (v10socklisto(r->pipe)) v10sockescribe(r->pipe,r->buffer_tcpip,r->ptr_tcpip);
		r->nbmsg_tcpip=0;
		r->ptr_tcpip=0;
		LeaveCriticalSection(&infohcritical);
	}else{
		EnterCriticalSection(&infohcritical);
		r->nbmsg_tcpip=0;
		r->ptr_tcpip=0;
		LeaveCriticalSection(&infohcritical);
	}
	r->ultimo_tcpip=damecent();
}

void infohsend(char command,infotreddisps *r, int op1, int op2,char *buffer)
{
	infohinit();
	EnterCriticalSection(&infohcritical);

	r->buffer_tcpip[r->ptr_tcpip++]=command;
	switch (command) {
	case LONG_BUFFER:
		memcpy(r->buffer_tcpip+r->ptr_tcpip,&op1,2);
		r->ptr_tcpip+=2;
		memcpy(r->buffer_tcpip+r->ptr_tcpip,&op2,2);
		r->ptr_tcpip+=2;
		break;
	case MOD_DISP: {
//		v10log(LOGNORMAL,"MOD_DISP. Escribiendo en buffer %d bytes\n",op1);
		memcpy(r->buffer_tcpip+r->ptr_tcpip,&op1,2);
		r->ptr_tcpip+=2;
//		v10log(LOGNORMAL,"MOD_DISP. Escribiendo en buffer %d bytes\n",op2); 
		memcpy(r->buffer_tcpip+r->ptr_tcpip,&op2,2);
		r->ptr_tcpip+=2;
		memcpy(r->buffer_tcpip+r->ptr_tcpip,buffer,op2);
		r->ptr_tcpip+=op2;
		break;
				   }

	case CWHO: {
		memcpy(r->buffer_tcpip+r->ptr_tcpip,&op1,2);
		r->ptr_tcpip+=2;
		break;
			   }

	case STATS:
		break;

	case DAM_EST: {
		memcpy(r->buffer_tcpip+r->ptr_tcpip,&op1,2);
		r->ptr_tcpip+=2;
		memcpy(r->buffer_tcpip+r->ptr_tcpip,&op2,2);
		r->ptr_tcpip+=2;
		break;
				  }

	case CONF: {
//		v10log(LOGNORMAL,"CONF. Escribiendo en buffer %d bytes\n",op2);
		memcpy(r->buffer_tcpip+r->ptr_tcpip,buffer,op2);
		r->ptr_tcpip+=op2;
		break;
			   }
	case PARPADEO:
		{
			memcpy(r->buffer_tcpip+r->ptr_tcpip,&op1,2);
			r->ptr_tcpip+=2;
		    // v10log(LOGNORMAL,"PARPADEO. Escribiendo en buffer %d bytes\n",op1);
			memcpy(r->buffer_tcpip+r->ptr_tcpip,buffer,op1);
			r->ptr_tcpip+=op1;
			break;
		}

	default: break;
	}
	if (r->ptr_tcpip>5000) {
		v10log(LOGERROR,"Aqui\n");
	}
	r->nbmsg_tcpip++;
	if (r->nbmsg_tcpip>=infotconfig.queue) {
		envia_tcpip(r);
	}
	LeaveCriticalSection(&infohcritical);
}


void infohstart(infotreddisps *r)
{
	if (r->numdisp) {
		infohlongbuffer(r,0,0);
		infohsend(START,r,0,0,NULL);
	}
}


void infohstop(infotreddisps *r)
{
	infohsend(CSTOP,r,0,0,NULL);
}


void infohwho(infotreddisps *r)
{
	strfill(r->buffer_salida+1,0xff,MAXELEMRED-1);
	r->buffer_salida[0]=0x02;
	r->buffer_salida[601]=0x55;
	infohlongbuffer(r,2+MAXELEMRED,MAXELEMRED);
	infohsend(MOD_DISP,r,0,2+MAXELEMRED,r->buffer_salida);
	infohsend(CWHO,r,1,0,NULL);									
}


void infohreset(infotreddisps *r)
{
	r->numerror=0;
	infohsend(RESET,r,0,0,NULL);
}


void infohlongbuffer(infotreddisps *r,int value_env,int value_rec) 
{
	if (!value_env) value_env=r->long_buffer;
	if (!value_rec) value_rec=r->numdisp*BYTESPORDISP;
	infohsend(LONG_BUFFER,r,value_env,value_rec,NULL);
}


void infohlimpia(infotreddisps *r)
{
	strfill(r->buffer_salida,0,MAX_BUFFER_ENV-1);
	strfill(r->buffer_entrada,0,MAX_BUFFER_REC-1); 
}


void infohresetstats(infotreddisps *r)
{
	infohsend(RESET_STATS,r,0,0,NULL);	
}


void infohreseterror(infotreddisps *r)
{
	infohsend(RESET_ERROR,r,0,0,NULL);	
}
void abreconexion(v10socks *s,int op,int bytes,char *buffer)
{
	int nt,nr;
	EnterCriticalSection(&infohcritical);
	for (nt=0;nt<infopick.numcards;nt++) {
		infotsios *t=infopick.t[nt];
		for (nr=0;nr<t->numred;nr ++) {
			infotreddisps *r=t->r+nr;
			if (r->pipe==s) {
				r->pipe->status=STSOCKREADY;
				v10log(LOGNORMAL,"Abierto socket %p de tarjeta %d red %d\n",s,nt,nr);
				if (r->numdisp>0) {
					infotgrabaconfig(t);
					infohreset(r);
					infohsend(MOD_DISP,r,0,r->long_buffer,r->buffer_salida);
					infohstart(r);
				}
			}
		}
	}
	LeaveCriticalSection(&infohcritical);
}

void cierraconexion(v10socks *s,int ip,int bytes,char *buffer)
{
	v10log(LOGNORMAL,"Cerrado socket %p\n",s);
}

#define MAXTCP 200
v10socks *abrecliente(char *dirip,char *servicio)
{
	v10socks *ret;
	v10horas habre=damecent();
	infohinit();
	ret=v10socknuevocliente(dirip,servicio,1,1024*4,abreconexion,abreconexion,NULL,NULL,cierraconexion);
	return(ret);
	if (ret==NULL) return(NULL);
	while (!v10socklisto(ret)) {
		if (damecent()-habre>MAXTCP) break;
	}
	if (v10socklisto(ret)==0) {
		v10socklibera(ret);
		return(NULL);
	}
	return ret;
}

void recupera_conexion(infotreddisps *r)
{	
	infotsios *t;
	char nbred;
	if (r->pipe) return;

	if (r->numdisp==0) return;
	if (r->pipe && r->pipe->status!=STSOCKROTA) return; 

	EnterCriticalSection(&infohcritical);
	t=r->t;
	if (r->pipe) v10socklibera(r->pipe);
	r->pipe=NULL;
	do {
		char servicio[MAXPATH];
		esperamensaje(1);
		nbred=r-t->r+'A';
		sprintf(servicio,"infopick%d",r-t->r+1);
		v10log(LOGNORMAL, "Conexión con línea %c de la tarjeta %s fallida (%d displays).\nReintentando recuperar conexión con red %c en tarjeta %s (%d displays).\n", nbred,t->dir_IP,r->numdisp,nbred,t->dir_IP,r->numdisp);
		r->pipe=abrecliente(t->dir_IP,servicio);
	} while (!r->pipe);
	v10log(LOGNORMAL, "Conexión con línea %c de la tarjeta %s recuperada\n\n", nbred,t->dir_IP);
	if (r->numdisp>0) {
		infotgrabaconfig(t);
		infohreset(r);
		infohsend(MOD_DISP,r,0,r->long_buffer,r->buffer_salida);
		infohstart(r);
	}
	r->stats_pend=damecent();
	LeaveCriticalSection(&infohcritical);
}