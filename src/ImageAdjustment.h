#ifndef __openPhotoBooth__ImageAdjustment__
#define __openPhotoBooth__ImageAdjustment__

#include <iostream>
#include <string.h>

using namespace std;

class ImageAdjustment
{
public:
	// IMAGE ADJUSTMENT VARIABLES
	string name;
	// Applicable on most adjustments:
	int adjust;
	// Only applicable on few adjustments:
	//float fadjust;         // <-- gamma (instead of adjust)
	unsigned char r, g, b; // <-- colorize
	
	// CONSTRUCTORS
	ImageAdjustment(string);
	ImageAdjustment(string, int);
	//ImageAdjustment(string, float);
	ImageAdjustment(string, int, unsigned char, unsigned char, unsigned char);
	

	
};

#endif /* defined(__openPhotoBooth__ImageAdjustment__) */
