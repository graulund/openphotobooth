#ifndef __myOpenPhotoBooth__FilterController__
#define __myOpenPhotoBooth__FilterController__ 

#include "Controller.h"
#include "FilterModel.h"
#include "FilterView.h"

class FilterController : public Controller
{
private:
	ofTexture myTexture;
	int filterOffset_;
public:
	FilterController(Controller *, int = 0);
	~FilterController();
	
	void draw();
	void update();

	void guiEvent(ofxUIEventArgs &);
	void mousePressed(int, int, int);
	void keyPressed(int);
	
	int getFilterOffset();
	void setFilterOffset(int);

	/* data */
};

#endif
