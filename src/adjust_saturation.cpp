#include "adjust_saturation.h"

#include <cmath>
#include <algorithm>
#include <iostream>

/*************************************************
 File: adjust_saturation.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: This is the image adjustment object for the saturation adjustment.
 *************************************************/

adjustSaturation::adjustSaturation(int newSize, int newAdjust)
	: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_SAT_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: SATURATION
 * Range of adjust is from -100 to 100.
 */
void adjustSaturation::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "SATURATION APPLIED" << std::endl;
#endif
	
	float x = -0.01F * adjust_;
	int channel;
	int r, g, b, maxval;

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
			
			// Getting the maximum value of the 3 subpixels
			maxval = std::max(std::max(r, g), b);
			
			// Handling each subpixel individually
			if(r != maxval)
			{
				r += ((maxval - r) * x);
			}
			if(g != maxval)
			{
				g += ((maxval - g) * x);
			}
			if(b != maxval)
			{
				b += ((maxval - b) * x);
			}
			
			// Saving the subpixels back
			pxlPtr[i-2] = IAdjustment::unclip(r);
			pxlPtr[i-1] = IAdjustment::unclip(g);
			pxlPtr[i]   = IAdjustment::unclip(b);
		}
	}
}
