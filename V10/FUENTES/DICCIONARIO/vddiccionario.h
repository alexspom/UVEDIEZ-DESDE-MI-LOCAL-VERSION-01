// Definición de las estructuras de diccionarios
typedef struct {
	char *nombre;
	int  tipo;
	size_t  offset;
	int  lon;
} diccols;

typedef struct {
	diccols *c;
	int     numcol;
} diccionarios;

typedef struct {
	diccionarios *d;
	int     numdic;
} diccionario;

// Prototipos de las funciones exportadas
VDEXPORT int vverificacampos(void *d1,void *d2,diccionarios *dic,va_list arg);
VDEXPORT void DICbuff2tabla(diccionario *dic,char *campo,int inicio,int lon, int decimales, char *defecto, char *bufferin,void *objeto);
VDEXPORT void debugestruct(diccionario *dic,void *estruc, char *mensaje);
VDEXPORT void DICdameoffset(diccionario *dic, void *estruc);