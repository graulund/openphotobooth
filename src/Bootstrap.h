#ifndef __myOpenPhotoBooth__Bootstrap__
#define __myOpenPhotoBooth__Bootstrap__

#include "Controller.h"
#include "FilterController.h"

#include "ofMain.h"

class Bootstrap : public ofBaseApp
{
private:
	Controller * controller_;
	ofxUICanvas * canvas_;
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int);
	void guiEvent(ofxUIEventArgs &);

	/* data */
};

#endif
