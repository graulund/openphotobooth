#ifndef __Module__Adjustment_Brightness__
#define __Module__Adjustment_Brightness__

#include "adjustment_interface.h"

#define NAME "Brightness"
#define DEFAULT_ADJUST 20

class adjustBrightness : public IAdjustment
{
private:

public:
	adjustBrightness(int, int = DEFAULT_ADJUST);
	// ~adjSaturation();

	void apply(unsigned char *);
	// int unclip(int);
	/* data */
};

#endif