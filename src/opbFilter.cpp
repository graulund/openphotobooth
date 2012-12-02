//
//  opbFilter.cpp
//  openPhotoBooth
//
//  Created by Andreas Graulund on 01/12/12.
//
//

#include "opbFilter.h"
#include <math.h>
#include <algorithm>
using namespace std;

int opbFilter::unclip(int value){
	return min(255, max(0, value));
}

void opbFilter::brightness(unsigned char * pixels, int length, int adjust){
	adjust = (int)floor(255.0 * (adjust / 100.0));
	for (int i = 0; i < length; i++) {
		pixels[i] = opbFilter::unclip(pixels[i] + adjust);
	}
}
