#ifndef __openPhotoBooth__adjust_hue__
#define __openPhotoBooth__adjust_hue__

#include "adjustment_interface.h"

#define ADJ_HUE_NAME "Hue"
#define ADJ_HUE_DEFAULT_ADJUST 50

class adjustHue : public IAdjustment
{
private:
	
public:
	adjustHue(int, int = ADJ_HUE_DEFAULT_ADJUST);
	// ~adjHue();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_hue__) */
