/************************************************/
/*               Bar Code Library               */
/*   Copyright (C) 1988-1992, StrandWare, Inc.  */
/*             All Rights Reserved              */
/************************************************/

#include "../v10.h"

/***
*
*   cm_generate()
*
*   Generates the Bar Code codes to print.
*
*   This function is called with:
*      error = cm_generate(ret_string, bar_type, string, text, CM_codes[printnum],
*                        offset, height, chksum, passes)
*
*       ret_string =                   string to store codes to.
*       bar_type =                     bar code type to print:
*       string =                       string to bar code
*       text =                         string to print under bar code
*       CM_codes =                     code structure ptr for printer codes.
*       offset =                       number of characters from left margin
*                                          to indent.
*       height =                       bar code height in 1/10 inch units
*                                          (max units = 10).
*       chksum =                       whether to print checksum if optional.
*       passes =                       number of strike over passes to print.
*
**/

/****************************************************************/
/* The following contains the tables for each of the bar codes. */
/****************************************************************/

/****************************************************************/
int CM_generate(unsigned char *ret_string, int bar_type, unsigned char *string, unsigned  char *text, struct code *codes, int offset, int height, int chksum, int passes)
{
  register int error;
  unsigned char *ptr;
  int printed;

   CM_Copy(savestr,string,0);          /* make copy of the bar code string */
   string = savestr;
   CM_Copy(CM_NEWSTR, string, 0);      /* copy string to save area also */

   CM_Wide = 0;

   printed = CM_CHECKSUM = CM_CHECKSUM2 = CM_3of9 = 0;
   switch (CM_RATIO) {
      case 1:                          /* 2:1 ratio */
              CM_WIDEBAR = 2;
              CM_NARROWBAR = 1;
              break;
      case 2:                          /* 2.5:1 ratio */
              CM_WIDEBAR = 5;
              CM_NARROWBAR = 2;
              break;
      default:                         /* 3:1 ratio */
              CM_WIDEBAR = 3;
              CM_NARROWBAR = 1;
              break;
   }

   switch (bar_type) {
      default:                         /* invalid bar type */
              error = 1;
              break;

      case CODE39:                          /* 3 of 9 code */
              error = strlen((char *)string) > CM_MAXBARLEN;
              CM_3of9 = 1;
              if (!error)  error = three_9(string,chksum);
              break;

      case INT25:                          /* interleaved 2 of 5 code */
		   error = strlen((char *)string) > CM_MAXBARLEN;
              if (!error)   error = two_5(string,chksum);
              break;

      case CODE128:                          /* code 128 code */
		   error = strlen((char *)string) > CM_MAXBARLEN;
              if (!error)  error = code128(string, 0, 1);
              break;
   }

   ptr = findchr(text,'_');            /* if checksum plug character */

   if (ptr && CM_CHECKSUM)
      *ptr = CM_CHECKSUM;
   if (error > 0)
      error = -error;
   if (!error && !printed) {
      if (BAR_WIDTH_COUNT != 1 && CM_save_width_count <= CM_MAXACROSS) {
         CM_Copy(CM_save[CM_save_width_count].text,text,0);
         CM_save[CM_save_width_count].offset = offset;
         CM_save[CM_save_width_count].height = height;
         CM_Copy(CM_save[CM_save_width_count].barcode,CM_barcode,CM_MAXBARLEN*4);
         CM_save[CM_save_width_count].barcnt = CM_barcnt;
       }
      if (CM_save_width_count >= BAR_WIDTH_COUNT)   {
         printbar(ret_string,bar_type,text,offset,codes,height,passes);
         if (!CM_COUNTBYTE) CM_save_width_count = 1;
      } else if (!CM_COUNTBYTE) error = CM_save_width_count++;
   }
   return (error);
}

/*************************************************************/
/* This module contains the subroutines needed to generate   */
/* the patterns for all of the bar codes in the libarary.    */
/*************************************************************/

void alternate(int value,int count) /* alternate bars using wide for 1 */
{
  unsigned int pattern;
  register int x;
  int dark;

  pattern = 0;
  dark = 1;
  x = 0;
  while (count) {
       count--;
       if (value & (1 << count)) {       /* if wide bar */
          pattern <<= CM_WIDEBAR;
          x += CM_WIDEBAR;
          if (dark)                     /* if it is supposed to be dark */
             pattern |= (1 << CM_WIDEBAR) - 1;
        } else {
          pattern <<= CM_NARROWBAR;
          x += CM_NARROWBAR;
          if (dark)                     /* if it is supposed to be dark */
             pattern |= (1 << CM_NARROWBAR) - 1;
         }
       dark = 1 - dark;                 /* toggle dark */
       if (x > 8) {
          addbar(pattern, x);
          x = pattern = 0;
        }
   }
  if (x) addbar(pattern, x);
}

void clearbar(void)  /* clear out the bar code buffers */
{
  register int x;
  unsigned char *ptr;

  CM_barcnt = CM_bitcnt = 0;          /* reset bar code bit pointer */
  CM_printcnt = 0;
  CM_barptr = CM_barcode;             /* reset bar code pointer */
  for (x=0,ptr=CM_barcode;x<CM_MAXBARLEN*4;x++)
      *ptr++ = 0;
  addbar (0,99);                      /* reset the bit counters */
}

void addbar(unsigned value,int count)  /* add the bit values to the bar code buffers */
{
  register unsigned int bit;
  int x;
  static int zerocount,onecount;

  if (count > 16) {
     zerocount = onecount = 0;
     return;
   }
  while (count) {
      count--;
      bit = value & (1 << count);
      bit >>= count;
      if (bit) {
         if (CM_Wide && zerocount >= 1) {/* add one more space */
            if (CM_3of9)
               zerocount = 0;          /* if 3 of 9, add one space only */
            zerocount += 2;            /* add one more space always */
            for (x=0; x<zerocount; x+=3) {
                CM_bitcnt++;
                CM_barcnt++;
                if (CM_bitcnt == 8) {
                   CM_bitcnt = 0;
                   CM_barptr++;
                 }
              }
          }
         onecount++;
         zerocount = 0;
         *CM_barptr +=(char) (1 << CM_bitcnt);
       } else {
         if (CM_Wide && onecount > 1 && !CM_3of9) {   /* add a bar if > 1 */
            for (x=0; x<onecount; x+=3) {
                *CM_barptr +=(char) (1 << CM_bitcnt);
                CM_bitcnt++;
                CM_barcnt++;
                if (CM_bitcnt == 8) {
                   CM_bitcnt = 0;
                   CM_barptr++;
                 }
              }
          }
         zerocount++;
         onecount = 0;
       }
      CM_bitcnt++;
      CM_barcnt++;
      if (CM_bitcnt == 8) {
         CM_bitcnt = 0;
         CM_barptr++;
       }
   }
}


/***************************************************************/
/* The following routines contain the code to generate the bit */
/* pattern for the various bar code types.                     */
/***************************************************************/

void  append(unsigned char *string, unsigned  char ch)  /* concatenate character to the end of a string */
{
  register int len;

	len = strlen((char *)string);
  string[len++] = ch;
  string[len] = '\0';
}

unsigned char *findchr(unsigned char *string, int letter)  /* locate the letter in the string */
{
   while (*string != letter && *string)
      string++;
   return(*string ? string : (unsigned char *)0);
}

/*************************************************************/
/* This module contains the code to take the bit patterns    */
/* that were generated by the bar code library functions and */
/* generate the printer codes into the string.               */
/*************************************************************/

/***************************************************************************/
/* declaration for variable that determines if Bytes are stored or counted */
/***************************************************************************/

void store_c(int letter, unsigned char **string) /* store a character to the string */
{
   if (!CM_COUNTBYTE) {
      **string = (char)letter;
      (*string)++;
    }
   CM_printcnt++;
}

void store_s(unsigned char *text, unsigned  char **string) /* store a character string to the string */
{
   while (*text) store_c(*(text++),string);
}


void printbar(unsigned char *string,
              int bar_type,
              unsigned char *text,
              int offset,
              struct code *codes,int height,int passes)  /* print bar  */
/* Returns:  Size in 1/100 inch units.                                   */
{
  static unsigned char worktext[CM_MAXTEXTLEN+1];
  int prtfunct;

  CM_Copy(worktext,text,0);
  text = worktext;

  if (!string && !CM_COUNTBYTE)
     return;
  if (!CM_barcnt)                     /* if nothing to print, return */
     return;
  CM_printcnt = 0;

  switch(codes->code_type) {
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
             prtfunct = 0;    /* dot matrix printing functions */
             break;
      case 6:  /* Laserjet with macros */
      case 7:  /* Laserjet without macros */
             prtfunct = 1;    /* laserjet printing functions */
             if (LANDSCAPE)
                prtfunct = 3; /* laserjet landscape functions */
             break;
      case 8:  /* Deskjet */
             prtfunct = 2;    /* deskjet printing functions */
             break;
      case 255:   /* PostScript */
              prtfunct = 4;    /* PostScript printing functions */
              break;
      default: /* unknown type */
              return;    /* return, invalid printer type */
   }
   switch(prtfunct) {
      case 0:
             printmatrix(string,text,offset,codes,height,passes);
             break;
      case 1:
             printlaser(string,text,offset,codes,height);
             break;
      case 2:
             printdeskjet(string,text,offset,codes,height);
             break;
      case 3:
             printllaser(string,text,offset,codes,height);
             break;
      case 4:
             printpscript(string,offset,codes,height);
             break;
   }
  return;
} 

void  CM_SendCount(unsigned char **string, int bytecount, int code_type) /* send the graphic count to matrix */
{
  int temp1,temp2,temp3,ready;

  switch (code_type) {
      default:
      case 3:
      case 1:                          /* Byte 2 = multiple of 256
                 Byte 1 = remaining Bytes */
             store_c(bytecount % 256,string);
             store_c(bytecount / 256,string);
             break;
      case 2:                          /* ascii dump of 4 digits */
             for (temp1=1000,temp2=bytecount;temp1;temp1 /= 10) {
                 temp3 = temp2 / temp1;
                 store_c(temp3 + '0',string);
                 temp2 -= temp3 * temp1;
              }
             break;
      case 4:                          /* no length sent */
             break;
      case 6:                          /* ascii dump for laser string */
      case 7:
      case 8:for (ready=0,temp1=10000,temp2=bytecount;temp1;temp1 /= 10) {
                 if (temp2 / temp1 || ready) {
                    ready = 1;
                    temp3 = temp2 / temp1;
                    store_c(temp3 + '0',string);
                    temp2 -= temp3 * temp1;
                  }
               }
             break;
   }
}

void CM_StoreBar(unsigned char **string, int code_type, int bit)  /* store bar/space for dot matrix */
{
   switch (code_type) {
      default:
      case 1:
      case 4:if (bit)  store_c(255,string);
                else   store_c(0,string);
             break;
      case 2:if (bit) {
                store_c(63,string);
                store_c(63,string);
                store_c(63,string);
                store_c(3<<4,string);       /* fire top 20 pins */
              } else {
                store_c(0,string);
                store_c(0,string);
                store_c(0,string);
                store_c(0,string);
              }
              break;
      case 3:if (bit) {
                store_c(255,string);
                store_c(255,string);
                store_c(15<<4,string);    /* fire top 20 pins */
              } else {
                store_c(0,string);
                store_c(0,string);
                store_c(0,string);
              }
             break;
   }
}

void CM_AddBar (int bytecount,int code_type)  /* increment counters when counting only */
{
   switch (code_type)  {
      default:
      case 1:
      case 4:CM_printcnt += bytecount;
             break;
      case 2:CM_printcnt += bytecount*4;
             break;
      case 3:CM_printcnt += bytecount*3;
             break;
   }
}

void CM_HPAdjust(unsigned char **string, unsigned *work_byte, int *count)  /* adjust bytes if > 8 bits */
{
  unsigned int b;
  while (*count >= 8) {
         b = (0xff << (*count-8)) & *work_byte;
         store_c(b >> (*count-8), string);
         *work_byte ^= b;
         *count -= 8;
     }
}

void CM_DoBars(struct code *codes, unsigned char *barbuf, int barcnt, unsigned  char ** string, void(*funct)(struct code *, int, unsigned  char **, int))
{
  register int y,z;
  int count;
  unsigned char work_byte;
  for (count=y=z=0 ; y<barcnt ; y++,z++) {
      if (z == 8)  z = 0;
      if (!z)  work_byte = *barbuf++;
      if (work_byte & 1) {
         if (count < 0) {        /* if counted zeros before */
            (*funct)(codes, -count, string, 0);
            count = 0;
          }
         count++;         /* count the one bit */
       } else {
         if (count > 0) {        /* if counted ones before */
            (*funct)(codes, count, string, 1);
            count = 0;
          }
         count--;         /* count the zero bit */
       }
      work_byte >>= 1;
    }
  if (count < 0)       /* if counted zeros last */
      (*funct)(codes, -count, string, 0);
  if (count > 0)       /* if counted ones last */
      (*funct)(codes, count, string, 1);
}

/* function called by dobars function for the printmatrix function */
void MBar(struct code *codes, int count, unsigned char **string, int value)
{
  register int x;
  for (x=DOTS * count; x; x--) CM_StoreBar(string,codes->code_type,value);
}

void printmatrix(unsigned char *string,unsigned  char *text,int offset,struct code *codes,int height,int passes) /* print to dot matrix */
{
  int save_count,bcount;
  unsigned char *save_ptr;
  int cnt;
  register int x,y;
  unsigned char *ptr;
  int z;
  int lines;
  int bitcnt[9];
  int linecnt;

  linecnt = 0;
  lines = height;
/* first adjust printhead to position for proper text printing when done */
  if (CM_LPI) {        /* if CM_LPI=0 dont do micro-adjust */
     x = lines - 1;                   /* get qty line feeds */
     y=(codes->sml_lf_ht*10)/codes->lpi; /* get dots per graphic line feed */
     y *= x;                          /* get number of dots moved */
     z = codes->sml_lf_ht / CM_LPI;   /* get dots per normal line feed */
     x = y / z;                       /* get dots to move to be normal */
     x *= z;
     x = y - x;
     z -= x;
     if (!x)    z = 0;
     if (z) {
        ptr = codes->sml_lf;
        while (*ptr != '?' && *ptr) store_c(*ptr++,&string);   /* get to the first ? */
        if (*(ptr+1) == '?') {         /* if ascii dump of count */
           store_c((z / 10) + '0',&string); /* store tens digit */
           store_c((z % 10) + '0',&string); /* store units digit */
           ptr += 2;
         } else {
           store_c(z,&string);        /* store the digit as binary */
           ptr++;
         }
        while (*ptr) store_c(*ptr++,&string);   /* store the rest */
        store_c(CM_LF,&string);
      }
   }
  save_ptr = string;                  /* save the beginning of line */
  save_count = CM_printcnt;           /* and save the number of Bytes in */
  for (x=1; x<=CM_save_width_count; x++) {
      if (CM_save_width_count > 1) {
         CM_Copy(text,CM_save[x].text,0);
         offset = CM_save[x].offset;
         height = CM_save[x].height;
         CM_Copy(CM_barcode,CM_save[x].barcode,CM_MAXBARLEN*4);
         CM_barcnt = CM_save[x].barcnt;
       }
      lines = height;
      bitcnt[x] = DOTS * CM_barcnt;
      store_s(codes->init,&string);
      store_c(CM_CR,&string);
      for (y=0; y<offset; y++)   store_c(' ',&string);
      store_s(codes->begin1,&string);  /* begin graphics mode */
      cnt = bitcnt[x];
      if (codes->code_type == 3 && *(codes->begin2)) { /* IBM X24 printer */
         cnt *= 3;
         cnt++;
       }
      CM_SendCount (&string, cnt, codes->code_type);
      store_s(codes->begin2,&string);  /* finishing touch to begin code */
      if (!CM_COUNTBYTE) CM_DoBars(codes, CM_barcode, CM_barcnt, &string, MBar);
         else            CM_AddBar (bitcnt[x], codes->code_type);
      store_s(codes->end1,&string);     /* end graphics mode */
      store_c(CM_CR,&string);          /* prepared for next code or pass */
   }

/* all bar codes now have 1 line generated.  Now replicate for the passes */
   bcount = CM_printcnt - save_count;
   for (x=1; x<passes; x++) {     /* this does the overstrike passes */
      if (!CM_COUNTBYTE) {      /* copy previous memory to duplicate line */
         CM_Copy (string, save_ptr, bcount);
         string += bcount;
       }
      CM_printcnt += bcount;
   }

/* the line is generated with any overstrike passes, now replicate that */
/* row for the number of lines we need. */
   bcount = CM_printcnt - save_count;
   if (CM_txtline[linecnt]) {
      if (*CM_txtline[linecnt]) {
         for (x=1; x<=passes; x++) {
             store_s(CM_txtline[linecnt], &string);
             store_c(CM_CR,&string);    /* print the text next to the code */
          }
         linecnt++;
       }
    }
   store_c(CM_LF,&string);

   for (y=1; y<lines; y++) {
      if (!CM_COUNTBYTE) {
         CM_Copy (string, save_ptr, bcount);
         string += bcount;
       }
      CM_printcnt += bcount;
      if (CM_txtline[linecnt]) {
         if (*CM_txtline[linecnt]) {
            for (x=1; x<=passes; x++) {
                store_s(CM_txtline[linecnt], &string);
                store_c(CM_CR,&string); /* print the text next to the code */
             }
            linecnt++;
         }
      }
      store_c(CM_LF,&string);
   }
   CM_printcnt -= 2;                   /* pull the last CR & LF */
   string -= 2;                /* put pointer back to overwrite */

   if (CM_LPI == 8) store_s(codes->lpi_8,&string);   /* set line spacing back */
   else     store_s(codes->lpi_6,&string);   /* set line spacing back */

/* now add the text under the bar code */

   if (*text) {
      store_c(CM_CR,&string);
      store_c(CM_LF,&string);          /* line feed before printing text */
   }

   save_ptr = string;                  /* save the beginning of line */
   save_count = CM_printcnt;           /* and save the number of Bytes in */
   for (x=1; x<=CM_save_width_count; x++) {
      if (CM_save_width_count > 1) {
         CM_Copy(text,CM_save[x].text,0);  /* do strcpy replacement */
         offset = CM_save[x].offset;
       }
      if (*text) {
	      y = strlen((char *)text);      /* get text length */
         z = CM_CPI * bitcnt[x];       /* calculate size in chars */
         z += codes->dpi-1;            /* round up */
         z /= codes->dpi;
         z -= y;                       /* find total extra spaces */
         z /= 2;                       /* divide by 2 */
         y = offset;
         for (y+=z; y > 0; y--)  store_c(' ',&string);
         store_s(text,&string);
         store_c(CM_CR,&string);
      }
   }

/* text is generated.  Now replicate for the passes */
   bcount = CM_printcnt - save_count;
   for (x=1; x<=passes; x++) {
      if (x == passes)  {
         if (*text) store_c(CM_LF,&string);
       } else {
         if (!CM_COUNTBYTE) {
            CM_Copy (string, save_ptr, bcount);
            string += bcount;
          }
         CM_printcnt += bcount;
       }
   }
   store_c(0,&string);                 /* terminating zero */

/* return size in hundreds */
/* return((100*bitcnt[CM_save_width_count])/codes->dpi); */
}


/* function called by dobars function for the printpscript function */ 
void PBar(struct code *codes, int count, unsigned char **string, int value)
{
  register int x;
   for (x=count; x; x--) store_s((unsigned char)value ? "  CM_Bar" : "  CM_Spc", string);
   store_s("\r\n",string);
}                

void printpscript(unsigned char *string, int offset, struct code *codes, int height)  /* print to postscript printer */
{
	int x;unsigned int y;
  int z,a;
  int dots,lines;
  int barcnt;
  store_s("/CMBarMag 1.0 def\r\n", &string);
  store_s("/CMSpcMag 1.0 def\r\n", &string);
  store_s("/CM_Bar   % draw bar code bar\r\n",&string);
  store_s("{0 1 CM_h rlineto CM_d CMBarMag mul -1 CM_h rmoveto} def\r\n",&string);
  store_s("/CM_Spc   % draw bar code space\r\n",&string);
  store_s("{CM_d CMSpcMag mul 0 rmoveto} def\r\n",&string);
   for (x=1; x<=CM_save_width_count; x++) {
      if (CM_save_width_count > 1) {
         offset = CM_save[x].offset;
         height = CM_save[x].height;
         CM_Copy(CM_barcode,CM_save[x].barcode,CM_MAXBARLEN*4);
         CM_barcnt = CM_save[x].barcnt;
       }
      dots = DOTS;                     /* grab globally defined DOT width */
      store_s("/CM_d ",&string);       /* set the dots per bar */

   /* convert the dots per inch to 1/72 units (2 decimal places) */
      y = 7200;
      if (dots < 10) y *=dots;       /* if no overflow, allow accuracy */
      y /= codes->dpi;        /* dpi in 1/7200 units */
      if (dots >= 10) y*=dots;        /* if overflow, mult after dividing */
      z = 10000;        /* The divisor value (XXX.XX) */
      a = 0;            /* when set, must store zero values */
      while (z) {
        if ((y / z) || a) {
           a = 1;
           store_c((y / z) + '0', &string);
         }
        y %= z;       /* pull off processed number */
        z /= 10;         /* work on next number */
        if (z == 10) {
           store_c('.', &string);
           a = 1;
         }
       }
      store_s(" def\r\n",&string);
      lines = (height * 72) / 10;      /* convert .1 inch height to points */
      store_s("/CM_h {",&string);      /* set the bar code height */
      store_c(lines/100+'0',&string);
      lines %= 100;
      store_c(lines/10+'0',&string);
      store_c(lines%10+'0',&string);
      store_s(" mul} def\r\n",&string);
      store_s("CM_d CMBarMag mul setlinewidth\r\n",&string);
      if (offset) {
         store_s("\r\n",&string);
         store_c((offset/100)+'0',&string);
         offset %= 100;
         store_c((offset/10) + '0',&string);
         store_c((offset%10) + '0',&string);
         store_s(" 0 rmoveto\r\n",&string);
      }

/* postscript initialization is now done.  print bar code information */

      CM_DoBars(codes, CM_barcode, CM_barcnt, &string, PBar);
    }
  store_s("  -",&string);             /* position to bottom center of code */
  barcnt = CM_barcnt;            /* get total bars and spaces */
  barcnt >>= 1;                       /* divide by two for the half mark */
  store_c((barcnt/100)+'0',&string);
  barcnt %= 100;
  store_c((barcnt/10) + '0',&string);
  store_c((barcnt%10) + '0',&string);
  store_s(" CM_d mul 0 rmoveto\r\n",&string);
  store_s("  currentpoint\r\n",&string);
  store_s("stroke\r\n",&string);
}

/* function called by dobars function for the laserjet portrait functions */
void LPBar(struct code *codes, int count, unsigned char **string, int value)
{
  static int bitsused = 0;
  static unsigned int work_byte = 0;
  if (value < 0) {
     if (bitsused)  {
        work_byte <<= (8 - bitsused);
        store_c(work_byte, string);
      }
     bitsused = 0;
     work_byte = 0;
     return;
   }
  if (value) value = (1 << DOTS) - 1;      /* set dots number of bits */
   while (count--) {
         work_byte <<= DOTS;
         bitsused += DOTS;
         work_byte |= value;     /* add in the bits */
         CM_HPAdjust (string, &work_byte, &bitsused);
    }
} 

void printlaser(unsigned char *string,unsigned char *text,int offset,struct code *codes,int height)  /* print to laser */
{
  register int x,y;
  int z;
  int dots,lines;
  int loopcnt;
  int Bytecount[9];
  if (offset) store_c(CM_CR,&string);
  store_s(CM_Push,&string);       /* save the current position */
  for (x=1; x<=CM_save_width_count; x++) {
      if (CM_save_width_count > 1) {
         store_s(CM_Pop,&string);
         store_s(CM_Push,&string);
         CM_Copy(text,CM_save[x].text,0);
         offset = CM_save[x].offset;
         height = CM_save[x].height;
         CM_Copy(CM_barcode,CM_save[x].barcode,CM_MAXBARLEN*4);
         CM_barcnt = CM_save[x].barcnt;
       }
      dots = DOTS;                     /* grab globally defined DOT width */
      lines = (codes->lpi* height) / 100;
      Bytecount[x] = dots * CM_barcnt;
      Bytecount[x] += 7;               /* add 7 to round up */
      Bytecount[x] /= 8;               /* get qty Bytes */
      for (y=0; y<offset; y++) store_c(' ',&string);
      store_s(codes->init,&string);
      if (codes->code_type == 6) {      /* if use macro type of printer */
         store_s(CM_StartMacro,&string);
         loopcnt = 1;                  /* do this only once, then macro */
       } else loopcnt = lines;
      while (loopcnt--) {
            store_s(codes->begin1,&string);  /* begin graphics mode */
            CM_SendCount (&string, Bytecount[x], codes->code_type);
            store_s(codes->begin2,&string);  /* finishing touch to begin code */
            if (!CM_COUNTBYTE) {
               CM_DoBars(codes, CM_barcode, CM_barcnt, &string, LPBar);
               LPBar(codes, -1, &string, -1);  /* clear statics and send last */
             } else  CM_printcnt += Bytecount[x];
       }
      store_s(codes->end1,&string);     /* end graphics mode */
      if (codes->code_type == 6) {
         store_s(CM_StopMacro,&string);
  /* one graphics line macro generated, now replicate for the number lines needed */
         for (y=1; y<lines; y++) store_s(CM_ExecuteMacro,&string);
         store_s(CM_DeleteMacro,&string);
       }
      if (*text) {
         if (offset || codes->code_type != 6) {
            store_c(CM_CR,&string);    /* carriage return now */
            store_c(CM_LF,&string);    /* line feed before printing text */
          } else {
            store_s(CM_Pop,&string);
            store_s(CM_Push,&string);
            if (*text) {
               y = height;             /* calculate # inches */
               y *= CM_LPI ? CM_LPI : 6; /* get the height in lines */
               y += 19;                /* round up to next line */
               y /= 10;
               while (y--) store_c(CM_LF,&string);
             }
          }
         Bytecount[x] = dots * CM_barcnt;
         y = strlen(text);
         z = CM_CPI * Bytecount[x];    /* calculate size in pica chars */
         z += codes->dpi-1;            /* round up */
         z /= codes->dpi;
         z -= y;                       /* find total extra spaces */
         z /= 2;                       /* divide by 2 */
         y = offset;
         for (y+=z; y > 0; y--)  store_c(' ',&string);
         store_s(text,&string);
       }
   }
  store_s(CM_Pop,&string);
  if (*text && CM_LPI)  {
     y = height;                      /* calculate # inches */
     y *= CM_LPI;                     /* get the height in lines */
     y += 29;                         /* round up to next line and add 2 */
     y /= 10;
     store_c(CM_CR,&string);          /* position cursor at col 0 */
     while (y--) store_c(CM_LF,&string);
   }
  store_c(0,&string);                 /* terminating zero */
/* return size in hundreds */
/* return((100*Bytecount[CM_save_width_count])/codes->dpi); */
}


void printdeskjet(unsigned char *string, unsigned char *text, int offset, struct code *codes, int height)  /* print to deskjet */
{
  register int x,y;
  int workline;
  int z;
  unsigned char *ptr;
  int dots,lines;
  unsigned int work_byte;
  int loopcnt;
  int Bytecount[9];
  unsigned char xpos[10];
   /* if doing multiple across, do in .1 inch increments */
  if (CM_save_width_count > 1) {
     lines = 5;
     height = (codes->lpi * height) / 500;  /* loop for the height */
   } else {
     lines = (codes->lpi * height) / 100;
     height = 1;       /* loop once only */
   }
  if (offset || CM_save_width_count > 1) store_c(CM_CR,&string);
  if (CM_save_width_count <= 1) for (y=0; y<offset; y++) store_c(' ',&string);
  store_s(codes->init,&string);
  for (workline=0 ; workline < height; workline++) {
      for (x=1; x<=CM_save_width_count; x++) {
          if (CM_save_width_count > 1) {
             offset = CM_save[x].offset;
             CM_Copy(CM_barcode,CM_save[x].barcode,CM_MAXBARLEN*4);
             CM_barcnt = CM_save[x].barcnt;
             if (x > 1)  {
                store_s(CM_PosCsr, &string);
                store_s("-5Y", &string);     /* positions up 5 lines */
              }
             work_byte = offset;
             work_byte *= codes->dpi;
             work_byte /= CM_CPI;
             ptr = xpos;
             for (z = 1000; z; z /= 10) {     /* up to 4 digits accuracy */
                if (work_byte / z || ptr != xpos || z == 1)
                   *ptr++ =(char)( (work_byte / z) + '0');  /* store digit */
                work_byte %= z;
              }
             *ptr++ = 'X';          /* store X relative */
             *ptr = '\0';                         /* store terminator */
           }
          dots = DOTS;                     /* grab globally defined DOT width */
          Bytecount[x] = dots * CM_barcnt;
          Bytecount[x] += 7;               /* add 7 to round up */
          Bytecount[x] /= 8;               /* get qty Bytes */
          loopcnt = lines;
          while (loopcnt--) {
                if (CM_save_width_count > 1) {
                   store_s(CM_PosCsr, &string);
                   store_s(xpos, &string);
                 }
               store_s(codes->begin1,&string);  /* begin graphics mode */
               CM_SendCount (&string, Bytecount[x], codes->code_type);
               store_s(codes->begin2,&string);  /* finishing touch to begin code */
               if (!CM_COUNTBYTE) {
                  CM_DoBars(codes, CM_barcode, CM_barcnt, &string, LPBar);
                  LPBar(codes, -1, &string, -1);  /* clear statics and send last */
                } else  CM_printcnt += Bytecount[x];
           }
       }
  }
 store_s(codes->end1,&string);       /* end graphics mode */
 store_c(CM_CR,&string);      /* carriage return */
 store_c(CM_LF,&string);         /* line feed before printing text */
 for (x=1; x<=CM_save_width_count; x++) {
      if (CM_save_width_count > 1) {
         CM_Copy(text,CM_save[x].text,0);
         offset = CM_save[x].offset;
         CM_barcnt = CM_save[x].barcnt;
       }
      if (*text) {
         store_c(CM_CR,&string);    /* carriage return now */
         Bytecount[x] = dots * CM_barcnt;
         y = strlen(text);
         z = CM_CPI * Bytecount[x];    /* calculate size in pica chars */
         z += codes->dpi-1;            /* round up */
         z /= codes->dpi;
         z -= y;                       /* find total extra spaces */
         z /= 2;                       /* divide by 2 */
         y = offset;
         for (y+=z; y > 0; y--) store_c(' ',&string);
         store_s(text,&string);
       }
  }
 if (*text) {
    store_c(CM_CR, &string);
    store_c(CM_LF, &string);
  }
 store_c(0,&string);                 /* terminating zero */
 /* return size in hundreds */
/* return((100*Bytecount[CM_save_width_count])/codes->dpi); */
}

void printllaser(unsigned char *string, unsigned char *text, int offset, struct code *codes, int height)  /* print landscape to laser */
{
  register int x,y;
  int z,a,bit;
  unsigned char *ptr,temp;
  int dots,lines;
  int Bytecount[9];
  int loopcnt;
  if (offset) store_c(CM_CR,&string);
  store_s(CM_Push,&string);       /* save the current position */
  for (x=1; x<=CM_save_width_count; x++)  {
      if (CM_save_width_count > 1)  {
         store_s(CM_Pop,&string);
         store_s(CM_Push,&string);
         CM_Copy(text,CM_save[x].text,0);
         offset = CM_save[x].offset;
         height = CM_save[x].height;
         CM_Copy(CM_barcode,CM_save[x].barcode,CM_MAXBARLEN*4);
         CM_barcnt = CM_save[x].barcnt;
       }
      dots = DOTS;                     /* grab globally defined DOT width */
      lines = (codes->lpi * height) / 100;
      Bytecount[x] = lines;
      Bytecount[x] += 7;               /* add 7 to round up */
      Bytecount[x] /= 8;               /* get qty Bytes */   
      for (y=0; y<offset; y++) store_c(' ',&string);
      store_s(codes->init,&string);
      y = CM_barcnt;                   /* grab count-1 (first is macro def) */
      ptr = CM_barcode + (y/8);
      z = y % 8;
      z--;                             /* set to how many to shift */
      temp = *ptr--;

/* begin a macro for the first bar, then end it */
      if (codes->code_type == 6) {
         store_s(CM_StartMacro,&string);
         store_s(codes->begin1,&string);  /* begin graphics mode */
         CM_SendCount (&string, Bytecount[x], codes->code_type);
         store_s(codes->begin2,&string);  /* finishing touch to begin code */
         for (y=0; y < Bytecount[x]-1; y++)  store_c(255,&string);
         if (lines % 8) store_c (256-(1 << (8-(lines % 8))), &string);
            else        store_c (255,&string);
         store_s(codes->end1,&string);     /* end graphics mode */
         store_s(CM_StopMacro,&string);   /* end the macro */
       }
      /* now generate the bars and spaces */
      for (y=CM_barcnt*dots,a=1; y; y--,a++) {
          if (z < 0) {
             z = 7;
             temp = *ptr--;
           }
          bit = temp & (1 << z);
          if (bit) {
             if (codes->code_type == 6) store_s(CM_ExecuteMacro,&string);   /* draw a bar */
                else  {
                 store_s(codes->begin1,&string);  /* begin graphics mode */
                 CM_SendCount (&string, Bytecount[x], codes->code_type);
                 store_s(codes->begin2,&string);  /* finishing touch to begin code */
                 for (loopcnt=0; loopcnt < Bytecount[x]-1; loopcnt++)
                     store_c(255,&string);
                 if (lines % 8) store_c (256-(1 << (8-(lines % 8))), &string);
                    else        store_c (255,&string);
                 store_s(codes->end1,&string);     /* end graphics mode */
                }
           } else {
             store_s(codes->begin1,&string);  /* begin graphics mode */
             CM_SendCount (&string, 1, codes->code_type);
             store_s(codes->begin2,&string);  /* finishing touch to begin code */
             store_c(0,&string);              /* print one zero for a space */
             store_s(codes->end1,&string);     /* end graphics mode */
           }
          if (a == dots) {
             z--;
             a = 0;
           }
       }
      if (codes->code_type == 6) store_s(CM_DeleteMacro,&string); /* delete the macro */
      if (*text) {
         y = lines;                    /* calculate # inches */
         y *= CM_LPI ? CM_LPI : 6;     /* get the height in lines */
         y += (codes->lpi/10)-1;       /* round up */
         y /= (codes->lpi/10);         /* size in inches */
         y++;                          /* bar printed at bottom, add 1 */
         store_s(CM_Pop,&string);
         store_s(CM_Push,&string);
         while (y--) store_c(CM_LF,&string);
         Bytecount[x] = dots * CM_barcnt;
         y = strlen(text);
         z = CM_CPI * Bytecount[x];    /* calculate size in pica chars */
         z += codes->dpi-1;            /* round up */
         z /= codes->dpi;
         z -= y;                       /* find total extra spaces */
         z /= 2;                       /* divide by 2 */
         y = offset;
         for (y+=z; y > 0; y--)  store_c(' ',&string);
         store_s(text,&string);
       }
    }
   store_s(CM_Pop,&string);
   if (*text && CM_LPI) {
      y = height;                      /* calculate # inches */
      y *= CM_LPI;                     /* get the height in lines */
      y += 29;                         /* round up to next line and add 2 */
      y /= 10;
      store_c(CM_CR,&string);          /* position cursor at position 0 */
      while (y--) store_c(CM_LF,&string);
    }
   store_c(0,&string);                 /* terminating zero */

/* return size in hundreds */
/* return((1000*CM_barcnt * dots)/codes->lpi); */
}

/***
*  barsize - Get the memory size that will be required for this bar code.
*
*  This function is called with:
*
*  length = barsize(bar_type,string,text,printnum,offset,height,chksum,passes);
*
*       int length =                   length of the returned string in bytes
*                                      -1 if bar_type invalid
*                                      -2 if string invalid
*                                      -3 if text invalid
*                                      -4 if printnum invalid
*                                      -5 if offset invalid
*                                      -6 if height invalid
*                                      -7 if chksum not 1 or 0
*                                      -8 if passes wrong
*                                      -9 if bar code generation error
*       unsigned bar_type =            Simbologia
*       char *string =                 the character string to bar code
*       char *text =                   the character string to print under bar
*       unsigned printnum =            Impresora a usar
*       unsigned offset =              number of characters from left margin
*                                          to indent.
*       unsigned height =              bar code height in 1/10 inch units
*                                          (max units = 20)
*       int chksum =                   whether to print checksum when optional
*       int passes =                   number of overstrike passes to print
**/

int barsize(int bar_type,
            unsigned char *string,
            unsigned char *text,
            int printnum,
            int offset,int height,int chksum,int passes)
/****************************************************************************/
{
  int stlen, txtlen, error,ret_code;
	stlen = strlen((char *)string);
	txtlen = strlen((char *)text);
  error = 0;
  if ((bar_type > CM_MAXBARCNT) || (bar_type < 1)) error = -1;
  if (!string || ((stlen > CM_MAXBARLEN) && (bar_type < 16))) error = -2;
  if (!text || ((txtlen > CM_MAXTEXTLEN) && (bar_type < 16))) error = -3;
  if (printnum > PRINTERS)     error = -4;
  if (offset > 250)            error = -5;
  if (height > CM_MAXHEIGHT || height < 1)  error = -6;
  if (chksum > 2 || chksum < 0)      error = -7;
  if (passes > 5 || passes < 1)      error = -8;
  if (!error) {
     CM_COUNTBYTE = 1;                /* count the Bytes */
     ret_code = CM_generate((unsigned char *) 0, bar_type, string, text,
                      &CM_codes[printnum], offset, height, chksum, passes);
     CM_COUNTBYTE = 0;                /* store the Bytes */
     if (ret_code < 10)  error = ret_code;
     if (ret_code < 0)   error = -9;
   }
   if (CM_printcnt > 32767)  error = -11;
   if (!error) return ((int) CM_printcnt);
      else     return (error);
}

void CM_Copy(unsigned char *dest,unsigned char *source,int length)  /* copy from source to dest */
{
   if (length) {
      while (length--)   *dest++ = *source++;
   } else {
     while (*source) *dest++ = *source++;
     *dest = *source;             /* copy terminator */
   }
}

