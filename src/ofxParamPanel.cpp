
#include "ofxParamPanel.h"
#include "ofxLabel.h"

ofxParamPanel::ofxParamPanel()
:ofxPanel()
,parent_(NULL)
,current_(this)
,is_open_(false)
{
}

ofxParamPanel::~ofxParamPanel()
{
	while(!allocated_.empty()) {
		delete allocated_.at(0);
		allocated_.erase(allocated_.begin());
	}
}

void ofxParamPanel::add(ofxBaseGui * element)
{
	current_->ofxPanel::add(element);
}

ofxButton* ofxParamPanel::addButton(string name)
{
	ofxButton* button = new ofxButton();
	current_->ofxPanel::add(button->setup(name));
	allocated_.push_back(button);
	return button;
}

ofxParamToggle* ofxParamPanel::addToggle(string name, bool& val)
{
	ofxParamToggle* toggle = new ofxParamToggle(name, val);
	current_->ofxPanel::add(toggle);
	allocated_.push_back(toggle);
	return toggle;
}

ofxLabel* ofxParamPanel::addString(string name)
{
	ofxLabel* label = new ofxLabel();
	current_->ofxPanel::add(label->setup(name, name));
	allocated_.push_back(label);
	return label;
}

void ofxParamPanel::addPanel(string name, ofxParamPanel* panel)
{
	current_->children_.push_back(panel);
	current_->addToggle(name, panel->is_open_);
}

void ofxParamPanel::load()
{
	ofxPanel::load();
	for(vector<ofxParamPanel*>::iterator it = children_.begin(); it != children_.end(); ++it) {
		(*it)->load();
	}
}

void ofxParamPanel::save()
{
	ofDirectory::createDirectory(ofFilePath::getEnclosingDirectory(filename), false, true);
	ofxPanel::save();
	for(vector<ofxParamPanel*>::iterator it = children_.begin(); it != children_.end(); ++it) {
		(*it)->save();
	}
}

void ofxParamPanel::beginGroup(string name)
{
	ofxParamPanel* next = new ofxParamPanel();
	next->setup(current_->name+"/"+name, current_->name+"/"+name+".xml", current_->b.x+current_->b.width, current_->b.y+current_->b.height);
	next->parent_ = current_;
	current_->children_.push_back(next);
	current_->addToggle(name, next->is_open_);
	current_ = next;
}

void ofxParamPanel::endGroup()
{
	current_ = current_->parent_;
}

void ofxParamPanel::draw()
{
	ofxPanel::draw();
	for(vector<ofxParamPanel*>::iterator it = children_.begin(); it != children_.end(); ++it) {
		if((*it)->isOpen()) {
			(*it)->draw();
		}
	}
}

