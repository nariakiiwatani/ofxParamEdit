#pragma once

#include "../libs/ofxGui/src/ofxSlider.h"

template<typename Type>
class ofxParamSlider : public ofxSlider<Type>{
public:
	ofxParamSlider();
	~ofxParamSlider();
	ofxParamSlider(string _name, Type min, Type max, float width = ofxSlider<Type>::defaultWidth, float height = ofxSlider<Type>::defaultHeight);
	ofxParamSlider(string _name, Type & val, Type min, Type max, float width = ofxSlider<Type>::defaultWidth, float height = ofxSlider<Type>::defaultHeight);
	ofxParamSlider* setup(string _name, Type & val, Type min, Type max, float width = ofxSlider<Type>::defaultWidth, float height = ofxSlider<Type>::defaultHeight);

	template<class ListenerClass>
	void addListener(ListenerClass * listener, void ( ListenerClass::*method )(Type&)){
		changed_ += Poco::delegate(listener, method);
	}

	template<class ListenerClass>
	void removeListener(ListenerClass * listener, void ( ListenerClass::*method )(Type&)){
		changed_ -= Poco::delegate(listener, method);
	}

	void draw();

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

template<typename Type>
void ofxParamSlider<Type>::draw()
{
	if(ref_ && ofxSlider<Type>::value != *ref_) {
		ofxSlider<Type>::value = *ref_;
	}
	ofxSlider<Type>::draw();
}