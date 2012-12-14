#include "adjust_contrast.h"

#include <cmath>
#include <algorithm>
#include <iostream>

adjustContrast::adjustContrast(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_CON_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: CONTRAST
 * Range of adjust is from -100 to 100.
 */
void adjustContrast::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "CONTRAST APPLIED" << std::endl;
#endif
	
	float x = pow((float)(adjust_ + 100.0F) / 100.0F, 2.0F);
	float pixel;
	for (int i = 0; i < imageSize_; i++) {
		pixel  = pxlPtr[i] / 255.0F;
		pixel -= 0.5F;
		pixel *= x;
		pixel += 0.5F;
		pixel *= 255.0F;
		
		pxlPtr[i] = IAdjustment::unclip((int)pixel);
	}
}
