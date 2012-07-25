/******************************************************************/
/**
 * @file	testApp.h
 * @brief	Example for ofxParamEdit addon
 * @note
 * @todo
 * @bug	
 *
 * @author	nariakiiwatani
 * @date	Jul. 24, 2012
 */
/******************************************************************/
#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp {
	public:

		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		void testBool(bool& val){printf("%s\n",ofToString(val).c_str());};
		void testInt(int& val){printf("%s\n",ofToString(val).c_str());};
		void testFloat(float& val){printf("%s\n",ofToString(val).c_str());};
};
