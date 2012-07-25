/**
 * ofxGuiString.h
 * by nariakiiwatani
 *
 * want this class to be included in ofxGui.
 */

#pragma once

#include "ofxBaseGui.h"

class ofxGuiString : public ofxBaseGui {
public:
	ofxGuiString(){};
	ofxGuiString(string str, float width = defaultWidth, float height = defaultHeight);
	ofxGuiString* setup(string str, float width = defaultWidth, float height = defaultHeight);
	
	virtual void mouseMoved(ofMouseEventArgs & args){}
	virtual void mousePressed(ofMouseEventArgs & args){}
	virtual void mouseDragged(ofMouseEventArgs & args){}
	virtual void mouseReleased(ofMouseEventArgs & args){}
	
	virtual void saveToXml(ofxXmlSettings& xml){}
	virtual void loadFromXml(ofxXmlSettings& xml){}

	virtual void setValue(float mx, float my, bool bCheckBounds){}
	
	void draw();
};
