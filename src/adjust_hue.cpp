#include "adjust_hue.h"

#include <cmath>

/*************************************************
 File: adjust_hue.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: This is the image adjustment object for the hue adjustment.
 *************************************************/

adjustHue::adjustHue(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_HUE_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: HUE
 * Range is 0 to 100.
 */
void adjustHue::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "HUE APPLIED" << std::endl;
#endif
	
	int channel;
	unsigned char r, g, b;
	unsigned char *rgb;
	float h;
	float *hsv;
	
	for (int i = 0; i < imageSize_; i++) {
		channel = i % 3;
		// Separating the subpixels into channels
		if (channel == 0) {
			r = pxlPtr[i];
		} else if (channel == 1) {
			g = pxlPtr[i];
		} else {
			b = pxlPtr[i];
			
			// Load HSV information
			hsv = IAdjustment::rgbToHSV(r, g, b);
			
			// Change hue
			h  = hsv[0] * 100.0F;
			h += std::abs((float)adjust_);
			h  = ((int)h) % 100; // precision loss?
			h /= 100.0F;
			
			rgb = IAdjustment::hsvToRGB(h, hsv[1], hsv[2]);
			
			// Saving the subpixels back
			pxlPtr[i-2] = IAdjustment::unclip(rgb[0]);
			pxlPtr[i-1] = IAdjustment::unclip(rgb[1]);
			pxlPtr[i]   = IAdjustment::unclip(rgb[2]);
			
			delete[] hsv;
			delete[] rgb;
		}
	}
}