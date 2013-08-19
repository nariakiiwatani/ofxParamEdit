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

template<typename Type>
ofxParamSlider<Type>::ofxParamSlider()
:ofxSlider<Type>()
,ref_(NULL)
{
}

template<typename Type>
ofxParamSlider<Type>::~ofxParamSlider()
{
	if(ref_) {
		ofxParamSlider<Type>::removeListener(this, &ofxParamSlider::onChange);
	}
}

template<typename Type>
ofxParamSlider<Type>::ofxParamSlider(string _name, Type min, Type max, float width, float height)
{
	dummy_ = min;
	setup(_name, dummy_, min, max, width, height);
}

template<typename Type>
ofxParamSlider<Type>::ofxParamSlider(string _name, Type& val, Type min, Type max, float width, float height)
{
	setup(_name, val, min, max, width, height);
}

template<typename Type>
ofxParamSlider<Type>* ofxParamSlider<Type>::setup(string _name, Type& val, Type min, Type max, float width, float height)
{
	ofxSlider<Type>::setup(_name, val, min, max, width, height);
	ofxSlider<Type>::addListener(this, &ofxParamSlider::onChange);
	setReference(val);
	return this;
}

template<typename Type>
void ofxParamSlider<Type>::onChange(Type& val)
{
	if(ref_) {
		*ref_ = val;
	}
	changed_.notify(this, val);
}

template<typename Type>
void ofxParamSlider<Type>::render()
{
	if(ref_ && ofxSlider<Type>::value != *ref_) {
		ofxSlider<Type>::value = *ref_;
		ofxSlider<Type>::generateDraw();
	}
	ofxSlider<Type>::render();
}

/* EOF */