#include "PreviewView.h"

PreviewView::PreviewView(View * oldView, std::string iconURL,
	int width, int height) : View(oldView, iconURL, width, height)
{
	delete oldView;
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
