#include "ofMain.h"
#include "Bootstrap.h"
#include "ofAppGlutWindow.h"

// Uncomment below to start debug mode
//#define __openPhotoBooth__DEBUG_FLAG__
// End

int main( )
{
    ofAppGlutWindow window;

	ofSetupOpenGL(&window, 640, 700, OF_WINDOW);
	
	ofRunApp(new Bootstrap());
}
