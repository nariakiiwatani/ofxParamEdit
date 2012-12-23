
#include "ofxParamPanel.h"
#include "ofxParamToggle.h"

ofxParamPanel::ofxParamPanel()
:ofxPanel()
,parent_(NULL)
,current_(this)
,is_open_(true)
{
}

void ofxParamPanel::add(ofxBaseGui * element)
{
	current_->ofxPanel::add(element);
}

void ofxParamPanel::add(string name, bool& val)
{
	current_->ofxPanel::add(new ofxParamToggle(name, val));
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
	current_->add(">"+name, next->is_open_);
	current_ = next;
}

void ofxParamPanel::endGroup()
{
	current_ = current_->parent_;
}

void ofxParamPanel::draw()
{
	if(is_open_) {
		ofxPanel::draw();
		for(vector<ofxParamPanel*>::iterator it = children_.begin(); it != children_.end(); ++it) {
			(*it)->draw();
		}
	}
}

