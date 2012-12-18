Open Photo Booth
================

Open Photo Booth is an application that takes a live webcam feed on your device as input, and allows you to easily add certain filters and annotations to the image and save it to a file and your connected Facebook profile. Nine different filters are in the application to begin with, and the magic part is that you can play the artist and make your own custom filters!

In addition to this, Open Photo Booth is open source and can be run on any platform. Try it yourself --- download the source and compile it anywhere! Or just download the binary from our website.

Open Photo Booth is written in C++ relying heavily on the OpenFrameworks library.

Project website
---------------

http://openphotobooth.24bps.com/

Prerequisites
-------------

* OpenFrameworks version 0071+
* OpenFrameworks addons: ofxOpenCV, ofxUI
* cURL internet connection library

Compilation instructions
------------------------

Since this application is based on OpenFrameworks, it should in theory be able to run on any platform. This application is built in Xcode 4.5 on a Mac, in the standard OpenFrameworks directory structure you get from any download of OpenFrameworks. This means that the project is placed in its own folder inside a second folder inside the `apps/` folder. Then the xcodeproj should be able to compile on the Mac.

If the linker has an issue, this is the header search path I used in my installation of Xcode:

	$(OF_CORE_HEADERS) ../../../addons/ofxXmlSettings/libs ../../../addons/ofxXmlSettings/src ../../../addons/ofxUI/libs ../../../addons/ofxUI/src ../../../addons/ofxOpenCv/libs ../../../addons/ofxOpenCv/libs/opencv ../../../addons/ofxOpenCv/libs/opencv/include ../../../addons/ofxOpenCv/libs/opencv/include/opencv ../../../addons/ofxOpenCv/libs/opencv/include/opencv2 ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/calib3d ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/contrib ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/core ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/features2d ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/flann ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/gpu ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/highgui ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/imgproc ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/legacy ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/ml ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/objdetect ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/ts ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/video ../../../addons/ofxOpenCv/libs/opencv/lib ../../../addons/ofxOpenCv/libs/opencv/lib/osx ../../../addons/ofxOpenCv/src

To implement this, simply click the Xcode project file at the top of your file list to the left in Xcode.

