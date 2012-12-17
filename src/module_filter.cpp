#include "module_filter.h"

#ifndef __INIT_STATIC_VARS__
#define __INIT_STATIC_VARS__
	int module_filter::filterCount_ = 0;
	std::vector<IAdjustment *> module_filter::globalList_ =
		std::vector<IAdjustment *>();
	bool module_filter::bsSampleBackground_ = false;
	int module_filter::bsThreshold_         = 40;
//	ofxCvColorImage      module_filter::colorImg       = *new ofxCvColorImage();
//	ofxCvGrayscaleImage  module_filter::grayImage      = *new ofxCvGrayscaleImage();
//	ofxCvGrayscaleImage  module_filter::grayBg         = *new ofxCvGrayscaleImage();
//	ofxCvGrayscaleImage  module_filter::grayDiff       = *new ofxCvGrayscaleImage();
//	ofxCvContourFinder 	 module_filter::contourFinder  = *new ofxCvContourFinder();

	ofxCvColorImage      module_filter::colorImg;
	ofxCvGrayscaleImage  module_filter::grayImage;
	ofxCvGrayscaleImage  module_filter::grayBg;
	ofxCvGrayscaleImage  module_filter::grayDiff;
	ofxCvContourFinder 	 module_filter::contourFinder;
	ofImage              module_filter::bsBackgroundImage;
	std::string          module_filter::bsBackgroundExtension = "";
	unsigned char *      module_filter::bsPixels ;//= new unsigned char[640*480*3];
#endif

bool filterSetUp = false;

module_filter::module_filter(std::string newName, int newImageSize, bool isBlueScreen)
	: name_(newName), imageSize_(newImageSize), isBlueScreen_(isBlueScreen)
{
	// STATIC CHANGES: -------------------------------------------------
	/* INCREASE FILTER COUNT WITH EVERY NEW MODULE_FILTER OBJECT	  */
	filterCount_++;

	/* PUSH ALL AVAILABLE ADJUSTMENTS TO THE "GLOBAL LIST"			  */
	if(!filterSetUp){
		globalList_.push_back(new adjustBrightness(imageSize_));
		globalList_.push_back(new adjustSaturation(imageSize_));
		globalList_.push_back(new adjustContrast(imageSize_));
		globalList_.push_back(new adjustVibrance(imageSize_));
		globalList_.push_back(new adjustGreyscale(imageSize_));
		globalList_.push_back(new adjustHue(imageSize_));
		globalList_.push_back(new adjustInvert(imageSize_));
		globalList_.push_back(new adjustSepia(imageSize_));
		globalList_.push_back(new adjustGamma(imageSize_));
		globalList_.push_back(new adjustNoise(imageSize_));
		globalList_.push_back(new adjustClip(imageSize_));
		globalList_.push_back(new adjustPosterize(imageSize_));
		globalList_.push_back(new adjustChannels(imageSize_));
		globalList_.push_back(new adjustCurves(imageSize_));
		globalList_.push_back(new adjustExposure(imageSize_));
		globalList_.push_back(new adjustColorize(imageSize_));
		globalList_.push_back(new adjustTintRed(imageSize_));
		globalList_.push_back(new adjustTintGreen(imageSize_));
		globalList_.push_back(new adjustTintBlue(imageSize_));
		// Allocate images for BS filter
		colorImg.allocate(640,480);
		grayImage.allocate(640,480);
		grayBg.allocate(640,480);
		grayDiff.allocate(640,480);
		// Done!
		filterSetUp = true;
	}
}

module_filter::~module_filter()
{
	if (filterCount_ > 0)
	{
		filterCount_--;
	}
	else
	{
		std::cout 	<< "FILTERCOUNT ERROR: module_filter.cpp" 
					<< std::endl;
	}
}

bool module_filter::addAdjustment(std::string adjustmentName, int adjust, int * options)
{
	for (std::vector<IAdjustment *>::iterator it = globalList_.begin();
		 it != globalList_.end(); it++)
	{
		if ((*it)->getName() == adjustmentName)
		{
			adjusts_.push_back(adjust);
			options_.push_back(options);
			list_.push_back(*it);
			return true;
		}
	}
	return false;
}

bool module_filter::addAdjustment(std::string adjustmentName, int adjust)
{
	return module_filter::addAdjustment(adjustmentName, adjust, NULL);
}

bool module_filter::addAdjustment(std::string adjustmentName)
{
	return module_filter::addAdjustment(adjustmentName, 0);
}

bool module_filter::removeAdjustment(std::string adjustmentName)
{
	std::vector<int>::iterator at = adjusts_.begin();
	for (std::vector<IAdjustment *>::iterator it = list_.begin();
		it != list_.end(); it++, at++)
	{
		if ((*it)->getName() == adjustmentName)
		{
			list_.erase(it);
			adjusts_.erase(at);
			return true;
		}
	}
	return false;
}

int module_filter::getFilterCount()
{
	return filterCount_;
}

std::string module_filter::getName()
{
	return name_;
}

bool module_filter::getIsBlueScreen(){
	return isBlueScreen_;
}

void module_filter::bsSampleBackground(){
	bsSampleBackground_ = true;
}

void module_filter::bsChangeThreshold(int increment){
	bsThreshold_ = std::max(0, std::min(255, bsThreshold_ + increment));
}

unsigned char * module_filter::getBsPixels(){
	return bsPixels;
}

bool module_filter::loadBsBackgroundImage(){
	bool successfullyLoaded = false;
	//Open the Open File Dialog
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a jpg or png");
	
	//Check if the user opened a file
	if (openFileResult.bSuccess){
		
		ofLogVerbose("User selected a file");
		
		//We have a file, check it and process it
		ofLogVerbose("getName(): "  + openFileResult.getName());
		ofLogVerbose("getPath(): "  + openFileResult.getPath());
		
		ofFile file (openFileResult.getPath());
		
		if (file.exists())
		{
			ofLogVerbose("The file exists - now checking the type via file extension");
			string fileExtension = ofToUpper(file.getExtension());
			
			//We only want images
			if (fileExtension == "JPG" || fileExtension == "PNG")
			{
				//Save the file extension to use when we save out
				bsBackgroundExtension = fileExtension;
				
				//Load the selected image
				ofImage image;
				image.loadImage(openFileResult.getPath());
				cout << "RESIZING" << endl;
				if (image.getWidth() > 640)
				{
					image.resize(640, (640 / image.getWidth()) * image.getHeight());
					cout << "RESIZE WIDTH" << endl;
				}
				else if (image.getHeight() > 480)
				{
					cout << "RESIZE HEIGHT" << endl;
					image.resize((480 / image.getHeight()) * image.getWidth(), 480);
				}
				bsBackgroundImage  = image;
				successfullyLoaded = true;
			}
		}

		
	}
	else
	{
		ofLogVerbose("User hit cancel");
	}
	
	// Create a quick blue background if we can't load something
	if (!successfullyLoaded) {
		int subpixels = 640*480*3;
		unsigned char * bluescreen = new unsigned char[subpixels];
		for (int i = 0; i < subpixels; i++) {
			int channel = i % 3;
			bluescreen[i] = channel == 2 ? 255 : 0; // Blue!
		}
		ofImage image;
		image.setFromPixels(bluescreen, 640, 480, OF_IMAGE_COLOR);
		bsBackgroundExtension = "PNG";
	}
	
	return successfullyLoaded;
}

void module_filter::apply(unsigned char * pxlArr)
{
	//std::cout << "APPLYING FILTER ";
	if (isBlueScreen_) {
		std::cout << "(BS)" << std::endl;
		
		// Special filter actions for the blue screen filter
		
		// --> Background detection: The below is adapted from the OpenCV example
		colorImg.setFromPixels(pxlArr, 640,480);
		grayImage = colorImg;
		if (bsSampleBackground_){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bsSampleBackground_ = false;
		}
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(bsThreshold_);
		// Find contours: Finds those which are between the size of 20 pixels and 1/3 the width times height pixels.
		// "Find holes" is set to true, so we will get interior contours as well.
		contourFinder.findContours(grayDiff, 20, (640*480)/3, 10, true);
		
		std::cout << "IMAGE DIMENSIONS " << colorImg.getWidth() << "x" << colorImg.getHeight() << ", " << grayImage.getWidth() << "x" << grayImage.getHeight() << ", " << grayDiff.getWidth() << "x" << grayDiff.getHeight() << std::endl;
		
		// --> Combination: This is the new part.
		//     Combines pixels from one array (live camera) with another (background image) based on the difference
		/*unsigned char * diffPixels = new unsigned char[640*480*3];
		diffPixels = grayDiff.getPixels();
		std::cout << "FIRST 3 DIFFPIXELS@" << &diffPixels << ": " << diffPixels[0] << " " << diffPixels[1] << " " << diffPixels[2] << std::endl;
		//delete[] pxlArr;
		pxlArr = diffPixels;*/
		
		bsPixels = grayDiff.getPixels();
		
		// BUT FIRST: FIX STUPID DOWNSAMPLING BUG BY ONLY SAMPLING
		// THE TOP 213x160 OF THE GRAYDIFF IMAGE (SCALING THAT UP)
		// The section below can be removed if bug is no longer present --------
		unsigned char * realBsPixels = new unsigned char[640*480*3];
		for (int i = 0; i < 640*480*3; i++) {
			realBsPixels[i] = (bsPixels[i/3] >= 255) ? 255 : 0;
		}
		// End bug fix ---------------------------------------------------------
		
		unsigned char * imgPixels = bsBackgroundImage.getPixels();
		for (int i = 0; i < 640*480*3; i++) {
			if (realBsPixels[i] >= 255) { // white pixel? Let's put me instead of the background
				bsPixels[i] = pxlArr[i];
			} else { // otherwise put the background.
				bsPixels[i] = imgPixels[i];
			}
		}
		delete[] realBsPixels;
		//delete[] imgPixels;
		
	} else {
		
		// Normal filters: Apply every adjustment sequentially, with given adjust arguments and options
		std::vector<int>::iterator at   = adjusts_.begin();
		std::vector<int *>::iterator ot = options_.begin();
		for (std::vector<IAdjustment *>::iterator it = list_.begin();
			 it != list_.end(); it++, at++, ot++)
		{
			(*it)->setAdjust(*at);
			(*it)->setOptions(*ot);
			(*it)->apply(pxlArr);
		}
		
	}
}