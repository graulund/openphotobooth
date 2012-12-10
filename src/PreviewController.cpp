#include "PreviewController.h"

PreviewController::PreviewController(Controller * oldController) :
	Controller(oldController)
{
	model_ = new PreviewModel(oldController->getModel());
	view_ = new PreviewView(oldController->getView(), model_->getIconURL(), 
		model_->getCamWidth(), model_->getCamHeight());

	initName();

	testImage_ = new ofImage();
	testImage_->allocate(640, 480, OF_IMAGE_COLOR);
	testImage_->loadImage("myPhoto 2012-12-08 09.56.33.jpg");

	delete oldController;
}

void PreviewController::draw()
{
	static_cast<PreviewView*>(view_)->drawPreview(
		model_->getThumbnail(model_->updateThumbnailSelector(0) - 1));
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

void PreviewController::mousePressed(int x, int y, int button)
{
	if (x < 640 && y < 480)
		static_cast<PreviewModel*>(model_)->setWordBubblePos(x, y);
	isSelectable(x, y);
}

void PreviewController::guiEvent(ofxUIEventArgs & newEvent)
{
	string buttonName = newEvent.widget->getName();
	ofxUIButton * button = (ofxUIButton *) newEvent.widget;

	if (buttonName == model_->getButtonName(1))
	{
		saveWordBubble();
		button->setValue(0);
	}
	else if (buttonName == model_->getButtonName(3))
	{	

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

void PreviewController::saveWordBubble()
{
	ofFbo fbo;
	ofPixels myPixels;

	fbo.allocate(640, 480, GL_RGB);

	fbo.begin();
	static_cast<PreviewView*>(view_)->drawPreview(
		model_->getThumbnail(model_->getImgIndex()));
	static_cast<PreviewView*>(view_)->drawWordBubble(
		static_cast<PreviewModel*>(model_)->getWordBubbleStr(),
		static_cast<PreviewModel*>(model_)->getWordBubble(), 
		static_cast<PreviewModel*>(model_)->getWordBubbleX(),
		static_cast<PreviewModel*>(model_)->getWordBubbleY());
	fbo.end();

	fbo.readToPixels(myPixels);
	model_->savePixelsToFile(myPixels, model_->getImageName());
}
