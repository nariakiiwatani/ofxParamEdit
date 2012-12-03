/**
 * ofxParamEditGroup.h
 * by nariakiiwatani
 */

#pragma once

#include "ofxPanel.h"
#include "ofxButton.h"

class ofxParamEdit;

class ofxParamEditGroup {
	friend class ofxParamEdit;
public:
	ofxParamEditGroup(string name, ofxParamEditGroup* parent, ofxParamEdit* controller);
	void add(ofxBaseGui* element);
	void open();
	void load();
	void save();
	void clear();
	string getName(bool check_parent=false, string separator="/");

	void setPosition(ofPoint p);
	void setPosition(float x, float y);
	ofPoint getPosition();

private:
	void openButtonPress(bool&);
	void backButtonPress(bool&);
private:
	ofxParamEdit* controller_;
	ofxParamEditGroup* parent_;
	ofxPanel panel_;
	string name_;
};

