#ifndef __myOpenPhotoBooth__View__
#define __myOpenPhotoBooth__View__ 

#include "ofxUI.h"
#include <vector>

class View
{
protected:
	ofxUILabelToggle * buttonLeft_, * buttonRight_;
	ofxUIImageButton * buttonCenter_;
	ofxUILabelButton * actButtonCenter_;
	ofxUIDropDownList * buttonDrop_;
	ofxUIDropDownList * editorDrop_;
	std::vector<string> buttonItems_;
	std::vector<string> editorItems_;
public:
	View(std::string, int, int, ofxUICanvas *);
	View(View *, std::string, int, int);
	// virtual ~View();
	void init(std::string, int, int, ofxUICanvas *);

	virtual void drawVideoGrabber(ofVideoGrabber *, float, float);
	virtual void drawThumbnails(ofImage *, int, int);
	virtual void drawThumbnailSelector(int);
	virtual void drawFilter(ofTexture);

	/* setter & getter */
	virtual void setButtonLabel(int, std::string);
	virtual void setButtonName(int, std::string);
	virtual void clearButtonStatus(int);
	/* data */
};

#endif
