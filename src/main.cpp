#include "ofMain.h"
#include "Bootstrap.h"
#include "ofAppGlutWindow.h"

int main( )
{
    ofAppGlutWindow window;

	ofSetupOpenGL(&window, 640, 700, OF_WINDOW);
	
	ofRunApp(new Bootstrap());
}
