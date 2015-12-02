#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// set root name
	param.setup("root");
	// add variable
	param.addButton("bang", this, &ofApp::callback);
	param.addToggle("on off", enable, this, &ofApp::callbackB);
	param.addSlider("size", size, 100.f, 500.f, this, &ofApp::callbackF);
	param.addColorSlider("color", color, ofFloatColor(0,0,0,0), ofFloatColor(1,1,1,1), this, &ofApp::callbackC);
	param.addVecSlider("pos", pos, ofVec2f(0,0), ofVec2f(ofGetWidth(), ofGetHeight()), this, &ofApp::callbackV);
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
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(bg_color);
	if(enable) {
		ofPushStyle();
		ofSetColor(color);
		ofPushMatrix();
		ofTranslate(pos);
		ofDrawRectangle(0,0,size,size);
		if(child_enable) {
			ofPushMatrix();
			ofTranslate(child_pos_x,child_pos_y);
			ofDrawRectangle(0,0,size,size);
			ofPopMatrix();
		}
		ofPopMatrix();
		ofPopStyle();
	}
	param.draw();
}

void ofApp::callback()
{
	ofLog(OF_LOG_NOTICE, "bang");
	bg_color.set(ofRandom(255),ofRandom(255),ofRandom(255));
}

void ofApp::callbackB(bool& val)
{
	ofLog(OF_LOG_NOTICE, "bool:%s", val?"true":"false");
}

void ofApp::callbackF(float& val)
{
	ofLog(OF_LOG_NOTICE, "float:%f", val);
}

void ofApp::callbackV(ofVec2f& val)
{
	ofLog(OF_LOG_NOTICE, "vec2:(%f,%f)", val.x, val.y);
}

void ofApp::callbackC(ofFloatColor& val)
{
	ofLog(OF_LOG_NOTICE, "color:(%f,%f,%f,%f)", val.r, val.g, val.b, val.a);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}