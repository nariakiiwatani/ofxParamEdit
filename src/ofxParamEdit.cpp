
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

void ofxParamEdit::setup(const string& name, float x, float y)
{
	root_.setup(name, name+".xml", x, y);
	root_.open();
}

ofxButton* ofxParamEdit::createButton(const string& name)
{
	ofxGuiGroup *current = stack_.back();
	ofxButton* button = new ofxButton();
	current->add(button->setup(name));
	allocated_.push_back(button);
	return button;
}

ofxParamToggle* ofxParamEdit::createToggle(const string& name)
{
	ofxGuiGroup *current = stack_.back();
	ofxParamToggle* toggle = new ofxParamToggle(name);
	current->add(toggle);
	allocated_.push_back(toggle);
	return toggle;
}

void ofxParamEdit::addToggle(const string& name, bool& val)
{
	ofxParamToggle* toggle = createToggle(name);
	toggle->setReference(val);
}

ofxLabel* ofxParamEdit::createLabel(const string& name)
{
	ofxGuiGroup *current = stack_.back();
	ofxLabel* label = new ofxLabel(name);
	current->add(label);
	allocated_.push_back(label);
	return label;
}

void ofxParamEdit::addLabel(const string& name)
{
	createLabel(name);
}

void ofxParamEdit::add(ofxBaseGui *gui)
{
	stack_.back()->add(gui);
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

void ofxParamEdit::beginGroup(const string& name, bool as_panel)
{
	ofxGuiGroup *parent = stack_.back();
	ofxGuiGroup *next = as_panel ? createPanel(name, parent) : createGroup(name, parent);
	groups_.push_back(next);
}

void ofxParamEdit::beginExistingGroup(const string& name, int index)
{
	ofxGuiGroup *group = getGroup(name, index);
	if(group) {
		stack_.push_back(group);
	}
	else {
		ofLog(OF_LOG_WARNING, "group "+name+" does not exist. creating new.");
		beginGroup(name);
	}
}

ofxParamPanel* ofxParamEdit::createPanel(const string& name, ofxGuiGroup *parent)
{
	ofxParamPanel *panel = new ofxParamPanel();
	const ofRectangle& b = parent->getShape();
	panel->setup(name, getCurrentFolderName()+name+".xml");
	panel->setPosition(b.x+b.width, b.y+b.height);
	panels_.push_back(panel);
	addToggle(name, panel->is_open_);
	allocated_.push_back(panel);
	
	stack_.push_back(panel);
	addButton(">back", panel, &ofxParamPanel::close);

	return panel;
}

ofxGuiGroup* ofxParamEdit::createGroup(const string& name, ofxGuiGroup *parent)
{
	ofxGuiGroup *group = new ofxGuiGroup();
	group->setup(name, getCurrentFolderName()+name+".xml");
	parent->add(group);
	allocated_.push_back(group);
	stack_.push_back(group);
	return group;
}

ofxGuiGroup* ofxParamEdit::getGroup(const string& name, int index)
{
	for(vector<ofxGuiGroup*>::iterator group = groups_.begin(); group != groups_.end(); ++group) {
		if((*group)->getName() == name) {
			if(--index < 0) {
				return *group;
			}
		}
	}
	return NULL;
}

string ofxParamEdit::getCurrentFolderName()
{
	string folder = "";
	for(vector<ofxGuiGroup*>::iterator it = stack_.begin(); it != stack_.end(); ++it) {
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