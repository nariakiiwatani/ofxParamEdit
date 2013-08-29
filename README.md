ofxParamEdit
============
by nariakiiwatani

Abstract
------------
ofxParamEdit provides the SIMPLEST interface to edit values with ofxGui.
You can edit normal valriables (like int, float,,,) through this addon.

Depends on...
------------
ofxGui  (v0.8.0 or later)

Usage
------------
see example/src/testApp.cpp

	ofxParamEdit param;
	// below are vars to be edit
	bool enable=true;
	ofFloatColor color;
	ofVec2f pos(300,100);
	float size=100;
	bool child_enable=true;
	float child_pos_x=50;
	float child_pos_y=50;
	// set root name
	param.setup("root");
	// add variable (with callback)
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

	// load from XML file
	param.load();
	// visible
	param.open();

