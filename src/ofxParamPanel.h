#pragma once

#include "ofxPanel.h"
#include "ofxParamSlider.h"

class ofxParamPanel : public ofxPanel{
public:
	ofxParamPanel();

	void add(ofxBaseGui * element);
	void add(string name, bool& val);
	template<typename Type>
	void add(string name, Type& val, Type min, Type max);

	void load();
	void save();

	void beginGroup(string name);
	void endGroup();
	void draw();

private:
	ofxParamPanel* parent_;
	ofxParamPanel* current_;
	vector<ofxParamPanel*> children_;
	bool is_open_;
};

template<typename Type>
void ofxParamPanel::add(string name, Type& val, Type min, Type max)
{
	current_->ofxPanel::add(new ofxParamSlider<Type>(name, val, min, max));
}

