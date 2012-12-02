#include "testApp.h"
#include <stdio.h>
#include <math.h>

bool talked = false;

//--------------------------------------------------------------
void testApp::setup(){
	
	camWidth 		= 320;	// try to grab at this size. 
	camHeight 		= 240;
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	videoInverted 	= new unsigned char[camWidth*camHeight*3];
	videoInverted2	= new unsigned char[camWidth*camHeight*3];
	videoInverted3	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);
	videoTexture2.allocate(camWidth,camHeight, GL_RGB);
	videoTexture3.allocate(camWidth,camHeight, GL_RGB);
}


//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(100,100,100);
	
	vidGrabber.grabFrame();
	
	if (vidGrabber.isFrameNew()){
		int totalPixels = camWidth*camHeight*3;
		unsigned char * pixels = vidGrabber.getPixels();
		
		int channel;
		
		float r, g, b;
		float adjust = 1.0;
		float adjust2 = 200.0;
		int namount = 20;
		
		for (int i = 0; i < totalPixels; i++){
			channel = i % 3;
			
			// OUTPUT 1: In the red --------------------------------------
			
			
			// Contrast up
			
			
			/** /float pixel;
			 
			 adjust2 = pow((float)(adjust2 + 100.0) / 100.0, 2.0);
			 
			 pixel  = pixels[i] / 255.0;
			 pixel -= 0.5;
			 pixel *= adjust2;
			 pixel += 0.5;
			 pixel *= 255.0;
			 
			 if(pixel > 255.0){ pixel = 255.0; }
			 if(pixel < 0.0){ pixel = 0.0; }
			 
			 //printf("%u to %0.2f\n", pixels[i], pixel);
			 
			 videoInverted[i] = (unsigned char)pixel;/**/
			
			/**/if(channel == 0){
				videoInverted[i] = min(pixels[i] + 100,   255);
			} else {
				videoInverted[i] = pixels[i];
			}/**/
			
			
			//videoInverted[i] = max(videoInverted[i] - 60, 0);
			
			// OUTPUT 2: Color inverted ----------------------------------
			
			if(channel == 2){ // Blue channel
				videoInverted2[i] = 255 - pixels[i];
			} else {
				videoInverted2[i] = pixels[i];
			}
			
			// Brighter or darker
			//videoInverted[i] = min(pixels[i] + 150, 255);
			
			// OUTPUT 3: SEPIA -------------------------------------------
			// Just storing the subpixel values until we have all three...
			if(channel == 0){ r = pixels[i]; }
			else if(channel == 1){ g = pixels[i]; }
			else {
				b = pixels[i];
				
				// Now we have all three.
				// Below is the formula for sepia, one I found online. Obviously it can be tweaked if need be.
				r = min(255.0, (r * (1 - (0.307 * adjust))) + (g * (0.769 * adjust)) + (b * (0.189 * adjust)));
				g = min(255.0, (r * (0.349 * adjust)) + (g * (1 - (0.314 * adjust))) + (b * (0.168 * adjust)));
				b = min(255.0, (r * (0.272 * adjust)) + (g * (0.534 * adjust)) + (b * (1- (0.869 * adjust))));
				
				// Add a little bit of noise for that real old timey look!
				int noise = (rand() % namount) - namount/2;
				
				// Convert and add the pixel values to the list, making sure they don't go out of 0..255 range.
				videoInverted3[i-2] = min(255, max(0, (int)(r + noise)));
				videoInverted3[i-1] = min(255, max(0, (int)(g + noise)));
				videoInverted3[i]   = min(255, max(0, (int)(b + noise)));
				
			}
			
			
			
			//printf("%u to %u\n", pixels[i], videoInverted[i]);
			
			// Gamma
			//videoInverted[i] = (pow((float)(pixels[i] / 255.0), adjust) * 255.0);
			
			
			
			
			
			// Random noise
			
			/*int namount = 20;
			int noise = (rand() % namount) - namount/2;
			int pixel = pixels[i] + noise;
				pixel = min(255, max(0, pixel));
			videoInverted[i] = pixel;*/
			
			
			/*if(!talked && pixels[i] > 0){
				printf("ADJUST IS %0.5f\n", adjust);
				printf("%u to %u\n", pixels[i], videoInverted[i]);
				printf("%x\n", pixels[i]);
				talked = true;
			}*/
			
		}
		videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGB);
		videoTexture2.loadData(videoInverted2, camWidth,camHeight, GL_RGB);
		videoTexture3.loadData(videoInverted3, camWidth,camHeight, GL_RGB);
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetHexColor(0xffffff);
	vidGrabber.draw(20,20);
	videoTexture.draw(20+camWidth,20,camWidth,camHeight);
	videoTexture2.draw(20,20+camHeight,camWidth,camHeight);
	videoTexture3.draw(20+camWidth,20+camHeight,camWidth,camHeight);
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}
	
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
