#include "ofApp.h"

void ofApp::setup() {
	
	// set window
    ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
    ofSetWindowPosition(0, 20);
	
	// amount of time image should be displayed, in ms
    millisImageTimeout = 5000;
	
    imageStartTime = 0;
	
	
	string videoLocation;
	#ifdef TARGET_RASPBERRY_PI
		videoLocation = "/home/pi/Public/video.mp4";
		backgroundVideo.loadMovie(videoLocation);
	#else
		videoLocation = "/Users/johnmars/Public/video.mp4";
	
		// load video
		if (backgroundVideo.load(videoLocation)) {
			
			// play it
			backgroundVideo.play();
			backgroundVideo.setLoopState(OF_LOOP_NORMAL);
			
		} else {
			ofLog(OF_LOG_NOTICE, "Video file was not loaded.");
		}
	#endif
	
	
	
	// set up directory watcher
    watcher.registerAllEvents(this);
	
	
	string folderToWatch;
	#ifdef TARGET_RASPBERRY_PI
		folderToWatch = ofToDataPath("/mnt/watchme", false);
	#else
		folderToWatch = ofToDataPath("/Users/johnmars/Public", false);
	#endif
	
	// start the watcher
    watcher.addPath(folderToWatch, false, &hiddenFileFilter);
    
}

void ofApp::update() {
	
	#ifdef TARGET_RASPBERRY_PI
	
	#else
		// continue to play video
		backgroundVideo.update();
	#endif
	

	// if there's a new image
    if (newImageReady) {
		
		// clear the old one
        currentImage.clear();
		
		// load the new one
        currentImage.load(imageLocation);
		
        newImageReady = false;
    }
	
}

void ofApp::draw() {
	
	// clear the frame
    ofBackground(0);
	
	// draw the video
    backgroundVideo.draw(0, 0, ofGetWidth(), ofGetHeight());
	
    ofFill();
	
	// if there's an image to be displayed, and it hasn't timed out
    if (currentImage.isAllocated() && imageStartTime + millisImageTimeout > ofGetElapsedTimeMillis()) {
		
		// draw the image
        currentImage.draw(50, 50, ofGetWidth() - 100, ofGetHeight() - 100);
		
    }
}


void ofApp::gotMessage(ofMessage msg) {
	
	// if the new file is a PNG
    if (ofIsStringInString(msg.message, ".png")) {
		
        printf("Event contains PNG");
        printf("Elapsed Time milliseconds: %llu", ofGetElapsedTimeMillis());
		
        imageStartTime = ofGetElapsedTimeMillis();
		
		// get the image ready to display
        imageLocation = msg.message;
        newImageReady = true;
		
    }
    
    
}
