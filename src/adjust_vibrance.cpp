#include "adjust_vibrance.h"

#include <cmath>
#include <algorithm>
#include <iostream>

adjustVibrance::adjustVibrance(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_VIB_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: VIBRANCE
 * Similar to saturation, but slightly smarter, more subtle.
 * Attempts to boost colors that are less saturated more and boost already saturated colors less.
 * Range of adjust is from -100 to 100.
 */
void adjustVibrance::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "VIBRANCE APPLIED" << std::endl;
#endif
	
	int adjust = -1 * adjust_;
	int channel;
	int r, g, b, maxval;
	float avgval, amtval;
	for (int i = 0; i < imageSize_; i++) {
		channel = i % 3;
		// Separating the subpixels into channels
		if (channel == 0) {
			r = pxlPtr[i];
		} else if (channel == 1) {
			g = pxlPtr[i];
		} else {
			b = pxlPtr[i];
			
			// Getting the maximum value of the 3 subpixels
			maxval = std::max(std::max(r, g), b);
			// Get the average value
			avgval = (r + g + b) / 3.0F;
			// Get adjusted average
			amtval = ((std::abs(maxval - avgval) * 2.0F / 255.0F) * adjust) / 100.0F;
			
			// Handling each subpixel individually
			if(r != maxval){
				r += ((maxval - r) * amtval);
			}
			if(g != maxval){
				g += ((maxval - g) * amtval);
			}
			if(b != maxval){
				b += ((maxval - b) * amtval);
			}
			
			// Saving the subpixels back
			pxlPtr[i-2] = IAdjustment::unclip(r);
			pxlPtr[i-1] = IAdjustment::unclip(g);
			pxlPtr[i]   = IAdjustment::unclip(b);
		}
	}
}
