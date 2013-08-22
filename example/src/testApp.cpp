#include "testApp.h"
#include "ofxParamEdit.h"

namespace {
	ofxParamEdit param;
	// below are vars to be edit
	bool enable=true;
	ofFloatColor color;
	ofVec2f pos(300,100);
	float size=100;
	bool child_enable=true;
	float child_pos_x=50;
	float child_pos_y=50;
	
	ofColor bg_color(128,128,128);
};

//--------------------------------------------------------------
void testApp::setup(){
	// set root name
	param.setup("root");
	// add variable
	param.addButton("bang", this, &testApp::callback);
	param.addToggle("on off", enable, this, &testApp::callbackB);
	param.addSlider("size", size, 100.f, 500.f, this, &testApp::callbackF);
	param.addColorSlider("color", color, ofFloatColor(0,0,0,0), ofFloatColor(1,1,1,1), this, &testApp::callbackC);
	param.addVecSlider("pos", pos, ofVec2f(0,0), ofVec2f(ofGetWidth(), ofGetHeight()), this, &testApp::callbackV);
	// create a group
	param.beginGroup("child", true);	// second arg should be true( or blank) if you wanted the group to be a panel
	param.addToggle("on off", child_enable);
	param.addSlider("x", child_pos_x, -(float)ofGetWidth(), (float)ofGetWidth());
	param.addSlider("y", child_pos_y, -(float)ofGetHeight(), (float)ofGetHeight());
	param.endGroup();

	param.load();
	param.open();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(bg_color);
	if(enable) {
		ofPushStyle();
		ofSetColor(color);
		ofPushMatrix();
		ofTranslate(pos);
		ofRect(0,0,size,size);
		if(child_enable) {
			ofPushMatrix();
			ofTranslate(child_pos_x,child_pos_y);
			ofRect(0,0,size,size);
			ofPopMatrix();
		}
		ofPopMatrix();
		ofPopStyle();
	}
	param.draw();
}

void testApp::callback()
{
	ofLog(OF_LOG_NOTICE, "bang");
	bg_color.set(ofRandom(255),ofRandom(255),ofRandom(255));
}

void testApp::callbackB(bool& val)
{
	ofLog(OF_LOG_NOTICE, "bool:%s", val?"true":"false");
}

void testApp::callbackF(float& val)
{
	ofLog(OF_LOG_NOTICE, "float:%f", val);
}

void testApp::callbackV(ofVec2f& val)
{
	ofLog(OF_LOG_NOTICE, "vec2:(%f,%f)", val.x, val.y);
}

void testApp::callbackC(ofFloatColor& val)
{
	ofLog(OF_LOG_NOTICE, "color:(%f,%f,%f,%f)", val.r, val.g, val.b, val.a);
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