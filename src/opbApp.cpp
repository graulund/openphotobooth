#include "opbApp.h"
#include "opbFilter.h"
#include <stdio.h>
#include <math.h>
#include <time.h>

using namespace std;

bool showFiltered = false;
bool freeze = false;
unsigned char * lastRawFrame;

//--------------------------------------------------------------
void opbApp::setup(){
	
	// Grab at the following camera size
	camWidth 		= 640;
	camHeight 		= 480;
	totalPixels     = camWidth * camHeight * 3;
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	lastRawFrame    = new unsigned char[totalPixels];
	videoModified 	= new unsigned char[totalPixels];
	//videoModified2	= new unsigned char[totalPixels];
	//videoModified3	= new unsigned char[totalPixels];
	videoTexture.allocate(camWidth, camHeight, GL_RGB);
	//videoTexture2.allocate(camWidth, camHeight, GL_RGB);
	//videoTexture3.allocate(camWidth, camHeight, GL_RGB);
	
	// Initialize GUI
	gui = new ofxUICanvas(0,480,640,60); //ofxUICanvas(float x, float y, float width, float height)
	gui->addLabelButton("Take photo", false);
	ofAddListener(gui->newGUIEvent, this, &opbApp::guiEvent);
	gui->loadSettings("GUI/guiSettings.xml");
}


//--------------------------------------------------------------
void opbApp::update(){
	
	//ofBackground(100,100,100);
	
	if(!freeze){
		vidGrabber.grabFrame();
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
	if (showFiltered) {
		// Draw the filtered camera
		videoTexture.draw(0, 0, camWidth, camHeight);
	} else {
		// Draw the unfiltered camera
		vidGrabber.draw(0,0);
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
		showFiltered = !showFiltered;
	}
}

//--------------------------------------------------------------
void opbApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void opbApp::mouseMoved(int x, int y ){
	
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

void opbApp::generateFilteredImage(unsigned char * pixels){
	cout << "GENERATING FILTERED IMAGE" << endl;
	opbFilter::brightness(pixels, totalPixels, 50);
	videoTexture.loadData(pixels, camWidth, camHeight, GL_RGB);
}

void opbApp::takePhoto(){
	freeze = true;
	//time_t seconds;
	//seconds = time(NULL);
	//vidGrabber.grabFrame();
	//generateFilteredImage(lastRawFrame);
	opbFilter::brightness(lastRawFrame, totalPixels, 50);
	videoTexture.loadData(lastRawFrame, camWidth, camHeight, GL_RGB);
	showFiltered = true;
	
	saveTextureToFile(videoTexture, "photo.jpg");
}

void opbApp::saveTextureToFile(ofTexture pixels, string path){
	ofPixels p;
	pixels.readToPixels(p);
	savePixelsToFile(p, path);
}

void opbApp::savePixelsToFile(ofPixels pixels, string path){
	ofSaveImage(pixels, path);
}

// ofxUI METHODS -----------------------------------------------

void opbApp::exit()
{
    gui->saveSettings("GUI/guiSettings.xml");
    delete gui;
}

void opbApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	cout << name << endl; //DEBUG
	if(name == "Take photo"){
		ofxUIButton *button = (ofxUIButton *) e.widget;
		if (button->getValue() == 0) {
			takePhoto();
		}
	}
}
