#include "PreviewView.h"

PreviewView::PreviewView(View * oldView, std::string iconURL,
	int width, int height, ofxUICanvas * canvas)
	: View(oldView, iconURL, width, height)
{   
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
