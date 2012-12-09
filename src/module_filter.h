#ifndef __myOpenPhotoBooth__Module_Filter__
#define __myOpenPhotoBooth__Module_Filter__

#define FILTER_CNT 4

class module_filter
{
private:
	typedef void (module_filter::*fnctArr)(unsigned char *);
	fnctArr ptrArr_[FILTER_CNT];
	int imageSize_;
public:
	// Init
	module_filter(int);

	// Image adjustments
	void brightness(unsigned char *);
	void saturation(unsigned char *);
	void vibrance(unsigned char *);
	void greyscale(unsigned char *);
	void contrast(unsigned char *);
	void hue(unsigned char *);
	void colorize(unsigned char *);
	void invert(unsigned char *);
	void sepia(unsigned char *);
	void gamma(unsigned char *);
	void noise(unsigned char *);
	void exposure(unsigned char *);
	//void channels(...); // more complicated ones
	//void curves(...);
	
	// Utility
	int unclip(int);
	unsigned char unclip(unsigned char);
	float * rgbToHSV(unsigned char r, unsigned char g, unsigned char b);
	unsigned char * hsvToRGB(float h, float s, float v);
	int getFilterCount();
	void getFilters(unsigned char *, int);	
};

#endif
