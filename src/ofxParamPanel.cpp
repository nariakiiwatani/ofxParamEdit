
#include "ofxParamPanel.h"
ofxParamPanel::ofxParamPanel()
{
	is_open_ = false;
}

ofxParamPanel::~ofxParamPanel()
{
}

void ofxParamPanel::load()
{
	loadFromFile(filename);
}

void ofxParamPanel::save()
{
	ofDirectory::createDirectory(ofFilePath::getEnclosingDirectory(filename), false, true);
	saveToFile(filename);
}

/* EOF */