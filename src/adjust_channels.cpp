#include "adjust_channels.h"

#include <cmath>

/*************************************************
 File: adjust_channels.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: This is the image adjustment object for the channels adjustment.
 *************************************************/

adjustChannels::adjustChannels(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_CHA_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: CHANNELS
 * Lets you modify the intensity of any combination of red, green, or blue channels individually.
 * No adjust and r, g, b values in options required. A value of zero for each channel will be ignored.
 */
void adjustChannels::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "CHANNELS APPLIED" << std::endl;
#endif
	
	if(options_ != NULL){
		int r, g, b, channel;
		float target_r, target_g, target_b;
		try {
			// Try extracting all three colors, skip this adjustment if we can't find them.
			target_r = options_[0] / 50.0F;
			target_g = options_[1] / 50.0F;
			target_b = options_[2] / 50.0F;
			
			// Back to the usual
			for (int i = 0; i < imageSize_; i++)
			{
				channel = i % 3;
				// Separating the subpixels into channels
				if (channel == 0)
				{
					r = pxlPtr[i];
				}
				else if (channel == 1)
				{
					g = pxlPtr[i];
				}
				else
				{
					b = pxlPtr[i];
					
					// Handling the subpixels
					if (target_r != 0) {
						if (target_r > 0) {
							r += (255 - r) * target_r;
						} else {
							r -= r * std::abs(target_r);
						}
					}
					
					if (target_g != 0) {
						if (target_g > 0) {
							g += (255 - g) * target_g;
						} else {
							g -= g * std::abs(target_g);
						}
					}
					
					if (target_b != 0) {
						if (target_b > 0) {
							b += (255 - b) * target_b;
						} else {
							b -= b * std::abs(target_b);
						}
					}
					
					// Saving the subpixels back
					pxlPtr[i-2] = IAdjustment::unclip(r);
					pxlPtr[i-1] = IAdjustment::unclip(g);
					pxlPtr[i]   = IAdjustment::unclip(b);
				}
			}
		} catch (std::exception& e) {}
	}
}