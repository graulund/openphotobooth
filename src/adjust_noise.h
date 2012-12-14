#ifndef __openPhotoBooth__adjust_noise__
#define __openPhotoBooth__adjust_noise__

#include "adjustment_interface.h"

#define ADJ_NOI_NAME "Noise"
#define ADJ_NOI_DEFAULT_ADJUST 50

class adjustNoise : public IAdjustment
{
private:
	
public:
	adjustNoise(int, int = ADJ_NOI_DEFAULT_ADJUST);
	// ~adjNoise();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_noise__) */
