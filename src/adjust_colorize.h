#ifndef __openPhotoBooth__adjust_colorize__
#define __openPhotoBooth__adjust_colorize__

#include "adjustment_interface.h"

#define ADJ_COL_NAME "Colorize"
#define ADJ_COL_DEFAULT_ADJUST 30

class adjustColorize : public IAdjustment
{
private:
	
public:
	adjustColorize(int, int = ADJ_COL_DEFAULT_ADJUST);
	// ~adjColorize();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_colorize__) */
