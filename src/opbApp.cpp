#include "opbApp.h"
#include "opbFilter.h"
#include <stdio.h>
#include <math.h>
#include <time.h>

bool showFiltered = false;
bool freeze = false;

ofImage thumbnail[6];
bool effectsPannel = false;
int currentPicture = 0, imgCount = 0;

unsigned char * lastRawFrame;

//--------------------------------------------------------------
void opbApp::setup(){
    // Grab at the following camera size
    ofEnableSmoothing();
    ofSetRectMode(OF_RECTMODE_CENTER);
    
	camWidth 		= 640;
	camHeight 		= 480;
	totalPixels     = camWidth * camHeight * 3;
    
    float dim       = 16;
    float xInit     = OFX_UI_GLOBAL_WIDGET_SPACING;
    float xPad      = OFX_UI_GLOBAL_PADDING;
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	lastRawFrame    = new unsigned char[totalPixels];
	videoModified 	= new unsigned char[totalPixels];
	//videoModified2	= new unsigned char[totalPixels];
	//videoModified3	= new unsigned char[totalPixels];
	videoTexture.allocate(camWidth, camHeight, GL_RGB);
    //	videoTexture2.allocate(camWidth, camHeight, GL_RGB);
    //	videoTexture3.allocate(camWidth, camHeight, GL_RGB);
	
	// Initialize GUI
	gui = new ofxUICanvas(0, camHeight, camWidth, 48); //ofxUICanvas(float x, float y, float width, float height)
    
    gui->addWidgetRight(new ofxUISpacer((camWidth/2 - xInit - xPad - dim), 0));
    gui->addWidgetRight(new ofxUIImageButton(dim * 2, dim * 2, false, "GUI/Images/Icon.png", "IMGPHOTO"));
    gui->addWidgetRight(new ofxUISpacer(180, 0));
    gui->addWidgetRight(new ofxUILabelToggle("Effects", false, 0, 0, 0, 0, OFX_UI_FONT_MEDIUM));
    
	ofAddListener(gui->newGUIEvent, this, &opbApp::guiEvent);
    //	gui->loadSettings("GUI/guiSettings.xml");
}

//--------------------------------------------------------------
void opbApp::update(){
	//ofBackground(100,100,100);
	
	if(!freeze){
		vidGrabber.update();
		lastRawFrame = vidGrabber.getPixels();
		
		if (vidGrabber.isFrameNew() && showFiltered) {
			unsigned char * pixels = vidGrabber.getPixels();
			generateFilteredImage(pixels);
		}
	}
}

//--------------------------------------------------------------
void opbApp::draw(){
	ofSetHexColor(0xffffff);
    drawPictureSelector(currentPicture);
    if (effectsPannel)
    {
        drawEffectsPanel();
    }
	else if (showFiltered) {
		// Draw the filtered camera
		videoTexture.draw(camWidth/2, camHeight/2, camWidth, camHeight);
	}
    else {
		// Draw the unfiltered camera
		vidGrabber.draw(camWidth/2, camHeight/2);
	}
    if (imgCount > 0)
    {
        drawThumbnails();
    }
}

//--------------------------------------------------------------
void opbApp::keyPressed(int key){
	// in fullscreen mode, on a pc at least, the
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}
	
	if(key == 'f' || key == 'F'){
        if (!effectsPannel)
        {
            showFiltered = !showFiltered;
        }
	}
    if (key == '>')
    {
        drawPictureSelector(currentPicture++);
    }
    if (key == '<')
    {
        drawPictureSelector(currentPicture--);
    }
}

//--------------------------------------------------------------
void opbApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void opbApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void opbApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void opbApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void opbApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void opbApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void opbApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void opbApp::dragEvent(ofDragInfo dragInfo){
    
}
//--------------------------------------------------------------
void opbApp::generateFilteredImage(unsigned char * pixels){
    //	cout << "GENERATING FILTERED IMAGE" << endl;
	opbFilter::brightness(pixels, totalPixels, 50);
	videoTexture.loadData(pixels, camWidth, camHeight, GL_RGB);
}
//--------------------------------------------------------------
void opbApp::takePhoto(){
	freeze = true;
    
    //    if (showFiltered) {
    //        opbFilter::brightness(lastRawFrame, totalPixels, 50);
    //    }
    
    videoTexture.loadData(lastRawFrame, camWidth, camHeight, GL_RGB);
    saveTextureToFile(videoTexture, "photo.jpg");
    
    
    thumbnail[imgCount].loadImage("photo.jpg");
    
    if (thumbnail[imgCount].getWidth() > 100)
    {
        thumbnail[imgCount].resize(100, 0);
    }
    if (thumbnail[imgCount].getHeight() > 100)
    {
        thumbnail[imgCount].resize(0, 100);
    }
    
    imgCount = (imgCount + 1) % 5;
	
    freeze = false;
    
}
//--------------------------------------------------------------
void opbApp::saveTextureToFile(ofTexture pixels, string path){
	ofPixels p;
	pixels.readToPixels(p);
	savePixelsToFile(p, path);
}
//--------------------------------------------------------------
void opbApp::savePixelsToFile(ofPixels pixels, string path){
	ofSaveImage(pixels, path);
}

// ofxUI METHODS -----------------------------------------------
void opbApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	cout << name << endl; //DEBUG
    
	if(name == "IMGPHOTO"){
		ofxUIButton * button = (ofxUIButton *) e.widget;
		if (button->getValue() == 0) {
			takePhoto();
		}
	}
    else if (name == "Effects")
    {
        effectsPannel = !effectsPannel;
        showFiltered = !showFiltered;
    }
}

void opbApp::exit()
{
    gui->saveSettings("GUI/guiSettings.xml");
    delete gui;
}
//--------------------------------------------------------------
void opbApp::drawEffectsPanel()
{
    vidGrabber.draw(camWidth/6+1, camHeight/6+1, camWidth/3, camHeight/3);
    videoTexture.draw(camWidth/2, camHeight/6+1, camWidth/3, camHeight/3);
}

void opbApp::drawPictureSelector(int newPictureNumber)
{
    if (imgCount > 1)
    {
        ofPushStyle();
        ofSetColor(255, 0, 0);
        ofNoFill();
        ofRect((125 * newPictureNumber) % (125 * imgCount) + 70, 614, 100, 100);
        ofPopStyle();
    }
}

void opbApp::drawThumbnails()
{
    if (imgCount > 0)
    {
        for (int i = 0; i <= imgCount; i++)
        {
            thumbnail[i].draw(70 + (125 * i), 614, 100, 100);
        }
    }
}