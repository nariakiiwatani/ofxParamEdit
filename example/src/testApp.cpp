/******************************************************************/
/**
 * @file	testApp.cpp
 * @brief	Example for ofxParamEdit addon
 * @note
 * @todo
 * @bug		Maybe becouse of ofEvent(or Poco::delegate?) bug, mouse events are incorrect if GUIs were added to Panel.
 			So I recommend commenting out ofRegisterMouseEvents in ofxSlider.cpp, ofxButton.cpp, and ofxToggle.cpp.
 *
 * @author	nariakiiwatani
 * @date	Jul. 24, 2012
 */
/******************************************************************/
#include "testApp.h"
#include "ofxParamEdit.h"

ofxParamEdit edit_("root");
int val_si2 = 0;
char val_sc = 0;
unsigned char val_uc = 0;
short val_ss = 8;
unsigned short val_us = 0;
int val_si = 0;
unsigned int val_ui = 0;
float val_f = 0;
double val_d = 0;
bool val_b = false;
bool val_b2 = false;
//--------------------------------------------------------------
void testApp::setup() {
	edit_.addString("you can edit and use");
	edit_.addString(" variables only adding");
	edit_.addString("  to ofxParamEdit");
	edit_.addString("");
	edit_.addString("most simply like this");
	edit_.addInt("int", val_si2, -1000, 1000);
	edit_.addString("------------------------");
	edit_.addString("");
	edit_.addString("or create group");
	edit_.beginGroup("group");
		edit_.addString("");
		edit_.addString("groups can be nested");
		edit_.beginGroup("group2");
			edit_.beginGroup("group3");
			edit_.endGroup();
		edit_.endGroup();
		edit_.addString("------------------------");
		edit_.addString("");
		edit_.addString("vars with callback");
		edit_.addString(" (output to console)");
		edit_.addChar("char", val_sc, 0, 100, this, &testApp::testInt);
		edit_.addInt("int", val_si, 0, 100, this, &testApp::testInt);
		edit_.addFloat("float", val_f, -1, 16, this, &testApp::testFloat);
		edit_.addBool("toggle", val_b, this, &testApp::testBool);
		edit_.addButton("button", val_b2, this, &testApp::testBool);
	edit_.endGroup();
	/**
	edit_.addString("------------------------");
	edit_.addString("");
	edit_.addString("other types");
	edit_.addUChar("uchar", val_uc, 0, 255);
	edit_.addShort("short", val_ss, -100, 100);
	edit_.addUShort("ushort", val_us, 0, 1000);
	edit_.addUInt("uint", val_ui, 0, 100);
	edit_.addDouble("double", val_d, -3.14, 6.28);
	/**/
}

//--------------------------------------------------------------
void testApp::update() {
}

//--------------------------------------------------------------
void testApp::draw() {
	if(edit_.isOpen()) {
		edit_.draw();
	}
	ofSetColor(0,0,0);
	int y = 1;
	int h = 15;
	ofDrawBitmapString("o: open gui", 300, ++y*h);
	ofDrawBitmapString("c: close gui", 300, ++y*h);
	++y;
	ofDrawBitmapString("preview vars in 'group'", 300, ++y*h);
	ofDrawBitmapString("char  : "+ofToString(val_sc), 300, ++y*h);
	ofDrawBitmapString("int   : "+ofToString(val_si), 300, ++y*h);
	ofDrawBitmapString("float : "+ofToString(val_f), 300, ++y*h);
	ofDrawBitmapString("toggle: "+ofToString(val_b), 300, ++y*h);
	ofDrawBitmapString("button: "+ofToString(val_b2), 300, ++y*h);

}


//--------------------------------------------------------------
void testApp::exit() {
}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
	switch(key) {
	case 'o':
		edit_.open();
		break;
	case 'c':
		edit_.close();
		break;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

