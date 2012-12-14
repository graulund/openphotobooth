#include "adjust_tint_red.h"

#include <cmath>

adjustTintRed::adjustTintRed(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_TRE_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: RED TINT
 * Uniformly shifts the colors in an image towards the red.
 * Adjust is from 0 to 100, the higher the closer.
 */
void adjustTintRed::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "RED TINT APPLIED" << std::endl;
#endif
	
	IAdjustment::colorize(pxlPtr, adjust_, 255, 0, 0);
}