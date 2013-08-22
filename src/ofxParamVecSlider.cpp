#include "ofxParamVecSlider.h"


template<typename Type>
ofxParamVecSlider<Type>::ofxParamVecSlider()
:ofxVecSlider_<Type>()
,ref_(NULL)
{
}

template<typename Type>
ofxParamVecSlider<Type>::~ofxParamVecSlider()
{
	if(ref_) {
		ofxVecSlider_<Type>::value.removeListener(this, &ofxParamVecSlider::onChange);
	}
}

template<typename Type>
ofxParamVecSlider<Type>::ofxParamVecSlider(string _name, const Type& min, const Type& max, float width, float height)
{
	dummy_ = min;
	setup(_name, dummy_, min, max, width, height);
}

template<typename Type>
ofxParamVecSlider<Type>::ofxParamVecSlider(string _name, Type& val, const Type& min, const Type& max, float width, float height)
{
	setup(_name, val, min, max, width, height);
}

template<typename Type>
ofxParamVecSlider<Type>* ofxParamVecSlider<Type>::setup(string _name, Type& val, const Type& min, const Type& max, float width, float height)
{
	ofxVecSlider_<Type>::setup(_name, val, min, max, width, height);
	ofxVecSlider_<Type>::value.addListener(this, &ofxParamVecSlider::onChange);
	setReference(val);
	return this;
}

template<typename Type>
void ofxParamVecSlider<Type>::onChange(Type& val)
{
	if(ref_) {
		*ref_ = val;
	}
	changed_.notify(this, val);
}

template<typename Type>
void ofxParamVecSlider<Type>::render()
{
	if(ref_ && ofxVecSlider_<Type>::value.get() != *ref_) {
		ofxVecSlider_<Type>::value = *ref_;
		ofxVecSlider_<Type>::generateDraw();
	}
	ofxVecSlider_<Type>::render();
}
template class ofxParamVecSlider<ofVec2f>;
template class ofxParamVecSlider<ofVec3f>;
template class ofxParamVecSlider<ofVec4f>;


/* EOF */