#pragma once

#include "ofxSliderGroup.h"

template<class Type>
class ofxParamVecSlider : public ofxVecSlider_<Type>
{
public:
	ofxParamVecSlider();
	~ofxParamVecSlider();
	ofxParamVecSlider(string _name, const Type& min, const Type& max, float width = ofxVecSlider_<Type>::defaultWidth, float height = ofxVecSlider_<Type>::defaultHeight);
	ofxParamVecSlider(string _name, Type & val, const Type& min, const Type& max, float width = ofxVecSlider_<Type>::defaultWidth, float height = ofxVecSlider_<Type>::defaultHeight);
	ofxParamVecSlider* setup(string _name, Type & val, const Type& min, const Type& max, float width = ofxVecSlider_<Type>::defaultWidth, float height = ofxVecSlider_<Type>::defaultHeight);
	
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