#include "module_filter.h"

#ifndef __INIT_STATIC_VARS__
#define __INIT_STATIC_VARS__
	int module_filter::filterCount_ = 0;
	std::vector<IAdjustment *> module_filter::globalList_ = 
		std::vector<IAdjustment *>();
#endif

module_filter::module_filter(std::string newName, int newImageSize) 
	: name_(newName), imageSize_(newImageSize)
{
	/* INCREASE FILTER COUNT WITH EVERY NEW MODULE_FILTER OBJECT	  */
	filterCount_++;

	/* PUSH ALL AVAIABLE FILTERS AT THE BACK 						  */
	globalList_.push_back(new adjustSaturation(imageSize_));
	globalList_.push_back(new adjustBrightness(imageSize_));
}

module_filter::~module_filter()
{
	if (filterCount_ > 0)
	{
		filterCount_--;
	}
	else
	{
		std::cout 	<< "FILTERCOUNT ERROR: module_filter.cpp" 
					<< std::endl;
	}
}

bool module_filter::addAdjustment(std::string adjustmentName)
{
	for (std::vector<IAdjustment *>::iterator it = globalList_.begin();
		it != globalList_.end(); it++)
	{
		if ((*it)->getName() == adjustmentName)
		{
			list_.push_back(*it);
			return true;
		}
	}
	return false;
}

bool module_filter::removeAdjustment(std::string adjustmentName)
{
	for (std::vector<IAdjustment *>::iterator it = list_.begin();
		it != list_.end(); it++)
	{
		if ((*it)->getName() == adjustmentName)
		{
			list_.erase(it);
			return true;
		}
	}
	return false;
}

int module_filter::getFilterCount()
{
	return filterCount_;
}

void module_filter::apply(unsigned char * pxlArr)
{
	for (std::vector<IAdjustment *>::iterator it = list_.begin();
		it != list_.end(); it++)
	{
		(*it)->apply(pxlArr);
	}
}