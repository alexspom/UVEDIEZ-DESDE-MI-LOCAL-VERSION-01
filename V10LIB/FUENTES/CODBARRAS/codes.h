
/* Definicion de las impresoras */
#define POSTCRIPT  0
#define EPSON120   1
#define PROPRIN    2
#define HPLS150    3
#define HPLS300    4
#define EPSONLQ    5
#define TOSH1340   6
#define OKIDATA    7
#define PROX24     8
#define HPRAS150   9
#define HPRAS300  10
#define HPDES150  11
#define HPDES300  12
#define HPPAINT   13

/* definicion de tipos de codigo de barra */
#define UPCA       1
#define UPCE       2
#define EAN_JAN13  3
#define EAN_JAN8   4
#define CODE39     5
#define EXT39      6
#define INT25      7
#define CODE128    8
#define CODABAR    9
#define POSTNET    10
#define MSI        11
#define CODE93     12
#define EXT93      13
#define UCC128     14
#define HIBC       15

/* Estructuras de datos */
#define CM_MAXBARLEN   80              /* Maximum Bar Code Input Text Length */
#define CM_MAXTEXTLEN  80              /* Maximum Text Input Length */
#define CM_MAXBARCNT   15              /* Maximum Bar Code Count */
#define CM_MAXHEIGHT   20              /* Maximum Bar Code Height */
#define CM_MAXACROSS   7	/* Maximum Bar Codes Across on Line */

struct CM_barparam {
   unsigned char text[CM_MAXTEXTLEN+1];
   int offset;
   int height;
   unsigned char barcode[CM_MAXBARLEN*4];/* max of 30 bits per bar code char */
   int barcnt;
   };

/* 0 = 11 digit, 1 = 6 digit system 0, 2 = 6 digit system 1 */
V10IMPORT unsigned int CM_UPCE_MODE;
extern unsigned char CM_NULLCHAR;   /* if set, encode this char to Null */
extern unsigned char CM_Wide;       /* set if should expand white space */
extern unsigned char CM_COUNTBYTE;  /* set if should only count bytes */
V10IMPORT char CM_3of9;                /* set if 3 of 9 bar code */
extern unsigned char CM_CR;         /* Carriage Return */
extern unsigned char CM_LF;         /* Line Feed */
V10IMPORT unsigned char CM_WIDEBAR;    /* dots for Wide Element */
V10IMPORT unsigned char CM_NARROWBAR;  /* dots for Narrow Element */

extern int BAR_WIDTH_COUNT;         /* bars to generate the wide way */
V10IMPORT int LANDSCAPE;               /* 1 if laser printer landscape */
V10IMPORT int DOTS;                    /* dot width of the bar */
V10IMPORT int CM_LPI;                  /* lines per inch for adjusting head */
V10IMPORT int CM_CPI;                  /* characters per inch for centering */
V10IMPORT int CM_RATIO;                /* bar code ratio */
V10IMPORT unsigned char CM_128TYPE;    /* Code 128 type-0=auto,1=A,2=B,3=C */
extern unsigned char CM_barcode[];  /* barcode storage area */
extern int CM_save_width_count;     /* count of how many bars generated */
extern struct CM_barparam CM_save[];   /* save location for barcode storage */
extern unsigned char *CM_barptr;
extern int CM_barcnt;
extern int CM_bitcnt;
extern unsigned int CM_printcnt;    /* number byte to print to printer */
extern unsigned char *CM_txtline[];
extern unsigned char CM_NEWSTR[];   /* storage for bar code string */
extern unsigned char savestr[];     /* storage for bar code string */
extern unsigned char CM_CHECKSUM;   /* storage for the checksum char */
extern unsigned char CM_CHECKSUM2;  /* storage for the second checksum */
extern unsigned char CM_MODE128;    /* storage for code 128 mode used */
#ifdef GENFNT
   extern unsigned char CM_FNTSTR[];
   extern unsigned char *CM_FNTPTR;
#endif /* GENFNT */
#ifdef FILEIO
   extern int CM_fhandle;
#endif /* FILEIO */

#define upper(c)    ((c) >= 'a' && (c) <= 'z' ? (c) - 32 : (c))

struct code;
/* Prototipos de las funciones */
V10IMPORT  int bar_code(char *ret_string,int bar_type,char *string,char *text,int printnum,
                        int offset,int height,int chksum,int passes);
int CM_generate(unsigned char *, int, unsigned char *, unsigned char *, struct code *,
                int, int, int, int);
void alternate(int, int);
void clearbar(void);
void addbar(unsigned int, int);
void append(unsigned char *, unsigned char);
int  chksum1(unsigned char *);
int chksum2(unsigned char *);
int chksum3(unsigned char *);
int chksum4(unsigned char *);
int chksum5(unsigned char *);
int chksum6(unsigned char *);
int chksum7(unsigned char *);
int two_sup(unsigned char *);
int five_sup(unsigned char *);
int UPC_A(int, unsigned char *, unsigned char *);
int UPC_E(int, unsigned char *, unsigned char *);
int UPC_E6(int, unsigned char *);

int EAN_13(unsigned char *, unsigned char *, unsigned char *);
int EAN_8(unsigned char *, unsigned char *);
unsigned char * findchr(unsigned char *, int);
void do_3x9(int,int);
int xthree_9(unsigned char *, int);
int three_9(unsigned char *, int);
int hibc(unsigned char *, int);
int xcode93(unsigned char *, int);
int code93(unsigned char *, int);
void do_2x5(unsigned int, int);
int two_5(unsigned char *, int);
int code128(unsigned char *, int, int);
int codabar(unsigned char *, int);
int postbar(unsigned char *);
void LPBar(struct code *, int, unsigned char **, int);
void LPZBar(struct code *, int, int, unsigned char **, int);
int msibar(unsigned char *, int);
void store_c(int, unsigned char **);
void store_s(unsigned char *,unsigned char **);
void printbar(unsigned char *, int, unsigned char *, int, struct code *, int, int);
void CM_SendCount(unsigned char **, int, int);
void CM_StoreBar(unsigned char **, int, int);
void CM_AddBar (int, int);
void CM_HPAdjust(unsigned char **, unsigned int *, int *);
void printmatrix(unsigned char *, unsigned char *, int, struct code *, int, int);
void printpscript(unsigned char *, int, struct code *, int);
void printlaser(unsigned char *, unsigned char *, int, struct code *, int);
void printdeskjet(unsigned char *, unsigned char *, int, struct code *, int);
void printllaser(unsigned char *, unsigned char *, int, struct code *, int);
void postmatrix(unsigned char *, int, struct code *, int);
void postpscript(unsigned char *, int, struct code *);
void postlaser(unsigned char *, int, struct code *);
void postdeskjet(unsigned char *, int, struct code *);
void postllaser(unsigned char *, int, struct code *);
void CM_DoPostnet(struct code *, int, unsigned char *, int,
                  unsigned char **, void(*)(struct code *, int, int,
	              unsigned char **, int), int, int, int);
void CM_DoBars(struct code *, unsigned char *, int,
               unsigned char **, void(*)(struct code *, int,
               unsigned char **, int));
V10IMPORT int barsize(int, unsigned char *, unsigned char *, int, int, int, int, int);
void CM_Copy(unsigned char *,unsigned char *, int);
int CM_textlength(unsigned char *);
/* Funciones de impresora */
struct code {
   unsigned char descript[30];         /* printer description */
   unsigned char init[15];             /* graphics initialization code */
				       /* sets graphics line feed on matrix */
   unsigned char begin1[10];           /* beginning code for graphics mode */
   unsigned char begin2[10];           /* additional chars to begin code */
   unsigned char end1[10];              /* ending code for graphics mode */
   unsigned char lpi_6[10];            /* code to reset to 6lpi text spacing */
   unsigned char lpi_8[10];            /* code to reset to 8lpi text spacing */
   unsigned char sml_lf[10];           /* code for 1/sml_lf_ht in. line feed */
   int sml_lf_ht;                      /* divisor of the above line feed */
   unsigned char code_type;            /* code type */
   long dpi;                            /* dots per inch resolution */
   long lpi;                            /* lines per inch resolution (*10) */
				       /* (lpi is ignored for PostScript) */
   };

/******************************************************************************
Available Code Types Are:

 255 - Postscript
   1 - 9 pin printers
   2 - 24 pin printers (send 4 bytes of 6 bits per print head pass)
   3 - 24 pin printers (send 3 bytes of 8 bits per print head pass)
   4 - Okidata microline "standard model" printer (many years old)
   6 - HP Laserjet (using macros to repeat the bar code elements)
   7 - HP Laserjet (using bit map raster graphics to generate the bar code)
   8 - HP Deskjet (portrait only).  Uses raster graphics and position cursor)
******************************************************************************/

#define PRINTERS 14


extern struct code CM_codes[PRINTERS];

extern unsigned char CM_StartMacro[];
extern unsigned char CM_StopMacro[];
extern unsigned char CM_ExecuteMacro[];
extern unsigned char CM_DeleteMacro[];
extern unsigned char CM_Push[];
extern unsigned char CM_Pop[];
extern unsigned char CM_PosCsr[];
