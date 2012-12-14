#ifndef __openPhotoBooth__adjust_vibrance__
#define __openPhotoBooth__adjust_vibrance__

#include "adjustment_interface.h"

#define ADJ_VIB_NAME "Vibrance"
#define ADJ_VIB_DEFAULT_ADJUST 80

class adjustVibrance : public IAdjustment
{
private:
	
public:
	adjustVibrance(int, int = ADJ_VIB_DEFAULT_ADJUST);
	// ~adjVibrance();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_vibrance__) */
