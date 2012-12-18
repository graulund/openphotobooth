#include "adjust_sepia.h"

/*************************************************
 File: adjust_sepia.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: This is the image adjustment object for the sepia adjustment.
 *************************************************/

#include <cmath>

adjustSepia::adjustSepia(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_SEP_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: SEPIA
 * Applies an adjustable sepia filter to the pixel array. Adjust is between 0 and 100.
 */
void adjustSepia::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "SEPIA APPLIED" << std::endl;
#endif
	
	unsigned char r, g, b;
	int channel;
	float x = adjust_ / 100.0F;
	for (int i = 0; i < imageSize_; i++) {
		channel = i % 3;
		// Separating the subpixels into channels
		if (channel == 0) {
			r = pxlPtr[i];
		} else if (channel == 1) {
			g = pxlPtr[i];
		} else {
			b = pxlPtr[i];
			
			r = std::min(255.0F, (r * (1.0F-(0.607F*x))) + (g * (0.769F*x)) + (b * (0.189F*x)));
			g = std::min(255.0F, (r * (0.349F*x)) + (g * (1.0F-(0.314F*x))) + (b * (0.168F*x)));
			b = std::min(255.0F, (r * (0.272F*x)) + (g * (0.534F*x)) + (b * (1.0F-(0.869F*x))));
			
			// Saving the subpixels back
			pxlPtr[i-2] = IAdjustment::unclip(r);
			pxlPtr[i-1] = IAdjustment::unclip(g);
			pxlPtr[i]   = IAdjustment::unclip(b);
		}
	}
}