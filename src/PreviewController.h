#ifndef __myOPenPhotoBooth__PreviewController__
#define __myOPenPhotoBooth__PreviewController__

#include "Controller.h"
#include "PreviewModel.h"
#include "PreviewView.h"

#define USE_FACEBOOK 1

class PreviewController : public Controller
 {
 private:
 	ofImage * testImage_;
 public:
 	PreviewController(Controller *);
 	// ~PreviewController();

 	void draw();

 	void keyPressed(int);
 	void mousePressed(int, int, int);
 	void guiEvent(ofxUIEventArgs &);
 	
 	std::string saveWordBubble(int = 0);
 };

#endif