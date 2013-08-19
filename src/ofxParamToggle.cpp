
#include "ofxParamToggle.h"

ofxParamToggle::ofxParamToggle()
:ofxToggle()
,ref_(NULL)
{
}

ofxParamToggle::~ofxParamToggle()
{
	if(ref_) {
		ofxToggle::removeListener(this, &ofxParamToggle::onChange);
	}
}

ofxParamToggle::ofxParamToggle(string _name, float width, float height)
{
	setup(_name, width, height);
}
ofxParamToggle::ofxParamToggle(string _name, bool & val, float width, float height)
{
	setup(_name, val, width, height);
}
ofxParamToggle* ofxParamToggle::setup(string _name, float width, float height)
{
	dummy_ = false;
	return setup(_name, dummy_, width, height);
}

ofxParamToggle* ofxParamToggle::setup(string _name, bool & val, float width, float height)
{
	ofxToggle::setup(_name, val, width, height);
	ofxToggle::addListener(this, &ofxParamToggle::onChange);
	ref_ = &val;
	return this;
}

void ofxParamToggle::onChange(bool& val)
{
	if(ref_) {
		*ref_ = val;
	}
	changed_.notify(this, val);
}

void ofxParamToggle::render()
{
	if(ref_ && value != *ref_) {
		value = *ref_;
		generateDraw();
	}
	ofxToggle::render();
}

/* EOF */