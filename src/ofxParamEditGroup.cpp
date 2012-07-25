/**
 * ofxParamEditGroup.cpp
 * by nariakiiwatani
 */

#pragma once

#include "ofxParamEdit.h"

ofxParamEditGroup::ofxParamEditGroup(string name, ofxParamEditGroup* parent, ofxParamEdit* controller)
:parent_(parent), controller_(controller)
{
	panel_.setup(name, name+".xml");
}

void ofxParamEditGroup::open()
{
	controller_->openGroup(this);
}

void ofxParamEditGroup::add(ofxBaseGui* element)
{
	panel_.add(element);
}
void ofxParamEditGroup::openButtonPress(bool& val)
{
	if(val == false) {
		open();
	}
}
void ofxParamEditGroup::backButtonPress(bool& val)
{
	if(val == false && parent_) {
		parent_->open();
	}
}
