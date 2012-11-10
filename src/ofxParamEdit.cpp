/******************************************************************/
/**
 * @file	ofxParamEdit.cpp
 * @brief	This class provides the SIMPLEST interface to edit values with ofxGui.
 * @note
 * @todo
 *
 * @author	nariakiiwatani
 * @date	Jul. 24, 2012
 */
/******************************************************************/

#pragma once

#include "ofxParamEdit.h"
#include "ofxGuiString.h"
#include <algorithm>

ofxParamEdit::ofxParamEdit()
:root_("param", NULL, this)
,current_(&root_)
,active_(&root_)
,enable_(true)
{
}
ofxParamEdit::ofxParamEdit(string name)
:root_(name, NULL, this)
,current_(&root_)
,active_(&root_)
,enable_(true)
{
}

ofxParamEdit::~ofxParamEdit()
{
	clear();
}

void ofxParamEdit::clear()
{
	while(!allocated_list_.empty()) {
		delete allocated_list_.at(0);
		allocated_list_.erase(allocated_list_.begin());
	}
	root_.clear();
	current_ = &root_;
	active_ = &root_;
}

void ofxParamEdit::draw()
{
	active_->panel_.draw();
}

void ofxParamEdit::beginGroup(string name)
{
	ofxParamEditGroup* group = new ofxParamEditGroup(name, current_, this);
	addButton(">open "+name, group, &ofxParamEditGroup::openButtonPress);
	current_  = group;
	addButton(">back", group, &ofxParamEditGroup::backButtonPress);
}

void ofxParamEdit::endGroup()
{
	current_->load();
	current_ = current_->parent_;
}

void ofxParamEdit::openGroup(ofxParamEditGroup* group)
{
	group->panel_.setPosition(active_->panel_.getPosition());
	active_ = group;
	enable_ = true;
}

/* ======================================
		add functions' implementation
		(unwillingness using macros...)
 ====================================== */

#define IMPL_ADD_SLIDER_FUNC(Type, type) \
void ofxParamEdit::add##Type(string name, type &value, type min, type max) { \
	_add##Type(name, value, min, max); \
} \
ofxParamEdit::ofxParamEdit##Type* ofxParamEdit::_add##Type(string name, type &value, type min, type max) { \
	ofxParamEdit##Type* edit = new ofxParamEdit##Type(name, value, min, max); \
	current_->add(edit->getGui()); \
	allocated_list_.push_back(edit); \
	return edit; \
}

#define IMPL_ADD_TOGGLE_FUNC1(Type) \
void ofxParamEdit::add##Type(string name) { \
	_add##Type(name); \
} \
ofxParamEdit::ofxParamEdit##Type* ofxParamEdit::_add##Type(string name) { \
	ofxParamEdit##Type* edit = new ofxParamEdit##Type(name); \
	current_->add(edit->getGui()); \
	allocated_list_.push_back(edit); \
	return edit; \
}
#define IMPL_ADD_TOGGLE_FUNC2(Type, type) \
void ofxParamEdit::add##Type(string name, type &value) { \
	_add##Type(name, value); \
} \
ofxParamEdit::ofxParamEdit##Type* ofxParamEdit::_add##Type(string name, type &value) { \
	ofxParamEdit##Type* edit = new ofxParamEdit##Type(name, value); \
	current_->add(edit->getGui()); \
	allocated_list_.push_back(edit); \
	return edit; \
}

IMPL_ADD_SLIDER_FUNC(Char, char)
IMPL_ADD_SLIDER_FUNC(UChar, unsigned char)
IMPL_ADD_SLIDER_FUNC(Short, short)
IMPL_ADD_SLIDER_FUNC(UShort, unsigned short)
IMPL_ADD_SLIDER_FUNC(Int, int)
IMPL_ADD_SLIDER_FUNC(UInt, unsigned int)
IMPL_ADD_SLIDER_FUNC(Float, float)
IMPL_ADD_SLIDER_FUNC(Double, double)
IMPL_ADD_TOGGLE_FUNC1(Bool)
IMPL_ADD_TOGGLE_FUNC2(Bool, bool)
IMPL_ADD_TOGGLE_FUNC1(Button)
IMPL_ADD_TOGGLE_FUNC2(Button, bool)

#undef IMPL_ADD_SLIDER_FUNC
#undef IMPL_ADD_TOGGLE_FUNC1
#undef IMPL_ADD_TOGGLE_FUNC2


void ofxParamEdit::addString(string name) {
	ofxGuiString* edit = new ofxGuiString(name);
	current_->add(edit);
	allocated_list_.push_back(edit);
}
