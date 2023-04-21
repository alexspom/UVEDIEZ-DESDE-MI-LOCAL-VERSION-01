/* Copyright (c) 2006 Yahoo! Inc. All rights reserved. */

/**
 * @class The Yahoo global namespace
 */
var YAHOO = function() {

    return {

        /**
         * Yahoo presentation platform utils namespace
         */
        util: {},

        /**
         * Yahoo presentation platform widgets namespace
         */
        widget: {},

        /**
         * Yahoo presentation platform examples namespace
         */
        example: {},

        /**
         * Returns the namespace specified and creates it if it doesn't exist
         *
         * YAHOO.namespace("property.package");
         * YAHOO.namespace("YAHOO.property.package");
         *
         * Either of the above would create YAHOO.property, then
         * YAHOO.property.package
         *
         * @param  {String} sNameSpace String representation of the desired 
         *                             namespace
         * @return {Object}            A reference to the namespace object
         */
        namespace: function( sNameSpace ) {

            if (!sNameSpace || !sNameSpace.length) {
                return null;
            }

            var levels = sNameSpace.split(".");

            var currentNS = YAHOO;

            // YAHOO is implied, so it is ignored if it is included
            for (var i=(levels[0] == "YAHOO") ? 1 : 0; i<levels.length; ++i) {
                currentNS[levels[i]] = currentNS[levels[i]] || {};
                currentNS = currentNS[levels[i]];
            }

            return currentNS;

        }
    };

} ();



/* Copyright (c) 2006 Yahoo! Inc. All rights reserved. */

YAHOO.util.Color = new function() {
    
    // Adapted from http://www.easyrgb.com/math.html
    // hsv values = 0 - 1
    // rgb values 0 - 255
    this.hsv2rgb = function (h, s, v) {
        var r, g, b;
        if ( s == 0 ) {
           r = v * 255;
           g = v * 255;
           b = v * 255;
        } else {

           // h must be < 1
           var var_h = h * 6;
           if ( var_h == 6 ) {
               var_h = 0;
           }

           //Or ... var_i = floor( var_h )
           var var_i = Math.floor( var_h );
           var var_1 = v * ( 1 - s );
           var var_2 = v * ( 1 - s * ( var_h - var_i ) );
           var var_3 = v * ( 1 - s * ( 1 - ( var_h - var_i ) ) );

           if ( var_i == 0 ) { 
               var_r = v; 
               var_g = var_3; 
               var_b = var_1;
           } else if ( var_i == 1 ) { 
               var_r = var_2;
               var_g = v;
               var_b = var_1;
           } else if ( var_i == 2 ) {
               var_r = var_1;
               var_g = v;
               var_b = var_3
           } else if ( var_i == 3 ) {
               var_r = var_1;
               var_g = var_2;
               var_b = v;
           } else if ( var_i == 4 ) {
               var_r = var_3;
               var_g = var_1;
               var_b = v;
           } else { 
               var_r = v;
               var_g = var_1;
               var_b = var_2
           }

           r = var_r * 255                  //rgb results = 0 ÷ 255
           g = var_g * 255
           b = var_b * 255

           }
        return [Math.round(r), Math.round(g), Math.round(b)];
    };

    this.rgb2hex = function (r,g,b) {
        return this.toHex(r) + this.toHex(g) + this.toHex(b);
    };

    this.hexchars = "0123456789ABCDEF";

    this.toHex = function(n) {
        n = n || 0;
        n = parseInt(n, 10);
        if (isNaN(n)) n = 0;
        n = Math.round(Math.min(Math.max(0, n), 255));

        return this.hexchars.charAt((n - n % 16) / 16) + this.hexchars.charAt(n % 16);
    };

    this.toDec = function(hexchar) {
        return this.hexchars.indexOf(hexchar.toUpperCase());
    };

    this.hex2rgb = function(str) { 
        var rgb = [];
        rgb[0] = (this.toDec(str.substr(0, 1)) * 16) + 
                        this.toDec(str.substr(1, 1));
        rgb[1] = (this.toDec(str.substr(2, 1)) * 16) + 
                        this.toDec(str.substr(3, 1));
        rgb[2] = (this.toDec(str.substr(4, 1)) * 16) + 
                        this.toDec(str.substr(5, 1));
        // gLogger.debug("hex2rgb: " + str + ", " + rgb.toString());
        return rgb;
    };

    this.isValidRGB = function(a) { 
        if ((!a[0] && a[0] !=0) || isNaN(a[0]) || a[0] < 0 || a[0] > 255) return false;
        if ((!a[1] && a[1] !=0) || isNaN(a[1]) || a[1] < 0 || a[1] > 255) return false;
        if ((!a[2] && a[2] !=0) || isNaN(a[2]) || a[2] < 0 || a[2] > 255) return false;

        return true;
    };
}

// ddcolorposter.js
/*
======================================================================
ddcolorposter.js: By Dynamic Drive (http://www.dynamicdrive.com)
Communicates between Yahoo Color Picker and form fields on your page
Created: Feb 20th, 06'
======================================================================
*/

function executeonload(functionref){
	if (window.addEventListener)
		window.addEventListener("load", functionref, false)
	else if (window.attachEvent)
		window.attachEvent("onload", functionref)
	else if (document.getElementById)
		window.onload=functionref
}

var ddcolorposter={
initialize:function(r,g,b, hexvalue){
	this.rvalue=r //store red value
	this.gvalue=g //store green value
	this.bvalue=b //store blue value
	this.hexvalue=hexvalue //store combined hex value
	if (typeof this.targetobj!="undefined"){
		this.targetobj.value=this.hexvalue //set field to selected hex color value
		if (typeof this.divobj!="undefined") //set adjacent div to selected hex color value
			this.divobj.style.backgroundColor="#"+this.hexvalue
	}
},
echocolor:function(inputobj, divID){
	this.targetobj='colorfield1'
	this.divobj=document.getElementById('colorbox1')
	this.targetobj.onblur=function(){
	if (inputobj.value.search(/^[a-zA-Z0-9]{6}$/)!=-1) //if field contains valid hex value
		document.getElementById('colorbox1').style.backgroundColor="#"+inputobj.value
	}
},
fillcolorbox:function(inputID, divID){
	var inputobj=document.getElementById(inputID)
	if (inputobj.value.search(/^[a-zA-Z0-9]{6}$/)!=-1) //if field contains valid hex value
		document.getElementById(divID).style.backgroundColor="#"+inputobj.value
}
}

// dom.js
/* Copyright (c) 2006 Yahoo! Inc. All rights reserved. */
YAHOO.util.Dom=new function(){this.get=function(el){if(typeof el=='string'){el=document.getElementById(el);}
return el;};this.getStyle=function(el,property){var value=null;var dv=document.defaultView;el=this.get(el);if(property=='opacity'&&el.filters){value=1;try{value=el.filters.item('DXImageTransform.Microsoft.Alpha').opacity/100;}catch(e){try{value=el.filters.item('alpha').opacity/100;}catch(e){}}}
else if(el.style[property]){value=el.style[property];}
else if(el.currentStyle&&el.currentStyle[property]){value=el.currentStyle[property];}
else if(dv&&dv.getComputedStyle)
{var converted='';for(i=0,len=property.length;i<len;++i){if(property.charAt(i)==property.charAt(i).toUpperCase()){converted=converted+'-'+property.charAt(i).toLowerCase();}else{converted=converted+property.charAt(i);}}
if(dv.getComputedStyle(el,'').getPropertyValue(converted)){value=dv.getComputedStyle(el,'').getPropertyValue(converted);}}
return value;};this.setStyle=function(el,property,val){el=this.get(el);switch(property){case'opacity':if(el.filters){el.style.filter='alpha(opacity='+val*100+')';if(!el.currentStyle.hasLayout){el.style.zoom=1;}}else{el.style.opacity=val;el.style['-moz-opacity']=val;el.style['-khtml-opacity']=val;}
break;default:el.style[property]=val;}};this.getXY=function(el){el=this.get(el);if(el.parentNode===null||this.getStyle(el,'display')=='none'){return false;}
var parent=null;var pos=[];var box;if(el.getBoundingClientRect){box=el.getBoundingClientRect();var scrollTop=document.documentElement.scrollTop||document.body.scrollTop;var scrollLeft=document.documentElement.scrollLeft||document.body.scrollLeft;return[box.left+scrollLeft,box.top+scrollTop];}
else if(document.getBoxObjectFor){box=document.getBoxObjectFor(el);pos=[box.x,box.y];}
else{pos=[el.offsetLeft,el.offsetTop];parent=el.offsetParent;if(parent!=el){while(parent){pos[0]+=parent.offsetLeft;pos[1]+=parent.offsetTop;parent=parent.offsetParent;}}
var ua=navigator.userAgent.toLowerCase();if(ua.indexOf('opera')!=-1||(ua.indexOf('safari')!=-1&&this.getStyle(el,'position')=='absolute')){pos[1]-=document.body.offsetTop;}}
if(el.parentNode){parent=el.parentNode;}
else{parent=null;}
while(parent&&parent.tagName!='BODY'&&parent.tagName!='HTML'){pos[0]-=parent.scrollLeft;pos[1]-=parent.scrollTop;if(parent.parentNode){parent=parent.parentNode;}
else{parent=null;}}
return pos;};this.getX=function(el){return this.getXY(el)[0];};this.getY=function(el){return this.getXY(el)[1];};this.setXY=function(el,pos,noRetry){el=this.get(el);var pageXY=YAHOO.util.Dom.getXY(el);if(pageXY===false){return false;}
var delta=[parseInt(YAHOO.util.Dom.getStyle(el,'left'),10),parseInt(YAHOO.util.Dom.getStyle(el,'top'),10)];if(isNaN(delta[0])){delta[0]=0;}
if(isNaN(delta[1])){delta[1]=0;}
if(pos[0]!==null){el.style.left=pos[0]-pageXY[0]+delta[0]+'px';}
if(pos[1]!==null){el.style.top=pos[1]-pageXY[1]+delta[1]+'px';}
var newXY=this.getXY(el);if(!noRetry&&(newXY[0]!=pos[0]||newXY[1]!=pos[1])){this.setXY(el,pos,true);}
return true;};this.setX=function(el,x){return this.setXY(el,[x,null]);};this.setY=function(el,y){return this.setXY(el,[null,y]);};this.getRegion=function(el){el=this.get(el);return new YAHOO.util.Region.getRegion(el);};this.getClientWidth=function(){return(document.documentElement.offsetWidth||document.body.offsetWidth);};this.getClientHeight=function(){return(self.innerHeight||document.documentElement.clientHeight||document.body.clientHeight);};};YAHOO.util.Region=function(t,r,b,l){this.top=t;this.right=r;this.bottom=b;this.left=l;};YAHOO.util.Region.prototype.contains=function(region){return(region.left>=this.left&&region.right<=this.right&&region.top>=this.top&&region.bottom<=this.bottom);};YAHOO.util.Region.prototype.getArea=function(){return((this.bottom-this.top)*(this.right-this.left));};YAHOO.util.Region.prototype.intersect=function(region){var t=Math.max(this.top,region.top);var r=Math.min(this.right,region.right);var b=Math.min(this.bottom,region.bottom);var l=Math.max(this.left,region.left);if(b>=t&&r>=l){return new YAHOO.util.Region(t,r,b,l);}else{return null;}};YAHOO.util.Region.prototype.union=function(region){var t=Math.min(this.top,region.top);var r=Math.max(this.right,region.right);var b=Math.max(this.bottom,region.bottom);var l=Math.min(this.left,region.left);return new YAHOO.util.Region(t,r,b,l);};YAHOO.util.Region.prototype.toString=function(){return("Region {"+"  t: "+this.top+", r: "+this.right+", b: "+this.bottom+", l: "+this.left+"}");}
YAHOO.util.Region.getRegion=function(el){var p=YAHOO.util.Dom.getXY(el);var t=p[1];var r=p[0]+el.offsetWidth;var b=p[1]+el.offsetHeight;var l=p[0];return new YAHOO.util.Region(t,r,b,l);};YAHOO.util.Point=function(x,y){this.x=x;this.y=y;this.top=y;this.right=x;this.bottom=y;this.left=x;};YAHOO.util.Point.prototype=new YAHOO.util.Region();

// dragdrop.js
/* Copyright (c) 2006 Yahoo! Inc. All rights reserved. */YAHOO.util.DragDrop=function(id,_2){if(id){this.init(id,_2);}};YAHOO.util.DragDrop.prototype={id:null,dragElId:null,handleElId:null,invalidHandleTypes:null,startPageX:0,startPageY:0,groups:null,locked:false,lock:function(){this.locked=true;},unlock:function(){this.locked=false;},isTarget:true,padding:null,_domRef:null,__ygDragDrop:true,constrainX:false,constrainY:false,minX:0,maxX:0,minY:0,maxY:0,maintainOffset:false,xTicks:null,yTicks:null,primaryButtonOnly:true,b4StartDrag:function(x,y){},startDrag:function(x,y){},b4Drag:function(e){},onDrag:function(e){},onDragEnter:function(e,id){},b4DragOver:function(e){},onDragOver:function(e,id){},b4DragOut:function(e){},onDragOut:function(e,id){},b4DragDrop:function(e){},onDragDrop:function(e,id){},b4EndDrag:function(e){},endDrag:function(e){},b4MouseDown:function(e){},onMouseDown:function(e){},onMouseUp:function(e){},getEl:function(){if(!this._domRef){this._domRef=this.DDM.getElement(this.id);}return this._domRef;},getDragEl:function(){return this.DDM.getElement(this.dragElId);},init:function(id,_6){this.initTarget(id,_6);YAHOO.util.Event.addListener(id,"mousedown",this.handleMouseDown,this,true);},initTarget:function(id,_7){this.DDM=YAHOO.util.DDM;this.padding=[0,0,0,0];this.groups={};this.id=id;this.setDragElId(id);this.invalidHandleTypes={a:"a"};this.handleElId=id;if(document&&document.body){this.setInitPosition();}this.addToGroup((_7)?_7:"default");},setPadding:function(_8,_9,_10,_11){if(!_9&&0!==_9){this.padding=[_8,_8,_8,_8];}else{if(!_10&&0!==_10){this.padding=[_8,_9,_8,_9];}else{this.padding=[_8,_9,_10,_11];}}},setInitPosition:function(_12,_13){var el=this.getEl();if(!this.DDM.verifyEl(el)){return;}var dx=_12||0;var dy=_13||0;var p=YAHOO.util.Dom.getXY(el);this.initPageX=p[0]-dx;this.initPageY=p[1]-dy;this.lastPageX=p[0];this.lastPageY=p[1];this.setStartPosition(p);},setStartPosition:function(pos){var p=pos||YAHOO.util.Dom.getXY(this.getEl());this.startPageX=p[0];this.startPageY=p[1];},addToGroup:function(_19){this.groups[_19]=true;this.DDM.regDragDrop(this,_19);},setDragElId:function(id){this.dragElId=id;},setHandleElId:function(id){this.handleElId=id;this.DDM.regHandle(this.id,id);},setOuterHandleElId:function(id){YAHOO.util.Event.addListener(id,"mousedown",this.handleMouseDown,this,true);this.setHandleElId(id);},unreg:function(){YAHOO.util.Event.removeListener(this.id,"mousedown",this.handleMouseDown);this._domRef=null;this.DDM._remove(this);},isLocked:function(){return (this.DDM.isLocked()||this.locked);},handleMouseDown:function(e,oDD){var EU=YAHOO.util.Event;var _22=e.which||e.button;if(this.primaryButtonOnly&&_22>1){return;}if(this.isLocked()){return;}this.DDM.refreshCache(this.groups);var pt=new YAHOO.util.Point(EU.getPageX(e),EU.getPageY(e));if(this.DDM.isOverTarget(pt,this)){var _24=EU.getTarget(e);if(this.isValidHandleChild(_24)&&(this.id==this.handleElId||this.DDM.handleWasClicked(_24,this.id))){this.setStartPosition();this.b4MouseDown(e);this.onMouseDown(e);this.DDM.handleMouseDown(e,this);this.DDM.stopEvent(e);}}},addInvalidHandleType:function(_25){var _26=_25.toUpperCase();this.invalidHandleTypes[_26]=_26;},removeInvalidHandleType:function(_27){var _28=_27.toUpperCase();this.invalidHandleTypes[_28]=null;},isValidHandleChild:function(_29){var _30=_29.nodeName;if(_30=="#text"){_30=_29.parentNode.nodeName;}return (!this.invalidHandleTypes[_30]);},setXTicks:function(_31,_32){this.xTicks=[];this.xTickSize=_32;var _33={};for(var i=this.initPageX;i>=this.minX;i=i-_32){if(!_33[i]){this.xTicks[this.xTicks.length]=i;_33[i]=true;}}for(i=this.initPageX;i<=this.maxX;i=i+_32){if(!_33[i]){this.xTicks[this.xTicks.length]=i;_33[i]=true;}}this.xTicks.sort(this.DDM.numericSort);},setYTicks:function(_35,_36){this.yTicks=[];this.yTickSize=_36;var _37={};for(var i=this.initPageY;i>=this.minY;i=i-_36){if(!_37[i]){this.yTicks[this.yTicks.length]=i;_37[i]=true;}}for(i=this.initPageY;i<=this.maxY;i=i+_36){if(!_37[i]){this.yTicks[this.yTicks.length]=i;_37[i]=true;}}this.yTicks.sort(this.DDM.numericSort);},setXConstraint:function(_38,_39,_40){this.leftConstraint=_38;this.rightConstraint=_39;this.minX=this.initPageX-_38;this.maxX=this.initPageX+_39;if(_40){this.setXTicks(this.initPageX,_40);}this.constrainX=true;},setYConstraint:function(iUp,_42,_43){this.topConstraint=iUp;this.bottomConstraint=_42;this.minY=this.initPageY-iUp;this.maxY=this.initPageY+_42;if(_43){this.setYTicks(this.initPageY,_43);}this.constrainY=true;},resetConstraints:function(){var dx=(this.maintainOffset)?this.lastPageX-this.initPageX:0;var dy=(this.maintainOffset)?this.lastPageY-this.initPageY:0;this.setInitPosition(dx,dy);if(this.constrainX){this.setXConstraint(this.leftConstraint,this.rightConstraint,this.xTickSize);}if(this.constrainY){this.setYConstraint(this.topConstraint,this.bottomConstraint,this.yTickSize);}},getTick:function(val,_45){if(!_45){return val;}else{if(_45[0]>=val){return _45[0];}else{for(var i=0;i<_45.length;++i){var _46=i+1;if(_45[_46]&&_45[_46]>=val){var _47=val-_45[i];var _48=_45[_46]-val;return (_48>_47)?_45[i]:_45[_46];}}return _45[_45.length-1];}}},toString:function(val,_49){return ("YAHOO.util.DragDrop {"+this.id+"}");}};if(!YAHOO.util.DragDropMgr){YAHOO.util.DragDropMgr=new function(){var _50=YAHOO.util;this.ids={};this.handleIds={};this.dragCurrent=null;this.dragOvers={};this.deltaX=0;this.deltaY=0;this.preventDefault=true;this.stopPropagation=true;this.initalized=false;this.locked=false;this.init=function(){};this.POINT=0;this.INTERSECT=1;this.mode=this.POINT;this._execOnAll=function(_51,_52){for(var i in this.ids){for(var j in this.ids[i]){var oDD=this.ids[i][j];if(!this.isTypeOfDD(oDD)){continue;}oDD[_51].apply(oDD,_52);}}};this._onLoad=function(){this._execOnAll("setInitPosition",[]);var EU=_50.Event;EU.addListener(document,"mouseup",this.handleMouseUp,this,true);EU.addListener(document,"mousemove",this.handleMouseMove,this,true);EU.addListener(window,"unload",this._onUnload,this,true);EU.addListener(window,"resize",this._onResize,this,true);this.initalized=true;};this._onResize=function(e){this._execOnAll("resetConstraints",[]);};this.lock=function(){this.locked=true;};this.unlock=function(){this.locked=false;};this.isLocked=function(){return this.locked;};this.locationCache={};this.useCache=true;this.clickPixelThresh=3;this.clickTimeThresh=1000;this.dragThreshMet=false;this.clickTimeout=null;this.startX=0;this.startY=0;this.regDragDrop=function(oDD,_54){if(!this.initialized){this.init();}if(!this.ids[_54]){this.ids[_54]={};}this.ids[_54][oDD.id]=oDD;};this._remove=function(oDD){for(var g in oDD.groups){if(g&&this.ids[g][oDD.id]){delete this.ids[g][oDD.id];}}delete this.handleIds[oDD.id];};this.regHandle=function(_56,_57){if(!this.handleIds[_56]){this.handleIds[_56]={};}this.handleIds[_56][_57]=_57;};this.isDragDrop=function(id){return (this.getDDById(id))?true:false;};this.getRelated=function(_58,_59){var _60=[];for(var i in _58.groups){for(j in this.ids[i]){var dd=this.ids[i][j];if(!this.isTypeOfDD(dd)){continue;}if(!_59||dd.isTarget){_60[_60.length]=dd;}}}return _60;};this.isLegalTarget=function(oDD,_62){var _63=this.getRelated(oDD);for(var i=0;i<_63.length;++i){if(_63[i].id==_62.id){return true;}}return false;};this.isTypeOfDD=function(oDD){return (oDD&&oDD.__ygDragDrop);};this.isHandle=function(_64,_65){return (this.handleIds[_64]&&this.handleIds[_64][_65]);};this.getDDById=function(id){for(var i in this.ids){if(this.ids[i][id]){return this.ids[i][id];}}return null;};this.handleMouseDown=function(e,oDD){this.dragCurrent=oDD;var el=oDD.getEl();this.startX=_50.Event.getPageX(e);this.startY=_50.Event.getPageY(e);this.deltaX=this.startX-el.offsetLeft;this.deltaY=this.startY-el.offsetTop;this.dragThreshMet=false;this.clickTimeout=setTimeout("var DDM=YAHOO.util.DDM;DDM.startDrag(DDM.startX, DDM.startY)",this.clickTimeThresh);};this.startDrag=function(x,y){clearTimeout(this.clickTimeout);if(this.dragCurrent){this.dragCurrent.b4StartDrag(x,y);this.dragCurrent.startDrag(x,y);}this.dragThreshMet=true;};this.handleMouseUp=function(e){if(!this.dragCurrent){return;}clearTimeout(this.clickTimeout);if(this.dragThreshMet){this.fireEvents(e,true);}else{}this.stopDrag(e);this.stopEvent(e);};this.stopEvent=function(e){if(this.stopPropagation){_50.Event.stopPropagation(e);}if(this.preventDefault){_50.Event.preventDefault(e);}};this.stopDrag=function(e){if(this.dragCurrent){if(this.dragThreshMet){this.dragCurrent.b4EndDrag(e);this.dragCurrent.endDrag(e);}this.dragCurrent.onMouseUp(e);}this.dragCurrent=null;this.dragOvers={};};this.handleMouseMove=function(e){if(!this.dragCurrent){return;}if(_50.Event.isIE&&!e.button){this.stopEvent(e);return this.handleMouseUp(e);}if(!this.dragThreshMet){var _66=Math.abs(this.startX-_50.Event.getPageX(e));var _67=Math.abs(this.startY-_50.Event.getPageY(e));if(_66>this.clickPixelThresh||_67>this.clickPixelThresh){this.startDrag(this.startX,this.startY);}}if(this.dragThreshMet){this.dragCurrent.b4Drag(e);this.dragCurrent.onDrag(e);this.fireEvents(e,false);}this.stopEvent(e);};this.fireEvents=function(e,_68){var dc=this.dragCurrent;if(!dc||dc.isLocked()){return;}var x=_50.Event.getPageX(e);var y=_50.Event.getPageY(e);var pt=new YAHOO.util.Point(x,y);var _70=[];var _71=[];var _72=[];var _73=[];var _74=[];for(var i in this.dragOvers){var ddo=this.dragOvers[i];if(!this.isTypeOfDD(ddo)){continue;}if(!this.isOverTarget(pt,ddo,this.mode)){_71.push(ddo);}_70[i]=true;delete this.dragOvers[i];}for(var _76 in dc.groups){if("string"!=typeof _76){continue;}for(i in this.ids[_76]){var oDD=this.ids[_76][i];if(!this.isTypeOfDD(oDD)){continue;}if(oDD.isTarget&&!oDD.isLocked()&&oDD!=dc){if(this.isOverTarget(pt,oDD,this.mode)){if(_68){_73.push(oDD);}else{if(!_70[oDD.id]){_74.push(oDD);}else{_72.push(oDD);}this.dragOvers[oDD.id]=oDD;}}}}}if(this.mode){if(_71.length>0){dc.b4DragOut(e,_71);dc.onDragOut(e,_71);}if(_74.length>0){dc.onDragEnter(e,_74);}if(_72.length>0){dc.b4DragOver(e,_72);dc.onDragOver(e,_72);}if(_73.length>0){dc.b4DragDrop(e,_73);dc.onDragDrop(e,_73);}}else{for(i=0;i<_71.length;++i){dc.b4DragOut(e,_71[i].id);dc.onDragOut(e,_71[i].id);}for(i=0;i<_74.length;++i){dc.onDragEnter(e,_74[i].id);}for(i=0;i<_72.length;++i){dc.b4DragOver(e,_72[i].id);dc.onDragOver(e,_72[i].id);}for(i=0;i<_73.length;++i){dc.b4DragDrop(e,_73[i].id);dc.onDragDrop(e,_73[i].id);}}};this.getBestMatch=function(dds){var _78=null;if(dds.length==1){_78=dds[0];}else{for(var i=0;i<dds.length;++i){var dd=dds[i];if(dd.cursorIsOver){_78=dd;break;}else{if(!_78||_78.overlap.getArea()<dd.overlap.getArea()){_78=dd;}}}}return _78;};this.refreshCache=function(_79){for(sGroup in _79){if("string"!=typeof sGroup){continue;}for(i in this.ids[sGroup]){var oDD=this.ids[sGroup][i];if(this.isTypeOfDD(oDD)){var loc=this.getLocation(oDD);if(loc){this.locationCache[oDD.id]=loc;}else{delete this.locationCache[oDD.id];oDD.unreg();}}}}};this.verifyEl=function(el){try{if(el){var _81=el.offsetParent;if(_81){return true;}}}catch(e){}return false;};this.getLocation=function(oDD){if(!this.isTypeOfDD(oDD)){return null;}var el=oDD.getEl();if(!this.verifyEl(el)){return null;}var _82=YAHOO.util.Dom.getXY(el);x1=_82[0];x2=x1+el.offsetWidth;y1=_82[1];y2=y1+el.offsetHeight;var t=y1-oDD.padding[0];var r=x2+oDD.padding[1];var b=y2+oDD.padding[2];var l=x1-oDD.padding[3];return new YAHOO.util.Region(t,r,b,l);};this.isOverTarget=function(pt,_87,_88){var loc=this.locationCache[_87.id];if(!loc||!this.useCache){loc=this.getLocation(_87);this.locationCache[_87.id]=loc;}_87.cursorIsOver=loc.contains(pt);_87.overlap=null;if(_88){var _89=YAHOO.util.Region.getRegion(this.dragCurrent.getDragEl());var _90=_89.intersect(loc);if(_90){_87.overlap=_90;return true;}else{return false;}}else{return _87.cursorIsOver;}};this._onUnload=function(e,me){this.unregAll();};this.unregAll=function(){if(this.dragCurrent){this.stopDrag();this.dragCurrent=null;}this._execOnAll("unreg",[]);for(i in this.elementCache){delete this.elementCache[i];}this.elementCache={};this.ids={};};this.elementCache={};this.getElWrapper=function(id){var _92=this.elementCache[id];if(!_92||!_92.el){_92=this.elementCache[id]=new this.ElementWrapper(document.getElementById(id));}return _92;};this.getElement=function(id){return document.getElementById(id);};this.getCss=function(id){var css=null;var el=document.getElementById(id);if(el){css=el.style;}return css;};this.ElementWrapper=function(el){this.el=el||null;this.id=this.el&&el.id;this.css=this.el&&el.style;};this.getPosX=function(el){return YAHOO.util.Dom.getX(el);};this.getPosY=function(el){return YAHOO.util.Dom.getY(el);};this.swapNode=function(n1,n2){if(n1.swapNode){n1.swapNode(n2);}else{var p=n2.parentNode;var s=n2.nextSibling;n1.parentNode.replaceChild(n2,n1);p.insertBefore(n1,s);}};this.getScroll=function(){var t,l;if(document.documentElement&&document.documentElement.scrollTop){t=document.documentElement.scrollTop;l=document.documentElement.scrollLeft;}else{if(document.body){t=document.body.scrollTop;l=document.body.scrollLeft;}}return {top:t,left:l};};this.getStyle=function(el,_97){if(el.style.styleProp){return el.style.styleProp;}else{if(el.currentStyle){return el.currentStyle[_97];}else{if(document.defaultView){return document.defaultView.getComputedStyle(el,null).getPropertyValue(_97);}}}};this.getScrollTop=function(){return this.getScroll().top;};this.getScrollLeft=function(){return this.getScroll().left;};this.moveToEl=function(_98,_99){var _100=YAHOO.util.Dom.getXY(_99);YAHOO.util.Dom.setXY(_98,_100);};this.getClientHeight=function(){return (window.innerHeight)?window.innerHeight:(document.documentElement&&document.documentElement.clientHeight)?document.documentElement.clientHeight:document.body.offsetHeight;};this.getClientWidth=function(){return (window.innerWidth)?window.innerWidth:(document.documentElement&&document.documentElement.clientWidth)?document.documentElement.clientWidth:document.body.offsetWidth;};this.numericSort=function(a,b){return (a-b);};this._timeoutCount=0;this._addListeners=function(){if(_50.Event&&document&&document.body){this._onLoad();}else{if(this._timeoutCount>500){}else{setTimeout("YAHOO.util.DDM._addListeners()",10);this._timeoutCount+=1;}}};this.handleWasClicked=function(node,id){if(this.isHandle(id,node.id)){return true;}else{var p=node.parentNode;while(p){if(this.isHandle(id,p.id)){return true;}else{p=p.parentNode;}}}return false;};};YAHOO.util.DDM=YAHOO.util.DragDropMgr;YAHOO.util.DDM._addListeners();}YAHOO.util.DD=function(id,_103){if(id){this.init(id,_103);}};YAHOO.util.DD.prototype=new YAHOO.util.DragDrop();YAHOO.util.DD.prototype.scroll=true;YAHOO.util.DD.prototype.autoOffset=function(_104,_105){var el=this.getEl();var _106=YAHOO.util.Dom.getXY(el);var x=_104-_106[0];var y=_105-_106[1];this.setDelta(x,y);};YAHOO.util.DD.prototype.setDelta=function(_107,_108){this.deltaX=_107;this.deltaY=_108;};YAHOO.util.DD.prototype.setDragElPos=function(_109,_110){var el=this.getDragEl();this.alignElWithMouse(el,_109,_110);};YAHOO.util.DD.prototype.alignElWithMouse=function(el,_111,_112){var _113=this.getTargetCoord(_111,_112);var _114=[_113.x,_113.y];YAHOO.util.Dom.setXY(el,_114);this.cachePosition(_113.x,_113.y);this.autoScroll(_113.x,_113.y,el.offsetHeight,el.offsetWidth);};YAHOO.util.DD.prototype.cachePosition=function(_115,_116){if(_115){this.lastPageX=_115;this.lastPageY=_116;}else{var _117=YAHOO.util.Dom.getXY(this.getEl());this.lastPageX=_117[0];this.lastPageY=_117[1];}};YAHOO.util.DD.prototype.autoScroll=function(x,y,h,w){if(this.scroll){var _120=this.DDM.getClientHeight();var _121=this.DDM.getClientWidth();var st=this.DDM.getScrollTop();var sl=this.DDM.getScrollLeft();var bot=h+y;var _125=w+x;var _126=(_120+st-y-this.deltaY);var _127=(_121+sl-x-this.deltaX);var _128=40;var _129=(document.all)?80:30;if(bot>_120&&_126<_128){window.scrollTo(sl,st+_129);}if(y<st&&st>0&&y-st<_128){window.scrollTo(sl,st-_129);}if(_125>_121&&_127<_128){window.scrollTo(sl+_129,st);}if(x<sl&&sl>0&&x-sl<_128){window.scrollTo(sl-_129,st);}}};YAHOO.util.DD.prototype.getTargetCoord=function(_130,_131){var x=_130-this.deltaX;var y=_131-this.deltaY;if(this.constrainX){if(x<this.minX){x=this.minX;}if(x>this.maxX){x=this.maxX;}}if(this.constrainY){if(y<this.minY){y=this.minY;}if(y>this.maxY){y=this.maxY;}}x=this.getTick(x,this.xTicks);y=this.getTick(y,this.yTicks);return {x:x,y:y};};YAHOO.util.DD.prototype.b4MouseDown=function(e){this.autoOffset(YAHOO.util.Event.getPageX(e),YAHOO.util.Event.getPageY(e));};YAHOO.util.DD.prototype.b4Drag=function(e){this.setDragElPos(YAHOO.util.Event.getPageX(e),YAHOO.util.Event.getPageY(e));};YAHOO.util.DDProxy=function(id,_132){if(id){this.forceCssPosition=false;this.init(id,_132);this.initFrame();}};YAHOO.util.DDProxy.prototype=new YAHOO.util.DD();YAHOO.util.DDProxy.frameDiv=null;YAHOO.util.DDProxy.dragElId="ygddfdiv";YAHOO.util.DDProxy.prototype.borderWidth=2;YAHOO.util.DDProxy.prototype.resizeFrame=true;YAHOO.util.DDProxy.prototype.centerFrame=false;YAHOO.util.DDProxy.createFrame=function(){var THIS=YAHOO.util.DDProxy;if(!document||!document.body){setTimeout(THIS.createFrame,50);return;}if(!THIS.frameDiv){THIS.frameDiv=document.createElement("div");THIS.frameDiv.id=THIS.dragElId;var s=THIS.frameDiv.style;s.position="absolute";s.visibility="hidden";s.cursor="move";s.border="2px solid #aaa";s.zIndex=999;document.body.appendChild(THIS.frameDiv);}};YAHOO.util.DDProxy.prototype.initFrame=function(){YAHOO.util.DDProxy.createFrame();this.setDragElId(YAHOO.util.DDProxy.dragElId);this.useAbsMath=true;};YAHOO.util.DDProxy.prototype.showFrame=function(_134,_135){var el=this.getEl();var s=this.getDragEl().style;if(this.resizeFrame){s.width=(parseInt(el.offsetWidth)-(2*this.borderWidth))+"px";s.height=(parseInt(el.offsetHeight)-(2*this.borderWidth))+"px";}if(this.centerFrame){this.setDelta(Math.round(parseInt(s.width)/2),Math.round(parseInt(s.width)/2));}this.setDragElPos(_134,_135);s.visibility="";};YAHOO.util.DDProxy.prototype.b4MouseDown=function(e){var x=YAHOO.util.Event.getPageX(e);var y=YAHOO.util.Event.getPageY(e);this.autoOffset(x,y);this.setDragElPos(x,y);};YAHOO.util.DDProxy.prototype.b4StartDrag=function(x,y){this.showFrame(x,y);};YAHOO.util.DDProxy.prototype.b4EndDrag=function(e){var s=this.getDragEl().style;s.visibility="hidden";};YAHOO.util.DDProxy.prototype.endDrag=function(e){var lel=this.getEl();var del=this.getDragEl();del.style.visibility="";lel.style.visibility="hidden";YAHOO.util.DDM.moveToEl(lel,del);del.style.visibility="hidden";lel.style.visibility="";};YAHOO.util.DDTarget=function(id,_138){if(id){this.initTarget(id,_138);}};YAHOO.util.DDTarget.prototype=new YAHOO.util.DragDrop();

// event.js

/* Copyright (c) 2006 Yahoo! Inc. All rights reserved. */YAHOO.util.CustomEvent=function(_1,_2){this.type=_1;this.scope=_2||window;this.subscribers=[];if(YAHOO.util["Event"]){YAHOO.util.Event.regCE(this);}};YAHOO.util.CustomEvent.prototype={subscribe:function(fn,_4,_5){this.subscribers.push(new YAHOO.util.Subscriber(fn,_4,_5));},unsubscribe:function(fn,_6){var _7=false;for(var i=0;i<this.subscribers.length;++i){var s=this.subscribers[i];if(s&&s.contains(fn,_6)){this._delete(i);_7=true;}}return _7;},fire:function(){for(var i=0;i<this.subscribers.length;++i){var s=this.subscribers[i];if(s){var _10=(s.override)?s.obj:this.scope;s.fn.call(_10,this.type,arguments,s.obj);}}},unsubscribeAll:function(){for(var i=0;i<this.subscribers.length;++i){this._delete(i);}},_delete:function(_11){var s=this.subscribers[_11];if(s){delete s.fn;delete s.obj;}delete this.subscribers[_11];}};YAHOO.util.Subscriber=function(fn,obj,_13){this.fn=fn;this.obj=obj||null;this.override=(_13);};YAHOO.util.Subscriber.prototype.contains=function(fn,obj){return (this.fn==fn&&this.obj==obj);};if(!YAHOO.util.Event){YAHOO.util.Event=function(){var _14=false;var _15=[];var _16=[];var _17=[];var _18=[];var _19=[];var _20=[];return {EL:0,TYPE:1,FN:2,WFN:3,SCOPE:3,ADJ_SCOPE:4,isSafari:(navigator.userAgent.match(/safari/gi)),isIE:(!this.isSafari&&navigator.userAgent.match(/msie/gi)),addListener:function(el,_22,fn,_23,_24){if(this._isValidCollection(el)){var ok=true;for(var i=0;i<el.length;++i){ok=(this.on(el[i],_22,fn,_23,_24)&&ok);}return ok;}else{if(typeof el=="string"){if(_14){el=this.getEl(el);}else{_16[_16.length]=[el,_22,fn,_23,_24];return true;}}}if(!el){return false;}if("unload"==_22&&_23!==this){_17[_17.length]=[el,_22,fn,_23,_24];return true;}var _26=(_24)?_23:el;var _27=function(e){return fn.call(_26,YAHOO.util.Event.getEvent(e),_23);};var li=[el,_22,fn,_27,_26];var _30=_15.length;_15[_30]=li;if(this.useLegacyEvent(el,_22)){var _31=this.getLegacyIndex(el,_22);if(_31==-1){_31=_19.length;_19[_31]=[el,_22,el["on"+_22]];_20[_31]=[];el["on"+_22]=function(e){YAHOO.util.Event.fireLegacyEvent(YAHOO.util.Event.getEvent(e),_31);};}_20[_31].push(_30);}else{if(el.addEventListener){el.addEventListener(_22,_27,false);}else{if(el.attachEvent){el.attachEvent("on"+_22,_27);}}}return true;},fireLegacyEvent:function(e,_32){var ok=true;var le=_20[_32];for(i=0;i<le.length;++i){var _34=le[i];if(_34){var li=_15[_34];var _35=li[this.ADJ_SCOPE];var ret=li[this.WFN].call(_35,e);ok=(ok&&ret);}}return ok;},getLegacyIndex:function(el,_37){for(var i=0;i<_19.length;++i){var le=_19[i];if(le&&le[0]==el&&le[1]==_37){return i;}}return -1;},useLegacyEvent:function(el,_38){return ((!el.addEventListener&&!el.attachEvent)||(_38=="click"&&this.isSafari));},removeListener:function(el,_39,fn){if(typeof el=="string"){el=this.getEl(el);}else{if(this._isValidCollection(el)){var ok=true;for(var i=0;i<el.length;++i){ok=(this.removeListener(el[i],_39,fn)&&ok);}return ok;}}var _40=null;var _41=this._getCacheIndex(el,_39,fn);if(_41>=0){_40=_15[_41];}if(!el||!_40){return false;}if(el.removeEventListener){el.removeEventListener(_39,_40[this.WFN],false);}else{if(el.detachEvent){el.detachEvent("on"+_39,_40[this.WFN]);}}delete _15[_41][this.WFN];delete _15[_41][this.FN];delete _15[_41];return true;},getTarget:function(ev,_43){var t=ev.target||ev.srcElement;if(_43&&t&&"#text"==t.nodeName){return t.parentNode;}else{return t;}},getPageX:function(ev){var x=ev.pageX;if(!x&&0!==x){x=ev.clientX||0;if(this.isIE){x+=this._getScrollLeft();}}return x;},getPageY:function(ev){var y=ev.pageY;if(!y&&0!==y){y=ev.clientY||0;if(this.isIE){y+=this._getScrollTop();}}return y;},getRelatedTarget:function(ev){var t=ev.relatedTarget;if(!t){if(ev.type=="mouseout"){t=ev.toElement;}else{if(ev.type=="mouseover"){t=ev.fromElement;}}}return t;},getTime:function(ev){if(!ev.time){var t=new Date().getTime();try{ev.time=t;}catch(e){return t;}}return ev.time;},stopEvent:function(ev){this.stopPropagation(ev);this.preventDefault(ev);},stopPropagation:function(ev){if(ev.stopPropagation){ev.stopPropagation();}else{ev.cancelBubble=true;}},preventDefault:function(ev){if(ev.preventDefault){ev.preventDefault();}else{ev.returnValue=false;}},getEvent:function(e){var ev=e||window.event;if(!ev){var c=this.getEvent.caller;while(c){ev=c.arguments[0];if(ev&&Event==ev.constructor){break;}c=c.caller;}}return ev;},getCharCode:function(ev){return ev.charCode||(ev.type=="keypress")?ev.keyCode:0;},_getCacheIndex:function(el,_48,fn){for(var i=0;i<_15.length;++i){var li=_15[i];if(li&&li[this.FN]==fn&&li[this.EL]==el&&li[this.TYPE]==_48){return i;}}return -1;},_isValidCollection:function(o){return (o&&o.length&&typeof o!="string"&&!o.tagName&&!o.alert&&typeof o[0]!="undefined");},elCache:{},getEl:function(id){return document.getElementById(id);},clearCache:function(){for(i in this.elCache){delete this.elCache[i];}},regCE:function(ce){_18.push(ce);},_load:function(e){_14=true;},_tryPreloadAttach:function(){var _52=!_14;for(var i=0;i<_16.length;++i){var d=_16[i];if(d){var el=this.getEl(d[this.EL]);if(el){this.on(el,d[this.TYPE],d[this.FN],d[this.SCOPE],d[this.ADJ_SCOPE]);delete _16[i];}}}if(_52){setTimeout("YAHOO.util.Event._tryPreloadAttach()",50);}},_unload:function(e,me){for(var i=0;i<_17.length;++i){var l=_17[i];if(l){var _56=(l[this.ADJ_SCOPE])?l[this.SCOPE]:window;l[this.FN].call(_56,this.getEvent(e),l[this.SCOPE]);}}if(_15&&_15.length>0){for(i=0;i<_15.length;++i){l=_15[i];if(l){this.removeListener(l[this.EL],l[this.TYPE],l[this.FN]);}}this.clearCache();}for(i=0;i<_18.length;++i){_18[i].unsubscribeAll();delete _18[i];}for(i=0;i<_19.length;++i){delete _19[i][0];delete _19[i];}},_getScrollLeft:function(){return this._getScroll()[1];},_getScrollTop:function(){return this._getScroll()[0];},_getScroll:function(){var dd=document.documentElement;db=document.body;if(dd&&dd.scrollTop){return [dd.scrollTop,dd.scrollLeft];}else{if(db){return [db.scrollTop,db.scrollLeft];}else{return [0,0];}}}};}();YAHOO.util.Event.on=YAHOO.util.Event.addListener;if(document&&document.body){YAHOO.util.Event._load();}else{YAHOO.util.Event.on(window,"load",YAHOO.util.Event._load,YAHOO.util.Event,true);}YAHOO.util.Event.on(window,"unload",YAHOO.util.Event._unload,YAHOO.util.Event,true);YAHOO.util.Event._tryPreloadAttach();}

// slider.js
/* Copyright (c) 2006 Yahoo! Inc. All rights reserved. */YAHOO.widget.Slider=function(_1,_2,_3){if(_1){this.init(_1,_2,true);var _4=this;this.thumb=_3;_3.onChange=function(){_4.onThumbChange();};var el=_3.getEl();this.thumbCenterPoint={x:el.offsetWidth/2,y:el.offsetHeight/2};this.isTarget=false;this.animate=YAHOO.widget.Slider.ANIM_AVAIL;this.baselinePos=YAHOO.util.Dom.getXY(this.getEl());this.tickPause=40;if(_3._isHoriz&&_3.xTicks){this.tickPause=Math.round(360/_3.xTicks.length);}else{if(_3.yTicks){this.tickPause=Math.round(360/_3.yTicks.length);}}_3.onMouseDown=function(){return _4.focus();};_3.b4MouseDown=function(){return _4.b4MouseDown();};_3.onMouseUp=function(){_4.onMouseUp();};_3.onDrag=function(){_4.fireEvents();};if(_3._isRegion){this.setRegionValue(0,0);}else{this.setValue(0);}}};YAHOO.widget.Slider.prototype=new YAHOO.util.DragDrop();YAHOO.widget.Slider.getHorizSlider=function(_6,_7,_8,_9,_10){return new YAHOO.widget.Slider(_6,_6,new YAHOO.widget.SliderThumb(_7,_6,_8,_9,0,0,_10));};YAHOO.widget.Slider.getVertSlider=function(_11,_12,iUp,_14,_15){return new YAHOO.widget.Slider(_11,_11,new YAHOO.widget.SliderThumb(_12,_11,0,0,iUp,_14,_15));};YAHOO.widget.Slider.getSliderRegion=function(_16,_17,_18,_19,iUp,_20,_21){return new YAHOO.widget.Slider(_16,_16,new YAHOO.widget.SliderThumb(_17,_16,_18,_19,iUp,_20,_21));};YAHOO.widget.Slider.ANIM_AVAIL=true;YAHOO.widget.Slider.prototype.lock=function(){this.thumb.lock();this.locked=true;};YAHOO.widget.Slider.prototype.unlock=function(){this.thumb.unlock();this.locked=false;};YAHOO.widget.Slider.prototype.onMouseUp=function(){this._deferSlideEnd=true;this.fireEvents();};YAHOO.widget.Slider.prototype.focus=function(){var el=this.getEl();if(el.focus){el.focus();}this.verifyOffset();if(this.isLocked()){return false;}else{this.onSlideStart();return true;}};YAHOO.widget.Slider.prototype.onChange=function(_22,_23){};YAHOO.widget.Slider.prototype.onSlideStart=function(){};YAHOO.widget.Slider.prototype.onSlideEnd=function(){};YAHOO.widget.Slider.prototype.getValue=function(){return this.thumb.getValue();};YAHOO.widget.Slider.prototype.getXValue=function(){return this.thumb.getXValue();};YAHOO.widget.Slider.prototype.getYValue=function(){return this.thumb.getYValue();};YAHOO.widget.Slider.prototype.onThumbChange=function(){var t=this.thumb;if(t._isRegion){t.onChange(t.getXValue(),t.getYValue());}else{t.onChange(t.getValue());}};YAHOO.widget.Slider.prototype.setValue=function(_25,_26){if(this.isLocked()){return false;}if(isNaN(_25)){return false;}var t=this.thumb;var _27,newY;if(t._isRegion){return false;}else{if(t._isHoriz){_27=t.initPageX+_25+this.thumbCenterPoint.x;this.moveThumb(_27,t.initPageY,_26);}else{newY=t.initPageY+_25+this.thumbCenterPoint.y;this.moveThumb(t.initPageX,newY,_26);}}return true;};YAHOO.widget.Slider.prototype.setRegionValue=function(_28,_29,_30){if(this.isLocked()){return false;}if(isNaN(_28)){return false;}var t=this.thumb;if(t._isRegion){var _31=t.initPageX+_28+this.thumbCenterPoint.x;var _32=t.initPageY+_29+this.thumbCenterPoint.y;this.moveThumb(_31,_32,_30);return true;}return false;};YAHOO.widget.Slider.prototype.verifyOffset=function(){var _33=YAHOO.util.Dom.getXY(this.getEl());if(_33[0]!=this.baselinePos[0]||_33[1]!=this.baselinePos[1]){this.thumb.resetConstraints();this.baselinePos=_33;return false;}return true;};YAHOO.widget.Slider.prototype.moveThumb=function(x,y,_36){this.verifyOffset();var _37=this;var t=this.thumb;t.setDelta(this.thumbCenterPoint.x,this.thumbCenterPoint.y);var _p=t.getTargetCoord(x,y);var p=[_p.x,_p.y];if(this.animate&&YAHOO.widget.Slider.ANIM_AVAIL&&t._graduated&&!_36){this.lock();setTimeout(function(){_37.moveOneTick(p);},this.tickPause);}else{if(this.animate&&YAHOO.widget.Slider.ANIM_AVAIL&&!_36){this.lock();var _40=new YAHOO.util.Motion(t.id,{points:{to:p}},0.4,YAHOO.util.Easing.easeOut);_40.onComplete.subscribe(function(){_37.endAnim();});_40.animate();}else{t.setDragElPos(x,y);this.fireEvents();}}};YAHOO.widget.Slider.prototype.moveOneTick=function(_41){var t=this.thumb;var _42=YAHOO.util.Dom.getXY(t.getEl());var tmp;var _44=null;if(t._isRegion){_44=this._getNextX(_42,_41);var _45=(_44)?_44[0]:_42[0];_44=this._getNextY([_45,_42[1]],_41);}else{if(t._isHoriz){_44=this._getNextX(_42,_41);}else{_44=this._getNextY(_42,_41);}}if(_44){YAHOO.util.Dom.setXY(t.getEl(),_44);if(!(_44[0]==_41[0]&&_44[1]==_41[1])){var _46=this;setTimeout(function(){_46.moveOneTick(_41);},this.tickPause);}else{this.unlock();this.fireEvents();}}else{this.unlock();this.fireEvents();}};YAHOO.widget.Slider.prototype._getNextX=function(_47,_48){var t=this.thumb;var _49;var tmp=[];var _50=null;if(_47[0]>_48[0]){_49=t.tickSize-this.thumbCenterPoint.x;tmp=t.getTargetCoord(_47[0]-_49,_47[1]);_50=[tmp.x,tmp.y];}else{if(_47[0]<_48[0]){_49=t.tickSize+this.thumbCenterPoint.x;tmp=t.getTargetCoord(_47[0]+_49,_47[1]);_50=[tmp.x,tmp.y];}else{}}return _50;};YAHOO.widget.Slider.prototype._getNextY=function(_51,_52){var t=this.thumb;var _53;var tmp=[];var _54=null;if(_51[1]>_52[1]){_53=t.tickSize-this.thumbCenterPoint.y;tmp=t.getTargetCoord(_51[0],_51[1]-_53);_54=[tmp.x,tmp.y];}else{if(_51[1]<_52[1]){_53=t.tickSize+this.thumbCenterPoint.y;tmp=t.getTargetCoord(_51[0],_51[1]+_53);_54=[tmp.x,tmp.y];}else{}}return _54;};YAHOO.widget.Slider.prototype.b4MouseDown=function(e){this.thumb.resetConstraints();};YAHOO.widget.Slider.prototype.onMouseDown=function(e){if(!this.isLocked()){var x=YAHOO.util.Event.getPageX(e);var y=YAHOO.util.Event.getPageY(e);this.moveThumb(x,y);this.focus();}};YAHOO.widget.Slider.prototype.onDrag=function(e){if(!this.isLocked()){var x=YAHOO.util.Event.getPageX(e);var y=YAHOO.util.Event.getPageY(e);this.moveThumb(x,y,true);}};YAHOO.widget.Slider.prototype.endAnim=function(){this.unlock();this.fireEvents();};YAHOO.widget.Slider.prototype.fireEvents=function(){var t=this.thumb;t.cachePosition();if(!this.isLocked()){if(t._isRegion){var _56=t.getXValue();var _57=t.getYValue();if(_56!=this.previousX||_57!=this.previousY){this.onChange(_56,_57);}this.previousX=_56;this.previousY=_57;}else{var _58=t.getValue();if(_58!=this.previousVal){this.onChange(_58);}this.previousVal=_58;}if(this._deferSlideEnd){this.onSlideEnd();this._deferSlideEnd=false;}}};YAHOO.widget.SliderThumb=function(id,_60,_61,_62,iUp,_63,_64){if(id){this.init(id,_60);this.parentElId=_60;}this.isTarget=false;this.tickSize=_64;this.maintainOffset=true;this.initSlider(_61,_62,iUp,_63,_64);};YAHOO.widget.SliderThumb.prototype=new YAHOO.util.DD();YAHOO.widget.SliderThumb.prototype.getOffsetFromParent=function(){var _65=YAHOO.util.Dom.getXY(this.getEl());var _66=YAHOO.util.Dom.getXY(this.parentElId);return [(_65[0]-_66[0]),(_65[1]-_66[1])];};YAHOO.widget.SliderThumb.prototype.startOffset=null;YAHOO.widget.SliderThumb.prototype._isHoriz=false;YAHOO.widget.SliderThumb.prototype._prevVal=0;YAHOO.widget.SliderThumb.prototype._graduated=false;YAHOO.widget.SliderThumb.prototype.initSlider=function(_67,_68,iUp,_69,_70){this.setXConstraint(_67,_68,_70);this.setYConstraint(iUp,_69,_70);if(_70&&_70>1){this._graduated=true;}this._isHoriz=(_67>0||_68>0);this._isVert=(iUp>0||_69>0);this._isRegion=(this._isHoriz&&this._isVert);this.startOffset=this.getOffsetFromParent();};YAHOO.widget.SliderThumb.prototype.getValue=function(){var val=(this._isHoriz)?this.getXValue():this.getYValue();return val;};YAHOO.widget.SliderThumb.prototype.getXValue=function(){var _72=this.getOffsetFromParent();return (_72[0]-this.startOffset[0]);};YAHOO.widget.SliderThumb.prototype.getYValue=function(){var _73=this.getOffsetFromParent();return (_73[1]-this.startOffset[1]);};YAHOO.widget.SliderThumb.prototype.onChange=function(x,y){};if("undefined"==typeof YAHOO.util.Anim){YAHOO.widget.Slider.ANIM_AVAIL=false;}

// startcolor.js
function PritisnjenEnter(e,form){
    var key=e.keyCode || e.which;
    if (key==13)
    {
        checkcolor();
    }
}
	function checkcolor()
	{
		var newcolor=document.getElementById("startcolor").value.replace('#', '');
		
		var error = "";
		
		if (newcolor == "") {
		   error = "You didn't enter a password.\n";
		}
		
		if (newcolor.length != 6) {
		   error = "Color code shoud cointain 6 characters.\n";
		}
		
		var illegalChars= /[\(\)\<\>\,\;\:\\\/\"\[\]ghijklmnoprstuvzwxyqGHIJKLMNOPRSTUVZQWXY]/
		if (newcolor.match(illegalChars)) {
		   error = "Color code contains illegal characters.\n";
		}

		if (error=="")
		{
			dela();
		}
		else
		{
			alert(error);
			document.getElementById("startcolor").select();
		}   
	}
	
	

	function dela() {
		var newcolor=document.getElementById("startcolor").value.replace('#', '');
	
		R = HexToR(newcolor);
		G = HexToG(newcolor);
		B = HexToB(newcolor);
		
		var hsvcolor=rgbToHsv(R,G,B);
		var slider=180-(hsvcolor.h/2);
		var newx=Math.round(hsvcolor.s*1.8);
		var newy=Math.round(180-hsvcolor.v*1.8);
		
		//alert(R+','+G+','+B+':'+hsvcolor.h+','+hsvcolor.s+','+hsvcolor.v);
		//alert(newx+','+newy);
		
		try {hue.setValue(slider);} catch(E) {return;}
		picker.setRegionValue(newx,newy);

		
		document.getElementById("pickerDiv").style.backgroundColor =
			"rgb(" + R + ", " + G + ", " + B + ")";
		
		document.getElementById("pickerhval").value = Math.round(hsvcolor.h *10)/10;
		document.getElementById("pickersval").value = Math.round(hsvcolor.s *10)/10;
		document.getElementById("pickervval").value = Math.round(hsvcolor.v *10)/10;
		
		document.getElementById("pickerSwatch").style.backgroundColor =
			"rgb(" + R + ", " + G + ", " + B + ")";
		
		document.getElementById("pickerrval").value = R;
		document.getElementById("pickergval").value = G;
		document.getElementById("pickerbval").value = B;
		
		var hexvalue = document.getElementById("pickerhexval").value ='#'+
			YAHOO.util.Color.rgb2hex(R, G, B);
			ddcolorposter.initialize(R, G, B, hexvalue)
			
		//document.getElementById("vnos").value ="vneseno";
			
	}
	
	
	function HexToR(h) {return parseInt((cutHex(h)).substring(0,2),16)}
	function HexToG(h) {return parseInt((cutHex(h)).substring(2,4),16)}
	function HexToB(h) {return parseInt((cutHex(h)).substring(4,6),16)}
	function cutHex(h) {return (h.charAt(0)=="#") ? h.substring(1,7):h}
	
	function rgbToHsv(red, green, blue)
	{
		r = red / 255; g = green / 255; b = blue / 255; // Scale to unity.

		var minVal = Math.min(r, g, b);
		var maxVal = Math.max(r, g, b);
		var delta = maxVal - minVal;
		var HSVh, HSVs, HSVv;
	
		HSVv = maxVal;
	
		if (delta == 0) {
			HSVh = 0;
			HSVs = 0;
		} else {
			HSVs = delta / maxVal;
			var del_R = (((maxVal - r) / 6) + (delta / 2)) / delta;
			var del_G = (((maxVal - g) / 6) + (delta / 2)) / delta;
			var del_B = (((maxVal - b) / 6) + (delta / 2)) / delta;
	
			if (r == maxVal) {HSVh = del_B - del_G;}
			else if (g == maxVal) {HSVh = (1 / 3) + del_R - del_B;}
			else if (b == maxVal) {HSVh = (2 / 3) + del_G - del_R;}
			
			if (HSVh < 0) {HSVh += 1;}
			if (HSVh > 1) {HSVh -= 1;}
		}
		HSVh = (HSVh * 360);
		HSVs = (HSVs * 100);
		HSVv = (HSVv * 100);
		return {
			h: HSVh,
			s: HSVs,
			v: HSVv
		};
	}


