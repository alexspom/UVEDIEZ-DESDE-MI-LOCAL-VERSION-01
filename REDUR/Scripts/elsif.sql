BEGIN
  FOR CONT IN 1..100 LOOP
     FOR I IN 1..12 LOOP
       VDECOUNI.REFRESCAZONA(I);
     END LOOP;
   END LOOP;
END;  

BEGIN
  IF :HAY>0 THEN
     :RET:='HAY 0';
   ELSIF :HAY<:PIDE THEN
     :RET:='MENOR';
    END IF;
END;    