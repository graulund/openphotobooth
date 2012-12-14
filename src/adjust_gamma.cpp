#include "adjust_gamma.h"

#include <cmath>

adjustGamma::adjustGamma(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_GAM_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: GAMMA
 * Adjusts the gamma of the image. Range is from 0 to infinity, but usually kept between 0 and 400-500.
 * Values between 0 and 100 will lessen the contrast, while values greater than 100 will increase it.
 *
 * Normally, gamma is a decimal value where above numbers are 0-1 and 4-5, but since we're using ints
 * for adjust, everything is multiplied by 100 in the argument and divided by 100 inside the function,
 * resulting in an integer argument.
 */
void adjustGamma::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "GAMMA APPLIED" << std::endl;
#endif
	
	float x    = adjust_ / 100.0F;
	for (int i = 0; i < imageSize_; i++) {
		pxlPtr[i] = IAdjustment::unclip(
						(int)(std::pow((float)(pxlPtr[i] / 255.0F), x) * 255.0F)
					);
	}
}