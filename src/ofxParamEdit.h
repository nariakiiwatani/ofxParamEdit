#pragma once

#include "ofxParamPanel.h"
#include "ofxParamSlider.h"
#include "ofxParamToggle.h"
#include "ofxParamVecSlider.h"
#include "ofxParamColorSlider.h"

class ofxLabel;
class ofxParamEdit
{
public:
	ofxParamEdit();
	~ofxParamEdit();

	void setup(const string& name, float x = 10, float y = 10);
	void draw();
	
	void open() { root_.open(); }
	void close() { root_.close(); }
	bool isOpen() { return root_.isOpen(); }	
	void setOpen(bool set) { set?open():close(); }
	void toggleOpen() { isOpen()?close():open(); }

	// adding vars
	void addLabel(const string& name);
//	void addButton(const string& name);	// useless
	void addToggle(const string& name, bool& val);
	template<typename Type>
	void addSlider(const string& name, Type& val, Type min, Type max);
	template<typename Type>
	void addVecSlider(const string& name, Type& val, const Type& min, const Type& max);
	template<typename Type>
	void addColorSlider(const string& name, ofColor_<Type>& val, const ofColor_<Type>& min, const ofColor_<Type>& max);

	// adding vars with callback
	template<class ListenerClass, typename ListenerMethod>
	void addButton(const string& name, ListenerClass *listener, ListenerMethod method);

	template<class ListenerClass, typename ListenerMethod>
	void addToggle(const string& name, ListenerClass *listener, ListenerMethod method);
	template<class ListenerClass, typename ListenerMethod>
	void addToggle(const string& name, bool& val, ListenerClass *listener, ListenerMethod method);
	
	template<typename Type, class ListenerClass, typename ListenerMethod>
	void addSlider(const string& name, Type min, Type max, ListenerClass *listener, ListenerMethod method);
	template<typename Type, class ListenerClass, typename ListenerMethod>
	void addSlider(const string& name, Type& val, Type min, Type max, ListenerClass *listener, ListenerMethod method);
	
	template<typename Type, class ListenerClass, typename ListenerMethod>
	void addVecSlider(const string& name, const Type& min, const Type& max, ListenerClass *listener, ListenerMethod method);
	template<typename Type, class ListenerClass, typename ListenerMethod>
	void addVecSlider(const string& name, Type& val, const Type& min, const Type& max, ListenerClass *listener, ListenerMethod method);

	template<typename Type, class ListenerClass, typename ListenerMethod>
	void addColorSlider(const string& name, const ofColor_<Type>& min, const ofColor_<Type>& max, ListenerClass *listener, ListenerMethod method);
	template<typename Type, class ListenerClass, typename ListenerMethod>
	void addColorSlider(const string& name, ofColor_<Type>& val, const ofColor_<Type>& min, const ofColor_<Type>& max, ListenerClass *listener, ListenerMethod method);

	// adding something
	void add(ofxBaseGui *gui);
	
	// file io
	void load();
	void save();
	
	// grouping
	void beginGroup(const string& name, bool as_panel=true);
	void beginExistingGroup(const string& name, int index=0);
	void endGroup();

private:
	template<typename Type>
	ofxParamSlider<Type>* createSlider(const string& name, Type min, Type max);
	template<typename Type>
	ofxParamVecSlider<Type>* createVecSlider(const string& name, const Type& min, const Type& max);
	template<typename Type>
	ofxParamColorSlider<Type>* createColorSlider(const string& name, const ofColor_<Type>& min, const ofColor_<Type>& max);
	ofxButton* createButton(const string& name);
	ofxParamToggle* createToggle(const string& name);
	ofxLabel* createLabel(const string& name);
	ofxGuiGroup* getGroup(const string& name, int index);
	ofxParamPanel* createPanel(const string& name, ofxGuiGroup *parent);
	ofxGuiGroup* createGroup(const string& name, ofxGuiGroup *parent);
private:
	ofxParamPanel root_;
	vector<ofxGuiGroup*> stack_;
	string getCurrentFolderName();

	vector<ofxParamPanel*> panels_;
	vector<ofxGuiGroup*> groups_;
	vector<ofxBaseGui*> allocated_;
};


template<class ListenerClass, typename ListenerMethod>
void ofxParamEdit::addButton(const string& name, ListenerClass *listener, ListenerMethod method)
{
	ofxButton* button = createButton(name);
	button->addListener(listener, method);
}
template<class ListenerClass, typename ListenerMethod>
void ofxParamEdit::addToggle(const string& name, ListenerClass *listener, ListenerMethod method)
{
	ofxParamToggle* toggle = createToggle(name);
	toggle->addListener(listener, method);
}
template<class ListenerClass, typename ListenerMethod>
void ofxParamEdit::addToggle(const string& name, bool& val, ListenerClass *listener, ListenerMethod method)
{
	ofxParamToggle* toggle = createToggle(name);
	toggle->setReference(val);
	toggle->addListener(listener, method);
}


template<typename Type>
ofxParamSlider<Type>* ofxParamEdit::createSlider(const string& name, Type min, Type max)
{
	ofxGuiGroup *current = stack_.back();
	ofxParamSlider<Type>* slider = new ofxParamSlider<Type>(name, min, max);
	current->add(slider);
	allocated_.push_back(slider);
	return slider;
}

template<typename Type>
ofxParamVecSlider<Type>* ofxParamEdit::createVecSlider(const string& name, const Type& min, const Type& max)
{
	ofxGuiGroup *current = stack_.back();
	ofxParamVecSlider<Type>* slider = new ofxParamVecSlider<Type>(name, min, max);
	current->add(slider);
	allocated_.push_back(slider);
	return slider;
}

template<typename Type>
ofxParamColorSlider<Type>* ofxParamEdit::createColorSlider(const string& name, const ofColor_<Type>& min, const ofColor_<Type>& max)
{
	ofxGuiGroup *current = stack_.back();
	ofxParamColorSlider<Type>* slider = new ofxParamColorSlider<Type>(name, min, max);
	current->add(slider);
	allocated_.push_back(slider);
	return slider;
}

template<typename Type>
void ofxParamEdit::addSlider(const string& name, Type& val, Type min, Type max)
{
	ofxParamSlider<Type>* slider = createSlider(name, min, max);
	slider->setReference(val);
}

template<typename Type, class ListenerClass, typename ListenerMethod>
void ofxParamEdit::addSlider(const string& name, Type min, Type max, ListenerClass *listener, ListenerMethod method)
{
	ofxParamSlider<Type>* slider = createSlider(name, min, max);
	slider->addListener(listener, method);
}

template<typename Type, class ListenerClass, typename ListenerMethod>
void ofxParamEdit::addSlider(const string& name, Type& val, Type min, Type max, ListenerClass *listener, ListenerMethod method)
{
	ofxParamSlider<Type>* slider = createSlider(name, min, max);
	slider->setReference(val);
	slider->addListener(listener, method);
}

template<typename Type>
void ofxParamEdit::addVecSlider(const string& name, Type& val, const Type& min, const Type& max)
{
	ofxParamVecSlider<Type>* slider = createVecSlider(name, min, max);
	slider->setReference(val);
}

template<typename Type, class ListenerClass, typename ListenerMethod>
void ofxParamEdit::addVecSlider(const string& name, const Type& min, const Type& max, ListenerClass *listener, ListenerMethod method)
{
	ofxParamVecSlider<Type>* slider = createVecSlider(name, min, max);
	slider->addListener(listener, method);
}

template<typename Type, class ListenerClass, typename ListenerMethod>
void ofxParamEdit::addVecSlider(const string& name, Type& val, const Type& min, const Type& max, ListenerClass *listener, ListenerMethod method)
{
	ofxParamVecSlider<Type>* slider = createVecSlider(name, min, max);
	slider->setReference(val);
	slider->addListener(listener, method);
}

template<typename Type>
void ofxParamEdit::addColorSlider(const string& name, ofColor_<Type>& val, const ofColor_<Type>& min, const ofColor_<Type>& max)
{
	ofxParamColorSlider<Type>* slider = createColorSlider(name, min, max);
	slider->setReference(val);
}

template<typename Type, class ListenerClass, typename ListenerMethod>
void ofxParamEdit::addColorSlider(const string& name, const ofColor_<Type>& min, const ofColor_<Type>& max, ListenerClass *listener, ListenerMethod method)
{
	ofxParamColorSlider<Type>* slider = createColorSlider(name, min, max);
	slider->addListener(listener, method);
}

template<typename Type, class ListenerClass, typename ListenerMethod>
void ofxParamEdit::addColorSlider(const string& name, ofColor_<Type>& val, const ofColor_<Type>& min, const ofColor_<Type>& max, ListenerClass *listener, ListenerMethod method)
{
	ofxParamColorSlider<Type>* slider = createColorSlider(name, min, max);
	slider->setReference(val);
	slider->addListener(listener, method);
}


/* EOF */