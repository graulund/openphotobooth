#ifndef __Module__Adjustment_Saturation__
#define __Module__Adjustment_Saturation__

#include "module_adjustment.h"

#define NAME "Saturation"
#define DEFAULT_ADJUST 80

class adjSaturation : public IAdjustment
{
private:

public:
	adjSaturation(int = DEFAULT_ADJUST);
	// ~adjSaturation();

	void apply(char *);
	int unclip(int);
	/* data */
};

#endif