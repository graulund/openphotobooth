#ifndef __Module__Adjustment_Saturation__
#define __Module__Adjustment_Saturation__

#include "adjustment_interface.h"

#define NAME "Saturation"
#define DEFAULT_ADJUST 80

class adjustSaturation : public IAdjustment
{
private:

public:
	adjustSaturation(int, int = DEFAULT_ADJUST);
	// ~adjSaturation();

	void apply(unsigned char *);
	// int unclip(int);
	/* data */
};

#endif