/*******************************************************************************
* Módulo : v10encripta.c                                                       *
* Función: Bajo nivel de comunicacion con criptoapi de windows                 *
*                                                                              *
*                                                                              *
* Autor	 : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 10-01-2007                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*
*******************************************************************************/

#include "v10.h"

#define MAXHEXA MAXCADENA


static HCRYPTPROV hCryptProv;
static int init;

static void fincrypto(void)
{
	if(hCryptProv) CryptReleaseContext(hCryptProv, 0);
}

static void initcrypto(void)
{
	
	if (init) return;
	init=1;
	if (CryptAcquireContext(&hCryptProv,NULL,NULL,PROV_RSA_FULL,0)) {
		v10log(LOGDEBUG,"Adquirido contexto criptografico.\n");
	} else {
        if (GetLastError() == NTE_BAD_KEYSET) {
            if (CryptAcquireContext(&hCryptProv,NULL,NULL,PROV_RSA_FULL,CRYPT_NEWKEYSET)==0) {
 				final(("Error al inicializar criptografia."));
			}
		} else 
			final(("Error al adquirir contexto criptografico"));
	}
	atexit(fincrypto);
}

static int digitohexa(int a)
{
	int ret;
	if (a>9) ret=a-10+'A';
	 else	  ret=a+'0';
	return(ret);
}

static char *pasaahexa(char *origen,int len,char *destino)
{
	char mihexa[MAXHEXA],*ptr;
	int i;
	if (destino==NULL) destino=mihexa;
	ptr=destino;
    for (i=0;i<len;i++) {
        *ptr++=digitohexa(origen[i]>>4);
		*ptr++=digitohexa(origen[i]&0xf);
	}
	*ptr=0;
	return(destino);
}

static int hexa2int(char *origen)
{
	int ret;
	ret=((*origen>'9'?*origen-'A'+10:*origen-'0')<<4)+(origen[1]>'9'?origen[1]-'A'+10:origen[1]-'0');
	return(ret);
}

static char *pasadehexa(char *origen,char *destino,int *lon)
{
	char *ptr=destino;
	while (*origen) {
		*ptr++=hexa2int(origen);
		origen+=2;
	}
	*lon=ptr-destino;
	return destino;
}

int damehash(char *origen,char *hash)
{
    HCRYPTHASH hHash;
    DWORD dwLength;
	char mihash[MAXHASH];
	DWORD lmihash;
	initcrypto();
    dwLength = strlen(origen);
	if (!CryptCreateHash(hCryptProv,CALG_SHA,0,0,&hHash)) {
		int ret=GetLastError();
		v10log(LOGERROR,"Error al ejecutar CryptCreateHash %x",ret);
		return(ret);
	}
	if(!CryptHashData(hHash,(BYTE *)origen,dwLength,0)) {
		int ret=GetLastError();
		v10log(LOGERROR,"Error al ejecutar CryptHashData %x",ret);
		return(ret);
	}
	lmihash=sizeof(mihash);
	if (CryptGetHashParam(hHash,HP_HASHVAL,mihash,&lmihash,0)) {
		pasaahexa(mihash,lmihash,hash);
		CryptDestroyHash(hHash);
	} else {
		int ret;
		ret=GetLastError();
		v10log(LOGERROR,"Error al obtener el hash %x\n",ret);
		return(ret);
	}
	return(0);
}

int compruebahash(char *origen,char *hash)
{
	int ret;
	char destino[MAXHASH];
	ret=damehash(origen,destino);
	if (ret) return(ret);
	if (strcmp(hash,destino)!=0) {
		return(-1);
	}
	return(0);
}

HCRYPTKEY dameclave(char *pass)
{
	HCRYPTKEY hKey;
    HCRYPTHASH hHash;
    DWORD dwLength;
	DWORD lmihash;
	char mihash[MAXHASH];
	char hash[MAXHASH];
	initcrypto();
	dwLength = strlen(pass);
	
	if (!CryptCreateHash(hCryptProv,CALG_SHA,0,0,&hHash)) {
		int ret=GetLastError();
		v10log(LOGERROR,"Error al ejecutar CryptCreateHash %x",ret);
		return(0);
    }
	if (!CryptHashData(hHash,(BYTE *)pass,dwLength,0)) {
		int ret=GetLastError();
		v10log(LOGERROR,"Error al ejecutar CryptHashData %x",ret);
		return(0);
	}
	lmihash=MAXHASH;
	if (CryptGetHashParam(hHash,HP_HASHVAL,mihash,&lmihash,0)) {
		pasaahexa(mihash,lmihash,hash);
	} else {
		int ret=GetLastError();
		v10log(LOGERROR,"Error al obtener el hash %x",ret);
		return(0);
	}	
	if (!CryptDeriveKey(hCryptProv,CALG_3DES,hHash,CRYPT_EXPORTABLE,&hKey)) {
		int ret=GetLastError();
		v10log(LOGERROR,"Error al ejecutar CryptDeriveKey %x",ret);
		return(0);
	}
	if(hHash) CryptDestroyHash(hHash);
	return(hKey);
}

int genfirma(HCRYPTKEY keysesion,char *priv,char *pub)
{
	HCRYPTKEY hpriv;
	DWORD lmiclavepri;
	char miclavepri[MAXCADENA];
	initcrypto();
	if (CryptGenKey(hCryptProv,AT_SIGNATURE,CRYPT_EXPORTABLE,&hpriv)) {
		v10log(LOGDEBUG,"Generada clave publica/privada\n");
	} else {
		int ret=GetLastError();
		v10log(LOGERROR,"Error al generar clave publica/privada %x",ret);
		return(ret);
	}
	lmiclavepri=MAXCADENA;
	if (CryptExportKey(hpriv,0,PUBLICKEYBLOB,0,miclavepri,&lmiclavepri)) {
		pasaahexa(miclavepri,lmiclavepri,pub);
		v10log(LOGDEBUG,"Creado el BLOB de clave publica %s\n",pub);
	} else {
		int ret=GetLastError();
		v10log(LOGERROR,"Error al exportar clave publica %x",ret);
		return(ret);
	}
	lmiclavepri=MAXCADENA;
	if (CryptExportKey(hpriv,keysesion,PRIVATEKEYBLOB,0,miclavepri,&lmiclavepri)) {
		pasaahexa(miclavepri,lmiclavepri,priv);
		v10log(LOGDEBUG,"Creada la de clave privada %s\n",priv);
	} else {
		int ret=GetLastError();
		v10log(LOGERROR,"Error al exportar clave privada %x",ret);
		return(ret);
	}
	if (hpriv) CryptDestroyKey(hpriv);
	return(0);
}

int recodificafirma(char *oldpwd,char *newpwd,char *cpriv)
{
	HCRYPTKEY session,hpriv;
	char miclavepri[MAXCADENA];
	DWORD lmiclavepri;
	int ret;
	session=dameclave(oldpwd);
    hpriv=dameclaveprivada(session,cpriv);
	CryptDestroyKey(session);
	session=dameclave(newpwd);
	lmiclavepri=MAXCADENA;
	if (CryptExportKey(hpriv,session,PRIVATEKEYBLOB,0,miclavepri,&lmiclavepri)!=0) {
	   pasaahexa(miclavepri,lmiclavepri,cpriv);
	   ret=0;
	} else {
		ret=GetLastError();
	}
	CryptDestroyKey(session);
	CryptDestroyKey(hpriv);
	return(ret);
}


int encriptasesion(HCRYPTKEY hkey,char *cadena,char *destino)
{
	char temp[MAXCADENA];
	int lon;
	initcrypto();
	pasadehexa(cadena,temp,&lon);
	if (!CryptEncrypt(hkey,0L,TRUE,0,temp,&lon,MAXCADENA)) {
		int ret;
		ret=GetLastError();
		v10log(LOGERROR,"Al encriptar la cadena %x\n",ret);
		return(ret);
	}
	pasaahexa(temp,lon,destino);
	return(0);
}

int desencriptasesion(HCRYPTKEY hkey,char *cadena,char *destino)
{
	char temp[MAXCADENA];
	int lon;
	initcrypto();
	pasadehexa(cadena,temp,&lon);
	if (!CryptDecrypt(hkey,0L,TRUE,0,temp,&lon)) {
		int ret;
		ret=GetLastError();
		v10log(LOGERROR,"Al desencriptar la cadena %x\n",ret);
		return(ret);
	}
	pasaahexa(temp,lon,destino);
	return(0);
}

HCRYPTKEY dameclavepublica(char *pub)
{
	HCRYPTKEY hpub;
	char temp[MAXCADENA];
	int lon;
	int ret=0;
	initcrypto();
    pasadehexa(pub,temp,&lon);
	if (!CryptImportKey(hCryptProv,temp,lon,0,AT_SIGNATURE,&hpub)) {
		int ret;
		ret=GetLastError();
		v10log(LOGERROR,"Al importar la clave publica error %x\n",ret);
		return(0);
	}
	return hpub;
}

HCRYPTKEY dameclaveprivada(HCRYPTKEY hkey,char *priv)
{
	HCRYPTKEY hpriv;
	char temp[MAXCADENA];
	int lon;
	int ret=0;
	initcrypto();
    pasadehexa(priv,temp,&lon);
	if (!CryptImportKey(hCryptProv,temp,lon,hkey,CRYPT_EXPORTABLE,&hpriv)) {
		int ret;
		ret=GetLastError();
		v10log(LOGERROR,"Al importar la clave privada error %x\n",ret);
		return(0);
	}
	return hpriv;
}

int firmadatosh(HCRYPTKEY hpriv,char *cadena,char *destino)
{
	char temp[MAXCADENA],temp1[MAXCADENA];
	int lon,lon1;
	HCRYPTHASH hash;
	initcrypto();

	pasadehexa(cadena,temp1,&lon1);
	CryptCreateHash(hCryptProv,CALG_MD5,0,0,&hash);
	CryptHashData(hash,temp1,lon1,0);
	lon=MAXCADENA;
	if (!CryptSignHash(hash,AT_SIGNATURE,NULL,0,temp,&lon)) {
		int ret;
		ret=GetLastError();
		return(ret);
	}
	if (hash) if (!CryptDestroyHash(hash)) {
		return(GetLastError());
	}
	pasaahexa(temp,lon,destino);
	return(0);
}

int firmadatos(HCRYPTKEY hpriv,char *cadena,char *destino)
{
	char temp[MAXCADENA];
	pasaahexa(cadena,strlen(cadena),temp);
	return(firmadatosh(hpriv,temp,destino));
}

int verificafirmah(HCRYPTKEY hpub,char *cadena,char *firma)
{
	char temp[MAXCADENA];
	int lon;
	int ret=0;
	HCRYPTHASH hash;
	initcrypto();
	pasadehexa(cadena,temp,&lon);
	CryptCreateHash(hCryptProv,CALG_MD5,0,0,&hash);
	CryptHashData(hash,temp,lon,0);
	pasadehexa(firma,temp,&lon);
	if (!CryptVerifySignature(hash,temp,lon,hpub,NULL,0))	{
		v10log(LOGNORMAL,"La firma no verifica\n");
		ret=-1;
	}
	if (hash) CryptDestroyHash(hash);
	return(ret);
}

int verificafirma(HCRYPTKEY hpub,char *cadena,char *firma)
{
	char temp[MAXCADENA];
	pasaahexa(cadena,strlen(cadena),temp);
	return(verificafirmah(hpub,temp,firma));
}
 
