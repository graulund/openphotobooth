#include "adjust_tint_green.h"

#include <cmath>

/*************************************************
 File: adjust_tint_green.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: This is the image adjustment object for the green tint adjustment.
 *************************************************/

adjustTintGreen::adjustTintGreen(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_TGR_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: GREEN TINT
 * Uniformly shifts the colors in an image towards the green.
 * Adjust is from 0 to 100, the higher the closer.
 */
void adjustTintGreen::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "GREEN TINT APPLIED" << std::endl;
#endif
	
	IAdjustment::colorize(pxlPtr, adjust_, 0, 255, 0);
}