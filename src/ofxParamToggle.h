#pragma once

#include "ofxToggle.h"

class ofxParamToggle : public ofxToggle{
public:
	ofxParamToggle();
	~ofxParamToggle();
	ofxParamToggle(string _name, float width = ofxToggle::defaultWidth, float height = ofxToggle::defaultHeight);
	ofxParamToggle(string _name, bool& val, float width = ofxToggle::defaultWidth, float height = ofxToggle::defaultHeight);
	ofxParamToggle * setup(string _name, float width = ofxToggle::defaultWidth, float height = ofxToggle::defaultHeight);
	ofxParamToggle * setup(string _name, bool& val, float width = ofxToggle::defaultWidth, float height = ofxToggle::defaultHeight);
	
	void setReference(bool& val) { ref_ = &val; }

	template<class ListenerClass, typename ListenerMethod>
	void addListener(ListenerClass * listener, ListenerMethod method){
		ofAddListener(changed_,listener,method);
	}

	template<class ListenerClass, typename ListenerMethod>
	void removeListener(ListenerClass * listener, ListenerMethod method){
		ofRemoveListener(changed_,listener,method);
	}
	void render();

private:
	void onChange(bool& val);
	bool dummy_;
	bool * ref_;
	ofEvent<bool> changed_;
};

/* EOF */