#ifndef __Module__Adjustment_Brightness__
#define __Module__Adjustment_Brightness__

#include "adjustment_interface.h"

#define FILTER_BRI_NAME "Brightness"
#define FILTER_BRI_DEFAULT_ADJUST 20

class adjustBrightness : public IAdjustment
{
private:

public:
	adjustBrightness(int, int = FILTER_BRI_DEFAULT_ADJUST);
	// ~adjBrightness();

	void apply(unsigned char *);
	/* data */
};

#endif