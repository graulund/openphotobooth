#ifndef __openPhotoBooth__adjust_curves__
#define __openPhotoBooth__adjust_curves__

#include "adjustment_interface.h"

#define ADJ_CUR_NAME "Curves"
#define ADJ_CUR_DEFAULT_ADJUST 0

class adjustCurves : public IAdjustment
{
private:
	
public:
	adjustCurves(int, int = ADJ_CUR_DEFAULT_ADJUST);
	// ~adjChannels();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_curves__) */
