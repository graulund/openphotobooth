#include "FilterModel.h"

FilterModel::FilterModel(Model * oldModel) : Model(oldModel, true)
{
	int fltrCnt = modFilter_->getFilterCount();

	textureArr_ = new ofTexture[fltrCnt];
	
	for (int i = 0; i < fltrCnt; i++)
	{
		textureArr_[i].allocate(640, 480, GL_RGB);
	}

	init();
}

FilterModel::~FilterModel()
{
	delete modFilter_;
	delete textureArr_;
//	delete pixelArr_;
}

void FilterModel::init()
{
	btnLabelL_ = BTN_LABL_L;
	btnLabelM_ = BTN_LABL_M;
	btnLabelR_ = BTN_LABL_R;	

	btnNameL_ = BTN_NAME_L;
	btnNameM_ = BTN_NAME_M;
	btnNameR_ = BTN_NAME_R;
}

void FilterModel::update()
{
	vidGrabber_->update();

	for (int i = 0; i < modFilter_->getFilterCount(); i++)
	{
		if (vidGrabber_->isFrameNew())
		{
		    memcpy(pixelArrSlot, vidGrabber_->getPixels(), 640*480*3);
			modFilter_->getFilters(pixelArrSlot, i, 30);
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

// 213 160
bool FilterModel::selectFilter(int x, int y)
{
	bool isSelectable = false;
	int fltrCnt = modFilter_->getFilterCount();

	if (x <= 640 && y <= 480)
	{
		if (y <= 160)
		{
			if (x > 426 && fltrCnt > 2)
			{
				filterSelector_ = 2;
				isSelectable = true;
			}
			if (x <= 426 && fltrCnt > 1)
			{
				filterSelector_ = 1;
				isSelectable = true;
			}
			if (x <= 213 && fltrCnt > 0)
			{
				filterSelector_ = 0;
				isSelectable = true;
			}
		}
		else if (y <= 320)
		{
			if (x > 426 && fltrCnt > 5)
			{
				filterSelector_ = 5;
				isSelectable = true;
			}
			if (x <= 426 && fltrCnt > 4)
			{
				filterSelector_ = 4;
				isSelectable = true;
			}
			if (x <= 213 && fltrCnt > 3)
			{
				filterSelector_ = 3;
				isSelectable = true;
			}
		}
		else
		{
			if (x > 426 && fltrCnt > 8)
			{
				filterSelector_ = 8;
				isSelectable = true;
			}
			if (x <= 426 && fltrCnt > 7)
			{
				filterSelector_ = 7;
				isSelectable = true;
			}
			if (x <= 213 && fltrCnt > 6)
			{
				filterSelector_ = 6;
				isSelectable = true;
			}			
		}
	}
}
