#include "adjust_noise.h"

#include <cmath>

adjustNoise::adjustNoise(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_NOI_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: NOISE
 * Adds noise to the image from a scale between 1 and 100. (However, there's no actual upper limit
 * to the adjust.)
 */
void adjustNoise::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "NOISE APPLIED" << std::endl;
#endif
	
	unsigned char r, g, b;
	int noise, channel;
	
	for (int i = 0; i < imageSize_; i++) {
		channel = i % 3;
		// Separating the subpixels into channels
		if (channel == 0) {
			r = pxlPtr[i];
		} else if (channel == 1) {
			g = pxlPtr[i];
		} else {
			b = pxlPtr[i];
			
			noise = (std::rand() % adjust_) - adjust_/2.0F;
			
			// Making sure we add an equal amount of noise to all channels,
			// so the noise is not color-specific.
			
			pxlPtr[i-2] = IAdjustment::unclip((int)(r + noise));
			pxlPtr[i-1] = IAdjustment::unclip((int)(g + noise));
			pxlPtr[i]   = IAdjustment::unclip((int)(b + noise));
		}
	}
}