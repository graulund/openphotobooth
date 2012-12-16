#ifndef __myOpenPhotoBooth__FilterView__
#define __myOpenPhotoBooth__FilterView__ 

#define FILTER_VIEW_CAM_WIDTH  213
#define FILTER_VIEW_CAM_HEIGHT 160

#include "View.h"

class FilterView : public View
{
public:
	FilterView(View *, std::string, int, int);
	~FilterView();

	void drawVideoGrabber(ofVideoGrabber *, float, float);
	void drawFilter(ofTexture *, std::string *, int);
	//void drawFilter(ofTexture, int);
	void drawFilterSelector(int);
	/* data */
	ofTrueTypeFont * typeFont_;
};

#endif
