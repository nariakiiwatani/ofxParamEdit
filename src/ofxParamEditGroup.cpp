/**
 * ofxParamEditGroup.cpp
 * by nariakiiwatani
 */

#pragma once

#include "ofxParamEdit.h"

ofxParamEditGroup::ofxParamEditGroup(string name, ofxParamEditGroup* parent, ofxParamEdit* controller)
:parent_(parent), controller_(controller),name_(name)
{
	panel_.setup(getName(true), getName(true)+".xml");
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
void ofxParamEditGroup::load()
{
	panel_.loadFromFile(getName(true)+".xml");
}

string ofxParamEditGroup::getName(bool check_parent, string separator)
{
	if(check_parent && parent_) {
		return parent_->getName(check_parent, separator)+separator+name_;
	}
	else {
		return name_;
	}
}
