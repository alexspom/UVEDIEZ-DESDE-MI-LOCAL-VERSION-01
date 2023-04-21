#include "v10wwwform.h"
 
void v10online2html(bloques *b, char *cad, int extonline) {
  char textoonline[MAXCADENA]="";
  char *inicio,*corchete;
  char tip[MAXCADENA]="";

  if (!b->online || strlen(b->online)==0) return;
  strcpy(textoonline,b->online);
  v10carespeciales(textoonline,'\n'," ");
  v10ansitohtml(textoonline);
  
  *cad=0;
  inicio=strchr(textoonline,'{');
  if (!inicio) inicio=textoonline;
  do {
	  corchete=strchr(inicio+1,'{');
	  if (corchete) strcopia(tip,inicio,(int)(corchete-inicio));
	  else strcpy(tip,inicio);
	  v10carespeciales(tip,'{',"<font color=\'#eb9800\'>{");
 	  v10carespeciales(tip,'}',"}</font>");		
	  if (extonline==0) {
		sprintf(cad+strlen(cad),"v10lib.nuevotip(\"%s\");\n", tip);
	  } else {
		strcat(cad,tip);
		strcat(cad,"\\n");
	  }
	  inicio=corchete; 
  } while (corchete);

   
}
