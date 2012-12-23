#pragma once

#include "ofxSlider.h"

template<typename Type>
class ofxParamSlider : public ofxSlider<Type>{
public:
	ofxParamSlider();
	~ofxParamSlider();
	ofxParamSlider(string _name, Type & val, Type min, Type max, float width = defaultWidth, float height = defaultHeight);
	ofxParamSlider* setup(string _name, Type & val, Type min, Type max, float width = defaultWidth, float height = defaultHeight);

	template<class ListenerClass>
	void addListener(ListenerClass * listener, void ( ListenerClass::*method )(Type&)){
		changed_ += Poco::delegate(listener, method);
	}

	template<class ListenerClass>
	void removeListener(ListenerClass * listener, void ( ListenerClass::*method )(Type&)){
		changed_ -= Poco::delegate(listener, method);
	}

private:
	void onChange(Type& val);
	Type* ref_;
	ofEvent<Type> changed_;
};

template<typename Type>
ofxParamSlider<Type>::ofxParamSlider()
:ofxSlider()
,ref_(NULL)
{
}

template<typename Type>
ofxParamSlider<Type>::~ofxParamSlider()
{
	if(ref_) {
		ofxParamSlider::removeListener(this, &ofxParamSlider::onChange);
	}
}

template<typename Type>
ofxParamSlider<Type>::ofxParamSlider(string _name, Type& val, Type min, Type max, float width, float height)
{
	setup(_name, val, min, max, width, height);
}

template<typename Type>
ofxParamSlider<Type>* ofxParamSlider<Type>::setup(string _name, Type& val, Type min, Type max, float width, float height)
{
	ofxSlider::setup(_name, val, min, max, width, height);
	ofxSlider::addListener(this, &ofxParamSlider::onChange);
	ref_ = &val;
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