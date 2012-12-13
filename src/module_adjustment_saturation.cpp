#include "adjSaturation.h"

#include <cmath>
#include <algorithm>

adjSaturation::adjSaturation(int newAdjust)
{
	adjust_ = newAdjust;
	name_ = NAME;
	// list_.push_back(*this);
}

void adjSaturation::apply(unsigned char * pxlPtr)
{
	float x = -0.01F * adjust;
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
			pxlPtr[i-2] = unclip(r);
			pxlPtr[i-1] = unclip(g);
			pxlPtr[i]   = unclip(b);
		}
	}
}
