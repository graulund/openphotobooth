#include "FilterModel.h"

FilterModel::FilterModel(Model * oldModel, int offset) : Model(oldModel, true), filterOffset_(offset)
{
	// Determining the amount of filters we're displaying on this page (given by offset)
	
	int fltrCnt  = filterVector_->size();
	filtersLeft_ = std::min(FILTER_PAGE_LENGTH, fltrCnt - filterOffset_);

	textureArr_  = new ofTexture[filtersLeft_];
	filterNames_ = new std::string[filtersLeft_];
	
	std::cout << "FILTER FROM " << filterOffset_ << " TO " << (filterOffset_ + filtersLeft_) << std::endl;
	
	// Allocating textures for filter previews
	
	for (int i = 0; i < filtersLeft_; i++)
	{
		textureArr_[i].allocate(640, 480, GL_RGB);
		filterNames_[i] = filterVector_->at(filterOffset_ + i).getName();
	}
	
	// Allocating special blue screen filter pixel array
	int subpixels = 640*480*3;
	BS_ = new unsigned char[subpixels];
	for (int i = 0; i < subpixels; i++) {
		int channel = i % 3;
		BS_[i] = channel == 2 ? 255 : 0; // Blue!
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
	btnNameAM_ = BTN_NAME_AM;
	btnNameR_ = BTN_NAME_R;
}

/**
 * UPDATE CALLED BY CONTROLLER
 */
void FilterModel::update()
{
	int fi = 0;
	vidGrabber_->update();

	for (int i = 0; i < filtersLeft_; i++)
	{
		if (vidGrabber_->isFrameNew())
		{
			fi = filterOffset_ + i;
			/* COPY "FRESH" PICTURE TO pixelArrSlot SO THAT EVERY FILTER
			   GOT A UNMODIFIED VERSION									*/
		    memcpy(pixelArrSlot, vidGrabber_->getPixels(), 640*480*3);
		    /* APPLY EVERY AVAILABLE FILTER TO THIS FRESH COPYS			*/
			filterVector_->at(fi).apply(pixelArrSlot);
			/* TRANSFORM PIXELS TO TEXTURE TO DRAW IT ON THE SCREEN		*/
		 	if(filterVector_->at(fi).getIsBlueScreen()){
				textureArr_[i].loadData(BS_, 640, 480, GL_RGB);
			} else {
				textureArr_[i].loadData(pixelArrSlot, 640, 480, GL_RGB);
			}
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
 * [FilterModel::getFilterNames description]
 * @return [description]
 */
std::string * FilterModel::getFilterNames()
{
	return filterNames_;
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
	
	// ZERO IS RESERVED FOR THE NO-FILTER, WHICH IS ALWAYS IN THE MIDDLE (x=1,y=1).
	// THIS IS WHY SOME NUMBERS ARE SHIFTED IN THE RESULTS.

	if (x <= 640 && y <= 480)
	{
		if (y <= 160)
		{
			if (x > 426 && fltrCnt >= 3 + filterOffset_)
			{
				filterSelector_ = 3 + filterOffset_;
				isSelectable = true;
			}
			if (x <= 426 && fltrCnt >= 2 + filterOffset_)
			{
				filterSelector_ = 2 + filterOffset_;
				isSelectable = true;
			}
			if (x <= 213 && fltrCnt >= 1 + filterOffset_)
			{
				filterSelector_ = 1 + filterOffset_;
				isSelectable = true;
			}
		}
		else if (y <= 320)
		{
			if (x > 426 && fltrCnt >= 5 + filterOffset_)
			{
				filterSelector_ = 5 + filterOffset_;
				isSelectable = true;
			}
			if (x <= 426)
			{
				filterSelector_ = 0; // THE MIDDLE <-----
				isSelectable = true;
			}
			if (x <= 213 && fltrCnt >= 4 + filterOffset_)
			{
				filterSelector_ = 4 + filterOffset_;
				isSelectable = true;
			}
		}
		else
		{
			if (x > 426 && fltrCnt >= 8 + filterOffset_)
			{
				filterSelector_ = 8 + filterOffset_;
				isSelectable = true;
			}
			if (x <= 426 && fltrCnt >= 7 + filterOffset_)
			{
				filterSelector_ = 7 + filterOffset_;
				isSelectable = true;
			}
			if (x <= 213 && fltrCnt >= 6 + filterOffset_)
			{
				filterSelector_ = 6 + filterOffset_;
				isSelectable = true;
			}			
		}
	}
}
