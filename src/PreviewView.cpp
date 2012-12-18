/*************************************************
 File: PreviewView.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: Follows the MVC/Mediator Pattern. It does hold all the 
 Style Elements for the Scene. Gets the Data injected form the 
 Controller. Unlikely other MVCs it holds the Buttons it self. This is
 due a characteristic from ofxUI. Nothing new expect the drawWordBubble
 *************************************************/

#include "PreviewView.h"

PreviewView::PreviewView(View * oldView, std::string iconURL,
	int width, int height, ofxUICanvas * canvas)
	: View(oldView, iconURL, width, height)
{
	// In the taken image state, we have some different controls.
    buttonLeft_->setVisible(false);
    buttonDrop_->setVisible(true);
    buttonDrop_->setValue(0);
    
	delete oldView;
}

PreviewView::~PreviewView()
{
	buttonLeft_->setVisible(true);
	delete buttonDrop_;
}

void PreviewView::drawPreview(ofTexture newPreview)
{
	newPreview.draw(0, 0);
}

void PreviewView::drawWordBubble(std::string * theText, 
	ofTrueTypeFont * wordBubble, int x, int y)
{
	wordBubble->drawStringAsShapes(*theText, 
		x - (wordBubble->stringWidth(*theText)/2), y);
}
