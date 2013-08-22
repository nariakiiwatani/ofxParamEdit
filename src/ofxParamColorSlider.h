#pragma once

#include "ofxSliderGroup.h"

template<class Type>
class ofxParamColorSlider : public ofxColorSlider_<Type>
{
	typedef ofColor_<Type> ColType;
public:
	ofxParamColorSlider();
	~ofxParamColorSlider();
	ofxParamColorSlider(string _name, const ColType& min, const ColType& max, float width = ofxColorSlider_<Type>::defaultWidth, float height = ofxColorSlider_<Type>::defaultHeight);
	ofxParamColorSlider(string _name, ColType& val, const ColType& min, const ColType& max, float width = ofxColorSlider_<Type>::defaultWidth, float height = ofxColorSlider_<Type>::defaultHeight);
	ofxParamColorSlider* setup(string _name, ColType& val, const ColType& min, const ColType& max, float width = ofxColorSlider_<Type>::defaultWidth, float height = ofxColorSlider_<Type>::defaultHeight);
	
	void setReference(ColType& val) { ref_ = &val; }
	
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
	void onChange(ColType& val);
	ColType dummy_;
	ColType *ref_;
	ofEvent<ColType> changed_;
};


/* EOF */