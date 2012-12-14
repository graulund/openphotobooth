#ifndef __myOpenPhotoBooth__Module_Filter__
#define __myOpenPhotoBooth__Module_Filter__

#define __openPhotoBooth__DEBUG_FLAG__

#include "adjustment_interface.h"

#include <string>
#include <vector>

#include <iostream>

/* INCLUDE ALL ADJUST_ HEADERS AVAILABLE THEN LOOK MODULE_FILTER.CPP
   LINE 13																*/
#include "adjust_brightness.h"
#include "adjust_saturation.h"
#include "adjust_contrast.h"
#include "adjust_vibrance.h"
#include "adjust_greyscale.h"
#include "adjust_hue.h"
#include "adjust_invert.h"
#include "adjust_sepia.h"
#include "adjust_gamma.h"
#include "adjust_noise.h"
#include "adjust_clip.h"
#include "adjust_posterize.h"
#include "adjust_channels.h"
#include "adjust_curves.h"
#include "adjust_exposure.h"
#include "adjust_colorize.h"
#include "adjust_tint_red.h"
#include "adjust_tint_green.h"
#include "adjust_tint_blue.h"

class module_filter
{
private:
	int imageSize_;
	/* COUNTER OF FILTER OBJECTS - STATIC TO SHARE THE SAME VAR			*/ 
	static int filterCount_;

	std::string name_;
	std::vector<IAdjustment *> list_;
	std::vector<int> adjusts_;
	std::vector<int *> options_;

	/* GLOBAL LIST WITH ALL AVAILABLE ADJUSTMENTS						*/
	static std::vector<IAdjustment *> globalList_;

public:
	module_filter(std::string, int);
	~module_filter();

	bool addAdjustment(std::string, int, int*);
	bool addAdjustment(std::string, int);
	bool addAdjustment(std::string);
	bool removeAdjustment(std::string);

	int getFilterCount();

	void apply(unsigned char *);
}; 

#endif
