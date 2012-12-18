/*************************************************
 File: FilterController.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: Controller for the Filter-state. Holds the Required 
 model(s) as a Reference. derived from the Main Controller. Adds 
specific Methods needed for the Preview.
 *************************************************/

#include "FilterController.h"

FilterController::FilterController(Controller * oldController, int offset) :
	Controller(oldController), filterOffset_(offset)
{
	model_ = new FilterModel(oldController->getModel(), filterOffset_);
	view_ = new FilterView(oldController->getView(), model_->getIconURL(), 
		model_->getCamWidth(), model_->getCamHeight(), filterOffset_);

	view_->setButtonLabel(1, model_->getButtonLabel(1));
	view_->setButtonLabel(2, model_->getButtonLabel(2));

	initName();

	myTexture.allocate(640, 480, GL_RGB);

	delete oldController;
}

/**
 * Default Deconstrucor. Didnt fint a way so far to safe delete the old
 * Model and View.
 */
FilterController::~FilterController()
{
	// delete model_;
	// delete view_;
}

void FilterController::update()
{
	model_->update();
}

void FilterController::mousePressed(int x, int y, int button)
{
	static_cast<FilterModel*>(model_)->selectFilter(x, y);
}

void FilterController::draw()
{
	int filtersLeft = std::min(FILTER_PAGE_LENGTH, static_cast<FilterModel*>(model_)->getFilterCount() - filterOffset_);
	
	view_->drawVideoGrabber(model_->getVideoGrabber(),
		model_->getCamWidth(), model_->getCamHeight(), model_->getCamWidth(), model_->getCamHeight());
	static_cast<FilterView*>(view_)->drawFilter(
		static_cast<FilterModel*>(model_)->getTextureArray(),
		static_cast<FilterModel*>(model_)->getFilterNames(),
		filtersLeft);
	view_->drawThumbnails(model_->getThumbnails(),
		model_->getImgIndex(), model_->getImgCount());
	view_->drawThumbnailSelector(model_->updateThumbnailSelector(0));
	static_cast<FilterView*>(view_)->drawFilterSelector(
		model_->getFilterSelector());
}

void FilterController::guiEvent(ofxUIEventArgs & newEvent)
{
	string buttonName = newEvent.widget->getName();
	ofxUIButton * button = (ofxUIButton *) newEvent.widget;
	
	if (buttonName == "Load Filter")
	{
		if (button->getValue() == 1){
			static_cast<FilterModel*>(model_)->loadFilterFromFileUI();
		}
	}
}

void FilterController::keyPressed(int key)
{
	if (key == 'a')
	{

	}

	Controller::keyPressed(key);
}

int FilterController::getFilterOffset(){
	return filterOffset_;
}

void FilterController::setFilterOffset(int offset){
	filterOffset_ = offset;
}