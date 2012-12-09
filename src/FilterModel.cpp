#include "FilterModel.h"

FilterModel::FilterModel(Model * oldModel) : Model(oldModel, true)
{
	int fltrCnt = modFilter_->getFilterCount();

	modFilter_ = new module_filter(640 * 480 * 3);
	textureArr_ = new ofTexture[fltrCnt];
	
	for (int i = 0; i < fltrCnt; i++)
	{
		textureArr_[i].allocate(640, 480, GL_RGB);
	}
}

FilterModel::~FilterModel()
{
	delete modFilter_;
	delete textureArr_;
//	delete pixelArr_;
}

void FilterModel::update()
{
	vidGrabber_->update();

	for (int i = 0; i < modFilter_->getFilterCount(); i++)
	{
		if (vidGrabber_->isFrameNew())
		{
		    memcpy(pixelArrSlot, vidGrabber_->getPixels(), 640*480*3);
			modFilter_->getFilters(pixelArrSlot, i);
		 	textureArr_[i].loadData(pixelArrSlot, 640, 480, GL_RGB);
	 	}
	}
}

float FilterModel::getCamWidth()
{
	return float(CAM_WIDTH);
}

float FilterModel::getCamHeight()
{
	return float(CAM_HEIGHT);
}

int FilterModel::getFilterCount()
{
	return modFilter_->getFilterCount();
}

std::string FilterModel::getButtonLabel(int btnNr)
{
	if (btnNr == 1)
	{
		return BTN_LABL_L;
	}
	else if (btnNr == 2)
	{
		return BTN_LABL_R;
	}
}

ofTexture * FilterModel::getTextureArray()
{
	return textureArr_;
}
