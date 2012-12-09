#include "module_filter.h"

#include <cmath>
#include <algorithm>
#include <iostream>

module_filter::module_filter(int size) : imageSize_(size)
{
	ptrArr_[0] = &module_filter::brightness;
	ptrArr_[1] = &module_filter::brightness;
	ptrArr_[2] = &module_filter::brightness2;
	ptrArr_[3] = &module_filter::brightness2;
}

void module_filter::brightness(unsigned char * pxlPtr)
{
	int x = (int) floor(255.0 * (50 / 100.0));
	
	for (int i = 0; i < imageSize_; i++)
	{
		pxlPtr[i] = unclip(pxlPtr[i] + x);
	}
}

void module_filter::brightness2(unsigned char * pxlPtr)
{
	int x = (int) floor(255.0 * (50 / 100.0));
	
	for (int i = 0; i < imageSize_; i++)
	{
		pxlPtr[i] = unclip(pxlPtr[i] + x);
	}
}

int module_filter::unclip(int value)
{
	return std::min(255, std::max(0, value));
}

int module_filter::getFilterCount()
{
	return int(FILTER_CNT);
}

void module_filter::getFilters(unsigned char * pxlPtr, int fnctNr)
{
	(*this.*ptrArr_[fnctNr])(pxlPtr);
}
