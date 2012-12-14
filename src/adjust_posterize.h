#ifndef __openPhotoBooth__adjust_posterize__
#define __openPhotoBooth__adjust_posterize__

#include "adjustment_interface.h"

#define ADJ_POS_NAME "Posterize"
#define ADJ_POS_DEFAULT_ADJUST 80

class adjustPosterize : public IAdjustment
{
private:
	
public:
	adjustPosterize(int, int = ADJ_POS_DEFAULT_ADJUST);
	// ~adjPosterize();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_posterize__) */
