#ifndef __adjustment_Interface__
#define __adjustment_Interface__

#include <string>

class IAdjustment
{
protected:
	std::string name_;
	int imageSize_, adjust_;

public:
	IAdjustment(int, int);
	// ~IAdjustment();

	virtual void setAdjust(int);

	virtual int getAdjust();
	virtual std::string getName();
	
	virtual void apply(unsigned char *) = 0;
	virtual int unclip(int);
	virtual unsigned char unclip(unsigned char);
	/* data */
};
#endif