#include "adjust_greyscale.h"

/*************************************************
 File: adjust_greyscale.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: This is the image adjustment object for the greyscale adjustment.
 *************************************************/

adjustGreyscale::adjustGreyscale(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_GRE_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: GREYSCALE
 * No adjust in this. Uses factors directly relating to how the human eye perceives color and values.
 * Derived from http://www.phpied.com/image-fun/
 */
void adjustGreyscale::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "GREYSCALE APPLIED" << std::endl;
#endif
	
	int channel;
	unsigned char r, g, b, maxval;
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
			
			// Calculate the average value of the channels using the special factors
			avgval = IAdjustment::unclip((int)(0.3 * r + 0.59 * g + 0.11 * b));
			
			// Saving the subpixels back
			pxlPtr[i-2] = avgval;
			pxlPtr[i-1] = avgval;
			pxlPtr[i]   = avgval;
		}
	}
}
