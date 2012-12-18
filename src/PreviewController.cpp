/*************************************************
 File: PreviewController.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: Controller for the Preview/state. Holds the Required 
 models as a Reference. derived from the Main Controller. Adds specidif
 Methods needed for the Preview.
 *************************************************/

#include "PreviewController.h"

/**
 * Copy Constructor to grep the Model and View from the Old Controller
 */
PreviewController::PreviewController(Controller * oldController) :
	Controller(oldController)
{
	model_ = new PreviewModel(oldController->getModel());
	view_ = new PreviewView(oldController->getView(), model_->getIconURL(), 
		model_->getCamWidth(), model_->getCamHeight(), canvas_);

	initName();

	delete oldController;
}

/**
 * Greps all the things needed for the State out of the Current Model
 * then calls the required Methods in the View to draw it to the scene
 */
void PreviewController::draw()
{
	static_cast<PreviewView*>(view_)->drawPreview(
		model_->getThumbnail(model_->getImageNumber()));
	if (static_cast<PreviewModel*>(model_)->isBubbleVisible())
	{
	static_cast<PreviewView*>(view_)->drawWordBubble(
		static_cast<PreviewModel*>(model_)->getWordBubbleStr(),
		static_cast<PreviewModel*>(model_)->getWordBubble(), 
		static_cast<PreviewModel*>(model_)->getWordBubbleX(),
		static_cast<PreviewModel*>(model_)->getWordBubbleY());
	}
	view_->drawThumbnails(model_->getThumbnails(),
		model_->getImgIndex(), model_->getImgCount());
	view_->drawThumbnailSelector(model_->updateThumbnailSelector(0));

}

/**
 * [PreviewController::keyPressed description]
 * @param key [description]
 */
void PreviewController::keyPressed(int key)
{
	static_cast<PreviewModel*>(model_)->editBubbleString(key);

	if (key == '>')
	{
		view_->drawThumbnailSelector(
			model_->updateThumbnailSelector(1));
	}
	else if (key == '<')
	{
		view_->drawThumbnailSelector(
			model_->updateThumbnailSelector(-1));
	}
}

/**
 * [PreviewController::mousePressed description]
 * @param x      [description]
 * @param y      [description]
 * @param button [description]
 */
void PreviewController::mousePressed(int x, int y, int button)
{
	if (x < 640 && y < 480)
		static_cast<PreviewModel*>(model_)->setWordBubblePos(x, y);
	isSelectable(x, y);
}

/**
 * Gui events specific for the Preview State
 * @param newEvent Event Object fired by ofxUI (mostly buttons)
 */
void PreviewController::guiEvent(ofxUIEventArgs & newEvent)
{
	string buttonName = newEvent.widget->getName();
	ofxUIButton * button = (ofxUIButton *) newEvent.widget;

	if (buttonName == "Save")
	{
		saveWordBubble();
		button->setValue(0);
	}
	else if (buttonName == "Facebook")
	{	
		saveWordBubble(USE_FACEBOOK);
		button->setValue(0);
	}
	else if (buttonName == model_->getButtonName(2))
	{
		if (button->getValue() == 1)
		{
			static_cast<PreviewModel*>(model_)->showWordBubble(true);
			static_cast<PreviewModel*>(model_)->setWordBubblePos(640/2, 480/2);	
		}
		else
		{
			static_cast<PreviewModel*>(model_)->showWordBubble(false);
		}
	}
}

/**
 * Saves the Picture with the Word Bubble on it. I think there is no
 * easyer way arround than this.
 * @param  option Options defined in the Header File!
 * @return        Filename of the new Image
 */
std::string PreviewController::saveWordBubble(int option)
{
	ofFbo fbo;
	ofPixels myPixels;

	int x = model_->getThumbnail(model_->getImageNumber()).getWidth();
	int y = model_->getThumbnail(model_->getImageNumber()).getHeight();

	fbo.allocate(x, y, GL_RGB);

	fbo.begin();
	static_cast<PreviewView*>(view_)->drawPreview(
		model_->getThumbnail(model_->getImageNumber()));
	static_cast<PreviewView*>(view_)->drawWordBubble(
		static_cast<PreviewModel*>(model_)->getWordBubbleStr(),
		static_cast<PreviewModel*>(model_)->getWordBubble(), 
		static_cast<PreviewModel*>(model_)->getWordBubbleX(),
		static_cast<PreviewModel*>(model_)->getWordBubbleY());
	fbo.end();

	fbo.readToPixels(myPixels);


	std::string imageName = model_->getImageName();
	model_->savePixelsToFile(myPixels, imageName);

	if (option == USE_FACEBOOK)
	{
		model_->saveToFacebook(imageName, x, y);
	}
	
	return imageName;
}
