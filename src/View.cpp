#include "View.h"
#include "Controller.h"

View::View(std::string iconURL, int width, int height, ofxUICanvas * canvas)
{
	init(iconURL, width, height, canvas);
}

View::View(View * oldView, std::string iconURL, int width, int height)
{
	buttonLeft_ = oldView->buttonLeft_;
	buttonRight_ = oldView->buttonRight_;
	buttonCenter_ = oldView->buttonCenter_;
	buttonDrop_ = oldView->buttonDrop_;

	buttonLeft_->setVisible(true);
	buttonLeft_->setValue(0);
	buttonDrop_->setVisible(false);
	buttonRight_->setValue(0);

	// init(iconURL, width, height, false);
}

void View::init(std::string iconURL, int width, int height, ofxUICanvas * canvas)
{
	buttonLeft_ = new ofxUILabelToggle(
		"BUTTON_LEFT", false, 100, 32, 8, 8, OFX_UI_FONT_MEDIUM);
	buttonCenter_ = new ofxUIImageButton(
		304, 8, 32, 32, false, iconURL, "BUTTON_CENT");
	actButtonCenter_ = new ofxUILabelButton("BUTTON_ACTCENT", false);
	buttonRight_ = new ofxUILabelToggle(
		"BUTTON_RIGHT", false, 100, 32, 532, 8, OFX_UI_FONT_MEDIUM);
    
    buttonItems_.push_back("Facebook");
    buttonItems_.push_back("Save");
    buttonDrop_ = new ofxUIDropDownList("Publish", buttonItems_, 100, 8, 8);
	
	// Filter editor drop down
	editorItems_.push_back("Create Filter");
	editorItems_.push_back("Load Filter");
	editorDrop_ = new ofxUIDropDownList("Editor", editorItems_, 100, 8, 8);
	
	canvas->addWidget(buttonLeft_);
	canvas->addWidget(buttonCenter_);
	canvas->addWidget(actButtonCenter_);
	canvas->addWidget(buttonRight_);
	canvas->addWidget(buttonDrop_);

	buttonDrop_->setVisible(false);
	buttonDrop_->setName("PREVBTN_L_D");
	
	editorDrop_->setVisible(false);
	editorDrop_->setName("EDITORDROP");
	
	actButtonCenter_->setVisible(false);
}

/**
 * Draws a given Video Grabber
 * @param vidGrabber Video Grabber which should be drawn to this View
 */
void View::drawVideoGrabber(ofVideoGrabber * vidGrabber, 
	float w, float h)
{
	vidGrabber->draw(0, 0, w, h);
}

/**
 * Draws a given Thumbnail array
 * @param thumbArr array of Thumbnail
 * @param imgIndx  current maximal image Index
 * @param imgCnt   current maximal image Count
 */
void View::drawThumbnails(ofImage * thumbArr, int imgIndx, int imgCnt)
{
	if (imgCnt > 0)
	{
		ofPushStyle();
		ofSetRectMode(OF_RECTMODE_CENTER);
		for (int i = 0; i < imgCnt; i++)
		{
			thumbArr[i].draw(70 + (125 * i), 614, 100, 100);
		}
		ofPopStyle();
	}
}

/**
 * Draw the Thumbnail Selector dependent of the given Int. If there is
 * less then two Thumbnails, no Selector will drawn.
 * @param imgNbr number of selected Thumbnail
 */
void View::drawThumbnailSelector(int imgNbr)
{
	if (imgNbr > 0)
	{
		ofPushStyle();
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofSetHexColor(0x00B2B2);
		ofNoFill();
		ofRect(70 + (125 * (imgNbr-1)), 614, 100, 100);
		ofPopStyle();
	}
}

/**
 * Set the Label of the Button. Select the button via a given Int.
 * @param btnNbr number of Button. One = Left, Two = Right
 * @param btnLbl label of the Button.
 */
void View::setButtonLabel(int btnNbr, std::string btnLbl)
{
	if (btnNbr == 1)
	{
		buttonLeft_->setLabelText(btnLbl);
	}
	else if (btnNbr == 2)
	{
		buttonRight_->setLabelText(btnLbl);
	}
}

void View::clearButtonStatus(int btnNbr)
{
	if (btnNbr == 1)
	{
		buttonLeft_->setValue(0);
	}
	else if (btnNbr == 2)
	{
		buttonRight_->setValue(0);
	}
	else if (btnNbr == 3)
	{
		buttonCenter_->setValue(0);
	}
}

void View::setButtonName(int btnNbr, std::string btnLbl)
{
	if (btnNbr == 1)
	{
		buttonLeft_->setName(btnLbl);
	}
	else if (btnNbr == 2)
	{
		buttonRight_->setName(btnLbl);
	}
	else if (btnNbr == 3)
	{
		buttonCenter_->setName(btnLbl);
	}
}

void View::drawFilter(ofTexture texture)
{
	texture.draw(0, 0, 640, 480);
}
