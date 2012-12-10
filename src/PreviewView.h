#ifndef __myOpenPhotoBooth__PreviewView__
#define __myOpenPhotoBooth__PreviewView__

#include "View.h"

 class PreviewView : public View
 {
 public:
 	PreviewView(View *, std::string, int, int);
 	// ~PreviewView();
 	
 	void drawPreview(ofTexture);
	void drawWordBubble(std::string *, ofTrueTypeFont *, int, int);
 };

#endif
