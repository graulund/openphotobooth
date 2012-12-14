#include "adjust_posterize.h"

#include <cmath>

adjustPosterize::adjustPosterize(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_POS_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: POSTERIZE
 * Applies posterization to the image: A continuous gradation of tone to several regions of fewer tones.
 * Range is from 0 to 100.
 */
void adjustPosterize::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "POSTERIZE APPLIED" << std::endl;
#endif
	
	float numOfAreas = 256.0F / adjust_;
	float numOfValues = 255.0F / (adjust_ - 1);
	
	for (int i = 0; i < imageSize_; i++) {
		pxlPtr[i] = IAdjustment::unclip(
						(int)(std::floor(std::floor(pxlPtr[i] / numOfAreas) * numOfValues))
					);
	}
}