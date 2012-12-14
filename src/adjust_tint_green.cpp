#include "adjust_tint_green.h"

#include <cmath>

adjustTintGreen::adjustTintGreen(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_TGR_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: GREEN TINT
 * Uniformly shifts the colors in an image towards the green.
 * Adjust is from 0 to 100, the higher the closer.
 */
void adjustTintGreen::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "GREEN TINT APPLIED" << std::endl;
#endif
	
	IAdjustment::colorize(pxlPtr, adjust_, 0, 255, 0);
}