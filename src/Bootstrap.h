#ifndef __myOpenPhotoBooth__Bootstrap__
#define __myOpenPhotoBooth__Bootstrap__

#include "Controller.h"
#include "FilterController.h"
#include "PreviewController.h"

#include "ofMain.h"

class Bootstrap : public ofBaseApp
{
private:
	bool lockModel_;
	Controller * controller_;
	ofxUICanvas * canvas_;
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int);
	void mousePressed(int, int, int);
	void guiEvent(ofxUIEventArgs &);

	/* data */
};

#endif
