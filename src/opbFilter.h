//
//  opbFilter.h
//  openPhotoBooth
//
//  Created by Andreas Graulund on 01/12/12.
//
//

#ifndef __openPhotoBooth__opbFilter__
#define __openPhotoBooth__opbFilter__

#include <iostream>

#endif /* defined(__openPhotoBooth__opbFilter__) */


class opbFilter
{
public:
	static int unclip(int value);
	static void brightness(unsigned char * pixels, int length, int adjust);
private:
	opbFilter () {} // only static class
};
