#include "ofApp.h"

void ofApp::setup() {
	
	// set window
//    ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
//   ofSetWindowPosition(0, 20);
    
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
    
    currentImage.allocate(width,height,OF_IMAGE_COLOR); 
//    currentImage.load("screen_hub_spoke_zones-01.jpg");
    backgroundVideo.setup(settings);
//    backgroundVideo.enableLooping();

	
    waitCounter = 0;
	
	// set up directory watcher
    watcher.registerAllEvents(this);
	
	
	string folderToWatch;
//	#ifdef TARGET_RASPBERRY_PI
		folderToWatch = ofToDataPath("/home/pi/inbox/", true);
//	#else
//		folderToWatch = ofToDataPath("", false);
//	#endif
	
	// start the watcher
    watcher.addPath(folderToWatch, false, &hiddenFileFilter);
    
}

void ofApp::update() {
	
	// if there's a new image
    if (newImageReady) {
        waitCounter ++;
        
        
        if(waitCounter > 100){
            ofLog() << "new image************";
            // clear the old one
            currentImage.clear();
            
            bool success = currentImage.load(imageLocation);
            if(success){
                ofLog() << "loaded********************";
            } else {
                ofLog() << "could not load";
            }
            newImageReady = false;

        }
        
        
		// load the new on
        
    
	
}

void ofApp::draw() {
	
	// clear the frame
    ofBackground(0);
	
	// draw the video
    backgroundVideo.draw(0, 0, width, height);
	
    ofFill();
	
	// if there's an image to be displayed, and it hasn't timed out
   if ( imageStartTime + millisImageTimeout > ofGetElapsedTimeMillis() ) {
	ofLog() << "drawing the image";		
		// draw the image
        currentImage.draw(0,0);
    }
}


void ofApp::gotMessage(ofMessage msg) {
	
	// if the new file is a PNG
    if (ofIsStringInString(msg.message, ".png")
        || ofIsStringInString(msg.message, ".jpg")
        || ofIsStringInString(msg.message, ".jpeg")) {
		

		
        imageStartTime = ofGetElapsedTimeMillis();
		
		// get the image ready to display
        imageLocation = msg.message;
        newImageReady = true;
        bDrawImage = true;
        
        ofLog() << "Elapsed Time milliseconds: " << imageStartTime;
        ofLog() << "image path: " << imageLocation;
		
        waitCounter = 0;
    }
    
    
}
