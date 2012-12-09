#include "Bootstrap.h"

/**
 * Main Setup Methof from openFrameworks. Called once when the App
 * starts
 */
void Bootstrap::setup()
{
	controller_ = new Controller();

	ofAddListener(controller_->getCanvas()->newGUIEvent, 
		this, &Bootstrap::guiEvent);
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

void Bootstrap::guiEvent(ofxUIEventArgs & newEvent)
{
	string buttonName = newEvent.widget->getName();
	ofxUIButton * button = (ofxUIButton *) newEvent.widget;

	if (buttonName == "BUTTON_RIGHT")
	{
		if (button->getValue() == 1)
		{
			controller_ = new FilterController(controller_);
		}
		else if (button->getValue() == 0)
		{
			controller_ = new Controller(controller_, true);
		}
	}
	else
	{
		controller_->guiEvent(newEvent);
	}
}