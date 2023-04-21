/************************************************/
/*               Bar Code Library               */
/*   Copyright (C) 1988-1992, StrandWare, Inc.  */
/*             All Rights Reserved              */
/************************************************/

#include "../v10.h"
/* 0 = 11 digit, 1 = 6 digit system 0, 2 = 6 digit system 1 */
   unsigned int CM_UPCE_MODE = 0;
   unsigned char CM_NULLCHAR = 0;      /* if set, encode this char to Null */
   unsigned char CM_Wide = 0;          /* set if should expand white space */
   unsigned char CM_COUNTBYTE = 0;     /* set if should only count bytes */
   char CM_3of9 = 0;                   /* set if 3 of 9 bar code */
   unsigned char CM_CR = '\r';         /* Carriage Return */
   unsigned char CM_LF = '\n';         /* Line Feed */
   unsigned char CM_WIDEBAR = 3;       /* dots for Wide Element */
   unsigned char CM_NARROWBAR = 1;     /* dots for Narrow Element */

   int BAR_WIDTH_COUNT = 1;            /* bars to generate the wide way */
   int LANDSCAPE = 0;                  /* 1 if laser printer landscape */
   int DOTS = 2;                       /* dot width of the bar (2 is best) */
   int CM_LPI = 6;                     /* lines per inch for adjusting head */
   int CM_CPI = 10;                    /* characters per inch for centering */
   int CM_RATIO = 3;                   /* bar code ratio */
   unsigned char CM_128TYPE = 0;       /* Automatic Code 128 Generation */
				       /* 0 = auto, 1 = A, 2 = B, 3 = C */
   unsigned char CM_barcode[CM_MAXBARLEN*4];    /* barcode storage area */
   int CM_save_width_count = 1;        /* count of how many bars generated */
   struct CM_barparam CM_save[CM_MAXACROSS+2]; /* barcode storage area */
   unsigned char *CM_barptr;
   int CM_barcnt;
   int CM_bitcnt;
   unsigned int CM_printcnt;           /* number bytes to print to printer */
   unsigned char *CM_txtline[CM_MAXHEIGHT];/* storage for text lines for matrix */
   unsigned char CM_NEWSTR[(CM_MAXBARLEN+1)*2]; /* storage for bar code string */
   unsigned char savestr[CM_MAXBARLEN+1]; /* storage for bar code string */
   unsigned char CM_CHECKSUM;          /* storage for the checksum char */
   unsigned char CM_CHECKSUM2;         /* storage for the second checksum */
   unsigned char CM_MODE128;           /* storage for code 128 mode used */
#ifdef GENFNT
   unsigned char CM_FNTSTR[80];
   unsigned char *CM_FNTPTR;
#endif /* GENFNT */
#ifdef FILEIO
   int CM_fhandle;
#endif /* FILEIO */

struct code CM_codes[PRINTERS] = {
/**************************************************************************/
/* for PostScript printers, set the dpi structure variable to an even     */
/* multiple of your printers resolution.  It is set to 150 now for a 300  */
/* dpi printer.  This makes the 1 dot wide element 1/150 of an inch.  The */
/* lpi structure variable is ignored for the PostScript printer.          */
/**************************************************************************/
   {  /* Postscript Printer */ "",
      "", "", "",
      "", "", "", "", 255, 255, 150, 150 },
   {  /* EPSON - 120 */ "",
      { 27,'A',8,27,'2',27,'A',8 }, { 27,'L' }, "",
      "", { 27,'A',12,27,'2' }, { 27,'0' }, { 27,'A','?'}, 72, 1, 120, 90 },
   {  /* Proprinter - 120 */ "",
      { 27,'3',24 }, { 27,'L' }, "",
      "", { 27,'A',12,27,'2' }, { 27,'0' }, { 27,'3','?' }, 216, 1, 120, 90 },
   {  /* HP LaserJet - 150 */ "",
      "\033*t150R\033*r1A", "\033*b", "W",
      "\033*rB", "","", "\033&l??C", 48, 6, 150, 1500 },
   {  /* HP LaserJet - 300 */ "",
      "\033*t300R\033*r1A", "\033*b", "W",
      "\033*rB", "","", "\033&l??C", 48, 6, 300, 3000 },
   {  /* EPSON LQ - 120 */ "",
      { 27,'3',20 }, { 27,'*',33 }, "",
      "", { 27,'2' }, { 27,'0' }, { 27,'3','?'}, 180, 3, 120, 90 },
   {  /* Toshiba P1340 - 180 */ "",
      "\033L06", "\033;", "",
      "", "\033L08", "\033L06", "\033L??", 48, 2, 180, 90 },
   {  /* Okidata Microline - 102 */ "",
      { 29, 27,'%','9',14 }, "\03", "",
      { 3,2 }, { 27,'6' }, { 27,'8' }, "\033%9?", 144, 4, 102, 90 },
   {  /* IBM PROPRINTER X24 - 120 */ "",
      { 27,'3',24 }, { 27,'[','g' }, { 9 },
      "", { 27,'3',36 }, { 27,'0' }, { 27,'3','?'}, 216, 3, 120, 90 },
   {  /* HP LaserJet (Raster) - 150 */ "",
      "\033*t150R\033*r1A", "\033*b", "W",
      "\033*rB", "","", "\033&l??C", 48, 7, 150, 1500 },
   {  /* HP LaserJet (Raster) - 300 */ "",
      "\033*t300R\033*r1A", "\033*b", "W",
      "\033*rB", "","", "\033&l??C", 48, 7, 300, 3000 },
   {  /* HP DeskJet (Raster) - 150 */ "",
      "\033*t150R\033*r1A", "\033*b", "W",
      "\033*rB", "","", "\033&l??C", 48, 8, 150, 1500 },
   {  /* HP DeskJet (Raster) - 300 */ "",
      "\033*t300R\033*r1A", "\033*b", "W",
      "\033*rB", "","", "\033&l??C", 48, 8, 300, 3000 },
   {  /* HP PaintJet (Raster) - 180 */ "",
      "\033*t180R\033*r1A", "\033*b", "W",
      "\033*rB", "","", "\033&l??C", 48, 8, 180, 1800 }
};

/*unsigned char CM_StartMacro[]   = "\033&f10y0X";*/
unsigned char CM_StartMacro[]   = "\033&f10y0X";
unsigned char CM_StopMacro[]    = "\033&f1X";
unsigned char CM_ExecuteMacro[] = "\033&f2X";
unsigned char CM_DeleteMacro[]  = "\033&f8X";
unsigned char CM_Push[]         = "\033&f0S";
unsigned char CM_Pop[]          = "\033&f1S";
/* used for Deskjet */
unsigned char CM_PosCsr[]       = "\033*b";

/***
*   barcode.c
*
*   Bar code interface functions for C.
*
*   This function is called with:
*
* char *ret_string;
* int length;
*
* length = barsize(bar_type,string,text,printnum,offset,height,chksum,passes);
* ret_string = malloc(length);
* length = bar_code(ret_string,bar_type,string,text,printnum,offset,height,chksum,passes);
* fwrite(ret_string,1,length,stdprn);
* free(ret_string);
*
*       int length =                   length of the returned string in bytes
*                                      -1 if ret_string invalid
*                                      -2 if bar_type invalid
*                                      -3 if string invalid
*                                      -4 if text invalid
*                                      -5 if printnum invalid
*                                      -6 if offset invalid
*                                      -7 if height invalid
*                                      -8 if chksum not 1 or 0
*                                      -9 if passes wrong
*                                      -10 if bar code generation error
*       char *ret_string =             array of characters to store code to
*       unsigned bar_type =            Simbologia
*       char *string =                 the character string to bar code
*       char *text =                   the character string to print under bar
*       unsigned printnum =            Impresora
*       unsigned offset =              number of characters from left margin
*                                          to indent.
*       unsigned height =              bar code height in 1/10 inch units
*                                          (max units = 20)
*       Boolean chksum =               whether to print checksum when optional
*       int passes =                   number of overstrike passes to print
**/

int bar_code(char *ret_string,int bar_type,char *string,char *text,int printnum,
         int offset,int height,int chksum,int passes)
{
  int error,ret_code;
  error = 0;
  if (!ret_string)   error = -1;
  if (bar_type > CM_MAXBARCNT || bar_type < 1)   error = -2;
  if (strlen(string) > CM_MAXBARLEN || !string)  error = -3;
  if (strlen(text) > CM_MAXTEXTLEN || !text)     error = -4;
  if (printnum > PRINTERS)                       error = -5;
  if (offset > 250)                              error = -6;
  if (height > CM_MAXHEIGHT || height < 1)       error = -7;
  if (chksum > 2 || chksum < 0)                  error = -8;
  if (passes > 5 || passes < 1)                  error = -9;
  if (!error) {
     ret_code = CM_generate(ret_string, bar_type, string, text,
                &CM_codes[printnum], offset, height, chksum, passes);
     if (ret_code < 0)  error = -10;
        else            error = ret_code;
   }
  if (CM_printcnt > 32767)  error = -11;
  if (!error)  return ((int) CM_printcnt);
     else      return (error);
}

