#include "adjustment_interface.h"

// IAdjustment::IAdjustment()
// {

// }

IAdjustment::IAdjustment(int newSize, int newAdjust)
{
    imageSize_ = newSize;
	adjust_ = newAdjust;
}

void IAdjustment::setAdjust(int newAdjust)
{
	adjust_ = newAdjust;
}

int IAdjustment::getAdjust()
{
	return adjust_;
}

std::string IAdjustment::getName()
{
	return name_;
}

int IAdjustment::unclip(int value)
{
	return std::min(255, std::max(0, value));
}

unsigned char IAdjustment::unclip(unsigned char value)
{
	return std::min((unsigned char)255, std::max((unsigned char)0, value));
}