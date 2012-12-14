#include "adjust_colorize.h"

adjustColorize::adjustColorize(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_COL_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: COLORIZE
 * Uniformly shifts the colors in an image towards the given color.
 * Adjust is from 0 to 100, the higher the closer.
 * Arguments are adjust and target r, g, b values.
 */
void adjustColorize::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "COLORIZE APPLIED" << std::endl;
#endif
	
	if(options_ != NULL){
		int r, g, b;
		try {
			// Try extracting all three colors, skip this adjustment if we can't find them.
			r = options_[0]; g = options_[1]; b = options_[2];
			
			IAdjustment::colorize(pxlPtr, adjust_, r, g, b);
		} catch (std::exception& e) {}
	}
}