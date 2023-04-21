/************************************************/
/*               Bar Code Library               */
/*   Copyright (C) 1988-1992, StrandWare, Inc.  */
/*             All Rights Reserved              */
/************************************************/

#include "../v10.h"

unsigned char two_five_pattern[10] = {
'\006', '\021', '\011', '\030', '\005', '\024', '\014', '\003', '\022', '\012'
   };

void do_2x5(unsigned value,int count)  /* alternate the bars for 2 of 5 bar code */
{
  int temp;
  temp = (int) (value >> (count-6));
  alternate(temp,6);                  /* put upper 6 bars in */
  alternate(value,count-6);           /* put remaining bars in */
}

int two_5(unsigned char *number,int chksum)  /* generate a 2 of 5 bar code */
{
  register int x;
  int y,z,digit;
  unsigned int bit;
  unsigned char *ptr;
  unsigned char *destptr;
  unsigned int two_char;
  int length;
  length = strlen(number);
  for (ptr=number,destptr=CM_NEWSTR,x=length; x ; x--,ptr++) {
      *destptr++ = *ptr;               /* make a copy to CM_NEWSTR */
      if (!isdigit(*ptr)) return(1);
   }
  *destptr = '\0';
  if (chksum) {
     digit = chksum1(CM_NEWSTR);      /* get checksum */
     CM_CHECKSUM = (char)(digit + '0');       /* save checksum */
     ptr = CM_NEWSTR + length;        /* point to end of buffer */
     *ptr++ = CM_CHECKSUM;            /* add the checksum */
     length++;
     *ptr = 0;                        /* add the terminator */
   }
  if (length & 1) {                   /* if length is odd */
     for (ptr=CM_NEWSTR+length,destptr=ptr + 1; length>=0; length--)
         *destptr-- = *ptr--;
     *CM_NEWSTR = '0';                  /* add a leading zero */
   }
  clearbar();                         /* clear the bar code area */
/* add the start code (0000) */
  addbar(0xff,CM_NARROWBAR);             /* add a narrow 1 */
  addbar(0x00,CM_NARROWBAR);             /* add a narrow 0 */
  addbar(0xff,CM_NARROWBAR);             /* add a narrow 1 */
  addbar(0x00,CM_NARROWBAR);             /* add a narrow 0 */
  for (ptr=CM_NEWSTR,x=strlen(CM_NEWSTR); x ; x-=2,ptr+=2) {
      two_char = 0;
      for (y=5; y; ) {
          y--;
          for (z=0 ; z<2 ; z++) {
              digit = *(ptr+z) - '0';
              if (digit >= 0 && digit <= 9) {
                 two_char <<= 1;
                 bit = two_five_pattern[digit];
                 bit &= (1 << y);
                 bit >>= y;
                 two_char += bit;
               }
           }
       }
      do_2x5(two_char,10);
   }
/* add the stop code (100) */
  addbar(0xff,CM_WIDEBAR);               /* add a wide 1 */
  addbar(0x00,CM_NARROWBAR);             /* add a narrow 0 */
  addbar(0xff,CM_NARROWBAR);             /* add a narrow 1 */
  return(0);
}
