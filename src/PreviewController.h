#ifndef __myOPenPhotoBooth__PreviewController__
#define __myOPenPhotoBooth__PreviewController__

#include "Controller.h"
#include "PreviewModel.h"
#include "PreviewView.h"

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
 	
 	void saveWordBubble();
 };

#endif