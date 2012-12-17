#include "Bootstrap.h"

/**
 * Main Setup Methof from openFrameworks. Called once when the App
 * starts
 */
void Bootstrap::setup()
{
	ofSetWindowTitle("Open Photo Booth");
	
	controller_ = new Controller();

	ofAddListener(controller_->getCanvas()->newGUIEvent, 
		this, &Bootstrap::guiEvent);

	lockModel_ = false;
}

void Bootstrap::update()
{
	controller_->update();
}

void Bootstrap::draw()
{
	controller_->draw();
}

void Bootstrap::keyPressed(int key)
{
	controller_->keyPressed(key);
}

void Bootstrap::mousePressed(int x, int y, int button)
{
	controller_->mousePressed(x, y, button);
	if (!lockModel_ && controller_->isSelectable(x, y))
	{
		controller_ = new PreviewController(controller_);
		lockModel_ = true;
	}
}

void Bootstrap::guiEvent(ofxUIEventArgs & newEvent)
{
	string buttonName = newEvent.widget->getName();
	ofxUIButton * button = (ofxUIButton *) newEvent.widget;

	std::cout << button->getValue() << " BUTTON NAME " << buttonName << std::endl;

	if (buttonName == "MAINRIGHT")
	{
		if (button->getValue() == 1)
		{
			int fltNo         = controller_->getModel()->getFilterSelector();
			int currentOffset = fltNo - (fltNo % 8);
			controller_ = new FilterController(controller_, currentOffset);
			lockModel_ = false;
		}
		// else if (button->getValue() == 0)
		// {
			// controller_ = new Controller(controller_, true);
			// button->setValue(1);
			// lockModel_ = false;
		// }
	}
	if (buttonName == "PREVMIDDLE")
	{
		controller_ = new Controller(controller_, true);
		lockModel_ = false;
	}
	else if (buttonName == "MAINMIDDLE")
	{
		if (button->getValue() == 1)
		{
			controller_->guiEvent(newEvent);	
		}
	}
	else if (buttonName == "FILTERACTMIDDLE")
	{
		if (button->getValue() == 1) {
			controller_ = new Controller(controller_, true);
			lockModel_ = false;
			button->setValue(0);
		}
	}
	else if (buttonName == "FILTERRIGHT")
	{
		if (button->getValue() == 1) {
			int offset = controller_->getFilterOffset(), page = 8;
			if (offset < 0 || offset + page > static_cast<FilterModel*>(controller_->getModel())->getFilterCount()) {
				offset = 0; // Loop around
			} else {
				offset += page;
			}
			
			controller_ = new FilterController(controller_, offset);
			lockModel_ = false;
		}
	}
	else
	{
		controller_->guiEvent(newEvent);
	}
}