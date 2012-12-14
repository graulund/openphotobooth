#ifndef __openPhotoBooth__adjust_gamma__
#define __openPhotoBooth__adjust_gamma__

#include "adjustment_interface.h"

#define ADJ_GAM_NAME "Gamma"
#define ADJ_GAM_DEFAULT_ADJUST 50

class adjustGamma : public IAdjustment
{
private:
	
public:
	adjustGamma(int, int = ADJ_GAM_DEFAULT_ADJUST);
	// ~adjGamma();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_gamma__) */
