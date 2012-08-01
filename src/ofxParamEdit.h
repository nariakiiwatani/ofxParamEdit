/******************************************************************/
/**
 * @file	ofxParamEdit.h
 * @brief	This class provides the SIMPLEST interface to edit values with ofxGui.
 * @note
 * @todo
 * @bug		Maybe becouse of ofEvent(or Poco::delegate?) bug, mouse events are incorrect if GUIs were added to Panel.
 *			So I recommend commenting out ofRegisterMouseEvents in ofxSlider.cpp, ofxButton.cpp, and ofxToggle.cpp.
 *
 * @author	nariakiiwatani
 * @date	Jul. 24, 2012
 */
/******************************************************************/

#pragma once

#include "ofxGui.h"
#include "ofxParamEditGroup.h"

class ofxParamEdit
{
public:
	ofxParamEdit();
	ofxParamEdit(string name);
	~ofxParamEdit();

	// between beginGroup and endGroup, controlls are added into the group
	void beginGroup(string name);
	void endGroup();
	// adding controlls
	void addChar(string name, char &value, char min, char max);
	void addUChar(string name, unsigned char &value, unsigned char min, unsigned char max);
	void addShort(string name, short &value, short min, short max);
	void addUShort(string name, unsigned short &value, unsigned short min, unsigned short max);
	void addInt(string name, int &value, int min, int max);
	void addUInt(string name, unsigned int &value, unsigned int min, unsigned int max);
	void addFloat(string name, float &value, float min, float max);
	void addDouble(string name, double &value, double min, double max);
	void addToggle(string name, bool &value) { addBool(name, value); }
	void addBool(string name, bool &value);
	void addButton(string name);
	void addButton(string name, bool &value);
	void addString(string str);
	// adding controlls (with callback)
	template<class ListenerClass>
	void addChar(string name, char &value, char min, char max, ListenerClass * listener, void ( ListenerClass::*method )(int&));
	template<class ListenerClass>
	void addUChar(string name, unsigned char &value, unsigned char min, unsigned char max, ListenerClass * listener, void ( ListenerClass::*method )(int&));
	template<class ListenerClass>
	void addShort(string name, short &value, short min, short max, ListenerClass * listener, void ( ListenerClass::*method )(int&));
	template<class ListenerClass>
	void addUShort(string name, unsigned short &value, unsigned short min, unsigned short max, ListenerClass * listener, void ( ListenerClass::*method )(int&));
	template<class ListenerClass>
	void addInt(string name, int &value, int min, int max, ListenerClass * listener, void ( ListenerClass::*method )(int&));
	template<class ListenerClass>
	void addUInt(string name, unsigned int &value, unsigned int min, unsigned int max, ListenerClass * listener, void ( ListenerClass::*method )(int&));
	template<class ListenerClass>
	void addFloat(string name, float &value, float min, float max, ListenerClass * listener, void ( ListenerClass::*method )(float&));
	template<class ListenerClass>
	void addDouble(string name, double &value, double min, double max, ListenerClass * listener, void ( ListenerClass::*method )(float&));
	template<class ListenerClass>
	void addBool(string name, bool &value, ListenerClass * listener, void ( ListenerClass::*method )(bool&));
	template<class ListenerClass>
	void addToggle(string name, bool &value, ListenerClass * listener, void ( ListenerClass::*method )(bool&));
	template<class ListenerClass>
	void addButton(string name, bool &value, ListenerClass * listener, void ( ListenerClass::*method )(bool&));
	template<class ListenerClass>
	void addButton(string name, ListenerClass * listener, void ( ListenerClass::*method )(bool&));

	void open() { enable_ = true; }
	void close() { enable_ = false; }
	bool isOpen() { return enable_; }

	// select a group to be drawn
	void openGroup(ofxParamEditGroup* group);
	void draw();

private:
	template<typename ParameterType, typename InnerType>
	class ofxParamEditSlider {
	public:
		ofxParamEditSlider(string name, ParameterType& param, ParameterType min, ParameterType max)
		:value_(param) {
			gui_.setup(name, param, min, max);
			gui_.addListener(this, &ofxParamEditSlider::valueChanged);
		}
		ofxSlider<InnerType>* getGui() { return &gui_; }
		template<class ListenerClass>
		void addListener(ListenerClass * listener, void ( ListenerClass::*method )(InnerType&)) {
			ofAddListener(changedE_, listener, method);
		}
	private:
		void valueChanged(InnerType& param) {
			ofNotifyEvent(changedE_, param, this);
			value_ = param;
		}
	private:
		ParameterType& value_;
		ofEvent<InnerType> changedE_;
		ofxSlider<InnerType> gui_;
	};
	typedef ofxParamEditSlider<char, int> ofxParamEditChar;
	typedef ofxParamEditSlider<unsigned char, int> ofxParamEditUChar;
	typedef ofxParamEditSlider<short, int> ofxParamEditShort;
	typedef ofxParamEditSlider<unsigned short, int> ofxParamEditUShort;
	typedef ofxParamEditSlider<int, int> ofxParamEditInt;
	typedef ofxParamEditSlider<unsigned int, int> ofxParamEditUInt;
	typedef ofxParamEditSlider<float, float> ofxParamEditFloat;
	typedef ofxParamEditSlider<double, float> ofxParamEditDouble;

	class ofxParamEditToggle {
	public:
		ofxParamEditToggle(string name, bool& param)
		:value_(param) {
			gui_.setup(name, param);
			gui_.addListener(this, &ofxParamEditToggle::valueChanged);
		}
		ofxToggle* getGui() { return &gui_; }
		template<class ListenerClass>
		void addListener(ListenerClass * listener, void ( ListenerClass::*method )(bool&)) {
			ofAddListener(changedE_, listener, method);
		}
	private:
		void valueChanged(bool& param) {
			ofNotifyEvent(changedE_, param, this);
			value_ = param;
		}
	private:
		bool& value_;
		ofEvent<bool> changedE_;
		ofxToggle gui_;
	};
	typedef ofxParamEditToggle ofxParamEditBool;

	class ofxParamEditButton {
	public:
		ofxParamEditButton(string name)
		:value_(dummy_) {
			gui_.setup(name);
			gui_.addListener(this, &ofxParamEditButton::valueChanged);
		}
		ofxParamEditButton(string name, bool& param)
		:value_(param) {
			gui_.setup(name);
			gui_.addListener(this, &ofxParamEditButton::valueChanged);
		}
		ofxButton* getGui() { return &gui_; }
		template<class ListenerClass>
		void addListener(ListenerClass * listener, void ( ListenerClass::*method )(bool&)) {
			ofAddListener(changedE_, listener, method);
		}
	private:
		void valueChanged(bool& param) {
			ofNotifyEvent(changedE_, param, this);
			value_ = param;
		}
	private:
		bool& value_;
		bool dummy_;
		ofEvent<bool> changedE_;
		ofxButton gui_;
	};

private:
	ofxParamEditChar* _addChar(string name, char &value, char min, char max);
	ofxParamEditUChar* _addUChar(string name, unsigned char &value, unsigned char min, unsigned char max);
	ofxParamEditShort* _addShort(string name, short &value, short min, short max);
	ofxParamEditUShort* _addUShort(string name, unsigned short &value, unsigned short min, unsigned short max);
	ofxParamEditInt* _addInt(string name, int &value, int min, int max);
	ofxParamEditUInt* _addUInt(string name, unsigned int &value, unsigned int min, unsigned int max);
	ofxParamEditFloat* _addFloat(string name, float &value, float min, float max);
	ofxParamEditDouble* _addDouble(string name, double &value, double min, double max);
	ofxParamEditBool* _addBool(string name, bool& value);
	ofxParamEditButton* _addButton(string name);
	ofxParamEditButton* _addButton(string name, bool &value);
private:
	ofxParamEditGroup root_;
	ofxParamEditGroup* current_;
	ofxParamEditGroup* active_;
	vector<void*> allocated_list_;
	bool enable_;
};

/* ======================================
		templates implementation
 ======================================= */
template<class ListenerClass>
void ofxParamEdit::addChar(string name, char &value, char min, char max, ListenerClass * listener, void ( ListenerClass::*method )(int&)) {
	ofxParamEditChar* edit = _addChar(name, value, min, max);
	if(listener && method) {
		edit->addListener(listener, method);
	}
}
template<class ListenerClass>
void ofxParamEdit::addUChar(string name, unsigned char &value, unsigned char min, unsigned char max, ListenerClass * listener, void ( ListenerClass::*method )(int&)) {
	ofxParamEditUChar* edit = _addUChar(name, value, min, max);
	if(listener && method) {
		edit->addListener(listener, method);
	}
}
template<class ListenerClass>
void ofxParamEdit::addShort(string name, short &value, short min, short max, ListenerClass * listener, void ( ListenerClass::*method )(int&)) {
	ofxParamEditShort* edit = _addShort(name, value, min, max);
	if(listener && method) {
		edit->addListener(listener, method);
	}
}
template<class ListenerClass>
void ofxParamEdit::addUShort(string name, unsigned short &value, unsigned short min, unsigned short max, ListenerClass * listener, void ( ListenerClass::*method )(int&)) {
	ofxParamEditUShort* edit = _addUShort(name, value, min, max);
	if(listener && method) {
		edit->addListener(listener, method);
	}
}
template<class ListenerClass>
void ofxParamEdit::addInt(string name, int &value, int min, int max, ListenerClass * listener, void ( ListenerClass::*method )(int&)) {
	ofxParamEditInt* edit = _addInt(name, value, min, max);
	if(listener && method) {
		edit->addListener(listener, method);
	}
}
template<class ListenerClass>
void ofxParamEdit::addUInt(string name, unsigned int &value, unsigned int min, unsigned int max, ListenerClass * listener, void ( ListenerClass::*method )(int&)) {
	ofxParamEditUInt* edit = _addUInt(name, value, min, max);
	if(listener && method) {
		edit->addListener(listener, method);
	}
}
template<class ListenerClass>
void ofxParamEdit::addFloat(string name, float &value, float min, float max, ListenerClass * listener, void ( ListenerClass::*method )(float&)) {
	ofxParamEditFloat* edit = _addFloat(name, value, min, max);
	if(listener && method) {
		edit->addListener(listener, method);
	}
}
template<class ListenerClass>
void ofxParamEdit::addDouble(string name, double &value, double min, double max, ListenerClass * listener, void ( ListenerClass::*method )(float&)) {
	ofxParamEditDouble* edit = _addDouble(name, value, min, max);
	if(listener && method) {
		edit->addListener(listener, method);
	}
}
template<class ListenerClass>
void ofxParamEdit::addBool(string name, bool &value, ListenerClass * listener, void ( ListenerClass::*method )(bool&)) {
	ofxParamEditBool* edit = _addBool(name, value);
	if(listener && method) {
		edit->addListener(listener, method);
	}
}
template<class ListenerClass>
void ofxParamEdit::addToggle(string name, bool &value, ListenerClass * listener, void ( ListenerClass::*method )(bool&)) {
	addBool(name, value, listener, method);
}
template<class ListenerClass>
void ofxParamEdit::addButton(string name, ListenerClass * listener, void ( ListenerClass::*method )(bool&)) {
	ofxParamEditButton* edit = _addButton(name);
	if(listener && method) {
		edit->addListener(listener, method);
	}
}
template<class ListenerClass>
void ofxParamEdit::addButton(string name, bool &value, ListenerClass * listener, void ( ListenerClass::*method )(bool&)) {
	ofxParamEditButton* edit = _addButton(name, value);
	if(listener && method) {
		edit->addListener(listener, method);
	}
}

