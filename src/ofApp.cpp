#include "ofApp.h"

void ofApp::setup() {
	
	// set window

    string videoLocation;
    string folderToWatch;
    
    ofxJSONElement config;
    
    
    receiver.setup(12345);

    bool success = config.open("config.json");
    if(success){
        ofLog() << "loaded config file";
        millisImageTimeout = config["timeout"].asInt();
        videoLocation = config["videoLocation"].asString();
        folderToWatch = config["folderToWatch"].asString();
        
    } else{
        ofLog() << "could not load config file";
        millisImageTimeout = 8000;
        folderToWatch = ofToDataPath("/home/pi/inbox/", true);
        videoLocation = "/home/pi/video.mp4";
    }
    
    
    width= ofGetWidth();
    height = ofGetHeight();
	
	// amount of time image should be displayed, in ms
	
    imageStartTime = 0;
    newImageReady = false;
    bDrawImage = false;
	
	
    
    
    ofxOMXPlayerSettings settings;
    settings.videoPath = videoLocation;
    settings.useHDMIForAudio = false;	//default true
    settings.enableTexture = true;		//default true
    settings.enableLooping = true;		//default true
    settings.enableAudio = false;		//default true, save resources by disabling
    
    
    backgroundVideo.setup(settings);

	
    currentImage.allocate(width,height,OF_IMAGE_COLOR);
	
	// set up directory watcher
    watcher.registerAllEvents(this);
    watcher.addPath(folderToWatch, false, &hiddenFileFilter);
	
	
	waitCounter = 0;

   
    
}

void ofApp::update() {
    
    
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        bool bSwitchMess = false;
        
        if(m.getAddress() == "/switch"){
            bSwitchMess = true;
        }

	
	// if there's a new image
    if (newImageReady ++ bSwitchMess) {
        waitCounter ++;
        
        
//        if(waitCounter > 100){
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
            imageStartTime = ofGetElapsedTimeMillis();
	    

//        }
    }
        
        
		// load the new on
        
    
	
}

void ofApp::draw() {
	
	// clear the frame
    ofBackground(0);
	
	// draw the video
	
    ofFill();
	
	// if there's an image to be displayed, and it hasn't timed out
   if ( imageStartTime + millisImageTimeout > ofGetElapsedTimeMillis() ) {
//	ofLog() << "drawing the image";		
		// draw the image
        currentImage.draw(0,0);
   } else {
       backgroundVideo.draw(0, 0, width, height);
   }

}


void ofApp::gotMessage(ofMessage msg) {
	
	// if the new file is a PNG
    if (ofIsStringInString(msg.message, ".png")
        || ofIsStringInString(msg.message, ".jpg")
        || ofIsStringInString(msg.message, ".jpeg")) {
		

		
       // imageStartTime = ofGetElapsedTimeMillis();
		
		// get the image ready to display
        imageLocation = msg.message;
        newImageReady = true;
        bDrawImage = true;
        
        ofLog() << "Elapsed Time milliseconds: " << imageStartTime;
        ofLog() << "image path: " << imageLocation;
		
        waitCounter = 0;
    }
    
    
}
