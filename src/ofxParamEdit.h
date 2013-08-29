#pragma once

#include "ofxParamPanel.h"
#include "ofxParamSlider.h"
#include "ofxParamToggle.h"

class ofxLabel;
class ofxParamEdit
{
public:
	ofxParamEdit();
	~ofxParamEdit();

	void setup(string name, float x = 10, float y = 10);
	
	void addButton(string name);
	void addToggle(string name, bool& val);
	template<typename Type>
	void addSlider(string name, Type& val, Type min, Type max);
	void addLabel(string name);

	void beginGroup(string name, bool panel=true);
	void endGroup();
	void draw();
	
	template<class ListenerClass, typename ListenerMethod>
	void addButton(string name, ListenerClass *listener, ListenerMethod method);

	template<class ListenerClass, typename ListenerMethod>
	void addToggle(string name, ListenerClass *listener, ListenerMethod method);
	template<class ListenerClass, typename ListenerMethod>
	void addToggle(string name, bool& val, ListenerClass *listener, ListenerMethod method);
	
	template<typename Type, class ListenerClass, typename ListenerMethod>
	void addSlider(string name, Type min, Type max, ListenerClass *listener, ListenerMethod method);
	template<typename Type, class ListenerClass, typename ListenerMethod>
	void addSlider(string name, Type& val, Type min, Type max, ListenerClass *listener, ListenerMethod method);

	void load();
	void save();
	
	void open() { root_.open(); }
	void close() { root_.close(); }
	bool isOpen() { return root_.isOpen(); }

private:
	template<typename Type>
	ofxParamSlider<Type>* createSlider(string name, Type min, Type max);
	ofxButton* createButton(string name);
	ofxParamToggle* createToggle(string name);
	ofxLabel* createLabel(string name);
	
	ofxParamPanel root_;
	vector<ofxGuiGroup*> stack_;
	string getCurrentFolderName();

	vector<ofxParamPanel*> panels_;
	vector<ofxBaseGui*> allocated_;
};

template<typename Type>
ofxParamSlider<Type>* ofxParamEdit::createSlider(string name, Type min, Type max)
{
	ofxGuiGroup *current = stack_.back();
	ofxParamSlider<Type>* slider = new ofxParamSlider<Type>(name, min, max);
	current->add(slider);
	allocated_.push_back(slider);
	return slider;
}

template<typename Type>
void ofxParamEdit::addSlider(string name, Type& val, Type min, Type max)
{
	ofxParamSlider<Type>* slider = createSlider(name, min, max);
	slider->setReference(val);
}

template<typename Type, class ListenerClass, typename ListenerMethod>
void ofxParamEdit::addSlider(string name, Type min, Type max, ListenerClass *listener, ListenerMethod method)
{
	ofxParamSlider<Type>* slider = createSlider(name, min, max);
	slider->addListener(listener, method);
}

template<typename Type, class ListenerClass, typename ListenerMethod>
void ofxParamEdit::addSlider(string name, Type& val, Type min, Type max, ListenerClass *listener, ListenerMethod method)
{
	ofxParamSlider<Type>* slider = createSlider(name, min, max);
	slider->setReference(val);
	slider->addListener(listener, method);
}

template<class ListenerClass, typename ListenerMethod>
void ofxParamEdit::addButton(string name, ListenerClass *listener, ListenerMethod method)
{
	ofxButton* button = createButton(name);
	button->addListener(listener, method);
}
template<class ListenerClass, typename ListenerMethod>
void ofxParamEdit::addToggle(string name, ListenerClass *listener, ListenerMethod method)
{
	ofxParamToggle* toggle = createToggle(name);
	toggle->addListener(listener, method);
}
template<class ListenerClass, typename ListenerMethod>
void ofxParamEdit::addToggle(string name, bool& val, ListenerClass *listener, ListenerMethod method)
{
	ofxParamToggle* toggle = createToggle(name);
	toggle->setReference(val);
	toggle->addListener(listener, method);
}

/* EOF */