#include "Controller.h"

Controller::Controller()
{
	init();
}

Controller::Controller(Controller * oldController, bool delOld)
{
	model_ = oldController->getModel();
	canvas_ = oldController->getCanvas();
	view_ = oldController->getView();

	model_ = new Model(model_);
	view_ = new View(view_, model_->getIconURL(),
		model_->getCamWidth(), model_->getCamHeight());

	view_->setButtonLabel(1, model_->getButtonLabel(1));
	view_->setButtonLabel(2, model_->getButtonLabel(2));

	if (delOld)
		delete oldController;
}

Controller::~Controller() { }

void Controller::init()
{
	model_ = new Model();
	canvas_ = new ofxUICanvas(0, model_->getCamHeight(), 
		model_->getCamWidth(), 48);
	view_ = new View(model_->getIconURL(), model_->getCamWidth(), 
		model_->getCamHeight(), canvas_);

	view_->setButtonLabel(1, model_->getButtonLabel(1));
	view_->setButtonLabel(2, model_->getButtonLabel(2));
}

/**
 * Main Update Method from openFrameworks. Called once for every Frame
 */
void Controller::update()
{
	model_->update();
}

/**
 * Main Draw Method from openFrameworks. Called once for every Frame
 */
void Controller::draw()
{
	view_->drawVideoGrabber(model_->getVideoGrabber(),
		model_->getCamWidth(), model_->getCamHeight());
	view_->drawThumbnails(model_->getThumbnails(),
		model_->getImgIndex(), model_->getImgCount());
	view_->drawThumbnailSelector(model_->updateThumbnailSelector(0));
}

/**
 * Action Listener for Key Pressed events
 * @param key the key that was pressed
 */
void Controller::keyPressed(int key)
{
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
 * Controlls all Events happens in the Current View
 * @param newEvent event object including widget which fired the event
 */
void Controller::guiEvent(ofxUIEventArgs & newEvent)
{
	string buttonName = newEvent.widget->getName();

	if (buttonName == "BUTTON_CENT")
	{
		ofxUIButton * button = (ofxUIButton *) newEvent.widget;
		if (button->getValue() == 0)
		{
			model_->saveImage();
		}
	}
	else if (buttonName == "BUTTON_LEFT")
	{

	}
}

/**
 * Returns the canvas used in this view. Helpful to Register
 * ActionListener in another Class
 * @return
 */
ofxUICanvas * Controller::getCanvas()
{
	// view_->getCanvas();
	return canvas_;
}

Model * Controller::getModel()
{
	return model_;
}

View * Controller::getView()
{
	return view_;
}