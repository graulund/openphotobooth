#ifndef __adjustment_Interface__
#define __adjustment_Interface__

#include <string>
#include <map>

class IAdjustment
{
protected:
	std::string name_;
	int imageSize_, adjust_;
	int * options_;

public:
	IAdjustment(int, int);
	// ~IAdjustment();

	virtual void setAdjust(int);
	virtual void setOptions(int *);

	virtual int getAdjust();
	virtual int * getOptions();
	virtual std::string getName();
	
	virtual void apply(unsigned char *) = 0;
	virtual int unclip(int);
	virtual unsigned char unclip(unsigned char);
	
	void curves(unsigned char *, int, int, int, int, int, int, int, int, int);
	void colorize(unsigned char *, int, unsigned char, unsigned char, unsigned char);
	float * rgbToHSV(unsigned char, unsigned char, unsigned char);
	unsigned char * hsvToRGB(float, float, float);
	
	std::map<int,int> bezier(int, int, int, int, int, int, int, int, int, int);
	/* data */
};
#endif