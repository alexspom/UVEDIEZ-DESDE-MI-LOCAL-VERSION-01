/************************************************/
/*               Bar Code Library               */
/*   Copyright (C) 1988-1992, StrandWare, Inc.  */
/*             All Rights Reserved              */
/************************************************/

#include "../v10.h"

unsigned int code128_start=102;
unsigned int code128_stop=6379;         /* 014353 */
unsigned int code128_data[] = {
03314, 03154, 03146, 02230, 02214, 02114, 02310, 02304, 02144,
03110, 03104, 03044, 02634, 02334, 02316, 02714, 02354, 02346,
03162, 03134, 03116, 03344, 03164, 03556, 03514, 03454, 03446,
03544, 03464, 03462, 03330, 03306, 03066, 02430, 02130, 02106,
02610, 02150, 02142, 03210, 03050, 03042, 02670, 02616, 02156,
02730, 02706, 02166, 03566, 03216, 03056, 03350, 03342, 03356,
03530, 03506, 03426, 03550, 03542, 03432, 03572, 03102, 03612,
02460, 02414, 02260, 02206, 02054, 02046, 02620, 02604, 02320,
02302, 02064, 02062, 03022, 03120, 03672, 03024, 02172, 02474,
02274, 02236, 02744, 02364, 02362, 03644, 03624, 03622, 03336,
03366, 03666, 02570, 02436, 02136, 02750, 02742, 03650, 03642,
02736, 02756, 03536, 03656, 03204, 03220, 03234                };

#define SHIFT 128
#define FNC_1 129
#define FNC_2 130
#define FNC_3 131
#define FNC_4 132

int code128(unsigned char *string,int uccflag,int checksum)  /* generate a code 128 bar code */
{
  unsigned int chksum;
  int uccchk;
  int count;
  int index;
  unsigned char *ptr;
  register unsigned int x,y;
  int mode,oldmode;
  int seglen, startseg, z;
  clearbar();                         /* clear the bar code area */
  CM_Copy(CM_NEWSTR, string, 0);
  if (!uccflag && CM_128TYPE == 3) {
      seglen=startseg=y=0;
      for (x=0; string[x]; x++) {
         if (string[x]==FNC_1) {
            if (seglen & 1) {
               for (z=y; z>startseg; z--) CM_NEWSTR[z]=CM_NEWSTR[z-1];
               CM_NEWSTR[z]='0';
               y++;
             }
            startseg = y+1;
            seglen = -1;
           }
          CM_NEWSTR[y++]=string[x];
          seglen++;
       }
      if (seglen & 1) {
         for (z=y; z>startseg; z--) CM_NEWSTR[z]=CM_NEWSTR[z-1];
         CM_NEWSTR[z]='0';
         y++;
       }
      CM_NEWSTR[y]='\0';
   }
  string = CM_NEWSTR;
  if (uccflag) {
     uccchk = chksum1(string) + '0';  /* calculate UCC-128 checksum */
	  x = strlen((char *)string);
     CM_CHECKSUM =(char) uccchk;
     string[x++] =(char) uccchk;               /* concatenate the checksum */
     string[x+1] =(char) '\0';
     for (; x; x--) {
         string[x] = string[x-1];
         if (!isdigit(string[x]))  return(1);
      }
     string[x] = FNC_1;
   }
   chksum = count = 0;
   if (!CM_128TYPE) {
	   if (strlen((char *)string) == 2) oldmode = 3;
      else                     oldmode = 0;
    } else   oldmode = mode = CM_128TYPE;
   if (uccflag) oldmode = mode = 3;   /* if UCC-128, only mode c allowed */
   for (ptr=string,x=strlen(string); x>0; x--,ptr++) {
       if (!CM_128TYPE && !uccflag) {
	   mode = 0;
           if ((ptr==string || oldmode == 3) && *ptr == FNC_1) mode = 3;                  /* FNC_1 ok, use code mode c */
           if (isdigit(ptr[0]) && isdigit(ptr[1]) && oldmode == 3)  mode = 3;                  /* continue with code mode c */
           if (isdigit(ptr[0])&&isdigit(ptr[1])&&isdigit(ptr[2])&&isdigit(ptr[3]))
              mode = 3;                  /* start at code mode c */
	       for (y = 0; y < strlen((char *)ptr) && !mode; y++) {
               if (ptr[y] < ' ' || ptr[y] == CM_NULLCHAR) mode = 1; /* if control code */
                  else  if (ptr[y] > 95 && ptr[y] < 128) /* if lower case */
                            mode = 2;
            }
	   if (!mode) mode = 2;
        }
       if (ptr == string) {             /* if first character */
          index = code128_start+mode;
          chksum = index;
          addbar(code128_data[index],11);  /* add the start character */
          oldmode = mode;
          CM_MODE128 =(char) index;
        }
       if (oldmode != mode) {
          count++;
          index = code128_start-mode;
          chksum += (count * index);
          addbar(code128_data[index],11);
          oldmode = mode;
         }
        index = -1;
        switch(mode) {
	 case 1:                       /* code type A */
	    switch(*ptr)
	    {
	    case SHIFT:
	       index = 98;
	       break;
	    case FNC_1:
	       index = 102;
	       break;
	    case FNC_2:
	       index = 97;
	       break;
	    case FNC_3:
	       index = 96;
	       break;
	    case FNC_4:
	       index = 101;
	       break;
	    default:
	       if (*ptr < 32)
		  index = *ptr + 64;
	       else
		  if (*ptr <= '_')
		     index = *ptr - 32;
	       break;
	    }
	    break;
	 case 2:                       /* code type B */
	    switch(*ptr)
	    {
	    case SHIFT:
	       index = 98;
	       break;
	    case FNC_1:
	       index = 102;
	       break;
	    case FNC_2:
	       index = 97;
	       break;
	    case FNC_3:
	       index = 96;
	       break;
	    case FNC_4:
	       index = 100;
	       break;
	    default:
	       index = *ptr - 32;
	       break;
	    }
	    break;
	 case 3:                       /* code type C */
	    if (*ptr == FNC_1)
	       index = 102;
	    if (isdigit(*ptr) && isdigit(ptr[1]))
	    {
	       index = *ptr++ - '0';
	       index *= 10;
	       index += *ptr - '0';
	       x--;
	    }
	    break;
      }
      if (index < 0 || index > 102)
	 return(1);                    /* error - can't barcode that */
      count++;
      chksum += (count * index);
      addbar(code128_data[index],11);
   }

   if (checksum)
   {
      chksum %= 103;
      addbar(code128_data[chksum],11);           /* add the checksum in */
      if (uccflag)
	 CM_CHECKSUM2 =(char) chksum;
      else
	 CM_CHECKSUM = (char)chksum;
   }

   addbar(code128_stop,13);                      /* add the stop character */
   return(0);
}
