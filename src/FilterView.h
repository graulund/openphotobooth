#ifndef __myOpenPhotoBooth__FilterView__
#define __myOpenPhotoBooth__FilterView__ 

#define FILTER_VIEW_CAM_WIDTH  213
#define FILTER_VIEW_CAM_HEIGHT 160
#define FILTER_PAGE_LENGTH 8

#include "View.h"

class FilterView : public View
{
private:
	int filterOffset_;
	ofTrueTypeFont * typeFont_;
public:
	FilterView(View *, std::string, int, int, int = 0);
	~FilterView();

	void drawVideoGrabber(ofVideoGrabber *, float, float);
	void drawFilter(ofTexture *, std::string *, int);
	//void drawFilter(ofTexture, int);
	void drawFilterSelector(int);
	/* data */
};

#endif
