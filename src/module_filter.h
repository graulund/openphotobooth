#ifndef __myOpenPhotoBooth__Module_Filter__
#define __myOpenPhotoBooth__Module_Filter__

#define FILTER_CNT 9

#include "ImageAdjustment.h"
#include <vector>

class module_filter
{
private:
	typedef void (module_filter::*fnctArr)(unsigned char *, int);
	fnctArr ptrArr_[FILTER_CNT];
	int imageSize_;
public:
	// Init
	module_filter(int);

	// Image adjustments
	void brightness(unsigned char *, int = 20); // adjust -100..100
	void saturation(unsigned char *, int = 80); // adjust -100..100
	void vibrance(unsigned char *, int = 80);   // adjust -100..100
	void greyscale(unsigned char *, int = 0);
	void contrast(unsigned char *, int = 50);   // adjust -100..100
	void hue(unsigned char *, int = 50);        // adjust 0..100
	void colorize(unsigned char *, int = 20);   // adjust 0..100, r, g, b
	void invert(unsigned char *, int = 0);
	void sepia(unsigned char *, int = 50);      // adjust 0..100
	void gamma(unsigned char *, int = 50);      // adjust 0.0F..infinity
	void noise(unsigned char *, int = 50);      // adjust 1..100
	void exposure(unsigned char *, int = 80);   // adjust -100..100
	//void channels(...); // more complicated ones
	//void curves(...);
	
	void posterize(unsigned char *, int = 80);
	void vignette(unsigned char *);
	
	// Filter application
	void applyFilter(unsigned char *, std::vector<ImageAdjustment>);
	void applyTestFilter(unsigned char *);
	void applyTestFilter2(unsigned char *);
	
	// Utility
	int unclip(int);
	unsigned char unclip(unsigned char);
	float * rgbToHSV(unsigned char r, unsigned char g, unsigned char b);
	unsigned char * hsvToRGB(float h, float s, float v);
	int getFilterCount();
	void getFilters(unsigned char *, int, int);
	
	// Default filters (move these elsewhere)
	//ImageAdjustment sinCity[4];
	//ImageAdjustment love[5];
};

#endif
