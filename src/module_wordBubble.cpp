#include "module_wordBubble.h"

/*************************************************
 File: module_wordbubble.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: This class has code related to the word bubble interface and functionality. These methods define the truetype font we're loading. verdana.ttf is expected to be in the bin/data/ folder.
 *************************************************/

module_wordBubble::module_wordBubble()
{
	ofTrueTypeFont::setGlobalDpi(72);
	typeFont_ = new ofTrueTypeFont();
	
	if (!typeFont_->isLoaded())
	{
		typeFont_->loadFont("verdana.ttf", 30, true, true, true);
	}
	
	typeFont_->setLineHeight(34.0f);
	typeFont_->setLetterSpacing(1.035);
}

ofTrueTypeFont * module_wordBubble::getString()
{
	return typeFont_;
}