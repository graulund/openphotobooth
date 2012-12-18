#include "adjust_invert.h"

/*************************************************
 File: adjust_invert.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: This is the image adjustment object for the invert adjustment.
 *************************************************/

adjustInvert::adjustInvert(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_INV_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: INVERT
 * Simply inverts the pixel values. No adjust.
 */
void adjustInvert::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "INVERT APPLIED" << std::endl;
#endif
	
	for (int i = 0; i < imageSize_; i++) {
		pxlPtr[i] = 255 - pxlPtr[i];
	}
}