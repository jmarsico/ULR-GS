// =============================================================================
//
// Copyright (c) 2009-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"


void ofApp::setup()
{
    ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
    ofSetWindowPosition(0, 20);
    millisImageTimeout = 5000;
    imageStartTime = 0;
    if(backgroundPlayer.loadMovie("/Users/sam/Documents/openFrameworks/of_v0.9.8_osx_release/apps/myApps/ULR-GS/bin/Pigeon.mp4")) {
        backgroundPlayer.play();
        backgroundPlayer.setLoopState(OF_LOOP_NORMAL);
    } else {
        ofLog(OF_LOG_NOTICE, "movie loading unsuccessful");
    }
    watcher.registerAllEvents(this);
    
    std::string folderToWatch = ofToDataPath("", true);
    bool listExistingItemsOnStart = true;
    
    watcher.addPath(folderToWatch, listExistingItemsOnStart, &fileFilter);
    
}

void ofApp::update() {
    backgroundPlayer.update();

    if(newImageReady) {
        currentImage.clear();
        currentImage.load(nextImage);
        newImageReady = false;
    }
}

void ofApp::draw()
{
    ofBackground(0);
    backgroundPlayer.draw(0, 0);
    ofFill();
    if(currentImage.isAllocated() && imageStartTime+millisImageTimeout > ofGetElapsedTimeMillis()) {
        currentImage.draw(100, 100);
    }
}


void ofApp::gotMessage(ofMessage msg)
{
    
    if(ofIsStringInString( msg.message, ".png")) {
        printf("event contains .png");
        printf("Elapsed Time milliseconds: %llu", ofGetElapsedTimeMillis());
        imageStartTime = ofGetElapsedTimeMillis();
        nextImage = msg.message;
        newImageReady = true;
    }
    
    
}
