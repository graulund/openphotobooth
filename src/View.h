#ifndef __myOpenPhotoBooth__View__
#define __myOpenPhotoBooth__View__ 

#include "ofxUI.h"

class View
{
protected:
	ofxUILabelToggle * buttonLeft_, * buttonRight_;
	ofxUIImageButton * buttonCenter_;
public:
	View(std::string, int, int, ofxUICanvas *);
	View(View *, std::string, int, int);
	void init(std::string, int, int, ofxUICanvas *);

	virtual void drawVideoGrabber(ofVideoGrabber *, float, float);
	virtual void drawThumbnails(ofImage *, int, int);
	virtual void drawThumbnailSelector(int);
	virtual void drawFilter(ofTexture);

	/* setter & getter */
	virtual void setButtonLabel(int, std::string);
	virtual void setButtonName(int, std::string);
	/* data */
};

#endif
