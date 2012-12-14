#ifndef __openPhotoBooth__adjust_channels__
#define __openPhotoBooth__adjust_channels__

#include "adjustment_interface.h"

#define ADJ_CHA_NAME "Channels"
#define ADJ_CHA_DEFAULT_ADJUST 0

class adjustChannels : public IAdjustment
{
private:
	
public:
	adjustChannels(int, int = ADJ_CHA_DEFAULT_ADJUST);
	// ~adjChannels();
	
	void apply(unsigned char *);
	/* data */
};

#endif /* defined(__openPhotoBooth__adjust_channels__) */
