#ifndef __openPhotoBooth__adjust_tint_red__
#define __openPhotoBooth__adjust_tint_red__

#include "adjustment_interface.h"

#define ADJ_TRE_NAME "Red tint"
#define ADJ_TRE_DEFAULT_ADJUST 20

class adjustTintRed : public IAdjustment
{
private:
	
public:
	adjustTintRed(int, int = ADJ_TRE_DEFAULT_ADJUST);
	// ~adjTintRed();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_tint_red__) */
