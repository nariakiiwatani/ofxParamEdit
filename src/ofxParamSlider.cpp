#include "ofxParamSlider.h"

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
		ofxSlider<Type>::removeListener(this, &ofxParamSlider::onChange);
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

template class ofxParamSlider<int>;
template class ofxParamSlider<unsigned int>;
template class ofxParamSlider<float>;
template class ofxParamSlider<double>;
template class ofxParamSlider<signed char>;
template class ofxParamSlider<unsigned char>;
template class ofxParamSlider<unsigned short>;
template class ofxParamSlider<short>;

/* EOF */