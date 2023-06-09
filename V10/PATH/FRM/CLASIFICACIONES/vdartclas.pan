# Módulo   : VDARTCLAS.PAN
# Función  : Clasificación de artículos
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
CLASIFICACIONES
 Clasificación   Oblig.  Clase
 _______________ _       _40______________
|

TABLA=VDCLASIFICACIONES

ORDERBY=NVL(SWTOBLIG,'ZZ'),ORDENCLASIF,CODCLASIF;
WHERE=VDUSER.TENGOPRIVILEGIO(PRIVILEGIOSVER)=1 AND TABLACLASIF='VDARTIC';
SELECT=DECODE(VDUSER.TENGOPRIVILEGIO(PRIVILEGIOSMOD),1,1,0) CODCLASE__ENTER;

POSTQUERY=FDESIGNACION("+CSELCLASE","")
PREUPDATE=FEJECUTA("CACTUALIZACLASE","No puedo actualizar la clase")
POSTCOMMIT=FEJECUTATODOS("+CPONBLANCO","","+CSELCLASE","")

CAMPO=CODART,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODCLASIF,PROTECT("ADMINISTRADOR"),TOOLTIP("Clasificación de artículos"),TITULO("Clasificación")
CAMPO=SWTOBLIG,PROTECT("ADMINISTRADOR"),TOOLTIP("Indica si la clasificación es obligatoria"),TITULO("Oblig"),WLONX=25,CHECKBOX("N","S")
CAMPO=CODCLASE,PROTECT("ARTICULOS"),TOOLTIP("Clase a la que pertenece el artículo"),AUXILIAR,POSTCHANGE=FDESIGNACION("CVERCLASE","No existe clase"),
                 CONTEXTUAL=FEJECUTAFORM("VDSELCLASE","N","CODCLASIF=:CODCLASIF","","CODCLASE=:CODCLASE"),
                 COMBOX("CLISTACLASES"),TITULO("Clase")

CURSOR=CLISTACLASES SELECT CODCLASE,DESCLASE 
                       FROM VDCLASES 
                       WHERE CODCLASIF=:CODCLASIF AND (CODCLASIF!='SUBTIPO' OR SUBSTR(CODCLASE,1,3) IN (SELECT SUBSTR(CODCLASE,1,3) FROM VDCLASEARTIC WHERE CODART=:CODART AND CODCLASIF='TIPOART'));

CURSOR=CVERCLASE SELECT :CODCLASE FROM VDCLASES WHERE CODCLASE=:CODCLASE AND CODCLASIF=:CODCLASIF
                  UNION
                 SELECT NULL FROM DUAL WHERE :CODCLASE IS NULL;

CURSOR=CPONBLANCO SELECT '' CODCLASE FROM DUAL;

CURSOR=CSELCLASE SELECT CODCLASE FROM VDCLASEARTIC WHERE CODART(+)=:CODART AND CODCLASIF(+)=:CODCLASIF;

CURSOR=CACTUALIZACLASE BEGIN
                   DELETE VDCLASEARTIC WHERE CODCLASIF=:CODCLASIF AND CODART=:CODART;
                   IF :CODCLASE IS NOT NULL THEN
                      INSERT INTO VDCLASEARTIC (CODCLASIF,CODCLASE,CODART,VDEXTRA,CODOPEMODIF,FECMODIF,HORAMODIF)
                        VALUES (:CODCLASIF,:CODCLASE,:CODART,'',VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS);
                    END IF;
                   IF :CODCLASIF='TIPOART' THEN
                      DELETE VDCLASEARTIC WHERE CODART=:CODART AND CODCLASIF='SUBTIPO' AND SUBSTR(CODCLASE,1,3)!=SUBSTR(:CODCLASE,1,3);
                     END IF;
                  END;@
                  

