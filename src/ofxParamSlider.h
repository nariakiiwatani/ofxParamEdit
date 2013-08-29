#pragma once

#include "ofxSlider.h"

template<typename Type>
class ofxParamSlider : public ofxSlider<Type>{
public:
	ofxParamSlider();
	~ofxParamSlider();
	ofxParamSlider(string _name, Type min, Type max, float width = ofxSlider<Type>::defaultWidth, float height = ofxSlider<Type>::defaultHeight);
	ofxParamSlider(string _name, Type & val, Type min, Type max, float width = ofxSlider<Type>::defaultWidth, float height = ofxSlider<Type>::defaultHeight);
	ofxParamSlider* setup(string _name, Type & val, Type min, Type max, float width = ofxSlider<Type>::defaultWidth, float height = ofxSlider<Type>::defaultHeight);
	
	void setReference(Type& val) { ref_ = &val; }

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
	void onChange(Type& val);
	Type dummy_;
	Type *ref_;
	ofEvent<Type> changed_;
};

/* EOF */