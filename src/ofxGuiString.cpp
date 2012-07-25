/**
 * ofxGuiString.cpp
 * by nariakiiwatani
 *
 * want this class to be included in ofxGui.
 */
 #include "ofxGuiString.h"

ofxGuiString::ofxGuiString(string str, float width, float height){
	setup(str,defaultWidth,height);
}

ofxGuiString* ofxGuiString::setup(string str, float width, float height){
	name = str;
	b.x = 0;
	b.y = 0;
	b.width = width;
	b.height = height;

	return this;
}

void ofxGuiString::draw(){

	ofPushStyle();
	ofPushMatrix();

	ofSetColor(backgroundColor);
	ofRect(b);

	ofTranslate(b.x, b.y);

	ofFill();
	ofSetColor(fillColor);

	ofSetColor(textColor);
	ofTranslate(0, b.height / 2 + 4);
	ofDrawBitmapString(name, textPadding, 0);

	ofPopMatrix();
	ofPopStyle();
}

