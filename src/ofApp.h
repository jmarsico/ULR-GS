#pragma once


#include <deque>
#include "ofMain.h"
#include "ofxIO.h"

#ifdef TARGET_RASPBERRY_PI
	#include "ofxOMXPlayer.h"
#endif



class ofApp: public ofBaseApp {
	
public:

    void setup();
    void update();
    void draw();

	// parse items from message queue. overrides built-in defininition of gotMessage()
    void gotMessage(ofMessage msg);

	// item added to directory
    void onDirectoryWatcherItemAdded(const ofxIO::DirectoryWatcherManager::DirectoryEvent& evt) {
		
		// send a message to the message queue
        ofSendMessage(evt.item.path());
		
		ofLog() << "File added: " << evt.item.path();
		
		ofLogToFile("log.txt", true);
		ofLog() << "File added: " << evt.item.path();
    }
	
	
	// directory watcher
    ofxIO::DirectoryWatcherManager watcher;
	
	// filter out hidden files
	ofxIO::HiddenFileFilter hiddenFileFilter;
	

	// double-ended queue for messages
    std::deque<std::string> messages;
	
	// video player
	#ifdef TARGET_RASPBERRY_PI
		ofxOMXPlayer backgroundVideo;
	#else
		ofVideoPlayer backgroundVideo;
	#endif
	
	
	// location of next image
    std::string imageLocation;
	
	// image
    ofImage currentImage;
	
	// when to start image
    int imageStartTime;
	
	// time image should be displayed, in ms
    int millisImageTimeout;
	
	// flag to display image
    bool newImageReady = false;
    
    bool bDrawImage;
	
};
