/*************************************************
 File: Model.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: Follows the MVC/Mediator Pattern. It does hold all the 
 Data and Business logic. Called from the Controller. Primary Model,
 all other models are derived form this.
 *************************************************/

#include "Model.h"

#include <ctime>

#define CAM_SUBPIXELS 640 * 480 * 3


/**
 * Default Constructor. Just called when the Application starts
 */
Model::Model()
{
	init();
	init(0, 0, 0);
}

/**
 * Copy Constructor. Copies all needed references to the new Model and
 * delete the old one after wards. Since we use new OBJECT to 
 * instantiate all the MVC objects needed, we have to delete them all
 * if we dont need them anymore. Otherwise we would have a Memory leak
 */
Model::Model(Model * oldModel, bool delOld)
{
	vidGrabber_ = oldModel->getVideoGrabber();
	texture_ = oldModel->getTexture();
	thumbArr_ = oldModel->getThumbnails();
	filterVector_ = oldModel->getFilterVector();

	imgCnt_ = oldModel->getImgCount();
	imgIndex_ = oldModel->getImgIndex();
	imgSelector_ = oldModel->updateThumbnailSelector(0);
	thmbCnt_ = oldModel->getThumbnailCount();
	filterSelector_ = oldModel->getFilterSelector();

	init();

	if (delOld)
		delete oldModel;
}

/**
 * SET THE BUTTON LABEL TO THE #DEFINED ONES
 */
void Model::init()
{
	btnLabelL_ = BTN_LABL_L;
	btnLabelR_ = BTN_LABL_R;

	btnNameL_ = BTN_NAME_L;
	btnNameM_ = BTN_NAME_M;
	btnNameAM_ = BTN_NAME_AM;
	btnNameR_ = BTN_NAME_R;
}

/**
 * Initializer Method used by different Contructors to remove dublicated
 * core
 * @param imgCnt      amount of Images
 * @param imgIndex    current Image Index
 * @param imgSelector current Position of the Thumbnail Selector
 */
void Model::init(int imgCnt, int imgIndex, int imgSelector)
{
	imgCnt_ = imgCnt;
	imgIndex_ = imgIndex;
	imgSelector_ = imgSelector;
	thmbCnt_ = THUMBNAIL_CNT;
	filterSelector_ = 0;

	vidGrabber_ = new ofVideoGrabber();
	texture_ = new ofTexture();
	thumbArr_ = new ofImage[THUMBNAIL_CNT];

	vidGrabber_->initGrabber(CAM_WIDTH, CAM_HEIGHT);
	texture_->allocate(CAM_WIDTH, CAM_HEIGHT, GL_RGB);

	/* NEW FILTER VECTOR! CARRIES ALL THE FILTERS AVAILABLE				*/
	filterVector_ = new std::vector<module_filter>();

	/* ADD FILTERS TO FILTER VECTOR - YOU CAN ADD ADJUSTMENTS TO
	   FILTERS RIGHT AFTER 												*/
	filterVector_->push_back(
		module_filter("Sin City", CAM_SUBPIXELS));
	filterVector_->push_back(
		module_filter("Love", CAM_SUBPIXELS));
	filterVector_->push_back(
		module_filter("Grunge", CAM_SUBPIXELS));
	filterVector_->push_back(
		module_filter("Cross Process", CAM_SUBPIXELS));
	filterVector_->push_back(
		module_filter("Vintage", CAM_SUBPIXELS));
	filterVector_->push_back(
		module_filter("Orange Peel", CAM_SUBPIXELS));
	filterVector_->push_back(
		module_filter("Trippy", CAM_SUBPIXELS));
	filterVector_->push_back(
		module_filter("Evil", CAM_SUBPIXELS));
	filterVector_->push_back(
		module_filter("Blue Screen", CAM_SUBPIXELS, true));

	/* ADD ADJUSTMENT TO FILTER ADD NEW FILTER IN MODEL.CPP LINE 60		
	   USE THIS METHODS IF YOU WANT TO ADD A USER INTERFACE WHATEVER    */

	// DEFAULT FILTERS:
	// Sin City -----
	filterVector_->at(0).addAdjustment("Contrast", 100);
	filterVector_->at(0).addAdjustment("Brightness", 15);
	filterVector_->at(0).addAdjustment("Posterize", 80);
	//filterVector_->at(0).addAdjustment("Clip", 30); // Doesn't look good
	filterVector_->at(0).addAdjustment("Greyscale");
	
	// Love -----
	int *lovecolor = new int[3];
	lovecolor[0] = 196; lovecolor[1] = 32; lovecolor[2] = 7;
	filterVector_->at(1).addAdjustment("Brightness", 10);
	filterVector_->at(1).addAdjustment("Contrast", 4);
	filterVector_->at(1).addAdjustment("Colorize", 35, lovecolor);
	filterVector_->at(1).addAdjustment("Vibrance", 50);
	filterVector_->at(1).addAdjustment("Gamma", 130);
	
	// Grunge -----
	filterVector_->at(2).addAdjustment("Gamma", 150);
	filterVector_->at(2).addAdjustment("Clip", 25);
	filterVector_->at(2).addAdjustment("Saturation", -60);
	filterVector_->at(2).addAdjustment("Contrast", 5);
	filterVector_->at(2).addAdjustment("Noise", 15);
	
	// Cross Process -----
	int *crproc = new int[3]; int *crcolor = new int[3];
	crproc[0] = 3; crproc[1] = 0; crproc[2] = 8;
	crcolor[0] = 232; crcolor[1] = 123; crcolor[2] = 34;
	filterVector_->at(3).addAdjustment("Brightness", 20);
	filterVector_->at(3).addAdjustment("Colorize", 4, crcolor);
	filterVector_->at(3).addAdjustment("Sepia", 20);
	filterVector_->at(3).addAdjustment("Channels", 0, crproc);
	filterVector_->at(3).addAdjustment("Contrast", 15);
	filterVector_->at(3).addAdjustment("Vibrance", 75);
	filterVector_->at(3).addAdjustment("Gamma", 160);
	
	// Vintage -----
	int *vintage = new int[3];
	vintage[0] = 8; vintage[1] = 4; vintage[2] = 2;
	filterVector_->at(4).addAdjustment("Greyscale");
	filterVector_->at(4).addAdjustment("Contrast", 5);
	filterVector_->at(4).addAdjustment("Noise", 10);
	filterVector_->at(4).addAdjustment("Sepia", 100);
	filterVector_->at(4).addAdjustment("Channels", 0, vintage);
	filterVector_->at(4).addAdjustment("Gamma", 87);
	
	// Orange Peel -----
	int *opeel = new int[3];
	opeel[0] = 255; opeel[1] = 144; opeel[2] = 0;
	filterVector_->at(5).addAdjustment("Vibrance", -30);
	filterVector_->at(5).addAdjustment("Saturation", -30);
	filterVector_->at(5).addAdjustment("Colorize", 30, opeel);
	filterVector_->at(5).addAdjustment("Contrast", -5);
	filterVector_->at(5).addAdjustment("Gamma", 140);
	
	// Trippy ------
	filterVector_->at(6).addAdjustment("Hue", 40);
	filterVector_->at(6).addAdjustment("Brightness", 25);
	filterVector_->at(6).addAdjustment("Vibrance", 70);
	filterVector_->at(6).addAdjustment("Contrast", 20);
	
	// Evil ------
	int *cold = new int[3];
	cold[0] = 0; cold[1] = 144; cold[2] = 255;
	filterVector_->at(7).addAdjustment("Invert");
	filterVector_->at(7).addAdjustment("Greyscale");
	filterVector_->at(7).addAdjustment("Contrast", 40);
	filterVector_->at(7).addAdjustment("Colorize", 40, cold);
	

}

/**
 * Saves the current frame from the Webcam with given Width and
 * Height to a File. Saves also the Thumbnail to an Array
 * @param camWidth  width of the Picture
 * @param camHeight height of the Picture
 */
void Model::saveImage()
{
	std::string imgName = getImageName();

	if (this->getCurrentFilter() != NULL && this->getCurrentFilter()->getIsBlueScreen()) {
		pixelArr_ = this->getCurrentFilter()->getBsPixels();
	} else {
		pixelArr_ = vidGrabber_->getPixels();
	}
	
	texture_->loadData(pixelArr_, CAM_WIDTH, CAM_HEIGHT, GL_RGB);
	saveTextureToFile(imgName);
	saveToThumbnail(imgName);
}

/**
 * Saves the ofPixel Object to a given Filename
 * @param pix  picture Object as Pixel
 * @param name name of the new Filename
 */
void Model::savePixelsToFile(ofPixels pix, std::string name)
{
	ofSaveImage(pix, name);
}

/**
 * Transforms a ofTexture to a ofPixel and saves it to a given
 * Filename
 * @param tex  picture Object as Texture
 * @param name name of the new Filename
 */
void Model::saveTextureToFile(std::string name)
{
	ofPixels p;
	texture_->readToPixels(p);
	savePixelsToFile(p, name);
}

/**
 * Resize and Saves a Picture file into an Array
 * @param tex  picture Object as Texture
 * @param name filename of the Picture which should be saved
 */
void Model::saveToThumbnail(std::string name)
{
	thumbArr_[imgIndex_].loadImage(name);
	// resizeToThumbnail(thumbArr_[imgIndex_], THUMBNAIL_RATIO);
	updateImgCount();
}

/**
 * Saves the ofImage to the thumbnail array.
 * @param newImage Image Object that holds the new Thumbnail
 */
void Model::saveToThumbnail(ofImage newImage)
{
	thumbArr_[imgIndex_] = newImage;
	updateImgCount();
}

/**
 * Updates the Image Count and Index for the Thumbnail Array
 */
void Model::updateImgCount()
{
	imgIndex_ = (imgIndex_ + 1) % THUMBNAIL_CNT;
	imgCnt_ = (imgCnt_ + 1) % (THUMBNAIL_CNT + 1);

	if (imgCnt_ == 0 && imgIndex_ > 0)
	{
		imgCnt_ = 1;
	}
}

/**
 * Resize a given ofImage file to a given aspect Ratio
 * @param img   image which shoule be resized
 * @param ratio aspect ratio in pixel
 */
void Model::resizeToThumbnail(ofImage img, float ratio)
{
	float imgWidth = img.getWidth();
	float imgHeight = img.getHeight();

	if (imgWidth > ratio)
	{
		img.resize(ratio, imgWidth / imgHeight);
		cout << "RESIZE WITH" << endl;
	}
	else if (imgHeight > ratio)
	{
		cout << "RESIZE HEIGHT" << endl;
		img.resize(imgHeight / imgWidth, ratio);
	}
}

/**
 * Fetches the last Texture from the Webcam
 */
void Model::update()
{
	vidGrabber_->update();

	if (vidGrabber_->isFrameNew())
	{
	    pixelArr_ = vidGrabber_->getPixels();
		
	    applyFilters();
		
		// Are we dealing with the blue screen filter? Special case:
		module_filter* currentFilter;
		currentFilter = this->getCurrentFilter();
		if (currentFilter != NULL && currentFilter->getIsBlueScreen()) {
			pixelArr_ = currentFilter->getBsPixels();
		}

	 	texture_->loadData(pixelArr_, 640, 480, GL_RGB);
 	}
}

/**
 * APPLYES THE SELECTED FILTER TO THE MAIN SCENE
 * @return true if any filter applied.
 */
bool Model::applyFilters()
{
	if (filterSelector_ > 0)
	{
		filterVector_->at(filterSelector_ - 1).apply(
			static_cast<unsigned char*>(pixelArr_));
		return true;
	}
	return false;
}

/**
 * Returns the current Image Count
 * @return
 */
int Model::getImgCount()
{
	return imgCnt_;
}

/**
 * Returns the size of the Thumbnail Array
 * @return (int) size of Thumbnail Array
 */
int Model::getThumbnailCount()
{
	return thmbCnt_;
}

/**
 * Updates the new Position of the THumnail Selector. Use a negative
 * int to decrease the Position. a Positive Interger increase the 
 * Position. A Zero return the current Position. If the Thumbnail
 * count below two, no selector is drawn.
 * @param  nextImage positive or Negative Int to change the Position
 * @return
 */
int Model::updateThumbnailSelector(int nextImage)
{
	if (imgCnt_ < 2)
	{
		return 0;
	}
	else if (nextImage > 0)
	{
		if (imgSelector_ + 1 > imgCnt_)
		{
			return (imgSelector_ = 1);
		}
		return ++imgSelector_;
	}
	else if (nextImage < 0)
	{
		if (imgSelector_ - 1 < 1)
		{
			return (imgSelector_ = imgCnt_);
		}
		return --imgSelector_;
	}
	else
	{
		return imgSelector_;
	}
}

int Model::getImageNumber()
{
	if (imgSelector_ == 0)
	{
		return 0;
	}
	else if (imgSelector_ > 0)
	{
		return imgSelector_ - 1;
	}
}

/**
 * Returns the Thumbnail Selector
 * @return
 */
int Model::getThumbnailSelector()
{
	return imgSelector_;
}

/**
 * Returns the current Image Index of the Thumbnail Array
 * @return
 */
int Model::getImgIndex()
{
	return imgIndex_;
}

/**
 * Returns the Cam Width in Pixel
 * @return
 */
float Model::getCamWidth()
{
	return float(CAM_WIDTH);
}

/**
 * Returns the Cam Height in Pixel
 * @return
 */
float Model::getCamHeight()
{
	return float(CAM_HEIGHT);
}

/**
 * Returns the Current Date and Time. Used for the Image Names
 * @return
 */
std::string Model::getCurrentDate()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	strftime (buffer, 80 ,"%Y-%m-%d %I.%M.%S", timeinfo);

	return (buffer);
}

/**
 * Returns the complete filename for a Image
 * @return
 */
std::string Model::getImageName()
{
    std::string imgName;
    imgName += IMG_NAME;
    imgName += " ";
    imgName += getCurrentDate();
    imgName += IMG_EXT;

    return imgName;
}
/**
 * Returns the Icon Path of the Middle Button defined in Model.h
 * @return
 */
std::string Model::getIconURL()
{
	return ICON_URL;
}

/**
 * Return the Button Label of the selected Button. Defined in Model.h
 * One = Left Button, Two = Right Button
 * @param  btnNr the ID of the Button which label should be returned
 * @return
 */
std::string Model::getButtonLabel(int btnNr)
{
	if (btnNr == 1)
	{
		return btnLabelL_;
	}
	else if (btnNr == 2)
	{
		return btnLabelR_;
	}
	else
	{
		return "";
	}
}

/**
 * RETURNS THE BUTTON NAME DEFINED BY BUTTON NUMBER
 * @param  btnNr [description]
 * @return       [description]
 */
std::string Model::getButtonName(int btnNr)
{
	if (btnNr == 1)
	{
		return btnNameL_;
	}
	else if (btnNr == 2)
	{
		return btnNameR_;
	}
	else if (btnNr == 3)
	{
		return btnNameM_;
	}
	else if (btnNr == 4)
	{
		return btnNameAM_;
	}
	else
	{
		return "";
	}
}

/**
 * Returns the VideoGrabber used in this Model
 * @return
 */
ofVideoGrabber * Model::getVideoGrabber()
{
	return vidGrabber_;
}

/**
 * Returns the Texture used to save the current Webcam frame to a File
 * @return
 */
ofTexture * Model::getTexture()
{
	return texture_;
}

/**
 * RETURNS SELECTED THUMBNAIL AS TEXTURE TO DRAW ON THE SCENE
 * @param  index [description]
 * @return       [description]
 */
ofTexture Model::getThumbnail(int index)
{
	return thumbArr_[index].getTextureReference();
}

/**
 * Returns the Array of Thumbnails
 * @return
 */
ofImage * Model::getThumbnails()
{
	return thumbArr_;
}

/**
 * Calculates the Image index on a X, Y Position given
 * @param  x mouse position
 * @param  y mouse position
 * @return   true if there is an Image
 */
bool Model::selectImage(int x, int y)
{
	bool isSelectable = false;

	if (y >= 564 && y <= 664)
	{
		if (x >= 520 && x <= 620 && imgCnt_ > 4)
		{
			imgSelector_ = 5;
			isSelectable = true;
		}
	
		if (x >= 395 && x <= 495 && imgCnt_ > 3)
		{
			imgSelector_ = 4;
			isSelectable = true;
		}
		if (x >= 270 && x <= 370 && imgCnt_ > 2)
		{
			imgSelector_ = 3;
			isSelectable = true;
		}

		if (x >= 145 && x <= 245 && imgCnt_ > 1)
		{
			imgSelector_ = 2;
			isSelectable = true;
		}
		if (x >= 20 && x <= 120 && imgCnt_ > 0)
		{
			imgSelector_ = 1;
			isSelectable = true;
		}
	}

	return isSelectable;
}

/**
 * Returns the filter which is in use right now
 * @return the filter 
 */
module_filter * Model::getCurrentFilter()
{
	if (filterSelector_ <= 0 || filterVector_->size() <= 0) {
		return NULL;
	}
	return &filterVector_->at(filterSelector_ - 1);
}

/**
 * RETURNS THE VECTOR WHERE ALL FILTERS ARE SAVED
 */
std::vector<module_filter> * Model::getFilterVector()
{
	return filterVector_;
}

/**
 * Returns the Number of filter the Used hat selected in the filter view
 * @return number of the filter
 */
int Model::getFilterSelector()
{
	return filterSelector_;
}

bool sortColorFunction (ofColor i,ofColor j) { 
	return (i.getBrightness()<j.getBrightness()); 
}

/**
 * SIMPLE FILE HANDLER
 * @param openFileResult the selected file
 */
void Model::processOpenFileSelection(ofFileDialogResult openFileResult){
	
	ofLogVerbose("getName(): "  + openFileResult.getName());
	ofLogVerbose("getPath(): "  + openFileResult.getPath());
	
	ofFile file (openFileResult.getPath()); 
	
	if (file.exists())
	{
		//Limiting this example to one image so we delete previous ones
		processedImages.clear();
		loadedImages.clear();
		
		ofLogVerbose("The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());
		
		//We only want images
		if (fileExtension == "JPG" || fileExtension == "PNG")
		{	
			//Save the file extension to use when we save out
			originalFileExtension = fileExtension;
			
			//Load the selected image
			ofImage image;
			image.loadImage(openFileResult.getPath());
			// if (image.getWidth() > 640 || image.getHeight() > 480)
			// {
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
			// }
			saveToThumbnail(image);
			
			//Make some short variables 
			int w = image.getWidth();
			int h = image.getHeight();
		}
	}
}

/**
 * Saves a Image to Facebook. Requires a Valid access_token and username
 * @param  imgName   Filename of the Image which should be uploaded
 * @param  imgWidth  Width of the Image
 * @param  imgHeight Height of the Image
 * @return           true if upload was successfull
 */
bool Model::saveToFacebook(std::string imgName, int imgWidth, 
	int imgHeight)
{
    CURL * urlHandler;
    CURLcode resault;
    
    struct curl_httppost * post = NULL;
    struct curl_httppost * last = NULL;

	/* Create an instance of out BufferStruct to accept LCs output		*/
    struct BufferStruct output; 
	output.buffer = NULL;
	output.size = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    urlHandler = curl_easy_init();

    /* @TODO
       THIS MUST BE FIXED												
       APP ACCESS TOKEN, DONT USE SIGNS NOT ALLOWED AS URL, USE %		
       ENTER AN VALID ACCESS_TOKEN HERE 								*/
	string access_token = 
   	"AAAFg85KzpIIBACrTp6tq8xmv8hHeJUJAJBZB7ZBxVdua2guPXSjZAzFJDflIneEZC8X2ytjZCPJQayZAHz0L7h7ziYkprsT4ZBq6suJZAx17jQZDZD";

    /* WHERE YOU WANT TO UPLOAD THE PICTURES							*/
    std::string url;
	url.append("https://graph.facebook.com/graulund/photos");
	// url.append("https://graph.facebook.com/oauth/access_token?");
	// url.append("https://graph.facebook.com/app?access_token=");
	// url.append(access_token);
	// url.append("client_id=");
	// url.append(app_id);
	// url.append("&client_secret=");
	// url.append(app_secret);
	// url.append("&grant_type=client_credentials");

	/* SINCE CURL JUST ALLOW CHAR * AS ARGUMENTS, WE HAVE TO TRANSFORM
	   THE URL STRINGS INTO CHAR *										*/
	char * charURL, * charImgName, * charImgPath, * charImgWidth,
		* charImgHeight;

	ofDirectory myDir;

	std::string imgPath = ofFilePath::getAbsolutePath(myDir.path());
	imgPath.append(imgName);

	charURL = stringToChar(url);
	charImgPath = stringToChar(imgPath);
	charImgName = stringToChar(imgName);

    /* IF INITIALIZATION WAS SUCCESSFULL WE CAN CONTINUE				*/
    if (urlHandler)
    {
    	
    	/* THIS IS THE WAY TO SET THE OPTIONS FOR THE HANDLER 			*/
        curl_easy_setopt(urlHandler, CURLOPT_URL, charURL);
        // curl_easy_setopt(urlHandler, CURLOPT_POST, 1); 
        
        // curl_easy_setopt(urlHandler, CURLOPT_HEADER, 1);
		
		/* Passing the function pointer to LC 							*/
        curl_easy_setopt(urlHandler, CURLOPT_WRITEFUNCTION, 
        	WriteMemoryCallback);
		/* Passing our BufferStruct to LC 								*/
        curl_easy_setopt(urlHandler, CURLOPT_WRITEDATA, 
        	(void *) & output); 

        /* ADDING FORMS FOR THE HTML POST 								*/
        curl_formadd(&post, &last, 
        	CURLFORM_COPYNAME, "access_token", 
        	CURLFORM_COPYCONTENTS, stringToChar(access_token),
        	CURLFORM_END);
        curl_formadd(&post, &last,
        	CURLFORM_COPYNAME, "name",   
        	CURLFORM_COPYCONTENTS, charImgName, 
        	CURLFORM_END);
        curl_formadd(&post, &last, 
        	CURLFORM_COPYNAME, "width",   
        	CURLFORM_COPYCONTENTS, new char(imgWidth), 
        	CURLFORM_END);
        curl_formadd(&post, &last, 
        	CURLFORM_COPYNAME, "height",   
        	CURLFORM_COPYCONTENTS, new char(imgHeight), 
        	CURLFORM_END);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "source", 
        	CURLFORM_FILE, charImgPath,
        	CURLFORM_CONTENTTYPE, "image/jpeg", 
        	CURLFORM_END);

        /* ADD ALL THE FIELDS TO THE URLHANDLER. ITS IMPORTENT THAT ALL
           ALL FIELDS ARE ADDED BEFORE THIS IS CALLED - TOOKS ME 30MIN
           TO FIGURE OUT.												*/
    	curl_easy_setopt(urlHandler, CURLOPT_HTTPPOST, post);

    	/* FOR SOME ERROR CHECKING 										*/
        resault = curl_easy_perform(urlHandler);

        if (resault != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", 
            	curl_easy_strerror(resault));
            
            curl_easy_cleanup(urlHandler);
        }
        
        curl_global_cleanup();
	}
	// curl_easy_getinfo(urlHandler, CURLINFO_EFFECTIVE_URL, &myPtr);

	/* PRINT OUT WHAT WE RECEIVED FROM FACEBOOK 						*/
	cout << output.buffer << endl;
}

char * Model::stringToChar(std::string myString)
{
	char * charURL = new char[myString.size() + 1];
    charURL[myString.size()] = 0;
    memcpy(charURL, myString.c_str(), myString.size());

    return charURL;
}

/* This is the function we pass to LC, which writes the output 
   to a BufferStruct													*/
size_t Model::WriteMemoryCallback(void *ptr, size_t size,
	size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;
    
	struct BufferStruct * mem = (struct BufferStruct *) data;
    
	mem->buffer = (char *) realloc(mem->buffer, mem->size + realsize + 1);
    
	if ( mem->buffer )
	{
		memcpy( &( mem->buffer[ mem->size ] ), ptr, realsize );
		mem->size += realsize;
		mem->buffer[ mem->size ] = 0;
	}
	return realsize;
}