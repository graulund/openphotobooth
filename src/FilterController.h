#ifndef __myOpenPhotoBooth__FilterController__
#define __myOpenPhotoBooth__FilterController__ 

#include "Controller.h"
#include "FilterModel.h"
#include "FilterView.h"

class FilterController : public Controller
{
private:
	ofTexture myTexture;
public:
	FilterController(Controller *);
	~FilterController();
	
	void draw();
	void update();

	void guiEvent(ofxUIEventArgs &);
	void mousePressed(int, int, int);
	void keyPressed(int);

	/* data */
};

#endif
