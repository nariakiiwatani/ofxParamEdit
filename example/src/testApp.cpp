#include "testApp.h"

#include "ofxGui.h"
#include "ofxParamPanel.h"
#include "ofxParamToggle.h"

namespace {
	ofxParamPanel panel_;
	bool toggle_value_;
	float float_value_;
	int int_value_;
};

//--------------------------------------------------------------
void testApp::setup(){
	panel_.setup("settings");
	panel_.addToggle("toggle", toggle_value_);
	panel_.beginGroup("hoge");
	panel_.addSlider("int", int_value_, 0, 255);
	panel_.beginGroup("fuga");
	panel_.addSlider("float", float_value_, -1.f, 1.f);
	panel_.endGroup();
	panel_.endGroup();
	panel_.load();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	panel_.draw();

	int x = 20;
	int y = 100;
	int y_interval = 15;
	string str = "";
	str = "toggle:";
	str += (toggle_value_?"true":"false");
	ofDrawBitmapString(str, x, y);	y += y_interval;
	str = "int:";
	str += ofToString(int_value_);
	ofDrawBitmapString(str, x, y);	y += y_interval;
	str = "float:";
	str += ofToString(float_value_);
	ofDrawBitmapString(str, x, y);	y += y_interval;
}

//--------------------------------------------------------------
void testApp::exit(){
	panel_.save();
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