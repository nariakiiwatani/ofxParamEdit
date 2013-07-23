ofxParamEdit
============
by nariakiiwatani

Abstract------------
ofxParamEdit provides the SIMPLEST interface to edit values with ofxGui.  
You can edit normal valriables (like int, float,,,) through this addon.  

Depends on...
------------
ofxGui  
ofxXmlSettings  

Caution
------------
ofxParamEdit needs ofxGui to be customized a bit.  
so I include ofxGui sources into this repository.  
Ofcource I'll update the sources when oF updated.  

Usage
------------
see example/src/testApp.cpp

For ofxGui users
------------
convert your code like below...

from:

	ofxFloatSlider f;
	f.setup("float value", 0, -1.f, 1.f);
	f.draw();

to:

	float f = 0;
	ofxParamPanel panel;
	panel.addSlider("float value", f, -1.f, 1.f);
	panel.draw();

even after the change, doSomething(f) will remain the same. :)

