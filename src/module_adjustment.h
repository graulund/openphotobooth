#ifndef __Module__Adjustment__
#define __Module__Adjustment__

class Adjustment
{
private:
	char * name_;
	int adjust_;

public:
	Adjustment();
	~Adjustment();

	virtual void setAdjust(int);

	virtual int getAdjust();
	virtual std::string getName();
	virtual void apply() = 0;
	virtual int unclip();
	virtual unsigned char unclip(unsigned char);
	/* data */
};
#endif