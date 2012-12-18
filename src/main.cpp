#include "ofMain.h"
#include "Bootstrap.h"
#include "ofAppGlutWindow.h"

// Uncomment below to start debug mode
//#define __openPhotoBooth__DEBUG_FLAG__
// End

/*************************************************
 File: main.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: This is where everything starts! Set up the window at 640x700 resolution and start the Bootstrapper.
 *************************************************/

int main( )
{
    ofAppGlutWindow window;

	ofSetupOpenGL(&window, 640, 700, OF_WINDOW);
	
	ofRunApp(new Bootstrap());
}
