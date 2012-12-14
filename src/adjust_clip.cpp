#include "adjust_clip.h"

#include <cmath>

adjustClip::adjustClip(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_CLI_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: CLIP
 * Clips a color to maximum values when it falls outside of the range specified in adjust.
 * Adjust is between 0 and 100.
 */
void adjustClip::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "CLIP APPLIED" << std::endl;
#endif
	
	float x = std::abs(adjust_) * 2.55F;
	
	for (int i = 0; i < imageSize_; i++) {
		if (pxlPtr[i] > 255.0F - x) {
			pxlPtr[i] = 255;
		} else if (pxlPtr[i] < x){
			pxlPtr[i] = 0;
		}
	}
}