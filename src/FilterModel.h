#ifndef __myOpenPhotoBooth__FilterModel__
#define __myOpenPhotoBooth__FilterModel__ 

#include "Model.h"

#define CAM_WIDTH 213
#define CAM_HEIGHT 160

#define ICON_URL "./GUI/Images/Icon2.png"
#define BTN_LABL_L "Twitter"
#define BTN_LABL_R "Special"

class FilterModel : public Model
{
private:
	unsigned char * pixelArr_[FILTER_CNT];
	unsigned char pixelArrSlot[640*480*3];

	ofTexture * textureArr_;
public:
	FilterModel(Model *);
	~FilterModel();

	void update();

	float getCamWidth();
	float getCamHeight();
	int getFilterCount();
	std::string getButtonLabel(int);
	ofTexture * getTextureArray();
	bool selectFilter(int, int);
};

#endif
