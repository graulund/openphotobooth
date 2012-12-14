#include "adjust_tint_blue.h"

#include <cmath>

adjustTintBlue::adjustTintBlue(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_TBL_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: BLUE TINT
 * Uniformly shifts the colors in an image towards the blue.
 * Adjust is from 0 to 100, the higher the closer.
 */
void adjustTintBlue::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "BLUE TINT APPLIED" << std::endl;
#endif
	
	IAdjustment::colorize(pxlPtr, adjust_, 0, 0, 255);
}