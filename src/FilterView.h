#ifndef __myOpenPhotoBooth__FilterView__
#define __myOpenPhotoBooth__FilterView__ 

#include "View.h"

class FilterView : public View
{
public:
	FilterView(View *, std::string, int, int);

	void drawVideoGrabber(ofVideoGrabber *, float, float);
	void drawFilter(ofTexture *, int);
	void drawFilter(ofTexture, int);
	/* data */
};
#endif