#ifndef __openPhotoBooth__adjust_tint_blue__
#define __openPhotoBooth__adjust_tint_blue__

#include "adjustment_interface.h"

#define ADJ_TBL_NAME "Blue tint"
#define ADJ_TBL_DEFAULT_ADJUST 20

class adjustTintBlue : public IAdjustment
{
private:
	
public:
	adjustTintBlue(int, int = ADJ_TBL_DEFAULT_ADJUST);
	// ~adjTintBlue();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_tint_blue__) */
