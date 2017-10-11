#include "ofApp.h"

void ofApp::setup() {
	
	// set window
    ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
    ofSetWindowPosition(0, 20);
    
    width = ofGetWidth();
    height = ofGetHeight();
	
	// amount of time image should be displayed, in ms
    millisImageTimeout = 5000;
	
    imageStartTime = 0;
    newImageReady = false;
    bDrawImage = false;
	
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
	
	// if there's a new image
    if (newImageReady) {
		
		// clear the old one
        currentImage.clear();
		
        currentImage.allocate(width,height, OF_IMAGE_COLOR);
        
		// load the new one
        if(currentImage.load(imageLocation)){
            ofLog() << "loaded";
        } else {
            ofLog() << "could not load";
        }
        newImageReady = false;
    }
    
    
    if(imageStartTime + millisImageTimeout > ofGetElapsedTimeMillis()){
        bDrawImage = false;
    }
    
	
}

void ofApp::draw() {
	
	// clear the frame
    ofBackground(0);
	
	// draw the video
    backgroundVideo.draw(0, 0, width, height);
	
    ofFill();
	
	// if there's an image to be displayed, and it hasn't timed out
    if ( bDrawImage ) {
		
		// draw the image
        currentImage.draw(0,0, width, height);
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
        bDrawImage = true;
		
    }
    
    
}
