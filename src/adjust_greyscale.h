#ifndef __openPhotoBooth__adjust_greyscale__
#define __openPhotoBooth__adjust_greyscale__

#include "adjustment_interface.h"

#define ADJ_GRE_NAME "Greyscale"
#define ADJ_GRE_DEFAULT_ADJUST 0

class adjustGreyscale : public IAdjustment
{
private:
	
public:
	adjustGreyscale(int, int = ADJ_GRE_DEFAULT_ADJUST);
	// ~adjGreyscale();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_greyscale__) */
