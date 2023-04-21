#include "info3.h"

/********************************************************
 Codificación de los digitos de un display alfanumérico *
                                                        *
                      __0__ __1__                       *
                     |\    |    /|                      *
                     | \   |   / |                      *
                    7|  \9 |A /B |2                     *
                     |   \ | /   |                      *
                     |__8_\|/____|                      *
                     |    /|\  C |                      *
                     |   / | \   |                      *
                    6| F/ E| D\  |3                     *
                     | /   |   \ |                      *
                     |/_5__|__4_\|                      *
                                                        *
                                                        *
********************************************************/

#define SA  0x80
#define SB  0x20
#define SC  0x08
#define SD  0x02
#define SE  0x01
#define SF  0x40
#define SG  0X10
//Tabla ascii para digitos numericos
unsigned infotascii8[256]={
     255,  1,  2,  4,  8, 16, 32, 64,128,  1,  2,  4,  8, 16, 32, 64,
     128,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  /*                         !                   "               #  */
           0           ,255           ,SB+SF              ,    255,
  /*       $                 %                   &               ' */
     255,255,255,255,
  /*       (                 )                   *               + */
   SA+SD+SE+SF         ,SA+SB+SC+SD    ,       255,            0,
  /*       ,                 -                   .               / */
           255         ,SG             ,         255     ,     255,
  /*       0                 1                   2               3 */
   SA+SB+SC+SD+SE+SF   , SB+SC         , SA+SB+SD+SE+SG  , SA+SB+SC+SD+SG,
  /*       4                 5                   6               7 */
   SB+SC+SF+SG         ,SA+SC+SD+SF+SG ,SA+SC+SD+SE+SF+SG,SA+SB+SC,
  /*       8                   9                 :               ; */
   SA+SB+SC+SD+SE+SF+SG,SA+SB+SC+SD+SF+SG,       255     ,     255,
  /*       <                   =                 >               ? */
           255         ,       255       ,       255     ,     255,
   /*      @                   A                 B               C */
   0xff    ,SA+SB+SC+SE+SF+SG,SA+SB+SC+SD+SE+SF+SG,SA+SD+SE+SF,
   /*      D                   E                 F               G */
   SA+SB+SC+SD+SE+SF   ,SA+SD+SE+SF+SG   ,SA+SE+SF+SG     ,    255,
   /*      H                   I                 J               K */
   SB+SC+SE+SF+SG      ,SE+SF            ,SB+SC+SD        ,    255,
   /*      L                   M                 N               O */
   SD+SE+SF            ,255              ,SA+SB+SC+SE+SF  ,SA+SB+SC+SD+SE+SF,
   /*      P                   Q                 R               S */
   SA+SB+SE+SF+SG      ,255              ,SA+SB+SC+SE+SF+SG,SA+SC+SD+SF+SG,
   /*      T                   U                 V               W */
   SD+SE+SF+SG         ,SB+SC+SD+SE+SF   ,SB+SC+SD+SE+SF  ,255,
   /*      X                   Y                 Z               [ */
   SB+SC+SE+SF+SG      ,SB+SC+SD+SF+SG   ,SA+SB+SD+SE+SG  ,SA+SD+SE+SF,
   /*      \                   ]                 ^               _ */
      255              ,SA+SB+SC+SD      ,255             ,SD,
   /*      `                   a                 b               c */
       255             ,SA+SB+SC+SE+SF+SG,SC+SD+SE+SF+SG  ,SD+SE+SG,
   /*      d                   e                 f               g */
   SB+SC+SD+SE+SG      ,SA+SB+SD+SE+SF+SG,SA+SE+SF+SG     ,SA+SB+SC+SD+SF+SG,
   /*      h                   i                 j               k */
   SC+SE+SF+SG         ,SE               ,SB+SC+SD+SE     ,255     ,
   /*      l                   m                 n               o */
   SE+SF               ,255              ,SC+SE+SG        ,SC+SD+SE+SG,
   /*      p                   q                 r               s */
   SA+SB+SE+SF+SG      ,SA+SB+SC+SF+SG   ,SE+SG           ,SA+SC+SD+SF+SG,
   /*      t                   u                 v               w */
   SD+SE+SF+SG         ,SC+SD+SE         ,SC+SD+SE        ,255     ,
   /*      x                   y                 z               { */
   SB+SC+SE+SF+SG      ,SB+SC+SD+SF+SG      ,SA+SB+SD+SE+SG  ,SA+SD+SE+SF,
   /*      |                   }                 ~                */
   255                 ,255              ,255             ,0xaa        ,
     255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
     255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
     255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
     255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
     255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
     255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
     255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
     255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  0xff};

#define D0   0x2000U
#define D1   0x2000U
#define D2   0x4000U
#define D3   0x0080U
#define D4   0x0020U
#define D5   0x0020U
#define D6   0x0001U
#define D7   0x0100U
#define D8   0x1000U
#define D9   0x0200U
#define DA   0x0400U
#define DB   0x0800U
#define DC   0x0010U
#define DD   0x0008U
#define DE   0x0004U
#define DF   0x0002U

#define A0   0x2000U
#define A1   0x2000U
#define A2   0x4000U
#define A3   0x0080U
#define A4   0x0020U
#define A5   0x0020U
#define A6   0x0001U
#define A7   0x0100U
#define A8   0x1000U
#define A9   0x0200U
#define AA   0x0400U
#define AB   0x0800U
#define AC   0x0010U
#define AD   0x0008U
#define AE   0x0004U
#define AF   0x0002U
#define AP   0X0040U

// Tabla ascii de digitos alfanumericos displays SETRONIA
unsigned infotascii16[256]={
       0,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  /*                         !                   "               #  */
           0           ,0             ,DA|D2              ,   0xFFFF,
  /*       $                 %                   &               ' */
       0,  0,  0,  0,
  /*       (                 )                   *               | */
   DB|DD         ,D9|DF     , D8|D9|DA|DB|DC|DD|DE|DF, D8|DA|DC|DE,
  /*       ,                 -                   .               / */
           0           ,D8|DC             ,         0       ,      DB|DF,
  /*       0                 1                   2                    3 */
   D0|D1|D2|D3|D4|D5|D6|D7|DB|DF  ,D2|D3|DB      , D0|D1|D2|D4|D5|D6|D8|DC   , D0|D1|D2|D3|D4|D5|DC            ,
  /*       4                 5                   6                     7 */
   D2|D3|D7|D8|DC     ,D0|D1|D3|D4|D5|D7|D8|DC    ,D0|D1|D3|D4|D5|D6|D7|D8|DC  ,D0|D1|D2|D3|DC      ,
  /*       8                   9                      :               ; */
   D0|D1|D2|D3|D4|D5|D6|D7|D8|DC ,D0|D1|D2|D3|D4|D5|D7|D8|DC , DA|DE            ,    DD  ,
  /*       <                   =                 >               ? */
      DB|DD           ,  D4|D5|D8|DC      ,  D9|DF      ,       0,
   /*      @                   A                     B                      C */
   0xffff             ,D0|D1|D2|D3|D6|D7|D8|DC ,D0|D1|D2|D3|D4|D5|DA|DE|DC,  D0|D1|D4|D5|D6|D7,
   /*      D                   E                 F               G */
   D0|D1|D2|D3|D4|D5|DA|DE   ,D0|D1|D4|D5|D6|D7|D8   ,D0|D1|D6|D7|D8     ,  D0|D1|D3|D4|D5|D6|D7|DC   ,
   /*      H                   I                 J               K */
   D2|D3|D6|D7|D8|DC   ,D0|D1|D4|D5|DA|DE             ,D2|D3|D4|D5|D6        , D6|D7|D8|DB|DD,
   /*      L                   M                 N               O */
   D4|D5|D6|D7            ,D2|D3|D6|D7|D9|DB ,D2|D3|D6|D7|D9|DD ,D0|D1|D2|D3|D4|D5|D6|D7,
   /*      P                   Q                 R               S */
   D0|D1|D2|D6|D7|D8|DC ,D0|D1|D2|D3|D4|D5|D6|D7|DD ,D0|D1|D2|D6|D7|D8|DC|DD,D0|D1|D3|D4|D5|D7|D8|DC,
   /*      T                   U                 V               W */
   D0|D1|DA|DE         ,D2|D3|D4|D5|D6|D7   ,D6|D7|DB|DF  ,D2|D3|D6|D7|DD|DF,
   /*      X                   Y                 Z               [ */
   D9|DB|DD|DF   ,D9|DB|DE            ,D0|D1|D4|D5|D8|DB|DC|DF  ,D0|D1|D4|D5|D6|D7,
   /*      \                   ]                 ^               _ */
      D9|DD                ,D0|D1|D2|D3|D4|D5     ,DD|DF               ,D4|D5,
   /*      `                   a                 b               c */
       D9               ,D4|D5|D6|D8|DE,D5|D6|D7|D8|DE  ,D5|D6|D8,
   /*      d                   e                 f                   g */
   D5|D6|D8|DA|DE  ,D4|D5|D6|D8|DF,   D1|D8|DA|DC|DE,   D0|D5|D7|D8|DA|DE,
   /*      h                   i                 j               k */
   D6|D7|D8|DE      ,D6               ,D2|D3|D4|DE     ,D6|D7|D8|DA|DE ,
   /*      l                   m                 n               o D5|D6|D8|DE*/
   D5|D6|D7              ,D3|D6|D8|DC|DE   ,D6|D8|DE        ,D5|D6|D8|DE,
   /*      p                   q                 r               s */
   D0|D6|D7|D8|DA      ,D0|D7|D8|DA|DE   ,D6|D8           ,D4|DC|DD,
   /*      t                   u                 v               w */
   D5|D6|D7|D8         ,D5|D6|DE         ,D6|DF        ,D3|D6|DD|DF      ,
   /*      x                   y                 z               { */
   D9|DB|DD|DF      ,D3|D4|DD      ,D5|D8|DF    ,D2|D3|DC,
   /*      |                   }                 ~                */
    DA|DE                   ,D6|D7|D8                ,0xaa               ,0          ,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  D0|D1|D3|D6|D8|DC,  D0|D1|D2|D3|D6|D7|D9|DD,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0xffff};

//Tabla ascii de digitos alfanumericos displays ELALGA
unsigned infotan16[256]={
       0,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000,
       0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
  /*                         !                   "               #  */
           0            ,0xffff         ,AA|A2              ,   0xFFFF,
  /*       $                 %                   &               ' */
     0xffff,0xffff,0xffff,0xffff,
  /*       (                 )                   *               | */
   AB|AD         ,A9|AF     , A8|A9|AA|AB|AC|AD|AE|AF, A8|AA|AC|AE,
  /*       ,                 -                   .               / */
           0xffff       ,A8|AC             ,      AP       ,      AB|AF,
  /*       0                 1                   2                    3 */
   A0|A1|A2|A3|A4|A5|A6|A7|AB|AF  ,A2|A3|AB      , A0|A1|A2|A4|A5|A6|A8|AC   , A0|A1|A2|A3|A4|A5|AC            ,
  /*       4                 5                   6                     7 */
   A2|A3|A7|A8|AC     ,A0|A1|A3|A4|A5|A7|A8|AC    ,A0|A1|A3|A4|A5|A6|A7|A8|AC  ,A0|A1|A2|A3      ,
  /*       8                   9                      :               ; */
   A0|A1|A2|A3|A4|A5|A6|A7|A8|AC ,A0|A1|A2|A3|A4|A5|A7|A8|AC , AA|AE            ,    AD  ,
  /*       <                   =                 >               ? */
      AB|AD           ,  A4|A5|A8|AC      ,  A9|AF      ,     0xffff,
   /*      @                   A                     B                      C */
   0xffff             ,A0|A1|A2|A3|A6|A7|A8|AC ,A0|A1|A2|A3|A4|A5|AA|AE|AC,  A0|A1|A4|A5|A6|A7,
   /*      D                   E                 F               G */
   A0|A1|A2|A3|A4|A5|AA|AE   ,A0|A1|A4|A5|A6|A7|A8   ,A0|A1|A6|A7|A8     ,  A0|A1|A3|A4|A5|A6|A7|AC   ,
   /*      H                   I                 J               K */
   A2|A3|A6|A7|A8|AC   ,A0|A1|A4|A5|AA|AE             ,A2|A3|A4|A5|A6        , A6|A7|A8|AB|AD,
   /*      L                   M                 N               O */
   A4|A5|A6|A7            ,A2|A3|A6|A7|A9|AB ,A2|A3|A6|A7|A9|AD ,A0|A1|A2|A3|A4|A5|A6|A7,
   /*      P                   Q                 R               S */
   A0|A1|A2|A6|A7|A8|AC ,A0|A1|A2|A3|A4|A5|A6|A7|AD ,A0|A1|A2|A6|A7|A8|AC|AD,A0|A1|A3|A4|A5|A7|A8|AC,
   /*      T                   U                 V               W */
   A0|A1|AA|AE         ,A2|A3|A4|A5|A6|A7   ,A6|A7|AB|AF  ,A2|A3|A6|A7|AD|AF,
   /*      X                   Y                 Z               [ */
   A9|AB|AD|AF   ,A9|AB|AE            ,A0|A1|A4|A5|A8|AB|AC|AF  ,A0|A1|A4|A5|A6|A7,
   /*      \                   ]                 ^               _ */
      A9|AD                ,A0|A1|A2|A3|A4|A5     ,AD|AF               ,A4|A5,
   /*      `                   a                 b               c */
       A9               ,A4|A5|A6|A8|AE,A5|A6|A7|A8|AE  ,A5|A6|A8,
   /*      A                   e                 f                   g */
   A5|A6|A8|AA|AE  ,A4|A5|A6|A8|AF,   A1|A8|AA|AC|AE,   A0|A5|A7|A8|AA|AE,
   /*      h                   i                 j               k */
   A6|A7|A8|AE      ,A6               ,A2|A3|A4|AE     ,A6|A7|A8|AA|AE ,
   /*      l                   m                 n               o */
   A5|A6|A7              ,A3|A6|A8|AC|AE   ,A6|A8|AE        ,A3|A4|A5|A6|A8|AC,
   /*      p                   q                 r               s */
   A0|A6|A7|A8|AA      ,A0|A7|A8|AA|AE   ,A6|A8           ,A4|AC|AD,
   /*      t                   u                 v               w */
   A5|A6|A7|A8         ,A5|A6|AE         ,A6|AF        ,A3|A6|AD|AF      ,
   /*      x                   y                 z               { */
   A9|AB|AD|AF      ,A3|A4|AD      ,A5|A8|AF    ,A2|A3|AC,
   /*      |                   }                 ~                */
    AA|AE                   ,A6|A7|A8                ,0xaaaa           ,0xffff      ,
     0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
     0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
     0xffff,0xffff,0xffff,0xffff,  A0|A1|A3|A6|A8|AC,  A0|A1|A2|A3|A6|A7|A9|AD,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
     0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
     0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
     0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
     0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
     
	 0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,//0xffff,0xffff,
	 A2|A3|AB,
	 A2|A3|AB|AP,
	 // todos los LEDS excepto el punto
	 A1|A2|A3|A4|A5|A6|A7|A8|A9|AA|AB|AC|AD|AE|AF,0xffff};
//     0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff};

