#include "Model.h"

#include <ctime>

Model::Model()
{
	init();
	init(0, 0, 0);
}

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
	btnNameR_ = BTN_NAME_R;
}

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

	/* NEW FILTER VECTOR! CARRYS ALL THE FILTERS AVAILABLE				*/
	filterVector_ = new std::vector<module_filter>();

	/* ADD FILTERS TO FILTER VECTOR - YOU CAN ADD ADJUSTMENTS TO
	   FILTERS RIGHT AFTER 												*/
	filterVector_->push_back(
		module_filter("FILTER ONE", 640 * 480 * 3));
	filterVector_->push_back(
		module_filter("VENICE", 640 * 480 * 3));

	/* ADD ADJUSTMENT TO FILTER ADD NEW FILTER IN MODEL.CPP LINE 60		
	   USE THIS METHODS IF YOU WANT TO ADD A USER INTERFACE WHATEVER    */

	filterVector_->at(0).addAdjustment("Saturation");
	filterVector_->at(0).addAdjustment("Brightness");
	filterVector_->at(1).addAdjustment("Brightness");

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

	pixelArr_ = vidGrabber_->getPixels();
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
 * Reize and Saves a Picture file into an Array
 * @param tex  picture Object as Texture
 * @param name filename of the Picture which should be saved
 */
void Model::saveToThumbnail(std::string name)
{
	thumbArr_[imgIndex_].loadImage(name);
	// resizeToThumbnail(thumbArr_[imgIndex_], THUMBNAIL_RATIO);
	updateImgCount();
}

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
 * @TODO
 * RETURNS THE MODIFICATION FILTER - DONT USE ANYMORE!1111ONE
 * @return THE FILTER
 */
module_filter * Model::getModFilter()
{
	return modFilter_;
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
						cout << "RESIZE WITH" << endl;
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
   	"AAAFg85KzpIIBAGMFPF4pHUPjcv1BgVGedNIjoTvqojGG0FARt6YtNnv3drTI1ZCc8BeyzZABNfnr0nlREHzame9dpc0C8wgSK2piqgUj41VW4LKITT";

    /* WHERE YOU WANT TO UPLOAD THE PICTURES							*/
    std::string url;
	url.append("https://graph.facebook.com/USER_NAME/photos");
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