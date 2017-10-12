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
    void gotMessage(ofMessage msg) override;

	// item added to directory
    void onDirectoryWatcherItemAdded(const ofxIO::DirectoryWatcherManager::DirectoryEvent& evt) {
		
		// send a message to the message queue
        ofSendMessage(evt.item.path());
//		
		ofLogNotice("watcher") << "File added: " << evt.item.path();
//		
//		ofLogToFile("log.txt", true);
//		ofLog() << "File added: " << evt.item.path();
    }
	
	void onDirectoryWatcherItemRemoved(const ofxIO::DirectoryWatcherManager::DirectoryEvent& evt) {
//		ofLogToFile("log.txt", true);
//		ofSendMessage("Removed:  " + evt.item.path());
	}
	
	void onDirectoryWatcherItemModified(const ofxIO::DirectoryWatcherManager::DirectoryEvent& evt) {
//		ofLogToFile("log.txt", true);
		ofSendMessage(evt.item.path());
	}
	
	void onDirectoryWatcherItemMovedFrom(const ofxIO::DirectoryWatcherManager::DirectoryEvent& evt) {
		ofLogToFile("log.txt", true);
		ofLogNotice("ofApp::onDirectoryWatcherItemMovedFrom") << "Moved From: " << evt.item.path();
	}
	
	void onDirectoryWatcherItemMovedTo(const ofxIO::DirectoryWatcherManager::DirectoryEvent& evt) {
		ofLogToFile("log.txt", true);
		ofLogNotice("ofApp::onDirectoryWatcherItemMovedTo") << "Moved To: " << evt.item.path();
	}

	// directory watcher error
    void onDirectoryWatcherError(const Poco::Exception& exc) {
        ofLogError() << "Error: " << exc.displayText();
		
		ofLogToFile("log.txt", true);
		ofLogError() << "Error: " << exc.displayText();
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
    int waitCounter;
	
	// when to start image
    int imageStartTime;
	
	// time image should be displayed, in ms
    int millisImageTimeout;
	
	// flag to display image
    bool newImageReady;
    
    bool bDrawImage;
    int width, height;
	
};
