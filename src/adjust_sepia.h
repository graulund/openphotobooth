#ifndef __openPhotoBooth__adjust_sepia__
#define __openPhotoBooth__adjust_sepia__

#include "adjustment_interface.h"

#define ADJ_SEP_NAME "Sepia"
#define ADJ_SEP_DEFAULT_ADJUST 50

class adjustSepia : public IAdjustment
{
private:
	
public:
	adjustSepia(int, int = ADJ_SEP_DEFAULT_ADJUST);
	// ~adjSepia();
	
	void apply(unsigned char *);
	/* data */
};


#endif /* defined(__openPhotoBooth__adjust_sepia__) */
