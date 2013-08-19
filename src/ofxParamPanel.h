#pragma once

#include "ofxPanel.h"

class ofxLabel;
class ofxParamPanel : public ofxPanel
{
	friend class ofxParamEdit;
public:
	ofxParamPanel();
	~ofxParamPanel();
	
	void load();
	void save();

	bool isOpen() { return is_open_; }
	void open() { is_open_ = true; }
	void close() { is_open_ = false; }
private:
	bool is_open_;
};

/* EOF */