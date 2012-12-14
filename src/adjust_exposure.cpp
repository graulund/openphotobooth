#include "adjust_exposure.h"

#include <cmath>

adjustExposure::adjustExposure(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_EXP_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: EXPOSURE
 * Adjusts the exposure of the image by the use of curves. Adjust is between -100 and 100.
 * Values over zero increases exposure, values below zero decreases exposure.
 */
void adjustExposure::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "EXPOSURE APPLIED" << std::endl;
#endif
	
	float x = std::abs(adjust_) / 100.0F;
	
	int y1, x2;
	y1 = 255 * x;
	x2 = 255 - (255 * x);
	
	if (adjust_ < 0) {
		// Ctrl points (x1,y1) and (x2,y2) reversed
		IAdjustment::curves(pxlPtr, 3, 0, 0, y1, 0, 255, x2, 255, 255);
	} else {
		// Normal
		IAdjustment::curves(pxlPtr, 3, 0, 0, 0, y1, x2, 255, 255, 255);
	}
}