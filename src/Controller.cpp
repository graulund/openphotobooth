#include "Controller.h"

/**
 * Default Constructor for the First Call
 */
Controller::Controller()
{
	init();
	initName();
}

/**
 * Copy Constructor. Uses an old Controller to get the used View and Model
 * with all the Settings. This way we dont have to create them all again
 * and prevent interface lag.
 */
Controller::Controller(Controller * oldController, bool delOld)
{
	model_ = oldController->getModel();
	canvas_ = oldController->getCanvas();
	view_ = oldController->getView();

	model_ = new Model(model_);
	view_ = new View(view_, model_->getIconURL(),
		model_->getCamWidth(), model_->getCamHeight());

	initName();

	if (delOld)
		delete oldController;
}

Controller::~Controller() {}

/**
 * Since C++ doesnt support to call another constructor of the same Object
 * we use a init() method to prevent dublicated code
 */
void Controller::init()
{
	model_ = new Model();
	canvas_ = new ofxUICanvas(0, model_->getCamHeight(), 
		model_->getCamWidth(), 48);
	view_ = new View(model_->getIconURL(), model_->getCamWidth(), 
		model_->getCamHeight(), canvas_);

	initName();
}

void Controller::initName()
{
	view_->setButtonLabel(1, model_->getButtonLabel(1));
	view_->setButtonLabel(2, model_->getButtonLabel(2));
	
	view_->setButtonName(1, model_->getButtonName(1));
	view_->setButtonName(2, model_->getButtonName(2));
	view_->setButtonName(3, model_->getButtonName(3));
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
	if (model_->getFilterSelector() > 0)
	{
		view_->drawFilter(*model_->getTexture());
	}
	else
	{
		view_->drawVideoGrabber(model_->getVideoGrabber(),
			model_->getCamWidth(), model_->getCamHeight());
	}

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
	else if (key == ' ')
	{	

	}
}

void Controller::mousePressed(int x, int y, int button)
{

}

/**
 * Controlls all Events happens in the Current View
 * @param newEvent event object including widget which fired the event
 */
void Controller::guiEvent(ofxUIEventArgs & newEvent)
{
	string buttonName = newEvent.widget->getName();

	if (buttonName == "MAINMIDDLE")
	{
		ofxUIButton * button = (ofxUIButton *) newEvent.widget;
		if (button->getValue() == 1)
		{
			// std::cout << "SAVE IMAGE" << std::endl;
			model_->saveImage();
		}
	}
	else if (buttonName == "MAINLEFT")
	{
		//Open the Open File Dialog
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a jpg or png"); 
		
		//Check if the user opened a file
		if (openFileResult.bSuccess){
			
			ofLogVerbose("User selected a file");
			
			//We have a file, check it and process it
			model_->processOpenFileSelection(openFileResult);
			
		}
		else 
		{
			ofLogVerbose("User hit cancel");
		}
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

/**
 * Returns the current used Model
 * @return the current Model
 */
Model * Controller::getModel()
{
	return model_;
}

/**
 * Returns the current used View
 * @return the current View
 */
View * Controller::getView()
{
	return view_;
}

bool Controller::isSelectable(int x, int y)
{
	return model_->selectImage(x, y);
}