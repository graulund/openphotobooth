#include "adjust_invert.h"

adjustInvert::adjustInvert(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_INV_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: INVERT
 * Simply inverts the pixel values. No adjust.
 */
void adjustInvert::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "INVERT APPLIED" << std::endl;
#endif
	
	for (int i = 0; i < imageSize_; i++) {
		pxlPtr[i] = 255 - pxlPtr[i];
	}
}