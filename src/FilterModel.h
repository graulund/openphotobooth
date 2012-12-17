#ifndef __myOpenPhotoBooth__FilterModel__
#define __myOpenPhotoBooth__FilterModel__ 

#include "Model.h"

#define CAM_WIDTH 213
#define CAM_HEIGHT 160

#define FILTER_PAGE_LENGTH 8

#define ICON_URL "./GUI/Images/Icon2.png"
#define BTN_LABL_L ""
#define BTN_LABL_M "CNTRL"
#define BTN_LABL_R "Next Page"
#define BTN_NAME_L "FILTERLEFT"
#define BTN_NAME_M "FILTERMIDDLE"
#define BTN_NAME_AM "FILTERACTMIDDLE"
#define BTN_NAME_R "FILTERRIGHT"


class FilterModel : public Model
{
private:
	// unsigned char * pixelArr_[FILTER_CNT];
	unsigned char pixelArrSlot[640*480*3];

	ofTexture * textureArr_;
	std::string * filterNames_;
	int filterOffset_;
	int filtersLeft_;
	unsigned char * BS_;
public:
	FilterModel(Model *, int = 0);
	~FilterModel();

	void init();
	void update();

	float getCamWidth();
	float getCamHeight();
	int getFilterCount();
	std::string getButtonLabel(int);
	ofTexture * getTextureArray();
	std::string * getFilterNames();
	bool selectFilter(int, int);
	
	void saveFilterToFile(module_filter);
	void saveFilterToFile(int);
	void loadFilterFromFile(std::string);
	void loadFilterFromFileUI();
	void loadFiltersInFolder();
};

#endif
