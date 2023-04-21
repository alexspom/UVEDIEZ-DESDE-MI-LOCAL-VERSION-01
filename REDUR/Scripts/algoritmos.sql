Insert into VDALGORITMOS
   (PROCESO, NOMBREALG, DESALG, DISCRIMINANTE, PARAMALG, 
    FUNCIONALG, LIBALGORITMO, ACTIVO, CODCOMEN, CODOPEMODIF, 
    FECMODIF, HORAMODIF)
 Values
   ('PICKING', 'ANULAREG', 'ANULA LA REGULARIZACION Y VUELVE A PEDIR CANTIDAD', '###SIRVEMENOS,PASOX0##FUNC#0', 'VDECOUNI.ANULAREG(:IDINFOPICK,:NUMDISP,:MITECLA)', 
    'procesatecladisp', 'XVDPICK.DLL', 'S', 97674928, 'X', 
    2457739, '08:02:41');
Insert into VDALGORITMOS
   (PROCESO, NOMBREALG, DESALG, DISCRIMINANTE, PARAMALG, 
    FUNCIONALG, LIBALGORITMO, ACTIVO, CODCOMEN, CODOPEMODIF, 
    FECMODIF, HORAMODIF)
 Values
   ('PICKING', 'DECREMENTA', 'DECREMENTA EL VALOR DEL DISPLAY', '###PICKING##MENOS#0', 'VDECOUNI.DECREMENTA(:IDINFOPICK,:NUMDISP,:MITECLA)', 
    'procesatecladisp', 'XVDPICK.DLL', 'S', 97674929, 'X', 
    2457739, '07:59:57');
Insert into VDALGORITMOS
   (PROCESO, NOMBREALG, DESALG, DISCRIMINANTE, PARAMALG, 
    FUNCIONALG, LIBALGORITMO, ACTIVO, CODCOMEN, CODOPEMODIF, 
    FECMODIF, HORAMODIF)
 Values
   ('PICKING', 'DECREMENTAX0', 'DECREMENTA EL VALOR DEL DISPLAY EN PASO POR CERO', '###PASOX0##MENOS#0', 'VDECOUNI.DECREMENTAX0(:IDINFOPICK,:NUMDISP,:MITECLA)', 
    'procesatecladisp', 'XVDPICK.DLL', 'S', 97674930, 'X', 
    2457797, '12:37:18');
Insert into VDALGORITMOS
   (PROCESO, NOMBREALG, DESALG, DISCRIMINANTE, PARAMALG, 
    FUNCIONALG, LIBALGORITMO, ACTIVO, CODCOMEN, CODOPEMODIF, 
    FECMODIF, HORAMODIF)
 Values
   ('PICKING', 'DEFECTO', 'FUNCION POR DEFECTO AL PULSAR UNA TECLA NO ESPERADA', '######', 'VDECOUNI.DEFECTO(:IDINFOPICK,:NUMDISP,:MITECLA)', 
    'procesatecladisp', 'XVDPICK.DLL', 'S', 97674931, 'X', 
    2457739, '08:02:55');
Insert into VDALGORITMOS
   (PROCESO, NOMBREALG, DESALG, DISCRIMINANTE, PARAMALG, 
    FUNCIONALG, LIBALGORITMO, ACTIVO, CODCOMEN, CODOPEMODIF, 
    FECMODIF, HORAMODIF)
 Values
   ('PICKING', 'INCREMENTA', 'INCREMENTA EL VALOR DEL DISPLAY', '###PICKING##MAS#0', 'VDECOUNI.INCREMENTA(:IDINFOPICK,:NUMDISP,:MITECLA)', 
    'procesatecladisp', 'XVDPICK.DLL', 'S', 97674932, 'X', 
    2457739, '08:03:01');
Insert into VDALGORITMOS
   (PROCESO, NOMBREALG, DESALG, DISCRIMINANTE, PARAMALG, 
    FUNCIONALG, LIBALGORITMO, ACTIVO, CODCOMEN, CODOPEMODIF, 
    FECMODIF, HORAMODIF)
 Values
   ('PICKING', 'INCREMENTAX0', 'INCREMENTA EL VALOR DEL DISPLAY EN PASO POR CERO', '###PASOX0##MAS#0', 'VDECOUNI.INCREMENTAX0(:IDINFOPICK,:NUMDISP,:MITECLA)', 
    'procesatecladisp', 'XVDPICK.DLL', 'S', 97674933, 'X', 
    2457797, '12:37:09');
Insert into VDALGORITMOS
   (PROCESO, NOMBREALG, DESALG, DISCRIMINANTE, PARAMALG, 
    FUNCIONALG, LIBALGORITMO, ACTIVO, CODCOMEN, CODOPEMODIF, 
    FECMODIF, HORAMODIF)
 Values
   ('PICKING', 'VALIDA', 'VALIDA EL PICKING', '###PICKING##VALIDA#0', 'VDECOUNI.VALIDA(:IDINFOPICK,:NUMDISP,:MITECLA)', 
    'procesatecladisp', 'XVDPICK.DLL', 'S', 97674934, 'X', 
    2457739, '08:03:12');
Insert into VDALGORITMOS
   (PROCESO, NOMBREALG, DESALG, DISCRIMINANTE, PARAMALG, 
    FUNCIONALG, LIBALGORITMO, ACTIVO, CODCOMEN, CODOPEMODIF, 
    FECMODIF, HORAMODIF)
 Values
   ('PICKING', 'VALIDACIERRE', 'VALIDA EL CIERRE DEL CANDADO', '###CONFCIERRE###0', 'VDECOUNI.VALIDACIERRE(:IDINFOPICK,:NUMDISP,:MITECLA)', 
    'procesatecladisp', 'XVDPICK.DLL', 'S', 97810752, 'X', 
    2457804, '10:16:10');
Insert into VDALGORITMOS
   (PROCESO, NOMBREALG, DESALG, DISCRIMINANTE, PARAMALG, 
    FUNCIONALG, LIBALGORITMO, ACTIVO, CODCOMEN, CODOPEMODIF, 
    FECMODIF, HORAMODIF)
 Values
   ('PICKING', 'VALIDAFIN', 'VALIDA EL FIN', '###FINBULTO,FINPICKING##VALIDA#0', 'VDECOUNI.VALIDAFIN(:IDINFOPICK,:NUMDISP,:MITECLA)', 
    'procesatecladisp', 'XVDPICK.DLL', 'S', 97674935, 'X', 
    2457801, '17:03:47');
Insert into VDALGORITMOS
   (PROCESO, NOMBREALG, DESALG, DISCRIMINANTE, PARAMALG, 
    FUNCIONALG, LIBALGORITMO, ACTIVO, CODCOMEN, CODOPEMODIF, 
    FECMODIF, HORAMODIF)
 Values
   ('PICKING', 'VALIDAFINBULTO', 'VALIDA EL FIN DEL BULTO EN EL CONTROLADOR', '####FINBULTO#VALIDA#1', 'VDECOUNI.VALIDAFINBULTO(:IDINFOPICK,:NUMDISP,:MITECLA)', 
    'procesatecladisp', 'XVDPICK.DLL', 'S', 98185861, 'X', 
    2457812, '21:00:47');
Insert into VDALGORITMOS
   (PROCESO, NOMBREALG, DESALG, DISCRIMINANTE, PARAMALG, 
    FUNCIONALG, LIBALGORITMO, ACTIVO, CODCOMEN, CODOPEMODIF, 
    FECMODIF, HORAMODIF)
 Values
   ('PICKING', 'VALIDAREG', 'VALIDA CUANDO SE SIRVE DE MENOS', '###SIRVEMENOS##VALIDA#0', 'VDECOUNI.VALIDAREG(:IDINFOPICK,:NUMDISP,:MITECLA)', 
    'procesatecladisp', 'XVDPICK.DLL', 'S', 97674937, 'X', 
    2457797, '10:28:15');
Insert into VDALGORITMOS
   (PROCESO, NOMBREALG, DESALG, DISCRIMINANTE, PARAMALG, 
    FUNCIONALG, LIBALGORITMO, ACTIVO, CODCOMEN, CODOPEMODIF, 
    FECMODIF, HORAMODIF)
 Values
   ('PICKING', 'VALIDAX0', 'VALIDA EL PASO POR CERO', '###PASOX0##VALIDA#0', 'VDECOUNI.VALIDAX0(:IDINFOPICK,:NUMDISP,:MITECLA)', 
    'procesatecladisp', 'XVDPICK.DLL', 'S', 97674936, 'X', 
    2457797, '10:28:15');
Insert into VDALGORITMOS
   (PROCESO, NOMBREALG, DESALG, DISCRIMINANTE, PARAMALG, 
    FUNCIONALG, LIBALGORITMO, ACTIVO, CODCOMEN, CODOPEMODIF, 
    FECMODIF, HORAMODIF)
 Values
   ('PICKING', 'VALIDAZONA', 'VALIDA EL CONTROLADOR DE ZONA', '#####VALIDA#1', 'VDECOUNI.VALIDAZONA(:IDINFOPICK,:NUMDISP,:MITECLA)', 
    'procesatecladisp', 'XVDPICK.DLL', 'S', 97674938, 'X', 
    2457739, '08:03:18');
COMMIT;