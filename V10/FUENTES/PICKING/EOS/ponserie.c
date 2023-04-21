#include <stdio.h>

#define DISPSERIE "DISPSERIE.DAT"
#define EEPROM "D:\\AVR\\PROYECTOS\\"
 
static long eliminaff(long serie)
{
  long aserie=serie;
  if ((serie&0xff)==0xff) serie++;
  if (((serie>>8)&0xff)==0xff) serie+=0x0100;
  if (((serie>>16)&0xff)==0xff) serie+=0x010000;
  if (((serie>>24)&0xff)==0xff) serie+=0x01000000;
  if (aserie==serie) return(serie);
     else            return(eliminaff(serie));
}

void grabaserie(char *destino)
{
  FILE *entrada,*salida;
  long serie,calcula;
  char buffer[100];
  entrada=fopen(DISPSERIE,"r+");
  if (entrada==NULL) {
     entrada=fopen(DISPSERIE,"w+");
     if (entrada==NULL) {
        printf("Error no puedo abrir fichero %s",DISPSERIE);
      }
   }
  fgets(buffer,sizeof(buffer),entrada);
  serie=atoi(buffer);
  serie=eliminaff(serie);
  printf("serie %08x\n",serie);
  salida=fopen(destino,"w+");
  if (salida==NULL) {
     printf("No puedo abrir %s\n");
     exit(-1);
   }
  calcula=0x4+0x1+0x91+(serie&0xff)+((serie>>8)&0xff)+((serie>>16)&0xff)+((serie>>24)&0xff);
  calcula=255-(calcula&0xff)+1;
  fprintf(salida,":04019100%02X%02X%02X%02X%02X\n",serie&0xff,(serie>>8)&0xff,(serie>>16)&0xff,(serie>>24)&0xff,calcula);
  fprintf(salida,":00000001FF\n");
  fseek(entrada,0,SEEK_SET);
  fprintf(entrada,"%09ld\n",serie+1);
  fclose(entrada);
  fclose(salida);
}

int main(int argc,char *argv[])
{
   char destino[2000],*eeprom;
   if (argc<2) {
      printf("Uso ponserie TIPODISP\n");
      exit(1);
    }
   if (argc>2) eeprom=argv[2];
      else     eeprom=argv[1];
   sprintf(destino,"%s%s\\%s.eep",EEPROM,argv[1],eeprom);
   grabaserie(destino);
   getch();
   return(0);
}
