#include "adjust_curves.h"

#include <cmath>
#include <map>

adjustCurves::adjustCurves(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_CUR_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: CURVES
 * Curves implementation using bezier curves.
 * No adjust. Nine values required in options array: selectedChannel, x0, y0, x1, y1, x2, y2, x3, y3.
 * x2 and y2 can be omitted using -1 for these coordinates.
 * Selected channel to modify with the curves is either:
 *   0 => r,
 *   1 => g,
 *   2 => b,
 *   3 => rgb (all channels)
 */
void adjustCurves::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "CURVES APPLIED" << std::endl;
#endif
	
	if(options_ != NULL){
		try {
			IAdjustment::curves(pxlPtr, options_[0], options_[1], options_[2], options_[3], options_[4], options_[5], options_[6], options_[7], options_[8]);
		} catch (std::exception& e) {}
	}
}