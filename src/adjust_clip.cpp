#include "adjust_clip.h"

/*************************************************
 File: adjust_clip.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: This is the image adjustment object for the clip adjustment.
 *************************************************/

#include <cmath>

adjustClip::adjustClip(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_CLI_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: CLIP
 * Clips a color to maximum values when it falls outside of the range specified in adjust.
 * Adjust is between 0 and 100.
 */
void adjustClip::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "CLIP APPLIED" << std::endl;
#endif
	
	float x = std::abs(adjust_) * 2.55F;
	
	for (int i = 0; i < imageSize_; i++) {
		if (pxlPtr[i] > 255.0F - x) {
			pxlPtr[i] = 255;
		} else if (pxlPtr[i] < x){
			pxlPtr[i] = 0;
		}
	}
}