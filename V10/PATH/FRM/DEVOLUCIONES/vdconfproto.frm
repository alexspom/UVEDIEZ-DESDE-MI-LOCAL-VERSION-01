INCLUDEFICHEROCSS="vertissimple.css"
#INCLUDECSS="fieldset#fsbl1 label{font-family:Tahoma;font-size:28pt;padding:0px 0px 0px 0px;color:#2E2E2E;position:absolute;overflow:visible;}"
#INCLUDEFICHEROHTML="botoneratactil.html"
#INCLUDEHTML="<SCRIPT> window.document.getElementById('tactil').style.top=550+'px'; window.document.getElementById('tactil').style.left=970+'px'; </SCRIPT>"

#INCLUDEFICHEROCSS="vertissimple.css"
BEGINBLOQUE=VDCONFPROTO1.PAN
  PREREGISTRO=PRESEHIJO
  POSY=4
  POSX=4
  WLONX=1240
  WLONY=905
  WHERE = STATUS = VDVST.FDVCPDTEPROTO;
ENDBLOQUE
BEGINBLOQUE=VDCONFPROTO2.PAN
  PADRE=VDCONFPROTO1.PAN
  PREQUERY=QUERYHIJO
  PREREGISTRO=PRESEHIJO
  POSY=16
  POSX=5
  REGPAG=40
  WLONY=720
  WLONX=1200
  WMARCOFRAME
ENDBLOQUE  
