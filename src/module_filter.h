#ifndef __myOpenPhotoBooth__Module_Filter__
#define __myOpenPhotoBooth__Module_Filter__

#define __openPhotoBooth__DEBUG_FLAG__

#include "ofxOpenCv.h"

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

	std::string name_;
	std::vector<IAdjustment *> list_;
	std::vector<int> adjusts_;
	std::vector<int *> options_;
	
	bool isBlueScreen_ = false;
	bool isBlueScreenBgSet_ = false;

	/* GLOBAL LIST WITH ALL AVAILABLE ADJUSTMENTS						*/
	static std::vector<IAdjustment *> globalList_;
	/* COUNTER OF FILTER OBJECTS - STATIC TO SHARE THE SAME VAR			*/
	static int filterCount_;
	
	// BLUE SCREEN FILTER RESOURCES (only one instance needed of each, so they are static)
	static bool bsSampleBackground_;
	static int bsThreshold_; // range is 0..255
	static ofxCvColorImage      colorImg;
	static ofxCvGrayscaleImage  grayImage;
	static ofxCvGrayscaleImage 	grayBg;
	static ofxCvGrayscaleImage 	grayDiff;
	static ofxCvContourFinder 	contourFinder;
	static ofImage              bsBackgroundImage;
	static std::string          bsBackgroundExtension;
	static unsigned char *      bsPixels;

public:
	module_filter(std::string, int, bool = false);
	~module_filter();

	bool addAdjustment(std::string, int, int*);
	bool addAdjustment(std::string, int);
	bool addAdjustment(std::string);
	bool removeAdjustment(std::string);
	std::vector<IAdjustment *> getAdjustments();
	std::vector<int> getAdjusts();
	std::vector<int *> getOptions();

	int getFilterCount();
	std::string getName();
	bool getIsBlueScreen();
	
	void bsSampleBackground();
	void bsChangeThreshold(int);
	bool loadBsBackgroundImage();
	unsigned char * getBsPixels();

	void apply(unsigned char *);
}; 

#endif
