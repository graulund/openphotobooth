#include "FilterView.h"

/**
 * Copy Constrcutor. Uses an old View to get the Settings and Initialized
 * a new Filter Class with those settings.
 */
FilterView::FilterView(View * oldView, std::string iconURL, 
	int width, int height) : View(oldView, iconURL, width, height)
{
	// In the filter grid state, we have some different controls.
	buttonLeft_->setVisible(false);
    editorDrop_->setVisible(true);
    editorDrop_->setValue(0);
	
	delete oldView;
}

FilterView::~FilterView()
{
	buttonLeft_->setVisible(true);
	delete editorDrop_;
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
 * Draws the Filter into the Scene. Poisition is given by the index
 * @param textureArr texture with applied filter
 * @param index      [description]
 */
void FilterView::drawFilter(ofTexture * textureArr, int index)
{
	int y = 0;
	for (int i = 0; i < index; i++)
	{
		if (i < 3)
		{
			textureArr[i].draw(((i + 1) * 213), y, 213, 160);
		}
		if (i >= 5)
		{
			y = 320;
			textureArr[i].draw((i * 213) % 639, y, 213, 160);
		}
		else if (i >= 2)
		{
			y = 160;
			textureArr[i].draw((i * 213) % 639, y, 213, 160);
		}
	}
}

void FilterView::drawFilterSelector(int fltrNr)
{
	ofPushStyle();
	ofSetHexColor(0x00B2B2);
	ofNoFill();
	if (fltrNr < 3)
	{
		ofRect((fltrNr * 213), 0, 213, 160);
	}
	if (fltrNr >= 5)
	{
		ofRect((fltrNr * 213) % 639, 320, 213, 160);
	}
	else if (fltrNr >= 2)
	{
		ofRect((fltrNr * 213) % 639, 160, 213, 160);
	}
	ofPopStyle();
}

void FilterView::drawFilter(ofTexture texture, int index)
{
	texture.draw(0, 0, 213, 160);
}
