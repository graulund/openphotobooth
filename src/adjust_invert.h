#ifndef __openPhotoBooth__adjust_invert__
#define __openPhotoBooth__adjust_invert__

#include "adjustment_interface.h"

#define ADJ_INV_NAME "Invert"
#define ADJ_INV_DEFAULT_ADJUST 0

class adjustInvert : public IAdjustment
{
private:
	
public:
	adjustInvert(int, int = ADJ_INV_DEFAULT_ADJUST);
	// ~adjInvert();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_invert__) */
