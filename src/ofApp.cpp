#include "ofApp.h"

void ofApp::setup() {
	
	// set window
    ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
    ofSetWindowPosition(0, 20);
	
	// amount of time image should be displayed, in ms
    millisImageTimeout = 5000;
	
    imageStartTime = 0;
	
	
	string videoLocation;
    videoLocation = "/home/pi/video.mp4";
    
    ofxOMXPlayerSettings settings;
    settings.videoPath = videoLocation;
    settings.useHDMIForAudio = false;	//default true
    settings.enableTexture = true;		//default true
    settings.enableLooping = true;		//default true
    settings.enableAudio = false;		//default true, save resources by disabling
    
    
    backgroundVideo.setup(settings);
//    backgroundVideo.enableLooping();

	
	
	
	// set up directory watcher
    watcher.registerAllEvents(this);
	
	
	string folderToWatch;
	#ifdef TARGET_RASPBERRY_PI
		folderToWatch = ofToDataPath("/home/pi/inbox", false);
	#else
		folderToWatch = ofToDataPath("", false);
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
    if (ofIsStringInString(msg.message, ".png")
        || ofIsStringInString(msg.message, ".jpg")
        || ofIsStringInString(msg.message, ".jpeg")) {
		
        ofLog() << "Event contains png, jpg or jpeg";
        ofLog() << "Elapsed Time milliseconds: " << ofGetElapsedTimeMillis();
        ofLog() << "image path: " << msg.message;
		
        imageStartTime = ofGetElapsedTimeMillis();
		
		// get the image ready to display
        imageLocation = msg.message;
        newImageReady = true;
		
    }
    
    
}
