#pragma once

#include "../libs/ofxGui/src/ofxPanel.h"
#include "ofxParamSlider.h"
#include "ofxParamToggle.h"

class ofxLabel;
class ofxParamPanel : public ofxPanel
{
public:
	ofxParamPanel();
	~ofxParamPanel();

	void add(ofxBaseGui * element);
	
	ofxButton* addButton(string name);
	template<typename ListenerClass>
	ofxButton* addButton(string name, ListenerClass * listener, void ( ListenerClass::*method )(bool&));

	ofxParamToggle* addToggle(string name, bool& val);
	template<typename ListenerClass>
	ofxParamToggle* addToggle(string name, ListenerClass * listener, void ( ListenerClass::*method )(bool&));
	template<typename ListenerClass>
	ofxParamToggle* addToggle(string name, bool& val, ListenerClass * listener, void ( ListenerClass::*method )(bool&));
	
	template<typename Type>
	ofxParamSlider<Type>* addSlider(string name, Type& val, Type min, Type max);
	template<typename Type, typename ListenerClass>
	ofxParamSlider<Type>* addSlider(string name, Type min, Type max, ListenerClass * listener, void ( ListenerClass::*method )(Type&));
	template<typename Type, typename ListenerClass>
	ofxParamSlider<Type>* addSlider(string name, Type& val, Type min, Type max, ListenerClass * listener, void ( ListenerClass::*method )(Type&));

	ofxLabel* addString(string name);

	void addPanel(string name, ofxParamPanel* panel);

	void load();
	void save();

	bool isOpen() { return is_open_; }
	void open() { is_open_ = true; }
	void close() { is_open_ = false; }

	void beginGroup(string name);
	void endGroup();
	void draw();

private:
	void setOpenCB(bool& set) { set?open():close(); }
	template<typename Type>
	ofxParamSlider<Type>* addSlider(string name, Type min, Type max);
	ofxParamToggle* addToggle(string name);
	ofxParamPanel* parent_;
	ofxParamPanel* current_;
	vector<ofxParamPanel*> children_;
	vector<ofxBaseGui*> allocated_;
	bool is_open_;
};

template<typename Type>
ofxParamSlider<Type>* ofxParamPanel::addSlider(string name, Type min, Type max)
{
	ofxParamSlider<Type>* slider = new ofxParamSlider<Type>(name, min, max);
	current_->ofxPanel::add(slider);
	allocated_.push_back(slider);
	return slider;
}

template<typename Type>
ofxParamSlider<Type>* ofxParamPanel::addSlider(string name, Type& val, Type min, Type max)
{
	ofxParamSlider<Type>* slider = new ofxParamSlider<Type>();
	slider->setup(name, val, min, max);
	current_->ofxPanel::add(slider);
	allocated_.push_back(slider);
	return slider;
}

template<typename Type, typename ListenerClass>
ofxParamSlider<Type>* ofxParamPanel::addSlider(string name, Type min, Type max, ListenerClass * listener, void ( ListenerClass::*method )(Type&))
{
	ofxParamSlider<Type>* slider = addSlider(name, min, max);
	slider->addListener(listener, method);
	return slider;
}

template<typename Type, typename ListenerClass>
ofxParamSlider<Type>* ofxParamPanel::addSlider(string name, Type& val, Type min, Type max, ListenerClass * listener, void ( ListenerClass::*method )(Type&))
{
	ofxParamSlider<Type>* slider = addSlider(name, val, min, max);
	slider->addListener(listener, method);
	return slider;
}

template<typename ListenerClass>
ofxButton* ofxParamPanel::addButton(string name, ListenerClass * listener, void ( ListenerClass::*method )(bool&))
{
	ofxButton* button = addButton(name);
	button->addListener(listener, method);
	return button;
}
template<typename ListenerClass>
ofxParamToggle* ofxParamPanel::addToggle(string name, ListenerClass * listener, void ( ListenerClass::*method )(bool&))
{
	ofxParamToggle* toggle = addToggle(name);
	toggle->addListener(listener, method);
	return toggle;
}
template<typename ListenerClass>
ofxParamToggle* ofxParamPanel::addToggle(string name, bool& val, ListenerClass * listener, void ( ListenerClass::*method )(bool&))
{
	ofxParamToggle* toggle = addToggle(name, val);
	toggle->addListener(listener, method);
	return toggle;
}
