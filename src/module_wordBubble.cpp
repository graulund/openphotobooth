#include "module_wordBubble.h"

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