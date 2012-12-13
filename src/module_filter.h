#ifndef __myOpenPhotoBooth__Module_Filter__
#define __myOpenPhotoBooth__Module_Filter__

#define __openPhotoBooth__DEBUG_FLAG__

#include "adjustment_interface.h"

#include <string>
#include <vector>

#include <iostream>

/* INCLUDE ALL ADJUST_ HEADERS AVAILABLE THEN LOOK MODULE_FILTER.CPP
   LINE 13																*/
#include "adjust_saturation.h"
#include "adjust_brightness.h"

class module_filter
{
private:
	int imageSize_;
	/* COUNTER OF FILTER OBJECTS - STATIC TO SHARE THE SAME VAR			*/ 
	static int filterCount_;

	std::string name_;
	std::vector<IAdjustment *> list_;

	/* GLOBAL LIST WITH ALL AVAIABLE ADJUSTMENTS						*/
	static std::vector<IAdjustment *> globalList_;

public:
	module_filter(std::string, int);
	~module_filter();

	bool addAdjustment(std::string);
	bool removeAdjustment(std::string);

	int getFilterCount();

	void apply(unsigned char *);
}; 

#endif
