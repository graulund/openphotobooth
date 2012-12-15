#ifndef __myOpenPhotoBooth__FilterView__
#define __myOpenPhotoBooth__FilterView__ 

#include "View.h"

class FilterView : public View
{
public:
	FilterView(View *, std::string, int, int);
	~FilterView();

	void drawVideoGrabber(ofVideoGrabber *, float, float);
	void drawFilter(ofTexture *, int);
	void drawFilter(ofTexture, int);
	void drawFilterSelector(int);
	/* data */
};

#endif
