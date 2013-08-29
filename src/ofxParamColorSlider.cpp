#include "ofxParamColorSlider.h"


template<typename Type>
ofxParamColorSlider<Type>::ofxParamColorSlider()
:ofxColorSlider_<Type>()
,ref_(NULL)
{
}

template<typename Type>
ofxParamColorSlider<Type>::~ofxParamColorSlider()
{
	if(ref_) {
		ofxColorSlider_<Type>::value.removeListener(this, &ofxParamColorSlider::onChange);
	}
}

template<typename Type>
ofxParamColorSlider<Type>::ofxParamColorSlider(string _name, const ColType& min, const ColType& max, float width, float height)
{
	dummy_ = min;
	setup(_name, dummy_, min, max, width, height);
}

template<typename Type>
ofxParamColorSlider<Type>::ofxParamColorSlider(string _name, ColType& val, const ColType& min, const ColType& max, float width, float height)
{
	setup(_name, val, min, max, width, height);
}

template<typename Type>
ofxParamColorSlider<Type>* ofxParamColorSlider<Type>::setup(string _name, ColType& val, const ColType& min, const ColType& max, float width, float height)
{
	ofxColorSlider_<Type>::setup(_name, val, min, max, width, height);
	ofxColorSlider_<Type>::value.addListener(this, &ofxParamColorSlider::onChange);
	setReference(val);
	return this;
}

template<typename Type>
void ofxParamColorSlider<Type>::onChange(ColType& val)
{
	if(ref_) {
		*ref_ = val;
	}
	changed_.notify(this, val);
}

template<typename Type>
void ofxParamColorSlider<Type>::render()
{
	if(ref_
	   && ofxColorSlider_<Type>::value.get().r != (*ref_).r
	   && ofxColorSlider_<Type>::value.get().g != (*ref_).g
	   && ofxColorSlider_<Type>::value.get().b != (*ref_).b
	   && ofxColorSlider_<Type>::value.get().a != (*ref_).a
	   ) {
		ofxColorSlider_<Type>::value = *ref_;
		ofxColorSlider_<Type>::generateDraw();
	}
	ofxColorSlider_<Type>::render();
}

template class ofxParamColorSlider<unsigned char>;
template class ofxParamColorSlider<unsigned short>;
template class ofxParamColorSlider<float>;


/* EOF */