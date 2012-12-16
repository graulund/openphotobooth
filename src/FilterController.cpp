#include "FilterController.h"

FilterController::FilterController(Controller * oldController) : 
	Controller(oldController)
{
	model_ = new FilterModel(oldController->getModel());
	view_ = new FilterView(oldController->getView(), model_->getIconURL(), 
		model_->getCamWidth(), model_->getCamHeight());

	view_->setButtonLabel(1, model_->getButtonLabel(1));
	view_->setButtonLabel(2, model_->getButtonLabel(2));

	// view_->clearButtonStatus(1);
	// view_->clearButtonStatus(2);
	// view_->clearButtonStatus(3);

	initName();

	myTexture.allocate(640, 480, GL_RGB);

	delete oldController;
}

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
	// std::cout << model_->getFilterSelector() << std::endl;
	// Controller::mousePressed(x, y, button);
}

void FilterController::draw()
{
	view_->drawVideoGrabber(model_->getVideoGrabber(),
		model_->getCamWidth(), model_->getCamHeight(), model_->getCamWidth(), model_->getCamHeight());
	static_cast<FilterView*>(view_)->drawFilter(
		static_cast<FilterModel*>(model_)->getTextureArray(),
		static_cast<FilterModel*>(model_)->getFilterNames(),
		static_cast<FilterModel*>(model_)->getFilterCount());
	view_->drawThumbnails(model_->getThumbnails(),
		model_->getImgIndex(), model_->getImgCount());
	view_->drawThumbnailSelector(model_->updateThumbnailSelector(0));
	static_cast<FilterView*>(view_)->drawFilterSelector(
		model_->getFilterSelector());
}

void FilterController::guiEvent(ofxUIEventArgs & newEvent)
{

}

void FilterController::keyPressed(int key)
{
	if (key == 'a')
	{

	}

	Controller::keyPressed(key);
}