#ifndef __myOpenPhotoBooth__Controller__
#define __myOpenPhotoBooth__Controller__

#include "Model.h"
#include "View.h"

#define CAM_WIDTH 640
#define CAM_HEIGHT 480
#define THUMBNAIL_CNT 5
#define THUMBNAIL_RATIO 100

class Controller
{
protected:
	View * view_;
	Model * model_;
	ofxUICanvas * canvas_;
public:
	Controller();
	Controller(Controller *, bool = false);
	virtual ~Controller();
	void init();
	void initName();

	virtual void update();
	virtual void draw();

	virtual	void keyPressed(int);
	virtual	void mousePressed(int, int, int);
	virtual void guiEvent(ofxUIEventArgs &);

	virtual ofxUICanvas * getCanvas();
	virtual Model * getModel();
	virtual View * getView();
	bool isSelectable(int, int);
	virtual int getFilterOffset();
	/* data */	
};

#endif
