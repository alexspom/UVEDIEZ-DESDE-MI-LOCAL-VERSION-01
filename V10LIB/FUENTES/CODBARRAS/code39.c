/************************************************/
/*               Bar Code Library               */
/*   Copyright (C) 1988-1992, StrandWare, Inc.  */
/*             All Rights Reserved              */
/************************************************/

#include "../v10.h"

int code39_start=0224;
int code39_data[] = {
0064, 0441, 0141, 0540, 0061, 0460, 0160, 0045, 0444,
0144, 0411, 0111, 0510, 0031, 0430, 0130, 0015, 0414,
0114, 0034, 0403, 0103, 0502, 0023, 0422, 0122, 0007,
0406, 0106, 0026, 0601, 0301, 0700, 0221, 0620, 0320,
0205, 0604, 0304, 0250, 0242, 0212, 0052          };
unsigned char code39_letter[] = {
'0', '1', '2', '3', '4', '5', '6', '7', '8',
'9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
'-', '.', ' ', '$', '/', '+', '%', 0         };


void do_3x9(int value,int count)  /* alternate the bars for 3 of 9 bar code */
{
   value <<= 1;
   count++;                            /* add the inter-character space */
   alternate(value,count);             /* put the codes in */
}

int xthree_9(unsigned char *string,int chksum)  /* print an extended 3 of 9 bar code */
{
  unsigned char *ptr;
  register int x;
  for (ptr=CM_NEWSTR,x=strlen((char *)string); x; x--,string++) {
      /* if null character */
      if (*string == CM_NULLCHAR) {
	 *ptr++ = '%';		/* null = %U */
	 *ptr++ = 'U';
	 continue;
       }
   /* if a normal 3of9 character, store as normal (except $/%+) */
      if (isdigit(*string) || isupper(*string) || findchr((char *)"-. ",*string)) {
	 *ptr++ = *string;
	 continue;
       }
   /* if a lower case letter, precede with a plus sign */
      if (islower(*string)) {
	 *ptr++ = '+';
	 *ptr++ = (char)upper(*string);
	 continue;
       }
   /* if a control char below 27, precede with dollar sign */
      if (*string < 27) {
	 *ptr++ = '$';
	 *ptr++ =(char)( (*string - 1) + 'A');
	 continue;
       }
      if (*string < ' ') {
	 *ptr++ = '%';
	 *ptr++ =(char)( (*string - 27) + 'A');
	 continue;
       }
      if (*string <= ':') {
	 *ptr++ = '/';
	 *ptr++ =(char)( (*string - '!') + 'A');
	 continue;
       }
      if (*string <= '?') {
	 *ptr++ = '%';
	 *ptr++ = (char)((*string - ';') + 'F');
	 continue;
       }
      if (*string == '@') {
	 *ptr++ = '%';
	 *ptr++ = 'V';
	 continue;
       }
      if (*string <= '_') {
	 *ptr++ = '%';
	 *ptr++ =(char)( (*string - '[') + 'K');
	 continue;
       }
      if (*string == '`') {
	 *ptr++ = '%';
	 *ptr++ = 'W';
	 continue;
       }
      if (*string <= 127) {
	 *ptr++ = '%';
	 *ptr++ =(char)( (*string - '{') + 'P');
	 continue;
       }
    }
   *ptr = '\0';                        /* terminate this string! */
   return(three_9(CM_NEWSTR,chksum));
}

int three_9(unsigned char *string,int chksum)  /* print a 3 of 9 bar code */
{
  int checksum;
  unsigned char *index;
  unsigned char *ptr;
  register int x;
  for (ptr=CM_NEWSTR,x=strlen(CM_NEWSTR); x; x--,ptr++)
      *ptr =(char) upper(*ptr);
  for (ptr=string,x=strlen(string) ; x; x--,ptr++) {
      if (!findchr(code39_letter,upper(*ptr))) return(1);
   }
  clearbar();                         /* clear the bar code area */
  do_3x9(code39_start,9);             /* add the start character */
  for (ptr=string,x=strlen(string) ; x ; x--,ptr++) {
      index = findchr(code39_letter,upper(*ptr));
      if (index) {
         do_3x9(code39_data[(int)(index-code39_letter)],9);
       }
   }
  if (chksum) {                     /* if checksum enabled, print it */
      for (checksum=0,ptr=string,x=strlen(string); x; x--,ptr++) {
          index = findchr(code39_letter,upper(*ptr));
          checksum += (int)(index-code39_letter);
       }
      checksum %= 43;
      CM_CHECKSUM = code39_letter[checksum];  /* save checksum */
      append(CM_NEWSTR,CM_CHECKSUM);   /* store checksum into new string */
      do_3x9(code39_data[checksum],9);
   }
  do_3x9(code39_start,9);              /* add the stop character */
   return(0);
}

int hibc(unsigned char *string,int chksum)  /* print a 3 of 9 HIBC bar code */
{
  unsigned char *ptr;
  ptr = CM_NEWSTR;
  *ptr++ = '+';
  while (*string) {
        *ptr++ = *string++;
   }
  *ptr = '\0';			/* terminate the string */
  return(three_9(CM_NEWSTR,chksum));
}

