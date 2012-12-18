#include "FilterView.h"

/*************************************************
 File: FilterView.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: The view for the filter grid state. This class (which is a part of the MVC paradigm) determines how the filter grid state looks in terms of live thumbnails, filter name overlays and selection rectangles.
 *************************************************/

/**
 * Copy Constrcutor. Uses an old View to get the Settings and Initialized
 * a new Filter Class with those settings.
 */
FilterView::FilterView(View * oldView, std::string iconURL, 
	int width, int height, int offset) : View(oldView, iconURL, width, height), filterOffset_(offset)
{
	// In the filter grid state, we have some different controls.
	buttonLeft_->setVisible(false);
	buttonCenter_->setVisible(false);
    editorDrop_->setVisible(true);
    editorDrop_->setValue(0);
	
	actButtonCenter_->setLabelText("Apply");
	actButtonCenter_->setValue(0);
	actButtonCenter_->setVisible(true);
	
	delete oldView;
	
	// Font for filter name display
	ofTrueTypeFont::setGlobalDpi(72);
	typeFont_ = new ofTrueTypeFont();
	
	if (!typeFont_->isLoaded())
	{
		typeFont_->loadFont("verdana.ttf", 14, true, true, true);
	}
	
	typeFont_->setLineHeight(16.0f);
	typeFont_->setLetterSpacing(1.035);
}

FilterView::~FilterView()
{
	buttonLeft_->setVisible(true);
	buttonCenter_->setVisible(true);
	editorDrop_->setVisible(false);
	actButtonCenter_->setVisible(false);
	actButtonCenter_->setValue(0);
	delete editorDrop_;
	delete actButtonCenter_;
}

/**
 * Draws a given Video Grabber
 * @param vidGrabber Video Grabber which should be drawn to this View
 */
void FilterView::drawVideoGrabber(ofVideoGrabber * vidGrabber,
	float w, float h)
{
	vidGrabber->draw(0, 0, w, h);
}

/**
 * Draws the Filter thumbnails on the Scene
 * @param textureArr texture with applied filter
 * @param index      the amount of filters being drawn
 */
void FilterView::drawFilter(ofTexture * textureArr, std::string * names, int index)
{
	int x = 0, y = 0, w = FILTER_VIEW_CAM_WIDTH, h = FILTER_VIEW_CAM_HEIGHT;
	int cols = 3, filters = 8, di = 0;
	
	for (int i = 0; i < index; i++)
	{
		// Position according to number in vector, skipping front/center.
		di = (i >= filters/2) ? i+1 : i;
		x  = (di % cols) * w;
		y  = (int)std::floor(((float)di)/((float)cols)) * h;
		// Draw!
		textureArr[i].draw(x, y, w, h);
		ofSetHexColor(0);
		typeFont_->drawString(names[i], x + 15, y + h - 14);
		ofSetHexColor(0xFFFFFF);
		typeFont_->drawString(names[i], x + 15, y + h - 15);
	}
}

void FilterView::drawFilterSelector(int fltrNr)
{
	ofPushStyle();
	ofSetHexColor(0xFFFFFF);
	ofNoFill();
	int di = 0, filters = 8, cols = 3,
		x = 0, y = 0, w = FILTER_VIEW_CAM_WIDTH, h = FILTER_VIEW_CAM_HEIGHT;
	if(fltrNr == 0){
		// Non-filter view
		x = w; y = h;
	} else {
		// Calculate table coordinates of filter on screen
		fltrNr = fltrNr - filterOffset_;
		di = (fltrNr > filters/2) ? fltrNr : fltrNr-1;
		
		// Do not draw if we're off screen
		if (di > FILTER_PAGE_LENGTH) {
			return;
		}
		
		// Calculate pixel coordinates
		x  = (di % cols) * w;
		y  = (int)std::floor(((float)di)/((float)cols)) * h;
	}
	// Draw several to simulate a thicker border
	ofRect(x, y, w, h); // 1px border
	ofRect(x+1, y+1, w-2, h-2); // 2px border
	ofRect(x+2, y+2, w-4, h-4); // 3px border
	ofRect(x+3, y+3, w-6, h-6); // 4px border!!!
	
	ofPopStyle();
}

/*void FilterView::drawFilter(ofTexture texture, int index)
{
	texture.draw(0, 0, 213, 160);
}*/
