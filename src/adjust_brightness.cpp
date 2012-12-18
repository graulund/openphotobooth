#include "adjust_brightness.h"

/*************************************************
 File: adjust_brightness.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: This is the image adjustment object for the brightness adjustment.
 *************************************************/

adjustBrightness::adjustBrightness(int newSize, int newAdjust)
	: IAdjustment(newSize, newAdjust)
{
	name_   = FILTER_BRI_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: BRIGHTNESS
 * Range of adjust is from -100 to 100.
 */
void adjustBrightness::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "BRIGHTNESS APPLIED" << std::endl;
#endif

	int x = (int) floor(255.0F * (adjust_ / 100.0F));
	
	for (int i = 0; i < imageSize_; i++)
	{
		pxlPtr[i] = IAdjustment::unclip(pxlPtr[i] + x);
	}
}