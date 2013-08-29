
#include "ofxParamEdit.h"
#include "ofxLabel.h"

ofxParamEdit::ofxParamEdit()
{
	panels_.push_back(&root_);
	stack_.push_back(&root_);
}

ofxParamEdit::~ofxParamEdit()
{
	while(!allocated_.empty()) {
		delete allocated_.at(0);
		allocated_.erase(allocated_.begin());
	}
}

void ofxParamEdit::setup(string name, float x, float y)
{
	root_.setup(name, name+".xml", x, y);
}

ofxButton* ofxParamEdit::createButton(string name)
{
	ofxGuiGroup *current = stack_.back();
	ofxButton* button = new ofxButton();
	current->add(button->setup(name));
	allocated_.push_back(button);
	return button;
}

ofxParamToggle* ofxParamEdit::createToggle(string name)
{
	ofxGuiGroup *current = stack_.back();
	ofxParamToggle* toggle = new ofxParamToggle(name);
	current->add(toggle);
	allocated_.push_back(toggle);
	return toggle;
}

void ofxParamEdit::addToggle(string name, bool& val)
{
	ofxParamToggle* toggle = createToggle(name);
	toggle->setReference(val);
}

ofxLabel* ofxParamEdit::createLabel(string name)
{
	ofxGuiGroup *current = stack_.back();
	ofxLabel* label = new ofxLabel(name);
	current->add(label);
	allocated_.push_back(label);
	return label;
}

void ofxParamEdit::addLabel(string name)
{
	createLabel(name);
}

void ofxParamEdit::load()
{
	for(vector<ofxParamPanel*>::iterator it = panels_.begin(); it != panels_.end(); ++it) {
		(*it)->load();
	}
}

void ofxParamEdit::save()
{
	for(vector<ofxParamPanel*>::iterator it = panels_.begin(); it != panels_.end(); ++it) {
		(*it)->save();
	}
}

void ofxParamEdit::beginGroup(string name, bool panel)
{
	ofxGuiGroup *group = stack_.back();
	if(panel) {
		ofxParamPanel* next = new ofxParamPanel();
		const ofRectangle& b = group->getShape();
		next->setup(name, getCurrentFolderName()+name+".xml");
		next->setPosition(b.x+b.width, b.y+b.height);
		panels_.push_back(next);
		addToggle(name, next->is_open_);
		stack_.push_back(next);
		addButton(">back", next, &ofxParamPanel::close);
		allocated_.push_back(next);
	}
	else {
		ofxGuiGroup *next = new ofxGuiGroup();
		next->setup(name, getCurrentFolderName()+name+".xml");
		group->add(next);
		stack_.push_back(next);
	}
}

string ofxParamEdit::getCurrentFolderName()
{
	string folder = "";
	for(vector<ofxParamPanel*>::iterator it = panels_.begin(); it != panels_.end(); ++it) {
		if(ofxParamPanel *p = dynamic_cast<ofxParamPanel*>(*it)) {
			folder += p->getName()+"/";
		}
	}
	return folder;
}

void ofxParamEdit::endGroup()
{
	stack_.pop_back();
}

void ofxParamEdit::draw()
{
	for(vector<ofxParamPanel*>::iterator it = panels_.begin(); it != panels_.end(); ++it) {
		if((*it)->isOpen()) {
			(*it)->draw();
		}
	}
}

/* EOF */