/*************************************************************************************************
* Módulo: VDERROR.H
* Propósito: Declaración de los identificadores de mensajes almacenados en la base de datos
* Autor: Construcción automática
* Fecha: 28-02-2008
**************************************************************************************************/


#ifndef __VDERROR__H__
#define __VDERROR__H__

// Modulo 1 SISTEMA DE PASSWORD
#define VD_EPASSCORTO		0xC0010001		/* PASSWORD DEMASIADO CORTO */
// Modulo 2 KERNEL
#define VD_EERR		0xC0020001		/* ERROR1 */
#define VD_ESINALG		0xC0020002		/* SIN ALGORITMO */
#define VD_ESTNOEXISTE		0xC0020003		/* ESTATUS NO EXISTE */
// Modulo 3 ERRORES ORACLE
#define VD_EREGMODIF		0xC0030001		/* REGISTRO MODIFICADO POR OTRO USUSARIO */
#define VD_EERRORACLE		0xC0030002		/* ERROR ORACLE */
#define VD_EERRBLOQUEO		0xC0030003		/* BLOQUEO DE ORACLE */


#endif
