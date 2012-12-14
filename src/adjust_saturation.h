#ifndef __Module__Adjustment_Saturation__
#define __Module__Adjustment_Saturation__

#include "adjustment_interface.h"

#define ADJ_SAT_NAME "Saturation"
#define ADJ_SAT_DEFAULT_ADJUST 80

class adjustSaturation : public IAdjustment
{
private:

public:
	adjustSaturation(int, int = ADJ_SAT_DEFAULT_ADJUST);
	// ~adjSaturation();

	void apply(unsigned char *);
	/* data */
};

#endif