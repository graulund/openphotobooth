/*************************************************
 File: PreviewModel.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: Follows the MVC/Mediator Pattern. It does hold all the 
 Data and Business logic. Called from the Controller. Model derived from
 the Main Model. The only new Operation is to edit the Word Bubble string
 *************************************************/

#include "PreviewModel.h"

PreviewModel::PreviewModel(Model * oldModel) : Model(oldModel, true)
{
	wordBubble_ = new module_wordBubble();
	wordBubbleStr_ = new string("Enter Text Here");
	
	bFirst_ = true;
	showBubble_ = false;
	init();
}

/**
 * Initializer method to set the Button Names and Labels
 */
void PreviewModel::init()
{
	btnLabelL_ = BTN_LABL_L;
	btnLabelM_ = BTN_LABL_M;
	btnLabelR_ = BTN_LABL_R;	

	btnNameL_ = BTN_NAME_L;
	btnNameM_ = BTN_NAME_M;
	btnNameR_ = BTN_NAME_R;
}

ofTrueTypeFont * PreviewModel::getWordBubble()
{
	return wordBubble_->getString();
}

std::string * PreviewModel::getWordBubbleStr()
{
	return wordBubbleStr_;
}

void PreviewModel::setWordBubblePos(int x, int y)
{
	wrdBblX_ = x;
	wrdBblY_ = y;
}

void PreviewModel::editBubbleString(int key)
{
	if (showBubble_)
	{
		std::string * typeStr = wordBubbleStr_;

		if (key == OF_KEY_DEL || key == OF_KEY_BACKSPACE)
		{
			*typeStr = typeStr->substr(0, typeStr->length() - 1);
		}
		else if (key == OF_KEY_RETURN)
		{
			*typeStr += "\n";
		}
		else
		{
			if (isFirstLetter())
			{
				typeStr->clear();
				setFirstLetter(false);
			}
			typeStr->append(1, (char)key);
		}
	}
}

void PreviewModel::showWordBubble(bool showBubble)
{
	showBubble_ = showBubble;
}

bool PreviewModel::isBubbleVisible()
{
	return showBubble_;
}

int PreviewModel::getWordBubbleX()
{
	return wrdBblX_;
}

int PreviewModel::getWordBubbleY()
{
	return wrdBblY_;
}

bool PreviewModel::isFirstLetter()
{
	return bFirst_;
}

void PreviewModel::setFirstLetter(bool firstLetter)
{
	bFirst_ = firstLetter;
}

