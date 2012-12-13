#include "adjust_saturation.h"

#include <cmath>
#include <algorithm>
#include <iostream>

adjustSaturation::adjustSaturation(int newSize, int newAdjust)
	: IAdjustment(newSize, newAdjust)
{
	name_ = NAME;
}

void adjustSaturation::apply(unsigned char * pxlPtr)
{
	#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "SATURATION APPLYED" << std::endl;
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
