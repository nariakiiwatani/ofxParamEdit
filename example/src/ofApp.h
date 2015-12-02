#pragma once

#include "ofMain.h"
#include "ofxParamEdit.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
private:
	void callback();
	void callbackB(bool& val);
	void callbackF(float& val);
	void callbackV(ofVec2f& val);
	void callbackC(ofFloatColor& val);

	ofxParamEdit param;
	// below are vars to be edit
	bool enable=true;
	ofFloatColor color;
	ofVec2f pos = ofVec2f(300,100);
	float size=100;
	bool child_enable=true;
	float child_pos_x=50;
	float child_pos_y=50;
	
	ofColor bg_color = ofColor(128,128,128);
};
