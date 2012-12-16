#include "module_filter.h"

#ifndef __INIT_STATIC_VARS__
#define __INIT_STATIC_VARS__
	int module_filter::filterCount_ = 0;
	std::vector<IAdjustment *> module_filter::globalList_ = 
		std::vector<IAdjustment *>();
#endif

bool adjustmentsAdded = false;

module_filter::module_filter(std::string newName, int newImageSize) 
	: name_(newName), imageSize_(newImageSize)
{
	/* INCREASE FILTER COUNT WITH EVERY NEW MODULE_FILTER OBJECT	  */
	filterCount_++;
	
	//adjusts_ = *new std::vector<int>();

	/* PUSH ALL AVAILABLE ADJUSTMENTS TO THE "GLOBAL LIST"			  */
	if(!adjustmentsAdded){
		globalList_.push_back(new adjustBrightness(imageSize_));
		globalList_.push_back(new adjustSaturation(imageSize_));
		globalList_.push_back(new adjustContrast(imageSize_));
		globalList_.push_back(new adjustVibrance(imageSize_));
		globalList_.push_back(new adjustGreyscale(imageSize_));
		globalList_.push_back(new adjustHue(imageSize_));
		globalList_.push_back(new adjustInvert(imageSize_));
		globalList_.push_back(new adjustSepia(imageSize_));
		globalList_.push_back(new adjustGamma(imageSize_));
		globalList_.push_back(new adjustNoise(imageSize_));
		globalList_.push_back(new adjustClip(imageSize_));
		globalList_.push_back(new adjustPosterize(imageSize_));
		globalList_.push_back(new adjustChannels(imageSize_));
		globalList_.push_back(new adjustCurves(imageSize_));
		globalList_.push_back(new adjustExposure(imageSize_));
		globalList_.push_back(new adjustColorize(imageSize_));
		globalList_.push_back(new adjustTintRed(imageSize_));
		globalList_.push_back(new adjustTintGreen(imageSize_));
		globalList_.push_back(new adjustTintBlue(imageSize_));
		adjustmentsAdded = true;
	}
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

bool module_filter::addAdjustment(std::string adjustmentName, int adjust, int * options)
{
	for (std::vector<IAdjustment *>::iterator it = globalList_.begin();
		 it != globalList_.end(); it++)
	{
		if ((*it)->getName() == adjustmentName)
		{
			adjusts_.push_back(adjust);
			options_.push_back(options);
			list_.push_back(*it);
			return true;
		}
	}
	return false;
}

bool module_filter::addAdjustment(std::string adjustmentName, int adjust)
{
	return module_filter::addAdjustment(adjustmentName, adjust, NULL);
}

bool module_filter::addAdjustment(std::string adjustmentName)
{
	return module_filter::addAdjustment(adjustmentName, 0);
}

bool module_filter::removeAdjustment(std::string adjustmentName)
{
	std::vector<int>::iterator at = adjusts_.begin();
	for (std::vector<IAdjustment *>::iterator it = list_.begin();
		it != list_.end(); it++, at++)
	{
		if ((*it)->getName() == adjustmentName)
		{
			list_.erase(it);
			adjusts_.erase(at);
			return true;
		}
	}
	return false;
}

int module_filter::getFilterCount()
{
	return filterCount_;
}

std::string module_filter::getName()
{
	return name_;
}

void module_filter::apply(unsigned char * pxlArr)
{
	std::vector<int>::iterator at   = adjusts_.begin();
	std::vector<int *>::iterator ot = options_.begin();
	for (std::vector<IAdjustment *>::iterator it = list_.begin();
		it != list_.end(); it++, at++, ot++)
	{
		(*it)->setAdjust(*at);
		(*it)->setOptions(*ot);
		(*it)->apply(pxlArr);
	}
}