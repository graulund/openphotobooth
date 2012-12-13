#include "FilterModel.h"

FilterModel::FilterModel(Model * oldModel) : Model(oldModel, true)
{
	int fltrCnt = filterVector_->size();

	textureArr_ = new ofTexture[fltrCnt];
	
	for (int i = 0; i < fltrCnt; i++)
	{
		textureArr_[i].allocate(640, 480, GL_RGB);
	}

	init();		
}

/**
 * @TODO
 * DEFAULT DECONSTRUCTER TO CLEAN UP THE MESS - NEEDS WORK BECAUSE IT
 * DOESNT WORK RIGHT NOW!
 */
FilterModel::~FilterModel()
{
	delete modFilter_;
	delete textureArr_;
//	delete pixelArr_;
}

/**
 * [FilterModel::init description]
 */
void FilterModel::init()
{
	btnLabelL_ = BTN_LABL_L;
	btnLabelM_ = BTN_LABL_M;
	btnLabelR_ = BTN_LABL_R;	

	btnNameL_ = BTN_NAME_L;
	btnNameM_ = BTN_NAME_M;
	btnNameR_ = BTN_NAME_R;
}

/**
 * UPDATE CALLED BY CONTROLLER
 */
void FilterModel::update()
{
	vidGrabber_->update();

	for (int i = 0; i < filterVector_->size(); i++)
	{
		if (vidGrabber_->isFrameNew())
		{
			/* COPY "FRESH" PICTURE TO pixelArrSlot SO THAT EVERY FILTER
			   GOT A UNMODIFIED VERSION									*/
		    memcpy(pixelArrSlot, vidGrabber_->getPixels(), 640*480*3);
		    /* APPLY EVERY AVAILABLE FILTER TO THIS FRESH COPYS			*/
			filterVector_->at(i).apply(pixelArrSlot);
			/* TRANSFORM PIXELS TO TEXTURE TO DRAW IT ON THE SCREEN		*/
		 	textureArr_[i].loadData(pixelArrSlot, 640, 480, GL_RGB);
	 	}
	}
}

/**
 * RETURNS THE CAM_WIDTH, UNFORTUNATELY UNSED DUE HARD CODING =(
 */
float FilterModel::getCamWidth()
{
	return float(CAM_WIDTH);
}

/**
 * [FilterModel::getCamHeight description]
 * @return [description]
 */
float FilterModel::getCamHeight()
{
	return float(CAM_HEIGHT);
}

/**
 * [FilterModel::getFilterCount description]
 * @return [description]
 */
int FilterModel::getFilterCount()
{
	return filterVector_->size();
}

/**
 * [FilterModel::getButtonLabel description]
 * @param  btnNr [description]
 * @return       [description]
 */
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

/**
 * [FilterModel::getTextureArray description]
 * @return [description]
 */
ofTexture * FilterModel::getTextureArray()
{
	return textureArr_;
}

/**
 * [FilterModel::selectFilter description]
 * @param  x [description]
 * @param  y [description]
 * @return   [description]
 */
bool FilterModel::selectFilter(int x, int y)
{
	bool isSelectable = false;
	int fltrCnt = filterVector_->size();

	if (x <= 640 && y <= 480)
	{
		if (y <= 160)
		{
			if (x > 426 && fltrCnt >= 2)
			{
				filterSelector_ = 2;
				isSelectable = true;
			}
			if (x <= 426 && fltrCnt >= 1)
			{
				filterSelector_ = 1;
				isSelectable = true;
			}
			if (x <= 213 && fltrCnt >= 0)
			{
				filterSelector_ = 0;
				isSelectable = true;
			}
		}
		else if (y <= 320)
		{
			if (x > 426 && fltrCnt >= 5)
			{
				filterSelector_ = 5;
				isSelectable = true;
			}
			if (x <= 426 && fltrCnt >= 4)
			{
				filterSelector_ = 4;
				isSelectable = true;
			}
			if (x <= 213 && fltrCnt >= 3)
			{
				filterSelector_ = 3;
				isSelectable = true;
			}
		}
		else
		{
			if (x > 426 && fltrCnt >= 8)
			{
				filterSelector_ = 8;
				isSelectable = true;
			}
			if (x <= 426 && fltrCnt >= 7)
			{
				filterSelector_ = 7;
				isSelectable = true;
			}
			if (x <= 213 && fltrCnt >= 6)
			{
				filterSelector_ = 6;
				isSelectable = true;
			}			
		}
	}
}
