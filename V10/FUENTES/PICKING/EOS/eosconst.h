
//Valores por defecto del UNC90

#define TIMEOUTWHO   100

#define TIMEOUTTRAMA 200
#define TENVTRAMA    20
#define TPERRO232    100
#define LIMITACIONLINEA 8000000
#define TCICLO       1
#define TRAMASNULAS  20

//Definicion de teclas del display
#define TECLAACEPTA   0

#define TECLAMAS      1

#define TECLAMENOS    2

#define TECLAFUNCION  3

//Valores maximos de constantes
#define MAXETHER         10
#define MAXLINEAS        32
#define MAXPUERTOS       16
#define MAXDISPLAYS     250
#define MAXTOTDISPLAYS  (MAXETHER*MAXLINEAS*MAXDISPLAYS)
#define MAXDIGDISPLAY    65
#define MAXSTATUSDISPLAY 10
#define MAXNOMBREDISPLAY 20
#define MAXLUCESDISPLAY   7
#define MAXBOTONESDISPLAY 4
#define MAXBYTESLUZ       ((MAXLUCESDISPLAY+3)/4)

//Definicion de bits de status en nibble alto
#define BITSTLEN     0X80
#define BITERRHARD   0X40
#define BITERRSOFT   0X20

