#ifndef __openPhotoBooth__adjust_tint_green__
#define __openPhotoBooth__adjust_tint_green__

#include "adjustment_interface.h"

#define ADJ_TGR_NAME "Green tint"
#define ADJ_TGR_DEFAULT_ADJUST 20

class adjustTintGreen : public IAdjustment
{
private:
	
public:
	adjustTintGreen(int, int = ADJ_TGR_DEFAULT_ADJUST);
	// ~adjTintGreen();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_tint_green__) */
