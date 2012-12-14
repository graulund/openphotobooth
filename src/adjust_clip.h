#ifndef __openPhotoBooth__adjust_clip__
#define __openPhotoBooth__adjust_clip__

#include "adjustment_interface.h"

#define ADJ_CLI_NAME "Clip"
#define ADJ_CLI_DEFAULT_ADJUST 70

class adjustClip : public IAdjustment
{
private:
	
public:
	adjustClip(int, int = ADJ_CLI_DEFAULT_ADJUST);
	// ~adjClip();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_clip__) */
