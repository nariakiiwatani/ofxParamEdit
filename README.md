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
	bool child_enable;
	int color_index;
	float pos_x;
	float pos_y;
	float child_pos_x;
	float child_pos_y;
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
	// load from xml file
	param.load();
	param.open();

