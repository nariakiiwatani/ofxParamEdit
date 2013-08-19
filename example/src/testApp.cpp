#include "testApp.h"
#include "ofxParamEdit.h"

namespace {
	ofxParamEdit param;
	// below are vars to be edit
	bool child_enable;
	int color_index;
	float pos_x;
	float pos_y;
	float child_pos_x;
	float child_pos_y;
};

//--------------------------------------------------------------
void testApp::setup(){
	// set root name
	param.setup("root");
	// add variable
	param.addSlider("color", color_index, 0, 7);
	// create a group
	param.beginGroup("pos", false);
	param.addSlider("x", pos_x, 0.f, (float)ofGetWidth());
	param.addSlider("y", pos_y, 0.f, (float)ofGetHeight());
	// groups can be nested
	param.beginGroup("child", true);	// second arg should be true( or blank) if you wanted the group to be a panel
	param.addToggle("on off", child_enable);
	param.addSlider("x", child_pos_x, -(float)ofGetWidth(), (float)ofGetWidth());
	param.addSlider("y", child_pos_y, -(float)ofGetHeight(), (float)ofGetHeight());
	param.endGroup();
	param.endGroup();

	param.load();
	param.open();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	static const ofColor col[8] = {
		ofColor::white,
		ofColor::red,
		ofColor::green,
		ofColor::blue,
		ofColor::cyan,
		ofColor::magenta,
		ofColor::yellow,
		ofColor::black,
	};
	ofBackground(ofColor::gray);
	ofPushStyle();
	ofSetColor(col[color_index]);
	ofPushMatrix();
	ofTranslate(pos_x,pos_y);
	ofRect(0,0,50,50);
	if(child_enable) {
		ofPushMatrix();
		ofTranslate(child_pos_x,child_pos_y);
		ofRect(0,0,50,50);
		ofPopMatrix();
	}
	ofPopMatrix();
	ofPopStyle();
	param.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

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

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}