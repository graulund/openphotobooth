#ifndef __openPhotoBooth__adjust_exposure__
#define __openPhotoBooth__adjust_exposure__

#include "adjustment_interface.h"

#define ADJ_EXP_NAME "Exposure"
#define ADJ_EXP_DEFAULT_ADJUST 50

class adjustExposure : public IAdjustment
{
private:
	
public:
	adjustExposure(int, int = ADJ_EXP_DEFAULT_ADJUST);
	// ~adjSepia();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_exposure__) */
