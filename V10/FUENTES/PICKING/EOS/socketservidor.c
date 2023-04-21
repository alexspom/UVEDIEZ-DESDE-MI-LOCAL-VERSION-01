#include "eos.h"

int puerto=16668;
int debug_s=1;
extern conf_rabbit confRabbit;

int captar_Mensaje (unsigned char **cadena, unsigned char **posicion, int descriptor_hijo)
{
// 	unsigned char *p;
	int buffer, recibido, ret;
	buffer=*cadena+MAXBUFFER-*posicion;
// 	p=*posicion;
	recibido=recv(descriptor_hijo, (void*)*posicion, buffer, 0);
	while (1){
		switch(recibido){
			case (-1):
				if (debug_s)
					if (errno!=11) {
						escribe_log(2, "Error en captar_Mensaje (recv): %s\n", strerror(errno));
						return (-1);
					}
					else {
						escribe_log(2, "¡¡Nadie me habla!!\n");
						return (0);
					}
				break;
			case (0):
				printf("El error está aquí: %s\n", strerror (errno));
//				if ((errno==EINTR || errno==EAGAIN)) usleep (1000);
				if (*cadena=='\0' ||strlen(*cadena)==0 || errno!=0) {
					escribe_log (2, "El cliente ha cortado la conexión.\n");
					return (-1);
				}
				printf("Me llegan %i caracteres.\n", strlen(*cadena));
			default:
				if (recibido==buffer)
					if (*(*cadena+MAXBUFFER-1)==0xff && recibido!=1) {
						*posicion=*cadena;
						return (1);
					}
					else {
						*posicion=*cadena;
						recibido=recv(descriptor_hijo, (void*)*cadena, MAXBUFFER, 0);
					}
				*posicion+=recibido*sizeof(char);
				return (1);
		}
	}
	return (-1);
}

int mandar_Mensaje(int descriptor_hijo, unsigned char *mensaje, unsigned char **posicion)
{
	int mandados, longcadena, i;
	unsigned char *p, *pp, *cadena;
	p=*posicion+sizeof(char);
	longcadena=2;
	while (*p!=0xff ) {
		if (p==mensaje+MAXBUFFER-1) p=mensaje;
		else p++;
		longcadena++;
	}
	p=*posicion;
	cadena=malloc (longcadena*sizeof(char));
	pp=cadena;
	for (i=0; i<=longcadena-1; i++){
		*(pp++)=*p;
		if (p==mensaje+MAXBUFFER-1) p=mensaje;
		else p++;
	}
// 	escribe_log(2, "cadena->'%d\n",cadena[0]);
	switch(mandados=send (descriptor_hijo, (void*)cadena, longcadena, 0)){
		case (-1):
			if (debug_s)  {
				if (errno==EPIPE) escribe_log(2, "Error en mandar_Mensaje (send): El cliente ha cortado la conexión\n");
				else  escribe_log(2, "Error en mandar_Mensaje (send): %s\n", strerror(errno));
				}
			break;
		case (0):
			if ((errno==EINTR || errno==EAGAIN)) usleep (1000);
			if (mandados<strlen(mensaje)+1) {
				escribe_log (2, "El cliente ha cortado la conexión.\n");
				free (cadena);
				return (-10);
			}
		default:
			*posicion=p;
			free (cadena);
			return (1);
	}
	free (cadena);
	return (-10);
}

 void *hiloLinea (void *param)
{
	struct timeval espera;
	thr_param_t *dato;
	int descriptor, descriptor_hijo, long_dir_remota, salida, respuesta_select;
	struct sockaddr_in direccion_local;
	struct sockaddr_in direccion_remota;
	fd_set esperando_a_leer, esperando_a_escribir;
	espera.tv_sec=0;
	espera.tv_usec=confRabbit.espera_mensaje;
	dato=(thr_param_t*)param;
// 	FD_ZERO(&esperando_a_leer);
	lwfd_zero(&esperando_a_leer);
// 	FD_ZERO(&esperando_a_escribir);
	lwfd_zero(&esperando_a_escribir);
	long_dir_remota=sizeof (struct sockaddr);
	direccion_local.sin_family = AF_INET;
	direccion_local.sin_port = htons(puerto);
	direccion_local.sin_addr.s_addr =htonl(INADDR_ANY);
	memset(&(direccion_local.sin_zero), '\0', 8);
	while (1){
		salida=1;
// 		descriptor=socket(PF_INET, SOCK_STREAM, 0);
		descriptor=lwsocket(PF_INET, SOCK_STREAM, 0);
		if (descriptor<3) escribe_log (2, "Descriptor vale %i: %s\n", descriptor, strerror(errno));
		if ((bind (descriptor, (struct sockaddr *)&direccion_local, sizeof (struct sockaddr)))!=-1) {
// 			if ((listen(descriptor,1))!=-1) {
			if ((lwlisten(descriptor,1))!=-1) {
				if ((descriptor_hijo = accept (descriptor, (struct sockaddr*)&direccion_remota, &long_dir_remota))!=-1){
// 					fcntl(descriptor_hijo, F_SETFL, O_NONBLOCK);
					lwfcntl(descriptor_hijo, F_SETFL, O_NONBLOCK);
// 					if (close (descriptor)==-1) escribe_log(2, "Error cerrando descriptor(0): %s\n", strerror(errno));
					if (lwclose (descriptor)==-1) escribe_log(2, "Error cerrando descriptor(0): %s\n", strerror(errno));
					if (debug_s) escribe_log(2, "Conectado con: %s\n", inet_ntoa(direccion_remota.sin_addr));
					while (salida>=0){
// 						FD_SET(descriptor_hijo, &esperando_a_leer);
						lwfd_set(descriptor_hijo, &esperando_a_leer);
						espera.tv_usec=confRabbit.espera_mensaje;
						if (dato->nuevo_mensaje_ida) {
// 							FD_SET(descriptor_hijo, &esperando_a_escribir);
							lwfd_set(descriptor_hijo, &esperando_a_escribir);
// 							respuesta_select=select (descriptor_hijo+1, &esperando_a_leer, &esperando_a_escribir, NULL, &espera);
							respuesta_select=lwselect (descriptor_hijo+1, &esperando_a_leer, &esperando_a_escribir, NULL, &espera);
						}
						else
// 							respuesta_select=select (descriptor_hijo+1, &esperando_a_leer, NULL, NULL, &espera);
							respuesta_select=lwselect (descriptor_hijo+1, &esperando_a_leer, NULL, NULL, &espera);
						salida=1;
						if (respuesta_select>0) {
// 							if (FD_ISSET (descriptor_hijo, &esperando_a_leer)) {
							if (lwfd_isset (descriptor_hijo, &esperando_a_leer)) {
								salida=captar_Mensaje (&dato->cadena_vuelta, &dato->cadena_vuelta_escritura, descriptor_hijo);
								if (salida==1) dato->nuevo_mensaje_vuelta++;
							}
// 							if (FD_ISSET (descriptor_hijo, &esperando_a_escribir)) {
							if (lwfd_isset (descriptor_hijo, &esperando_a_escribir)) {
								if (salida!=-1 && dato->nuevo_mensaje_ida>0){
									salida=mandar_Mensaje (descriptor_hijo, dato->cadena_ida, &dato->cadena_ida_lectura);
// 									FD_CLR (descriptor_hijo, &esperando_a_escribir);
									lwfd_clr (descriptor_hijo, &esperando_a_escribir);
									if (salida>0)
										dato->nuevo_mensaje_ida--;
								}
							}
						}
						else
							if (respuesta_select==-1 && debug_s) escribe_log(2, "Error en select\n");
// 						FD_CLR (descriptor_hijo, &esperando_a_escribir);
						lwfd_clr(descriptor_hijo, &esperando_a_escribir);
					}
					FD_CLR (descriptor_hijo, &esperando_a_leer);
					if (lwclose (descriptor_hijo)==-1) escribe_log(2, "Error cerrando descriptor_hijo(1): %s\n", strerror(errno));
					if (close (descriptor_hijo)==-1) escribe_log(2, "Error cerrando descriptor_hijo(1): %s\n", strerror(errno));
				}
				else {
					if (debug_s) escribe_log(2, "Error en  (accept): %s\n", strerror(errno));
// 					if (close (descriptor_hijo)==-1) escribe_log(2, "Error cerrando descriptor_hijo(2): %s\n", strerror(errno));
					if (lwclose (descriptor_hijo)==-1) escribe_log(2, "Error cerrando descriptor_hijo(2): %s\n", strerror(errno));
				}
			}
			else {
				if (debug_s) escribe_log(2, "Error en  (listen): %s\n", strerror(errno));
// 				if (close (descriptor)==-1) escribe_log(2, "Error cerrando descriptor(1): %s\n", strerror(errno));
				if (lwclose (descriptor)==-1) escribe_log(2, "Error cerrando descriptor(1): %s\n", strerror(errno));
			}
		}
		else {
			if (debug_s)  escribe_log(2, "Error en  bind: %s\n", strerror(errno));
			if (errno==98) usleep (1000000);
// 			if (close (descriptor)==-1) escribe_log(2, "Error cerrando descriptor(2): %s\n", strerror(errno));
			if (lwclose (descriptor)==-1) escribe_log(2, "Error cerrando descriptor(2): %s\n", strerror(errno));
		}
	}
}
