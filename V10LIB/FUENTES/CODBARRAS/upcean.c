/************************************************/
/*               Bar Code Library               */
/*   Copyright (C) 1988-1992, StrandWare, Inc.  */
/*             All Rights Reserved              */
/************************************************/

#include "../v10.h"

char upc_leftguard = '\013';
char upc_delineator = 1;
char upc_rightguard = '\025';
char upc_centerguard = '\012';
unsigned char upc_odd_data[] = {
'\015', '\031', '\023', '\075', '\043', '\061', '\057', '\073', '\067', '\013'
};
unsigned char upc_even_data[] = {
'\047', '\063', '\033', '\041', '\035', '\071', '\005', '\021', '\011', '\027'
};
unsigned char upc_right_data[] = {
'\162', '\146', '\154', '\102', '\134', '\116', '\120', '\104', '\110', '\164'
};
unsigned char upc_parpat[] = {
'\003', '\005', '\011', '\021', '\006', '\014', '\030', '\012', '\022', '\024'
};
unsigned char upc_parpat0[] = {
'\007', '\013', '\023', '\043', '\015', '\031', '\061', '\025', '\045', '\051'
};
unsigned char upc_firstflag[] = {   /* bit set if left hand b */
'\000', '\013', '\015', '\016', '\023', '\031', '\034', '\025', '\026', '\032'
};


int chksum1(unsigned char *string) /* calculate the UPC/EAN checksum for the string of numbers */
{
  int chksum[2];
  register int count;
  count = strlen((char *)string);      /* get length */
  count &= 1;                         /* get odd or even */
  chksum[0]=chksum[1] = 0;            /* reset checksum */
  while (*string) {
      chksum[count] += (*string++ - '0');
      count = 1-count;
   }
  chksum[1] *= 3;                     /* multiply odd by 3 */
  chksum[0] += chksum[1];             /* add two checksums */
  count = chksum[0]/10;
  count++;
  count *= 10;
  count -= chksum[0];
  if (count == 10)  count = 0;
  return(count);
}

int chksum3(unsigned char *string) /* calculate the sup. checksum for the string of numbers */
{
  int chksum[2];
  register int count;
  count = strlen((char *)string);      /* get length */
  count &= 1;                         /* get odd or even */
  chksum[0]=chksum[1] = 0;            /* reset checksum */
  while (*string) {
        chksum[count] += (*string++ - '0');
        count = 1-count;
   }
  chksum[1] *= 3;                     /* multiply odd by 3 */
  chksum[0] *= 9;                     /* multiply even by 9 */
  chksum[0] += chksum[1];             /* add two checksums */
  count = chksum[0]%10;               /* the units position is checksum */
  return(count);
}

int two_sup(unsigned char *digits)  /* generate a 2 digit supplemental code */
{
  register int x;
  unsigned char *ptr;
  int number;
  for (x=2,ptr=digits ; x && *ptr ; x--,ptr++) if (!isdigit(*ptr)) return(1);
  number = 0;
  for (x=2,ptr=digits; x && *ptr; x--,ptr++) {
      number *= 10;
      number += *ptr - '0';
   }
  addbar(0,9);                           /* add nine blank bars */
  addbar(upc_leftguard,4);               /* add left guard code (1011) */
  ptr = digits;
  if (number & 2)                     /* add first digit */
      addbar(upc_even_data[*ptr-'0'],7);
   else
      addbar(upc_odd_data[*ptr-'0'],7);
  addbar(upc_delineator,2);              /* add character delineator (01) */
  ptr++;
  if (number & 1)                     /* add the second digit */
     addbar(upc_even_data[*ptr-'0'],7);
   else
     addbar(upc_odd_data[*ptr-'0'],7);
   return(0);
}

int five_sup(unsigned char *digits)  /* generate a 5 digit supplemental code */
{
  unsigned char console[7];
  register int x;
  int number;
  unsigned char *ptr;
  unsigned char *destptr;
  unsigned int parity;
  for (x=5,ptr=digits ; x && *ptr ; x--,ptr++) if (!isdigit(*ptr)) return(1);
  for (x=5,ptr=digits,destptr=console; x && *ptr; x--) *destptr++ = *ptr++;
  *destptr = '\0';
  number = chksum3(console);
  parity = upc_parpat[number];
  CM_CHECKSUM2 =(char) (number + '0');        /* save as second checksum */
  addbar(0,9);                           /* add nine blank bars */
  addbar(upc_leftguard,4);               /* add left guard code (1011) */
  for (x=5,ptr=digits; x && *ptr; x--,ptr++) {
      if (parity & 1)                  /* if even parity */
         addbar(upc_even_data[*ptr-'0'],7);
       else
         addbar(upc_odd_data[*ptr-'0'],7);
      if (x > 1) addbar(upc_delineator,2);        /* add character delineator (01) */
      parity >>= 1;                    /* shift to check next bit */
   }
   return(0);
}

int UPC_A(int sys, unsigned char *left, unsigned  char *right)  /* generate a UPC-A bar code */
{
  unsigned char console[15];
  register int x, number;
  unsigned char *ptr;
  unsigned char *destptr;
  int error;
  error = 0;
  for (x=5,ptr=left ; x && *ptr ; x--,ptr++) if (!isdigit(*ptr))  error = 1;
  for (x=5,ptr=right ; x && *ptr ; x--,ptr++) if (!isdigit(*ptr)) error = 1;
  if (sys > '9' || sys < '0')     error = 1;
  if (error) return(1);
  clearbar();                         /* clear the bar code area */
  addbar(upc_rightguard,3);              /* add left guard code (101) */
  addbar(upc_odd_data[sys-'0'],7);       /* add system code */
  for (x=5,ptr=left ; x ; x--) {
      number = *ptr++ - '0';
      addbar(upc_odd_data[number],7);     /* add the digit */
   }
  addbar(upc_centerguard,5);             /* add center guard code (01010) */
  for (x=5,ptr=right ; x ; x--) {
      number = *ptr++ - '0';
      addbar(upc_right_data[number],7);   /* add the digit */
   }
  destptr = console;                  /* assemble checksum string */
  *destptr++ = (unsigned char) sys;
  for (x=5,ptr=left ; x && *ptr ; x--)
     *destptr++ = *ptr++;
  for (x=5,ptr=right ; x && *ptr ; x--)
     *destptr++ = *ptr++;
  *destptr = '\0';
  number = chksum1(console);          /* get the checksum */
  CM_CHECKSUM =(char)( number + '0');         /* save checksum */
  append(CM_NEWSTR,CM_CHECKSUM);      /* store checksum into new string */
  addbar(upc_right_data[number],7);      /* add the checksum */
  addbar(upc_rightguard,3);              /* add right guard bars */
  return(0);
}

int UPC_E(int sys, unsigned char *left, unsigned  char *right)  /* generate a UPC-E bar code */
{
  unsigned char console[15];
  register int x;
  int chksum,digit;
  unsigned int parity;
  unsigned char *ptr;
  unsigned char *destptr;
  for (x=5,ptr=left ; x && *ptr ; x--,ptr++) if (!isdigit(*ptr)) return(1);
  for (x=5,ptr=right ; x && *ptr ; x--,ptr++) if (!isdigit(*ptr)) return(1);
  if (sys != '0' && sys != '1') return(1);
  destptr = console;
  *destptr++ =(char) sys;
  for (x=5,ptr=left; x; x--) *destptr++ = *ptr++;
  for (x=5,ptr=right; x; x--) *destptr++ = *ptr++;
  *destptr = '\0';
  chksum = chksum1(console);          /* get the checksum */
  CM_CHECKSUM =(char)( chksum + '0');         /* save checksum */
  append(CM_NEWSTR,CM_CHECKSUM);      /* store checksum into new string */
  parity = upc_parpat0[chksum];       /* get odd/even status's for chksum */
  if (sys == '1') parity = ~parity;		       /* reverse the parity if system = 1 */
  ptr = console;
  if (left[4] == '0') {
      if (left[3] == '0') {
	 if (left[2] <= '2') {          /* if 1000 items available */
	    if (right[0] != '0' || right[1] != '0')  return(1);
	    ptr[0] = left[0];
	    ptr[1] = left[1];
	    ptr[2] = right[2];
	    ptr[3] = right[3];
	    ptr[4] = right[4];
	    ptr[5] = left[2];
          } else {                         /* if 100 items available */
	    if (right[0] != '0' || right[1] != '0' || right[2] != '0') return(1);
	    ptr[0] = left[0];
	    ptr[1] = left[1];
	    ptr[2] = left[2];
	    ptr[3] = right[3];
	    ptr[4] = right[4];
	    ptr[5] = '3';
	 }
       } else {                            /* if 10 items available */
	 if (right[0]!='0' || right[1]!='0' || right[2]!='0' || right[3]!='0')
	    return(1);
	 ptr[0] = left[0];
	 ptr[1] = left[1];
	 ptr[2] = left[2];
	 ptr[3] = left[3];
	 ptr[4] = right[4];
	 ptr[5] = '4';
      }
   } else {                               /* if 5 items available */
     if (right[0]!='0' || right[1]!='0' || right[2]!='0'
	 || right[3] != '0' || right[4]<'5')
	    return(1);
     ptr[0] = left[0];
     ptr[1] = left[1];
     ptr[2] = left[2];
     ptr[3] = left[3];
     ptr[4] = left[4];
     ptr[5] = right[4];
  }
  ptr[6] = '\0';
  clearbar();                         /* clear the bar code area */
  addbar(upc_rightguard,3);              /* add left guard code (101) */
  for (x=0,ptr=console ; x<6 ; x++) {
      digit = *ptr++;
      digit -= '0';
      if (parity & 1)
	 addbar(upc_even_data[digit],7);
      else
	 addbar(upc_odd_data[digit],7);
      parity >>=1;
   }
   addbar(upc_rightguard,6);              /* add right guard bars (010101) */
   return(0);
}

int UPC_E6(int sys, unsigned char *string)  /* generate a UPC-E bar code (6 digit input) */
{
  unsigned char console[15];
  register int x;
  int chksum,digit;
  unsigned int parity;
  unsigned char *ptr;
  unsigned char *destptr;
  for (x=6,ptr=string ; x && *ptr ; x--,ptr++) if (!isdigit(*ptr)) return(1);
  if (sys != '0' && sys != '1') return(1);
  destptr = console;
  destptr[0] =(char) sys;
  destptr[11] = '\0';
  switch (string[5]) {                 /* expanded by last digit */
      case '0':
      case '1':                        /* 1000 items available */
      case '2':
               destptr[3] = string[5];
               destptr[4] = destptr[5] = destptr[6] = destptr[7] = '0';
               destptr[1] = string[0];
               destptr[2] = string[1];
               destptr[8] = string[2];
               destptr[9] = string[3];
               destptr[10] = string[4];
               break;
      case '3':                        /* 100 items available */
               destptr[4] = destptr[5] = destptr[6] = destptr[7] = destptr[8] = '0';
               destptr[1] = string[0];
               destptr[2] = string[1];
               destptr[3] = string[2];
               destptr[9] = string[3];
               destptr[10] = string[4];
               break;
      case '4':                        /* 10 items available */
               destptr[5] = destptr[6] = destptr[7] = destptr[8] = destptr[9] = '0';
               destptr[1] = string[0];
               destptr[2] = string[1];
               destptr[3] = string[2];
               destptr[4] = string[3];
               destptr[10] = string[4];
               break;
      default:                         /* 5 items available */
               destptr[6] = destptr[7] = destptr[8] = destptr[9] = '0';
               destptr[1] = string[0];
               destptr[2] = string[1];
               destptr[3] = string[2];
               destptr[4] = string[3];
               destptr[5] = string[4];
               destptr[10] = string[5];
               break;
   }
  chksum = chksum1(console);          /* get the checksum */
  CM_CHECKSUM =(char)( chksum + '0');         /* save checksum */
  parity = upc_parpat0[chksum];       /* get odd/even status's for chksum */
  if (sys == '1') parity = ~parity;		       /* reverse the parity if system = 1 */
  clearbar();                         /* clear the bar code area */
  addbar(upc_rightguard,3);              /* add left guard code (101) */
  for (x=0,ptr=string ; x<6 ; x++) {
      digit = *ptr++;
      digit -= '0';
      if (parity & 1)
	 addbar(upc_even_data[digit],7);
       else
	 addbar(upc_odd_data[digit],7);
      parity >>=1;
   }
  addbar(upc_rightguard,6);              /* add right guard bars (010101) */
  return(0);
}

int EAN_13(unsigned char *flag, unsigned  char *left, unsigned  char *right)  /* generate a EAN-13 bar code */
{
  unsigned char console[20];
  register int x;
  int number,data;
  unsigned int mask;
  unsigned char *ptr;
  unsigned char *destptr;
  for (x=2,ptr=flag ; x && *ptr ; x--,ptr++) if (!isdigit(*ptr)) return(1);
  for (x=5,ptr=left ; x && *ptr ; x--,ptr++) if (!isdigit(*ptr)) return(1);
  for (x=5,ptr=right ; x && *ptr ; x--,ptr++) if (!isdigit(*ptr)) return(1);
  clearbar();                         /* clear the bar code area */
  addbar(upc_rightguard,3);              /* add left guard code (101) */
  number = flag[1] - '0';             /* get second flag char */
  addbar(upc_odd_data[number],7);        /* add second flag char */
  number = flag[0] - '0';             /* get first flag char */
  data = upc_firstflag[number];       /* get left a/b encodation data */
  mask = 1 << 4;
  for (x=0,ptr=left ; x<5 ; x++) {
      number = *ptr++ - '0';
      if (data & mask)
	 addbar(upc_even_data[number],7); /* add left hand b digit */
       else
	 addbar(upc_odd_data[number],7);  /* add left hand a digit */
      mask >>= 1;
   }
  addbar(upc_centerguard,5);             /* add center guard code (01010) */
  for (x=0,ptr=right ; x<5 ; x++) {
      number = *ptr++ - '0';
      addbar(upc_right_data[number],7);   /* add the digit */
   }
  destptr = console;                  /* assemble checksum string */
  for (x=2,ptr=flag ; x && *ptr ; x--,ptr++) *destptr++ = *ptr;
  for (x=5,ptr=left ; x && *ptr ; x--,ptr++) *destptr++ = *ptr;
  for (x=5,ptr=right ; x && *ptr ; x--,ptr++) *destptr++ = *ptr;
  *destptr = '\0';
  number = chksum1(console);          /* get the checksum */
  CM_CHECKSUM =(char)( number + '0');         /* save checksum */
  append(CM_NEWSTR,CM_CHECKSUM);      /* store checksum into new string */
  addbar(upc_right_data[number],7);   /* add the checksum */
  addbar(upc_rightguard,3);           /* add right guard bars (101) */
  return(0);
}

int EAN_8(unsigned char *flag, unsigned  char *left)  /* generate a EAN-8 bar code */
{
  unsigned char console[20];
  register int x;
  int number;
  unsigned char *ptr;
  unsigned char *destptr;
  for (x=2,ptr=flag ; x && *ptr ; x--,ptr++) if (!isdigit(*ptr)) return(1);
  for (x=2,ptr=left ; x && *ptr ; x--,ptr++) if (!isdigit(*ptr)) return(1);
  clearbar();                         /* clear the bar code area */
  addbar(upc_rightguard,3);              /* add left guard code (101) */
  for (x=0,ptr=flag ; x<2 ; x++) {
      number = *ptr++ - '0';
      addbar(upc_odd_data[number],7);  /* add left hand a digit */
   }
  for (x=0,ptr=left ; x<2 ; x++) {
      number = *ptr++ - '0';
      addbar(upc_odd_data[number],7);  /* add left hand a digit */
   }
  addbar(upc_centerguard,5);          /* add center guard code (01010) */
  for ( ; x<5 ; x++) {
      number = *ptr++ - '0';
      addbar(upc_right_data[number],7);   /* add right hand a digit */
   }
  destptr = console;                  /* assemble the checksum */
  for (x=2,ptr=flag ; x && *ptr ; x--,ptr++) *destptr++ = *ptr;
  for (x=5,ptr=left ; x && *ptr ; x--,ptr++) *destptr++ = *ptr;
  *destptr = '\0';
  number = chksum1(console);          /* get the checksum */
  CM_CHECKSUM =(char)( number + '0');         /* save checksum */
  append(CM_NEWSTR,CM_CHECKSUM);      /* store checksum into new string */
  addbar(upc_right_data[number],7);      /* add the checksum */
  addbar(upc_rightguard,3);              /* add right guard bars (101) */
  return(0);
}
