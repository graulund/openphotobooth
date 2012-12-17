#include "FilterModel.h"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstdlib>

FilterModel::FilterModel(Model * oldModel, int offset) : Model(oldModel, true), filterOffset_(offset)
{
	// Determining the amount of filters we're displaying on this page (given by offset)
	
	int fltrCnt  = filterVector_->size();
	filtersLeft_ = std::min(FILTER_PAGE_LENGTH, fltrCnt - filterOffset_);

	textureArr_  = new ofTexture[filtersLeft_];
	filterNames_ = new std::string[filtersLeft_];
	
	std::cout << "FILTER FROM " << filterOffset_ << " TO " << (filterOffset_ + filtersLeft_) << std::endl;
	
	// Allocating textures for filter previews
	
	for (int i = 0; i < filtersLeft_; i++)
	{
		textureArr_[i].allocate(640, 480, GL_RGB);
		filterNames_[i] = filterVector_->at(filterOffset_ + i).getName();
	}
	
	// Allocating special blue screen filter pixel array
	int subpixels = 640*480*3;
	BS_ = new unsigned char[subpixels];
	for (int i = 0; i < subpixels; i++) {
		int channel = i % 3;
		BS_[i] = channel == 2 ? 255 : 0; // Blue!
	}

	init();		
}

/**
 * @TODO
 * DEFAULT DECONSTRUCTER TO CLEAN UP THE MESS - NEEDS WORK BECAUSE IT
 * DOESNT WORK RIGHT NOW!
 */
FilterModel::~FilterModel()
{
	delete modFilter_;
	delete textureArr_;
//	delete pixelArr_;
}

/**
 * [FilterModel::init description]
 */
void FilterModel::init()
{
	btnLabelL_ = BTN_LABL_L;
	btnLabelM_ = BTN_LABL_M;
	btnLabelR_ = BTN_LABL_R;	

	btnNameL_ = BTN_NAME_L;
	btnNameM_ = BTN_NAME_M;
	btnNameAM_ = BTN_NAME_AM;
	btnNameR_ = BTN_NAME_R;
}

/**
 * UPDATE CALLED BY CONTROLLER
 */
void FilterModel::update()
{
	int fi = 0;
	vidGrabber_->update();

	for (int i = 0; i < filtersLeft_; i++)
	{
		if (vidGrabber_->isFrameNew())
		{
			fi = filterOffset_ + i;
		 	if(filterVector_->at(fi).getIsBlueScreen()){
				// Special blue screen blue square preview image
				textureArr_[i].loadData(BS_, 640, 480, GL_RGB);
			} else {
				/* COPY "FRESH" PICTURE TO pixelArrSlot SO THAT EVERY FILTER
				 GOT A UNMODIFIED VERSION									*/
				memcpy(pixelArrSlot, vidGrabber_->getPixels(), 640*480*3);
				/* APPLY EVERY AVAILABLE FILTER TO THIS FRESH COPYS			*/
				filterVector_->at(fi).apply(pixelArrSlot);
				/* TRANSFORM PIXELS TO TEXTURE TO DRAW IT ON THE SCREEN		*/
				textureArr_[i].loadData(pixelArrSlot, 640, 480, GL_RGB);
			}
	 	}
	}
}

/**
 * RETURNS THE CAM_WIDTH, UNFORTUNATELY UNSED DUE HARD CODING =(
 */
float FilterModel::getCamWidth()
{
	return float(CAM_WIDTH);
}

/**
 * [FilterModel::getCamHeight description]
 * @return [description]
 */
float FilterModel::getCamHeight()
{
	return float(CAM_HEIGHT);
}

/**
 * [FilterModel::getFilterCount description]
 * @return [description]
 */
int FilterModel::getFilterCount()
{
	return filterVector_->size();
}

/**
 * [FilterModel::getButtonLabel description]
 * @param  btnNr [description]
 * @return       [description]
 */
std::string FilterModel::getButtonLabel(int btnNr)
{
	if (btnNr == 1)
	{
		return BTN_LABL_L;
	}
	else if (btnNr == 2)
	{
		return BTN_LABL_R;
	}
}

/**
 * [FilterModel::getTextureArray description]
 * @return [description]
 */
ofTexture * FilterModel::getTextureArray()
{
	return textureArr_;
}

/**
 * [FilterModel::getFilterNames description]
 * @return [description]
 */
std::string * FilterModel::getFilterNames()
{
	return filterNames_;
}

/**
 * [FilterModel::selectFilter description]
 * @param  x [description]
 * @param  y [description]
 * @return   [description]
 */
bool FilterModel::selectFilter(int x, int y)
{
	bool isSelectable = false;
	int fltrCnt = filterVector_->size();
	
	// ZERO IS RESERVED FOR THE NO-FILTER, WHICH IS ALWAYS IN THE MIDDLE (x=1,y=1).
	// THIS IS WHY SOME NUMBERS ARE SHIFTED IN THE RESULTS.

	if (x <= 640 && y <= 480)
	{
		if (y <= 160)
		{
			if (x > 426 && fltrCnt >= 3 + filterOffset_)
			{
				filterSelector_ = 3 + filterOffset_;
				isSelectable = true;
			}
			if (x <= 426 && fltrCnt >= 2 + filterOffset_)
			{
				filterSelector_ = 2 + filterOffset_;
				isSelectable = true;
			}
			if (x <= 213 && fltrCnt >= 1 + filterOffset_)
			{
				filterSelector_ = 1 + filterOffset_;
				isSelectable = true;
			}
		}
		else if (y <= 320)
		{
			if (x > 426 && fltrCnt >= 5 + filterOffset_)
			{
				filterSelector_ = 5 + filterOffset_;
				isSelectable = true;
			}
			if (x <= 426)
			{
				filterSelector_ = 0; // THE MIDDLE <-----
				isSelectable = true;
			}
			if (x <= 213 && fltrCnt >= 4 + filterOffset_)
			{
				filterSelector_ = 4 + filterOffset_;
				isSelectable = true;
			}
		}
		else
		{
			if (x > 426 && fltrCnt >= 8 + filterOffset_)
			{
				filterSelector_ = 8 + filterOffset_;
				isSelectable = true;
			}
			if (x <= 426 && fltrCnt >= 7 + filterOffset_)
			{
				filterSelector_ = 7 + filterOffset_;
				isSelectable = true;
			}
			if (x <= 213 && fltrCnt >= 6 + filterOffset_)
			{
				filterSelector_ = 6 + filterOffset_;
				isSelectable = true;
			}			
		}
	}
}

void FilterModel::saveFilterToFile(module_filter filter){
	if (&filter == NULL) {
		return;
	}
	// The filename
	std::string filename = filter.getName() + ".pbf";
	// The file reference
	std::ofstream file (filename.c_str());
	// The filter lists
	std::vector<IAdjustment *> list = filter.getAdjustments();
	std::vector<int> adjusts        = filter.getAdjusts();
	std::vector<int *> options      = filter.getOptions();
	// Let's go
	if (file.is_open()) {
		file << filter.getName() << std::endl;
		for (int i = 0; i < list.size(); i++) {
			file << list.at(i)->getName();
			if (adjusts.at(i) > 0) {
				file << " " << adjusts.at(i);
			}
			if (options.at(i)) {
				// Assume a list of options has three elements (@todo more flexible)
				for (int j = 0; j < 3; j++) {
					file << " " << options.at(i)[j];
				}
			}
			file << std::endl;
		}
	}
	file.close();
	// Done!
}
void FilterModel::saveFilterToFile(int filterSelector){
	FilterModel::saveFilterToFile(filterVector_->at(filterSelector - 1));
}
void FilterModel::loadFilterFromFile(std::string filename){
	// The file
	std::ifstream file (filename.c_str());
	// The loading and splitting mechanisms
	char line[256];
	std::vector<std::string> tokens;
	int i = 0;
	module_filter* filter;
	bool filterDefined = false;
	// The adjustments being loaded
	std::string filtername;
	std::string adjname;
	int adjust;
	// Let's go!
	if (file.is_open()) {
		while (file.good()) {
			// Read one line
			file.getline(line, 256);
			string sline(line);
			// If it's the first line, it's the filter name
			if (i == 0) {
				filtername = sline;
				// And now we have the filter being loaded
				filter = new module_filter(filtername, 640*480*3);
				filterDefined = true;
			} else {
				// Split it up by space
				std::istringstream iss(sline);
				std::copy(istream_iterator<string>(iss),
						  istream_iterator<string>(),
						  back_inserter<vector<string> >(tokens));
				// Handle each token
				if (tokens.size() > 0) {
					// Name
					adjname = tokens.at(0);
					// Options
					std::vector<int> options; // always a new vector, otherwise we get overwritten options!!!
					for (int i = 1; i < tokens.size(); i++) {
						if (i == 1) {
							adjust = atoi(tokens.at(i).c_str());
						} else {
							options.push_back(atoi(tokens.at(i).c_str()));
						}
					}
					// Add this image adjustment
					if (options.size() > 0) {
						filter->addAdjustment(adjname, adjust, &options[0]);
					} else {
						filter->addAdjustment(adjname, adjust);
					}
					// Clear
					adjust = 0;
				}
				// Clear
				tokens.clear();
			}
			i++;
		}
		if (filterDefined) {
			// ADD THIS FILTER TO OUR LIST OF FILTERS!
			filterVector_->push_back(*filter);
		}
	}
}
void FilterModel::loadFilterFromFileUI(){
	//Open the Open File Dialog
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a Photo Booth Filter (PBF) file");
	
	//Check if the user opened a file
	if (openFileResult.bSuccess){
		
		ofLogVerbose("User selected a file");
		
		//We have a file, check it and process it
		ofLogVerbose("getName(): "  + openFileResult.getName());
		ofLogVerbose("getPath(): "  + openFileResult.getPath());
		
		
		loadFilterFromFile(openFileResult.getPath());
	}
	else
	{
		ofLogVerbose("User hit cancel");
	}
}
void FilterModel::loadFiltersInFolder(){
	// Idea: Load all filters in the data folder
}
