#ifndef __openPhotoBooth__adjust_contrast__
#define __openPhotoBooth__adjust_contrast__

#include "adjustment_interface.h"

#define ADJ_CON_NAME "Contrast"
#define ADJ_CON_DEFAULT_ADJUST 50

class adjustContrast : public IAdjustment
{
private:
	
public:
	adjustContrast(int, int = ADJ_CON_DEFAULT_ADJUST);
	// ~adjContrast();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_contrast__) */
