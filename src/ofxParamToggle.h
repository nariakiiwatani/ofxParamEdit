#pragma once

#include "../libs/ofxGui/src/ofxToggle.h"

class ofxParamToggle : public ofxToggle{
public:
	ofxParamToggle();
	~ofxParamToggle();
	ofxParamToggle(string _name, float width = ofxToggle::defaultWidth, float height = ofxToggle::defaultHeight);
	ofxParamToggle(string _name, bool& val, float width = ofxToggle::defaultWidth, float height = ofxToggle::defaultHeight);
	ofxParamToggle * setup(string _name, float width = ofxToggle::defaultWidth, float height = ofxToggle::defaultHeight);
	ofxParamToggle * setup(string _name, bool& val, float width = ofxToggle::defaultWidth, float height = ofxToggle::defaultHeight);

	template<class ListenerClass>
	void addListener(ListenerClass * listener, void ( ListenerClass::*method )(bool&)){
		changed_ += Poco::delegate(listener, method);
	}

	template<class ListenerClass>
	void removeListener(ListenerClass * listener, void ( ListenerClass::*method )(bool&)){
		changed_ -= Poco::delegate(listener, method);
	}

	void draw();

private:
	void onChange(bool& val);
	bool dummy_;
	bool * ref_;
	ofEvent<bool> changed_;
};
