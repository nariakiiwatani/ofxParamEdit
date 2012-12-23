#pragma once

#include "ofxToggle.h"

class ofxParamToggle : public ofxToggle{
public:
	ofxParamToggle();
	~ofxParamToggle();
	ofxParamToggle(string _name, bool& val, float width = defaultWidth, float height = defaultHeight);
	ofxParamToggle * setup(string _name, bool& val, float width = defaultWidth, float height = defaultHeight);

	template<class ListenerClass>
	void addListener(ListenerClass * listener, void ( ListenerClass::*method )(bool&)){
		changed_ += Poco::delegate(listener, method);
	}

	template<class ListenerClass>
	void removeListener(ListenerClass * listener, void ( ListenerClass::*method )(bool&)){
		changed_ -= Poco::delegate(listener, method);
	}

private:
	void onChange(bool& val);
	bool * ref_;
	ofEvent<bool> changed_;
};
