#pragma once

#include "ofMain.h"
#include "ofxUI.h"

class opbApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
	void generateFilteredImage(unsigned char * pixels);
	void takePhoto();
	void saveTextureToFile(ofTexture pixels, string path);
	void savePixelsToFile(ofPixels pixels, string path);
		
		ofVideoGrabber 		vidGrabber;
	unsigned char * 	videoModified;
	unsigned char * 	videoModified2;
	unsigned char * 	videoModified3;
	//unsigned char * 	videoModified4;
	ofTexture			videoTexture;
	ofTexture			videoTexture2;
	ofTexture			videoTexture3;
		int 				camWidth;
		int 				camHeight;
		int                 totalPixels;
	
	ofxUICanvas *gui;
	void exit();
	void guiEvent(ofxUIEventArgs &e);
};
