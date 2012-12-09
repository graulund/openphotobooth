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
	module_filter(int);

	void brightness(unsigned char *);
	void brightness2(unsigned char *);
	int unclip(int);

	int getFilterCount();
	void getFilters(unsigned char *, int);	
};

#endif
